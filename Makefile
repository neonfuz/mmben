CFLAGS += `sdl2-config --cflags`
LDFLAGS += `sdl2-config --libs` -lSDL2_image

all: bin/mmben bin/parser

bin/mmben: src/mains/mmben.c src/*.c
	mkdir -p bin
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

bin/parser: src/mains/parser.c src/*.c src/lib/*/*.c
	mkdir -p bin
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f bin/*

.PHONY: all clean
