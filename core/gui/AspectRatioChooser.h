#ifndef ASPECTRATIOCHOSER_H
#define ASPECTRATIOCHOSER_H

// ****************************************************************************
// 
// Copyright (C) 2005-2013 Doom9 , al & Qt part 2014-> Jeroi
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

#include "core/util/DAR.h"
#include "core/util/LogItem.h"
#include <QDialog>


using namespace MeXgui::core::util;


namespace MeXgui
{
	namespace core
	{
		namespace gui
		{
        class AspectRatioChooser: public QDialog
        {
            Q_OBJECT

        public:
            explicit AspectRatioChooser(QWidget *parent = 0);

            static DialogResult *show(Dar defaultDar, Dar &newDar);

            void SetValues(Dar ar);
            ~AspectRatioChooser();

        private:
            MeXgui::core::gui::AspectRatioChooser *ui;
            bool bDisableEvents;

            void radioButton_CheckedChanged(QObject *sender, QEvent *e);
            void numericUpDown2_ValueChanged(QObject *sender, QEvent *e);
            void numericUpDown1_ValueChanged(QObject *sender, QEvent *e);

        };
		}
	}
}



#endif // ASPECTRATIOCHOSER_H
