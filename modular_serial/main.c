/* 
 * Search for pseudo collision in md5 hash funcion using a birthday attack approach
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#include"md5.h"
#include"generator.h"

#define MAX 50000               /* How many hashes will be generated */
#define DESIRED_COLLISION 15    /* How many bytes must be equal to be considered a collision */
#define BUFFER_SIZE 22          /* The size for create a string representation of a number */

#define WARNS_AFTER 10000       /* Display a warning of status after X repetitions */

void parse_arguments(int argc, char *argv[]);       /* Function to parse arguments received from stdin */
void display_help_message();                        /* Display the parameters order and how to use properly */

int main(int argc, char *argv[])
{
    unsigned long long int values[MAX];
    char *hashes[MAX];
    char buffer[BUFFER_SIZE];
    unsigned char byte_collisions;  /* Counts equal bytes in two hashes */

    seed_generator();
    printf("==> Generating %lu random messages...\n", MAX);

    clock_t start = clock();

    for (int i = 0; i < MAX; i++){
        values[i] = generate_number(); 
        values[i] = (values[i] << 32) | generate_number();
    }

    printf("==> Hashing all %lu messages...\n", MAX);

    for (int i = 0; i < MAX; i++){
        snprintf(buffer, BUFFER_SIZE, "%ld", values[i]); /* Representing the number as string for hash process */
        hashes[i] = md5(buffer, strlen(buffer));         /* Get the hexadecimal md5 hash */
    }

    printf("==> Searching for collisions in hashes\n");

    for (int i = 0; i < MAX; i++){
        if (i % WARNS_AFTER == 0){
            printf("Already checked %d hashes\n", i); 
        }
    
        for (int j = i + 1; j < MAX; j++){
            byte_collisions = 0;

            /* 
             * It's possible to have same numbers being generated by random function.
             * Of course, they are equal, not collision.
            */
            if (values[i] == values[j]){
                continue; 
            }

            /* Check how many bytes are equal */
            for (int k = 0; k < MD5_HEX_DIGEST_SIZE; k++){
                /*
                 * Checks whether it's possible to satisfy the desired collision value with the remaining bytes to test.
                 * Remaining tries + collisions found must be equal or greater than desired collision value.
                 * This prevents to continue test hashes that doesn't satisfy the desired collision value, improving performance.
                */
                if(((MD5_HEX_DIGEST_SIZE - 1) - k) + byte_collisions < DESIRED_COLLISION){
                    break; 
                }

                if ((hashes[i][k] == hashes[j][k])){
                    byte_collisions++;
                } 
            }

            if(byte_collisions >= DESIRED_COLLISION){
                printf("==> %d bytes collision found!!!! Iteration: %d\n", byte_collisions, i);
                printf("md5('%ld')\t==\t%s\nmd5('%ld')\t==\t%s\n", values[i], hashes[i], values[j], hashes[j]);
            }
        }
    }

    printf("Finished search for collision\n");
    printf("Time elapsed: %f seconds\n", ((double)clock() - start) / CLOCKS_PER_SEC);
    printf("Time elapsed: %f minutes\n", (((double)clock() - start) / CLOCKS_PER_SEC) / 60);
    printf("Time elapsed: %f hours\n", ((((double)clock() - start) / CLOCKS_PER_SEC) / 60) / 60);

    return 0;
}

void parse_arguments(int argc, char *argv[])
{
    if (argc < 2){
        display_help_message(); 
    }
}

void display_help_message(char *program_name)
{
    printf("Usage: %s [desired byte collision]\n");
    printf("[desired byte collision] = How many bytes must be equal for the hash be considered a collision\n");
}
