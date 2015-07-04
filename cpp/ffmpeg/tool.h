#ifndef TOOL_H_INCLUDED
#define TOOL_H_INCLUDED
#include "libavformat/avformat.h"
#include "libavcodec/avcodec.h"
#include "libswscale/swscale.h"
int yuv_analysis(const char* yuvname);
void SaveFrame(uint8_t *pFrame, int width, int height, int video_id, char *videofile);
int content_analysis2(char* videofile, int mn);


#endif // TOOL_H_INCLUDED
