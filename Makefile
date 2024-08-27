INCLUDE_MATH=-lm

build_dir:
	mkdir -p build

debug: build_dir
	clang src/*.c -g -O0 -o build/main_debug ${INCLUDE_MATH}

run: build_dir
	clang src/*.c -o build/main ${INCLUDE_MATH} 
	./build/main 

img: build_dir
	clang src/*.c -o build/main ${INCLUDE_MATH} 
	./build/main > ayy.ppm 

release: build_dir
	clang src/*.c -o build/main ${INCLUDE_MATH} 
