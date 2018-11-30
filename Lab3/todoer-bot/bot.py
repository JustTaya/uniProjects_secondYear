import os
from flask import Flask, request
import telebot
from telebot import types
import db

# init bot
token = os.environ.get('TOKEN')
bot = telebot.TeleBot(token)

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


# message handlers
@bot.message_handler(commands=['start'])
def start(message):
    database.new_user(message.chat.id, message.from_user.first_name, states['init_state'])
    markup = types.ReplyKeyboardMarkup(row_width=1)
    add_button = types.KeyboardButton('New list')
    show_button = types.KeyboardButton('Show lists')
    faq_button = types.KeyboardButton('FAQ')
    markup.add(add_button, show_button, faq_button)
    bot.send_message(message.chat.id, 'Hello, ' + message.from_user.first_name, reply_markup=markup)


@bot.message_handler(func=lambda message: message.content_type == 'text' and message.text == 'New list')
def new_list(message):
    bot.send_message(message.chat.id, 'Print the name of new list')


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
