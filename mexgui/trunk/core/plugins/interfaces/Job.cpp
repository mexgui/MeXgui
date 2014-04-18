#include "Job.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Diagnostics;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Xml::Serialization;
using namespace MeGUI::core::details;
using namespace MeGUI::core::plugins::interfaces;
using namespace MeGUI::core::util;
using namespace MeGUI::packages::tools::besplitter;

namespace MeGUI
{

Random *const JobID::gen = new Random();

	const std::string &JobID::getName() const
	{
		return name;
	}

	const int &JobID::getUniqueID() const
	{
		return uniqueID;
	}

	JobID::JobID(const std::string &name)
	{
		for (int i = 0; i < name.length(); i++)
			if (!(isalnum(name[i]) || name[i] == '_'))
				throw new MeGUIException("The name must be alphanumeric, including underscores.");

		this->name = name;
		this->uniqueID = gen->Next();
	}

	std::string JobID::ToString()
	{
		return name + " " + StringConverterHelper::toString(uniqueID);
	}

	bool JobID::Equals(object *obj)
	{
		JobID *other = dynamic_cast<JobID*>(obj);
		if (other == 0)
			return false;

		return (name == other->name && uniqueID == other->uniqueID);
	}

	int JobID::GetHashCode()
	{
		return name.GetHashCode() ^ uniqueID.GetHashCode();
	}

	Job::Job()
	{
	}

	Job::Job(const std::string &input, const std::string &output)
	{
		Input = input;
		Output = output;
		if (!input.empty() && input == output)
			throw new MeGUIException("Input and output files may not be the same");

		FilesToDelete = std::vector<std::string>();
	}
}
