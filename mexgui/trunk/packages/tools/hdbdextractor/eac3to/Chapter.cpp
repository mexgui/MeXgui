#include "Chapter.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;

namespace eac3to
{

	Chapter::Chapter()
	{
	}

	const int &Chapter::getNumber() const
	{
		return privateNumber;
	}

	void Chapter::setNumber(const int &value)
	{
		privateNumber = value;
	}

	const DateTime &Chapter::getTime() const
	{
		return privateTime;
	}

	void Chapter::setTime(const DateTime &value)
	{
		privateTime = value;
	}

	const std::string &Chapter::getName() const
	{
		return privateName;
	}

	void Chapter::setName(const std::string &value)
	{
		privateName = value;
	}
}
