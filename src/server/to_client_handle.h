#ifndef _TO_SERVER_CLIENT_HANDLE_H_
#define _TO_SERVER_CLIENT_HANDLE_H_

#include "to_connection.h"
#include "to_backend.h"

#include "packages/to_packages.h"

struct TOServer;

typedef struct TOClientHandle {
    struct TOServer* server;
    Connection* connection;
} TOClientHandle;

typedef void (TOClientHandlePacket)(TOClientHandle* handle, void* buffer, unsigned long long length);

typedef struct TOClientHandlePacketCallback {
    TOReqPackageType type;
    TOClientHandlePacket* callback;
} TOClientHandlePacketCallback;

TOClientHandle* to_create_client_handle(struct TOServer* server, Connection* connection);

int to_handle_client(void *ptr);

#endif