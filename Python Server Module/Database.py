import threading


class Database:
    client_lock = threading.Lock()
    connected_clients = list()

    @staticmethod
    def computer_exist(ip_address):
        return True
