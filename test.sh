#!/bin/bash

#---------------------------------------------------------------
# A script to automate tests of all implementations
#
# The results will be stored in /docs/tests directory
#---------------------------------------------------------------

OUTPUTDIR=docs/tests/

function display_help_message {
    echo ":: Usage:  $0 [implementation] [prefix size] [repetitions] [number of threads](not required for serial implementation)"
    echo
    echo -e "[implementation]:\tThe desired implementation (e.g. serial, modular_serial, parallel, modular_parallel)"
    echo -e "[prefix size]:\t\tDesired size of the collision. Collision is a prefix 'x' that is equal to a prefix 'y'"
    echo -e "[repetitions]:\t\tNumber of times that the test will be repeated"
    echo -e "[number of threads]:\tFor parallel implementations, must specify the number of threads to use"
}

# Check if the required arguments were passed
if [ "$#" -lt 3 ]; then
    display_help_message
    exit 1
fi

# Check if in parallel implementations, the number of threads was passed
if [ $1 == "modular_parallel" ] || [ $1 == "parallel" ]; then
    if [ "$#" -ne 4 ]; then
        display_help_message
        exit 1
    fi
fi

# Each file will have a different name, the current seconds since epoch
FILENAME="$1_$2_$(date +%s).txt"

echo "==> Starting test"

if [ ! -z $4 ]; then
    echo "TESTS WITH $4 THREADS" >> $OUTPUTDIR/$FILENAME
fi

# Repeat the tests how many times were passed
for i in $(seq 1 $3); do
    echo "==> Starting the $i repetition of the test"
    echo -e "\n\n\n Execution number $i\n" >> $OUTPUTDIR/$FILENAME
    { time ./build/$1.bin $2 $4 >> $OUTPUTDIR/$FILENAME; } 2>> $OUTPUTDIR/$FILENAME
done

echo "==> Test finished"
echo "==> Results in $OUTPUTDIR$FILENAME"
