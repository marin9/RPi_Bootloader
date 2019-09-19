CC=gcc
CFLAGS=-Wall -Wextra

SRC=main.c serial.c
TARGET=rpiloader


all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)

