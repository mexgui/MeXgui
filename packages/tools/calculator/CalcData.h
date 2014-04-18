#pragma once

#include "core/details/CodecManager.h"
#include "core/details/Streams.h"
#include "core/util/FileSize.h"
#include <QString>
#include <QMap>
#include <cmath>

// ****************************************************************************
// 
// Copyright (C) 2005-2012 Doom9 & al
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




//using namespace System::Collections::Generic;

//using namespace System::Text;


using namespace MeXgui::core::util;
using namespace MeXgui::core::details;

//using namespace System::Diagnostics;
using namespace eac3to;
using namespace MeXgui::Properties;

namespace MeXgui
{
	namespace packages
	{
		namespace tools
		{
			namespace calculator
			{
				class CalcData
				{
				private:
					static const decimal mp4OverheadWithBframes;
					static const decimal mp4OverheadWithoutBframes;
					static const decimal aviVideoOverhead;
					static const decimal cbrMP3Overhead;
					static const decimal vbrMP3Overhead;
					static const decimal ac3Overhead;
					static const int AACBlockSize = 1024;
					static const int AC3BlockSize = 1536;
					static const int MP3BlockSize = 1152;
					static const int VorbisBlockSize = 1024;
					static const int mkvAudioTrackHeaderSize = 140;
					static const int mkvVorbisTrackHeaderSize = 4096;
					static const unsigned int mkvIframeOverhead = 26;
					static const unsigned int mkvPframeOverhead = 13;
					static const unsigned int mkvBframeOverhead = 16;
					static const QString qualityCodecModifierValues;

				public:
//C# TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++0x:
//ORIGINAL LINE: public CalcData(long frames, decimal fps) : this(frames, fps, nullptr, nullptr, false, nullptr)
					CalcData(qint64 frames, decimal fps);

					CalcData(qint64 frames, decimal fps, MeXgui::ContainerType *container, MeXgui::VideoCodec *codec, bool bframes, AudioBitrateCalculationStream audios[]);

							private:
								MeXgui::ContainerType *privateContainerType;
							public:
								const MeXgui::ContainerType &getContainerType() const;
								void setContainerType(const MeXgui::ContainerType &value);
							private:
								MeXgui::VideoCodec *privateVideoCodec;
							public:
								const MeXgui::VideoCodec &getVideoCodec() const;
								void setVideoCodec(const MeXgui::VideoCodec &value);
							private:
//ORIGINAL LINE: private AudioBitrateCalculationStream[] privateAudioStreams;
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
								AudioBitrateCalculationStream *privateAudioStreams;
							public:
								const AudioBitrateCalculationStream *getAudioStreams() const;
								void setAudioStreams(AudioBitrateCalculationStream value[]);
							private:
								bool privateHasBFrames;
							public:
								const bool &getHasBFrames() const;
								void setHasBFrames(const bool &value);
							private:
								decimal privateFramesPerSecond;
							public:
								const decimal &getFramesPerSecond() const;
								void setFramesPerSecond(const decimal &value);
							private:
								qint64 privateFrames;
							public:
								const qint64 &getFrames() const;
								void setFrames(const qint64 &value);
							private:
								Size *privateFrameSize;
							public:
								const Size &getFrameSize() const;
								void setFrameSize(const Size &value);
							private:
								float privateBitsPerPixel;
							public:
								const float &getBitsPerPixel() const;
								void setBitsPerPixel(const float &value);

							private:
								float privateQualityCodecModifier;
							public:
								const float &getQualityCodecModifier() const;
								void setQualityCodecModifier(const float &value);
							private:
								float privateQualityCoeffient;
							public:
								const float &getQualityCoeffient() const;
								void setQualityCoeffient(const float &value);
							private:
								float privateQualityEstimate;
							public:
								const float &getQualityEstimate() const;
								void setQualityEstimate(const float &value);

