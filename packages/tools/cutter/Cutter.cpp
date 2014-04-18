#include "Cutter.h"




//using namespace System::Collections::Generic;



//using namespace System::Data;



//using namespace System::Text;


using namespace MeXgui::core::util;
namespace MeXgui
{
	namespace packages
	{
		namespace tools
		{
			namespace cutter
			{

				const QString &CutterTool::getName() const
				{
					return "AVS Cutter";
				}

				void CutterTool::Run(MainForm *info)
				{
					OpenFileDialog *d = new OpenFileDialog();
					d->Filter = "AviSynth scripts (*.avs)|*.avs";
					d->Title = "Select the input video";
					if (d->show() != DialogResult::OK)
						return;
					(new Cutter(info, d->FileName))->Show();
				}

				const Shortcut &CutterTool::getShortcuts() const
				{
					return new Shortcut[] {Shortcut::CtrlD};
				}

				const QString &CutterTool::getID() const
				{
					return getName();
				}
			}
		}
	}
}
