#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include "utils.h"
#include "ui.h"
#include "listener.h"
#include "aes.h"

void msg_receive(int sock)
{
    char recv_encrypted_data[MAX_DATA_LENGTH] = {0};
    char raw_data[MAX_DATA_LENGTH] = {0};
    int encrypted_data_length;
    // receive a single msg (blocking).
    // UDP datagaram will have the actual data length within it.
    if ((encrypted_data_length = recvfrom(sock, recv_encrypted_data, MAX_DATA_LENGTH, 0, NULL, 0)) < 0)
        perror("recvfrom");

    // decrypt the data.
    int raw_data_length;
    if ((raw_data_length = msg_decrypt((unsigned char *)recv_encrypted_data, encrypted_data_length, key, iv, (unsigned char *)raw_data)) > 0)
    {
        raw_data[raw_data_length] = '\n';
        raw_data[raw_data_length + 1] = '\0';

        // separate the magic data, username and the message and constrcut the string to be displayed.
        int offset = 0;
        unsigned short magic_data;
        memcpy(&magic_data, raw_data, sizeof(magic_data));
        offset += sizeof(magic_data);
        if (magic_data == MAGIC_DATA)
        {
            // username.
            char username[MAX_USER_NAME_LENGTH + 1] = {0}; // 1 extra to hold \0 char.
            memcpy(username, raw_data + offset, MAX_USER_NAME_LENGTH);
            offset += MAX_USER_NAME_LENGTH;
            ui_append_to_chat_room(username);
            ui_append_to_chat_room("> ");

            // message.
            char message[MAX_INPUT_LENGTH + 2] = {0}; // 2 extras to hold \n and \0 chars.
            memcpy(message, raw_data + offset, MAX_INPUT_LENGTH);
            message[strlen(message) + 1] = '\n';
            ui_append_to_chat_room(message);
        }
    }
    // call recursively.
    msg_receive(sock);
}

void *msg_listen_thread()
{
    int sock = 0;
    struct sockaddr_in s;
    if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
        perror("socket");

    memset(&s, 0, sizeof(s));
    s.sin_family = AF_INET;
    s.sin_addr.s_addr = htonl(INADDR_ANY);
    s.sin_port = htons(port);

    int reuse_port = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEPORT, &reuse_port, sizeof(reuse_port)) < 0)
        perror("setsockopt");

    if (bind(sock, (struct sockaddr *)&s, sizeof(s)) < 0)
        perror("bind");

    msg_receive(sock);

    close(sock);
    return NULL;
}
