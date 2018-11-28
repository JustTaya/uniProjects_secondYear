import os
import psycopg2

DATABASE_URL = os.environ['DATABASE_URL']
conn = psycopg2.connect(DATABASE_URL, sslmode='require')
cur = conn.cursor()


def init_db():
    cur.execute("""CREATE TABLE IF NOT EXISTS Users(
            userID int NOT NULL ,
            first_name varchar(80),
            State int,
            ListID UUID,
            NoteID UUID)""")

    cur.execute("""CREATE TABLE IF NOT EXISTS Lists(
            UserID int NOT NULL,
            ListName varchar(50) NOT NULL,
            ListID UUID)""")

    cur.execute("""CREATE TABLE IF NOT EXISTS Notes (
            NoteID UUID,
            ListID UUID,
            NoteName varchar(50) NOT NULL ,
            ListName  varchar(50),
            NoteText  text,
            NoteImage varchar(256),
            NoteFile varchar(256),
            NoteVoice varchar(256),
            NoteAudio varchar(256))""")
    cur.close()

