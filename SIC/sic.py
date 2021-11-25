import function

OPTABLE = {}
ORDER = ['START', 'END', 'BYTE', 'RESW', 'WORD']
Symbol = []
MC = []
LOCAL = 0
InitialValue = 0
error_index = 0


class Node:
    def __init__(self, key, value):
        self.left = None
        self.right = None
        self.key = key
        self.value = value

    def insert(self, key, value):
        if self.key:
            if key < self.key:
                if self.left is None:
                    self.left = Node(key, value)
                else:
                    self.left.insert(key, value)
            elif key > self.key:
                if self.right is None:
                    self.right = Node(key, value)
                else:
                    self.right.insert(key, value)
        else:
            self.key = key
            self.value = value

    def search(self, key):
        if self.key:
            if key == self.key:
                return self.value
            elif key < self.key:
                if self.left is not None:
                    return self.left.search(key)
                else:
                    return None
            else:
                if self.right is not None:
                    return self.right.search(key)
                else:
                    return None

    def get_tree(self):
        if self.left:
            self.left.get_tree()
        Symbol.append('{:<20}'.format(self.key) + '\t' + self.value)
        if self.right:
            self.right.get_tree()


class Instruction:
    def __init__(self):
        self.instruction = ''
        self.order = ''
        self.opCode = ''
        self.leftAddress = ''
        self.rightAddress = ''
        self.symbol = ''
        self.label = ''
        self.machineCode = ''
        self.need_split = ''
        self.root = None

    def set_instruction(self, instruction):
        self.instruction = instruction

    def set_item(self):
        space = self.instruction.find(' ')
        if space == -1:
            self.order = self.instruction

        else:
            first = self.instruction[0:space:]
            instruction = self.instruction[space+1::]
            if first in OPTABLE or first in ORDER:
                self.order = first
            else:
                self.symbol = first
            space = instruction.find(' ')
            if space == -1:
                self.label = instruction
            else:
                second = instruction[0:space:]
                instruction = instruction[space + 1::]
                self.order = second
                self.label = instruction

        global LOCAL
        global InitialValue
        if self.order == 'START':
            LOCAL = function.hex_to_dec(self.label)
            self.leftAddress = LOCAL
            InitialValue = LOCAL

        elif LOCAL == InitialValue:
            self.leftAddress = LOCAL
            LOCAL += 3
        else:
            self.leftAddress = LOCAL
            if self.order == 'RESW':
                temp = LOCAL + 3 * int(self.label)
            elif self.order == 'RESB':
                temp = LOCAL + int(self.label)
            elif self.order == 'BYTE':
                if self.label[0] == 'X':
                    label = self.label[1::]
                    label = label.replace("'", '')
                    temp = LOCAL + len(label) / 2

                elif self.label[0] == 'C':
                    label = self.label[1::]
                    label = label.replace("'", '')
                    temp = LOCAL + len(label)

            else:
                if self.order in OPTABLE or self.order in ORDER:
                    temp = LOCAL + 3
                else:
                    self.machineCode = 'error'
                    temp = LOCAL

            LOCAL = int(temp)
        self.leftAddress = function.dec_to_hex(self.leftAddress)
        self.process_label()

    def process_label(self):
        if self.label.find(',X') is not -1:
            self.label = self.label[0:self.label.find(',X'):]
            self.need_split = 'X'
        if self.order == 'BYTE':
            if self.label[0] == 'X':
                label = self.label[1::]
                label = label.replace("'", '')
                self.rightAddress = label
            elif self.label[0] == 'C':
                label = self.label[1::]
                label = label.replace("'", '')
                temp = ''
                for c in label:
                    temp += function.dec_to_hex(ord(c))
                self.rightAddress = function.fill_zeros(temp)

    def set_op_code(self):
        if self.order not in ORDER:
            self.opCode = OPTABLE.get(self.order)
        else:
            self.opCode = None

    def set_address(self, address):
        if self.need_split == 'X':
            temp = function.hex_to_dec(address) + function.hex_to_dec('8000')
            temp = function.dec_to_hex(temp)
            self.rightAddress = temp
        elif self.order == 'WORD':
            self.rightAddress = function.dec_to_hex(int(self.label))
            self.rightAddress = function.fill_zeros(self.rightAddress)
        else:
            self.rightAddress = address


class SIC:
    def __init__(self, file_name):
        self.file_name = file_name
        self.flag = False

        if len(OPTABLE) == 0:
            key, value = function.xlsx_loader()
            for i in range(len(key)):
                OPTABLE[key[i]] = value[i]

        self.lines = function.txt_loader(file_name)
        self.instruction = []
        for i in range(len(self.lines)):
            self.instruction.append(Instruction())

    def start(self):
        self.pass_one()
        self.create_symbol_table()
        self.pass_two()

    def pass_one(self):
        for i in range(len(self.lines)):
            self.instruction[i].set_instruction(self.lines[i])
            self.instruction[i].set_item()
            self.instruction[i].set_op_code()

    def create_symbol_table(self):
        for i in range(len(self.instruction)):
            temp = self.instruction[i]
            if temp.order == 'END':
                pass
            elif not self.flag:
                self.root = Node(temp.symbol, temp.leftAddress)
                self.flag = True
            else:
                if not temp.symbol == '':
                    self.root.insert(temp.symbol, temp.leftAddress)
        self.root.get_tree()

    def pass_two(self):
        global error_index
        for i in range(len(self.instruction)):
            temp = self.instruction[i]
            result = self.root.search(temp.label)
            if result is not None:
                temp.set_address(result)
            else:
                check = len(temp.rightAddress) == 0 and not temp.order == 'RESW' and not temp.order == 'RESB' and not temp.order == 'START'
                if temp.order == 'RSUB':
                    temp.set_address('0000')
                elif temp.order == 'WORD':
                    temp.set_address(result)
                elif check:
                    temp.machineCode = 'error'
            if temp.machineCode == 'error':
                if temp.order in OPTABLE and result is None:
                    error_index = i - 1
            elif temp.opCode is None:
                temp.machineCode = temp.rightAddress
            else:
                temp.machineCode = temp.opCode + temp.rightAddress
            if error_index < i and not error_index == 0:
                temp.leftAddress = function.dec_to_hex(function.hex_to_dec(temp.leftAddress) - 3)
            if temp.order == 'END':
                temp.machineCode = ' '
            MC.append(temp.machineCode)


