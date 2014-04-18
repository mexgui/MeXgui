#include "MeGUI.core.gui.StandardAndCustomComboBox.h"




//using namespace System::Collections::Generic;



//using namespace System::Configuration;

//using namespace System::Data;



//using namespace System::Text;


using namespace MeGUI::core::util;
namespace MeGUI
{
	namespace core
	{
		namespace gui
		{
			SCItem::SCItem(object *tag, bool isStandard)
			{
				Tag = tag;
				IsStandard = isStandard;
			}

			QString SCItem::ToString()
			{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
				return Tag->ToString();
			}
			
			StandardAndCustomComboBox::StandardAndCustomComboBox() : MeGUI::core::gui::NiceComboBox()
			{
				InitializeInstanceFields();
			}

			StandardAndCustomComboBox::StandardAndCustomComboBox(const QString &clearText, const QString &chooseNewText) : MeGUI::core::gui::NiceComboBox()
			{
				InitializeInstanceFields();
				InitializeComponent();

				numOpener = 1;

//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
				clearItem = new NiceComboBoxNormalItem(clearText, delegate(NiceComboBoxNormalItem i, QEvent e)
				{
					clearCustomItems();
				}
			   );

//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
				Items.push_back(new NiceComboBoxNormalItem(chooseNewText, 0, delegate(NiceComboBoxNormalItem i, QEvent e)
				{
					object *o = Getter();
					if (o != 0)
					{
						AddCustomItem(o);
						setSelectedObject(o);
					}
				}
			   ));
			}

			void StandardAndCustomComboBox::SetFileSCBoxType(const QString &chooseNewText, const QString &chooseNewFolder, MeGUI::core::gui::FileSCBox::FileSCBoxType oType)
			{
				if (oType == FileSCBox::OC_FILE_AND_FOLDER || oType == FileSCBox::OC_FILE)
				{
					Items.clear();
//C# TO C++ CONVERTER WARNING: C# to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
					delete clearItem;

					numOpener = 1;

//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
					Items.push_back(new NiceComboBoxNormalItem(chooseNewText, 0, delegate(NiceComboBoxNormalItem i, QEvent e)
					{
						object *o = Getter();
						if (o != 0)
						{
							AddCustomItem(o);
							setSelectedObject(o);
						}
					}
				   ));
				}
				if (oType == FileSCBox::OC_FILE_AND_FOLDER)
				{
					numOpener = 2;

//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
					Items.push_back(new NiceComboBoxNormalItem(chooseNewFolder, 0, delegate(NiceComboBoxNormalItem i, QEvent e)
					{
						object *o = GetterFolder();
						if (o != 0)
						{
							AddCustomItem(o);
							setSelectedObject(o);
						}
					}
				   ));
				}
				numStandardItems = numCustomItems = 0;
			}

			void StandardAndCustomComboBox::SetTargetSizeSCBoxType(const QString &clearText, const QString &chooseCustomSize)
			{
				Items.clear();
				numOpener = 1;
				numStandardItems = numCustomItems = 0;

//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
				Items.push_back(new NiceComboBoxNormalItem(chooseCustomSize, 0, delegate(NiceComboBoxNormalItem i, QEvent e)
				{
					object *o = Getter();
					if (o != 0)
					{
						if (bSaveEveryItem)
						{
							AddCustomItem(o);
							setSelectedObject(o);
						}
						else
						{
							oTemporaryItem->Tag = o;
//C# TO C++ CONVERTER WARNING: C# to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
							delete getSelectedItem();
						}
					}
				}
			   ));

//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
				clearItem = new NiceComboBoxNormalItem(clearText, delegate(NiceComboBoxNormalItem i, QEvent e)
				{
					clearCustomItems();
				}
			   );

				if (!bSaveEveryItem)
//C# TO C++ CONVERTER WARNING: C# to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
					delete clearItem;
			}

			void StandardAndCustomComboBox::AddStandardItem(object *o)
			{
				if (numStandardItems == 0)
					Items.Insert(0, new NiceComboBoxSeparator());

				Items.Insert(numStandardItems, new NiceComboBoxNormalItem(new SCItem(o, true)));
				numStandardItems++;
			}

