#include "to_client.h"

#define BUFFLEN 1023

typedef void (TOClientCommandCallback)(TOClient* client, int argc, char* argv[]);

typedef struct TOClientCommand {
    const char* command;
    TOClientCommandCallback* callback;
} TOClientCommand;

void to_client_get_self_callback(TOClient* client, int argc, char* argv[]);
void to_client_map_callback(TOClient* client, int argc, char* argv[]);
void to_client_go_callback(TOClient* client, int argc, char* argv[]);
void to_client_ghand_callback(TOClient* client, int argc, char* argv[]);
void to_client_slashing_callback(TOClient* client, int argc, char* argv[]);
void to_client_stats_callback(TOClient* client, int argc, char* argv[]);
