all: powergridsim

CXXFLAGS := $(shell sdl2-config --cflags) $(shell pkg-config imgui --cflags) -I/usr/include/imgui/backends/
LDFLAGS := $(shell sdl2-config --libs) $(shell pkg-config imgui --libs) -lGL

SDL_BACKEND := imgui_impl_sdlrenderer.cpp

powergridsim: main.cpp
	g++ $(CXXFLAGS) -o powergridsim $(SDL_BACKEND) main.cpp $(LDFLAGS)

.PHONY: clean

clean:
	rm powergridsim

