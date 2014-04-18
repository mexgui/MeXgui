#include "DeinterlaceFilter.h"




//using namespace System::Collections::Generic;

//using namespace System::Text;

namespace MeXgui
{

	DeinterlaceFilter::DeinterlaceFilter(const QString &title, const QString &script)
	{
		this->title = title;
		this->script = script;
	}

	QString DeinterlaceFilter::ToString()
	{
		return this->title;
	}

	const QString &DeinterlaceFilter::getScript() const
	{
		return script;
	}

	void DeinterlaceFilter::setScript(const QString &value)
	{
		script = value;
	}

	const QString &DeinterlaceFilter::getTitle() const
	{
		return title;
	}

	void DeinterlaceFilter::setTitle(const QString &value)
	{
		title = value;
	}
}
