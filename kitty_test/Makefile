CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = kitty_tester

all: $(TARGET)

$(TARGET): kitty_tester.o
	$(CC) kitty_tester.o -o $(TARGET)

kitty_encoder_body.inc: key_encoding.c extract_kitty.py
	python3 ./extract_kitty.py

kitty_tester.o: kitty_tester.c kitty_mocks.h kitty_encoder_body.inc
	$(CC) $(CFLAGS) -c kitty_tester.c -o kitty_tester.o

clean:
	rm -f $(TARGET) *.o kitty_encoder_body.inc