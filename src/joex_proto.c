/*  =========================================================================
<<<<<<< HEAD
    joex_proto - joex example protocol
=======
    joex_proto - joe example protocol
>>>>>>> 71fbb8dc832938493e68c2b249e3233edca66aca

    Codec class for joex_proto.

    ** WARNING *************************************************************
    THIS SOURCE FILE IS 100% GENERATED. If you edit this file, you will lose
    your changes at the next build cycle. This is great for temporary printf
    statements. DO NOT MAKE ANY CHANGES YOU WISH TO KEEP. The correct places
    for commits are:

     * The XML model used for this code generation: joex_proto.xml, or
     * The code generation script that built this file: zproto_codec_c
    ************************************************************************
    =========================================================================
*/

/*
@header
<<<<<<< HEAD
    joex_proto - joex example protocol
=======
    joex_proto - joe example protocol
>>>>>>> 71fbb8dc832938493e68c2b249e3233edca66aca
@discuss
@end
*/

#include "../include/joex_proto.h"

//  Structure of our class

struct _joex_proto_t {
    zframe_t *routing_id;               //  Routing_id from ROUTER, if any
    int id;                             //  joex_proto message ID
    byte *needle;                       //  Read/write pointer for serialization
    byte *ceiling;                      //  Valid upper limit for read pointer
    char name [256];                    //  name
    zhash_t *header;                    //  header
    size_t header_bytes;                //  Size of hash content
<<<<<<< HEAD
    char filename [256];                //  filename
    zchunk_t *data;                     //  data
    uint64_t size;                      //  size
    uint64_t offset;                    //  offset
    uint64_t checksum;                  //  checksum
    char reason [256];                  //  reason
=======
    char reason [256];                  //  reason
    uint64_t code;                      //  code
    zchunk_t *data;                     //  data
    uint64_t offset;                    //  offset
    uint64_t chunksize;                 //  chunksize
    uint64_t chunkchecksum;             //  chunkchecksum
    char filename [256];                //  filename
    uint64_t filesize;                  //  filesize
    uint64_t filechecksum;              //  filechecksum
>>>>>>> 71fbb8dc832938493e68c2b249e3233edca66aca
};

//  --------------------------------------------------------------------------
//  Network data encoding macros

//  Put a block of octets to the frame
#define PUT_OCTETS(host,size) { \
    memcpy (self->needle, (host), size); \
    self->needle += size; \
}

//  Get a block of octets from the frame
#define GET_OCTETS(host,size) { \
    if (self->needle + size > self->ceiling) { \
        zsys_warning ("joex_proto: GET_OCTETS failed"); \
        goto malformed; \
    } \
    memcpy ((host), self->needle, size); \
    self->needle += size; \
}

//  Put a 1-byte number to the frame
#define PUT_NUMBER1(host) { \
    *(byte *) self->needle = (byte) (host); \
    self->needle++; \
}

//  Put a 2-byte number to the frame
#define PUT_NUMBER2(host) { \
    self->needle [0] = (byte) (((host) >> 8)  & 255); \
    self->needle [1] = (byte) (((host))       & 255); \
    self->needle += 2; \
}

//  Put a 4-byte number to the frame
#define PUT_NUMBER4(host) { \
    self->needle [0] = (byte) (((host) >> 24) & 255); \
    self->needle [1] = (byte) (((host) >> 16) & 255); \
    self->needle [2] = (byte) (((host) >> 8)  & 255); \
    self->needle [3] = (byte) (((host))       & 255); \
    self->needle += 4; \
}

//  Put a 8-byte number to the frame
#define PUT_NUMBER8(host) { \
    self->needle [0] = (byte) (((host) >> 56) & 255); \
    self->needle [1] = (byte) (((host) >> 48) & 255); \
    self->needle [2] = (byte) (((host) >> 40) & 255); \
    self->needle [3] = (byte) (((host) >> 32) & 255); \
    self->needle [4] = (byte) (((host) >> 24) & 255); \
    self->needle [5] = (byte) (((host) >> 16) & 255); \
    self->needle [6] = (byte) (((host) >> 8)  & 255); \
    self->needle [7] = (byte) (((host))       & 255); \
    self->needle += 8; \
}

//  Get a 1-byte number from the frame
#define GET_NUMBER1(host) { \
    if (self->needle + 1 > self->ceiling) { \
        zsys_warning ("joex_proto: GET_NUMBER1 failed"); \
        goto malformed; \
    } \
    (host) = *(byte *) self->needle; \
    self->needle++; \
}

//  Get a 2-byte number from the frame
#define GET_NUMBER2(host) { \
    if (self->needle + 2 > self->ceiling) { \
        zsys_warning ("joex_proto: GET_NUMBER2 failed"); \
        goto malformed; \
    } \
    (host) = ((uint16_t) (self->needle [0]) << 8) \
           +  (uint16_t) (self->needle [1]); \
    self->needle += 2; \
}

//  Get a 4-byte number from the frame
#define GET_NUMBER4(host) { \
    if (self->needle + 4 > self->ceiling) { \
        zsys_warning ("joex_proto: GET_NUMBER4 failed"); \
        goto malformed; \
    } \
    (host) = ((uint32_t) (self->needle [0]) << 24) \
           + ((uint32_t) (self->needle [1]) << 16) \
           + ((uint32_t) (self->needle [2]) << 8) \
           +  (uint32_t) (self->needle [3]); \
    self->needle += 4; \
}

