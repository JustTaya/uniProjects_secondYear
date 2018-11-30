import os
from flask import Flask, request
import telebot
from telebot import types
import db

token = os.environ.get('TOKEN')
bot = telebot.TeleBot(token)
database = db.Database()
database.init_tables()

server = Flask(__name__)


@bot.message_handler(commands=['start'])
def start(message):
    # db.cur.execute(
    #    """INSERT INTO Users (userID,first_name,State) VALUES (%s, %s, %s)",(message.char.id, message.chat.first_name, 0)""")
    markup = types.ReplyKeyboardMarkup(row_width=2)
    add_button = types.KeyboardButton('New list')
    show_button = types.KeyboardButton('Show lists')
    faq_button = types.KeyboardButton('FAQ')
    markup.add(add_button, show_button, faq_button)
    bot.send_message(message.chat.id, 'Hello, ' + message.from_user.first_name)


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
