#include "AvsReader.h"




//using namespace System::Collections::Generic;



//using namespace System::Text;


using namespace MeXgui::core::util;

namespace MeXgui
{

    IMediaFile *AvsFileFactory::Open(const QString &file)
	{
		return AvsFile::OpenScriptFile(file);
	}

    int AvsFileFactory::HandleLevel(const QString &file)
	{
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'EndsWith' method:
		if (file.ToLower(System::Globalization::CultureInfo::InvariantCulture)->EndsWith(".avs"))
			return 10;
		return -1;
	}

    const QString &AvsFileFactory::getID() const
	{
		return "AviSynth";
	}

	AvsFile::AvsVideoReader::AvsVideoReader(AviSynthClip *clip, int width, int height)
	{
		InitializeInstanceFields();
		this->clip = clip;
		this->width = width;
		this->height = height;
	}

	const int &AvsFile::AvsVideoReader::getFrameCount() const
	{
		return this->clip->getnum_frames();
	}

	BitQMap *AvsFile::AvsVideoReader::ReadFrameBitQMap(int position)
	{
		BitQMap *bmp = new BitQMap(width, height, System::Drawing::Imaging::PixelFormat::Format24bppRgb);
		try
		{
			// Lock the bitQMap's bits.  
			Rectangle *rect = new Rectangle(0, 0, bmp->Width, bmp->Height);
			System::Drawing::Imaging::BitQMapData *bmpData = bmp->LockBits(rect, System::Drawing::Imaging::ImageLockMode::ReadWrite, bmp->PixelFormat);
			try
			{
				// Get the address of the first line.
				void* ptr = bmpData->Scan0;
				// Read data
				clip->ReadFrame(ptr, bmpData->Stride, position);
			}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
			finally
			{
				// Unlock the bits.
				bmp->UnlockBits(bmpData);
			}
			bmp->RotateFlip(RotateFlipType::Rotate180FlipX);
			return bmp;
		}
		catch (System::Runtime::InteropServices::SEHException *e1)
		{
			delete bmp;
			if (MainForm::Instance->getSettings()->getOpenAVSInThreadDuringSession())
			{
				MainForm::Instance->getSettings()->setOpenAVSInThreadDuringSession(false);
				MessageBox::Show("External AviSynth Error. As a result during this session the option \"Improved AVS opening\" in the settings is now disabled. Please disable it there completly if necessary.", "AviSynth Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
			throw;
		}
		catch (std::exception &e2)
		{
			delete bmp;
			throw;
		}
	}

	void AvsFile::AvsVideoReader::InitializeInstanceFields()
	{
		delete clip;
	}

	AvsFile::AvsAudioReader::AvsAudioReader(AviSynthClip *clip)
	{
		this->clip = clip;
	}

	const qint64 &AvsFile::AvsAudioReader::getSampleCount() const
	{
		return clip->getSamplesCount();
	}

	const bool &AvsFile::AvsAudioReader::getSupportsFastReading() const
	{
		return true;
	}

	qint64 AvsFile::AvsAudioReader::ReadAudioSamples(qint64 nStart, int nAmount, IntPtr buf)
	{
		clip->ReadAudio(buf, nStart, nAmount);
	#warning Need to check whether nAmount samples are guaranteed to be returned
		return nAmount;
	}

	unsigned char *AvsFile::AvsAudioReader::ReadAudioSamples(qint64 nStart, int nAmount)
	{
	#warning slow reading is not supported here
		return 0;
	}

	const AviSynthClip &AvsFile::getClip() const
	{
		return this->clip;
	}

    AvsFile *AvsFile::OpenScriptFile(const QString &fileName)
	{
		return new AvsFile(fileName, false);
	}

    AvsFile *AvsFile::ParseScript(const QString &scriptBody)
	{
		return new AvsFile(scriptBody, true);
	}

    AvsFile::AvsFile(const QString &script, bool parse)
	{
		InitializeInstanceFields();
		try
		{
			this->enviroment = new AviSynthScriptEnvironment();
			this->clip = parse ? enviroment->ParseScript(script, RGB24) : enviroment->OpenScriptFile(script, RGB24);

//			checked
				if (clip->getHasVideo())
				{
					quint64 width = static_cast<quint64>(clip->getVideoWidth());
					quint64 height = static_cast<quint64>(clip->getVideoHeight());
					info = new VideoInformation(clip->getHasVideo(), width, height, Dar(clip->GetIntVariable("MeXgui_darx", -1), clip->GetIntVariable("MeXgui_dary", -1), width, height), static_cast<quint64>(clip->getnum_frames()), (static_cast<double>(clip->getraten())) / (static_cast<double>(clip->getrated())), clip->getraten(), clip->getrated());
				}
				else
					info = new VideoInformation(false, 0, 0, Dar::A1x1, static_cast<quint64>(clip->getSamplesCount()), static_cast<double>(clip->getAudioSampleRate()), 0, 0);
//C# TO C++ CONVERTER TODO TASK: End of the original C# 'checked' block
		}
		catch (std::exception &e1)
		{
			cleanup();
			throw;
		}
	}

	void AvsFile::cleanup()
	{
		delay(100);
		if (this->clip != 0)
		{
			(dynamic_cast<IDisposable*>(this->clip))->Dispose();
//C# TO C++ CONVERTER WARNING: C# to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
			delete this->clip;
		}
		if (this->enviroment != 0)
		{
			(dynamic_cast<IDisposable*>(this->enviroment))->Dispose();
//C# TO C++ CONVERTER WARNING: C# to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
			delete this->enviroment;
		}
//C# TO C++ CONVERTER WARNING: There is no garbage collector in native C++:
//		GC::SuppressFinalize(this);
	}

	const VideoInformation &AvsFile::getVideoInfo() const
	{
		return info;
	}

	const bool &AvsFile::getCanReadVideo() const
	{
		return true;
	}

	const bool &AvsFile::getCanReadAudio() const
	{
		return true;
	}

	IAudioReader *AvsFile::GetAudioReader(int track)
	{
		if (track != 0 || !clip->getHasAudio())
            throw std::exception(QString::Format("Can't read audio track {0}, because it can't be found", track));
		if (audioReader == 0)
//C# TO C++ CONVERTER TODO TASK: There is no built-in support for multithreading in native C++:
			lock (this)
			{
				if (audioReader == 0)
					audioReader = new AvsAudioReader(clip);
			}
		return audioReader;
	}

	IVideoReader *AvsFile::GetVideoReader()
	{
		if (!this->getVideoInfo()->HasVideo)
			throw std::exception("Can't get Video Reader, since there is no video stream!");
		if (videoReader == 0)
//C# TO C++ CONVERTER TODO TASK: There is no built-in support for multithreading in native C++:
			lock (this)
			{
				if (videoReader == 0)
					videoReader = new AvsVideoReader(clip, static_cast<int>(getVideoInfo()->Width), static_cast<int>(getVideoInfo()->Height));
			}
		return videoReader;
	}

	AvsFile::~AvsFile()
	{
		InitializeInstanceFields();
		cleanup();
	}

	void AvsFile::InitializeInstanceFields()
	{
		delete clip;
		delete enviroment;
	}
}
