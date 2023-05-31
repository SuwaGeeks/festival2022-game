CC := g++
CFLAGS := -DDX_GCC_COMPILE -I"dxlib"
LDFLAGS := -Ldxlib
LDLIBS := -lDxLib -lDxUseCLib -lDxDrawFunc -ljpeg -lpng -lzlib -ltiff -ltheora_static -lvorbis_static -lvorbisfile_static -logg_static -lbulletdynamics -lbulletcollision -lbulletmath -lopusfile -lopus -lsilk_common -lcelt

SRC_DIR := src
OBJ_DIR := build

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

game.exe: $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS) $(LDLIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean_b:
	rm -f $(OBJ_DIR)/*.o game.exe

clean:
	del /Q $(OBJ_DIR)\*.o && del /Q game.exe