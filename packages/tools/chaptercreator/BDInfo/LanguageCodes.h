#pragma once

#include <QString>
#include <QVector>

// ****************************************************************************
// 
// Copyright (C) 2009  Cinema Squid
// 
// code from http://www.cinemasquid.com/blu-ray/tools/bdinfo
// 
// ****************************************************************************




//using namespace System::Collections::Generic;

//using namespace System::Text;

//using namespace System::Linq;

namespace BDInfo
{
  class LanguageCodes
  {
public:
	static QVector<KeyValuePair<QString, QString>*> GetTopLanguages();

	static QVector<KeyValuePair<QString, QString>*> GetLanguages();

	static QString GetName(const QString &code);

  };
}
