#pragma once

//----------------------------------------------------------------------------------------
//	Copyright © 2004 - 2012 Tangible Software Solutions Inc.
//	This class can be used by anyone provided that the copyright notice remains intact.
//
//	This class is used to replace some conversions to or from strings.
//----------------------------------------------------------------------------------------
#include <QTextStream>

class StringConverterHelper
{
public:
	template<typename T>
	static QString toString(const T &subject)
	{
		QTextStream ss;
		ss << subject;
		return ss.str();
	}

	template<typename T>
	static T fromString(const QString &subject)
	{
		QTextStream ss(subject);
		T target;
		ss >> target;
		return target;
	}
};
