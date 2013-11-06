#include "MeGUI.core.gui.NiceComboBox.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::ComponentModel;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Data;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Diagnostics;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Drawing;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;
namespace MeGUI
{
	namespace core
	{
		namespace gui
		{

			const int &NiceComboBox::getSelectedIndex() const
			{
				if (selectedItem == 0)
					return -1;
				return (Items.find(selectedItem));
			}

			void NiceComboBox::setSelectedIndex(const int &value)
			{
				if (value == -1)
//C# TO C++ CONVERTER WARNING: C# to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
					delete getSelectedItem();
				else
					setSelectedItem(Items[value]);
			}

			const MeGUI::core::gui::NiceComboBoxItem &NiceComboBox::getSelectedItem() const
			{
				return selectedItem;
			}

			void NiceComboBox::setSelectedItem(const NiceComboBoxItem &value)
			{
				if (selectedItem != 0)
					selectedItem->setTicked(false);
				if (value != 0)
					value->setTicked(true);

				selectedItem = value;

				if (value != 0)
					textBox1->Text = value->Name;
				else if (oTemporaryItem->Tag != 0)
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
					textBox1->Text = oTemporaryItem->Tag->ToString();
				else
					textBox1->Text = "";

				SelectionChanged(this, textBox1->Text);
			}

			const std::string &NiceComboBox::getSelectedText() const
			{
				return textBox1->Text;
			}

			NiceComboBox::NiceComboBox() : Items(new List<NiceComboBoxItem>())
			{
				InitializeInstanceFields();
				InitializeComponent();
				oTemporaryItem = new SCItem(0, false);
			}

			void NiceComboBox::dropDownButton_Click(object *sender, EventArgs *e)
			{
				ContextMenuStrip *s = new ContextMenuStrip();
				s->Items->AddRange(createMenu(Items));
				s->Show(dropDownButton, 0, dropDownButton->Height);
			}

			ToolStripItem *NiceComboBox::createMenu(std::vector<NiceComboBoxItem*> &items)
			{
				ToolStripItem result[items.size()];

				int index = 0;
				for (std::vector<NiceComboBoxItem*>::const_iterator i = items.begin(); i != items.end(); ++i)
				{
					if (dynamic_cast<NiceComboBoxSeparator*>(*i) != 0)
						result[index] = new ToolStripSeparator();
					else
					{
						ToolStripMenuItem *t = new ToolStripMenuItem((*i)->Name);
						t->Checked = (*i)->getTicked();
						t->Tag = *i;
						if (dynamic_cast<NiceComboBoxNormalItem*>(*i) != 0)
							t->Click += new EventHandler(this, &NiceComboBox::item_Click);
						else if (dynamic_cast<NiceComboBoxSubMenuItem*>(*i) != 0)
						{
							t->DropDownItems->AddRange(createMenu((static_cast<NiceComboBoxSubMenuItem*>(*i))->SubItems));
						}
						else
							assert(false);

						result[index] = t;
					}
					++index;
				}
				return result;
			}

			void NiceComboBox::item_Click(object *sender, EventArgs *e)
			{
				ToolStripItem *i = static_cast<ToolStripItem*>(sender);
				NiceComboBoxNormalItem *item = static_cast<NiceComboBoxNormalItem*>(i->Tag);
				if (item->Selectable)
					setSelectedItem(item);

				item->OnClick();
			}

			void NiceComboBox::Dispose(bool disposing)
			{
				if (disposing && (components != 0))
				{
					delete components;
				}
				UserControl::Dispose(disposing);
			}

