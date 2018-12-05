from telebot import types

init_markup = types.ReplyKeyboardMarkup(row_width=2)
add_button = types.KeyboardButton('➕ New list')
show_button = types.KeyboardButton('◾️ Show lists')
faq_button = types.KeyboardButton('◾️ FAQ')
init_markup.add(add_button, show_button, faq_button)

none_markup = types.ReplyKeyboardMarkup(row_width=1)
cancel_button = types.KeyboardButton('✖️ Cancel')
none_markup.add(cancel_button)

list_chosen_markup = types.ReplyKeyboardMarkup(row_width=2)
add_button = types.KeyboardButton('➕ New note')
edit_button = types.KeyboardButton('◾️ Edit name')
delete_button = types.KeyboardButton('✖️ Delete list')
back_button = types.KeyboardButton('⬅️ Go back')
list_chosen_markup.add(add_button, edit_button, delete_button, back_button)

note_chosen_markup = types.ReplyKeyboardMarkup(row_width=2)
edit_button = types.KeyboardButton('◾️ Edit name')
delete_button = types.KeyboardButton('✖️ Delete note')
attach_button = types.KeyboardButton('➕ Attach item')
get_button = types.KeyboardButton('◾️ Get attached items')
# back_button = types.KeyboardButton('⬅️ 🔙🔙🔙🔙🔙Go back')
note_chosen_markup.add(edit_button, delete_button, attach_button, get_button, back_button)

attach_markup = types.ReplyKeyboardMarkup(row_width=2)
Image = types.KeyboardButton("Image")
File = types.KeyboardButton("File")
Voice = types.KeyboardButton("Voice")
Audio = types.KeyboardButton("Audio")
attach_markup.add(Image, File, Voice, Audio)
