#include "MeGUI.packages.tools.calculator.ExtraSizeTab.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::ComponentModel;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Data;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Drawing;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;
using namespace MeGUI::core::details;
using namespace MeGUI::core::util;
using namespace MediaInfoWrapper;
namespace MeGUI
{
	namespace packages
	{
		namespace tools
		{
			namespace calculator
			{

				ExtraSizeTab::ExtraSizeTab() : filter("All Files (*.*)|*.*")
				{
					InitializeInstanceFields();
					InitializeComponent();
					//DragDropUtil.RegisterSingleFileDragDrop(this, selectExtraFile, this.filter);
				}

				void ExtraSizeTab::raiseEvent()
				{
					SomethingChanged(this, EventArgs::Empty);
				}

				void ExtraSizeTab::selectExtraFile(const std::string &file)
				{
					setFileSize(((getFileSize().Of2(file)) != 0) ? getFileSize().Of2(file) : getFileSize().Empty);
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
					size->Text = getFileSize().ToString();
					name->Text = System::IO::Path::GetFileName(file);
					raiseEvent();
				}

				const MeGUI::core::util::FileSize &ExtraSizeTab::getFileSize() const
				{
					return privateFileSize;
				}

				void ExtraSizeTab::setFileSize(const MeGUI::core::util::FileSize &value)
				{
					privateFileSize = value;
				}

				void ExtraSizeTab::selectButton_Click(object *sender, EventArgs *e)
				{
					openFileDialog->Filter = this->filter;
					if (openFileDialog->ShowDialog() == DialogResult::OK)
					{
						selectExtraFile(openFileDialog->FileName);
					}
				}

				void ExtraSizeTab::removeLink_LinkClicked(object *sender, EventArgs *e)
				{
					if (this->Parent != 0)
						this->Parent->Controls->Remove(this);
				}

				void ExtraSizeTab::selectButton_Enter(object *sender, EventArgs *e)
				{
					selectButton->Focus();
				}

				void ExtraSizeTab::Dispose(bool disposing)
				{
					if (disposing && (components != 0))
					{
						delete components;
					}
					UserControl::Dispose(disposing);
				}

				void ExtraSizeTab::InitializeComponent()
				{
					this->components = new System::ComponentModel::Container();
					System::ComponentModel::ComponentResourceManager *resources = new System::ComponentModel::ComponentResourceManager(ExtraSizeTab::typeid);
					this->label2 = new System::Windows::Forms::Label();
					this->selectButton = new System::Windows::Forms::Button();
					this->openFileDialog = new System::Windows::Forms::OpenFileDialog();
					this->audioLabel = new System::Windows::Forms::Label();
					this->name = new System::Windows::Forms::TextBox();
					this->size = new System::Windows::Forms::TextBox();
					this->removeLink = new System::Windows::Forms::LinkLabel();
					this->removalToolTip = new System::Windows::Forms::ToolTip(this->components);
					this->SuspendLayout();
					// 
					// label2
					// 
					this->label2->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right)));
					this->label2->AutoSize = true;
					this->label2->Location = new System::Drawing::Point(354, 8);
					this->label2->Name = "label2";
					this->label2->Size = new System::Drawing::Size(27, 13);
					this->label2->TabIndex = 22;
					this->label2->Text = "Size";
					// 
					// selectButton
					// 
					this->selectButton->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right)));
					this->selectButton->Location = new System::Drawing::Point(313, 27);
					this->selectButton->Name = "selectButton";
					this->selectButton->Size = new System::Drawing::Size(24, 21);
					this->selectButton->TabIndex = 1;
					this->selectButton->Text = "...";
					this->selectButton->Click += new System::EventHandler(this, &ExtraSizeTab::selectButton_Click);
					this->selectButton->Enter += new System::EventHandler(this, &ExtraSizeTab::selectButton_Enter);
					// 
					// audioLabel
					// 
					this->audioLabel->Location = new System::Drawing::Point(30, 8);
					this->audioLabel->Name = "audioLabel";
					this->audioLabel->Size = new System::Drawing::Size(40, 16);
					this->audioLabel->TabIndex = 31;
					this->audioLabel->Text = "Extra";
					// 
					// name
					// 
					this->name->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
					this->name->Location = new System::Drawing::Point(8, 28);
					this->name->Name = "name";
					this->name->ReadOnly = true;
					this->name->Size = new System::Drawing::Size(303, 20);
					this->name->TabIndex = 0;
					this->name->TabStop = false;
					this->name->Enter += new System::EventHandler(this, &ExtraSizeTab::selectButton_Click);
					// 
					// size
					// 
					this->size->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right)));
					this->size->Location = new System::Drawing::Point(357, 28);
					this->size->Name = "size";
					this->size->ReadOnly = true;
					this->size->Size = new System::Drawing::Size(70, 20);
					this->size->TabIndex = 2;
					this->size->TabStop = false;
					// 
					// removeLink
					// 
					this->removeLink->Cursor = System::Windows::Forms::Cursors::Hand;
					this->removeLink->Image = (static_cast<System::Drawing::Image*>(resources->GetObject("removeLink.Image")));
					this->removeLink->Location = new System::Drawing::Point(5, 3);
					this->removeLink->Name = "removeLink";
					this->removeLink->Padding = new System::Windows::Forms::Padding(16, 0, 3, 3);
					this->removeLink->Size = new System::Drawing::Size(27, 23);
					this->removeLink->TabIndex = 3;
					this->removeLink->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
					this->removalToolTip->SetToolTip(this->removeLink, "Extra data");
					this->removeLink->LinkClicked += new System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &ExtraSizeTab::removeLink_LinkClicked);
					this->removeLink->Click += new System::EventHandler(this, &ExtraSizeTab::removeLink_LinkClicked);
					// 
					// removalToolTip
					// 
					this->removalToolTip->AutomaticDelay = 300;
					this->removalToolTip->ToolTipTitle = "Remove";
					// 
					// ExtraSizeTab
					// 
					this->AutoScaleDimensions = new System::Drawing::SizeF(6, 13);
					this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
					this->Controls->Add(this->removeLink);
					this->Controls->Add(this->size);
					this->Controls->Add(this->name);
					this->Controls->Add(this->audioLabel);
					this->Controls->Add(this->label2);
					this->Controls->Add(this->selectButton);
					this->Name = "ExtraSizeTab";
					this->Size = new System::Drawing::Size(435, 50);
					this->ResumeLayout(false);
					this->PerformLayout();

				}

				void ExtraSizeTab::InitializeInstanceFields()
				{
					delete components;
				}
			}
		}
	}
}
