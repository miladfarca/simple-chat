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
        // :info
        if (strcmp(input + 1, "info") == 0)
        {
            print_info();
            return TRUE;
        }
        // :help
        if (strcmp(input + 1, "help") == 0)
        {
            print_help();
            return TRUE;
        }
        // :key [new key]
        char key_[4] = {0}; // 1 extra, strcmp needs to hit a null char.
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
        // :address [new address]
        char address_[8] = {0};
        memcpy(address_, input + 1, 7);
        if (strcmp(address_, "address") == 0)
        {
            if (set_address(input + 9))
            {
                ui_append_to_chat_room(ui_get_alert_message(ADDRESS_CHANGED));
                return TRUE;
            }
            ui_append_to_chat_room(ui_get_alert_message(INVALID_INPUT));
            return TRUE;
        }
        // :port [new port]
        char port_[5] = {0};
        memcpy(port_, input + 1, 4);
        if (strcmp(port_, "port") == 0)
        {
            // This change can only be done before the listener thread starts, hence
            // can only be done before full initializations.
            if (!env_initialized())
            {
                set_port(input + 6);
                return TRUE;
            }
            ui_append_to_chat_room(ui_get_alert_message(CHANGE_PAST_INITIALIZATION));
            return TRUE;
        }
        return TRUE;
    }
    return FALSE;
}