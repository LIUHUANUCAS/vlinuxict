

/*
 *this function uses the library to detect the video file
 *we get from the network, and send to result to the ip who
 *sends the video data.
 *
 *author:	JIN
 *data:		2013/01/22
 *
 */
#include <stdio.h>
#include <time.h>
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
void SaveFrame(uint8_t *pFrame, int width, int height, int video_id, char *videofile)
{
	FILE *pFile;
	char szFilename[128];

	char strFormatByte[4];
	strFormatByte[0] = 'd';
	strFormatByte[1] = 'y';
	strFormatByte[2] = 'm';
	strFormatByte[3] = 0;


	sprintf(szFilename, "%s_%dx%d.264",videofile,width,height);
	pFile=fopen(szFilename, "ab");
	if(pFile==NULL)
	{
		fprintf(stderr, "open target file error\n");
		return;
	}


	fwrite(&strFormatByte,sizeof(char),4,pFile);
	fwrite(&width,sizeof(int),1,pFile);
	fwrite(&height,sizeof(int),1,pFile);
	int frame_size = width * height + 2 * ((width+1)/2)*((height+1)/2);
	fwrite(pFrame, sizeof(uint8_t), frame_size, pFile);
	//fwrite(pFrame, sizeof(uint8_t), width * height * 3 / 2, pFile);

	fclose(pFile);
}

int yuv_analysis(const char* yuvname)
{
	FILE *pFile;
	uint8_t *pFrame=NULL;
	int width=0,last_width=0;
	int height=0,last_height=0;;
	int video_id,hit_id = 0,total_frame=0;
	char strFormatByte[4];

	char _strFormatByte[4];
	_strFormatByte[0] = 'd';
	_strFormatByte[1] = 'y';
	_strFormatByte[2] = 'm';
	_strFormatByte[3] = 0;

	int frame_size;

	pFile=fopen(yuvname, "rb");
	if(pFile==NULL)
	{
		fprintf(stderr, "open target file error\n");
		return -1;
	}



	while(!feof(pFile))
	{
		total_frame++;
		memset(strFormatByte,0,4);
		fread(&strFormatByte,sizeof(char),4,pFile);
		if(strncmp(strFormatByte,_strFormatByte,3))
			break;
		last_width = width;
		last_height = height;
		fread(&width,sizeof(int),1,pFile);
		fread(&height,sizeof(int),1,pFile);

		if(width!=last_width||height!=last_height)
		{
			frame_size = width * height + 2 * ((width+1)/2)*((height+1)/2);
			if(pFrame != NULL)
			{
				free(pFrame);
				pFrame = NULL;
			}

			if(pFrame == NULL)
				pFrame = (uint8_t *)calloc(frame_size,sizeof(uint8_t));
		}
		memset(pFrame,0,frame_size);
		fread(pFrame, sizeof(uint8_t), frame_size, pFile);


		//int video_id = feature_match(pFrame,width, height);
		//SaveFrame(buffer, pCodecCtx->width, pCodecCtx->height, video_id, videofile);
		//if (video_id > 0) {
		//	printf("match frame: %d, %d, %d\n", hit_id, video_id, total_frame);

	//		hit_id++;
	//	}

		//fseek(pFile,0,SEEK_CUR);
	}

	if(pFrame != NULL)
	{
		free(pFrame);
		pFrame = NULL;
	}

	fclose(pFile);


	return -1;
}



