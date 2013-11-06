#include "DialogSettings.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
using namespace MeGUI::core::util;

namespace MeGUI
{

	const bool &DialogSettings::getOverwriteJobOutputResponse() const
	{
		return ovewriteJobOutputResponse;
	}

	void DialogSettings::setOverwriteJobOutputResponse(const bool &value)
	{
		ovewriteJobOutputResponse = value;
	}

	const bool &DialogSettings::getAskAboutOverwriteJobOutput() const
	{
		return askAboutOverwriteJobOutput;
	}

	void DialogSettings::setAskAboutOverwriteJobOutput(const bool &value)
	{
		askAboutOverwriteJobOutput = value;
	}

	const bool &DialogSettings::getDuplicateResponse() const
	{
		return dupResponse;
	}

	void DialogSettings::setDuplicateResponse(const bool &value)
	{
		dupResponse = value;
	}

	const bool &DialogSettings::getAskAboutDuplicates() const
	{
		return askAboutDuplicates;
	}

	void DialogSettings::setAskAboutDuplicates(const bool &value)
	{
		askAboutDuplicates = value;
	}

	const bool &DialogSettings::getAskAboutError() const
	{
		return askAboutError;
	}

	void DialogSettings::setAskAboutError(const bool &value)
	{
		askAboutError = value;
	}

	const bool &DialogSettings::getContinueDespiteError() const
	{
		return continueDespiteError;
	}

	void DialogSettings::setContinueDespiteError(const bool &value)
	{
		continueDespiteError = value;
	}

	const bool &DialogSettings::getAskAboutYV12() const
	{
		return askAboutYV12;
	}

	void DialogSettings::setAskAboutYV12(const bool &value)
	{
		askAboutYV12 = value;
	}

	const bool &DialogSettings::getAddConvertToYV12() const
	{
		return addConvertToYV12;
	}

	void DialogSettings::setAddConvertToYV12(const bool &value)
	{
		addConvertToYV12 = value;
	}

	const bool &DialogSettings::getAskAboutVOBs() const
	{
		return askAboutVOBs;
	}

	void DialogSettings::setAskAboutVOBs(const bool &value)
	{
		askAboutVOBs = value;
	}

	const bool &DialogSettings::getUseOneClick() const
	{
		return useOneClick;
	}

	void DialogSettings::setUseOneClick(const bool &value)
	{
		useOneClick = value;
	}

	const bool &DialogSettings::getAskAboutIntermediateDelete() const
	{
		return askAboutIntermediateDelete;
	}

	void DialogSettings::setAskAboutIntermediateDelete(const bool &value)
	{
		askAboutIntermediateDelete = value;
	}

	const bool &DialogSettings::getIntermediateDelete() const
	{
		return intermediateDelete;
	}

	void DialogSettings::setIntermediateDelete(const bool &value)
	{
		intermediateDelete = value;
	}

	DialogSettings::DialogSettings()
	{
		InitializeInstanceFields();
		askAboutVOBs = true;
		useOneClick = true;
		askAboutError = true;
		askAboutYV12 = true;
		addConvertToYV12 = true;
		continueDespiteError = true;
		askAboutDuplicates = true;
		dupResponse = true;
		askAboutIntermediateDelete = true;
		intermediateDelete = true;
	}

	void DialogSettings::InitializeInstanceFields()
	{
		ovewriteJobOutputResponse = true;
		askAboutOverwriteJobOutput = true;
	}
}
