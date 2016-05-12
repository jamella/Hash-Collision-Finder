# Hash-Collision-Finder
A parallel and distributed generic attack to find collision in hash functions

## Compiling
To compile all implementations:
```
make
```
Compiling specific implementations:
```
make serial
make parallel
make modular_serial
make modular_parallel
```
The builded implementations are stored in ```build/``` directory.

## Usage
For serial implementations, you only need to specify how many bytes must be equal:
```
$ ./serial [how many bytes equal to consider a collision]
$ ./serial 12   # If 12 bytes are equal in the hash, it will be considered a collision
$ ./modular_serial 16
```

For parallel implementations, you must pass also how many threads you want to create:
```
$ ./parallel 12 4             # 12 bytes equal and it will create 4 threads
$ ./modular_parallel 12 8     # 8 threads
```

## Testing
There is a test script to automate tests. First, give permissions to file:
```
$ chmod +x test.sh
```

The script takes 4 arguments:
- The name of the implementation to test
- How many bytes of partial collision (equal prefix)
- Number of repetitions of the test
- Number of threads (Required only for parallel implementations)

Examples:  
```$ ./test.sh serial 5 10```: This will run the ```serial``` implementation looking for a 5 bytes equal prefix 10 times.  
```$ ./test.sh modular_parallel 10 20 8```: This will run ```modular_parallel``` implementation looking for a 10 bytes equal prefix, 20 times and using 8 threads.  