//  Get a 8-byte number from the frame
#define GET_NUMBER8(host) { \
    if (self->needle + 8 > self->ceiling) { \
        zsys_warning ("joex_proto: GET_NUMBER8 failed"); \
        goto malformed; \
    } \
    (host) = ((uint64_t) (self->needle [0]) << 56) \
           + ((uint64_t) (self->needle [1]) << 48) \
           + ((uint64_t) (self->needle [2]) << 40) \
           + ((uint64_t) (self->needle [3]) << 32) \
           + ((uint64_t) (self->needle [4]) << 24) \
           + ((uint64_t) (self->needle [5]) << 16) \
           + ((uint64_t) (self->needle [6]) << 8) \
           +  (uint64_t) (self->needle [7]); \
    self->needle += 8; \
}

//  Put a string to the frame
#define PUT_STRING(host) { \
    size_t string_size = strlen (host); \
    PUT_NUMBER1 (string_size); \
    memcpy (self->needle, (host), string_size); \
    self->needle += string_size; \
}

//  Get a string from the frame
#define GET_STRING(host) { \
    size_t string_size; \
    GET_NUMBER1 (string_size); \
    if (self->needle + string_size > (self->ceiling)) { \
        zsys_warning ("joex_proto: GET_STRING failed"); \
        goto malformed; \
    } \
    memcpy ((host), self->needle, string_size); \
    (host) [string_size] = 0; \
    self->needle += string_size; \
}

//  Put a long string to the frame
#define PUT_LONGSTR(host) { \
    size_t string_size = strlen (host); \
    PUT_NUMBER4 (string_size); \
    memcpy (self->needle, (host), string_size); \
    self->needle += string_size; \
}

//  Get a long string from the frame
#define GET_LONGSTR(host) { \
    size_t string_size; \
    GET_NUMBER4 (string_size); \
    if (self->needle + string_size > (self->ceiling)) { \
        zsys_warning ("joex_proto: GET_LONGSTR failed"); \
        goto malformed; \
    } \
    free ((host)); \
    (host) = (char *) malloc (string_size + 1); \
    memcpy ((host), self->needle, string_size); \
    (host) [string_size] = 0; \
    self->needle += string_size; \
}


//  --------------------------------------------------------------------------
//  Create a new joex_proto

joex_proto_t *
joex_proto_new (void)
{
    joex_proto_t *self = (joex_proto_t *) zmalloc (sizeof (joex_proto_t));
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

        //  Free class properties
        zframe_destroy (&self->routing_id);
        zhash_destroy (&self->header);
        zchunk_destroy (&self->data);

        //  Free object itself
        free (self);
        *self_p = NULL;
    }
}


<<<<<<< HEAD
//  --------------------------------------------------------------------------
//  Receive a joex_proto from the socket. Returns 0 if OK, -1 if
//  the recv was interrupted, or -2 if the message is malformed.
//  Blocks if there is no message waiting.

int
joex_proto_recv (joex_proto_t *self, zsock_t *input)
{
    assert (input);
    int rc = 0;

    if (zsock_type (input) == ZMQ_ROUTER) {
        zframe_destroy (&self->routing_id);
        self->routing_id = zframe_recv (input);
        if (!self->routing_id || !zsock_rcvmore (input)) {
            zsys_warning ("joex_proto: no routing ID");
            rc = -1;            //  Interrupted
            goto malformed;
        }
    }
    zmq_msg_t frame;
    zmq_msg_init (&frame);
    int size = zmq_msg_recv (&frame, zsock_resolve (input), 0);
    if (size == -1) {
        zsys_warning ("joex_proto: interrupted");
        rc = -1;                //  Interrupted
        goto malformed;
    }
    //  Get and check protocol signature
    self->needle = (byte *) zmq_msg_data (&frame);
    self->ceiling = self->needle + zmq_msg_size (&frame);

    uint16_t signature;
    GET_NUMBER2 (signature);
    if (signature != (0xAAA0 | 0)) {
        zsys_warning ("joex_proto: invalid signature");
        rc = -2;                //  Malformed
        goto malformed;
    }
    //  Get message id and parse per message type
    GET_NUMBER1 (self->id);

    switch (self->id) {
        case JOEX_PROTO_HELLO:
            GET_STRING (self->name);
            {
                size_t hash_size;
                GET_NUMBER4 (hash_size);
                self->header = zhash_new ();
                zhash_autofree (self->header);
                while (hash_size--) {
                    char key [256];
                    char *value = NULL;
                    GET_STRING (key);
                    GET_LONGSTR (value);
                    zhash_insert (self->header, key, value);
                    free (value);
                }
            }
            break;

        case JOEX_PROTO_PING:
            break;

        case JOEX_PROTO_PONG:
            break;

        case JOEX_PROTO_UPLOAD:
            GET_STRING (self->filename);
            break;

        case JOEX_PROTO_CHUNK:
            {
                size_t chunk_size;
                GET_NUMBER4 (chunk_size);
                if (self->needle + chunk_size > (self->ceiling)) {
                    zsys_warning ("joex_proto: data is missing data");
                    rc = -2;    //  Malformed
                    goto malformed;
                }
                zchunk_destroy (&self->data);
                self->data = zchunk_new (self->needle, chunk_size);
                self->needle += chunk_size;
            }
            GET_NUMBER8 (self->size);
            GET_NUMBER8 (self->offset);
            GET_NUMBER8 (self->checksum);
            break;

        case JOEX_PROTO_UPLOAD_FINISHED:
            break;

        case JOEX_PROTO_CLOSE:
            GET_STRING (self->filename);
            GET_NUMBER8 (self->size);
            break;

        case JOEX_PROTO_OK:
            break;

        case JOEX_PROTO_ERROR:
            GET_STRING (self->reason);
            break;

        default:
            zsys_warning ("joex_proto: bad message ID");
            rc = -2;            //  Malformed
            goto malformed;
    }
    //  Successful return
    zmq_msg_close (&frame);
    return rc;

    //  Error returns
    malformed:
        zmq_msg_close (&frame);
        return rc;              //  Invalid message
}


//  --------------------------------------------------------------------------
//  Send the joex_proto to the socket. Does not destroy it. Returns 0 if
//  OK, else -1.

