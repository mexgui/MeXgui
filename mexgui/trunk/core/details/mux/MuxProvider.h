#pragma once

#include "core/details/CodecManager.h"
#include "core/gui/MeGUI.MainForm.h"
#include "MuxPathComparer.h"
#include "core/plugins/interfaces/IMuxing.h"
#include "core/util/GenericRegisterer.h"
#include "core/details/MeGUISettings.h"
#include "core/plugins/interfaces/IJobProcessor.h"
#include "MuxPath.h"
#include "packages/muxer/mp4box/MP4BoxMuxer.h"
#include "packages/muxer/mkvmerge/MkvMergeMuxer.h"
#include "packages/muxer/avimuxgui/AMGMuxer.h"
#include "packages/muxer/tsmuxer/tsMuxeR.h"
#include "core/util/VideoUtil.h"
#include "packages/audio/AudioEncoderInterface.h"
#include "packages/video/xvid/XviDEncoder.h"
#include "packages/video/x264/x264Encoder.h"
#include <string>
#include <vector>
#include <algorithm>

// ****************************************************************************
// 
// Copyright (C) 2005-2013 Doom9 & al
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

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;

namespace MeGUI
{
	enum MuxerType
	{
		MP4BOX,
		MKVMERGE,
		AVIMUXGUI,
		TSMUXER
	};
	class MuxableType
	{
	public:
		OutputType *outputType;
		ICodec *codec;
		MuxableType(OutputType *type, ICodec *codec);
	};
	class MuxProvider
	{
	private:
		MainForm *mainForm;
		MuxPathComparer *comparer;
		VideoEncoderProvider *vProvider;
		AudioEncoderProvider *aProvider;
	public:
		MuxProvider(MainForm *mainForm);

		IMuxing *GetMuxer(MuxerType type);

		IJobProcessor *GetMuxer(MuxerType type, MeGUISettings *settings);


		/// <summary>
		/// Finds the best mux path and the output types the encoders should produce
		/// </summary>
		/// <param name="videoCodec"></param>
		/// <param name="audioCodecs"></param>
		/// <param name="containerType"></param>
		/// <param name="dictatedTypes"></param>
		/// <returns></returns>
//ORIGINAL LINE: public MuxPath GetMuxPath(VideoEncoderType videoCodec, AudioEncoderType[] audioCodecs, ContainerType containerType, params MuxableType[] dictatedTypes)
//C# TO C++ CONVERTER TODO TASK: Use 'va_start', 'va_arg', and 'va_end' to access the parameter array within this method:
		MuxPath *GetMuxPath(VideoEncoderType *videoCodec, AudioEncoderType audioCodecs[], ContainerType *containerType, ...);

		/// <summary>
		/// Finds the best mux path
		/// </summary>
		/// <param name="containerType"></param>
		/// <param name="allTypes"></param>
		/// <returns></returns>
//ORIGINAL LINE: public MuxPath GetMuxPath(ContainerType containerType, bool alwaysMux, params MuxableType[] allTypes)
//C# TO C++ CONVERTER TODO TASK: Use 'va_start', 'va_arg', and 'va_end' to access the parameter array within this method:
		MuxPath *GetMuxPath(ContainerType *containerType, bool alwaysMux, ...);

//ORIGINAL LINE: public bool CanBeMuxed(ContainerType containerType, params MuxableType[] allTypes)
//C# TO C++ CONVERTER TODO TASK: Use 'va_start', 'va_arg', and 'va_end' to access the parameter array within this method:
		bool CanBeMuxed(ContainerType *containerType, ...);

//ORIGINAL LINE: public bool CanBeMuxed(VideoEncoderType codec, AudioEncoderType[] audioCodecs, ContainerType containerType, params MuxableType[] decidedTypes)
//C# TO C++ CONVERTER TODO TASK: Use 'va_start', 'va_arg', and 'va_end' to access the parameter array within this method:
		bool CanBeMuxed(VideoEncoderType *codec, AudioEncoderType audioCodecs[], ContainerType *containerType, ...);

		std::vector<ContainerType*> GetSupportedContainers();

		std::vector<DeviceType*> GetSupportedDevices(ContainerType *oType);

