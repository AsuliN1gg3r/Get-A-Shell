# Created by Eyal Asulin™
from RSA import RSA
from Server import Server
from InteractiveShell import InteractiveShell

def main():
    """rsa = RSA()
    test_str = "I like to sniff.... packets"
    print("String:", test_str)
    encrypted = rsa.encrypt(rsa.public_key, test_str)
    print("Encrypted:", encrypted)
    decrypted = rsa.decrypt(encrypted)
    print("Decrypted:", decrypted)"""
    server = Server()
    server.run()
    """time.sleep(20)
    Database.client_lock.acquire()
    con_cl = Database.connected_clients
    Database.client_lock.release()"""
    InteractiveShell.start_shell()


if __name__ == "__main__":
    main()
