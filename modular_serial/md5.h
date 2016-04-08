#ifndef MD5_H
#define MD5_H

/* MD5 operate on 512-bit blocks */
#define MD5_BLOCK_SIZE 512

/* MD5 generate 128-bit output (16 bytes) */
#define MD5_DIGEST_SIZE 16

/* Digest is represented with 32 bytes in hexadecimal */
#define MD5_HEX_DIGEST_SIZE 32

/* Computes the raw 128-bit hash */
unsigned char* raw_md5(const char *data, int data_length);

/* Computes the hexadecimal representation of the hash */
char* md5(const char *data, int data_length);

#endif
