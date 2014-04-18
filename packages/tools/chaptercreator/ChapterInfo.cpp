#include "ChapterInfo.h"




//using namespace System::Collections::Generic;

//using namespace System::Linq;

//using namespace System::Text;



//using namespace System::Xml;



namespace MeXgui
{

	const QString &ChapterInfo::getTitle() const
	{
		return privateTitle;
	}

	void ChapterInfo::setTitle(const QString &value)
	{
		privateTitle = value;
	}

	const QString &ChapterInfo::getLangCode() const
	{
		return privateLangCode;
	}

	void ChapterInfo::setLangCode(const QString &value)
	{
		privateLangCode = value;
	}

	const QString &ChapterInfo::getSourceName() const
	{
		return privateSourceName;
	}

	void ChapterInfo::setSourceName(const QString &value)
	{
		privateSourceName = value;
	}

	const int &ChapterInfo::getTitleNumber() const
	{
		return privateTitleNumber;
	}

	void ChapterInfo::setTitleNumber(const int &value)
	{
		privateTitleNumber = value;
	}

	const QString &ChapterInfo::getSourceType() const
	{
		return privateSourceType;
	}

	void ChapterInfo::setSourceType(const QString &value)
	{
		privateSourceType = value;
	}

	const QString &ChapterInfo::getSourceHash() const
	{
		return privateSourceHash;
	}

	void ChapterInfo::setSourceHash(const QString &value)
	{
		privateSourceHash = value;
	}

	const double &ChapterInfo::getFramesPerSecond() const
	{
		return privateFramesPerSecond;
	}

	void ChapterInfo::setFramesPerSecond(const double &value)
	{
		privateFramesPerSecond = value;
	}

	const TimeSpan &ChapterInfo::getDuration() const
	{
		return privateDuration;
	}

	void ChapterInfo::setDuration(const TimeSpan &value)
	{
		privateDuration = value;
	}

	const QVector<Chapter> &ChapterInfo::getChapters() const
	{
		return privateChapters;
	}

	void ChapterInfo::setChapters(const QVector<Chapter> &value)
	{
		privateChapters = value;
	}

	QString ChapterInfo::ToString()
	{
		if (getChapters().size() > 1 || getChapters().empty())
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
			return QString::Format("{0} - {1}  -  {2}  -  [{3} Chapters]", getTitle(), getSourceName(), getDuration()->ToString(), getChapters().size());
		else
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
			return QString::Format("{0} - {1}  -  {2}  -  [{3} Chapter]", getTitle(), getSourceName(), getDuration()->ToString(), getChapters().size());
	}

	void ChapterInfo::ChangeFps(double fps)
	{
		for (int i = 0; i < getChapters().size(); i++)
		{
			Chapter c = getChapters()[i];
			double frames = c.getTime()->TotalSeconds * getFramesPerSecond();
			getChapters()[i] = Chapter(new object[] {Name = c.getName(), Time = new TimeSpan(static_cast<qint64>(Math::Round(frames / fps * TimeSpan::TicksPerSecond)))});
		}

		double totalFrames = getDuration()->TotalSeconds * getFramesPerSecond();
		setDuration(new TimeSpan(static_cast<qint64>(Math::Round((totalFrames / fps) * TimeSpan::TicksPerSecond))));
		setFramesPerSecond(fps);
	}

	void ChapterInfo::SaveText(const QString &filename)
	{
		QVector<QString> lines = QVector<QString>();
		int i = 0;
		for (QVector<Chapter>::const_iterator c = getChapters().begin(); c != getChapters().end(); ++c)
		{
			i++;
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
			if ((*c).getTime()->ToString()->Length == 8)
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
				lines.push_back("CHAPTER" + i.ToString("00") + "=" + (*c).getTime()->ToString() + ".000"); // better formating
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
			else if ((*c).getTime()->ToString()->Length > 12)
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
				lines.push_back("CHAPTER" + i.ToString("00") + "=" + (*c).getTime()->ToString()->substr(0, 12)); // remove some duration length too long
			else
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
				lines.push_back("CHAPTER" + i.ToString("00") + "=" + (*c).getTime()->ToString());
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
			lines.push_back("CHAPTER" + i.ToString("00") + "NAME=" + (*c).getName());
		}
		File::WriteAllLines(filename, lines.ToArray());
	}

