#include <ncurses.h>

// Alert types
enum alert_type
{
    KEY_CHANGED,
    USERNAME_CHANGED
};


WINDOW *ui_newwin(int height, int width, int start_y, int start_x);
void ui_init();
void ui_reset_input();
void ui_append_to_chat_room(char *input);
char *ui_get_alert_message(enum alert_type type);
void ui_refresh();
void ui_end();