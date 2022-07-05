CFLAGS:=-Wall 
CPPFLAGS:=
LDLFLAGS:=
PREFIX?=/usr

all:daemon1 display

daemon1:daemon1.o
	$(CC) $(CFLAGS) $^ -o $@ -lshrd_log

display: display.o
	$(CC) $(CFLAGS) $^ -o $@ -lshrd_log

%.o:%.c
	$(CC) -c $(CFLAGS) $^ -o $@ -lshrd_log

install:
	install -m 755 daemon1 $(PREFIX)/bin
	install -m 755 display $(PREFIX)/bin

uninstall:
	$(RM) $(PREFIX)/bin/daemon1
	$(RM) $(PREFIX)/bin/display

clean:
	$(RM) -f daemon1 daemon1.o
	$(RM) -f display display.o