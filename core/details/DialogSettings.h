#pragma once

#include "DialogManager.h"

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




//using namespace System::Text;

using namespace MeXgui::core::util;

namespace MeXgui
{
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[LogByMembers]
	class DialogSettings
	{
	private:
		bool ovewriteJobOutputResponse;
	public:
		const bool &getOverwriteJobOutputResponse() const;
		void setOverwriteJobOutputResponse(const bool &value);

	private:
		bool askAboutOverwriteJobOutput;
	public:
		const bool &getAskAboutOverwriteJobOutput() const;
		void setAskAboutOverwriteJobOutput(const bool &value);

	private:
		bool dupResponse;
	public:
		const bool &getDuplicateResponse() const;
		void setDuplicateResponse(const bool &value);

	private:
		bool askAboutDuplicates;
	public:
		const bool &getAskAboutDuplicates() const;
		void setAskAboutDuplicates(const bool &value);

	private:
		bool askAboutError;
	public:
		const bool &getAskAboutError() const;
		void setAskAboutError(const bool &value);

	private:
		bool continueDespiteError;
	public:
		const bool &getContinueDespiteError() const;
		void setContinueDespiteError(const bool &value);

	private:
		bool askAboutYV12;
	public:
		const bool &getAskAboutYV12() const;
		void setAskAboutYV12(const bool &value);

	private:
		bool addConvertToYV12;
	public:
		const bool &getAddConvertToYV12() const;
		void setAddConvertToYV12(const bool &value);

	private:
		bool askAboutVOBs;
	public:
		const bool &getAskAboutVOBs() const;
		void setAskAboutVOBs(const bool &value);

	private:
		bool useOneClick;
	public:
		const bool &getUseOneClick() const;
		void setUseOneClick(const bool &value);

	private:
		bool askAboutIntermediateDelete;
	public:
		const bool &getAskAboutIntermediateDelete() const;
		void setAskAboutIntermediateDelete(const bool &value);

	private:
		bool intermediateDelete;
	public:
		const bool &getIntermediateDelete() const;
		void setIntermediateDelete(const bool &value);

		DialogSettings();

	private:
		void InitializeInstanceFields();
	};
}
