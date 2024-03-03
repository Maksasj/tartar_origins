#include "to_client.h"

#define BUFFLEN 1023

typedef void (TOClientCommandCallback)(TOClient* client, int argc, char* argv[]);

typedef struct TOClientCommand {
    const char* command;
    TOClientCommandCallback* callback;
} TOClientCommand;

void to_client_get_self_entity_callback(TOClient* client, int argc, char* argv[]);
void to_client_use_callback(TOClient* client, int argc, char* argv[]);

/*
void to_client_sync_character_info(TOClient* client);

void to_client_go_command_callback(TOClient* client, int argc, char* argv[]);
void to_client_stats_command_callback(TOClient* client, int argc, char* argv[]);
void to_client_map_command_callback(TOClient* client, int argc, char* argv[]);
*/
