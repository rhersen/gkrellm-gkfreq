gkfreq_cpus.so: gkfreq_cpus.o formatter.o
	gcc -shared -o gkfreq_cpus.so gkfreq_cpus.o formatter.o

formatter.o: formatter.c
	gcc -fPIC -O2 -Wall -std=gnu1x `pkg-config gtk+-2.0 --cflags` -o formatter.o -c formatter.c

gkfreq_cpus.o: gkfreq_cpu.c
	gcc -fPIC -O2 -Wall -std=gnu1x `pkg-config gtk+-2.0 --cflags` -o gkfreq_cpus.o -c gkfreq_cpu.c

clean:
	rm -rf *.o *.so a.out

install:
	cp gkfreq*.so /usr/lib/gkrellm2/plugins/

install-local:
	cp gkfreq*.so /usr/local/lib/gkrellm2/plugins/

install-home:
	cp gkfreq*.so ~/.gkrellm2/plugins
