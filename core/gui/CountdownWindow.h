#pragma once

#include "core/util/LogItem.h"
#include "UpdateWindow.h"
#include <QString>
#include "stringconverter.h"

// ****************************************************************************
// 
// Copyright (C) 2005-2009  Doom9 & al
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
// 
// ****************************************************************************




//using namespace System::Collections::Generic;



//using namespace System::Data;



//using namespace System::Text;



namespace MeXgui
{
	namespace core
	{
		namespace gui
		{
            class CountdownWindow : public QDialog
			{
                Q_OBJECT
			private:
				int countdown;
				int remain;

				public:
                ~CountdownWindow();


//C# TO C++ CONVERTER WARNING: Unlike C#, there is no automatic call to this finalizer method in native C++:
				private:


			public:


				CountdownWindow(int countdown);
                ~CountdownWindow();

			private:
				void CountdownWindow_Load(QObject *sender, QEvent *e);

				typedef void (*UpdateProgressBar)(int minValue, int maxValue, int currentValue);
				void SetProgressBar(int minValue, int maxValue, int currentValue);

				typedef void (*UpdateCancelButton)(const QString &text);
				void SetButtonText(const QString &text);

				/// <summary>
				/// TimerTick. Refresh the ProgressBar and the Button.
				/// </summary>
				void TimerTick(QObject *sender, System::QEvent *e);

                QTimer *timer;
                MeXgui::core::gui::CountdownWindow *ui;

			private:
				void InitializeInstanceFields();
			};
		}
	}
}
