
CC = gcc
CFLAGS = -Wall -W -O2

PREFIX = /usr/local

prime-indicator: 
	$(CC) prime-indicator.c -o prime-indicator $(CFLAGS) `pkg-config --cflags --libs gtk+-2.0 appindicator-0.1`

clean:
	rm -f *.o
