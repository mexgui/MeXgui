#ifndef GLOBAL_H // header guards
#define GLOBAL_H
#include <QString>
#include <QtSql>

// define audio encoder SQL id's
#define mp3id 1
#define AftenId 2
#define FFmpegId 3
#define NeroId 4
#define VorbisId 5
#define FlacId 6
#define QAACId 7
#define OPUSId 8

// define video encoder SQL id's
#define FFmpegId 1
#define XvidId 2
#define x264Id 3

namespace globals {
    // extern tells the compiler this variable is declared elsewhere
    extern QString InputPath;
    extern QString InputExtension;
    extern QString InputFileName;
    extern QSqlDatabase db;


    struct audioProfile {

        QString Name = "", PreferredDecoderString = "", Profile = "", DownmixMode = "", BitrateMode = "", Mode = "";
        bool    delayEnabled = false, AutoGain = false, ApplyDRC = false, CreateHintTrack = false, NoDelay = false;
        int     id = 0, encoderId = 0, Bitrate = 0,SampleRateType = 0,Normalize = 0,
                AbrBitrate =0, encoderId = 0, ;
        float   delay = 0, Quality = 0, CompressionLevel = 0;

        };

    struct videoProfile {
        QString Name = "", PreferredDecoderString = "", Profile = "", DownmixMode = "", BitrateMode = "", Mode = "";
        bool    delayEnabled = false, AutoGain = false, ApplyDRC = false, CreateHintTrack = false, NoDelay = false;
        int     id = 0, encoderId = 0, Bitrate = 0,SampleRateType = 0,Normalize = 0,
                AbrBitrate =0, encoderId = 0, ;
        float   delay = 0, Quality = 0, CompressionLevel = 0;

        };

    struct encoderProfiles {
        int profileId;
        QString encoderName, profileName;
    };

    struct containerList {
        int id;
        QString containerName;
    };

    struct job {
        int id;
        QString encoderName, status;
        QDateTime startTime, endTime;
        quint64 duration;
        bool encoding=false;
    };


}



#endif
