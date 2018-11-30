import os
import psycopg2
import psycopg2.extensions

psycopg2.extensions.register_type(psycopg2.extensions.UNICODE)
psycopg2.extensions.register_type(psycopg2.extensions.UNICODEARRAY)

DATABASE_URL = os.environ['DATABASE_URL']


class Database:
    def __init__(self):
        self.conn = psycopg2.connect(DATABASE_URL, sslmode='require')
        self.cur = self.conn.cursor()

    def init_tables(self):
        self.cur.execute("""CREATE TABLE IF NOT EXISTS Users(
                userID integer PRIMARY KEY,
                first_name varchar(80),
                State integer ,
                ListID uuid,
                NoteID uuid)""")
        self.cur.execute("""CREATE TABLE IF NOT EXISTS Lists(
                UserID integer NOT NULL,
                ListName varchar(50) NOT NULL,
                ListID UUID PRIMARY KEY,
                FOREIGN KEY (UserID) REFERENCES Users(UserID))""")
        self.cur.execute("""CREATE TABLE IF NOT EXISTS Notes (
                NoteID UUID,
                ListID UUID,
                NoteName varchar(50) NOT NULL ,
                ListName  varchar(50),
                NoteText  text,
                NoteImage varchar(256),
                NoteFile varchar(256),
                NoteVoice varchar(256),
                NoteAudio varchar(256),
                FOREIGN KEY (ListID) REFERENCES Lists(ListID))""")
        self.cur.execute("""CREATE TABLE IF NOT EXISTS State(
                userID integer, 
                State integer,
                FOREIGN KEY (UserID) REFERENCES Users(UserID))""")
        self.conn.commit()

    def close(self):
        self.conn.close()
