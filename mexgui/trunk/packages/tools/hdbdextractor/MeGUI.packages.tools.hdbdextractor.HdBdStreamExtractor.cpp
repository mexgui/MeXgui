#include "MeGUI.packages.tools.hdbdextractor.HdBdStreamExtractor.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::ComponentModel;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Diagnostics;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text::RegularExpressions;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;
using namespace MeGUI::core::plugins::interfaces;
using namespace MeGUI::core::details;
using namespace MeGUI::core::util;
using namespace eac3to;
namespace MeGUI
{
	namespace packages
	{
		namespace tools
		{
			namespace hdbdextractor
			{

				HdBdStreamExtractor::HdBdStreamExtractor(MainForm *info)
				{
					InitializeInstanceFields();
					this->mainForm = info;
					this->settings = info->getSettings();
					InitializeComponent();
				}

				void HdBdStreamExtractor::SetProgress(object *sender, ProgressChangedEventArgs *e)
				{
					SetToolStripProgressBarValue(e->ProgressPercentage);
					if (e->UserState != 0)
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
						SetToolStripLabelText(e->UserState->ToString());
				}

				void HdBdStreamExtractor::SetData(object *sender, RunWorkerCompletedEventArgs *e)
				{
					SetToolStripProgressBarValue(0);
					SetToolStripLabelText(Extensions::GetStringValue((static_cast<ResultState>(e->Result))));
					ResetCursor(Cursors::Default);

					if (e->Result != 0)
					{
						switch (static_cast<ResultState>(e->Result))
						{
							case FeatureCompleted:
								FeatureDataGridView->DataSource = _oEac3toInfo->getFeatures();
								FeatureButton->Enabled = true;
								FeatureDataGridView->SelectionChanged += new System::EventHandler(this, &HdBdStreamExtractor::FeatureDataGridView_SelectionChanged);
								if (_oEac3toInfo->getFeatures().size() == 1)
									FeatureDataGridView->Rows[0]->Selected = true;
								break;
							case StreamCompleted:
								if (FileSelection->Checked)
									StreamDataGridView->DataSource = _oEac3toInfo->getFeatures()[0]->getStreams();
								else
									StreamDataGridView->DataSource = (static_cast<eac3to::Feature*>(FeatureDataGridView->SelectedRows[0]->DataBoundItem))->getStreams();
								SelectTracks();
								FeatureButton->Enabled = true;
								break;
							case ExtractCompleted:
								QueueButton->Enabled = true;
								break;
						}
					}
				}

				void HdBdStreamExtractor::SetToolStripProgressBarValue(int value)
				{
//C# TO C++ CONVERTER TODO TASK: There is no built-in support for multithreading in native C++:
					lock (this)
					{
						if (this->InvokeRequired)
							this->BeginInvoke(new SetToolStripProgressBarValueCallback(SetToolStripProgressBarValue), value);
						else
							this->ToolStripProgressBar->Value = value;
					}
				}

				void HdBdStreamExtractor::SetToolStripLabelText(const std::string &message)
				{
//C# TO C++ CONVERTER TODO TASK: There is no built-in support for multithreading in native C++:
					lock (this)
					{
						if (this->InvokeRequired)
							this->BeginInvoke(new SetToolStripLabelTextCallback(SetToolStripLabelText), message);
						else
							this->ToolStripStatusLabel->Text = message;
					}
				}

				void HdBdStreamExtractor::ResetCursor(System::Windows::Forms::Cursor *cursor)
				{
//C# TO C++ CONVERTER TODO TASK: There is no built-in support for multithreading in native C++:
					lock (this)
					{
						if (this->InvokeRequired)
							this->BeginInvoke(new ResetCursorCallback(ResetCursor), cursor);
						else
							this->Cursor = cursor;
					}
				}

				void HdBdStreamExtractor::FolderInputSourceButton_Click(object *sender, EventArgs *e)
				{
					std::string myinput = "";
					std::string outputFolder = "";
					DialogResult *dr;
					int idx = 0;
					input.clear();

					if (FolderSelection->Checked)
					{
						folderBrowserDialog1->SelectedPath = MainForm::Instance->getSettings()->getLastSourcePath();
						folderBrowserDialog1->Description = "Choose an input directory";
						folderBrowserDialog1->ShowNewFolderButton = false;
						dr = folderBrowserDialog1->ShowDialog();
						if (dr != System::Windows::Forms::DialogResult::OK)
							return;
						inputType = 1;
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'EndsWith' method:
						if (folderBrowserDialog1->SelectedPath->EndsWith(":\\"))
							myinput = folderBrowserDialog1->SelectedPath;
						else
							myinput = folderBrowserDialog1->SelectedPath + System::IO::Path::DirectorySeparatorChar;
						if (dr == System::Windows::Forms::DialogResult::OK)
							MainForm::Instance->getSettings()->setLastSourcePath(myinput);
						outputFolder = myinput.substr(0, myinput.rfind("\\") + 1);
						input.push_back(myinput);
					}
					else
					{
						dr = openFileDialog1->ShowDialog();
						if (dr != System::Windows::Forms::DialogResult::OK)
							return;
						inputType = 2;
						for (unknown::const_iterator file = openFileDialog1->FileNames.begin(); file != openFileDialog1->FileNames.end(); ++file)
						{
							if (idx == 0)
							{
								outputFolder = System::IO::Path::GetDirectoryName(*file);
								myinput = *file;
								input.push_back(*file);
							}
							else // seamless branching
							{
								myinput += "+" + *file;
								input.push_back(*file);
							}
							idx++;
						}
					}

					FolderInputTextBox->Text = myinput;
					if (FolderInputTextBox->Text->empty())
						return;

					if (FolderOutputTextBox->Text->empty())
					{
						if (!MainForm::Instance->getSettings()->getDefaultOutputDir().empty())
							FolderOutputTextBox->Text = MainForm::Instance->getSettings()->getDefaultOutputDir();
						else
							FolderOutputTextBox->Text = outputFolder;
					}
					FeatureButton_Click(0, 0);
				}

				void HdBdStreamExtractor::FolderOutputSourceButton_Click(object *sender, EventArgs *e)
				{
					folderBrowserDialog1->SelectedPath = MainForm::Instance->getSettings()->getLastDestinationPath();
					folderBrowserDialog1->Description = "Choose an output directory";
					folderBrowserDialog1->ShowNewFolderButton = true;
					DialogResult *dr = folderBrowserDialog1->ShowDialog();

					if (dr == System::Windows::Forms::DialogResult::OK)
					{
						FolderOutputTextBox->Text = folderBrowserDialog1->SelectedPath;
						MainForm::Instance->getSettings()->setLastDestinationPath(folderBrowserDialog1->SelectedPath);
					}
				}

				void HdBdStreamExtractor::FeatureButton_Click(object *sender, EventArgs *e)
				{
					if (FolderInputTextBox->Text->empty())
					{
						MessageBox::Show("Configure input source folder prior to retrieving features.", "Feature Retrieval", MessageBoxButtons::OK, MessageBoxIcon::Exclamation, MessageBoxDefaultButton::Button1);
						return;
					}

					FeatureButton->Enabled = false;
					Cursor = Cursors::WaitCursor;

					_oEac3toInfo = new Eac3toInfo(input, 0, 0);
					_oEac3toInfo->FetchInformationCompleted += new OnFetchInformationCompletedHandler(this, &HdBdStreamExtractor::SetData);
					_oEac3toInfo->ProgressChanged += new OnProgressChangedHandler(this, &HdBdStreamExtractor::SetProgress);
					_oEac3toInfo->FetchFeatureInformation();
				}

