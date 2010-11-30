# vim:noet

CC=g++
CFLAGS=-Wall -c -I$(INCLUDEDIR)
LDFLAGS=-L/usr/lib -lglut -lglui -lGLU -lGL
INCLUDEDIR=include/
SOURCEDIR=.
OBJECTDIR=.
SOURCES:=$(wildcard $(SOURCEDIR)/*.cpp)
OBJECTS=$(SOURCES:$(SOURCEDIR)%.cpp=$(OBJECTDIR)%.o)
SHELL = /bin/sh

.DEFAULT_GOAL := P5

P5: $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

$(OBJECTDIR)/%.o: $(SOURCEDIR)/%.cpp
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: clean
clean:
	rm -rf $(OBJECTS) P4
