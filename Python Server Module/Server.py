from Communicator import Communicator


class Server:
    def __init__(self):
        self.__communicator = None

    def run(self):
        self.__communicator = Communicator()
        self.__communicator.listen()