		/// <summary>
		/// gets all the containers that can be supported given the video and a list of audio types
		/// this is used to limit the container dropdown in the autoencode window
		/// </summary>
		/// <param name="videoType">the desired video type</param>
		/// <param name="audioTypes">the desired audio types</param>
		/// <returns>a list of containers that can be supported</returns>
//ORIGINAL LINE: public List<ContainerType> GetSupportedContainers(params MuxableType[] inputTypes)
//C# TO C++ CONVERTER TODO TASK: Use 'va_start', 'va_arg', and 'va_end' to access the parameter array within this method:
		std::vector<ContainerType*> GetSupportedContainers(...);

//ORIGINAL LINE: public List<ContainerType> GetSupportedContainers(VideoEncoderType videoCodec, AudioEncoderType[] audioCodecs, params MuxableType[] dictatedOutputTypes)
//C# TO C++ CONVERTER TODO TASK: Use 'va_start', 'va_arg', and 'va_end' to access the parameter array within this method:
		std::vector<ContainerType*> GetSupportedContainers(VideoEncoderType *videoCodec, AudioEncoderType audioCodecs[], ...);

		/// <summary>
		/// Finds the best mux path if some of the inputs have not yet been
		/// produced (they are yet to be encoded). When this is the case,
		/// there is more flexibility, as some encoders can produce outputs
		/// in multiple formats. This function suggests the output formats
		/// they should produce as well as the mux path.
		/// </summary>
		/// <param name="undecidedInputs">List of encoder types for the inputs which have not yet been encoded</param>
		/// <param name="decidedInputs">List of file types for the inputs which are already encoded</param>
		/// <param name="containerType">Target container type</param>
		/// <returns></returns>
	private:
		MuxPath *findBestMuxPathAndConfig(std::vector<IEncoderType*> &undecidedInputs, std::vector<MuxableType*> &decidedInputs, ContainerType *containerType);

		/// <summary>
		/// Given a mux path in which all the inputs have already been handled,
		/// this finds the shortest mux path to achieve the desired container type.
		/// </summary>
		/// <param name="currentMuxPath"></param>
		/// <param name="remainingMuxers">List of muxers which haven't yet been used
		/// in this final stage. There's no point having a muxer twice in this final
		/// stage, as the output of the second time could substitute the output of 
		/// the first time.</param>
		/// <param name="desiredContainerType"></param>
		/// <returns></returns>
		MuxPath *getShortestMuxPath(MuxPath *currentMuxPath, std::vector<IMuxing*> &remainingMuxers, ContainerType *desiredContainerType);

		/// <summary>
		/// Step in the recursive stage which chooses, of all the MuxableTypes which
		/// *could* be handled, whether they should be. That means, it generates a
		/// mux path which involves muxing in each of the 2^n combinations of inputs
		/// at this stage. 
		/// 
		/// I'm not sure if this step is actually necessary. The only possible
		/// use I can think of is if you have a specific muxpath rule which says
		/// that only one file can be muxed in at a time, or only some specific
		/// combination of files can be muxed in at a time.
		///           -- berrinam
		/// </summary>
		/// <param name="currentMuxPath"></param>
		/// <param name="muxer"></param>
		/// <param name="decidedHandledTypes"></param>
		/// <param name="undecidedPossibleHandledTypes"></param>
		/// <param name="unhandledInputTypes"></param>
		/// <param name="desiredContainerType"></param>
		/// <returns></returns>
		MuxPath *getShortestMuxPath(MuxPath *currentMuxPath, IMuxing *muxer, std::vector<MuxableType*> &decidedHandledTypes, std::vector<MuxableType*> &undecidedPossibleHandledTypes, std::vector<MuxableType*> &unhandledInputTypes, ContainerType *desiredContainerType);

		/// <summary>
		/// Finds the shortest mux path for a given set of input MuxableTypes (ie the
		/// encoder output types have all already been chosen here).
		/// </summary>
		/// Initial stage: if currentMuxPath is empty, it creates a first leg.
		/// Recursive step: It tries out adding all possible muxers to the current mux path,
		///                 and calls itself with this extended mux path. It returns the shortest path.
		/// Final step: This will stop recursing if there are no muxers that can help, or if a muxer 
		///                 is found in one step that finalizes the path. This is guaranteed to finish:
		///                 if no progress is made, then it will not recurse. Otherwise, there is a finite
		///                 amount of progress (progress is the number of streams muxed), so it will eventually
		///                 stop progressing.
		/// <param name="currentMuxPath">Current mux path to be worked on</param>
		/// <param name="unhandledDesiredInputTypes">What remains to be muxed</param>
		/// <param name="desiredContainerType">Container type we are aiming at</param>
		/// <returns></returns>
		MuxPath *getShortestMuxPath(MuxPath *currentMuxPath, std::vector<MuxableType*> &unhandledDesiredInputTypes, ContainerType *desiredContainerType);

