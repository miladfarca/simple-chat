#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <arpa/inet.h>
#include "ui.h"
#include "utils.h"
#include "commands.h"

// globals
BOOL initialized = FALSE;
char username[MAX_USER_NAME_LENGTH] = {0};
unsigned char key[KEY_LENGTH] = {0};
unsigned char iv[IV_LENGTH] = {0}; //TODO
unsigned int address = ADDRESS;
unsigned short port = PORT;

BOOL env_initialized()
{
    return initialized;
}

void init_env()
{
    // setup username.
    set_username_from_sys();

    // setup key.
    set_key(DEFAULT_KEY);

    // check if user has a .scrc file, use it to reset the settings.
    maybe_read_scrc();

    initialized = TRUE;
}

void maybe_read_scrc()
{
    // check if `~/.scrc` exists and user has access to it.
    const char *homedir;
    if ((homedir = getenv("HOME")) == NULL)
    {
        homedir = getpwuid(getuid())->pw_dir;
    }
    char buff[50] = {0};
    char *file_name = SCRC_FILE_PATH;
    int homedir_length = strlen(homedir);
    memcpy(buff, homedir, homedir_length);
    memcpy(buff + homedir_length, file_name, strlen(file_name));
    if (access(buff, R_OK) == 0)
    {
        FILE *fp;
        char *line = NULL;
        size_t len = 0;
        ssize_t read;

        fp = fopen(buff, "r");
        if (fp != NULL)
        {
            while ((read = getline(&line, &len, fp)) != -1)
            {
                char command[20] = {':'};
                memcpy(command + 1, line, read - 1); // don't read the `\n` char.
                maybe_run_command(command);
            }

            fclose(fp);
            if (line)
            {
                free(line);
            }
        }
    }
}

void set_username_from_sys()
{
    uid_t uid = geteuid();
    struct passwd *pw = getpwuid(uid);
    if (pw)
    {
        memcpy(username, pw->pw_name, MAX_USER_NAME_LENGTH);
        return;
    }
    // Set a random username.
    srand(time(NULL));
    int random = (rand() % 100) + 1; // random int between 0 and 100.
    char random_s[4] = {0};          // include extra byte for \0 added by sprintf.
    sprintf(random_s, "%d", random);
    memcpy(username, random_s, sizeof(random_s));
}

void set_username(char *new_username)
{
    char buffer[MAX_USER_NAME_LENGTH] = {0};
    int length = strlen(new_username);
    if (length > MAX_USER_NAME_LENGTH)
    {
        length = MAX_USER_NAME_LENGTH;
    }
    memcpy(buffer, new_username, length);
    memcpy(username, buffer, MAX_USER_NAME_LENGTH);
}

char *get_username()
{
    return username;
}

void set_key(char *new_key)
{
    char buffer[KEY_LENGTH] = {0};
    int length = strlen(new_key);
    if (length > KEY_LENGTH)
    {
        length = KEY_LENGTH;
    }
    memcpy(buffer, new_key, length);
    memcpy(key, buffer, KEY_LENGTH);
}

BOOL set_address(char *new_address)
{
    // convert it to binary format.
    struct in_addr addr;
    if (inet_aton(new_address, &addr) == 0)
    {
        return FALSE;
    }
    // convert to host byte order.
    address = ntohl(addr.s_addr);
    return TRUE;
}

void set_port(char *new_port)
{
    port = (unsigned short)atoi(new_port);
}

void print_info()
{
    ui_append_to_chat_room("[username = ");
    ui_append_to_chat_room(username);
    ui_append_to_chat_room(", ");
    ui_append_to_chat_room("address = ");
    // convert to network order, needed by ntoa.
    struct in_addr ip_addr;
    ip_addr.s_addr = htonl(address);
    ui_append_to_chat_room(inet_ntoa(ip_addr));
    ui_append_to_chat_room(", ");
    ui_append_to_chat_room("port = ");
    // port to string.
    char port_s[MAX_PORT_LEGNTH + 1] = {0}; // include extra byte for \0 added by sprintf.
    sprintf(port_s, "%d", PORT);
    ui_append_to_chat_room(port_s);
    ui_append_to_chat_room("]\n");
}

void end()
{
    ui_end();
    exit(0);
}
