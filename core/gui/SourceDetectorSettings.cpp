#include "SourceDetectorSettings.h"




//using namespace System::Collections::Generic;

//using namespace System::Text;

//using namespace System::Threading;
using namespace MeXgui::core::util;

namespace MeXgui
{

	SourceDetectorSettings::SourceDetectorSettings()
	{
		combedFrameMinimum = 5.0;
		minimumUsefulSections = 20;
		hybridThreshold = 5;
		decimationThreshold = 2.0;
		portionThreshold = 5.0;
		analysePercent = 1;
		minAnalyseSections = 150;
		hybridFOPercent = 10;
		portionsAllowed = false;
		maxPortions = 5;
		priority = ThreadPriority::BelowNormal;
	}

	const double &SourceDetectorSettings::getCombedFrameMinimum() const
	{
		return combedFrameMinimum;
	}

	void SourceDetectorSettings::setCombedFrameMinimum(const double &value)
	{
		combedFrameMinimum = value;
	}

	const int &SourceDetectorSettings::getMinimumUsefulSections() const
	{
		return minimumUsefulSections;
	}

	void SourceDetectorSettings::setMinimumUsefulSections(const int &value)
	{
		minimumUsefulSections = value;
	}

	const double &SourceDetectorSettings::getDecimationThreshold() const
	{
		return decimationThreshold;
	}

	void SourceDetectorSettings::setDecimationThreshold(const double &value)
	{
		decimationThreshold = value;
	}

	const int &SourceDetectorSettings::getMaxPortions() const
	{
		return maxPortions;
	}

	void SourceDetectorSettings::setMaxPortions(const int &value)
	{
		maxPortions = value;
	}

	const ThreadPriority &SourceDetectorSettings::getPriority() const
	{
		return priority;
	}

	void SourceDetectorSettings::setPriority(const ThreadPriority &value)
	{
		priority = value;
	}

	const bool &SourceDetectorSettings::getPortionsAllowed() const
	{
		return portionsAllowed;
	}

	void SourceDetectorSettings::setPortionsAllowed(const bool &value)
	{
		portionsAllowed = value;
	}

	const double &SourceDetectorSettings::getPortionThreshold() const
	{
		return portionThreshold;
	}

	void SourceDetectorSettings::setPortionThreshold(const double &value)
	{
		portionThreshold = value;
	}

	const int &SourceDetectorSettings::getHybridFOPercent() const
	{
		return hybridFOPercent;
	}

	void SourceDetectorSettings::setHybridFOPercent(const int &value)
	{
		hybridFOPercent = value;
	}

	const int &SourceDetectorSettings::getMinimumAnalyseSections() const
	{
		return minAnalyseSections;
	}

	void SourceDetectorSettings::setMinimumAnalyseSections(const int &value)
	{
		minAnalyseSections = value;
	}

	const int &SourceDetectorSettings::getAnalysePercent() const
	{
		return analysePercent;
	}

	void SourceDetectorSettings::setAnalysePercent(const int &value)
	{
		analysePercent = value;
	}

	const int &SourceDetectorSettings::getHybridPercent() const
	{
		return hybridThreshold;
	}

	void SourceDetectorSettings::setHybridPercent(const int &value)
	{
		hybridThreshold = value;
	}
}
