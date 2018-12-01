import os
from flask import Flask, request
import telebot
from telebot import util
import markups
import db

# init bot
token = os.environ.get('TOKEN')
bot = telebot.TeleBot(token)

# for large text messages
large_text = open("large_text.txt", "rb").read()

# init db
database = db.Database()
database.init_tables()

# dictionary for bot states
states = {'init_state': 0,
          'list_menu': 1,
          'wait_list_name': 2,
          'list_chosen': 3,
          'note_menu': 4,
          'wait_note_name': 5,
          'note_chosen': 6,
          'wait_text': 7,
          'wait_image': 8,
          'wait_file': 9,
          'wait_voice': 10,
          'wait_audio': 11
          }

server = Flask(__name__)


def add_list(id, name):
    if '/' in name:
        bot.send_message(id, 'Invalid list name. Print another name of the list.',
                         reply_markup=markups.none_markup)
    else:
        database.new_list(id, name)
        database.set_state(id, states['init_state'])
        bot.send_message(id, 'List added', reply_markup=markups.init_markup)


# message handlers
@bot.message_handler(commands=['start'])
def start(message):
    database.new_user(message.chat.id, message.from_user.first_name, states['init_state'])
    bot.send_message(message.chat.id, 'Hello, ' + message.from_user.first_name,
                     reply_markup=markups.init_markup)


@bot.message_handler(func=lambda message: message.content_type == 'text' and message.text == 'New list')
def new_list(message):
    state = database.get_state(message.chat.id)
    bot.send_message(message.chat.id, state)
    if (state[0] == states['wait_list_name']):
        add_list(message.chat.id, message.text)
    else:
        database.set_state(message.chat.id, states['wait_list_name'])
        bot.send_message(message.chat.id, 'Print the name of new list',
                         reply_markup=markups.none_markup)


@bot.message_handler(func=lambda message: message.content_type == 'text' and message.text == 'Show lists')
def show_lists(message):
    if database.get_state(message.chat.id) == states['wait_list_name']:
        add_list(message.chat.id, message.text)
    else:
        lists = database.get_lists(message.chat.id)
        res = ''
        numb = 0
        for i in lists:
            res += '/' + str(numb) + ' ' + str(i[0]) + '\n'
            numb += 1
        splitted_text = util.split_string(res, 3000)
        bot.send_message(message.chat.id, 'Your lists: ')
        # for text in splitted_text:
        bot.send_message(message.chat.id, res)


@bot.message_handler(func=lambda message: message.content_type == 'text')
def get_message(message):
    state = database.get_state(message.chat.id)
    if state[0] == states['wait_list_name']:
        add_list(message.chat.id, message.text)


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