				void HdBdStreamExtractor::StreamDataGridView_DataSourceChanged(object *sender, EventArgs *e)
				{
					for (unknown::const_iterator row = StreamDataGridView->Rows.begin(); row != StreamDataGridView->Rows.end(); ++row)
					{
						Stream *s = dynamic_cast<Stream*>((*row)->DataBoundItem);
						DataGridViewComboBoxCell *comboBox = dynamic_cast<DataGridViewComboBoxCell*>((*row)->Cells["StreamExtractAsComboBox"]);
						DataGridViewTextBoxCell *tbLang = dynamic_cast<DataGridViewTextBoxCell*>((*row)->Cells["languageDataGridViewTextBoxColumn"]);
						comboBox->Items->Clear();
						comboBox->Items->AddRange(s->ExtractTypes);

						switch (s->getType())
						{
							case eac3to::Chapter:
								comboBox->Value = "TXT";
								break;
							case eac3to::Join:
								if (s->getName() == "Joined EVO")
									comboBox->Value = "EVO";
								else
									comboBox->Value = "VOB";
								break;
							case eac3to::Subtitle:
//C# TO C++ CONVERTER NOTE: The following 'switch' operated on a string variable and was converted to C++ 'if-else' logic:
//								switch (s.Description.Substring(11, 3))
//ORIGINAL LINE: case "ASS":
								if (s->getDescription().substr(11, 3) == "ASS")
								{
										comboBox->Value = "ASS";
								}
//ORIGINAL LINE: case "SSA":
								else if (s->getDescription().substr(11, 3) == "SSA")
								{
										comboBox->Value = "SSA";
								}
//ORIGINAL LINE: case "SRT":
								else if (s->getDescription().substr(11, 3) == "SRT")
								{
										comboBox->Value = "SRT";
								}
//ORIGINAL LINE: case "Vob":
								else if (s->getDescription().substr(11, 3) == "Vob")
								{
										comboBox->Value = "IDX";
								}
								else
								{
										comboBox->Value = "SUP";
								}
								break;
							case eac3to::Video:
								comboBox->Value = "MKV";
								break;
							case eac3to::Audio:
								comboBox->Value = comboBox->Items[0];
								break;
						}

						if ((s->getType() == eac3to::Audio) || (s->getType() == eac3to::Subtitle))
						{
							wchar_t separator[1] = {','};
//ORIGINAL LINE: string[] split = s.Description.Split(separator, 100);
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Split' method:
							std::string *split = s->getDescription().Split(separator, 100);

							if (s->getName().find("Subtitle") != string::npos)
								s->setLanguage(s->getName());
							else
								s->setLanguage(split[1].substr(1, split[1].length() - 1));

							bool bFound = false;
							for (std::map<std::string, std::string>::const_iterator strLanguage = LanguageSelectionContainer::getLanguages().begin(); strLanguage != LanguageSelectionContainer::getLanguages().end(); ++strLanguage)
							{
								if (s->getLanguage().ToLower(System::Globalization::CultureInfo::InvariantCulture)->Contains(strLanguage->first->ToLower(System::Globalization::CultureInfo::InvariantCulture)))
								{
									s->setLanguage(strLanguage->first);
									bFound = true;
									break;
								}
							}
							if (!bFound)
							{
								if (!FolderSelection->Checked && System::IO::Path::GetExtension(FolderInputTextBox->Text)->ToLower(System::Globalization::CultureInfo::InvariantCulture)->Equals(".mkv"))
									s->setLanguage("English");
								else
									s->setLanguage("");
							}
						}
						else
							s->setLanguage("");
					}
				}

				void HdBdStreamExtractor::QueueButton_Click(object *sender, EventArgs *e)
				{
					if (FolderOutputTextBox->Text->empty())
					{
						MessageBox::Show("Configure output target folder prior to queueing job.", "Queue Job", MessageBoxButtons::OK, MessageBoxIcon::Exclamation, MessageBoxDefaultButton::Button1);
						return;
					}
					if (StreamDataGridView->Rows->Count == 0)
					{
						MessageBox::Show("Retrieve streams prior to queueing job.", "Queue Job", MessageBoxButtons::OK, MessageBoxIcon::Exclamation, MessageBoxDefaultButton::Button1);
						return;
					}
					if (!IsStreamCheckedForExtract())
					{
						MessageBox::Show("Select stream(s) to extract prior to queueing job.", "Queue Job", MessageBoxButtons::OK, MessageBoxIcon::Exclamation, MessageBoxDefaultButton::Button1);
						return;
					}
					if (FolderSelection->Checked && FeatureDataGridView->SelectedRows->Count == 0)
					{
						MessageBox::Show("Select feature prior to queueing job.", "Queue Job", MessageBoxButtons::OK, MessageBoxIcon::Exclamation, MessageBoxDefaultButton::Button1);
						return;
					}
					if (!Drives::ableToWriteOnThisDrive(System::IO::Path::GetPathRoot(FolderOutputTextBox->Text)))
					{
						MessageBox::Show("MeGUI cannot write on " + System::IO::Path::GetPathRoot(FolderOutputTextBox->Text) + "\nPlease, select another Output path.", "Information", MessageBoxButtons::OK, MessageBoxIcon::Exclamation, MessageBoxDefaultButton::Button1);
						return;
					}


					eac3toArgs args = eac3toArgs();
					HDStreamsExJob *job;

					args.seteac3toPath(settings->getEAC3toPath());
					if (FolderSelection->Checked)
						args.setfeatureNumber(StringConverterHelper::toString((static_cast<Feature*>(FeatureDataGridView->SelectedRows[0]->DataBoundItem))->getNumber()));
					args.setworkingFolder(FolderOutputTextBox->Text->empty() ? FolderOutputTextBox->Text : System::IO::Path::GetDirectoryName(args.geteac3toPath()));
					args.setresultState(ExtractCompleted);

					try
					{
						args.setargs(GenerateArguments());
					}
					catch (ApplicationException *ex)
					{
						MessageBox::Show(ex->Message, "Stream Extract", MessageBoxButtons::OK, MessageBoxIcon::Exclamation, MessageBoxDefaultButton::Button1);
						return;
					}

					// Load to MeGUI job queue
					if (FolderSelection->Checked)
					{
						const std::string tempVector[] = {dummyInput};
						job = new HDStreamsExJob(std::vector<std::string>(tempVector, tempVector + sizeof(tempVector) / sizeof(tempVector[0])), this->FolderOutputTextBox->Text, args.getfeatureNumber(), args.getargs(), inputType);
					}
					else
						job = new HDStreamsExJob(input, this->FolderOutputTextBox->Text, 0, args.getargs(), inputType);

					lastJob = job;
					mainForm->getJobs()->addJobsToQueue(job);
					if (this->closeOnQueue->Checked)
						this->Close();
				}

				const MeGUI::HDStreamsExJob &HdBdStreamExtractor::getLastJob() const
				{
					return lastJob;
				}

				void HdBdStreamExtractor::setLastJob(const HDStreamsExJob &value)
				{
					lastJob = value;
				}

				const bool &HdBdStreamExtractor::getJobCreated() const
				{
					return lastJob != 0;
				}

