#ifndef QAUDIODECODERF_H
#define QAUDIODECODERF_H

#include <QIODevice>
#include <QFile>
#include <QAudioInput>
#include "ffmpeg.h"
#include <stdint.h>

class QAudioDecoderF
{
public:
    QAudioDecoderF();
    QAudioDecoderF(QString file);
    virtual bool openFile(QString file);
    virtual void close();
private:
    int audioStream = -1;
    AVCodecContext *codecContext;
    AVCodec *codec;
    AVPacket packet;
    uint8_t *buffer;
};

#endif // QAUDIODECODERF_H
