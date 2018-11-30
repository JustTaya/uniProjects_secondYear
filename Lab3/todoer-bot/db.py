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
                ListID UUID DEFAULT uuid_generate_v4 (),
                PRIMARY KEY (ListID),
                FOREIGN KEY (UserID) REFERENCES Users(UserID))""")
        self.cur.execute("""CREATE TABLE IF NOT EXISTS Notes (
                NoteID UUID DEFAULT uuid_generate_v4 (),
                ListID UUID,
                NoteName varchar(50) NOT NULL ,
                ListName  varchar(50),
                NoteText  text,
                NoteImage varchar(256),
                NoteFile varchar(256),
                NoteVoice varchar(256),
                NoteAudio varchar(256),
                FOREIGN KEY (ListID) REFERENCES Lists(ListID))""")
        self.conn.commit()

    def user_exists(self, id):
        cur = self.conn.cursor()
        cur.execute("SELECT * FROM Users WHERE UserID = %s", (id,))
        return cur.fetchone() is not None

    def new_user(self, id, username, state):
        if not self.user_exists(id):
            self.cur.execute(
                "INSERT INTO Users (userID,first_name,State) VALUES (%s,%s,%s) ", (id, username, state))
        self.conn.commit()

    def new_list(self, id, name):
        self.cur.execute(
            "INSERT INTO Lists (userID,ListName) VALUES (%s,%s) ", (id, name))
        self.conn.commit()

    def set_state(self, id, new_state):
        self.cur.execute("UPDATE Users SET State=%s WHERE userID=%s", (id, new_state))
        self.conn.commit()

    def get_state(self, id):
        self.cur.execute("SELECT State FROM Users WHERE UserID = %s", (id,))
        state = self.cur.fetchone()
        return state

    def close(self):
        self.conn.close()
