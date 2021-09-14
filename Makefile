VPATH=${SRC_PATH}:./src
CC=gcc
ODIR=obj
_OBJ = main.o utils.o ui.o sender.o listener.o aes.o commands.o flags.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c
	@mkdir -p $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS)

sc: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) -lcurses -lpthread -lcrypto

clean:
	rm -f $(ODIR)/*.o
