#include "MeGUI.packages.tools.cutter.Cutter.h"

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
using namespace MeGUI::core::util;
namespace MeGUI
{
	namespace packages
	{
		namespace tools
		{
			namespace cutter
			{

				Cutter::Cutter(MainForm *mainForm, const std::string &scriptName)
				{
					InitializeInstanceFields();
					InitializeComponent();
					this->scriptName = scriptName;

					transitionStyle->DataSource = EnumProxy::CreateArray(TransitionStyle::typeid);
					transitionStyle->BindingContext = new BindingContext();

					avsScript->Text += scriptName;

					openPreview(mainForm);
				}

				void Cutter::openPreview(MainForm *mainForm)
				{
					player = new VideoPlayer();
					bool videoLoaded = player->loadVideo(mainForm, scriptName, ZONES, false);
					if (!videoLoaded)
						return;

					startFrame->Maximum = endFrame->Maximum = player->getReader()->getFrameCount() - 1;
					cuts->Framerate = player->getFramerate();
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
					avsScript->Text += "   (" + cuts->Framerate.ToString("##.###") + "FPS)";

					player->setAllowClose(false);
					player->ZoneSet += new ZoneSetCallback(this, &Cutter::player_ZoneSet);
					player->Show();
					player->SetScreenSize();
					this->TopMost = player->TopMost = true;
					if (!mainForm->getSettings()->getAlwaysOnTop())
						this->TopMost = player->TopMost = false;
				}

				void Cutter::player_ZoneSet(int start, int end)
				{
					startFrame->Value = start;
					endFrame->Value = end;
					addZoneButton_Click(0, 0);
				}

				void Cutter::addZoneButton_Click(object *sender, EventArgs *e)
				{
					if (addSelectedSection())
						updateListView();
				}

				bool Cutter::addSelectedSection()
				{
					CutSection *s = new CutSection();
					s->startFrame = static_cast<int>(startFrame->Value);
					s->endFrame = static_cast<int>(endFrame->Value);

					if (s->endFrame <= s->startFrame)
					{
						MessageBox::Show("The end frame must be larger than the start frame", "Invalid section configuration", MessageBoxButtons::OK, MessageBoxIcon::Stop);
						return false;
					}

					if (!cuts->addSection(s))
					{
						MessageBox::Show("Section overlaps with another", "Invalid configuration", MessageBoxButtons::OK, MessageBoxIcon::Stop);
						return false;
					}
					return true;
				}

				void Cutter::updateListView()
				{
					sections->BeginUpdate();
					sections->Items->Clear();
					for (std::vector<CutSection*>::const_iterator cut = cuts->getAllCuts().begin(); cut != cuts->getAllCuts().end(); ++cut)
					{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
						ListViewItem *item = new ListViewItem(new std::string[] {(*cut)->startFrame->ToString(), (*cut)->endFrame->ToString()});
						item->Tag = *cut;
						sections->Items->Add(item);
						if (item->Index % 2 != 0)
							item->BackColor = Color::White;
						else
							item->BackColor = Color::WhiteSmoke;
					}
					clearZonesButton->Enabled = sections->Items->Count > 0;
					sections->EndUpdate();
				}

				void Cutter::clearZonesButton_Click(object *sender, EventArgs *e)
				{
					if (MessageBox::Show("Are you sure you want to clear all sections?", "Are you sure?", MessageBoxButtons::YesNo, MessageBoxIcon::Warning) != System::Windows::Forms::DialogResult::Yes)
						return;

					cuts->Clear();
					updateListView();
				}

				void Cutter::updateZoneButton_Click(object *sender, EventArgs *e)
				{
					Cuts *old = cuts->clone();
					removeSelectedZones();

					if (addSelectedSection())
						updateListView();
					else
						cuts = old;
				}

				void Cutter::removeSelectedZones()
				{
					for (unknown::const_iterator item = sections->SelectedItems.begin(); item != sections->SelectedItems.end(); ++item)
					{
						cuts->remove(static_cast<CutSection*>((*item)->Tag));
					}
				}

				void Cutter::sections_ItemSelectionChanged(object *sender, ListViewItemSelectionChangedEventArgs *e)
				{
					removeZoneButton->Enabled = sections->SelectedItems->Count > 0;
					updateZoneButton->Enabled = sections->SelectedItems->Count == 1;
				}

