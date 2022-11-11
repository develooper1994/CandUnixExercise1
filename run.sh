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

gcc -Wall -Wextra -Wpedantic -g3 -O0 -o myhead.o -c myhead.c
gcc -Wall -Wextra -Wpedantic -g3 -O0 -o myhead myhead.o myvector.o

./mycat -d 0 -n 10 mycat.c -x -v
./mycat -d 0 -n 10 mycat.c -v
./mycat -d 0 -n 10 mycat.c -x
./mycat -d 0 -n 10 mycat.c -o
./mycat -d 0 -n 10 mycat.c -t

./myhead -d 0 -c 10 myheadmyhead.c -x -v
./myhead -d 0 -c 10 myheadmyhead.c -v
./myhead -d 0 -c 10 myheadmyhead.c -x
./myhead -d 0 -c 10 myheadmyhead.c -o
./myhead -d 0 -c 10 myheadmyhead.c -t

./myhead -d 0 myhead.c -x -v
./myhead -d 0 myhead.c -v
./myhead -d 0 myhead.c -x
./myhead -d 0 myhead.c -o
./myhead -d 0 myhead.c -t

./myhead -n 10 myhead.c -x -v
./myhead -n 10 myhead.c -v
./myhead -n 10 myhead.c -x
./myhead -n 10 myhead.c -o
./myhead -n 10 myhead.c -t

./myhead -c 10 myhead.c -x -v
./myhead -c 10 myhead.c -v
./myhead -c 10 myhead.c -x
./myhead -c 10 myhead.c -o
./myhead -c 10 myhead.c -t

./myhead myhead.c -x -v
./myhead myhead.c -v
./myhead myhead.c -x
./myhead myhead.c -o
./myhead myhead.c -t

./myhead myhead.c

gcc -Wall -Wextra -Wpedantic -g3 -O0 -o mytail.o -c mytail.c
gcc -Wall -Wextra -Wpedantic -g3 -O0 -o mytail mytail.o mytail.o

./mytail -d 0 -n 10 mytail.c -x -v
./mytail -d 0 -n 10 mytail.c -v
./mytail -d 0 -n 10 mytail.c -x
./mytail -d 0 -n 10 mytail.c -o
./mytail -d 0 -n 10 mytail.c -t

./mytail -d 0 -c 10 mytail.c -x -v
./mytail -d 0 -c 10 mytail.c -v
./mytail -d 0 -c 10 mytail.c -x
./mytail -d 0 -c 10 mytail.c -o
./mytail -d 0 -c 10 mytail.c -t

./mytail -d 0 mytail.c -x -v
./mytail -d 0 mytail.c -v
./mytail -d 0 mytail.c -x
./mytail -d 0 mytail.c -o
./mytail -d 0 mytail.c -t

./mytail -n 10 mytail.c -x -v
./mytail -n 10 mytail.c -v
./mytail -n 10 mytail.c -x
./mytail -n 10 mytail.c -o
./mytail -n 10 mytail.c -t

./mytail -c 10 mytail.c -x -v
./mytail -c 10 mytail.c -v
./mytail -c 10 mytail.c -x
./mytail -c 10 mytail.c -o
./mytail -c 10 mytail.c -t

./mytail mytail.c -x -v
./mytail mytail.c -v
./mytail mytail.c -x
./mytail mytail.c -o
./mytail mytail.c -t

./mytail mytail.c
