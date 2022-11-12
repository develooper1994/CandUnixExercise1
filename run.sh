#!/usr/bin/env bash
gcc -Wall -Wextra -Wpedantic -g3 -O0 -o myvector.o -c myvector.c
gcc -Wall -Wextra -Wpedantic -g3 -O0 -o mycat.o -c mycat.c
gcc -Wall -Wextra -Wpedantic -g3 -O0 -o mycat mycat.o myvector.o

./mycat -r -n 10 mycat.c -x -v
./mycat -r -n 10 mycat.c -v
./mycat -r -n 10 mycat.c -x
./mycat -r -n 10 mycat.c -o
./mycat -r -n 10 mycat.c -t

./mycat -r -c 10 mycat.c -x -v
./mycat -r -c 10 mycat.c -v
./mycat -r -c 10 mycat.c -x
./mycat -r -c 10 mycat.c -o
./mycat -r -c 10 mycat.c -t

./mycat -r mycat.c -x -v
./mycat -r mycat.c -v
./mycat -r mycat.c -x
./mycat -r mycat.c -o
./mycat -r mycat.c -t

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

./myhead -r -n 10 myhead.c -x -v
./myhead -r -n 10 myhead.c -v
./myhead -r -n 10 myhead.c -x
./myhead -r -n 10 myhead.c -o
./myhead -r -n 10 myhead.c -t

./myhead -r -c 10 myhead.c -x -v
./myhead -r -c 10 myhead.c -v
./myhead -r -c 10 myhead.c -x
./myhead -r -c 10 myhead.c -o
./myhead -r -c 10 myhead.c -t

./myhead -r myhead.c -x -v
./myhead -r myhead.c -v
./myhead -r myhead.c -x
./myhead -r myhead.c -o
./myhead -r myhead.c -t

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

./mytail -r -n 10 mytail.c -x -v
./mytail -r -n 10 mytail.c -v
./mytail -r -n 10 mytail.c -x
./mytail -r -n 10 mytail.c -o
./mytail -r -n 10 mytail.c -t

./mytail -r -c 10 mytail.c -x -v
./mytail -r -c 10 mytail.c -v
./mytail -r -c 10 mytail.c -x
./mytail -r -c 10 mytail.c -o
./mytail -r -c 10 mytail.c -t

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
