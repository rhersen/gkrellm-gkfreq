all: gkfreq_cpu0.so gkfreq_cpu1.so gkfreq_cpu2.so gkfreq_cpu3.so gkfreq_cpu4.so gkfreq_cpu5.so gkfreq_cpu6.so gkfreq_cpu7.so

gkfreq_cpu0.o: gkfreq_cpu0.c
	gcc -fPIC -O2 -Wall `pkg-config gtk+-2.0 --cflags` -c gkfreq_cpu0.c

gkfreq_cpu0.so: gkfreq_cpu0.o
	gcc -shared -Wall -o gkfreq_cpu0.so gkfreq_cpu0.o

gkfreq_cpu1.o: gkfreq_cpu1.c
	gcc -fPIC -O2 -Wall `pkg-config gtk+-2.0 --cflags` -c gkfreq_cpu1.c

gkfreq_cpu1.so: gkfreq_cpu1.o
	gcc -shared -Wall -o gkfreq_cpu1.so gkfreq_cpu1.o

gkfreq_cpu2.o: gkfreq_cpu2.c
	gcc -fPIC -O2 -Wall `pkg-config gtk+-2.0 --cflags` -c gkfreq_cpu2.c

gkfreq_cpu2.so: gkfreq_cpu2.o
	gcc -shared -Wall -o gkfreq_cpu2.so gkfreq_cpu2.o

gkfreq_cpu3.o: gkfreq_cpu3.c
	gcc -fPIC -O2 -Wall `pkg-config gtk+-2.0 --cflags` -c gkfreq_cpu3.c

gkfreq_cpu3.so: gkfreq_cpu3.o
	gcc -shared -Wall -o gkfreq_cpu3.so gkfreq_cpu3.o

gkfreq_cpu4.o: gkfreq_cpu4.c
	gcc -fPIC -O2 -Wall `pkg-config gtk+-2.0 --cflags` -c gkfreq_cpu4.c

gkfreq_cpu4.so: gkfreq_cpu4.o
	gcc -shared -Wall -o gkfreq_cpu4.so gkfreq_cpu4.o

gkfreq_cpu5.o: gkfreq_cpu5.c
	gcc -fPIC -O2 -Wall `pkg-config gtk+-2.0 --cflags` -c gkfreq_cpu5.c

gkfreq_cpu5.so: gkfreq_cpu5.o
	gcc -shared -Wall -o gkfreq_cpu5.so gkfreq_cpu5.o

gkfreq_cpu6.o: gkfreq_cpu6.c
	gcc -fPIC -O2 -Wall `pkg-config gtk+-2.0 --cflags` -c gkfreq_cpu6.c

gkfreq_cpu6.so: gkfreq_cpu6.o
	gcc -shared -Wall -o gkfreq_cpu6.so gkfreq_cpu6.o

gkfreq_cpu7.o: gkfreq_cpu7.c
	gcc -fPIC -O2 -Wall `pkg-config gtk+-2.0 --cflags` -c gkfreq_cpu7.c

gkfreq_cpu7.so: gkfreq_cpu7.o
	gcc -shared -Wall -o gkfreq_cpu7.so gkfreq_cpu7.o

clean:
	rm -rf *.o *.so

install:
	cp gkfreq*.so /usr/lib/gkrellm2/plugins/

install-local:
	cp gkfreq*.so /usr/local/lib/gkrellm2/plugins/

install-home:
	cp gkfreq*.so ~/.gkrellm2/plugins
