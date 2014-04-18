#include "MeXgui.packages.tools.oneclick.OneClickConfigPanel.h"




//using namespace System::Collections::Generic;


namespace MeXgui
{
	namespace packages
	{
		namespace tools
		{
			namespace oneclick
			{

				void OneClickConfigPanel::initAvsHandler()
				{
					// Init AVS handlers
					avsProfile->setManager(mainForm->getProfiles());
				}

				void OneClickConfigPanel::initVideoHandler()
				{
					videoProfile->setManager(mainForm->getProfiles());
				}

				OneClickConfigPanel::OneClickConfigPanel()
				{
					InitializeInstanceFields();
					InitializeComponent();
					mainForm = MainForm::Instance;
					// We do this because the designer will attempt to put such a long string in the resources otherwise
					containerFormatLabel->Text = "Since the possible output filetypes are not known until the input is configured, the output type cannot be configured in a profile. Instead, here is a list of known file-types. You choose which you are happy with, and MeXgui will attempt to encode to one of those on the list.";

					for (QVector<ContainerType*>::const_iterator t = mainForm->getMuxProvider()->GetSupportedContainers().begin(); t != mainForm->getMuxProvider()->GetSupportedContainers().end(); ++t)
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
						containerTypeList->Items->Add((*t)->ToString());

					initAvsHandler();
					initVideoHandler();

					audioConfigurations = QVector<OneClickAudioControl*>();
					audioConfigurations.push_back(oneClickAudioControl1);
					oneClickAudioControl1->SetDefault();
					cbUnknownLanguage->Items->AddRange((QVector<QString>(LanguageSelectionContainer::getLanguages().Keys))->ToArray());
					cbUnknownLanguage->SelectedItem = "English";

				}

				const MeXgui::OneClickSettings &OneClickConfigPanel::getSettings() const
				{
					OneClickSettings *val = new OneClickSettings();
					val->setAutomaticDeinterlacing(autoDeint->Checked);
					val->setAvsProfileName(avsProfile->getSelectedProfile()->getFQName());
					val->setContainerCandidates(getContainerCandidates());
					val->setDontEncodeVideo(chkDontEncodeVideo->Checked);
					val->setDisableIntermediateMKV(chkDisableIntermediateMKV->Checked);
					val->setFilesize(fileSize->getValue());
					val->setOutputResolution(static_cast<qint64>(horizontalResolution->Value));
					val->setPrerenderVideo(preprocessVideo->Checked);
					val->setSignalAR(signalAR->Checked);
					val->setSplitSize(splitSize->getValue());
					val->setAutoCrop(autoCrop->Checked);
					val->setKeepInputResolution(keepInputResolution->Checked);
					val->setVideoProfileName(videoProfile->getSelectedProfile()->getFQName());
					val->setUseChaptersMarks(usechaptersmarks->Checked);
					val->setDefaultWorkingDirectory(workingDirectory->getFilename());
					val->setDefaultOutputDirectory(outputDirectory->getFilename());

					QVector<OneClickAudioSettings*> arrSettings = QVector<OneClickAudioSettings*>();
					for (int i = 0; i < audioConfigurations.size(); i++)
					{
						bool bFound = false;
						for (int j = 0; j < i; j++)
						{
							if (audioConfigurations[i]->getLanguage()->Equals(audioConfigurations[j]->getLanguage()))
							{
								bFound = true;
								break;
							}
						}
						if (!bFound)
							arrSettings.push_back(new OneClickAudioSettings(audioConfigurations[i]->getLanguage(), audioConfigurations[i]->getEncoderProfile()->getFQName(), audioConfigurations[i]->getEncodingMode(), audioConfigurations[i]->getUseFirstTrackOnly()));
					}
					val->setAudioSettings(arrSettings);

					QVector<QString> arrDefaultAudio = QVector<QString>();
					for (unknown::const_iterator s = lbDefaultAudio->Items.begin(); s != lbDefaultAudio->Items.end(); ++s)
						arrDefaultAudio.push_back(*s);
					val->setDefaultAudioLanguage(arrDefaultAudio);

					QVector<QString> arrDefaultSubtitle = QVector<QString>();
					for (unknown::const_iterator s = lbDefaultSubtitle->Items.begin(); s != lbDefaultSubtitle->Items.end(); ++s)
						arrDefaultSubtitle.push_back(*s);
					val->setDefaultSubtitleLanguage(arrDefaultSubtitle);

					val->setDefaultLanguage(cbUnknownLanguage->SelectedText);

					QVector<QString> arrIndexerPriority = QVector<QString>();
					for (unknown::const_iterator s = lbIndexerPriority->Items.begin(); s != lbIndexerPriority->Items.end(); ++s)
						arrIndexerPriority.push_back(*s);

					if (cbLanguageSelect->SelectedText->Equals("none"))
						val->setUseNoLanguagesAsFallback(true);
					else
						val->setUseNoLanguagesAsFallback(false);

					val->setIndexerPriority(arrIndexerPriority);
					val->setLeadingName(txtLeadingName->Text);
					val->setWorkingNameReplace(txtWorkingNameDelete->Text);
					val->setWorkingNameReplaceWith(txtWorkingNameReplaceWith->Text);
					return val;
				}

				void OneClickConfigPanel::setSettings(const OneClickSettings &value)
				{
					autoDeint->Checked = value->getAutomaticDeinterlacing();
					avsProfile->SetProfileNameOrWarn(value->getAvsProfileName());
					setContainerCandidates(value->getContainerCandidates());
					chkDontEncodeVideo->Checked = value->getDontEncodeVideo();
					fileSize->setValue(value->getFilesize());
					horizontalResolution->Value = value->getOutputResolution();
					preprocessVideo->Checked = value->getPrerenderVideo();
					signalAR->Checked = value->getSignalAR();
					chkDisableIntermediateMKV->Checked = value->getDisableIntermediateMKV();
					splitSize->setValue(value->getSplitSize());
					autoCrop->Checked = value->getAutoCrop();
					keepInputResolution->Checked = value->getKeepInputResolution();
					videoProfile->SetProfileNameOrWarn(value->getVideoProfileName());
					usechaptersmarks->Checked = value->getUseChaptersMarks();
					workingDirectory->setFilename(value->getDefaultWorkingDirectory());
					outputDirectory->setFilename(value->getDefaultOutputDirectory());
					txtWorkingNameDelete->Text = value->getWorkingNameReplace();
					txtWorkingNameReplaceWith->Text = value->getWorkingNameReplaceWith();
					txtLeadingName->Text = value->getLeadingName();

					int i = 0;
					AudioResetTrack();
					for (QVector<OneClickAudioSettings*>::const_iterator o = value->getAudioSettings().begin(); o != value->getAudioSettings().end(); ++o)
					{
						if (i++ == 0)
						{
							audioConfigurations[0]->SetProfileNameOrWarn((*o)->getProfile());
							audioConfigurations[0]->setEncodingMode((*o)->getAudioEncodingMode());
							audioConfigurations[0]->setUseFirstTrackOnly((*o)->getUseFirstTrackOnly());
						}
						else
							AudioAddTrack(*o);
					}

					if (!value->getDefaultLanguage().empty())
						cbUnknownLanguage->SelectedItem = value->getDefaultLanguage();

					QVector<QString> arrNonDefaultAudio = QVector<QString>(LanguageSelectionContainer::getLanguages().Keys);
					arrNonDefaultAudio.push_back("[none]");
					for (QVector<QString>::const_iterator strLanguage = value->getDefaultAudioLanguage().begin(); strLanguage != value->getDefaultAudioLanguage().end(); ++strLanguage)
						arrNonDefaultAudio.Remove(*strLanguage);

					QVector<QString> arrNonDefaultSubtitle = QVector<QString>(LanguageSelectionContainer::getLanguages().Keys);
					arrNonDefaultSubtitle.push_back("[none]");
					for (QVector<QString>::const_iterator strLanguage = value->getDefaultSubtitleLanguage().begin(); strLanguage != value->getDefaultSubtitleLanguage().end(); ++strLanguage)
						arrNonDefaultSubtitle.Remove(*strLanguage);

					lbDefaultAudio->Items->Clear();
					lbDefaultAudio->Items->AddRange(value->getDefaultAudioLanguage().ToArray());
					lbDefaultAudio_SelectedIndexChanged(0, 0);
					lbNonDefaultAudio->Items->Clear();
					lbNonDefaultAudio->Items->AddRange(arrNonDefaultAudio.ToArray());
					lbNonDefaultAudio_SelectedIndexChanged(0, 0);

					lbDefaultSubtitle->Items->Clear();
					lbDefaultSubtitle->Items->AddRange(value->getDefaultSubtitleLanguage().ToArray());
					lbDefaultSubtitle_SelectedIndexChanged(0, 0);
					lbNonDefaultSubtitle->Items->Clear();
					lbNonDefaultSubtitle->Items->AddRange(arrNonDefaultSubtitle.ToArray());
					lbNonDefaultSubtitle_SelectedIndexChanged(0, 0);

					lbIndexerPriority->Items->Clear();
					lbIndexerPriority->Items->AddRange(value->getIndexerPriority().ToArray());

					if (!value->getUseNoLanguagesAsFallback())
						cbLanguageSelect->SelectedItem = "all";
					else
						cbLanguageSelect->SelectedItem = "none";
				}

