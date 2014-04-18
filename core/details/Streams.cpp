#include "Streams.h"




//using namespace System::Collections::Generic;

//using namespace System::Text;
using namespace MeXgui::core::util;
namespace MeXgui
{
	namespace core
	{
		namespace details
		{

			MuxStream::MuxStream(const QString &path, const QString &language, const QString &name, int delay, bool bDefaultTrack, bool bForceTrack, TrackInfo *MuxOnlyInfo)
			{
				this->_language = language;
				this->_name = name;
				this->path = path;
				this->delay = delay;
				this->bDefaultTrack = bDefaultTrack;
				this->bForceTrack = bForceTrack;
				this->MuxOnlyInfo = MuxOnlyInfo;
			}

			MuxStream::MuxStream()
			{
			}

			const QString &MuxStream::getlanguage() const
			{
				return _language;
			}

			void MuxStream::setlanguage(const QString &value)
			{
				_language = value;
			}

			const QString &MuxStream::getname() const
			{
				return _name;
			}

			void MuxStream::setname(const QString &value)
			{
				_name = value;
			}

			BitrateCalculationStream::BitrateCalculationStream(const QString &filename)
			{
				this->Filename = filename;
				if (Filename != "")
					fillInfo();
			}

			void BitrateCalculationStream::fillInfo()
			{
				Size = FileSize::Of2(Filename);
			}

			AudioBitrateCalculationStream::AudioBitrateCalculationStream()
			{
			}

			AudioBitrateCalculationStream::AudioBitrateCalculationStream(const QString &filename) : BitrateCalculationStream(filename)
			{
			}

			void AudioBitrateCalculationStream::fillInfo()
			{
				BitrateCalculationStream::fillInfo();
				Type = AType = VideoUtil::guessAudioType(Filename);
			}
		}
	}
}
