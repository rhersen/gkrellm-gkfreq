all: gkfreq_cpu0.so gkfreq_cpu1.so gkfreq_cpu2.so gkfreq_cpu3.so gkfreq_cpu4.so gkfreq_cpu5.so gkfreq_cpu6.so gkfreq_cpu7.so

gkfreq_cpu0.o: gkfreq_cpu.c
	gcc -fPIC -O2 -Wall `pkg-config gtk+-2.0 --cflags` -DCPU=\"cpu0\" -o gkfreq_cpu0.o -c gkfreq_cpu.c

gkfreq_cpu0.so: gkfreq_cpu0.o
	gcc -shared -o gkfreq_cpu0.so gkfreq_cpu0.o

gkfreq_cpu1.o: gkfreq_cpu.c
	gcc -fPIC -O2 -Wall `pkg-config gtk+-2.0 --cflags` -DCPU=\"cpu1\" -o gkfreq_cpu1.o -c gkfreq_cpu.c

gkfreq_cpu1.so: gkfreq_cpu1.o
	gcc -shared -o gkfreq_cpu1.so gkfreq_cpu1.o

gkfreq_cpu2.o: gkfreq_cpu.c
	gcc -fPIC -O2 -Wall `pkg-config gtk+-2.0 --cflags` -DCPU=\"cpu2\" -o gkfreq_cpu2.o -c gkfreq_cpu.c

gkfreq_cpu2.so: gkfreq_cpu2.o
	gcc -shared -o gkfreq_cpu2.so gkfreq_cpu2.o

gkfreq_cpu3.o: gkfreq_cpu.c
	gcc -fPIC -O2 -Wall `pkg-config gtk+-2.0 --cflags` -DCPU=\"cpu3\" -o gkfreq_cpu3.o -c gkfreq_cpu.c

gkfreq_cpu3.so: gkfreq_cpu3.o
	gcc -shared -o gkfreq_cpu3.so gkfreq_cpu3.o

gkfreq_cpu4.o: gkfreq_cpu.c
	gcc -fPIC -O2 -Wall `pkg-config gtk+-2.0 --cflags` -DCPU=\"cpu4\" -o gkfreq_cpu4.o -c gkfreq_cpu.c

gkfreq_cpu4.so: gkfreq_cpu4.o
	gcc -shared -o gkfreq_cpu4.so gkfreq_cpu4.o

gkfreq_cpu5.o: gkfreq_cpu.c
	gcc -fPIC -O2 -Wall `pkg-config gtk+-2.0 --cflags` -DCPU=\"cpu5\" -o gkfreq_cpu5.o -c gkfreq_cpu.c

gkfreq_cpu5.so: gkfreq_cpu5.o
	gcc -shared -o gkfreq_cpu5.so gkfreq_cpu5.o

gkfreq_cpu6.o: gkfreq_cpu.c
	gcc -fPIC -O2 -Wall `pkg-config gtk+-2.0 --cflags` -DCPU=\"cpu6\" -o gkfreq_cpu6.o -c gkfreq_cpu.c

gkfreq_cpu6.so: gkfreq_cpu6.o
	gcc -shared -o gkfreq_cpu6.so gkfreq_cpu6.o

gkfreq_cpu7.o: gkfreq_cpu.c
	gcc -fPIC -O2 -Wall `pkg-config gtk+-2.0 --cflags` -DCPU=\"cpu7\" -o gkfreq_cpu7.o -c gkfreq_cpu.c

gkfreq_cpu7.so: gkfreq_cpu7.o
	gcc -shared -o gkfreq_cpu7.so gkfreq_cpu7.o

clean:
	rm -rf *.o *.so

install:
	cp gkfreq*.so /usr/lib/gkrellm2/plugins/

install-local:
	cp gkfreq*.so /usr/local/lib/gkrellm2/plugins/

install-home:
	cp gkfreq*.so ~/.gkrellm2/plugins
