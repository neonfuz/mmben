main: *.c
	$(CC) $(CFLAGS) -o $@ $^ `sdl2-config --cflags --libs`

clean:
	rm -f main

.PHONY: clean
