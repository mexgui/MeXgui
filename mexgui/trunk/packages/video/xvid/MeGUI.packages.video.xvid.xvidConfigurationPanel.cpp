#include "MeGUI.packages.video.xvid.xvidConfigurationPanel.h"

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
using namespace MeGUI::core::plugins::interfaces;
namespace MeGUI
{
	namespace packages
	{
		namespace video
		{
			namespace xvid
			{

				xvidConfigurationPanel::xvidConfigurationPanel() : MeGUI::core::details::video::VideoConfigurationPanel()
				{
					InitializeInstanceFields();
					InitializeComponent();
					cqmComboBox1->setStandardItems(new std::string[] {xvidSettings::H263Matrix, xvidSettings::MPEGMatrix});
				}

				void xvidConfigurationPanel::doCheckBoxAdjustments()
				{
					if (static_cast<int>(xvidNbBFrames->Value) > 0)
					{
						xvidUseVHQForBframes->Enabled = true;
						xvidMinBQuant->Enabled = true;
						xvidMaxBQuant->Enabled = true;
						xvidBframeQuantRatio->Enabled = true;
						xvidBframeQuantOffset->Enabled = true;
						xvidBframeThreshold->Enabled = true;
						xvidFrameDropRatio->Enabled = true;
					}
					else // no b-frames
					{
						xvidUseVHQForBframes->Enabled = false;
						xvidUseVHQForBframes->Checked = false;
						xvidMinBQuant->Enabled = false;
						xvidMaxBQuant->Enabled = false;
						xvidBframeQuantRatio->Enabled = false;
						xvidBframeQuantOffset->Enabled = false;
						xvidBframeThreshold->Enabled = false;
						xvidFrameDropRatio->Enabled = false;
					}
				}

				bool xvidConfigurationPanel::isBitrateMode(int mode)
				{
					return !(mode == static_cast<int>(VideoCodecSettings::CQ) || mode == static_cast<int>(VideoCodecSettings::quality));
				}

				void xvidConfigurationPanel::doDropDownAdjustments()
				{
					logfileOpenButton->Enabled = false;
					if (isBitrateMode(xvidEncodingMode->SelectedIndex))
					{
						xvidBitrateQuantLabel->Text = "Bitrate";
						xvidBitrateQuantizer->Maximum = 10000;
						xvidBitrateQuantizer->Minimum = 1;
						xvidBitrateQuantizer->Increment = 1;
						xvidBitrateQuantizer->DecimalPlaces = 0;
					}
					else
					{
						xvidBitrateQuantLabel->Text = "Quantizer";
						xvidBitrateQuantizer->Maximum = 31;
						xvidBitrateQuantizer->Minimum = 1;
						xvidBitrateQuantizer->Increment = 0.1;
						xvidBitrateQuantizer->DecimalPlaces = 1;
					}
					switch (this->xvidEncodingMode->SelectedIndex)
					{
						case 0: // cbr
							xvidProfile->SelectedIndex = 0;
							xvidProfile->Enabled = false;
							xvidTurbo->Checked = false;
							xvidTurbo->Enabled = false;
							xvidRCGroupbox->Enabled = false;
							xvidCBRRcGroupBox->Enabled = true;
							break;
						case 1: // CQ
							xvidProfile->SelectedIndex = 0;
							xvidProfile->Enabled = false;
							xvidTurbo->Checked = false;
							xvidTurbo->Enabled = false;
							xvidRCGroupbox->Enabled = false;
							xvidCBRRcGroupBox->Enabled = true;
							break;
						case 2: // 2pass first pass
							xvidProfile->Enabled = true;
							xvidTurbo->Enabled = true;
							xvidRCGroupbox->Enabled = true;
							xvidCBRRcGroupBox->Enabled = false;
							logfileOpenButton->Enabled = true;
							break;
						case 3: // 2 pass 2nd pass
							xvidProfile->Enabled = true;
							xvidTurbo->Enabled = true;
							xvidRCGroupbox->Enabled = true;
							xvidCBRRcGroupBox->Enabled = false;
							logfileOpenButton->Enabled = true;
							break;
						case 4: // automated 2pass
							xvidProfile->Enabled = true;
							xvidTurbo->Enabled = true;
							xvidRCGroupbox->Enabled = true;
							xvidCBRRcGroupBox->Enabled = false;
							logfileOpenButton->Enabled = true;
							break;
					}
					switch (this->xvidProfile->SelectedIndex)
					{
						case 0: // Unrestricted
							this->xvidNbBFrames->Maximum = 4;
							this->xvidPackedBitstream->Enabled = true;
							this->cqmComboBox1->Enabled = true;
							this->xvidQpel->Enabled = true;
							this->xvidGMC->Enabled = true;
							this->xvidOverflowControlStrength->Minimum = 0;
							this->xvidMaxOverflowDegradation->Minimum = 0;
							this->xvidMaxOverflowImprovement->Minimum = 0;
							this->xvidInterlaced->Enabled = true;
							this->xvidVbvBuffer->Enabled = false;
							this->xvidVbvMaxRate->Enabled = false;
							this->xvidVbvPeakRate->Enabled = false;
							this->xvidVbvBuffer->Text = "0";
							this->xvidVbvMaxRate->Text = "0";
							this->xvidVbvPeakRate->Text = "0";
							break;
						case 1: // Home Theater
							this->xvidNbBFrames->Maximum = 1;
							this->xvidPackedBitstream->Checked = true;
							this->fourCC->SelectedIndex = 2;
							this->cqmComboBox1->setSelectedIndex(0);
							this->cqmComboBox1->Enabled = false;
							this->xvidQpel->Enabled = false;
							this->xvidQpel->Checked = false;
							this->xvidGMC->Enabled = false;
							this->xvidGMC->Checked = false;
							this->xvidOverflowControlStrength->Minimum = 10;
							this->xvidMaxOverflowDegradation->Minimum = 10;
							this->xvidMaxOverflowImprovement->Minimum = 10;
							this->xvidInterlaced->Enabled = true;
							this->xvidVbvBuffer->Enabled = false;
							this->xvidVbvMaxRate->Enabled = false;
							this->xvidVbvPeakRate->Enabled = false;
							this->xvidVbvBuffer->Text = "0";
							this->xvidVbvMaxRate->Text = "0";
							this->xvidVbvPeakRate->Text = "0";
							break;
						case 2: // Hi-Def 720p
							this->xvidNbBFrames->Maximum = 2;
							this->xvidPackedBitstream->Checked = false;
							this->fourCC->SelectedIndex = 2;
							this->cqmComboBox1->setSelectedIndex(0);
							this->cqmComboBox1->Enabled = false;
							this->xvidQpel->Enabled = false;
							this->xvidQpel->Checked = false;
							this->xvidGMC->Enabled = false;
							this->xvidGMC->Checked = false;
							this->xvidOverflowControlStrength->Minimum = 10;
							this->xvidMaxOverflowDegradation->Minimum = 10;
							this->xvidMaxOverflowImprovement->Minimum = 10;
							this->xvidInterlaced->Enabled = true;
							this->xvidVbvBuffer->Enabled = false;
							this->xvidVbvMaxRate->Enabled = false;
							this->xvidVbvPeakRate->Enabled = false;
							this->xvidVbvBuffer->Text = "0";
							this->xvidVbvMaxRate->Text = "0";
							this->xvidVbvPeakRate->Text = "0";
							break;
						case 3: // Hi-Def 1080p
							this->xvidNbBFrames->Maximum = 2;
							this->xvidPackedBitstream->Checked = false;
							this->fourCC->SelectedIndex = 2;
							this->cqmComboBox1->setSelectedIndex(0);
							this->cqmComboBox1->Enabled = false;
							this->xvidQpel->Enabled = false;
							this->xvidQpel->Checked = false;
							this->xvidGMC->Enabled = false;
							this->xvidGMC->Checked = false;
							this->xvidOverflowControlStrength->Minimum = 10;
							this->xvidMaxOverflowDegradation->Minimum = 10;
							this->xvidMaxOverflowImprovement->Minimum = 10;
							this->xvidInterlaced->Enabled = true;
							this->xvidVbvBuffer->Enabled = false;
							this->xvidVbvMaxRate->Enabled = false;
							this->xvidVbvPeakRate->Enabled = false;
							this->xvidVbvBuffer->Text = "0";
							this->xvidVbvMaxRate->Text = "0";
							this->xvidVbvPeakRate->Text = "0";
							break;
						case 4: // Handheld
							this->xvidNbBFrames->Maximum = 0;
							this->fourCC->SelectedIndex = 2;
							this->cqmComboBox1->setSelectedIndex(0);
							this->cqmComboBox1->Enabled = false;
							this->xvidQpel->Enabled = false;
							this->xvidQpel->Checked = false;
							this->xvidGMC->Enabled = false;
							this->xvidGMC->Checked = false;
							this->xvidOverflowControlStrength->Minimum = 10;
							this->xvidMaxOverflowDegradation->Minimum = 10;
							this->xvidMaxOverflowImprovement->Minimum = 10;
							this->xvidInterlaced->Checked = false;
							this->xvidInterlaced->Enabled = false;
							this->xvidVbvBuffer->Enabled = false;
							this->xvidVbvMaxRate->Enabled = false;
							this->xvidVbvPeakRate->Enabled = false;
							this->xvidVbvBuffer->Text = "0";
							this->xvidVbvMaxRate->Text = "0";
							this->xvidVbvPeakRate->Text = "0";
							break;
						case 5: // Portable
							this->xvidNbBFrames->Maximum = 0;
							this->fourCC->SelectedIndex = 2;
							this->cqmComboBox1->setSelectedIndex(0);
							this->cqmComboBox1->Enabled = false;
							this->xvidQpel->Enabled = false;
							this->xvidQpel->Checked = false;
							this->xvidGMC->Enabled = false;
							this->xvidGMC->Checked = false;
							this->xvidOverflowControlStrength->Minimum = 10;
							this->xvidMaxOverflowDegradation->Minimum = 10;
							this->xvidMaxOverflowImprovement->Minimum = 10;
							this->xvidInterlaced->Checked = false;
							this->xvidInterlaced->Enabled = false;
							this->xvidVbvBuffer->Enabled = false;
							this->xvidVbvMaxRate->Enabled = false;
							this->xvidVbvPeakRate->Enabled = false;
							this->xvidVbvBuffer->Text = "0";
							this->xvidVbvMaxRate->Text = "0";
							this->xvidVbvPeakRate->Text = "0";
							break;
						case 6: // Custom
							this->xvidOverflowControlStrength->Minimum = 10;
							this->xvidMaxOverflowDegradation->Minimum = 10;
							this->xvidMaxOverflowImprovement->Minimum = 10;
							this->xvidVbvBuffer->Enabled = true;
							this->xvidVbvMaxRate->Enabled = true;
							this->xvidVbvPeakRate->Enabled = true;
							break;
					}
					// We check whether the bitrate/quality text needs to be changed
					if (isBitrateMode(lastEncodingMode) != isBitrateMode(xvidEncodingMode->SelectedIndex))
					{
						if (isBitrateMode(xvidEncodingMode->SelectedIndex))
						{
							this->xvidBitrateQuantizer->Value = 700;
						}
						else
						{
							this->xvidBitrateQuantizer->Value = 8;
						}
					}

					lastEncodingMode = this->xvidEncodingMode->SelectedIndex;

					if (xvidVHQ->SelectedIndex == 0)
					{
						xvidUseVHQForBframes->Checked = false;
						xvidUseVHQForBframes->Enabled = false;
					}
					else
						xvidUseVHQForBframes->Enabled = true;
				}

				std::string xvidConfigurationPanel::getCommandline()
				{
					return XviDEncoder::genCommandline("input", "output", 0, dynamic_cast<xvidSettings*>(getSettings()), 1, 1, 0);
				}

				void xvidConfigurationPanel::doCodecSpecificAdjustments()
				{
					doDropDownAdjustments();
					doCheckBoxAdjustments();
				}

				void xvidConfigurationPanel::doCodecSpecificLoadAdjustments()
				{
					if (fourCC->SelectedIndex == -1)
						this->fourCC->SelectedIndex = 0;
					if (xvidEncodingMode->SelectedIndex == -1)
						this->xvidEncodingMode->SelectedIndex = 0; // cbr
					if (xvidMotionSearchPrecision->SelectedIndex == -1)
						this->xvidMotionSearchPrecision->SelectedIndex = 6;
					if (xvidVHQ->SelectedIndex == -1)
						this->xvidVHQ->SelectedIndex = 1;
					if (cqmComboBox1->getSelectedIndex() == -1)
						cqmComboBox1->setSelectedIndex(0);
					if (HVSMasking->SelectedIndex == -1)
						HVSMasking->SelectedIndex = 0;
				}

				bool xvidConfigurationPanel::isValidSettings(VideoCodecSettings *settings)
				{
					return dynamic_cast<xvidSettings*>(settings) != 0;
				}

				MeGUI::VideoCodecSettings *xvidConfigurationPanel::defaultSettings()
				{
					return new xvidSettings();
				}

