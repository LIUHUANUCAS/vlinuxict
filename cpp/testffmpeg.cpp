#include <stdio.h>
#include <time.h>
#include <iostream>
#include "libavformat/avformat.h"
#include "libavcodec/avcodec.h"
//#include "libswscale/swscale.h"
using namespace std;


int content_analysis2(char* videofile, int mn)
{
	AVFormatContext *pFormatCtx=NULL;
	AVCodecContext *pCodecCtx=NULL;
	AVCodec *pCodec=NULL;
	AVFrame *pFrame=NULL;
	AVFrame *pFrameYUV=NULL;
	struct SwsContext *img_convert_ctx;
	AVPacket packet;
	uint8_t *buffer=NULL;
	uint8_t *base_buffer=NULL;
	int base_flag = 1;
	int frameFinished;
	int videoStream = 0;
	int matchFrameNum = 0;

	//
	//unsigned char* yuvdata = NULL;
	int numBytes;
	int total_frame = 0;
	int width,height,linesize;
	int video_id=0,hit_id=0;
	uint8_t* ptr = NULL;



	int keynum = 0;
	int skipframe = 0;
	int frameRate = 0;
	int framecount = 0;

	//av_log_set_flags(AV_LOG_SKIP_REPEATED);

	//av_log_set_level(AV_LOG_DEBUG);
//	avcodec_register_all();
//	av_register_all();
//	avformat_network_init();



}

int main(int argc, char* argv[])
{
	//content_analysis2("D:\\workspace\\反动视频\\subtitle\\Uyghu.mp4",1000000);
	//content_analysis2("D:\\workspace\\反动视频\\subtitle\\Uyghur_Scholar_Ilham_Tohti.mp4",1000000);
	char* filename = "1.mp4";
	content_analysis2(filename,10000);

	return 0;
}

