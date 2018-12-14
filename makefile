all: ctl.o writer.o
	gcc -o ctl ctl.c
	gcc -o writer writer.c

ctl.o:
	gcc -c ctl.c

writer.o:
	gcc -c writer.c

clean:
	rm *.o
