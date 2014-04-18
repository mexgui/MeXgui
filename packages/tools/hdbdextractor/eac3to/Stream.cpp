#include "Stream.h"




namespace eac3to
{

	const int &Stream::getNumber() const
	{
		return privateNumber;
	}

	void Stream::setNumber(const int &value)
	{
		privateNumber = value;
	}

	const QString &Stream::getName() const
	{
		return privateName;
	}

	void Stream::setName(const QString &value)
	{
		privateName = value;
	}

	const StreamType &Stream::getType() const
	{
		return privateType;
	}

	void Stream::setType(const StreamType &value)
	{
		privateType = value;
	}

	const QString &Stream::getDescription() const
	{
		return privateDescription;
	}

	void Stream::setDescription(const QString &value)
	{
		privateDescription = value;
	}

	const QString &Stream::getLanguage() const
	{
		return privateLanguage;
	}

	void Stream::setLanguage(const QString &value)
	{
		privateLanguage = value;
	}

	Stream::Stream()
	{
	}

	Stream::Stream(const QString &s)
	{
		if (s.empty())
			throw new ArgumentNullException("s", "The string 's' cannot be null or empty.");

		setNumber(int::Parse(s.substr(0, s.find(":"))));

		if (s.find("Joined EVO") != string::npos)
			setName("Joined EVO");
		else if (s.find("Joined VOB") != string::npos)
			setName("Joined VOB");
		else if (s.find("Subtitle") != string::npos)
			setName(s.substr(s.rfind(",") + 1));
		else
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
			setName(s.substr(s.find(":") + 1, s.find(',') - s.find(":") - 1)->Trim());

		setDescription(s.substr(s.find(":") + 1));
	}

	Stream *Stream::Parse(const QString &s)
	{
		//EVO, 1 video track, 1 audio track, 3 subtitle tracks, 1:43:54
		//"director"

		/////////////////////////////////////////////////////////////////
		//////// input file
		/*
		M2TS, 1 video track, 1 audio track, 0:00:11, 60i /1.001
		1: h264/AVC, 1080i60 /1.001 (16:9)
		2: AC3, 5.1 channels, 640kbps, 48khz             
		  */

		if (s.empty())
			throw new ArgumentNullException("s", "The string 's' cannot be null or empty.");

		Stream *stream = 0;

		if (s.find("AVC") != string::npos || s.find("VC-1") != string::npos || s.find("MPEG") != string::npos || s.find("DIRAC") != string::npos || s.find("THEORA") != string::npos)
			stream = VideoStream::Parse(s);
		else if (s.find("AC3") != string::npos || s.find("TrueHD") != string::npos || s.find("DTS") != string::npos || s.find("RAW") != string::npos || s.find("PCM") != string::npos || s.find("MP") != string::npos || s.find("AAC") != string::npos || s.find("FLAC") != string::npos || s.find("WAVPACK") != string::npos || s.find("TTA") != string::npos || s.find("VORBIS") != string::npos)
			stream = AudioStream::Parse(s);
		else if (s.find("Subtitle") != string::npos)
			stream = SubtitleStream::Parse(s);
		else if (s.find("Chapters") != string::npos)
			stream = ChapterStream::Parse(s);
		else if (s.find("Joined") != string::npos)
			stream = JoinStream::Parse(s);

		return stream;
	}

	QString Stream::ToString()
	{
		return QString::Format("{0}: {1}", getNumber(), getDescription());
	}
}
