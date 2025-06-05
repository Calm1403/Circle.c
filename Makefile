files = main.o circle.o board.o winfo.o

Circle: $(files)
	$(CC) $^ -o Circle

$(files): %.o: %.c
	$(CC) -c $< -o $@

clean:
	rm *.o Circle