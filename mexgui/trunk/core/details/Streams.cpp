#include "Streams.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
using namespace MeGUI::core::util;
namespace MeGUI
{
	namespace core
	{
		namespace details
		{

			MuxStream::MuxStream(const std::string &path, const std::string &language, const std::string &name, int delay, bool bDefaultTrack, bool bForceTrack, TrackInfo *MuxOnlyInfo)
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

			const std::string &MuxStream::getlanguage() const
			{
				return _language;
			}

			void MuxStream::setlanguage(const std::string &value)
			{
				_language = value;
			}

			const std::string &MuxStream::getname() const
			{
				return _name;
			}

			void MuxStream::setname(const std::string &value)
			{
				_name = value;
			}

			BitrateCalculationStream::BitrateCalculationStream(const std::string &filename)
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

			AudioBitrateCalculationStream::AudioBitrateCalculationStream(const std::string &filename) : BitrateCalculationStream(filename)
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
