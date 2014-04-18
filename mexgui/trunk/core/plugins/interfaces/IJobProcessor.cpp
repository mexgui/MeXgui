#include "IJobProcessor.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
using namespace MeGUI::core::util;

namespace MeGUI
{

	const std::string &JobPreProcessor::getID() const
	{
		return id;
	}

	const Processor &JobPreProcessor::getPreProcessor() const
	{
		return processor;
	}

	JobPreProcessor::JobPreProcessor(Processor p, const std::string &id)
	{
		this->id = id;
		this->processor = p;
	}

	const std::string &JobPostProcessor::getID() const
	{
		return id;
	}

	const Processor &JobPostProcessor::getPostProcessor() const
	{
		return processor;
	}

	JobPostProcessor::JobPostProcessor(Processor p, const std::string &id)
	{
		this->id = id;
		this->processor = p;
	}

	const std::string &JobProcessorFactory::getID() const
	{
		return id;
	}

	const ProcessorFactory &JobProcessorFactory::getFactory() const
	{
		return factory;
	}

	JobProcessorFactory::JobProcessorFactory(ProcessorFactory factory, const std::string &id)
	{
		this->factory = factory;
		this->id = id;
	}
}
