/*
 *this function uses the library to detect the video file
 *we get from the network, and send to result to the ip who
 *sends the video data.
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <libavformat/avformat.h>
#include <libavformat/avio.h>
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
#include <libavutil/avutil.h>
#include "process.h"


#if LIBAVCODEC_VERSION_INT < AV_VERSION_INT(55,28,1)
#define av_frame_alloc avcodec_alloc_frame
#define av_frame_free avcodec_free_frame
#endif

void SaveFrame(AVFrame *pFrame, int width, int height, int iFrame) {
  FILE *pFile;
  char szFilename[32];
  int  y;

  // Open file
  sprintf(szFilename, "frame%d.ppm", iFrame);
  pFile=fopen(szFilename, "wb");
  if(pFile==NULL)
    return;

  // Write header
  fprintf(pFile, "P6\n%d %d\n255\n", width, height);

  // Write pixel data
  for(y=0; y<height; y++)
    fwrite(pFrame->data[0]+y*pFrame->linesize[0], 1, width*3, pFile);

  // Close file
  fclose(pFile);
}

void processVideo(char* filename){
    /**指针都需要初始化为0*/

    printf("in processvideo.c\n");
    /**open video file */
    /**4.*/
    /**1.注册所有视频文件格式和编码库*/
    av_register_all();//只需要调用一次就可以了

    /**2.打开视频文件*/
    AVFormatContext* pFormatCtx=0;
    //存储信息在pFormatCtx结构当中

    int res = avformat_open_input(&pFormatCtx, filename, NULL, NULL);//avformat_open_input(&pFormatCtx,filename,NULL,NULL);
    if(res !=0 ){
        printf("open file failed...\n");
        return ;
    }

    /**3.获取系统中流媒体信息*/
    res = avformat_find_stream_info(pFormatCtx,NULL);
    if(res < 0 ){
        printf("can not file stream information...\n");
        return ;
    }

    /**4.将信息放在放在pFormatCtx中*/
    av_dump_format(pFormatCtx,0,filename,0);



    /**5.获取第一帧视频流*/
    AVCodecContext* pCodecCtxOrig=0;
    AVCodecContext* pCodecCtx=0;
    int videoStream = -1;
    int i;

    for(i=0;i<pFormatCtx->nb_streams;++i)
		if(pFormatCtx->streams[i]->codec->codec_type==AVMEDIA_TYPE_VIDEO) {
       // if(pFormatCtx->streams[i]->codec->codec_tag == AVMEDIA_TYPE_VIDEO){
            videoStream = i;
            break;
        }

    if(videoStream == -1){
        printf("do not find a video stream...\n");
        return ;
	}
    //获取指向视频流环境的指针
//    pCodecCtx = pFormatCtx->streams[videoStream]->codec;
    pCodecCtxOrig=pFormatCtx->streams[videoStream]->codec;

    AVCodec* pCodec = 0;
    //获取解析流的解析函数
    //pCodec = avcodec_find_decoder(pCodecCtx->codec_tag);
    pCodec = avcodec_find_decoder(pCodecCtxOrig->codec_id);

    if(pCodec == NULL){
        printf("codec is not supported...\n");
        return ;
    }
    //复制环境
    pCodecCtx = avcodec_alloc_context3(pCodec);

    if(avcodec_copy_context(pCodecCtx,pCodecCtxOrig) !=0){
        printf("can not copy codec content...\n");
        return ;
    }

    //打开codec
    if(avcodec_open2(pCodecCtx,pCodec,NULL) < 0){
        printf("can not open codec ...\n");
        return ;
    }

    //存储数据

    AVFrame* pFrame = 0;
    AVFrame* pFrameRGB = 0;
    //分配视频数据帧
    pFrame = av_frame_alloc();
    //分配avFrame 结构
    pFrameRGB = av_frame_alloc();
    if(pFrameRGB == NULL){
        return ;
    }

    uint8_t* buffer = NULL;
    int numBytes;
    numBytes = avpicture_get_size(PIX_FMT_RGB24,pCodecCtx->width,pCodecCtx->height);
    buffer = (uint8_t*)av_malloc(numBytes*sizeof(uint8_t));

//    avpicture_fill();
    avpicture_fill((AVPicture*)pFrameRGB,buffer,PIX_FMT_RGB24,pCodecCtx->width,pCodecCtx->height);



    /**6.读取数据*/

    struct SwsContext * sws_ctx = 0;
    int frameFinished;
    AVPacket packet;
    //初始化SWS环境
    sws_ctx = sws_getContext(
            pCodecCtx->width,
            pCodecCtx->height,
            pCodecCtx->pix_fmt,
            pCodecCtx->width,
            pCodecCtx->height,
            PIX_FMT_RGB24,
            SWS_BILINEAR,
            NULL,
            NULL,
            NULL
    );
    i= 0;
    while(av_read_frame(pFormatCtx,&packet)>=0){
        if(packet.stream_index == videoStream){
            avcodec_decode_video2(pCodecCtx,pFrame,&frameFinished,&packet);

            if(frameFinished){
                sws_scale(sws_ctx,(uint8_t const * const *)pFrame->data,pFrame->linesize,0,pCodecCtx->height,
                pFrameRGB->data,pFrameRGB->linesize
                );

                   // Save the frame to disk
            if(++i<=5)
                SaveFrame(pFrameRGB, pCodecCtx->width, pCodecCtx->height,i);
            }
        }//end if index

        av_free_packet(&packet);
    }



         // Free the RGB image
      av_free(buffer);
      av_frame_free(&pFrameRGB);

      // Free the YUV frame
      av_frame_free(&pFrame);

      // Close the codecs
      avcodec_close(pCodecCtx);
      avcodec_close(pCodecCtxOrig);

      // Close the video file
      avformat_close_input(&pFormatCtx);

}


