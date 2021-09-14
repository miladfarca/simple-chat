#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "ui.h"
#include "utils.h"

// globals
char username[MAX_USER_NAME_LENGTH] = {0};
unsigned char key[KEY_LENGTH] = {0};
unsigned char iv[IV_LENGTH] = {0}; //TODO

void init_env()
{
    // setup username.
    set_username_from_sys();

    // setup key.
    set_key(DEFAULT_KEY);
}

void set_username_from_sys()
{
    int un = getlogin_r(username, MAX_USER_NAME_LENGTH);
    if (un < 0)
    {
        srand(time(NULL));
        int random = (rand() % 100) + 1; // random int between 0 and 100.
        char random_s[7] = {0};
        sprintf(random_s, "%d", random);
        memcpy(username, random_s, sizeof(random_s));
    }
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

void end()
{
    ui_end();
    exit(0);
}