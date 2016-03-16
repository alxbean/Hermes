/*************************************************************************
    > File Name: example.c
    > Author: shuaixiang
    > Mail: shuaixiang@yuewen.com
    > Created Time: Mon 22 Feb 2016 06:29:16 AM UTC
 ************************************************************************/

#include <msgpack.h>
#include <stdio.h>

void print(char const* buf, unsigned int len)
{
    size_t i = 0;
    for(; i < len ; ++i)
        printf("%02x ", 0xff & buf[i]);
    printf("\n");
}

int main(void) {

        /* creates buffer and serializer instance. */
        msgpack_sbuffer* buffer = msgpack_sbuffer_new();
        msgpack_packer* pk = msgpack_packer_new(buffer, msgpack_sbuffer_write);

        /* serializes ["Hello", "MessagePack"]. */
        msgpack_pack_array(pk, 2);
        msgpack_pack_bin(pk, 5);
        msgpack_pack_bin_body(pk, "Hello", 5);
        msgpack_pack_bin(pk, 11);
        msgpack_pack_bin_body(pk, "MessagePack", 11);
        msgpack_pack_float(pk, 1);
        print(buffer->data, buffer->size);
        

        /* deserializes it. */
        msgpack_unpacked msg;
        msgpack_unpacked_init(&msg);
        bool success = msgpack_unpack_next(&msg, buffer->data, buffer->size, NULL);

        /* prints the deserialized object. */
        msgpack_object obj = msg.data;
        msgpack_object_print(stdout, obj);  /*=> ["Hello", "MessagePack"] */

        /* cleaning */
        msgpack_sbuffer_free(buffer);
        msgpack_packer_free(pk);
}
