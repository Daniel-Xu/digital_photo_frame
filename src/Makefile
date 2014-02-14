obj=fb.o jpeg.o disp.o pic_link.o err.o mouse.o do.o main.o
CFLAGS=-c -g -Iinclude
LDFLAGS=-L../jpeg-8/.libs/ -ljpeg -lpthread
CC=gcc

all: $(obj)
	$(CC) $(obj) -o app $(LDFLAGS) 

disp.o: disp.c
	$(CC) disp.c $(CFLAGS)
fb.o: fb.c
	$(CC) fb.c $(CFLAGS)
jpeg.o: jpeg.c
	$(CC) jpeg.c -c -I../jpeg-8/ -Iinclude
pic_link.o: pic_link.c
	$(CC) pic_link.c $(CFLAGS)
err.o: err.c
	$(CC) err.c $(CFLAGS)
mouse.o: mouse.c
	$(CC) mouse.c $(CFLAGS)
do.o: do.c
	$(CC) do.c $(CFLAGS)
main.o: main.c
	$(CC) main.c $(CFLAGS)

clean:
	rm -f *.o
	rm -f app
	rm -f *~
.PHONY: clean
