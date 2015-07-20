LIBS=-lavcodec \
	 -lavformat \
	 -lavutil
INCLUDE=/usr/local/gitffmpeg/include

LIBSPATH=/usr/local/gitffmpeg/lib
OBJS=video
$(OBJS):./decodevideo.o
	gcc -o ${OBJS} decodevideo.o -L${LIBSPATH}  ${LIBS}
decodevideo.o:decodevideo.c
	gcc -c decodevideo.c -I${INCLUDE}

clean:
	rm *.o
