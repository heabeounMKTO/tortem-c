INCLUDE_MATH=-lm
DEBUG=main_debug
RELEASE=main

build_dir:
	mkdir -p build

debug: build_dir
	gcc -Werror -Wall -Wextra src/*.c -g -O0 -o build/${DEBUG} ${INCLUDE_MATH}
	gdb build/${DEBUG}
run: build_dir
	gcc -Werror -Wall -Wextra src/*.c -o build/${DEBUG} ${INCLUDE_MATH} 
	./build/${DEBUG} 
clean:
	rm -rf build

img: build_dir
	gcc  src/*.c -o build/${RELEASE} ${INCLUDE_MATH} -s 
	./build/${RELEASE} > ayy.ppm 

release: build_dir
	gcc src/*.c -o build/${RELEASE} ${INCLUDE_MATH} -s 
