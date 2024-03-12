#ifndef _TO_SERVER_CLIENT_HANDLE_H_
#define _TO_SERVER_CLIENT_HANDLE_H_

#include "to_connection.h"
#include "to_backend.h"

#include "packages/to_packages.h"

struct TOServer;

typedef int (TOClientHandlePacket)(struct TOServer* server, Connection* con, EffectUse* use);

typedef struct TOClientHandlePacketCallback {
    TOReqPackageType type;
    TOClientHandlePacket* callback;
} TOClientHandlePacketCallback;

extern TOClientHandlePacketCallback callbacks[2];
extern unsigned long long callbackCount;

int to_handle_client(struct TOServer* server, Connection* con);

#endif