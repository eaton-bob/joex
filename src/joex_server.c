/*  =========================================================================
    joex_server - class description

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
    joex_server - 
@discuss
@end
*/

#include "joex_classes.h"

//  Structure of our class

struct _joex_server_t {
    int filler;     //  Declare class properties here
};


//  --------------------------------------------------------------------------
//  Create a new joex_server

joex_server_t *
joex_server_new (void)
{
    joex_server_t *self = (joex_server_t *) zmalloc (sizeof (joex_server_t));
    assert (self);
    //  Initialize class properties here
    return self;
}


//  --------------------------------------------------------------------------
//  Destroy the joex_server

void
joex_server_destroy (joex_server_t **self_p)
{
    assert (self_p);
    if (*self_p) {
        joex_server_t *self = *self_p;
        //  Free class properties here
        //  Free object itself
        free (self);
        *self_p = NULL;
    }
}

//  --------------------------------------------------------------------------
//  Self test of this class

void
joex_server_test (bool verbose)
{
    printf (" * joex_server: ");

    //  @selftest
    //  Simple create/destroy test
    joex_server_t *self = joex_server_new ();
    assert (self);
    joex_server_destroy (&self);
    //  @end
    printf ("OK\n");
}
