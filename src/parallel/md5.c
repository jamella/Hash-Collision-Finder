#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<openssl/md5.h>

#include"md5.h"

unsigned char* raw_md5(const char *data, int data_length)
{
    MD5_CTX context;
    unsigned char *digest = (char*)malloc(MD5_DIGEST_SIZE);

    MD5_Init(&context);

    while (data_length > 0) {
        if (data_length > MD5_BLOCK_SIZE) {
            MD5_Update(&context, data, MD5_BLOCK_SIZE);
        } else {
            MD5_Update(&context, data, data_length);
        }

        data_length -= MD5_BLOCK_SIZE;
        data += MD5_BLOCK_SIZE;
    }

    MD5_Final(digest, &context);

    return digest;
}

char* md5(const char *data, int data_length)
{
    char *out = (char*)malloc(MD5_HEX_DIGEST_SIZE + 1);
    unsigned char *digest = raw_md5(data, data_length);

    for (int n = 0; n < MD5_DIGEST_SIZE; ++n) {
        snprintf(&(out[n*2]), 16*2, "%02x", (unsigned int)digest[n]);
    }

    free(digest);

    return out;
}

char* get_hex_from_raw_digest(unsigned char *digest)
{
    char *out = (char*)malloc(MD5_HEX_DIGEST_SIZE + 1);
    for (int n = 0; n < MD5_DIGEST_SIZE; ++n) {
        snprintf(&(out[n*2]), 16*2, "%02x", (unsigned int)digest[n]);
    }

    return out;
}
