PROJECT := powergridsim
BINARY := powergridsim
CXX := g++

all: $(BINARY)

CXXFLAGS := $(shell sdl2-config --cflags) -I./imgui -I./imgui/backends -g -pedantic -Wall
LDFLAGS := $(shell sdl2-config --libs) -lGL

IMGUI_SRC := imgui/imgui.cpp imgui/imgui_draw.cpp imgui/imgui_widgets.cpp imgui/imgui_tables.cpp imgui/imgui_demo.cpp imgui/backends/imgui_impl_sdl2.cpp imgui/backends/imgui_impl_opengl3.cpp
SRC := src/imgui_custom.cpp src/gui.cpp src/main.cpp

IMGUI_OBJ := $(patsubst %.cpp,%.o,$(IMGUI_SRC))
OBJ := $(patsubst %.cpp,%.o,$(SRC))

$(BINARY): $(IMGUI_OBJ) $(OBJ)
	g++ $(CXXFLAGS) -o $(BINARY) $(IMGUI_OBJ) $(OBJ) $(LDFLAGS)

%.o: %.c
	$(CXX) -c $(CXXFLAGS) $<

.PHONY: clean

clean:
	rm -f powergridsim *.o src/*.o imgui/*.o imgui/backends/*o

