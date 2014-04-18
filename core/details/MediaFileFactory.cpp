#include "MediaFileFactory.h"




//using namespace System::Collections::Generic;

//using namespace System::Text;

namespace MeXgui
{

	MediaFileFactory::MediaFileFactory(MainForm *mainForm)
	{
		this->mainForm = mainForm;
	}

	IMediaFile *MediaFileFactory::Open(const QString &file)
	{
		int bestHandleLevel = -1;
		IMediaFile *bestMediaFile = 0;
		for (MeXgui::GenericRegisterer<IMediaFileFactory*>::const_iterator factory = mainForm->getPackageSystem()->getMediaFileTypes()->begin(); factory != mainForm->getPackageSystem()->getMediaFileTypes()->end(); ++factory)
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