				std::string HdBdStreamExtractor::GenerateArguments()
				{
					StringBuilder *sb = new StringBuilder();

					for (unknown::const_iterator row = StreamDataGridView->Rows.begin(); row != StreamDataGridView->Rows.end(); ++row)
					{
						Stream *stream = dynamic_cast<Stream*>((*row)->DataBoundItem);
						DataGridViewCheckBoxCell *extractStream = dynamic_cast<DataGridViewCheckBoxCell*>((*row)->Cells["StreamExtractCheckBox"]);

//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
						if (extractStream->Value != 0 && int::Parse(extractStream->Value->ToString()) == 1)
						{
							if ((*row)->Cells["StreamExtractAsComboBox"]->Value == 0)
								throw new ApplicationException(std::string::Format("Specify an extraction type for stream:\r\n\n\t{0}: {1}", stream->getNumber(), stream->getName()));

							if (FolderSelection->Checked)
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
								sb->Append(std::string::Format("{0}:\"{1}\" {2} ", stream->getNumber(), System::IO::Path::Combine(FolderOutputTextBox->Text, std::string::Format("F{0}_T{1}_{2} - {3}.{4}", (static_cast<Feature*>(FeatureDataGridView->SelectedRows[0]->DataBoundItem))->getNumber(), stream->getNumber(), Extensions::GetStringValue(stream->getType()), (*row)->Cells["languageDataGridViewTextBoxColumn"]->Value, ((*row)->Cells["StreamExtractAsComboBox"]->Value)->ToString()->ToLower(System::Globalization::CultureInfo::InvariantCulture))), (*row)->Cells["StreamAddOptionsTextBox"]->Value)->Trim());
							else
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
								sb->Append(std::string::Format("{0}:\"{1}\" {2} ", stream->getNumber(), System::IO::Path::Combine(FolderOutputTextBox->Text, std::string::Format("T{0}_{1} - {2}.{3}", stream->getNumber(), Extensions::GetStringValue(stream->getType()), (*row)->Cells["languageDataGridViewTextBoxColumn"]->Value, ((*row)->Cells["StreamExtractAsComboBox"]->Value)->ToString()->ToLower(System::Globalization::CultureInfo::InvariantCulture))), (*row)->Cells["StreamAddOptionsTextBox"]->Value)->Trim());

							if ((*row)->Cells["StreamExtractAsComboBox"]->Value->Equals(AudioCodec::DTS->getID()))
								sb->Append(" -core");

							sb->Append(" ");
						}
					}

//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
					return sb->ToString();
				}

				void HdBdStreamExtractor::CancelButton2_Click(object *sender, EventArgs *e)
				{
					this->Close();
				}

				void HdBdStreamExtractor::HelpButton2_Click(object *sender, EventArgs *e)
				{
					System::Diagnostics::Process::Start("http://en.wikibooks.org/wiki/Eac3to/How_to_Use");
				}

				void HdBdStreamExtractor::HdBrStreamExtractor_FormClosing(object *sender, System::Windows::Forms::FormClosingEventArgs *e)
				{
					//if (backgroundWorker != null)
					//{
					//    if (backgroundWorker.IsBusy)
					//        if (MessageBox.Show("A process is still running. Do you want to cancel it?", "Cancel process?", MessageBoxButtons.YesNo, MessageBoxIcon.Question) == DialogResult.Yes)
					//            backgroundWorker.CancelAsync();

					//    if (backgroundWorker.CancellationPending)
					//        backgroundWorker.Dispose();
					//}
				}

				bool HdBdStreamExtractor::IsStreamCheckedForExtract()
				{
					bool enableQueue = false;

					for (unknown::const_iterator row = StreamDataGridView->Rows.begin(); row != StreamDataGridView->Rows.end(); ++row)
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
						if ((*row)->Cells["StreamExtractCheckBox"]->Value != 0 && int::Parse((*row)->Cells["StreamExtractCheckBox"]->Value->ToString()) == 1)
							enableQueue = true;

					return enableQueue;
				}

				void HdBdStreamExtractor::Eac3toLinkLabel_LinkClicked(object *sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs *e)
				{
					System::Diagnostics::Process::Start("http://forum.doom9.org/showthread.php?t=125966");
				}

				void HdBdStreamExtractor::FeatureDataGridView_SelectionChanged(object *sender, EventArgs *e)
				{
					// only fire after the Databind has completed on grid and a row is selected
					if (FeatureDataGridView->Rows->Count == _oEac3toInfo->getFeatures().size() && FeatureDataGridView->SelectedRows->Count == 1)
					{
						if (_oEac3toInfo->IsBusy()) // disallow selection change
						{
							if (FeatureDataGridView->Tag != 0)
							{
								FeatureDataGridView->SelectionChanged -= new System::EventHandler(this, &HdBdStreamExtractor::FeatureDataGridView_SelectionChanged);
								FeatureDataGridView->CurrentRow->Selected = false;
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
								FeatureDataGridView->Rows[int::Parse(FeatureDataGridView->Tag->ToString())]->Selected = true;
								FeatureDataGridView->SelectionChanged += new System::EventHandler(this, &HdBdStreamExtractor::FeatureDataGridView_SelectionChanged);
							}
						}
						else // backgroundworker is not busy, allow selection change
						{
							Feature *feature = dynamic_cast<Feature*>(FeatureDataGridView->SelectedRows[0]->DataBoundItem);

							// Check for Streams
							if (feature->getStreams().empty() || feature->getStreams().empty())
							{
								// create dummy input string for megui job
								if (feature->getDescription().find("EVO") != string::npos)
								{
									if (feature->getDescription().find("+") != string::npos)
									{
										if (FolderInputTextBox->Text->ToUpper(System::Globalization::CultureInfo::InvariantCulture)->Contains("HVDVD_TS"))
											dummyInput = FolderInputTextBox->Text->substr(0, FolderInputTextBox->Text->find("HVDVD_TS")) + "HVDVD_TS\\" + feature->getDescription().substr(0, feature->getDescription().find("+"));
										else
											dummyInput = FolderInputTextBox->Text + "HVDVD_TS\\" + feature->getDescription().substr(0, feature->getDescription().find("+"));
									}
									else
									{
										if (FolderInputTextBox->Text->ToUpper(System::Globalization::CultureInfo::InvariantCulture)->Contains("HVDVD_TS"))
											dummyInput = FolderInputTextBox->Text->substr(0, FolderInputTextBox->Text->find("HVDVD_TS")) + "HVDVD_TS\\" + feature->getDescription().substr(0, feature->getDescription().find(","));
										else
											dummyInput = FolderInputTextBox->Text + "HVDVD_TS\\" + feature->getDescription().substr(0, feature->getDescription().find(","));
									}
								}
								else if (feature->getDescription().find("(angle") != string::npos)
								{
									dummyInput = getBDMVPath(FolderInputTextBox->Text, feature->getDescription().substr(0, feature->getDescription().find(" (")));
								}
								else if (feature->getDescription().substr(feature->getDescription().rfind(".") + 1, 4) == "m2ts")
								{
									std::string des = feature->getDescription().substr(feature->getDescription().find(",") + 2, feature->getDescription().rfind(",") - feature->getDescription().find(",") - 2);

									if (des.find("+") != string::npos) // seamless branching
										dummyInput = getBDMVPath(FolderInputTextBox->Text, feature->getDescription().substr(0, feature->getDescription().find(",")));
									else
										dummyInput = getBDMVPath(FolderInputTextBox->Text, des);
								}
								else
									dummyInput = getBDMVPath(FolderInputTextBox->Text, feature->getDescription().substr(0, feature->getDescription().find(",")));

								Cursor = Cursors::WaitCursor;
								_oEac3toInfo->FetchStreamInformation((static_cast<Feature*>(FeatureDataGridView->SelectedRows[0]->DataBoundItem))->getNumber());
							}
							else // use already collected streams
							{
								StreamDataGridView->DataSource = feature->getStreams();
								SelectTracks();
							}
						}
					}
				}