							private:
								FileSize privateVideoOverhead;
							public:
								const FileSize &getVideoOverhead() const;
								void setVideoOverhead(const FileSize &value);
							private:
								FileSize privateAudioOverhead;
							public:
								const FileSize &getAudioOverhead() const;
								void setAudioOverhead(const FileSize &value);
							private:
								FileSize privateExtraOverhead;
							public:
								const FileSize &getExtraOverhead() const;
								void setExtraOverhead(const FileSize &value);

							private:
								float privateVideoOverheadRatio;
							public:
								const float &getVideoOverheadRatio() const;
								void setVideoOverheadRatio(const float &value);
							private:
								float privateAudioOverheadRatio;
							public:
								const float &getAudioOverheadRatio() const;
								void setAudioOverheadRatio(const float &value);
							private:
								float privateExtraOverheadRatio;
							public:
								const float &getExtraOverheadRatio() const;
								void setExtraOverheadRatio(const float &value);

							private:
								FileSize privateExtraSize;
							public:
								const FileSize &getExtraSize() const;
								void setExtraSize(const FileSize &value);
							private:
								FileSize privateVideoSize;
							public:
								const FileSize &getVideoSize() const;
								void setVideoSize(const FileSize &value);
							private:
								FileSize privateAudioSize;
							public:
								const FileSize &getAudioSize() const;
								void setAudioSize(const FileSize &value);
							private:
								FileSize privateTotalSize;
							public:
								const FileSize &getTotalSize() const;
								void setTotalSize(const FileSize &value);

					const decimal &getVideoBitrate() const;
					void setVideoBitrate(const decimal &value);

					const decimal &getTotalSeconds() const;
					const FileSize &getVideoMuxSize() const;
					const FileSize &getAudioMuxSize() const;
					const FileSize &getExtraMuxSize() const;

					void CalcByTotalSize();

					void CalcByVideoSize();

					void CalcByBitsPerPixel();

					void CalcByQualityEstimate();

				private:
					void CalcBitsPerPixel();

					void CalcQualityEstimate();

					void CalcQualityCodecModifier();

					void CalcVideoOverhead();

					/// <summary>
					/// gets the video overhead in the m2ts container
					/// </summary>
					/// <param name="iAudioStreamCount">audio stream count</param>
					/// <returns>overhead this video track will incurr</returns>
					qint64 GetM2tsVideoOverhead(int iAudioStreamCount);

					void CalcAudioOverheadAndSize();

					void CalcExtraOverhead();

					/// <summary>
					/// gets the overhead a given audio type will incurr in the matroska container
					/// given its length and sampling rate
					/// </summary>
					/// <param name="AudioType">type of the audio track</param>
					/// <param name="samplingRate">sampling rate of the audio track</param>
					/// <param name="length">length of the audio track</param>
					/// <returns>overhead this audio track will incurr</returns>
					static int GetMkvAudioOverhead(AudioType *audioType, int samplingRate, double length);

					/// <summary>
					/// gets the overhead a given audio type will incurr in the m2ts container
					/// </summary>
					/// <param name="AudioType">type of the audio track</param>
					/// <param name="lFrames">frames of the video track</param>
					/// <param name="length">length of the audio track</param>
					/// <param name="lFileSize">size of the audio track</param>
					/// <param name="bVideoHandling">true if video will also be muxed</param>
					/// <returns>overhead this audio track will incurr</returns>
					static int GetM2tsAudioOverhead(AudioType *audioType, qint64 lFrames, quint64 length, quint64 lFileSize, bool bVideohandling);

					/// <summary>
					/// gets the avi container overhead for the given audio type and bitrate mode
					/// bitrate mode only needs to be taken into account for MP3 but it's there for all cases nontheless
					/// </summary>
					/// <param name="AudioType">the type of audio</param>
					/// <param name="bitrateMode">the bitrate mode of the given audio type</param>
					/// <returns>the overhead in bytes per frame</returns>
					static decimal GetAviAudioOverhead(AudioType *audioType);
				};
			}
		}
	}
}
