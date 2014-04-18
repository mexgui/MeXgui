#include "CommandlineMuxer.h"




//using namespace System::Collections::Generic;

//using namespace System::Diagnostics;



//using namespace System::Text;
using namespace MeXgui::core::details;
using namespace MeXgui::core::util;

namespace MeXgui
{

	void CommandlineMuxer::setProjectedFileSize()
	{
		su->setProjectedFileSize(FileSize::Empty);
		Nullable<FileSize> tempVar = FileSize.Of2(job.getSettings().getVideoInput());
		su->setProjectedFileSize(su->getProjectedFileSize() + (tempVar::HasValue ? tempVar : FileSize::Empty));
		Nullable<FileSize> tempVar2 = FileSize.Of2(job.getSettings().getMuxedInput());
		su->setProjectedFileSize(su->getProjectedFileSize() + (tempVar2::HasValue ? tempVar2 : FileSize::Empty));

		for (QVector<MuxStream*>::const_iterator s = job->getSettings()->getAudioStreams().begin(); s != job->getSettings()->getAudioStreams().end(); ++s)
			su->setProjectedFileSize(su->getProjectedFileSize() + (FileSize::Of2(this, &(*s)->path) != 0) ? FileSize::Of2(this, &(*s)->path) : FileSize::Empty);

		for (QVector<MuxStream*>::const_iterator s = job->getSettings()->getSubtitleStreams().begin(); s != job->getSettings()->getSubtitleStreams().end(); ++s)
			su->setProjectedFileSize(su->getProjectedFileSize() + (FileSize::Of2(this, &(*s)->path) != 0) ? FileSize::Of2(this, &(*s)->path) : FileSize::Empty);
	}

	void CommandlineMuxer::checkJobIO()
	{
		ensureInputFilesExistIfNeeded(job->getSettings());
		setProjectedFileSize();
	}

	void CommandlineMuxer::ensureInputFilesExistIfNeeded(MuxSettings *settings)
	{
		Util::ensureExistsIfNeeded(settings->getMuxedInput());
		Util::ensureExistsIfNeeded(settings->getVideoInput());
		Util::ensureExistsIfNeeded(settings->getChapterFile());
		for (QVector<MuxStream*>::const_iterator s = settings->getAudioStreams().begin(); s != settings->getAudioStreams().end(); ++s)
			Util::ensureExistsIfNeeded((*s)->path);
		for (QVector<MuxStream*>::const_iterator s = settings->getSubtitleStreams().begin(); s != settings->getSubtitleStreams().end(); ++s)
		{
			if ((*s)->MuxOnlyInfo != 0)
				Util::ensureExistsIfNeeded((*s)->MuxOnlyInfo->SourceFileName);
			else
				Util::ensureExistsIfNeeded((*s)->path);
		}
	}
}
