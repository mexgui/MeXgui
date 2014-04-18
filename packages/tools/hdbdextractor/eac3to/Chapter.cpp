#include "Chapter.h"




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

	const QString &Chapter::getName() const
	{
		return privateName;
	}

	void Chapter::setName(const QString &value)
	{
		privateName = value;
	}
}
