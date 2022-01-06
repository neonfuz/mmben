CFLAGS += `sdl2-config --cflags`
LDFLAGS += `sdl2-config --libs` -lSDL2_image

all: bin/mmben bin/parser bin/wadlist

bin/%: src/mains/%/*.c src/lib/*/*.c
	mkdir -p bin
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f bin/*

.PHONY: all clean