int
joex_proto_send (joex_proto_t *self, zsock_t *output)
{
    assert (self);
    assert (output);

    if (zsock_type (output) == ZMQ_ROUTER)
        zframe_send (&self->routing_id, output, ZFRAME_MORE + ZFRAME_REUSE);

    size_t frame_size = 2 + 1;          //  Signature and message ID
    switch (self->id) {
        case JOEX_PROTO_HELLO:
            frame_size += 1 + strlen (self->name);
            frame_size += 4;            //  Size is 4 octets
            if (self->header) {
                self->header_bytes = 0;
                char *item = (char *) zhash_first (self->header);
                while (item) {
                    self->header_bytes += 1 + strlen (zhash_cursor (self->header));
                    self->header_bytes += 4 + strlen (item);
                    item = (char *) zhash_next (self->header);
                }
            }
            frame_size += self->header_bytes;
            break;
        case JOEX_PROTO_UPLOAD:
            frame_size += 1 + strlen (self->filename);
            break;
        case JOEX_PROTO_CHUNK:
            frame_size += 4;            //  Size is 4 octets
            if (self->data)
                frame_size += zchunk_size (self->data);
            frame_size += 8;            //  size
            frame_size += 8;            //  offset
            frame_size += 8;            //  checksum
            break;
        case JOEX_PROTO_CLOSE:
            frame_size += 1 + strlen (self->filename);
            frame_size += 8;            //  size
            break;
        case JOEX_PROTO_ERROR:
            frame_size += 1 + strlen (self->reason);
            break;
    }
    //  Now serialize message into the frame
    zmq_msg_t frame;
    zmq_msg_init_size (&frame, frame_size);
    self->needle = (byte *) zmq_msg_data (&frame);
    PUT_NUMBER2 (0xAAA0 | 0);
    PUT_NUMBER1 (self->id);
    size_t nbr_frames = 1;              //  Total number of frames to send

    switch (self->id) {
        case JOEX_PROTO_HELLO:
            PUT_STRING (self->name);
            if (self->header) {
                PUT_NUMBER4 (zhash_size (self->header));
                char *item = (char *) zhash_first (self->header);
                while (item) {
                    PUT_STRING (zhash_cursor (self->header));
                    PUT_LONGSTR (item);
                    item = (char *) zhash_next (self->header);
                }
            }
            else
                PUT_NUMBER4 (0);    //  Empty hash
            break;

        case JOEX_PROTO_UPLOAD:
            PUT_STRING (self->filename);
            break;

        case JOEX_PROTO_CHUNK:
            if (self->data) {
                PUT_NUMBER4 (zchunk_size (self->data));
                memcpy (self->needle,
                        zchunk_data (self->data),
                        zchunk_size (self->data));
                self->needle += zchunk_size (self->data);
            }
            else
                PUT_NUMBER4 (0);    //  Empty chunk
            PUT_NUMBER8 (self->size);
            PUT_NUMBER8 (self->offset);
            PUT_NUMBER8 (self->checksum);
            break;

        case JOEX_PROTO_CLOSE:
            PUT_STRING (self->filename);
            PUT_NUMBER8 (self->size);
            break;

        case JOEX_PROTO_ERROR:
            PUT_STRING (self->reason);
            break;

    }
    //  Now send the data frame
    zmq_msg_send (&frame, zsock_resolve (output), --nbr_frames? ZMQ_SNDMORE: 0);

    return 0;
}


//  --------------------------------------------------------------------------
//  Print contents of message to stdout

void
joex_proto_print (joex_proto_t *self)
{
    assert (self);
    switch (self->id) {
        case JOEX_PROTO_HELLO:
            zsys_debug ("JOEX_PROTO_HELLO:");
            zsys_debug ("    name='%s'", self->name);
            zsys_debug ("    header=");
            if (self->header) {
                char *item = (char *) zhash_first (self->header);
                while (item) {
                    zsys_debug ("        %s=%s", zhash_cursor (self->header), item);
                    item = (char *) zhash_next (self->header);
                }
            }
            else
                zsys_debug ("(NULL)");
            break;

        case JOEX_PROTO_PING:
            zsys_debug ("JOEX_PROTO_PING:");
            break;

        case JOEX_PROTO_PONG:
            zsys_debug ("JOEX_PROTO_PONG:");
            break;

        case JOEX_PROTO_UPLOAD:
            zsys_debug ("JOEX_PROTO_UPLOAD:");
            zsys_debug ("    filename='%s'", self->filename);
            break;

        case JOEX_PROTO_CHUNK:
            zsys_debug ("JOEX_PROTO_CHUNK:");
            zsys_debug ("    data=[ ... ]");
            zsys_debug ("    size=%ld", (long) self->size);
            zsys_debug ("    offset=%ld", (long) self->offset);
            zsys_debug ("    checksum=%ld", (long) self->checksum);
            break;

        case JOEX_PROTO_UPLOAD_FINISHED:
            zsys_debug ("JOEX_PROTO_UPLOAD_FINISHED:");
            break;

        case JOEX_PROTO_CLOSE:
            zsys_debug ("JOEX_PROTO_CLOSE:");
            zsys_debug ("    filename='%s'", self->filename);
            zsys_debug ("    size=%ld", (long) self->size);
            break;

        case JOEX_PROTO_OK:
            zsys_debug ("JOEX_PROTO_OK:");
            break;

        case JOEX_PROTO_ERROR:
            zsys_debug ("JOEX_PROTO_ERROR:");
            zsys_debug ("    reason='%s'", self->reason);
            break;

    }
}


//  --------------------------------------------------------------------------
//  Get/set the message routing_id

zframe_t *
joex_proto_routing_id (joex_proto_t *self)
{
    assert (self);
    return self->routing_id;
}

