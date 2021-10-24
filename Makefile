VPATH=${SRC_PATH}:./src
CC=gcc
ODIR=obj
_OBJ = main.o utils.o ui.o sender.o listener.o aes.o commands.o flags.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c
	@mkdir -p $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) -I/usr/local/opt/openssl@1.1/include

simple-chat: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) -lcurses -lpthread -lcrypto -L/usr/local/opt/openssl@1.1/lib

.PHONY: install
PREFIX = /usr/local
install: simple-chat
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp $< $(DESTDIR)$(PREFIX)/bin/simple-chat

clean:
	rm -f $(ODIR)/*.o
