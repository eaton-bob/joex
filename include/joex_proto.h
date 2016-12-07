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

#ifndef JOEX_PROTO_H_INCLUDED
#define JOEX_PROTO_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

//  @interface
//  Create a new joex_proto
JOEX_EXPORT joex_proto_t *
    joex_proto_new (void);

//  Destroy the joex_proto
JOEX_EXPORT void
    joex_proto_destroy (joex_proto_t **self_p);

//  Self test of this class
JOEX_EXPORT void
    joex_proto_test (bool verbose);

//  @end

#ifdef __cplusplus
}
#endif

#endif
