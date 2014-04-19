#include "JobWorkerWindow.h"




//using namespace System::Collections::Generic;



//using namespace System::Data;

//using namespace System::Diagnostics;





//using namespace System::Threading;

//using namespace System::Text;


using namespace MeXgui::core::details;
using namespace MeXgui::core::util;
namespace MeXgui
{
	namespace core
	{
		namespace gui
		{

			const QString &NameTakenException::getName() const
			{
				return name;
			}

			NameTakenException::NameTakenException(const QString &name) : MeXguiException("Worker name '" + name + "' is already in use.")
			{
				this->name = name;
			}
		}
	}
}
