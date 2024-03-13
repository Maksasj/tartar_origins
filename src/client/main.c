#include "to_client.h"
#include "to_client_command.h"

#define TO_SERVER_PORT 6969
#define TO_SERVER_ADDRESS "127.0.0.1"

TOClientCommand commands[] = {
    { "self",       to_client_get_self_callback     },
    { "map",        to_client_map_callback          },
    { "go",         to_client_go_callback           },
    { "ghand",      to_client_ghand_callback        },
    { "slashing",   to_client_slashing_callback     }
};
unsigned int commandCount = sizeof(commands) / sizeof(TOClientCommand);

int to_client_handle(TOClient* client) {
    printf("> ");

    char input[BUFFLEN];
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("Failed to fgets command\n");
        return 0;
    }

    input[strcspn(input, "\n")] = '\0';

    char *argv[10];
    int argc = 0;

    char *token = strtok(input, " \t"); // Split based on spaces and tabs
    while (token != NULL && argc < 10) {
        argv[argc++] = token;
        token = strtok(NULL, " \t");
    }

    if(argc == 0)
        return 0;

    if(strcmp(argv[0], "exit") == 0)
        return 1;

    for(unsigned int i = 0; i < commandCount; ++i)
        if(strcmp(argv[0], commands[i].command) == 0)
            commands[i].callback(client, argc, argv);

    return 0;
}

int main(){
    TOClient* client = to_new_client();
    if(client == NULL) {
        TO_LOG(TO_ERROR, "Cannot create socket");
        return 1;
    }

    TO_LOG(TO_INFO, "Trying connect to server %s:%d", TO_SERVER_ADDRESS, TO_SERVER_PORT);
    int res = to_client_connect(client, TO_SERVER_ADDRESS, TO_SERVER_PORT);

    if(!res) {
        TO_LOG(TO_ERROR, "Failed to connect to server");
        return 0;
    }

    TO_LOG(TO_INFO, "Successfully connected to server");

    for(;;)
        if(to_client_handle(client))
            break;

    to_close_client(client);
    to_free_client(client);

    return 0;
}