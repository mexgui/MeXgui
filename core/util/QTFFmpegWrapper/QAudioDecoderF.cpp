#include "QAudioDecoderF.h"

QAudioDecoderF::QAudioDecoderF()
{
 av_register_all();
}



bool QVideoDecoder::initCodec()
{
   ffmpeg::avcodec_init();
   ffmpeg::avcodec_register_all();
   ffmpeg::av_register_all();

   printf("License: %s\n",ffmpeg::avformat_license());
   printf("AVCodec version %d\n",ffmpeg::avformat_version());
   printf("AVFormat configuration: %s\n",ffmpeg::avformat_configuration());

   return true;
}
