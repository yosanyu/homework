import requests
from bs4 import BeautifulSoup
import json
import socket
from datas import Data


def make_url(code, score):
    url = 'http://www.cpbl.com.tw/web/team_playergrade.php?&gameno=01&team='
    url += code
    url += '&year=2020&grade='
    url += score
    url += '&syear=2020'
    return url


class Server:
    def __init__(self):
        self.league = ''
        self.team = None
        self.score = None

        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket.bind(('127.0.0.1', 1060))
        self.socket.listen(2)
        self.receive()

    def receive(self):
        while True:
            conn, addr = self.socket.accept()
            message = conn.recv(1000)
            message = message.decode('utf-8')
            url = self.get_url(message)

            req = requests.get(url)
            r = req.content
            soup = BeautifulSoup(r, "html.parser")

            players = soup.find_all("tr")

            players_score = []
            if self.league == 'C':
                if self.score == '1':
                    players_score = Data.get_CPBL_batting()
                elif self.score == '2':
                    players_score = Data.get_CPBL_pitching()
                else:
                    players_score = Data.get_CPBL_garrison()

            scores = []
            for player in players:
                score = player.find_all('td')
                if len(score) == 0:
                    pass
                else:
                    b = {}
                    for i in range(len(score)):
                        b[players_score[i]] = score[i].string
                    scores.append(b)

            js = json.dumps(scores)

            conn.sendall(js.encode('utf-8'))
            conn.close()

    def get_url(self, message):
        self.split_message(message)

        # get teams and their codes.
        teams = []
        codes = []
        if self.league == 'C':
            teams = Data.get_CPBL_team()
            codes = Data.get_CPBL_code()

        code = teams.index(self.team)

        return make_url(codes[code], self.score)

    def split_message(self, message):
        self.league = message[0]
        index = message.find(',')
        self.team = message[1:index]
        self.score = message[index + 1]


if __name__ == '__main__':
    server = Server()

'''
    def test(self):
        # setup ui
        self.ui.table_ui(self)
        self.work = WorkThread()
       # self.work.set_team()
        self.work.start()
        self.work.trigger.connect(self.display)
'''


            
            
        


