#include "AvisynthWrapper.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Runtime::InteropServices;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Runtime::Serialization;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Threading;

namespace MeGUI
{

	AviSynthException::AviSynthException(SerializationInfo *info, StreamingContext *context) : ApplicationException(info, context)
	{
	}

	AviSynthException::AviSynthException(const std::string &message) : ApplicationException(message)
	{
	}

	AviSynthException::AviSynthException() : ApplicationException()
	{
	}

	AviSynthException::AviSynthException(const std::string &message, std::exception &innerException) : ApplicationException(message, innerException)
	{
	}

	std::string AviSynthScriptEnvironment::GetLastError()
	{
		return 0;
	}

	AviSynthScriptEnvironment::AviSynthScriptEnvironment()
	{
	}

	const IntPtr &AviSynthScriptEnvironment::getHandle() const
	{
		return new void*(0);
	}

	AviSynthClip *AviSynthScriptEnvironment::OpenScriptFile(const std::string &filePath, AviSynthColorspace forceColorspace)
	{
		return new AviSynthClip("Import", filePath, forceColorspace, this);
	}

	AviSynthClip *AviSynthScriptEnvironment::ParseScript(const std::string &script, AviSynthColorspace forceColorspace)
	{
		return new AviSynthClip("Eval", script, forceColorspace, this);
	}

	AviSynthClip *AviSynthScriptEnvironment::OpenScriptFile(const std::string &filePath)
	{
		return OpenScriptFile(filePath, RGB24);
	}

	AviSynthClip *AviSynthScriptEnvironment::ParseScript(const std::string &script)
	{
		return ParseScript(script, RGB24);
	}

	AviSynthScriptEnvironment::~AviSynthScriptEnvironment()
	{

	}

	AviSynthClip::EnvRef::EnvRef(IntPtr e, int threadID)
	{
		this->env = e;
		refCount = 1;
		lockObj = new object();
		this->threadID = threadID;
	}

#if defined(dimzon)
Hashtable *AviSynthClip::_threadHash = new Hashtable();
#endif

#if defined(dimzon)
	MeGUI::AviSynthClip::EnvRef *AviSynthClip::createNewEnvRef(int threadId)
	{
		//TODO:
		return new EnvRef(new void*(0), threadId);
	}
#endif

#if defined(dimzon)
	void AviSynthClip::destroyEnvRef(EnvRef *r)
	{
		//TODO:
	}
#endif

#if defined(dimzon)
	MeGUI::AviSynthClip::EnvRef *AviSynthClip::addRef()
	{
		int threadId = Thread::CurrentThread::ManagedThreadId;
//C# TO C++ CONVERTER TODO TASK: There is no built-in support for multithreading in native C++:
		lock (_threadHash->SyncRoot)
		{
			EnvRef *r;
			if (_threadHash->ContainsKey(threadId))
			{
				r = static_cast<EnvRef*>(_threadHash[threadId]);
//C# TO C++ CONVERTER TODO TASK: There is no built-in support for multithreading in native C++:
				lock(r->lockObj)
				{
					if (0 == r->refCount)
					{
						r = createNewEnvRef(threadId);
						_threadHash->Remove(threadId);
						_threadHash->Add(threadId, r);
					}
					else
					{
						++r->refCount;
					}
				}
			}
			else
			{
				r = createNewEnvRef(threadId);
				_threadHash->Add(threadId, r);
			}
			return r;
		}
	}
#endif

#if defined(dimzon)
	void AviSynthClip::Release()
	{
		if (_avsEnv == 0)
			return;
//C# TO C++ CONVERTER TODO TASK: There is no built-in support for multithreading in native C++:
		lock (_avsEnv->lockObj)
		{
			--_avsEnv->refCount;
			if (0 == _avsEnv->refCount)
			{
				destroyEnvRef(_avsEnv);
			}
		}
//C# TO C++ CONVERTER WARNING: C# to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
		delete _avsEnv;
	}
#endif

	std::string AviSynthClip::getLastError()
	{
		const int errlen = 1024;
		StringBuilder *sb = new StringBuilder(errlen);
		sb->Length = dimzon_avs_getlasterror(_avs, sb, errlen);
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		return sb->ToString();
	}

	const bool &AviSynthClip::getHasVideo() const
	{
		return getVideoWidth() > 0 && getVideoHeight() > 0;
	}

	const int &AviSynthClip::getVideoWidth() const
	{
		return _vi.width;
	}

	const int &AviSynthClip::getVideoHeight() const
	{
		return _vi.height;
	}

	const int &AviSynthClip::getraten() const
	{
		return _vi.raten;
	}

	const int &AviSynthClip::getrated() const
	{
		return _vi.rated;
	}

	const int &AviSynthClip::getaspectn() const
	{
		return _vi.aspectn;
	}

	const int &AviSynthClip::getaspectd() const
	{
		return _vi.aspectd;
	}

	const int &AviSynthClip::getinterlaced_frame() const
	{
		return _vi.interlaced_frame;
	}

	const int &AviSynthClip::gettop_field_first() const
	{
		return _vi.top_field_first;
	}

