CC = g++
TARGET = t2m 
#LIBS = -L/usr/local/lib -lcryptopp
CFLAGS = -I/usr/local/include -Wall -Wextra -std=c++14
DBG = -g

.PHONY: default all clean

default: $(TARGET)

Debug: $(TARGET)

Release: $(TARGET)

all: default

SOURCES = $(wildcard *.cxx) $(wildcard */*.cxx)
HEADERS = $(wildcard *.hh) $(wildcard */*.hh)
OBJECTS = $(SOURCES:.cxx=.o)

%.o: %.cxx $(HEADERS)
	$(CC) $(CFLAGS) $(DBG) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

clean:
	rm -rf $(OBJECTS) $(TARGET)
