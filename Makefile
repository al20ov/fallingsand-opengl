SRC					=				main.cpp																		\
										src/Map.cpp																	\
										src/Shader.cpp

OUT					=				program

PREFLAGS		=				$(shell pkg-config --cflags glfw3)					\
										$(shell pkg-config --cflags glew)

POSTFLAGS		=				$(shell pkg-config --static --libs glfw3)		\
										$(shell pkg-config --static --libs glew)

INCLUDE			=				-Isrc



all:
	g++ $(INCLUDE) $(PREFLAGS) $(SRC) $(POSTFLAGS) -o $(OUT)

.PHONY: all
