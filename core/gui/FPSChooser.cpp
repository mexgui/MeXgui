#include "FPSChooser.h"




//using namespace System::Collections::Generic;



//using namespace System::Text;


using namespace MeXgui::core::util;
namespace MeXgui
{
	namespace core
	{
		namespace gui
		{

const object FPSChooser::Framerates[8] = {FPS(23.976), FPS(24.0), FPS(25.0), FPS(29.97), FPS(30.0), FPS(50.0), FPS(59.94), FPS(60.0)};

			FPSChooser::FPSChooser() : StandardAndCustomComboBox("Clear user-selected framerates...", "Select framerate...")
			{
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
				StandardAndCustomComboBox::Getter = delegate
				{
					decimal result;
					Nullable<decimal> tempVar = getValue();
					if (NumberChooser::show("Enter your framerate:", "Custom framerate", 3, 1, 1000, tempVar::HasValue ? tempVar : 25, result) == DialogResult::OK)
						return FPS(result);
					else
						return 0;
				};
				setStandardItems(Framerates);
				if (MainForm::Instance != 0) // form designer fix
					setCustomFPSs(MainForm::Instance->getSettings()->getCustomFPSs());
			}

			void FPSChooser::Dispose(bool disposing)
			{
				if (MainForm::Instance != 0) // form designer fix
					MainForm::Instance->getSettings()->setCustomFPSs(getCustomFPSs());
				StandardAndCustomComboBox::Dispose(disposing);
			}

			const QString &FPSChooser::getNullString() const
			{
				return nullString;
			}

			void FPSChooser::setNullString(const QString &value)
			{
				nullString = value;
				fillStandard();
			}

			void FPSChooser::fillStandard()
			{
				QVector<object*> objects = QVector<object*>();
				if (!getNullString().empty())
					objects.push_back(getNullString());
				objects.AddRange(Framerates);
				StandardAndCustomComboBox::setStandardItems(objects.ToArray());

			}

			const FPS &FPSChooser::getCustomFPSs() const
			{
				return Util::CastAll<FPS>(getCustomItems());
			}

			void FPSChooser::setCustomFPSs(const FPS &value[])
			{
				if (value == 0 || value->Length == 0)
					return;
				setCustomItems(Util::CastAll<FPS, object*>(value));
			}

			const Nullable<decimal> &FPSChooser::getValue() const
			{
				if (getSelectedObject()->Equals(getNullString()))
					return 0;
				return (static_cast<FPS>(getSelectedObject())).fps;
			}

			void FPSChooser::setValue(const Nullable<decimal> &value)
			{
				if (!value.HasValue)
				{
					setSelectedObject(getNullString());
					return;
				}
				if (value.GetValueOrDefault() == 0)
					return;
				setSelectedObject(FPS(value.Value));
			}

			const decimal &FPSChooser::getCertainValue() const
			{
				return getValue().Value;
			}

			void FPSChooser::setCertainValue(const decimal &value)
			{
				setValue(value);
			}

			FPS::FPS(decimal v)
			{
				fps = v;
			}

			QString FPS::ToString()
			{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
				return fps.ToString();
			}

			MeXgui::core::gui::FPS FPS::Parse(const QString &s)
			{
				return FPS(decimal::Parse(s));
			}

			bool FPS::Equals(object *obj)
			{
				if (!(dynamic_cast<FPS>(obj) != 0))
					return false;
				decimal other = (static_cast<FPS>(obj)).fps;
				return (abs(fps - other) < MainForm::Instance->getSettings()->getAcceptableFPSError());
			}

			int FPS::GetHashCode()
			{
				return 0;
			}

			bool FPSConverter::CanConvertFrom(ITypeDescriptorContext *context, Type *sourceType)
			{
				return (sourceType == QString::typeid);
			}

			object *FPSConverter::ConvertFrom(ITypeDescriptorContext *context, System::Globalization::CultureInfo *culture, object *value)
			{
				if (dynamic_cast<QString>(value) != 0)
					return FPS::Parse(static_cast<QString>(value));

				throw std::exception();
			}

			object *FPSConverter::ConvertTo(ITypeDescriptorContext *context, System::Globalization::CultureInfo *culture, object *value, Type *destinationType)
			{
				if (destinationType == QString::typeid)
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
					return value->ToString();

				return TypeConverter::ConvertTo(context, culture, value, destinationType);
			}
		}
	}
}
