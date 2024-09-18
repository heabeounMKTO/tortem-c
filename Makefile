INCLUDE_MATH=-lm -ffast-math
DEBUG=main_debug
RELEASE=main
SIMD:= -msse -msse2 -msse3 -mavx
USE_SCALAR:=0

build_dir:
	mkdir -p build

debug: build_dir
	gcc -DHB_VEC_SCALAR=${USE_SCALAR} -Werror -Wall -Wextra src/*.c -g -O0 -o build/${DEBUG} ${INCLUDE_MATH}
	gdb build/${DEBUG}

run: build_dir
	gcc -DHB_VEC_SCALAR=${USE_SCALAR} -ffast-math -lm -march=native -Werror -Wall -Wextra src/*.c -o build/${DEBUG} ${INCLUDE_MATH} 
	./build/${DEBUG} 

clean:
	rm -rf build

img: build_dir
	gcc -DHB_VEC_SCALAR=${USE_SCALAR} -march=native src/*.c -o build/${RELEASE} ${INCLUDE_MATH} -s 
	./build/${RELEASE} > ayy.ppm 

release: build_dir
	gcc src/*.c -o build/${RELEASE} ${INCLUDE_MATH} -s 
