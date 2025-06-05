
CFLAGS = -Wall -std=c99
FILES = main.o circle.o board.o winfo.o

Circle: $(FILES)
	gcc $(CFLAGS) $^ -o Circle

$(FILES): %.o: %.c
	gcc $(CFLAGS) -c $< -o $@

clean:
	rm *.o Circle