#include "CustomDataGridView.h"







namespace MeXgui
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

				void CustomDataGridView::VerticalScrollBar_VisibleChanged()
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
