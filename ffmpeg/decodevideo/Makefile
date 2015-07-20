LIBS=-lavcodec   \
	 -lavformat  \
	 -lavutil    \
	 -lswscale   \
	 -lz
FFMPEGHOME=/usr/local/ffmpeg
INCLUDE=${FFMPEGHOME}/include

LIBSPATH=${FFMPEGHOME}/lib
OBJS=main
$(OBJS):process.o main.o
	gcc -o ${OBJS} process.o main.o  -L${LIBSPATH}  ${LIBS}
process.o:process.c process.h
	gcc -c process.c -I${INCLUDE}
main.o:main.c 
	gcc -c main.c  -I${INCLUDE}

clean:
	rm *.o