	void ChapterInfo::SaveQpfile(const QString &filename)
	{
		QVector<QString> lines = QVector<QString>();
		for (QVector<Chapter>::const_iterator c = getChapters().begin(); c != getChapters().end(); ++c)
			lines.push_back(QString::Format("{0} K", static_cast<qint64>(Math::Round((*c).getTime()->TotalSeconds * getFramesPerSecond()))));
		File::WriteAllLines(filename, lines.ToArray());
	}

	void ChapterInfo::SaveCelltimes(const QString &filename)
	{
		QVector<QString> lines = QVector<QString>();
		for (QVector<Chapter>::const_iterator c = getChapters().begin(); c != getChapters().end(); ++c)
			lines.push_back(StringConverterHelper::toString(static_cast<qint64>(Math::Round((*c).getTime()->TotalSeconds * getFramesPerSecond()))));
		File::WriteAllLines(filename, lines.ToArray());
	}

	void ChapterInfo::SaveTsmuxerMeta(const QString &filename)
	{
		QString text = "--custom-" + "\r\n" + "chapters=";
		for (QVector<Chapter>::const_iterator c = getChapters().begin(); c != getChapters().end(); ++c)
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
			text += (*c).getTime()->ToString() + ";";
		text = text.substr(0, text.length() - 1);
		File::WriteAllText(filename, text);
	}

	void ChapterInfo::SaveTimecodes(const QString &filename)
	{
		QVector<QString> lines = QVector<QString>();
		for (QVector<Chapter>::const_iterator c = getChapters().begin(); c != getChapters().end(); ++c)
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
			lines.push_back((*c).getTime()->ToString());
		File::WriteAllLines(filename, lines.ToArray());
	}

	void ChapterInfo::SaveXml(const QString &filename)
	{
		Random *rndb = new Random();
		XmlTextWriter *xmlchap = new XmlTextWriter(filename, Encoding::UTF8);
		xmlchap->Formatting = Formatting::Indented;
		xmlchap->WriteStartDocument();
		xmlchap->WriteComment("<!DOCTYPE Tags SYSTEM " + "\"" + "matroskatags.dtd" + "\"" + ">");
		xmlchap->WriteStartElement("Chapters");
		xmlchap->WriteStartElement("EditionEntry");
		xmlchap->WriteElementString("EditionFlagHidden", "0");
		xmlchap->WriteElementString("EditionFlagDefault", "0");
		xmlchap->WriteElementString("EditionUID", static_cast<QString>(rndb->Next(1, int::MaxValue)));
		for (QVector<Chapter>::const_iterator c = getChapters().begin(); c != getChapters().end(); ++c)
		{
			xmlchap->WriteStartElement("ChapterAtom");
			xmlchap->WriteStartElement("ChapterDisplay");
			xmlchap->WriteElementString("ChapterString", (*c).getName());
			xmlchap->WriteElementString("ChapterLanguage", getLangCode().empty() ? "und" : getLangCode());
			xmlchap->WriteEndElement();
			xmlchap->WriteElementString("ChapterUID", static_cast<QString>(rndb->Next(1, int::MaxValue)));
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
			if ((*c).getTime()->ToString()->Length == 8)
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
				xmlchap->WriteElementString("ChapterTimeStart", (*c).getTime()->ToString() + ".0000000");
			else
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
				xmlchap->WriteElementString("ChapterTimeStart", (*c).getTime()->ToString());
			xmlchap->WriteElementString("ChapterFlagHidden", "0");
			xmlchap->WriteElementString("ChapterFlagEnabled", "1");
			xmlchap->WriteEndElement();
		}
		xmlchap->WriteEndElement();
		xmlchap->WriteEndElement();
		xmlchap->Flush();
		xmlchap->Close();
	}
}
