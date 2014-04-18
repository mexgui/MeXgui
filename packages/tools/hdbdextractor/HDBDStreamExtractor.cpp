#include "HDBDStreamExtractor.h"




//using namespace System::Collections::Generic;



//using namespace System::Diagnostics;

//using namespace System::Text;

//using namespace System::Text::RegularExpressions;


using namespace MeXgui::core::plugins::interfaces;
using namespace MeXgui::core::details;
using namespace MeXgui::core::util;
using namespace eac3to;
namespace MeXgui
{
	namespace packages
	{
		namespace tools
		{
			namespace hdbdextractor
			{

				const QString &HdBdExtractorTool::getName() const
				{
					return "HD Streams Extractor";
				}

				void HdBdExtractorTool::Run(MainForm *info)
				{
					(new HdBdStreamExtractor(info))->Show();
				}

				const Shortcut &HdBdExtractorTool::getShortcuts() const
				{
					return new Shortcut[] {Shortcut::CtrlF7};
				}

				const QString &HdBdExtractorTool::getID() const
				{
					return getName();
				}
			}
		}
	}
}
