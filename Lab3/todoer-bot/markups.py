from telebot import types

init_markup = types.ReplyKeyboardMarkup(row_width=1)
add_button = types.KeyboardButton('New list')
show_button = types.KeyboardButton('Show lists')
faq_button = types.KeyboardButton('FAQ')
init_markup.add(add_button, show_button, faq_button)

none_markup = types.ForceReply(selective=False)
