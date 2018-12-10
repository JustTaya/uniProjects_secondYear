import unittest
from unittest import TestCase

from db import Database


class TestDatabase(unittest.TestCase):
    def setUp(self):
        self.db = Database()
        self.db.init_tables()

    def tearDown(self):
        self.db.close()

    def test_init_tables_Users(self):
        self.db.cur.execute(
            """SELECT EXISTS (SELECT * FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_NAME = 'Users')""")
        self.assertIsNotNone(self.db.cur.fetchone(), "Users table exists.")

    def test_init_tables_Lists(self):
        self.db.cur.execute(
            """SELECT EXISTS (SELECT * FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_NAME = 'Lists')""")
        self.assertIsNotNone(self.db.cur.fetchone(), "Lists table exists.")

    def test_init_tables_Notes(self):
        self.db.cur.execute(
            """SELECT EXISTS (SELECT * FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_NAME = 'Notes')""")
        self.assertIsNotNone(self.db.cur.fetchone(), "Notes table exists.")

    def test_init_tables_Images(self):
        self.db.cur.execute(
            """SELECT EXISTS (SELECT * FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_NAME = 'Images')""")
        self.assertIsNotNone(self.db.cur.fetchone(), "Images table exists.")

    def test_init_tables_Files(self):
        self.db.cur.execute(
            """SELECT EXISTS (SELECT * FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_NAME = 'Files')""")
        self.assertIsNotNone(self.db.cur.fetchone(), "Files table exists.")

    def test_init_tables_Voices(self):
        self.db.cur.execute(
            """SELECT EXISTS (SELECT * FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_NAME = 'Voices')""")
        self.assertIsNotNone(self.db.cur.fetchone(), "Voices table exists.")

    def test_init_tables_Audio(self):
        self.db.cur.execute(
            """SELECT EXISTS (SELECT * FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_NAME = 'Audio')""")
        self.assertIsNotNone(self.db.cur.fetchone(), "Audio table exists.")

    def test_new_user(self):
        self.db.new_user(441220162, "Tai", 0)
        self.db.cur.execute("SELECT first_name, State FROM Users WHERE userID=%s", (441220162,))
        data = self.db.cur.fetchone()
        self.assertTrue((data[0] == 'Tai' and data[1] == 0), "New user created.")

    def test_user_exists_false(self):
        self.assertFalse(self.db.user_exists(441220162), "Not created user does not exist.")

    def test_user_exists_true(self):
        self.db.new_user(441220162, "Tai", 0)
        self.assertTrue(self.db.user_exists(441220162), "Created user exists.")

    def test_set_state(self):
        self.db.new_user(441220162, "Tai", 0)
        self.db.set_state(441220162, 3)
        self.db.cur.execute("SELECT State FROM Users WHERE userID=%s", (441220162,))
        self.assertEqual(self.db.cur.fetchone()[0], 3, "Created user exists.")


# def test_init_state(self):
#    self.fail()

# def test_get_state(self):
#   self.fail()


if __name__ == '__main__':
    unittest.main()