				const QString &OneClickConfigPanel::getContainerCandidates() const
				{
					QString val[containerTypeList->CheckedItems->Count];
					containerTypeList->CheckedItems->CopyTo(val, 0);
					return val;
				}

				void OneClickConfigPanel::setContainerCandidates(const QString &value[])
				{
					for (int i = 0; i < containerTypeList->Items->Count; i++)
						containerTypeList->SetItemChecked(i, false);

					for (QString[]::const_iterator val = value->begin(); val != value->end(); ++val)
					{
						int index = containerTypeList->Items->find(*val);
						if (index > -1)
							containerTypeList->SetItemChecked(index, true);
					}
				}

				void OneClickConfigPanel::keepInputResolution_CheckedChanged()
				{
					if (keepInputResolution->Checked)
						horizontalResolution->Enabled = autoCrop->Enabled = signalAR->Enabled = false;
					else
						horizontalResolution->Enabled = autoCrop->Enabled = signalAR->Enabled = true;
				}

				void OneClickConfigPanel::videoProfile_SelectedProfileChanged()
				{
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'StartsWith' method:
					if (videoProfile->getSelectedProfile()->getFQName().StartsWith("x264") && !chkDontEncodeVideo->Checked)
						usechaptersmarks->Enabled = true;
					else
						usechaptersmarks->Enabled = false;
				}

				void OneClickConfigPanel::chkDontEncodeVideo_CheckedChanged()
				{
					if (chkDontEncodeVideo->Checked)
					{
						horizontalResolution->Enabled = autoCrop->Enabled = signalAR->Enabled = videoProfile->Enabled = false;
						usechaptersmarks->Enabled = keepInputResolution->Enabled = preprocessVideo->Enabled = false;
						autoDeint->Enabled = fileSize->Enabled = avsProfile->Enabled = false;
					}
					else
					{
						videoProfile->Enabled = keepInputResolution->Enabled = preprocessVideo->Enabled = true;
						autoDeint->Enabled = fileSize->Enabled = avsProfile->Enabled = true;
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'StartsWith' method:
						if (videoProfile->getSelectedProfile()->getFQName().StartsWith("x264"))
							usechaptersmarks->Enabled = true;
						else
							usechaptersmarks->Enabled = false;
						if (keepInputResolution->Checked)
							horizontalResolution->Enabled = autoCrop->Enabled = signalAR->Enabled = false;
						else
							horizontalResolution->Enabled = autoCrop->Enabled = signalAR->Enabled = true;
					}
				}

				void OneClickConfigPanel::btnAddAudio_Click()
				{
					QVector<QString> arrAudio = QVector<QString>();
					for (unknown::const_iterator s = lbNonDefaultAudio->SelectedItems.begin(); s != lbNonDefaultAudio->SelectedItems.end(); ++s)
					{
						lbDefaultAudio->Items->Add(*s);
						arrAudio.push_back(*s);
					}
					for (QVector<QString>::const_iterator s = arrAudio.begin(); s != arrAudio.end(); ++s)
						lbNonDefaultAudio->Items->Remove(*s);
				}

				void OneClickConfigPanel::btnRemoveAudio_Click()
				{
					QVector<QString> arrAudio = QVector<QString>();
					for (unknown::const_iterator s = lbDefaultAudio->SelectedItems.begin(); s != lbDefaultAudio->SelectedItems.end(); ++s)
					{
						lbNonDefaultAudio->Items->Add(*s);
						arrAudio.push_back(*s);
					}
					for (QVector<QString>::const_iterator s = arrAudio.begin(); s != arrAudio.end(); ++s)
						lbDefaultAudio->Items->Remove(*s);
				}

				void OneClickConfigPanel::btnAudioUp_Click()
				{
					int iPos = lbDefaultAudio->SelectedIndex;
					if (iPos < 1)
						return;

					object *o = lbDefaultAudio->SelectedItem;
					lbDefaultAudio->Items->RemoveAt(iPos);
					lbDefaultAudio->Items->Insert(iPos - 1, o);
					lbDefaultAudio->SelectedIndex = iPos - 1;
				}

				void OneClickConfigPanel::btnAudioDown_Click()
				{
					int iPos = lbDefaultAudio->SelectedIndex;
					if (iPos < 0 || iPos > lbDefaultAudio->Items->Count - 2)
						return;

					object *o = lbDefaultAudio->SelectedItem;
					lbDefaultAudio->Items->RemoveAt(iPos);
					lbDefaultAudio->Items->Insert(iPos + 1, o);
					lbDefaultAudio->SelectedIndex = iPos + 1;
				}

				void OneClickConfigPanel::lbDefaultAudio_SelectedIndexChanged()
				{
					if (lbDefaultAudio->SelectedIndex < 0)
					{
						btnRemoveAudio->Enabled = btnAudioUp->Enabled = btnAudioDown->Enabled = false;
						return;
					}
					btnRemoveAudio->Enabled = true;
					if (lbDefaultAudio->SelectedIndex == 0)
						btnAudioUp->Enabled = false;
					else
						btnAudioUp->Enabled = true;
					if (lbDefaultAudio->SelectedIndex == lbDefaultAudio->Items->Count - 1)
						btnAudioDown->Enabled = false;
					else
						btnAudioDown->Enabled = true;
				}

				void OneClickConfigPanel::lbNonDefaultAudio_SelectedIndexChanged()
				{
					if (lbNonDefaultAudio->SelectedIndex < 0)
						btnAddAudio->Enabled = false;
					else
						btnAddAudio->Enabled = true;
				}

				void OneClickConfigPanel::btnAddSubtitle_Click()
				{
					QVector<QString> arrSubtitle = QVector<QString>();
					for (unknown::const_iterator s = lbNonDefaultSubtitle->SelectedItems.begin(); s != lbNonDefaultSubtitle->SelectedItems.end(); ++s)
					{
						lbDefaultSubtitle->Items->Add(*s);
						arrSubtitle.push_back(*s);
					}
					for (QVector<QString>::const_iterator s = arrSubtitle.begin(); s != arrSubtitle.end(); ++s)
						lbNonDefaultSubtitle->Items->Remove(*s);
				}

				void OneClickConfigPanel::btnRemoveSubtitle_Click()
				{
					QVector<QString> arrSubtitle = QVector<QString>();
					for (unknown::const_iterator s = lbDefaultSubtitle->SelectedItems.begin(); s != lbDefaultSubtitle->SelectedItems.end(); ++s)
					{
						lbNonDefaultSubtitle->Items->Add(*s);
						arrSubtitle.push_back(*s);
					}
					for (QVector<QString>::const_iterator s = arrSubtitle.begin(); s != arrSubtitle.end(); ++s)
						lbDefaultSubtitle->Items->Remove(*s);
				}

				void OneClickConfigPanel::btnSubtitleUp_Click()
				{
					int iPos = lbDefaultSubtitle->SelectedIndex;
					if (iPos < 1)
						return;

					object *o = lbDefaultSubtitle->SelectedItem;
					lbDefaultSubtitle->Items->RemoveAt(iPos);
					lbDefaultSubtitle->Items->Insert(iPos - 1, o);
					lbDefaultSubtitle->SelectedIndex = iPos - 1;
				}

				void OneClickConfigPanel::btnSubtitleDown_Click()
				{
					int iPos = lbDefaultSubtitle->SelectedIndex;
					if (iPos < 0 || iPos > lbDefaultSubtitle->Items->Count - 2)
						return;

					object *o = lbDefaultSubtitle->SelectedItem;
					lbDefaultSubtitle->Items->RemoveAt(iPos);
					lbDefaultSubtitle->Items->Insert(iPos + 1, o);
					lbDefaultSubtitle->SelectedIndex = iPos + 1;
				}

				void OneClickConfigPanel::lbDefaultSubtitle_SelectedIndexChanged()
				{
					if (lbDefaultSubtitle->SelectedIndex < 0)
					{
						btnRemoveSubtitle->Enabled = btnSubtitleUp->Enabled = btnSubtitleDown->Enabled = false;
						return;
					}
					btnRemoveSubtitle->Enabled = true;
					if (lbDefaultSubtitle->SelectedIndex == 0)
						btnSubtitleUp->Enabled = false;
					else
						btnSubtitleUp->Enabled = true;
					if (lbDefaultSubtitle->SelectedIndex == lbDefaultSubtitle->Items->Count - 1)
						btnSubtitleDown->Enabled = false;
					else
						btnSubtitleDown->Enabled = true;
				}

				void OneClickConfigPanel::lbNonDefaultSubtitle_SelectedIndexChanged()
				{
					if (lbNonDefaultSubtitle->SelectedIndex < 0)
						btnAddSubtitle->Enabled = false;
					else
						btnAddSubtitle->Enabled = true;
				}

