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

    def test_set_list_notExists(self):
        self.db.new_user(441220162, "Tai", 0)
        self.db.set_list(441220162, 0)
        self.db.cur.execute("SELECT ListID FROM Users WHERE userID=%s", (441220162,))
        self.assertIsNone(self.db.cur.fetchone()[0], "List is not set if not exists.")

    def test_get_cur_list_numbNotExists(self):
        self.db.new_user(441220162, "Tai", 0)
        self.assertIsNone(self.db.get_cur_list_numb(441220162), "Got current list number if not exists.")

    def test_get_cur_list_numbExists(self):
        self.db.new_user(441220162, "Tai", 0)
        self.db.new_list(441220162, "List")
        self.db.set_list(441220162, 0)
        self.assertEqual(self.db.get_cur_list_numb(441220162)[0], 0, "Got current list number.")

    def test_new_note_listExists(self):
        self.db.new_user(441220162, "Tai", 0)
        self.db.new_list(441220162, "List")
        self.db.set_list(441220162, 0)
        self.db.new_note(441220162, "Note")
        self.db.cur.execute("SELECT NoteName FROM Notes WHERE userID = %s", (441220162,))
        self.assertEqual(self.db.cur.fetchone()[0], "Note", "New note added.")

    def test_new_note_listNotExists(self):
        self.db.new_user(441220162, "Tai", 0)
        self.db.new_note(441220162, "Note1")
        self.db.cur.execute("SELECT NoteName FROM Notes WHERE userID = %s", (441220162,))
        self.assertIsNone(self.db.cur.fetchone(), "New note added.")

    def test_delete_list_Exists(self):
        self.db.new_user(441220162, "Tai", 0)
        self.db.new_list(441220162, "List")
        self.db.set_list(441220162, 0)
        self.db.delete_list(441220162)
        self.db.cur.execute("SELECT * FROM Lists WHERE userID = %s and ListName = %s", (441220162, "List"))
        self.assertIsNone(self.db.cur.fetchone(), "The list deleted")

    def test_delete_list_checkNumb(self):
        self.db.new_user(441220162, "Tai", 0)
        self.db.new_list(441220162, "List0")
        self.db.new_list(441220162, "List1")
        self.db.set_list(441220162, 0)
        self.db.delete_list(441220162)
        self.db.cur.execute("SELECT numb FROM Lists WHERE userID = %s and ListName = %s", (441220162, "List1"))
        self.assertEqual(self.db.cur.fetchone()[0], 0, "The number changed")

    def test_delete_list_NotExists(self):
        self.db.new_user(441220162, "Tai", 0)
        self.db.new_list(441220162, "List")
        self.db.delete_list(441220162)
        self.db.cur.execute("SELECT * FROM Lists WHERE userID = %s and ListName = %s", (441220162, "List"))
        self.assertIsNotNone(self.db.cur.fetchone(), "The list is not deleted")

    def test_edit_list_Exists(self):
        self.db.new_user(441220162, "Tai", 0)
        self.db.new_list(441220162, "List")
        self.db.set_list(441220162, 0)
        self.db.edit_list(441220162, "New_list")
        self.db.cur.execute("SELECT * FROM Lists WHERE userID = %s and ListName = %s", (441220162, "New_list"))
        new_name = self.db.cur.fetchone()
        self.db.cur.execute("SELECT * FROM Lists WHERE userID = %s and ListName = %s", (441220162, "List"))
        old_name = self.db.cur.fetchone()
        self.assertTrue((new_name is not None) and (old_name is None), "The list edited")

    def test_edit_list_NotExists(self):
        self.db.new_user(441220162, "Tai", 0)
        self.db.new_list(441220162, "List")
        self.db.edit_list(441220162, "New_list")
        self.db.cur.execute("SELECT * FROM Lists WHERE userID = %s and ListName = %s", (441220162, "New_list"))
        new_name = self.db.cur.fetchone()
        self.db.cur.execute("SELECT * FROM Lists WHERE userID = %s and ListName = %s", (441220162, "List"))
        old_name = self.db.cur.fetchone()
        self.assertTrue((new_name is None) and (old_name is not None), "The list is not edited if not exists")

    def test_set_note_listExists(self):
        self.db.new_user(441220162, "Tai", 0)
        self.db.new_list(441220162, "List")
        self.db.set_list(441220162, 0)
        self.db.new_note(441220162, "Note")
        self.db.set_note(441220162, 0)
        self.db.cur.execute("SELECT NoteID FROM Users WHERE userID=%s", (441220162,))
        noteID = self.db.cur.fetchone()[0]
        self.db.cur.execute("SELECT NoteName FROM Notes WHERE NoteID = %s", (noteID,))
        self.assertEqual(self.db.cur.fetchone()[0], "Note", "Note set.")

    def test_set_note_listNotExists(self):
        self.db.new_user(441220162, "Tai", 0)
        self.db.new_list(441220162, "List")
        self.db.new_note(441220162, "Note")
        self.db.set_note(441220162, 0)
        self.db.cur.execute("SELECT NoteID FROM Users WHERE userID=%s", (441220162,))
        self.assertIsNone(self.db.cur.fetchone()[0], "List set.")

    def test_set_note_noteNotExists(self):
        self.db.new_user(441220162, "Tai", 0)
        self.db.new_list(441220162, "List")
        self.db.set_note(441220162, 0)
        self.db.cur.execute("SELECT NoteID FROM Users WHERE userID=%s", (441220162,))
        self.assertIsNone(self.db.cur.fetchone()[0], "List set.")

    def test_delete_note_Exists(self):
        self.db.new_user(441220162, "Tai", 0)
        self.db.new_list(441220162, "List")
        self.db.set_list(441220162, 0)
        self.db.new_note(441220162, "Note")
        self.db.set_note(441220162, 0)
        self.db.delete_note(441220162)
        self.db.cur.execute("SELECT * FROM Notes WHERE userID = %s and NoteName = %s", (441220162, "Note"))
        self.assertIsNone(self.db.cur.fetchone(), "The note deleted")

    def test_delete_note_checkNumb(self):
        self.db.new_user(441220162, "Tai", 0)
        self.db.new_list(441220162, "List")
        self.db.set_list(441220162, 0)
        self.db.new_note(441220162, "Note0")
        self.db.new_note(441220162, "Note1")
        self.db.set_note(441220162, 0)
        self.db.delete_note(441220162)
        self.db.cur.execute("SELECT numb FROM Notes WHERE userID = %s", (441220162,))
        self.assertEqual(self.db.cur.fetchone()[0], 0, "The number changed")

    def test_delete_note_NotExists(self):
        self.db.new_user(441220162, "Tai", 0)
        self.db.new_list(441220162, "List")
        self.db.set_list(441220162, 0)
        self.db.new_note(441220162, "Note")
        self.db.delete_note(441220162)
        self.db.cur.execute("SELECT * FROM Notes WHERE userID = %s and NoteName = %s", (441220162, "Note"))
        self.assertIsNotNone(self.db.cur.fetchone(), "The note is not deleted if not exists")

    def test_edit_note_Exists(self):
        self.db.new_user(441220162, "Tai", 0)
        self.db.new_list(441220162, "List")
        self.db.set_list(441220162, 0)
        self.db.new_note(441220162, "Note")
        self.db.set_note(441220162, 0)
        self.db.edit_note(441220162, "New_note")
        self.db.cur.execute("SELECT * FROM Notes WHERE userID = %s and NoteName = %s", (441220162, "New_note"))
        new_name = self.db.cur.fetchone()
        self.db.cur.execute("SELECT * FROM Notes WHERE userID = %s and NoteName = %s", (441220162, "Note"))
        old_name = self.db.cur.fetchone()
        self.assertTrue((new_name is not None) and (old_name is None), "The note edited")

    def test_edit_note_NotExists(self):
        self.db.new_user(441220162, "Tai", 0)
        self.db.new_list(441220162, "List")
        self.db.set_list(441220162, 0)
        self.db.new_note(441220162, "Note")
        self.db.edit_note(441220162, "New_note")
        self.db.cur.execute("SELECT * FROM Notes WHERE userID = %s and NoteName = %s", (441220162, "New_note"))
        new_name = self.db.cur.fetchone()
        self.db.cur.execute("SELECT * FROM Notes WHERE userID = %s and NoteName = %s", (441220162, "Note"))
        old_name = self.db.cur.fetchone()
        self.assertTrue((new_name is None) and (old_name is not None), "The note is not edited if not exists")

    def test_get_lists_exists(self):
        self.db.new_user(441220162, "Tai", 0)
        self.db.new_list(441220162, "List0")
        self.db.new_list(441220162, "List1")
        data = self.db.get_lists(441220162)
        self.assertTrue((len(data) == 2) and (data[0][0] == "List0") and (data[1][0] == "List1"), "Lists exist.")

    def test_get_lists_notExists(self):
        self.db.new_user(441220162, "Tai", 0)
        data = self.db.get_lists(441220162)
        self.assertTrue(len(data) == 0, "Lists do not exist.")

    def test_get_notes_exists(self):
        self.db.new_user(441220162, "Tai", 0)
        self.db.new_list(441220162, "List")
        self.db.set_list(441220162, 0)
        self.db.new_note(441220162, "Note0")
        self.db.new_note(441220162, "Note1")
        data = self.db.get_notes(441220162, 0)
        self.assertTrue((len(data) == 2) and (data[0][0] == "Note0") and (data[1][0] == "Note1"), "Notes exist.")

    def test_get_notes_notExists(self):
        self.db.new_user(441220162, "Tai", 0)
        self.db.new_list(441220162, "List")
        self.db.set_list(441220162, 0)
        data = self.db.get_notes(441220162, 0)
        self.assertTrue(len(data) == 0, "Notes do not exist.")

    def test_get_notes_listNotExists(self):
        self.db.new_user(441220162, "Tai", 0)
        self.db.set_list(441220162, 0)
        self.assertIsNone(self.db.get_notes(441220162, 0), "Notes do not exist.")

    def test_new_image_Exists(self):
        self.db.new_user(441220162, "Tai", 0)
        self.db.new_list(441220162, "List")
        self.db.set_list(441220162, 0)
        self.db.new_note(441220162, "Note")
        self.db.set_note(441220162, 0)
        self.db.new_image(441220162, "123")
        self.db.cur.execute("SELECT NoteID FROM Users WHERE userID = %s", (441220162,))
        noteID = self.db.cur.fetchone()[0]
        self.db.cur.execute("SELECT NoteImage FROM Images WHERE NoteID = %s", (noteID,))
        data = self.db.cur.fetchone()[0]
        self.assertEqual(data, "123", "New image added.")

    def test_new_image_NotExists(self):
        self.db.new_user(441220162, "Tai", 0)
        self.db.new_image(441220162, "123")
        self.db.cur.execute("SELECT * FROM Images WHERE NoteImage = %s", ("123",))
        self.assertIsNone(self.db.cur.fetchone(), "New image is not added.")

    def test_new_file_Exists(self):
        self.db.new_user(441220162, "Tai", 0)
        self.db.new_list(441220162, "List")
        self.db.set_list(441220162, 0)
        self.db.new_note(441220162, "Note")
        self.db.set_note(441220162, 0)
        self.db.new_file(441220162, "123")
        self.db.cur.execute("SELECT NoteID FROM Users WHERE userID = %s", (441220162,))
        noteID = self.db.cur.fetchone()[0]
        self.db.cur.execute("SELECT NoteFile FROM Files WHERE NoteID = %s", (noteID,))
        data = self.db.cur.fetchone()[0]
        self.assertEqual(data, "123", "New file added.")

    def test_new_file_NotExists(self):
        self.db.new_user(441220162, "Tai", 0)
        self.db.new_file(441220162, "123")
        self.db.cur.execute("SELECT * FROM Files WHERE NoteFile = %s", ("123",))
        self.assertIsNone(self.db.cur.fetchone(), "New file is not added.")

    def test_new_voice_Exists(self):
        self.db.new_user(441220162, "Tai", 0)
        self.db.new_list(441220162, "List")
        self.db.set_list(441220162, 0)
        self.db.new_note(441220162, "Note")
        self.db.set_note(441220162, 0)
        self.db.new_voice(441220162, "123")
        self.db.cur.execute("SELECT NoteID FROM Users WHERE userID = %s", (441220162,))
        noteID = self.db.cur.fetchone()[0]
        self.db.cur.execute("SELECT NoteVoice FROM Voices WHERE NoteID = %s", (noteID,))
        data = self.db.cur.fetchone()[0]
        self.assertEqual(data, "123", "New voice added.")

    def test_new_voice_NotExists(self):
        self.db.new_user(441220162, "Tai", 0)
        self.db.new_voice(441220162, "123")
        self.db.cur.execute("SELECT * FROM Voices WHERE NoteVoice = %s", ("123",))
        self.assertIsNone(self.db.cur.fetchone(), "New voice is not added.")

    def test_new_audio_Exists(self):
        self.db.new_user(441220162, "Tai", 0)
        self.db.new_list(441220162, "List")
        self.db.set_list(441220162, 0)
        self.db.new_note(441220162, "Note")
        self.db.set_note(441220162, 0)
        self.db.new_audio(441220162, "123")
        self.db.cur.execute("SELECT NoteID FROM Users WHERE userID = %s", (441220162,))
        noteID = self.db.cur.fetchone()[0]
        self.db.cur.execute("SELECT NoteAudio FROM Audio WHERE NoteID = %s", (noteID,))
        data = self.db.cur.fetchone()[0]
        self.assertEqual(data, "123", "New audio added.")

    def test_new_audio_NotExists(self):
        self.db.new_user(441220162, "Tai", 0)
        self.db.new_audio(441220162, "123")
        self.db.cur.execute("SELECT * FROM Audio WHERE NoteAudio = %s", ("123",))
        self.assertIsNone(self.db.cur.fetchone(), "New audio is not added.")

    def test_get_images_Exists(self):
        self.db.new_user(441220162, "Tai", 0)
        self.db.new_list(441220162, "List")
        self.db.set_list(441220162, 0)
        self.db.new_note(441220162, "Note")
        self.db.set_note(441220162, 0)
        self.db.new_image(441220162, "123")
        self.db.new_image(441220162, "abc")
        data = self.db.get_images(441220162)
        self.assertTrue((data[0][0] == "123") and (data[1][0] == "abc") and (len(data) == 2), "Got images.")

    def test_get_images_NotExists(self):
        self.db.new_user(441220162, "Tai", 0)
        self.assertIsNone(self.db.get_images(441220162), "No images.")

    def test_get_files_Exists(self):
        self.db.new_user(441220162, "Tai", 0)
        self.db.new_list(441220162, "List")
        self.db.set_list(441220162, 0)
        self.db.new_note(441220162, "Note")
        self.db.set_note(441220162, 0)
        self.db.new_file(441220162, "123")
        self.db.new_file(441220162, "abc")
        data = self.db.get_files(441220162)
        self.assertTrue((data[0][0] == "123") and (data[1][0] == "abc") and (len(data) == 2), "Got files.")

    def test_get_files_NotExists(self):
        self.db.new_user(441220162, "Tai", 0)
        self.assertIsNone(self.db.get_files(441220162), "No files.")

    def test_get_voices_Exists(self):
        self.db.new_user(441220162, "Tai", 0)
        self.db.new_list(441220162, "List")
        self.db.set_list(441220162, 0)
        self.db.new_note(441220162, "Note")
        self.db.set_note(441220162, 0)
        self.db.new_voice(441220162, "123")
        self.db.new_voice(441220162, "abc")
        data = self.db.get_voices(441220162)
        self.assertTrue((data[0][0] == "123") and (data[1][0] == "abc") and (len(data) == 2), "Got voices.")

    def test_get_voices_NotExists(self):
        self.db.new_user(441220162, "Tai", 0)
        self.assertIsNone(self.db.get_voices(441220162), "No voices.")

    def test_get_audio_Exists(self):
        self.db.new_user(441220162, "Tai", 0)
        self.db.new_list(441220162, "List")
        self.db.set_list(441220162, 0)
        self.db.new_note(441220162, "Note")
        self.db.set_note(441220162, 0)
        self.db.new_audio(441220162, "123")
        self.db.new_audio(441220162, "abc")
        data = self.db.get_audio(441220162)
        self.assertTrue((data[0][0] == "123") and (data[1][0] == "abc") and (len(data) == 2), "Got audio.")

    def test_get_audio_NotExists(self):
        self.db.new_user(441220162, "Tai", 0)
        self.assertIsNone(self.db.get_audio(441220162), "No audio.")


if __name__ == '__main__':
    unittest.main()
