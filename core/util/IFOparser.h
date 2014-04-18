#pragma once

#include "LanguageSelectionContainer.h"
#include <QString>
#include <cmath>
#include <stdexcept>

// ****************************************************************************
// 
// Copyright (C) 2009-2012 Kurtnoise (kurtnoise@free.fr)
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
// 
// ****************************************************************************









//using namespace System::Text;



namespace MeXgui
{
	namespace core
	{
		namespace util
		{
			class IFOparser
			{
				/// <summary>
				/// Determine the IFO file that contains the menu: although it often is the largest
				/// IFO, this is not always the case, especially with elaborate DVDs with many extras.
				/// Therefore, look for the largest VOBs, and determine the IFO based on that.
				/// </summary>
				/// <param name="inputPath">Path that contains the DVD</param>
				/// <returns>Filename of the IFO that contains the movie</returns>
			public:
				static QString DetermineMovieIFO(const QString &inputPath);

				static unsigned char *GetFileBlock(const QString &strFile, qint64 pos, int count);

				static short ToInt16(unsigned char bytes[]);
			private:
				static unsigned int ToInt32(unsigned char bytes[]);
				static short ToShort(unsigned char bytes[]);
			public:
				static qint64 ToFilePosition(unsigned char bytes[]);

			private:
				static qint64 GetTotalFrames(TimeSpan *time, int fps);

				static QString TwoLong(int val);

				static int AsHex(int val);

				static Nullable<short> GetFrames(unsigned char val);

				static int GetFrames(TimeSpan *time, int fps);

			public:
				static qint64 GetPCGIP_Position(const QString &ifoFile);

				static int GetProgramChains(const QString &ifoFile, qint64 pcgitPosition);

				static unsigned int GetChainOffset(const QString &ifoFile, qint64 pcgitPosition, int programChain);

				static int GetNumberOfPrograms(const QString &ifoFile, qint64 pcgitPosition, unsigned int chainOffset);

				static Nullable<TimeSpan*> ReadTimeSpan(const QString &ifoFile, qint64 pcgitPosition, unsigned int chainOffset, double &fps);

				static Nullable<TimeSpan*> ReadTimeSpan(unsigned char playbackBytes[], double &fps);

				/// <summary>
				/// get Audio Language from the IFO file
				/// </summary>
				/// <param name="fileName">name of the IFO file</param>
				/// <param name="count">the audio stream number</param>
				/// <returns>Language as String</returns>
				static QString getAudioLanguage(const QString &FileName, int count);

				/// <summary>
				/// get several Subtitles Informations from the IFO file
				/// </summary>
				/// <param name="fileName">name of the IFO file</param>
				/// <returns>several infos as String</returns>       
				static QString *GetSubtitlesStreamsInfos(const QString &FileName, int iPGC, bool bGetAllStreams);

				/// <summary>
				/// get number of PGCs
				/// </summary>
				/// <param name="fileName">name of the IFO file</param>
				/// <returns>number of PGS as unsigned integer</returns>
				static unsigned int getPGCnb(const QString &FileName);

			private:
				static unsigned int ReadUInt32(BinaryReader *br);

				/// <summary>
				/// get Aspect Ratio Video Information from the IFO file
				/// </summary>
				/// <param name="fileName">name of the IFO file</param>
				/// <returns>aspect ratio info as String</returns>
			public:
				static QString GetVideoAR(const QString &FileName);
			};
		}
	}
}
