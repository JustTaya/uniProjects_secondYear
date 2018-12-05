import os
from flask import Flask, request
import telebot
from telebot import util
import markups
import db

# init bot
token = os.environ.get('TOKEN')
bot = telebot.TeleBot(token)

# init db
database = db.Database()
database.init_tables()

# dictionary for bot states
states = {
    'list_menu': 0,
    'wait_list_name': 1,
    'list_chosen': 2,
    'wait_note_name': 3,
    'note_chosen': 4,
    'wait_text': 5,
    'wait_image': 6,
    'wait_file': 7,
    'wait_voice': 8,
    'wait_audio': 9,
    'edit_list': 10,
    'edit_note': 11,
    'attach_menu': 12
}

server = Flask(__name__)


def add_list(id, name):
    if '/' in name:
        bot.send_message(id, 'Invalid list name. Print another name of the list.',
                         reply_markup=markups.none_markup)
    else:
        database.new_list(id, name)
        database.set_state(id, states['list_menu'])
        bot.send_message(id, 'List added', reply_markup=markups.init_markup)
        show_l(id)


def add_note(message):
    if '/' in message.text or len(message.text) > 50:
        bot.send_message(message.chat.id, 'Invalid note name. Print another name of the list.',
                         reply_markup=markups.none_markup)
    else:
        database.new_note(message.chat.id, message.text)
        bot.send_message(message.chat.id, 'Note added', reply_markup=markups.list_chosen_markup)
        bot.send_message(message.chat.id, database.get_cur_list_numb(message.chat.id)[0])
        show_cur_n(message.chat.id, int(database.get_cur_list_numb(message.chat.id)[0]))


def show_items(id):
    bot.send_message(id, 'Images: ')
    images = database.get_images(id)
    for i in images:
        bot.send_photo(id, images[0][0])
    bot.send_message(id, 'Files: ')
    files = database.get_files(id)
    for i in files:
        bot.send_document(id, files[0][0])
    bot.send_message(id, 'Voices: ')
    voices = database.get_voices(id)
    for i in voices:
        bot.send_voice(id, voices[0][0])
    bot.send_message(id, 'Audio: ')
    audio = database.get_audio(id)
    for i in audio:
        bot.send_audio(id, audio[0][0])


def show_l(id):
    database.set_state(id, states['list_menu'])
    lists = database.get_lists(id)
    res = ''
    numb = 0
    for i in lists:
        res += '/' + str(numb) + ' ' + str(i[0]) + '\n'
        numb += 1
    bot.send_message(id, 'Your lists: ')
    bot.send_message(id, res, reply_markup=markups.init_markup)


def show_n(message):
    tmp = message.text[1:]
    if not tmp.isdigit():
        bot.send_message(message.chat.id, "Invalid command", reply_markup=markups.none_markup)
    else:
        show_cur_n(message.chat.id, int(tmp))


def show_cur_n(id, tmp):
    list = database.get_list(id, tmp)[0]
    if list != None:
        database.set_state(id, states['list_chosen'])
        bot.send_message(id, "Notes in list " + list + "")
        notes = database.get_notes(id, tmp)
        res = ''
        numb = 0
        for i in notes:
            res += '/' + str(numb) + ' ' + str(i[0]) + '\n'
            numb += 1
        if res == "":
            bot.send_message(id, "No notes yet.", reply_markup=markups.list_chosen_markup)
        else:
            bot.send_message(id, res, reply_markup=markups.list_chosen_markup)
    else:
        bot.send_message(id, tmp, reply_markup=markups.none_markup)


def show_n_inside(message):
    tmp = message.text[1:]
    if not tmp.isdigit():
        bot.send_message(message.chat.id, "Invalid command", reply_markup=markups.none_markup)
    else:
        database.set_note(message.chat.id, int(tmp))
        note = database.get_note(message.chat.id)[0]
        if note:
            database.set_state(message.chat.id, states['note_chosen'])
            bot.send_message(message.chat.id, "Note:" + note, reply_markup=markups.note_chosen_markup)


def new_list_name(id, name):
    if '/' in name:
        bot.send_message(id, 'Invalid list name. Print another name of the list.',
                         reply_markup=markups.none_markup)
    else:
        database.edit_list(id, name)
        database.set_state(id, states['list_menu'])
        bot.send_message(id, 'List name edited', reply_markup=markups.init_markup)
        show_l(id)


