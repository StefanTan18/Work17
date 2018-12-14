all: ctl.o writer.o
	gcc ctl.c writer.c

clean:
	rm *.o
