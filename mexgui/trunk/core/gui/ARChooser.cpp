#include "ARChooser.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::ComponentModel;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;
using namespace MeGUI::core::util;
namespace MeGUI
{
	namespace core
	{
		namespace gui
		{

			void ARChooser::Dispose(bool disposing)
			{
				if (MainForm::Instance != 0) // Form designer fix
					MainForm::Instance->getSettings()->setCustomDARs(getCustomDARs());
				StandardAndCustomComboBox::Dispose(disposing);
			}

            const std::string ARChooser::Later = "Auto-detect later";
            const Named<Dar> ARChooser::ARs[7] = {new Named<Dar>("ITU 16:9 PAL (1.823361)", Dar::ITU16x9PAL), new Named<Dar>("ITU 4:3 PAL (1.367521)", Dar::ITU4x3PAL), new Named<Dar>("ITU 16:9 NTSC (1.823169)", Dar::ITU16x9NTSC), new Named<Dar>("ITU 4:3 NTSC (1.367377)", Dar::ITU4x3NTSC), new Named<Dar>("4:3 (1.333333)", Dar::STATIC4x3), new Named<Dar>("16:9 (1.777778)", Dar::STATIC16x9), new Named<Dar>("1:1", Dar::A1x1)};

			ARChooser::ARChooser() : StandardAndCustomComboBox("Clear user-selected ARs...", "Select AR...")
			{
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
				StandardAndCustomComboBox::Getter = delegate
				{
					Dar result;
					Nullable<Dar> tempVar = getValue();
					if (AspectRatioChooser::ShowDialog(tempVar::HasValue ? tempVar : Dar::ITU16x9PAL, result) == DialogResult::OK)
						return result;
					else
						return 0;
				};

				setHasLater(true);

				if (MainForm::Instance != 0) // Form designer fix
					setCustomDARs(MainForm::Instance->getSettings()->getCustomDARs());
			}

			const bool &ARChooser::getHasLater() const
			{
				return hasLater;
			}

			void ARChooser::setHasLater(const bool &value)
			{
				hasLater = value;
				if (hasLater)
				{
					std::vector<object*> o = std::vector<object*>();
					o.push_back(Later);
					o.AddRange(ARs);
					StandardAndCustomComboBox::setStandardItems(o.ToArray());
				}
				else
				{
					StandardAndCustomComboBox::setStandardItems(ARs);
				}
			}

			const Nullable<Dar> &ARChooser::getValue() const
			{
				if (getSelectedObject()->Equals(Later))
					return 0;
				if (dynamic_cast<Named<Dar>*>(getSelectedObject()) != 0)
					return (static_cast<Named<Dar>*>(getSelectedObject()))->Data;
				else
					return (static_cast<Dar>(getSelectedObject()));
			}

			void ARChooser::setValue(const Nullable<Dar> &value)
			{
				if (!value.HasValue)
					setSelectedObject(Later);
				else
					setSelectedObject(value);
			}

			const MeGUI::core::util::Dar &ARChooser::getRealValue() const
			{
				if (getHasLater())
					throw std::exception("For OneClicker, use Value");
				return getValue().Value;
			}

			void ARChooser::setRealValue(const Dar &value)
			{
				setValue(value);
			}

			const Dar &ARChooser::getCustomDARs() const
			{
				return Util::CastAll<Dar>(getCustomItems());
			}

			void ARChooser::setCustomDARs(const Dar &value[])
			{
				if (value == 0 || value->Length == 0)
					return;
				StandardAndCustomComboBox::setCustomItems(Util::CastAll<Dar, object*>(value));
			}
		}
	}
}
