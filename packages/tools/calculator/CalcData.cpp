#include "CalcData.h"




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

const decimal CalcData::mp4OverheadWithBframes = 10.4;
const decimal CalcData::mp4OverheadWithoutBframes = 4.3;
const decimal CalcData::aviVideoOverhead = 24;
const decimal CalcData::cbrMP3Overhead = 23.75;
const decimal CalcData::vbrMP3Overhead = 40;
const decimal CalcData::ac3Overhead = 23.75;
const QString CalcData::qualityCodecModifierValues = "MPEG2=1.022,ASP=1.018,AVC=1.0,VC1=1.004";

				CalcData::CalcData(qint64 frames, decimal fps)
				{
				}

				CalcData::CalcData(qint64 frames, decimal fps, MeXgui::ContainerType *container, MeXgui::VideoCodec *codec, bool bframes, AudioBitrateCalculationStream audios[])
				{
					if (fps <= 0)
						throw new ArgumentException("Frames per second must be greater than zero.", "fps");
					if (frames <= 0)
						throw new ArgumentException("Frames must be greater than zero.", "frames");

					setFrames(frames);
					setFramesPerSecond(fps);
					setContainerType(container);
					setVideoCodec(codec);
					setHasBFrames(bframes);
					setAudioStreams(audios);
					setVideoOverheadRatio(1);
					setAudioOverheadRatio(1);
					setExtraOverheadRatio(1);
					setQualityCoeffient(0.75F);
				}

				const MeXgui::ContainerType &CalcData::getContainerType() const
				{
					return privateContainerType;
				}

				void CalcData::setContainerType(const MeXgui::ContainerType &value)
				{
					privateContainerType = value;
				}

				const MeXgui::VideoCodec &CalcData::getVideoCodec() const
				{
					return privateVideoCodec;
				}

				void CalcData::setVideoCodec(const MeXgui::VideoCodec &value)
				{
					privateVideoCodec = value;
				}

				const AudioBitrateCalculationStream &CalcData::getAudioStreams() const
				{
					return privateAudioStreams;
				}

				void CalcData::setAudioStreams(const AudioBitrateCalculationStream &value[])
				{
					privateAudioStreams = value;
				}

				const bool &CalcData::getHasBFrames() const
				{
					return privateHasBFrames;
				}

				void CalcData::setHasBFrames(const bool &value)
				{
					privateHasBFrames = value;
				}

				const decimal &CalcData::getFramesPerSecond() const
				{
					return privateFramesPerSecond;
				}

				void CalcData::setFramesPerSecond(const decimal &value)
				{
					privateFramesPerSecond = value;
				}

				const qint64 &CalcData::getFrames() const
				{
					return privateFrames;
				}

				void CalcData::setFrames(const qint64 &value)
				{
					privateFrames = value;
				}

				const Size &CalcData::getFrameSize() const
				{
					return privateFrameSize;
				}

				void CalcData::setFrameSize(const Size &value)
				{
					privateFrameSize = value;
				}

				const float &CalcData::getBitsPerPixel() const
				{
					return privateBitsPerPixel;
				}

				void CalcData::setBitsPerPixel(const float &value)
				{
					privateBitsPerPixel = value;
				}

				const float &CalcData::getQualityCodecModifier() const
				{
					return privateQualityCodecModifier;
				}

				void CalcData::setQualityCodecModifier(const float &value)
				{
					privateQualityCodecModifier = value;
				}

				const float &CalcData::getQualityCoeffient() const
				{
					return privateQualityCoeffient;
				}

				void CalcData::setQualityCoeffient(const float &value)
				{
					privateQualityCoeffient = value;
				}

				const float &CalcData::getQualityEstimate() const
				{
					return privateQualityEstimate;
				}

				void CalcData::setQualityEstimate(const float &value)
				{
					privateQualityEstimate = value;
				}

				const MeXgui::core::util::FileSize &CalcData::getVideoOverhead() const
				{
					return privateVideoOverhead;
				}

				void CalcData::setVideoOverhead(const FileSize &value)
				{
					privateVideoOverhead = value;
				}

				const MeXgui::core::util::FileSize &CalcData::getAudioOverhead() const
				{
					return privateAudioOverhead;
				}

				void CalcData::setAudioOverhead(const FileSize &value)
				{
					privateAudioOverhead = value;
				}

				const MeXgui::core::util::FileSize &CalcData::getExtraOverhead() const
				{
					return privateExtraOverhead;
				}

				void CalcData::setExtraOverhead(const FileSize &value)
				{
					privateExtraOverhead = value;
				}

				const float &CalcData::getVideoOverheadRatio() const
				{
					return privateVideoOverheadRatio;
				}

				void CalcData::setVideoOverheadRatio(const float &value)
				{
					privateVideoOverheadRatio = value;
				}

				const float &CalcData::getAudioOverheadRatio() const
				{
					return privateAudioOverheadRatio;
				}

				void CalcData::setAudioOverheadRatio(const float &value)
				{
					privateAudioOverheadRatio = value;
				}

				const float &CalcData::getExtraOverheadRatio() const
				{
					return privateExtraOverheadRatio;
				}

				void CalcData::setExtraOverheadRatio(const float &value)
				{
					privateExtraOverheadRatio = value;
				}

				const MeXgui::core::util::FileSize &CalcData::getExtraSize() const
				{
					return privateExtraSize;
				}

				void CalcData::setExtraSize(const FileSize &value)
				{
					privateExtraSize = value;
				}

				const MeXgui::core::util::FileSize &CalcData::getVideoSize() const
				{
					return privateVideoSize;
				}

				void CalcData::setVideoSize(const FileSize &value)
				{
					privateVideoSize = value;
				}

				const MeXgui::core::util::FileSize &CalcData::getAudioSize() const
				{
					return privateAudioSize;
				}

				void CalcData::setAudioSize(const FileSize &value)
				{
					privateAudioSize = value;
				}

				const MeXgui::core::util::FileSize &CalcData::getTotalSize() const
				{
					return privateTotalSize;
				}

				void CalcData::setTotalSize(const FileSize &value)
				{
					privateTotalSize = value;
				}

				const decimal &CalcData::getVideoBitrate() const
				{
					return static_cast<decimal>(getVideoSize().getBytes()) / 1000 / getTotalSeconds() * 8;
				}

				void CalcData::setVideoBitrate(const decimal &value)
				{
					setVideoSize(FileSize(static_cast<quint64>(getTotalSeconds() * value * 1000 / 8)));
				}

				const decimal &CalcData::getTotalSeconds() const
				{
					return static_cast<decimal>(getFrames()) / static_cast<decimal>(getFramesPerSecond());
				}

				const MeXgui::core::util::FileSize &CalcData::getVideoMuxSize() const
				{
					return FileSize(static_cast<quint64>(static_cast<float>(getVideoSize().getBytes()) * getVideoOverheadRatio()) + getVideoOverhead().getBytes());
				}

				const MeXgui::core::util::FileSize &CalcData::getAudioMuxSize() const
				{
					return FileSize(static_cast<quint64>(static_cast<float>(getAudioSize().getBytes()) * getAudioOverheadRatio()) + getAudioOverhead().getBytes());
				}

				const MeXgui::core::util::FileSize &CalcData::getExtraMuxSize() const
				{
					return FileSize(static_cast<quint64>(static_cast<float>(getExtraSize().getBytes()) * getExtraOverheadRatio()) + getExtraOverhead().getBytes());
				}

				void CalcData::CalcByTotalSize()
				{
					CalcVideoOverhead();
					CalcAudioOverheadAndSize();
					CalcExtraOverhead();
					CalcQualityCodecModifier();
					setVideoSize(FileSize(static_cast<quint64>(static_cast<float>(getTotalSize().getBytes()) / getVideoOverheadRatio())) - getAudioMuxSize() - getExtraMuxSize() - getVideoOverhead());
					CalcBitsPerPixel();
					CalcQualityEstimate();
				}

				void CalcData::CalcByVideoSize()
				{
					CalcVideoOverhead();
					CalcAudioOverheadAndSize();
					CalcExtraOverhead();
					CalcQualityCodecModifier();
					setTotalSize(getVideoMuxSize() + getAudioMuxSize() + getExtraMuxSize());
					CalcBitsPerPixel();
					CalcQualityEstimate();
				}

				void CalcData::CalcByBitsPerPixel()
				{
					CalcVideoOverhead();
					CalcAudioOverheadAndSize();
					CalcExtraOverhead();
					CalcQualityCodecModifier();
					setVideoSize(FileSize(static_cast<quint64>((getBitsPerPixel() / 8 * static_cast<float>(getFrameSize()->Width * getFrameSize()->Height) * getFrames() / getVideoOverheadRatio())) - getVideoOverhead().getBytes()));
					setTotalSize(getVideoMuxSize() + getAudioMuxSize() + getExtraMuxSize());
					CalcQualityEstimate();
				}

				void CalcData::CalcByQualityEstimate()
				{
					CalcVideoOverhead();
					CalcAudioOverheadAndSize();
					CalcExtraOverhead();
					CalcQualityCodecModifier();
					setVideoBitrate(static_cast<decimal>(getQualityEstimate()) * (static_cast<decimal>(pow(static_cast<float>(getFrameSize()->Width * getFrameSize()->Height), getQualityCoeffient() * getQualityCodecModifier())) * getFramesPerSecond()) / 1000);
					setTotalSize(getVideoMuxSize() + getAudioMuxSize() + getExtraMuxSize());
					CalcBitsPerPixel();
				}

				void CalcData::CalcBitsPerPixel()
				{
					setBitsPerPixel(static_cast<float>(getVideoSize().getBytes()) * 8 / static_cast<float>(getFrames()) / static_cast<float>(getFrameSize()->Width * getFrameSize()->Height));
				}

				void CalcData::CalcQualityEstimate()
				{
					setQualityEstimate(static_cast<float>(getVideoBitrate()) / (static_cast<float>(pow(static_cast<float>(getFrameSize()->Width * getFrameSize()->Height), getQualityCoeffient() * getQualityCodecModifier())) * static_cast<float>(getFramesPerSecond())) * 1000);
				}

				void CalcData::CalcQualityCodecModifier()
				{
					QMap<QString, float> *qualityCodecModifiers = QMap<QString, float>();

					// read the values into the dictionary
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Split' method:
					for (unknown::const_iterator mod = qualityCodecModifierValues.Split(',').begin(); mod != qualityCodecModifierValues.Split(',').end(); ++mod)
					{
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Split' method:
						qualityCodecModifiers->Add((*mod).Split('=')[0], float::Parse((*mod).Split('=')[1], System::Globalization::CultureInfo::InvariantCulture));
					}

					// use values when found in dictionary, otherwise default to no-modification
					if (qualityCodecModifiers->ContainsKey(getVideoCodec()->getID()))
						setQualityCodecModifier(qualityCodecModifiers[getVideoCodec()->getID()]);
					else
						setQualityCodecModifier(1);
				}

				void CalcData::CalcVideoOverhead()
				{
					setVideoOverheadRatio(1);

					if (getContainerType() == getContainerType()->MP4)
					{
						setVideoOverhead(FileSize(B, (getHasBFrames() ? mp4OverheadWithBframes : mp4OverheadWithoutBframes) * getFrames()));
					}
					else if (getContainerType() == getContainerType()->MKV)
					{
						qint64 nbIframes = getFrames() / 10;
						qint64 nbBframes = getHasBFrames() ? (getFrames() - nbIframes) / 2 : 0;
						qint64 nbPframes = getFrames() - nbIframes - nbBframes;
						setVideoOverhead(FileSize(B, (4300 + 1400 + nbIframes * mkvIframeOverhead + nbPframes * mkvPframeOverhead + nbBframes * mkvBframeOverhead + getTotalSeconds() * 12 / 2))); // this line for 12 bytes per cluster overhoad
					}
					else if (getContainerType() == getContainerType()->AVI)
					{
						setVideoOverhead(FileSize(B, getFrames() * aviVideoOverhead));
					}
					else if (getContainerType() == getContainerType()->M2TS)
					{
						setVideoOverhead(FileSize(B, GetM2tsVideoOverhead(sizeof(getAudioStreams()) / sizeof(getAudioStreams()[0]))));
					}
				}

				qint64 CalcData::GetM2tsVideoOverhead(int iAudioStreamCount)
				{
					if (iAudioStreamCount == 0)
					{
						setVideoOverheadRatio(1.06f);
						return 0;
					}
					qint64 videoOverhead = 0;
					qint64 videoSize = static_cast<qint64>(getVideoBitrate()) * static_cast<qint64>(getTotalSeconds()); //videoOverhead+generalOverhead+rawVideo
					int packageSize = 192;
					int packageFill = 184; //of 192
					qint64 packageCount = videoSize / packageSize + 1;
					qint64 packageOverhead = packageCount * (packageSize - packageFill);
					videoOverhead += packageOverhead;
					return videoOverhead;
				}

				void CalcData::CalcAudioOverheadAndSize()
				{
					setAudioOverheadRatio(1);
					setAudioSize(FileSize::Empty);
					setAudioOverhead(FileSize::Empty);

//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++0x inferred typing option is selected:
					for (MeXgui::core::details::AudioBitrateCalculationStream::const_iterator audio = getAudioStreams()->begin(); audio != getAudioStreams()->end(); ++audio)
					{
						setAudioSize(getAudioSize() + ((((*audio)->Size) != 0) ? (*audio)->Size : FileSize::Empty));

						if (getContainerType() == getContainerType()->MKV)
							setAudioOverhead(getAudioOverhead() + FileSize(B, GetMkvAudioOverhead((*audio)->AType, 48000, static_cast<double>(getTotalSeconds()))));
						else if (getContainerType() == getContainerType()->M2TS)
							setAudioOverhead(getAudioOverhead() + FileSize(B, GetM2tsAudioOverhead((*audio)->AType, getFrames(), static_cast<quint64>(getTotalSeconds()), (*audio)->Size->Value->Bytes, true)));
						else if (getContainerType() == getContainerType()->AVI)
							setAudioOverhead(getAudioOverhead() + FileSize(B, GetAviAudioOverhead((*audio)->AType) * getFrames()));
					}
				}

				void CalcData::CalcExtraOverhead()
				{
					if (getContainerType() == getContainerType()->M2TS)
						setExtraOverheadRatio(2);
					else
						setExtraOverheadRatio(1);
				}

				int CalcData::GetMkvAudioOverhead(AudioType *audioType, int samplingRate, double length)
				{
					if (audioType == 0)
						return 0;
					qint64 nbSamples = static_cast<qint64>(static_cast<double>(samplingRate) * length);
					int headerSize = mkvAudioTrackHeaderSize;
					int samplesPerBlock = 0;
					if (audioType == AudioType::MP4AAC || audioType == AudioType::M4A || audioType == AudioType::RAWAAC)
						samplesPerBlock = AACBlockSize;
					else if (audioType == AudioType::VBRMP3 || audioType == AudioType::CBRMP3 || audioType == AudioType::MP3 || audioType == AudioType::DTS)
						samplesPerBlock = MP3BlockSize;
					else if (audioType == AudioType::AC3)
						samplesPerBlock = AC3BlockSize;
					else if (audioType == AudioType::VORBIS)
					{
						samplesPerBlock = VorbisBlockSize;
						headerSize = mkvVorbisTrackHeaderSize;
					}
					else // unknown types..
					{
						samplesPerBlock = AC3BlockSize;
					}
					double blockOverhead = static_cast<double>(nbSamples) / static_cast<double>(samplesPerBlock) * 22.0 / 8.0;
					int overhead = static_cast<int>(headerSize + 5 * length + blockOverhead);
					return overhead;
				}

				int CalcData::GetM2tsAudioOverhead(AudioType *audioType, qint64 lFrames, quint64 length, quint64 lFileSize, bool bVideohandling)
				{
					if (audioType == AudioType::DTS || audioType == AudioType::DTSHD || audioType == AudioType::DTSMA)
					{
						// formula based on http://forum.doom9.org/showpost.php?p=1484281&postcount=141
						int packageSize = 192;
						quint64 audioOverhead = 0;
						double packageFill = 184.0;
						quint64 dtsRawsize = lFileSize;
						quint64 hdRawsize = 0;
						int averageBitrate = static_cast<int>(lFileSize / length) + 1;
						quint64 hdOverhead = 0;
						if (averageBitrate > 194000)
						{
							dtsRawsize = static_cast<quint64>(192000 * length);
							hdRawsize = (static_cast<quint64>(averageBitrate) - 192000) * length;
							if (hdRawsize > 0)
							{
								hdOverhead = hdRawsize * static_cast<quint64>(packageSize) / static_cast<quint64>(packageFill) + length * 1024 * 10 - hdRawsize;
							}
						}
						quint64 dtsMult = 1147;
						audioOverhead = dtsMult * static_cast<quint64>(packageSize) * length - dtsRawsize;
						audioOverhead += hdOverhead;
						return static_cast<int>(audioOverhead);
					}
					else
					{
						//// formula based on http://forum.doom9.org/showpost.php?p=1473477&postcount=18
						//int blocksize = 80;
						//if (audioType == AudioType.AC3 || audioType == AudioType.THD|| audioType == AudioType.PCM)
						//{
						//    blocksize = 907;
						//}
						//int audioOverhead = (int)((2 * blocksize) / 180.0 * 8.0 + 17.0 + 0.5) * ((int)(lFileSize * 1.0 / (blocksize * 1.0) + 0.5));
						//if (bVideohandling)
						//{
						//    double audiobitrate = lFileSize / length;
						//    audioOverhead += (int)lFrames * (262 + ((int)audiobitrate / 184 + 1)) + 9412;
						//}
						//return audioOverhead;

						// formula based on http://forum.doom9.org/showpost.php?p=1488863&postcount=162
						int packageSize = 192;
						quint64 audioOverhead = 0;
						double packageFill = 184.0;
						int pesOverhead = 17;
						quint64 ac3RawSize = lFileSize;
						quint64 hdRawSize = 0;
						int averageBitrate = static_cast<int>(lFileSize / length) + 1;
						if (averageBitrate > 88000)
						{
							ac3RawSize = 80000 * length;
							hdRawSize = (static_cast<quint64>(averageBitrate) - 80000) * length;
							averageBitrate = 80000;
						}
						int audioPackageSizePerSecond = averageBitrate / 250 + 1; // = averageBitrate*8/1000/2
						int effectiveAudioPackagePerSecond = audioPackageSizePerSecond + pesOverhead;
						int containerPackagesCountPerAudioPackagePerSecond = static_cast<int>(effectiveAudioPackagePerSecond / packageFill) + 1;
						int containerPackageSizePerAudioPackagePerSecond = packageSize * containerPackagesCountPerAudioPackagePerSecond;
						audioOverhead = ac3RawSize * static_cast<quint64>(containerPackageSizePerAudioPackagePerSecond) / static_cast<quint64>(audioPackageSizePerSecond) - ac3RawSize;
						quint64 hdOverhead = 0;
						if (hdRawSize > 0)
						{
							hdOverhead = hdRawSize * static_cast<quint64>(packageSize / packageFill) + length * 1024 * 10 - hdRawSize;
						}
						audioOverhead += hdOverhead;
						if (bVideohandling)
						{
							double audiobitrate = lFileSize / length;
							audioOverhead += static_cast<quint64>(lFrames) * (262 + (static_cast<quint64>(audiobitrate / 184) + 1)) + 9412;
						}
						return static_cast<int>(audioOverhead);
					}
				}

				decimal CalcData::GetAviAudioOverhead(AudioType *audioType)
				{
					if (audioType == AudioType::AC3)
						return ac3Overhead;
					else if (audioType == AudioType::MP3)
						return vbrMP3Overhead;
					else if (audioType == AudioType::VBRMP3)
						return vbrMP3Overhead;
					else if (audioType == AudioType::CBRMP3)
						return cbrMP3Overhead;
					else if (audioType == AudioType::RAWAAC)
						return vbrMP3Overhead;
					else if (audioType == AudioType::DTS)
						return ac3Overhead;
					else
						return 0;
				}
			}
		}
	}
}