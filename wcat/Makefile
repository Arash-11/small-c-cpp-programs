PROGNAME=wcat
CC=gcc
CFLAGS=-Wall -Werror
# FILE=
# exec: $(PROGNAME)
# 	@ ./$(PROGNAME) $(FILE)

$(PROGNAME): $(PROGNAME).c
	@ $(CC) $(CFLAGS) -o bin/$(PROGNAME) $(PROGNAME).c

clean:
	rm $(PROGNAME)
