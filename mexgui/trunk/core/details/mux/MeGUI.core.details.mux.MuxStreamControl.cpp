#include "MeGUI.core.details.mux.MuxStreamControl.h"

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
	namespace core
	{
		namespace details
		{
			namespace mux
			{

				MuxStreamControl::MuxStreamControl()
				{
					InitializeInstanceFields();
					InitializeComponent();
					subtitleLanguage->Items->AddRange((std::vector<std::string>(LanguageSelectionContainer::getLanguages().Keys))->ToArray());
				}

				const MeGUI::core::details::MuxStream &MuxStreamControl::getStream() const
				{
					if (input->getFilename().empty())
						return 0;

					int iDelay = 0;
					if (showDelay)
						iDelay = static_cast<int>(audioDelay->Value);
					bool bDefault = false;
					if (showDefaultSubtitleStream)
						bDefault = chkDefaultStream->Checked;
					bool bForce = false;
					if (showForceSubtitleStream)
						bForce = chkForceStream->Checked;

					return new MuxStream(input->getFilename(), subtitleLanguage->Text, subName->Text, iDelay, bDefault, bForce, _trackInfo);
				}

				void MuxStreamControl::setStream(const MuxStream &value)
				{
					if (value == 0)
					{
						removeSubtitleTrack_Click(0, 0);
						return;
					}

					input->setFilename(value->path);
					if (!value->getlanguage().empty())
					{
						if (!(LanguageSelectionContainer::lookupISOCode(value->getlanguage())).empty())
							subtitleLanguage->Text = LanguageSelectionContainer::lookupISOCode(value->getlanguage());
						else
							subtitleLanguage->Text = value->getlanguage();
					}
					subName->Text = value->getname();
					audioDelay->Value = value->delay;
					chkDefaultStream->Checked = value->bDefaultTrack;
					chkForceStream->Checked = value->bForceTrack;
					_trackInfo = value->MuxOnlyInfo;
				}

				void MuxStreamControl::setShowDelay(const bool &value)
				{
					showDelay = value;
					delayLabel->Visible = value;
					audioDelay->Visible = value;
				}

				const bool &MuxStreamControl::getShowDelay() const
				{
					return showDelay;
				}

				void MuxStreamControl::setShowDefaultSubtitleStream(const bool &value)
				{
					showDefaultSubtitleStream = value;
					chkDefaultStream->Visible = value;
				}

				const bool &MuxStreamControl::getShowDefaultSubtitleStream() const
				{
					return showDefaultSubtitleStream;
				}

				void MuxStreamControl::setShowForceSubtitleStream(const bool &value)
				{
					showForceSubtitleStream = value;
					chkForceStream->Visible = value;
				}

				const bool &MuxStreamControl::getShowForceSubtitleStream() const
				{
					return showForceSubtitleStream;
				}

				const std::string &MuxStreamControl::getFilter() const
				{
					return input->getFilter();
				}

				void MuxStreamControl::setFilter(const std::string &value)
				{
					input->setFilter(value);
				}

				void MuxStreamControl::SetLanguage(const std::string &lang)
				{
					subtitleLanguage->SelectedItem = lang;
				}

				void MuxStreamControl::SetAutoEncodeMode()
				{
					audioDelay->Enabled = input->Enabled = false;
				}

				void MuxStreamControl::removeSubtitleTrack_Click(object *sender, EventArgs *e)
				{
					input->Text = "";
					subtitleLanguage->SelectedIndex = -1;
					subName->Text = "";
					audioDelay->Value = 0;
					raiseEvent();
				}

				void MuxStreamControl::raiseEvent()
				{
					FileUpdated(this, new EventArgs());
				}

				void MuxStreamControl::input_FileSelected(FileBar *sender, FileBarEventArgs *args)
				{
					Nullable<int> tempVar = PrettyFormatting.getDelayAndCheck(input.getFilename());
					audioDelay->Value = tempVar::HasValue ? tempVar : 0;

					bool bFound = false;
					for (std::map<std::string, std::string>::const_iterator strLanguage = LanguageSelectionContainer::getLanguages().begin(); strLanguage != LanguageSelectionContainer::getLanguages().end(); ++strLanguage)
					{
						if (input->getFilename().ToLower(System::Globalization::CultureInfo::InvariantCulture)->Contains(strLanguage->first->ToLower(System::Globalization::CultureInfo::InvariantCulture)))
						{
							SetLanguage(strLanguage->first);
							bFound = true;
							break;
						}
					}
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'EndsWith' method:
					if (!bFound && input->getFilename().ToLower(System::Globalization::CultureInfo::InvariantCulture)->EndsWith(".idx"))
					{
						std::vector<SubtitleInfo*> subTracks;
						idxReader::readFileProperties(input->getFilename(), subTracks);
						if (subTracks.size() > 0)
							SetLanguage(LanguageSelectionContainer::Short2FullLanguageName(subTracks[0]->getName()));
					}
					raiseEvent();
				}

				void MuxStreamControl::chkForceStream_CheckedChanged(object *sender, EventArgs *e)
				{
					std::string strForceName = MeGUI::MainForm::Instance->getSettings()->getAppendToForcedStreams();

					if (strForceName.empty())
						return;

//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'EndsWith' method:
					if (chkForceStream->Checked && !subName->Text->EndsWith(strForceName))
					{
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'EndsWith' method:
						if (!subName->Text->empty() && !subName->Text->EndsWith(" "))
							subName->Text += " ";
						subName->Text += strForceName;
					}
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'EndsWith' method:
					else if (!chkForceStream->Checked && subName->Text->EndsWith(strForceName))
					{
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'TrimEnd' method:
						subName->Text = (subName->Text->substr(0, subName->Text->Length - strForceName.length()))->TrimEnd();
					}
				}

				void MuxStreamControl::Dispose(bool disposing)
				{
					if (disposing && (components != 0))
					{
						delete components;
					}
					UserControl::Dispose(disposing);
				}

				void MuxStreamControl::InitializeComponent()
				{
					this->subName = new System::Windows::Forms::TextBox();
					this->SubNamelabel = new System::Windows::Forms::Label();
					this->subtitleLanguage = new System::Windows::Forms::ComboBox();
					this->subtitleLanguageLabel = new System::Windows::Forms::Label();
					this->subtitleInputLabel = new System::Windows::Forms::Label();
					this->delayLabel = new System::Windows::Forms::Label();
					this->audioDelay = new System::Windows::Forms::NumericUpDown();
					this->tableLayoutPanel1 = new System::Windows::Forms::TableLayoutPanel();
					this->input = new MeGUI::FileBar();
					this->chkDefaultStream = new System::Windows::Forms::CheckBox();
					this->chkForceStream = new System::Windows::Forms::CheckBox();
					this->removeSubtitleTrack = new System::Windows::Forms::Button();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->audioDelay))->BeginInit();
					this->tableLayoutPanel1->SuspendLayout();
					this->SuspendLayout();
					// 
					// subName
					// 
					this->tableLayoutPanel1->SetColumnSpan(this->subName, 2);
					this->subName->Location = new System::Drawing::Point(232, 30);
					this->subName->MaxLength = 100;
					this->subName->Name = "subName";
					this->subName->Size = new System::Drawing::Size(168, 20);
					this->subName->TabIndex = 40;
					// 
					// SubNamelabel
					// 
					this->SubNamelabel->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right)));
					this->SubNamelabel->AutoSize = true;
					this->SubNamelabel->Location = new System::Drawing::Point(191, 34);
					this->SubNamelabel->Name = "SubNamelabel";
					this->SubNamelabel->Size = new System::Drawing::Size(35, 13);
					this->SubNamelabel->TabIndex = 39;
					this->SubNamelabel->Text = "Name";
					// 
					// subtitleLanguage
					// 
					this->subtitleLanguage->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right)));
					this->subtitleLanguage->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
					this->subtitleLanguage->Location = new System::Drawing::Point(64, 30);
					this->subtitleLanguage->Name = "subtitleLanguage";
					this->subtitleLanguage->Size = new System::Drawing::Size(121, 21);
					this->subtitleLanguage->Sorted = true;
					this->subtitleLanguage->TabIndex = 37;
					// 
					// subtitleLanguageLabel
					// 
					this->subtitleLanguageLabel->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right)));
					this->subtitleLanguageLabel->AutoSize = true;
					this->subtitleLanguageLabel->Location = new System::Drawing::Point(3, 34);
					this->subtitleLanguageLabel->Name = "subtitleLanguageLabel";
					this->subtitleLanguageLabel->Size = new System::Drawing::Size(55, 13);
					this->subtitleLanguageLabel->TabIndex = 36;
					this->subtitleLanguageLabel->Text = "Language";
					// 
					// subtitleInputLabel
					// 
					this->subtitleInputLabel->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right)));
					this->subtitleInputLabel->AutoSize = true;
					this->subtitleInputLabel->Location = new System::Drawing::Point(3, 7);
					this->subtitleInputLabel->Name = "subtitleInputLabel";
					this->subtitleInputLabel->Size = new System::Drawing::Size(55, 13);
					this->subtitleInputLabel->TabIndex = 33;
					this->subtitleInputLabel->Text = "Input";
					// 
					// delayLabel
					// 
					this->delayLabel->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right)));
					this->delayLabel->AutoSize = true;
					this->delayLabel->Location = new System::Drawing::Point(3, 65);
					this->delayLabel->Name = "delayLabel";
					this->delayLabel->Size = new System::Drawing::Size(55, 13);
					this->delayLabel->TabIndex = 43;
					this->delayLabel->Text = "Delay";
					// 
					// audioDelay
					// 
					this->audioDelay->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right)));
					this->audioDelay->Location = new System::Drawing::Point(64, 62);
					this->audioDelay->Maximum = decimal(new int[4] {2147483647, 0, 0, 0});
					this->audioDelay->Minimum = decimal(new int[4] {-2147483648, 0, 0, -2147483648});
					this->audioDelay->Name = "audioDelay";
					this->audioDelay->Size = new System::Drawing::Size(121, 20);
					this->audioDelay->TabIndex = 42;
					// 
					// tableLayoutPanel1
					// 
					this->tableLayoutPanel1->ColumnCount = 6;
					this->tableLayoutPanel1->ColumnStyles->Add(new System::Windows::Forms::ColumnStyle());
					this->tableLayoutPanel1->ColumnStyles->Add(new System::Windows::Forms::ColumnStyle());
					this->tableLayoutPanel1->ColumnStyles->Add(new System::Windows::Forms::ColumnStyle());
					this->tableLayoutPanel1->ColumnStyles->Add(new System::Windows::Forms::ColumnStyle());
					this->tableLayoutPanel1->ColumnStyles->Add(new System::Windows::Forms::ColumnStyle());
					this->tableLayoutPanel1->ColumnStyles->Add(new System::Windows::Forms::ColumnStyle());
					this->tableLayoutPanel1->Controls->Add(this->input, 1, 0);
					this->tableLayoutPanel1->Controls->Add(this->delayLabel, 0, 2);
					this->tableLayoutPanel1->Controls->Add(this->subtitleInputLabel, 0, 0);
					this->tableLayoutPanel1->Controls->Add(this->subName, 3, 1);
					this->tableLayoutPanel1->Controls->Add(this->audioDelay, 1, 2);
					this->tableLayoutPanel1->Controls->Add(this->SubNamelabel, 2, 1);
					this->tableLayoutPanel1->Controls->Add(this->subtitleLanguage, 1, 1);
					this->tableLayoutPanel1->Controls->Add(this->subtitleLanguageLabel, 0, 1);
					this->tableLayoutPanel1->Controls->Add(this->chkDefaultStream, 3, 2);
					this->tableLayoutPanel1->Controls->Add(this->chkForceStream, 4, 2);
					this->tableLayoutPanel1->Controls->Add(this->removeSubtitleTrack, 5, 1);
					this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
					this->tableLayoutPanel1->Location = new System::Drawing::Point(0, 0);
					this->tableLayoutPanel1->Name = "tableLayoutPanel1";
					this->tableLayoutPanel1->RowCount = 3;
					this->tableLayoutPanel1->RowStyles->Add(new System::Windows::Forms::RowStyle());
					this->tableLayoutPanel1->RowStyles->Add(new System::Windows::Forms::RowStyle());
					this->tableLayoutPanel1->RowStyles->Add(new System::Windows::Forms::RowStyle());
					this->tableLayoutPanel1->Size = new System::Drawing::Size(434, 90);
					this->tableLayoutPanel1->TabIndex = 44;
					// 
					// input
					// 
					this->tableLayoutPanel1->SetColumnSpan(this->input, 5);
					this->input->setFilename("");
					this->input->setFilter("");
					this->input->setFilterIndex(0);
					this->input->setFolderMode(false);
					this->input->Location = new System::Drawing::Point(63, 2);
					this->input->Margin = new System::Windows::Forms::Padding(2);
					this->input->Name = "input";
					this->input->setReadOnly(true);
					this->input->setSaveMode(false);
					this->input->Size = new System::Drawing::Size(365, 23);
					this->input->TabIndex = 41;
					this->input->setTitle("");
					this->input->FileSelected += new MeGUI::FileBarEventHandler(this, &MuxStreamControl::input_FileSelected);
					// 
					// chkDefaultStream
					// 
					this->chkDefaultStream->Anchor = System::Windows::Forms::AnchorStyles::Left;
					this->chkDefaultStream->AutoSize = true;
					this->chkDefaultStream->Location = new System::Drawing::Point(232, 63);
					this->chkDefaultStream->Name = "chkDefaultStream";
					this->chkDefaultStream->Size = new System::Drawing::Size(85, 17);
					this->chkDefaultStream->TabIndex = 44;
					this->chkDefaultStream->Text = "default track";
					this->chkDefaultStream->UseVisualStyleBackColor = true;
					this->chkDefaultStream->Visible = false;
					// 
					// chkForceStream
					// 
					this->chkForceStream->Anchor = System::Windows::Forms::AnchorStyles::Left;
					this->chkForceStream->AutoSize = true;
					this->tableLayoutPanel1->SetColumnSpan(this->chkForceStream, 2);
					this->chkForceStream->Location = new System::Drawing::Point(323, 63);
					this->chkForceStream->Name = "chkForceStream";
					this->chkForceStream->Size = new System::Drawing::Size(83, 17);
					this->chkForceStream->TabIndex = 45;
					this->chkForceStream->Text = "forced track";
					this->chkForceStream->UseVisualStyleBackColor = true;
					this->chkForceStream->Visible = false;
					this->chkForceStream->CheckedChanged += new System::EventHandler(this, &MuxStreamControl::chkForceStream_CheckedChanged);
					// 
					// removeSubtitleTrack
					// 
					this->removeSubtitleTrack->Anchor = System::Windows::Forms::AnchorStyles::None;
					this->removeSubtitleTrack->Location = new System::Drawing::Point(407, 29);
					this->removeSubtitleTrack->Margin = new System::Windows::Forms::Padding(0);
					this->removeSubtitleTrack->Name = "removeSubtitleTrack";
					this->removeSubtitleTrack->Size = new System::Drawing::Size(22, 23);
					this->removeSubtitleTrack->TabIndex = 46;
					this->removeSubtitleTrack->Text = "X";
					// 
					// MuxStreamControl
					// 
					this->AutoScaleDimensions = new System::Drawing::SizeF(6, 13);
					this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
					this->Controls->Add(this->tableLayoutPanel1);
					this->Name = "MuxStreamControl";
					this->Size = new System::Drawing::Size(434, 90);
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->audioDelay))->EndInit();
					this->tableLayoutPanel1->ResumeLayout(false);
					this->tableLayoutPanel1->PerformLayout();
					this->ResumeLayout(false);

				}

				void MuxStreamControl::InitializeInstanceFields()
				{
					delete components;
				}
			}
		}
	}
}
