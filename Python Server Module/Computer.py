import time


class Computer:
    def __init__(self, ip_address, sock):
        """
        Constructor of Computer
        :param ip_address: ip address
        :type ip_address: str
        :param sock: client socket
        :type sock: socket
        """
        self.ip_address = ip_address
        self.sock = sock
        self.last_updated = time.time()
        self.__metadata = dict()

    def update_socket(self, sock):
        """
        This function update the client socket and the last_updated time
        :param sock:
        :return:
        """
        try:
            self.sock.close()
        except Exception as e:
            print(e)
        self.sock = sock
        self.last_updated = time.time()
