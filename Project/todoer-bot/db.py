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
        self.cur.execute("""CREATE EXTENSION IF NOT EXISTS "uuid-ossp" """)
        self.cur.execute("""CREATE EXTENSION IF NOT EXISTS pgcrypto """)
        self.cur.execute("""CREATE SCHEMA IF NOT EXISTS Todo""")
        self.cur.execute("""CREATE TABLE IF NOT EXISTS Todo.Users(
                userID INTEGER PRIMARY KEY,
                first_name VARCHAR(80),
                State INTEGER DEFAULT 0,
                listsNumber INTEGER DEFAULT 0,
                token VARCHAR(256),
                token_secret VARCHAR(256),
                ListID UUID,
                NoteID UUID)""")
        self.cur.execute("""CREATE TABLE IF NOT EXISTS Todo.Lists(
                UserID INTEGER NOT NULL,
                ListName VARCHAR(50) NOT NULL,
                ListID UUID DEFAULT uuid_generate_v4 (),
                numb INTEGER,
                notesNumber INTEGER DEFAULT 0,
                PRIMARY KEY (ListID),
                FOREIGN KEY (UserID) REFERENCES Todo.Users(UserID) on delete cascade on update cascade)""")
        self.cur.execute("""CREATE TABLE IF NOT EXISTS Todo.Notes (
                NoteID UUID DEFAULT uuid_generate_v4 (),
                ListID UUID,
                userID INTEGER,
                numb INTEGER , 
                NoteName VARCHAR (50) NOT NULL ,
                NoteText TEXT,
                PRIMARY KEY (NoteID),
                FOREIGN KEY (ListID) REFERENCES Todo.Lists(ListID) on delete cascade on update cascade)""")
        self.cur.execute("""CREATE TABLE IF NOT EXISTS Todo.Images(
                NoteImage VARCHAR(256),
                NoteID UUID,
                FOREIGN KEY (NoteID) REFERENCES Todo.Notes(NoteID) on delete cascade on update cascade)""")
        self.cur.execute("""CREATE TABLE IF NOT EXISTS Todo.Files(
                NoteFile VARCHAR(256),
                NoteID UUID,
                FOREIGN KEY (NoteID) REFERENCES Todo.Notes(NoteID) on delete cascade on update cascade)""")
        self.cur.execute("""CREATE TABLE IF NOT EXISTS Todo.Voices(
                NoteVoice VARCHAR(256),
                NoteID UUID,
                FOREIGN KEY (NoteID) REFERENCES Todo.Notes(NoteID) on delete cascade on update cascade)""")
        self.cur.execute("""CREATE TABLE IF NOT EXISTS Todo.Audio(
                NoteAudio VARCHAR(256),
                NoteID UUID,
                FOREIGN KEY (NoteID) REFERENCES Todo.Notes(NoteID) on delete cascade on update cascade)""")
        self.conn.commit()

    def user_exists(self, id):
        self.cur = self.conn.cursor()
        self.cur.execute("SELECT * FROM Todo.Users WHERE UserID = %s", (id,))
        return self.cur.fetchone() is not None

    def new_user(self, id, username, state):
        if not self.user_exists(id):
            self.cur.execute(
                "INSERT INTO Todo.Users (userID,first_name,State) VALUES (%s,%s,%s) ", (id, username, state))
        self.conn.commit()

    def new_list(self, id, name):
        self.cur.execute("SELECT listsNumber FROM Todo.Users WHERE userID=%s", (id,))
        list_numb = self.cur.fetchone()[0] + 1
        self.cur.execute("UPDATE Todo.Users SET listsNumber=%s WHERE userID=%s", (list_numb, id))
        self.cur.execute(
            "INSERT INTO Todo.Lists (userID,ListName, numb) VALUES (%s,%s, %s) ", (id, name, list_numb - 1))
        self.conn.commit()

    def new_note(self, id, name):
        self.cur.execute("SELECT ListID FROM Todo.Users WHERE userID=%s", (id,))
        listID = self.cur.fetchone()[0]
        self.cur.execute("SELECT notesNumber FROM Todo.Lists WHERE ListID=%s", (listID,))
        note_numb = self.cur.fetchone()[0] + 1
        self.cur.execute("UPDATE Todo.Lists SET notesNumber=%s WHERE ListID=%s", (note_numb, listID))
        self.cur.execute(
            "INSERT INTO Todo.Notes (ListID,NoteName,userID, numb) VALUES (%s,%s,%s,%s) ", (listID, name, id, note_numb - 1))
        self.conn.commit()

    def delete_list(self, id):
        self.cur.execute("SELECT ListID FROM Todo.Users WHERE userID=%s", (id,))
        listID = self.cur.fetchone()[0]
        self.cur.execute("SELECT numb FROM Todo.Lists WHERE ListID=%s", (listID,))
        number = self.cur.fetchone()[0]
        self.cur.execute("UPDATE Todo.Lists SET numb=numb-1 WHERE numb>%s", (number,))
        self.cur.execute("UPDATE Todo.Users SET listsNumber=listsNumber-1 WHERE userID=%s", (id,))
        self.cur.execute("DELETE FROM Todo.Lists WHERE ListID=%s", (listID,))
        self.conn.commit()

    def edit_list(self, id, name):
        self.cur.execute("SELECT ListID FROM Todo.Users WHERE userID=%s", (id,))
        listID = self.cur.fetchone()[0]
        self.cur.execute("UPDATE Todo.Lists SET ListName = %s WHERE ListID = %s", (name, listID))
        self.conn.commit()

    def delete_note(self, id):
        self.cur.execute("SELECT ListID, NoteID FROM Todo.Users WHERE userID=%s", (id,))
        data = self.cur.fetchone()
        listID = data[0]
        noteID = data[1]
        self.cur.execute("SELECT numb FROM Todo.Notes WHERE NoteID=%s", (noteID,))
        number = self.cur.fetchone()[0]
        self.cur.execute("UPDATE Todo.Notes SET numb=numb-1 WHERE numb>%s", (number,))
        self.cur.execute("UPDATE Todo.Lists SET notesNumber=notesNumber-1 WHERE ListID=%s", (listID,))
        self.cur.execute("DELETE FROM Todo.Notes WHERE ListID=%s", (listID,))
        self.conn.commit()

    def get_lists(self, id):
        self.cur.execute("SELECT ListName FROM Todo.Lists WHERE userID = %s", (id,))
        lists = self.cur.fetchall()
        return lists

    def get_list(self, id, numb):
        self.cur.execute("SELECT ListName FROM Todo.Lists WHERE userID = %s AND numb = %s", (id, numb))
        list = self.cur.fetchone()
        return list

    def get_notes(self, userID, list_numb):
        self.cur.execute("SELECT ListID FROM Todo.Lists WHERE userID = %s AND numb = %s", (userID, list_numb))
        listID = self.cur.fetchone()[0]
        self.cur.execute("UPDATE Todo.Users SET ListID=%s WHERE userID=%s", (listID, userID))
        self.cur.execute("SELECT NoteName FROM Todo.Notes WHERE ListID = %s", (listID,))
        notes = self.cur.fetchall()
        return notes

    def get_note(self, id):
        self.cur.execute("SELECT NoteID FROM Todo.Users WHERE userID = %s", (id,))
        noteID = self.cur.fetchone()[0]
        self.cur.execute("SELECT NoteName FROM Todo.Notes WHERE NoteID = %s", (noteID,))
        note = self.cur.fetchone()
        return note

    def set_state(self, id, new_state):
        self.cur.execute("UPDATE Todo.Users SET State=%s WHERE userID=%s", (new_state, id))
        self.conn.commit()

    def init_state(self, id):
        self.cur.execute("UPDATE Todo.Users SET State=%s, ListID=%s, NoteID=%s WHERE userID=%s",
                         (0, None, None, id))
        self.conn.commit()

    def set_list(self, id, list_numb):
        self.cur.execute("SELECT ListID FROM Todo.Lists WHERE userID = %s AND numb = %s", (id, list_numb))
        listID = self.cur.fetchone()[0]
        self.cur.execute("UPDATE Todo.Users SET ListID=%s WHERE userID=%s", (listID, id))

    def set_note(self, id, numb):
        self.cur.execute("SELECT ListID FROM Todo.Users WHERE userID = %s", (id,))
        listID = self.cur.fetchone()[0]
        self.cur.execute("SELECT NoteID FROM Todo.Notes WHERE ListID = %s AND numb = %s", (listID, numb))
        noteID = self.cur.fetchone()[0]
        self.cur.execute("UPDATE Todo.Users SET NoteID=%s WHERE userID=%s", (noteID, id))
        self.conn.commit()

    def get_state(self, id):
        self.cur.execute("SELECT State FROM Todo.Users WHERE userID = %s", (id,))
        state = self.cur.fetchone()
        return state

    def get_cur_list_numb(self, id):
        self.cur.execute("SELECT ListID FROM Todo.Users WHERE userID = %s", (id,))
        listID = self.cur.fetchone()[0]
        self.cur.execute("SELECT numb FROM Todo.Lists WHERE ListID = %s", (listID,))
        name = self.cur.fetchone()
        return name

    def edit_note(self, id, name):
        self.cur.execute("SELECT NoteID FROM Todo.Users WHERE userID=%s", (id,))
        noteID = self.cur.fetchone()[0]
        self.cur.execute("UPDATE Todo.Notes SET NoteName = %s WHERE NoteID = %s", (name, noteID))
        self.conn.commit()

    def new_image(self, id, imageID):
        self.cur.execute("SELECT NoteID FROM Todo.Users WHERE userID=%s", (id,))
        noteID = self.cur.fetchone()[0]
        self.cur.execute("INSERT INTO Todo.Images (NoteImage, NoteID) VALUES (%s,%s) ", (imageID, noteID))
        self.conn.commit()

    def new_file(self, id, fileID):
        self.cur.execute("SELECT NoteID FROM Todo.Users WHERE userID=%s", (id,))
        noteID = self.cur.fetchone()[0]
        self.cur.execute("INSERT INTO Todo.Files (NoteFile, NoteID) VALUES (%s,%s) ", (fileID, noteID))
        self.conn.commit()

    def new_voice(self, id, voiceID):
        self.cur.execute("SELECT NoteID FROM Todo.Users WHERE userID=%s", (id,))
        noteID = self.cur.fetchone()[0]
        self.cur.execute("INSERT INTO Todo.Voices (NoteVoice, NoteID) VALUES (%s,%s) ", (voiceID, noteID))
        self.conn.commit()

    def new_audio(self, id, audioID):
        self.cur.execute("SELECT NoteID FROM Todo.Users WHERE userID=%s", (id,))
        noteID = self.cur.fetchone()[0]
        self.cur.execute("INSERT INTO Todo.Audio (NoteAudio, NoteID) VALUES (%s,%s) ", (audioID, noteID))
        self.conn.commit()

    def get_images(self, id):
        self.cur.execute("SELECT NoteID FROM Todo.Users WHERE userID=%s", (id,))
        noteID = self.cur.fetchone()[0]
        self.cur.execute("SELECT NoteImage FROM Todo.Images WHERE NoteID=%s ", (noteID,))
        images = self.cur.fetchall()
        return images

    def get_files(self, id):
        self.cur.execute("SELECT NoteID FROM Todo.Users WHERE userID=%s", (id,))
        noteID = self.cur.fetchone()[0]
        self.cur.execute("SELECT NoteFile FROM Todo.Files WHERE NoteID=%s ", (noteID,))
        files = self.cur.fetchall()
        return files

    def get_voices(self, id):
        self.cur.execute("SELECT NoteID FROM Todo.Users WHERE userID=%s", (id,))
        noteID = self.cur.fetchone()[0]
        self.cur.execute("SELECT NoteVoice FROM Todo.Voices WHERE NoteID=%s ", (noteID,))
        voices = self.cur.fetchall()
        return voices

    def get_audio(self, id):
        self.cur.execute("SELECT NoteID FROM Todo.Users WHERE userID=%s", (id,))
        noteID = self.cur.fetchone()[0]
        self.cur.execute("SELECT NoteAudio FROM Todo.Audio WHERE NoteID=%s ", (noteID,))
        audio = self.cur.fetchall()
        return audio


    def close(self):
        self.conn.close()
