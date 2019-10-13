CC=gcc
CFLAGS=-Wall -Wextra
TARGET=rpiloader

SRC=$(wildcard *.c)
INC=$(wildcard *.h)
OBJ=$(SRC:.c=.o)

$(TARGET): $(OBJ)
	@echo " Create\t\t" $@
	@$(CC) $(OBJ) -o $@ $(LDFLAGS)

%.o : %.c $(INC)
	@echo " Compile\t" $@
	@$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@echo " Clean"
	@-rm -f $(TARGET) *.o
