CFLAGS += `sdl2-config --cflags`
LDFLAGS += `sdl2-config --libs` -lSDL2_image

main: src/*.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f main

.PHONY: clean
