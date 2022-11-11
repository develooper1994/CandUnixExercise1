#!/usr/bin/env bash
gcc -Wall -Wextra -Wpedantic -g3 -O0 -o myvector.o -c myvector.c
gcc -Wall -Wextra -Wpedantic -g3 -O0 -o mycat.o -c mycat.c
gcc -Wall -Wextra -Wpedantic -g3 -O0 -o mycat mycat.o myvector.o

./mycat -d 0 -n 10 mycat.c -x -v
./mycat -d 0 -n 10 mycat.c -v
./mycat -d 0 -n 10 mycat.c -x
./mycat -d 0 -n 10 mycat.c -o
./mycat -d 0 -n 10 mycat.c -t

./mycat -d 0 -c 10 mycat.c -x -v
./mycat -d 0 -c 10 mycat.c -v
./mycat -d 0 -c 10 mycat.c -x
./mycat -d 0 -c 10 mycat.c -o
./mycat -d 0 -c 10 mycat.c -t

./mycat -d 0 mycat.c -x -v
./mycat -d 0 mycat.c -v
./mycat -d 0 mycat.c -x
./mycat -d 0 mycat.c -o
./mycat -d 0 mycat.c -t

./mycat -n 10 mycat.c -x -v
./mycat -n 10 mycat.c -v
./mycat -n 10 mycat.c -x
./mycat -n 10 mycat.c -o
./mycat -n 10 mycat.c -t

./mycat -c 10 mycat.c -x -v
./mycat -c 10 mycat.c -v
./mycat -c 10 mycat.c -x
./mycat -c 10 mycat.c -o
./mycat -c 10 mycat.c -t

./mycat mycat.c -x -v
./mycat mycat.c -v
./mycat mycat.c -x
./mycat mycat.c -o
./mycat mycat.c -t

./mycat mycat.c