void
joex_proto_set_routing_id (joex_proto_t *self, zframe_t *routing_id)
{
    if (self->routing_id)
        zframe_destroy (&self->routing_id);
    self->routing_id = zframe_dup (routing_id);
}


//  --------------------------------------------------------------------------
//  Get/set the joex_proto id

int
joex_proto_id (joex_proto_t *self)
{
    assert (self);
    return self->id;
}

void
joex_proto_set_id (joex_proto_t *self, int id)
{
    self->id = id;
}

//  --------------------------------------------------------------------------
//  Return a printable command string

const char *
joex_proto_command (joex_proto_t *self)
{
    assert (self);
    switch (self->id) {
        case JOEX_PROTO_HELLO:
            return ("HELLO");
            break;
        case JOEX_PROTO_PING:
            return ("PING");
            break;
        case JOEX_PROTO_PONG:
            return ("PONG");
            break;
        case JOEX_PROTO_UPLOAD:
            return ("UPLOAD");
            break;
        case JOEX_PROTO_CHUNK:
            return ("CHUNK");
            break;
        case JOEX_PROTO_UPLOAD_FINISHED:
            return ("UPLOAD_FINISHED");
            break;
        case JOEX_PROTO_CLOSE:
            return ("CLOSE");
            break;
        case JOEX_PROTO_OK:
            return ("OK");
            break;
        case JOEX_PROTO_ERROR:
            return ("ERROR");
            break;
    }
    return "?";
}

//  --------------------------------------------------------------------------
//  Get/set the name field

const char *
joex_proto_name (joex_proto_t *self)
{
    assert (self);
    return self->name;
}

void
joex_proto_set_name (joex_proto_t *self, const char *value)
{
    assert (self);
    assert (value);
    if (value == self->name)
        return;
    strncpy (self->name, value, 255);
    self->name [255] = 0;
}


//  --------------------------------------------------------------------------
//  Get the header field without transferring ownership

zhash_t *
joex_proto_header (joex_proto_t *self)
{
    assert (self);
    return self->header;
}

//  Get the header field and transfer ownership to caller

zhash_t *
joex_proto_get_header (joex_proto_t *self)
{
    zhash_t *header = self->header;
    self->header = NULL;
    return header;
}

//  Set the header field, transferring ownership from caller

void
joex_proto_set_header (joex_proto_t *self, zhash_t **header_p)
{
    assert (self);
    assert (header_p);
    zhash_destroy (&self->header);
    self->header = *header_p;
    *header_p = NULL;
}


//  --------------------------------------------------------------------------
//  Get/set the filename field

const char *
joex_proto_filename (joex_proto_t *self)
{
    assert (self);
    return self->filename;
}

void
joex_proto_set_filename (joex_proto_t *self, const char *value)
{
    assert (self);
    assert (value);
    if (value == self->filename)
        return;
    strncpy (self->filename, value, 255);
    self->filename [255] = 0;
}


//  --------------------------------------------------------------------------
//  Get the data field without transferring ownership

zchunk_t *
joex_proto_data (joex_proto_t *self)
{
    assert (self);
    return self->data;
}

//  Get the data field and transfer ownership to caller

zchunk_t *
joex_proto_get_data (joex_proto_t *self)
{
    zchunk_t *data = self->data;
    self->data = NULL;
    return data;
}

//  Set the data field, transferring ownership from caller

void
joex_proto_set_data (joex_proto_t *self, zchunk_t **chunk_p)
{
    assert (self);
    assert (chunk_p);
    zchunk_destroy (&self->data);
    self->data = *chunk_p;
    *chunk_p = NULL;
}


//  --------------------------------------------------------------------------
//  Get/set the size field

uint64_t
joex_proto_size (joex_proto_t *self)
{
    assert (self);
    return self->size;
}

void
joex_proto_set_size (joex_proto_t *self, uint64_t size)
{
    assert (self);
    self->size = size;
}


//  --------------------------------------------------------------------------
//  Get/set the offset field

uint64_t
joex_proto_offset (joex_proto_t *self)
{
    assert (self);
    return self->offset;
}

void
joex_proto_set_offset (joex_proto_t *self, uint64_t offset)
{
    assert (self);
    self->offset = offset;
}


//  --------------------------------------------------------------------------
//  Get/set the checksum field

uint64_t
joex_proto_checksum (joex_proto_t *self)
{
    assert (self);
    return self->checksum;
}

void
joex_proto_set_checksum (joex_proto_t *self, uint64_t checksum)
{
    assert (self);
    self->checksum = checksum;
}


//  --------------------------------------------------------------------------
//  Get/set the reason field

const char *
joex_proto_reason (joex_proto_t *self)
{
    assert (self);
    return self->reason;
}