				void Cutter::removeZoneButton_Click(object *sender, EventArgs *e)
				{
					if (MessageBox::Show("Are you sure you want to delete the selected sections?", "Are you sure?", MessageBoxButtons::YesNo, MessageBoxIcon::Warning) != System::Windows::Forms::DialogResult::Yes)
						return;
					removeSelectedZones();
					updateListView();
				}

				void Cutter::OnClosing(CancelEventArgs *e)
				{
					player->setAllowClose(true);
					player->Close();
//C# TO C++ CONVERTER WARNING: C# to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
					delete player;
					System::Windows::Forms::Form::OnClosing(e);
				}

				void Cutter::closeButton_Click(object *sender, EventArgs *e)
				{
					Close();
				}

				void Cutter::transitionStyle_SelectedIndexChanged(object *sender, EventArgs *e)
				{
					cuts->Style = static_cast<TransitionStyle>(transitionStyle->SelectedIndex);
				}

				void Cutter::addCutsToScript_Click(object *sender, EventArgs *e)
				{
					if (cutsAdded)
					{
						MessageBox::Show("Cuts already added; can't cut again", "Cuts already added", MessageBoxButtons::OK, MessageBoxIcon::Error);
						return;
					}
					if (cuts->getAllCuts().empty())
					{
						MessageBox::Show("At least one section must be created", "No sections created", MessageBoxButtons::OK, MessageBoxIcon::Error);
						return;
					}
					FilmCutter::WriteCutsToScript(scriptName, cuts, false);
					MessageBox::Show("Cuts written!", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
					cutsAdded = true;
					avsScript->Text += "*";
				}

				void Cutter::saveCuts_Click(object *sender, EventArgs *e)
				{
					if (cuts->getAllCuts().empty())
					{
						MessageBox::Show("At least one section must be created", "No sections created", MessageBoxButtons::OK, MessageBoxIcon::Error);
						return;
					}

					SaveFileDialog *d = new SaveFileDialog();
					d->Filter = "MeGUI cut list (*.clt)|*.clt";
					d->Title = "Select a place to save the cut list";
					if (d->ShowDialog() != System::Windows::Forms::DialogResult::OK)
						return;

					FilmCutter::WriteCutsToFile(d->FileName, cuts);
					MessageBox::Show("Cuts written!", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
				}

				void Cutter::doAllClose_Click(object *sender, EventArgs *e)
				{
					if (cuts->getAllCuts().empty())
					{
						MessageBox::Show("At least one section must be created", "No sections created", MessageBoxButtons::OK, MessageBoxIcon::Error);
						return;
					}
					if (cutsAdded)
					{
						if (MessageBox::Show("Cuts already added to script, if you have altered cuts the cutfile will not match\n\r Continue?", "Cuts already added", MessageBoxButtons::YesNo, MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::No)
						{
							return;
						}
					}
					std::string savecutsto = scriptName + ".clt";
					if (System::IO::File::Exists(savecutsto))
					{
						DialogResult *result = MessageBox::Show("Cutfile already exists, overwrite?", "Overwrite cutfile", MessageBoxButtons::YesNoCancel, MessageBoxIcon::Question);
						if (result == System::Windows::Forms::DialogResult::Cancel)
							return;

						if (result == System::Windows::Forms::DialogResult::No)
						{
							SaveFileDialog *d = new SaveFileDialog();
							d->Filter = "MeGUI cut list (*.clt)|*.clt";
							d->Title = "Select a place to save the cut list";
							if (d->ShowDialog() != System::Windows::Forms::DialogResult::OK)
								return;
							savecutsto = d->FileName;
						}
					}

					if (!cutsAdded)
					{
						FilmCutter::WriteCutsToScript(scriptName, cuts, false);
					}
					FilmCutter::WriteCutsToFile(savecutsto, cuts);
					Close();


				}

				void Cutter::sections_SelectedIndexChanged(object *sender, EventArgs *e)
				{
					if (sections->SelectedItems->Count != 1)
						return;

					startFrame->Value = (static_cast<CutSection*>(sections->SelectedItems[0]->Tag))->startFrame;
					endFrame->Value = (static_cast<CutSection*>(sections->SelectedItems[0]->Tag))->endFrame;
				}

				void Cutter::Dispose(bool disposing)
				{
					if (disposing && (components != 0))
					{
						delete components;
					}
					System::Windows::Forms::Form::Dispose(disposing);
				}

				void Cutter::InitializeComponent()
				{
					System::ComponentModel::ComponentResourceManager *resources = new System::ComponentModel::ComponentResourceManager(Cutter::typeid);
					this->flowLayoutPanel1 = new System::Windows::Forms::FlowLayoutPanel();
					this->addZoneButton = new System::Windows::Forms::Button();
					this->clearZonesButton = new System::Windows::Forms::Button();
					this->updateZoneButton = new System::Windows::Forms::Button();
					this->removeZoneButton = new System::Windows::Forms::Button();
					this->label1 = new System::Windows::Forms::Label();
					this->transitionStyle = new System::Windows::Forms::ComboBox();
					this->startFrameLabel = new System::Windows::Forms::Label();
					this->endFrameLabel = new System::Windows::Forms::Label();
					this->tableLayoutPanel1 = new System::Windows::Forms::TableLayoutPanel();
					this->startFrame = new System::Windows::Forms::NumericUpDown();
					this->endFrame = new System::Windows::Forms::NumericUpDown();
					this->flowLayoutPanel2 = new System::Windows::Forms::FlowLayoutPanel();
					this->doAllClose = new System::Windows::Forms::Button();
					this->closeButton = new System::Windows::Forms::Button();
					this->saveCuts = new System::Windows::Forms::Button();
					this->addCutsToScript = new System::Windows::Forms::Button();
					this->helpButton1 = new MeGUI::core::gui::HelpButton();
					this->avsScript = new System::Windows::Forms::Label();
					this->groupBox1 = new System::Windows::Forms::GroupBox();
					this->sections = new System::Windows::Forms::ListView();
					this->columnHeader1 = (static_cast<System::Windows::Forms::ColumnHeader*>(new System::Windows::Forms::ColumnHeader()));
					this->columnHeader2 = (static_cast<System::Windows::Forms::ColumnHeader*>(new System::Windows::Forms::ColumnHeader()));
					this->flowLayoutPanel1->SuspendLayout();
					this->tableLayoutPanel1->SuspendLayout();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->startFrame))->BeginInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->endFrame))->BeginInit();
					this->flowLayoutPanel2->SuspendLayout();
					this->groupBox1->SuspendLayout();
					this->SuspendLayout();
					// 
					// flowLayoutPanel1
					// 
					this->flowLayoutPanel1->AutoSize = true;
					this->flowLayoutPanel1->Controls->Add(this->addZoneButton);
					this->flowLayoutPanel1->Controls->Add(this->clearZonesButton);
					this->flowLayoutPanel1->Controls->Add(this->updateZoneButton);
					this->flowLayoutPanel1->Controls->Add(this->removeZoneButton);
					this->flowLayoutPanel1->Controls->Add(this->label1);
					this->flowLayoutPanel1->Controls->Add(this->transitionStyle);
					this->flowLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Bottom;
					this->flowLayoutPanel1->Location = new System::Drawing::Point(0, 354);
					this->flowLayoutPanel1->Name = "flowLayoutPanel1";
					this->flowLayoutPanel1->Padding = new System::Windows::Forms::Padding(5);
					this->flowLayoutPanel1->Size = new System::Drawing::Size(476, 39);
					this->flowLayoutPanel1->TabIndex = 0;
					// 
					// addZoneButton
					// 
					this->addZoneButton->AutoSize = true;
					this->addZoneButton->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
					this->addZoneButton->Location = new System::Drawing::Point(8, 8);
					this->addZoneButton->Name = "addZoneButton";
					this->addZoneButton->Size = new System::Drawing::Size(36, 23);
					this->addZoneButton->TabIndex = 16;
					this->addZoneButton->Text = "Add";
					this->addZoneButton->Click += new System::EventHandler(this, &Cutter::addZoneButton_Click);
					// 
					// clearZonesButton
					// 
					this->clearZonesButton->AutoSize = true;
					this->clearZonesButton->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
					this->clearZonesButton->Enabled = false;
					this->clearZonesButton->Location = new System::Drawing::Point(50, 8);
					this->clearZonesButton->Name = "clearZonesButton";
					this->clearZonesButton->Size = new System::Drawing::Size(42, 23);
					this->clearZonesButton->TabIndex = 14;
					this->clearZonesButton->Text = "Clear";
					this->clearZonesButton->Click += new System::EventHandler(this, &Cutter::clearZonesButton_Click);
					// 
					// updateZoneButton
					// 
					this->updateZoneButton->AutoSize = true;
					this->updateZoneButton->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
					this->updateZoneButton->Enabled = false;
					this->updateZoneButton->Location = new System::Drawing::Point(98, 8);
					this->updateZoneButton->Name = "updateZoneButton";
					this->updateZoneButton->Size = new System::Drawing::Size(52, 23);
					this->updateZoneButton->TabIndex = 17;
					this->updateZoneButton->Text = "Update";
					this->updateZoneButton->Click += new System::EventHandler(this, &Cutter::updateZoneButton_Click);
					// 
					// removeZoneButton
					// 
					this->removeZoneButton->AutoSize = true;
					this->removeZoneButton->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
					this->removeZoneButton->Enabled = false;
					this->removeZoneButton->Location = new System::Drawing::Point(156, 8);
					this->removeZoneButton->Name = "removeZoneButton";
					this->removeZoneButton->Size = new System::Drawing::Size(56, 23);
					this->removeZoneButton->TabIndex = 15;
					this->removeZoneButton->Text = "Remove";
					this->removeZoneButton->Click += new System::EventHandler(this, &Cutter::removeZoneButton_Click);
					// 
					// label1
					// 
					this->label1->AutoSize = true;
					this->label1->Dock = System::Windows::Forms::DockStyle::Fill;
					this->label1->Location = new System::Drawing::Point(218, 5);
					this->label1->Name = "label1";
					this->label1->Size = new System::Drawing::Size(80, 29);
					this->label1->TabIndex = 18;
					this->label1->Text = "Transition style";
					this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
					// 
					// transitionStyle
					// 
					this->transitionStyle->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
					this->transitionStyle->FormattingEnabled = true;
					this->transitionStyle->Location = new System::Drawing::Point(304, 8);
					this->transitionStyle->Name = "transitionStyle";
					this->transitionStyle->Size = new System::Drawing::Size(141, 21);
					this->transitionStyle->TabIndex = 19;
					this->transitionStyle->SelectedIndexChanged += new System::EventHandler(this, &Cutter::transitionStyle_SelectedIndexChanged);
					// 
					// startFrameLabel
					// 
					this->startFrameLabel->AutoSize = true;
					this->startFrameLabel->Dock = System::Windows::Forms::DockStyle::Fill;
					this->startFrameLabel->Location = new System::Drawing::Point(8, 5);
					this->startFrameLabel->Name = "startFrameLabel";
					this->startFrameLabel->Size = new System::Drawing::Size(64, 27);
					this->startFrameLabel->TabIndex = 10;
					this->startFrameLabel->Text = "Start Frame";
					this->startFrameLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
					// 
					// endFrameLabel
					// 
					this->endFrameLabel->AutoSize = true;
					this->endFrameLabel->Dock = System::Windows::Forms::DockStyle::Fill;
					this->endFrameLabel->Location = new System::Drawing::Point(8, 32);
					this->endFrameLabel->Name = "endFrameLabel";
					this->endFrameLabel->Size = new System::Drawing::Size(64, 27);
					this->endFrameLabel->TabIndex = 12;
					this->endFrameLabel->Text = "End Frame";
					this->endFrameLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
					// 
					// tableLayoutPanel1
					// 
					this->tableLayoutPanel1->AutoSize = true;
					this->tableLayoutPanel1->ColumnCount = 2;
					this->tableLayoutPanel1->ColumnStyles->Add(new System::Windows::Forms::ColumnStyle());
					this->tableLayoutPanel1->ColumnStyles->Add(new System::Windows::Forms::ColumnStyle());
					this->tableLayoutPanel1->Controls->Add(this->startFrameLabel, 0, 0);
					this->tableLayoutPanel1->Controls->Add(this->endFrameLabel, 0, 1);
					this->tableLayoutPanel1->Controls->Add(this->startFrame, 1, 0);
					this->tableLayoutPanel1->Controls->Add(this->endFrame, 1, 1);
					this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Bottom;
					this->tableLayoutPanel1->Location = new System::Drawing::Point(0, 290);
					this->tableLayoutPanel1->Name = "tableLayoutPanel1";
					this->tableLayoutPanel1->Padding = new System::Windows::Forms::Padding(5);
					this->tableLayoutPanel1->RowCount = 2;
					this->tableLayoutPanel1->RowStyles->Add(new System::Windows::Forms::RowStyle());
					this->tableLayoutPanel1->RowStyles->Add(new System::Windows::Forms::RowStyle());
					this->tableLayoutPanel1->Size = new System::Drawing::Size(476, 64);
					this->tableLayoutPanel1->TabIndex = 14;
					// 
					// startFrame
					// 
					this->startFrame->Dock = System::Windows::Forms::DockStyle::Fill;
					this->startFrame->Location = new System::Drawing::Point(78, 8);
					this->startFrame->Name = "startFrame";
					this->startFrame->Size = new System::Drawing::Size(393, 21);
					this->startFrame->TabIndex = 13;
					// 
					// endFrame
					// 
					this->endFrame->Dock = System::Windows::Forms::DockStyle::Fill;
					this->endFrame->Location = new System::Drawing::Point(78, 35);
					this->endFrame->Name = "endFrame";
					this->endFrame->Size = new System::Drawing::Size(393, 21);
					this->endFrame->TabIndex = 14;
					// 
					// flowLayoutPanel2
					// 
					this->flowLayoutPanel2->AutoSize = true;
					this->flowLayoutPanel2->Controls->Add(this->doAllClose);
					this->flowLayoutPanel2->Controls->Add(this->closeButton);
					this->flowLayoutPanel2->Controls->Add(this->saveCuts);
					this->flowLayoutPanel2->Controls->Add(this->addCutsToScript);
					this->flowLayoutPanel2->Controls->Add(this->helpButton1);
					this->flowLayoutPanel2->Dock = System::Windows::Forms::DockStyle::Bottom;
					this->flowLayoutPanel2->FlowDirection = System::Windows::Forms::FlowDirection::RightToLeft;
					this->flowLayoutPanel2->Location = new System::Drawing::Point(0, 393);
					this->flowLayoutPanel2->Name = "flowLayoutPanel2";
					this->flowLayoutPanel2->Padding = new System::Windows::Forms::Padding(5);
					this->flowLayoutPanel2->Size = new System::Drawing::Size(476, 39);
					this->flowLayoutPanel2->TabIndex = 15;
					// 
					// doAllClose
					// 
					this->doAllClose->Location = new System::Drawing::Point(366, 8);
					this->doAllClose->Name = "doAllClose";
					this->doAllClose->Size = new System::Drawing::Size(97, 23);
					this->doAllClose->TabIndex = 4;
					this->doAllClose->Text = "Do all and close";
					this->doAllClose->UseVisualStyleBackColor = true;
					this->doAllClose->Click += new System::EventHandler(this, &Cutter::doAllClose_Click);
					// 
					// closeButton
					// 
					this->closeButton->AutoSize = true;
					this->closeButton->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
					this->closeButton->DialogResult = System::Windows::Forms::DialogResult::Cancel;
					this->closeButton->Location = new System::Drawing::Point(317, 8);
					this->closeButton->Name = "closeButton";
					this->closeButton->Size = new System::Drawing::Size(43, 23);
					this->closeButton->TabIndex = 0;
					this->closeButton->Text = "Close";
					this->closeButton->UseVisualStyleBackColor = true;
					this->closeButton->Click += new System::EventHandler(this, &Cutter::closeButton_Click);
					// 
					// saveCuts
					// 
					this->saveCuts->AutoSize = true;
					this->saveCuts->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
					this->saveCuts->Location = new System::Drawing::Point(230, 8);
					this->saveCuts->Name = "saveCuts";
					this->saveCuts->Size = new System::Drawing::Size(81, 23);
					this->saveCuts->TabIndex = 1;
					this->saveCuts->Text = "Save cuts file";
					this->saveCuts->UseVisualStyleBackColor = true;
					this->saveCuts->Click += new System::EventHandler(this, &Cutter::saveCuts_Click);
					// 
					// addCutsToScript
					// 
					this->addCutsToScript->AutoSize = true;
					this->addCutsToScript->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
					this->addCutsToScript->Location = new System::Drawing::Point(123, 8);
					this->addCutsToScript->Name = "addCutsToScript";
					this->addCutsToScript->Size = new System::Drawing::Size(101, 23);
					this->addCutsToScript->TabIndex = 2;
					this->addCutsToScript->Text = "Add cuts to script";
					this->addCutsToScript->UseVisualStyleBackColor = true;
					this->addCutsToScript->Click += new System::EventHandler(this, &Cutter::addCutsToScript_Click);
					// 
					// helpButton1
					// 
					this->helpButton1->setArticleName("Avs Cutter");
					this->helpButton1->AutoSize = true;
					this->helpButton1->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
					this->helpButton1->Location = new System::Drawing::Point(79, 8);
					this->helpButton1->Name = "helpButton1";
					this->helpButton1->Size = new System::Drawing::Size(38, 23);
					this->helpButton1->TabIndex = 3;
					// 
					// avsScript
					// 
					this->avsScript->Dock = System::Windows::Forms::DockStyle::Top;
					this->avsScript->Location = new System::Drawing::Point(0, 0);
					this->avsScript->Name = "avsScript";
					this->avsScript->Padding = new System::Windows::Forms::Padding(2);
					this->avsScript->Size = new System::Drawing::Size(476, 21);
					this->avsScript->TabIndex = 17;
					this->avsScript->Text = "AviSynth script:   ";
					// 
					// groupBox1
					// 
					this->groupBox1->Controls->Add(this->sections);
					this->groupBox1->Dock = System::Windows::Forms::DockStyle::Fill;
					this->groupBox1->Location = new System::Drawing::Point(0, 21);
					this->groupBox1->Name = "groupBox1";
					this->groupBox1->Padding = new System::Windows::Forms::Padding(5);
					this->groupBox1->Size = new System::Drawing::Size(476, 269);
					this->groupBox1->TabIndex = 18;
					this->groupBox1->TabStop = false;
					this->groupBox1->Text = "Included sections";
					// 
					// sections
					// 
					this->sections->Columns->AddRange(new System::Windows::Forms::ColumnHeader[2] {this->columnHeader1, this->columnHeader2});
					this->sections->Dock = System::Windows::Forms::DockStyle::Fill;
					this->sections->FullRowSelect = true;
					this->sections->Location = new System::Drawing::Point(5, 19);
					this->sections->Name = "sections";
					this->sections->Size = new System::Drawing::Size(466, 245);
					this->sections->TabIndex = 17;
					this->sections->UseCompatibleStateImageBehavior = false;
					this->sections->View = System::Windows::Forms::View::Details;
					this->sections->ItemSelectionChanged += new System::Windows::Forms::ListViewItemSelectionChangedEventHandler(this, &Cutter::sections_ItemSelectionChanged);
					this->sections->SelectedIndexChanged += new System::EventHandler(this, &Cutter::sections_SelectedIndexChanged);
					// 
					// columnHeader1
					// 
					this->columnHeader1->Text = "Start frame";
					this->columnHeader1->Width = 193;
					// 
					// columnHeader2
					// 
					this->columnHeader2->Text = "End frame";
					this->columnHeader2->Width = 262;
					// 
					// Cutter
					// 
					this->AutoScaleDimensions = new System::Drawing::SizeF(6, 13);
					this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
					this->ClientSize = new System::Drawing::Size(476, 432);
					this->Controls->Add(this->groupBox1);
					this->Controls->Add(this->avsScript);
					this->Controls->Add(this->tableLayoutPanel1);
					this->Controls->Add(this->flowLayoutPanel1);
					this->Controls->Add(this->flowLayoutPanel2);
					this->Font = new System::Drawing::Font("Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, (static_cast<unsigned char>(0)));
					this->Icon = (static_cast<System::Drawing::Icon*>(resources->GetObject("$this.Icon")));
					this->Name = "Cutter";
					this->Text = "MeGUI - AVS Cutter";
					this->flowLayoutPanel1->ResumeLayout(false);
					this->flowLayoutPanel1->PerformLayout();
					this->tableLayoutPanel1->ResumeLayout(false);
					this->tableLayoutPanel1->PerformLayout();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->startFrame))->EndInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->endFrame))->EndInit();
					this->flowLayoutPanel2->ResumeLayout(false);
					this->flowLayoutPanel2->PerformLayout();
					this->groupBox1->ResumeLayout(false);
					this->ResumeLayout(false);
					this->PerformLayout();

				}

				void Cutter::InitializeInstanceFields()
				{
					cutsAdded = false;
					cuts = new Cuts(FADE);
					delete components;
				}
			}
		}
	}
}
