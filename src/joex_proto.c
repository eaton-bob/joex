/*  =========================================================================
    joex_proto - class description

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
    joex_proto - 
@discuss
@end
*/

#include "joex_classes.h"

//  Structure of our class

struct _joex_proto_t {
    int filler;     //  Declare class properties here
};


//  --------------------------------------------------------------------------
//  Create a new joex_proto

joex_proto_t *
joex_proto_new (void)
{
    joex_proto_t *self = (joex_proto_t *) zmalloc (sizeof (joex_proto_t));
    assert (self);
    //  Initialize class properties here
    return self;
}


//  --------------------------------------------------------------------------
//  Destroy the joex_proto

void
joex_proto_destroy (joex_proto_t **self_p)
{
    assert (self_p);
    if (*self_p) {
        joex_proto_t *self = *self_p;
        //  Free class properties here
        //  Free object itself
        free (self);
        *self_p = NULL;
    }
}

//  --------------------------------------------------------------------------
//  Self test of this class

void
joex_proto_test (bool verbose)
{
    printf (" * joex_proto: ");

    //  @selftest
    //  Simple create/destroy test
    joex_proto_t *self = joex_proto_new ();
    assert (self);
    joex_proto_destroy (&self);
    //  @end
    printf ("OK\n");
}
