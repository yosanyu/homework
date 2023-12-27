from PyQt5 import QtCore, QtGui, QtWidgets
from datas import Data


class Ui_MainWindow(object):
    def __init__(self):
        self.league = ''

    def main_ui(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(1000, 600)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        MainWindow.setCentralWidget(self.centralwidget)

        # start button
        self.button = QtWidgets.QPushButton(self.centralwidget)
        self.button.setGeometry(QtCore.QRect(300, 210, 400, 100))
        self.button.setObjectName("start")
        self.font = QtGui.QFont()
        self.font.setPointSize(25)
        self.button.setFont(self.font)
        self.button.setText("開始")

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def menu_ui(self, MainWindow):
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")

        # label
        self.CPBL_image = QtWidgets.QLabel(self.centralwidget)
        self.CPBL_image.setGeometry(QtCore.QRect(50, 35, 250, 115))
        self.CPBL_image.setObjectName("CPBL")
        self.CPBL_image.setStyleSheet("background-image : url(logo/CPBL.png);")

        # combobox
        self.CPBL_team = QtWidgets.QComboBox(self.centralwidget)
        self.CPBL_team.setGeometry(QtCore.QRect(330, 85, 500, 60))
        self.CPBL_team.setObjectName("team")
        self.CPBL_team.setFont(QtGui.QFont("Roman times", 15))

        # Get teams and their logos path.
        teams = Data.get_CPBL_team()
        logos = Data.get_CPBL_logo()
        self.CPBL_team.setIconSize(QtCore.QSize(60, 60))

        for i in range(len(teams)):
            self.CPBL_team.addItem(QtGui.QIcon(logos[i]), teams[i])

        self.CPBL_score = QtWidgets.QComboBox(self.centralwidget)
        self.CPBL_score.setGeometry(QtCore.QRect(330, 150, 500, 60))
        self.CPBL_score.setObjectName("score")
        self.CPBL_score.setFont(QtGui.QFont("Roman times", 15))
        score = ['打擊成績', '投球成績', '守備成績']
        self.CPBL_score.addItems(score)

        # button
        self.CPBL_button = QtWidgets.QPushButton(self.centralwidget)
        self.CPBL_button.setGeometry(QtCore.QRect(850, 85, 100, 60))
        self.CPBL_button.setObjectName("CPBL_button")
        self.CPBL_button.setFont(self.font)
        self.CPBL_button.setText("確認")

        MainWindow.setCentralWidget(self.centralwidget)
        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def table_ui(self, MainWindow):
        #MainWindow.setObjectName("MainWindow")
        #MainWindow.resize(800, 600)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        MainWindow.setCentralWidget(self.centralwidget)

        self.tableWidget = QtWidgets.QTableWidget(self.centralwidget)
        self.tableWidget.setGeometry(QtCore.QRect(30, 50, 850, 450))
        self.tableWidget.setObjectName("tableWidget")
        self.tableWidget.setColumnCount(0)
        self.tableWidget.setRowCount(0)

        self.tableWidget.setEditTriggers(QtWidgets.QAbstractItemView.NoEditTriggers)

        self.menu_button = QtWidgets.QPushButton(self.centralwidget)
        self.menu_button.setGeometry(QtCore.QRect(400, 510, 200, 60))
        self.menu_button.setObjectName("home_button")
        self.menu_button.setFont(self.font)
        self.menu_button.setText("回上一頁")

        self.menubar = QtWidgets.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 800, 21))
        self.menubar.setObjectName("menubar")
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)

        self.retranslateUi(MainWindow)
        #QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def choose_team_ui(self, MainWindow):
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        MainWindow.setCentralWidget(self.centralwidget)
        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "MainWindow"))

    def set_league(self, league):
        self.league = league

