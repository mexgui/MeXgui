#include "File.h"




namespace eac3to
{

	const int &File::getIndex() const
	{
		return privateIndex;
	}

	void File::setIndex(const int &value)
	{
		privateIndex = value;
	}

	const QString &File::getName() const
	{
		return getFullName().substr(0, getFullName().find('.'));
	}

	const QString &File::getExtension() const
	{
		return getFullName().substr(getFullName().find('.') + 1);
	}

	const QString &File::getFullName() const
	{
		return privateFullName;
	}

	void File::setFullName(const QString &value)
	{
		privateFullName = value;
	}

	File::File()
	{
	}

	File::File(const QString &fileName, int index)
	{
		if (fileName.empty())
			throw new ArgumentNullException("fileName", "The string 'fileName' cannot be null or empty.");

		setFullName(fileName);
		setIndex(index);
	}

	QString File::ToString()
	{
		return getFullName();
	}
}
