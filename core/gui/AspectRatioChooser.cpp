#include "AspectRatioChooser.h"
#include "ui_AspectRatioChooser.h"

using namespace MeXgui::core::util;

namespace MeXgui
{
	namespace core
	{
		namespace gui
		{

			AspectRatioChooser::AspectRatioChooser()
			{
                QDialog(parent),
                ui(new Ui::Dialogexample)
                {
                ui->setupUi(this);
                }
                connect(ui . ,SIGNAL(clicked()), this, SLOT(accept()));
                connect(this->rejectButton, SIGNAL(clicked()), this, SLOT(reject()));
                connect(this, SIGNAL(finished (int)), this, SLOT(dialogIsFinished(int)));
			}

			DialogResult *AspectRatioChooser::show(Dar defaultDar, Dar &newDar)
			{
				AspectRatioChooser *n = new AspectRatioChooser();
				n->SetValues(defaultDar);
				if (defaultDar.getY() < 1)
					n->radioButton2->Checked = true;
				else
					n->radioButton1->Checked = true;

				DialogResult *r = n->show();
				if (n->radioButton1->Checked)
					newDar = Dar(n->numericUpDown1->Value);
				else
					newDar = Dar(static_cast<quint64>(n->numericUpDown2->Value), static_cast<quint64>(n->numericUpDown3->Value));
				return r;
			}

			void AspectRatioChooser::SetValues(Dar ar)
			{
				bDisableEvents = true;
                if (ar.getAR() >= numericUpDown1->Minimum && ar.getAR() <= numericUpDown1->Maximum)
					numericUpDown1->Value = ar.getAR();
				if (ar.getX() >= numericUpDown2->Minimum && ar.getX() <= numericUpDown2->Maximum)
					numericUpDown2->Value = ar.getX();
				if (ar.getY() >= numericUpDown3->Minimum && ar.getY() <= numericUpDown3->Maximum)
					numericUpDown3->Value = ar.getY();
				bDisableEvents = false;
			}

			void AspectRatioChooser::radioButton_CheckedChanged(QObject *sender, QEvent *e)
			{
				numericUpDown1->Enabled = radioButton1->Checked;
				numericUpDown2->Enabled = numericUpDown3->Enabled = !radioButton1->Checked;
			}

			void AspectRatioChooser::numericUpDown2_ValueChanged(QObject *sender, QEvent *e)
			{
				if (bDisableEvents)
					return;
				bDisableEvents = true;
				Dar ar = Dar(static_cast<quint64>(numericUpDown2->Value), static_cast<quint64>(numericUpDown3->Value));
				if (ar.getAR() >= numericUpDown1->Minimum && ar.getAR() <= numericUpDown1->Maximum)
					numericUpDown1->Value = ar.getAR();
				bDisableEvents = false;
			}

			void AspectRatioChooser::numericUpDown1_ValueChanged(QObject *sender, QEvent *e)
			{
				if (bDisableEvents)
					return;
				bDisableEvents = true;
				Dar ar = Dar(numericUpDown1->Value);
				if (ar.getX() >= numericUpDown2->Minimum && ar.getX() <= numericUpDown2->Maximum)
					numericUpDown2->Value = ar.getX();
				if (ar.getY() >= numericUpDown3->Minimum && ar.getY() <= numericUpDown3->Maximum)
					numericUpDown3->Value = ar.getY();
				bDisableEvents = false;
			}

            AspectRatioChooser::~AspectRatioChooser()
            {
                delete ui;
            }
		}
	}
}
