import socket
import argparse
import win32.win32api
import sys
from args import Argument


sock = None


# Set socket
def set_socket():
    global sock
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)


# Press ctrl + c or close console to call this function.
def leave(event):
    message = 'Leave'
    message = message.encode('utf-8')
    address = Argument.get_address(args)
    sock.sendto(message, address)
    sys.exit(0)


# Connect to server
def connect():
    text = 'Join,' + Argument.get_username(args)
    message = text.encode('utf-8')

    address = Argument.get_address(args)
    sock.sendto(message, address)

    message = sock.recv(Argument.get_max_bytes())
    message = message.decode('utf-8')
    print(message)

    if message == 'The name has used so you should use another name.':
        sys.exit(0)
    else:
        running(address)


# Input messages
def running(address):
    b_running = True
    while b_running:
        your_input = input()
        if is_leave(your_input) is True:
            if check_leave() is True:
                message = your_input.encode('utf-8')
                sock.sendto(message, address)
                b_running = False
            else:
                send_message(address, your_input)

        else:
            send_message(address, your_input)


# Send message to server
def send_message(address, your_input):
    message = 'Send,' + your_input
    message = message.encode('utf-8')
    sock.sendto(message, address)


# Check the input
def is_leave(your_input):
    if your_input == 'Leave':
        return True
    else:
        return False


# Check user want to leave?
def check_leave():
    print('Do you want to leave this chat room?')
    choice = input('(y/n) : ')
    return is_yes(choice)


# Check choice
def is_yes(choice):
    if choice == 'y' or choice == 'Y':
        return True
    else:
        return False


# main function
if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Connect to server')

    parser.add_argument('host', help='Input ip address')
    parser.add_argument('-p', metavar='PORT', type=int, default=1060,
                        help='UDP port (default 1060)')

    parser.add_argument('-u', metavar='username', help='Input your nickname')

    args = parser.parse_args()

    win32.win32api.SetConsoleCtrlHandler(leave, True)
    set_socket()
    connect()
