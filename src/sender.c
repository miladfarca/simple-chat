#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include "utils.h"
#include "sender.h"
#include "aes.h"

void msg_send(char *msg)
{
    int sock = 0;
    struct sockaddr_in s;
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
        perror("socket");

    s.sin_family = AF_INET;
    s.sin_addr.s_addr = htonl(INADDR_BROADCAST);
    s.sin_port = htons(PORT);

    int broadcast_enable = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &broadcast_enable, sizeof(broadcast_enable)))
        perror("setsockopt");

    char raw_data[MAX_DATA_LENGTH] = {0};
    char encrypted_data[MAX_DATA_LENGTH] = {0};
    int offset = 0;
    // append magic data to the beginning.
    unsigned short magic_data = MAGIC_DATA;
    memcpy(raw_data, &magic_data, sizeof(magic_data));
    offset += sizeof(magic_data);

    // next append the user name, use all the space.
    memcpy(raw_data + offset, get_username(), MAX_USER_NAME_LENGTH);
    offset += sizeof(username);

    // append the data.
    memcpy(raw_data + offset, msg, strlen(msg));

    // encrypt the data.
    // MD and username have fixed size. msg could be variable.
    int raw_data_length = MAGIC_DATA_LENGTH + MAX_USER_NAME_LENGTH + strlen(msg);

    int encrypted_data_length = msg_encrypt((unsigned char *)raw_data, raw_data_length, key, iv,
                                            (unsigned char *)encrypted_data);

    if (sendto(sock, encrypted_data, encrypted_data_length, 0, (struct sockaddr *)&s, sizeof(struct sockaddr_in)) < 0)
        perror("sendto");
}
