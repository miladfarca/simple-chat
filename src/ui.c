#include "utils.h"
#include "ui.h"
#include "sender.h"
#include "commands.h"
#include "flags.h"

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
  if (!flag__process_only)
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
}

void ui_reset_input()
{
  // move cursor to input box
  // and wait for input (blocking).
  char input[MAX_INPUT_LENGTH] = {0};
  if (!flag__process_only)
  {
    wscanw(chat_input_content, "%" MAX_INPUT_LENGTH_S "[^\n]", input);

    // clear input.
    werase(chat_input_content);
    wrefresh(chat_input_content);

    // execute as command or send the message.
    if (!maybe_run_command(input))
    {
      msg_send(input);
    }
  }
  else
  {
    scanf("%" MAX_INPUT_LENGTH_S "[^\n]", input);
    msg_send(input);
    getchar(); // there is a dangling `\n` in stdin which we need to get rid of.
               // fflush(stdin); wont work:
               // > The fflush function does not flush data out of an input stream; it
               //    is instead used to push data buffered in an output stream to the destination
  }
  ui_reset_input();
}

void ui_append_to_chat_room(char *input)
{
  // '\n\0' should already be part of the input.
  if (!flag__silent)
  {
    if (flag__process_only)
    {
      printf("%s", input);
      // Doing a printf without `\n` will not auto flush to stdout: https://stackoverflow.com/q/1716296
      // but there is a `scanf` coming later which could cause a flush: https://stackoverflow.com/q/66815208/14940626
      // However, if stdout is redirected with `>` then the terminal is no longer interactive which means
      // a flush will not happen automatically with scanf and we will need to do it manually.
      fflush(stdout);
      return;
    }
    waddstr(chat_room_content, input);
    wrefresh(chat_room_content);
  }
}

char *ui_get_alert_message(enum alert_type type)
{
  switch (type)
  {
  case KEY_CHANGED:
    return "[key was updated]\n";
  case USERNAME_CHANGED:
    return "[username was updated]\n";
  case ADDRESS_CHANGED:
    return "[address was updated]\n";
  case CHANGE_PAST_INITIALIZATION:
    return "[cannot change after initialization, use .scrc file instead]\n";
  case INVALID_INPUT:
    return "[input was invalid, command is ignored]\n";
  case SEND_ERROR:
    return "[an error occurred while sending your message]\n";
  }
  return NULL;
}

void ui_clear_chat_room()
{
  wclear(chat_room_content);
  wrefresh(chat_room_content);
}

void ui_refresh()
{
  refresh();
}

void ui_end()
{
  endwin();
}
