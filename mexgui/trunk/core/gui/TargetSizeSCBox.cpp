#include "TargetSizeSCBox.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::ComponentModel;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Diagnostics;
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

const Named<FileSize> TargetSizeSCBox::PredefinedFilesizes[5] = {new Named<FileSize>("CD  (700MB)", FileSize(MB, 700)), new Named<FileSize>("DVD or BD-5  (4480MB)", FileSize(MB, 4480)), new Named<FileSize>("DVD-DL or BD-9 (8145MB)", FileSize(MB, 8145)), new Named<FileSize>("BD  (23450MB)", FileSize(MB, 23450)), new Named<FileSize>("BD-DL  (46900MB)", FileSize(MB, 46900))};

			void TargetSizeSCBox::Dispose(bool disposing)
			{
				if (MainForm::Instance != 0 && StandardAndCustomComboBox::bSaveEveryItem) // form designer fix
					MainForm::Instance->getSettings()->setCustomFileSizes(getCustomSizes());
				StandardAndCustomComboBox::Dispose(disposing);
			}

			const std::string &TargetSizeSCBox::getNullString() const
			{
				return nullString;
			}

			void TargetSizeSCBox::setNullString(const std::string &value)
			{
				nullString = value;
				fillStandard();
			}

			const MeGUI::core::util::FileSize &TargetSizeSCBox::getMinimumFileSize() const
			{
				return minSize;
			}

			void TargetSizeSCBox::setMinimumFileSize(const FileSize &value)
			{
				minSize = value;
			}

			const Nullable<FileSize> &TargetSizeSCBox::getMaximumFileSize() const
			{
				return maxSize;
			}

			void TargetSizeSCBox::setMaximumFileSize(const Nullable<FileSize> &value)
			{
				maxSize = value;
			}

			TargetSizeSCBox::TargetSizeSCBox() : StandardAndCustomComboBox("Remove custom sizes...", "Select custom size...")
			{
				InitializeInstanceFields();
				StandardAndCustomComboBox::Getter = new Getter(this, &TargetSizeSCBox::getter);
				StandardAndCustomComboBox::bSaveEveryItem = true;
				setSaveCustomValues(false);
				if (MainForm::Instance != 0) // form designer fix
					setCustomSizes(MainForm::Instance->getSettings()->getCustomFileSizes());
			}

			void TargetSizeSCBox::fillStandard()
			{
				std::vector<object*> objects = std::vector<object*>();
				if (!getNullString().empty())
					objects.push_back(getNullString());
				objects.AddRange(TargetSizeSCBox::PredefinedFilesizes);
				StandardAndCustomComboBox::setStandardItems(objects.ToArray());
			}

			object *TargetSizeSCBox::getter()
			{
				Nullable<FileSize> tempVar = getValue();
				ofd->setValue(tempVar::HasValue ? tempVar : FileSize(MB, 700));
				if (ofd->ShowDialog() == DialogResult::OK)
				{
					if (ofd->getValue() >= minSize && !maxSize.HasValue || ofd->getValue() <= maxSize)
						return ofd->getValue();
					else
						MessageBox::Show(genRestrictions(), "Invalid filesize", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				}
				return 0;
			}

			const FileSize &TargetSizeSCBox::getCustomSizes() const
			{
				return Util::CastAll<FileSize>(getCustomItems());
			}

			void TargetSizeSCBox::setCustomSizes(const FileSize &value[])
			{
				if (value == 0 || value->Length == 0)
					return;
				setCustomItems(Util::CastAll<FileSize, object*>(value));
			}

			std::string TargetSizeSCBox::genRestrictions()
			{
				if (maxSize.HasValue)
					return std::string::Format("Filesize must be between {0} and {1}.", minSize, maxSize);
				else
					return std::string::Format("Filesize must be at least {0}.", minSize);
			}

			const Nullable<FileSize> &TargetSizeSCBox::getValue() const
			{
				object *o = StandardAndCustomComboBox::getSelectedObject();
				if (o->Equals(getNullString()))
					return 0;
				if (dynamic_cast<Named<FileSize>*>(o) != 0)
					return (static_cast<Named<FileSize>*>(o))->Data;
				else
					return static_cast<FileSize>(o);
			}

			void TargetSizeSCBox::setValue(const Nullable<FileSize> &value)
			{
				if (value.HasValue)
					StandardAndCustomComboBox::setSelectedObject(value.Value);
				else
					StandardAndCustomComboBox::setSelectedObject(getNullString());
			}

			const MeGUI::core::util::FileSize &TargetSizeSCBox::getCertainValue() const
			{
				return getValue().Value;
			}

			void TargetSizeSCBox::setCertainValue(const FileSize &value)
			{
				setValue(value);
			}

			const bool &TargetSizeSCBox::getSaveCustomValues() const
			{
				return StandardAndCustomComboBox::bSaveEveryItem;
			}

			void TargetSizeSCBox::setSaveCustomValues(const bool &value)
			{
				if (StandardAndCustomComboBox::bSaveEveryItem != value)
				{
					StandardAndCustomComboBox::bSaveEveryItem = value;
					StandardAndCustomComboBox::SetTargetSizeSCBoxType("Remove custom sizes...", "Select custom size...");
					fillStandard();
					if (MainForm::Instance != 0) // form designer fix
						setCustomSizes(MainForm::Instance->getSettings()->getCustomFileSizes());
				}
			}

			void TargetSizeSCBox::InitializeInstanceFields()
			{
				minSize = FileSize::MinNonZero;
				maxSize = Nullable<FileSize>();
				ofd = new FileSizeDialog();
			}
		}
	}
}