				void OneClickConfigPanel::btnIndexerUp_Click()
				{
					int iPos = lbIndexerPriority->SelectedIndex;
					if (iPos < 1)
						return;

					object *o = lbIndexerPriority->SelectedItem;
					lbIndexerPriority->Items->RemoveAt(iPos);
					lbIndexerPriority->Items->Insert(iPos - 1, o);
					lbIndexerPriority->SelectedIndex = iPos - 1;
					lbIndexerPriority_MouseClick(0, 0);
				}

				void OneClickConfigPanel::btnIndexerDown_Click()
				{
					int iPos = lbIndexerPriority->SelectedIndex;
					if (iPos < 0 || iPos > lbIndexerPriority->Items->Count - 2)
						return;

					object *o = lbIndexerPriority->SelectedItem;
					lbIndexerPriority->Items->RemoveAt(iPos);
					lbIndexerPriority->Items->Insert(iPos + 1, o);
					lbIndexerPriority->SelectedIndex = iPos + 1;
					lbIndexerPriority_MouseClick(0, 0);
				}

				void OneClickConfigPanel::lbIndexerPriority_MouseClick(object *sender, MouseEventArgs *e)
				{
					int iPos = lbIndexerPriority->SelectedIndex;
					btnIndexerUp->Enabled = iPos > 0;
					btnIndexerDown->Enabled = iPos >= 0 && iPos <= lbIndexerPriority->Items->Count - 2;
				}

				void OneClickConfigPanel::audioTab_MouseClick(object *sender, MouseEventArgs *e)
				{
					if (e->Button != MouseButtons::Right)
						return;

					System::Drawing::Point *p = e->Location;
					for (int i = 0; i < audioTab->TabCount; i++)
					{
						System::Drawing::Rectangle *rect = audioTab->GetTabRect(i);
						rect->Offset(2, 2);
						rect->Width -= 4;
						rect->Height -= 4;
						if (rect->Contains(p))
						{
							iSelectedAudioTabPage = i;
							audioMenu->Show(audioTab, e->Location);
							break;
						}
					}
				}

				void OneClickConfigPanel::audioAddTrack_Click()
				{
					AudioAddTrack(0);
				}

				void OneClickConfigPanel::audioRemoveTrack_Click()
				{
					AudioRemoveTrack(iSelectedAudioTabPage);
				}

				void OneClickConfigPanel::AudioAddTrack(OneClickAudioSettings *oSettings)
				{
					if (oSettings == 0)
						oSettings = new OneClickAudioSettings("English", audioConfigurations[0]->getEncoderProfile()->getFQName(), audioConfigurations[0]->getEncodingMode(), audioConfigurations[0]->getUseFirstTrackOnly());

					TabPage *p = new TabPage(oSettings->getLanguage());
					p->UseVisualStyleBackColor = audioTab->TabPages[0]->UseVisualStyleBackColor;
					p->Padding = audioTab->TabPages[0]->Padding;

					OneClickAudioControl *a = new OneClickAudioControl();
					a->Dock = audioConfigurations[0]->Dock;
					a->Padding = audioConfigurations[0]->Padding;
					a->Location = audioConfigurations[0]->Location;
					a->setEncodingMode(oSettings->getAudioEncodingMode());
					a->SetProfileNameOrWarn(oSettings->getProfile());
					a->setLanguage(oSettings->getLanguage());
					a->setUseFirstTrackOnly(oSettings->getUseFirstTrackOnly());
					a->LanguageChanged += new EventHandler(this, &OneClickConfigPanel::audio1_LanguageChanged);
					audioConfigurations.push_back(a);

					audioTab->TabPages->Insert(audioTab->TabCount - 1, p);
					p->Controls->Add(a);
					audioTab->SelectedTab = p;
				}

				void OneClickConfigPanel::AudioResetTrack()
				{
					// delete all tracks beside the first and last one
					for (int i = audioTab->TabCount - 1; i > 1; i--)
						audioTab->TabPages->RemoveAt(i - 1);
					for (int i = audioConfigurations.size() - 1; i > 0; i--)
						audioConfigurations.RemoveAt(i);
				}

				void OneClickConfigPanel::audio1_LanguageChanged()
				{
					for (int i = 1; i < audioTab->TabCount - 1; i++)
						audioTab->TabPages[i]->Text = audioConfigurations[i]->getLanguage();
				}

				void OneClickConfigPanel::AudioRemoveTrack(int iTabPageIndex)
				{
					if (iTabPageIndex == 0 || iTabPageIndex == audioTab->TabCount - 1)
						return;

					audioTab->TabPages->RemoveAt(iTabPageIndex);
					audioConfigurations.RemoveAt(iTabPageIndex);
					if (iTabPageIndex < audioTab->TabCount - 1)
						audioTab->SelectedIndex = iTabPageIndex;
					else
						audioTab->SelectedIndex = iTabPageIndex - 1;
				}

				void OneClickConfigPanel::audioTab_SelectedIndexChanged()
				{
					if (audioTab->SelectedTab->Text->Equals("   +"))
						AudioAddTrack(0);
				}

				void OneClickConfigPanel::audioTab_KeyUp(object *sender, KeyEventArgs *e)
				{
					if (e->KeyCode == Keys::Delete || e->KeyCode == Keys::Back)
						AudioRemoveTrack(audioTab->SelectedIndex);
				}

				void OneClickConfigPanel::audioTab_VisibleChanged()
				{
					if (!audioTab->Visible || audioTab->TabCount == audioConfigurations.size() + 1)
						return;

					QVector<OneClickAudioSettings*> arrSettings = QVector<OneClickAudioSettings*>();
					for (QVector<OneClickAudioControl*>::const_iterator o = audioConfigurations.begin(); o != audioConfigurations.end(); ++o)
						arrSettings.push_back(new OneClickAudioSettings((*o)->getLanguage(), (*o)->getEncoderProfile()->FQName, (*o)->getEncodingMode(), (*o)->getUseFirstTrackOnly()));
					AudioResetTrack();
					int i = 0;
					for (QVector<OneClickAudioSettings*>::const_iterator o = arrSettings.begin(); o != arrSettings.end(); ++o)
					{
						if (i++ == 0)
						{
							audioConfigurations[0]->SetProfileNameOrWarn((*o)->Profile);
							audioConfigurations[0]->setEncodingMode((*o)->AudioEncodingMode);
						}
						else
							AudioAddTrack(*o);
					}
				}

				void OneClickConfigPanel::audioTab_MouseDoubleClick(object *sender, MouseEventArgs *e)
				{
					AudioAddTrack(0);
				}

				void OneClickConfigPanel::audioMenu_Opening(object *sender, System::ComponentModel::CancelEventArgs *e)
				{
					audioRemoveTrack->Enabled = (iSelectedAudioTabPage != audioConfigurations.size());
				}

				void OneClickConfigPanel::deleteOutput_Click()
				{
					outputDirectory->setFilename("");
				}

				void OneClickConfigPanel::deleteWorking_Click()
				{
					workingDirectory->setFilename("");
				}

				void OneClickConfigPanel::Dispose(bool disposing)
				{
					if (disposing && (components != 0))
					{
						delete components;
					}
					UserControl::Dispose(disposing);
				}

