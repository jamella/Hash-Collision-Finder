/* 
 * Search for pseudo collision in md5 hash funcion using a birthday attack approach
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<omp.h>

#include"md5.h"
#include"generator.h"

#define BUFFER_SIZE 22          /* The size for create a string representation of a number */
#define WARNS_AFTER 10000       /* Display a warning of status after X repetitions */

#define THREADS 4

void parse_arguments(int argc, char *argv[], unsigned int *desired_collision);       /* Function to parse arguments received from stdin */
void display_help_message();                        /* Display the parameters order and how to use properly */

int main(int argc, char *argv[])
{
    unsigned long long int *values;
    unsigned char **hashes;
    char buffer[BUFFER_SIZE];
    unsigned int desired_collision = 0;

    parse_arguments(argc, argv, &desired_collision);
    const unsigned __int128 iterations = calculate_iterations(desired_collision);

    seed_generator();
    printf("==> Generating %lu random messages...\n", iterations);

    values = malloc(sizeof(unsigned long long int) * iterations);
    hashes = malloc(sizeof(unsigned char*) * iterations);

    clock_t start = clock();

    for (int i = 0; i < iterations; i++){
        /* Display how many hashes were already processed */
        if(i % WARNS_AFTER == 0){
            printf("==> Status: %d hashes processed\n", i); 
        }

        values[i] = generate_number(); 
        values[i] = (values[i] << 32) | generate_number();

        snprintf(buffer, BUFFER_SIZE, "%ld", values[i]); /* Representing the number as string for hash process */
        hashes[i] = raw_md5(buffer, strlen(buffer));         /* Get the hexadecimal md5 hash */

        # pragma omp parallel for num_threads(THREADS)
        for (int j = 0; j < i; j++){
            int byte_collisions = 0;

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
                 * Storing temporarily the bytes to compare 
                 * I was having issue using bitshift operations in matrix implementation
                 */
                unsigned char first_byte = 0, second_byte = 0;
                /*
                 * Checks whether it's possible to satisfy the desired collision value with the remaining bytes to test.
                 * Remaining tries + collisions found must be equal or greater than desired collision value.
                 * This prevents to continue test hashes that doesn't satisfy the desired collision value, improving performance.
                 */
                if(((MD5_HEX_DIGEST_SIZE - 1) - (k * 2)) + byte_collisions < desired_collision){
                    break; 
                }

                first_byte = hashes[i][k];
                second_byte = hashes[j][k];

                if (((first_byte >> 4) ^ (second_byte >> 4)) == 0){
                    byte_collisions++;
                } 

                if (((first_byte << 4) ^ (second_byte << 4)) == 0){
                    byte_collisions++;
                } 
            }

            if(byte_collisions >= desired_collision){
                printf("==> %d bytes collision found!!!! Iteration: %d\n", byte_collisions, i);
                printf("md5('%ld')\t==\t%s\nmd5('%ld')\t==\t%s\n", values[i], get_hex_from_raw_digest(hashes[i]), values[j], get_hex_from_raw_digest(hashes[j]));
            }

        }
    }
        
    printf("Finished search for collision\n");
    printf("Time elapsed: %f seconds\n", ((double)clock() - start) / CLOCKS_PER_SEC);
    printf("Time elapsed: %f minutes\n", (((double)clock() - start) / CLOCKS_PER_SEC) / 60);
    printf("Time elapsed: %f hours\n", ((((double)clock() - start) / CLOCKS_PER_SEC) / 60) / 60);

    return 0;
}

void parse_arguments(int argc, char *argv[], unsigned int *desired_collision)
{
    if (argc < 2){
        display_help_message(argv[0]); 
        exit(1);
    }

    *desired_collision = atoi(argv[1]);
}

void display_help_message(char *program_name)
{
    printf("Usage: %s [desired byte collision]\n", program_name);
    printf("[desired byte collision] = How many bytes must be equal for the hash be considered a collision\n");
}