void
joex_proto_set_reason (joex_proto_t *self, const char *value)
{
    assert (self);
    assert (value);
    if (value == self->reason)
        return;
    strncpy (self->reason, value, 255);
    self->reason [255] = 0;
=======
//  --------------------------------------------------------------------------
//  Receive a joex_proto from the socket. Returns 0 if OK, -1 if
//  the recv was interrupted, or -2 if the message is malformed.
//  Blocks if there is no message waiting.

int
joex_proto_recv (joex_proto_t *self, zsock_t *input)
{
    assert (input);
    int rc = 0;

    if (zsock_type (input) == ZMQ_ROUTER) {
        zframe_destroy (&self->routing_id);
        self->routing_id = zframe_recv (input);
        if (!self->routing_id || !zsock_rcvmore (input)) {
            zsys_warning ("joex_proto: no routing ID");
            rc = -1;            //  Interrupted
            goto malformed;
        }
    }
    zmq_msg_t frame;
    zmq_msg_init (&frame);
    int size = zmq_msg_recv (&frame, zsock_resolve (input), 0);
    if (size == -1) {
        zsys_warning ("joex_proto: interrupted");
        rc = -1;                //  Interrupted
        goto malformed;
    }
    //  Get and check protocol signature
    self->needle = (byte *) zmq_msg_data (&frame);
    self->ceiling = self->needle + zmq_msg_size (&frame);

    uint16_t signature;
    GET_NUMBER2 (signature);
    if (signature != (0xAAA0 | 0)) {
        zsys_warning ("joex_proto: invalid signature");
        rc = -2;                //  Malformed
        goto malformed;
    }
    //  Get message id and parse per message type
    GET_NUMBER1 (self->id);

    switch (self->id) {
        case JOEX_PROTO_HELLO:
            GET_STRING (self->name);
            {
                size_t hash_size;
                GET_NUMBER4 (hash_size);
                self->header = zhash_new ();
                zhash_autofree (self->header);
                while (hash_size--) {
                    char key [256];
                    char *value = NULL;
                    GET_STRING (key);
                    GET_LONGSTR (value);
                    zhash_insert (self->header, key, value);
                    free (value);
                }
            }
            break;

        case JOEX_PROTO_PING:
            break;

        case JOEX_PROTO_PONG:
            break;

        case JOEX_PROTO_OK:
            break;

        case JOEX_PROTO_CLOSE:
            break;

        case JOEX_PROTO_ERROR:
            GET_STRING (self->reason);
            GET_NUMBER8 (self->code);
            break;

        case JOEX_PROTO_CHUNK:
            {
                size_t chunk_size;
                GET_NUMBER4 (chunk_size);
                if (self->needle + chunk_size > (self->ceiling)) {
                    zsys_warning ("joex_proto: data is missing data");
                    rc = -2;    //  Malformed
                    goto malformed;
                }
                zchunk_destroy (&self->data);
                self->data = zchunk_new (self->needle, chunk_size);
                self->needle += chunk_size;
            }
            GET_NUMBER8 (self->offset);
            GET_NUMBER8 (self->chunksize);
            GET_NUMBER8 (self->chunkchecksum);
            break;

        case JOEX_PROTO_UPLOAD:
            GET_STRING (self->filename);
            GET_NUMBER8 (self->filesize);
            GET_NUMBER8 (self->filechecksum);
            break;

        case JOEX_PROTO_UPLOAD_FINISHED:
            break;

        default:
            zsys_warning ("joex_proto: bad message ID");
            rc = -2;            //  Malformed
            goto malformed;
    }
    //  Successful return
    zmq_msg_close (&frame);
    return rc;

    //  Error returns
    malformed:
        zmq_msg_close (&frame);
        return rc;              //  Invalid message
}


//  --------------------------------------------------------------------------
//  Send the joex_proto to the socket. Does not destroy it. Returns 0 if
//  OK, else -1.

int
joex_proto_send (joex_proto_t *self, zsock_t *output)
{
    assert (self);
    assert (output);

    if (zsock_type (output) == ZMQ_ROUTER)
        zframe_send (&self->routing_id, output, ZFRAME_MORE + ZFRAME_REUSE);

    size_t frame_size = 2 + 1;          //  Signature and message ID
    switch (self->id) {
        case JOEX_PROTO_HELLO:
            frame_size += 1 + strlen (self->name);
            frame_size += 4;            //  Size is 4 octets
            if (self->header) {
                self->header_bytes = 0;
                char *item = (char *) zhash_first (self->header);
                while (item) {
                    self->header_bytes += 1 + strlen (zhash_cursor (self->header));
                    self->header_bytes += 4 + strlen (item);
                    item = (char *) zhash_next (self->header);
                }
            }
            frame_size += self->header_bytes;
            break;
        case JOEX_PROTO_ERROR:
            frame_size += 1 + strlen (self->reason);
            frame_size += 8;            //  code
            break;
        case JOEX_PROTO_CHUNK:
            frame_size += 4;            //  Size is 4 octets
            if (self->data)
                frame_size += zchunk_size (self->data);
            frame_size += 8;            //  offset
            frame_size += 8;            //  chunksize
            frame_size += 8;            //  chunkchecksum
            break;
        case JOEX_PROTO_UPLOAD:
            frame_size += 1 + strlen (self->filename);
            frame_size += 8;            //  filesize
            frame_size += 8;            //  filechecksum
            break;
    }
    //  Now serialize message into the frame
    zmq_msg_t frame;
    zmq_msg_init_size (&frame, frame_size);
    self->needle = (byte *) zmq_msg_data (&frame);
    PUT_NUMBER2 (0xAAA0 | 0);
    PUT_NUMBER1 (self->id);
    size_t nbr_frames = 1;              //  Total number of frames to send

    switch (self->id) {
        case JOEX_PROTO_HELLO:
            PUT_STRING (self->name);
            if (self->header) {
                PUT_NUMBER4 (zhash_size (self->header));
                char *item = (char *) zhash_first (self->header);
                while (item) {
                    PUT_STRING (zhash_cursor (self->header));
                    PUT_LONGSTR (item);
                    item = (char *) zhash_next (self->header);
                }
            }
            else
                PUT_NUMBER4 (0);    //  Empty hash
            break;

        case JOEX_PROTO_ERROR:
            PUT_STRING (self->reason);
            PUT_NUMBER8 (self->code);
            break;

        case JOEX_PROTO_CHUNK:
            if (self->data) {
                PUT_NUMBER4 (zchunk_size (self->data));
                memcpy (self->needle,
                        zchunk_data (self->data),
                        zchunk_size (self->data));
                self->needle += zchunk_size (self->data);
            }
            else
                PUT_NUMBER4 (0);    //  Empty chunk
            PUT_NUMBER8 (self->offset);
            PUT_NUMBER8 (self->chunksize);
            PUT_NUMBER8 (self->chunkchecksum);
            break;

        case JOEX_PROTO_UPLOAD:
            PUT_STRING (self->filename);
            PUT_NUMBER8 (self->filesize);
            PUT_NUMBER8 (self->filechecksum);
            break;

    }
    //  Now send the data frame
    zmq_msg_send (&frame, zsock_resolve (output), --nbr_frames? ZMQ_SNDMORE: 0);

    return 0;
}


//  --------------------------------------------------------------------------
//  Print contents of message to stdout

void
joex_proto_print (joex_proto_t *self)
{
    assert (self);
    switch (self->id) {
        case JOEX_PROTO_HELLO:
            zsys_debug ("JOEX_PROTO_HELLO:");
            zsys_debug ("    name='%s'", self->name);
            zsys_debug ("    header=");
            if (self->header) {
                char *item = (char *) zhash_first (self->header);
                while (item) {
                    zsys_debug ("        %s=%s", zhash_cursor (self->header), item);
                    item = (char *) zhash_next (self->header);
                }
            }
            else
                zsys_debug ("(NULL)");
            break;

        case JOEX_PROTO_PING:
            zsys_debug ("JOEX_PROTO_PING:");
            break;

        case JOEX_PROTO_PONG:
            zsys_debug ("JOEX_PROTO_PONG:");
            break;

        case JOEX_PROTO_OK:
            zsys_debug ("JOEX_PROTO_OK:");
            break;

        case JOEX_PROTO_CLOSE:
            zsys_debug ("JOEX_PROTO_CLOSE:");
            break;

        case JOEX_PROTO_ERROR:
            zsys_debug ("JOEX_PROTO_ERROR:");
            zsys_debug ("    reason='%s'", self->reason);
            zsys_debug ("    code=%ld", (long) self->code);
            break;

        case JOEX_PROTO_CHUNK:
            zsys_debug ("JOEX_PROTO_CHUNK:");
            zsys_debug ("    data=[ ... ]");
            zsys_debug ("    offset=%ld", (long) self->offset);
            zsys_debug ("    chunksize=%ld", (long) self->chunksize);
            zsys_debug ("    chunkchecksum=%ld", (long) self->chunkchecksum);
            break;

        case JOEX_PROTO_UPLOAD:
            zsys_debug ("JOEX_PROTO_UPLOAD:");
            zsys_debug ("    filename='%s'", self->filename);
            zsys_debug ("    filesize=%ld", (long) self->filesize);
            zsys_debug ("    filechecksum=%ld", (long) self->filechecksum);
            break;

        case JOEX_PROTO_UPLOAD_FINISHED:
            zsys_debug ("JOEX_PROTO_UPLOAD_FINISHED:");
            break;

    }
}


//  --------------------------------------------------------------------------
//  Get/set the message routing_id

zframe_t *
joex_proto_routing_id (joex_proto_t *self)
{
    assert (self);
    return self->routing_id;
}

void
joex_proto_set_routing_id (joex_proto_t *self, zframe_t *routing_id)
{
    if (self->routing_id)
        zframe_destroy (&self->routing_id);
    self->routing_id = zframe_dup (routing_id);
}


//  --------------------------------------------------------------------------
//  Get/set the joex_proto id

int
joex_proto_id (joex_proto_t *self)
{
    assert (self);
    return self->id;
}

void
joex_proto_set_id (joex_proto_t *self, int id)
{
    self->id = id;
}

//  --------------------------------------------------------------------------
//  Return a printable command string

const char *
joex_proto_command (joex_proto_t *self)
{
    assert (self);
    switch (self->id) {
        case JOEX_PROTO_HELLO:
            return ("HELLO");
            break;
        case JOEX_PROTO_PING:
            return ("PING");
            break;
        case JOEX_PROTO_PONG:
            return ("PONG");
            break;
        case JOEX_PROTO_OK:
            return ("OK");
            break;
        case JOEX_PROTO_CLOSE:
            return ("CLOSE");
            break;
        case JOEX_PROTO_ERROR:
            return ("ERROR");
            break;
        case JOEX_PROTO_CHUNK:
            return ("CHUNK");
            break;
        case JOEX_PROTO_UPLOAD:
            return ("UPLOAD");
            break;
        case JOEX_PROTO_UPLOAD_FINISHED:
            return ("UPLOAD_FINISHED");
            break;
    }
    return "?";
}

//  --------------------------------------------------------------------------
//  Get/set the name field

const char *
joex_proto_name (joex_proto_t *self)
{
    assert (self);
    return self->name;
}

void
joex_proto_set_name (joex_proto_t *self, const char *value)
{
    assert (self);
    assert (value);
    if (value == self->name)
        return;
    strncpy (self->name, value, 255);
    self->name [255] = 0;
}


//  --------------------------------------------------------------------------
//  Get the header field without transferring ownership

zhash_t *
joex_proto_header (joex_proto_t *self)
{
    assert (self);
    return self->header;
}

//  Get the header field and transfer ownership to caller

zhash_t *
joex_proto_get_header (joex_proto_t *self)
{
    zhash_t *header = self->header;
    self->header = NULL;
    return header;
}

//  Set the header field, transferring ownership from caller

void
joex_proto_set_header (joex_proto_t *self, zhash_t **header_p)
{
    assert (self);
    assert (header_p);
    zhash_destroy (&self->header);
    self->header = *header_p;
    *header_p = NULL;
}


//  --------------------------------------------------------------------------
//  Get/set the reason field

const char *
joex_proto_reason (joex_proto_t *self)
{
    assert (self);
    return self->reason;
}

void
joex_proto_set_reason (joex_proto_t *self, const char *value)
{
    assert (self);
    assert (value);
    if (value == self->reason)
        return;
    strncpy (self->reason, value, 255);
    self->reason [255] = 0;
}


//  --------------------------------------------------------------------------
//  Get/set the code field

uint64_t
joex_proto_code (joex_proto_t *self)
{
    assert (self);
    return self->code;
}

void
joex_proto_set_code (joex_proto_t *self, uint64_t code)
{
    assert (self);
    self->code = code;
}


//  --------------------------------------------------------------------------
//  Get the data field without transferring ownership

zchunk_t *
joex_proto_data (joex_proto_t *self)
{
    assert (self);
    return self->data;
}

//  Get the data field and transfer ownership to caller

zchunk_t *
joex_proto_get_data (joex_proto_t *self)
{
    zchunk_t *data = self->data;
    self->data = NULL;
    return data;
}

//  Set the data field, transferring ownership from caller

void
joex_proto_set_data (joex_proto_t *self, zchunk_t **chunk_p)
{
    assert (self);
    assert (chunk_p);
    zchunk_destroy (&self->data);
    self->data = *chunk_p;
    *chunk_p = NULL;
}


//  --------------------------------------------------------------------------
//  Get/set the offset field

uint64_t
joex_proto_offset (joex_proto_t *self)
{
    assert (self);
    return self->offset;
}

void
joex_proto_set_offset (joex_proto_t *self, uint64_t offset)
{
    assert (self);
    self->offset = offset;
}


//  --------------------------------------------------------------------------
//  Get/set the chunksize field

uint64_t
joex_proto_chunksize (joex_proto_t *self)
{
    assert (self);
    return self->chunksize;
}

void
joex_proto_set_chunksize (joex_proto_t *self, uint64_t chunksize)
{
    assert (self);
    self->chunksize = chunksize;
}


//  --------------------------------------------------------------------------
//  Get/set the chunkchecksum field

uint64_t
joex_proto_chunkchecksum (joex_proto_t *self)
{
    assert (self);
    return self->chunkchecksum;
}

void
joex_proto_set_chunkchecksum (joex_proto_t *self, uint64_t chunkchecksum)
{
    assert (self);
    self->chunkchecksum = chunkchecksum;
}


//  --------------------------------------------------------------------------
//  Get/set the filename field

const char *
joex_proto_filename (joex_proto_t *self)
{
    assert (self);
    return self->filename;
}

void
joex_proto_set_filename (joex_proto_t *self, const char *value)
{
    assert (self);
    assert (value);
    if (value == self->filename)
        return;
    strncpy (self->filename, value, 255);
    self->filename [255] = 0;
}


//  --------------------------------------------------------------------------
//  Get/set the filesize field

uint64_t
joex_proto_filesize (joex_proto_t *self)
{
    assert (self);
    return self->filesize;
}

void
joex_proto_set_filesize (joex_proto_t *self, uint64_t filesize)
{
    assert (self);
    self->filesize = filesize;
}


//  --------------------------------------------------------------------------
//  Get/set the filechecksum field

uint64_t
joex_proto_filechecksum (joex_proto_t *self)
{
    assert (self);
    return self->filechecksum;
}

void
joex_proto_set_filechecksum (joex_proto_t *self, uint64_t filechecksum)
{
    assert (self);
    self->filechecksum = filechecksum;
>>>>>>> 71fbb8dc832938493e68c2b249e3233edca66aca
}



//  --------------------------------------------------------------------------
//  Selftest

void
joex_proto_test (bool verbose)
{
    printf (" * joex_proto: ");

    if (verbose)
        printf ("\n");

    //  @selftest
    //  Simple create/destroy test
    joex_proto_t *self = joex_proto_new ();
    assert (self);
    joex_proto_destroy (&self);
    //  Create pair of sockets we can send through
    //  We must bind before connect if we wish to remain compatible with ZeroMQ < v4
    zsock_t *output = zsock_new (ZMQ_DEALER);
    assert (output);
    int rc = zsock_bind (output, "inproc://selftest-joex_proto");
    assert (rc == 0);

    zsock_t *input = zsock_new (ZMQ_ROUTER);
    assert (input);
    rc = zsock_connect (input, "inproc://selftest-joex_proto");
    assert (rc == 0);


    //  Encode/send/decode and verify each message type
    int instance;
    self = joex_proto_new ();
    joex_proto_set_id (self, JOEX_PROTO_HELLO);

    joex_proto_set_name (self, "Life is short but Now lasts for ever");
    zhash_t *hello_header = zhash_new ();
    zhash_insert (hello_header, "Name", "Brutus");
    joex_proto_set_header (self, &hello_header);
    //  Send twice
    joex_proto_send (self, output);
    joex_proto_send (self, output);

    for (instance = 0; instance < 2; instance++) {
        joex_proto_recv (self, input);
        assert (joex_proto_routing_id (self));
        assert (streq (joex_proto_name (self), "Life is short but Now lasts for ever"));
        zhash_t *header = joex_proto_get_header (self);
<<<<<<< HEAD
        assert (zhash_size (header) == 2);
=======
        assert (zhash_size (header) == 1);
>>>>>>> 71fbb8dc832938493e68c2b249e3233edca66aca
        assert (streq ((char *) zhash_first (header), "Brutus"));
        assert (streq ((char *) zhash_cursor (header), "Name"));
        zhash_destroy (&header);
        if (instance == 1)
            zhash_destroy (&hello_header);
    }
    joex_proto_set_id (self, JOEX_PROTO_PING);

    //  Send twice
    joex_proto_send (self, output);
    joex_proto_send (self, output);

    for (instance = 0; instance < 2; instance++) {
        joex_proto_recv (self, input);
        assert (joex_proto_routing_id (self));
    }
    joex_proto_set_id (self, JOEX_PROTO_PONG);

    //  Send twice
    joex_proto_send (self, output);
    joex_proto_send (self, output);

    for (instance = 0; instance < 2; instance++) {
        joex_proto_recv (self, input);
        assert (joex_proto_routing_id (self));
    }
<<<<<<< HEAD
    joex_proto_set_id (self, JOEX_PROTO_UPLOAD);

    joex_proto_set_filename (self, "Life is short but Now lasts for ever");
=======
    joex_proto_set_id (self, JOEX_PROTO_OK);

>>>>>>> 71fbb8dc832938493e68c2b249e3233edca66aca
    //  Send twice
    joex_proto_send (self, output);
    joex_proto_send (self, output);

    for (instance = 0; instance < 2; instance++) {
        joex_proto_recv (self, input);
        assert (joex_proto_routing_id (self));
<<<<<<< HEAD
        assert (streq (joex_proto_filename (self), "Life is short but Now lasts for ever"));
    }
    joex_proto_set_id (self, JOEX_PROTO_CHUNK);

    zchunk_t *chunk_data = zchunk_new ("Captcha Diem", 12);
    joex_proto_set_data (self, &chunk_data);
    joex_proto_set_size (self, 123);
    joex_proto_set_offset (self, 123);
    joex_proto_set_checksum (self, 123);
=======
    }
    joex_proto_set_id (self, JOEX_PROTO_CLOSE);

>>>>>>> 71fbb8dc832938493e68c2b249e3233edca66aca
    //  Send twice
    joex_proto_send (self, output);
    joex_proto_send (self, output);

    for (instance = 0; instance < 2; instance++) {
        joex_proto_recv (self, input);
        assert (joex_proto_routing_id (self));
<<<<<<< HEAD
        assert (memcmp (zchunk_data (joex_proto_data (self)), "Captcha Diem", 12) == 0);
        if (instance == 1)
            zchunk_destroy (&chunk_data);
        assert (joex_proto_size (self) == 123);
        assert (joex_proto_offset (self) == 123);
        assert (joex_proto_checksum (self) == 123);
    }
    joex_proto_set_id (self, JOEX_PROTO_UPLOAD_FINISHED);

=======
    }
    joex_proto_set_id (self, JOEX_PROTO_ERROR);

    joex_proto_set_reason (self, "Life is short but Now lasts for ever");
    joex_proto_set_code (self, 123);
