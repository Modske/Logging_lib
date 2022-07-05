CFLAGS:=-Wall -fPIC
CPPFLAGS:=
LDLFLAGS:=

PREFIX?=/usr

all:libshrd_log.so

libshrd_log.so: shrd_log.o
	$(CC) -shared -o $@ $^ -lsqlite3 -std=c99

shrd_log.o: shrd_log.c
	$(CC) -c $(CFLAGS) $^ -lsqlite3 -std=c99

install:
	install -m 755 libshrd_log.so $(PREFIX)/lib/libshrd_log.so
	ldconfig
	install -m 644 shrd_log.h $(PREFIX)/include/shrd_log.h

uninstall:
	$(RM) $(PREFIX)/lib/libshrd_log.so
	$(RM) $(PREFIX)/include/shrd_log.h

clean:
	$(RM) shrd_log.o
	$(RM) libshrd_log.so