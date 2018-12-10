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
        self.assertEqual(self.db.cur.fetchone()[0], 3, "State set.")

    def test_init_state(self):
        self.db.new_user(441220162, "Tai", 3)
        self.db.init_state(441220162)
        self.db.cur.execute("SELECT State FROM Users WHERE userID=%s", (441220162,))
        self.assertEqual(self.db.cur.fetchone()[0], 0, "Init state set.")

    def test_get_state(self):
        self.db.new_user(441220162, "Tai", 0)
        self.db.set_state(441220162, 3)
        self.db.cur.execute("SELECT State FROM Users WHERE userID = %s", (441220162,))
        self.assertEqual(self.db.cur.fetchone()[0], self.db.get_state(441220162)[0], "Get state.")

    def test_new_list(self):
        self.db.new_user(441220162, "Tai", 0)
        self.db.new_list(441220162, "List")
        self.db.cur.execute("SELECT ListName FROM Lists WHERE userID = %s", (441220162,))
        self.assertEqual(self.db.cur.fetchone()[0], "List", "New list added.")

    def test_set_list(self):
        self.db.new_user(441220162, "Tai", 0)
        self.db.new_list(441220162, "List")
        self.db.set_list(441220162, 0)
        self.db.cur.execute("SELECT ListID FROM Users WHERE userID=%s", (441220162,))
        listID = self.db.cur.fetchone()[0]
        self.db.cur.execute("SELECT ListName FROM Lists WHERE ListID = %s", (listID,))
        self.assertEqual(self.db.cur.fetchone()[0], "List", "List set.")

    def test_get_cur_list_numb(self):
        self.db.new_user(441220162, "Tai", 0)
        self.db.new_list(441220162, "List")
        self.db.set_list(441220162, 0)
        self.assertEqual(self.db.get_cur_list_numb(441220162)[0], 0, "Got current list number.")



if __name__ == '__main__':
    unittest.main()
