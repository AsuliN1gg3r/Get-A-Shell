from Communicator import Communicator
import threading
from RuntimeDatabase import RuntimeDatabase
from Handler import Handler
import time


class Server:
    def __init__(self):
        self.__communicator = None

    def run(self):
        print("aaa")
        self.__communicator = Communicator()
        threading.Thread(target=self.__communicator.listen).start()
