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
<<<<<<< HEAD
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
    'edit_note': 11
}
=======
states = {'init_state': 0,
          'list_menu': 1,
          'wait_list_name': 2,
          'list_chosen': 3,
          # 'note_menu': 4,
          'wait_note_name': 5,
          'note_chosen': 6,
          'wait_text': 7,
          'wait_image': 8,
          'wait_file': 9,
          'wait_voice': 10,
          'wait_audio': 11
          }
>>>>>>> Database

server = Flask(__name__)


def add_list(id, name):
    if '/' in name:
        bot.send_message(id, 'Invalid list name. Print another name of the list.',
                         reply_markup=markups.none_markup)
    else:
        database.new_list(id, name)
        database.set_state(id, states['init_state'])
        bot.send_message(id, 'List added', reply_markup=markups.init_markup)


def add_note(id, name):
    if '/' in name:
        bot.send_message(id, 'Invalid note name. Print another name of the list.',
                         reply_markup=markups.none_markup)
    else:
<<<<<<< HEAD
        database.new_note(message.chat.id, message.text)
        bot.send_message(message.chat.id, 'Note added', reply_markup=markups.list_chosen_markup)
        bot.send_message(message.chat.id, database.get_cur_list_numb(message.chat.id)[0])
        show_cur_n(message.chat.id, int(database.get_cur_list_numb(message.chat.id)[0]))
=======
        database.new_note(id, name)
        database.set_state(id, states['init_state'])
        bot.send_message(id, 'List added', reply_markup=markups.init_markup)
>>>>>>> Database


def show_lists(id):
    database.set_state(id, states['list_menu'])
    lists = database.get_lists(id)
    res = ''
    numb = 0
    for i in lists:
        res += '/' + str(numb) + ' ' + str(i[0]) + '\n'
        numb += 1
    bot.send_message(id, 'Your lists: ')
<<<<<<< HEAD
    if numb <= 30:
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
=======
    for text in splitted_text:
        bot.send_message(id, text)
>>>>>>> Database


def show_notes(id):
    database.set_state(id, states['list_chosen'])
    notes = database.get_notes(id)
    list = database.get_cur_list(id)
    res = ''
    numb = 0
    for i in notes:
        res += '/' + str(numb) + ' ' + str(i[0]) + '\n'
        numb += 1
    splitted_text = util.split_string(res, 3000)
    bot.send_message(id, 'Notes in:' + str(list[0]))
    for text in splitted_text:
        bot.send_message(id, splitted_text)


<<<<<<< HEAD
def new_list_name(id, name):
    if '/' in name:
        bot.send_message(id, 'Invalid list name. Print another name of the list.',
                         reply_markup=markups.none_markup)
    else:
        database.edit_list(id, name)
        database.set_state(id, states['list_menu'])
        bot.send_message(id, 'List name edited', reply_markup=markups.init_markup)
        show_l(id)
=======
def init_state(id):
    database.set_state(id, states['init_state'])
    bot.send_message(id, 'Chose action', reply_markup=markups.init_markup)
>>>>>>> Database


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


<<<<<<< HEAD
@bot.message_handler(func=lambda message: message.content_type == 'text' and message.text == '➕ New list')
=======
@bot.message_handler(func=lambda message: message.text[0] == '/')
def get_message(message):
    state = database.get_state(message.chat.id)
    if state[0] == states['wait_list_name']:
        add_list(message.chat.id, message.text)
    else:
        text = message.text
        text.replace("/", "")
        if not text.isdigit():
            bot.send_message(id, 'Invalid command', reply_markup=markups.none_markup)
        else:
            if state[0] == states['list_menu']:
                notes = database.get_notes(message.chat.id, int(text))
                res = ''
                numb = 0
                for i in notes:
                    res += '/' + str(numb) + ' ' + str(i[0]) + '\n'
                    numb += 1
                splitted_text = util.split_string(res, 3000)
                bot.send_message(message.chat.id, 'Your lists: ')
                for text in splitted_text:
                    bot.send_message(message.chat.id, splitted_text)
            if state[0] == states['list_chosen']:
                res = ''


@bot.message_handler(func=lambda message: message.text == 'New list')
>>>>>>> Database
def new_list(message):
    state = database.get_state(message.chat.id)
    if state[0] == states['wait_list_name']:
        add_list(message.chat.id, message.text)
    elif state[0] == states['wait_note_name']:
        add_note(message.chat.id, message.text)
    else:
        database.set_state(message.chat.id, states['wait_list_name'])
        bot.send_message(message.chat.id, 'Print the name of new list',
                         reply_markup=markups.none_markup)


<<<<<<< HEAD
@bot.message_handler(func=lambda message: message.content_type == 'text' and message.text == '◾️ Show lists')
def show_lists(message):
    show_l(message.chat.id)


@bot.message_handler(func=lambda message: message.content_type == 'text' and message.text == '⬅️ Go back')
def go_back(message):
=======
@bot.message_handler(func=lambda message: message.text == 'New note')
def new_note(message):
>>>>>>> Database
    state = database.get_state(message.chat.id)
    if state[0] == states['wait_list_name']:
        add_list(message.chat.id, message.text)
    elif state[0] == states['wait_note_name']:
        add_note(message.chat.id, message.text)
<<<<<<< HEAD
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
=======
    else:
        database.set_state(message.chat.id, states['wait_note_name'])
        bot.send_message(message.chat.id, 'Print the name of new note',
                         reply_markup=markups.none_markup)


@bot.message_handler(func=lambda message: message.content_type == 'text' and message.text == 'Show lists')
def show_lists(message):
    show_lists(message.chat.id)
    database.set_state(message.chat.id, states['list_menu'])


@bot.message_handler(func=lambda message: message.text == 'Go back')
def go_back(message):
    state = database.get_state(message.chat.id)
    if state[0] == states['wait_list_name']:
        add_list(message.chat.id, message.text)
    elif state[0] == states['list_chosen']:
        database.setList(message.chat.id, None)
        show_lists(message.chat.id)
    elif state[0] == states['note_chosen']:
        database.set_state(message.chat.id, states['list_chosen'])
        show_notes(message.chat.id)


@bot.message_handler(content_types=['text'])
def get_message(message):
>>>>>>> Database
    state = database.get_state(message.chat.id)
    if state[0] == states['wait_list_name']:
        add_list(message.chat.id, message.text)
    elif state[0] == states['wait_note_name']:
        add_note(message.chat.id, message.text)
<<<<<<< HEAD
    elif state[0] == states['list_chosen']:
        database.set_state(message.chat.id, states['wait_note_name'])
        bot.send_message(message.chat.id, 'Enter the name of new note',
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
=======


# Handles all sent documents and audio files
@bot.message_handler(content_types=['document', 'audio'])
def handle_docs_audio(message):
    pass
>>>>>>> Database


@server.route('/' + token, methods=['POST'])
def get_message():
    bot.process_new_updates([telebot.types.Update.de_json(request.stream.read().decode("utf-8"))])
    return "!", 200


@server.route("/")
def webhook():
    bot.remove_webhook()
    bot.set_webhook(url='https://todoer-bot.herokuapp.com/')
    return "!", 200


if __name__ == "__main__":
    server.run(host="0.0.0.0", port=int(os.environ.get('PORT', 5000)))