	const int &AviSynthClip::getnum_frames() const
	{
		return _vi.num_frames;
	}

	const bool &AviSynthClip::getHasAudio() const
	{
		return _vi.num_audio_samples != 0;
	}

	const int &AviSynthClip::getAudioSampleRate() const
	{
		return _vi.audio_samples_per_second;
	}

	const long long &AviSynthClip::getSamplesCount() const
	{
		return _vi.num_audio_samples;
	}

	const AudioSampleType &AviSynthClip::getSampleType() const
	{
		return _vi.sample_type;
	}

	const short &AviSynthClip::getChannelsCount() const
	{
		return static_cast<short>(_vi.nchannels);
	}

	const AviSynthColorspace &AviSynthClip::getPixelType() const
	{
		return _vi.pixel_type;
	}

	const AviSynthColorspace &AviSynthClip::getOriginalColorspace() const
	{
		return _colorSpace;
	}

	const AudioSampleType &AviSynthClip::getOriginalSampleType() const
	{
		return _sampleType;
	}

	int AviSynthClip::GetIntVariable(const std::string &variableName, int defaultValue)
	{
		int v = 0;
		int res = 0;
		res = dimzon_avs_getintvariable(this->_avs, variableName, v);
		if (res < 0)
			throw new AviSynthException(getLastError());
		return (0 == res) ? v : defaultValue;
	}

	void AviSynthClip::ReadAudio(IntPtr addr, long long offset, int count)
	{
		if (0 != dimzon_avs_getaframe(_avs, addr, offset, count))
			throw new AviSynthException(getLastError());
	}

	void AviSynthClip::ReadAudio(unsigned char buffer, long long offset, int count)
	{
		GCHandle *h = GCHandle::Alloc(buffer,GCHandleType::Pinned);
		try
		{
			ReadAudio(h->AddrOfPinnedObject(), offset, count);
		}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
		finally
		{
			h->Free();
		}
	}

	void AviSynthClip::ReadFrame(IntPtr addr, int stride, int frame)
	{
		if (0 != dimzon_avs_getvframe(_avs, addr, stride, frame))
			throw new AviSynthException(getLastError());
	}

	AviSynthClip::AviSynthClip(const std::string &func, const std::string &arg, AviSynthColorspace forceColorspace, AviSynthScriptEnvironment *env)
	{
		_vi = AVSDLLVideoInfo();
		_avs = new void*(0);
		_colorSpace = Unknown;
		_sampleType = Unknown;
		bool bOpenSuccess = false;

		if (MainForm::Instance->getSettings()->getOpenAVSInThreadDuringSession())
		{
			MainForm::Instance->setAvsLock(MainForm::Instance->getAvsLock() + 1);

//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
			Thread *t = new Thread(new ThreadStart(delegate
			{
				System::Windows::Forms::Application::UseWaitCursor = true;
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
				if (0 == dimzon_avs_init_2(_avs, func, arg, _vi, _colorSpace, _sampleType, forceColorspace.ToString()))
					bOpenSuccess = true;
					MainForm::Instance->setAvsLock(MainForm::Instance->getAvsLock() - 1);
					if (MainForm::Instance->getAvsLock() == 0)
						System::Windows::Forms::Application::UseWaitCursor = false;
			}
		   ));
			t->Start();

			while (t->ThreadState == ThreadState::Running)
			{
				System::Windows::Forms::Application::DoEvents();
				delay(100);
			}
		}
		else
		{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
			if (0 == dimzon_avs_init_2(_avs, func, arg, _vi, _colorSpace, _sampleType, forceColorspace.ToString()))
				bOpenSuccess = true;
		}

		if (bOpenSuccess == false)
		{
			std::string err = getLastError();
			cleanup(false);
			throw new AviSynthException(err);
		}
	}

	void AviSynthClip::cleanup(bool disposing)
	{
		dimzon_avs_destroy(_avs);
		_avs = new void*(0);
		if (disposing)
//C# TO C++ CONVERTER WARNING: There is no garbage collector in native C++:
//			GC::SuppressFinalize(this);
	}

	void AviSynthClip::Finalize()
	{
		cleanup(false);
	}

	AviSynthClip::~AviSynthClip()
	{
		cleanup(true);
	}

	const short &AviSynthClip::getBitsPerSample() const
	{
		return static_cast<short>(getBytesPerSample()*8);
	}

	const short &AviSynthClip::getBytesPerSample() const
	{
		switch (getSampleType())
		{
			case INT8:
				return 1;
			case INT16:
				return 2;
			case INT24:
				return 3;
			case INT32:
				return 4;
			case FLOAT:
				return 4;
			default:
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
				throw new ArgumentException(getSampleType().ToString());
		}
	}

	const int &AviSynthClip::getAvgBytesPerSec() const
	{
		return getAudioSampleRate() * getChannelsCount() * getBytesPerSample();
	}

	const long long &AviSynthClip::getAudioSizeInBytes() const
	{
		return getSamplesCount() * getChannelsCount() * getBytesPerSample();
	}
}
