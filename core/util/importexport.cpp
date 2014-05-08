#include "importexport.h"
#include <QFile>
#include <QList>
#include <QXmlStreamReader>
#include <QMessageBox>
#include <QSqlQuery>
#include "../gui/globals.h"

using namespace globals;
using namespace core::util;



importExport::importExport()
{


}


void importExport::importAudioProfile(QString &xml)
{
    audioProfile I;
    QFile file(xml);
    QXmlStreamReader * xmlReader = new QXmlStreamReader(this);

    file.open(QIODevice::ReadOnly);
    xmlReader->setDevice(&file);


    while (!xmlReader.isEndDocument())
          {
           if (xmlReader->isStartElement())
              {
                  QString name = xmlReader->name().toString();

                  if (name == "Name" ) I.Name = xmlReader->readElementText();
                  else  if (name == "delay" ) I.delay = xmlReader->readElementText().toFloat();
                  else  if (name == "delayEnabled" ){
                      if (xmlReader.readElementText() = "true") I.delayEnabled = true;
                      else I.delayEnabled = false;
                  }
                  else  if (name == "PreferredDecoderString" ) I.PreferredDecoderString = xmlReader.readElementText();
                  else  if (name == "DownmixMode" ) I.DownmixMode = xmlReader->readElementText();
                  else  if (name == "BitrateMode" ) I.BitrateMode = xmlReader->readElementText();
                  else  if (name == "Bitrate" ) I.Bitrate = xmlReader->readElementText().toInt();
                  else  if (name == "AutoGain" ){
                      if (xmlReader.readElementText()=="true") I.AutoGain = true;
                      else I.AutoGain = false;
                  }
                  else  if (name == "SampleRateType" ) I.SampleRateType = xmlReader->readElementText().toInt();
                  else  if (name == "ApplyDRC" ){
                      if (xmlReader.readElementText() =="true") I.ApplyDRC = true;
                      else I.ApplyDRC = false;
                  }
                  else  if (name == "Normalize" ) I.Normalize = xmlReader->readElementText().toInt();
                  else  if (name == "Quality" ) I.Quality = xmlReader->readElementText().toFloat();
                  else  if (name == "AbrBitrate" ) I.AbrBitrate = xmlReader->readElementText().toInt();
                  else  if (name == "CreateHintTrack" ) {
                      if (xmlReader.readElementText() =="true") I.CreateHintTrack = true;
                      else I.CreateHintTrack = false;
                  }
                  else  if (name == "AbrBitrate" ) I.AbrBitrate = xmlReader->readElementText().toInt();
                  else  if (name == "Profile" ) I.Profile = xmlReader->readElementText();
              }
              if (xmlReader->isEndElement()) {
                  //Here is support for differend audioEncoder setting profiles
                  QString endName = xmlReader->name().toString();
                  if      (endName == "GenericProfileOfMP3Settings")        I.encoderId = mp3id;
                  else if (endName == "GenericProfileOfNeroAACSettings")    I.encoderId = NeroId;
                  else if (endName == "GenericProfileOfFlacSettings")       I.encoderId = FlacId;
                  else if (endName == "GenericProfileOfOggVorbisSettings")  I.encoderId = VorbisId;
                  else if (endName == "GenericProfileOfOpusSettings")       I.encoderId = OPUSId;
                  else if (endName == "GenericProfileOfAftenSettings")      I.encoderId = AftenId;
                  else if (endName == "GenericProfileOfQaacSettings")       I.encoderId = QAACId;
                  else if (endName == "GenericProfileOfMP2Settings")        I.encoderId = FFmpegId;
                  else if (endName == "GenericProfileOfAC3Settings")        I.encoderId = FFmpegId;
                  else if (endName == "GenericProfileOfMP2Settings")        I.encoderId = FFmpegId;
              }



              if (xmlReader.hasError())
              {
                  QMessageBox::critical(this,"MeXgui Audio Profile Importer",xmlReader->error(),QMessageBox::Ok);
                  return;
              }
              xmlReader->readNext();

        }



    QSqlQuery query;
    try {
         bool result = query.exec(QString("insert into AudioProfiles values(NULL,'%1',%2,%3,%4,'%5','%6','%7',%8,%9,%10,%11,%12,'%13',%14,%15,%16,'%17',%18,%19)")
               .arg(I.Name).arg(I.encoderId).arg(I.delay).arg(I.delayEnabled).arg(I.PreferredDecoderString).arg(I.DownmixMode).arg(I.BitrateMode)
               .arg(I.Bitrate).arg(I.AutoGain).arg(I.SampleRateType).arg(I.ApplyDRC).arg(I.Normalize).arg(I.Profile).arg(I.Quality).arg(I.AbrBitrate)
               .arg(I.CreateHintTrack).arg(I.Mode).arg(I.NoDelay).arg(I.CompressionLevel));
         if (!result) throw QString(query.lastError());
    }
    catch(QString error) {
        QMessageBox::critical(this,"MeXgui Audio Profile Importer", error + "\n\nSQL guery was:\n\n" + query.lastQuery(),QMessageBox::Ok);
    }

    file.close();
    delete xmlReader;
    delete I;
}

void importExport::exportAudioProfile(int id)
{

}

void importExport::importVideoProfile(QString &file)
{

}

void importExport::exportVideoProfile(int id)
{

}

void importExport::importJob(QString &file)
{

}

void importExport::exportJob(int id)
{

}
