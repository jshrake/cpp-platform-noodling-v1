UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
	RUN_CMD := ./build/GRIM_NAME build/libGRIM_NAME_lib.dylib
else
	RUN_CMD := ./build/GRIM_NAME build/libGRIM_NAME_lib.so
endif

default: build

run: build
	$(RUN_CMD)

build:
	cmake -H. -Bbuild -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_EXPORT_COMPILE_COMMANDS=1
	cmake --build build

clean:
	-rm -rf build

tags:
	rc -J ./build
	ctags -R .

.PHONY: build clean default run tags
