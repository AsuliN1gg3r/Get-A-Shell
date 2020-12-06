import socket
import threading
from HttpRequest import HttpRequest


class Communicator:
    def __init__(self, host='127.0.0.1', port=80):
        self.__sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.__sock.bind((host, port))
        print("[+] Server started on port", port)
        self.__client_lock = threading.Lock()
        self.__connected_clients = list()

    def listen(self):
        while True:
            self.__sock.listen()
            client, addr = self.__sock.accept()
            #print("[+] New client connected ->", addr)
            self.__handle_new_client(client, addr)

    @staticmethod
    def read_whole_socket(sock):
        data = b''
        while True:
            part = sock.recv(1024)
            data += part
            if len(part) < 1024:
                break
        return data.decode()

    def __handle_new_client(self, client_sock, addr):
        data = self.read_whole_socket(client_sock)
        request = HttpRequest.parse_http_request(data)
        print(HttpRequest.shell_user_agent(request))
