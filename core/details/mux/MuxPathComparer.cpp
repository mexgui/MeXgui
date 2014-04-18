#include "MuxPathComparer.h"




//using namespace System::Collections::Generic;

//using namespace System::Reflection;

//using namespace System::Text;

namespace MeXgui
{

	MuxPathComparer::MuxPathComparer()
	{
		InitializeInstanceFields();
		registerChecker(new CheckMuxPath(&CheckForUnsupportedCodecs));
		registerChecker(new CheckMuxPath(&CheckForVFWMatroska));
		registerComparer(0, new MuxPathCompare(&CompareByLength));
		registerComparer(100, new MuxPathCompare(&CompareByAACContainer)); // A higher order number means it is less important
	}

	void MuxPathComparer::registerComparer(int order, MuxPathCompare method)
	{
		PreferencedComparer p = PreferencedComparer();
		p.method = method;
		p.preference = order;
//C# TO C++ CONVERTER TODO TASK: There is no built-in support for multithreading in native C++:
		lock (this)
		{
			comparisonMethods.push_back(p);
			comparisonSorted = false;
		}
	}

	void MuxPathComparer::registerChecker(CheckMuxPath checker)
	{
		checkingMethods.push_back(checker);
	}

	int MuxPathComparer::Compare(MuxPath *x, MuxPath *y)
	{
//C# TO C++ CONVERTER TODO TASK: There is no built-in support for multithreading in native C++:
		lock (this)
		{
			if (!comparisonSorted)
			{
				comparisonMethods.Sort(Compare);
				comparisonSorted = true;
			}

			for (QVector<PreferencedComparer>::const_iterator comparer = comparisonMethods.begin(); comparer != comparisonMethods.end(); ++comparer)
			{
				int result = (*comparer).method(x, y);
				if (result != 0)
					return result;
			}
			return 0;
		}
	}

	bool MuxPathComparer::BadMuxPath(MuxPath *path)
	{
//C# TO C++ CONVERTER TODO TASK: There is no built-in support for multithreading in native C++:
		lock (this)
		{
			for (QVector<CheckMuxPath>::const_iterator checker = checkingMethods.begin(); checker != checkingMethods.end(); ++checker)
			{
				if (checker(path))
					return true;
			}
			return false;
		}
	}

	MuxPath *MuxPathComparer::GetBestMuxPath(QVector<MuxPath*> &muxPaths)
	{
		muxPaths.RemoveAll(BadMuxPath);
		if (muxPaths.empty())
			return 0;

		muxPaths.Sort(Compare);
		return muxPaths[0];
	}

	int MuxPathComparer::CompareByLength(MuxPath *x, MuxPath *y)
	{
		return x->getLength() - y->getLength();
	}

	int MuxPathComparer::CompareByAACContainer(MuxPath *x, MuxPath *y)
	{
		int xInitialRawAAC = 0, yInitialRawAAC = 0;
		for (QVector<MuxableType*>::const_iterator initialType = x->getInitialInputTypes().begin(); initialType != x->getInitialInputTypes().end(); ++initialType)
		{
			if ((*initialType)->outputType->Equals(AudioType::RAWAAC))
				xInitialRawAAC++;
		}
		for (QVector<MuxableType*>::const_iterator initialType = y->getInitialInputTypes().begin(); initialType != y->getInitialInputTypes().end(); ++initialType)
		{
			if ((*initialType)->outputType->Equals(AudioType::RAWAAC))
				yInitialRawAAC++;
		}
		return xInitialRawAAC - yInitialRawAAC;
	}

	bool MuxPathComparer::CheckForUnsupportedCodecs(MuxPath *x)
	{
		for (int i = 0; i < x->getLength(); i++)
		{
			for (QVector<MuxableType*>::const_iterator type = x[i].handledInputTypes.begin(); type != x[i].handledInputTypes.end(); ++type)
			{
				for (int j = i; j < x->getLength(); j++)
				{
					if (dynamic_cast<VideoCodec*>((*type)->codec) != 0)
					{
						if (!x[j].muxerInterface->SupportsVideoCodec(static_cast<VideoCodec*>((*type)->codec)))
							return true;
					}
					else if (dynamic_cast<AudioCodec*>((*type)->codec) != 0)
					{
						if (!x[j].muxerInterface->SupportsAudioCodec(static_cast<AudioCodec*>((*type)->codec)))
							return true;
					}
				}
			}
		}
		return false;
	}

	bool MuxPathComparer::CheckForVFWMatroska(MuxPath *x)
	{
		if (x->getTargetType() != ContainerType::MKV)
			return false;

		for (MeXgui::MuxPath::const_iterator mpl = x->begin(); mpl != x->end(); ++mpl)
		{
		   /* if (mpl.muxerInterface is AVC2AVIMuxerProvider)
		    {
		        return true;
		    }*/
		}
		return false;
	}

	int MuxPathComparer::Compare(PreferencedComparer a, PreferencedComparer b)
	{
		return a.preference - b.preference;
	}

	void MuxPathComparer::InitializeInstanceFields()
	{
		comparisonMethods = QVector<PreferencedComparer>();
		checkingMethods = QVector<CheckMuxPath>();
		comparisonSorted = false;
	}
}
