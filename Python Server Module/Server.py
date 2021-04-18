from Communicator import Communicator
import threading


class Server:
    def __init__(self):
        self.__communicator = None

    def run(self):
        self.__communicator = Communicator()
        threading.Thread(target=self.__communicator.listen).start()