	private:
		void InitializeInstanceFields();
	};
	class MuxPathLeg
	{
	public:
		IMuxing *muxerInterface;
		std::vector<MuxableType*> handledInputTypes;
		std::vector<MuxableType*> unhandledInputTypes; // those remain for the next leg
	};
	class MP4BoxMuxerProvider : public MuxerProvider
	{

	public:
		MP4BoxMuxerProvider();

		virtual IJobProcessor *GetMuxer(MeGUISettings *settings);
	};
	class MKVMergeMuxerProvider : public MuxerProvider
	{
	public:
		MKVMergeMuxerProvider();

		virtual IJobProcessor *GetMuxer(MeGUISettings *settings);
	};
	class AVIMuxGUIMuxerProvider : public MuxerProvider
	{
	public:
		AVIMuxGUIMuxerProvider();

		virtual IJobProcessor *GetMuxer(MeGUISettings *settings);
	};

	class TSMuxerProvider : public MuxerProvider
	{
	public:
		TSMuxerProvider();

		virtual IJobProcessor *GetMuxer(MeGUISettings *settings);
	};

	class MuxerProvider : public IMuxing
	{
	protected:
		std::vector<VideoType*> supportedVideoTypes;
		std::vector<VideoCodec*> supportedVideoCodecs;
		std::vector<AudioCodec*> supportedAudioCodecs;
		std::vector<AudioType*> supportedAudioTypes;
		std::vector<SubtitleType*> supportedSubtitleTypes;
		std::vector<ChapterType*> supportedChapterTypes;
		std::vector<ContainerType*> supportedContainers;
		std::vector<ContainerType*> supportedContainerInputTypes;
		std::vector<DeviceType*> supportedDeviceTypes;
		bool supportsAnyInputtableAudioCodec;
		bool supportsAnyInputtableVideoCodec;
		std::string videoInputFilter, audioInputFilter, subtitleInputFilter;
//ORIGINAL LINE: protected int[] maxFilesOfType;
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
		int *maxFilesOfType;
		std::string name;
		System::Windows::Forms::Shortcut *shortcut;
		std::string id;
		MeGUI::MuxerType type;
	public:
		MuxerProvider(const std::string &id);
		const std::string &getID() const;
		bool SupportsVideoCodec(VideoCodec *codec);

		bool SupportsAudioCodec(AudioCodec *codec);

		std::vector<VideoCodec*> GetSupportedVideoCodecs();

		std::vector<AudioCodec*> GetSupportedAudioCodecs();

		const std::string &getName() const;

		const MeGUI::MuxerType &getMuxerType() const;

		const System::Windows::Forms::Shortcut &getShortcut() const;

		std::vector<VideoType*> GetSupportedVideoTypes();

		std::vector<AudioType*> GetSupportedAudioTypes();

		std::vector<SubtitleType*> GetSupportedSubtitleTypes();

		std::vector<ChapterType*> GetSupportedChapterTypes();

		std::vector<ContainerType*> GetSupportedContainers();

		std::vector<DeviceType*> GetSupportedDeviceTypes();

		std::vector<ContainerType*> GetSupportedContainerTypes();

		std::vector<ContainerType*> GetSupportedContainerInputTypes();

		std::vector<ContainerType*> GetContainersInCommon(IMuxing *iMuxing);

		virtual IJobProcessor *GetMuxer(MeGUISettings*) = 0;

		/// <summary>
		/// Returns the number of the type if it is supported, otherwise -1
		/// </summary>
		/// <param name="type"></param>
		/// <returns></returns>
	private:
		int getSupportedType(MuxableType *type);

	public:
		ProcessingLevel CanBeProcessed(MuxableType inputTypes[], std::vector<MuxableType*> &handledInputTypes, std::vector<MuxableType*> &unhandledInputTypes);


		ProcessingLevel CanBeProcessed(ContainerType inputContainers[], MuxableType inputTypes[], std::vector<MuxableType*> &handledInputTypes, std::vector<MuxableType*> &unhandledInputTypes);

		std::string GetOutputTypeFilter(ContainerType *containerType);

		std::string GetOutputTypeFilter();

		std::string GetVideoInputFilter();

		std::string GetAudioInputFilter();

		std::string GetChapterInputFilter();

		std::string GetSubtitleInputFilter();

		std::string GetMuxedInputFilter();

		std::string GetDeviceInputFilter();

