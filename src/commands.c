#include "utils.h"
#include <stdlib.h>
#include <string.h>
#include "ui.h"

BOOL maybe_run_command(char *input)
{
    if (input[0] == ':')
    {
        // :q
        if (strcmp(input + 1, "q") == 0)
        {
            end();
        }
        // :c
        if (strcmp(input + 1, "c") == 0)
        {
            ui_clear_chat_room();
            return TRUE;
        }
        // :ref
        if (strcmp(input + 1, "ref") == 0)
        {
            ui_refresh();
            return TRUE;
        }
        // :key [new key]
        char key_[4] = {0};
        memcpy(key_, input + 1, 3);
        if (strcmp(key_, "key") == 0)
        {
            set_key(input + 5);
            ui_append_to_chat_room(ui_get_alert_message(KEY_CHANGED));
            return TRUE;
        }
        // :name [new name]
        char name_[5] = {0};
        memcpy(name_, input + 1, 4);
        if (strcmp(name_, "name") == 0)
        {
            set_username(input + 6);
            ui_append_to_chat_room(ui_get_alert_message(USERNAME_CHANGED));
            return TRUE;
        }
        return TRUE;
    }
    return FALSE;
}