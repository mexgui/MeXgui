#include "LanguageSelectionContainer.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;

namespace MeGUI
{

	const std::map<std::string, std::string> &LanguageSelectionContainer::getLanguages() const
	{
		return languagesBibliographic;
	}

	const std::map<std::string, std::string> &LanguageSelectionContainer::getLanguagesTerminology() const
	{
		return languagesTerminology;
	}

	void LanguageSelectionContainer::addLanguageB(const std::string &name, const std::string &iso)
	{
		languagesBibliographic.insert(make_pair(name, iso));
		languagesReverseBibliographic.insert(make_pair(iso, name));
	}

	void LanguageSelectionContainer::addLanguageT(const std::string &name, const std::string &iso)
	{
		languagesTerminology.insert(make_pair(name, iso));
		languagesReverseTerminology.insert(make_pair(iso, name));
	}

	LanguageSelectionContainer::LanguageSelectionContainer()
	{
		// http://www.loc.gov/standards/iso639-2/php/code_list.php

		languagesBibliographic = std::map<std::string, std::string>();
		languagesReverseBibliographic = std::map<std::string, std::string>();

		languagesTerminology = std::map<std::string, std::string>();
		languagesReverseTerminology = std::map<std::string, std::string>();

		addLanguageB("Abkhazian", "abk");
		addLanguageB("Achinese", "ace");
		addLanguageB("Acoli", "ach");
		addLanguageB("Adangme", "ada");
		addLanguageB("Adygei (Adyghe)", "ady");
		addLanguageB("Afar", "aar");
		addLanguageB("Afrihili", "afh");
		addLanguageB("Afrikaans", "afr");
		addLanguageB("Afro-Asiatic (Other)", "afa");
		addLanguageB("Akan", "aka");
		addLanguageB("Akkadian", "akk");
		addLanguageB("Albanian", "alb");
		addLanguageB("Aleut", "ale");
		addLanguageB("Algonquian languages", "alg");
		addLanguageB("Altaic (Other)", "tut");
		addLanguageB("Apache languages", "apa");
		addLanguageB("Arabic", "ara");
		addLanguageB("Aragonese", "arg");
		addLanguageB("Aramaic", "arc");
		addLanguageB("Arapaho", "arp");
		addLanguageB("Araucanian", "arn");
		addLanguageB("Arawak", "arw");
		addLanguageB("Armenian", "arm");
		addLanguageB("Assamese", "ast");
		addLanguageB("Athapascan languages", "art");
		addLanguageB("Australian languages", "aus");
		addLanguageB("Austronesian (Other)", "map");
		addLanguageB("Avaric", "ava");
		addLanguageB("Avestan", "ave");
		addLanguageB("Awadhi", "awa");
		addLanguageB("Aymara", "aym");
		addLanguageB("Azerbaijani", "aze");
		addLanguageB("Balinese", "ban");
		addLanguageB("Bantu", "bnt");
		addLanguageB("Basque", "baq");
		addLanguageB("Belarusian", "bel");
		addLanguageB("Bosnian", "bos");
		addLanguageB("Breton", "bre");
		addLanguageB("Bulgarian", "bul");
		addLanguageB("Burmese", "bur");
		addLanguageB("Catalan", "cat");
		addLanguageB("Chinese", "chi");
		addLanguageB("Corsican", "cos");
		addLanguageB("Croatian", "hrv");
		addLanguageB("Czech", "cze");
		addLanguageB("Danish", "dan");
		addLanguageB("Dutch", "dut");
		addLanguageB("Estonian", "est");
		addLanguageB("Faroese", "fao");
		addLanguageB("Finnish", "fin");
		addLanguageB("French", "fre");
		addLanguageB("Georgian", "geo");
		addLanguageB("German", "ger");
		addLanguageB("Greek", "gre");
		addLanguageB("Hebrew", "heb");
		addLanguageB("Hindi", "hin");
		addLanguageB("Hungarian", "hun");
		addLanguageB("English", "eng");
		addLanguageB("Icelandic", "ice");
		addLanguageB("Indonesian", "ind");
		addLanguageB("Irish", "gai");
		addLanguageB("Italian", "ita");
		addLanguageB("Japanese", "jpn");
		addLanguageB("Kashmiri", "kas");
		addLanguageB("Kongo", "kon");
		addLanguageB("Korean", "kor");
		addLanguageB("Latvian", "lav");
		addLanguageB("Lithuanian", "lit");
		addLanguageB("Macedonian", "mac");
		addLanguageB("Malay", "may");
		addLanguageB("Maltese", "mlt");
		addLanguageB("Maori", "mao");
		addLanguageB("Moldavian", "mol");
		addLanguageB("Mongolian", "mon");
		addLanguageB("Norwegian", "nor");
		addLanguageB("Punjabi", "pan");
		addLanguageB("Persian", "per");
		addLanguageB("Polish", "pol");
		addLanguageB("Portuguese", "por");
		addLanguageB("Romanian", "rum");
		addLanguageB("Russian", "rus");
		addLanguageB("Serbian", "srp");
		addLanguageB("Slovak", "slo");
		addLanguageB("Slovenian", "slv");
		addLanguageB("Spanish", "spa");
		addLanguageB("Swahili", "swa");
		addLanguageB("Swedish", "swe");
		addLanguageB("Thai", "tha");
		addLanguageB("Tibetan", "tib");
		addLanguageB("Turkish", "tur");
		addLanguageB("Urdu", "urd");
		addLanguageB("Ukrainian", "ukr");
		addLanguageB("Uzbek", "uzb");
		addLanguageB("Vietnamese", "vie");
		addLanguageB("Welsh", "wel");
		addLanguageB("Zhuang", "zha");
		addLanguageB("Zulu", "zul");
		addLanguageB("Zuni", "zun");

		addLanguageT("Abkhazian", "abk");
		addLanguageT("Achinese", "ace");
		addLanguageT("Acoli", "ach");
		addLanguageT("Adangme", "ada");
		addLanguageT("Adygei (Adyghe)", "ady");
		addLanguageT("Afar", "aar");
		addLanguageT("Afrihili", "afh");
		addLanguageT("Afrikaans", "afr");
		addLanguageT("Afro-Asiatic (Other)", "afa");
		addLanguageT("Akan", "aka");
		addLanguageT("Akkadian", "akk");
		addLanguageT("Albanian", "sqi");
		addLanguageT("Aleut", "ale");
		addLanguageT("Algonquian languages", "alg");
		addLanguageT("Altaic (Other)", "tut");
		addLanguageT("Apache languages", "apa");
		addLanguageT("Arabic", "ara");
		addLanguageT("Aragonese", "arg");
		addLanguageT("Aramaic", "arc");
		addLanguageT("Arapaho", "arp");
		addLanguageT("Araucanian", "arn");
		addLanguageT("Arawak", "arw");
		addLanguageT("Armenian", "hye");
		addLanguageT("Assamese", "ast");
		addLanguageT("Athapascan languages", "art");
		addLanguageT("Australian languages", "aus");
		addLanguageT("Austronesian (Other)", "map");
		addLanguageT("Avaric", "ava");
		addLanguageT("Avestan", "ave");
		addLanguageT("Awadhi", "awa");
		addLanguageT("Aymara", "aym");
		addLanguageT("Azerbaijani", "aze");
		addLanguageT("Balinese", "ban");
		addLanguageT("Bantu", "bnt");
		addLanguageT("Basque", "eus");
		addLanguageT("Belarusian", "bel");
		addLanguageT("Bosnian", "bos");
		addLanguageT("Breton", "bre");
		addLanguageT("Bulgarian", "bul");
		addLanguageT("Burmese", "mya");
		addLanguageT("Catalan", "cat");
		addLanguageT("Chinese", "zho");
		addLanguageT("Corsican", "cos");
		addLanguageT("Croatian", "hrv");
		addLanguageT("Czech", "ces");
		addLanguageT("Danish", "dan");
		addLanguageT("Dutch", "nld");
		addLanguageT("Estonian", "est");
		addLanguageT("Faroese", "fao");
		addLanguageT("Finnish", "fin");
		addLanguageT("French", "fra");
		addLanguageT("Georgian", "kat");
		addLanguageT("German", "deu");
		addLanguageT("Greek", "ell");
		addLanguageT("Hebrew", "heb");
		addLanguageT("Hindi", "hin");
		addLanguageT("Hungarian", "hun");
		addLanguageT("English", "eng");
		addLanguageT("Icelandic", "isl");
		addLanguageT("Indonesian", "ind");
		addLanguageT("Irish", "gai");
		addLanguageT("Italian", "ita");
		addLanguageT("Japanese", "jpn");
		addLanguageT("Kashmiri", "kas");
		addLanguageT("Kongo", "kon");
		addLanguageT("Korean", "kor");
		addLanguageT("Latvian", "lav");
		addLanguageT("Lithuanian", "lit");
		addLanguageT("Macedonian", "mkd");
		addLanguageT("Malay", "msa");
		addLanguageT("Maltese", "mlt");
		addLanguageT("Maori", "mri");
		addLanguageT("Moldavian", "mol");
		addLanguageT("Mongolian", "mon");
		addLanguageT("Norwegian", "nor");
		addLanguageT("Punjabi", "pan");
		addLanguageT("Persian", "fas");
		addLanguageT("Polish", "pol");
		addLanguageT("Portuguese", "por");
		addLanguageT("Romanian", "ron");
		addLanguageT("Russian", "rus");
		addLanguageT("Serbian", "srp");
		addLanguageT("Slovak", "slk");
		addLanguageT("Slovenian", "slv");
		addLanguageT("Spanish", "spa");
		addLanguageT("Swahili", "swa");
		addLanguageT("Swedish", "swe");
		addLanguageT("Thai", "tha");
		addLanguageT("Tibetan", "bod");
		addLanguageT("Turkish", "tur");
		addLanguageT("Urdu", "urd");
		addLanguageT("Ukrainian", "ukr");
		addLanguageT("Uzbek", "uzb");
		addLanguageT("Vietnamese", "vie");
		addLanguageT("Welsh", "cym");
		addLanguageT("Zhuang", "zha");
		addLanguageT("Zulu", "zul");
		addLanguageT("Zuni", "zun");
	}

