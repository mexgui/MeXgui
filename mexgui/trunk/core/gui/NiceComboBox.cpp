#include "NiceComboBox.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::ComponentModel;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Data;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Diagnostics;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Drawing;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;
namespace MeGUI
{
	namespace core
	{
		namespace gui
		{

			const bool &NiceComboBoxItem::getTicked() const
			{
				return ticked;
			}

			void NiceComboBoxItem::setTicked(const bool &value)
			{
				ticked = value;
			}

			NiceComboBoxItem::NiceComboBoxItem(const std::string &name, object *tag)
			{
				Name = name;
				Tag = tag;
			}

			void NiceComboBoxNormalItem::OnClick()
			{
				ItemClicked(this, new EventArgs());
			}

			NiceComboBoxNormalItem::NiceComboBoxNormalItem(const std::string &name, object *tag) : NiceComboBoxItem(name,tag)
			{
				InitializeInstanceFields();
			}

			NiceComboBoxNormalItem::NiceComboBoxNormalItem(const std::string &name, object *tag, NiceComboBoxItemClicked handler)
			{
				InitializeInstanceFields();
				ItemClicked += handler;
				Selectable = false;
			}

			NiceComboBoxNormalItem::NiceComboBoxNormalItem(object *stringableObject)
			{
				InitializeInstanceFields();
			}

			NiceComboBoxNormalItem::NiceComboBoxNormalItem(object *stringableObject, NiceComboBoxItemClicked handler)
			{
				InitializeInstanceFields();
			}

			void NiceComboBoxNormalItem::InitializeInstanceFields()
			{
				Selectable = true;
			}

			NiceComboBoxSubMenuItem::NiceComboBoxSubMenuItem(const std::string &name, object *tag, ...) : NiceComboBoxItem(name, tag)
			{
				SubItems = std::vector<NiceComboBoxItem*>(subItems);
			}

			NiceComboBoxSubMenuItem::NiceComboBoxSubMenuItem(object *stringableObject, ...)
			{
			}

			NiceComboBoxSeparator::NiceComboBoxSeparator() : NiceComboBoxItem(0, 0)
			{
			}
		}
	}
}