	private:
		void InitializeInstanceFields();
	};

//C# TO C++ CONVERTER TODO TASK: There is no native C++ template equivalent to generic constraints:
	template<typename TCodec, typename TType, typename TEncoderType> where TType : OutputType
	class EncodingProvider : public IEncoding<TCodec, TType, TEncoderType>
	{
	protected:
		std::vector<TType> supportedTypes;
		std::vector<TCodec> supportedCodecs;
		std::vector<TEncoderType> supportedEncoderTypes;

	public:
		virtual IJobProcessor *CreateEncoder(MeGUISettings*) = 0;

		EncodingProvider()
		{
			supportedTypes = std::vector<TType>();
			supportedCodecs = std::vector<TCodec>();
			supportedEncoderTypes = std::vector<TEncoderType>();
		}


		std::vector<TEncoderType> GetSupportedEncoderTypes()
		{
			return supportedEncoderTypes;
		}

		std::vector<TCodec> GetSupportedCodecs()
		{
			return supportedCodecs;
		}

		std::vector<TType> GetSupportedOutputTypes(TEncoderType codec)
		{
			if (std::find(supportedEncoderTypes.begin(), supportedEncoderTypes.end(), codec) != supportedEncoderTypes.end())
				return supportedTypes;
			else
				return std::vector<TType>();
		}

		IJobProcessor *GetEncoder(TEncoderType codec, TType outputType, MeGUISettings *settings)
		{
			if (std::find(supportedEncoderTypes.begin(), supportedEncoderTypes.end(), codec) != supportedEncoderTypes.end())
			{
				for (std::vector<TType>::const_iterator vto = GetSupportedOutputTypes(codec).begin(); vto != GetSupportedOutputTypes(codec).end(); ++vto)
				{
					if (vto->GetType() == outputType->GetType())
						return CreateEncoder(settings);
				}
			}
			return 0;
		}

		std::string GetOutputTypeFilter(TEncoderType codec, TType outputType)
		{
			if (std::find(supportedEncoderTypes.begin(), supportedEncoderTypes.end(), codec) != supportedEncoderTypes.end())
			{
				for (std::vector<TType>::const_iterator vto = GetSupportedOutputTypes(codec).begin(); vto != GetSupportedOutputTypes(codec).end(); ++vto)
				{
					if (vto->GetType() == outputType->GetType())
						return vto->OutputFilterString;
				}
				return 0;
			}
			return "";
		}

