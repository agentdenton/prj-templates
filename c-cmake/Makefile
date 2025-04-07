BUILD_DIR = build
CMAKE_OPTIONS = -G Ninja \
                -DCMAKE_BUILD_TYPE=Debug \

build: configure
	@cmake --build ${BUILD_DIR}

configure:
	@cmake -S . -B ${BUILD_DIR} ${CMAKE_OPTIONS}

clean:
	@ninja -C ${BUILD_DIR} clean

cleanall:
	rm -rf ${BUILD_DIR}

.PHONY: build configure clean cleanall
