#include "error.h"

using namespace core::util;

error::error(QObject *parent) :
    QObject(parent)
{
}

QString error::Message()
{
    return message;
}

void error::setMessage(QString *customMessage)
{
    message = customMessage;
}