int func2(int argc, char *argv[]) {
  // Initalizing these to NULL prevents segfaults!
  AVFormatContext   *pFormatCtx = NULL;
  int               i, videoStream;
  AVCodecContext    *pCodecCtxOrig = NULL;
  AVCodecContext    *pCodecCtx = NULL;
  AVCodec           *pCodec = NULL;
  AVFrame           *pFrame = NULL;
  AVFrame           *pFrameRGB = NULL;
  AVPacket          packet;
  int               frameFinished;
  int               numBytes;
  uint8_t           *buffer = NULL;
  struct SwsContext *sws_ctx = NULL;

  if(argc < 2) {
    printf("Please provide a movie file\n");
    return -1;
  }
  // Register all formats and codecs
  av_register_all();

  // Open video file
  if(avformat_open_input(&pFormatCtx, argv[1], NULL, NULL)!=0)
    return -1; // Couldn't open file

  // Retrieve stream information
  if(avformat_find_stream_info(pFormatCtx, NULL)<0)
    return -1; // Couldn't find stream information

  // Dump information about file onto standard error
  av_dump_format(pFormatCtx, 0, argv[1], 0);

  // Find the first video stream
  videoStream=-1;
  for(i=0; i<pFormatCtx->nb_streams; i++)
    if(pFormatCtx->streams[i]->codec->codec_type==AVMEDIA_TYPE_VIDEO) {
      videoStream=i;
      break;
    }
  if(videoStream==-1)
    return -1; // Didn't find a video stream

  // Get a pointer to the codec context for the video stream
  pCodecCtxOrig=pFormatCtx->streams[videoStream]->codec;
  // Find the decoder for the video stream
  pCodec=avcodec_find_decoder(pCodecCtxOrig->codec_id);
  if(pCodec==NULL) {
    fprintf(stderr, "Unsupported codec!\n");
    return -1; // Codec not found
  }
  // Copy context
  pCodecCtx = avcodec_alloc_context3(pCodec);
  if(avcodec_copy_context(pCodecCtx, pCodecCtxOrig) != 0) {
    fprintf(stderr, "Couldn't copy codec context");
    return -1; // Error copying codec context
  }

  // Open codec
  if(avcodec_open2(pCodecCtx, pCodec, NULL)<0)
    return -1; // Could not open codec

  // Allocate video frame
  pFrame=av_frame_alloc();

  // Allocate an AVFrame structure
  pFrameRGB=av_frame_alloc();
  if(pFrameRGB==NULL)
    return -1;

  // Determine required buffer size and allocate buffer
  numBytes=avpicture_get_size(PIX_FMT_RGB24, pCodecCtx->width,
			      pCodecCtx->height);
  buffer=(uint8_t *)av_malloc(numBytes*sizeof(uint8_t));

  // Assign appropriate parts of buffer to image planes in pFrameRGB
  // Note that pFrameRGB is an AVFrame, but AVFrame is a superset
  // of AVPicture
  avpicture_fill((AVPicture *)pFrameRGB, buffer, PIX_FMT_RGB24,
		 pCodecCtx->width, pCodecCtx->height);

  // initialize SWS context for software scaling
  sws_ctx = sws_getContext(
               pCodecCtx->width,
			   pCodecCtx->height,
			   pCodecCtx->pix_fmt,
			   pCodecCtx->width,
			   pCodecCtx->height,
			   PIX_FMT_RGB24,
			   SWS_BILINEAR,
			   NULL,
			   NULL,
			   NULL
			   );

  // Read frames and save first five frames to disk
  i=0;
  while(av_read_frame(pFormatCtx, &packet)>=0) {
    // Is this a packet from the video stream?
    if(packet.stream_index==videoStream) {
      // Decode video frame
      avcodec_decode_video2(pCodecCtx, pFrame, &frameFinished, &packet);

      // Did we get a video frame?
      if(frameFinished) {
	// Convert the image from its native format to RGB
	sws_scale(sws_ctx, (uint8_t const * const *)pFrame->data,
		  pFrame->linesize, 0, pCodecCtx->height,
		  pFrameRGB->data, pFrameRGB->linesize);

	// Save the frame to disk
	if(++i<=5)
	  SaveFrame(pFrameRGB, pCodecCtx->width, pCodecCtx->height,
		    i);
      }
    }

    // Free the packet that was allocated by av_read_frame
    av_free_packet(&packet);
  }

  // Free the RGB image
  av_free(buffer);
  av_frame_free(&pFrameRGB);

  // Free the YUV frame
  av_frame_free(&pFrame);

  // Close the codecs
  avcodec_close(pCodecCtx);
  avcodec_close(pCodecCtxOrig);

  // Close the video file
  avformat_close_input(&pFormatCtx);

  return 0;
}