				const MeGUI::xvidSettings &xvidConfigurationPanel::getSettings() const
				{
					xvidSettings *xs = new xvidSettings();
					xs->setFourCC(fourCC->SelectedIndex);
					xs->setTurbo(this->xvidTurbo->Checked);
					xs->setEncodingMode(this->xvidEncodingMode->SelectedIndex);
					xs->setQuantizer(xvidBitrateQuantizer->Value);
					xs->setBitrateQuantizer(static_cast<int>(xvidBitrateQuantizer->Value));

					if (!xvidKeyframeInterval->Text->Equals(""))
						xs->setKeyframeInterval(int::Parse(this->xvidKeyframeInterval->Text));
					xs->setNbBframes(static_cast<int>(xvidNbBFrames->Value));
					xs->setPackedBitstream(xvidPackedBitstream->Checked);
					xs->setXvidProfile(xvidProfile->SelectedIndex);
					xs->setVbvBuffer(int::Parse(xvidVbvBuffer->Text));
					xs->setVbvMaxRate(int::Parse(xvidVbvMaxRate->Text));
					xs->setVbvPeakRate(int::Parse(xvidVbvPeakRate->Text));
					xs->setMotionSearchPrecision(xvidMotionSearchPrecision->SelectedIndex);
					xs->setVHQMode(xvidVHQ->SelectedIndex);
					xs->setVHQForBframes(xvidUseVHQForBframes->Checked);
					xs->setQPel(xvidQpel->Checked);
					xs->setGMC(xvidGMC->Checked);
					xs->setNbThreads(static_cast<int>(nbThreads->Value));
					xs->setChromaMotion(xvidChromaMotion->Checked);
					xs->setClosedGOP(xvidClosedGop->Checked);
					xs->setInterlaced(xvidInterlaced->Checked);
					xs->setMinQuantizer(static_cast<int>(xvidMinIQuant->Value));
					xs->setMaxQuantizer(static_cast<int>(xvidMaxIQuant->Value));
					xs->setMinPQuant(static_cast<int>(xvidMinPQuant->Value));
					xs->setMaxPQuant(static_cast<int>(xvidMaxPQuant->Value));
					xs->setMinBQuant(static_cast<int>(xvidMinBQuant->Value));
					xs->setMaxBQuant(static_cast<int>(xvidMaxBQuant->Value));
					xs->setCreditsQuantizer(static_cast<int>(xvidCreditsQuantizer->Value));
					xs->setTrellis(xvidTrellisQuant->Checked);
					xs->setBQuantRatio(static_cast<int>(xvidBframeQuantRatio->Value));
					xs->setBQuantOffset(static_cast<int>(xvidBframeQuantOffset->Value));
					xs->setKeyFrameBoost(static_cast<int>(xvidIframeBoost->Value));
					if (!xvidKeyframeTreshold->Text->Equals(""))
						xs->setKeyframeThreshold(int::Parse(xvidKeyframeTreshold->Text));
					xs->setKeyframeReduction(static_cast<int>(xvidKeyframeReduction->Value));
					xs->setOverflowControlStrength(static_cast<int>(xvidOverflowControlStrength->Value));
					xs->setMaxOverflowImprovement(static_cast<int>(xvidMaxOverflowImprovement->Value));
					xs->setMaxOverflowDegradation(static_cast<int>(xvidMaxOverflowDegradation->Value));
					xs->setHighBitrateDegradation(static_cast<int>(xvidHighBitrateDegradation->Value));
					xs->setLowBitrateImprovement(static_cast<int>(xvidLowBitrateImprovement->Value));
					if (!xvidRCDelayFactor->Text->Equals(""))
						xs->setReactionDelayFactor(int::Parse(xvidRCDelayFactor->Text));
					if (!xvidRCAveragingPeriod->Text->Equals(""))
						xs->setAveragingPeriod(int::Parse(xvidRCAveragingPeriod->Text));
					if (!xvidRCBufferSize->Text->Equals("") && !xvidRCBufferSize->Text->Equals("0"))
						xs->setRateControlBuffer(int::Parse(xvidRCBufferSize->Text));
					xs->setBframeThreshold(this->xvidBframeThreshold->Value);
					xs->setFrameDropRatio(static_cast<int>(xvidFrameDropRatio->Value));
					xs->setQuantizerMatrix(cqmComboBox1->getSelectedText());
					xs->setCustomEncoderOptions(customCommandlineOptions->Text);
					xs->setLogfile(this->logfile->Text);
					xs->setHVSMasking(HVSMasking->SelectedIndex);
					return xs;
				}

				void xvidConfigurationPanel::setSettings(const xvidSettings &value)
				{
					xvidSettings *xs = value;
					fourCC->SelectedIndex = xs->getFourCC();
					this->xvidTurbo->Checked = xs->getTurbo();
					this->xvidEncodingMode->SelectedIndex = xs->getEncodingMode();
					lastEncodingMode = xvidEncodingMode->SelectedIndex;
					if (xs->getEncodingMode() == 1) // CQ
						xvidBitrateQuantizer->Value = xs->getQuantizer();
					else
						xvidBitrateQuantizer->Value = xs->getBitrateQuantizer();
					this->nbThreads->Value = xs->getNbThreads();
					this->xvidKeyframeInterval->Text = StringConverterHelper::toString(xs->getKeyframeInterval());
					;
					xvidNbBFrames->Value = xs->getNbBframes();
					xvidPackedBitstream->Checked = xs->getPackedBitstream();
					xvidProfile->SelectedIndex = xs->getXvidProfile();
					xvidVbvBuffer->Text = StringConverterHelper::toString(xs->getVbvBuffer());
					xvidVbvMaxRate->Text = StringConverterHelper::toString(xs->getVbvMaxRate());
					xvidVbvPeakRate->Text = StringConverterHelper::toString(xs->getVbvPeakRate());
					xvidMotionSearchPrecision->SelectedIndex = xs->getMotionSearchPrecision();
					xvidVHQ->SelectedIndex = xs->getVHQMode();
					xvidUseVHQForBframes->Checked = xs->getVHQForBframes();
					xvidQpel->Checked = xs->getQPel();
					xvidGMC->Checked = xs->getGMC();
					xvidChromaMotion->Checked = xs->getChromaMotion();
					xvidClosedGop->Checked = xs->getClosedGOP();
					xvidInterlaced->Checked = xs->getInterlaced();
					xvidMinIQuant->Value = xs->getMinQuantizer();
					xvidMaxIQuant->Value = xs->getMaxQuantizer();
					xvidMinPQuant->Value = xs->getMinPQuant();
					xvidMaxPQuant->Value = xs->getMaxPQuant();
					xvidMinBQuant->Value = xs->getMinBQuant();
					xvidMaxBQuant->Value = xs->getMaxBQuant();
					xvidCreditsQuantizer->Value = xs->getCreditsQuantizer();
					xvidTrellisQuant->Checked = xs->getTrellis();
					xvidBframeQuantRatio->Value = xs->getBQuantRatio();
					xvidBframeQuantOffset->Value = xs->getBQuantOffset();
					xvidIframeBoost->Value = xs->getKeyFrameBoost();
					xvidKeyframeTreshold->Text = StringConverterHelper::toString(xs->getKeyframeThreshold());
					xvidKeyframeReduction->Value = xs->getKeyframeReduction();
					xvidOverflowControlStrength->Value = xs->getOverflowControlStrength();
					xvidMaxOverflowImprovement->Value = xs->getMaxOverflowImprovement();
					xvidMaxOverflowDegradation->Value = xs->getMaxOverflowDegradation();
					xvidHighBitrateDegradation->Value = xs->getHighBitrateDegradation();
					xvidLowBitrateImprovement->Value = xs->getLowBitrateImprovement();
					xvidRCDelayFactor->Text = StringConverterHelper::toString(xs->getReactionDelayFactor());
					xvidRCAveragingPeriod->Text = StringConverterHelper::toString(xs->getAveragingPeriod());
					if (xs->getRateControlBuffer() > 0)
						xvidRCBufferSize->Text = StringConverterHelper::toString(xs->getRateControlBuffer());
					else
						xvidRCBufferSize->Text = "";
					this->xvidBframeThreshold->Value = xs->getBframeThreshold();
					xvidFrameDropRatio->Value = static_cast<decimal>(xs->getFrameDropRatio());
					cqmComboBox1->setSelectedObject(xs->getQuantizerMatrix());
					customCommandlineOptions->Text = xs->getCustomEncoderOptions();
					this->logfile->Text = xs->getLogfile();
					HVSMasking->SelectedIndex = xs->getHVSMasking();
				}

				void xvidConfigurationPanel::updateEvent(object *sender, EventArgs *e)
				{
					genericUpdate();
				}

				void xvidConfigurationPanel::textField_KeyPress(object *sender, KeyPressEventArgs *e)
				{
					if (!isdigit(e->KeyChar) && static_cast<int>(Keys::Back) != static_cast<int>(e->KeyChar))
						e->Handled = true;
				}

				void xvidConfigurationPanel::logfileOpenButton_Click(object *sender, System::EventArgs *e)
				{
					if (this->saveFileDialog->ShowDialog() == DialogResult::OK)
					{
						this->logfile->Text = saveFileDialog->FileName;
						this->showCommandLine();
					}
				}

				void xvidConfigurationPanel::cqmComboBox1_SelectionChanged(object *sender, const std::string &val)
				{
					genericUpdate();
				}

				void xvidConfigurationPanel::xvidProfile_SelectedIndexChanged(object *sender, EventArgs *e)
				{
					genericUpdate();
				}

				void xvidConfigurationPanel::xvidVbvBuffer_TextChanged(object *sender, EventArgs *e)
				{
					genericUpdate();
				}

				void xvidConfigurationPanel::xvidVbvMaxRate_TextChanged(object *sender, EventArgs *e)
				{
					genericUpdate();
				}

				void xvidConfigurationPanel::xvidVbvPeakRate_TextChanged(object *sender, EventArgs *e)
				{
					genericUpdate();
				}

				void xvidConfigurationPanel::Dispose(bool disposing)
				{
					if (disposing && (components != 0))
					{
						delete components;
					}
					MeGUI::core::details::video::VideoConfigurationPanel::Dispose(disposing);
				}

