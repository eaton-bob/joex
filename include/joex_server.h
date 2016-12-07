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

#ifndef JOEX_SERVER_H_INCLUDED
#define JOEX_SERVER_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

//  @interface
//  Create a new joex_server
JOEX_EXPORT joex_server_t *
    joex_server_new (void);

//  Destroy the joex_server
JOEX_EXPORT void
    joex_server_destroy (joex_server_t **self_p);

//  Self test of this class
JOEX_EXPORT void
    joex_server_test (bool verbose);

//  @end

#ifdef __cplusplus
}
#endif

#endif
