#include <pthread.h>
#include <stdlib.h>
#include "utils.h"
#include "ui.h"
#include "listener.h"
#include "flags.h"

int main(int argc, char **argv)
{
    // setup and then check for flags.
    parse_args(argc, argv);
    if (flag__print_version)
    {
        printf("simple-chat " VERSION "\n");
        exit(0);
    }
    else if (flag__print_help)
    {
        printf("usage simple-chat [options]:\n");
        printf("%-20s %s", " --help", "print usage and exit\n");
        printf("%-20s %s", " --process-only", "disables the gui and usage of commands (expect for .scrc)\n");
        printf("%-20s %s", " --silent", "disables all the text output\n");
        printf("%-20s %s", " --version", "print version and exit\n");
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