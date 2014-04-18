#include "MuxPath.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;

namespace MeGUI
{

	const ContainerType &MuxPath::getTargetType() const
	{
		return targetType;
	}

	void MuxPath::setTargetType(const ContainerType &value)
	{
		targetType = value;
	}

	const std::vector<MuxableType*> &MuxPath::getInitialInputTypes() const
	{
		return initialInputTypes;
	}

	void MuxPath::setInitialInputTypes(const std::vector<MuxableType*> &value)
	{
		initialInputTypes = value;
	}

	const int &MuxPath::getLength() const
	{
		return path.size();
	}

	void MuxPath::Add(MuxPathLeg leg)
	{
		path.push_back(leg);
	}

	MuxPath::MuxPath(ContainerType *targetType)
	{
		path = std::vector<MuxPathLeg>();
		initialInputTypes = std::vector<MuxableType*>();
		this->targetType = targetType;
		alwaysMux = false;
	}

	MuxPath::MuxPath(IEnumerable<MuxableType*> *initialInputTypes, ContainerType *targetType)
	{
		this->initialInputTypes.AddRange(initialInputTypes);
	}

	MuxPath::MuxPath(IEnumerable<MuxableType*> *initialInputTypes, ContainerType *targetType, bool alwaysMux)
	{
		this->alwaysMux = alwaysMux;
	}

	MuxPath *MuxPath::Clone()
	{
		MuxPath *nMuxPath = new MuxPath(initialInputTypes, targetType);
		nMuxPath->path->AddRange(path);
		return nMuxPath;
	}

	IEnumerator<MuxPathLeg> *MuxPath::GetEnumerator()
	{
		return path.begin();
	}

	MuxPathLeg MuxPath::operator [](int index)
	{
		return path[index];
	}

	bool MuxPath::IsCompleted()
	{
		if (path.empty())
		{
			if (initialInputTypes.size() == 1 && MainForm::Instance->getSettings()->getAlwaysMuxMKV() && this->targetType == ContainerType::MKV)
				return false;

			return (initialInputTypes.empty() || (initialInputTypes.size() == 1 && !alwaysMux && initialInputTypes[0]->outputType->getContainerType() == this->targetType));
		}
		else
		{
			return (path[path.size() - 1].unhandledInputTypes.empty() && path[path.size() - 1].muxerInterface->GetSupportedContainerTypes()->Contains(targetType));
		}
	}
}
