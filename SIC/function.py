import openpyxl


def xlsx_loader():
    file_name = 'instruction.xlsx'
    work_book = openpyxl.load_workbook(file_name)
    sheet = work_book[work_book.sheetnames[0]]
    key = []
    value = []
    for row in sheet.rows:
        key.append(row[0].value)
        value.append(str(row[1].value))
    return key, value


def txt_loader(file_name):
    file_open = open(file_name)
    data = file_open.readlines()
    file_open.close()
    for i in range(len(data)):
        data[i] = data[i].replace('\t', ' ')
        data[i] = data[i].replace('\n', '')
        if data[i][0] == ' ':
            data[i] = data[i][1:]
    return data


def hex_to_dec(convert):
    dec = [10, 11, 12, 13, 14, 15]
    hex = ['A', 'B', 'C', 'D', 'E', 'F']
    result = 0
    bits = []
    for each in convert:
        bits.append(each)
    bits.reverse()

    for i in range(len((bits))):
        if bits[i] in hex:
            result += (dec[hex.index(bits[i])] * (16 ** i))
        else:
            result += (int(bits[i]) * (16 ** i))
    return result


def dec_to_hex(convert):
    #print(convert)
    dec = [10, 11, 12, 13, 14, 15]
    hex = ['A', 'B', 'C', 'D', 'E', 'F']
    bits = []
    while convert > 0:
        bits.append(convert % 16)
        convert = int(convert/16)
    bits.reverse()
    result = ''
    for i in range(len(bits)):
        if bits[i] in dec:
            result += hex[dec.index(bits[i])]
        else:
            result += str(bits[i])
    return result


def fill_zeros(content):
    temp = ''
    for i in range(6 - len(content)):
        temp += '0'
    for i in range(len(content)):
        temp += content[i]
    return temp
