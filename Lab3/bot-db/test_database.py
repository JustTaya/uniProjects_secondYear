from unittest import TestCase
from db import Database
import psycopg2


class TestDatabase(TestCase):
    @classmethod
    def setUp(cls):
        cls.db = Database()

    @classmethod
    def test_init_tables_Users(cls):
        cls.db.init_tables()
        cls.db.cur.execute(
            """SELECT EXISTS (SELECT * FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_NAME = 'Users')""")
        cls.assertIsNotNone(cls.db.cur.fetchone(), "Users table exists.")

    @classmethod
    def test_init_tables_Lists(cls):
        cls.db.cur.execute(
            """SELECT EXISTS (SELECT * FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_NAME = 'Lists')""")
        cls.assertIsNotNone(cls.db.cur.fetchone(), "Lists table exists.")

    @classmethod
    def test_init_tables_Notes(cls):
        cls.db.cur.execute(
            """SELECT EXISTS (SELECT * FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_NAME = 'Notes')""")
        cls.assertIsNotNone(cls.db.cur.fetchone(), "Notes table exists.")

    @classmethod
    def test_init_tables_Images(cls):
        cls.db.cur.execute(
            """SELECT EXISTS (SELECT * FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_NAME = 'Images')""")
        cls.assertIsNotNone(cls.db.cur.fetchone(), "Images table exists.")

    @classmethod
    def test_init_tables_Files(cls):
        cls.db.cur.execute(
            """SELECT EXISTS (SELECT * FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_NAME = 'Files')""")
        cls.assertIsNotNone(cls.db.cur.fetchone(), "Files table exists.")

    @classmethod
    def test_init_tables_Voices(cls):
        cls.db.cur.execute(
            """SELECT EXISTS (SELECT * FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_NAME = 'Voices')""")
        cls.assertIsNotNone(cls.db.cur.fetchone(), "Voices table exists.")

    @classmethod
    def test_init_tables_Audio(cls):
        cls.db.cur.execute(
            """SELECT EXISTS (SELECT * FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_NAME = 'Audio')""")
        cls.assertIsNotNone(cls.db.cur.fetchone(), "Audio table exists.")
