/*  =========================================================================
    joex_client - JOEX Client

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
#include "../include/joex_client.h"

//  Forward reference to method arguments structure
typedef struct _client_args_t client_args_t;

//  This structure defines the context for a client connection
typedef struct {
    //  These properties must always be present in the client_t
    //  and are set by the generated engine. The cmdpipe gets
    //  messages sent to the actor; the msgpipe may be used for
    //  faster asynchronous message flows.
    zsock_t *cmdpipe;           //  Command pipe to/from caller API
    zsock_t *msgpipe;           //  Message pipe to/from caller API
    zsock_t *dealer;            //  Socket to talk to server
    joex_proto_t *message;      //  Message to/from server
    client_args_t *args;        //  Arguments from methods

    //  TODO: Add specific properties for your application
} client_t;

//  Include the generated client engine
#include "joex_client_engine.inc"

//  Allocate properties and structures for a new client instance.
//  Return 0 if OK, -1 if failed

static int
client_initialize (client_t *self)
{
    return 0;
}

//  Free properties and structures for a client instance

static void
client_terminate (client_t *self)
{
    //  Destroy properties here
}


//  ---------------------------------------------------------------------------
//  Selftest

void
joex_client_test (bool verbose)
{
    printf (" * joex_client: ");
    if (verbose)
        printf ("\n");

    //  @selftest
    // TODO: fill this out
    joex_client_t *client = joex_client_new ();
    joex_client_set_verbose(client, verbose);
    joex_client_destroy (&client);
    //  @end
    printf ("OK\n");
}


//  ---------------------------------------------------------------------------
//  remember_client_address
//

static void
remember_client_address (client_t *self)
{
}


//  ---------------------------------------------------------------------------
//  connect_to_server_endpoint
//

static void
connect_to_server_endpoint (client_t *self)
{
}


//  ---------------------------------------------------------------------------
//  set_client_address
//

static void
set_client_address (client_t *self)
{
}


//  ---------------------------------------------------------------------------
//  use_connect_timeout
//

static void
use_connect_timeout (client_t *self)
{
}


//  ---------------------------------------------------------------------------
//  client_is_connected
//

static void
client_is_connected (client_t *self)
{
}


//  ---------------------------------------------------------------------------
//  signal_success
//

static void
signal_success (client_t *self)
{
}


//  ---------------------------------------------------------------------------
//  signal_server_not_present
//

static void
signal_server_not_present (client_t *self)
{
}
