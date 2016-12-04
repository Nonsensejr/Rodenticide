IDIR=/opt/X11/include/
CC=gcc
CFLAGS=-I$(IDIR)
LDIR =-L/opt/X11/lib/
OBJ = rdtc.o rdtc.o 
LIBS=-lX11
DEPS = rdtc.h

%.o: %.c $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS) $(LDIR) $(LIBS)

rdtc: $(OBJ)
		gcc -o $@ $^ $(CFLAGS) 

