

/*
 *this function uses the library to detect the video file
 *we get from the network, and send to result to the ip who
 *sends the video data.
 */
#include <stdio.h>
#include <time.h>
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
#include "process.h"

int main(int argc, char* argv[])
{
	char name[]="/home/lainan/smalldumb.mp4";
	char name1[]="/home/lainan/smalldumb2.avi";

    processVideo(name1);
    char* last[] = {name1,name};
//    func2(2,last);
    printf("end of process main...\n");
	return 0;
}