			void StandardAndCustomComboBox::AddCustomItem(object *name)
			{
				if (numCustomItems == 0)
				{
					Items.Insert(Items.size() - numOpener, new NiceComboBoxSeparator());
					if (clearItem != 0)
						Items.Insert(Items.size() - numOpener, clearItem);
				}

				if (clearItem != 0)
					Items.Insert(Items.size() - 2 - numOpener, new NiceComboBoxNormalItem(new SCItem(name, false)));
				else
					Items.Insert(Items.size() - 1 - numOpener, new NiceComboBoxNormalItem(new SCItem(name, false)));
				numCustomItems++;
			}

			void StandardAndCustomComboBox::clearStandardItems()
			{
				if (numStandardItems == 0)
					return;

				Items.RemoveRange(0, numStandardItems + 1);
				numStandardItems = 0;
			}

			void StandardAndCustomComboBox::clearCustomItems()
			{
				int start = getCustomItemStart();

				if (getSelectedIndex() >= start)
					setSelectedIndex(0);

				Items.RemoveRange(start, numCustomItems);
				if (numCustomItems > 0)
				{
					Items.RemoveAt(start);
					if (clearItem != 0)
						Items.RemoveAt(start);
				}

				numCustomItems = 0;
			}

			int StandardAndCustomComboBox::getCustomItemStart()
			{
				if (numStandardItems > 0)
					return numStandardItems + 1;
				return 0;
			}

			const object &StandardAndCustomComboBox::getCustomItems() const
			{
				object res[numCustomItems];
				int start = getCustomItemStart();

				for (int i = 0; i < numCustomItems; ++i)
				{
					res[i] = (static_cast<SCItem*>(Items[start + i]->Tag))->Tag;
				}
				return res;
			}

			void StandardAndCustomComboBox::setCustomItems(const object &value[])
			{
				clearCustomItems();
				if (value == 0)
					return;
				for (object[]::const_iterator s = value->begin(); s != value->end(); ++s)
					AddCustomItem(*s);
			}

			const object &StandardAndCustomComboBox::getStandardItems() const
			{
				object res[numStandardItems];

				for (int i = 0; i < numStandardItems; ++i)
				{
					res[i] = (dynamic_cast<SCItem*>(Items[i]->Tag))->Tag;
				}
				return res;
			}

			void StandardAndCustomComboBox::setStandardItems(const object &value[])
			{
				clearStandardItems();
				for (object[]::const_iterator o = value->begin(); o != value->end(); ++o)
					AddStandardItem(*o);
				if (getSelectedIndex() == -1 && value->Length > 0)
					setSelectedIndex(0);
			}

			const object &StandardAndCustomComboBox::getSelectedObject() const
			{
				return getSelectedSCItem()->Tag;
			}

			void StandardAndCustomComboBox::setSelectedObject(const object &value)
			{
//C# TO C++ CONVERTER WARNING: C# to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
				delete oTemporaryItem->Tag;

				if (value == 0)
					return;

//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
				if (value->ToString() == "")
					return;

				for (QVector<NiceComboBoxItem*>::const_iterator i = Items.begin(); i != Items.end(); ++i)
				{
					if (static_cast<dynamic_cast<SCItem*>((*i)->Tag)*>(!) = 0 && (static_cast<SCItem*>((*i)->Tag))->Tag->Equals(value))
					{
						setSelectedItem(*i);
						return;
					}
				}
				if (bSaveEveryItem)
				{
					AddCustomItem(value);
					setSelectedObject(value);
				}
				else
				{
					oTemporaryItem->Tag = value;
//C# TO C++ CONVERTER WARNING: C# to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
					delete getSelectedItem();
				}
			}

			const MeGUI::core::gui::SCItem &StandardAndCustomComboBox::getSelectedSCItem() const
			{
				if (oTemporaryItem->Tag != 0 && getSelectedItem() == 0)
					return oTemporaryItem;

				if (getSelectedItem() == 0)
					setSelectedIndex(0);

				return static_cast<SCItem*>(getSelectedItem()->Tag);
			}

			void StandardAndCustomComboBox::Dispose(bool disposing)
			{
				if (disposing && (components != 0))
				{
					delete components;
				}
				MeGUI::core::gui::NiceComboBox::Dispose(disposing);
			}

			void StandardAndCustomComboBox::InitializeComponent()
			{
				this->components = new System::ComponentModel::Container();
			}

			void StandardAndCustomComboBox::InitializeInstanceFields()
			{
				delete components;
			}
		}
	}
}