		virtual std::string GetInputTypeFilter()
		{
			return "AviSynth script files(*.avs)|*.avs";
		}

	};


//C# TO C++ CONVERTER TODO TASK: There is no native C++ template equivalent to generic constraints:
	template<typename TCodec, typename TType, typename TEncoderType> where TType : OutputType
	class AllEncoderProvider
	{
	private:
		std::vector<IEncoding<TCodec, TType, TEncoderType>*> registeredEncoders;
	public:
		AllEncoderProvider()
		{
			registeredEncoders = std::vector<IEncoding<TCodec, TType, TEncoderType>*>();
		}
		/// <summary>
		/// checks all available video encoders to see if one supports the desired video codec with the desired
		/// output type
		/// </summary>
		/// <param name="videoCodec">the desired video codec</param>
		/// <param name="outputType">the desired video output</param>
		/// <returns>true if the codec/output type combo can be fullfilled, false if not</returns>
		bool IsSupported(TEncoderType codec, TType outputType)
		{
			IJobProcessor *encoder = GetEncoder(new MeGUISettings(), codec, outputType);
			if (encoder != 0)
				return true;
			else
				return false;
		}
		/// <summary>
		/// gets the input filter string for a given codec type (based on the encoder that is capable of encoding
		/// the desired codec)
		/// </summary>
		/// <param name="codec">the desired codec</param>
		/// <returns>the input filter string for the desired codec</returns>
		std::string GetSupportedInput(TCodec codec)
		{
			IEncoding<TCodec, TType, TEncoderType> *enc = 0;
			for (std::vector<IEncoding<TCodec, TType, TEncoderType>*>::const_iterator encoder = this->registeredEncoders.begin(); encoder != this->registeredEncoders.end(); ++encoder)
			{
				if ((*encoder)->GetSupportedCodecs()->Contains(codec))
				{
					enc = *encoder;
					break;
				}
			}
			if (enc == 0)
			{
				return "";
			}
			else
			{
				return enc->GetInputTypeFilter();
			}
		}
		/// <summary>
		/// gets all input types supported by the first encoder capable of handling the desired codec
		/// </summary>
		/// <param name="codec">the desired codec</param>
		/// <returns>a list of output types that the encoder for this desired codec can deliver directly</returns>
		TType *GetSupportedOutput(TEncoderType encoderType)
		{
			IEncoding<TCodec, TType, TEncoderType> *enc = 0;
			for (std::vector<IEncoding<TCodec, TType, TEncoderType>*>::const_iterator encoder = this->registeredEncoders.begin(); encoder != this->registeredEncoders.end(); ++encoder)
			{
				if ((*encoder)->GetSupportedEncoderTypes()->Contains(encoderType))
				{
					enc = *encoder;
					break;
				}
			}
			if (enc == 0)
			{
				return new TType[0];
			}
			else
			{
				std::vector<TType> supportedTypes = enc->GetSupportedOutputTypes(encoderType);
				return supportedTypes.ToArray();
			}
		}
		/// <summary>
		/// gets an encoder for the given codec and output type
		/// </summary>
		/// <param name="videoCodec">the desired video codec</param>
		/// <param name="outputType">the desired output type</param>
		/// <returns>the encoder found or null if no encoder was found</returns>
		IJobProcessor *GetEncoder(MeGUISettings *settings, TEncoderType codec, TType outputType)
		{
			IJobProcessor *encoder = 0;
			for (std::vector<IEncoding<TCodec, TType, TEncoderType>*>::const_iterator encodingInterface = this->registeredEncoders.begin(); encodingInterface != this->registeredEncoders.end(); ++encodingInterface)
			{
				if (!(*encodingInterface)->GetSupportedEncoderTypes()->Contains(codec))
					continue;
				if (!(*encodingInterface)->GetSupportedOutputTypes(codec)->Contains(outputType))
					continue;
				encoder = (*encodingInterface)->GetEncoder(codec, outputType, settings);
			}
			return encoder;
		}
		/// <summary>
		/// registers a new encoder to the program
		/// </summary>
		/// <param name="encoder"></param>
		void RegisterEncoder(IEncoding<TCodec, TType, TEncoderType> *encoder)
		{
			this->registeredEncoders.push_back(encoder);
		}
	};

	class AudioEncodingProvider : public EncodingProvider<AudioCodec*, AudioType*, AudioEncoderType*>
	{
	public:
		AudioEncodingProvider();

		virtual std::string GetInputTypeFilter();

		virtual IJobProcessor *CreateEncoder(MeGUISettings *settings);
	};
	class VideoEncoderProvider : public AllEncoderProvider<VideoCodec*, VideoType*, VideoEncoderType*>
	{
	public:
		VideoEncoderProvider();
	};
	class AudioEncoderProvider : public AllEncoderProvider<AudioCodec*, AudioType*, AudioEncoderType*>
	{
	public:
		AudioEncoderProvider();
	};
	class XviDEncoderProvider : public EncodingProvider<VideoCodec*, VideoType*, VideoEncoderType*>
	{
	public:
		XviDEncoderProvider();

		virtual IJobProcessor *CreateEncoder(MeGUISettings *settings);
	};

	class X264EncoderProvider : public EncodingProvider<VideoCodec*, VideoType*, VideoEncoderType*>
	{
	public:
		X264EncoderProvider();

		virtual IJobProcessor *CreateEncoder(MeGUISettings *settings);
	};
	class NeroAACEncodingProvider : public AudioEncodingProvider
	{
	public:
		NeroAACEncodingProvider();
	};

	class LameMP3EncodingProvider : public AudioEncodingProvider
	{
	public:
		LameMP3EncodingProvider();
	};

	class VorbisEncodingProvider : public AudioEncodingProvider
	{
	public:
		VorbisEncodingProvider();
	};

	class AC3EncodingProvider : public AudioEncodingProvider
	{
	public:
		AC3EncodingProvider();
	};

	class MP2EncodingProvider : public AudioEncodingProvider
	{
	public:
		MP2EncodingProvider();
	};

	class AftenEncodingProvider : public AudioEncodingProvider
	{
	public:
		AftenEncodingProvider();
	};

	class FlacEncodingProvider : public AudioEncodingProvider
	{
	public:
		FlacEncodingProvider();
	};

	class QaacEncodingProvider : public AudioEncodingProvider
	{
	public:
		QaacEncodingProvider();
	};

	class OpusEncodingProvider : public AudioEncodingProvider
	{
	public:
		OpusEncodingProvider();
	};
}
