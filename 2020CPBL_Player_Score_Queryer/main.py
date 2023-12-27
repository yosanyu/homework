from PyQt5 import QtWidgets
from PyQt5 import QtCore
from PyQt5.QtCore import QThread, pyqtSignal
from ui import Ui_MainWindow
import sys
import socket
import json
from datas import Data


class MainWindow(QtWidgets.QMainWindow):
    def __init__(self):
        self.players = []
        super(MainWindow, self).__init__()
        self.ui = Ui_MainWindow()
        self.ui.main_ui(self)
        self.ui.button.clicked.connect(self.choose_CPBL)

    def choose_CPBL(self):
        self.ui.menu_ui(self)
        self.ui.CPBL_button.clicked.connect(self.choose_team)

    def choose_team(self):
        team = self.ui.CPBL_team.currentText()
        self.score = self.ui.CPBL_score.currentIndex() + 1
        self.ui.table_ui(self)
        self.ui.menu_button.clicked.connect(self.choose_CPBL)
        self.work = WorkThread()
        self.work.set_variable(team, str(self.score))
        self.work.start()
        self.work.trigger.connect(self.display)

    def display(self, players):
        if self.score == 1:
            scores = Data.get_CPBL_batting()
            filter_index = Data.get_CPBL_bfilter()
        elif self.score == 2:
            scores = Data.get_CPBL_pitching()
            filter_index = Data.get_CPBL_pfilter()
        else:
            scores = Data.get_CPBL_garrison()
            filter_index = Data.get_CPBL_gfilter()
            
        self.ui.tableWidget.setColumnCount(len(filter_index))    
        self.ui.tableWidget.setRowCount(len(players))

        new_scores = []
        for i in range(len(filter_index)):
            new_scores.append(scores[filter_index[i]])

        self.ui.tableWidget.setHorizontalHeaderLabels(new_scores)

        # Set items of table.
        row = 0
        for i in players:
            column = 0
            index = 0
            for j in scores:
                if index in filter_index:
                    item = QtWidgets.QTableWidgetItem(i[j])
                    item.setTextAlignment(QtCore.Qt.AlignVCenter | QtCore.Qt.AlignHCenter)
                    self.ui.tableWidget.setItem(row, column, item)
                    column += 1
                index += 1
            row += 1



class WorkThread(QThread):
    trigger = pyqtSignal(list)
    team = ''
    score = ''

    def __int__(self):
        super(WorkThread, self).__init__()

    def set_variable(self, team, score):
        self.team = team
        self.score = score

    def run(self):
        # TCP client
        client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        client.connect(('127.0.0.1', 1060))
        message = 'C' + self.team + ',' + self.score
        client.sendall(message.encode('utf-8'))
        # Receive data from server.
        js = None
        while True:
            data = client.recv(100000)
            if len(data) == 0:
                break
            else:
                data = data.decode('utf-8')
                js = json.loads(data)

        self.trigger.emit(js)


if __name__ == '__main__':
    app = QtWidgets.QApplication([])
    window = MainWindow()
    window.show()
    sys.exit(app.exec_())
