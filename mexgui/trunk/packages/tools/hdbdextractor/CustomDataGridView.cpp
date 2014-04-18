#include "CustomDataGridView.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Drawing;
namespace MeGUI
{
	namespace packages
	{
		namespace tools
		{
			namespace hdbdextractor
			{

				CustomDataGridView::CustomDataGridView() : DataGridView()
				{
					VerticalScrollBar->Visible = true;
					VerticalScrollBar::VisibleChanged += new EventHandler(this, &CustomDataGridView::VerticalScrollBar_VisibleChanged);
				}

				void CustomDataGridView::VerticalScrollBar_VisibleChanged(object *sender, EventArgs *e)
				{
					if (!VerticalScrollBar->Visible)
					{
						VerticalScrollBar->Location = new Point(ClientRectangle->Width - VerticalScrollBar->Width, 1);
						VerticalScrollBar->Size = new Size(VerticalScrollBar->Width, ClientRectangle->Height - 1); // - HorizontalScrollBar.Height);
						VerticalScrollBar::Show();
					}

					VerticalScrollBar->Visible = true;
				}
			}
		}
	}
}