def new_note_name(id, name):
    if '/' in name:
        bot.send_message(id, 'Invalid note name. Print another name of the note.',
                         reply_markup=markups.none_markup)
    else:
        database.edit_note(id, name)
        bot.send_message(id, 'Note name edited', reply_markup=markups.list_chosen_markup)
        show_cur_n(id, int(database.get_cur_list_numb(id)[0]))


# message handlers
@bot.message_handler(commands=['start'])
def start(message):
    database.new_user(message.chat.id, message.from_user.first_name, states['list_menu'])
    bot.send_message(message.chat.id, 'Hello, ' + message.from_user.first_name,
                     reply_markup=markups.init_markup)


@bot.message_handler(content_types=["photo"])
def add_image(message):
    bot.send_message(message.chat.id, "Image", reply_markup=markups.list_chosen_markup)
    # state = database.get_state(message.chat.id)
    # if state == states['wait_image']:
    bot.send_message(message.chat.id, "Image1", reply_markup=markups.list_chosen_markup)
    database.new_image(message.chat.id, message.photo[0].file_id)
    bot.send_message(message.chat.id, "Image2", reply_markup=markups.list_chosen_markup)
    database.set_state(message.chat.id, states['note_chosen'])
    bot.send_message(message.chat.id, "Image added", reply_markup=markups.list_chosen_markup)
    show_cur_n(message.chat.id, int(database.get_cur_list_numb(message.chat.id)[0]))


@bot.message_handler(content_types=["document"])
def add_file(message):
    state = database.get_state(message.chat.id)
    if state == states['wait_file']:
        database.set_state(message.chat.id, states['note_chosen'])
        database.new_file(message.chat.id, message.document.file_id)
        bot.send_message(message.chat.id, "File added", reply_markup=markups.list_chosen_markup)
        show_cur_n(message.chat.id, int(database.get_cur_list_numb(message.chat.id)[0]))


@bot.message_handler(content_types=["voice"])
def add_voice(message):
    state = database.get_state(message.chat.id)
    if state == states['wait_voice']:
        database.new_image(message.chat.id, message.voice.file_id)
        database.set_state(message.chat.id, states['note_chosen'])

        bot.send_message(message.chat.id, "Voice added", reply_markup=markups.list_chosen_markup)
        show_cur_n(message.chat.id, int(database.get_cur_list_numb(message.chat.id)[0]))


@bot.message_handler(content_types=["audio"])
def add_audio(message):
    state = database.get_state(message.chat.id)
    if state == states['wait_audio']:
        database.new_image(message.chat.id, message.audio.file_id)
        database.set_state(message.chat.id, states['note_chosen'])
        bot.send_message(message.chat.id, "Audio added", reply_markup=markups.list_chosen_markup)
        show_cur_n(message.chat.id, int(database.get_cur_list_numb(message.chat.id)[0]))


@bot.message_handler(func=lambda message: message.content_type == 'text' and message.text == '➕ New list')
def new_list(message):
    state = database.get_state(message.chat.id)
    if state[0] == states['wait_list_name']:
        add_list(message.chat.id, message.text)
    elif state[0] == states['wait_note_name']:
        add_note(message.chat.id, message.text)
    else:
        database.set_state(message.chat.id, states['wait_list_name'])
        bot.send_message(message.chat.id, 'Enter the name of new list',
                         reply_markup=markups.none_markup)


@bot.message_handler(func=lambda message: message.content_type == 'text' and message.text == '◾️ Show lists')
def show_lists(message):
    show_l(message.chat.id)


@bot.message_handler(func=lambda message: message.content_type == 'text' and message.text == '⬅️ Go back')
def go_back(message):
    state = database.get_state(message.chat.id)
    if state[0] == states['wait_list_name']:
        add_list(message.chat.id, message.text)
    elif state[0] == states['wait_note_name']:
        add_note(message.chat.id, message.text)
    elif state[0] == states['edit_list']:
        new_list_name(message.chat.id, message.text)
    elif state[0] == states['edit_note']:
        new_note_name(message.chat.id, message.text)
    elif state[0] == states['list_chosen']:
        database.set_state(message.chat.id, states['list_menu'])
        show_l(message.chat.id)
    elif state[0] == states['note_chosen']:
        database.set_state(message.chat.id, states['list_chosen'])
        show_n(message)


