#include "JobWorkerWindow.h"




//using namespace System::Collections::Generic;



//using namespace System::Data;

//using namespace System::Diagnostics;





//using namespace System::Threading;

//using namespace System::Text;


using namespace MeGUI::core::details;
using namespace MeGUI::core::util;
namespace MeGUI
{
	namespace core
	{
		namespace gui
		{

			const QString &NameTakenException::getName() const
			{
				return name;
			}

			NameTakenException::NameTakenException(const QString &name) : MeGUIException("Worker name '" + name + "' is already in use.")
			{
				this->name = name;
			}
		}
	}
}
