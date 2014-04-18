#include "Job.h"




//using namespace System::Collections::Generic;

//using namespace System::Diagnostics;

//using namespace System::Xml::Serialization;
using namespace MeXgui::core::details;
using namespace MeXgui::core::plugins::interfaces;
using namespace MeXgui::core::util;
using namespace MeXgui::packages::tools::besplitter;

namespace MeXgui
{

Random *const JobID::gen = new Random();

	const QString &JobID::getName() const
	{
		return name;
	}

	const int &JobID::getUniqueID() const
	{
		return uniqueID;
	}

	JobID::JobID(const QString &name)
	{
		for (int i = 0; i < name.length(); i++)
			if (!(isalnum(name[i]) || name[i] == '_'))
				throw new MeXguiException("The name must be alphanumeric, including underscores.");

		this->name = name;
		this->uniqueID = gen->Next();
	}

	QString JobID::ToString()
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

	Job::Job(const QString &input, const QString &output)
	{
		Input = input;
		Output = output;
		if (!input.empty() && input == output)
			throw new MeXguiException("Input and output files may not be the same");

		FilesToDelete = QVector<QString>();
	}
}