				void HdBdStreamExtractor::FeatureDataGridView_DataBindingComplete(object *sender, System::Windows::Forms::DataGridViewBindingCompleteEventArgs *e)
				{
					FeatureDataGridView->ClearSelection();
				}

				void HdBdStreamExtractor::FeatureDataGridView_RowLeave(object *sender, System::Windows::Forms::DataGridViewCellEventArgs *e)
				{
					FeatureDataGridView->Tag = e->RowIndex;
				}

				void HdBdStreamExtractor::FeatureDataGridView_DataSourceChanged(object *sender, EventArgs *e)
				{
					for (unknown::const_iterator row = FeatureDataGridView->Rows.begin(); row != FeatureDataGridView->Rows.end(); ++row)
					{
						Feature *feature = dynamic_cast<Feature*>((*row)->DataBoundItem);
						DataGridViewComboBoxCell *comboBox = dynamic_cast<DataGridViewComboBoxCell*>((*row)->Cells["FeatureFileDataGridViewComboBoxColumn"]);

						if (feature != 0)
						{
							if (feature->getFiles().size() > 0 || feature->getFiles().size() > 0)
							{
								for (std::vector<File*>::const_iterator file = feature->getFiles().begin(); file != feature->getFiles().end(); ++file)
								{
									comboBox->Items->Add((*file)->getFullName());

									if ((*file)->getIndex() == 1)
										comboBox->Value = (*file)->getFullName();
								}
							}
						}
					}
				}

				void HdBdStreamExtractor::SelectTracks()
				{
					if (!MainForm::Instance->getSettings()->getAutoSelectHDStreams())
						return;

					bool bVideoSelected = false;
					for (unknown::const_iterator row = StreamDataGridView->Rows.begin(); row != StreamDataGridView->Rows.end(); ++row)
					{
						DataGridViewCheckBoxCell *extractStream = dynamic_cast<DataGridViewCheckBoxCell*>((*row)->Cells["StreamExtractCheckBox"]);
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
						if ((*row)->Cells["StreamTypeTextBox"]->Value->ToString()->Equals("Chapter"))
						{
							extractStream->Value = 1;
						}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
						else if (!bVideoSelected && (*row)->Cells["StreamTypeTextBox"]->Value->ToString()->Equals("Video"))
						{
							extractStream->Value = 1;
							bVideoSelected = true;
						}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
						else if ((*row)->Cells["languageDataGridViewTextBoxColumn"]->Value->ToString()->ToLowerInvariant()->Equals(MainForm::Instance->getSettings()->getDefaultLanguage1().ToLowerInvariant()) || (*row)->Cells["languageDataGridViewTextBoxColumn"]->Value->ToString()->ToLowerInvariant()->Equals(MainForm::Instance->getSettings()->getDefaultLanguage2().ToLowerInvariant()))
						{
							extractStream->Value = 1;
						}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
						else if (((*row)->Cells["languageDataGridViewTextBoxColumn"]->Value->ToString()->Trim())->empty() && ((*row)->Cells["StreamTypeTextBox"]->Value->ToString()->Equals("Audio") || (*row)->Cells["StreamTypeTextBox"]->Value->ToString()->Equals("Subtitle")))
						{
							extractStream->Value = 1;
						}
					}
				}

				std::string HdBdStreamExtractor::getBDMVPath(const std::string &path, const std::string &file)
				{
					std::string filePath;
					while (System::IO::Directory::Exists(path))
					{
						filePath = System::IO::Path::Combine(System::IO::Path::Combine(path, "BDMV\\STREAM"), file);
						if (System::IO::File::Exists(filePath))
							return filePath;

						filePath = System::IO::Path::Combine(System::IO::Path::Combine(path, "BDMV\\PLAYLIST"), file);
						if (System::IO::File::Exists(filePath))
							return filePath;

						if (System::IO::Path::GetFullPath(path)->Equals(System::IO::Path::GetPathRoot(path)))
							return file;

						System::IO::DirectoryInfo *pathInfo = new System::IO::DirectoryInfo(path);
						path = pathInfo->Parent->FullName;
					}
					return file;
				}

				void HdBdStreamExtractor::Dispose(bool disposing)
				{
					if (disposing && (components != 0))
					{
						delete components;
					}
					System::Windows::Forms::Form::Dispose(disposing);
				}

