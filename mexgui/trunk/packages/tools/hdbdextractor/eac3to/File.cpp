#include "File.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;

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

	const std::string &File::getName() const
	{
		return getFullName().substr(0, getFullName().find('.'));
	}

	const std::string &File::getExtension() const
	{
		return getFullName().substr(getFullName().find('.') + 1);
	}

	const std::string &File::getFullName() const
	{
		return privateFullName;
	}

	void File::setFullName(const std::string &value)
	{
		privateFullName = value;
	}

	File::File()
	{
	}

	File::File(const std::string &fileName, int index)
	{
		if (fileName.empty())
			throw new ArgumentNullException("fileName", "The string 'fileName' cannot be null or empty.");

		setFullName(fileName);
		setIndex(index);
	}

	std::string File::ToString()
	{
		return getFullName();
	}
}
