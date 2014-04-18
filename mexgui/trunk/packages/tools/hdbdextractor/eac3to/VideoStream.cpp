#include "VideoStream.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;

namespace eac3to
{

	const VStreamType &VideoStream::getVType() const
	{
		return privateVType;
	}

	void VideoStream::setVType(const VStreamType &value)
	{
		privateVType = value;
	}

	const std::string &VideoStream::getResolution() const
	{
		return privateResolution;
	}

	void VideoStream::setResolution(const std::string &value)
	{
		privateResolution = value;
	}

	const bool &VideoStream::getIsProgerssive() const
	{
		return privateIsProgerssive;
	}

	void VideoStream::setIsProgerssive(const bool &value)
	{
		privateIsProgerssive = value;
	}

	const double &VideoStream::getFramerate() const
	{
		return privateFramerate;
	}

	void VideoStream::setFramerate(const double &value)
	{
		privateFramerate = value;
	}

	const double &VideoStream::getRatio() const
	{
		return privateRatio;
	}

	void VideoStream::setRatio(const double &value)
	{
		privateRatio = value;
	}

	const object &VideoStream::getExtractTypes() const
	{
		switch (getVType())
		{
			case AVC:
				return new object[] {"MKV", "H264"};
			case VC1:
				return new object[] {"MKV", "VC1"};
			case MPEG:
				return new object[] {"MKV", "M2V"};
			case THEORA:
				return new object[] {"MKV", "OGG"};
			case DIRAC:
				return new object[] {"MKV", "DRC"};
			default:
				return new object[] {"MKV"};
		}
	}

	VideoStream::VideoStream(const std::string &s) : Stream(s)
	{
		if (s.empty())
			throw new ArgumentNullException("s", "The string 's' cannot be null or empty.");

		Stream::setType(Video);
	}

	Stream *VideoStream::Parse(const std::string &s)
	{
		//3: VC-1, 1080p24 /1.001 (16:9) with pulldown flags

		if (s.empty())
			throw new ArgumentNullException("s", "The string 's' cannot be null or empty.");

		VideoStream *videoStream = new VideoStream(s);

//C# TO C++ CONVERTER NOTE: The following 'switch' operated on a string variable and was converted to C++ 'if-else' logic:
//		switch (videoStream.Name.ToUpper(System.Globalization.CultureInfo.InvariantCulture))
//ORIGINAL LINE: case "AVC":
		if (videoStream->getName().ToUpper(System::Globalization::CultureInfo::InvariantCulture) == "AVC")
		{
				videoStream->setVType(AVC);
		}
//ORIGINAL LINE: case "VC-1":
		else if (videoStream->getName().ToUpper(System::Globalization::CultureInfo::InvariantCulture) == "VC-1")
		{
				videoStream->setVType(VC1);
		}
//ORIGINAL LINE: case "MPEG":
		else if (videoStream->getName().ToUpper(System::Globalization::CultureInfo::InvariantCulture) == "MPEG" || videoStream->getName().ToUpper(System::Globalization::CultureInfo::InvariantCulture) == "MPEG2")
		{
				videoStream->setVType(MPEG);
		}
//ORIGINAL LINE: case "THEORA":
		else if (videoStream->getName().ToUpper(System::Globalization::CultureInfo::InvariantCulture) == "THEORA")
		{
				videoStream->setVType(THEORA);
		}
//ORIGINAL LINE: case "DIRAC":
		else if (videoStream->getName().ToUpper(System::Globalization::CultureInfo::InvariantCulture) == "DIRAC")
		{
				videoStream->setVType(DIRAC);
		}

		return videoStream;
	}

	std::string VideoStream::ToString()
	{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		return Stream::ToString();
	}
}