			void NiceComboBox::InitializeComponent()
			{
				this->components = new System::ComponentModel::Container();
				this->dropDownButton = new System::Windows::Forms::Button();
				this->textBox1 = new System::Windows::Forms::TextBox();
				this->contextMenuStrip1 = new System::Windows::Forms::ContextMenuStrip(this->components);
				this->helloToolStripMenuItem = new System::Windows::Forms::ToolStripMenuItem();
				this->hiToolStripMenuItem = new System::Windows::Forms::ToolStripMenuItem();
				this->hereToolStripMenuItem = new System::Windows::Forms::ToolStripMenuItem();
				this->toolStripSeparator1 = new System::Windows::Forms::ToolStripSeparator();
				this->toolStripTextBox1 = new System::Windows::Forms::ToolStripTextBox();
				this->tableLayoutPanel1 = new System::Windows::Forms::TableLayoutPanel();
				this->contextMenuStrip1->SuspendLayout();
				this->tableLayoutPanel1->SuspendLayout();
				this->SuspendLayout();
				// 
				// dropDownButton
				// 
				this->dropDownButton->Anchor = System::Windows::Forms::AnchorStyles::None;
				this->dropDownButton->AutoSize = true;
				this->dropDownButton->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
				this->dropDownButton->Font = new System::Drawing::Font("Marlett", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, (static_cast<unsigned char>(2)));
				this->dropDownButton->Location = new System::Drawing::Point(179, 3);
				this->dropDownButton->Margin = new System::Windows::Forms::Padding(3, 1, 1, 1);
				this->dropDownButton->Name = "dropDownButton";
				this->dropDownButton->Size = new System::Drawing::Size(28, 22);
				this->dropDownButton->TabIndex = 0;
				this->dropDownButton->Text = "6";
				this->dropDownButton->UseVisualStyleBackColor = true;
				this->dropDownButton->Click += new System::EventHandler(this, &NiceComboBox::dropDownButton_Click);
				// 
				// textBox1
				// 
				this->textBox1->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right)));
				this->textBox1->Location = new System::Drawing::Point(1, 4);
				this->textBox1->Margin = new System::Windows::Forms::Padding(1, 0, 0, 0);
				this->textBox1->Name = "textBox1";
				this->textBox1->ReadOnly = true;
				this->textBox1->Size = new System::Drawing::Size(175, 20);
				this->textBox1->TabIndex = 1;
				// 
				// contextMenuStrip1
				// 
				this->contextMenuStrip1->Items->AddRange(new System::Windows::Forms::ToolStripItem[4] {this->helloToolStripMenuItem, this->hereToolStripMenuItem, this->toolStripSeparator1, this->toolStripTextBox1});
				this->contextMenuStrip1->Name = "contextMenuStrip1";
				this->contextMenuStrip1->Size = new System::Drawing::Size(161, 79);
				// 
				// helloToolStripMenuItem
				// 
				this->helloToolStripMenuItem->DropDownItems->AddRange(new System::Windows::Forms::ToolStripItem[1] {this->hiToolStripMenuItem});
				this->helloToolStripMenuItem->Name = "helloToolStripMenuItem";
				this->helloToolStripMenuItem->Size = new System::Drawing::Size(160, 22);
				this->helloToolStripMenuItem->Text = "Hello";
				// 
				// hiToolStripMenuItem
				// 
				this->hiToolStripMenuItem->Name = "hiToolStripMenuItem";
				this->hiToolStripMenuItem->Size = new System::Drawing::Size(86, 22);
				this->hiToolStripMenuItem->Text = "Hi";
				// 
				// hereToolStripMenuItem
				// 
				this->hereToolStripMenuItem->Name = "hereToolStripMenuItem";
				this->hereToolStripMenuItem->Size = new System::Drawing::Size(160, 22);
				this->hereToolStripMenuItem->Text = "Here";
				// 
				// toolStripSeparator1
				// 
				this->toolStripSeparator1->Name = "toolStripSeparator1";
				this->toolStripSeparator1->Size = new System::Drawing::Size(157, 6);
				// 
				// toolStripTextBox1
				// 
				this->toolStripTextBox1->Name = "toolStripTextBox1";
				this->toolStripTextBox1->Size = new System::Drawing::Size(100, 23);
				this->toolStripTextBox1->Text = "aoeu";
				// 
				// tableLayoutPanel1
				// 
				this->tableLayoutPanel1->AutoSize = true;
				this->tableLayoutPanel1->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
				this->tableLayoutPanel1->ColumnCount = 2;
				this->tableLayoutPanel1->ColumnStyles->Add(new System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 100));
				this->tableLayoutPanel1->ColumnStyles->Add(new System::Windows::Forms::ColumnStyle());
				this->tableLayoutPanel1->Controls->Add(this->textBox1, 0, 0);
				this->tableLayoutPanel1->Controls->Add(this->dropDownButton, 1, 0);
				this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
				this->tableLayoutPanel1->Location = new System::Drawing::Point(0, 0);
				this->tableLayoutPanel1->Name = "tableLayoutPanel1";
				this->tableLayoutPanel1->RowCount = 1;
				this->tableLayoutPanel1->RowStyles->Add(new System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100));
				this->tableLayoutPanel1->Size = new System::Drawing::Size(208, 28);
				this->tableLayoutPanel1->TabIndex = 2;
				// 
				// NiceComboBox
				// 
				this->AutoScaleDimensions = new System::Drawing::SizeF(6, 13);
				this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				this->Controls->Add(this->tableLayoutPanel1);
				this->MaximumSize = new System::Drawing::Size(1000, 28);
				this->MinimumSize = new System::Drawing::Size(64, 28);
				this->Name = "NiceComboBox";
				this->Size = new System::Drawing::Size(208, 28);
				this->contextMenuStrip1->ResumeLayout(false);
				this->contextMenuStrip1->PerformLayout();
				this->tableLayoutPanel1->ResumeLayout(false);
				this->tableLayoutPanel1->PerformLayout();
				this->ResumeLayout(false);
				this->PerformLayout();

			}

			void NiceComboBox::InitializeInstanceFields()
			{
				delete components;
			}
		}
	}
}
