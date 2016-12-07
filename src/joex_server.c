/*  =========================================================================
    joex_server - joex_server

    Copyright (c) the Contributors as noted in the AUTHORS file.       
    This file is part of CZMQ, the high-level C binding for 0MQ:       
    http://czmq.zeromq.org.                                            
                                                                       
    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.           
    =========================================================================
*/

/*
@header
    Description of class for man page.
@discuss
    Detailed discussion of the class, if any.
@end
*/

#include "joex_classes.h"
//  TODO: Change these to match your project's needs
#include "../include/joex_proto.h"
#include "../include/joex_server.h"

//  ---------------------------------------------------------------------------
//  Forward declarations for the two main classes we use here

typedef struct _server_t server_t;
typedef struct _client_t client_t;

//  This structure defines the context for each running server. Store
//  whatever properties and structures you need for the server.

struct _server_t {
    //  These properties must always be present in the server_t
    //  and are set by the generated engine; do not modify them!
    zsock_t *pipe;              //  Actor pipe back to caller
    zconfig_t *config;          //  Current loaded configuration

    //  TODO: Add any properties you need here
    zhashx_t *clients;          // name -> client_t*
};

//  ---------------------------------------------------------------------------
//  This structure defines the state for each client connection. It will
//  be passed to each action in the 'self' argument.

struct _client_t {
    //  These properties must always be present in the client_t
    //  and are set by the generated engine; do not modify them!
    server_t *server;           //  Reference to parent server
    joex_proto_t *message;      //  Message in and out

    //  TODO: Add specific properties for your application
    char *name;
};

//  Include the generated server engine
#include "joex_server_engine.inc"

//  Allocate properties and structures for a new server instance.
//  Return 0 if OK, or -1 if there was an error.

static int
server_initialize (server_t *self)
{
    //  Construct properties here
    self->clients = zhashx_new ();
    return 0;
}

//  Free properties and structures for a server instance

static void
server_terminate (server_t *self)
{
    //  Destroy properties here
    zhashx_destroy (&self->clients);
}

//  Process server API method, return reply message if any

static zmsg_t *
server_method (server_t *self, const char *method, zmsg_t *msg)
{
    return NULL;
}

//  Apply new configuration.

static void
server_configuration (server_t *self, zconfig_t *config)
{
    //  Apply new configuration
}

//  Allocate properties and structures for a new client connection and
//  optionally engine_set_next_event (). Return 0 if OK, or -1 on error.

static int
client_initialize (client_t *self)
{
    //  Construct properties here
    self->name = strdup (joex_proto_name (self->message));
    return 0;
}

//  Free properties and structures for a client connection

static void
client_terminate (client_t *self)
{
    //  Destroy properties here
    zstr_free (&self->name);
}

//  ---------------------------------------------------------------------------
//  Selftest

void
joex_server_test (bool verbose)
{
    printf (" * joex_server: ");
    if (verbose)
        printf ("\n");

    //  @selftest
    zactor_t *server = zactor_new (joex_server, "server");
    if (verbose)
        zstr_send (server, "VERBOSE");
    zstr_sendx (server, "BIND", "ipc://@/joex_server", NULL);

    zsock_t *client = zsock_new (ZMQ_DEALER);
    assert (client);
    zsock_set_rcvtimeo (client, 2000);
    zsock_connect (client, "ipc://@/joex_server");

    joex_proto_t *request = joex_proto_new ();

    int r;
    // send hello
    joex_proto_set_id (request, JOEX_PROTO_HELLO);
    joex_proto_set_name (request, "client1");
    joex_proto_send (request, client);

    r = joex_proto_recv (request, client);
    assert (r == 0);
    assert (joex_proto_id (request) == JOEX_PROTO_OK);

    // send PONG
    joex_proto_set_id (request, JOEX_PROTO_PONG);
    joex_proto_send (request, client);

    r = joex_proto_recv (request, client);
    assert (r == 0);
    assert (joex_proto_id (request) == JOEX_PROTO_ERROR);
    assert (streq (joex_proto_reason (request), "command invalid"));

    // send hello client1 AGAIN
    joex_proto_set_id (request, JOEX_PROTO_HELLO);
    joex_proto_set_name (request, "client1");
    joex_proto_send (request, client);

    r = joex_proto_recv (request, client);
    assert (r == 0);
    assert (joex_proto_id (request) == JOEX_PROTO_ERROR);

    joex_proto_destroy (&request);

    zsock_destroy (&client);
    zactor_destroy (&server);
    //  @end
    printf ("OK\n");
}


//  ---------------------------------------------------------------------------
//  register_new_client
//

static void
register_new_client (client_t *self)
{
    if (zhashx_lookup (self->server->clients, self->name)) {
        engine_set_exception (self, exception_event);
        zsys_debug ("engine_set_exception");
    }
    else
        zhashx_insert (self->server->clients, self->name, self);
}


//  ---------------------------------------------------------------------------
//  signal_command_invalid
//

static void
signal_command_invalid (client_t *self)
{
    joex_proto_set_reason (self->message, "command invalid");
    joex_proto_set_code (self->message, 300);
}


//  ---------------------------------------------------------------------------
//  signal_duplicated_client
//

static void
signal_duplicated_client (client_t *self)
{
    joex_proto_set_reason (self->message, "duplicate user");
    joex_proto_set_code (self->message, 301);
}
