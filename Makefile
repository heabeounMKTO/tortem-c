INCLUDE_MATH=-lm -ffast-math
DEBUG=main_debug
RELEASE=main
SIMD:= -msse -msse2 -msse3 -mavx
USE_SCALAR:=0
OUTPUT_NAME:=ayy.ppm


build_dir:
	mkdir -p build

animation_dir: 
	mkdir -p animation_output

debug: build_dir
	gcc -DHB_VEC_SCALAR -Werror -Wall -Wextra src/*.c -g -O0 -o build/${DEBUG} ${INCLUDE_MATH}
	gdb build/${DEBUG}

run: build_dir
	gcc -ffast-math -lm -march=native -Werror -Wall -Wextra src/*.c -o build/${DEBUG} ${INCLUDE_MATH} 
	./build/${DEBUG} 

run_sc: build_dir
	gcc -DDEBUG_PIXELS -ffast-math -lm -march=native src/*.c -o build/${DEBUG} -ljpeg -lpng ${INCLUDE_MATH} 
	./build/${DEBUG} 

debug_txt: debug_simd debug_scalar

debug_simd: build_dir
	gcc -march=native -Werror -Wall -Wextra src/*.c -o build/${DEBUG} ${INCLUDE_MATH} 
	./build/${DEBUG} > debug_simd.txt

debug_scalar: build_dir
	gcc -DHB_VEC_SCALAR=1 -Werror -Wall -Wextra src/*.c -o build/${DEBUG} ${INCLUDE_MATH} &&	./build/${DEBUG} > debug_scalar.txt 

clean:
	rm -rf build

img: build_dir
	gcc -march=native -ljpeg src/*.c -o build/${RELEASE} ${INCLUDE_MATH} -s 
	./build/${RELEASE} > ${OUTPUT_NAME} 

img_sc: build_dir
	gcc  -march=native src/*.c -o build/${RELEASE} ${INCLUDE_MATH} -ljpeg -lpng -s 
	./build/${RELEASE}  

animation: animation_dir 
	gcc  -DTORTEM_RENDER_ANIM -march=native src/*.c -o build/${RELEASE} ${INCLUDE_MATH} -ljpeg -lpng -s 
	./build/${RELEASE}  

mp4_output:
	ffmpeg -framerate 30 -i animation_output/output%04d.jpg -c:v libx264 -r 30 -pix_fmt yuv420p output_video.mp4


release: build_dir
	gcc src/*.c -o build/${RELEASE} ${INCLUDE_MATH} -s 
