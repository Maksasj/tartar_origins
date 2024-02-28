#include "to_client.h"
#include "to_client_command.h"

TOClientCommand commands[] = {
    { "go",     to_client_go_command_callback       },

    { "info",   to_client_stats_command_callback    },
    { "stats",  to_client_stats_command_callback    },

    { "map",    to_client_map_command_callback      },
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

    for(unsigned int i = 0; i < commandCount; ++i) {
        if(strcmp(argv[0], commands[i].command) == 0) {
            commands[i].callback(client, argc, argv);
            break;
        }
    }

    return 0;
}

int main(){
    TOClient* client = to_new_client();

    printf("Trying to connect\n");
    int res = to_client_connect(client, "127.0.0.1", 6969);
    if(!res) {
        printf("Failed to conenct\n");
        return 1;
    }
    printf("Successfully connected to server\n");

    to_client_sync_character_info(client);

    while(1) {
        if(to_client_handle(client))
            break;
    }

    close(client->socket);

    return 0;
}