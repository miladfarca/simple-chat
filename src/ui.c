#include "utils.h"
#include "ui.h"
#include "sender.h"
#include "commands.h"

WINDOW *chat_room_border;
WINDOW *chat_room_content;
WINDOW *chat_input_border;
WINDOW *chat_input_content;

WINDOW *ui_new_win(int height, int width, int start_y, int start_x, BOOL add_border, BOOL scrollable)
{
  WINDOW *win = newwin(height, width, start_y, start_x);
  if (add_border)
  {
    box(win, 0, 0);
  }
  if (scrollable)
  {
    scrollok(win, TRUE);
  }
  wrefresh(win);
  return win;
}

void ui_init()
{
  initscr();
  refresh();

  // get window size
  int win_y, win_x; // row, col
  getmaxyx(stdscr, win_y, win_x);

  // generate borders
  int chat_input_border_height = 4;
  int height = win_y - chat_input_border_height;
  int width = win_x;
  int start_x = 0;
  int start_y = 0;
  chat_room_border = ui_new_win(height, width, start_y, start_x, TRUE, FALSE);

  height = chat_input_border_height;
  width = win_x;
  start_x = 0;
  start_y = win_y - chat_input_border_height;
  chat_input_border = ui_new_win(height, width, start_y, start_x, TRUE, FALSE);

  // generate inner content
  int content_offset = 1;
  height = win_y - chat_input_border_height - (2 * content_offset);
  width = win_x - (2 * content_offset);
  start_x = content_offset;
  start_y = content_offset;
  chat_room_content = ui_new_win(height, width, start_y, start_x, FALSE, TRUE);

  height = chat_input_border_height - (2 * content_offset);
  width = win_x - (2 * content_offset);
  start_x = content_offset;
  start_y = win_y - chat_input_border_height + content_offset;
  chat_input_content = ui_new_win(height, width, start_y, start_x, FALSE, TRUE);
}

void ui_reset_input()
{
  // move cursor to input box
  // and wait for input (blocking).
  char input[MAX_INPUT_LENGTH] = {0};
  wscanw(chat_input_content, "%" MAX_INPUT_LENGTH_S "[^\n]", input);

  // clear input.
  werase(chat_input_content);
  wrefresh(chat_input_content);

  // execute as command or send the message.
  if (!maybe_run_commands(input))
  {
    msg_send(input);
  }

  ui_reset_input();
}

void ui_append_to_chat_room(char *input)
{
  waddstr(chat_room_content, input);
  wrefresh(chat_room_content);
}

char *ui_get_alert_message(enum alert_type type)
{
  switch (type)
  {
  case KEY_CHANGED:
    return "[key was updated]\n";
  case USERNAME_CHANGED:
    return "[username was updated]\n";
  }
  return NULL;
}

void ui_end()
{
  endwin();
}
