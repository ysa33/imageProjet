CC = g++
CFLAGS = -g -Wall
LDFLAGS = -L/usr/X11R6/lib -lm -lGL -lglut -lGLU  -lGLEW
TARGETS= test3 opengl_exo1 opengl_exo2 opengl_exo3  opengl_exo4   opengl_exo5 opengl_exo6 

all: $(TARGETS)

$(TARGETS):
	$(CC) $(CFLAGS) $@.c  $(LDFLAGS)  -o $@

test3:
	$(CC) $(CFLAGS) $@.c  $(LDFLAGS)  -o $@


clean:
	rm -f $(TARGETS)
