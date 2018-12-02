from telebot import types

init_markup = types.ReplyKeyboardMarkup(row_width=1)
add_button = types.KeyboardButton('New list')
show_button = types.KeyboardButton('Show lists')
faq_button = types.KeyboardButton('FAQ')
init_markup.add(add_button, show_button, faq_button)

none_markup = types.ReplyKeyboardMarkup(row_width=1)
back_button = types.KeyboardButton('Go back')
none_markup.add(add_button, back_button)

list_chosen_markup = types.ReplyKeyboardMarkup(row_width=1)
add_button = types.KeyboardButton('New note')
edit_button = types.KeyboardButton('Edit name')
delete_button = types.KeyboardButton('Delete list')
# back_button = types.KeyboardButton('Go back')
list_chosen_markup.add(add_button, edit_button, delete_button, back_button)

note_chosen_markup = types.ReplyKeyboardMarkup(row_width=1)
edit_button = types.KeyboardButton('Edit name')
delete_button = types.KeyboardButton('Delete note')
back_button = types.KeyboardButton('Go back')
note_chosen_markup.add(add_button, edit_button, delete_button, back_button)
