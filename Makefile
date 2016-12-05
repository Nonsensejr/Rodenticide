IDIR=/opt/X11/include/
LDIR=/opt/X11/lib/
XDODIR=xdotool/
XDOLIB=xdo
LIBS=X11
CFLAGS=-I$(IDIR) -L$(LDIR) -L$(XDODIR) -l$(LIBS) -l$(XDOLIB) 
CC=gcc
OBJ=rdtc.o

xdotool/%.o: %.c
		$(CC) -c -o $@ $< $(CFLAGS)

rdtc: $(OBJ)
		gcc -o $@ $^ $(CFLAGS)
