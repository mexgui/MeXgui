#ifndef ERROR_H
#define ERROR_H

#include <QObject>
namespace core {
    namespace util {
        class error : public QObject
        {
            Q_OBJECT
        public:
            explicit error(QObject *parent = 0);

            QString Message();
            void setMessage(QString * customMessage);

        signals:

        public slots:

        protected:
            QString message;

        };


    }
}

#endif // ERROR_H
