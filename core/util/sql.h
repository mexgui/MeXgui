#ifndef SQL_H
#define SQL_H

#include <QObject>
#include <QtSql/QtSql>
#include "error.h"
#include "../gui/globals.h"

using namespace globals;

namespace core {
    namespace util {


        class sql : public QObject
        {
         Q_OBJECT
        public:
             explicit sql(QObject *parent = 0);
             ~sql();
            void insertJob();
            void deleteJob();
            void updateJob();
            void getJobs();

            void insertAudioPreset(audioProfile &sA);
            void insertVideoPreset(videoProfile &sV);

            void deleteAudioPreset(int &id);
            void deleteVideoPreset(int &id);

            void updateAudioPreset(int &id);
            void updateVideoPreset(int &id);

            audioProfile getAudioPreset(int id);
            videoProfile getVideoPreset(int id);

            encoderProfiles * getEncoderProfiles();
            containerList * getContainerList();

        signals:

        public slots:

        private:
            QSqlDatabase db;

        };

    }
}

#endif // SQL_H
