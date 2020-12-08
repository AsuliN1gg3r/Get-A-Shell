from Communicator import Communicator
import threading
import HttpResponse


class Server:
    def __init__(self):
        self.__communicator = None

    def run(self):
        self.__communicator = Communicator()
        threading.Thread(target=self.__communicator.listen).start()
        """while True:
            if len(Database.idle_connections) > 0:
                command = input("Shell> ")
                Database.idle_connections['127.0.0.1'].send(HttpResponse.HttpResponse.generate_response(200, command, set_cookie=1).encode())
                Database.wait_for_post_request[1] = threading.Event()
                Database.wait_for_post_request[1].wait()
                print(Database.wait_for_post_request[1])"""

