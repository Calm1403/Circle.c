
CFLAGS = -Wall -std=c99
FILES = main.o circle.o board.o winfo.o

Circle: $(FILES)
	$(CC) $(CFLAGS) $^ -o Circle

$(FILES): %.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm *.o Circle