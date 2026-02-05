# Space64 - N64 Game Makefile
# Uses libdragon + tiny3d

BUILD_DIR = build
SRC_DIR = src
ASSETS_DIR = assets

# Path to tiny3d (local copy in this repo)
T3D_INST = $(shell pwd)/tiny3d

# Include libdragon and tiny3d build rules
include $(N64_INST)/include/n64.mk
include $(T3D_INST)/t3d.mk

# Compiler flags
N64_CFLAGS += -std=gnu2x -Os -I$(SRC_DIR)

# Project name
PROJECT_NAME = space64

# Source files
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# Asset conversion - PNG to sprites
assets_png = $(wildcard $(ASSETS_DIR)/*.png)
assets_sprites = $(addprefix filesystem/,$(notdir $(assets_png:%.png=%.sprite)))

# Asset conversion - WAV to wav64
assets_wav = $(wildcard $(ASSETS_DIR)/*.wav)
assets_audio = $(addprefix filesystem/,$(notdir $(assets_wav:%.wav=%.wav64)))

# All converted assets
assets_conv = $(assets_sprites) $(assets_audio)

# Main target
all: $(PROJECT_NAME).z64

# Convert PNG to sprite
filesystem/%.sprite: $(ASSETS_DIR)/%.png
	@mkdir -p $(dir $@)
	@echo "    [SPRITE] $@"
	$(N64_MKSPRITE) $(MKSPRITE_FLAGS) -f CI4 -o filesystem "$<"

# Convert WAV to wav64
filesystem/%.wav64: $(ASSETS_DIR)/%.wav
	@mkdir -p $(dir $@)
	@echo "    [AUDIO] $@"
	$(N64_AUDIOCONV) --wav-compress 1 -o filesystem "$<"

# DFS filesystem depends on converted assets
$(BUILD_DIR)/$(PROJECT_NAME).dfs: $(assets_conv)

# ELF depends on object files
$(BUILD_DIR)/$(PROJECT_NAME).elf: $(OBJS)

# ROM settings - include DFS
$(PROJECT_NAME).z64: N64_ROM_TITLE="Space64"
$(PROJECT_NAME).z64: $(BUILD_DIR)/$(PROJECT_NAME).dfs

# Build object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) -c $(N64_CFLAGS) -o $@ $<

# Clean
clean:
	rm -rf $(BUILD_DIR) filesystem *.z64

# Rebuild
rebuild: clean all

-include $(wildcard $(BUILD_DIR)/*.d)

.PHONY: all clean rebuild