				void HdBdStreamExtractor::InitializeComponent()
				{
					this->components = new System::ComponentModel::Container();
					System::Windows::Forms::DataGridViewCellStyle *dataGridViewCellStyle1 = new System::Windows::Forms::DataGridViewCellStyle();
					System::ComponentModel::ComponentResourceManager *resources = new System::ComponentModel::ComponentResourceManager(HdBdStreamExtractor::typeid);
					this->StatusStrip = new System::Windows::Forms::StatusStrip();
					this->ToolStripStatusLabel = new System::Windows::Forms::ToolStripStatusLabel();
					this->ToolStripProgressBar = new System::Windows::Forms::ToolStripProgressBar();
					this->FolderInputTextBox = new System::Windows::Forms::TextBox();
					this->folderBrowserDialog1 = new System::Windows::Forms::FolderBrowserDialog();
					this->HelpButton2 = new System::Windows::Forms::Button();
					this->QueueButton = new System::Windows::Forms::Button();
					this->CancelButton2 = new System::Windows::Forms::Button();
					this->InputGroupBox = new System::Windows::Forms::GroupBox();
					this->FileSelection = new System::Windows::Forms::RadioButton();
					this->FolderSelection = new System::Windows::Forms::RadioButton();
					this->FolderInputSourceButton = new System::Windows::Forms::Button();
					this->Eac3toLinkLabel = new System::Windows::Forms::LinkLabel();
					this->FeatureGroupBox = new System::Windows::Forms::GroupBox();
					this->FeatureDataGridView = new MeGUI::packages::tools::hdbdextractor::CustomDataGridView();
					this->FeatureNumberDataGridViewTextBoxColumn1 = new System::Windows::Forms::DataGridViewTextBoxColumn();
					this->FeatureNameDataGridViewTextBoxColumn = new System::Windows::Forms::DataGridViewTextBoxColumn();
					this->FeatureDescriptionDataGridViewTextBoxColumn = new System::Windows::Forms::DataGridViewTextBoxColumn();
					this->FeatureFileDataGridViewComboBoxColumn = new System::Windows::Forms::DataGridViewComboBoxColumn();
					this->FeatureDurationDataGridViewTextBoxColumn = new System::Windows::Forms::DataGridViewTextBoxColumn();
					this->FeatureBindingSource = new System::Windows::Forms::BindingSource(this->components);
					this->StreamGroupBox = new System::Windows::Forms::GroupBox();
					this->StreamDataGridView = new MeGUI::packages::tools::hdbdextractor::CustomDataGridView();
					this->StreamExtractCheckBox = new System::Windows::Forms::DataGridViewCheckBoxColumn();
					this->StreamNumberTextBox = new System::Windows::Forms::DataGridViewTextBoxColumn();
					this->StreamTypeTextBox = new System::Windows::Forms::DataGridViewTextBoxColumn();
					this->StreamDescriptionTextBox = new System::Windows::Forms::DataGridViewTextBoxColumn();
					this->StreamExtractAsComboBox = new System::Windows::Forms::DataGridViewComboBoxColumn();
					this->StreamAddOptionsTextBox = new System::Windows::Forms::DataGridViewTextBoxColumn();
					this->numberDataGridViewTextBoxColumn = new System::Windows::Forms::DataGridViewTextBoxColumn();
					this->nameDataGridViewTextBoxColumn = new System::Windows::Forms::DataGridViewTextBoxColumn();
					this->typeDataGridViewTextBoxColumn = new System::Windows::Forms::DataGridViewTextBoxColumn();
					this->languageDataGridViewTextBoxColumn = new System::Windows::Forms::DataGridViewTextBoxColumn();
					this->StreamsBindingSource = new System::Windows::Forms::BindingSource(this->components);
					this->OutputGroupBox = new System::Windows::Forms::GroupBox();
					this->FolderOutputSourceButton = new System::Windows::Forms::Button();
					this->FolderOutputTextBox = new System::Windows::Forms::TextBox();
					this->openFileDialog1 = new System::Windows::Forms::OpenFileDialog();
					this->FeatureButton = new System::Windows::Forms::Button();
					this->extractTypesBindingSource = new System::Windows::Forms::BindingSource(this->components);
					this->closeOnQueue = new System::Windows::Forms::CheckBox();
					this->StatusStrip->SuspendLayout();
					this->InputGroupBox->SuspendLayout();
					this->FeatureGroupBox->SuspendLayout();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->FeatureDataGridView))->BeginInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->FeatureBindingSource))->BeginInit();
					this->StreamGroupBox->SuspendLayout();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->StreamDataGridView))->BeginInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->StreamsBindingSource))->BeginInit();
					this->OutputGroupBox->SuspendLayout();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->extractTypesBindingSource))->BeginInit();
					this->SuspendLayout();
					// 
					// StatusStrip
					// 
					this->StatusStrip->Items->AddRange(new System::Windows::Forms::ToolStripItem[2] {this->ToolStripStatusLabel, this->ToolStripProgressBar});
					this->StatusStrip->Location = new System::Drawing::Point(0, 456);
					this->StatusStrip->Name = "StatusStrip";
					this->StatusStrip->ShowItemToolTips = true;
					this->StatusStrip->Size = new System::Drawing::Size(580, 22);
					this->StatusStrip->TabIndex = 11;
					// 
					// ToolStripStatusLabel
					// 
					this->ToolStripStatusLabel->AutoSize = false;
					this->ToolStripStatusLabel->Name = "ToolStripStatusLabel";
					this->ToolStripStatusLabel->Size = new System::Drawing::Size(358, 17);
					this->ToolStripStatusLabel->Text = "Ready";
					this->ToolStripStatusLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
					this->ToolStripStatusLabel->ToolTipText = "Status";
					// 
					// ToolStripProgressBar
					// 
					this->ToolStripProgressBar->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
					this->ToolStripProgressBar->Name = "ToolStripProgressBar";
					this->ToolStripProgressBar->Size = new System::Drawing::Size(200, 16);
					this->ToolStripProgressBar->ToolTipText = "Progress";
					// 
					// FolderInputTextBox
					// 
					this->FolderInputTextBox->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
					this->FolderInputTextBox->Location = new System::Drawing::Point(6, 19);
					this->FolderInputTextBox->Name = "FolderInputTextBox";
					this->FolderInputTextBox->Size = new System::Drawing::Size(514, 21);
					this->FolderInputTextBox->TabIndex = 0;
					// 
					// HelpButton2
					// 
					this->HelpButton2->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left)));
					this->HelpButton2->AutoSize = true;
					this->HelpButton2->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
					this->HelpButton2->Location = new System::Drawing::Point(12, 425);
					this->HelpButton2->Name = "HelpButton2";
					this->HelpButton2->Size = new System::Drawing::Size(38, 23);
					this->HelpButton2->TabIndex = 8;
					this->HelpButton2->Text = "Help";
					this->HelpButton2->UseVisualStyleBackColor = true;
					this->HelpButton2->Click += new System::EventHandler(this, &HdBdStreamExtractor::HelpButton2_Click);
					// 
					// QueueButton
					// 
					this->QueueButton->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right)));
					this->QueueButton->Location = new System::Drawing::Point(414, 425);
					this->QueueButton->Name = "QueueButton";
					this->QueueButton->Size = new System::Drawing::Size(75, 23);
					this->QueueButton->TabIndex = 9;
					this->QueueButton->Text = "Queue";
					this->QueueButton->UseVisualStyleBackColor = true;
					this->QueueButton->Click += new System::EventHandler(this, &HdBdStreamExtractor::QueueButton_Click);
					// 
					// CancelButton2
					// 
					this->CancelButton2->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right)));
					this->CancelButton2->DialogResult = System::Windows::Forms::DialogResult::Cancel;
					this->CancelButton2->Location = new System::Drawing::Point(495, 425);
					this->CancelButton2->Name = "CancelButton2";
					this->CancelButton2->Size = new System::Drawing::Size(75, 23);
					this->CancelButton2->TabIndex = 10;
					this->CancelButton2->Text = "Cancel";
					this->CancelButton2->UseVisualStyleBackColor = true;
					this->CancelButton2->Click += new System::EventHandler(this, &HdBdStreamExtractor::CancelButton2_Click);
					// 
					// InputGroupBox
					// 
					this->InputGroupBox->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
					this->InputGroupBox->Controls->Add(this->FileSelection);
					this->InputGroupBox->Controls->Add(this->FolderSelection);
					this->InputGroupBox->Controls->Add(this->FolderInputSourceButton);
					this->InputGroupBox->Controls->Add(this->FolderInputTextBox);
					this->InputGroupBox->Location = new System::Drawing::Point(12, 3);
					this->InputGroupBox->Name = "InputGroupBox";
					this->InputGroupBox->Size = new System::Drawing::Size(558, 74);
					this->InputGroupBox->TabIndex = 0;
					this->InputGroupBox->TabStop = false;
					this->InputGroupBox->Text = "Input";
					// 
					// FileSelection
					// 
					this->FileSelection->AutoSize = true;
					this->FileSelection->Location = new System::Drawing::Point(170, 46);
					this->FileSelection->Name = "FileSelection";
					this->FileSelection->Size = new System::Drawing::Size(116, 17);
					this->FileSelection->TabIndex = 14;
					this->FileSelection->TabStop = true;
					this->FileSelection->Text = "Select File as Input";
					this->FileSelection->UseVisualStyleBackColor = true;
					// 
					// FolderSelection
					// 
					this->FolderSelection->AutoSize = true;
					this->FolderSelection->Checked = true;
					this->FolderSelection->Location = new System::Drawing::Point(18, 46);
					this->FolderSelection->Name = "FolderSelection";
					this->FolderSelection->Size = new System::Drawing::Size(130, 17);
					this->FolderSelection->TabIndex = 13;
					this->FolderSelection->TabStop = true;
					this->FolderSelection->Text = "Select Folder as Input";
					this->FolderSelection->UseVisualStyleBackColor = true;
					// 
					// FolderInputSourceButton
					// 
					this->FolderInputSourceButton->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right)));
					this->FolderInputSourceButton->AutoSize = true;
					this->FolderInputSourceButton->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
					this->FolderInputSourceButton->Location = new System::Drawing::Point(523, 16);
					this->FolderInputSourceButton->Name = "FolderInputSourceButton";
					this->FolderInputSourceButton->Size = new System::Drawing::Size(29, 23);
					this->FolderInputSourceButton->TabIndex = 12;
					this->FolderInputSourceButton->Text = "...";
					this->FolderInputSourceButton->UseVisualStyleBackColor = true;
					this->FolderInputSourceButton->Click += new System::EventHandler(this, &HdBdStreamExtractor::FolderInputSourceButton_Click);
					// 
					// Eac3toLinkLabel
					// 
					this->Eac3toLinkLabel->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left)));
					this->Eac3toLinkLabel->AutoSize = true;
					this->Eac3toLinkLabel->Location = new System::Drawing::Point(57, 430);
					this->Eac3toLinkLabel->Name = "Eac3toLinkLabel";
					this->Eac3toLinkLabel->Size = new System::Drawing::Size(40, 13);
					this->Eac3toLinkLabel->TabIndex = 13;
					this->Eac3toLinkLabel->TabStop = true;
					this->Eac3toLinkLabel->Text = "eac3to";
					this->Eac3toLinkLabel->LinkClicked += new System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &HdBdStreamExtractor::Eac3toLinkLabel_LinkClicked);
					// 
					// FeatureGroupBox
					// 
					this->FeatureGroupBox->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
					this->FeatureGroupBox->Controls->Add(this->FeatureDataGridView);
					this->FeatureGroupBox->Location = new System::Drawing::Point(12, 134);
					this->FeatureGroupBox->Name = "FeatureGroupBox";
					this->FeatureGroupBox->Size = new System::Drawing::Size(558, 110);
					this->FeatureGroupBox->TabIndex = 14;
					this->FeatureGroupBox->TabStop = false;
					this->FeatureGroupBox->Text = "Feature(s)";
					// 
					// FeatureDataGridView
					// 
					this->FeatureDataGridView->AllowUserToAddRows = false;
					this->FeatureDataGridView->AllowUserToDeleteRows = false;
					this->FeatureDataGridView->AllowUserToResizeColumns = false;
					this->FeatureDataGridView->AllowUserToResizeRows = false;
					this->FeatureDataGridView->AutoGenerateColumns = false;
					this->FeatureDataGridView->AutoSizeRowsMode = System::Windows::Forms::DataGridViewAutoSizeRowsMode::AllCells;
					this->FeatureDataGridView->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
					this->FeatureDataGridView->Columns->AddRange(new System::Windows::Forms::DataGridViewColumn[5] {this->FeatureNumberDataGridViewTextBoxColumn1, this->FeatureNameDataGridViewTextBoxColumn, this->FeatureDescriptionDataGridViewTextBoxColumn, this->FeatureFileDataGridViewComboBoxColumn, this->FeatureDurationDataGridViewTextBoxColumn});
					this->FeatureDataGridView->DataSource = this->FeatureBindingSource;
					this->FeatureDataGridView->Dock = System::Windows::Forms::DockStyle::Fill;
					this->FeatureDataGridView->Location = new System::Drawing::Point(3, 17);
					this->FeatureDataGridView->MultiSelect = false;
					this->FeatureDataGridView->Name = "FeatureDataGridView";
					this->FeatureDataGridView->RowHeadersVisible = false;
					this->FeatureDataGridView->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
					this->FeatureDataGridView->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
					this->FeatureDataGridView->ShowEditingIcon = false;
					this->FeatureDataGridView->Size = new System::Drawing::Size(552, 90);
					this->FeatureDataGridView->TabIndex = 13;
					this->FeatureDataGridView->DataSourceChanged += new System::EventHandler(this, &HdBdStreamExtractor::FeatureDataGridView_DataSourceChanged);
					this->FeatureDataGridView->DataBindingComplete += new System::Windows::Forms::DataGridViewBindingCompleteEventHandler(this, &HdBdStreamExtractor::FeatureDataGridView_DataBindingComplete);
					this->FeatureDataGridView->RowLeave += new System::Windows::Forms::DataGridViewCellEventHandler(this, &HdBdStreamExtractor::FeatureDataGridView_RowLeave);
					// 
					// FeatureNumberDataGridViewTextBoxColumn1
					// 
					this->FeatureNumberDataGridViewTextBoxColumn1->DataPropertyName = "Number";
					this->FeatureNumberDataGridViewTextBoxColumn1->HeaderText = "#";
					this->FeatureNumberDataGridViewTextBoxColumn1->MinimumWidth = 26;
					this->FeatureNumberDataGridViewTextBoxColumn1->Name = "FeatureNumberDataGridViewTextBoxColumn1";
					this->FeatureNumberDataGridViewTextBoxColumn1->ReadOnly = true;
					this->FeatureNumberDataGridViewTextBoxColumn1->Resizable = System::Windows::Forms::DataGridViewTriState::False;
					this->FeatureNumberDataGridViewTextBoxColumn1->ToolTipText = "Feature number";
					this->FeatureNumberDataGridViewTextBoxColumn1->Width = 26;
					// 
					// FeatureNameDataGridViewTextBoxColumn
					// 
					this->FeatureNameDataGridViewTextBoxColumn->DataPropertyName = "Name";
					this->FeatureNameDataGridViewTextBoxColumn->HeaderText = "Name";
					this->FeatureNameDataGridViewTextBoxColumn->MinimumWidth = 125;
					this->FeatureNameDataGridViewTextBoxColumn->Name = "FeatureNameDataGridViewTextBoxColumn";
					this->FeatureNameDataGridViewTextBoxColumn->ReadOnly = true;
					this->FeatureNameDataGridViewTextBoxColumn->Resizable = System::Windows::Forms::DataGridViewTriState::False;
					this->FeatureNameDataGridViewTextBoxColumn->ToolTipText = "Feature name";
					this->FeatureNameDataGridViewTextBoxColumn->Width = 125;
					// 
					// FeatureDescriptionDataGridViewTextBoxColumn
					// 
					this->FeatureDescriptionDataGridViewTextBoxColumn->DataPropertyName = "Description";
					this->FeatureDescriptionDataGridViewTextBoxColumn->HeaderText = "Description";
					this->FeatureDescriptionDataGridViewTextBoxColumn->MinimumWidth = 244;
					this->FeatureDescriptionDataGridViewTextBoxColumn->Name = "FeatureDescriptionDataGridViewTextBoxColumn";
					this->FeatureDescriptionDataGridViewTextBoxColumn->ReadOnly = true;
					this->FeatureDescriptionDataGridViewTextBoxColumn->Resizable = System::Windows::Forms::DataGridViewTriState::False;
					this->FeatureDescriptionDataGridViewTextBoxColumn->ToolTipText = "Feature description";
					this->FeatureDescriptionDataGridViewTextBoxColumn->Width = 244;
					// 
					// FeatureFileDataGridViewComboBoxColumn
					// 
					this->FeatureFileDataGridViewComboBoxColumn->HeaderText = "File(s)";
					this->FeatureFileDataGridViewComboBoxColumn->MinimumWidth = 90;
					this->FeatureFileDataGridViewComboBoxColumn->Name = "FeatureFileDataGridViewComboBoxColumn";
					this->FeatureFileDataGridViewComboBoxColumn->Resizable = System::Windows::Forms::DataGridViewTriState::False;
					this->FeatureFileDataGridViewComboBoxColumn->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::Automatic;
					this->FeatureFileDataGridViewComboBoxColumn->ToolTipText = "Feature File(s)";
					this->FeatureFileDataGridViewComboBoxColumn->Width = 90;
					// 
					// FeatureDurationDataGridViewTextBoxColumn
					// 
					this->FeatureDurationDataGridViewTextBoxColumn->DataPropertyName = "Duration";
					this->FeatureDurationDataGridViewTextBoxColumn->HeaderText = "Duration";
					this->FeatureDurationDataGridViewTextBoxColumn->MinimumWidth = 52;
					this->FeatureDurationDataGridViewTextBoxColumn->Name = "FeatureDurationDataGridViewTextBoxColumn";
					this->FeatureDurationDataGridViewTextBoxColumn->ReadOnly = true;
					this->FeatureDurationDataGridViewTextBoxColumn->Resizable = System::Windows::Forms::DataGridViewTriState::False;
					this->FeatureDurationDataGridViewTextBoxColumn->Width = 52;
					// 
					// FeatureBindingSource
					// 
					this->FeatureBindingSource->AllowNew = false;
					this->FeatureBindingSource->DataSource = eac3to::Feature::typeid;
					// 
					// StreamGroupBox
					// 
					this->StreamGroupBox->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
					this->StreamGroupBox->Controls->Add(this->StreamDataGridView);
					this->StreamGroupBox->Location = new System::Drawing::Point(12, 250);
					this->StreamGroupBox->Name = "StreamGroupBox";
					this->StreamGroupBox->Size = new System::Drawing::Size(558, 169);
					this->StreamGroupBox->TabIndex = 15;
					this->StreamGroupBox->TabStop = false;
					this->StreamGroupBox->Text = "Stream(s)";
					// 
					// StreamDataGridView
					// 
					this->StreamDataGridView->AllowUserToAddRows = false;
					this->StreamDataGridView->AllowUserToDeleteRows = false;
					this->StreamDataGridView->AllowUserToResizeColumns = false;
					this->StreamDataGridView->AllowUserToResizeRows = false;
					dataGridViewCellStyle1->BackColor = System::Drawing::SystemColors::Window;
					this->StreamDataGridView->AlternatingRowsDefaultCellStyle = dataGridViewCellStyle1;
					this->StreamDataGridView->AutoGenerateColumns = false;
					this->StreamDataGridView->AutoSizeRowsMode = System::Windows::Forms::DataGridViewAutoSizeRowsMode::AllCells;
					this->StreamDataGridView->ColumnHeadersHeight = 21;
					this->StreamDataGridView->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::DisableResizing;
					this->StreamDataGridView->Columns->AddRange(new System::Windows::Forms::DataGridViewColumn[10] {this->StreamExtractCheckBox, this->StreamNumberTextBox, this->StreamTypeTextBox, this->StreamDescriptionTextBox, this->StreamExtractAsComboBox, this->StreamAddOptionsTextBox, this->numberDataGridViewTextBoxColumn, this->nameDataGridViewTextBoxColumn, this->typeDataGridViewTextBoxColumn, this->languageDataGridViewTextBoxColumn});
					this->StreamDataGridView->DataSource = this->StreamsBindingSource;
					this->StreamDataGridView->Dock = System::Windows::Forms::DockStyle::Fill;
					this->StreamDataGridView->Location = new System::Drawing::Point(3, 17);
					this->StreamDataGridView->MultiSelect = false;
					this->StreamDataGridView->Name = "StreamDataGridView";
					this->StreamDataGridView->RowHeadersVisible = false;
					this->StreamDataGridView->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
					this->StreamDataGridView->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
					this->StreamDataGridView->ShowEditingIcon = false;
					this->StreamDataGridView->Size = new System::Drawing::Size(552, 149);
					this->StreamDataGridView->TabIndex = 7;
					this->StreamDataGridView->DataSourceChanged += new System::EventHandler(this, &HdBdStreamExtractor::StreamDataGridView_DataSourceChanged);
					// 
					// StreamExtractCheckBox
					// 
					this->StreamExtractCheckBox->FalseValue = "0";
					this->StreamExtractCheckBox->HeaderText = "Extract?";
					this->StreamExtractCheckBox->IndeterminateValue = "-1";
					this->StreamExtractCheckBox->MinimumWidth = 50;
					this->StreamExtractCheckBox->Name = "StreamExtractCheckBox";
					this->StreamExtractCheckBox->Resizable = System::Windows::Forms::DataGridViewTriState::False;
					this->StreamExtractCheckBox->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::Automatic;
					this->StreamExtractCheckBox->ToolTipText = "Extract stream?";
					this->StreamExtractCheckBox->TrueValue = "1";
					this->StreamExtractCheckBox->Width = 50;
					// 
					// StreamNumberTextBox
					// 
					this->StreamNumberTextBox->DataPropertyName = "Number";
					this->StreamNumberTextBox->HeaderText = "#";
					this->StreamNumberTextBox->MinimumWidth = 26;
					this->StreamNumberTextBox->Name = "StreamNumberTextBox";
					this->StreamNumberTextBox->Resizable = System::Windows::Forms::DataGridViewTriState::False;
					this->StreamNumberTextBox->ToolTipText = "Stream Number";
					this->StreamNumberTextBox->Width = 26;
					// 
					// StreamTypeTextBox
					// 
					this->StreamTypeTextBox->DataPropertyName = "Type";
					this->StreamTypeTextBox->HeaderText = "Type";
					this->StreamTypeTextBox->MinimumWidth = 45;
					this->StreamTypeTextBox->Name = "StreamTypeTextBox";
					this->StreamTypeTextBox->Resizable = System::Windows::Forms::DataGridViewTriState::False;
					this->StreamTypeTextBox->ToolTipText = "Stream type";
					this->StreamTypeTextBox->Width = 45;
					// 
					// StreamDescriptionTextBox
					// 
					this->StreamDescriptionTextBox->DataPropertyName = "Description";
					this->StreamDescriptionTextBox->HeaderText = "Description";
					this->StreamDescriptionTextBox->MinimumWidth = 260;
					this->StreamDescriptionTextBox->Name = "StreamDescriptionTextBox";
					this->StreamDescriptionTextBox->Resizable = System::Windows::Forms::DataGridViewTriState::False;
					this->StreamDescriptionTextBox->ToolTipText = "Stream description";
					this->StreamDescriptionTextBox->Width = 260;
					// 
					// StreamExtractAsComboBox
					// 
					this->StreamExtractAsComboBox->HeaderText = "Extract As";
					this->StreamExtractAsComboBox->MinimumWidth = 69;
					this->StreamExtractAsComboBox->Name = "StreamExtractAsComboBox";
					this->StreamExtractAsComboBox->Resizable = System::Windows::Forms::DataGridViewTriState::False;
					this->StreamExtractAsComboBox->ToolTipText = "Stream extract type";
					this->StreamExtractAsComboBox->Width = 69;
					// 
					// StreamAddOptionsTextBox
					// 
					this->StreamAddOptionsTextBox->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
					this->StreamAddOptionsTextBox->HeaderText = "+ Options";
					this->StreamAddOptionsTextBox->MinimumWidth = 65;
					this->StreamAddOptionsTextBox->Name = "StreamAddOptionsTextBox";
					this->StreamAddOptionsTextBox->Resizable = System::Windows::Forms::DataGridViewTriState::False;
					this->StreamAddOptionsTextBox->ToolTipText = "Stream extract additional options";
					// 
					// numberDataGridViewTextBoxColumn
					// 
					this->numberDataGridViewTextBoxColumn->DataPropertyName = "Number";
					this->numberDataGridViewTextBoxColumn->HeaderText = "Number";
					this->numberDataGridViewTextBoxColumn->Name = "numberDataGridViewTextBoxColumn";
					// 
					// nameDataGridViewTextBoxColumn
					// 
					this->nameDataGridViewTextBoxColumn->DataPropertyName = "Name";
					this->nameDataGridViewTextBoxColumn->HeaderText = "Name";
					this->nameDataGridViewTextBoxColumn->Name = "nameDataGridViewTextBoxColumn";
					// 
					// typeDataGridViewTextBoxColumn
					// 
					this->typeDataGridViewTextBoxColumn->DataPropertyName = "Type";
					this->typeDataGridViewTextBoxColumn->HeaderText = "Type";
					this->typeDataGridViewTextBoxColumn->Name = "typeDataGridViewTextBoxColumn";
					// 
					// languageDataGridViewTextBoxColumn
					// 
					this->languageDataGridViewTextBoxColumn->DataPropertyName = "Language";
					this->languageDataGridViewTextBoxColumn->HeaderText = "Language";
					this->languageDataGridViewTextBoxColumn->Name = "languageDataGridViewTextBoxColumn";
					// 
					// StreamsBindingSource
					// 
					this->StreamsBindingSource->DataSource = eac3to::Stream::typeid;
					// 
					// OutputGroupBox
					// 
					this->OutputGroupBox->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
					this->OutputGroupBox->Controls->Add(this->FolderOutputSourceButton);
					this->OutputGroupBox->Controls->Add(this->FolderOutputTextBox);
					this->OutputGroupBox->Location = new System::Drawing::Point(10, 83);
					this->OutputGroupBox->Name = "OutputGroupBox";
					this->OutputGroupBox->Size = new System::Drawing::Size(558, 45);
					this->OutputGroupBox->TabIndex = 16;
					this->OutputGroupBox->TabStop = false;
					this->OutputGroupBox->Text = "Output";
					// 
					// FolderOutputSourceButton
					// 
					this->FolderOutputSourceButton->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right)));
					this->FolderOutputSourceButton->AutoSize = true;
					this->FolderOutputSourceButton->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
					this->FolderOutputSourceButton->Location = new System::Drawing::Point(523, 17);
					this->FolderOutputSourceButton->Name = "FolderOutputSourceButton";
					this->FolderOutputSourceButton->Size = new System::Drawing::Size(29, 23);
					this->FolderOutputSourceButton->TabIndex = 13;
					this->FolderOutputSourceButton->Text = "...";
					this->FolderOutputSourceButton->UseVisualStyleBackColor = true;
					this->FolderOutputSourceButton->Click += new System::EventHandler(this, &HdBdStreamExtractor::FolderOutputSourceButton_Click);
					// 
					// FolderOutputTextBox
					// 
					this->FolderOutputTextBox->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
					this->FolderOutputTextBox->Location = new System::Drawing::Point(6, 19);
					this->FolderOutputTextBox->Name = "FolderOutputTextBox";
					this->FolderOutputTextBox->Size = new System::Drawing::Size(514, 21);
					this->FolderOutputTextBox->TabIndex = 1;
					// 
					// openFileDialog1
					// 
					this->openFileDialog1->Filter = "E-VOB Files (.*evo,*.vob)|*.evo;*.vob|Transport Streams Files (*.m2t*,*.mts,*.ts)" + "|*.m2t*;*.mts;*.ts|Matroska Files (.*mkv)|*.mkv|Blu-ray Playlist|*.mpls|All Files supported|*.evo;*.vob;" + "*.m2t*;*.mts;*.ts;*.mkv;*.mpls";
					this->openFileDialog1->FilterIndex = 5;
					this->openFileDialog1->Multiselect = true;
					// 
					// FeatureButton
					// 
					this->FeatureButton->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right)));
					this->FeatureButton->Location = new System::Drawing::Point(333, 425);
					this->FeatureButton->Name = "FeatureButton";
					this->FeatureButton->Size = new System::Drawing::Size(75, 23);
					this->FeatureButton->TabIndex = 18;
					this->FeatureButton->Text = "Features";
					this->FeatureButton->UseVisualStyleBackColor = true;
					this->FeatureButton->Visible = false;
					// 
					// extractTypesBindingSource
					// 
					this->extractTypesBindingSource->DataMember = "ExtractTypes";
					this->extractTypesBindingSource->DataSource = this->StreamsBindingSource;
					// 
					// closeOnQueue
					// 
					this->closeOnQueue->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right)));
					this->closeOnQueue->Checked = true;
					this->closeOnQueue->CheckState = System::Windows::Forms::CheckState::Checked;
					this->closeOnQueue->Location = new System::Drawing::Point(336, 425);
					this->closeOnQueue->Name = "closeOnQueue";
					this->closeOnQueue->Size = new System::Drawing::Size(72, 24);
					this->closeOnQueue->TabIndex = 19;
					this->closeOnQueue->Text = "and close";
					// 
					// HdBdStreamExtractor
					// 
					this->AutoScaleDimensions = new System::Drawing::SizeF(6, 13);
					this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
					this->ClientSize = new System::Drawing::Size(580, 478);
					this->Controls->Add(this->closeOnQueue);
					this->Controls->Add(this->FeatureButton);
					this->Controls->Add(this->OutputGroupBox);
					this->Controls->Add(this->StreamGroupBox);
					this->Controls->Add(this->FeatureGroupBox);
					this->Controls->Add(this->Eac3toLinkLabel);
					this->Controls->Add(this->InputGroupBox);
					this->Controls->Add(this->CancelButton2);
					this->Controls->Add(this->QueueButton);
					this->Controls->Add(this->HelpButton2);
					this->Controls->Add(this->StatusStrip);
					this->Font = new System::Drawing::Font("Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, (static_cast<unsigned char>(0)));
					this->Icon = (static_cast<System::Drawing::Icon*>(resources->GetObject("$this.Icon")));
					this->MaximizeBox = false;
					this->Name = "HdBdStreamExtractor";
					this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
					this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
					this->Text = "MeGUI - HD-DVD/Blu-ray Streams Extractor";
					this->FormClosing += new System::Windows::Forms::FormClosingEventHandler(this, &HdBdStreamExtractor::HdBrStreamExtractor_FormClosing);
					this->StatusStrip->ResumeLayout(false);
					this->StatusStrip->PerformLayout();
					this->InputGroupBox->ResumeLayout(false);
					this->InputGroupBox->PerformLayout();
					this->FeatureGroupBox->ResumeLayout(false);
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->FeatureDataGridView))->EndInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->FeatureBindingSource))->EndInit();
					this->StreamGroupBox->ResumeLayout(false);
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->StreamDataGridView))->EndInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->StreamsBindingSource))->EndInit();
					this->OutputGroupBox->ResumeLayout(false);
					this->OutputGroupBox->PerformLayout();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->extractTypesBindingSource))->EndInit();
					this->ResumeLayout(false);
					this->PerformLayout();

				}

				void HdBdStreamExtractor::InitializeInstanceFields()
				{
					delete lastJob;
					inputType = 1;
					dummyInput = "";
					input = std::vector<std::string>();
					delete components;
				}
			}
		}
	}
}