>>>>>>> 71fbb8dc832938493e68c2b249e3233edca66aca
    //  Send twice
    joex_proto_send (self, output);
    joex_proto_send (self, output);

    for (instance = 0; instance < 2; instance++) {
        joex_proto_recv (self, input);
        assert (joex_proto_routing_id (self));
<<<<<<< HEAD
    }
    joex_proto_set_id (self, JOEX_PROTO_CLOSE);

    joex_proto_set_filename (self, "Life is short but Now lasts for ever");
    joex_proto_set_size (self, 123);
=======
        assert (streq (joex_proto_reason (self), "Life is short but Now lasts for ever"));
        assert (joex_proto_code (self) == 123);
    }
    joex_proto_set_id (self, JOEX_PROTO_CHUNK);

    zchunk_t *chunk_data = zchunk_new ("Captcha Diem", 12);
    joex_proto_set_data (self, &chunk_data);
    joex_proto_set_offset (self, 123);
    joex_proto_set_chunksize (self, 123);
    joex_proto_set_chunkchecksum (self, 123);
>>>>>>> 71fbb8dc832938493e68c2b249e3233edca66aca
    //  Send twice
    joex_proto_send (self, output);
    joex_proto_send (self, output);

    for (instance = 0; instance < 2; instance++) {
        joex_proto_recv (self, input);
        assert (joex_proto_routing_id (self));
<<<<<<< HEAD
        assert (streq (joex_proto_filename (self), "Life is short but Now lasts for ever"));
        assert (joex_proto_size (self) == 123);
    }
    joex_proto_set_id (self, JOEX_PROTO_OK);