@bot.message_handler(func=lambda message: message.content_type == 'text' and message.text == '✖️ Cancel')
def cancel(message):
    state = database.get_state(message.chat.id)
    if state[0] == states['wait_list_name']:
        database.set_state(message.chat.id, states['list_menu'])
        show_l(message.chat.id)
    elif state[0] == states['wait_note_name']:
        database.set_state(message.chat.id, states['list_chosen'])
        show_cur_n(message.chat.id, int(database.get_cur_list_numb(message.chat.id)[0]))
    elif state[0] == states['edit_list']:
        database.set_state(message.chat.id, states['list_chosen'])
        show_n(message)
    elif state[0] == states['edit_note']:
        database.set_state(message.chat.id, states['note_chosen'])
        show_cur_n(message.chat.id, int(database.get_cur_list_numb(message.chat.id)[0]))
    elif state[0] == states['list_chosen']:
        database.set_state(message.chat.id, states['list_menu'])
        show_l(message.chat.id)
    elif state[0] == states['note_chosen']:
        database.set_state(message.chat.id, states['list_chosen'])
        show_n(message)
    elif state == states['wait_image'] or state == states['wait_file'] or state == states['wait_voice'] or state == \
            states['wait_audio']:
        database.set_state(message.chat.id, states['note_chosen'])
        show_cur_n(message.chat.id, int(database.get_cur_list_numb(message.chat.id)[0]))


@bot.message_handler(func=lambda message: message.content_type == 'text' and message.text == '✖️ Delete list')
def delete_list(message):
    state = database.get_state(message.chat.id)
    if state[0] == states['wait_list_name']:
        add_list(message.chat.id, message.text)
    elif state[0] == states['wait_note_name']:
        add_note(message.chat.id, message.text)
    elif state[0] == states['edit_list']:
        new_list_name(message.chat.id, message.text)
    elif state[0] == states['edit_note']:
        new_note(message.chat.id, message.text)
    elif state[0] == states['list_chosen']:
        database.delete_list(message.chat.id)
        database.set_state(message.chat.id, states['list_menu'])
        show_l(message.chat.id)


@bot.message_handler(func=lambda message: message.content_type == 'text' and message.text == '✖️ Delete note')
def delete_note(message):
    state = database.get_state(message.chat.id)
    if state[0] == states['wait_list_name']:
        add_list(message.chat.id, message.text)
    elif state[0] == states['wait_note_name']:
        add_note(message.chat.id, message.text)
    elif state[0] == states['edit_list']:
        new_list_name(message.chat.id, message.text)
    elif state[0] == states['edit_note']:
        new_note(message.chat.id, message.text)
    elif state[0] == states['note_chosen']:
        database.delete_note(message.chat.id)
        database.set_state(message.chat.id, states['list_menu'])
        show_cur_n(message.chat.id, int(database.get_cur_list_numb(message.chat.id)[0]))


@bot.message_handler(func=lambda message: message.content_type == 'text' and message.text == '◾️ Edit name')
def edit_name(message):
    state = database.get_state(message.chat.id)
    if state[0] == states['wait_list_name']:
        add_list(message.chat.id, message.text)
    elif state[0] == states['wait_note_name']:
        add_note(message.chat.id, message.text)
    elif state[0] == states['edit_list']:
        new_list_name(message.chat.id, message.text)
    elif state[0] == states['edit_note']:
        new_note_name(message.chat.id, message.text)
    elif state[0] == states['list_chosen']:
        database.set_state(message.chat.id, states['edit_list'])
        bot.send_message(message.chat.id, 'Enter new name:',
                         reply_markup=markups.none_markup)
    elif state[0] == states['note_chosen']:
        database.set_state(message.chat.id, states['edit_note'])
        bot.send_message(message.chat.id, "Enter new note name",
                         reply_markup=markups.none_markup)


@bot.message_handler(func=lambda message: message.content_type == 'text' and message.text == '➕ New note')
def new_note(message):
    state = database.get_state(message.chat.id)
    if state[0] == states['wait_list_name']:
        add_list(message.chat.id, message.text)
    elif state[0] == states['wait_note_name']:
        add_note(message.chat.id, message.text)
    elif state[0] == states['list_chosen']:
        database.set_state(message.chat.id, states['wait_note_name'])
        bot.send_message(message.chat.id, 'Enter the name of new note',
                         reply_markup=markups.none_markup)


