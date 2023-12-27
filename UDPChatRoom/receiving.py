from args import Argument
import socket
import argparse
import win32.win32api
import sys


sock = None


# Set socket
def set_socket():
    global sock
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)


# Press ctrl + c or close console to call this function.
def close(event):
    print('Close')
    address = Argument.get_address(args)
    message = set_message('Close')
    message = message.encode('utf-8')
    sock.sendto(message, address)
    sys.exit(0)


# Connect to server
def connect():
    message = set_message('Open')
    message = message.encode('utf-8')
    address = Argument.get_address(args)
    sock.sendto(message, address)
    message = sock.recv(Argument.get_max_bytes())
    message = message.decode('utf-8')

    print(message)

    if check_username(message):
        receive()
    else:
        sys.exit(0)


def set_message(command):
    return command + ',' + Argument.get_username(args)


# If the username is not in server then server will send
# 'Can not find the user in server.' to this client.
def check_username(message):
    if message == 'Can not find the user.':
        return False
    elif message == 'This name has used.':
        return False
    else:
        return True


# Receive messages
def receive():
    while True:
        message = sock.recv(Argument.get_max_bytes())
        message = message.decode('utf-8')
        print(message)
        if check_close(message):
            sys.exit(0)


# If sending client has closed that server will send 'Close' to this client.
def check_close(message):
    if message == 'Close':
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

    win32.win32api.SetConsoleCtrlHandler(close, True)
    set_socket()
    connect()