				void xvidConfigurationPanel::InitializeComponent()
				{
					this->xvidOtherGroupBox = new System::Windows::Forms::GroupBox();
					this->xvidVbvPeakRateLabel = new System::Windows::Forms::Label();
					this->xvidVbvMaxRateLabel = new System::Windows::Forms::Label();
					this->xvidVbvBufferLabel = new System::Windows::Forms::Label();
					this->xvidVbvPeakRate = new System::Windows::Forms::TextBox();
					this->xvidVbvMaxRate = new System::Windows::Forms::TextBox();
					this->xvidVbvBuffer = new System::Windows::Forms::TextBox();
					this->xvidProfile = new System::Windows::Forms::ComboBox();
					this->xvidProfileLabel = new System::Windows::Forms::Label();
					this->xvidMotionSearchPrecision = new System::Windows::Forms::ComboBox();
					this->xvidMotionSearchPrecisionLabel = new System::Windows::Forms::Label();
					this->xvidPackedBitstream = new System::Windows::Forms::CheckBox();
					this->xvidPackedBitstreamLabel = new System::Windows::Forms::Label();
					this->xvidNbBFrames = new System::Windows::Forms::NumericUpDown();
					this->xvidNbBframesLabel = new System::Windows::Forms::Label();
					this->xvidKeyframeInterval = new System::Windows::Forms::TextBox();
					this->xvidKeyframeIntervalLabel = new System::Windows::Forms::Label();
					this->xvidThreadsLabel = new System::Windows::Forms::Label();
					this->nbThreads = new System::Windows::Forms::NumericUpDown();
					this->xvidInterlaced = new System::Windows::Forms::CheckBox();
					this->xvidTrellisQuant = new System::Windows::Forms::CheckBox();
					this->fourCCLabel = new System::Windows::Forms::Label();
					this->fourCC = new System::Windows::Forms::ComboBox();
					this->xvidCodecToolsGroupBox = new System::Windows::Forms::GroupBox();
					this->HVSMasking = new System::Windows::Forms::ComboBox();
					this->label1 = new System::Windows::Forms::Label();
					this->cqmComboBox1 = new MeGUI::core::gui::FileSCBox();
					this->xvidUseVHQForBframes = new System::Windows::Forms::CheckBox();
					this->xvidUseVHQForBframesLabel = new System::Windows::Forms::Label();
					this->xvidClosedGop = new System::Windows::Forms::CheckBox();
					this->xvidClosedGopLabel = new System::Windows::Forms::Label();
					this->xvidQuantTypeLabel = new System::Windows::Forms::Label();
					this->xvidChromaMotion = new System::Windows::Forms::CheckBox();
					this->xvidChromaMotionLabel = new System::Windows::Forms::Label();
					this->xvidCartoonMode = new System::Windows::Forms::CheckBox();
					this->xvidCartoonModeLabel = new System::Windows::Forms::Label();
					this->xvidGMC = new System::Windows::Forms::CheckBox();
					this->xvidGMCLabel = new System::Windows::Forms::Label();
					this->xvidQpel = new System::Windows::Forms::CheckBox();
					this->xvidQPelLabel = new System::Windows::Forms::Label();
					this->xvidVHQ = new System::Windows::Forms::ComboBox();
					this->xvidVHQLabel = new System::Windows::Forms::Label();
					this->xvidGeneralOptionsGroupBox = new System::Windows::Forms::GroupBox();
					this->logfile = new System::Windows::Forms::TextBox();
					this->logfileOpenButton = new System::Windows::Forms::Button();
					this->logfileLabel = new System::Windows::Forms::Label();
					this->xvidBitrateQuantizer = new System::Windows::Forms::NumericUpDown();
					this->xvidBitrateQuantLabel = new System::Windows::Forms::Label();
					this->xvidTurbo = new System::Windows::Forms::CheckBox();
					this->xvidEncodingMode = new System::Windows::Forms::ComboBox();
					this->xvidModeLabel = new System::Windows::Forms::Label();
					this->xvidOtherOptionsGroupbox = new System::Windows::Forms::GroupBox();
					this->xvidFrameDropRatio = new System::Windows::Forms::NumericUpDown();
					this->xvidFrameDropRatioLabel = new System::Windows::Forms::Label();
					this->xvidHQAC = new System::Windows::Forms::CheckBox();
					this->xvidHQACLabel = new System::Windows::Forms::Label();
					this->xvidChromaOptimizerLabel = new System::Windows::Forms::Label();
					this->xvidChromaOptimizer = new System::Windows::Forms::CheckBox();
					this->xvidBframeThresholdLabel = new System::Windows::Forms::Label();
					this->xvidBframeThreshold = new System::Windows::Forms::NumericUpDown();
					this->xvidRCGroupbox = new System::Windows::Forms::GroupBox();
					this->xvidLowBitrateImprovement = new System::Windows::Forms::NumericUpDown();
					this->xvidHighBitrateDegradation = new System::Windows::Forms::NumericUpDown();
					this->xvidLowBitrateImprovementLabel = new System::Windows::Forms::Label();
					this->xvidHighBitrateDegradationLabel = new System::Windows::Forms::Label();
					this->xvidMaxOverflowDegradation = new System::Windows::Forms::NumericUpDown();
					this->xvidMaxOverflowImprovement = new System::Windows::Forms::NumericUpDown();
					this->xvidOverflowControlStrength = new System::Windows::Forms::NumericUpDown();
					this->xvidMaxOverflowDegradationLabel = new System::Windows::Forms::Label();
					this->xvidMaxOverflowImprovementLabel = new System::Windows::Forms::Label();
					this->xvidOverflowControlStrengthLabel = new System::Windows::Forms::Label();
					this->xvidKeyframeReduction = new System::Windows::Forms::NumericUpDown();
					this->xvidKeyframeTreshold = new System::Windows::Forms::TextBox();
					this->xvidIframeBoost = new System::Windows::Forms::NumericUpDown();
					this->xvidKeyframeReductionLabel = new System::Windows::Forms::Label();
					this->xvidKeyframeTresholdLabel = new System::Windows::Forms::Label();
					this->xvidIframeBoostLabel = new System::Windows::Forms::Label();
					this->xvidQuantizerGroupbox = new System::Windows::Forms::GroupBox();
					this->xvidCreditsQuantizer = new System::Windows::Forms::NumericUpDown();
					this->xvidCreditsQuantizerLabel = new System::Windows::Forms::Label();
					this->xvidBframeQuantOffset = new System::Windows::Forms::NumericUpDown();
					this->xvidBframeQuantRatio = new System::Windows::Forms::NumericUpDown();
					this->xvidBframeQuantOffsetLabel = new System::Windows::Forms::Label();
					this->xvidBframeQuantRatioLabel = new System::Windows::Forms::Label();
					this->xvidMaxBQuant = new System::Windows::Forms::NumericUpDown();
					this->xvidMinBQuant = new System::Windows::Forms::NumericUpDown();
					this->xvidMinPQuant = new System::Windows::Forms::NumericUpDown();
					this->xvidMaxPQuant = new System::Windows::Forms::NumericUpDown();
					this->xvidMaxBQuantLabel = new System::Windows::Forms::Label();
					this->xvidMinBQuantLabel = new System::Windows::Forms::Label();
					this->xvidMaxPQuantLabel = new System::Windows::Forms::Label();
					this->xvidMinPQuantLabel = new System::Windows::Forms::Label();
					this->xvidMaxIQuant = new System::Windows::Forms::NumericUpDown();
					this->xvidMinIQuant = new System::Windows::Forms::NumericUpDown();
					this->xvidMaxIQuantLabel = new System::Windows::Forms::Label();
					this->xvidMinIQuantLabel = new System::Windows::Forms::Label();
					this->xvidCBRRcGroupBox = new System::Windows::Forms::GroupBox();
					this->xvidRCBufferSize = new System::Windows::Forms::TextBox();
					this->xvidRCBufferSizeLabel = new System::Windows::Forms::Label();
					this->xvidRCAveragingPeriodLabel = new System::Windows::Forms::Label();
					this->xvidRCAveragingPeriod = new System::Windows::Forms::TextBox();
					this->xvidRCDelayFactorLabel = new System::Windows::Forms::Label();
					this->xvidRCDelayFactor = new System::Windows::Forms::TextBox();
					this->openFileDialog = new System::Windows::Forms::OpenFileDialog();
					this->saveFileDialog = new System::Windows::Forms::SaveFileDialog();
					this->advancedTabPage = new System::Windows::Forms::TabPage();
					this->gbx264CustomCmd = new System::Windows::Forms::GroupBox();
					this->customCommandlineOptions = new System::Windows::Forms::TextBox();
					this->xvidCustomCommandlineOptionsLabel = new System::Windows::Forms::Label();
					this->xvidCustomCommandlineOptions = new System::Windows::Forms::TextBox();
					this->quantizerMatrixGroupbox = new System::Windows::Forms::GroupBox();
					this->tabControl1->SuspendLayout();
					this->mainTabPage->SuspendLayout();
					this->xvidOtherGroupBox->SuspendLayout();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->xvidNbBFrames))->BeginInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->nbThreads))->BeginInit();
					this->xvidCodecToolsGroupBox->SuspendLayout();
					this->xvidGeneralOptionsGroupBox->SuspendLayout();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->xvidBitrateQuantizer))->BeginInit();
					this->xvidOtherOptionsGroupbox->SuspendLayout();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->xvidFrameDropRatio))->BeginInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->xvidBframeThreshold))->BeginInit();
					this->xvidRCGroupbox->SuspendLayout();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->xvidLowBitrateImprovement))->BeginInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->xvidHighBitrateDegradation))->BeginInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->xvidMaxOverflowDegradation))->BeginInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->xvidMaxOverflowImprovement))->BeginInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->xvidOverflowControlStrength))->BeginInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->xvidKeyframeReduction))->BeginInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->xvidIframeBoost))->BeginInit();
					this->xvidQuantizerGroupbox->SuspendLayout();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->xvidCreditsQuantizer))->BeginInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->xvidBframeQuantOffset))->BeginInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->xvidBframeQuantRatio))->BeginInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->xvidMaxBQuant))->BeginInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->xvidMinBQuant))->BeginInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->xvidMinPQuant))->BeginInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->xvidMaxPQuant))->BeginInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->xvidMaxIQuant))->BeginInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->xvidMinIQuant))->BeginInit();
					this->xvidCBRRcGroupBox->SuspendLayout();
					this->advancedTabPage->SuspendLayout();
					this->gbx264CustomCmd->SuspendLayout();
					this->quantizerMatrixGroupbox->SuspendLayout();
					this->SuspendLayout();
					// 
					// tabControl1
					// 
					this->tabControl1->Controls->Add(this->advancedTabPage);
					this->tabControl1->Size = new System::Drawing::Size(500, 458);
					this->tabControl1->Controls->SetChildIndex(this->advancedTabPage, 0);
					this->tabControl1->Controls->SetChildIndex(this->mainTabPage, 0);
					// 
					// commandline
					// 
					this->commandline->Location = new System::Drawing::Point(4, 464);
					this->commandline->Size = new System::Drawing::Size(496, 59);
					this->commandline->Text = " ";
					// 
					// mainTabPage
					// 
					this->mainTabPage->Controls->Add(this->xvidOtherGroupBox);
					this->mainTabPage->Controls->Add(this->xvidCodecToolsGroupBox);
					this->mainTabPage->Controls->Add(this->xvidGeneralOptionsGroupBox);
					this->mainTabPage->Size = new System::Drawing::Size(492, 432);
					// 
					// xvidOtherGroupBox
					// 
					this->xvidOtherGroupBox->Controls->Add(this->xvidVbvPeakRateLabel);
					this->xvidOtherGroupBox->Controls->Add(this->xvidVbvMaxRateLabel);
					this->xvidOtherGroupBox->Controls->Add(this->xvidVbvBufferLabel);
					this->xvidOtherGroupBox->Controls->Add(this->xvidVbvPeakRate);
					this->xvidOtherGroupBox->Controls->Add(this->xvidVbvMaxRate);
					this->xvidOtherGroupBox->Controls->Add(this->xvidVbvBuffer);
					this->xvidOtherGroupBox->Controls->Add(this->xvidProfile);
					this->xvidOtherGroupBox->Controls->Add(this->xvidProfileLabel);
					this->xvidOtherGroupBox->Controls->Add(this->xvidMotionSearchPrecision);
					this->xvidOtherGroupBox->Controls->Add(this->xvidMotionSearchPrecisionLabel);
					this->xvidOtherGroupBox->Controls->Add(this->xvidPackedBitstream);
					this->xvidOtherGroupBox->Controls->Add(this->xvidPackedBitstreamLabel);
					this->xvidOtherGroupBox->Controls->Add(this->xvidNbBFrames);
					this->xvidOtherGroupBox->Controls->Add(this->xvidNbBframesLabel);
					this->xvidOtherGroupBox->Controls->Add(this->xvidKeyframeInterval);
					this->xvidOtherGroupBox->Controls->Add(this->xvidKeyframeIntervalLabel);
					this->xvidOtherGroupBox->Controls->Add(this->xvidThreadsLabel);
					this->xvidOtherGroupBox->Controls->Add(this->nbThreads);
					this->xvidOtherGroupBox->Controls->Add(this->xvidInterlaced);
					this->xvidOtherGroupBox->Controls->Add(this->xvidTrellisQuant);
					this->xvidOtherGroupBox->Controls->Add(this->fourCCLabel);
					this->xvidOtherGroupBox->Controls->Add(this->fourCC);
					this->xvidOtherGroupBox->Location = new System::Drawing::Point(326, 3);
					this->xvidOtherGroupBox->Name = "xvidOtherGroupBox";
					this->xvidOtherGroupBox->Size = new System::Drawing::Size(162, 423);
					this->xvidOtherGroupBox->TabIndex = 24;
					this->xvidOtherGroupBox->TabStop = false;
					this->xvidOtherGroupBox->Text = "Other Settings";
					// 
					// xvidVbvPeakRateLabel
					// 
					this->xvidVbvPeakRateLabel->AutoSize = true;
					this->xvidVbvPeakRateLabel->Location = new System::Drawing::Point(8, 392);
					this->xvidVbvPeakRateLabel->Name = "xvidVbvPeakRateLabel";
					this->xvidVbvPeakRateLabel->Size = new System::Drawing::Size(32, 13);
					this->xvidVbvPeakRateLabel->TabIndex = 23;
					this->xvidVbvPeakRateLabel->Text = "Peak";
					// 
					// xvidVbvMaxRateLabel
					// 
					this->xvidVbvMaxRateLabel->Location = new System::Drawing::Point(8, 358);
					this->xvidVbvMaxRateLabel->Name = "xvidVbvMaxRateLabel";
					this->xvidVbvMaxRateLabel->Size = new System::Drawing::Size(42, 23);
					this->xvidVbvMaxRateLabel->TabIndex = 22;
					this->xvidVbvMaxRateLabel->Text = "Max";
					// 
					// xvidVbvBufferLabel
					// 
					this->xvidVbvBufferLabel->Location = new System::Drawing::Point(8, 324);
					this->xvidVbvBufferLabel->Name = "xvidVbvBufferLabel";
					this->xvidVbvBufferLabel->Size = new System::Drawing::Size(42, 23);
					this->xvidVbvBufferLabel->TabIndex = 21;
					this->xvidVbvBufferLabel->Text = "Buffer";
					// 
					// xvidVbvPeakRate
					// 
					this->xvidVbvPeakRate->Enabled = false;
					this->xvidVbvPeakRate->Location = new System::Drawing::Point(56, 389);
					this->xvidVbvPeakRate->Name = "xvidVbvPeakRate";
					this->xvidVbvPeakRate->Size = new System::Drawing::Size(100, 20);
					this->xvidVbvPeakRate->TabIndex = 20;
					this->xvidVbvPeakRate->Text = "0";
					this->xvidVbvPeakRate->TextChanged += new System::EventHandler(this, &xvidConfigurationPanel::xvidVbvPeakRate_TextChanged);
					// 
					// xvidVbvMaxRate
					// 
					this->xvidVbvMaxRate->Enabled = false;
					this->xvidVbvMaxRate->Location = new System::Drawing::Point(56, 355);
					this->xvidVbvMaxRate->Name = "xvidVbvMaxRate";
					this->xvidVbvMaxRate->Size = new System::Drawing::Size(100, 20);
					this->xvidVbvMaxRate->TabIndex = 19;
					this->xvidVbvMaxRate->Text = "0";
					this->xvidVbvMaxRate->TextChanged += new System::EventHandler(this, &xvidConfigurationPanel::xvidVbvMaxRate_TextChanged);
					// 
					// xvidVbvBuffer
					// 
					this->xvidVbvBuffer->Enabled = false;
					this->xvidVbvBuffer->Location = new System::Drawing::Point(56, 321);
					this->xvidVbvBuffer->Name = "xvidVbvBuffer";
					this->xvidVbvBuffer->Size = new System::Drawing::Size(100, 20);
					this->xvidVbvBuffer->TabIndex = 18;
					this->xvidVbvBuffer->Text = "0";
					this->xvidVbvBuffer->TextChanged += new System::EventHandler(this, &xvidConfigurationPanel::xvidVbvBuffer_TextChanged);
					// 
					// xvidProfile
					// 
					this->xvidProfile->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
					this->xvidProfile->DropDownWidth = 145;
					this->xvidProfile->Items->AddRange(new object[7] {"Unrestricted", "Home Theatre", "Hi-Def (720p)", "Hi-Def (1080p)", "Handheld", "Portable", "Custom"});
					this->xvidProfile->Location = new System::Drawing::Point(11, 287);
					this->xvidProfile->Name = "xvidProfile";
					this->xvidProfile->Size = new System::Drawing::Size(145, 21);
					this->xvidProfile->TabIndex = 17;
					this->xvidProfile->SelectedIndexChanged += new System::EventHandler(this, &xvidConfigurationPanel::xvidProfile_SelectedIndexChanged);
					// 
					// xvidProfileLabel
					// 
					this->xvidProfileLabel->Location = new System::Drawing::Point(8, 271);
					this->xvidProfileLabel->Name = "xvidProfileLabel";
					this->xvidProfileLabel->Size = new System::Drawing::Size(136, 24);
					this->xvidProfileLabel->TabIndex = 16;
					this->xvidProfileLabel->Text = "Profile:";
					// 
					// xvidMotionSearchPrecision
					// 
					this->xvidMotionSearchPrecision->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
					this->xvidMotionSearchPrecision->Items->AddRange(new object[7] {"0 - None", "1 - Very Low", "2 - Low", "3 - Medium", "4 - High", "5 - Very High", "6 - Ultra High"});
					this->xvidMotionSearchPrecision->Location = new System::Drawing::Point(11, 244);
					this->xvidMotionSearchPrecision->Name = "xvidMotionSearchPrecision";
					this->xvidMotionSearchPrecision->Size = new System::Drawing::Size(145, 21);
					this->xvidMotionSearchPrecision->TabIndex = 15;
					this->xvidMotionSearchPrecision->SelectedIndexChanged += new System::EventHandler(this, &xvidConfigurationPanel::updateEvent);
					// 
					// xvidMotionSearchPrecisionLabel
					// 
					this->xvidMotionSearchPrecisionLabel->Location = new System::Drawing::Point(8, 225);
					this->xvidMotionSearchPrecisionLabel->Name = "xvidMotionSearchPrecisionLabel";
					this->xvidMotionSearchPrecisionLabel->Size = new System::Drawing::Size(136, 24);
					this->xvidMotionSearchPrecisionLabel->TabIndex = 14;
					this->xvidMotionSearchPrecisionLabel->Text = "Motion Search Precision :";
					// 
					// xvidPackedBitstream
					// 
					this->xvidPackedBitstream->Location = new System::Drawing::Point(11, 87);
					this->xvidPackedBitstream->Name = "xvidPackedBitstream";
					this->xvidPackedBitstream->Size = new System::Drawing::Size(16, 24);
					this->xvidPackedBitstream->TabIndex = 13;
					this->xvidPackedBitstream->CheckedChanged += new System::EventHandler(this, &xvidConfigurationPanel::updateEvent);
					// 
					// xvidPackedBitstreamLabel
					// 
					this->xvidPackedBitstreamLabel->Location = new System::Drawing::Point(27, 92);
					this->xvidPackedBitstreamLabel->Name = "xvidPackedBitstreamLabel";
					this->xvidPackedBitstreamLabel->Size = new System::Drawing::Size(100, 23);
					this->xvidPackedBitstreamLabel->TabIndex = 12;
					this->xvidPackedBitstreamLabel->Text = "Packed Bitstream";
					// 
					// xvidNbBFrames
					// 
					this->xvidNbBFrames->Location = new System::Drawing::Point(116, 144);
					this->xvidNbBFrames->Maximum = decimal(new int[4] {4, 0, 0, 0});
					this->xvidNbBFrames->Name = "xvidNbBFrames";
					this->xvidNbBFrames->Size = new System::Drawing::Size(40, 20);
					this->xvidNbBFrames->TabIndex = 11;
					this->xvidNbBFrames->ValueChanged += new System::EventHandler(this, &xvidConfigurationPanel::updateEvent);
					// 
					// xvidNbBframesLabel
					// 
					this->xvidNbBframesLabel->Location = new System::Drawing::Point(8, 146);
					this->xvidNbBframesLabel->Name = "xvidNbBframesLabel";
					this->xvidNbBframesLabel->Size = new System::Drawing::Size(83, 23);
					this->xvidNbBframesLabel->TabIndex = 10;
					this->xvidNbBframesLabel->Text = "Nb of B-frames";
					// 
					// xvidKeyframeInterval
					// 
					this->xvidKeyframeInterval->Location = new System::Drawing::Point(116, 119);
					this->xvidKeyframeInterval->Name = "xvidKeyframeInterval";
					this->xvidKeyframeInterval->Size = new System::Drawing::Size(40, 20);
					this->xvidKeyframeInterval->TabIndex = 9;
					this->xvidKeyframeInterval->Text = "300";
					this->xvidKeyframeInterval->TextChanged += new System::EventHandler(this, &xvidConfigurationPanel::updateEvent);
					// 
					// xvidKeyframeIntervalLabel
					// 
					this->xvidKeyframeIntervalLabel->Location = new System::Drawing::Point(8, 119);
					this->xvidKeyframeIntervalLabel->Name = "xvidKeyframeIntervalLabel";
					this->xvidKeyframeIntervalLabel->Size = new System::Drawing::Size(104, 25);
					this->xvidKeyframeIntervalLabel->TabIndex = 8;
					this->xvidKeyframeIntervalLabel->Text = "Max Keyframe Int.";
					// 
					// xvidThreadsLabel
					// 
					this->xvidThreadsLabel->AutoSize = true;
					this->xvidThreadsLabel->Location = new System::Drawing::Point(8, 172);
					this->xvidThreadsLabel->Name = "xvidThreadsLabel";
					this->xvidThreadsLabel->Size = new System::Drawing::Size(46, 13);
					this->xvidThreadsLabel->TabIndex = 4;
					this->xvidThreadsLabel->Text = "Threads";
					// 
					// nbThreads
					// 
					this->nbThreads->Location = new System::Drawing::Point(84, 170);
					this->nbThreads->Name = "nbThreads";
					this->nbThreads->Size = new System::Drawing::Size(72, 20);
					this->nbThreads->TabIndex = 5;
					this->nbThreads->ValueChanged += new System::EventHandler(this, &xvidConfigurationPanel::updateEvent);
					// 
					// xvidInterlaced
					// 
					this->xvidInterlaced->Location = new System::Drawing::Point(11, 64);
					this->xvidInterlaced->Name = "xvidInterlaced";
					this->xvidInterlaced->Size = new System::Drawing::Size(104, 24);
					this->xvidInterlaced->TabIndex = 3;
					this->xvidInterlaced->Text = "Interlaced";
					this->xvidInterlaced->CheckedChanged += new System::EventHandler(this, &xvidConfigurationPanel::updateEvent);
					// 
					// xvidTrellisQuant
					// 
					this->xvidTrellisQuant->Location = new System::Drawing::Point(11, 16);
					this->xvidTrellisQuant->Name = "xvidTrellisQuant";
					this->xvidTrellisQuant->Size = new System::Drawing::Size(104, 24);
					this->xvidTrellisQuant->TabIndex = 0;
					this->xvidTrellisQuant->Text = "Trellis Quant";
					this->xvidTrellisQuant->CheckedChanged += new System::EventHandler(this, &xvidConfigurationPanel::updateEvent);
					// 
					// fourCCLabel
					// 
					this->fourCCLabel->Location = new System::Drawing::Point(8, 199);
					this->fourCCLabel->Name = "fourCCLabel";
					this->fourCCLabel->Size = new System::Drawing::Size(46, 18);
					this->fourCCLabel->TabIndex = 6;
					this->fourCCLabel->Text = "FourCC";
					// 
					// fourCC
					// 
					this->fourCC->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
					this->fourCC->Items->AddRange(new object[4] {"XVID", "DIVX", "DX50", "MP4V"});
					this->fourCC->Location = new System::Drawing::Point(84, 196);
					this->fourCC->Name = "fourCC";
					this->fourCC->Size = new System::Drawing::Size(72, 21);
					this->fourCC->TabIndex = 7;
					this->fourCC->SelectedIndexChanged += new System::EventHandler(this, &xvidConfigurationPanel::updateEvent);
					// 
					// xvidCodecToolsGroupBox
					// 
					this->xvidCodecToolsGroupBox->Controls->Add(this->HVSMasking);
					this->xvidCodecToolsGroupBox->Controls->Add(this->label1);
					this->xvidCodecToolsGroupBox->Controls->Add(this->cqmComboBox1);
					this->xvidCodecToolsGroupBox->Controls->Add(this->xvidUseVHQForBframes);
					this->xvidCodecToolsGroupBox->Controls->Add(this->xvidUseVHQForBframesLabel);
					this->xvidCodecToolsGroupBox->Controls->Add(this->xvidClosedGop);
					this->xvidCodecToolsGroupBox->Controls->Add(this->xvidClosedGopLabel);
					this->xvidCodecToolsGroupBox->Controls->Add(this->xvidQuantTypeLabel);
					this->xvidCodecToolsGroupBox->Controls->Add(this->xvidChromaMotion);
					this->xvidCodecToolsGroupBox->Controls->Add(this->xvidChromaMotionLabel);
					this->xvidCodecToolsGroupBox->Controls->Add(this->xvidCartoonMode);
					this->xvidCodecToolsGroupBox->Controls->Add(this->xvidCartoonModeLabel);
					this->xvidCodecToolsGroupBox->Controls->Add(this->xvidGMC);
					this->xvidCodecToolsGroupBox->Controls->Add(this->xvidGMCLabel);
					this->xvidCodecToolsGroupBox->Controls->Add(this->xvidQpel);
					this->xvidCodecToolsGroupBox->Controls->Add(this->xvidQPelLabel);
					this->xvidCodecToolsGroupBox->Controls->Add(this->xvidVHQ);
					this->xvidCodecToolsGroupBox->Controls->Add(this->xvidVHQLabel);
					this->xvidCodecToolsGroupBox->Location = new System::Drawing::Point(0, 136);
					this->xvidCodecToolsGroupBox->Name = "xvidCodecToolsGroupBox";
					this->xvidCodecToolsGroupBox->Size = new System::Drawing::Size(320, 290);
					this->xvidCodecToolsGroupBox->TabIndex = 23;
					this->xvidCodecToolsGroupBox->TabStop = false;
					this->xvidCodecToolsGroupBox->Text = "Tools";
					// 
					// HVSMasking
					// 
					this->HVSMasking->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
					this->HVSMasking->FormattingEnabled = true;
					this->HVSMasking->Items->AddRange(new object[2] {"None", "Lumi"});
					this->HVSMasking->Location = new System::Drawing::Point(192, 184);
					this->HVSMasking->Name = "HVSMasking";
					this->HVSMasking->Size = new System::Drawing::Size(121, 21);
					this->HVSMasking->TabIndex = 18;
					this->HVSMasking->SelectedIndexChanged += new System::EventHandler(this, &xvidConfigurationPanel::updateEvent);
					// 
					// label1
					// 
					this->label1->AutoSize = true;
					this->label1->Location = new System::Drawing::Point(9, 187);
					this->label1->Name = "label1";
					this->label1->Size = new System::Drawing::Size(72, 13);
					this->label1->TabIndex = 17;
					this->label1->Text = "HVS Masking";
					// 
					// cqmComboBox1
					// 
					this->cqmComboBox1->setFilter("");
					this->cqmComboBox1->Location = new System::Drawing::Point(10, 241);
					this->cqmComboBox1->MaximumSize = new System::Drawing::Size(1000, 29);
					this->cqmComboBox1->MinimumSize = new System::Drawing::Size(64, 29);
					this->cqmComboBox1->Name = "cqmComboBox1";
					this->cqmComboBox1->setSelectedIndex(-1);
