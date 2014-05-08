#ifndef IMPORTEXPORT_H
#define IMPORTEXPORT_H

#include <QWidget>
#include <QFile>

namespace core {
    namespace util {
        class importExport
        {

        public:
            virtual void importExport();
            virtual void importAudioProfile(QFile &file);
            virtual void exportAudioProfile(int id);
            virtual void importVideoProfile(QFile &file);
            virtual void exportVideoProfile(int id);
            virtual void importJob(QFile &file);
            virtual void exportJob(int id);

        };
    }
}




#endif // IMPORTEXPORT_H
