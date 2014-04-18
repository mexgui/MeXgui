#include "FileSCBox.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
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

			FileSCBox::FileSCBox() : StandardAndCustomComboBox("Clear user-selected files...", "Select file...")
			{
				InitializeInstanceFields();
				StandardAndCustomComboBox::Getter = new Getter(this, &FileSCBox::getter);
				StandardAndCustomComboBox::bSaveEveryItem = true;
			}

			object *FileSCBox::getter()
			{
				if (ofd->ShowDialog() == DialogResult::OK)
					return ofd->FileName;
				return 0;
			}

			object *FileSCBox::getterFolder()
			{
				if (fbd->ShowDialog() == DialogResult::OK)
				{
					MainForm::Instance->getSettings()->setLastUsedOneClickFolder(fbd->SelectedPath);
					return fbd->SelectedPath;
				}
				return 0;
			}

			const std::string &FileSCBox::getFilter() const
			{
				return ofd->Filter;
			}

			void FileSCBox::setFilter(const std::string &value)
			{
				ofd->Filter = value;
			}

			const MeGUI::core::gui::FileSCBox::FileSCBoxType &FileSCBox::getType() const
			{
				return oType;
			}

			void FileSCBox::setType(const FileSCBoxType &value)
			{
				oType = value;
				if (oType == OC_FILE || oType == OC_FILE_AND_FOLDER)
				{
					StandardAndCustomComboBox::SetFileSCBoxType("Select file...", "Select folder...", oType);
					if (oType == OC_FILE_AND_FOLDER)
					{
						StandardAndCustomComboBox::GetterFolder = new Getter(this, &FileSCBox::getterFolder);
						if (MainForm::Instance != 0 && System::IO::Directory::Exists(MainForm::Instance->getSettings()->getLastUsedOneClickFolder()))
							fbd->SelectedPath = MainForm::Instance->getSettings()->getLastUsedOneClickFolder();
					}
				}
			}

			void FileSCBox::InitializeInstanceFields()
			{
				ofd = new OpenFileDialog();
				fbd = new FolderBrowserDialog();
				oType = Default;
			}
		}
	}
}
