# Created by Eyal Asulin™
from Server import Server
from InteractiveShell import InteractiveShell

def main():

    server = Server()
    server.run()
    InteractiveShell.start_shell()


if __name__ == "__main__":
    main()