//返回-1解析失败，返回-2无封堵建议，其它有封堵建议
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
	avcodec_register_all();
	av_register_all();
	avformat_network_init();

	pFormatCtx = avformat_alloc_context();
	//pFormatCtx->interrupt_callback.callback =  decode_interrupt_cb;
	if(avformat_open_input(&pFormatCtx,videofile,NULL,NULL) < 0){
		//if(av_open_input_file(&pFormatCtx, videofile, NULL, 0, NULL) < 0){
		fprintf(stderr, "Couldn't Open video file %s\n",videofile);
		return -1;
	}

	if(avformat_find_stream_info(pFormatCtx,NULL)<0){
	//	av_close_input_file(pFormatCtx);
		fprintf(stderr, "av_find_stream_info error\n");
		return -1; // Couldn't open file
	}

	//== find video stream
	int i;
	videoStream=-1;
	for(i=0;i<pFormatCtx->nb_streams;i++){
		if(pFormatCtx->streams[i]->codec->codec_type==AVMEDIA_TYPE_VIDEO){
			videoStream=i;
			break;
		}
	}

	if(videoStream==-1){
	//	av_close_input_file(pFormatCtx);
		fprintf(stderr, "Didn't find a video stream and pFormatCtx->nb_streams is %d\n",pFormatCtx->nb_streams);
		return -1; // Didn't find a video stream
	}

	pCodecCtx=pFormatCtx->streams[videoStream]->codec;
	if(pCodecCtx==NULL){
	//	av_close_input_file(pFormatCtx);

		fprintf(stderr, "Codec not found\n");
		return -1; // Codec not found
	}
	printf("%d\n",pCodecCtx->codec_id);

	// 	if(pCodecCtx->codec_id == CODEC_ID_H263)
	// 	{
	// 		pCodecCtx->codec_id = CODEC_ID_H264;
	// 	}

	pCodec=avcodec_find_decoder(pCodecCtx->codec_id);
	if(pCodec==NULL){
		if(pCodecCtx!=NULL)
			avcodec_close(pCodecCtx);
	//	if(pFormatCtx!=NULL)
	//		av_close_input_file(pFormatCtx);
		return -1;
	}



	//  	if(pCodecCtx->codec_id != CODEC_ID_MPEG4 && pCodecCtx->codec_id!=CODEC_ID_MJPEG)
	//  	{
	// 		if(pCodec->capabilities&CODEC_CAP_TRUNCATED){
	// 			pCodecCtx->flags|=CODEC_FLAG_TRUNCATED;
	// 		}
	// 	}

	if(pCodecCtx->pix_fmt == PIX_FMT_NONE)
	{
		//avcodec_close(pCodecCtx);
		if(pCodecCtx!=NULL)
			avcodec_close(pCodecCtx);
	//	if(pFormatCtx!=NULL)
	//		av_close_input_file(pFormatCtx);
		return -1; // Could not open codec
	}

	//== open decoder
	if(avcodec_open2(pCodecCtx,pCodec, NULL)<0){
		if(pCodecCtx!=NULL)
			avcodec_close(pCodecCtx);
	//	if(pFormatCtx!=NULL)
	//		av_close_input_file(pFormatCtx);
		return -1; // Could not open codec
	}

	// 	int frame_width = (pCodecCtx->width/4)*4;
	// 	int frame_height = (pCodecCtx->height/4)*4;
	int frame_width = pCodecCtx->width;
	int frame_height = pCodecCtx->height;
	int frame_pix_fmt = pCodecCtx->pix_fmt;

	pFrame = avcodec_alloc_frame();
	if(pFrame== NULL)
	{
		avcodec_close(pCodecCtx);
	//	av_close_input_file(pFormatCtx);
		fprintf(stderr, "pFrame==NULL\n");
		return -1;
	}

	pFrameYUV=avcodec_alloc_frame();
	if(pFrameYUV==NULL){
		av_free(pFrame);
		avcodec_close(pCodecCtx);
		fprintf(stderr, "pFrameYUV==NULL\n");
		return -1;
	}

	numBytes=avpicture_get_size(PIX_FMT_YUV420P, pCodecCtx->width,pCodecCtx->height);

	buffer=(uint8_t*)calloc(numBytes,sizeof(uint8_t));
	base_buffer=(uint8_t*)calloc(numBytes,sizeof(uint8_t));
	if(buffer == NULL)
	{
		av_free(pFrame);
	//	av_close_input_file(pFormatCtx);
		return -1;
	}
	avpicture_fill((AVPicture *)pFrameYUV, buffer, PIX_FMT_YUV420P,pCodecCtx->width, pCodecCtx->height);
	img_convert_ctx = sws_getContext(pCodecCtx->width,pCodecCtx->height,pCodecCtx->pix_fmt,
		pCodecCtx->width,pCodecCtx->height,PIX_FMT_YUV420P,
		SWS_BICUBIC,NULL,NULL,NULL);


	if (mn==0) mn=0x7fffffff;
	int FlagIFrame = 0;
	while(av_read_frame(pFormatCtx,&packet)>=0)
	{
		//printf("I Frame = %d streamid = %d\n",packet.flags,packet.stream_index);
		if(packet.stream_index==videoStream/*&&packet.flags*/)
		{
			//avcodec_decode_video2(pCodecCtx, pFrame, &frameFinished,packet.data, packet.size);
			// 			if(packet.pos > 1600000)
			// 				printf("%d\n",packet.pos);
			// 			printf("%d\n",packet.pos);
			// 			if(packet.flags != 1)
			// 				continue;
			int nRet = avcodec_decode_video2(pCodecCtx, pFrame, &frameFinished,&packet);



			if(nRet < 0)
			{
				av_free_packet(&packet);
				continue;
			}
			// 			if(pFrame->pict_type != AV_PICTURE_TYPE_I)
			// 				continue;
			if(frameFinished)
			{

				if(frame_width   != pFrame->width  ||
					frame_height  != pFrame->height ||
					frame_pix_fmt != pFrame->format)
				{
					printf("error\n");
					av_free_packet(&packet);
					break;
				}


				int offset = 0;
				width = pCodecCtx->width;
				height = pCodecCtx->height;
				if(frame_height!=height||frame_width!=width)
				{
					av_free_packet(&packet);
					break;
				}
				sws_scale(img_convert_ctx,(const uint8_t* const*)pFrame->data,pFrame->linesize,0,pCodecCtx->height,pFrameYUV->data,pFrameYUV->linesize);
				// 				printf("%d*%d\n",frame_width,frame_height);
				// 				printf("%d*%d\n",pCodecCtx->width,pCodecCtx->height);
				int mi;
				for( mi=0;mi<3;mi++) {
					ptr = pFrameYUV->data[mi];
					linesize = pFrameYUV->linesize[mi];
					if (mi == 1) {
						width = (width+1)/2;
						height = (height+1)/2;
					}
					int j;
					for( j=0;j<height;j++) {
						memcpy(buffer+offset,ptr,width*sizeof(uint8_t));
						ptr += linesize;
						offset += width;
					}
				}

				if(base_flag == 1)
				{
					memcpy(base_buffer,buffer,numBytes);
					base_flag = 0;
					continue;
				}
				skipframe++;
				//roi_rect roiRect = trim_blacl_edge(buffer,pCodecCtx->width, pCodecCtx->height);
				int ret = calc_frame_diff(base_buffer,buffer,pCodecCtx->width, pCodecCtx->height);
				if(ret>10||skipframe>30)
				{
					base_flag = 1;
					total_frame++;
					printf("decode frame: %d %d\n",total_frame,ret);
					char outfilename[32];
					sprintf(outfilename,"bmp\\frame-%d-%d.bmp",total_frame,ret);

					calc_subtitle_diff(buffer,pCodecCtx->width, pCodecCtx->height);
					//SaveFrame(buffer, pCodecCtx->width, pCodecCtx->height, video_id, outfilename);
					saveYUV2BMP(buffer,pCodecCtx->width, pCodecCtx->height,outfilename);
					skipframe = 0;
				}

				//video_id = feature_match(buffer,pCodecCtx->width, pCodecCtx->height);
				//SaveFrame(buffer, pCodecCtx->width, pCodecCtx->height, video_id, videofile);
				if (video_id > 0) {
					printf("match frame: %d, %d, %d\n", hit_id, video_id, total_frame);
					//SaveFrame(buffer, pCodecCtx->width, pCodecCtx->height, video_id,videofile);
					//	hitID[i] = video_id;
					hit_id++;
				}

				//total_frame++;
				if (hit_id > mn) {
					av_free_packet(&packet);
					break;
				}


				if(total_frame>2000&&!FlagIFrame)
				{
					FlagIFrame = 1;
				}
			}
		}
		av_free_packet(&packet);

	}

	printf("decode frame:%d %d\n",hit_id,total_frame);



	if(pFrame!=NULL)
		av_free(pFrame);
	if(pFrameYUV!=NULL)
		av_free(pFrameYUV);
	if(buffer!=NULL)
		free(buffer);

	// 	if (pCodecCtx)
	// 		avcodec_close(pCodecCtx);
	// 	avformat_close_input(&fmt_ctx);
	//
	// 	if(pCodecCtx!=NULL)
	// 		avcodec_close(pCodecCtx);
	if(pFormatCtx!=NULL)
		avformat_close_input(&pFormatCtx);

	return hit_id;

}

int main(int argc, char* argv[])
{
	//content_analysis2("D:\\workspace\\反动视频\\subtitle\\Uyghu.mp4",1000000);
	//content_analysis2("D:\\workspace\\反动视频\\subtitle\\Uyghur_Scholar_Ilham_Tohti.mp4",1000000);
	content_analysis2(" ~/1.rmvb ",1000000);
	return 0;
}