				void OneClickConfigPanel::InitializeComponent()
				{
					this->components = new System::ComponentModel::Container();
					System::Windows::Forms::Label *label3;
					this->otherGroupBox = new System::Windows::Forms::GroupBox();
					this->keepInputResolution = new System::Windows::Forms::CheckBox();
					this->autoCrop = new System::Windows::Forms::CheckBox();
					this->preprocessVideo = new System::Windows::Forms::CheckBox();
					this->autoDeint = new System::Windows::Forms::CheckBox();
					this->signalAR = new System::Windows::Forms::CheckBox();
					this->horizontalResolution = new System::Windows::Forms::NumericUpDown();
					this->outputResolutionLabel = new System::Windows::Forms::Label();
					this->tabControl1 = new System::Windows::Forms::TabControl();
					this->tabPage1 = new System::Windows::Forms::TabPage();
					this->groupBox6 = new System::Windows::Forms::GroupBox();
					this->chkDontEncodeVideo = new System::Windows::Forms::CheckBox();
					this->usechaptersmarks = new System::Windows::Forms::CheckBox();
					this->videoCodecLabel = new System::Windows::Forms::Label();
					this->tabPage3 = new System::Windows::Forms::TabPage();
					this->extraGroupbox = new System::Windows::Forms::GroupBox();
					this->audioTab = new System::Windows::Forms::TabControl();
					this->audioPage0 = new System::Windows::Forms::TabPage();
					this->audioPageAdd = new System::Windows::Forms::TabPage();
					this->tabPage2 = new System::Windows::Forms::TabPage();
					this->groupBox8 = new System::Windows::Forms::GroupBox();
					this->label2 = new System::Windows::Forms::Label();
					this->filesizeLabel = new System::Windows::Forms::Label();
					this->groupBox7 = new System::Windows::Forms::GroupBox();
					this->containerTypeList = new System::Windows::Forms::CheckedListBox();
					this->containerFormatLabel = new System::Windows::Forms::Label();
					this->tabPage4 = new System::Windows::Forms::TabPage();
					this->cbLanguageSelect = new System::Windows::Forms::ComboBox();
					this->label7 = new System::Windows::Forms::Label();
					this->groupBox2 = new System::Windows::Forms::GroupBox();
					this->btnSubtitleDown = new QPushButton;
					this->btnSubtitleUp = new QPushButton;
					this->btnRemoveSubtitle = new QPushButton;
					this->btnAddSubtitle = new QPushButton;
					this->lbNonDefaultSubtitle = new System::Windows::Forms::ListBox();
					this->lbDefaultSubtitle = new System::Windows::Forms::ListBox();
					this->groupBox1 = new System::Windows::Forms::GroupBox();
					this->btnAudioDown = new QPushButton;
					this->btnAudioUp = new QPushButton;
					this->btnRemoveAudio = new QPushButton;
					this->btnAddAudio = new QPushButton;
					this->lbNonDefaultAudio = new System::Windows::Forms::ListBox();
					this->lbDefaultAudio = new System::Windows::Forms::ListBox();
					this->tabPage5 = new System::Windows::Forms::TabPage();
					this->chkDisableIntermediateMKV = new System::Windows::Forms::CheckBox();
					this->groupBox5 = new System::Windows::Forms::GroupBox();
					this->deleteWorking = new QPushButton;
					this->deleteOutput = new QPushButton;
					this->label8 = new System::Windows::Forms::Label();
					this->workingDirectoryLabel = new System::Windows::Forms::Label();
					this->groupBox4 = new System::Windows::Forms::GroupBox();
					this->label1 = new System::Windows::Forms::Label();
					this->txtLeadingName = new System::Windows::Forms::TextBox();
					this->label6 = new System::Windows::Forms::Label();
					this->label5 = new System::Windows::Forms::Label();
					this->txtWorkingNameReplaceWith = new System::Windows::Forms::TextBox();
					this->txtWorkingNameDelete = new System::Windows::Forms::TextBox();
					this->groupBox3 = new System::Windows::Forms::GroupBox();
					this->btnIndexerDown = new QPushButton;
					this->btnIndexerUp = new QPushButton;
					this->lbIndexerPriority = new System::Windows::Forms::ListBox();
					this->audioMenu = new System::Windows::Forms::ContextMenuStrip(this->components);
					this->audioAddTrack = new System::Windows::Forms::ToolStripMenuItem();
					this->audioRemoveTrack = new System::Windows::Forms::ToolStripMenuItem();
					this->label4 = new System::Windows::Forms::Label();
					this->cbUnknownLanguage = new System::Windows::Forms::ComboBox();
					this->avsProfile = new MeXgui::core::gui::ConfigableProfilesControl();
					this->videoProfile = new MeXgui::core::gui::ConfigableProfilesControl();
					this->oneClickAudioControl1 = new MeXgui::OneClickAudioControl();
					this->splitSize = new MeXgui::core::gui::TargetSizeSCBox();
					this->fileSize = new MeXgui::core::gui::TargetSizeSCBox();
					this->outputDirectory = new MeXgui::FileBar();
					this->workingDirectory = new MeXgui::FileBar();
					label3 = new System::Windows::Forms::Label();
					this->otherGroupBox->SuspendLayout();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->horizontalResolution))->BeginInit();
					this->tabControl1->SuspendLayout();
					this->tabPage1->SuspendLayout();
					this->groupBox6->SuspendLayout();
					this->tabPage3->SuspendLayout();
					this->extraGroupbox->SuspendLayout();
					this->audioTab->SuspendLayout();
					this->audioPage0->SuspendLayout();
					this->tabPage2->SuspendLayout();
					this->groupBox8->SuspendLayout();
					this->groupBox7->SuspendLayout();
					this->tabPage4->SuspendLayout();
					this->groupBox2->SuspendLayout();
					this->groupBox1->SuspendLayout();
					this->tabPage5->SuspendLayout();
					this->groupBox5->SuspendLayout();
					this->groupBox4->SuspendLayout();
					this->groupBox3->SuspendLayout();
					this->audioMenu->SuspendLayout();
					this->SuspendLayout();
					// 
					// label3
					// 
					label3->AutoSize = true;
					label3->Location = new System::Drawing::Point(6, 96);
					label3->Name = "label3";
					label3->Size = new System::Drawing::Size(78, 13);
					label3->TabIndex = 40;
					label3->Text = "Avisynth profile";
					// 
					// otherGroupBox
					// 
					this->otherGroupBox->Controls->Add(this->keepInputResolution);
					this->otherGroupBox->Controls->Add(this->autoCrop);
					this->otherGroupBox->Controls->Add(label3);
					this->otherGroupBox->Controls->Add(this->avsProfile);
					this->otherGroupBox->Controls->Add(this->preprocessVideo);
					this->otherGroupBox->Controls->Add(this->autoDeint);
					this->otherGroupBox->Controls->Add(this->signalAR);
					this->otherGroupBox->Controls->Add(this->horizontalResolution);
					this->otherGroupBox->Controls->Add(this->outputResolutionLabel);
					this->otherGroupBox->Location = new System::Drawing::Point(6, 99);
					this->otherGroupBox->Name = "otherGroupBox";
					this->otherGroupBox->Size = new System::Drawing::Size(416, 152);
					this->otherGroupBox->TabIndex = 38;
					this->otherGroupBox->TabStop = false;
					this->otherGroupBox->Text = " Filesize and Avisynth setup ";
					// 
					// keepInputResolution
					// 
					this->keepInputResolution->AutoSize = true;
					this->keepInputResolution->Location = new System::Drawing::Point(109, 46);
					this->keepInputResolution->Name = "keepInputResolution";
					this->keepInputResolution->Size = new System::Drawing::Size(242, 17);
					this->keepInputResolution->TabIndex = 42;
					this->keepInputResolution->Text = "Keep Input Resolution (disable crop && resize)";
					this->keepInputResolution->UseVisualStyleBackColor = true;
					this->keepInputResolution->CheckedChanged += new System::EventHandler(this, &OneClickConfigPanel::keepInputResolution_CheckedChanged);
					// 
					// autoCrop
					// 
					this->autoCrop->AutoSize = true;
					this->autoCrop->Checked = true;
					this->autoCrop->CheckState = System::Windows::Forms::CheckState::Checked;
					this->autoCrop->Location = new System::Drawing::Point(188, 21);
					this->autoCrop->Name = "autoCrop";
					this->autoCrop->Size = new System::Drawing::Size(70, 17);
					this->autoCrop->TabIndex = 41;
					this->autoCrop->Text = "AutoCrop";
					this->autoCrop->UseVisualStyleBackColor = true;
					// 
					// preprocessVideo
					// 
					this->preprocessVideo->AutoSize = true;
					this->preprocessVideo->Location = new System::Drawing::Point(109, 118);
					this->preprocessVideo->Name = "preprocessVideo";
					this->preprocessVideo->Size = new System::Drawing::Size(101, 17);
					this->preprocessVideo->TabIndex = 37;
					this->preprocessVideo->Text = "Prerender video";
					this->preprocessVideo->UseVisualStyleBackColor = true;
					// 
					// autoDeint
					// 
					this->autoDeint->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right)));
					this->autoDeint->AutoSize = true;
					this->autoDeint->Location = new System::Drawing::Point(272, 118);
					this->autoDeint->Name = "autoDeint";
					this->autoDeint->Size = new System::Drawing::Size(138, 17);
					this->autoDeint->TabIndex = 35;
					this->autoDeint->Text = "Automatic Deinterlacing";
					this->autoDeint->UseVisualStyleBackColor = true;
					// 
					// signalAR
					// 
					this->signalAR->AutoSize = true;
					this->signalAR->Location = new System::Drawing::Point(272, 21);
					this->signalAR->Name = "signalAR";
					this->signalAR->Size = new System::Drawing::Size(109, 17);
					this->signalAR->TabIndex = 32;
					this->signalAR->Text = "Anamorph Output";
					this->signalAR->UseVisualStyleBackColor = true;
					// 
					// horizontalResolution
					// 
					this->horizontalResolution->Increment = decimal(new int[4] {16, 0, 0, 0});
					this->horizontalResolution->Location = new System::Drawing::Point(109, 20);
					this->horizontalResolution->Maximum = decimal(new int[4] {5000, 0, 0, 0});
					this->horizontalResolution->Minimum = decimal(new int[4] {16, 0, 0, 0});
					this->horizontalResolution->Name = "horizontalResolution";
					this->horizontalResolution->Size = new System::Drawing::Size(64, 20);
					this->horizontalResolution->TabIndex = 27;
					this->horizontalResolution->Value = decimal(new int[4] {640, 0, 0, 0});
					// 
					// outputResolutionLabel
					// 
					this->outputResolutionLabel->Location = new System::Drawing::Point(5, 24);
					this->outputResolutionLabel->Name = "outputResolutionLabel";
					this->outputResolutionLabel->Size = new System::Drawing::Size(100, 13);
					this->outputResolutionLabel->TabIndex = 30;
					this->outputResolutionLabel->Text = "Output Resolution";
					// 
					// tabControl1
					// 
					this->tabControl1->Controls->Add(this->tabPage1);
					this->tabControl1->Controls->Add(this->tabPage3);
					this->tabControl1->Controls->Add(this->tabPage2);
					this->tabControl1->Controls->Add(this->tabPage4);
					this->tabControl1->Controls->Add(this->tabPage5);
					this->tabControl1->Dock = System::Windows::Forms::DockStyle::Fill;
					this->tabControl1->Location = new System::Drawing::Point(0, 0);
					this->tabControl1->Name = "tabControl1";
					this->tabControl1->SelectedIndex = 0;
					this->tabControl1->Size = new System::Drawing::Size(433, 280);
					this->tabControl1->TabIndex = 39;
					// 
					// tabPage1
					// 
					this->tabPage1->Controls->Add(this->otherGroupBox);
					this->tabPage1->Controls->Add(this->groupBox6);
					this->tabPage1->Location = new System::Drawing::Point(4, 22);
					this->tabPage1->Name = "tabPage1";
					this->tabPage1->Padding = new System::Windows::Forms::Padding(3);
					this->tabPage1->Size = new System::Drawing::Size(425, 254);
					this->tabPage1->TabIndex = 0;
					this->tabPage1->Text = "Video";
					this->tabPage1->UseVisualStyleBackColor = true;
					// 
					// groupBox6
					// 
					this->groupBox6->Controls->Add(this->chkDontEncodeVideo);
					this->groupBox6->Controls->Add(this->usechaptersmarks);
					this->groupBox6->Controls->Add(this->videoProfile);
					this->groupBox6->Controls->Add(this->videoCodecLabel);
					this->groupBox6->Location = new System::Drawing::Point(6, 6);
					this->groupBox6->Name = "groupBox6";
					this->groupBox6->Size = new System::Drawing::Size(416, 87);
					this->groupBox6->TabIndex = 47;
					this->groupBox6->TabStop = false;
					this->groupBox6->Text = " Video Setup ";
					// 
					// chkDontEncodeVideo
					// 
					this->chkDontEncodeVideo->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right)));
					this->chkDontEncodeVideo->AutoSize = true;
					this->chkDontEncodeVideo->Location = new System::Drawing::Point(77, 22);
					this->chkDontEncodeVideo->Name = "chkDontEncodeVideo";
					this->chkDontEncodeVideo->Size = new System::Drawing::Size(119, 17);
					this->chkDontEncodeVideo->TabIndex = 42;
					this->chkDontEncodeVideo->Text = "Don\'t encode video";
					// 
					// usechaptersmarks
					// 
					this->usechaptersmarks->AutoSize = true;
					this->usechaptersmarks->Location = new System::Drawing::Point(202, 22);
					this->usechaptersmarks->Name = "usechaptersmarks";
					this->usechaptersmarks->Size = new System::Drawing::Size(197, 17);
					this->usechaptersmarks->TabIndex = 41;
					this->usechaptersmarks->Text = "Force key frames for chapters marks";
					this->usechaptersmarks->UseVisualStyleBackColor = true;
					// 
					// videoCodecLabel
					// 
					this->videoCodecLabel->Location = new System::Drawing::Point(6, 51);
					this->videoCodecLabel->Name = "videoCodecLabel";
					this->videoCodecLabel->Size = new System::Drawing::Size(90, 13);
					this->videoCodecLabel->TabIndex = 18;
					this->videoCodecLabel->Text = "Encoder";
					// 
					// tabPage3
					// 
					this->tabPage3->Controls->Add(this->extraGroupbox);
					this->tabPage3->Location = new System::Drawing::Point(4, 22);
					this->tabPage3->Name = "tabPage3";
					this->tabPage3->Padding = new System::Windows::Forms::Padding(3);
					this->tabPage3->Size = new System::Drawing::Size(425, 254);
					this->tabPage3->TabIndex = 2;
					this->tabPage3->Text = "Audio";
					this->tabPage3->UseVisualStyleBackColor = true;
					// 
					// extraGroupbox
					// 
					this->extraGroupbox->Controls->Add(this->audioTab);
					this->extraGroupbox->Location = new System::Drawing::Point(3, 6);
					this->extraGroupbox->Name = "extraGroupbox";
					this->extraGroupbox->Size = new System::Drawing::Size(419, 242);
					this->extraGroupbox->TabIndex = 40;
					this->extraGroupbox->TabStop = false;
					this->extraGroupbox->Text = " Audio Setup ";
					// 
					// audioTab
					// 
					this->audioTab->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
					this->audioTab->Controls->Add(this->audioPage0);
					this->audioTab->Controls->Add(this->audioPageAdd);
					this->audioTab->Location = new System::Drawing::Point(6, 30);
					this->audioTab->Name = "audioTab";
					this->audioTab->SelectedIndex = 0;
					this->audioTab->Size = new System::Drawing::Size(407, 150);
					this->audioTab->TabIndex = 44;
					this->audioTab->SelectedIndexChanged += new System::EventHandler(this, &OneClickConfigPanel::audioTab_SelectedIndexChanged);
					this->audioTab->VisibleChanged += new System::EventHandler(this, &OneClickConfigPanel::audioTab_VisibleChanged);
					this->audioTab->KeyUp += new System::Windows::Forms::KeyEventHandler(this, &OneClickConfigPanel::audioTab_KeyUp);
					this->audioTab->MouseClick += new System::Windows::Forms::MouseEventHandler(this, &OneClickConfigPanel::audioTab_MouseClick);
					this->audioTab->MouseDoubleClick += new System::Windows::Forms::MouseEventHandler(this, &OneClickConfigPanel::audioTab_MouseDoubleClick);
					// 
					// audioPage0
					// 
					this->audioPage0->Controls->Add(this->oneClickAudioControl1);
					this->audioPage0->Location = new System::Drawing::Point(4, 22);
					this->audioPage0->Name = "audioPage0";
					this->audioPage0->Size = new System::Drawing::Size(399, 124);
					this->audioPage0->TabIndex = 2;
					this->audioPage0->Text = "Default";
					this->audioPage0->UseVisualStyleBackColor = true;
					// 
					// audioPageAdd
					// 
					this->audioPageAdd->Location = new System::Drawing::Point(4, 22);
					this->audioPageAdd->Name = "audioPageAdd";
					this->audioPageAdd->Size = new System::Drawing::Size(399, 124);
					this->audioPageAdd->TabIndex = 3;
					this->audioPageAdd->Text = "   +";
					this->audioPageAdd->UseVisualStyleBackColor = true;
					// 
					// tabPage2
					// 
					this->tabPage2->Controls->Add(this->groupBox8);
					this->tabPage2->Controls->Add(this->groupBox7);
					this->tabPage2->Location = new System::Drawing::Point(4, 22);
					this->tabPage2->Name = "tabPage2";
					this->tabPage2->Padding = new System::Windows::Forms::Padding(3);
					this->tabPage2->Size = new System::Drawing::Size(425, 254);
					this->tabPage2->TabIndex = 1;
					this->tabPage2->Text = "Output";
					this->tabPage2->UseVisualStyleBackColor = true;
					// 
					// groupBox8
					// 
					this->groupBox8->Controls->Add(this->splitSize);
					this->groupBox8->Controls->Add(this->fileSize);
					this->groupBox8->Controls->Add(this->label2);
					this->groupBox8->Controls->Add(this->filesizeLabel);
					this->groupBox8->Location = new System::Drawing::Point(3, 148);
					this->groupBox8->Name = "groupBox8";
					this->groupBox8->Size = new System::Drawing::Size(416, 100);
					this->groupBox8->TabIndex = 19;
					this->groupBox8->TabStop = false;
					this->groupBox8->Text = " File ";
					// 
					// label2
					// 
					this->label2->Location = new System::Drawing::Point(8, 57);
					this->label2->Name = "label2";
					this->label2->Size = new System::Drawing::Size(90, 13);
					this->label2->TabIndex = 39;
					this->label2->Text = "Splitting";
					// 
					// filesizeLabel
					// 
					this->filesizeLabel->Location = new System::Drawing::Point(8, 31);
					this->filesizeLabel->Name = "filesizeLabel";
					this->filesizeLabel->Size = new System::Drawing::Size(90, 13);
					this->filesizeLabel->TabIndex = 40;
					this->filesizeLabel->Text = "Filesize";
					// 
					// groupBox7
					// 
					this->groupBox7->Controls->Add(this->containerTypeList);
					this->groupBox7->Controls->Add(this->containerFormatLabel);
					this->groupBox7->Location = new System::Drawing::Point(3, 7);
					this->groupBox7->Name = "groupBox7";
					this->groupBox7->Size = new System::Drawing::Size(419, 135);
					this->groupBox7->TabIndex = 18;
					this->groupBox7->TabStop = false;
					this->groupBox7->Text = " Container ";
					// 
					// containerTypeList
					// 
					this->containerTypeList->CheckOnClick = true;
					this->containerTypeList->Location = new System::Drawing::Point(6, 16);
					this->containerTypeList->Name = "containerTypeList";
					this->containerTypeList->Size = new System::Drawing::Size(171, 109);
					this->containerTypeList->TabIndex = 21;
					// 
					// containerFormatLabel
					// 
					this->containerFormatLabel->Location = new System::Drawing::Point(183, 16);
					this->containerFormatLabel->Name = "containerFormatLabel";
					this->containerFormatLabel->Size = new System::Drawing::Size(223, 109);
					this->containerFormatLabel->TabIndex = 18;
					this->containerFormatLabel->Text = "Text change later for resource behavior reasons";
					// 
					// tabPage4
					// 
					this->tabPage4->Controls->Add(this->cbUnknownLanguage);
					this->tabPage4->Controls->Add(this->label4);
					this->tabPage4->Controls->Add(this->cbLanguageSelect);
					this->tabPage4->Controls->Add(this->label7);
					this->tabPage4->Controls->Add(this->groupBox2);
					this->tabPage4->Controls->Add(this->groupBox1);
					this->tabPage4->Location = new System::Drawing::Point(4, 22);
					this->tabPage4->Name = "tabPage4";
					this->tabPage4->Padding = new System::Windows::Forms::Padding(3);
					this->tabPage4->Size = new System::Drawing::Size(425, 254);
					this->tabPage4->TabIndex = 3;
					this->tabPage4->Text = "Language";
					this->tabPage4->UseVisualStyleBackColor = true;
					// 
					// cbLanguageSelect
					// 
					this->cbLanguageSelect->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
					this->cbLanguageSelect->FormattingEnabled = true;
					this->cbLanguageSelect->Items->AddRange(new object[2] {"all", "none"});
					this->cbLanguageSelect->Location = new System::Drawing::Point(268, 227);
					this->cbLanguageSelect->Name = "cbLanguageSelect";
					this->cbLanguageSelect->Size = new System::Drawing::Size(130, 21);
					this->cbLanguageSelect->TabIndex = 47;
					// 
					// label7
					// 
					this->label7->AutoSize = true;
					this->label7->Location = new System::Drawing::Point(16, 230);
					this->label7->Name = "label7";
					this->label7->Size = new System::Drawing::Size(238, 13);
					this->label7->TabIndex = 46;
					this->label7->Text = "Languages to select if selection does not match: ";
					// 
					// groupBox2
					// 
					this->groupBox2->Controls->Add(this->btnSubtitleDown);
					this->groupBox2->Controls->Add(this->btnSubtitleUp);
					this->groupBox2->Controls->Add(this->btnRemoveSubtitle);
					this->groupBox2->Controls->Add(this->btnAddSubtitle);
					this->groupBox2->Controls->Add(this->lbNonDefaultSubtitle);
					this->groupBox2->Controls->Add(this->lbDefaultSubtitle);
					this->groupBox2->Location = new System::Drawing::Point(6, 101);
					this->groupBox2->Name = "groupBox2";
					this->groupBox2->Size = new System::Drawing::Size(413, 93);
					this->groupBox2->TabIndex = 2;
					this->groupBox2->TabStop = false;
					this->groupBox2->Text = " Default Subtitle Language ";
					// 
					// btnSubtitleDown
					// 
					this->btnSubtitleDown->Location = new System::Drawing::Point(151, 68);
					this->btnSubtitleDown->Name = "btnSubtitleDown";
					this->btnSubtitleDown->Size = new System::Drawing::Size(29, 20);
					this->btnSubtitleDown->TabIndex = 6;
					this->btnSubtitleDown->Text = "-";
					this->btnSubtitleDown->UseVisualStyleBackColor = true;
					this->btnSubtitleDown->Click += new System::EventHandler(this, &OneClickConfigPanel::btnSubtitleDown_Click);
					// 
					// btnSubtitleUp
					// 
					this->btnSubtitleUp->Location = new System::Drawing::Point(151, 18);
					this->btnSubtitleUp->Name = "btnSubtitleUp";
					this->btnSubtitleUp->Size = new System::Drawing::Size(29, 20);
					this->btnSubtitleUp->TabIndex = 5;
					this->btnSubtitleUp->Text = "+";
					this->btnSubtitleUp->UseVisualStyleBackColor = true;
					this->btnSubtitleUp->Click += new System::EventHandler(this, &OneClickConfigPanel::btnSubtitleUp_Click);
					// 
					// btnRemoveSubtitle
					// 
					this->btnRemoveSubtitle->Location = new System::Drawing::Point(151, 43);
					this->btnRemoveSubtitle->Name = "btnRemoveSubtitle";
					this->btnRemoveSubtitle->Size = new System::Drawing::Size(29, 20);
					this->btnRemoveSubtitle->TabIndex = 4;
					this->btnRemoveSubtitle->Text = ">>";
					this->btnRemoveSubtitle->UseVisualStyleBackColor = true;
					this->btnRemoveSubtitle->Click += new System::EventHandler(this, &OneClickConfigPanel::btnRemoveSubtitle_Click);
					// 
					// btnAddSubtitle
					// 
					this->btnAddSubtitle->Location = new System::Drawing::Point(227, 43);
					this->btnAddSubtitle->Name = "btnAddSubtitle";
					this->btnAddSubtitle->Size = new System::Drawing::Size(29, 20);
					this->btnAddSubtitle->TabIndex = 3;
					this->btnAddSubtitle->Text = "<<";
					this->btnAddSubtitle->UseVisualStyleBackColor = true;
					this->btnAddSubtitle->Click += new System::EventHandler(this, &OneClickConfigPanel::btnAddSubtitle_Click);
					// 
					// lbNonDefaultSubtitle
					// 
					this->lbNonDefaultSubtitle->FormattingEnabled = true;
					this->lbNonDefaultSubtitle->Location = new System::Drawing::Point(262, 18);
					this->lbNonDefaultSubtitle->Name = "lbNonDefaultSubtitle";
					this->lbNonDefaultSubtitle->Size = new System::Drawing::Size(130, 69);
					this->lbNonDefaultSubtitle->Sorted = true;
					this->lbNonDefaultSubtitle->TabIndex = 2;
					this->lbNonDefaultSubtitle->SelectedIndexChanged += new System::EventHandler(this, &OneClickConfigPanel::lbNonDefaultSubtitle_SelectedIndexChanged);
					// 
					// lbDefaultSubtitle
					// 
					this->lbDefaultSubtitle->FormattingEnabled = true;
					this->lbDefaultSubtitle->Location = new System::Drawing::Point(15, 18);
					this->lbDefaultSubtitle->Name = "lbDefaultSubtitle";
					this->lbDefaultSubtitle->Size = new System::Drawing::Size(130, 69);
					this->lbDefaultSubtitle->TabIndex = 1;
					this->lbDefaultSubtitle->SelectedIndexChanged += new System::EventHandler(this, &OneClickConfigPanel::lbDefaultSubtitle_SelectedIndexChanged);
					// 
					// groupBox1
					// 
					this->groupBox1->Controls->Add(this->btnAudioDown);
					this->groupBox1->Controls->Add(this->btnAudioUp);
					this->groupBox1->Controls->Add(this->btnRemoveAudio);
					this->groupBox1->Controls->Add(this->btnAddAudio);
					this->groupBox1->Controls->Add(this->lbNonDefaultAudio);
					this->groupBox1->Controls->Add(this->lbDefaultAudio);
					this->groupBox1->Location = new System::Drawing::Point(6, 6);
					this->groupBox1->Name = "groupBox1";
					this->groupBox1->Size = new System::Drawing::Size(413, 93);
					this->groupBox1->TabIndex = 1;
					this->groupBox1->TabStop = false;
					this->groupBox1->Text = "Default Audio Language";
					// 
					// btnAudioDown
					// 
					this->btnAudioDown->Location = new System::Drawing::Point(151, 68);
					this->btnAudioDown->Name = "btnAudioDown";
					this->btnAudioDown->Size = new System::Drawing::Size(29, 20);
					this->btnAudioDown->TabIndex = 6;
					this->btnAudioDown->Text = "-";
					this->btnAudioDown->UseVisualStyleBackColor = true;
					this->btnAudioDown->Click += new System::EventHandler(this, &OneClickConfigPanel::btnAudioDown_Click);
					// 
					// btnAudioUp
					// 
					this->btnAudioUp->Location = new System::Drawing::Point(151, 18);
					this->btnAudioUp->Name = "btnAudioUp";
					this->btnAudioUp->Size = new System::Drawing::Size(29, 20);
					this->btnAudioUp->TabIndex = 5;
					this->btnAudioUp->Text = "+";
					this->btnAudioUp->UseVisualStyleBackColor = true;
					this->btnAudioUp->Click += new System::EventHandler(this, &OneClickConfigPanel::btnAudioUp_Click);
					// 
					// btnRemoveAudio
					// 
					this->btnRemoveAudio->Location = new System::Drawing::Point(151, 43);
					this->btnRemoveAudio->Name = "btnRemoveAudio";
					this->btnRemoveAudio->Size = new System::Drawing::Size(29, 20);
					this->btnRemoveAudio->TabIndex = 4;
					this->btnRemoveAudio->Text = ">>";
					this->btnRemoveAudio->UseVisualStyleBackColor = true;
					this->btnRemoveAudio->Click += new System::EventHandler(this, &OneClickConfigPanel::btnRemoveAudio_Click);
					// 
					// btnAddAudio
					// 
					this->btnAddAudio->Location = new System::Drawing::Point(227, 43);
					this->btnAddAudio->Name = "btnAddAudio";
					this->btnAddAudio->Size = new System::Drawing::Size(29, 20);
					this->btnAddAudio->TabIndex = 3;
					this->btnAddAudio->Text = "<<";
					this->btnAddAudio->UseVisualStyleBackColor = true;
					this->btnAddAudio->Click += new System::EventHandler(this, &OneClickConfigPanel::btnAddAudio_Click);
					// 
					// lbNonDefaultAudio
					// 
					this->lbNonDefaultAudio->FormattingEnabled = true;
					this->lbNonDefaultAudio->Location = new System::Drawing::Point(262, 18);
					this->lbNonDefaultAudio->Name = "lbNonDefaultAudio";
					this->lbNonDefaultAudio->Size = new System::Drawing::Size(130, 69);
					this->lbNonDefaultAudio->Sorted = true;
					this->lbNonDefaultAudio->TabIndex = 2;
					this->lbNonDefaultAudio->SelectedIndexChanged += new System::EventHandler(this, &OneClickConfigPanel::lbNonDefaultAudio_SelectedIndexChanged);
					// 
					// lbDefaultAudio
					// 
					this->lbDefaultAudio->FormattingEnabled = true;
					this->lbDefaultAudio->Location = new System::Drawing::Point(15, 19);
					this->lbDefaultAudio->Name = "lbDefaultAudio";
					this->lbDefaultAudio->Size = new System::Drawing::Size(130, 69);
					this->lbDefaultAudio->TabIndex = 1;
					this->lbDefaultAudio->SelectedIndexChanged += new System::EventHandler(this, &OneClickConfigPanel::lbDefaultAudio_SelectedIndexChanged);
					// 
					// tabPage5
					// 
					this->tabPage5->Controls->Add(this->chkDisableIntermediateMKV);
					this->tabPage5->Controls->Add(this->groupBox5);
					this->tabPage5->Controls->Add(this->groupBox4);
					this->tabPage5->Controls->Add(this->groupBox3);
					this->tabPage5->Location = new System::Drawing::Point(4, 22);
					this->tabPage5->Name = "tabPage5";
					this->tabPage5->Padding = new System::Windows::Forms::Padding(3);
					this->tabPage5->Size = new System::Drawing::Size(425, 254);
					this->tabPage5->TabIndex = 4;
					this->tabPage5->Text = "Other";
					this->tabPage5->UseVisualStyleBackColor = true;
					// 
					// chkDisableIntermediateMKV
					// 
					this->chkDisableIntermediateMKV->AutoSize = true;
					this->chkDisableIntermediateMKV->Location = new System::Drawing::Point(15, 221);
					this->chkDisableIntermediateMKV->Name = "chkDisableIntermediateMKV";
					this->chkDisableIntermediateMKV->Size = new System::Drawing::Size(161, 17);
					this->chkDisableIntermediateMKV->TabIndex = 45;
					this->chkDisableIntermediateMKV->Text = "disable intermediate MKV file";
					this->chkDisableIntermediateMKV->UseVisualStyleBackColor = true;
					// 
					// groupBox5
					// 
					this->groupBox5->Controls->Add(this->deleteWorking);
					this->groupBox5->Controls->Add(this->deleteOutput);
					this->groupBox5->Controls->Add(this->outputDirectory);
					this->groupBox5->Controls->Add(this->label8);
					this->groupBox5->Controls->Add(this->workingDirectory);
					this->groupBox5->Controls->Add(this->workingDirectoryLabel);
					this->groupBox5->Location = new System::Drawing::Point(6, 6);
					this->groupBox5->Name = "groupBox5";
					this->groupBox5->Size = new System::Drawing::Size(413, 84);
					this->groupBox5->TabIndex = 44;
					this->groupBox5->TabStop = false;
					this->groupBox5->Text = " Default Directories ";
					// 
					// deleteWorking
					// 
					this->deleteWorking->Location = new System::Drawing::Point(370, 52);
					this->deleteWorking->Name = "deleteWorking";
					this->deleteWorking->Size = new System::Drawing::Size(28, 23);
					this->deleteWorking->TabIndex = 46;
					this->deleteWorking->Text = "X";
					this->deleteWorking->UseVisualStyleBackColor = true;
					this->deleteWorking->Click += new System::EventHandler(this, &OneClickConfigPanel::deleteWorking_Click);
					// 
					// deleteOutput
					// 
					this->deleteOutput->Location = new System::Drawing::Point(370, 20);
					this->deleteOutput->Name = "deleteOutput";
					this->deleteOutput->Size = new System::Drawing::Size(28, 23);
					this->deleteOutput->TabIndex = 45;
					this->deleteOutput->Text = "X";
					this->deleteOutput->UseVisualStyleBackColor = true;
					this->deleteOutput->Click += new System::EventHandler(this, &OneClickConfigPanel::deleteOutput_Click);
					// 
					// label8
					// 
					this->label8->Location = new System::Drawing::Point(6, 25);
					this->label8->Name = "label8";
					this->label8->Size = new System::Drawing::Size(108, 13);
					this->label8->TabIndex = 44;
					this->label8->Text = "Output";
					// 
					// workingDirectoryLabel
					// 
					this->workingDirectoryLabel->Location = new System::Drawing::Point(6, 56);
					this->workingDirectoryLabel->Name = "workingDirectoryLabel";
					this->workingDirectoryLabel->Size = new System::Drawing::Size(108, 13);
					this->workingDirectoryLabel->TabIndex = 41;
					this->workingDirectoryLabel->Text = "Working";
					// 
					// groupBox4
					// 
					this->groupBox4->Controls->Add(this->label1);
					this->groupBox4->Controls->Add(this->txtLeadingName);
					this->groupBox4->Controls->Add(this->label6);
					this->groupBox4->Controls->Add(this->label5);
					this->groupBox4->Controls->Add(this->txtWorkingNameReplaceWith);
					this->groupBox4->Controls->Add(this->txtWorkingNameDelete);
					this->groupBox4->Location = new System::Drawing::Point(212, 96);
					this->groupBox4->Name = "groupBox4";
					this->groupBox4->Size = new System::Drawing::Size(207, 111);
					this->groupBox4->TabIndex = 43;
					this->groupBox4->TabStop = false;
					this->groupBox4->Text = " Project Name ";
					// 
					// label1
					// 
					this->label1->AutoSize = true;
					this->label1->Location = new System::Drawing::Point(7, 31);
					this->label1->Name = "label1";
					this->label1->Size = new System::Drawing::Size(45, 13);
					this->label1->TabIndex = 5;
					this->label1->Text = "Leading";
					// 
					// txtLeadingName
					// 
					this->txtLeadingName->Location = new System::Drawing::Point(60, 28);
					this->txtLeadingName->Name = "txtLeadingName";
					this->txtLeadingName->Size = new System::Drawing::Size(121, 20);
					this->txtLeadingName->TabIndex = 4;
					// 
					// label6
					// 
					this->label6->AutoSize = true;
					this->label6->Location = new System::Drawing::Point(7, 83);
					this->label6->Name = "label6";
					this->label6->Size = new System::Drawing::Size(29, 13);
					this->label6->TabIndex = 3;
					this->label6->Text = "With";
					// 
					// label5
					// 
					this->label5->AutoSize = true;
					this->label5->Location = new System::Drawing::Point(7, 57);
					this->label5->Name = "label5";
					this->label5->Size = new System::Drawing::Size(47, 13);
					this->label5->TabIndex = 2;
					this->label5->Text = "Replace";
					// 
					// txtWorkingNameReplaceWith
					// 
					this->txtWorkingNameReplaceWith->Location = new System::Drawing::Point(60, 80);
					this->txtWorkingNameReplaceWith->Name = "txtWorkingNameReplaceWith";
					this->txtWorkingNameReplaceWith->Size = new System::Drawing::Size(121, 20);
					this->txtWorkingNameReplaceWith->TabIndex = 1;
					// 
					// txtWorkingNameDelete
					// 
					this->txtWorkingNameDelete->Location = new System::Drawing::Point(60, 54);
					this->txtWorkingNameDelete->Name = "txtWorkingNameDelete";
					this->txtWorkingNameDelete->Size = new System::Drawing::Size(121, 20);
					this->txtWorkingNameDelete->TabIndex = 0;
					// 
					// groupBox3
					// 
					this->groupBox3->Controls->Add(this->btnIndexerDown);
					this->groupBox3->Controls->Add(this->btnIndexerUp);
					this->groupBox3->Controls->Add(this->lbIndexerPriority);
					this->groupBox3->Location = new System::Drawing::Point(6, 96);
					this->groupBox3->Name = "groupBox3";
					this->groupBox3->Size = new System::Drawing::Size(200, 111);
					this->groupBox3->TabIndex = 42;
					this->groupBox3->TabStop = false;
					this->groupBox3->Text = " Indexer / Opener Priority ";
					// 
					// btnIndexerDown
					// 
					this->btnIndexerDown->Enabled = false;
					this->btnIndexerDown->Location = new System::Drawing::Point(145, 64);
					this->btnIndexerDown->Name = "btnIndexerDown";
					this->btnIndexerDown->Size = new System::Drawing::Size(29, 23);
					this->btnIndexerDown->TabIndex = 44;
					this->btnIndexerDown->Text = "-";
					this->btnIndexerDown->UseVisualStyleBackColor = true;
					this->btnIndexerDown->Click += new System::EventHandler(this, &OneClickConfigPanel::btnIndexerDown_Click);
					// 
					// btnIndexerUp
					// 
					this->btnIndexerUp->Enabled = false;
					this->btnIndexerUp->Location = new System::Drawing::Point(145, 33);
					this->btnIndexerUp->Name = "btnIndexerUp";
					this->btnIndexerUp->Size = new System::Drawing::Size(29, 23);
					this->btnIndexerUp->TabIndex = 43;
					this->btnIndexerUp->Text = "+";
					this->btnIndexerUp->UseVisualStyleBackColor = true;
					this->btnIndexerUp->Click += new System::EventHandler(this, &OneClickConfigPanel::btnIndexerUp_Click);
					// 
					// lbIndexerPriority
					// 
					this->lbIndexerPriority->FormattingEnabled = true;
					this->lbIndexerPriority->Location = new System::Drawing::Point(33, 18);
					this->lbIndexerPriority->Name = "lbIndexerPriority";
					this->lbIndexerPriority->Size = new System::Drawing::Size(106, 82);
					this->lbIndexerPriority->TabIndex = 42;
					this->lbIndexerPriority->MouseClick += new System::Windows::Forms::MouseEventHandler(this, &OneClickConfigPanel::lbIndexerPriority_MouseClick);
					// 
					// audioMenu
					// 
					this->audioMenu->Items->AddRange(new System::Windows::Forms::ToolStripItem[2] {this->audioAddTrack, this->audioRemoveTrack});
					this->audioMenu->Name = "audioMenu";
					this->audioMenu->Size = new System::Drawing::Size(150, 48);
					this->audioMenu->Opening += new System::ComponentModel::CancelEventHandler(this, &OneClickConfigPanel::audioMenu_Opening);
					// 
					// audioAddTrack
					// 
					this->audioAddTrack->Name = "audioAddTrack";
					this->audioAddTrack->Size = new System::Drawing::Size(149, 22);
					this->audioAddTrack->Text = "Add Track";
					this->audioAddTrack->Click += new System::EventHandler(this, &OneClickConfigPanel::audioAddTrack_Click);
					// 
					// audioRemoveTrack
					// 
					this->audioRemoveTrack->Name = "audioRemoveTrack";
					this->audioRemoveTrack->Size = new System::Drawing::Size(149, 22);
					this->audioRemoveTrack->Text = "Remove Track";
					this->audioRemoveTrack->Click += new System::EventHandler(this, &OneClickConfigPanel::audioRemoveTrack_Click);
					// 
					// label4
					// 
					this->label4->AutoSize = true;
					this->label4->Location = new System::Drawing::Point(16, 204);
					this->label4->Name = "label4";
					this->label4->Size = new System::Drawing::Size(212, 13);
					this->label4->TabIndex = 48;
					this->label4->Text = "Language to set if it cannot be determined: ";
					// 
					// cbUnknownLanguage
					// 
					this->cbUnknownLanguage->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
					this->cbUnknownLanguage->FormattingEnabled = true;
					this->cbUnknownLanguage->Location = new System::Drawing::Point(268, 201);
					this->cbUnknownLanguage->Name = "cbUnknownLanguage";
					this->cbUnknownLanguage->Size = new System::Drawing::Size(130, 21);
					this->cbUnknownLanguage->TabIndex = 49;
					// 
					// avsProfile
					// 
					this->avsProfile->Location = new System::Drawing::Point(109, 90);
					this->avsProfile->Name = "avsProfile";
					this->avsProfile->setProfileSet("AviSynth");
					this->avsProfile->Size = new System::Drawing::Size(298, 22);
					this->avsProfile->TabIndex = 39;
					// 
					// videoProfile
					// 
					this->videoProfile->Location = new System::Drawing::Point(77, 47);
					this->videoProfile->Name = "videoProfile";
					this->videoProfile->setProfileSet("Video");
					this->videoProfile->Size = new System::Drawing::Size(330, 22);
					this->videoProfile->TabIndex = 40;
					// 
					// oneClickAudioControl1
					// 
					this->oneClickAudioControl1->Location = new System::Drawing::Point(6, 9);
					this->oneClickAudioControl1->Name = "oneClickAudioControl1";
					this->oneClickAudioControl1->Size = new System::Drawing::Size(386, 114);
					this->oneClickAudioControl1->TabIndex = 0;
					// 
					// splitSize
					// 
					this->splitSize->setCustomSizes(new MeXgui::core::util::FileSize[0]);
					this->splitSize->Location = new System::Drawing::Point(69, 49);
					this->splitSize->MaximumSize = new System::Drawing::Size(1000, 29);
					this->splitSize->MinimumSize = new System::Drawing::Size(64, 29);
					this->splitSize->Name = "splitSize";
					this->splitSize->setNullString("Dont split");
					this->splitSize->setSaveCustomValues(false);
					this->splitSize->setSelectedIndex(0);
					this->splitSize->Size = new System::Drawing::Size(340, 29);
					this->splitSize->TabIndex = 41;
					// 
					// fileSize
					// 
					this->fileSize->setCustomSizes(new MeXgui::core::util::FileSize[0]);
					this->fileSize->Location = new System::Drawing::Point(69, 23);
					this->fileSize->MaximumSize = new System::Drawing::Size(1000, 29);
					this->fileSize->MinimumSize = new System::Drawing::Size(64, 29);
					this->fileSize->Name = "fileSize";
					this->fileSize->setNullString("Don\'t care");
					this->fileSize->setSaveCustomValues(false);
					this->fileSize->setSelectedIndex(0);
					this->fileSize->Size = new System::Drawing::Size(340, 29);
					this->fileSize->TabIndex = 42;
					// 
					// outputDirectory
					// 
					this->outputDirectory->setFilename("");
					this->outputDirectory->setFilter("");
					this->outputDirectory->setFilterIndex(0);
					this->outputDirectory->setFolderMode(true);
					this->outputDirectory->Location = new System::Drawing::Point(64, 19);
					this->outputDirectory->Name = "outputDirectory";
					this->outputDirectory->setReadOnly(true);
					this->outputDirectory->setSaveMode(false);
					this->outputDirectory->Size = new System::Drawing::Size(300, 26);
					this->outputDirectory->TabIndex = 43;
					this->outputDirectory->setTitle("");
					// 
					// workingDirectory
					// 
					this->workingDirectory->setFilename("");
					this->workingDirectory->setFilter("");
					this->workingDirectory->setFilterIndex(0);
					this->workingDirectory->setFolderMode(true);
					this->workingDirectory->Location = new System::Drawing::Point(64, 51);
					this->workingDirectory->Name = "workingDirectory";
					this->workingDirectory->setReadOnly(true);
					this->workingDirectory->setSaveMode(false);
					this->workingDirectory->Size = new System::Drawing::Size(300, 26);
					this->workingDirectory->TabIndex = 42;
					this->workingDirectory->setTitle("");
					// 
					// OneClickConfigPanel
					// 
					this->AutoScaleDimensions = new System::Drawing::SizeF(6, 13);
					this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
					this->Controls->Add(this->tabControl1);
					this->Name = "OneClickConfigPanel";
					this->Size = new System::Drawing::Size(433, 280);
					this->otherGroupBox->ResumeLayout(false);
					this->otherGroupBox->PerformLayout();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->horizontalResolution))->EndInit();
					this->tabControl1->ResumeLayout(false);
					this->tabPage1->ResumeLayout(false);
					this->groupBox6->ResumeLayout(false);
					this->groupBox6->PerformLayout();
					this->tabPage3->ResumeLayout(false);
					this->extraGroupbox->ResumeLayout(false);
					this->audioTab->ResumeLayout(false);
					this->audioPage0->ResumeLayout(false);
					this->tabPage2->ResumeLayout(false);
					this->groupBox8->ResumeLayout(false);
					this->groupBox7->ResumeLayout(false);
					this->tabPage4->ResumeLayout(false);
					this->tabPage4->PerformLayout();
					this->groupBox2->ResumeLayout(false);
					this->groupBox1->ResumeLayout(false);
					this->tabPage5->ResumeLayout(false);
					this->tabPage5->PerformLayout();
					this->groupBox5->ResumeLayout(false);
					this->groupBox4->ResumeLayout(false);
					this->groupBox4->PerformLayout();
					this->groupBox3->ResumeLayout(false);
					this->audioMenu->ResumeLayout(false);
					this->ResumeLayout(false);

				}

				void OneClickConfigPanel::InitializeInstanceFields()
				{
					iSelectedAudioTabPage = -1;
					delete components;
				}
			}
		}
	}
}