//C# TO C++ CONVERTER WARNING: C# to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
					delete this->cqmComboBox1->getSelectedItem();
					this->cqmComboBox1->Size = new System::Drawing::Size(302, 29);
					this->cqmComboBox1->TabIndex = 16;
					this->cqmComboBox1->SelectionChanged += new MeGUI::StringChanged(this, &xvidConfigurationPanel::cqmComboBox1_SelectionChanged);
					// 
					// xvidUseVHQForBframes
					// 
					this->xvidUseVHQForBframes->Location = new System::Drawing::Point(296, 37);
					this->xvidUseVHQForBframes->Name = "xvidUseVHQForBframes";
					this->xvidUseVHQForBframes->Size = new System::Drawing::Size(16, 24);
					this->xvidUseVHQForBframes->TabIndex = 3;
					this->xvidUseVHQForBframes->CheckedChanged += new System::EventHandler(this, &xvidConfigurationPanel::updateEvent);
					// 
					// xvidUseVHQForBframesLabel
					// 
					this->xvidUseVHQForBframesLabel->Location = new System::Drawing::Point(8, 46);
					this->xvidUseVHQForBframesLabel->Name = "xvidUseVHQForBframesLabel";
					this->xvidUseVHQForBframesLabel->Size = new System::Drawing::Size(120, 16);
					this->xvidUseVHQForBframesLabel->TabIndex = 2;
					this->xvidUseVHQForBframesLabel->Text = "Use VHQ for Bframes";
					// 
					// xvidClosedGop
					// 
					this->xvidClosedGop->Checked = true;
					this->xvidClosedGop->CheckState = System::Windows::Forms::CheckState::Checked;
					this->xvidClosedGop->Location = new System::Drawing::Point(296, 154);
					this->xvidClosedGop->Name = "xvidClosedGop";
					this->xvidClosedGop->Size = new System::Drawing::Size(16, 24);
					this->xvidClosedGop->TabIndex = 15;
					this->xvidClosedGop->CheckedChanged += new System::EventHandler(this, &xvidConfigurationPanel::updateEvent);
					// 
					// xvidClosedGopLabel
					// 
					this->xvidClosedGopLabel->Location = new System::Drawing::Point(8, 159);
					this->xvidClosedGopLabel->Name = "xvidClosedGopLabel";
					this->xvidClosedGopLabel->Size = new System::Drawing::Size(100, 16);
					this->xvidClosedGopLabel->TabIndex = 14;
					this->xvidClosedGopLabel->Text = "Closed GOP";
					// 
					// xvidQuantTypeLabel
					// 
					this->xvidQuantTypeLabel->Location = new System::Drawing::Point(8, 222);
					this->xvidQuantTypeLabel->Name = "xvidQuantTypeLabel";
					this->xvidQuantTypeLabel->Size = new System::Drawing::Size(100, 16);
					this->xvidQuantTypeLabel->TabIndex = 12;
					this->xvidQuantTypeLabel->Text = "Quantization Type";
					// 
					// xvidChromaMotion
					// 
					this->xvidChromaMotion->Checked = true;
					this->xvidChromaMotion->CheckState = System::Windows::Forms::CheckState::Checked;
					this->xvidChromaMotion->Location = new System::Drawing::Point(296, 133);
					this->xvidChromaMotion->Name = "xvidChromaMotion";
					this->xvidChromaMotion->Size = new System::Drawing::Size(16, 24);
					this->xvidChromaMotion->TabIndex = 11;
					this->xvidChromaMotion->CheckedChanged += new System::EventHandler(this, &xvidConfigurationPanel::updateEvent);
					// 
					// xvidChromaMotionLabel
					// 
					this->xvidChromaMotionLabel->Location = new System::Drawing::Point(8, 134);
					this->xvidChromaMotionLabel->Name = "xvidChromaMotionLabel";
					this->xvidChromaMotionLabel->Size = new System::Drawing::Size(100, 16);
					this->xvidChromaMotionLabel->TabIndex = 10;
					this->xvidChromaMotionLabel->Text = "Chroma motion";
					// 
					// xvidCartoonMode
					// 
					this->xvidCartoonMode->Location = new System::Drawing::Point(296, 109);
					this->xvidCartoonMode->Name = "xvidCartoonMode";
					this->xvidCartoonMode->Size = new System::Drawing::Size(16, 24);
					this->xvidCartoonMode->TabIndex = 9;
					this->xvidCartoonMode->Visible = false;
					this->xvidCartoonMode->CheckedChanged += new System::EventHandler(this, &xvidConfigurationPanel::updateEvent);
					// 
					// xvidCartoonModeLabel
					// 
					this->xvidCartoonModeLabel->Location = new System::Drawing::Point(8, 112);
					this->xvidCartoonModeLabel->Name = "xvidCartoonModeLabel";
					this->xvidCartoonModeLabel->Size = new System::Drawing::Size(100, 16);
					this->xvidCartoonModeLabel->TabIndex = 8;
					this->xvidCartoonModeLabel->Text = "Cartoon mode";
					this->xvidCartoonModeLabel->Visible = false;
					// 
					// xvidGMC
					// 
					this->xvidGMC->Location = new System::Drawing::Point(296, 85);
					this->xvidGMC->Name = "xvidGMC";
					this->xvidGMC->Size = new System::Drawing::Size(16, 24);
					this->xvidGMC->TabIndex = 7;
					this->xvidGMC->CheckedChanged += new System::EventHandler(this, &xvidConfigurationPanel::updateEvent);
					// 
					// xvidGMCLabel
					// 
					this->xvidGMCLabel->Location = new System::Drawing::Point(8, 90);
					this->xvidGMCLabel->Name = "xvidGMCLabel";
					this->xvidGMCLabel->Size = new System::Drawing::Size(100, 16);
					this->xvidGMCLabel->TabIndex = 6;
					this->xvidGMCLabel->Text = "GMC";
					// 
					// xvidQpel
					// 
					this->xvidQpel->Location = new System::Drawing::Point(296, 61);
					this->xvidQpel->Name = "xvidQpel";
					this->xvidQpel->Size = new System::Drawing::Size(16, 24);
					this->xvidQpel->TabIndex = 5;
					this->xvidQpel->CheckedChanged += new System::EventHandler(this, &xvidConfigurationPanel::updateEvent);
					// 
					// xvidQPelLabel
					// 
					this->xvidQPelLabel->Location = new System::Drawing::Point(8, 68);
					this->xvidQPelLabel->Name = "xvidQPelLabel";
					this->xvidQPelLabel->Size = new System::Drawing::Size(100, 16);
					this->xvidQPelLabel->TabIndex = 4;
					this->xvidQPelLabel->Text = "QPel";
					// 
					// xvidVHQ
					// 
					this->xvidVHQ->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
					this->xvidVHQ->Items->AddRange(new object[5] {"0 - Off", "1 - Mode Decision", "2 - Limited Search", "3 - Medium Search", "4 - Wide Search"});
					this->xvidVHQ->Location = new System::Drawing::Point(192, 16);
					this->xvidVHQ->Name = "xvidVHQ";
					this->xvidVHQ->Size = new System::Drawing::Size(121, 21);
					this->xvidVHQ->TabIndex = 1;
					this->xvidVHQ->SelectedIndexChanged += new System::EventHandler(this, &xvidConfigurationPanel::updateEvent);
					// 
					// xvidVHQLabel
					// 
					this->xvidVHQLabel->Location = new System::Drawing::Point(8, 24);
					this->xvidVHQLabel->Name = "xvidVHQLabel";
					this->xvidVHQLabel->Size = new System::Drawing::Size(100, 16);
					this->xvidVHQLabel->TabIndex = 0;
					this->xvidVHQLabel->Text = "VHQ mode";
					// 
					// xvidGeneralOptionsGroupBox
					// 
					this->xvidGeneralOptionsGroupBox->Controls->Add(this->logfile);
					this->xvidGeneralOptionsGroupBox->Controls->Add(this->logfileOpenButton);
					this->xvidGeneralOptionsGroupBox->Controls->Add(this->logfileLabel);
					this->xvidGeneralOptionsGroupBox->Controls->Add(this->xvidBitrateQuantizer);
					this->xvidGeneralOptionsGroupBox->Controls->Add(this->xvidBitrateQuantLabel);
					this->xvidGeneralOptionsGroupBox->Controls->Add(this->xvidTurbo);
					this->xvidGeneralOptionsGroupBox->Controls->Add(this->xvidEncodingMode);
					this->xvidGeneralOptionsGroupBox->Controls->Add(this->xvidModeLabel);
					this->xvidGeneralOptionsGroupBox->Location = new System::Drawing::Point(0, 3);
					this->xvidGeneralOptionsGroupBox->Name = "xvidGeneralOptionsGroupBox";
					this->xvidGeneralOptionsGroupBox->Size = new System::Drawing::Size(320, 127);
					this->xvidGeneralOptionsGroupBox->TabIndex = 22;
					this->xvidGeneralOptionsGroupBox->TabStop = false;
					this->xvidGeneralOptionsGroupBox->Text = "General";
					// 
					// logfile
					// 
					this->logfile->Location = new System::Drawing::Point(57, 77);
					this->logfile->Name = "logfile";
					this->logfile->ReadOnly = true;
					this->logfile->Size = new System::Drawing::Size(225, 20);
					this->logfile->TabIndex = 15;
					this->logfile->Text = "2pass.stats";
					// 
					// logfileOpenButton
					// 
					this->logfileOpenButton->Location = new System::Drawing::Point(288, 75);
					this->logfileOpenButton->Name = "logfileOpenButton";
					this->logfileOpenButton->Size = new System::Drawing::Size(24, 23);
					this->logfileOpenButton->TabIndex = 16;
					this->logfileOpenButton->Text = "...";
					this->logfileOpenButton->Click += new System::EventHandler(this, &xvidConfigurationPanel::logfileOpenButton_Click);
					// 
					// logfileLabel
					// 
					this->logfileLabel->Location = new System::Drawing::Point(8, 80);
					this->logfileLabel->Name = "logfileLabel";
					this->logfileLabel->Size = new System::Drawing::Size(56, 20);
					this->logfileLabel->TabIndex = 14;
					this->logfileLabel->Text = "Logfile";
					// 
					// xvidBitrateQuantizer
					// 
					this->xvidBitrateQuantizer->Location = new System::Drawing::Point(192, 43);
					this->xvidBitrateQuantizer->Maximum = decimal(new int[4] {10000, 0, 0, 0});
					this->xvidBitrateQuantizer->Name = "xvidBitrateQuantizer";
					this->xvidBitrateQuantizer->Size = new System::Drawing::Size(120, 20);
					this->xvidBitrateQuantizer->TabIndex = 13;
					this->xvidBitrateQuantizer->ValueChanged += new System::EventHandler(this, &xvidConfigurationPanel::updateEvent);
					// 
					// xvidBitrateQuantLabel
					// 
					this->xvidBitrateQuantLabel->Location = new System::Drawing::Point(8, 48);
					this->xvidBitrateQuantLabel->Name = "xvidBitrateQuantLabel";
					this->xvidBitrateQuantLabel->Size = new System::Drawing::Size(100, 24);
					this->xvidBitrateQuantLabel->TabIndex = 3;
					this->xvidBitrateQuantLabel->Text = "Bitrate";
					// 
					// xvidTurbo
					// 
					this->xvidTurbo->Location = new System::Drawing::Point(120, 16);
					this->xvidTurbo->Name = "xvidTurbo";
					this->xvidTurbo->Size = new System::Drawing::Size(64, 24);
					this->xvidTurbo->TabIndex = 1;
					this->xvidTurbo->Text = "Turbo";
					this->xvidTurbo->CheckedChanged += new System::EventHandler(this, &xvidConfigurationPanel::updateEvent);
					// 
					// xvidEncodingMode
					// 
					this->xvidEncodingMode->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
					this->xvidEncodingMode->Items->AddRange(new object[5] {"CBR", "CQ", "2pass - 1st pass", "2pass - 2nd pass", "Automated 2pass"});
					this->xvidEncodingMode->Location = new System::Drawing::Point(192, 16);
					this->xvidEncodingMode->Name = "xvidEncodingMode";
					this->xvidEncodingMode->Size = new System::Drawing::Size(121, 21);
					this->xvidEncodingMode->TabIndex = 2;
					this->xvidEncodingMode->SelectedIndexChanged += new System::EventHandler(this, &xvidConfigurationPanel::updateEvent);
					// 
					// xvidModeLabel
					// 
					this->xvidModeLabel->Location = new System::Drawing::Point(8, 24);
					this->xvidModeLabel->Name = "xvidModeLabel";
					this->xvidModeLabel->Size = new System::Drawing::Size(100, 24);
					this->xvidModeLabel->TabIndex = 0;
					this->xvidModeLabel->Text = "Mode";
					// 
					// xvidOtherOptionsGroupbox
					// 
					this->xvidOtherOptionsGroupbox->Controls->Add(this->xvidFrameDropRatio);
					this->xvidOtherOptionsGroupbox->Controls->Add(this->xvidFrameDropRatioLabel);
					this->xvidOtherOptionsGroupbox->Controls->Add(this->xvidHQAC);
					this->xvidOtherOptionsGroupbox->Controls->Add(this->xvidHQACLabel);
					this->xvidOtherOptionsGroupbox->Controls->Add(this->xvidChromaOptimizerLabel);
					this->xvidOtherOptionsGroupbox->Controls->Add(this->xvidChromaOptimizer);
					this->xvidOtherOptionsGroupbox->Controls->Add(this->xvidBframeThresholdLabel);
					this->xvidOtherOptionsGroupbox->Controls->Add(this->xvidBframeThreshold);
					this->xvidOtherOptionsGroupbox->Location = new System::Drawing::Point(289, 246);
					this->xvidOtherOptionsGroupbox->Name = "xvidOtherOptionsGroupbox";
					this->xvidOtherOptionsGroupbox->Size = new System::Drawing::Size(200, 136);
					this->xvidOtherOptionsGroupbox->TabIndex = 3;
					this->xvidOtherOptionsGroupbox->TabStop = false;
					this->xvidOtherOptionsGroupbox->Text = "Other options";
					this->xvidOtherOptionsGroupbox->Visible = false;
					// 
					// xvidFrameDropRatio
					// 
					this->xvidFrameDropRatio->Location = new System::Drawing::Point(139, 99);
					this->xvidFrameDropRatio->Name = "xvidFrameDropRatio";
					this->xvidFrameDropRatio->Size = new System::Drawing::Size(48, 20);
					this->xvidFrameDropRatio->TabIndex = 7;
					this->xvidFrameDropRatio->ValueChanged += new System::EventHandler(this, &xvidConfigurationPanel::updateEvent);
					// 
					// xvidFrameDropRatioLabel
					// 
					this->xvidFrameDropRatioLabel->Location = new System::Drawing::Point(12, 101);
					this->xvidFrameDropRatioLabel->Name = "xvidFrameDropRatioLabel";
					this->xvidFrameDropRatioLabel->Size = new System::Drawing::Size(100, 23);
					this->xvidFrameDropRatioLabel->TabIndex = 6;
					this->xvidFrameDropRatioLabel->Text = "Frame drop Ratio";
					// 
					// xvidHQAC
					// 
					this->xvidHQAC->Location = new System::Drawing::Point(171, 74);
					this->xvidHQAC->Name = "xvidHQAC";
					this->xvidHQAC->Size = new System::Drawing::Size(16, 24);
					this->xvidHQAC->TabIndex = 5;
					this->xvidHQAC->CheckedChanged += new System::EventHandler(this, &xvidConfigurationPanel::updateEvent);
					// 
					// xvidHQACLabel
					// 
					this->xvidHQACLabel->Location = new System::Drawing::Point(12, 77);
					this->xvidHQACLabel->Name = "xvidHQACLabel";
					this->xvidHQACLabel->Size = new System::Drawing::Size(100, 23);
					this->xvidHQACLabel->TabIndex = 4;
					this->xvidHQACLabel->Text = "HQ AC Coefficients";
					// 
					// xvidChromaOptimizerLabel
					// 
					this->xvidChromaOptimizerLabel->Location = new System::Drawing::Point(12, 53);
					this->xvidChromaOptimizerLabel->Name = "xvidChromaOptimizerLabel";
					this->xvidChromaOptimizerLabel->Size = new System::Drawing::Size(100, 23);
					this->xvidChromaOptimizerLabel->TabIndex = 2;
					this->xvidChromaOptimizerLabel->Text = "Chroma Optimizer";
					// 
					// xvidChromaOptimizer
					// 
					this->xvidChromaOptimizer->Location = new System::Drawing::Point(171, 51);
					this->xvidChromaOptimizer->Name = "xvidChromaOptimizer";
					this->xvidChromaOptimizer->Size = new System::Drawing::Size(16, 24);
					this->xvidChromaOptimizer->TabIndex = 3;
					this->xvidChromaOptimizer->CheckedChanged += new System::EventHandler(this, &xvidConfigurationPanel::updateEvent);
					// 
					// xvidBframeThresholdLabel
					// 
					this->xvidBframeThresholdLabel->Location = new System::Drawing::Point(12, 29);
					this->xvidBframeThresholdLabel->Name = "xvidBframeThresholdLabel";
					this->xvidBframeThresholdLabel->Size = new System::Drawing::Size(100, 23);
					this->xvidBframeThresholdLabel->TabIndex = 0;
					this->xvidBframeThresholdLabel->Text = "B-frame Threshold";
					// 
					// xvidBframeThreshold
					// 
					this->xvidBframeThreshold->Location = new System::Drawing::Point(139, 29);
					this->xvidBframeThreshold->Maximum = decimal(new int[4] {255, 0, 0, 0});
					this->xvidBframeThreshold->Minimum = decimal(new int[4] {255, 0, 0, -2147483648});
					this->xvidBframeThreshold->Name = "xvidBframeThreshold";
					this->xvidBframeThreshold->Size = new System::Drawing::Size(48, 20);
					this->xvidBframeThreshold->TabIndex = 1;
					this->xvidBframeThreshold->ValueChanged += new System::EventHandler(this, &xvidConfigurationPanel::updateEvent);
					// 
					// xvidRCGroupbox
					// 
					this->xvidRCGroupbox->Controls->Add(this->xvidLowBitrateImprovement);
					this->xvidRCGroupbox->Controls->Add(this->xvidHighBitrateDegradation);
					this->xvidRCGroupbox->Controls->Add(this->xvidLowBitrateImprovementLabel);
					this->xvidRCGroupbox->Controls->Add(this->xvidHighBitrateDegradationLabel);
					this->xvidRCGroupbox->Controls->Add(this->xvidMaxOverflowDegradation);
					this->xvidRCGroupbox->Controls->Add(this->xvidMaxOverflowImprovement);
					this->xvidRCGroupbox->Controls->Add(this->xvidOverflowControlStrength);
					this->xvidRCGroupbox->Controls->Add(this->xvidMaxOverflowDegradationLabel);
					this->xvidRCGroupbox->Controls->Add(this->xvidMaxOverflowImprovementLabel);
					this->xvidRCGroupbox->Controls->Add(this->xvidOverflowControlStrengthLabel);
					this->xvidRCGroupbox->Controls->Add(this->xvidKeyframeReduction);
					this->xvidRCGroupbox->Controls->Add(this->xvidKeyframeTreshold);
					this->xvidRCGroupbox->Controls->Add(this->xvidIframeBoost);
					this->xvidRCGroupbox->Controls->Add(this->xvidKeyframeReductionLabel);
					this->xvidRCGroupbox->Controls->Add(this->xvidKeyframeTresholdLabel);
					this->xvidRCGroupbox->Controls->Add(this->xvidIframeBoostLabel);
					this->xvidRCGroupbox->Location = new System::Drawing::Point(0, 150);
					this->xvidRCGroupbox->Name = "xvidRCGroupbox";
					this->xvidRCGroupbox->Size = new System::Drawing::Size(280, 232);
					this->xvidRCGroupbox->TabIndex = 1;
					this->xvidRCGroupbox->TabStop = false;
					this->xvidRCGroupbox->Text = "Rate Control";
					// 
					// xvidLowBitrateImprovement
					// 
					this->xvidLowBitrateImprovement->Location = new System::Drawing::Point(208, 208);
					this->xvidLowBitrateImprovement->Name = "xvidLowBitrateImprovement";
					this->xvidLowBitrateImprovement->Size = new System::Drawing::Size(56, 20);
					this->xvidLowBitrateImprovement->TabIndex = 15;
					this->xvidLowBitrateImprovement->ValueChanged += new System::EventHandler(this, &xvidConfigurationPanel::updateEvent);
					// 
					// xvidHighBitrateDegradation
					// 
					this->xvidHighBitrateDegradation->Location = new System::Drawing::Point(208, 184);
					this->xvidHighBitrateDegradation->Name = "xvidHighBitrateDegradation";
					this->xvidHighBitrateDegradation->Size = new System::Drawing::Size(56, 20);
					this->xvidHighBitrateDegradation->TabIndex = 13;
					this->xvidHighBitrateDegradation->ValueChanged += new System::EventHandler(this, &xvidConfigurationPanel::updateEvent);
					// 
					// xvidLowBitrateImprovementLabel
					// 
					this->xvidLowBitrateImprovementLabel->Location = new System::Drawing::Point(8, 208);
					this->xvidLowBitrateImprovementLabel->Name = "xvidLowBitrateImprovementLabel";
					this->xvidLowBitrateImprovementLabel->Size = new System::Drawing::Size(200, 16);
					this->xvidLowBitrateImprovementLabel->TabIndex = 14;
					this->xvidLowBitrateImprovementLabel->Text = "Low bitrate scenes improvement (%)";
					// 
					// xvidHighBitrateDegradationLabel
					// 
					this->xvidHighBitrateDegradationLabel->Location = new System::Drawing::Point(8, 184);
					this->xvidHighBitrateDegradationLabel->Name = "xvidHighBitrateDegradationLabel";
					this->xvidHighBitrateDegradationLabel->Size = new System::Drawing::Size(200, 16);
					this->xvidHighBitrateDegradationLabel->TabIndex = 12;
					this->xvidHighBitrateDegradationLabel->Text = "High bitrate scenes degradation (%)";
					// 
					// xvidMaxOverflowDegradation
					// 
					this->xvidMaxOverflowDegradation->Location = new System::Drawing::Point(208, 149);
					this->xvidMaxOverflowDegradation->Name = "xvidMaxOverflowDegradation";
					this->xvidMaxOverflowDegradation->Size = new System::Drawing::Size(56, 20);
					this->xvidMaxOverflowDegradation->TabIndex = 11;
					this->xvidMaxOverflowDegradation->Value = decimal(new int[4] {5, 0, 0, 0});
					this->xvidMaxOverflowDegradation->ValueChanged += new System::EventHandler(this, &xvidConfigurationPanel::updateEvent);
					// 
					// xvidMaxOverflowImprovement
					// 
					this->xvidMaxOverflowImprovement->Location = new System::Drawing::Point(208, 125);
					this->xvidMaxOverflowImprovement->Name = "xvidMaxOverflowImprovement";
					this->xvidMaxOverflowImprovement->Size = new System::Drawing::Size(56, 20);
					this->xvidMaxOverflowImprovement->TabIndex = 9;
					this->xvidMaxOverflowImprovement->Value = decimal(new int[4] {5, 0, 0, 0});
					this->xvidMaxOverflowImprovement->ValueChanged += new System::EventHandler(this, &xvidConfigurationPanel::updateEvent);
					// 
					// xvidOverflowControlStrength
					// 
					this->xvidOverflowControlStrength->Location = new System::Drawing::Point(208, 101);
					this->xvidOverflowControlStrength->Name = "xvidOverflowControlStrength";
					this->xvidOverflowControlStrength->Size = new System::Drawing::Size(56, 20);
					this->xvidOverflowControlStrength->TabIndex = 7;
					this->xvidOverflowControlStrength->Value = decimal(new int[4] {5, 0, 0, 0});
					this->xvidOverflowControlStrength->ValueChanged += new System::EventHandler(this, &xvidConfigurationPanel::updateEvent);
					// 
					// xvidMaxOverflowDegradationLabel
					// 
					this->xvidMaxOverflowDegradationLabel->Location = new System::Drawing::Point(8, 149);
					this->xvidMaxOverflowDegradationLabel->Name = "xvidMaxOverflowDegradationLabel";
					this->xvidMaxOverflowDegradationLabel->Size = new System::Drawing::Size(160, 23);
					this->xvidMaxOverflowDegradationLabel->TabIndex = 10;
					this->xvidMaxOverflowDegradationLabel->Text = "Max overflow degradation (%)";
					// 
					// xvidMaxOverflowImprovementLabel
					// 
					this->xvidMaxOverflowImprovementLabel->Location = new System::Drawing::Point(8, 125);
					this->xvidMaxOverflowImprovementLabel->Name = "xvidMaxOverflowImprovementLabel";
					this->xvidMaxOverflowImprovementLabel->Size = new System::Drawing::Size(168, 23);
					this->xvidMaxOverflowImprovementLabel->TabIndex = 8;
					this->xvidMaxOverflowImprovementLabel->Text = "Max overflow improvement (%)";
					// 
					// xvidOverflowControlStrengthLabel
					// 
					this->xvidOverflowControlStrengthLabel->Location = new System::Drawing::Point(8, 101);
					this->xvidOverflowControlStrengthLabel->Name = "xvidOverflowControlStrengthLabel";
					this->xvidOverflowControlStrengthLabel->Size = new System::Drawing::Size(168, 23);
					this->xvidOverflowControlStrengthLabel->TabIndex = 6;
					this->xvidOverflowControlStrengthLabel->Text = "Overflow control strength (%)";
					// 
					// xvidKeyframeReduction
					// 
					this->xvidKeyframeReduction->Location = new System::Drawing::Point(208, 64);
					this->xvidKeyframeReduction->Name = "xvidKeyframeReduction";
					this->xvidKeyframeReduction->Size = new System::Drawing::Size(56, 20);
					this->xvidKeyframeReduction->TabIndex = 5;
					this->xvidKeyframeReduction->Value = decimal(new int[4] {20, 0, 0, 0});
					this->xvidKeyframeReduction->ValueChanged += new System::EventHandler(this, &xvidConfigurationPanel::updateEvent);
					// 
					// xvidKeyframeTreshold
					// 
					this->xvidKeyframeTreshold->Location = new System::Drawing::Point(208, 40);
					this->xvidKeyframeTreshold->Name = "xvidKeyframeTreshold";
					this->xvidKeyframeTreshold->Size = new System::Drawing::Size(56, 20);
					this->xvidKeyframeTreshold->TabIndex = 3;
					this->xvidKeyframeTreshold->Text = "1";
					this->xvidKeyframeTreshold->TextChanged += new System::EventHandler(this, &xvidConfigurationPanel::updateEvent);
					this->xvidKeyframeTreshold->KeyPress += new System::Windows::Forms::KeyPressEventHandler(this, &xvidConfigurationPanel::textField_KeyPress);
					// 
					// xvidIframeBoost
					// 
					this->xvidIframeBoost->Location = new System::Drawing::Point(208, 16);
					this->xvidIframeBoost->Maximum = decimal(new int[4] {1000, 0, 0, 0});
					this->xvidIframeBoost->Name = "xvidIframeBoost";
					this->xvidIframeBoost->Size = new System::Drawing::Size(56, 20);
					this->xvidIframeBoost->TabIndex = 1;
					this->xvidIframeBoost->Value = decimal(new int[4] {100, 0, 0, 0});
					this->xvidIframeBoost->ValueChanged += new System::EventHandler(this, &xvidConfigurationPanel::updateEvent);
					// 
					// xvidKeyframeReductionLabel
					// 
					this->xvidKeyframeReductionLabel->Location = new System::Drawing::Point(8, 72);
					this->xvidKeyframeReductionLabel->Name = "xvidKeyframeReductionLabel";
					this->xvidKeyframeReductionLabel->Size = new System::Drawing::Size(120, 23);
					this->xvidKeyframeReductionLabel->TabIndex = 4;
					this->xvidKeyframeReductionLabel->Text = "... are reduced by (%)";
					// 
					// xvidKeyframeTresholdLabel
					// 
					this->xvidKeyframeTresholdLabel->Location = new System::Drawing::Point(8, 48);
					this->xvidKeyframeTresholdLabel->Name = "xvidKeyframeTresholdLabel";
					this->xvidKeyframeTresholdLabel->Size = new System::Drawing::Size(168, 23);
					this->xvidKeyframeTresholdLabel->TabIndex = 2;
					this->xvidKeyframeTresholdLabel->Text = "I-frames closer than ... (frames)";
					// 
					// xvidIframeBoostLabel
					// 
					this->xvidIframeBoostLabel->Location = new System::Drawing::Point(8, 24);
					this->xvidIframeBoostLabel->Name = "xvidIframeBoostLabel";
					this->xvidIframeBoostLabel->Size = new System::Drawing::Size(128, 23);
					this->xvidIframeBoostLabel->TabIndex = 0;
					this->xvidIframeBoostLabel->Text = "I-frame boost (10x %)";
					// 
					// xvidQuantizerGroupbox
					// 
					this->xvidQuantizerGroupbox->Controls->Add(this->xvidCreditsQuantizer);
					this->xvidQuantizerGroupbox->Controls->Add(this->xvidCreditsQuantizerLabel);
					this->xvidQuantizerGroupbox->Controls->Add(this->xvidBframeQuantOffset);
					this->xvidQuantizerGroupbox->Controls->Add(this->xvidBframeQuantRatio);
					this->xvidQuantizerGroupbox->Controls->Add(this->xvidBframeQuantOffsetLabel);
					this->xvidQuantizerGroupbox->Controls->Add(this->xvidBframeQuantRatioLabel);
					this->xvidQuantizerGroupbox->Controls->Add(this->xvidMaxBQuant);
					this->xvidQuantizerGroupbox->Controls->Add(this->xvidMinBQuant);
					this->xvidQuantizerGroupbox->Controls->Add(this->xvidMinPQuant);
					this->xvidQuantizerGroupbox->Controls->Add(this->xvidMaxPQuant);
					this->xvidQuantizerGroupbox->Controls->Add(this->xvidMaxBQuantLabel);
					this->xvidQuantizerGroupbox->Controls->Add(this->xvidMinBQuantLabel);
					this->xvidQuantizerGroupbox->Controls->Add(this->xvidMaxPQuantLabel);
					this->xvidQuantizerGroupbox->Controls->Add(this->xvidMinPQuantLabel);
					this->xvidQuantizerGroupbox->Controls->Add(this->xvidMaxIQuant);
					this->xvidQuantizerGroupbox->Controls->Add(this->xvidMinIQuant);
					this->xvidQuantizerGroupbox->Controls->Add(this->xvidMaxIQuantLabel);
					this->xvidQuantizerGroupbox->Controls->Add(this->xvidMinIQuantLabel);
					this->xvidQuantizerGroupbox->Location = new System::Drawing::Point(0, 3);
					this->xvidQuantizerGroupbox->Name = "xvidQuantizerGroupbox";
					this->xvidQuantizerGroupbox->Size = new System::Drawing::Size(489, 144);
					this->xvidQuantizerGroupbox->TabIndex = 0;
					this->xvidQuantizerGroupbox->TabStop = false;
					this->xvidQuantizerGroupbox->Text = "Quantizers";
					// 
					// xvidCreditsQuantizer
					// 
					this->xvidCreditsQuantizer->Location = new System::Drawing::Point(144, 88);
					this->xvidCreditsQuantizer->Maximum = decimal(new int[4] {32, 0, 0, 0});
					this->xvidCreditsQuantizer->Minimum = decimal(new int[4] {1, 0, 0, 0});
					this->xvidCreditsQuantizer->Name = "xvidCreditsQuantizer";
					this->xvidCreditsQuantizer->Size = new System::Drawing::Size(40, 20);
					this->xvidCreditsQuantizer->TabIndex = 7;
					this->xvidCreditsQuantizer->Value = decimal(new int[4] {20, 0, 0, 0});
					this->xvidCreditsQuantizer->ValueChanged += new System::EventHandler(this, &xvidConfigurationPanel::updateEvent);
					// 
					// xvidCreditsQuantizerLabel
					// 
					this->xvidCreditsQuantizerLabel->Location = new System::Drawing::Point(8, 88);
					this->xvidCreditsQuantizerLabel->Name = "xvidCreditsQuantizerLabel";
					this->xvidCreditsQuantizerLabel->Size = new System::Drawing::Size(100, 23);
					this->xvidCreditsQuantizerLabel->TabIndex = 6;
					this->xvidCreditsQuantizerLabel->Text = "Credits Quantizer";
					// 
					// xvidBframeQuantOffset
					// 
					this->xvidBframeQuantOffset->Increment = decimal(new int[4] {100, 0, 0, 0});
					this->xvidBframeQuantOffset->Location = new System::Drawing::Point(428, 112);
					this->xvidBframeQuantOffset->Maximum = decimal(new int[4] {1000, 0, 0, 0});
					this->xvidBframeQuantOffset->Minimum = decimal(new int[4] {1000, 0, 0, -2147483648});
					this->xvidBframeQuantOffset->Name = "xvidBframeQuantOffset";
					this->xvidBframeQuantOffset->Size = new System::Drawing::Size(48, 20);
					this->xvidBframeQuantOffset->TabIndex = 17;
					this->xvidBframeQuantOffset->Value = decimal(new int[4] {100, 0, 0, 0});
					this->xvidBframeQuantOffset->ValueChanged += new System::EventHandler(this, &xvidConfigurationPanel::updateEvent);
					// 
					// xvidBframeQuantRatio
					// 
					this->xvidBframeQuantRatio->Increment = decimal(new int[4] {10, 0, 0, 0});
					this->xvidBframeQuantRatio->Location = new System::Drawing::Point(136, 112);
					this->xvidBframeQuantRatio->Maximum = decimal(new int[4] {1000, 0, 0, 0});
					this->xvidBframeQuantRatio->Name = "xvidBframeQuantRatio";
					this->xvidBframeQuantRatio->Size = new System::Drawing::Size(48, 20);
					this->xvidBframeQuantRatio->TabIndex = 9;
					this->xvidBframeQuantRatio->Value = decimal(new int[4] {150, 0, 0, 0});
					this->xvidBframeQuantRatio->ValueChanged += new System::EventHandler(this, &xvidConfigurationPanel::updateEvent);
					// 
					// xvidBframeQuantOffsetLabel
					// 
					this->xvidBframeQuantOffsetLabel->Location = new System::Drawing::Point(301, 112);
					this->xvidBframeQuantOffsetLabel->Name = "xvidBframeQuantOffsetLabel";
					this->xvidBframeQuantOffsetLabel->Size = new System::Drawing::Size(120, 23);
					this->xvidBframeQuantOffsetLabel->TabIndex = 16;
					this->xvidBframeQuantOffsetLabel->Text = "B-frame Quant offset";
					// 
					// xvidBframeQuantRatioLabel
					// 
					this->xvidBframeQuantRatioLabel->Location = new System::Drawing::Point(8, 112);
					this->xvidBframeQuantRatioLabel->Name = "xvidBframeQuantRatioLabel";
					this->xvidBframeQuantRatioLabel->Size = new System::Drawing::Size(128, 23);
					this->xvidBframeQuantRatioLabel->TabIndex = 8;
					this->xvidBframeQuantRatioLabel->Text = "B-frame Quantizer Ratio";
					// 
					// xvidMaxBQuant
					// 
					this->xvidMaxBQuant->Location = new System::Drawing::Point(436, 64);
					this->xvidMaxBQuant->Maximum = decimal(new int[4] {31, 0, 0, 0});
					this->xvidMaxBQuant->Name = "xvidMaxBQuant";
					this->xvidMaxBQuant->Size = new System::Drawing::Size(40, 20);
					this->xvidMaxBQuant->TabIndex = 15;
					this->xvidMaxBQuant->Value = decimal(new int[4] {31, 0, 0, 0});
					this->xvidMaxBQuant->ValueChanged += new System::EventHandler(this, &xvidConfigurationPanel::updateEvent);
					// 
					// xvidMinBQuant
					// 
					this->xvidMinBQuant->Location = new System::Drawing::Point(144, 64);
					this->xvidMinBQuant->Maximum = decimal(new int[4] {31, 0, 0, 0});
					this->xvidMinBQuant->Name = "xvidMinBQuant";
					this->xvidMinBQuant->Size = new System::Drawing::Size(40, 20);
					this->xvidMinBQuant->TabIndex = 5;
					this->xvidMinBQuant->Value = decimal(new int[4] {2, 0, 0, 0});
					this->xvidMinBQuant->ValueChanged += new System::EventHandler(this, &xvidConfigurationPanel::updateEvent);
					// 
					// xvidMinPQuant
					// 
					this->xvidMinPQuant->Location = new System::Drawing::Point(144, 40);
					this->xvidMinPQuant->Maximum = decimal(new int[4] {31, 0, 0, 0});
					this->xvidMinPQuant->Name = "xvidMinPQuant";
					this->xvidMinPQuant->Size = new System::Drawing::Size(40, 20);
					this->xvidMinPQuant->TabIndex = 3;
					this->xvidMinPQuant->Value = decimal(new int[4] {2, 0, 0, 0});
					this->xvidMinPQuant->ValueChanged += new System::EventHandler(this, &xvidConfigurationPanel::updateEvent);
					// 
					// xvidMaxPQuant
					// 
					this->xvidMaxPQuant->Location = new System::Drawing::Point(436, 40);
					this->xvidMaxPQuant->Maximum = decimal(new int[4] {31, 0, 0, 0});
					this->xvidMaxPQuant->Name = "xvidMaxPQuant";
					this->xvidMaxPQuant->Size = new System::Drawing::Size(40, 20);
					this->xvidMaxPQuant->TabIndex = 13;
					this->xvidMaxPQuant->Value = decimal(new int[4] {31, 0, 0, 0});
					this->xvidMaxPQuant->ValueChanged += new System::EventHandler(this, &xvidConfigurationPanel::updateEvent);
					// 
					// xvidMaxBQuantLabel
					// 
					this->xvidMaxBQuantLabel->Location = new System::Drawing::Point(301, 66);
					this->xvidMaxBQuantLabel->Name = "xvidMaxBQuantLabel";
					this->xvidMaxBQuantLabel->Size = new System::Drawing::Size(136, 16);
					this->xvidMaxBQuantLabel->TabIndex = 14;
					this->xvidMaxBQuantLabel->Text = "Max B-frame Quantizer";
					// 
					// xvidMinBQuantLabel
					// 
					this->xvidMinBQuantLabel->Location = new System::Drawing::Point(8, 64);
					this->xvidMinBQuantLabel->Name = "xvidMinBQuantLabel";
					this->xvidMinBQuantLabel->Size = new System::Drawing::Size(120, 23);
					this->xvidMinBQuantLabel->TabIndex = 4;
					this->xvidMinBQuantLabel->Text = "Min B-frame Quantizer";
					// 
					// xvidMaxPQuantLabel
					// 
					this->xvidMaxPQuantLabel->Location = new System::Drawing::Point(301, 42);
					this->xvidMaxPQuantLabel->Name = "xvidMaxPQuantLabel";
					this->xvidMaxPQuantLabel->Size = new System::Drawing::Size(128, 23);
					this->xvidMaxPQuantLabel->TabIndex = 12;
					this->xvidMaxPQuantLabel->Text = "Max P-frame Quantizer";
					// 
					// xvidMinPQuantLabel
					// 
					this->xvidMinPQuantLabel->Location = new System::Drawing::Point(8, 40);
					this->xvidMinPQuantLabel->Name = "xvidMinPQuantLabel";
					this->xvidMinPQuantLabel->Size = new System::Drawing::Size(120, 23);
					this->xvidMinPQuantLabel->TabIndex = 2;
					this->xvidMinPQuantLabel->Text = "Min P-frame Quantizer";
					// 
					// xvidMaxIQuant
					// 
					this->xvidMaxIQuant->Location = new System::Drawing::Point(436, 16);
					this->xvidMaxIQuant->Maximum = decimal(new int[4] {31, 0, 0, 0});
					this->xvidMaxIQuant->Name = "xvidMaxIQuant";
					this->xvidMaxIQuant->Size = new System::Drawing::Size(40, 20);
					this->xvidMaxIQuant->TabIndex = 11;
					this->xvidMaxIQuant->Value = decimal(new int[4] {31, 0, 0, 0});
					this->xvidMaxIQuant->ValueChanged += new System::EventHandler(this, &xvidConfigurationPanel::updateEvent);
					// 
					// xvidMinIQuant
					// 
					this->xvidMinIQuant->Location = new System::Drawing::Point(144, 16);
					this->xvidMinIQuant->Maximum = decimal(new int[4] {31, 0, 0, 0});
					this->xvidMinIQuant->Name = "xvidMinIQuant";
					this->xvidMinIQuant->Size = new System::Drawing::Size(40, 20);
					this->xvidMinIQuant->TabIndex = 1;
					this->xvidMinIQuant->Value = decimal(new int[4] {2, 0, 0, 0});
					this->xvidMinIQuant->ValueChanged += new System::EventHandler(this, &xvidConfigurationPanel::updateEvent);
					// 
					// xvidMaxIQuantLabel
					// 
					this->xvidMaxIQuantLabel->Location = new System::Drawing::Point(301, 18);
					this->xvidMaxIQuantLabel->Name = "xvidMaxIQuantLabel";
					this->xvidMaxIQuantLabel->Size = new System::Drawing::Size(120, 23);
					this->xvidMaxIQuantLabel->TabIndex = 10;
					this->xvidMaxIQuantLabel->Text = "Max I-frame Quantizer";
					// 
					// xvidMinIQuantLabel
					// 
					this->xvidMinIQuantLabel->Location = new System::Drawing::Point(8, 16);
					this->xvidMinIQuantLabel->Name = "xvidMinIQuantLabel";
					this->xvidMinIQuantLabel->Size = new System::Drawing::Size(120, 23);
					this->xvidMinIQuantLabel->TabIndex = 0;
					this->xvidMinIQuantLabel->Text = "Min I-frame Quantizer";
					// 
					// xvidCBRRcGroupBox
					// 
					this->xvidCBRRcGroupBox->Controls->Add(this->xvidRCBufferSize);
					this->xvidCBRRcGroupBox->Controls->Add(this->xvidRCBufferSizeLabel);
					this->xvidCBRRcGroupBox->Controls->Add(this->xvidRCAveragingPeriodLabel);
					this->xvidCBRRcGroupBox->Controls->Add(this->xvidRCAveragingPeriod);
					this->xvidCBRRcGroupBox->Controls->Add(this->xvidRCDelayFactorLabel);
					this->xvidCBRRcGroupBox->Controls->Add(this->xvidRCDelayFactor);
					this->xvidCBRRcGroupBox->Location = new System::Drawing::Point(289, 150);
					this->xvidCBRRcGroupBox->Name = "xvidCBRRcGroupBox";
					this->xvidCBRRcGroupBox->Size = new System::Drawing::Size(200, 90);
					this->xvidCBRRcGroupBox->TabIndex = 2;
					this->xvidCBRRcGroupBox->TabStop = false;
					this->xvidCBRRcGroupBox->Text = "CBR RC";
					// 
					// xvidRCBufferSize
					// 
					this->xvidRCBufferSize->Location = new System::Drawing::Point(139, 64);
					this->xvidRCBufferSize->MaxLength = 9;
					this->xvidRCBufferSize->Name = "xvidRCBufferSize";
					this->xvidRCBufferSize->Size = new System::Drawing::Size(48, 20);
					this->xvidRCBufferSize->TabIndex = 5;
					this->xvidRCBufferSize->TextChanged += new System::EventHandler(this, &xvidConfigurationPanel::updateEvent);
					this->xvidRCBufferSize->KeyPress += new System::Windows::Forms::KeyPressEventHandler(this, &xvidConfigurationPanel::textField_KeyPress);
					// 
					// xvidRCBufferSizeLabel
					// 
					this->xvidRCBufferSizeLabel->Location = new System::Drawing::Point(12, 64);
					this->xvidRCBufferSizeLabel->Name = "xvidRCBufferSizeLabel";
					this->xvidRCBufferSizeLabel->Size = new System::Drawing::Size(100, 23);
					this->xvidRCBufferSizeLabel->TabIndex = 4;
					this->xvidRCBufferSizeLabel->Text = "RC Buffer Size";
					// 
					// xvidRCAveragingPeriodLabel
					// 
					this->xvidRCAveragingPeriodLabel->Location = new System::Drawing::Point(12, 40);
					this->xvidRCAveragingPeriodLabel->Name = "xvidRCAveragingPeriodLabel";
					this->xvidRCAveragingPeriodLabel->Size = new System::Drawing::Size(100, 23);
					this->xvidRCAveragingPeriodLabel->TabIndex = 2;
					this->xvidRCAveragingPeriodLabel->Text = "Averaging period";
					// 
					// xvidRCAveragingPeriod
					// 
					this->xvidRCAveragingPeriod->Location = new System::Drawing::Point(139, 40);
					this->xvidRCAveragingPeriod->Name = "xvidRCAveragingPeriod";
					this->xvidRCAveragingPeriod->Size = new System::Drawing::Size(48, 20);
					this->xvidRCAveragingPeriod->TabIndex = 3;
					this->xvidRCAveragingPeriod->Text = "100";
					this->xvidRCAveragingPeriod->TextChanged += new System::EventHandler(this, &xvidConfigurationPanel::updateEvent);
					this->xvidRCAveragingPeriod->KeyPress += new System::Windows::Forms::KeyPressEventHandler(this, &xvidConfigurationPanel::textField_KeyPress);
					// 
					// xvidRCDelayFactorLabel
					// 
					this->xvidRCDelayFactorLabel->Location = new System::Drawing::Point(12, 16);
					this->xvidRCDelayFactorLabel->Name = "xvidRCDelayFactorLabel";
					this->xvidRCDelayFactorLabel->Size = new System::Drawing::Size(120, 23);
					this->xvidRCDelayFactorLabel->TabIndex = 0;
					this->xvidRCDelayFactorLabel->Text = "Reaction Delay Factor";
					// 
					// xvidRCDelayFactor
					// 
					this->xvidRCDelayFactor->Location = new System::Drawing::Point(139, 16);
					this->xvidRCDelayFactor->Name = "xvidRCDelayFactor";
					this->xvidRCDelayFactor->Size = new System::Drawing::Size(48, 20);
					this->xvidRCDelayFactor->TabIndex = 1;
					this->xvidRCDelayFactor->Text = "16";
					this->xvidRCDelayFactor->TextChanged += new System::EventHandler(this, &xvidConfigurationPanel::updateEvent);
					this->xvidRCDelayFactor->KeyPress += new System::Windows::Forms::KeyPressEventHandler(this, &xvidConfigurationPanel::textField_KeyPress);
					// 
					// openFileDialog
					// 
					this->openFileDialog->FileName = "openFileDialog1";
					// 
					// advancedTabPage
					// 
					this->advancedTabPage->Controls->Add(this->gbx264CustomCmd);
					this->advancedTabPage->Controls->Add(this->xvidOtherOptionsGroupbox);
					this->advancedTabPage->Controls->Add(this->xvidRCGroupbox);
					this->advancedTabPage->Controls->Add(this->xvidQuantizerGroupbox);
					this->advancedTabPage->Controls->Add(this->xvidCBRRcGroupBox);
					this->advancedTabPage->Location = new System::Drawing::Point(4, 22);
					this->advancedTabPage->Name = "advancedTabPage";
					this->advancedTabPage->Size = new System::Drawing::Size(492, 432);
					this->advancedTabPage->TabIndex = 3;
					this->advancedTabPage->Text = "Advanced";
					this->advancedTabPage->UseVisualStyleBackColor = true;
					// 
					// gbx264CustomCmd
					// 
					this->gbx264CustomCmd->Controls->Add(this->customCommandlineOptions);
					this->gbx264CustomCmd->Location = new System::Drawing::Point(0, 384);
					this->gbx264CustomCmd->Name = "gbx264CustomCmd";
					this->gbx264CustomCmd->Size = new System::Drawing::Size(489, 45);
					this->gbx264CustomCmd->TabIndex = 9;
					this->gbx264CustomCmd->TabStop = false;
					this->gbx264CustomCmd->Text = "Custom Command Line";
					// 
					// customCommandlineOptions
					// 
					this->customCommandlineOptions->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
					this->customCommandlineOptions->Location = new System::Drawing::Point(10, 16);
					this->customCommandlineOptions->Name = "customCommandlineOptions";
					this->customCommandlineOptions->Size = new System::Drawing::Size(466, 20);
					this->customCommandlineOptions->TabIndex = 0;
					this->customCommandlineOptions->TextChanged += new System::EventHandler(this, &xvidConfigurationPanel::updateEvent);
					// 
					// xvidCustomCommandlineOptionsLabel
					// 
					this->xvidCustomCommandlineOptionsLabel->Location = new System::Drawing::Point(10, 19);
					this->xvidCustomCommandlineOptionsLabel->Name = "xvidCustomCommandlineOptionsLabel";
					this->xvidCustomCommandlineOptionsLabel->Size = new System::Drawing::Size(162, 23);
					this->xvidCustomCommandlineOptionsLabel->TabIndex = 3;
					this->xvidCustomCommandlineOptionsLabel->Text = "Custom Commandline Options";
					// 
					// xvidCustomCommandlineOptions
					// 
					this->xvidCustomCommandlineOptions->Location = new System::Drawing::Point(178, 19);
					this->xvidCustomCommandlineOptions->Name = "xvidCustomCommandlineOptions";
					this->xvidCustomCommandlineOptions->Size = new System::Drawing::Size(264, 20);
					this->xvidCustomCommandlineOptions->TabIndex = 4;
					this->xvidCustomCommandlineOptions->TextChanged += new System::EventHandler(this, &xvidConfigurationPanel::updateEvent);
					// 
					// quantizerMatrixGroupbox
					// 
					this->quantizerMatrixGroupbox->Controls->Add(this->xvidCustomCommandlineOptions);
					this->quantizerMatrixGroupbox->Controls->Add(this->xvidCustomCommandlineOptionsLabel);
					this->quantizerMatrixGroupbox->Location = new System::Drawing::Point(9, 295);
					this->quantizerMatrixGroupbox->Name = "quantizerMatrixGroupbox";
					this->quantizerMatrixGroupbox->Size = new System::Drawing::Size(480, 54);
					this->quantizerMatrixGroupbox->TabIndex = 17;
					this->quantizerMatrixGroupbox->TabStop = false;
					this->quantizerMatrixGroupbox->Text = "Other Options";
					// 
					// xvidConfigurationPanel
					// 
					this->AutoScaleDimensions = new System::Drawing::SizeF(6, 13);
					this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
					this->Name = "xvidConfigurationPanel";
					this->Size = new System::Drawing::Size(503, 526);
					this->tabControl1->ResumeLayout(false);
					this->mainTabPage->ResumeLayout(false);
					this->xvidOtherGroupBox->ResumeLayout(false);
					this->xvidOtherGroupBox->PerformLayout();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->xvidNbBFrames))->EndInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->nbThreads))->EndInit();
					this->xvidCodecToolsGroupBox->ResumeLayout(false);
					this->xvidCodecToolsGroupBox->PerformLayout();
					this->xvidGeneralOptionsGroupBox->ResumeLayout(false);
					this->xvidGeneralOptionsGroupBox->PerformLayout();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->xvidBitrateQuantizer))->EndInit();
					this->xvidOtherOptionsGroupbox->ResumeLayout(false);
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->xvidFrameDropRatio))->EndInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->xvidBframeThreshold))->EndInit();
					this->xvidRCGroupbox->ResumeLayout(false);
					this->xvidRCGroupbox->PerformLayout();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->xvidLowBitrateImprovement))->EndInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->xvidHighBitrateDegradation))->EndInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->xvidMaxOverflowDegradation))->EndInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->xvidMaxOverflowImprovement))->EndInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->xvidOverflowControlStrength))->EndInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->xvidKeyframeReduction))->EndInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->xvidIframeBoost))->EndInit();
					this->xvidQuantizerGroupbox->ResumeLayout(false);
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->xvidCreditsQuantizer))->EndInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->xvidBframeQuantOffset))->EndInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->xvidBframeQuantRatio))->EndInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->xvidMaxBQuant))->EndInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->xvidMinBQuant))->EndInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->xvidMinPQuant))->EndInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->xvidMaxPQuant))->EndInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->xvidMaxIQuant))->EndInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->xvidMinIQuant))->EndInit();
					this->xvidCBRRcGroupBox->ResumeLayout(false);
					this->xvidCBRRcGroupBox->PerformLayout();
					this->advancedTabPage->ResumeLayout(false);
					this->gbx264CustomCmd->ResumeLayout(false);
					this->gbx264CustomCmd->PerformLayout();
					this->quantizerMatrixGroupbox->ResumeLayout(false);
					this->quantizerMatrixGroupbox->PerformLayout();
					this->ResumeLayout(false);
					this->PerformLayout();

				}

				void xvidConfigurationPanel::InitializeInstanceFields()
				{
					delete components;
				}
			}
		}
	}
}