	LanguageSelectionContainer::LanguageSelectionContainer()
	{
	}

	std::string LanguageSelectionContainer::lookupISOCode(const std::string &code)
	{
		if (languagesReverseBibliographic.find(code) != languagesReverseBibliographic.end())
			return languagesReverseBibliographic[code];
		else if (languagesReverseTerminology.find(code) != languagesReverseTerminology.end())
			return languagesReverseTerminology[code];
		else
			return "";
	}

	std::string LanguageSelectionContainer::getISO639dot1(const std::string &iso639dot2)
	{
		for (unknown::const_iterator ci = System::Globalization::CultureInfo::GetCultures(System::Globalization::CultureTypes::AllCultures).begin(); ci != System::Globalization::CultureInfo::GetCultures(System::Globalization::CultureTypes::AllCultures).end(); ++ci)
		{
			if ((*ci)->ThreeLetterISOLanguageName == iso639dot2) // we found our language
			{
				//if (ci.TwoLetterISOLanguageName.Length == 2) // sometimes we get 3 letter codes here, divxmux can't handle those
					return (*ci)->TwoLetterISOLanguageName;
			}
		}
		return 0;
	}

	std::string LanguageSelectionContainer::Short2FullLanguageName(const std::string &LngCode)
	{
		std::string Language = "";
//C# TO C++ CONVERTER NOTE: The following 'switch' operated on a string variable and was converted to C++ 'if-else' logic:
//		switch (LngCode.ToLower(System.Globalization.CultureInfo.InvariantCulture))
//ORIGINAL LINE: case "aa":
		if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "aa")
		{
				Language = "Afar";
		}
//ORIGINAL LINE: case "ab":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "ab")
		{
				Language = "Abkhazian";
		}
//ORIGINAL LINE: case "af":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "af")
		{
				Language = "Afrikaans";
		}
//ORIGINAL LINE: case "am":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "am")
		{
				Language = "Amharic";
		}
//ORIGINAL LINE: case "ar":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "ar")
		{
				Language = "Arabic";
		}
//ORIGINAL LINE: case "as":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "as")
		{
				Language = "Assamese";
		}
//ORIGINAL LINE: case "ay":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "ay")
		{
				Language = "Aymara";
		}
//ORIGINAL LINE: case "az":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "az")
		{
				Language = "Azerbaijani";
		}
//ORIGINAL LINE: case "ba":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "ba")
		{
				Language = "Bashkir";
		}
//ORIGINAL LINE: case "be":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "be")
		{
				Language = "Byelorussian";
		}
//ORIGINAL LINE: case "bg":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "bg")
		{
				Language = "Bulgarian";
		}
//ORIGINAL LINE: case "bh":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "bh")
		{
				Language = "Bihari";
		}
//ORIGINAL LINE: case "bi":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "bi")
		{
				Language = "Bislama";
		}
//ORIGINAL LINE: case "bn":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "bn")
		{
				Language = "Bengali; Bangla";
		}
//ORIGINAL LINE: case "bo":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "bo")
		{
				Language = "Tibetan";
		}
//ORIGINAL LINE: case "br":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "br")
		{
				Language = "Breton";
		}
//ORIGINAL LINE: case "ca":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "ca")
		{
				Language = "Catalan";
		}
//ORIGINAL LINE: case "co":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "co")
		{
				Language = "Corsican";
		}
//ORIGINAL LINE: case "cs":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "cs")
		{
				Language = "Czech";
		}
//ORIGINAL LINE: case "cy":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "cy")
		{
				Language = "Welsh";
		}
//ORIGINAL LINE: case "da":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "da")
		{
				Language = "Danish";
		}
//ORIGINAL LINE: case "de":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "de")
		{
				Language = "German";
		}
//ORIGINAL LINE: case "dz":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "dz")
		{
				Language = "Bhutani";
		}
//ORIGINAL LINE: case "el":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "el")
		{
				Language = "Greek";
		}
//ORIGINAL LINE: case "en":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "en")
		{
				Language = "English";
		}
//ORIGINAL LINE: case "eo":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "eo")
		{
				Language = "Esperanto";
		}
//ORIGINAL LINE: case "es":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "es")
		{
				Language = "Spanish";
		}
//ORIGINAL LINE: case "et":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "et")
		{
				Language = "Estonian";
		}
//ORIGINAL LINE: case "eu":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "eu")
		{
				Language = "Basque";
		}
//ORIGINAL LINE: case "fa":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "fa")
		{
				Language = "Persian";
		}
//ORIGINAL LINE: case "fi":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "fi")
		{
				Language = "Finnish";
		}
//ORIGINAL LINE: case "fj":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "fj")
		{
				Language = "Fiji";
		}
//ORIGINAL LINE: case "fo":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "fo")
		{
				Language = "Faroese";
		}
//ORIGINAL LINE: case "fr":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "fr")
		{
				Language = "French";
		}
//ORIGINAL LINE: case "fy":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "fy")
		{
				Language = "Frisian";
		}
//ORIGINAL LINE: case "ga":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "ga")
		{
				Language = "Irish";
		}
//ORIGINAL LINE: case "gd":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "gd")
		{
				Language = "Scots Gaelic";
		}
//ORIGINAL LINE: case "gl":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "gl")
		{
				Language = "Galician";
		}
//ORIGINAL LINE: case "gn":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "gn")
		{
				Language = "Guarani";
		}
//ORIGINAL LINE: case "gu":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "gu")
		{
				Language = "Gujarati";
		}
//ORIGINAL LINE: case "ha":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "ha")
		{
				Language = "Hausa";
		}
//ORIGINAL LINE: case "he":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "he")
		{
				Language = "Hebrew (formerly iw)";
		}
//ORIGINAL LINE: case "hi":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "hi")
		{
				Language = "Hindi";
		}
//ORIGINAL LINE: case "hr":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "hr")
		{
				Language = "Croatian";
		}
//ORIGINAL LINE: case "hu":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "hu")
		{
				Language = "Hungarian";
		}
//ORIGINAL LINE: case "hy":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "hy")
		{
				Language = "Armenian";
		}
//ORIGINAL LINE: case "ia":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "ia")
		{
				Language = "Interlingua";
		}
//ORIGINAL LINE: case "id":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "id")
		{
				Language = "Indonesian (formerly in)";
		}
//ORIGINAL LINE: case "ie":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "ie")
		{
				Language = "Interlingue";
		}
//ORIGINAL LINE: case "ik":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "ik")
		{
				Language = "Inupiak";
		}
//ORIGINAL LINE: case "is":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "is")
		{
				Language = "Icelandic";
		}
//ORIGINAL LINE: case "it":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "it")
		{
				Language = "Italian";
		}
//ORIGINAL LINE: case "iu":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "iu")
		{
				Language = "Inuktitut";
		}
//ORIGINAL LINE: case "iw":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "iw")
		{
				Language = "Hebrew";
		}
//ORIGINAL LINE: case "ja":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "ja")
		{
				Language = "Japanese";
		}
//ORIGINAL LINE: case "jw":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "jw")
		{
				Language = "Javanese";
		}
//ORIGINAL LINE: case "ka":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "ka")
		{
				Language = "Georgian";
		}
//ORIGINAL LINE: case "kk":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "kk")
		{
				Language = "Kazakh";
		}
//ORIGINAL LINE: case "kl":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "kl")
		{
				Language = "Greenlandic";
		}
//ORIGINAL LINE: case "km":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "km")
		{
				Language = "Cambodian";
		}
//ORIGINAL LINE: case "kn":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "kn")
		{
				Language = "Kannada";
		}
//ORIGINAL LINE: case "ko":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "ko")
		{
				Language = "Korean";
		}
//ORIGINAL LINE: case "ks":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "ks")
		{
				Language = "Kashmiri";
		}
//ORIGINAL LINE: case "ku":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "ku")
		{
				Language = "Kurdish";
		}
//ORIGINAL LINE: case "ky":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "ky")
		{
				Language = "Kirghiz";
		}
//ORIGINAL LINE: case "la":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "la")
		{
				Language = "Latin";
		}
//ORIGINAL LINE: case "ln":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "ln")
		{
				Language = "Lingala";
		}
//ORIGINAL LINE: case "lo":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "lo")
		{
				Language = "Laothian";
		}
//ORIGINAL LINE: case "lt":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "lt")
		{
				Language = "Lithuanian";
		}
//ORIGINAL LINE: case "lv":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "lv")
		{
				Language = "Latvian, Lettish";
		}
//ORIGINAL LINE: case "mg":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "mg")
		{
				Language = "Malagasy";
		}
//ORIGINAL LINE: case "mi":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "mi")
		{
				Language = "Maori";
		}
//ORIGINAL LINE: case "mk":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "mk")
		{
				Language = "Macedonian";
		}
//ORIGINAL LINE: case "ml":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "ml")
		{
				Language = "Malayalam";
		}
//ORIGINAL LINE: case "mn":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "mn")
		{
				Language = "Mongolian";
		}
//ORIGINAL LINE: case "mo":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "mo")
		{
				Language = "Moldavian";
		}
//ORIGINAL LINE: case "mr":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "mr")
		{
				Language = "Marathi";
		}
//ORIGINAL LINE: case "ms":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "ms")
		{
				Language = "Malay";
		}
//ORIGINAL LINE: case "mt":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "mt")
		{
				Language = "Maltese";
		}
//ORIGINAL LINE: case "my":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "my")
		{
				Language = "Burmese";
		}
//ORIGINAL LINE: case "na":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "na")
		{
				Language = "Nauru";
		}
//ORIGINAL LINE: case "ne":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "ne")
		{
				Language = "Nepali";
		}
//ORIGINAL LINE: case "nl":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "nl")
		{
				Language = "Dutch";
		}
//ORIGINAL LINE: case "no":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "no")
		{
				Language = "Norwegian";
		}
//ORIGINAL LINE: case "oc":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "oc")
		{
				Language = "Occitan";
		}
//ORIGINAL LINE: case "om":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "om")
		{
				Language = "(Afan) Oromo";
		}
//ORIGINAL LINE: case "or":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "or")
		{
				Language = "Oriya";
		}
//ORIGINAL LINE: case "pa":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "pa")
		{
				Language = "Punjabi";
		}
//ORIGINAL LINE: case "pl":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "pl")
		{
				Language = "Polish";
		}
//ORIGINAL LINE: case "ps":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "ps")
		{
				Language = "Pashto, Pushto";
		}
//ORIGINAL LINE: case "pt":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "pt")
		{
				Language = "Portuguese";
		}
//ORIGINAL LINE: case "qu":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "qu")
		{
				Language = "Quechua";
		}
//ORIGINAL LINE: case "rm":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "rm")
		{
				Language = "Rhaeto-Romance";
		}
//ORIGINAL LINE: case "rn":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "rn")
		{
				Language = "Kirundi";
		}
//ORIGINAL LINE: case "ro":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "ro")
		{
				Language = "Romanian";
		}
//ORIGINAL LINE: case "ru":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "ru")
		{
				Language = "Russian";
		}
//ORIGINAL LINE: case "rw":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "rw")
		{
				Language = "Kinyarwanda";
		}
//ORIGINAL LINE: case "sa":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "sa")
		{
				Language = "Sanskrit";
		}
//ORIGINAL LINE: case "sd":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "sd")
		{
				Language = "Sindhi";
		}
//ORIGINAL LINE: case "sg":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "sg")
		{
				Language = "Sangho";
		}
//ORIGINAL LINE: case "sh":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "sh")
		{
				Language = "Serbo-Croatian";
		}
//ORIGINAL LINE: case "si":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "si")
		{
				Language = "Sinhalese";
		}
//ORIGINAL LINE: case "sk":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "sk")
		{
				Language = "Slovak";
		}
//ORIGINAL LINE: case "sl":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "sl")
		{
				Language = "Slovenian";
		}
//ORIGINAL LINE: case "sm":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "sm")
		{
				Language = "Samoan";
		}
//ORIGINAL LINE: case "sn":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "sn")
		{
				Language = "Shona";
		}
//ORIGINAL LINE: case "so":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "so")
		{
				Language = "Somali";
		}
//ORIGINAL LINE: case "sq":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "sq")
		{
				Language = "Albanian";
		}
//ORIGINAL LINE: case "sr":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "sr")
		{
				Language = "Serbian";
		}
//ORIGINAL LINE: case "ss":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "ss")
		{
				Language = "Siswati";
		}
//ORIGINAL LINE: case "st":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "st")
		{
				Language = "Sesotho";
		}
//ORIGINAL LINE: case "su":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "su")
		{
				Language = "Sundanese";
		}
//ORIGINAL LINE: case "sv":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "sv")
		{
				Language = "Swedish";
		}
//ORIGINAL LINE: case "sw":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "sw")
		{
				Language = "Swahili";
		}
//ORIGINAL LINE: case "ta":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "ta")
		{
				Language = "Tamil";
		}
//ORIGINAL LINE: case "te":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "te")
		{
				Language = "Telugu";
		}
//ORIGINAL LINE: case "tg":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "tg")
		{
				Language = "Tajik";
		}
//ORIGINAL LINE: case "th":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "th")
		{
				Language = "Thai";
		}
//ORIGINAL LINE: case "ti":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "ti")
		{
				Language = "Tigrinya";
		}
//ORIGINAL LINE: case "tk":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "tk")
		{
				Language = "Turkmen";
		}
//ORIGINAL LINE: case "tl":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "tl")
		{
				Language = "Tagalog";
		}
//ORIGINAL LINE: case "tn":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "tn")
		{
				Language = "Setswana";
		}
//ORIGINAL LINE: case "to":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "to")
		{
				Language = "Tonga";
		}
//ORIGINAL LINE: case "tr":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "tr")
		{
				Language = "Turkish";
		}
//ORIGINAL LINE: case "ts":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "ts")
		{
				Language = "Tsonga";
		}
//ORIGINAL LINE: case "tt":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "tt")
		{
				Language = "Tatar";
		}
//ORIGINAL LINE: case "tw":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "tw")
		{
				Language = "Twi";
		}
//ORIGINAL LINE: case "ug":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "ug")
		{
				Language = "Uighur";
		}
//ORIGINAL LINE: case "uk":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "uk")
		{
				Language = "Ukrainian";
		}
//ORIGINAL LINE: case "ur":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "ur")
		{
				Language = "Urdu";
		}
//ORIGINAL LINE: case "uz":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "uz")
		{
				Language = "Uzbek";
		}
//ORIGINAL LINE: case "vi":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "vi")
		{
				Language = "Vietnamese";
		}
//ORIGINAL LINE: case "vo":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "vo")
		{
				Language = "Volapuk";
		}
//ORIGINAL LINE: case "wo":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "wo")
		{
				Language = "Wolof";
		}
//ORIGINAL LINE: case "xh":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "xh")
		{
				Language = "Xhosa";
		}
//ORIGINAL LINE: case "yi":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "yi")
		{
				Language = "Yiddish (formerly ji)";
		}
//ORIGINAL LINE: case "yo":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "yo")
		{
				Language = "Yoruba";
		}
//ORIGINAL LINE: case "za":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "za")
		{
				Language = "Zhuang";
		}
//ORIGINAL LINE: case "zh":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "zh")
		{
				Language = "Chinese";
		}
//ORIGINAL LINE: case "zu":
		else if (LngCode.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "zu")
		{
				Language = "Zulu";
		}
		return Language;
	}
}
