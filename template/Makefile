UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
	RUN_CMD := ./build/GRIM_NAME build/libGRIM_NAME_lib.dylib
else
	RUN_CMD := ./build/GRIM_NAME build/libGRIM_NAME_lib.so
endif

default: build/GRIM_NAME

run: build/GRIM_NAME
	$(RUN_CMD)

build/GRIM_NAME: build/CMakeCache.txt src/grim_platform.cpp src/GRIM_NAME.cpp
	cmake --build build

build/CMakeCache.txt: CMakeLists.txt
	cmake -H. -Bbuild -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DGRIM_SANITIZERS="-fsanitize=address"

clean:
	-rm -rf build

tags:
	rc -J ./build
	ctags -R .

.PHONY: clean run tags
