import unittest
from unittest import TestCase

from db import Database


class TestDatabase(unittest.TestCase):
    def setUp(self):
        self.db = Database()
        self.db.init_tables()

    def tearDown(self):
        if self.db.conn.closed == 0:
            self.db.clear()
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
        id = 441220162
        name = "Tai"
        state = 0
        self.db.new_user(id, name, state)
        self.db.cur.execute("SELECT first_name, State FROM Users WHERE userID=%s", (441220162,))
        data = self.db.cur.fetchone()
        self.assertTrue((data[0] == 'Tai' and data[1] == 0), "New user created.")

    def test_new_user_invalid_name(self):
        id = 441220162
        name = "a" * 51
        state = 0
        self.db.new_user(id, name, state)
        self.db.cur.execute("SELECT first_name, State FROM Users WHERE userID=%s", (id,))
        data = self.db.cur.fetchone()
        self.assertIsNone(data, "Invalid username.")

    def test_user_exists_false(self):
        id = 441220162
        self.assertFalse(self.db.user_exists(id), "Not created user does not exist.")

    def test_user_exists_true(self):
        id = 441220162
        name = "Tai"
        state = 0
        self.db.new_user(id, name, state)
        self.assertTrue(self.db.user_exists(id), "Created user exists.")

    def test_set_state(self):
        id = 441220162
        name = "Tai"
        state = 0
        self.db.new_user(id, name, state)
        self.db.set_state(id, 3)
        self.db.cur.execute("SELECT State FROM Users WHERE userID=%s", (441220162,))
        self.assertEqual(self.db.cur.fetchone()[0], 3, "State set.")

    def test_init_state(self):
        id = 441220162
        name = "Tai"
        state = 3
        self.db.new_user(id, name, state)
        self.db.init_state(id)
        self.db.cur.execute("SELECT State FROM Users WHERE userID=%s", (441220162,))
        self.assertEqual(self.db.cur.fetchone()[0], 0, "Init state set.")

    def test_get_state(self):
        id = 441220162
        name = "Tai"
        state = 0
        self.db.new_user(id, name, state)
        self.db.set_state(id, 3)
        self.db.cur.execute("SELECT State FROM Users WHERE userID = %s", (441220162,))
        self.assertEqual(self.db.cur.fetchone()[0], self.db.get_state(441220162)[0], "Get state.")

    def test_new_list(self):
        id = 441220162
        name = "Tai"
        state = 0
        self.db.new_user(id, name, state)
        self.db.new_list(id, "List")
        self.db.cur.execute("SELECT ListName FROM Lists WHERE userID = %s", (441220162,))
        self.assertEqual(self.db.cur.fetchone()[0], "List", "New list added.")

    def test_new_list_invalid_name(self):
        id = 441220162
        name = "Tai"
        state = 0
        self.db.new_user(id, name, state)
        list_name = "a"*51
        self.db.new_list(id, list_name)
        self.db.cur.execute("SELECT ListName FROM Lists WHERE userID = %s", (441220162,))
        self.assertIsNone(self.db.cur.fetchone(), "Invalid list name.")

    def test_set_list(self):
        id = 441220162
        name = "Tai"
        state = 0
        self.db.new_user(id, name, state)
        self.db.new_list(id, "List")
        self.db.set_list(id, 0)
        self.db.cur.execute("SELECT ListID FROM Users WHERE userID=%s", (441220162,))
        listID = self.db.cur.fetchone()[0]
        self.db.cur.execute("SELECT ListName FROM Lists WHERE ListID = %s", (listID,))
        self.assertEqual(self.db.cur.fetchone()[0], "List", "List set.")

    def test_set_list_notExists(self):
        id = 441220162
        name = "Tai"
        state = 0
        self.db.new_user(id, name, state)
        self.db.set_list(id, 0)
        self.db.cur.execute("SELECT ListID FROM Users WHERE userID=%s", (id,))
        self.assertIsNone(self.db.cur.fetchone()[0], "List is not set if does not exist.")

    def test_get_cur_list_numbNotExists(self):
        id = 441220162
        name = "Tai"
        state = 0
        self.db.new_user(id, name, state)
        self.assertIsNone(self.db.get_cur_list_numb(id), "Got current list number if does not exist.")

    def test_get_cur_list_numbExists(self):
        id = 441220162
        name = "Tai"
        state = 0
        self.db.new_user(id, name, state)
        self.db.new_list(id, "List")
        self.db.set_list(id, 0)
        self.assertEqual(self.db.get_cur_list_numb(id)[0], 0, "Got current list number.")

    def test_new_note_listExists(self):
        id = 441220162
        name = "Tai"
        state = 0
        self.db.new_user(id, name, state)
        self.db.new_list(id, "List")
        self.db.set_list(id, 0)
        self.db.new_note(id, "Note")
        self.db.cur.execute("SELECT NoteName FROM Notes WHERE userID = %s", (id,))
        self.assertEqual(self.db.cur.fetchone()[0], "Note", "New note added.")

    def test_new_note_invalid_name(self):
        id = 441220162
        name = "Tai"
        state = 0
        self.db.new_user(id, name, state)
        self.db.new_list(id, "List")
        self.db.set_list(id, 0)
        note_name = "a" * 51
        self.db.new_note(id, note_name)
        self.db.cur.execute("SELECT NoteName FROM Notes WHERE userID = %s", (id,))
        self.assertIsNone(self.db.cur.fetchone(),  "Invalid note name.")

    def test_new_note_listNotExists(self):
        id = 441220162
        name = "Tai"
        state = 0
        self.db.new_user(id, name, state)
        self.db.new_note(id, "Note1")
        self.db.cur.execute("SELECT NoteName FROM Notes WHERE userID = %s", (id,))
        self.assertIsNone(self.db.cur.fetchone(), "New note added.")

    def test_delete_list_Exists(self):
        id = 441220162
        name = "Tai"
        state = 0
        self.db.new_user(id, name, state)
        self.db.new_list(id, "List")
        self.db.set_list(id, 0)
        self.db.delete_list(id)
        self.db.cur.execute("SELECT * FROM Lists WHERE userID = %s and ListName = %s", (id, "List"))
        self.assertIsNone(self.db.cur.fetchone(), "List deleted")

    def test_delete_list_checkNumb(self):
        id = 441220162
        name = "Tai"
        state = 0
        self.db.new_user(id, name, state)
        self.db.new_list(id, "List0")
        self.db.new_list(id, "List1")
        self.db.set_list(id, 0)
        self.db.delete_list(id)
        self.db.cur.execute("SELECT numb FROM Lists WHERE userID = %s and ListName = %s", (id, "List1"))
        self.assertEqual(self.db.cur.fetchone()[0], 0, "Number changed")

    def test_delete_list_NotExists(self):
        id = 441220162
        name = "Tai"
        state = 0
        self.db.new_user(id, name, state)
        self.db.new_list(id, "List")
        self.db.delete_list(id)
        self.db.cur.execute("SELECT * FROM Lists WHERE userID = %s and ListName = %s", (id, "List"))
        self.assertIsNotNone(self.db.cur.fetchone(), "List is not deleted")

    def test_edit_list_Exists(self):
        id = 441220162
        name = "Tai"
        state = 0
        self.db.new_user(id, name, state)
        self.db.new_list(id, "List")
        self.db.set_list(id, 0)
        self.db.edit_list(id, "New_list")
        self.db.cur.execute("SELECT * FROM Lists WHERE userID = %s and ListName = %s", (id, "New_list"))
        new_name = self.db.cur.fetchone()
        self.db.cur.execute("SELECT * FROM Lists WHERE userID = %s and ListName = %s", (id, "List"))
        old_name = self.db.cur.fetchone()
        self.assertTrue((new_name is not None) and (old_name is None), "List edited")

    def test_edit_list_NotExists(self):
        id = 441220162
        name = "Tai"
        state = 0
        self.db.new_user(id, name, state)
        self.db.new_list(id, "List")
        self.db.edit_list(id, "New_list")
        self.db.cur.execute("SELECT * FROM Lists WHERE userID = %s and ListName = %s", (id, "New_list"))
        new_name = self.db.cur.fetchone()
        self.db.cur.execute("SELECT * FROM Lists WHERE userID = %s and ListName = %s", (id, "List"))
        old_name = self.db.cur.fetchone()
        self.assertTrue((new_name is None) and (old_name is not None), "List is not edited if does not exist")

    def test_set_note_listExists(self):
        id = 441220162
        name = "Tai"
        state = 0
        self.db.new_user(id, name, state)
        self.db.new_list(id, "List")
        self.db.set_list(id, 0)
        self.db.new_note(id, "Note")
        self.db.set_note(id, 0)
        self.db.cur.execute("SELECT NoteID FROM Users WHERE userID=%s", (id,))
        noteID = self.db.cur.fetchone()[0]
        self.db.cur.execute("SELECT NoteName FROM Notes WHERE NoteID = %s", (noteID,))
        self.assertEqual(self.db.cur.fetchone()[0], "Note", "Note set.")

    def test_set_note_listNotExists(self):
        id = 441220162
        name = "Tai"
        state = 0
        self.db.new_user(id, name, state)
        self.db.new_list(id, "List")
        self.db.new_note(id, "Note")
        self.db.set_note(id, 0)
        self.db.cur.execute("SELECT NoteID FROM Users WHERE userID=%s", (id,))
        self.assertIsNone(self.db.cur.fetchone()[0], "List set.")

    def test_set_note_noteNotExists(self):
        id = 441220162
        name = "Tai"
        state = 0
        self.db.new_user(id, name, state)
        self.db.new_list(id, "List")
        self.db.set_note(id, 0)
        self.db.cur.execute("SELECT NoteID FROM Users WHERE userID=%s", (id,))
        self.assertIsNone(self.db.cur.fetchone()[0], "List set.")

    def test_delete_note_Exists(self):
        id = 441220162
        name = "Tai"
        state = 0
        self.db.new_user(id, name, state)
        self.db.new_list(id, "List")
        self.db.set_list(id, 0)
        self.db.new_note(id, "Note")
        self.db.set_note(id, 0)
        self.db.delete_note(id)
        self.db.cur.execute("SELECT * FROM Notes WHERE userID = %s and NoteName = %s", (id, "Note"))
        self.assertIsNone(self.db.cur.fetchone(), "Note deleted")

    def test_delete_note_checkNumb(self):
        id = 441220162
        name = "Tai"
        state = 0
        self.db.new_user(id, name, state)
        self.db.new_list(id, "List")
        self.db.set_list(id, 0)
        self.db.new_note(id, "Note0")
        self.db.new_note(id, "Note1")
        self.db.set_note(id, 0)
        self.db.delete_note(id)
        self.db.cur.execute("SELECT numb FROM Notes WHERE userID = %s", (id,))
        self.assertEqual(self.db.cur.fetchone()[0], 0, "Number changed")

    def test_delete_note_NotExists(self):
        id = 441220162
        name = "Tai"
        state = 0
        self.db.new_user(id, name, state)
        self.db.new_list(id, "List")
        self.db.set_list(id, 0)
        self.db.new_note(id, "Note")
        self.db.delete_note(id)
        self.db.cur.execute("SELECT * FROM Notes WHERE userID = %s and NoteName = %s", (id, "Note"))
        self.assertIsNotNone(self.db.cur.fetchone(), "Note is not deleted if does not exist")

    def test_edit_note_Exists(self):
        id = 441220162
        name = "Tai"
        state = 0
        self.db.new_user(id, name, state)
        self.db.new_list(id, "List")
        self.db.set_list(id, 0)
        self.db.new_note(id, "Note")
        self.db.set_note(id, 0)
        self.db.edit_note(id, "New_note")
        self.db.cur.execute("SELECT * FROM Notes WHERE userID = %s and NoteName = %s", (id, "New_note"))
        new_name = self.db.cur.fetchone()
        self.db.cur.execute("SELECT * FROM Notes WHERE userID = %s and NoteName = %s", (id, "Note"))
        old_name = self.db.cur.fetchone()
        self.assertTrue((new_name is not None) and (old_name is None), "Note edited")

    def test_edit_note_NotExists(self):
        id = 441220162
        name = "Tai"
        state = 0
        self.db.new_user(id, name, state)
        self.db.new_list(id, "List")
        self.db.set_list(id, 0)
        self.db.new_note(id, "Note")
        self.db.edit_note(id, "New_note")
        self.db.cur.execute("SELECT * FROM Notes WHERE userID = %s and NoteName = %s", (id, "New_note"))
        new_name = self.db.cur.fetchone()
        self.db.cur.execute("SELECT * FROM Notes WHERE userID = %s and NoteName = %s", (id, "Note"))
        old_name = self.db.cur.fetchone()
        self.assertTrue((new_name is None) and (old_name is not None), "Note is not edited if does not exist")

    def test_get_lists_exists(self):
        id = 441220162
        name = "Tai"
        state = 0
        self.db.new_user(id, name, state)
        self.db.new_list(id, "List0")
        self.db.new_list(id, "List1")
        data = self.db.get_lists(id)
        self.assertTrue((len(data) == 2) and (data[0][0] == "List0") and (data[1][0] == "List1"), "Lists exist.")

    def test_get_lists_notExists(self):
        id = 441220162
        name = "Tai"
        state = 0
        self.db.new_user(id, name, state)
        data = self.db.get_lists(id)
        self.assertTrue(len(data) == 0, "Lists do not exist.")

    def test_get_notes_exists(self):
        id = 441220162
        name = "Tai"
        state = 0
        self.db.new_user(id, name, state)
        self.db.new_list(id, "List")
        self.db.set_list(id, 0)
        self.db.new_note(id, "Note0")
        self.db.new_note(id, "Note1")
        data = self.db.get_notes(id, 0)
        self.assertTrue((len(data) == 2) and (data[0][0] == "Note0") and (data[1][0] == "Note1"), "Notes exist.")

    def test_get_notes_notExists(self):
        id = 441220162
        name = "Tai"
        state = 0
        self.db.new_user(id, name, state)
        self.db.new_list(id, "List")
        self.db.set_list(id, 0)
        data = self.db.get_notes(id, 0)
        self.assertTrue(len(data) == 0, "Notes do not exist.")

    def test_get_notes_listNotExists(self):
        id = 441220162
        name = "Tai"
        state = 0
        self.db.new_user(id, name, state)
        self.db.set_list(id, 0)
        self.assertIsNone(self.db.get_notes(id, 0), "Notes do not exist.")

    def test_new_image_Exists(self):
        id = 441220162
        name = "Tai"
        state = 0
        self.db.new_user(id, name, state)
        self.db.new_list(id, "List")
        self.db.set_list(id, 0)
        self.db.new_note(id, "Note")
        self.db.set_note(id, 0)
        self.db.new_image(id, "123")
        self.db.cur.execute("SELECT NoteID FROM Users WHERE userID = %s", (id,))
        noteID = self.db.cur.fetchone()[0]
        self.db.cur.execute("SELECT NoteImage FROM Images WHERE NoteID = %s", (noteID,))
        data = self.db.cur.fetchone()[0]
        self.assertEqual(data, "123", "New image added.")

    def test_new_image_NotExists(self):
        id = 441220162
        name = "Tai"
        state = 0
        self.db.new_user(id, name, state)
        self.db.new_image(id, "123")
        self.db.cur.execute("SELECT * FROM Images WHERE NoteImage = %s", ("123",))
        self.assertIsNone(self.db.cur.fetchone(), "New image is not added.")

    def test_new_file_Exists(self):
        id = 441220162
        name = "Tai"
        state = 0
        self.db.new_user(id, name, state)
        self.db.new_list(id, "List")
        self.db.set_list(id, 0)
        self.db.new_note(id, "Note")
        self.db.set_note(id, 0)
        self.db.new_file(id, "123")
        self.db.cur.execute("SELECT NoteID FROM Users WHERE userID = %s", (id,))
        noteID = self.db.cur.fetchone()[0]
        self.db.cur.execute("SELECT NoteFile FROM Files WHERE NoteID = %s", (noteID,))
        data = self.db.cur.fetchone()[0]
        self.assertEqual(data, "123", "New file added.")

    def test_new_file_NotExists(self):
        id = 441220162
        name = "Tai"
        state = 0
        self.db.new_user(id, name, state)
        self.db.new_file(id, "123")
        self.db.cur.execute("SELECT * FROM Files WHERE NoteFile = %s", ("123",))
        self.assertIsNone(self.db.cur.fetchone(), "New file is not added.")

    def test_new_voice_Exists(self):
        id = 441220162
        name = "Tai"
        state = 0
        self.db.new_user(id, name, state)
        self.db.new_list(id, "List")
        self.db.set_list(id, 0)
        self.db.new_note(id, "Note")
        self.db.set_note(id, 0)
        self.db.new_voice(id, "123")
        self.db.cur.execute("SELECT NoteID FROM Users WHERE userID = %s", (id,))
        noteID = self.db.cur.fetchone()[0]
        self.db.cur.execute("SELECT NoteVoice FROM Voices WHERE NoteID = %s", (noteID,))
        data = self.db.cur.fetchone()[0]
        self.assertEqual(data, "123", "New voice added.")

    def test_new_voice_NotExists(self):
        id = 441220162
        name = "Tai"
        state = 0
        self.db.new_user(id, name, state)
        self.db.new_voice(id, "123")
        self.db.cur.execute("SELECT * FROM Voices WHERE NoteVoice = %s", ("123",))
        self.assertIsNone(self.db.cur.fetchone(), "New voice is not added.")

    def test_new_audio_Exists(self):
        id = 441220162
        name = "Tai"
        state = 0
        self.db.new_user(id, name, state)
        self.db.new_list(id, "List")
        self.db.set_list(id, 0)
        self.db.new_note(id, "Note")
        self.db.set_note(id, 0)
        self.db.new_audio(id, "123")
        self.db.cur.execute("SELECT NoteID FROM Users WHERE userID = %s", (id,))
        noteID = self.db.cur.fetchone()[0]
        self.db.cur.execute("SELECT NoteAudio FROM Audio WHERE NoteID = %s", (noteID,))
        data = self.db.cur.fetchone()[0]
        self.assertEqual(data, "123", "New audio added.")

    def test_new_audio_NotExists(self):
        id = 441220162
        name = "Tai"
        state = 0
        self.db.new_user(id, name, state)
        self.db.new_audio(id, "123")
        self.db.cur.execute("SELECT * FROM Audio WHERE NoteAudio = %s", ("123",))
        self.assertIsNone(self.db.cur.fetchone(), "New audio is not added.")

    def test_get_images_Exists(self):
        id = 441220162
        name = "Tai"
        state = 0
        self.db.new_user(id, name, state)
        self.db.new_list(id, "List")
        self.db.set_list(id, 0)
        self.db.new_note(id, "Note")
        self.db.set_note(id, 0)
        self.db.new_image(id, "123")
        self.db.new_image(id, "abc")
        data = self.db.get_images(id)
        self.assertTrue((data[0][0] == "123") and (data[1][0] == "abc") and (len(data) == 2), "Got images.")

    def test_get_images_NotExists(self):
        id = 441220162
        name = "Tai"
        state = 0
        self.db.new_user(id, name, state)
        self.assertIsNone(self.db.get_images(id), "No images.")

    def test_get_files_Exists(self):
        id = 441220162
        name = "Tai"
        state = 0
        self.db.new_user(id, name, state)
        self.db.new_list(id, "List")
        self.db.set_list(id, 0)
        self.db.new_note(id, "Note")
        self.db.set_note(id, 0)
        self.db.new_file(id, "123")
        self.db.new_file(id, "abc")
        data = self.db.get_files(id)
        self.assertTrue((data[0][0] == "123") and (data[1][0] == "abc") and (len(data) == 2), "Got files.")

    def test_get_files_NotExists(self):
        id = 441220162
        name = "Tai"
        state = 0
        self.db.new_user(id, name, state)
        self.assertIsNone(self.db.get_files(id), "No files.")

    def test_get_voices_Exists(self):
        id = 441220162
        name = "Tai"
        state = 0
        self.db.new_user(id, name, state)
        self.db.new_list(id, "List")
        self.db.set_list(id, 0)
        self.db.new_note(id, "Note")
        self.db.set_note(id, 0)
        self.db.new_voice(id, "123")
        self.db.new_voice(id, "abc")
        data = self.db.get_voices(id)
        self.assertTrue((data[0][0] == "123") and (data[1][0] == "abc") and (len(data) == 2), "Got voices.")

    def test_get_voices_NotExists(self):
        id = 441220162
        name = "Tai"
        state = 0
        self.db.new_user(id, name, state)
        self.assertIsNone(self.db.get_voices(id), "No voices.")

    def test_get_audio_Exists(self):
        id = 441220162
        name = "Tai"
        state = 0
        self.db.new_user(id, name, state)
        self.db.new_list(id, "List")
        self.db.set_list(id, 0)
        self.db.new_note(id, "Note")
        self.db.set_note(id, 0)
        self.db.new_audio(id, "123")
        self.db.new_audio(id, "abc")
        data = self.db.get_audio(id)
        self.assertTrue((data[0][0] == "123") and (data[1][0] == "abc") and (len(data) == 2), "Got audio.")

    def test_get_audio_NotExists(self):
        id = 441220162
        name = "Tai"
        state = 0
        self.db.new_user(id, name, state)
        self.assertIsNone(self.db.get_audio(id), "No audio.")

    def test_close(self):
        self.db.close()
        self.assertTrue(self.db.conn != 0, "Closed")


if __name__ == '__main__':
    unittest.main()
