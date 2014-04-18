#include "MediaFileFactory.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;

namespace MeGUI
{

	MediaFileFactory::MediaFileFactory(MainForm *mainForm)
	{
		this->mainForm = mainForm;
	}

	IMediaFile *MediaFileFactory::Open(const std::string &file)
	{
		int bestHandleLevel = -1;
		IMediaFile *bestMediaFile = 0;
		for (MeGUI::GenericRegisterer<IMediaFileFactory*>::const_iterator factory = mainForm->getPackageSystem()->getMediaFileTypes()->begin(); factory != mainForm->getPackageSystem()->getMediaFileTypes()->end(); ++factory)
		{
			int handleLevel = factory->second->HandleLevel(file);
			if (handleLevel < 0)
				continue;
			IMediaFile *mFile = factory->second->Open(file);
			if (mFile != 0 && handleLevel > bestHandleLevel)
			{
				bestHandleLevel = handleLevel;
				bestMediaFile = mFile;
			}
			else if (mFile != 0)
				delete mFile;
		}
		return bestMediaFile;
	}
}