@bot.message_handler(func=lambda message: message.content_type == 'text' and message.text == '➕ Attach item')
def attach_item(message):
    state = database.get_state(message.chat.id)
    if state[0] == states['wait_list_name']:
        add_list(message.chat.id, message.text)
    elif state[0] == states['wait_note_name']:
        add_note(message.chat.id, message.text)
    elif state[0] == states['note_chosen']:
        database.set_state(message.chat.id, states['attach_menu'])
        bot.send_message(message.chat.id, 'Choose what to attach',
                         reply_markup=markups.attach_markup)


@bot.message_handler(func=lambda message: message.content_type == 'text' and message.text == '◾️ Get attached items')
def get_attached(message):
    state = database.get_state(message.chat.id)
    if state[0] == states['wait_list_name']:
        add_list(message.chat.id, message.text)
    elif state[0] == states['wait_note_name']:
        add_note(message.chat.id, message.text)
    elif state[0] == states['note_chosen']:
        database.set_state(message.chat.id, states['note_chosen'])
        bot.send_message(message.chat.id, 'Attached items:',
                         reply_markup=markups.note_chosen_markup)
        show_items(message.chat.id)


@bot.message_handler(func=lambda message: message.content_type == 'text' and message.text == 'Image')
def new_image(message):
    state = database.get_state(message.chat.id)
    if state[0] == states['wait_list_name']:
        add_list(message.chat.id, message.text)
    elif state[0] == states['wait_note_name']:
        add_note(message.chat.id, message.text)
    elif state[0] == states['attach_menu']:
        database.set_state(message.chat.id, states['wait_image'])
        bot.send_message(message.chat.id, 'Attached items:',
                         reply_markup=markups.none_markup)


@bot.message_handler(func=lambda message: message.content_type == 'text' and message.text == 'File')
def new_file(message):
    state = database.get_state(message.chat.id)
    if state[0] == states['wait_list_name']:
        add_list(message.chat.id, message.text)
    elif state[0] == states['wait_note_name']:
        add_note(message.chat.id, message.text)
    elif state[0] == states['attach_menu']:
        database.set_state(message.chat.id, states['wait_file'])
        bot.send_message(message.chat.id, 'Attached items:',
                         reply_markup=markups.none_markup)


@bot.message_handler(func=lambda message: message.content_type == 'text' and message.text == 'Voice')
def new_voice(message):
    state = database.get_state(message.chat.id)
    if state[0] == states['wait_list_name']:
        add_list(message.chat.id, message.text)
    elif state[0] == states['wait_note_name']:
        add_note(message.chat.id, message.text)
    elif state[0] == states['attach_menu']:
        database.set_state(message.chat.id, states['wait_voice'])
        bot.send_message(message.chat.id, 'Attached items:',
                         reply_markup=markups.none_markup)


@bot.message_handler(func=lambda message: message.content_type == 'text' and message.text == 'Audio')
def new_audio(message):
    state = database.get_state(message.chat.id)
    if state[0] == states['wait_list_name']:
        add_list(message.chat.id, message.text)
    elif state[0] == states['wait_note_name']:
        add_note(message.chat.id, message.text)
    elif state[0] == states['attach_menu']:
        database.set_state(message.chat.id, states['wait_audio'])
        bot.send_message(message.chat.id, 'Attached items:',
                         reply_markup=markups.none_markup)


@bot.message_handler(func=lambda message: message.content_type == 'text' and message.text[0] == '/')
def get_message(message):
    state = database.get_state(message.chat.id)
    if state[0] == states['list_menu']:
        show_n(message)
    if state[0] == states['list_chosen']:
        show_n_inside(message)


@bot.message_handler(func=lambda message: message.content_type == 'text')
def get_message(message):
    state = database.get_state(message.chat.id)
    if state[0] == states['wait_list_name']:
        add_list(message.chat.id, message.text)
    elif state[0] == states['wait_note_name']:
        add_note(message)
    elif state[0] == states['edit_list']:
        new_list_name(message.chat.id, message.text)
    elif state[0] == states['edit_note']:
        new_note_name(message.chat.id, message.text)


@server.route('/' + token, methods=['POST'])
def get_message():
    bot.process_new_updates([telebot.types.Update.de_json(request.stream.read().decode("utf-8"))])
    return "!", 200


@server.route("/")
def webhook():
    bot.remove_webhook()
    bot.set_webhook(url='https://telesaverbot.herokuapp.com/' + token)
    return "!", 200


if __name__ == "__main__":
    server.run(host="0.0.0.0", port=int(os.environ.get('PORT', 5000)))