=======
        assert (memcmp (zchunk_data (joex_proto_data (self)), "Captcha Diem", 12) == 0);
        if (instance == 1)
            zchunk_destroy (&chunk_data);
        assert (joex_proto_offset (self) == 123);
        assert (joex_proto_chunksize (self) == 123);
        assert (joex_proto_chunkchecksum (self) == 123);
    }
    joex_proto_set_id (self, JOEX_PROTO_UPLOAD);

    joex_proto_set_filename (self, "Life is short but Now lasts for ever");
    joex_proto_set_filesize (self, 123);
    joex_proto_set_filechecksum (self, 123);
>>>>>>> 71fbb8dc832938493e68c2b249e3233edca66aca
    //  Send twice
    joex_proto_send (self, output);
    joex_proto_send (self, output);

    for (instance = 0; instance < 2; instance++) {
        joex_proto_recv (self, input);
        assert (joex_proto_routing_id (self));
<<<<<<< HEAD
    }
    joex_proto_set_id (self, JOEX_PROTO_ERROR);

    joex_proto_set_reason (self, "Life is short but Now lasts for ever");
=======
        assert (streq (joex_proto_filename (self), "Life is short but Now lasts for ever"));
        assert (joex_proto_filesize (self) == 123);
        assert (joex_proto_filechecksum (self) == 123);
    }
    joex_proto_set_id (self, JOEX_PROTO_UPLOAD_FINISHED);

>>>>>>> 71fbb8dc832938493e68c2b249e3233edca66aca
    //  Send twice
    joex_proto_send (self, output);
    joex_proto_send (self, output);

    for (instance = 0; instance < 2; instance++) {
        joex_proto_recv (self, input);
        assert (joex_proto_routing_id (self));
<<<<<<< HEAD
        assert (streq (joex_proto_reason (self), "Life is short but Now lasts for ever"));
=======
>>>>>>> 71fbb8dc832938493e68c2b249e3233edca66aca
    }

    joex_proto_destroy (&self);
    zsock_destroy (&input);
    zsock_destroy (&output);
    //  @end

    printf ("OK\n");
}
