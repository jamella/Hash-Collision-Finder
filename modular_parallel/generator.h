#ifndef GENERATOR_H
#define GENERATOR_H

#define true 1
#define false 0

/* Uses timespec */
_Bool seed_generator();

/* Return a call to random() */
long int generate_number();

#endif
