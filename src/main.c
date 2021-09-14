#include <pthread.h>
#include <stdlib.h>
#include "utils.h"
#include "ui.h"
#include "listener.h"
#include "flags.h"

int main(int argc, char **argv)
{
    //setup flags
    parse_args(argc, argv);
    //if help is needed
    if (flag__print_help)
    {
        printf("SC - Simple Chat " VERSION "\n");
        exit(0);
    }

    // init ui and the env.
    ui_init();
    init_env();

    // listen for incoming data in a new thread.
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, msg_listen_thread, NULL);

    // start input panel (blocking).
    ui_reset_input();

    pthread_join(thread_id, NULL);
    end();

    return 0;
}