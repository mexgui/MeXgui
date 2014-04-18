#include "IJobProcessor.h"




//using namespace System::Collections::Generic;

//using namespace System::Text;
using namespace MeXgui::core::util;

namespace MeXgui
{

	const QString &JobPreProcessor::getID() const
	{
		return id;
	}

	const Processor &JobPreProcessor::getPreProcessor() const
	{
		return processor;
	}

	JobPreProcessor::JobPreProcessor(Processor p, const QString &id)
	{
		this->id = id;
		this->processor = p;
	}

	const QString &JobPostProcessor::getID() const
	{
		return id;
	}

	const Processor &JobPostProcessor::getPostProcessor() const
	{
		return processor;
	}

	JobPostProcessor::JobPostProcessor(Processor p, const QString &id)
	{
		this->id = id;
		this->processor = p;
	}

	const QString &JobProcessorFactory::getID() const
	{
		return id;
	}

	const ProcessorFactory &JobProcessorFactory::getFactory() const
	{
		return factory;
	}

	JobProcessorFactory::JobProcessorFactory(ProcessorFactory factory, const QString &id)
	{
		this->factory = factory;
		this->id = id;
	}
}
