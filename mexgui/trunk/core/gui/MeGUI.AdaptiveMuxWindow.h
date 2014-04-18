#pragma once

#include "core/details/mux/baseMuxWindow.h"
#include "core/details/mux/MuxProvider.h"
#include "core/util/JobUtil.h"
#include "core/details/CodecManager.h"
#include "MeGUI.MainForm.h"
#include "core/util/VideoUtil.h"
#include "core/util/LogItem.h"
#include "core/details/mux/MeGUI.core.details.mux.MuxStreamControl.h"
#include "core/details/MeGUI.core.details.JobChain.h"
#include "core/plugins/interfaces/IMuxing.h"
#include "packages/video/x264/x264Settings.h"
#include "core/details/Streams.h"
#include "core/util/FileSize.h"
#include <string>
#include <vector>
#include <stdexcept>

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
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;

using namespace MeGUI::core::details;
using namespace MeGUI::core::details::mux;
using namespace MeGUI::core::util;

namespace MeGUI
{
	class AdaptiveMuxWindow : public baseMuxWindow
	{
	private:
		MuxProvider *muxProvider;
		JobUtil *jobUtil;
		bool minimizedMode;
		VideoEncoderType *knownVideoType;
//ORIGINAL LINE: private AudioEncoderType[] knownAudioTypes;
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
		AudioEncoderType *knownAudioTypes;

		public:
		~AdaptiveMuxWindow()
		{
			this->Dispose(true);
		}

//C# TO C++ CONVERTER WARNING: Unlike C#, there is no automatic call to this finalizer method in native C++:
		private:
		void Finalize()
		{
			this->Dispose(false);
		}

	public:
		AdaptiveMuxWindow(MainForm *mainForm);

	protected:
		virtual void fileUpdated();

		virtual void upDeviceTypes();

	private:
		void cbContainer_SelectedIndexChanged(object *sender, EventArgs *e);

		void getTypes(AudioEncoderType aCodec[], MuxableType audioTypes[], MuxableType subtitleTypes[]);


	protected:
		virtual void checkIO();

	private:
		void updateDeviceTypes();

		void updatePossibleContainers();

	public:
		const JobChain &getJobs() const;
		/// <summary>
		/// sets the GUI to a minimal mode allowing to configure audio track languages, configure subtitles, and chapters
		/// the rest of the options are deactivated
		/// </summary>
		/// <param name="videoInput">the video input</param>
		/// <param name="framerate">the framerate of the video input</param>
		/// <param name="audioStreams">the audio streams whose languages have to be assigned</param>
		/// <param name="output">the output file</param>
		/// <param name="splitSize">the output split size</param>
		void setMinimizedMode(const std::string &videoInput, const std::string &videoName, VideoEncoderType *videoType, double framerate, MuxStream audioStreams[], AudioEncoderType audioTypes[], const std::string &output, Nullable<FileSize> splitSize, ContainerType *cft);

		void getAdditionalStreams(MuxStream audio[], MuxStream subtitles[], std::string &chapters, std::string &output, ContainerType *&cot);

	protected:
		virtual void muxButton_Click(object *sender, System::EventArgs *e);


		/// <summary>
		/// Required designer variable.
		/// </summary>
	private:
		System::ComponentModel::IContainer *components;

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		void Dispose(bool disposing);


		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent();


		System::Windows::Forms::ComboBox *containerFormat;

	private:
		void InitializeInstanceFields();
	};
}
