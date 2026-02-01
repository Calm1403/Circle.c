
CFLAGS = -Wall
FILES = main.o circle.o board.o winfo.o

# Target:  dependencies ...
#          commands
#          ...
#
# $(FILES): %.o: %.c is likely a better
# way of going about getting the compilation
# units. % identifies a pattern with
# respect to a target; we get C files and
# create object files by the specified names in
# this case.
#

Circle: $(FILES)
	gcc $(CFLAGS) $^ -o Circle -lm

$(FILES): %.o: %.c
	gcc $(CFLAGS) -c $< -o $@

clean:
	rm *.o Circle
