#!/bin/bash

#-----------------------------------------------------------------
# Abstraction of the automate test script, generalizing even more
#-----------------------------------------------------------------

function display_help_message {
    echo ":: Usage: $0 [prefix size] [repetitions] [number of threads] "
    echo
    echo -e "[prefix size]:\t\tHow many bytes must collide in the prefix to be considered a collision"
    echo -e "[repetitions]:\t\tNumber of repetitions for each test"
    echo -e "[number of threads]:\tHow many threads will be used for parallel implementations"
}

# Check if the required arguments were passed
if [ "$#" -lt 3 ]; then
    display_help_message
    exit 1
fi

echo "==> Starting tests"

echo "==> Starting serial implementations tests"
./test.sh serial $1 $2
./test.sh modular_serial $1 $2

echo "==> Starting parallel implementations tests"

for i in $(seq 2 $3); do
    ./test.sh parallel $1 $2 $i
    ./test.sh modular_parallel $1 $2 $i
done

echo "==> Finished all tests"
