CC = g++
CFLAGS = -g -Wall
LDFLAGS = -L/usr/X11R6/lib -lm -lGL -lglut -lGLU  -lGLEW
TARGETS= projet_image

all: $(TARGETS)

$(TARGETS):
	$(CC) $(CFLAGS) $@.c  $(LDFLAGS)  -o $@



clean:
	rm -f $(TARGETS)
	rm *~
