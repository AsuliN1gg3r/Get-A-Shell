import sqlite3
import pickle

PATH = "database.sqlite"


class Database:
    def __init__(self):
        self.__connection = None
        try:
            self.__connection = sqlite3.connect(PATH)
        except Exception:
            pass

    def insert_new_computer(self):
        pass
