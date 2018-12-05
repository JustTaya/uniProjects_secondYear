from unittest import TestCase
from db import Database


class TestDatabase(TestCase):
    def test_init_tables(self):
        d = Database()
        d.init_tables()
        tmp = 0
        d.cur.execute("IF OBJECT_ID('Users', 'U') IS NOT NULL %s=1", (tmp,))
        self.assertTrue(tmp == 1, "Users")

    def test_user_exists(self):
        self.fail()

    def test_new_user(self):
        self.fail()

    def test_new_list(self):
        self.fail()

    def test_new_note(self):
        self.fail()

    def test_delete_list(self):
        self.fail()

    def test_edit_list(self):
        self.fail()

    def test_delete_note(self):
        self.fail()

    def test_get_lists(self):
        self.fail()

    def test_get_list(self):
        self.fail()

    def test_get_notes(self):
        self.fail()

    def test_get_note(self):
        self.fail()

    def test_set_state(self):
        self.fail()

    def test_init_state(self):
        self.fail()

    def test_set_list(self):
        self.fail()

    def test_set_note(self):
        self.fail()

    def test_get_state(self):
        self.fail()

    def test_get_cur_list_numb(self):
        self.fail()

    def test_edit_note(self):
        self.fail()

    def test_new_image(self):
        self.fail()

    def test_new_file(self):
        self.fail()

    def test_new_voice(self):
        self.fail()

    def test_new_audio(self):
        self.fail()

    def test_get_images(self):
        self.fail()

    def test_get_files(self):
        self.fail()

    def test_get_voices(self):
        self.fail()

    def test_get_audio(self):
        self.fail()

    def test_close(self):
        self.fail()
