#include "DeinterlaceFilter.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;

namespace MeGUI
{

	DeinterlaceFilter::DeinterlaceFilter(const std::string &title, const std::string &script)
	{
		this->title = title;
		this->script = script;
	}

	std::string DeinterlaceFilter::ToString()
	{
		return this->title;
	}

	const std::string &DeinterlaceFilter::getScript() const
	{
		return script;
	}

	void DeinterlaceFilter::setScript(const std::string &value)
	{
		script = value;
	}

	const std::string &DeinterlaceFilter::getTitle() const
	{
		return title;
	}

	void DeinterlaceFilter::setTitle(const std::string &value)
	{
		title = value;
	}
}
