import socket
import argparse
from args import Argument


def check_command(message, command, length):
    if message[0:length] == command:
        return True
    else:
        return False


class Server:
    def __init__(self):
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.socket.bind(Argument.get_address(args))
        self.user = {}
        self.receiver_address = {}
        self.receive_message()

    # Receive messages from client.
    def receive_message(self):
        while True:
            try:
                message, address = self.socket.recvfrom(Argument.get_max_bytes())
                self.check_message(message, address)
            except ConnectionResetError:
                pass

    # Check messages and choice action.
    def check_message(self, message, address):
        text = message.decode('utf-8')
        if text[0:5] == 'Leave' or text[0:4] == 'Send':
            user = self.user.get(address)
            print(user + ' ' + text)
        else:
            print(text)

        # Command is 'Join'
        if check_command(text, 'Join', 4) is True:
            self.user_join(address, text[5::])

        # Command is 'Open'
        elif check_command(text, 'Open', 4) is True:
            self.open_room(address, text[5::])

        # Command is 'Send'
        elif check_command(text, 'Send', 4) is True:
            self.user_send_message(address, text)

        # Command is 'Leave'
        elif check_command(text, 'Leave', 5) is True:
            username = self.user.get(address)
            self.user_leave(address, username)

        # Command is 'Close'
        else:
            self.close_room(text[6::])

    # user join the chat room.
    def user_join(self, address, username):
        temp_username = self.user.values()
        if username in temp_username:
            reply = 'The name has used so you should use another name.'
            self.socket.sendto(reply.encode('utf-8'), address)
        else:
            self.user[address] = username
            message = username + ' join chat room.'
            reply = 'You join a chat room'
            self.socket.sendto(reply.encode('utf-8'), address)
            self.send_to_receiver(message)

    # Open the chat room of user.
    def open_room(self, address, username):
        all_username = self.user.values()
        if username in all_username:
            if self.receiver_address. __contains__(username) is True:
                reply = 'This name has used.'
            else:
                self.receiver_address[username] = address
                reply = 'Room is open.'
        else:
            reply = 'Can not find the user.'
            print('Can not find this user whose name is ' + username)

        self.socket.sendto(reply.encode('utf-8'), address)

    # Set the message
    def user_send_message(self, address, text):
        if address in self.user:
            username = self.user.get(address)
            message = username + ' : ' + text[5::]
            self.send_to_receiver(message)

    # If user input 'Leave' and want to leave chat room.
    def user_leave(self, address, username):
        message = username + ' left'
        self.user.pop(address)
        if self.receiver_address. __contains__(username) is True:
            address = self.receiver_address.get(username)
            local_message = 'Close'
            self.socket.sendto(local_message.encode('utf-8'), address)
            self.receiver_address.pop(username)

        self.send_to_receiver(message)

    # Send messages to all Receiving Client.
    def send_to_receiver(self, message):
        all_address = list(self.receiver_address.values())
        for address in all_address:
            print(address)
            self.socket.sendto(message.encode('utf-8'), address)

    # Remove address of the room which has closed.
    def close_room(self, username):
        if self.receiver_address. __contains__(username) is True:
            self.receiver_address.pop(username)


# main function
if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Bind host')
    parser.add_argument('host', help='Input ip address')
    parser.add_argument('-p', metavar='PORT', type=int, default=1060,
                        help='UDP port (default 1060)')
    args = parser.parse_args()
    server = Server()
