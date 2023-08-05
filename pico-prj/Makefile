BUILD_DIR := src/build
BIN_PATH := $(BUILD_DIR)/app.elf

.PHONY: all setup build flash debug clean

all:
	@echo "Makefile for building and debugging rp2040 application"
	@echo "Available targets:"
	@echo "   setup   - Generate the build files"
	@echo "   build   - Compile the application"
	@echo "   flash   - Flash firmware onto the target board"
	@echo "   debug   - Start OpenOCD for GDB debugging"
	@echo "   clean   - Remove generated files"

setup:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake -DCMAKE_BUILD_TYPE=Debug ..

build:
	make -C $(BUILD_DIR)

flash: build
	openocd \
		-f interface/cmsis-dap.cfg \
		-f target/rp2040.cfg \
		-c "adapter speed 5000" \
		-c "program $(BIN_PATH) verify reset exit"

debug: build
	openocd \
		-f interface/cmsis-dap.cfg \
		-c "adapter speed 5000" \
		-f target/rp2040.cfg \
		-s tcl

clean:
	rm -rf $(BUILD_DIR)
