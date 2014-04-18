#include "AviSynthSettings.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
using namespace MeGUI::core::plugins::interfaces;

namespace MeGUI
{

std::string AviSynthSettings::ID = "AviSynth";

	const std::string &AviSynthSettings::getSettingsID() const
	{
		return ID;
	}

	void AviSynthSettings::FixFileNames(std::map<std::string, std::string> &_)
	{
	}

	AviSynthSettings::AviSynthSettings()
	{
		this->setTemplate("<input>\r\n<deinterlace>\r\n<crop>\r\n<resize>\r\n<denoise>\r\n"); // Default -- will act as it did before avs profiles
		this->setResizeMethod(Lanczos); // Lanczos
		this->setDenoiseMethod((DegetDenoiseMethod()pe)0); // UnDot
		this->setDeinterlace(false);
		this->setDenoise(false);
		this->setResize(true);
		this->setIVTC(false);
		this->setMPEG2Deblock(false);
		this->setColourCorrect(true);
		this->setMod16Method(none);
		this->setDSS2(false);
		this->setUpsize(false);
		this->setModValue(mod8);
		this->acceptableAspectError = 1;
	}

	AviSynthSettings::AviSynthSettings(const std::string &template_Renamed, ResizeFilterType resizeMethod, bool resize, bool upsize, DenoiseFilterType denoiseMethod, bool denoise, bool mpeg2deblock, bool colourCorrect, mod16Method method, bool dss2, modValue modValueUsed, decimal acceptableAspectError)
	{
		this->setTemplate(template_Renamed);
		this->setResize(resize);
		this->setResizeMethod(resizeMethod);
		this->setDenoiseMethod(denoiseMethod);
		this->setDeinterlace(deinterlace);
		this->setDenoise(denoise);
		this->setIVTC(ivtc);
		this->setMPEG2Deblock(mpeg2deblock);
		this->setColourCorrect(colourCorrect);
		this->setMod16Method(method);
		this->setDSS2(dss2);
		this->setUpsize(upsize);
		this->setModValue(modValueUsed);
		this->acceptableAspectError = acceptableAspectError;
	}

	bool AviSynthSettings::Equals(object *obj)
	{
		return Equals(dynamic_cast<GenericSettings*>(obj));
	}

	bool AviSynthSettings::Equals(GenericSettings *other)
	{
		return other == 0 ? false : PropertyEqualityTester::AreEqual(this, other);
	}

	int AviSynthSettings::GetHashCode()
	{
		return __super::GetHashCode();
	}

	object *AviSynthSettings::ICloneable_Clone()
	{
		return Clone();
	}

	MeGUI::core::plugins::interfaces::GenericSettings *AviSynthSettings::GenericSettings_Clone()
	{
		return dynamic_cast<AviSynthSettings*>(this->MemberwiseClone());
	}

	AviSynthSettings *AviSynthSettings::Clone()
	{
		return dynamic_cast<AviSynthSettings*>(this->MemberwiseClone());
	}

	const mod16Method &AviSynthSettings::getMod16Method() const
	{
		return mod16Method;
	}

	void AviSynthSettings::setMod16Method(const mod16Method &value)
	{
		mod16Method = value;
	}

	const modValue &AviSynthSettings::getModValue() const
	{
		return modValueUsed;
	}

	void AviSynthSettings::setModValue(const modValue &value)
	{
		modValueUsed = value;
	}

	const bool &AviSynthSettings::getResize() const
	{
		return resize;
	}

	void AviSynthSettings::setResize(const bool &value)
	{
		resize = value;
	}

	const bool &AviSynthSettings::getUpsize() const
	{
		return upsize;
	}

	void AviSynthSettings::setUpsize(const bool &value)
	{
		upsize = value;
	}

	const std::string &AviSynthSettings::getTemplate() const
	{
		return template_Renamed;
	}

	void AviSynthSettings::setTemplate(const std::string &value)
	{
//ORIGINAL LINE: string[] lines = value.Split('\r', '\n');
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Split' method:
		std::string *lines = value.Split('\r', '\n');
		StringBuilder *script = new StringBuilder();
		script->EnsureCapacity(value.length());
		for (std::string::const_iterator line = lines->begin(); line != lines->end(); ++line)
		{
			if ((*line).Length > 0)
			{
				script->Append(*line);
				script->Append("\r\n");
			}
		}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		template_Renamed = script->ToString();
	}

	const ResizeFilterType &AviSynthSettings::getResizeMethod() const
	{
		return resizeMethod;
	}

	void AviSynthSettings::setResizeMethod(const ResizeFilterType &value)
	{
		resizeMethod = value;
	}

	const DenoiseFilterType &AviSynthSettings::getDenoiseMethod() const
	{
		return denoiseMethod;
	}

	void AviSynthSettings::setDenoiseMethod(const DenoiseFilterType &value)
	{
		denoiseMethod = value;
	}

	const bool &AviSynthSettings::getDeinterlace() const
	{
		return deinterlace;
	}

	void AviSynthSettings::setDeinterlace(const bool &value)
	{
		deinterlace = value;
	}

	const bool &AviSynthSettings::getDenoise() const
	{
		return denoise;
	}

	void AviSynthSettings::setDenoise(const bool &value)
	{
		denoise = value;
	}

	const bool &AviSynthSettings::getIVTC() const
	{
		return ivtc;
	}

	void AviSynthSettings::setIVTC(const bool &value)
	{
		ivtc = value;
	}

	const bool &AviSynthSettings::getMPEG2Deblock() const
	{
		return mpeg2deblock;
	}

	void AviSynthSettings::setMPEG2Deblock(const bool &value)
	{
		mpeg2deblock = value;
	}

	const bool &AviSynthSettings::getColourCorrect() const
	{
		return colourCorrect;
	}

	void AviSynthSettings::setColourCorrect(const bool &value)
	{
		colourCorrect = value;
	}

	const bool &AviSynthSettings::getDSS2() const
	{
		return dss2;
	}

	void AviSynthSettings::setDSS2(const bool &value)
	{
		dss2 = value;
	}

	const decimal &AviSynthSettings::getAcceptableAspectError() const
	{
		return acceptableAspectError;
	}

	void AviSynthSettings::setAcceptableAspectError(const decimal &value)
	{
		acceptableAspectError = value;
	}

	const std::string &AviSynthSettings::getRequiredFiles() const
	{
		return new std::string[0];
	}

	const std::string &AviSynthSettings::getRequiredProfiles() const
	{
		return new std::string[0];
	}
}
