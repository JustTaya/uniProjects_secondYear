import os
from flask import Flask, request
import telebot
from telebot import types
import db

token = os.environ.get('TOKEN')
bot = telebot.TeleBot(token)
MAIN_MENU = types.ReplyKeyboardMarkup(resize_keyboard=True)
MAIN_MENU.row('New list')
MAIN_MENU.row('Show lists')
MAIN_MENU.row('FAQ')
db.init_db()

server = Flask(__name__)

@bot.message_handler(commands=['start'])
def start(message):
    custom_keyboard = [['New list', 'Show lists'],
                       ['F']]
    bot.send_message(message.chat_id, 'Hello, ' + message.from_user.first_name)


@bot.message_handler(func=lambda message: True, content_types=['text'])
def echo_message(message):
    bot.reply_to(message, message.text)


@server.route('/' + token, methods=['POST'])
def getMessage():
    bot.process_new_updates([telebot.types.Update.de_json(request.stream.read().decode("utf-8"))])
    return "!", 200


@server.route("/")
def webhook():
    bot.remove_webhook()
    bot.set_webhook(url='https://todoer-bot.herokuapp.com/')
    return "!", 200


if __name__ == "__main__":
    server.run(host="0.0.0.0", port=int(os.environ.get('PORT', 5000)))
