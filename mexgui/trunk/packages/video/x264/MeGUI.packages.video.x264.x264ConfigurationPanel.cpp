#include "MeGUI.packages.video.x264.x264ConfigurationPanel.h"

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
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Xml;
using namespace MeGUI::core::details::video;
using namespace MeGUI::core::gui;
using namespace MeGUI::core::plugins::interfaces;
namespace MeGUI
{
	namespace packages
	{
		namespace video
		{
			namespace x264
			{

				x264ConfigurationPanel::x264ConfigurationPanel() : MeGUI::core::details::video::VideoConfigurationPanel()
				{
					InitializeInstanceFields();
					InitializeComponent();
					cqmComboBox1->setStandardItems(new std::string[] {"Flat (none)", "JVT"});
					cqmComboBox1->setSelectedIndex(0);
					this->setAdvancedToolTips(MainForm::Instance->getSettings()->getUseAdvancedTooltips());
					AVCLevels *al = new AVCLevels();
					this->avcLevel->Items->AddRange(EnumProxy::CreateArray(AVCLevels::SupportedLevels));
					this->avcLevel->SelectedItem = EnumProxy::Create(AVCLevels::L_UNRESTRICTED);
					x264DeviceList = x264Device::CreateDeviceList();
					for (std::vector<x264Device*>::const_iterator oDevice = x264DeviceList.begin(); oDevice != x264DeviceList.end(); ++oDevice)
						this->targetDevice->Items->Add((*oDevice)->getName());
					oTargetDevice = x264DeviceList[0];
					x264Tunes->Items->AddRange(EnumProxy::CreateArray(x264Settings::SupportedPsyTuningModes));
					x264Tunes->SelectedItem = EnumProxy::Create(x264Settings::NONE);
				}

				void x264ConfigurationPanel::doCheckBoxAdjustments()
				{
					x264AlphaDeblock->Enabled = x264DeblockActive->Checked;
					x264BetaDeblock->Enabled = x264DeblockActive->Checked;
					fakeInterlaced->Enabled = cbInterlaceMode->SelectedIndex == 0;
				}

				void x264ConfigurationPanel::doDeviceSpecificAdjustments()
				{
					// AVC profile
					if (oTargetDevice->getProfile() > -1)
					{
						if (avcProfile->SelectedIndex > oTargetDevice->getProfile())
							avcProfile->SelectedIndex = oTargetDevice->getProfile();
						else if (updateDevice == true && avcProfile->SelectedIndex < oTargetDevice->getProfile())
							avcProfile->SelectedIndex = oTargetDevice->getProfile();
					}
					else if (updateDevice == true)
						avcProfile->SelectedIndex = 2;

					// AVC level
					if (getAVCLevel().compare(oTargetDevice->getAVCLevel()) > 0)
						avcLevel->SelectedItem = EnumProxy::Create(oTargetDevice->getAVCLevel());
					else if (updateDevice == true && getAVCLevel().compare(oTargetDevice->getAVCLevel()) < 0)
						avcLevel->SelectedItem = EnumProxy::Create(oTargetDevice->getAVCLevel());

					// VBVBufsize
					if (oTargetDevice->getVBVBufsize() > -1)
					{
						if (x264VBVBufferSize->Value == 0 || x264VBVBufferSize->Value > oTargetDevice->getVBVBufsize())
							x264VBVBufferSize->Value = oTargetDevice->getVBVBufsize();
						else if (updateDevice == true && x264VBVBufferSize->Value < oTargetDevice->getVBVBufsize())
							x264VBVBufferSize->Value = oTargetDevice->getVBVBufsize();
					}
					else if (updateDevice == true)
					{
						if (getAVCLevel() == AVCLevels::L_UNRESTRICTED)
							x264VBVBufferSize->Value = 0;
						else
							x264VBVBufferSize->Value = (new AVCLevels())->getMaxCBP(getAVCLevel(), avcProfile->SelectedIndex == 2);
					}

					// VBVMaxrate
					if (oTargetDevice->getVBVMaxrate() > -1)
					{
						if (x264VBVMaxRate->Value == 0 || x264VBVMaxRate->Value > oTargetDevice->getVBVMaxrate())
							x264VBVMaxRate->Value = oTargetDevice->getVBVMaxrate();
						else if (updateDevice == true && x264VBVMaxRate->Value < oTargetDevice->getVBVMaxrate())
							x264VBVMaxRate->Value = oTargetDevice->getVBVMaxrate();
					}
					else if (updateDevice == true)
					{
						if (getAVCLevel() == AVCLevels::L_UNRESTRICTED)
							x264VBVMaxRate->Value = 0;
						else
							x264VBVMaxRate->Value = (new AVCLevels())->getMaxBR(getAVCLevel(), avcProfile->SelectedIndex == 2);
					}

					// --b-pyramid
					if (oTargetDevice->getBPyramid() > -1)
					{
						if (oTargetDevice->getBPyramid() != cbBPyramid->SelectedIndex)
							cbBPyramid->SelectedIndex = oTargetDevice->getBPyramid();
					}
					else if (updateDevice == true)
						cbBPyramid->SelectedIndex = 1;

					// Blu-ray
					if (oTargetDevice->getBluRay())
					{
						chkBlurayCompat->Checked = true;
						chkOpenGop->Checked = true;
						x264aud->Checked = true;
						if (x264hrd->SelectedIndex == 0)
							x264hrd->SelectedIndex = 1;
						if (x264WeightedPPrediction->SelectedIndex > 1)
							x264WeightedPPrediction->SelectedIndex = 1;
						if (cbBPyramid->SelectedIndex > 1)
							cbBPyramid->SelectedIndex = 1;
						slicesnb->Value = 4;
					}
					else if (updateDevice == true)
					{
						x264hrd->SelectedIndex = 0;
						chkBlurayCompat->Checked = false;
						chkOpenGop->Checked = false;
						x264aud->Checked = false;
						slicesnb->Value = 0;
						if (cbBPyramid->SelectedIndex == 1)
							cbBPyramid->SelectedIndex = 2;
						if (this->x264WeightedPPrediction->SelectedIndex != x264Settings::GetDefaultNumberOfWeightp(static_cast<x264Settings::x264PresetLevelModes>(tbx264Presets->Value), chkTuneFastDecode->Checked, avcProfile->SelectedIndex, chkBlurayCompat->Checked))
							this->x264WeightedPPrediction->SelectedIndex = x264Settings::GetDefaultNumberOfWeightp(static_cast<x264Settings::x264PresetLevelModes>(tbx264Presets->Value), chkTuneFastDecode->Checked, avcProfile->SelectedIndex, chkBlurayCompat->Checked);
					}
					else if (chkBlurayCompat->Checked)
					{
						x264aud->Checked = true;
						if (x264hrd->SelectedIndex == 0)
							x264hrd->SelectedIndex = 1;
						if (x264WeightedPPrediction->SelectedIndex > 1)
							x264WeightedPPrediction->SelectedIndex = 1;
						if (cbBPyramid->SelectedIndex > 1)
							cbBPyramid->SelectedIndex = 1;
						if (x264NumberOfBFrames->Value > 3)
							x264NumberOfBFrames->Value = 3;
						if (x264NumberOfRefFrames->Value > 6)
							x264NumberOfRefFrames->Value = 6;
					}

					// BFrames
					if (oTargetDevice->getBFrames() > -1)
					{
						if (x264NumberOfBFrames->Value > oTargetDevice->getBFrames())
							x264NumberOfBFrames->Value = oTargetDevice->getBFrames();
					}
					if (updateDevice == true)
					{
						int iDefaultBFrames = x264Settings::GetDefaultNumberOfBFrames(static_cast<x264Settings::x264PresetLevelModes>(tbx264Presets->Value), getPsyTuning(), chkTuneZeroLatency->Checked, avcProfile->SelectedIndex, oTargetDevice, chkBlurayCompat->Checked);
						if (x264NumberOfBFrames->Value != iDefaultBFrames)
							x264NumberOfBFrames->Value = iDefaultBFrames;
					}

					// Reference Frames
					if (oTargetDevice->getReferenceFrames() > -1)
					{
						if (x264NumberOfRefFrames->Value > oTargetDevice->getReferenceFrames())
							x264NumberOfRefFrames->Value = oTargetDevice->getReferenceFrames();
					}
					if (updateDevice == true)
					{
						int iDefaultRFrames = x264Settings::GetDefaultNumberOfRefFrames(static_cast<x264Settings::x264PresetLevelModes>(tbx264Presets->Value), getPsyTuning(), oTargetDevice, getAVCLevel(), chkBlurayCompat->Checked);
						if (x264NumberOfRefFrames->Value != iDefaultRFrames)
							x264NumberOfRefFrames->Value = iDefaultRFrames;
					}

				}

				void x264ConfigurationPanel::doMacroBlockAdjustments()
				{
					bool enableOptions = (macroblockOptions->SelectedIndex == 2); // custom
					x264I4x4mv->Enabled = enableOptions;
					x264P4x4mv->Enabled = enableOptions;
					x264P8x8mv->Enabled = enableOptions;
					x264B8x8mv->Enabled = enableOptions;
					x264I8x8mv->Enabled = enableOptions;
					adaptiveDCT->Enabled = enableOptions;

					if (macroblockOptions->SelectedIndex == 1) // none
					{
						x264I4x4mv->Checked = false;
						x264P4x4mv->Checked = false;
						x264P8x8mv->Checked = false;
						x264B8x8mv->Checked = false;
						x264I8x8mv->Checked = false;
						adaptiveDCT->Checked = false;
						return;
					}

					if (macroblockOptions->SelectedIndex == 0) // all
					{
						x264P8x8mv->Checked = true;
						x264I4x4mv->Checked = true;
						x264P4x4mv->Checked = true;
						x264B8x8mv->Checked = true;

						if (avcProfile->SelectedIndex > 1)
						{
							adaptiveDCT->Checked = true;
							x264I8x8mv->Checked = true;
						}
						else
						{
							adaptiveDCT->Checked = false;
							x264I8x8mv->Checked = false;
						}
					}
					else if (macroblockOptions->SelectedIndex == 2) // custom
					{
						if (avcProfile->SelectedIndex > 1)
						{
							if (adaptiveDCT->Checked)
							{
								x264I8x8mv->Checked = true;
							}
							else
							{
								x264I8x8mv->Enabled = false;
								x264I8x8mv->Checked = false;
							}
						}
						else
						{
							adaptiveDCT->Enabled = false;
							adaptiveDCT->Checked = false;
							x264I8x8mv->Enabled = false;
							x264I8x8mv->Checked = false;
						}

						if (!this->x264P8x8mv->Checked) // p4x4 requires p8x8
						{
							this->x264P4x4mv->Checked = false;
							this->x264P4x4mv->Enabled = false;
						}
					}
					else // Default
					{
						x264P8x8mv->Checked = true;
						x264I4x4mv->Checked = true;
						x264P4x4mv->Checked = false;
						x264B8x8mv->Checked = true;

						if (avcProfile->SelectedIndex > 1)
						{
							adaptiveDCT->Checked = true;
							x264I8x8mv->Checked = true;
						}
						else
						{
							adaptiveDCT->Checked = false;
							x264I8x8mv->Checked = false;
						}
					}
					genericUpdate();
				}

				void x264ConfigurationPanel::doTrellisAdjustments()
				{
					deadzoneInter->Enabled = (trellis->SelectedIndex == 0);
					deadzoneIntra->Enabled = (trellis->SelectedIndex == 0);
					lbx264DeadZones->Enabled = (trellis->SelectedIndex == 0);
					if (trellis->SelectedIndex != 0)
					{
						deadzoneIntra->Value = 11;
						deadzoneInter->Value = 21;
					}
					if (getPsyTuning() == x264Settings::GRAIN && trellis->SelectedIndex != 0)
					{
						deadzoneInter->Value = 6;
						deadzoneIntra->Value = 6;
					}
				}

				void x264ConfigurationPanel::doSubmeAdjustments()
				{
					if (x264SubpelRefinement->SelectedIndex == 10)
					{
						if (trellis->SelectedIndex != 2)
							trellis->SelectedIndex = 2;
						if (cbAQMode->SelectedIndex == 0)
							cbAQMode->SelectedIndex = 1;
					}
				}

				void x264ConfigurationPanel::doTuningsAdjustments()
				{
					if (this->x264NumberOfRefFrames->Value != x264Settings::GetDefaultNumberOfRefFrames(static_cast<x264Settings::x264PresetLevelModes>(tbx264Presets->Value), getPsyTuning(), oTargetDevice, getAVCLevel(), chkBlurayCompat->Checked))
						this->x264NumberOfRefFrames->Value = x264Settings::GetDefaultNumberOfRefFrames(static_cast<x264Settings::x264PresetLevelModes>(tbx264Presets->Value), getPsyTuning(), oTargetDevice, getAVCLevel(), chkBlurayCompat->Checked);
					if (this->x264NumberOfBFrames->Value != x264Settings::GetDefaultNumberOfBFrames(static_cast<x264Settings::x264PresetLevelModes>(tbx264Presets->Value), getPsyTuning(), chkTuneZeroLatency->Checked, avcProfile->SelectedIndex, oTargetDevice, chkBlurayCompat->Checked))
						this->x264NumberOfBFrames->Value = x264Settings::GetDefaultNumberOfBFrames(static_cast<x264Settings::x264PresetLevelModes>(tbx264Presets->Value), getPsyTuning(), chkTuneZeroLatency->Checked, avcProfile->SelectedIndex, oTargetDevice, chkBlurayCompat->Checked);
					if (this->x264WeightedPPrediction->SelectedIndex != x264Settings::GetDefaultNumberOfWeightp(static_cast<x264Settings::x264PresetLevelModes>(tbx264Presets->Value), chkTuneFastDecode->Checked, avcProfile->SelectedIndex, chkBlurayCompat->Checked))
						this->x264WeightedPPrediction->SelectedIndex = x264Settings::GetDefaultNumberOfWeightp(static_cast<x264Settings::x264PresetLevelModes>(tbx264Presets->Value), chkTuneFastDecode->Checked, avcProfile->SelectedIndex, chkBlurayCompat->Checked);
					if (this->cbAQMode->SelectedIndex != x264Settings::GetDefaultAQMode(static_cast<x264Settings::x264PresetLevelModes>(tbx264Presets->Value), getPsyTuning()))
						this->cbAQMode->SelectedIndex = x264Settings::GetDefaultAQMode(static_cast<x264Settings::x264PresetLevelModes>(tbx264Presets->Value), getPsyTuning());
					if (this->lookahead->Value != x264Settings::GetDefaultRCLookahead(static_cast<x264Settings::x264PresetLevelModes>(tbx264Presets->Value), chkTuneZeroLatency->Checked))
						this->lookahead->Value = x264Settings::GetDefaultRCLookahead(static_cast<x264Settings::x264PresetLevelModes>(tbx264Presets->Value), chkTuneZeroLatency->Checked);

					switch (getPsyTuning())
					{
						case x264Settings::NONE:
						{
								if (this->x264AlphaDeblock->Value != 0)
									this->x264AlphaDeblock->Value = 0;
								if (this->x264BetaDeblock->Value != 0)
									this->x264BetaDeblock->Value = 0;
								if (this->PsyTrellis->Value != 0.0)
									this->PsyTrellis->Value = 0.0;
								if (this->PsyRD->Value != 1.0)
									this->PsyRD->Value = 1.0;
								if (this->numAQStrength->Value != 1.0)
									this->numAQStrength->Value = 1.0;
								if (this->x264IPFrameFactor->Value != 1.4)
									this->x264IPFrameFactor->Value = 1.4;
								if (this->x264PBFrameFactor->Value != 1.3)
									this->x264PBFrameFactor->Value = 1.3;
								if (this->deadzoneInter->Value != 21)
									this->deadzoneInter->Value = 21;
								if (this->deadzoneIntra->Value != 11)
									this->deadzoneIntra->Value = 11;
								if (this->x264QuantizerCompression->Value != 0.6)
									this->x264QuantizerCompression->Value = 0.6;
								if (noDCTDecimateOption->Checked)
									noDCTDecimateOption->Checked = false;
								if (nopsy->Checked)
									nopsy->Checked = false;
						}
							break;
						case x264Settings::FILM:
						{
								if (this->x264AlphaDeblock->Value != -1)
									this->x264AlphaDeblock->Value = -1;
								if (this->x264BetaDeblock->Value != -1)
									this->x264BetaDeblock->Value = -1;
								if (this->PsyTrellis->Value != 0.15)
									this->PsyTrellis->Value = 0.15;
								if (this->PsyRD->Value != 1.0)
									this->PsyRD->Value = 1.0;
								if (this->numAQStrength->Value != 1.0)
									this->numAQStrength->Value = 1.0;
								if (this->x264IPFrameFactor->Value != 1.4)
									this->x264IPFrameFactor->Value = 1.4;
								if (this->x264PBFrameFactor->Value != 1.3)
									this->x264PBFrameFactor->Value = 1.3;
								if (this->deadzoneInter->Value != 21)
									this->deadzoneInter->Value = 21;
								if (this->deadzoneIntra->Value != 11)
									this->deadzoneIntra->Value = 11;
								if (this->x264QuantizerCompression->Value != 0.6)
									this->x264QuantizerCompression->Value = 0.6;
								if (noDCTDecimateOption->Checked)
									noDCTDecimateOption->Checked = false;
								if (nopsy->Checked)
									nopsy->Checked = false;
						}
							break;
						case x264Settings::ANIMATION:
						{
								if (this->x264AlphaDeblock->Value != 1)
									this->x264AlphaDeblock->Value = 1;
								if (this->x264BetaDeblock->Value != 1)
									this->x264BetaDeblock->Value = 1;
								if (this->PsyTrellis->Value != 0.0)
									this->PsyTrellis->Value = 0.0;
								if (this->PsyRD->Value != 0.4)
									this->PsyRD->Value = 0.4;
								if (this->numAQStrength->Value != 0.6)
									this->numAQStrength->Value = 0.6;
								if (this->x264IPFrameFactor->Value != 1.4)
									this->x264IPFrameFactor->Value = 1.4;
								if (this->x264PBFrameFactor->Value != 1.3)
									this->x264PBFrameFactor->Value = 1.3;
								if (this->deadzoneInter->Value != 21)
									this->deadzoneInter->Value = 21;
								if (this->deadzoneIntra->Value != 11)
									this->deadzoneIntra->Value = 11;
								if (this->x264QuantizerCompression->Value != 0.6)
									this->x264QuantizerCompression->Value = 0.6;
								if (noDCTDecimateOption->Checked)
									noDCTDecimateOption->Checked = false;
								if (nopsy->Checked)
									nopsy->Checked = false;
						}
							break;
						case x264Settings::GRAIN:
						{
								if (this->x264AlphaDeblock->Value != -2)
									this->x264AlphaDeblock->Value = -2;
								if (this->x264BetaDeblock->Value != -2)
									this->x264BetaDeblock->Value = -2;
								if (this->PsyTrellis->Value != 0.25)
									this->PsyTrellis->Value = 0.25;
								if (this->PsyRD->Value != 1.0)
									this->PsyRD->Value = 1.0;
								if (this->numAQStrength->Value != 0.5)
									this->numAQStrength->Value = 0.5;
								if (this->x264IPFrameFactor->Value != 1.1)
									this->x264IPFrameFactor->Value = 1.1;
								if (this->x264PBFrameFactor->Value != 1.1)
									this->x264PBFrameFactor->Value = 1.1;
								if (this->deadzoneInter->Value != 6)
									this->deadzoneInter->Value = 6;
								if (this->deadzoneIntra->Value != 6)
									this->deadzoneIntra->Value = 6;
								if (this->x264QuantizerCompression->Value != 0.8)
									this->x264QuantizerCompression->Value = 0.8;
								if (!noDCTDecimateOption->Checked)
									noDCTDecimateOption->Checked = true;
								if (nopsy->Checked)
									nopsy->Checked = false;
						}
							break;
						case x264Settings::PSNR:
						{
								if (this->x264AlphaDeblock->Value != 0)
									this->x264AlphaDeblock->Value = 0;
								if (this->x264BetaDeblock->Value != 0)
									this->x264BetaDeblock->Value = 0;
								if (this->PsyTrellis->Value != 0.0)
									this->PsyTrellis->Value = 0.0;
								if (this->PsyRD->Value != 1.0)
									this->PsyRD->Value = 1.0;
								if (this->numAQStrength->Value != 1.0)
									this->numAQStrength->Value = 1.0;
								if (this->x264IPFrameFactor->Value != 1.4)
									this->x264IPFrameFactor->Value = 1.4;
								if (this->x264PBFrameFactor->Value != 1.3)
									this->x264PBFrameFactor->Value = 1.3;
								if (this->deadzoneInter->Value != 21)
									this->deadzoneInter->Value = 21;
								if (this->deadzoneIntra->Value != 11)
									this->deadzoneIntra->Value = 11;
								if (this->x264QuantizerCompression->Value != 0.6)
									this->x264QuantizerCompression->Value = 0.6;
								if (noDCTDecimateOption->Checked)
									noDCTDecimateOption->Checked = false;
								if (!nopsy->Checked)
									nopsy->Checked = true;
						}
							break;
						case x264Settings::SSIM:
						{
								if (this->x264AlphaDeblock->Value != 0)
									this->x264AlphaDeblock->Value = 0;
								if (this->x264BetaDeblock->Value != 0)
									this->x264BetaDeblock->Value = 0;
								if (this->PsyTrellis->Value != 0.0)
									this->PsyTrellis->Value = 0.0;
								if (this->PsyRD->Value != 1.0)
									this->PsyRD->Value = 1.0;
								if (this->numAQStrength->Value != 1.0)
									this->numAQStrength->Value = 1.0;
								if (this->x264IPFrameFactor->Value != 1.4)
									this->x264IPFrameFactor->Value = 1.4;
								if (this->x264PBFrameFactor->Value != 1.3)
									this->x264PBFrameFactor->Value = 1.3;
								if (this->deadzoneInter->Value != 21)
									this->deadzoneInter->Value = 21;
								if (this->deadzoneIntra->Value != 11)
									this->deadzoneIntra->Value = 11;
								if (this->x264QuantizerCompression->Value != 0.6)
									this->x264QuantizerCompression->Value = 0.6;
								if (noDCTDecimateOption->Checked)
									noDCTDecimateOption->Checked = false;
								if (!nopsy->Checked)
									nopsy->Checked = true;
						}
							break;
						case x264Settings::STILLIMAGE:
						{
								if (this->x264AlphaDeblock->Value != 3)
									this->x264AlphaDeblock->Value = 3;
								if (this->x264BetaDeblock->Value != -3)
									this->x264BetaDeblock->Value = -3;
								if (this->PsyTrellis->Value != 0.7)
									this->PsyTrellis->Value = 0.7;
								if (this->PsyRD->Value != 2.0)
									this->PsyRD->Value = 2.0;
								if (this->numAQStrength->Value != 1.2)
									this->numAQStrength->Value = 1.2;
								if (this->x264IPFrameFactor->Value != 1.4)
									this->x264IPFrameFactor->Value = 1.4;
								if (this->x264PBFrameFactor->Value != 1.3)
									this->x264PBFrameFactor->Value = 1.3;
								if (this->deadzoneInter->Value != 21)
									this->deadzoneInter->Value = 21;
								if (this->deadzoneIntra->Value != 11)
									this->deadzoneIntra->Value = 11;
								if (this->x264QuantizerCompression->Value != 0.6)
									this->x264QuantizerCompression->Value = 0.6;
								if (noDCTDecimateOption->Checked)
									noDCTDecimateOption->Checked = false;
								if (nopsy->Checked)
									nopsy->Checked = false;
						}
							break;
					}

					x264DeblockActive->Checked = !chkTuneFastDecode->Checked;
					cabac->Checked = !chkTuneFastDecode->Checked;
					x264WeightedBPrediction->Checked = !chkTuneFastDecode->Checked;
					mbtree->Checked = !chkTuneZeroLatency->Checked;
				}

				void x264ConfigurationPanel::doPresetsAdjustments()
				{
					if (this->x264NumberOfRefFrames->Value != x264Settings::GetDefaultNumberOfRefFrames(static_cast<x264Settings::x264PresetLevelModes>(tbx264Presets->Value), getPsyTuning(), oTargetDevice, getAVCLevel(), chkBlurayCompat->Checked))
						this->x264NumberOfRefFrames->Value = x264Settings::GetDefaultNumberOfRefFrames(static_cast<x264Settings::x264PresetLevelModes>(tbx264Presets->Value), getPsyTuning(), oTargetDevice, getAVCLevel(), chkBlurayCompat->Checked);
					if (this->x264NumberOfBFrames->Value != x264Settings::GetDefaultNumberOfBFrames(static_cast<x264Settings::x264PresetLevelModes>(tbx264Presets->Value), getPsyTuning(), chkTuneZeroLatency->Checked, avcProfile->SelectedIndex, oTargetDevice, chkBlurayCompat->Checked))
						this->x264NumberOfBFrames->Value = x264Settings::GetDefaultNumberOfBFrames(static_cast<x264Settings::x264PresetLevelModes>(tbx264Presets->Value), getPsyTuning(), chkTuneZeroLatency->Checked, avcProfile->SelectedIndex, oTargetDevice, chkBlurayCompat->Checked);
					if (this->x264WeightedPPrediction->SelectedIndex != x264Settings::GetDefaultNumberOfWeightp(static_cast<x264Settings::x264PresetLevelModes>(tbx264Presets->Value), chkTuneFastDecode->Checked, avcProfile->SelectedIndex, chkBlurayCompat->Checked))
						this->x264WeightedPPrediction->SelectedIndex = x264Settings::GetDefaultNumberOfWeightp(static_cast<x264Settings::x264PresetLevelModes>(tbx264Presets->Value), chkTuneFastDecode->Checked, avcProfile->SelectedIndex, chkBlurayCompat->Checked);
					if (this->cbAQMode->SelectedIndex != x264Settings::GetDefaultAQMode(static_cast<x264Settings::x264PresetLevelModes>(tbx264Presets->Value), getPsyTuning()))
						this->cbAQMode->SelectedIndex = x264Settings::GetDefaultAQMode(static_cast<x264Settings::x264PresetLevelModes>(tbx264Presets->Value), getPsyTuning());
					if (this->lookahead->Value != x264Settings::GetDefaultRCLookahead(static_cast<x264Settings::x264PresetLevelModes>(tbx264Presets->Value), chkTuneZeroLatency->Checked))
						this->lookahead->Value = x264Settings::GetDefaultRCLookahead(static_cast<x264Settings::x264PresetLevelModes>(tbx264Presets->Value), chkTuneZeroLatency->Checked);

					switch (tbx264Presets->Value)
					{
						case 0: // Ultra Fast
						{
								if (this->x264MERange->Value != 16)
									this->x264MERange->Value = 16;
								if (macroblockOptions->SelectedIndex != 1)
									macroblockOptions->SelectedIndex = 1;
								if (x264SubpelRefinement->SelectedIndex != 0)
									x264SubpelRefinement->SelectedIndex = 0;
								if (x264METype->SelectedIndex != 0)
									x264METype->SelectedIndex = 0;
								if (trellis->SelectedIndex != 0)
									trellis->SelectedIndex = 0;
								if (x264BframePredictionMode->SelectedIndex != 1)
									x264BframePredictionMode->SelectedIndex = 1;
								if (scenecut->Checked)
									scenecut->Checked = false;
								if (x264DeblockActive->Checked)
									x264DeblockActive->Checked = false;
								if (cabac->Checked)
									cabac->Checked = false;
								if (!chkTuneFastDecode->Checked)
									cabac->Enabled = false;
								if (adaptiveDCT->Checked)
									adaptiveDCT->Checked = false;
								if (!x264MixedReferences->Checked)
									x264MixedReferences->Checked = true;
								if (mbtree->Checked)
									mbtree->Checked = false;
								mbtree->Enabled = false;
								if (noFastPSkip->Checked)
									noFastPSkip->Checked = false;
								if (x264NewAdaptiveBframes->SelectedIndex != 0)
									x264NewAdaptiveBframes->SelectedIndex = 0;
								if (this->x264WeightedBPrediction->Checked)
									this->x264WeightedBPrediction->Checked = false;
						}
							break;
						case 1: // Super Fast
						{
								if (macroblockOptions->SelectedIndex != 2)
									macroblockOptions->SelectedIndex = 2;
								if (!x264I4x4mv->Checked)
									x264I4x4mv->Checked = true;
								if (!x264I8x8mv->Checked)
									x264I8x8mv->Checked = true;
								if (x264B8x8mv->Checked)
									x264B8x8mv->Checked = false;
								if (x264P4x4mv->Checked)
									x264P4x4mv->Checked = false;
								if (x264P8x8mv->Checked)
									x264P8x8mv->Checked = false;
								if (x264METype->SelectedIndex != 0)
									x264METype->SelectedIndex = 0;
								if (x264SubpelRefinement->SelectedIndex != 1)
									x264SubpelRefinement->SelectedIndex = 1;
								if (!x264MixedReferences->Checked)
									x264MixedReferences->Checked = true;
								if (trellis->SelectedIndex != 0)
									trellis->SelectedIndex = 0;
								if (mbtree->Checked)
									mbtree->Checked = false;
								mbtree->Enabled = false;
								if (x264BframePredictionMode->SelectedIndex != 1)
									x264BframePredictionMode->SelectedIndex = 1;
								if (!cabac->Checked)
									cabac->Checked = true;
								if (!chkTuneFastDecode->Checked)
									cabac->Enabled = true;
								if (!x264DeblockActive->Checked)
									x264DeblockActive->Checked = true;
								if (!scenecut->Checked)
									scenecut->Checked = true;
								if (this->x264MERange->Value != 16)
									this->x264MERange->Value = 16;
								if (noFastPSkip->Checked)
									noFastPSkip->Checked = false;
								if (x264NewAdaptiveBframes->SelectedIndex != 1)
									x264NewAdaptiveBframes->SelectedIndex = 1;
								if (!this->x264WeightedBPrediction->Checked)
									this->x264WeightedBPrediction->Checked = true;
								if (!adaptiveDCT->Checked)
									adaptiveDCT->Checked = true;
						}
							break;
						case 2: // Very Fast
						{
								if (macroblockOptions->SelectedIndex != 3)
									macroblockOptions->SelectedIndex = 3;
								if (x264METype->SelectedIndex != 1)
									x264METype->SelectedIndex = 1;
								if (x264SubpelRefinement->SelectedIndex != 2)
									x264SubpelRefinement->SelectedIndex = 2;
								if (!x264MixedReferences->Checked)
									x264MixedReferences->Checked = true;
								if (trellis->SelectedIndex != 0)
									trellis->SelectedIndex = 0;
								if (!mbtree->Checked)
									mbtree->Checked = true;
								mbtree->Enabled = true;
								if (x264BframePredictionMode->SelectedIndex != 1)
									x264BframePredictionMode->SelectedIndex = 1;
								if (!cabac->Checked)
									cabac->Checked = true;
								if (!chkTuneFastDecode->Checked)
									cabac->Enabled = true;
								if (!x264DeblockActive->Checked)
									 x264DeblockActive->Checked = true;
								if (!scenecut->Checked)
									scenecut->Checked = true;
								if (this->x264MERange->Value != 16)
									this->x264MERange->Value = 16;
								if (noFastPSkip->Checked)
									noFastPSkip->Checked = false;
								if (x264NewAdaptiveBframes->SelectedIndex != 1)
									x264NewAdaptiveBframes->SelectedIndex = 1;
								if (!this->x264WeightedBPrediction->Checked)
									this->x264WeightedBPrediction->Checked = true;
								if (!adaptiveDCT->Checked)
									adaptiveDCT->Checked = true;
						}
							break;
						case 3: // Faster
						{
								if (x264SubpelRefinement->SelectedIndex != 4)
									x264SubpelRefinement->SelectedIndex = 4;
								if (!mbtree->Checked)
									mbtree->Checked = true;
								mbtree->Enabled = true;
								if (trellis->SelectedIndex != 1)
									trellis->SelectedIndex = 1;
								if (!x264MixedReferences->Checked)
									 x264MixedReferences->Checked = true;
								if (x264METype->SelectedIndex != 1)
									x264METype->SelectedIndex = 1;
								if (macroblockOptions->SelectedIndex != 3)
									macroblockOptions->SelectedIndex = 3;
								if (x264BframePredictionMode->SelectedIndex != 1)
									x264BframePredictionMode->SelectedIndex = 1;
								if (!cabac->Checked)
									cabac->Checked = true;
								if (!chkTuneFastDecode->Checked)
									cabac->Enabled = true;
								if (!x264DeblockActive->Checked)
									 x264DeblockActive->Checked = true;
								if (!scenecut->Checked)
									 scenecut->Checked = true;
								if (this->x264MERange->Value != 16)
									this->x264MERange->Value = 16;
								if (noFastPSkip->Checked)
									noFastPSkip->Checked = false;
								if (x264NewAdaptiveBframes->SelectedIndex != 1)
									x264NewAdaptiveBframes->SelectedIndex = 1;
								if (!this->x264WeightedBPrediction->Checked)
									this->x264WeightedBPrediction->Checked = true;
								if (adaptiveDCT->Checked)
									adaptiveDCT->Checked = false;
						}
							break;
						case 4: // Fast
						{
								if (x264SubpelRefinement->SelectedIndex != 6)
									x264SubpelRefinement->SelectedIndex = 6;
								if (trellis->SelectedIndex != 1)
									trellis->SelectedIndex = 1;
								if (x264MixedReferences->Checked)
									 x264MixedReferences->Checked = false;
								if (!mbtree->Checked)
									 mbtree->Checked = true;
								mbtree->Enabled = true;
								if (x264METype->SelectedIndex != 1)
									x264METype->SelectedIndex = 1;
								if (macroblockOptions->SelectedIndex != 3)
									macroblockOptions->SelectedIndex = 3;
								if (x264BframePredictionMode->SelectedIndex != 1)
									x264BframePredictionMode->SelectedIndex = 1;
								if (!cabac->Checked)
									cabac->Checked = true;
								if (!chkTuneFastDecode->Checked)
									cabac->Enabled = true;
								if (!x264DeblockActive->Checked)
									 x264DeblockActive->Checked = true;
								if (!scenecut->Checked)
									 scenecut->Checked = true;
								if (this->x264MERange->Value != 16)
									this->x264MERange->Value = 16;
								if (noFastPSkip->Checked)
									noFastPSkip->Checked = false;
								if (x264NewAdaptiveBframes->SelectedIndex != 1)
									x264NewAdaptiveBframes->SelectedIndex = 1;
								if (!this->x264WeightedBPrediction->Checked)
									this->x264WeightedBPrediction->Checked = true;
								if (adaptiveDCT->Checked)
									adaptiveDCT->Checked = false;
						}
							break;
						case 5: // Medium
						{
								if (x264METype->SelectedIndex != 1)
									x264METype->SelectedIndex = 1;
								if (x264SubpelRefinement->SelectedIndex != 7)
									x264SubpelRefinement->SelectedIndex = 7;
								if (x264NewAdaptiveBframes->SelectedIndex != 1)
									x264NewAdaptiveBframes->SelectedIndex = 1;
								if (x264BframePredictionMode->SelectedIndex != 1)
									x264BframePredictionMode->SelectedIndex = 1;
								if (trellis->SelectedIndex != 1)
									trellis->SelectedIndex = 1;
								if (x264MixedReferences->Checked)
									x264MixedReferences->Checked = false;
								if (!mbtree->Checked)
									mbtree->Checked = true;
								mbtree->Enabled = true;
								if (macroblockOptions->SelectedIndex != 3)
									macroblockOptions->SelectedIndex = 3;
								if (!cabac->Checked)
									cabac->Checked = true;
								if (!chkTuneFastDecode->Checked)
									cabac->Enabled = true;
								if (!x264DeblockActive->Checked)
									x264DeblockActive->Checked = true;
								if (!scenecut->Checked)
									scenecut->Checked = true;
								if (this->x264MERange->Value != 16)
									this->x264MERange->Value = 16;
								if (noFastPSkip->Checked)
									noFastPSkip->Checked = false;
								if (!this->x264WeightedBPrediction->Checked)
									this->x264WeightedBPrediction->Checked = true;
								if (adaptiveDCT->Checked)
									adaptiveDCT->Checked = false;
						}
							break;
						case 6: // Slow
						{
								if (x264METype->SelectedIndex != 2)
									x264METype->SelectedIndex = 2;
								if (x264SubpelRefinement->SelectedIndex != 8)
									x264SubpelRefinement->SelectedIndex = 8;
								if (x264NewAdaptiveBframes->SelectedIndex != 2)
									x264NewAdaptiveBframes->SelectedIndex = 2;
								if (x264BframePredictionMode->SelectedIndex != 3)
									x264BframePredictionMode->SelectedIndex = 3;
								if (trellis->SelectedIndex != 1)
									trellis->SelectedIndex = 1;
								if (x264MixedReferences->Checked)
									 x264MixedReferences->Checked = false;
								if (!mbtree->Checked)
									 mbtree->Checked = true;
								mbtree->Enabled = true;
								if (macroblockOptions->SelectedIndex != 3)
									macroblockOptions->SelectedIndex = 3;
								if (!cabac->Checked)
									cabac->Checked = true;
								if (!chkTuneFastDecode->Checked)
									cabac->Enabled = true;
								if (!x264DeblockActive->Checked)
									 x264DeblockActive->Checked = true;
								if (!scenecut->Checked)
									 scenecut->Checked = true;
								if (this->x264MERange->Value != 16)
									this->x264MERange->Value = 16;
								if (noFastPSkip->Checked)
									noFastPSkip->Checked = false;
								if (!this->x264WeightedBPrediction->Checked)
									this->x264WeightedBPrediction->Checked = true;
								if (adaptiveDCT->Checked)
									adaptiveDCT->Checked = false;
						}
							break;
						case 7: // Slower
						{
								if (x264METype->SelectedIndex != 2)
									x264METype->SelectedIndex = 2;
								if (x264SubpelRefinement->SelectedIndex != 9)
									x264SubpelRefinement->SelectedIndex = 9;
								if (x264NewAdaptiveBframes->SelectedIndex != 2)
									x264NewAdaptiveBframes->SelectedIndex = 2;
								if (trellis->SelectedIndex != 2)
									trellis->SelectedIndex = 2;
								if (x264BframePredictionMode->SelectedIndex != 3)
									x264BframePredictionMode->SelectedIndex = 3;
								if (macroblockOptions->SelectedIndex != 0)
									macroblockOptions->SelectedIndex = 0;
								if (x264MixedReferences->Checked)
									 x264MixedReferences->Checked = false;
								if (!mbtree->Checked)
									mbtree->Checked = true;
								mbtree->Enabled = true;
								if (!cabac->Checked)
									cabac->Checked = true;
								if (!chkTuneFastDecode->Checked)
									cabac->Enabled = true;
								if (!x264DeblockActive->Checked)
									 x264DeblockActive->Checked = true;
								if (!scenecut->Checked)
									 scenecut->Checked = true;
								if (this->x264MERange->Value != 16)
									this->x264MERange->Value = 16;
								if (noFastPSkip->Checked)
									noFastPSkip->Checked = false;
								if (!this->x264WeightedBPrediction->Checked)
									this->x264WeightedBPrediction->Checked = true;
								if (adaptiveDCT->Checked)
									adaptiveDCT->Checked = false;
						}
							break;
						case 8: // Very Slow
						{
								if (x264METype->SelectedIndex != 2)
									x264METype->SelectedIndex = 2;
								if (x264SubpelRefinement->SelectedIndex != 10)
									x264SubpelRefinement->SelectedIndex = 10;
								if (this->x264MERange->Value != 24)
									this->x264MERange->Value = 24;
								if (x264NewAdaptiveBframes->SelectedIndex != 2)
									x264NewAdaptiveBframes->SelectedIndex = 2;
								if (x264BframePredictionMode->SelectedIndex != 3)
									x264BframePredictionMode->SelectedIndex = 3;
								if (macroblockOptions->SelectedIndex != 0)
									macroblockOptions->SelectedIndex = 0;
								if (trellis->SelectedIndex != 2)
									trellis->SelectedIndex = 2;
								if (x264MixedReferences->Checked)
									 x264MixedReferences->Checked = false;
								if (!mbtree->Checked)
									mbtree->Checked = true;
								mbtree->Enabled = true;
								if (!cabac->Checked)
									cabac->Checked = true;
								if (!chkTuneFastDecode->Checked)
									cabac->Enabled = true;
								if (!x264DeblockActive->Checked)
									 x264DeblockActive->Checked = true;
								if (!scenecut->Checked)
									 scenecut->Checked = true;
								if (noFastPSkip->Checked)
									noFastPSkip->Checked = false;
								if (!this->x264WeightedBPrediction->Checked)
									this->x264WeightedBPrediction->Checked = true;
								if (adaptiveDCT->Checked)
									adaptiveDCT->Checked = false;
						}
							break;
						case 9: // Placebo
						{
								if (x264METype->SelectedIndex != 4)
									x264METype->SelectedIndex = 4;
								if (x264SubpelRefinement->SelectedIndex != 11)
									x264SubpelRefinement->SelectedIndex = 11;
								if (this->x264MERange->Value != 24)
									this->x264MERange->Value = 24;
								if (x264NewAdaptiveBframes->SelectedIndex != 2)
									x264NewAdaptiveBframes->SelectedIndex = 2;
								if (x264BframePredictionMode->SelectedIndex != 3)
									x264BframePredictionMode->SelectedIndex = 3;
								if (macroblockOptions->SelectedIndex != 0)
									macroblockOptions->SelectedIndex = 0;
								if (!noFastPSkip->Checked)
									noFastPSkip->Checked = true;
								if (trellis->SelectedIndex != 2)
									trellis->SelectedIndex = 2;
								if (x264MixedReferences->Checked)
									 x264MixedReferences->Checked = false;
								if (!mbtree->Checked)
									mbtree->Checked = true;
								mbtree->Enabled = true;
								if (!cabac->Checked)
									cabac->Checked = true;
								if (!chkTuneFastDecode->Checked)
									cabac->Enabled = true;
								if (!x264DeblockActive->Checked)
									 x264DeblockActive->Checked = true;
								if (!scenecut->Checked)
									 scenecut->Checked = true;
								if (!this->x264WeightedBPrediction->Checked)
									this->x264WeightedBPrediction->Checked = true;
								if (adaptiveDCT->Checked)
									adaptiveDCT->Checked = false;
						}
							break;
						default:
							break;
					}
				}

				void x264ConfigurationPanel::setNonQPOptionsEnabled(bool enabled)
				{
					//x264MinimimQuantizer.Enabled = enabled;
					//x264MaximumQuantizer.Enabled = enabled;
					//x264MaxQuantDelta.Enabled = enabled;
					//x264IPFrameFactor.Enabled = enabled;
					//x264PBFrameFactor.Enabled = enabled;
					//x264ChromaQPOffset.Enabled = enabled;
					x264RCGroupbox->Enabled = enabled;
				}

				bool x264ConfigurationPanel::isBitrateMode(int mode)
				{
					return !(mode == static_cast<int>(VideoCodecSettings::CQ) || mode == static_cast<int>(VideoCodecSettings::quality));
				}

				void x264ConfigurationPanel::doEncodingModeAdjustments()
				{
					this->gbAQ->Enabled = true;
					if (isBitrateMode(x264EncodingMode->SelectedIndex))
					{
						this->x264BitrateQuantizerLabel->Text = "Bitrate";
						x264TempFrameComplexityBlur->Enabled = true;
						x264TempFrameComplexityBlurLabel->Enabled = true;
						x264TempQuantBlur->Enabled = true;
						x264TempQuantBlurLabel->Enabled = true;

						x264BitrateQuantizer->Maximum = 300000;
						x264BitrateQuantizer->Minimum = 0;
						x264BitrateQuantizer->DecimalPlaces = 0;
						x264BitrateQuantizer->Increment = 10;

						cbTarget->Text = "Targeting file size";
						tooltipHelp->SetToolTip(x264BitrateQuantizer, SelectHelpText("bitrate"));
					}
					else
					{
						x264TempFrameComplexityBlur->Enabled = false;
						x264TempFrameComplexityBlurLabel->Enabled = false;
						x264TempQuantBlur->Enabled = false;
						x264TempQuantBlurLabel->Enabled = false;
						if (x264EncodingMode->SelectedIndex == static_cast<int>(VideoCodecSettings::CQ))
						{
							this->x264BitrateQuantizerLabel->Text = "Quantizer";
							this->gbAQ->Enabled = false;
							tooltipHelp->SetToolTip(x264BitrateQuantizer, SelectHelpText("qp"));
						}
						if (x264EncodingMode->SelectedIndex == static_cast<int>(VideoCodecSettings::quality))
						{
							this->x264BitrateQuantizerLabel->Text = "Quality";
							cbTarget->Text = "Targeting quality";
							tooltipHelp->SetToolTip(x264BitrateQuantizer, SelectHelpText("crf"));
						}

						if (x264EncodingMode->SelectedIndex == static_cast<int>(VideoCodecSettings::quality)) // crf
						{
							x264BitrateQuantizer->Maximum = 51;
							x264BitrateQuantizer->Minimum = 0.0;
							x264BitrateQuantizer->DecimalPlaces = 1;
							x264BitrateQuantizer->Increment = 0.1;
						}
						else // qp
						{
							x264BitrateQuantizer->Maximum = 69;
							x264BitrateQuantizer->Minimum = 0;
							x264BitrateQuantizer->Value = static_cast<int>(x264BitrateQuantizer->Value); // makes sure it is an integer, in case we just swapped from crf
							x264BitrateQuantizer->DecimalPlaces = 0;
							x264BitrateQuantizer->Increment = 1;
						}

					}
					if (x264EncodingMode->SelectedIndex != static_cast<int>(VideoCodecSettings::CQ))
						setNonQPOptionsEnabled(true);
					else
						setNonQPOptionsEnabled(false);

					switch (x264EncodingMode->SelectedIndex)
					{
						case static_cast<int>(VideoCodecSettings::CBR): //Actually, ABR
							x264SlowFirstpass->Enabled = false;
							x264RateTol->Enabled = true;
							x264RateTolLabel->Enabled = true;
							logfileOpenButton->Enabled = false;
							break;

						case static_cast<int>(VideoCodecSettings::CQ):
							x264SlowFirstpass->Enabled = false;
							x264RateTol->Enabled = false;
							x264RateTolLabel->Enabled = false;
							logfileOpenButton->Enabled = false;
							break;

						case static_cast<int>(VideoCodecSettings::twopass1):
						case static_cast<int>(VideoCodecSettings::threepass1):
							x264SlowFirstpass->Enabled = true;
							x264RateTol->Enabled = true;
							x264RateTolLabel->Enabled = true;
							logfileOpenButton->Enabled = true;
							break;

						case static_cast<int>(VideoCodecSettings::twopass2):
						case static_cast<int>(VideoCodecSettings::threepass2):
						case static_cast<int>(VideoCodecSettings::threepass3):
							x264SlowFirstpass->Enabled = false;
							x264RateTol->Enabled = true;
							x264RateTolLabel->Enabled = true;
							logfileOpenButton->Enabled = true;
							break;
						case static_cast<int>(VideoCodecSettings::twopassAutomated):
						case static_cast<int>(VideoCodecSettings::threepassAutomated):
							x264SlowFirstpass->Enabled = true;
							x264RateTol->Enabled = true;
							x264RateTolLabel->Enabled = true;
							logfileOpenButton->Enabled = true;
							break;
						case static_cast<int>(VideoCodecSettings::quality):
							x264SlowFirstpass->Enabled = false;
							logfileOpenButton->Enabled = false;
							x264RateTol->Enabled = false;
							x264RateTolLabel->Enabled = false;
							break;
					}

					// We check whether the bitrate/quality text needs to be changed
					if (isBitrateMode(lastEncodingMode) != isBitrateMode(x264EncodingMode->SelectedIndex))
					{
						if (isBitrateMode(x264EncodingMode->SelectedIndex))
							this->x264BitrateQuantizer->Value = 1000;
						else
							this->x264BitrateQuantizer->Value = 23;
					}

					// No Scenecut
					x264SCDSensitivity->Enabled = scenecut->Checked;

					lastEncodingMode = x264EncodingMode->SelectedIndex;
				}

				void x264ConfigurationPanel::doMBOptionsAdjustments()
				{
					if (!x264P8x8mv->Checked)
					{
						// x264P4x4mv.Checked = false;
						x264P4x4mv->Enabled = false;
					}
					switch (avcProfile->SelectedIndex)
					{
						case 0: // BP
						case 1: // MP
							if (x264P8x8mv->Checked && x264B8x8mv->Checked && x264I4x4mv->Checked && x264P4x4mv->Checked)
								this->macroblockOptions->SelectedIndex = 0;
							else if (!x264P8x8mv->Checked && !x264B8x8mv->Checked && !x264I4x4mv->Checked && !x264P4x4mv->Checked)
								this->macroblockOptions->SelectedIndex = 1;
							else
								this->macroblockOptions->SelectedIndex = 3;
							break;
						case 2: // HP
							if (x264P8x8mv->Checked && x264B8x8mv->Checked && x264I4x4mv->Checked && x264I8x8mv->Checked && x264P4x4mv->Checked && adaptiveDCT->Checked)
								this->macroblockOptions->SelectedIndex = 0;
							else if (!x264P8x8mv->Checked && !x264B8x8mv->Checked && !x264I4x4mv->Checked && !x264I8x8mv->Checked && !x264P4x4mv->Checked && !adaptiveDCT->Checked)
								this->macroblockOptions->SelectedIndex = 1;
							else
								this->macroblockOptions->SelectedIndex = 3;
							break;
					}
				}

				std::string x264ConfigurationPanel::getCommandline()
				{
					return x264Encoder::genCommandline("input", "output", 0, -1, -1, 0, 1, dynamic_cast<x264Settings*>(getSettings()), 0, 0);
				}

				void x264ConfigurationPanel::doCodecSpecificAdjustments()
				{
					doDeviceSpecificAdjustments();
					doEncodingModeAdjustments();
					doCheckBoxAdjustments();
					doTrellisAdjustments();
					doMacroBlockAdjustments();
					x264DialogTriStateAdjustment();
					doMacroBlockAdjustments();
					doSubmeAdjustments();
				}

				void x264ConfigurationPanel::doCodecSpecificLoadAdjustments()
				{
					if (x264EncodingMode->SelectedIndex == -1)
						this->x264EncodingMode->SelectedIndex = 0;
					if (x264SubpelRefinement->SelectedIndex == -1)
						this->x264SubpelRefinement->SelectedIndex = 7;
					if (x264BframePredictionMode->SelectedIndex == -1)
						this->x264BframePredictionMode->SelectedIndex = 1;
					if (x264METype->SelectedIndex == -1)
						this->x264METype->SelectedIndex = 0;
					if (macroblockOptions->SelectedIndex == -1)
						macroblockOptions->SelectedIndex = 3;
					if (cqmComboBox1->getSelectedIndex() == -1)
						cqmComboBox1->setSelectedIndex(0); // flat matrix
					if (this->avcProfile->SelectedIndex == -1)
						avcProfile->SelectedIndex = 2; // high
					if (cbAQMode->SelectedIndex == -1)
						cbAQMode->SelectedIndex = 1;
					if (x264Tunes->SelectedIndex == -1)
						x264Tunes->SelectedIndex = 0; // Default
					if (cbBPyramid->SelectedIndex == -1)
						cbBPyramid->SelectedIndex = 2;
					lastEncodingMode = this->x264EncodingMode->SelectedIndex;

					try
					{
						std::string p = System::IO::Path::Combine(Application::StartupPath, "Data");
						p = System::IO::Path::Combine(p, "ContextHelp.xml");
						ContextHelp->Load(p);
						SetToolTips();
					}
					catch (...)
					{
						MessageBox::Show("The ContextHelp.xml file could not be found. Please check in the 'Data' directory to see if it exists. Help tooltips will not be available.", "File Not Found", MessageBoxButtons::OK, MessageBoxIcon::Information);
					}

					advancedSettings_CheckedChanged(0, 0); // to open/close advanced tabs
					tbx264Presets_Scroll(0, 0); // to update the trackbar label
				}

				bool x264ConfigurationPanel::isValidSettings(VideoCodecSettings *settings)
				{
					return dynamic_cast<x264Settings*>(settings) != 0;
				}

				MeGUI::VideoCodecSettings *x264ConfigurationPanel::defaultSettings()
				{
					return new x264Settings();
				}

				const MeGUI::x264Settings &x264ConfigurationPanel::getSettings() const
				{
					x264Settings *xs = new x264Settings();
					xs->setDeadZoneInter(static_cast<int>(deadzoneInter->Value));
					xs->setDeadZoneIntra(static_cast<int>(deadzoneIntra->Value));
					xs->setInterlacedMode(static_cast<x264Settings::x264InterlacedModes>(this->cbInterlaceMode->SelectedIndex));
					xs->setNoDCTDecimate(this->noDCTDecimateOption->Checked);
					xs->setSSIMCalculation(this->ssim->Checked);
					xs->setPSNRCalculation(this->psnr->Checked);
					xs->setStitchAble(this->stitchable->Checked);
					xs->setNoFastPSkip(noFastPSkip->Checked);
					xs->setX264SlowFirstpass(this->x264SlowFirstpass->Checked);
					xs->setNoMixedRefs(x264MixedReferences->Checked);
					xs->setEncodingMode(x264EncodingMode->SelectedIndex);
					xs->setBitrateQuantizer(static_cast<int>(x264BitrateQuantizer->Value));
					xs->setQuantizerCRF(x264BitrateQuantizer->Value);
					xs->setKeyframeInterval(static_cast<int>(x264KeyframeInterval->Value));
					xs->setNbRefFrames(static_cast<int>(this->x264NumberOfRefFrames->Value));
					xs->setNbBframes(static_cast<int>(this->x264NumberOfBFrames->Value));
					xs->setNewAdaptiveBFrames(x264NewAdaptiveBframes->SelectedIndex);
					xs->setPsyRDO(this->PsyRD->Value);
					xs->setPsyTrellis(this->PsyTrellis->Value);
					xs->setDeblock(x264DeblockActive->Checked);
					xs->setAlphaDeblock(static_cast<int>(x264AlphaDeblock->Value));
					xs->setBetaDeblock(static_cast<int>(x264BetaDeblock->Value));
					xs->setCabac(cabac->Checked);
					xs->setSubPelRefinement(this->x264SubpelRefinement->SelectedIndex);
					xs->setWeightedBPrediction(x264WeightedBPrediction->Checked);
					xs->setWeightedPPrediction(x264WeightedPPrediction->SelectedIndex);
					xs->setChromaME(this->x264ChromaMe->Checked);
					xs->setX264Trellis(trellis->SelectedIndex);
					xs->setMacroBlockOptions(macroblockOptions->SelectedIndex);
					xs->setP8x8mv(x264P8x8mv->Checked);
					xs->setB8x8mv(x264B8x8mv->Checked);
					xs->setI4x4mv(x264I4x4mv->Checked);
					xs->setI8x8mv(x264I8x8mv->Checked);
					xs->setP4x4mv(x264P4x4mv->Checked);
					xs->setMinQuantizer(static_cast<int>(x264MinimimQuantizer->Value));
					xs->setMaxQuantizer(static_cast<int>(x264MaximumQuantizer->Value));
					xs->setMaxQuantDelta(static_cast<int>(x264MaxQuantDelta->Value));
					xs->setCreditsQuantizer(static_cast<int>(this->x264CreditsQuantizer->Value));
					xs->setChromaQPOffset(this->x264ChromaQPOffset->Value);
					xs->setIPFactor(x264IPFrameFactor->Value);
					xs->setPBFactor(x264PBFrameFactor->Value);
					xs->setVBVBufferSize(static_cast<int>(x264VBVBufferSize->Value));
					xs->setVBVMaxBitrate(static_cast<int>(x264VBVMaxRate->Value));
					xs->setVBVInitialBuffer(x264VBVInitialBuffer->Value);
					xs->setBitrateVariance(x264RateTol->Value);
					xs->setQuantCompression(x264QuantizerCompression->Value);
					xs->setTempComplexityBlur(static_cast<int>(x264TempFrameComplexityBlur->Value));
					xs->setTempQuanBlurCC(x264TempQuantBlur->Value);
					xs->setSCDSensitivity(static_cast<int>(this->x264SCDSensitivity->Value));
					xs->setBframeBias(static_cast<int>(this->x264BframeBias->Value));
					xs->setBframePredictionMode(this->x264BframePredictionMode->SelectedIndex);
					xs->setMEType(this->x264METype->SelectedIndex);
					xs->setMERange(static_cast<int>(x264MERange->Value));
					xs->setNbThreads(static_cast<int>(x264NbThreads->Value));
					xs->setMinGOPSize(static_cast<int>(x264MinGOPSize->Value));
					xs->setLogfile(this->logfile->Text);
					xs->setAdaptiveDCT(adaptiveDCT->Checked);
					xs->setCustomEncoderOptions(customCommandlineOptions->Text);
					if (cqmComboBox1->getSelectedIndex() > 1)
						xs->setQuantizerMatrixType(2);
					else
						xs->setQuantizerMatrixType(cqmComboBox1->getSelectedIndex());
					xs->setQuantizerMatrix(cqmComboBox1->getSelectedText());
					xs->setProfile(avcProfile->SelectedIndex);
					xs->setAVCLevel(getAVCLevel());
					xs->setNoiseReduction(static_cast<int>(NoiseReduction->Value));
					xs->setAQmode(static_cast<int>(cbAQMode->SelectedIndex));
					xs->setAQstrength(numAQStrength->Value);
					xs->setOpenGopValue(chkOpenGop->Checked);
					xs->setColorPrim(static_cast<int>(colorPrim->SelectedIndex));
					xs->setTransfer(static_cast<int>(transfer->SelectedIndex));
					xs->setColorMatrix(static_cast<int>(colorMatrix->SelectedIndex));
					xs->setX264PullDown(static_cast<int>(x264PullDown->SelectedIndex));
					xs->setSampleAR(static_cast<int>(sampleAR->SelectedIndex));
					xs->setPicStruct(picStruct->Checked);
					xs->setFakeInterlaced(fakeInterlaced->Checked);
					xs->setNonDeterministic(nonDeterministic->Checked);
					xs->setUseQPFile(useQPFile->Checked);
					xs->setQPFile(this->qpfile->Text);
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
					xs->setRange(this->x264Range->SelectedItem->ToString());
					xs->setx264PresetLevel(static_cast<x264Settings::x264PresetLevelModes>(this->tbx264Presets->Value));
					xs->setx264PsyTuning(getPsyTuning());
					xs->setTuneFastDecode(chkTuneFastDecode->Checked);
					xs->setTuneZeroLatency(chkTuneZeroLatency->Checked);
					xs->setx264AdvancedSettings(advancedSettings->Checked);
					xs->setNoMBTree(mbtree->Checked);
					xs->setLookahead(static_cast<int>(lookahead->Value));
					xs->setThreadInput(threadin->Checked);
					xs->setNoPsy(nopsy->Checked);
					xs->setScenecut(scenecut->Checked);
					xs->setSlicesNb(static_cast<int>(this->slicesnb->Value));
					xs->setMaxSliceSyzeBytes(static_cast<int>(this->maxSliceSizeBytes->Value));
					xs->setMaxSliceSyzeMBs(static_cast<int>(this->maxSliceSizeMB->Value));
					xs->setx264BFramePyramid(this->cbBPyramid->SelectedIndex);
					xs->setx264GOPCalculation(this->cbGOPCalculation->SelectedIndex);
					xs->setX264Aud(x264aud->Checked);
					xs->setNalhrd(static_cast<int>(x264hrd->SelectedIndex));
					for (std::vector<x264Device*>::const_iterator oDevice = x264DeviceList.begin(); oDevice != x264DeviceList.end(); ++oDevice)
					{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
						if ((*oDevice)->getName()->Equals(targetDevice->SelectedItem->ToString(), StringComparison::CurrentCultureIgnoreCase))
						{
							xs->setTargetDevice(*oDevice);
							break;
						}
					}
					xs->setBlurayCompat(chkBlurayCompat->Checked);
					xs->setX26410Bits(ch10BitsEncoder->Checked);
					return xs;
				}

				void x264ConfigurationPanel::setSettings(const x264Settings &value)
				{ // Warning! The ordering of components matters because of the dependency code!
					x264Settings *xs = value;
					updating = true;
					tbx264Presets->Value = static_cast<int>(xs->getx264PresetLevel());
					if (xs->getProfile() > 2)
						avcProfile->SelectedIndex = 2;
					else
						avcProfile->SelectedIndex = xs->getProfile();
					avcLevel->SelectedItem = EnumProxy::Create(xs->getAVCLevel());
					x264Tunes->SelectedItem = EnumProxy::Create(xs->getx264PsyTuning());
					chkTuneFastDecode->Checked = xs->getTuneFastDecode();
					chkTuneZeroLatency->Checked = xs->getTuneZeroLatency();
					deadzoneInter->Value = xs->getDeadZoneInter();
					deadzoneIntra->Value = xs->getDeadZoneIntra();
					cbInterlaceMode->SelectedIndex = static_cast<int>(xs->getInterlacedMode());
					noDCTDecimateOption->Checked = xs->getNoDCTDecimate();
					ssim->Checked = xs->getSSIMCalculation();
					stitchable->Checked = xs->getStitchAble();
					updateDeviceBlocked = true;
					targetDevice->SelectedItem = xs->getTargetDevice()->getName();
					updateDeviceBlocked = false;
					chkBlurayCompat->Checked = xs->getBlurayCompat();
					x264EncodingMode->SelectedIndex = xs->getEncodingMode();
					doEncodingModeAdjustments();
					this->x264NumberOfRefFrames->Value = xs->getNbRefFrames();
					this->x264NumberOfBFrames->Value = xs->getNbBframes();
					noFastPSkip->Checked = xs->getNoFastPSkip();
					this->x264SubpelRefinement->SelectedIndex = xs->getSubPelRefinement();
					x264SlowFirstpass->Checked = xs->getX264SlowFirstpass();
					x264BitrateQuantizer->Value = (isBitrateMode(xs->getEncodingMode()) || xs->getQuantizerCRF() == 0) ? xs->getBitrateQuantizer() : xs->getQuantizerCRF();
					x264KeyframeInterval->Text = StringConverterHelper::toString(xs->getKeyframeInterval());
					x264NewAdaptiveBframes->SelectedIndex = xs->getNewAdaptiveBFrames();
					x264DeblockActive->Checked = xs->getDeblock();
					x264AlphaDeblock->Value = xs->getAlphaDeblock();
					x264BetaDeblock->Value = xs->getBetaDeblock();
					cabac->Checked = xs->getCabac();
					x264ChromaMe->Checked = xs->getChromaME();
					PsyRD->Value = xs->getPsyRDO();
					trellis->SelectedIndex = xs->getX264Trellis();
					PsyTrellis->Value = xs->getPsyTrellis();
					macroblockOptions->SelectedIndex = xs->getMacroBlockOptions();
					if (macroblockOptions->SelectedIndex != 1)
					{
						adaptiveDCT->Checked = xs->getAdaptiveDCT();
						x264P8x8mv->Checked = xs->getP8x8mv();
						x264B8x8mv->Checked = xs->getB8x8mv();
						x264I4x4mv->Checked = xs->getI4x4mv();
						x264I8x8mv->Checked = xs->getI8x8mv();
						x264P4x4mv->Checked = xs->getP4x4mv();
					}
					x264MinimimQuantizer->Value = xs->getMinQuantizer();
					x264MaximumQuantizer->Value = xs->getMaxQuantizer();
					x264MaxQuantDelta->Value = xs->getMaxQuantDelta();
					this->x264CreditsQuantizer->Value = xs->getCreditsQuantizer();
					x264IPFrameFactor->Value = xs->getIPFactor();
					x264PBFrameFactor->Value = xs->getPBFactor();
					x264ChromaQPOffset->Value = xs->getChromaQPOffset();
					if (xs->getVBVBufferSize() > 0)
					{
						this->x264VBVMaxRate->Enabled = this->x264VBVMaxRateLabel->Enabled = true;
						x264VBVBufferSize->Text = StringConverterHelper::toString(xs->getVBVBufferSize());
					}
					else
					{
						this->x264VBVMaxRate->Enabled = this->x264VBVMaxRateLabel->Enabled = false;
						x264VBVBufferSize->Text = "0";
					}
					if (xs->getVBVMaxBitrate() > 0)
					{
						this->x264VBVMaxRate->Enabled = this->x264VBVMaxRateLabel->Enabled = true;
						x264VBVMaxRate->Text = StringConverterHelper::toString(xs->getVBVMaxBitrate());
					}
					else
					{
						x264VBVBufferSize->Text = "0";
						x264VBVMaxRate->Text = "0";
					}
					x264VBVInitialBuffer->Value = xs->getVBVInitialBuffer();
					x264RateTol->Value = xs->getBitrateVariance();
					x264QuantizerCompression->Value = xs->getQuantCompression();
					x264TempFrameComplexityBlur->Value = xs->getTempComplexityBlur();
					x264TempQuantBlur->Value = xs->getTempQuanBlurCC();
					this->x264SCDSensitivity->Value = xs->getSCDSensitivity();
					this->x264BframeBias->Value = xs->getBframeBias();
					this->x264BframePredictionMode->SelectedIndex = xs->getBframePredictionMode();
					this->x264METype->SelectedIndex = xs->getMEType();
					x264MERange->Value = xs->getMERange();
					x264NbThreads->Value = xs->getNbThreads();
					x264MinGOPSize->Text = StringConverterHelper::toString(xs->getMinGOPSize());
					customCommandlineOptions->Text = xs->getCustomEncoderOptions();
					this->logfile->Text = xs->getLogfile();
					cqmComboBox1->setSelectedObject(xs->getQuantizerMatrix());
					psnr->Checked = xs->getPSNRCalculation();
					cbAQMode->SelectedIndex = xs->getAQmode();
					chkOpenGop->Checked = xs->getOpenGopValue();
					colorPrim->SelectedIndex = xs->getColorPrim();
					transfer->SelectedIndex = xs->getTransfer();
					colorMatrix->SelectedIndex = xs->getColorMatrix();
					x264PullDown->SelectedIndex = xs->getX264PullDown();
					sampleAR->SelectedIndex = xs->getSampleAR();
					picStruct->Checked = xs->getPicStruct();
					fakeInterlaced->Checked = xs->getFakeInterlaced();
					nonDeterministic->Checked = xs->getNonDeterministic();
					x264Range->SelectedItem = xs->getRange();
					numAQStrength->Value = xs->getAQstrength();
					NoiseReduction->Text = StringConverterHelper::toString(xs->getNoiseReduction());
					advancedSettings->Checked = xs->getx264AdvancedSettings();
					lookahead->Value = xs->getLookahead();
					mbtree->Checked = xs->getNoMBTree();
					threadin->Checked = xs->getThreadInput();
					nopsy->Checked = xs->getNoPsy();
					x264MixedReferences->Checked = xs->getNoMixedRefs();
					scenecut->Checked = xs->getScenecut();
					this->slicesnb->Value = xs->getSlicesNb();
					this->maxSliceSizeBytes->Value = xs->getMaxSliceSyzeBytes();
					this->maxSliceSizeMB->Value = xs->getMaxSliceSyzeMBs();
					this->cbBPyramid->SelectedIndex = xs->getx264BFramePyramid();
					this->cbGOPCalculation->SelectedIndex = xs->getx264GOPCalculation();
					x264WeightedBPrediction->Checked = xs->getWeightedBPrediction();
					x264WeightedPPrediction->SelectedIndex = xs->getWeightedPPrediction();
					x264aud->Checked = xs->getX264Aud();
					x264hrd->SelectedIndex = xs->getNalhrd();
					useQPFile->Checked = xs->getUseQPFile();
					this->qpfile->Text = xs->getQPFile();
					ch10BitsEncoder->Checked = xs->getX26410Bits();
					updating = false;
					genericUpdate();
				}

				void x264ConfigurationPanel::updateEvent(object *sender, EventArgs *e)
				{
					genericUpdate();
				}

				void x264ConfigurationPanel::textField_KeyPress(object *sender, KeyPressEventArgs *e)
				{
					if (!isdigit(e->KeyChar) && static_cast<int>(Keys::Back) != static_cast<int>(e->KeyChar))
						e->Handled = true;
				}

				void x264ConfigurationPanel::logfileOpenButton_Click(object *sender, System::EventArgs *e)
				{
					saveFileDialog->Filter = "x264 2pass stats files (*.stats)|*.stats";
					saveFileDialog->FilterIndex = 1;
					if (this->saveFileDialog->ShowDialog() == DialogResult::OK)
					{
						this->logfile->Text = saveFileDialog->FileName;
						this->showCommandLine();
					}
				}

				std::string x264ConfigurationPanel::SelectHelpText(const std::string &node)
				{
					StringBuilder *HelpText = new StringBuilder(64);

					std::string xpath = "/ContextHelp/Codec[@name='x264']/" + node;
					XmlNodeList *nl = ContextHelp->SelectNodes(xpath); // Return the details for the specified node

					if (nl->Count == 1) // if it finds the required HelpText, count should be 1
					{
						HelpText->Append(nl[0]->Attributes["name"]->Value);
						HelpText->AppendLine();
						if (getAdvancedToolTips())
							HelpText->AppendLine(nl[0]["Advanced"]->InnerText);
						else
							HelpText->AppendLine(nl[0]["Basic"]->InnerText);
						HelpText->AppendLine();
						HelpText->AppendLine("Default : " + nl[0]["Default"]->InnerText);
						HelpText->AppendLine("Recommended : " + nl[0]["Recommended"]->InnerText);
					}
					else // If count isn't 1, then theres no valid data.
						HelpText->Append("No help available");

//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
					return (HelpText->ToString());
				}

				void x264ConfigurationPanel::SetToolTips()
				{
					/**********/
					/* Main   */
					/**********/
					tooltipHelp->SetToolTip(avcProfile, SelectHelpText("profile"));
					tooltipHelp->SetToolTip(avcLevel, SelectHelpText("level"));
					tooltipHelp->SetToolTip(x264Tunes, SelectHelpText("tunes"));
					tooltipHelp->SetToolTip(cbTarget, SelectHelpText("targetmode"));
					tooltipHelp->SetToolTip(tbx264Presets, SelectHelpText("presets"));
					tooltipHelp->SetToolTip(x264BitrateQuantizer, SelectHelpText("bitrate"));
					tooltipHelp->SetToolTip(targetDevice, SelectHelpText("device"));
					tooltipHelp->SetToolTip(x264EncodingMode, SelectHelpText("encodingmode"));
					tooltipHelp->SetToolTip(ch10BitsEncoder, SelectHelpText("encoder10bit"));

					/**************/
					/* Frame-Type */
					/**************/
					tooltipHelp->SetToolTip(x264KeyframeInterval, SelectHelpText("keyint"));
					tooltipHelp->SetToolTip(NoiseReduction, SelectHelpText("nr"));
					tooltipHelp->SetToolTip(noFastPSkip, SelectHelpText("no-fast-pskip"));
					tooltipHelp->SetToolTip(macroblockOptions, SelectHelpText("partitions"));
					tooltipHelp->SetToolTip(x264ChromaMe, SelectHelpText("no-chroma-me"));
					tooltipHelp->SetToolTip(x264WeightedBPrediction, SelectHelpText("weightb"));
					tooltipHelp->SetToolTip(x264WeightedPPrediction, SelectHelpText("weightp"));
					tooltipHelp->SetToolTip(x264SubpelRefinement, SelectHelpText("subme"));
					tooltipHelp->SetToolTip(cabac, SelectHelpText("no-cabac"));
					tooltipHelp->SetToolTip(x264DeblockActive, SelectHelpText("nf"));
					tooltipHelp->SetToolTip(x264NewAdaptiveBframes, SelectHelpText("b-adapt"));
					tooltipHelp->SetToolTip(x264NumberOfRefFrames, SelectHelpText("ref"));
					tooltipHelp->SetToolTip(x264NumberOfBFrames, SelectHelpText("bframes"));
					tooltipHelp->SetToolTip(x264AlphaDeblock, SelectHelpText("filter"));
					tooltipHelp->SetToolTip(x264BetaDeblock, SelectHelpText("filter"));
					tooltipHelp->SetToolTip(x264CreditsQuantizer, SelectHelpText("creditsquant"));
					tooltipHelp->SetToolTip(x264IPFrameFactor, SelectHelpText("ipratio"));
					tooltipHelp->SetToolTip(x264PBFrameFactor, SelectHelpText("pbratio"));
					tooltipHelp->SetToolTip(x264ChromaQPOffset, SelectHelpText("chroma-qp-offset"));
					tooltipHelp->SetToolTip(cbBPyramid, SelectHelpText("b-pyramid"));
					tooltipHelp->SetToolTip(x264SlowFirstpass, SelectHelpText("slow-firstpass"));
					tooltipHelp->SetToolTip(cbInterlaceMode, SelectHelpText("interlaced"));
					tooltipHelp->SetToolTip(x264PullDown, SelectHelpText("pulldown"));
					tooltipHelp->SetToolTip(scenecut, SelectHelpText("noscenecut"));
					tooltipHelp->SetToolTip(chkOpenGop, SelectHelpText("opengop"));
					tooltipHelp->SetToolTip(slicesnb, SelectHelpText("slicesnb"));
					tooltipHelp->SetToolTip(maxSliceSizeBytes, SelectHelpText("maxSliceSizeBytes"));
					tooltipHelp->SetToolTip(maxSliceSizeMB, SelectHelpText("maxSliceSizeMB"));
					tooltipHelp->SetToolTip(x264MinGOPSize, SelectHelpText("min-keyint"));
					tooltipHelp->SetToolTip(x264SCDSensitivity, SelectHelpText("scenecut"));
					tooltipHelp->SetToolTip(x264BframeBias, SelectHelpText("b-bias"));
					tooltipHelp->SetToolTip(x264BframePredictionMode, SelectHelpText("direct"));
					tooltipHelp->SetToolTip(cbGOPCalculation, SelectHelpText("gopcalculation"));

					/*************************/
					/* Rate Control Tooltips */
					/*************************/
					tooltipHelp->SetToolTip(x264MinimimQuantizer, SelectHelpText("qpmin"));
					tooltipHelp->SetToolTip(x264MaximumQuantizer, SelectHelpText("qpmax"));
					tooltipHelp->SetToolTip(x264MaxQuantDelta, SelectHelpText("qpstep"));
					tooltipHelp->SetToolTip(x264VBVBufferSize, SelectHelpText("vbv-bufsize"));
					tooltipHelp->SetToolTip(x264VBVMaxRate, SelectHelpText("vbv-maxrate"));
					tooltipHelp->SetToolTip(x264VBVInitialBuffer, SelectHelpText("vbv-init"));
					tooltipHelp->SetToolTip(x264RateTol, SelectHelpText("ratetol"));
					tooltipHelp->SetToolTip(x264QuantizerCompression, SelectHelpText("qcomp"));
					tooltipHelp->SetToolTip(x264TempFrameComplexityBlur, SelectHelpText("cplxblur"));
					tooltipHelp->SetToolTip(x264TempQuantBlur, SelectHelpText("qblur"));
					tooltipHelp->SetToolTip(mbtree, SelectHelpText("mbtree"));
					tooltipHelp->SetToolTip(lookahead, SelectHelpText("lookahead"));
					tooltipHelp->SetToolTip(deadzoneInter, SelectHelpText("deadzoneInter"));
					tooltipHelp->SetToolTip(deadzoneIntra, SelectHelpText("deadzoneIntra"));
					tooltipHelp->SetToolTip(cqmComboBox1, SelectHelpText("cqm"));

					/*************************/
					/* Analysis Tooltips */
					/*************************/
					tooltipHelp->SetToolTip(cbAQMode, SelectHelpText("aqmode"));
					tooltipHelp->SetToolTip(numAQStrength, SelectHelpText("aqstrength"));
					tooltipHelp->SetToolTip(macroblockOptions, SelectHelpText("analyse"));
					tooltipHelp->SetToolTip(adaptiveDCT, SelectHelpText("i8x8dct"));
					tooltipHelp->SetToolTip(x264B8x8mv, SelectHelpText("b8x8mv"));
					tooltipHelp->SetToolTip(x264P8x8mv, SelectHelpText("p8x8mv"));
					tooltipHelp->SetToolTip(x264P4x4mv, SelectHelpText("p4x4mv"));
					tooltipHelp->SetToolTip(x264I4x4mv, SelectHelpText("i4x4mv"));
					tooltipHelp->SetToolTip(x264I8x8mv, SelectHelpText("i8x8mv"));
					tooltipHelp->SetToolTip(x264aud, SelectHelpText("aud"));
					tooltipHelp->SetToolTip(x264hrd, SelectHelpText("nalhrd"));
					tooltipHelp->SetToolTip(noDCTDecimateOption, SelectHelpText("noDCTDecimateOption"));
					tooltipHelp->SetToolTip(nopsy, SelectHelpText("nopsy"));
					tooltipHelp->SetToolTip(fakeInterlaced, SelectHelpText("fakeInterlaced"));
					tooltipHelp->SetToolTip(chkBlurayCompat, SelectHelpText("blurayCompat"));
					tooltipHelp->SetToolTip(x264MixedReferences, SelectHelpText("mixed-refs"));
					tooltipHelp->SetToolTip(PsyRD, SelectHelpText("psyrd"));
					tooltipHelp->SetToolTip(PsyTrellis, SelectHelpText("psytrellis"));
					tooltipHelp->SetToolTip(trellis, SelectHelpText("trellis"));
					tooltipHelp->SetToolTip(x264METype, SelectHelpText("me"));
					tooltipHelp->SetToolTip(x264MERange, SelectHelpText("merange"));

					/**************************/
					/* Misc Tooltips */
					/**************************/
					tooltipHelp->SetToolTip(x264NbThreads, SelectHelpText("threads"));
					tooltipHelp->SetToolTip(psnr, SelectHelpText("psnr"));
					tooltipHelp->SetToolTip(ssim, SelectHelpText("ssim"));
					tooltipHelp->SetToolTip(stitchable, SelectHelpText("stitchable"));
					tooltipHelp->SetToolTip(logfile, SelectHelpText("logfile"));
					tooltipHelp->SetToolTip(customCommandlineOptions, SelectHelpText("customcommandline"));
					tooltipHelp->SetToolTip(qpfile, SelectHelpText("qpf"));
					tooltipHelp->SetToolTip(useQPFile, SelectHelpText("qpf"));
					tooltipHelp->SetToolTip(sampleAR, SelectHelpText("sampleAR"));
					tooltipHelp->SetToolTip(x264Range, SelectHelpText("x264Range"));
					tooltipHelp->SetToolTip(picStruct, SelectHelpText("picStruct"));
					tooltipHelp->SetToolTip(colorPrim, SelectHelpText("colorPrim"));
					tooltipHelp->SetToolTip(colorMatrix, SelectHelpText("colorMatrix"));
					tooltipHelp->SetToolTip(transfer, SelectHelpText("transfer"));
					tooltipHelp->SetToolTip(nonDeterministic, SelectHelpText("nonDeterministic"));
					tooltipHelp->SetToolTip(threadin, SelectHelpText("threadin"));
					tooltipHelp->SetToolTip(chkTuneFastDecode, SelectHelpText("fastdecode"));
					tooltipHelp->SetToolTip(chkTuneZeroLatency, SelectHelpText("zerolatency"));

				}

				void x264ConfigurationPanel::x264DialogTriStateAdjustment()
				{
					bool turboOptions = this->x264SlowFirstpass->Checked && (this->x264EncodingMode->SelectedIndex == static_cast<int>(VideoCodecSettings::threepass1) || this->x264EncodingMode->SelectedIndex == static_cast<int>(VideoCodecSettings::twopass1));

					// First we do the Profile Adjustments
					switch (avcProfile->SelectedIndex)
					{
						case 0: // baseline, disable cabac, b-frames and i8x8
							cabac->Checked = false;
							cabac->Enabled = false;
							x264NumberOfBFrames->Value = 0;
							x264NumberOfBFrames->Enabled = false;
							x264NumberOfBFramesLabel->Enabled = false;
							cqmComboBox1->setSelectedIndex(0);
							quantizerMatrixGroupbox->Enabled = false;
							break;
						case 1: // main profile, disable i8x8
							if (!x264NumberOfBFrames->Enabled)
							{
								x264NumberOfBFrames->Enabled = true;
								x264NumberOfBFrames->Value = 3;
								x264NumberOfBFramesLabel->Enabled = true;
								x264WeightedBPrediction->Checked = true;
							}
							cqmComboBox1->setSelectedIndex(0);
							quantizerMatrixGroupbox->Enabled = false;
							if (!chkTuneFastDecode->Checked && !cabac->Enabled)
							{
								cabac->Enabled = true;
								cabac->Checked = true;
							}
							break;
						case 2: // high profile, enable everything
							if (!x264NumberOfBFrames->Enabled)
							{
								x264NumberOfBFrames->Enabled = true;
								x264NumberOfBFrames->Value = 3;
								x264NumberOfBFramesLabel->Enabled = true;
								x264WeightedBPrediction->Checked = true;
							}
							if (!adaptiveDCT->Enabled)
							{
								adaptiveDCT->Enabled = true;
								adaptiveDCT->Checked = true;
							}
							quantizerMatrixGroupbox->Enabled = true;
							if (!chkTuneFastDecode->Checked && !cabac->Enabled)
							{
								cabac->Enabled = true;
								cabac->Checked = true;
							}
							break;
					}

					// Now we do B frames adjustments
					if (this->x264NumberOfBFrames->Value == 0)
					{
						this->x264NewAdaptiveBframes->Enabled = false;
						this->x264AdaptiveBframesLabel->Enabled = false;
						this->x264BframePredictionMode->Enabled = false;
						this->x264BframePredictionModeLabel->Enabled = false;
						this->x264WeightedBPrediction->Checked = false;
						this->x264WeightedBPrediction->Enabled = false;
						this->x264BframeBias->Value = 0;
						this->x264BframeBias->Enabled = false;
						this->x264BframeBiasLabel->Enabled = false;
						this->cbBPyramid->Enabled = false;
					}
					else
					{
						this->x264NewAdaptiveBframes->Enabled = true;
						this->x264AdaptiveBframesLabel->Enabled = true;
						this->x264BframePredictionMode->Enabled = true;
						this->x264BframePredictionModeLabel->Enabled = true;
						this->x264WeightedBPrediction->Enabled = true;
						// We can enable these if we don't have turbo options
						this->x264BframeBias->Enabled = true;
						this->x264BframeBiasLabel->Enabled = true;
						if (this->x264NumberOfBFrames->Value >= 2) // pyramid requires at least two b-frames
							this->cbBPyramid->Enabled = true;
						else
							this->cbBPyramid->Enabled = false;
					}

					// Now we do some additional checks -- ref frames, cabac
					if (!x264VBVBufferSize->Text->empty())
					{
						this->x264VBVMaxRate->Enabled = true;
						this->x264VBVMaxRateLabel->Enabled = true;
					}
					if (this->x264NumberOfRefFrames->Value > 1) // mixed references require at least two reference frames
					{
						if (!this->x264MixedReferences->Enabled)
							this->x264MixedReferences->Enabled = true;
					}
					else
						this->x264MixedReferences->Enabled = false;

					if (this->x264SubpelRefinement->SelectedIndex > 4)
					{
						this->PsyRD->Enabled = true;
						this->PsyRDLabel->Enabled = true;
					}
					else
					{
						this->PsyRD->Enabled = false;
						this->PsyRDLabel->Enabled = false;
					}
					if (this->trellis->SelectedIndex > 0)
					{
						this->PsyTrellis->Enabled = true;
						this->PsyTrellisLabel->Enabled = true;
					}
					else
					{
						this->PsyTrellis->Enabled = false;
						this->PsyTrellisLabel->Enabled = false;
						switch (getPsyTuning())
						{
							case x264Settings::FILM:
								this->PsyTrellis->Value = 0.15;
								break;
							case x264Settings::GRAIN:
								this->PsyTrellis->Value = 0.25;
								break;
							default:
								this->PsyTrellis->Value = 0;
								break;
						}
					}
				}

				void x264ConfigurationPanel::cqmComboBox1_SelectionChanged(object *sender, const std::string &val)
				{
					genericUpdate();
				}

				void x264ConfigurationPanel::VisitLink()
				{
					try
					{
						//Call the Process.Start method to open the default browser 
						//with a URL:
						System::Diagnostics::Process::Start("http://www.videolan.org/developers/x264.html");
					}
					catch (std::exception &e1)
					{
						MessageBox::Show("Unable to open link that was clicked.");
					}
				}

				void x264ConfigurationPanel::cbAQMode_SelectedIndexChanged(object *sender, EventArgs *e)
				{
					if (cbAQMode->SelectedIndex != 0)
						numAQStrength->Enabled = true;
					else
						numAQStrength->Enabled = false;
					genericUpdate();
				}

				void x264ConfigurationPanel::useQPFile_CheckedChanged(object *sender, EventArgs *e)
				{
					qpfile->Enabled = useQPFile->Checked;
					qpfileOpenButton->Enabled = useQPFile->Checked;
				}

				void x264ConfigurationPanel::qpfileOpenButton_Click(object *sender, EventArgs *e)
				{
					openFileDialog->Filter = "x264 QP Files (*.qpf, *.txt)|*.qpf;*.txt";
					openFileDialog->FilterIndex = 1;
					openFileDialog->FileName = "";
					if (this->openFileDialog->ShowDialog() == DialogResult::OK)
					{
						this->qpfile->Text = openFileDialog->FileName;
						this->showCommandLine();
					}
				}

				void x264ConfigurationPanel::tbx264Presets_Scroll(object *sender, EventArgs *e)
				{
					switch (tbx264Presets->Value)
					{
						case 0:
							lbPreset->Text = "Ultra Fast";
							break;
						case 1:
							lbPreset->Text = "Super Fast";
							break;
						case 2:
							lbPreset->Text = "Very Fast";
							break;
						case 3:
							lbPreset->Text = "Faster";
							break;
						case 4:
							lbPreset->Text = "Fast";
							break;
						case 5:
							lbPreset->Text = "Medium";
							break;
						case 6:
							lbPreset->Text = "Slow";
							break;
						case 7:
							lbPreset->Text = "Slower";
							break;
						case 8:
							lbPreset->Text = "Very Slow";
							break;
						case 9:
							lbPreset->Text = "Placebo";
							break;
					}
					if (sender != 0) // workaround so that the first loaded profile will not be overwritten
						doPresetsAdjustments();
					genericUpdate();
				}

				void x264ConfigurationPanel::advancedSettings_CheckedChanged(object *sender, EventArgs *e)
				{
					if (advancedSettings->Checked)
					{
						if (!tabControl1->TabPages->Contains(FrameTypeTabPage))
							tabControl1->TabPages->Add(FrameTypeTabPage);
						if (!tabControl1->TabPages->Contains(RCTabPage))
							tabControl1->TabPages->Add(RCTabPage);
						if (!tabControl1->TabPages->Contains(AnalysisTabPage))
							tabControl1->TabPages->Add(AnalysisTabPage);
						if (!tabControl1->TabPages->Contains(MiscTabPage))
							tabControl1->TabPages->Add(MiscTabPage);
						x264EncodingMode->Visible = true;
						cbTarget->Visible = false;
						avcProfileGroupbox->Enabled = !ch10BitsEncoder->Checked;
						avcLevelGroupbox->Enabled = true;
						ch10BitsEncoder->Visible = MainForm::Instance->getSettings()->Is10Bitx264Available();
					}
					else
					{
						if (tabControl1->TabPages->Contains(FrameTypeTabPage))
							tabControl1->TabPages->Remove(FrameTypeTabPage);
						if (tabControl1->TabPages->Contains(RCTabPage))
							tabControl1->TabPages->Remove(RCTabPage);
						if (tabControl1->TabPages->Contains(AnalysisTabPage))
							tabControl1->TabPages->Remove(AnalysisTabPage);
						if (tabControl1->TabPages->Contains(MiscTabPage))
							tabControl1->TabPages->Remove(MiscTabPage);
						x264EncodingMode->Visible = false;
						cbTarget->Visible = true;
						avcProfileGroupbox->Enabled = false;
						avcLevelGroupbox->Enabled = false;
						ch10BitsEncoder->Visible = false;
					}
					genericUpdate();
				}

				void x264ConfigurationPanel::dSettings_Click(object *sender, EventArgs *e)
				{
					// Main Tab
					this->x264EncodingMode->SelectedIndex = 9;
					this->x264BitrateQuantizer->Value = 23;
					this->x264Tunes->SelectedIndex = 0;
					this->tbx264Presets->Value = 5;
					this->avcProfile->SelectedIndex = 2;
					this->avcLevel->SelectedItem = EnumProxy::Create(AVCLevels::L_UNRESTRICTED);
					this->advancedSettings->Checked = true;
					this->targetDevice->SelectedIndex = 0;
					this->ch10BitsEncoder->Enabled = false;
					this->ch10BitsEncoder->Checked = false;

					// Frame-Type Tab
					this->x264DeblockActive->Checked = true;
					this->x264AlphaDeblock->Value = 0;
					this->x264BetaDeblock->Value = 0;
					this->cabac->Checked = true;
					this->x264KeyframeInterval->Text = "250";
					this->x264MinGOPSize->Text = "25";
					this->chkOpenGop->Checked = false;
					this->slicesnb->Value = 0;
					this->maxSliceSizeBytes->Value = 0;
					this->maxSliceSizeMB->Value = 0;
					this->x264WeightedBPrediction->Checked = true;
					this->x264NumberOfBFrames->Value = 3;
					this->x264BframeBias->Value = 0;
					this->x264NewAdaptiveBframes->SelectedIndex = 1;
					this->cbBPyramid->SelectedIndex = 2;
					this->x264NumberOfRefFrames->Value = 3;
					this->x264SCDSensitivity->Value = 40;
					this->x264WeightedPPrediction->SelectedIndex = 2;
					this->cbInterlaceMode->SelectedIndex = static_cast<int>(x264Settings::progressive);
					this->x264PullDown->SelectedIndex = 0;
					this->scenecut->Checked = true;
					this->cbGOPCalculation->SelectedIndex = 1;

					// Rate Control Tab
					this->x264MinimimQuantizer->Value = 0;
					this->x264MaximumQuantizer->Value = 69;
					this->x264MaxQuantDelta->Value = 4;
					this->x264IPFrameFactor->Value = 1.4;
					this->x264PBFrameFactor->Value = 1.3;
					this->deadzoneInter->Value = 0;
					this->deadzoneIntra->Value = 0;
					this->x264ChromaQPOffset->Value = 0;
					this->x264CreditsQuantizer->Value = 40;
					this->x264VBVBufferSize->Text = "0";
					this->x264VBVMaxRate->Text = "0";
					this->x264VBVInitialBuffer->Value = 0.9;
					this->x264RateTol->Value = 1.0;
					this->x264QuantizerCompression->Value = 0.6;
					this->x264TempFrameComplexityBlur->Value = 20;
					this->x264TempQuantBlur->Value = 0.5;
					this->lookahead->Value = 40;
					this->cbAQMode->SelectedIndex = 1;
					this->numAQStrength->Value = 1.0;
					this->mbtree->Checked = true;
					this->cqmComboBox1->setSelectedIndex(0);

					// Analysis Tab
					this->x264ChromaMe->Checked = true;
					this->x264MERange->Value = 16;
					this->x264METype->SelectedIndex = 1;
					this->x264SubpelRefinement->SelectedIndex = 7;
					this->x264BframePredictionMode->SelectedIndex = 1;
					this->trellis->SelectedIndex = 1;
					this->PsyRD->Value = 1.0;
					this->PsyTrellis->Value = 0.0;
					this->x264MixedReferences->Checked = false;
					this->noDCTDecimateOption->Checked = false;
					this->noFastPSkip->Checked = false;
					this->nopsy->Checked = false;
					this->NoiseReduction->Text = "0";
					this->macroblockOptions->SelectedIndex = 3;
					this->adaptiveDCT->Checked = true;
					this->x264I4x4mv->Checked = true;
					this->x264P4x4mv->Checked = false;
					this->x264I8x8mv->Checked = true;
					this->x264P8x8mv->Checked = true;
					this->x264B8x8mv->Checked = true;
					this->x264hrd->SelectedIndex = 0;
					this->x264aud->Checked = false;
					this->fakeInterlaced->Checked = false;
					this->chkBlurayCompat->Checked = false;

					// Misc Tab
					this->useQPFile->Checked = false;
					this->psnr->Checked = false;
					this->ssim->Checked = false;
					this->sampleAR->SelectedIndex = 0;
					this->x264Range->SelectedIndex = 0;
					this->picStruct->Checked = false;
					this->colorPrim->SelectedIndex = 0;
					this->transfer->SelectedIndex = 0;
					this->colorMatrix->SelectedIndex = 0;
					this->x264SlowFirstpass->Checked = false;
					this->threadin->Checked = true;
					this->x264NbThreads->Value = 0;
					this->nonDeterministic->Checked = false;
					this->chkTuneFastDecode->Checked = false;
					this->chkTuneZeroLatency->Checked = false;
					this->stitchable->Checked = false;

					// to update presets label
					tbx264Presets_Scroll(0, 0);
				}

				void x264ConfigurationPanel::btPresetSettings_Click(object *sender, EventArgs *e)
				{
					doPresetsAdjustments();
					doTuningsAdjustments();
				}

				void x264ConfigurationPanel::x264Tunes_SelectedIndexChanged(object *sender, EventArgs *e)
				{
					doTuningsAdjustments();
					genericUpdate();
				}

				void x264ConfigurationPanel::avcProfile_SelectedIndexChanged(object *sender, EventArgs *e)
				{
					if (this->x264NumberOfBFrames->Value != x264Settings::GetDefaultNumberOfBFrames(static_cast<x264Settings::x264PresetLevelModes>(tbx264Presets->Value), getPsyTuning(), chkTuneZeroLatency->Checked, avcProfile->SelectedIndex, oTargetDevice, chkBlurayCompat->Checked))
						this->x264NumberOfBFrames->Value = x264Settings::GetDefaultNumberOfBFrames(static_cast<x264Settings::x264PresetLevelModes>(tbx264Presets->Value), getPsyTuning(), chkTuneZeroLatency->Checked, avcProfile->SelectedIndex, oTargetDevice, chkBlurayCompat->Checked);
					if (this->x264WeightedPPrediction->SelectedIndex != x264Settings::GetDefaultNumberOfWeightp(static_cast<x264Settings::x264PresetLevelModes>(tbx264Presets->Value), chkTuneFastDecode->Checked, avcProfile->SelectedIndex, chkBlurayCompat->Checked))
						this->x264WeightedPPrediction->SelectedIndex = x264Settings::GetDefaultNumberOfWeightp(static_cast<x264Settings::x264PresetLevelModes>(tbx264Presets->Value), chkTuneFastDecode->Checked, avcProfile->SelectedIndex, chkBlurayCompat->Checked);

					avcLevel_SelectedIndexChanged(0, 0);
				}

				void x264ConfigurationPanel::cbTarget_SelectionChangeCommitted(object *sender, EventArgs *e)
				{
					if (cbTarget->SelectedIndex == 0)
					{
						if (MainForm::Instance->getSettings()->getNbPasses() == 3)
							x264EncodingMode->SelectedIndex = 8;
						else
							x264EncodingMode->SelectedIndex = 4;
					}
					else
					{
						x264EncodingMode->SelectedIndex = 9;
					}
				}

				void x264ConfigurationPanel::pictureBox1_Click(object *sender, EventArgs *e)
				{
					VisitLink();
				}

				void x264ConfigurationPanel::targetDevice_SelectedIndexChanged(object *sender, EventArgs *e)
				{
					oTargetDevice = x264DeviceList[0];
					for (std::vector<x264Device*>::const_iterator oDevice = x264DeviceList.begin(); oDevice != x264DeviceList.end(); ++oDevice)
					{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
						if ((*oDevice)->getName()->Equals(targetDevice->SelectedItem->ToString(), StringComparison::CurrentCultureIgnoreCase))
						{
							oTargetDevice = *oDevice;
							break;
						}
					}

					if (!updateDeviceBlocked)
						updateDevice = true;
					genericUpdate();
					updateDevice = false;
				}

				MeGUI::x264Settings::x264PsyTuningModes x264ConfigurationPanel::getPsyTuning()
				{
					EnumProxy *o = dynamic_cast<EnumProxy*>(x264Tunes->SelectedItem);
					return static_cast<x264Settings::x264PsyTuningModes>(o->getRealValue());
				}

				MeGUI::AVCLevels::Levels x264ConfigurationPanel::getAVCLevel()
				{
					EnumProxy *o = dynamic_cast<EnumProxy*>(avcLevel->SelectedItem);
					return static_cast<AVCLevels::Levels>(o->getRealValue());
				}

				void x264ConfigurationPanel::avcLevel_SelectedIndexChanged(object *sender, EventArgs *e)
				{
					AVCLevels::Levels avcLevel = getAVCLevel();
					if (avcLevel == AVCLevels::L_UNRESTRICTED || avcProfile->SelectedIndex < 0)
					{
						x264VBVBufferSize->Value = 0;
						x264VBVMaxRate->Value = 0;
					}
					else
					{
						AVCLevels *al = new AVCLevels();
						x264VBVBufferSize->Value = al->getMaxCBP(avcLevel, avcProfile->SelectedIndex == 2);
						x264VBVMaxRate->Value = al->getMaxBR(avcLevel, avcProfile->SelectedIndex == 2);
					}
					genericUpdate();
				}

				void x264ConfigurationPanel::x264VBVBufferSize_ValueChanged(object *sender, EventArgs *e)
				{
					x264VBVBufferSize->ForeColor = System::Drawing::SystemColors::WindowText;
					AVCLevels::Levels avcLevel = getAVCLevel();
					if (avcLevel != AVCLevels::L_UNRESTRICTED && avcProfile->SelectedIndex >= 0)
					{
						AVCLevels *al = new AVCLevels();
						if (x264VBVBufferSize->Value <= 0 || x264VBVBufferSize->Value > al->getMaxCBP(avcLevel, avcProfile->SelectedIndex == 2))
							x264VBVBufferSize->ForeColor = System::Drawing::Color::Red;
					}
					updateEvent(sender, e);
				}

				void x264ConfigurationPanel::x264VBVMaxRate_ValueChanged(object *sender, EventArgs *e)
				{
					x264VBVMaxRate->ForeColor = System::Drawing::SystemColors::WindowText;
					AVCLevels::Levels avcLevel = getAVCLevel();
					if (avcLevel != AVCLevels::L_UNRESTRICTED && avcProfile->SelectedIndex >= 0)
					{
						AVCLevels *al = new AVCLevels();
						if (x264VBVMaxRate->Value <= 0 || x264VBVMaxRate->Value > al->getMaxBR(avcLevel, avcProfile->SelectedIndex == 2))
							x264VBVMaxRate->ForeColor = System::Drawing::Color::Red;
					}
					updateEvent(sender, e);
				}

				void x264ConfigurationPanel::ch10BitsEncoder_CheckedChanged(object *sender, EventArgs *e)
				{
					avcProfileGroupbox->Enabled = !ch10BitsEncoder->Checked;
					updateEvent(sender, e);
				}

				void x264ConfigurationPanel::Dispose(bool disposing)
				{
					if (disposing && (components != 0))
					{
						delete components;
					}
					MeGUI::core::details::video::VideoConfigurationPanel::Dispose(disposing);
				}

				void x264ConfigurationPanel::InitializeComponent()
				{
					System::ComponentModel::ComponentResourceManager *resources = new System::ComponentModel::ComponentResourceManager(x264ConfigurationPanel::typeid);
					this->x264CodecGeneralGroupbox = new System::Windows::Forms::GroupBox();
					this->cbTarget = new System::Windows::Forms::ComboBox();
					this->x264BitrateQuantizer = new System::Windows::Forms::NumericUpDown();
					this->x264EncodingMode = new System::Windows::Forms::ComboBox();
					this->x264BitrateQuantizerLabel = new System::Windows::Forms::Label();
					this->FrameTypeTabPage = new System::Windows::Forms::TabPage();
					this->gbSlicing = new System::Windows::Forms::GroupBox();
					this->maxSliceSizeMB = new System::Windows::Forms::NumericUpDown();
					this->label11 = new System::Windows::Forms::Label();
					this->maxSliceSizeBytes = new System::Windows::Forms::NumericUpDown();
					this->label10 = new System::Windows::Forms::Label();
					this->slicesnb = new System::Windows::Forms::NumericUpDown();
					this->label9 = new System::Windows::Forms::Label();
					this->gbFTOther = new System::Windows::Forms::GroupBox();
					this->cbInterlaceMode = new System::Windows::Forms::ComboBox();
					this->lblInterlacedMode = new System::Windows::Forms::Label();
					this->x264PullDown = new System::Windows::Forms::ComboBox();
					this->pullDownLabel = new System::Windows::Forms::Label();
					this->lblWeightedP = new System::Windows::Forms::Label();
					this->x264WeightedPPrediction = new System::Windows::Forms::ComboBox();
					this->lbExtraIFframes = new System::Windows::Forms::Label();
					this->scenecut = new System::Windows::Forms::CheckBox();
					this->x264NumberOfRefFrames = new System::Windows::Forms::NumericUpDown();
					this->label6 = new System::Windows::Forms::Label();
					this->x264SCDSensitivity = new System::Windows::Forms::NumericUpDown();
					this->x264GeneralBFramesgGroupbox = new System::Windows::Forms::GroupBox();
					this->label12 = new System::Windows::Forms::Label();
					this->cbBPyramid = new System::Windows::Forms::ComboBox();
					this->x264WeightedBPrediction = new System::Windows::Forms::CheckBox();
					this->x264BframeBias = new System::Windows::Forms::NumericUpDown();
					this->x264BframeBiasLabel = new System::Windows::Forms::Label();
					this->x264AdaptiveBframesLabel = new System::Windows::Forms::Label();
					this->x264NewAdaptiveBframes = new System::Windows::Forms::ComboBox();
					this->x264NumberOfBFramesLabel = new System::Windows::Forms::Label();
					this->x264NumberOfBFrames = new System::Windows::Forms::NumericUpDown();
					this->gbH264Features = new System::Windows::Forms::GroupBox();
					this->cabac = new System::Windows::Forms::CheckBox();
					this->x264BetaDeblock = new System::Windows::Forms::NumericUpDown();
					this->x264AlphaDeblock = new System::Windows::Forms::NumericUpDown();
					this->x264DeblockActive = new System::Windows::Forms::CheckBox();
					this->x264BetaDeblockLabel = new System::Windows::Forms::Label();
					this->x264AlphaDeblockLabel = new System::Windows::Forms::Label();
					this->gbGOPSize = new System::Windows::Forms::GroupBox();
					this->label19 = new System::Windows::Forms::Label();
					this->cbGOPCalculation = new System::Windows::Forms::ComboBox();
					this->chkOpenGop = new System::Windows::Forms::CheckBox();
					this->x264KeyframeIntervalLabel = new System::Windows::Forms::Label();
					this->x264KeyframeInterval = new System::Windows::Forms::NumericUpDown();
					this->x264MinGOPSize = new System::Windows::Forms::NumericUpDown();
					this->x264MinGOPSizeLabel = new System::Windows::Forms::Label();
					this->RCTabPage = new System::Windows::Forms::TabPage();
					this->x264RCGroupbox = new System::Windows::Forms::GroupBox();
					this->mbtree = new System::Windows::Forms::CheckBox();
					this->label8 = new System::Windows::Forms::Label();
					this->lookahead = new System::Windows::Forms::NumericUpDown();
					this->x264RateTolLabel = new System::Windows::Forms::Label();
					this->x264VBVInitialBuffer = new System::Windows::Forms::NumericUpDown();
					this->x264VBVInitialBufferLabel = new System::Windows::Forms::Label();
					this->x264VBVMaxRate = new System::Windows::Forms::NumericUpDown();
					this->x264TempQuantBlur = new System::Windows::Forms::NumericUpDown();
					this->x264TempFrameComplexityBlur = new System::Windows::Forms::NumericUpDown();
					this->x264QuantizerCompression = new System::Windows::Forms::NumericUpDown();
					this->x264VBVBufferSize = new System::Windows::Forms::NumericUpDown();
					this->x264TempQuantBlurLabel = new System::Windows::Forms::Label();
					this->x264TempFrameComplexityBlurLabel = new System::Windows::Forms::Label();
					this->x264QuantizerCompressionLabel = new System::Windows::Forms::Label();
					this->x264VBVMaxRateLabel = new System::Windows::Forms::Label();
					this->x264VBVBufferSizeLabel = new System::Windows::Forms::Label();
					this->x264RateTol = new System::Windows::Forms::NumericUpDown();
					this->gbAQ = new System::Windows::Forms::GroupBox();
					this->numAQStrength = new System::Windows::Forms::NumericUpDown();
					this->lbAQStrength = new System::Windows::Forms::Label();
					this->cbAQMode = new System::Windows::Forms::ComboBox();
					this->lbAQMode = new System::Windows::Forms::Label();
					this->quantizerMatrixGroupbox = new System::Windows::Forms::GroupBox();
					this->cqmComboBox1 = new MeGUI::core::gui::FileSCBox();
					this->x264QuantizerGroupBox = new System::Windows::Forms::GroupBox();
					this->deadzoneIntra = new System::Windows::Forms::NumericUpDown();
					this->deadzoneInter = new System::Windows::Forms::NumericUpDown();
					this->lbx264DeadZones = new System::Windows::Forms::Label();
					this->x264PBFrameFactor = new System::Windows::Forms::NumericUpDown();
					this->x264IPFrameFactor = new System::Windows::Forms::NumericUpDown();
					this->lbQuantizersRatio = new System::Windows::Forms::Label();
					this->x264CreditsQuantizer = new System::Windows::Forms::NumericUpDown();
					this->x264CreditsQuantizerLabel = new System::Windows::Forms::Label();
					this->x264ChromaQPOffset = new System::Windows::Forms::NumericUpDown();
					this->x264ChromaQPOffsetLabel = new System::Windows::Forms::Label();
					this->x264MaxQuantDelta = new System::Windows::Forms::NumericUpDown();
					this->x264MaximumQuantizer = new System::Windows::Forms::NumericUpDown();
					this->x264MinimimQuantizer = new System::Windows::Forms::NumericUpDown();
					this->x264MinimimQuantizerLabel = new System::Windows::Forms::Label();
					this->label3 = new System::Windows::Forms::Label();
					this->label2 = new System::Windows::Forms::Label();
					this->customCommandlineOptionsLabel = new System::Windows::Forms::Label();
					this->saveFileDialog = new System::Windows::Forms::SaveFileDialog();
					this->openFileDialog = new System::Windows::Forms::OpenFileDialog();
					this->helpButton1 = new MeGUI::core::gui::HelpButton();
					this->gbPresets = new System::Windows::Forms::GroupBox();
					this->lbPreset = new System::Windows::Forms::Label();
					this->tbx264Presets = new System::Windows::Forms::TrackBar();
					this->gbTunes = new System::Windows::Forms::GroupBox();
					this->x264Tunes = new System::Windows::Forms::ComboBox();
					this->AnalysisTabPage = new System::Windows::Forms::TabPage();
					this->x264Bluray = new System::Windows::Forms::GroupBox();
					this->chkBlurayCompat = new System::Windows::Forms::CheckBox();
					this->fakeInterlaced = new System::Windows::Forms::CheckBox();
					this->x264hrdLabel = new System::Windows::Forms::Label();
					this->x264hrd = new System::Windows::Forms::ComboBox();
					this->x264aud = new System::Windows::Forms::CheckBox();
					this->x264QuantOptionsGroupbox = new System::Windows::Forms::GroupBox();
					this->label16 = new System::Windows::Forms::Label();
					this->label15 = new System::Windows::Forms::Label();
					this->label14 = new System::Windows::Forms::Label();
					this->label13 = new System::Windows::Forms::Label();
					this->NoiseReduction = new System::Windows::Forms::NumericUpDown();
					this->NoiseReductionLabel = new System::Windows::Forms::Label();
					this->nopsy = new System::Windows::Forms::CheckBox();
					this->x264MixedReferences = new System::Windows::Forms::CheckBox();
					this->x264BframePredictionMode = new System::Windows::Forms::ComboBox();
					this->x264BframePredictionModeLabel = new System::Windows::Forms::Label();
					this->label4 = new System::Windows::Forms::Label();
					this->PsyTrellis = new System::Windows::Forms::NumericUpDown();
					this->label5 = new System::Windows::Forms::Label();
					this->PsyRD = new System::Windows::Forms::NumericUpDown();
					this->noDCTDecimateOption = new System::Windows::Forms::CheckBox();
					this->noFastPSkip = new System::Windows::Forms::CheckBox();
					this->trellis = new System::Windows::Forms::ComboBox();
					this->label7 = new System::Windows::Forms::Label();
					this->x264MBGroupbox = new System::Windows::Forms::GroupBox();
					this->label1 = new System::Windows::Forms::Label();
					this->macroblockOptions = new System::Windows::Forms::ComboBox();
					this->adaptiveDCT = new System::Windows::Forms::CheckBox();
					this->x264I4x4mv = new System::Windows::Forms::CheckBox();
					this->x264I8x8mv = new System::Windows::Forms::CheckBox();
					this->x264P4x4mv = new System::Windows::Forms::CheckBox();
					this->x264B8x8mv = new System::Windows::Forms::CheckBox();
					this->x264P8x8mv = new System::Windows::Forms::CheckBox();
					this->x264OtherOptionsGroupbox = new System::Windows::Forms::GroupBox();
					this->label17 = new System::Windows::Forms::Label();
					this->x264SubpelRefinement = new System::Windows::Forms::ComboBox();
					this->x264SubpelRefinementLabel = new System::Windows::Forms::Label();
					this->x264ChromaMe = new System::Windows::Forms::CheckBox();
					this->x264MERangeLabel = new System::Windows::Forms::Label();
					this->x264METypeLabel = new System::Windows::Forms::Label();
					this->x264METype = new System::Windows::Forms::ComboBox();
					this->x264MERange = new System::Windows::Forms::NumericUpDown();
					this->pictureBox1 = new System::Windows::Forms::PictureBox();
					this->advancedSettings = new System::Windows::Forms::CheckBox();
					this->PsyTrellisLabel = new System::Windows::Forms::Label();
					this->PsyRDLabel = new System::Windows::Forms::Label();
					this->x264NumberOfRefFramesLabel = new System::Windows::Forms::Label();
					this->trellisLabel = new System::Windows::Forms::Label();
					this->MiscTabPage = new System::Windows::Forms::TabPage();
					this->gbOther = new System::Windows::Forms::GroupBox();
					this->chkTuneZeroLatency = new System::Windows::Forms::CheckBox();
					this->chkTuneFastDecode = new System::Windows::Forms::CheckBox();
					this->x264NbThreads = new System::Windows::Forms::NumericUpDown();
					this->nonDeterministic = new System::Windows::Forms::CheckBox();
					this->x264SlowFirstpass = new System::Windows::Forms::CheckBox();
					this->threadin = new System::Windows::Forms::CheckBox();
					this->x264NbThreadsLabel = new System::Windows::Forms::Label();
					this->gbAdjust = new System::Windows::Forms::GroupBox();
					this->btPresetSettings = new System::Windows::Forms::Button();
					this->dSettings = new System::Windows::Forms::Button();
					this->gbInOut = new System::Windows::Forms::GroupBox();
					this->stitchable = new System::Windows::Forms::CheckBox();
					this->sampleAR = new System::Windows::Forms::ComboBox();
					this->sampleARLabel = new System::Windows::Forms::Label();
					this->ssim = new System::Windows::Forms::CheckBox();
					this->psnr = new System::Windows::Forms::CheckBox();
					this->gbVUI = new System::Windows::Forms::GroupBox();
					this->label18 = new System::Windows::Forms::Label();
					this->x264Range = new System::Windows::Forms::ComboBox();
					this->colorMatrixLabel = new System::Windows::Forms::Label();
					this->transferLabel = new System::Windows::Forms::Label();
					this->colorPrimLabel = new System::Windows::Forms::Label();
					this->colorMatrix = new System::Windows::Forms::ComboBox();
					this->transfer = new System::Windows::Forms::ComboBox();
					this->colorPrim = new System::Windows::Forms::ComboBox();
					this->picStruct = new System::Windows::Forms::CheckBox();
					this->gbQPFile = new System::Windows::Forms::GroupBox();
					this->logfile = new System::Windows::Forms::TextBox();
					this->logfileLabel = new System::Windows::Forms::Label();
					this->logfileOpenButton = new System::Windows::Forms::Button();
					this->qpfileOpenButton = new System::Windows::Forms::Button();
					this->qpfile = new System::Windows::Forms::TextBox();
					this->useQPFile = new System::Windows::Forms::CheckBox();
					this->gbx264CustomCmd = new System::Windows::Forms::GroupBox();
					this->customCommandlineOptions = new System::Windows::Forms::TextBox();
					this->avcLevel = new System::Windows::Forms::ComboBox();
					this->avcProfileGroupbox = new System::Windows::Forms::GroupBox();
					this->avcProfile = new System::Windows::Forms::ComboBox();
					this->avcLevelGroupbox = new System::Windows::Forms::GroupBox();
					this->deviceGroupbox = new System::Windows::Forms::GroupBox();
					this->targetDevice = new System::Windows::Forms::ComboBox();
					this->ch10BitsEncoder = new System::Windows::Forms::CheckBox();
					this->tabControl1->SuspendLayout();
					this->mainTabPage->SuspendLayout();
					this->x264CodecGeneralGroupbox->SuspendLayout();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->x264BitrateQuantizer))->BeginInit();
					this->FrameTypeTabPage->SuspendLayout();
					this->gbSlicing->SuspendLayout();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->maxSliceSizeMB))->BeginInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->maxSliceSizeBytes))->BeginInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->slicesnb))->BeginInit();
					this->gbFTOther->SuspendLayout();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->x264NumberOfRefFrames))->BeginInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->x264SCDSensitivity))->BeginInit();
					this->x264GeneralBFramesgGroupbox->SuspendLayout();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->x264BframeBias))->BeginInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->x264NumberOfBFrames))->BeginInit();
					this->gbH264Features->SuspendLayout();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->x264BetaDeblock))->BeginInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->x264AlphaDeblock))->BeginInit();
					this->gbGOPSize->SuspendLayout();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->x264KeyframeInterval))->BeginInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->x264MinGOPSize))->BeginInit();
					this->RCTabPage->SuspendLayout();
					this->x264RCGroupbox->SuspendLayout();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->lookahead))->BeginInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->x264VBVInitialBuffer))->BeginInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->x264VBVMaxRate))->BeginInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->x264TempQuantBlur))->BeginInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->x264TempFrameComplexityBlur))->BeginInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->x264QuantizerCompression))->BeginInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->x264VBVBufferSize))->BeginInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->x264RateTol))->BeginInit();
					this->gbAQ->SuspendLayout();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->numAQStrength))->BeginInit();
					this->quantizerMatrixGroupbox->SuspendLayout();
					this->x264QuantizerGroupBox->SuspendLayout();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->deadzoneIntra))->BeginInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->deadzoneInter))->BeginInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->x264PBFrameFactor))->BeginInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->x264IPFrameFactor))->BeginInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->x264CreditsQuantizer))->BeginInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->x264ChromaQPOffset))->BeginInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->x264MaxQuantDelta))->BeginInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->x264MaximumQuantizer))->BeginInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->x264MinimimQuantizer))->BeginInit();
					this->gbPresets->SuspendLayout();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->tbx264Presets))->BeginInit();
					this->gbTunes->SuspendLayout();
					this->AnalysisTabPage->SuspendLayout();
					this->x264Bluray->SuspendLayout();
					this->x264QuantOptionsGroupbox->SuspendLayout();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->NoiseReduction))->BeginInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->PsyTrellis))->BeginInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->PsyRD))->BeginInit();
					this->x264MBGroupbox->SuspendLayout();
					this->x264OtherOptionsGroupbox->SuspendLayout();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->x264MERange))->BeginInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->pictureBox1))->BeginInit();
					this->MiscTabPage->SuspendLayout();
					this->gbOther->SuspendLayout();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->x264NbThreads))->BeginInit();
					this->gbAdjust->SuspendLayout();
					this->gbInOut->SuspendLayout();
					this->gbVUI->SuspendLayout();
					this->gbQPFile->SuspendLayout();
					this->gbx264CustomCmd->SuspendLayout();
					this->avcProfileGroupbox->SuspendLayout();
					this->avcLevelGroupbox->SuspendLayout();
					this->deviceGroupbox->SuspendLayout();
					this->SuspendLayout();
					// 
					// tabControl1
					// 
					this->tabControl1->Controls->Add(this->FrameTypeTabPage);
					this->tabControl1->Controls->Add(this->RCTabPage);
					this->tabControl1->Controls->Add(this->AnalysisTabPage);
					this->tabControl1->Controls->Add(this->MiscTabPage);
					this->tabControl1->Size = new System::Drawing::Size(510, 429);
					this->tabControl1->SizeMode = System::Windows::Forms::TabSizeMode::FillToRight;
					this->tabControl1->TabIndex = 0;
					this->tabControl1->Controls->SetChildIndex(this->MiscTabPage, 0);
					this->tabControl1->Controls->SetChildIndex(this->AnalysisTabPage, 0);
					this->tabControl1->Controls->SetChildIndex(this->RCTabPage, 0);
					this->tabControl1->Controls->SetChildIndex(this->FrameTypeTabPage, 0);
					this->tabControl1->Controls->SetChildIndex(this->mainTabPage, 0);
					// 
					// commandline
					// 
					this->commandline->Location = new System::Drawing::Point(0, 431);
					this->commandline->Size = new System::Drawing::Size(507, 89);
					this->commandline->TabIndex = 1;
					this->commandline->Text = " ";
					// 
					// mainTabPage
					// 
					this->mainTabPage->Controls->Add(this->ch10BitsEncoder);
					this->mainTabPage->Controls->Add(this->deviceGroupbox);
					this->mainTabPage->Controls->Add(this->avcProfileGroupbox);
					this->mainTabPage->Controls->Add(this->avcLevelGroupbox);
					this->mainTabPage->Controls->Add(this->advancedSettings);
					this->mainTabPage->Controls->Add(this->pictureBox1);
					this->mainTabPage->Controls->Add(this->gbTunes);
					this->mainTabPage->Controls->Add(this->gbPresets);
					this->mainTabPage->Controls->Add(this->helpButton1);
					this->mainTabPage->Controls->Add(this->x264CodecGeneralGroupbox);
					this->mainTabPage->Size = new System::Drawing::Size(502, 403);
					// 
					// x264CodecGeneralGroupbox
					// 
					this->x264CodecGeneralGroupbox->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
					this->x264CodecGeneralGroupbox->Controls->Add(this->cbTarget);
					this->x264CodecGeneralGroupbox->Controls->Add(this->x264BitrateQuantizer);
					this->x264CodecGeneralGroupbox->Controls->Add(this->x264EncodingMode);
					this->x264CodecGeneralGroupbox->Controls->Add(this->x264BitrateQuantizerLabel);
					this->x264CodecGeneralGroupbox->Location = new System::Drawing::Point(6, 98);
					this->x264CodecGeneralGroupbox->Name = "x264CodecGeneralGroupbox";
					this->x264CodecGeneralGroupbox->Size = new System::Drawing::Size(310, 48);
					this->x264CodecGeneralGroupbox->TabIndex = 0;
					this->x264CodecGeneralGroupbox->TabStop = false;
					this->x264CodecGeneralGroupbox->Text = " Encoding Mode ";
					// 
					// cbTarget
					// 
					this->cbTarget->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
					this->cbTarget->FormattingEnabled = true;
					this->cbTarget->Items->AddRange(new object[2] {"Targeting file size", "Targeting quality"});
					this->cbTarget->Location = new System::Drawing::Point(15, 18);
					this->cbTarget->Name = "cbTarget";
					this->cbTarget->Size = new System::Drawing::Size(121, 21);
					this->cbTarget->TabIndex = 18;
					this->cbTarget->SelectionChangeCommitted += new System::EventHandler(this, &x264ConfigurationPanel::cbTarget_SelectionChangeCommitted);
					// 
					// x264BitrateQuantizer
					// 
					this->x264BitrateQuantizer->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right)));
					this->x264BitrateQuantizer->Location = new System::Drawing::Point(249, 19);
					this->x264BitrateQuantizer->Maximum = decimal(new int[4] {300000, 0, 0, 0});
					this->x264BitrateQuantizer->Name = "x264BitrateQuantizer";
					this->x264BitrateQuantizer->Size = new System::Drawing::Size(55, 20);
					this->x264BitrateQuantizer->TabIndex = 5;
					this->x264BitrateQuantizer->ValueChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// x264EncodingMode
					// 
					this->x264EncodingMode->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right)));
					this->x264EncodingMode->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
					this->x264EncodingMode->Items->AddRange(new object[10] {"ABR", "Const. Quantizer", "2pass - 1st pass", "2pass - 2nd pass", "Automated 2pass", "3pass - 1st pass", "3pass - 2nd pass", "3pass - 3rd pass", "Automated 3pass", "Const. Quality"});
					this->x264EncodingMode->Location = new System::Drawing::Point(15, 18);
					this->x264EncodingMode->Name = "x264EncodingMode";
					this->x264EncodingMode->Size = new System::Drawing::Size(121, 21);
					this->x264EncodingMode->TabIndex = 2;
					this->x264EncodingMode->SelectedIndexChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// x264BitrateQuantizerLabel
					// 
					this->x264BitrateQuantizerLabel->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right)));
					this->x264BitrateQuantizerLabel->Location = new System::Drawing::Point(182, 17);
					this->x264BitrateQuantizerLabel->Margin = new System::Windows::Forms::Padding(3);
					this->x264BitrateQuantizerLabel->Name = "x264BitrateQuantizerLabel";
					this->x264BitrateQuantizerLabel->Padding = new System::Windows::Forms::Padding(3);
					this->x264BitrateQuantizerLabel->Size = new System::Drawing::Size(69, 23);
					this->x264BitrateQuantizerLabel->TabIndex = 3;
					this->x264BitrateQuantizerLabel->Text = "Bitrate";
					this->x264BitrateQuantizerLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
					// 
					// FrameTypeTabPage
					// 
					this->FrameTypeTabPage->Controls->Add(this->gbSlicing);
					this->FrameTypeTabPage->Controls->Add(this->gbFTOther);
					this->FrameTypeTabPage->Controls->Add(this->x264GeneralBFramesgGroupbox);
					this->FrameTypeTabPage->Controls->Add(this->gbH264Features);
					this->FrameTypeTabPage->Controls->Add(this->gbGOPSize);
					this->FrameTypeTabPage->Location = new System::Drawing::Point(4, 22);
					this->FrameTypeTabPage->Name = "FrameTypeTabPage";
					this->FrameTypeTabPage->Size = new System::Drawing::Size(502, 403);
					this->FrameTypeTabPage->TabIndex = 3;
					this->FrameTypeTabPage->Text = "Frame-Type";
					this->FrameTypeTabPage->UseVisualStyleBackColor = true;
					// 
					// gbSlicing
					// 
					this->gbSlicing->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right)));
					this->gbSlicing->Controls->Add(this->maxSliceSizeMB);
					this->gbSlicing->Controls->Add(this->label11);
					this->gbSlicing->Controls->Add(this->maxSliceSizeBytes);
					this->gbSlicing->Controls->Add(this->label10);
					this->gbSlicing->Controls->Add(this->slicesnb);
					this->gbSlicing->Controls->Add(this->label9);
					this->gbSlicing->Location = new System::Drawing::Point(3, 287);
					this->gbSlicing->Name = "gbSlicing";
					this->gbSlicing->Size = new System::Drawing::Size(250, 113);
					this->gbSlicing->TabIndex = 14;
					this->gbSlicing->TabStop = false;
					this->gbSlicing->Text = " Slicing ";
					// 
					// maxSliceSizeMB
					// 
					this->maxSliceSizeMB->Location = new System::Drawing::Point(159, 79);
					this->maxSliceSizeMB->Name = "maxSliceSizeMB";
					this->maxSliceSizeMB->Size = new System::Drawing::Size(85, 20);
					this->maxSliceSizeMB->TabIndex = 5;
					this->maxSliceSizeMB->ValueChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// label11
					// 
					this->label11->AutoSize = true;
					this->label11->Location = new System::Drawing::Point(14, 81);
					this->label11->Name = "label11";
					this->label11->Size = new System::Drawing::Size(87, 13);
					this->label11->TabIndex = 4;
					this->label11->Text = "Max size (in mbs)";
					// 
					// maxSliceSizeBytes
					// 
					this->maxSliceSizeBytes->Location = new System::Drawing::Point(159, 50);
					this->maxSliceSizeBytes->Maximum = decimal(new int[4] {250, 0, 0, 0});
					this->maxSliceSizeBytes->Name = "maxSliceSizeBytes";
					this->maxSliceSizeBytes->Size = new System::Drawing::Size(85, 20);
					this->maxSliceSizeBytes->TabIndex = 3;
					this->maxSliceSizeBytes->ValueChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// label10
					// 
					this->label10->AutoSize = true;
					this->label10->Location = new System::Drawing::Point(14, 52);
					this->label10->Name = "label10";
					this->label10->Size = new System::Drawing::Size(93, 13);
					this->label10->TabIndex = 2;
					this->label10->Text = "Max size (in bytes)";
					// 
					// slicesnb
					// 
					this->slicesnb->Location = new System::Drawing::Point(159, 21);
					this->slicesnb->Name = "slicesnb";
					this->slicesnb->Size = new System::Drawing::Size(85, 20);
					this->slicesnb->TabIndex = 1;
					this->slicesnb->ValueChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// label9
					// 
					this->label9->AutoSize = true;
					this->label9->Location = new System::Drawing::Point(14, 25);
					this->label9->Name = "label9";
					this->label9->Size = new System::Drawing::Size(108, 13);
					this->label9->TabIndex = 0;
					this->label9->Text = "Nb of slices by Frame";
					// 
					// gbFTOther
					// 
					this->gbFTOther->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
					this->gbFTOther->Controls->Add(this->cbInterlaceMode);
					this->gbFTOther->Controls->Add(this->lblInterlacedMode);
					this->gbFTOther->Controls->Add(this->x264PullDown);
					this->gbFTOther->Controls->Add(this->pullDownLabel);
					this->gbFTOther->Controls->Add(this->lblWeightedP);
					this->gbFTOther->Controls->Add(this->x264WeightedPPrediction);
					this->gbFTOther->Controls->Add(this->lbExtraIFframes);
					this->gbFTOther->Controls->Add(this->scenecut);
					this->gbFTOther->Controls->Add(this->x264NumberOfRefFrames);
					this->gbFTOther->Controls->Add(this->label6);
					this->gbFTOther->Controls->Add(this->x264SCDSensitivity);
					this->gbFTOther->Location = new System::Drawing::Point(259, 193);
					this->gbFTOther->Name = "gbFTOther";
					this->gbFTOther->Size = new System::Drawing::Size(240, 207);
					this->gbFTOther->TabIndex = 13;
					this->gbFTOther->TabStop = false;
					this->gbFTOther->Text = " Other ";
					// 
					// cbInterlaceMode
					// 
					this->cbInterlaceMode->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
					this->cbInterlaceMode->FormattingEnabled = true;
					this->cbInterlaceMode->Items->AddRange(new object[3] {"none", "TFF", "BFF"});
					this->cbInterlaceMode->Location = new System::Drawing::Point(167, 108);
					this->cbInterlaceMode->Name = "cbInterlaceMode";
					this->cbInterlaceMode->Size = new System::Drawing::Size(65, 21);
					this->cbInterlaceMode->TabIndex = 26;
					this->cbInterlaceMode->SelectedIndexChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// lblInterlacedMode
					// 
					this->lblInterlacedMode->AutoSize = true;
					this->lblInterlacedMode->Location = new System::Drawing::Point(9, 111);
					this->lblInterlacedMode->Name = "lblInterlacedMode";
					this->lblInterlacedMode->Size = new System::Drawing::Size(84, 13);
					this->lblInterlacedMode->TabIndex = 25;
					this->lblInterlacedMode->Text = "Interlaced Mode";
					this->lblInterlacedMode->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
					// 
					// x264PullDown
					// 
					this->x264PullDown->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
					this->x264PullDown->FormattingEnabled = true;
					this->x264PullDown->Items->AddRange(new object[7] {"none", "22", "32", "64", "double", "triple", "euro"});
					this->x264PullDown->Location = new System::Drawing::Point(167, 134);
					this->x264PullDown->Name = "x264PullDown";
					this->x264PullDown->Size = new System::Drawing::Size(65, 21);
					this->x264PullDown->TabIndex = 24;
					this->x264PullDown->SelectedIndexChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// pullDownLabel
					// 
					this->pullDownLabel->AutoSize = true;
					this->pullDownLabel->Location = new System::Drawing::Point(9, 137);
					this->pullDownLabel->Name = "pullDownLabel";
					this->pullDownLabel->Size = new System::Drawing::Size(50, 13);
					this->pullDownLabel->TabIndex = 23;
					this->pullDownLabel->Text = "Pulldown";
					// 
					// lblWeightedP
					// 
					this->lblWeightedP->AutoSize = true;
					this->lblWeightedP->Location = new System::Drawing::Point(9, 84);
					this->lblWeightedP->Name = "lblWeightedP";
					this->lblWeightedP->Size = new System::Drawing::Size(142, 13);
					this->lblWeightedP->TabIndex = 22;
					this->lblWeightedP->Text = "P-frame Weighted Prediction";
					this->lblWeightedP->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
					// 
					// x264WeightedPPrediction
					// 
					this->x264WeightedPPrediction->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
					this->x264WeightedPPrediction->FormattingEnabled = true;
					this->x264WeightedPPrediction->Items->AddRange(new object[3] {"Disabled", "Blind", "Smart"});
					this->x264WeightedPPrediction->Location = new System::Drawing::Point(167, 81);
					this->x264WeightedPPrediction->Name = "x264WeightedPPrediction";
					this->x264WeightedPPrediction->Size = new System::Drawing::Size(65, 21);
					this->x264WeightedPPrediction->TabIndex = 21;
					this->x264WeightedPPrediction->SelectedIndexChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// lbExtraIFframes
					// 
					this->lbExtraIFframes->AutoSize = true;
					this->lbExtraIFframes->Location = new System::Drawing::Point(9, 52);
					this->lbExtraIFframes->Name = "lbExtraIFframes";
					this->lbExtraIFframes->Size = new System::Drawing::Size(126, 13);
					this->lbExtraIFframes->TabIndex = 20;
					this->lbExtraIFframes->Text = "Number of Extra I-Frames";
					this->lbExtraIFframes->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
					// 
					// scenecut
					// 
					this->scenecut->Checked = true;
					this->scenecut->CheckState = System::Windows::Forms::CheckState::Checked;
					this->scenecut->Location = new System::Drawing::Point(12, 161);
					this->scenecut->Name = "scenecut";
					this->scenecut->Size = new System::Drawing::Size(163, 24);
					this->scenecut->TabIndex = 19;
					this->scenecut->Text = "Adaptive I-Frame Decision";
					this->scenecut->UseVisualStyleBackColor = true;
					this->scenecut->CheckedChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// x264NumberOfRefFrames
					// 
					this->x264NumberOfRefFrames->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right)));
					this->x264NumberOfRefFrames->Location = new System::Drawing::Point(181, 21);
					this->x264NumberOfRefFrames->Maximum = decimal(new int[4] {16, 0, 0, 0});
					this->x264NumberOfRefFrames->Minimum = decimal(new int[4] {1, 0, 0, 0});
					this->x264NumberOfRefFrames->Name = "x264NumberOfRefFrames";
					this->x264NumberOfRefFrames->Size = new System::Drawing::Size(51, 20);
					this->x264NumberOfRefFrames->TabIndex = 18;
					this->x264NumberOfRefFrames->Value = decimal(new int[4] {3, 0, 0, 0});
					this->x264NumberOfRefFrames->ValueChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// label6
					// 
					this->label6->AutoSize = true;
					this->label6->Location = new System::Drawing::Point(9, 23);
					this->label6->Name = "label6";
					this->label6->Size = new System::Drawing::Size(146, 13);
					this->label6->TabIndex = 17;
					this->label6->Text = "Number of Reference Frames";
					this->label6->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
					// 
					// x264SCDSensitivity
					// 
					this->x264SCDSensitivity->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right)));
					this->x264SCDSensitivity->Location = new System::Drawing::Point(181, 50);
					this->x264SCDSensitivity->Minimum = decimal(new int[4] {1, 0, 0, -2147483648});
					this->x264SCDSensitivity->Name = "x264SCDSensitivity";
					this->x264SCDSensitivity->Size = new System::Drawing::Size(51, 20);
					this->x264SCDSensitivity->TabIndex = 16;
					this->x264SCDSensitivity->Value = decimal(new int[4] {40, 0, 0, 0});
					this->x264SCDSensitivity->ValueChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// x264GeneralBFramesgGroupbox
					// 
					this->x264GeneralBFramesgGroupbox->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right)));
					this->x264GeneralBFramesgGroupbox->Controls->Add(this->label12);
					this->x264GeneralBFramesgGroupbox->Controls->Add(this->cbBPyramid);
					this->x264GeneralBFramesgGroupbox->Controls->Add(this->x264WeightedBPrediction);
					this->x264GeneralBFramesgGroupbox->Controls->Add(this->x264BframeBias);
					this->x264GeneralBFramesgGroupbox->Controls->Add(this->x264BframeBiasLabel);
					this->x264GeneralBFramesgGroupbox->Controls->Add(this->x264AdaptiveBframesLabel);
					this->x264GeneralBFramesgGroupbox->Controls->Add(this->x264NewAdaptiveBframes);
					this->x264GeneralBFramesgGroupbox->Controls->Add(this->x264NumberOfBFramesLabel);
					this->x264GeneralBFramesgGroupbox->Controls->Add(this->x264NumberOfBFrames);
					this->x264GeneralBFramesgGroupbox->Location = new System::Drawing::Point(259, 3);
					this->x264GeneralBFramesgGroupbox->Name = "x264GeneralBFramesgGroupbox";
					this->x264GeneralBFramesgGroupbox->Size = new System::Drawing::Size(240, 184);
					this->x264GeneralBFramesgGroupbox->TabIndex = 7;
					this->x264GeneralBFramesgGroupbox->TabStop = false;
					this->x264GeneralBFramesgGroupbox->Text = " B-Frames ";
					// 
					// label12
					// 
					this->label12->AutoSize = true;
					this->label12->Location = new System::Drawing::Point(14, 155);
					this->label12->Name = "label12";
					this->label12->Size = new System::Drawing::Size(54, 13);
					this->label12->TabIndex = 20;
					this->label12->Text = "B-Pyramid";
					// 
					// cbBPyramid
					// 
					this->cbBPyramid->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
					this->cbBPyramid->FormattingEnabled = true;
					this->cbBPyramid->Items->AddRange(new object[3] {"Disabled", "Strict", "Normal"});
					this->cbBPyramid->Location = new System::Drawing::Point(149, 152);
					this->cbBPyramid->Name = "cbBPyramid";
					this->cbBPyramid->Size = new System::Drawing::Size(83, 21);
					this->cbBPyramid->TabIndex = 19;
					this->cbBPyramid->SelectedIndexChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// x264WeightedBPrediction
					// 
					this->x264WeightedBPrediction->Checked = true;
					this->x264WeightedBPrediction->CheckState = System::Windows::Forms::CheckState::Checked;
					this->x264WeightedBPrediction->Location = new System::Drawing::Point(17, 19);
					this->x264WeightedBPrediction->Name = "x264WeightedBPrediction";
					this->x264WeightedBPrediction->Padding = new System::Windows::Forms::Padding(3);
					this->x264WeightedBPrediction->Size = new System::Drawing::Size(194, 23);
					this->x264WeightedBPrediction->TabIndex = 18;
					this->x264WeightedBPrediction->Text = "Weighted Prediction for B-Frames";
					this->x264WeightedBPrediction->CheckedChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// x264BframeBias
					// 
					this->x264BframeBias->Location = new System::Drawing::Point(149, 80);
					this->x264BframeBias->Minimum = decimal(new int[4] {90, 0, 0, -2147483648});
					this->x264BframeBias->Name = "x264BframeBias";
					this->x264BframeBias->Size = new System::Drawing::Size(85, 20);
					this->x264BframeBias->TabIndex = 16;
					this->x264BframeBias->ValueChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// x264BframeBiasLabel
					// 
					this->x264BframeBiasLabel->AutoSize = true;
					this->x264BframeBiasLabel->Location = new System::Drawing::Point(14, 82);
					this->x264BframeBiasLabel->Name = "x264BframeBiasLabel";
					this->x264BframeBiasLabel->Size = new System::Drawing::Size(65, 13);
					this->x264BframeBiasLabel->TabIndex = 15;
					this->x264BframeBiasLabel->Text = "B-frame bias";
					this->x264BframeBiasLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
					// 
					// x264AdaptiveBframesLabel
					// 
					this->x264AdaptiveBframesLabel->AutoSize = true;
					this->x264AdaptiveBframesLabel->Location = new System::Drawing::Point(14, 125);
					this->x264AdaptiveBframesLabel->Name = "x264AdaptiveBframesLabel";
					this->x264AdaptiveBframesLabel->Size = new System::Drawing::Size(96, 13);
					this->x264AdaptiveBframesLabel->TabIndex = 12;
					this->x264AdaptiveBframesLabel->Text = "Adaptive B-Frames";
					// 
					// x264NewAdaptiveBframes
					// 
					this->x264NewAdaptiveBframes->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
					this->x264NewAdaptiveBframes->Items->AddRange(new object[3] {"0-Off", "1-Fast", "2-Optimal"});
					this->x264NewAdaptiveBframes->Location = new System::Drawing::Point(149, 122);
					this->x264NewAdaptiveBframes->Name = "x264NewAdaptiveBframes";
					this->x264NewAdaptiveBframes->Size = new System::Drawing::Size(83, 21);
					this->x264NewAdaptiveBframes->TabIndex = 11;
					this->x264NewAdaptiveBframes->SelectedIndexChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// x264NumberOfBFramesLabel
					// 
					this->x264NumberOfBFramesLabel->AutoSize = true;
					this->x264NumberOfBFramesLabel->Location = new System::Drawing::Point(14, 56);
					this->x264NumberOfBFramesLabel->Name = "x264NumberOfBFramesLabel";
					this->x264NumberOfBFramesLabel->Size = new System::Drawing::Size(100, 13);
					this->x264NumberOfBFramesLabel->TabIndex = 0;
					this->x264NumberOfBFramesLabel->Text = "Number of B-frames";
					this->x264NumberOfBFramesLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
					// 
					// x264NumberOfBFrames
					// 
					this->x264NumberOfBFrames->Location = new System::Drawing::Point(149, 54);
					this->x264NumberOfBFrames->Maximum = decimal(new int[4] {16, 0, 0, 0});
					this->x264NumberOfBFrames->Name = "x264NumberOfBFrames";
					this->x264NumberOfBFrames->Size = new System::Drawing::Size(85, 20);
					this->x264NumberOfBFrames->TabIndex = 1;
					this->x264NumberOfBFrames->Value = decimal(new int[4] {3, 0, 0, 0});
					this->x264NumberOfBFrames->ValueChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// gbH264Features
					// 
					this->gbH264Features->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
					this->gbH264Features->Controls->Add(this->cabac);
					this->gbH264Features->Controls->Add(this->x264BetaDeblock);
					this->gbH264Features->Controls->Add(this->x264AlphaDeblock);
					this->gbH264Features->Controls->Add(this->x264DeblockActive);
					this->gbH264Features->Controls->Add(this->x264BetaDeblockLabel);
					this->gbH264Features->Controls->Add(this->x264AlphaDeblockLabel);
					this->gbH264Features->Location = new System::Drawing::Point(3, 3);
					this->gbH264Features->Name = "gbH264Features";
					this->gbH264Features->Size = new System::Drawing::Size(250, 132);
					this->gbH264Features->TabIndex = 4;
					this->gbH264Features->TabStop = false;
					this->gbH264Features->Text = " H.264 Features ";
					// 
					// cabac
					// 
					this->cabac->Checked = true;
					this->cabac->CheckState = System::Windows::Forms::CheckState::Checked;
					this->cabac->Location = new System::Drawing::Point(17, 93);
					this->cabac->Name = "cabac";
					this->cabac->Padding = new System::Windows::Forms::Padding(3);
					this->cabac->Size = new System::Drawing::Size(162, 23);
					this->cabac->TabIndex = 12;
					this->cabac->Text = "CABAC";
					this->cabac->CheckedChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// x264BetaDeblock
					// 
					this->x264BetaDeblock->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right)));
					this->x264BetaDeblock->Location = new System::Drawing::Point(193, 66);
					this->x264BetaDeblock->Maximum = decimal(new int[4] {6, 0, 0, 0});
					this->x264BetaDeblock->Minimum = decimal(new int[4] {6, 0, 0, -2147483648});
					this->x264BetaDeblock->Name = "x264BetaDeblock";
					this->x264BetaDeblock->Size = new System::Drawing::Size(51, 20);
					this->x264BetaDeblock->TabIndex = 4;
					this->x264BetaDeblock->ValueChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// x264AlphaDeblock
					// 
					this->x264AlphaDeblock->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right)));
					this->x264AlphaDeblock->Location = new System::Drawing::Point(193, 43);
					this->x264AlphaDeblock->Maximum = decimal(new int[4] {6, 0, 0, 0});
					this->x264AlphaDeblock->Minimum = decimal(new int[4] {6, 0, 0, -2147483648});
					this->x264AlphaDeblock->Name = "x264AlphaDeblock";
					this->x264AlphaDeblock->Size = new System::Drawing::Size(51, 20);
					this->x264AlphaDeblock->TabIndex = 2;
					this->x264AlphaDeblock->ValueChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// x264DeblockActive
					// 
					this->x264DeblockActive->Checked = true;
					this->x264DeblockActive->CheckState = System::Windows::Forms::CheckState::Checked;
					this->x264DeblockActive->Location = new System::Drawing::Point(17, 19);
					this->x264DeblockActive->Name = "x264DeblockActive";
					this->x264DeblockActive->Padding = new System::Windows::Forms::Padding(3);
					this->x264DeblockActive->Size = new System::Drawing::Size(156, 23);
					this->x264DeblockActive->TabIndex = 0;
					this->x264DeblockActive->Text = "Deblocking";
					this->x264DeblockActive->CheckedChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// x264BetaDeblockLabel
					// 
					this->x264BetaDeblockLabel->AutoSize = true;
					this->x264BetaDeblockLabel->Location = new System::Drawing::Point(14, 68);
					this->x264BetaDeblockLabel->Name = "x264BetaDeblockLabel";
					this->x264BetaDeblockLabel->Size = new System::Drawing::Size(111, 13);
					this->x264BetaDeblockLabel->TabIndex = 3;
					this->x264BetaDeblockLabel->Text = "Deblocking Threshold";
					this->x264BetaDeblockLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
					// 
					// x264AlphaDeblockLabel
					// 
					this->x264AlphaDeblockLabel->AutoSize = true;
					this->x264AlphaDeblockLabel->Location = new System::Drawing::Point(14, 45);
					this->x264AlphaDeblockLabel->Name = "x264AlphaDeblockLabel";
					this->x264AlphaDeblockLabel->Size = new System::Drawing::Size(104, 13);
					this->x264AlphaDeblockLabel->TabIndex = 1;
					this->x264AlphaDeblockLabel->Text = "Deblocking Strength";
					this->x264AlphaDeblockLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
					// 
					// gbGOPSize
					// 
					this->gbGOPSize->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
					this->gbGOPSize->Controls->Add(this->label19);
					this->gbGOPSize->Controls->Add(this->cbGOPCalculation);
					this->gbGOPSize->Controls->Add(this->chkOpenGop);
					this->gbGOPSize->Controls->Add(this->x264KeyframeIntervalLabel);
					this->gbGOPSize->Controls->Add(this->x264KeyframeInterval);
					this->gbGOPSize->Controls->Add(this->x264MinGOPSize);
					this->gbGOPSize->Controls->Add(this->x264MinGOPSizeLabel);
					this->gbGOPSize->Location = new System::Drawing::Point(2, 141);
					this->gbGOPSize->Name = "gbGOPSize";
					this->gbGOPSize->Size = new System::Drawing::Size(251, 140);
					this->gbGOPSize->TabIndex = 1;
					this->gbGOPSize->TabStop = false;
					this->gbGOPSize->Text = " GOP Size ";
					// 
					// label19
					// 
					this->label19->AutoSize = true;
					this->label19->Location = new System::Drawing::Point(15, 31);
					this->label19->Name = "label19";
					this->label19->Size = new System::Drawing::Size(84, 13);
					this->label19->TabIndex = 13;
					this->label19->Text = "GOP calculation";
					this->label19->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
					// 
					// cbGOPCalculation
					// 
					this->cbGOPCalculation->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
					this->cbGOPCalculation->Items->AddRange(new object[2] {"Fixed", "FPS based"});
					this->cbGOPCalculation->Location = new System::Drawing::Point(129, 28);
					this->cbGOPCalculation->Name = "cbGOPCalculation";
					this->cbGOPCalculation->Size = new System::Drawing::Size(116, 21);
					this->cbGOPCalculation->TabIndex = 12;
					this->cbGOPCalculation->SelectedIndexChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// chkOpenGop
					// 
					this->chkOpenGop->AutoSize = true;
					this->chkOpenGop->Location = new System::Drawing::Point(18, 105);
					this->chkOpenGop->Name = "chkOpenGop";
					this->chkOpenGop->Size = new System::Drawing::Size(78, 17);
					this->chkOpenGop->TabIndex = 5;
					this->chkOpenGop->Text = "Open GOP";
					this->chkOpenGop->UseVisualStyleBackColor = true;
					this->chkOpenGop->CheckedChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// x264KeyframeIntervalLabel
					// 
					this->x264KeyframeIntervalLabel->AutoSize = true;
					this->x264KeyframeIntervalLabel->Location = new System::Drawing::Point(15, 59);
					this->x264KeyframeIntervalLabel->Name = "x264KeyframeIntervalLabel";
					this->x264KeyframeIntervalLabel->Size = new System::Drawing::Size(158, 13);
					this->x264KeyframeIntervalLabel->TabIndex = 0;
					this->x264KeyframeIntervalLabel->Text = "Maximum GOP Size (0 = Infinite)";
					this->x264KeyframeIntervalLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
					// 
					// x264KeyframeInterval
					// 
					this->x264KeyframeInterval->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right)));
					this->x264KeyframeInterval->Location = new System::Drawing::Point(197, 55);
					this->x264KeyframeInterval->Maximum = decimal(new int[4] {999, 0, 0, 0});
					this->x264KeyframeInterval->Name = "x264KeyframeInterval";
					this->x264KeyframeInterval->Size = new System::Drawing::Size(48, 20);
					this->x264KeyframeInterval->TabIndex = 1;
					this->x264KeyframeInterval->Value = decimal(new int[4] {250, 0, 0, 0});
					this->x264KeyframeInterval->ValueChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// x264MinGOPSize
					// 
					this->x264MinGOPSize->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right)));
					this->x264MinGOPSize->Location = new System::Drawing::Point(197, 80);
					this->x264MinGOPSize->Minimum = decimal(new int[4] {1, 0, 0, 0});
					this->x264MinGOPSize->Name = "x264MinGOPSize";
					this->x264MinGOPSize->Size = new System::Drawing::Size(48, 20);
					this->x264MinGOPSize->TabIndex = 3;
					this->x264MinGOPSize->Value = decimal(new int[4] {25, 0, 0, 0});
					this->x264MinGOPSize->ValueChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// x264MinGOPSizeLabel
					// 
					this->x264MinGOPSizeLabel->AutoSize = true;
					this->x264MinGOPSizeLabel->Location = new System::Drawing::Point(15, 82);
					this->x264MinGOPSizeLabel->Name = "x264MinGOPSizeLabel";
					this->x264MinGOPSizeLabel->Size = new System::Drawing::Size(97, 13);
					this->x264MinGOPSizeLabel->TabIndex = 2;
					this->x264MinGOPSizeLabel->Text = "Minimum GOP Size";
					this->x264MinGOPSizeLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
					// 
					// RCTabPage
					// 
					this->RCTabPage->Controls->Add(this->x264RCGroupbox);
					this->RCTabPage->Controls->Add(this->gbAQ);
					this->RCTabPage->Controls->Add(this->quantizerMatrixGroupbox);
					this->RCTabPage->Controls->Add(this->x264QuantizerGroupBox);
					this->RCTabPage->Location = new System::Drawing::Point(4, 22);
					this->RCTabPage->Name = "RCTabPage";
					this->RCTabPage->Size = new System::Drawing::Size(502, 403);
					this->RCTabPage->TabIndex = 4;
					this->RCTabPage->Text = "Rate Control";
					this->RCTabPage->UseVisualStyleBackColor = true;
					// 
					// x264RCGroupbox
					// 
					this->x264RCGroupbox->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
					this->x264RCGroupbox->Controls->Add(this->mbtree);
					this->x264RCGroupbox->Controls->Add(this->label8);
					this->x264RCGroupbox->Controls->Add(this->lookahead);
					this->x264RCGroupbox->Controls->Add(this->x264RateTolLabel);
					this->x264RCGroupbox->Controls->Add(this->x264VBVInitialBuffer);
					this->x264RCGroupbox->Controls->Add(this->x264VBVInitialBufferLabel);
					this->x264RCGroupbox->Controls->Add(this->x264VBVMaxRate);
					this->x264RCGroupbox->Controls->Add(this->x264TempQuantBlur);
					this->x264RCGroupbox->Controls->Add(this->x264TempFrameComplexityBlur);
					this->x264RCGroupbox->Controls->Add(this->x264QuantizerCompression);
					this->x264RCGroupbox->Controls->Add(this->x264VBVBufferSize);
					this->x264RCGroupbox->Controls->Add(this->x264TempQuantBlurLabel);
					this->x264RCGroupbox->Controls->Add(this->x264TempFrameComplexityBlurLabel);
					this->x264RCGroupbox->Controls->Add(this->x264QuantizerCompressionLabel);
					this->x264RCGroupbox->Controls->Add(this->x264VBVMaxRateLabel);
					this->x264RCGroupbox->Controls->Add(this->x264VBVBufferSizeLabel);
					this->x264RCGroupbox->Controls->Add(this->x264RateTol);
					this->x264RCGroupbox->Location = new System::Drawing::Point(3, 192);
					this->x264RCGroupbox->Name = "x264RCGroupbox";
					this->x264RCGroupbox->Size = new System::Drawing::Size(496, 200);
					this->x264RCGroupbox->TabIndex = 22;
					this->x264RCGroupbox->TabStop = false;
					this->x264RCGroupbox->Text = "Rate Control";
					// 
					// mbtree
					// 
					this->mbtree->Checked = true;
					this->mbtree->CheckState = System::Windows::Forms::CheckState::Checked;
					this->mbtree->Location = new System::Drawing::Point(295, 68);
					this->mbtree->Name = "mbtree";
					this->mbtree->Size = new System::Drawing::Size(195, 17);
					this->mbtree->TabIndex = 16;
					this->mbtree->Text = "Use MB-Tree";
					this->mbtree->UseVisualStyleBackColor = true;
					this->mbtree->CheckedChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// label8
					// 
					this->label8->AutoSize = true;
					this->label8->Location = new System::Drawing::Point(292, 21);
					this->label8->Name = "label8";
					this->label8->Size = new System::Drawing::Size(142, 13);
					this->label8->TabIndex = 15;
					this->label8->Text = "Nb of Frames for Lookahead";
					// 
					// lookahead
					// 
					this->lookahead->Location = new System::Drawing::Point(443, 19);
					this->lookahead->Maximum = decimal(new int[4] {250, 0, 0, 0});
					this->lookahead->Name = "lookahead";
					this->lookahead->Size = new System::Drawing::Size(48, 20);
					this->lookahead->TabIndex = 14;
					this->lookahead->Value = decimal(new int[4] {40, 0, 0, 0});
					this->lookahead->ValueChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// x264RateTolLabel
					// 
					this->x264RateTolLabel->AutoSize = true;
					this->x264RateTolLabel->Location = new System::Drawing::Point(12, 95);
					this->x264RateTolLabel->Name = "x264RateTolLabel";
					this->x264RateTolLabel->Size = new System::Drawing::Size(82, 13);
					this->x264RateTolLabel->TabIndex = 6;
					this->x264RateTolLabel->Text = "Bitrate Variance";
					this->x264RateTolLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
					// 
					// x264VBVInitialBuffer
					// 
					this->x264VBVInitialBuffer->DecimalPlaces = 1;
					this->x264VBVInitialBuffer->Increment = decimal(new int[4] {1, 0, 0, 65536});
					this->x264VBVInitialBuffer->Location = new System::Drawing::Point(229, 68);
					this->x264VBVInitialBuffer->Maximum = decimal(new int[4] {1, 0, 0, 0});
					this->x264VBVInitialBuffer->Name = "x264VBVInitialBuffer";
					this->x264VBVInitialBuffer->Size = new System::Drawing::Size(48, 20);
					this->x264VBVInitialBuffer->TabIndex = 5;
					this->x264VBVInitialBuffer->Value = decimal(new int[4] {9, 0, 0, 65536});
					this->x264VBVInitialBuffer->ValueChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// x264VBVInitialBufferLabel
					// 
					this->x264VBVInitialBufferLabel->AutoSize = true;
					this->x264VBVInitialBufferLabel->Location = new System::Drawing::Point(12, 70);
					this->x264VBVInitialBufferLabel->Name = "x264VBVInitialBufferLabel";
					this->x264VBVInitialBufferLabel->Size = new System::Drawing::Size(86, 13);
					this->x264VBVInitialBufferLabel->TabIndex = 4;
					this->x264VBVInitialBufferLabel->Text = "VBV Initial Buffer";
					this->x264VBVInitialBufferLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
					// 
					// x264VBVMaxRate
					// 
					this->x264VBVMaxRate->Enabled = false;
					this->x264VBVMaxRate->Location = new System::Drawing::Point(222, 43);
					this->x264VBVMaxRate->Maximum = decimal(new int[4] {99999999, 0, 0, 0});
					this->x264VBVMaxRate->Name = "x264VBVMaxRate";
					this->x264VBVMaxRate->Size = new System::Drawing::Size(55, 20);
					this->x264VBVMaxRate->TabIndex = 3;
					this->x264VBVMaxRate->ValueChanged += new System::EventHandler(this, &x264ConfigurationPanel::x264VBVMaxRate_ValueChanged);
					// 
					// x264TempQuantBlur
					// 
					this->x264TempQuantBlur->DecimalPlaces = 1;
					this->x264TempQuantBlur->Increment = decimal(new int[4] {5, 0, 0, 65536});
					this->x264TempQuantBlur->Location = new System::Drawing::Point(229, 168);
					this->x264TempQuantBlur->Maximum = decimal(new int[4] {99, 0, 0, 0});
					this->x264TempQuantBlur->Name = "x264TempQuantBlur";
					this->x264TempQuantBlur->Size = new System::Drawing::Size(48, 20);
					this->x264TempQuantBlur->TabIndex = 13;
					this->x264TempQuantBlur->Value = decimal(new int[4] {5, 0, 0, 65536});
					this->x264TempQuantBlur->ValueChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// x264TempFrameComplexityBlur
					// 
					this->x264TempFrameComplexityBlur->Location = new System::Drawing::Point(229, 143);
					this->x264TempFrameComplexityBlur->Maximum = decimal(new int[4] {999, 0, 0, 0});
					this->x264TempFrameComplexityBlur->Name = "x264TempFrameComplexityBlur";
					this->x264TempFrameComplexityBlur->Size = new System::Drawing::Size(48, 20);
					this->x264TempFrameComplexityBlur->TabIndex = 11;
					this->x264TempFrameComplexityBlur->Value = decimal(new int[4] {20, 0, 0, 0});
					this->x264TempFrameComplexityBlur->ValueChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// x264QuantizerCompression
					// 
					this->x264QuantizerCompression->DecimalPlaces = 1;
					this->x264QuantizerCompression->Increment = decimal(new int[4] {1, 0, 0, 65536});
					this->x264QuantizerCompression->Location = new System::Drawing::Point(229, 118);
					this->x264QuantizerCompression->Maximum = decimal(new int[4] {1, 0, 0, 0});
					this->x264QuantizerCompression->Name = "x264QuantizerCompression";
					this->x264QuantizerCompression->Size = new System::Drawing::Size(48, 20);
					this->x264QuantizerCompression->TabIndex = 9;
					this->x264QuantizerCompression->Value = decimal(new int[4] {6, 0, 0, 65536});
					this->x264QuantizerCompression->ValueChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// x264VBVBufferSize
					// 
					this->x264VBVBufferSize->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right)));
					this->x264VBVBufferSize->Location = new System::Drawing::Point(222, 18);
					this->x264VBVBufferSize->Maximum = decimal(new int[4] {99999999, 0, 0, 0});
					this->x264VBVBufferSize->Name = "x264VBVBufferSize";
					this->x264VBVBufferSize->Size = new System::Drawing::Size(55, 20);
					this->x264VBVBufferSize->TabIndex = 1;
					this->x264VBVBufferSize->ValueChanged += new System::EventHandler(this, &x264ConfigurationPanel::x264VBVBufferSize_ValueChanged);
					// 
					// x264TempQuantBlurLabel
					// 
					this->x264TempQuantBlurLabel->AutoSize = true;
					this->x264TempQuantBlurLabel->Location = new System::Drawing::Point(12, 170);
					this->x264TempQuantBlurLabel->Name = "x264TempQuantBlurLabel";
					this->x264TempQuantBlurLabel->Size = new System::Drawing::Size(143, 13);
					this->x264TempQuantBlurLabel->TabIndex = 12;
					this->x264TempQuantBlurLabel->Text = "Temp. Blur of Quant after CC";
					this->x264TempQuantBlurLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
					// 
					// x264TempFrameComplexityBlurLabel
					// 
					this->x264TempFrameComplexityBlurLabel->AutoSize = true;
					this->x264TempFrameComplexityBlurLabel->Location = new System::Drawing::Point(12, 145);
					this->x264TempFrameComplexityBlurLabel->Name = "x264TempFrameComplexityBlurLabel";
					this->x264TempFrameComplexityBlurLabel->Size = new System::Drawing::Size(174, 13);
					this->x264TempFrameComplexityBlurLabel->TabIndex = 10;
					this->x264TempFrameComplexityBlurLabel->Text = "Temp. Blur of est. Frame complexity";
					this->x264TempFrameComplexityBlurLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
					// 
					// x264QuantizerCompressionLabel
					// 
					this->x264QuantizerCompressionLabel->AutoSize = true;
					this->x264QuantizerCompressionLabel->Location = new System::Drawing::Point(12, 120);
					this->x264QuantizerCompressionLabel->Name = "x264QuantizerCompressionLabel";
					this->x264QuantizerCompressionLabel->Size = new System::Drawing::Size(115, 13);
					this->x264QuantizerCompressionLabel->TabIndex = 8;
					this->x264QuantizerCompressionLabel->Text = "Quantizer Compression";
					this->x264QuantizerCompressionLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
					// 
					// x264VBVMaxRateLabel
					// 
					this->x264VBVMaxRateLabel->AutoSize = true;
					this->x264VBVMaxRateLabel->Enabled = false;
					this->x264VBVMaxRateLabel->Location = new System::Drawing::Point(12, 45);
					this->x264VBVMaxRateLabel->Name = "x264VBVMaxRateLabel";
					this->x264VBVMaxRateLabel->Size = new System::Drawing::Size(108, 13);
					this->x264VBVMaxRateLabel->TabIndex = 2;
					this->x264VBVMaxRateLabel->Text = "VBV Maximum Bitrate";
					this->x264VBVMaxRateLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
					// 
					// x264VBVBufferSizeLabel
					// 
					this->x264VBVBufferSizeLabel->AutoSize = true;
					this->x264VBVBufferSizeLabel->Location = new System::Drawing::Point(12, 21);
					this->x264VBVBufferSizeLabel->Name = "x264VBVBufferSizeLabel";
					this->x264VBVBufferSizeLabel->Size = new System::Drawing::Size(82, 13);
					this->x264VBVBufferSizeLabel->TabIndex = 0;
					this->x264VBVBufferSizeLabel->Text = "VBV Buffer Size";
					this->x264VBVBufferSizeLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
					// 
					// x264RateTol
					// 
					this->x264RateTol->DecimalPlaces = 1;
					this->x264RateTol->Increment = decimal(new int[4] {1, 0, 0, 65536});
					this->x264RateTol->Location = new System::Drawing::Point(229, 93);
					this->x264RateTol->Minimum = decimal(new int[4] {1, 0, 0, 65536});
					this->x264RateTol->Name = "x264RateTol";
					this->x264RateTol->Size = new System::Drawing::Size(48, 20);
					this->x264RateTol->TabIndex = 7;
					this->x264RateTol->Value = decimal(new int[4] {10, 0, 0, 65536});
					this->x264RateTol->ValueChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// gbAQ
					// 
					this->gbAQ->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right)));
					this->gbAQ->Controls->Add(this->numAQStrength);
					this->gbAQ->Controls->Add(this->lbAQStrength);
					this->gbAQ->Controls->Add(this->cbAQMode);
					this->gbAQ->Controls->Add(this->lbAQMode);
					this->gbAQ->Location = new System::Drawing::Point(298, 3);
					this->gbAQ->Name = "gbAQ";
					this->gbAQ->Size = new System::Drawing::Size(201, 78);
					this->gbAQ->TabIndex = 7;
					this->gbAQ->TabStop = false;
					this->gbAQ->Text = "Adaptive Quantizers";
					// 
					// numAQStrength
					// 
					this->numAQStrength->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right)));
					this->numAQStrength->DecimalPlaces = 1;
					this->numAQStrength->Increment = decimal(new int[4] {1, 0, 0, 65536});
					this->numAQStrength->Location = new System::Drawing::Point(109, 46);
					this->numAQStrength->Maximum = decimal(new int[4] {2, 0, 0, 0});
					this->numAQStrength->Name = "numAQStrength";
					this->numAQStrength->Size = new System::Drawing::Size(78, 20);
					this->numAQStrength->TabIndex = 3;
					this->numAQStrength->Value = decimal(new int[4] {10, 0, 0, 65536});
					this->numAQStrength->ValueChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// lbAQStrength
					// 
					this->lbAQStrength->AutoSize = true;
					this->lbAQStrength->Location = new System::Drawing::Point(12, 48);
					this->lbAQStrength->Name = "lbAQStrength";
					this->lbAQStrength->Size = new System::Drawing::Size(50, 13);
					this->lbAQStrength->TabIndex = 2;
					this->lbAQStrength->Text = "Strength ";
					this->lbAQStrength->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
					// 
					// cbAQMode
					// 
					this->cbAQMode->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right)));
					this->cbAQMode->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
					this->cbAQMode->FormattingEnabled = true;
					this->cbAQMode->Items->AddRange(new object[3] {"Disabled", "Variance AQ (complexity mask)", "Auto-variance AQ (experimental)"});
					this->cbAQMode->Location = new System::Drawing::Point(52, 19);
					this->cbAQMode->Name = "cbAQMode";
					this->cbAQMode->Size = new System::Drawing::Size(135, 21);
					this->cbAQMode->TabIndex = 1;
					this->cbAQMode->SelectedIndexChanged += new System::EventHandler(this, &x264ConfigurationPanel::cbAQMode_SelectedIndexChanged);
					// 
					// lbAQMode
					// 
					this->lbAQMode->AutoSize = true;
					this->lbAQMode->Location = new System::Drawing::Point(12, 22);
					this->lbAQMode->Name = "lbAQMode";
					this->lbAQMode->Size = new System::Drawing::Size(34, 13);
					this->lbAQMode->TabIndex = 0;
					this->lbAQMode->Text = "Mode";
					this->lbAQMode->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
					// 
					// quantizerMatrixGroupbox
					// 
					this->quantizerMatrixGroupbox->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right)));
					this->quantizerMatrixGroupbox->Controls->Add(this->cqmComboBox1);
					this->quantizerMatrixGroupbox->Location = new System::Drawing::Point(298, 87);
					this->quantizerMatrixGroupbox->Name = "quantizerMatrixGroupbox";
					this->quantizerMatrixGroupbox->Size = new System::Drawing::Size(201, 59);
					this->quantizerMatrixGroupbox->TabIndex = 2;
					this->quantizerMatrixGroupbox->TabStop = false;
					this->quantizerMatrixGroupbox->Text = "Quantizer Matrices";
					// 
					// cqmComboBox1
					// 
					this->cqmComboBox1->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
					this->cqmComboBox1->setFilter("Quantizer matrix files (*.cfg)|*.cfg|All Files (*.*)|*.*");
					this->cqmComboBox1->Location = new System::Drawing::Point(12, 19);
					this->cqmComboBox1->MaximumSize = new System::Drawing::Size(1000, 29);
					this->cqmComboBox1->MinimumSize = new System::Drawing::Size(64, 29);
					this->cqmComboBox1->Name = "cqmComboBox1";
					this->cqmComboBox1->setSelectedIndex(0);
					this->cqmComboBox1->Size = new System::Drawing::Size(175, 29);
					this->cqmComboBox1->TabIndex = 5;
					this->cqmComboBox1->setType(MeGUI::core::gui::FileSCBox::Default);
					this->cqmComboBox1->SelectionChanged += new MeGUI::StringChanged(this, &x264ConfigurationPanel::cqmComboBox1_SelectionChanged);
					// 
					// x264QuantizerGroupBox
					// 
					this->x264QuantizerGroupBox->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
					this->x264QuantizerGroupBox->Controls->Add(this->deadzoneIntra);
					this->x264QuantizerGroupBox->Controls->Add(this->deadzoneInter);
					this->x264QuantizerGroupBox->Controls->Add(this->lbx264DeadZones);
					this->x264QuantizerGroupBox->Controls->Add(this->x264PBFrameFactor);
					this->x264QuantizerGroupBox->Controls->Add(this->x264IPFrameFactor);
					this->x264QuantizerGroupBox->Controls->Add(this->lbQuantizersRatio);
					this->x264QuantizerGroupBox->Controls->Add(this->x264CreditsQuantizer);
					this->x264QuantizerGroupBox->Controls->Add(this->x264CreditsQuantizerLabel);
					this->x264QuantizerGroupBox->Controls->Add(this->x264ChromaQPOffset);
					this->x264QuantizerGroupBox->Controls->Add(this->x264ChromaQPOffsetLabel);
					this->x264QuantizerGroupBox->Controls->Add(this->x264MaxQuantDelta);
					this->x264QuantizerGroupBox->Controls->Add(this->x264MaximumQuantizer);
					this->x264QuantizerGroupBox->Controls->Add(this->x264MinimimQuantizer);
					this->x264QuantizerGroupBox->Controls->Add(this->x264MinimimQuantizerLabel);
					this->x264QuantizerGroupBox->Location = new System::Drawing::Point(3, 3);
					this->x264QuantizerGroupBox->Name = "x264QuantizerGroupBox";
					this->x264QuantizerGroupBox->Size = new System::Drawing::Size(291, 183);
					this->x264QuantizerGroupBox->TabIndex = 0;
					this->x264QuantizerGroupBox->TabStop = false;
					this->x264QuantizerGroupBox->Text = "Quantizers";
					// 
					// deadzoneIntra
					// 
					this->deadzoneIntra->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right)));
					this->deadzoneIntra->Location = new System::Drawing::Point(229, 84);
					this->deadzoneIntra->Name = "deadzoneIntra";
					this->deadzoneIntra->Size = new System::Drawing::Size(48, 20);
					this->deadzoneIntra->TabIndex = 17;
					this->deadzoneIntra->Value = decimal(new int[4] {11, 0, 0, 0});
					this->deadzoneIntra->ValueChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// deadzoneInter
					// 
					this->deadzoneInter->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right)));
					this->deadzoneInter->Location = new System::Drawing::Point(175, 84);
					this->deadzoneInter->Name = "deadzoneInter";
					this->deadzoneInter->Size = new System::Drawing::Size(48, 20);
					this->deadzoneInter->TabIndex = 15;
					this->deadzoneInter->Value = decimal(new int[4] {21, 0, 0, 0});
					this->deadzoneInter->ValueChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// lbx264DeadZones
					// 
					this->lbx264DeadZones->AutoSize = true;
					this->lbx264DeadZones->Location = new System::Drawing::Point(12, 86);
					this->lbx264DeadZones->Name = "lbx264DeadZones";
					this->lbx264DeadZones->Size = new System::Drawing::Size(123, 13);
					this->lbx264DeadZones->TabIndex = 21;
					this->lbx264DeadZones->Text = "Deadzones (Inter / Intra)";
					this->lbx264DeadZones->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
					// 
					// x264PBFrameFactor
					// 
					this->x264PBFrameFactor->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right)));
					this->x264PBFrameFactor->DecimalPlaces = 1;
					this->x264PBFrameFactor->Increment = decimal(new int[4] {1, 0, 0, 65536});
					this->x264PBFrameFactor->Location = new System::Drawing::Point(229, 49);
					this->x264PBFrameFactor->Maximum = decimal(new int[4] {10, 0, 0, 0});
					this->x264PBFrameFactor->Minimum = decimal(new int[4] {1, 0, 0, 0});
					this->x264PBFrameFactor->Name = "x264PBFrameFactor";
					this->x264PBFrameFactor->Size = new System::Drawing::Size(48, 20);
					this->x264PBFrameFactor->TabIndex = 20;
					this->x264PBFrameFactor->Value = decimal(new int[4] {13, 0, 0, 65536});
					this->x264PBFrameFactor->ValueChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// x264IPFrameFactor
					// 
					this->x264IPFrameFactor->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right)));
					this->x264IPFrameFactor->DecimalPlaces = 1;
					this->x264IPFrameFactor->Increment = decimal(new int[4] {1, 0, 0, 65536});
					this->x264IPFrameFactor->Location = new System::Drawing::Point(175, 49);
					this->x264IPFrameFactor->Maximum = decimal(new int[4] {10, 0, 0, 0});
					this->x264IPFrameFactor->Minimum = decimal(new int[4] {1, 0, 0, 0});
					this->x264IPFrameFactor->Name = "x264IPFrameFactor";
					this->x264IPFrameFactor->Size = new System::Drawing::Size(48, 20);
					this->x264IPFrameFactor->TabIndex = 19;
					this->x264IPFrameFactor->Value = decimal(new int[4] {14, 0, 0, 65536});
					this->x264IPFrameFactor->ValueChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// lbQuantizersRatio
					// 
					this->lbQuantizersRatio->AutoSize = true;
					this->lbQuantizersRatio->Location = new System::Drawing::Point(12, 51);
					this->lbQuantizersRatio->Name = "lbQuantizersRatio";
					this->lbQuantizersRatio->Size = new System::Drawing::Size(135, 13);
					this->lbQuantizersRatio->TabIndex = 18;
					this->lbQuantizersRatio->Text = "Quantizers Ratio (I:P / P:B)";
					this->lbQuantizersRatio->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
					// 
					// x264CreditsQuantizer
					// 
					this->x264CreditsQuantizer->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right)));
					this->x264CreditsQuantizer->Location = new System::Drawing::Point(229, 149);
					this->x264CreditsQuantizer->Maximum = decimal(new int[4] {51, 0, 0, 0});
					this->x264CreditsQuantizer->Minimum = decimal(new int[4] {1, 0, 0, 0});
					this->x264CreditsQuantizer->Name = "x264CreditsQuantizer";
					this->x264CreditsQuantizer->Size = new System::Drawing::Size(48, 20);
					this->x264CreditsQuantizer->TabIndex = 7;
					this->x264CreditsQuantizer->Value = decimal(new int[4] {40, 0, 0, 0});
					this->x264CreditsQuantizer->ValueChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// x264CreditsQuantizerLabel
					// 
					this->x264CreditsQuantizerLabel->Location = new System::Drawing::Point(9, 149);
					this->x264CreditsQuantizerLabel->Name = "x264CreditsQuantizerLabel";
					this->x264CreditsQuantizerLabel->Padding = new System::Windows::Forms::Padding(3);
					this->x264CreditsQuantizerLabel->Size = new System::Drawing::Size(122, 17);
					this->x264CreditsQuantizerLabel->TabIndex = 6;
					this->x264CreditsQuantizerLabel->Text = "Credits Quantizer";
					this->x264CreditsQuantizerLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
					// 
					// x264ChromaQPOffset
					// 
					this->x264ChromaQPOffset->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right)));
					this->x264ChromaQPOffset->Location = new System::Drawing::Point(229, 119);
					this->x264ChromaQPOffset->Maximum = decimal(new int[4] {12, 0, 0, 0});
					this->x264ChromaQPOffset->Minimum = decimal(new int[4] {12, 0, 0, -2147483648});
					this->x264ChromaQPOffset->Name = "x264ChromaQPOffset";
					this->x264ChromaQPOffset->Size = new System::Drawing::Size(48, 20);
					this->x264ChromaQPOffset->TabIndex = 13;
					this->x264ChromaQPOffset->ValueChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// x264ChromaQPOffsetLabel
					// 
					this->x264ChromaQPOffsetLabel->Location = new System::Drawing::Point(9, 119);
					this->x264ChromaQPOffsetLabel->Name = "x264ChromaQPOffsetLabel";
					this->x264ChromaQPOffsetLabel->Padding = new System::Windows::Forms::Padding(3);
					this->x264ChromaQPOffsetLabel->Size = new System::Drawing::Size(122, 17);
					this->x264ChromaQPOffsetLabel->TabIndex = 12;
					this->x264ChromaQPOffsetLabel->Text = "Chroma QP Offset";
					this->x264ChromaQPOffsetLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
					// 
					// x264MaxQuantDelta
					// 
					this->x264MaxQuantDelta->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right)));
					this->x264MaxQuantDelta->Location = new System::Drawing::Point(229, 17);
					this->x264MaxQuantDelta->Maximum = decimal(new int[4] {51, 0, 0, 0});
					this->x264MaxQuantDelta->Minimum = decimal(new int[4] {1, 0, 0, 0});
					this->x264MaxQuantDelta->Name = "x264MaxQuantDelta";
					this->x264MaxQuantDelta->Size = new System::Drawing::Size(48, 20);
					this->x264MaxQuantDelta->TabIndex = 5;
					this->x264MaxQuantDelta->Value = decimal(new int[4] {4, 0, 0, 0});
					this->x264MaxQuantDelta->ValueChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// x264MaximumQuantizer
					// 
					this->x264MaximumQuantizer->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right)));
					this->x264MaximumQuantizer->Location = new System::Drawing::Point(175, 17);
					this->x264MaximumQuantizer->Maximum = decimal(new int[4] {69, 0, 0, 0});
					this->x264MaximumQuantizer->Minimum = decimal(new int[4] {1, 0, 0, 0});
					this->x264MaximumQuantizer->Name = "x264MaximumQuantizer";
					this->x264MaximumQuantizer->Size = new System::Drawing::Size(48, 20);
					this->x264MaximumQuantizer->TabIndex = 3;
					this->x264MaximumQuantizer->Value = decimal(new int[4] {69, 0, 0, 0});
					this->x264MaximumQuantizer->ValueChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// x264MinimimQuantizer
					// 
					this->x264MinimimQuantizer->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right)));
					this->x264MinimimQuantizer->Location = new System::Drawing::Point(121, 17);
					this->x264MinimimQuantizer->Maximum = decimal(new int[4] {51, 0, 0, 0});
					this->x264MinimimQuantizer->Name = "x264MinimimQuantizer";
					this->x264MinimimQuantizer->Size = new System::Drawing::Size(48, 20);
					this->x264MinimimQuantizer->TabIndex = 1;
					this->x264MinimimQuantizer->ValueChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// x264MinimimQuantizerLabel
					// 
					this->x264MinimimQuantizerLabel->Location = new System::Drawing::Point(9, 16);
					this->x264MinimimQuantizerLabel->Name = "x264MinimimQuantizerLabel";
					this->x264MinimimQuantizerLabel->Padding = new System::Windows::Forms::Padding(3);
					this->x264MinimimQuantizerLabel->Size = new System::Drawing::Size(93, 18);
					this->x264MinimimQuantizerLabel->TabIndex = 0;
					this->x264MinimimQuantizerLabel->Text = "Min/Max/Delta";
					this->x264MinimimQuantizerLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
					// 
					// label3
					// 
					this->label3->Location = new System::Drawing::Point(12, 227);
					this->label3->Name = "label3";
					this->label3->Size = new System::Drawing::Size(207, 17);
					this->label3->TabIndex = 16;
					this->label3->Text = "Intra luma quantization deadzone";
					// 
					// label2
					// 
					this->label2->Location = new System::Drawing::Point(12, 201);
					this->label2->Name = "label2";
					this->label2->Size = new System::Drawing::Size(207, 17);
					this->label2->TabIndex = 14;
					this->label2->Text = "Inter luma quantization deadzone";
					// 
					// customCommandlineOptionsLabel
					// 
					this->customCommandlineOptionsLabel->Location = new System::Drawing::Point(6, 301);
					this->customCommandlineOptionsLabel->Name = "customCommandlineOptionsLabel";
					this->customCommandlineOptionsLabel->Size = new System::Drawing::Size(167, 13);
					this->customCommandlineOptionsLabel->TabIndex = 1;
					this->customCommandlineOptionsLabel->Text = "Custom Commandline Options";
					this->customCommandlineOptionsLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
					// 
					// openFileDialog
					// 
					this->openFileDialog->FileName = "openFileDialog1";
					// 
					// helpButton1
					// 
					this->helpButton1->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
					this->helpButton1->setArticleName("Video Encoder Configuration/x264");
					this->helpButton1->AutoSize = true;
					this->helpButton1->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
					this->helpButton1->Location = new System::Drawing::Point(455, 358);
					this->helpButton1->Name = "helpButton1";
					this->helpButton1->Size = new System::Drawing::Size(39, 23);
					this->helpButton1->TabIndex = 10;
					// 
					// gbPresets
					// 
					this->gbPresets->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
					this->gbPresets->BackColor = System::Drawing::Color::Transparent;
					this->gbPresets->Controls->Add(this->lbPreset);
					this->gbPresets->Controls->Add(this->tbx264Presets);
					this->gbPresets->Location = new System::Drawing::Point(6, 152);
					this->gbPresets->Name = "gbPresets";
					this->gbPresets->Size = new System::Drawing::Size(310, 102);
					this->gbPresets->TabIndex = 13;
					this->gbPresets->TabStop = false;
					this->gbPresets->Text = " Preset ";
					// 
					// lbPreset
					// 
					this->lbPreset->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right)));
					this->lbPreset->AutoSize = true;
					this->lbPreset->Font = new System::Drawing::Font("Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, (static_cast<unsigned char>(0)));
					this->lbPreset->Location = new System::Drawing::Point(45, 28);
					this->lbPreset->Name = "lbPreset";
					this->lbPreset->Size = new System::Drawing::Size(44, 13);
					this->lbPreset->TabIndex = 1;
					this->lbPreset->Text = "Medium";
					// 
					// tbx264Presets
					// 
					this->tbx264Presets->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
					this->tbx264Presets->AutoSize = false;
					this->tbx264Presets->BackColor = System::Drawing::SystemColors::ControlLightLight;
					this->tbx264Presets->Location = new System::Drawing::Point(12, 50);
					this->tbx264Presets->Maximum = 9;
					this->tbx264Presets->Name = "tbx264Presets";
					this->tbx264Presets->Size = new System::Drawing::Size(286, 30);
					this->tbx264Presets->TabIndex = 0;
					this->tbx264Presets->TickStyle = System::Windows::Forms::TickStyle::TopLeft;
					this->tbx264Presets->Value = 5;
					this->tbx264Presets->Scroll += new System::EventHandler(this, &x264ConfigurationPanel::tbx264Presets_Scroll);
					this->tbx264Presets->ValueChanged += new System::EventHandler(this, &x264ConfigurationPanel::tbx264Presets_Scroll);
					// 
					// gbTunes
					// 
					this->gbTunes->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right)));
					this->gbTunes->Controls->Add(this->x264Tunes);
					this->gbTunes->Location = new System::Drawing::Point(322, 98);
					this->gbTunes->Name = "gbTunes";
					this->gbTunes->Size = new System::Drawing::Size(172, 48);
					this->gbTunes->TabIndex = 14;
					this->gbTunes->TabStop = false;
					this->gbTunes->Text = " Tuning ";
					// 
					// x264Tunes
					// 
					this->x264Tunes->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
					this->x264Tunes->FormattingEnabled = true;
					this->x264Tunes->Location = new System::Drawing::Point(10, 16);
					this->x264Tunes->Name = "x264Tunes";
					this->x264Tunes->Size = new System::Drawing::Size(157, 21);
					this->x264Tunes->TabIndex = 0;
					this->x264Tunes->SelectedIndexChanged += new System::EventHandler(this, &x264ConfigurationPanel::x264Tunes_SelectedIndexChanged);
					// 
					// AnalysisTabPage
					// 
					this->AnalysisTabPage->Controls->Add(this->x264Bluray);
					this->AnalysisTabPage->Controls->Add(this->x264QuantOptionsGroupbox);
					this->AnalysisTabPage->Controls->Add(this->x264MBGroupbox);
					this->AnalysisTabPage->Controls->Add(this->x264OtherOptionsGroupbox);
					this->AnalysisTabPage->Location = new System::Drawing::Point(4, 22);
					this->AnalysisTabPage->Name = "AnalysisTabPage";
					this->AnalysisTabPage->Padding = new System::Windows::Forms::Padding(3);
					this->AnalysisTabPage->Size = new System::Drawing::Size(502, 403);
					this->AnalysisTabPage->TabIndex = 5;
					this->AnalysisTabPage->Text = "Analysis";
					this->AnalysisTabPage->UseVisualStyleBackColor = true;
					// 
					// x264Bluray
					// 
					this->x264Bluray->Controls->Add(this->chkBlurayCompat);
					this->x264Bluray->Controls->Add(this->fakeInterlaced);
					this->x264Bluray->Controls->Add(this->x264hrdLabel);
					this->x264Bluray->Controls->Add(this->x264hrd);
					this->x264Bluray->Controls->Add(this->x264aud);
					this->x264Bluray->Location = new System::Drawing::Point(296, 135);
					this->x264Bluray->Name = "x264Bluray";
					this->x264Bluray->Size = new System::Drawing::Size(200, 134);
					this->x264Bluray->TabIndex = 29;
					this->x264Bluray->TabStop = false;
					this->x264Bluray->Text = " Blu-Ray ";
					// 
					// chkBlurayCompat
					// 
					this->chkBlurayCompat->AutoSize = true;
					this->chkBlurayCompat->Location = new System::Drawing::Point(9, 98);
					this->chkBlurayCompat->Name = "chkBlurayCompat";
					this->chkBlurayCompat->Size = new System::Drawing::Size(154, 17);
					this->chkBlurayCompat->TabIndex = 4;
					this->chkBlurayCompat->Text = "Enable Blu-ray compatibility";
					this->chkBlurayCompat->UseVisualStyleBackColor = true;
					this->chkBlurayCompat->CheckedChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// fakeInterlaced
					// 
					this->fakeInterlaced->AutoSize = true;
					this->fakeInterlaced->Location = new System::Drawing::Point(9, 75);
					this->fakeInterlaced->Name = "fakeInterlaced";
					this->fakeInterlaced->Size = new System::Drawing::Size(100, 17);
					this->fakeInterlaced->TabIndex = 3;
					this->fakeInterlaced->Text = "Fake Interlaced";
					this->fakeInterlaced->UseVisualStyleBackColor = true;
					this->fakeInterlaced->CheckedChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// x264hrdLabel
					// 
					this->x264hrdLabel->AutoSize = true;
					this->x264hrdLabel->Location = new System::Drawing::Point(6, 29);
					this->x264hrdLabel->Name = "x264hrdLabel";
					this->x264hrdLabel->Size = new System::Drawing::Size(52, 13);
					this->x264hrdLabel->TabIndex = 2;
					this->x264hrdLabel->Text = "HRD Info";
					this->x264hrdLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
					// 
					// x264hrd
					// 
					this->x264hrd->AutoCompleteCustomSource->AddRange(new std::string[3] {"None", "VBR", "CBR"});
					this->x264hrd->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
					this->x264hrd->FormattingEnabled = true;
					this->x264hrd->Items->AddRange(new object[3] {"None", "VBR", "CBR"});
					this->x264hrd->Location = new System::Drawing::Point(66, 26);
					this->x264hrd->Name = "x264hrd";
					this->x264hrd->Size = new System::Drawing::Size(111, 21);
					this->x264hrd->TabIndex = 1;
					this->x264hrd->SelectedIndexChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// x264aud
					// 
					this->x264aud->AutoSize = true;
					this->x264aud->Location = new System::Drawing::Point(9, 52);
					this->x264aud->Name = "x264aud";
					this->x264aud->Size = new System::Drawing::Size(153, 17);
					this->x264aud->TabIndex = 0;
					this->x264aud->Text = "Use Access Unit Delimiters";
					this->x264aud->UseVisualStyleBackColor = true;
					this->x264aud->CheckedChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// x264QuantOptionsGroupbox
					// 
					this->x264QuantOptionsGroupbox->Controls->Add(this->label16);
					this->x264QuantOptionsGroupbox->Controls->Add(this->label15);
					this->x264QuantOptionsGroupbox->Controls->Add(this->label14);
					this->x264QuantOptionsGroupbox->Controls->Add(this->label13);
					this->x264QuantOptionsGroupbox->Controls->Add(this->NoiseReduction);
					this->x264QuantOptionsGroupbox->Controls->Add(this->NoiseReductionLabel);
					this->x264QuantOptionsGroupbox->Controls->Add(this->nopsy);
					this->x264QuantOptionsGroupbox->Controls->Add(this->x264MixedReferences);
					this->x264QuantOptionsGroupbox->Controls->Add(this->x264BframePredictionMode);
					this->x264QuantOptionsGroupbox->Controls->Add(this->x264BframePredictionModeLabel);
					this->x264QuantOptionsGroupbox->Controls->Add(this->label4);
					this->x264QuantOptionsGroupbox->Controls->Add(this->PsyTrellis);
					this->x264QuantOptionsGroupbox->Controls->Add(this->label5);
					this->x264QuantOptionsGroupbox->Controls->Add(this->PsyRD);
					this->x264QuantOptionsGroupbox->Controls->Add(this->noDCTDecimateOption);
					this->x264QuantOptionsGroupbox->Controls->Add(this->noFastPSkip);
					this->x264QuantOptionsGroupbox->Controls->Add(this->trellis);
					this->x264QuantOptionsGroupbox->Controls->Add(this->label7);
					this->x264QuantOptionsGroupbox->Location = new System::Drawing::Point(6, 135);
					this->x264QuantOptionsGroupbox->Name = "x264QuantOptionsGroupbox";
					this->x264QuantOptionsGroupbox->Size = new System::Drawing::Size(284, 272);
					this->x264QuantOptionsGroupbox->TabIndex = 28;
					this->x264QuantOptionsGroupbox->TabStop = false;
					this->x264QuantOptionsGroupbox->Text = "Extra";
					// 
					// label16
					// 
					this->label16->AutoSize = true;
					this->label16->Location = new System::Drawing::Point(16, 214);
					this->label16->Name = "label16";
					this->label16->Size = new System::Drawing::Size(160, 13);
					this->label16->TabIndex = 21;
					this->label16->Text = "No Psychovisual Enhancements";
					// 
					// label15
					// 
					this->label15->AutoSize = true;
					this->label15->Location = new System::Drawing::Point(16, 190);
					this->label15->Name = "label15";
					this->label15->Size = new System::Drawing::Size(78, 13);
					this->label15->TabIndex = 20;
					this->label15->Text = "No Fast P-Skip";
					// 
					// label14
					// 
					this->label14->AutoSize = true;
					this->label14->Location = new System::Drawing::Point(16, 167);
					this->label14->Name = "label14";
					this->label14->Size = new System::Drawing::Size(97, 13);
					this->label14->TabIndex = 19;
					this->label14->Text = "No Dct Decimation";
					// 
					// label13
					// 
					this->label13->AutoSize = true;
					this->label13->Location = new System::Drawing::Point(16, 145);
					this->label13->Name = "label13";
					this->label13->Size = new System::Drawing::Size(139, 13);
					this->label13->TabIndex = 18;
					this->label13->Text = "No Mixed Reference frames";
					// 
					// NoiseReduction
					// 
					this->NoiseReduction->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right)));
					this->NoiseReduction->Location = new System::Drawing::Point(224, 239);
					this->NoiseReduction->Maximum = decimal(new int[4] {10000, 0, 0, 0});
					this->NoiseReduction->Name = "NoiseReduction";
					this->NoiseReduction->Size = new System::Drawing::Size(44, 20);
					this->NoiseReduction->TabIndex = 17;
					this->NoiseReduction->ValueChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// NoiseReductionLabel
					// 
					this->NoiseReductionLabel->Location = new System::Drawing::Point(16, 241);
					this->NoiseReductionLabel->Name = "NoiseReductionLabel";
					this->NoiseReductionLabel->Size = new System::Drawing::Size(86, 13);
					this->NoiseReductionLabel->TabIndex = 16;
					this->NoiseReductionLabel->Text = "Noise Reduction";
					this->NoiseReductionLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
					// 
					// nopsy
					// 
					this->nopsy->CheckAlign = System::Drawing::ContentAlignment::MiddleRight;
					this->nopsy->Location = new System::Drawing::Point(224, 209);
					this->nopsy->Name = "nopsy";
					this->nopsy->Size = new System::Drawing::Size(45, 24);
					this->nopsy->TabIndex = 15;
					this->nopsy->UseVisualStyleBackColor = true;
					this->nopsy->CheckedChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// x264MixedReferences
					// 
					this->x264MixedReferences->CheckAlign = System::Drawing::ContentAlignment::MiddleRight;
					this->x264MixedReferences->Location = new System::Drawing::Point(224, 140);
					this->x264MixedReferences->Name = "x264MixedReferences";
					this->x264MixedReferences->Size = new System::Drawing::Size(45, 24);
					this->x264MixedReferences->TabIndex = 14;
					this->x264MixedReferences->CheckedChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// x264BframePredictionMode
					// 
					this->x264BframePredictionMode->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
					this->x264BframePredictionMode->Items->AddRange(new object[4] {"None", "Spatial", "Temporal", "Auto"});
					this->x264BframePredictionMode->Location = new System::Drawing::Point(154, 25);
					this->x264BframePredictionMode->Name = "x264BframePredictionMode";
					this->x264BframePredictionMode->Size = new System::Drawing::Size(115, 21);
					this->x264BframePredictionMode->TabIndex = 13;
					this->x264BframePredictionMode->SelectedIndexChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// x264BframePredictionModeLabel
					// 
					this->x264BframePredictionModeLabel->Location = new System::Drawing::Point(16, 29);
					this->x264BframePredictionModeLabel->Name = "x264BframePredictionModeLabel";
					this->x264BframePredictionModeLabel->Size = new System::Drawing::Size(102, 13);
					this->x264BframePredictionModeLabel->TabIndex = 12;
					this->x264BframePredictionModeLabel->Text = "MV Prediction mode";
					this->x264BframePredictionModeLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
					// 
					// label4
					// 
					this->label4->AutoSize = true;
					this->label4->Location = new System::Drawing::Point(16, 116);
					this->label4->Name = "label4";
					this->label4->Size = new System::Drawing::Size(97, 13);
					this->label4->TabIndex = 11;
					this->label4->Text = "Psy-Trellis Strength";
					// 
					// PsyTrellis
					// 
					this->PsyTrellis->DecimalPlaces = 2;
					this->PsyTrellis->Increment = decimal(new int[4] {1, 0, 0, 131072});
					this->PsyTrellis->Location = new System::Drawing::Point(224, 114);
					this->PsyTrellis->Name = "PsyTrellis";
					this->PsyTrellis->Size = new System::Drawing::Size(45, 20);
					this->PsyTrellis->TabIndex = 10;
					this->PsyTrellis->ValueChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// label5
					// 
					this->label5->Location = new System::Drawing::Point(16, 90);
					this->label5->Name = "label5";
					this->label5->Size = new System::Drawing::Size(86, 13);
					this->label5->TabIndex = 9;
					this->label5->Text = "Psy-RD Strength";
					// 
					// PsyRD
					// 
					this->PsyRD->DecimalPlaces = 2;
					this->PsyRD->Increment = decimal(new int[4] {1, 0, 0, 131072});
					this->PsyRD->Location = new System::Drawing::Point(224, 88);
					this->PsyRD->Maximum = decimal(new int[4] {2, 0, 0, 0});
					this->PsyRD->Name = "PsyRD";
					this->PsyRD->Size = new System::Drawing::Size(45, 20);
					this->PsyRD->TabIndex = 8;
					this->PsyRD->Value = decimal(new int[4] {10, 0, 0, 65536});
					this->PsyRD->ValueChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// noDCTDecimateOption
					// 
					this->noDCTDecimateOption->CheckAlign = System::Drawing::ContentAlignment::MiddleRight;
					this->noDCTDecimateOption->Location = new System::Drawing::Point(224, 163);
					this->noDCTDecimateOption->Name = "noDCTDecimateOption";
					this->noDCTDecimateOption->Size = new System::Drawing::Size(45, 23);
					this->noDCTDecimateOption->TabIndex = 6;
					this->noDCTDecimateOption->CheckedChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// noFastPSkip
					// 
					this->noFastPSkip->CheckAlign = System::Drawing::ContentAlignment::MiddleRight;
					this->noFastPSkip->Location = new System::Drawing::Point(224, 186);
					this->noFastPSkip->Name = "noFastPSkip";
					this->noFastPSkip->Size = new System::Drawing::Size(45, 23);
					this->noFastPSkip->TabIndex = 7;
					this->noFastPSkip->CheckedChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// trellis
					// 
					this->trellis->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
					this->trellis->Items->AddRange(new object[3] {"0 - None", "1 - Final MB", "2 - Always"});
					this->trellis->Location = new System::Drawing::Point(154, 53);
					this->trellis->Name = "trellis";
					this->trellis->Size = new System::Drawing::Size(115, 21);
					this->trellis->TabIndex = 1;
					this->trellis->SelectedIndexChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// label7
					// 
					this->label7->Location = new System::Drawing::Point(16, 56);
					this->label7->Name = "label7";
					this->label7->Size = new System::Drawing::Size(34, 13);
					this->label7->TabIndex = 0;
					this->label7->Text = "Trellis";
					this->label7->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
					// 
					// x264MBGroupbox
					// 
					this->x264MBGroupbox->Controls->Add(this->label1);
					this->x264MBGroupbox->Controls->Add(this->macroblockOptions);
					this->x264MBGroupbox->Controls->Add(this->adaptiveDCT);
					this->x264MBGroupbox->Controls->Add(this->x264I4x4mv);
					this->x264MBGroupbox->Controls->Add(this->x264I8x8mv);
					this->x264MBGroupbox->Controls->Add(this->x264P4x4mv);
					this->x264MBGroupbox->Controls->Add(this->x264B8x8mv);
					this->x264MBGroupbox->Controls->Add(this->x264P8x8mv);
					this->x264MBGroupbox->Location = new System::Drawing::Point(296, 6);
					this->x264MBGroupbox->Name = "x264MBGroupbox";
					this->x264MBGroupbox->Size = new System::Drawing::Size(202, 123);
					this->x264MBGroupbox->TabIndex = 27;
					this->x264MBGroupbox->TabStop = false;
					this->x264MBGroupbox->Text = "Macroblocks";
					// 
					// label1
					// 
					this->label1->AutoSize = true;
					this->label1->Location = new System::Drawing::Point(6, 19);
					this->label1->Name = "label1";
					this->label1->Size = new System::Drawing::Size(50, 13);
					this->label1->TabIndex = 7;
					this->label1->Text = "Partitions";
					// 
					// macroblockOptions
					// 
					this->macroblockOptions->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
					this->macroblockOptions->Items->AddRange(new object[4] {"All", "None", "Custom", "Default"});
					this->macroblockOptions->Location = new System::Drawing::Point(66, 16);
					this->macroblockOptions->Name = "macroblockOptions";
					this->macroblockOptions->Size = new System::Drawing::Size(111, 21);
					this->macroblockOptions->TabIndex = 0;
					this->macroblockOptions->SelectedIndexChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// adaptiveDCT
					// 
					this->adaptiveDCT->Checked = true;
					this->adaptiveDCT->CheckState = System::Windows::Forms::CheckState::Checked;
					this->adaptiveDCT->Location = new System::Drawing::Point(9, 40);
					this->adaptiveDCT->Name = "adaptiveDCT";
					this->adaptiveDCT->Size = new System::Drawing::Size(104, 24);
					this->adaptiveDCT->TabIndex = 1;
					this->adaptiveDCT->Text = "Adaptive DCT";
					this->adaptiveDCT->CheckedChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// x264I4x4mv
					// 
					this->x264I4x4mv->Checked = true;
					this->x264I4x4mv->CheckState = System::Windows::Forms::CheckState::Checked;
					this->x264I4x4mv->Location = new System::Drawing::Point(9, 67);
					this->x264I4x4mv->Name = "x264I4x4mv";
					this->x264I4x4mv->Size = new System::Drawing::Size(56, 24);
					this->x264I4x4mv->TabIndex = 2;
					this->x264I4x4mv->Text = "I4x4";
					this->x264I4x4mv->CheckedChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// x264I8x8mv
					// 
					this->x264I8x8mv->Checked = true;
					this->x264I8x8mv->CheckState = System::Windows::Forms::CheckState::Checked;
					this->x264I8x8mv->Location = new System::Drawing::Point(9, 93);
					this->x264I8x8mv->Name = "x264I8x8mv";
					this->x264I8x8mv->Size = new System::Drawing::Size(56, 24);
					this->x264I8x8mv->TabIndex = 4;
					this->x264I8x8mv->Text = "I8x8";
					this->x264I8x8mv->CheckedChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// x264P4x4mv
					// 
					this->x264P4x4mv->Location = new System::Drawing::Point(66, 67);
					this->x264P4x4mv->Name = "x264P4x4mv";
					this->x264P4x4mv->Size = new System::Drawing::Size(64, 24);
					this->x264P4x4mv->TabIndex = 3;
					this->x264P4x4mv->Text = "P4x4";
					this->x264P4x4mv->CheckedChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// x264B8x8mv
					// 
					this->x264B8x8mv->Checked = true;
					this->x264B8x8mv->CheckState = System::Windows::Forms::CheckState::Checked;
					this->x264B8x8mv->Location = new System::Drawing::Point(121, 93);
					this->x264B8x8mv->Name = "x264B8x8mv";
					this->x264B8x8mv->Size = new System::Drawing::Size(56, 24);
					this->x264B8x8mv->TabIndex = 6;
					this->x264B8x8mv->Text = "B8x8";
					this->x264B8x8mv->CheckedChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// x264P8x8mv
					// 
					this->x264P8x8mv->Checked = true;
					this->x264P8x8mv->CheckState = System::Windows::Forms::CheckState::Checked;
					this->x264P8x8mv->Location = new System::Drawing::Point(66, 93);
					this->x264P8x8mv->Name = "x264P8x8mv";
					this->x264P8x8mv->Size = new System::Drawing::Size(64, 24);
					this->x264P8x8mv->TabIndex = 5;
					this->x264P8x8mv->Text = "P8x8";
					this->x264P8x8mv->CheckedChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// x264OtherOptionsGroupbox
					// 
					this->x264OtherOptionsGroupbox->Controls->Add(this->label17);
					this->x264OtherOptionsGroupbox->Controls->Add(this->x264SubpelRefinement);
					this->x264OtherOptionsGroupbox->Controls->Add(this->x264SubpelRefinementLabel);
					this->x264OtherOptionsGroupbox->Controls->Add(this->x264ChromaMe);
					this->x264OtherOptionsGroupbox->Controls->Add(this->x264MERangeLabel);
					this->x264OtherOptionsGroupbox->Controls->Add(this->x264METypeLabel);
					this->x264OtherOptionsGroupbox->Controls->Add(this->x264METype);
					this->x264OtherOptionsGroupbox->Controls->Add(this->x264MERange);
					this->x264OtherOptionsGroupbox->Location = new System::Drawing::Point(6, 6);
					this->x264OtherOptionsGroupbox->Name = "x264OtherOptionsGroupbox";
					this->x264OtherOptionsGroupbox->Size = new System::Drawing::Size(284, 123);
					this->x264OtherOptionsGroupbox->TabIndex = 19;
					this->x264OtherOptionsGroupbox->TabStop = false;
					this->x264OtherOptionsGroupbox->Text = "Motion Estimation";
					// 
					// label17
					// 
					this->label17->AutoSize = true;
					this->label17->Location = new System::Drawing::Point(8, 19);
					this->label17->Name = "label17";
					this->label17->Size = new System::Drawing::Size(68, 13);
					this->label17->TabIndex = 9;
					this->label17->Text = "Chroma M.E.";
					// 
					// x264SubpelRefinement
					// 
					this->x264SubpelRefinement->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right)));
					this->x264SubpelRefinement->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
					this->x264SubpelRefinement->Items->AddRange(new object[12] {"00 - Fullpel Only (not recommended)", "01 - QPel SAD", "02 - QPel SATD", "03 - HPel on MB then QPel", "04 - Always QPel", "05 - QPel & Bidir ME", "06 - RD on I/P frames", "07 - RD on all frames", "08 - RD refinement on I/P frames", "09 - RD refinement on all frames", "10 - QP-RD", "11 - Full RD: disable all early terminations"});
					this->x264SubpelRefinement->Location = new System::Drawing::Point(125, 96);
					this->x264SubpelRefinement->Name = "x264SubpelRefinement";
					this->x264SubpelRefinement->Size = new System::Drawing::Size(154, 21);
					this->x264SubpelRefinement->TabIndex = 8;
					this->x264SubpelRefinement->SelectedIndexChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// x264SubpelRefinementLabel
					// 
					this->x264SubpelRefinementLabel->AutoSize = true;
					this->x264SubpelRefinementLabel->Location = new System::Drawing::Point(8, 98);
					this->x264SubpelRefinementLabel->Name = "x264SubpelRefinementLabel";
					this->x264SubpelRefinementLabel->Size = new System::Drawing::Size(104, 13);
					this->x264SubpelRefinementLabel->TabIndex = 7;
					this->x264SubpelRefinementLabel->Text = "Subpixel Refinement";
					this->x264SubpelRefinementLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
					// 
					// x264ChromaMe
					// 
					this->x264ChromaMe->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right)));
					this->x264ChromaMe->CheckAlign = System::Drawing::ContentAlignment::MiddleRight;
					this->x264ChromaMe->Checked = true;
					this->x264ChromaMe->CheckState = System::Windows::Forms::CheckState::Checked;
					this->x264ChromaMe->Location = new System::Drawing::Point(230, 15);
					this->x264ChromaMe->Name = "x264ChromaMe";
					this->x264ChromaMe->Size = new System::Drawing::Size(48, 23);
					this->x264ChromaMe->TabIndex = 0;
					this->x264ChromaMe->CheckedChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// x264MERangeLabel
					// 
					this->x264MERangeLabel->AutoSize = true;
					this->x264MERangeLabel->Location = new System::Drawing::Point(8, 46);
					this->x264MERangeLabel->Name = "x264MERangeLabel";
					this->x264MERangeLabel->Size = new System::Drawing::Size(64, 13);
					this->x264MERangeLabel->TabIndex = 1;
					this->x264MERangeLabel->Text = "M.E. Range";
					this->x264MERangeLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
					// 
					// x264METypeLabel
					// 
					this->x264METypeLabel->AutoSize = true;
					this->x264METypeLabel->Location = new System::Drawing::Point(8, 72);
					this->x264METypeLabel->Name = "x264METypeLabel";
					this->x264METypeLabel->Size = new System::Drawing::Size(75, 13);
					this->x264METypeLabel->TabIndex = 5;
					this->x264METypeLabel->Text = "M.E. Algorithm";
					this->x264METypeLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
					// 
					// x264METype
					// 
					this->x264METype->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right)));
					this->x264METype->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
					this->x264METype->Items->AddRange(new object[5] {"Diamond", "Hexagon", "Multi hex", "Exhaustive", "SATD Exhaustive"});
					this->x264METype->Location = new System::Drawing::Point(125, 70);
					this->x264METype->Name = "x264METype";
					this->x264METype->Size = new System::Drawing::Size(154, 21);
					this->x264METype->TabIndex = 6;
					this->x264METype->SelectedIndexChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// x264MERange
					// 
					this->x264MERange->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right)));
					this->x264MERange->Location = new System::Drawing::Point(231, 44);
					this->x264MERange->Maximum = decimal(new int[4] {64, 0, 0, 0});
					this->x264MERange->Minimum = decimal(new int[4] {4, 0, 0, 0});
					this->x264MERange->Name = "x264MERange";
					this->x264MERange->Size = new System::Drawing::Size(48, 20);
					this->x264MERange->TabIndex = 2;
					this->x264MERange->Value = decimal(new int[4] {16, 0, 0, 0});
					this->x264MERange->ValueChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// pictureBox1
					// 
					this->pictureBox1->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right)));
					this->pictureBox1->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
					this->pictureBox1->Image = (static_cast<System::Drawing::Image*>(resources->GetObject("pictureBox1.Image")));
					this->pictureBox1->InitialImage = 0;
					this->pictureBox1->Location = new System::Drawing::Point(6, 20);
					this->pictureBox1->Name = "pictureBox1";
					this->pictureBox1->Size = new System::Drawing::Size(488, 72);
					this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
					this->pictureBox1->TabIndex = 15;
					this->pictureBox1->TabStop = false;
					this->pictureBox1->Click += new System::EventHandler(this, &x264ConfigurationPanel::pictureBox1_Click);
					// 
					// advancedSettings
					// 
					this->advancedSettings->AutoSize = true;
					this->advancedSettings->Location = new System::Drawing::Point(21, 364);
					this->advancedSettings->Name = "advancedSettings";
					this->advancedSettings->Size = new System::Drawing::Size(146, 17);
					this->advancedSettings->TabIndex = 16;
					this->advancedSettings->Text = "Show Advanced Settings";
					this->advancedSettings->UseVisualStyleBackColor = true;
					this->advancedSettings->CheckedChanged += new System::EventHandler(this, &x264ConfigurationPanel::advancedSettings_CheckedChanged);
					// 
					// PsyTrellisLabel
					// 
					this->PsyTrellisLabel->AutoSize = true;
					this->PsyTrellisLabel->Location = new System::Drawing::Point(5, 147);
					this->PsyTrellisLabel->Name = "PsyTrellisLabel";
					this->PsyTrellisLabel->Padding = new System::Windows::Forms::Padding(3);
					this->PsyTrellisLabel->Size = new System::Drawing::Size(103, 19);
					this->PsyTrellisLabel->TabIndex = 11;
					this->PsyTrellisLabel->Text = "Psy-Trellis Strength";
					// 
					// PsyRDLabel
					// 
					this->PsyRDLabel->AutoSize = true;
					this->PsyRDLabel->Location = new System::Drawing::Point(5, 122);
					this->PsyRDLabel->Name = "PsyRDLabel";
					this->PsyRDLabel->Padding = new System::Windows::Forms::Padding(3);
					this->PsyRDLabel->Size = new System::Drawing::Size(92, 19);
					this->PsyRDLabel->TabIndex = 9;
					this->PsyRDLabel->Text = "Psy-RD Strength";
					// 
					// x264NumberOfRefFramesLabel
					// 
					this->x264NumberOfRefFramesLabel->AutoSize = true;
					this->x264NumberOfRefFramesLabel->Location = new System::Drawing::Point(4, 42);
					this->x264NumberOfRefFramesLabel->Name = "x264NumberOfRefFramesLabel";
					this->x264NumberOfRefFramesLabel->Padding = new System::Windows::Forms::Padding(3);
					this->x264NumberOfRefFramesLabel->Size = new System::Drawing::Size(152, 19);
					this->x264NumberOfRefFramesLabel->TabIndex = 2;
					this->x264NumberOfRefFramesLabel->Text = "Number of Reference Frames";
					this->x264NumberOfRefFramesLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
					// 
					// trellisLabel
					// 
					this->trellisLabel->AutoSize = true;
					this->trellisLabel->Location = new System::Drawing::Point(5, 93);
					this->trellisLabel->Name = "trellisLabel";
					this->trellisLabel->Padding = new System::Windows::Forms::Padding(3);
					this->trellisLabel->Size = new System::Drawing::Size(40, 19);
					this->trellisLabel->TabIndex = 0;
					this->trellisLabel->Text = "Trellis";
					this->trellisLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
					// 
					// MiscTabPage
					// 
					this->MiscTabPage->Controls->Add(this->gbOther);
					this->MiscTabPage->Controls->Add(this->gbAdjust);
					this->MiscTabPage->Controls->Add(this->gbInOut);
					this->MiscTabPage->Controls->Add(this->gbVUI);
					this->MiscTabPage->Controls->Add(this->gbQPFile);
					this->MiscTabPage->Controls->Add(this->gbx264CustomCmd);
					this->MiscTabPage->Location = new System::Drawing::Point(4, 22);
					this->MiscTabPage->Name = "MiscTabPage";
					this->MiscTabPage->Padding = new System::Windows::Forms::Padding(3);
					this->MiscTabPage->Size = new System::Drawing::Size(502, 403);
					this->MiscTabPage->TabIndex = 6;
					this->MiscTabPage->Text = "Misc";
					this->MiscTabPage->UseVisualStyleBackColor = true;
					// 
					// gbOther
					// 
					this->gbOther->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
					this->gbOther->Controls->Add(this->chkTuneZeroLatency);
					this->gbOther->Controls->Add(this->chkTuneFastDecode);
					this->gbOther->Controls->Add(this->x264NbThreads);
					this->gbOther->Controls->Add(this->nonDeterministic);
					this->gbOther->Controls->Add(this->x264SlowFirstpass);
					this->gbOther->Controls->Add(this->threadin);
					this->gbOther->Controls->Add(this->x264NbThreadsLabel);
					this->gbOther->Location = new System::Drawing::Point(6, 291);
					this->gbOther->Name = "gbOther";
					this->gbOther->Size = new System::Drawing::Size(317, 106);
					this->gbOther->TabIndex = 34;
					this->gbOther->TabStop = false;
					this->gbOther->Text = "Other";
					// 
					// chkTuneZeroLatency
					// 
					this->chkTuneZeroLatency->CheckAlign = System::Drawing::ContentAlignment::MiddleRight;
					this->chkTuneZeroLatency->Location = new System::Drawing::Point(184, 76);
					this->chkTuneZeroLatency->Name = "chkTuneZeroLatency";
					this->chkTuneZeroLatency->Size = new System::Drawing::Size(125, 24);
					this->chkTuneZeroLatency->TabIndex = 40;
					this->chkTuneZeroLatency->Text = "Zero Latency";
					this->chkTuneZeroLatency->UseVisualStyleBackColor = true;
					this->chkTuneZeroLatency->CheckedChanged += new System::EventHandler(this, &x264ConfigurationPanel::x264Tunes_SelectedIndexChanged);
					// 
					// chkTuneFastDecode
					// 
					this->chkTuneFastDecode->CheckAlign = System::Drawing::ContentAlignment::MiddleRight;
					this->chkTuneFastDecode->Location = new System::Drawing::Point(12, 76);
					this->chkTuneFastDecode->Name = "chkTuneFastDecode";
					this->chkTuneFastDecode->Size = new System::Drawing::Size(125, 24);
					this->chkTuneFastDecode->TabIndex = 39;
					this->chkTuneFastDecode->Text = "Fast Decode";
					this->chkTuneFastDecode->UseVisualStyleBackColor = true;
					this->chkTuneFastDecode->CheckedChanged += new System::EventHandler(this, &x264ConfigurationPanel::x264Tunes_SelectedIndexChanged);
					// 
					// x264NbThreads
					// 
					this->x264NbThreads->Location = new System::Drawing::Point(113, 21);
					this->x264NbThreads->Maximum = decimal(new int[4] {16, 0, 0, 0});
					this->x264NbThreads->Name = "x264NbThreads";
					this->x264NbThreads->Size = new System::Drawing::Size(37, 20);
					this->x264NbThreads->TabIndex = 12;
					this->x264NbThreads->ValueChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// nonDeterministic
					// 
					this->nonDeterministic->CheckAlign = System::Drawing::ContentAlignment::MiddleRight;
					this->nonDeterministic->Location = new System::Drawing::Point(12, 47);
					this->nonDeterministic->Name = "nonDeterministic";
					this->nonDeterministic->Size = new System::Drawing::Size(125, 24);
					this->nonDeterministic->TabIndex = 38;
					this->nonDeterministic->Text = "Non Deterministic";
					this->nonDeterministic->UseVisualStyleBackColor = true;
					this->nonDeterministic->CheckedChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// x264SlowFirstpass
					// 
					this->x264SlowFirstpass->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right)));
					this->x264SlowFirstpass->CheckAlign = System::Drawing::ContentAlignment::MiddleRight;
					this->x264SlowFirstpass->Location = new System::Drawing::Point(184, 48);
					this->x264SlowFirstpass->Name = "x264SlowFirstpass";
					this->x264SlowFirstpass->Size = new System::Drawing::Size(125, 24);
					this->x264SlowFirstpass->TabIndex = 37;
					this->x264SlowFirstpass->Text = "Slow first pass";
					this->x264SlowFirstpass->CheckedChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// threadin
					// 
					this->threadin->CheckAlign = System::Drawing::ContentAlignment::MiddleRight;
					this->threadin->Checked = true;
					this->threadin->CheckState = System::Windows::Forms::CheckState::Checked;
					this->threadin->Location = new System::Drawing::Point(184, 18);
					this->threadin->Margin = new System::Windows::Forms::Padding(0);
					this->threadin->Name = "threadin";
					this->threadin->Size = new System::Drawing::Size(125, 24);
					this->threadin->TabIndex = 13;
					this->threadin->Text = "Thread-Input";
					this->threadin->UseVisualStyleBackColor = true;
					this->threadin->CheckedChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// x264NbThreadsLabel
					// 
					this->x264NbThreadsLabel->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right)));
					this->x264NbThreadsLabel->Location = new System::Drawing::Point(12, 17);
					this->x264NbThreadsLabel->Margin = new System::Windows::Forms::Padding(3);
					this->x264NbThreadsLabel->Name = "x264NbThreadsLabel";
					this->x264NbThreadsLabel->Size = new System::Drawing::Size(125, 24);
					this->x264NbThreadsLabel->TabIndex = 11;
					this->x264NbThreadsLabel->Text = "Threads (0=Auto)";
					this->x264NbThreadsLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
					// 
					// gbAdjust
					// 
					this->gbAdjust->Controls->Add(this->btPresetSettings);
					this->gbAdjust->Controls->Add(this->dSettings);
					this->gbAdjust->Location = new System::Drawing::Point(329, 310);
					this->gbAdjust->Name = "gbAdjust";
					this->gbAdjust->Size = new System::Drawing::Size(167, 87);
					this->gbAdjust->TabIndex = 33;
					this->gbAdjust->TabStop = false;
					this->gbAdjust->Text = "Adjustments";
					// 
					// btPresetSettings
					// 
					this->btPresetSettings->Location = new System::Drawing::Point(6, 48);
					this->btPresetSettings->Name = "btPresetSettings";
					this->btPresetSettings->Size = new System::Drawing::Size(150, 23);
					this->btPresetSettings->TabIndex = 37;
					this->btPresetSettings->Text = "Preset Settings";
					this->tooltipHelp->SetToolTip(this->btPresetSettings, "Adjust x264 settings according to the preset chosen.");
					this->btPresetSettings->UseVisualStyleBackColor = true;
					this->btPresetSettings->Click += new System::EventHandler(this, &x264ConfigurationPanel::btPresetSettings_Click);
					// 
					// dSettings
					// 
					this->dSettings->Location = new System::Drawing::Point(6, 19);
					this->dSettings->Name = "dSettings";
					this->dSettings->Size = new System::Drawing::Size(150, 23);
					this->dSettings->TabIndex = 35;
					this->dSettings->Text = "Default Settings";
					this->tooltipHelp->SetToolTip(this->dSettings, "Restore x264 default Settings.");
					this->dSettings->UseVisualStyleBackColor = true;
					this->dSettings->Click += new System::EventHandler(this, &x264ConfigurationPanel::dSettings_Click);
					// 
					// gbInOut
					// 
					this->gbInOut->Controls->Add(this->stitchable);
					this->gbInOut->Controls->Add(this->sampleAR);
					this->gbInOut->Controls->Add(this->sampleARLabel);
					this->gbInOut->Controls->Add(this->ssim);
					this->gbInOut->Controls->Add(this->psnr);
					this->gbInOut->Location = new System::Drawing::Point(329, 179);
					this->gbInOut->Name = "gbInOut";
					this->gbInOut->Size = new System::Drawing::Size(167, 125);
					this->gbInOut->TabIndex = 32;
					this->gbInOut->TabStop = false;
					this->gbInOut->Text = "Input/Output";
					// 
					// stitchable
					// 
					this->stitchable->CheckAlign = System::Drawing::ContentAlignment::MiddleRight;
					this->stitchable->Location = new System::Drawing::Point(10, 64);
					this->stitchable->Name = "stitchable";
					this->stitchable->Padding = new System::Windows::Forms::Padding(3);
					this->stitchable->Size = new System::Drawing::Size(150, 23);
					this->stitchable->TabIndex = 34;
					this->stitchable->Text = "Stitch able";
					this->stitchable->CheckedChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// sampleAR
					// 
					this->sampleAR->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
					this->sampleAR->FormattingEnabled = true;
					this->sampleAR->Items->AddRange(new object[10] {"Default", "1:1", "4:3", "8:9", "10:11", "12:11", "16:11", "32:27", "40:33", "64:45"});
					this->sampleAR->Location = new System::Drawing::Point(86, 93);
					this->sampleAR->Name = "sampleAR";
					this->sampleAR->Size = new System::Drawing::Size(70, 21);
					this->sampleAR->TabIndex = 33;
					this->sampleAR->SelectedIndexChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// sampleARLabel
					// 
					this->sampleARLabel->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right)));
					this->sampleARLabel->AutoSize = true;
					this->sampleARLabel->Location = new System::Drawing::Point(14, 96);
					this->sampleARLabel->Margin = new System::Windows::Forms::Padding(3);
					this->sampleARLabel->Name = "sampleARLabel";
					this->sampleARLabel->Size = new System::Drawing::Size(59, 13);
					this->sampleARLabel->TabIndex = 32;
					this->sampleARLabel->Text = "Force SAR";
					this->sampleARLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
					// 
					// ssim
					// 
					this->ssim->CheckAlign = System::Drawing::ContentAlignment::MiddleRight;
					this->ssim->Location = new System::Drawing::Point(10, 42);
					this->ssim->Name = "ssim";
					this->ssim->Padding = new System::Windows::Forms::Padding(3);
					this->ssim->Size = new System::Drawing::Size(150, 23);
					this->ssim->TabIndex = 31;
					this->ssim->Text = "SSIM calculation";
					this->ssim->CheckedChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// psnr
					// 
					this->psnr->CheckAlign = System::Drawing::ContentAlignment::MiddleRight;
					this->psnr->Location = new System::Drawing::Point(10, 20);
					this->psnr->Name = "psnr";
					this->psnr->Padding = new System::Windows::Forms::Padding(3);
					this->psnr->Size = new System::Drawing::Size(150, 23);
					this->psnr->TabIndex = 30;
					this->psnr->Text = "PSNR calculation";
					this->psnr->CheckedChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// gbVUI
					// 
					this->gbVUI->Controls->Add(this->label18);
					this->gbVUI->Controls->Add(this->x264Range);
					this->gbVUI->Controls->Add(this->colorMatrixLabel);
					this->gbVUI->Controls->Add(this->transferLabel);
					this->gbVUI->Controls->Add(this->colorPrimLabel);
					this->gbVUI->Controls->Add(this->colorMatrix);
					this->gbVUI->Controls->Add(this->transfer);
					this->gbVUI->Controls->Add(this->colorPrim);
					this->gbVUI->Controls->Add(this->picStruct);
					this->gbVUI->Location = new System::Drawing::Point(6, 179);
					this->gbVUI->Name = "gbVUI";
					this->gbVUI->Size = new System::Drawing::Size(317, 106);
					this->gbVUI->TabIndex = 31;
					this->gbVUI->TabStop = false;
					this->gbVUI->Text = "V.U.I";
					// 
					// label18
					// 
					this->label18->AutoSize = true;
					this->label18->Location = new System::Drawing::Point(12, 24);
					this->label18->Name = "label18";
					this->label18->Size = new System::Drawing::Size(39, 13);
					this->label18->TabIndex = 46;
					this->label18->Text = "Range";
					// 
					// x264Range
					// 
					this->x264Range->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
					this->x264Range->FormattingEnabled = true;
					this->x264Range->Items->AddRange(new object[3] {"auto", "tv", "pc"});
					this->x264Range->Location = new System::Drawing::Point(63, 20);
					this->x264Range->Name = "x264Range";
					this->x264Range->Size = new System::Drawing::Size(74, 21);
					this->x264Range->TabIndex = 45;
					this->x264Range->SelectedIndexChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// colorMatrixLabel
					// 
					this->colorMatrixLabel->AutoSize = true;
					this->colorMatrixLabel->Location = new System::Drawing::Point(153, 78);
					this->colorMatrixLabel->Name = "colorMatrixLabel";
					this->colorMatrixLabel->Size = new System::Drawing::Size(62, 13);
					this->colorMatrixLabel->TabIndex = 44;
					this->colorMatrixLabel->Text = "Color Matrix";
					// 
					// transferLabel
					// 
					this->transferLabel->AutoSize = true;
					this->transferLabel->Location = new System::Drawing::Point(153, 51);
					this->transferLabel->Name = "transferLabel";
					this->transferLabel->Size = new System::Drawing::Size(46, 13);
					this->transferLabel->TabIndex = 43;
					this->transferLabel->Text = "Transfer";
					// 
					// colorPrimLabel
					// 
					this->colorPrimLabel->AutoSize = true;
					this->colorPrimLabel->Location = new System::Drawing::Point(153, 24);
					this->colorPrimLabel->Name = "colorPrimLabel";
					this->colorPrimLabel->Size = new System::Drawing::Size(76, 13);
					this->colorPrimLabel->TabIndex = 42;
					this->colorPrimLabel->Text = "Color Primaries";
					// 
					// colorMatrix
					// 
					this->colorMatrix->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
					this->colorMatrix->FormattingEnabled = true;
					this->colorMatrix->Items->AddRange(new object[8] {"undefined", "bt709", "fcc", "bt470bg", "smpte170m", "smpte240m", "GBR", "YCgCo"});
					this->colorMatrix->Location = new System::Drawing::Point(235, 75);
					this->colorMatrix->Name = "colorMatrix";
					this->colorMatrix->Size = new System::Drawing::Size(74, 21);
					this->colorMatrix->TabIndex = 41;
					this->colorMatrix->SelectedIndexChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// transfer
					// 
					this->transfer->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
					this->transfer->FormattingEnabled = true;
					this->transfer->Items->AddRange(new object[9] {"undefined", "bt709", "bt470m", "bt470bg", "linear", "log100", "log316", "smpte170m", "smpte240m"});
					this->transfer->Location = new System::Drawing::Point(235, 48);
					this->transfer->Name = "transfer";
					this->transfer->Size = new System::Drawing::Size(74, 21);
					this->transfer->TabIndex = 40;
					this->transfer->SelectedIndexChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// colorPrim
					// 
					this->colorPrim->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
					this->colorPrim->FormattingEnabled = true;
					this->colorPrim->Items->AddRange(new object[7] {"undefined", "bt709", "bt470m", "bt470bg", "smpte170m", "smpte240m", "film"});
					this->colorPrim->Location = new System::Drawing::Point(235, 21);
					this->colorPrim->Name = "colorPrim";
					this->colorPrim->Size = new System::Drawing::Size(74, 21);
					this->colorPrim->TabIndex = 39;
					this->colorPrim->SelectedIndexChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// picStruct
					// 
					this->picStruct->CheckAlign = System::Drawing::ContentAlignment::MiddleRight;
					this->picStruct->Location = new System::Drawing::Point(12, 45);
					this->picStruct->Name = "picStruct";
					this->picStruct->Size = new System::Drawing::Size(125, 24);
					this->picStruct->TabIndex = 28;
					this->picStruct->Text = "Force pic_struct";
					this->picStruct->UseVisualStyleBackColor = true;
					this->picStruct->CheckedChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// gbQPFile
					// 
					this->gbQPFile->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right)));
					this->gbQPFile->Controls->Add(this->logfile);
					this->gbQPFile->Controls->Add(this->logfileLabel);
					this->gbQPFile->Controls->Add(this->logfileOpenButton);
					this->gbQPFile->Controls->Add(this->qpfileOpenButton);
					this->gbQPFile->Controls->Add(this->qpfile);
					this->gbQPFile->Controls->Add(this->useQPFile);
					this->gbQPFile->Location = new System::Drawing::Point(6, 77);
					this->gbQPFile->Name = "gbQPFile";
					this->gbQPFile->Size = new System::Drawing::Size(490, 96);
					this->gbQPFile->TabIndex = 30;
					this->gbQPFile->TabStop = false;
					this->gbQPFile->Text = " Files ";
					// 
					// logfile
					// 
					this->logfile->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
					this->logfile->Location = new System::Drawing::Point(113, 21);
					this->logfile->Name = "logfile";
					this->logfile->ReadOnly = true;
					this->logfile->Size = new System::Drawing::Size(323, 20);
					this->logfile->TabIndex = 29;
					this->logfile->Text = "2pass.stats";
					// 
					// logfileLabel
					// 
					this->logfileLabel->Location = new System::Drawing::Point(12, 18);
					this->logfileLabel->Margin = new System::Windows::Forms::Padding(3);
					this->logfileLabel->Name = "logfileLabel";
					this->logfileLabel->Size = new System::Drawing::Size(75, 23);
					this->logfileLabel->TabIndex = 28;
					this->logfileLabel->Text = "Logfile:";
					this->logfileLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
					// 
					// logfileOpenButton
					// 
					this->logfileOpenButton->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right)));
					this->logfileOpenButton->Location = new System::Drawing::Point(453, 19);
					this->logfileOpenButton->Name = "logfileOpenButton";
					this->logfileOpenButton->Size = new System::Drawing::Size(26, 23);
					this->logfileOpenButton->TabIndex = 30;
					this->logfileOpenButton->Text = "...";
					this->logfileOpenButton->Click += new System::EventHandler(this, &x264ConfigurationPanel::logfileOpenButton_Click);
					// 
					// qpfileOpenButton
					// 
					this->qpfileOpenButton->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right)));
					this->qpfileOpenButton->Enabled = false;
					this->qpfileOpenButton->Location = new System::Drawing::Point(453, 56);
					this->qpfileOpenButton->Name = "qpfileOpenButton";
					this->qpfileOpenButton->Size = new System::Drawing::Size(26, 23);
					this->qpfileOpenButton->TabIndex = 27;
					this->qpfileOpenButton->Text = "...";
					this->qpfileOpenButton->Click += new System::EventHandler(this, &x264ConfigurationPanel::qpfileOpenButton_Click);
					// 
					// qpfile
					// 
					this->qpfile->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
					this->qpfile->Enabled = false;
					this->qpfile->Location = new System::Drawing::Point(113, 59);
					this->qpfile->Name = "qpfile";
					this->qpfile->ReadOnly = true;
					this->qpfile->Size = new System::Drawing::Size(323, 20);
					this->qpfile->TabIndex = 26;
					this->qpfile->Text = ".qpf";
					// 
					// useQPFile
					// 
					this->useQPFile->CheckAlign = System::Drawing::ContentAlignment::MiddleRight;
					this->useQPFile->Location = new System::Drawing::Point(15, 60);
					this->useQPFile->Name = "useQPFile";
					this->useQPFile->Size = new System::Drawing::Size(79, 17);
					this->useQPFile->TabIndex = 24;
					this->useQPFile->Text = "Use qp File";
					this->useQPFile->UseVisualStyleBackColor = true;
					this->useQPFile->CheckedChanged += new System::EventHandler(this, &x264ConfigurationPanel::useQPFile_CheckedChanged);
					// 
					// gbx264CustomCmd
					// 
					this->gbx264CustomCmd->Controls->Add(this->customCommandlineOptions);
					this->gbx264CustomCmd->Location = new System::Drawing::Point(6, 6);
					this->gbx264CustomCmd->Name = "gbx264CustomCmd";
					this->gbx264CustomCmd->Size = new System::Drawing::Size(490, 65);
					this->gbx264CustomCmd->TabIndex = 27;
					this->gbx264CustomCmd->TabStop = false;
					this->gbx264CustomCmd->Text = " Custom Command Line ";
					// 
					// customCommandlineOptions
					// 
					this->customCommandlineOptions->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
					this->customCommandlineOptions->Location = new System::Drawing::Point(15, 19);
					this->customCommandlineOptions->Multiline = true;
					this->customCommandlineOptions->Name = "customCommandlineOptions";
					this->customCommandlineOptions->Size = new System::Drawing::Size(464, 34);
					this->customCommandlineOptions->TabIndex = 0;
					this->customCommandlineOptions->TextChanged += new System::EventHandler(this, &x264ConfigurationPanel::updateEvent);
					// 
					// avcLevel
					// 
					this->avcLevel->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
					this->avcLevel->Location = new System::Drawing::Point(10, 16);
					this->avcLevel->Name = "avcLevel";
					this->avcLevel->Size = new System::Drawing::Size(157, 21);
					this->avcLevel->TabIndex = 0;
					this->avcLevel->SelectedIndexChanged += new System::EventHandler(this, &x264ConfigurationPanel::avcLevel_SelectedIndexChanged);
					// 
					// avcProfileGroupbox
					// 
					this->avcProfileGroupbox->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right)));
					this->avcProfileGroupbox->Controls->Add(this->avcProfile);
					this->avcProfileGroupbox->Enabled = false;
					this->avcProfileGroupbox->Location = new System::Drawing::Point(322, 152);
					this->avcProfileGroupbox->Name = "avcProfileGroupbox";
					this->avcProfileGroupbox->Size = new System::Drawing::Size(172, 48);
					this->avcProfileGroupbox->TabIndex = 38;
					this->avcProfileGroupbox->TabStop = false;
					this->avcProfileGroupbox->Text = " AVC Profile ";
					// 
					// avcProfile
					// 
					this->avcProfile->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
					this->avcProfile->Items->AddRange(new object[3] {"Baseline Profile", "Main Profile", "High Profile"});
					this->avcProfile->Location = new System::Drawing::Point(10, 16);
					this->avcProfile->Name = "avcProfile";
					this->avcProfile->Size = new System::Drawing::Size(157, 21);
					this->avcProfile->TabIndex = 0;
					this->avcProfile->SelectedIndexChanged += new System::EventHandler(this, &x264ConfigurationPanel::avcProfile_SelectedIndexChanged);
					// 
					// avcLevelGroupbox
					// 
					this->avcLevelGroupbox->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right)));
					this->avcLevelGroupbox->Controls->Add(this->avcLevel);
					this->avcLevelGroupbox->Enabled = false;
					this->avcLevelGroupbox->Location = new System::Drawing::Point(322, 206);
					this->avcLevelGroupbox->Name = "avcLevelGroupbox";
					this->avcLevelGroupbox->Size = new System::Drawing::Size(172, 48);
					this->avcLevelGroupbox->TabIndex = 37;
					this->avcLevelGroupbox->TabStop = false;
					this->avcLevelGroupbox->Text = " AVC Level ";
					// 
					// deviceGroupbox
					// 
					this->deviceGroupbox->Controls->Add(this->targetDevice);
					this->deviceGroupbox->Location = new System::Drawing::Point(6, 260);
					this->deviceGroupbox->Name = "deviceGroupbox";
					this->deviceGroupbox->Size = new System::Drawing::Size(488, 48);
					this->deviceGroupbox->TabIndex = 39;
					this->deviceGroupbox->TabStop = false;
					this->deviceGroupbox->Text = " Target Playback Device ";
					// 
					// targetDevice
					// 
					this->targetDevice->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
					this->targetDevice->Location = new System::Drawing::Point(10, 19);
					this->targetDevice->Name = "targetDevice";
					this->targetDevice->Size = new System::Drawing::Size(473, 21);
					this->targetDevice->TabIndex = 1;
					this->targetDevice->SelectedIndexChanged += new System::EventHandler(this, &x264ConfigurationPanel::targetDevice_SelectedIndexChanged);
					// 
					// ch10BitsEncoder
					// 
					this->ch10BitsEncoder->AutoSize = true;
					this->ch10BitsEncoder->Location = new System::Drawing::Point(21, 341);
					this->ch10BitsEncoder->Name = "ch10BitsEncoder";
					this->ch10BitsEncoder->Size = new System::Drawing::Size(142, 17);
					this->ch10BitsEncoder->TabIndex = 40;
					this->ch10BitsEncoder->Text = "Enable 10-Bits Encoding";
					this->ch10BitsEncoder->UseVisualStyleBackColor = true;
					this->ch10BitsEncoder->CheckedChanged += new System::EventHandler(this, &x264ConfigurationPanel::ch10BitsEncoder_CheckedChanged);
					// 
					// x264ConfigurationPanel
					// 
					this->AutoScaleDimensions = new System::Drawing::SizeF(6, 13);
					this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
					this->Name = "x264ConfigurationPanel";
					this->Size = new System::Drawing::Size(510, 523);
					this->tabControl1->ResumeLayout(false);
					this->mainTabPage->ResumeLayout(false);
					this->mainTabPage->PerformLayout();
					this->x264CodecGeneralGroupbox->ResumeLayout(false);
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->x264BitrateQuantizer))->EndInit();
					this->FrameTypeTabPage->ResumeLayout(false);
					this->gbSlicing->ResumeLayout(false);
					this->gbSlicing->PerformLayout();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->maxSliceSizeMB))->EndInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->maxSliceSizeBytes))->EndInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->slicesnb))->EndInit();
					this->gbFTOther->ResumeLayout(false);
					this->gbFTOther->PerformLayout();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->x264NumberOfRefFrames))->EndInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->x264SCDSensitivity))->EndInit();
					this->x264GeneralBFramesgGroupbox->ResumeLayout(false);
					this->x264GeneralBFramesgGroupbox->PerformLayout();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->x264BframeBias))->EndInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->x264NumberOfBFrames))->EndInit();
					this->gbH264Features->ResumeLayout(false);
					this->gbH264Features->PerformLayout();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->x264BetaDeblock))->EndInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->x264AlphaDeblock))->EndInit();
					this->gbGOPSize->ResumeLayout(false);
					this->gbGOPSize->PerformLayout();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->x264KeyframeInterval))->EndInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->x264MinGOPSize))->EndInit();
					this->RCTabPage->ResumeLayout(false);
					this->x264RCGroupbox->ResumeLayout(false);
					this->x264RCGroupbox->PerformLayout();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->lookahead))->EndInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->x264VBVInitialBuffer))->EndInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->x264VBVMaxRate))->EndInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->x264TempQuantBlur))->EndInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->x264TempFrameComplexityBlur))->EndInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->x264QuantizerCompression))->EndInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->x264VBVBufferSize))->EndInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->x264RateTol))->EndInit();
					this->gbAQ->ResumeLayout(false);
					this->gbAQ->PerformLayout();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->numAQStrength))->EndInit();
					this->quantizerMatrixGroupbox->ResumeLayout(false);
					this->x264QuantizerGroupBox->ResumeLayout(false);
					this->x264QuantizerGroupBox->PerformLayout();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->deadzoneIntra))->EndInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->deadzoneInter))->EndInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->x264PBFrameFactor))->EndInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->x264IPFrameFactor))->EndInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->x264CreditsQuantizer))->EndInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->x264ChromaQPOffset))->EndInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->x264MaxQuantDelta))->EndInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->x264MaximumQuantizer))->EndInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->x264MinimimQuantizer))->EndInit();
					this->gbPresets->ResumeLayout(false);
					this->gbPresets->PerformLayout();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->tbx264Presets))->EndInit();
					this->gbTunes->ResumeLayout(false);
					this->AnalysisTabPage->ResumeLayout(false);
					this->x264Bluray->ResumeLayout(false);
					this->x264Bluray->PerformLayout();
					this->x264QuantOptionsGroupbox->ResumeLayout(false);
					this->x264QuantOptionsGroupbox->PerformLayout();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->NoiseReduction))->EndInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->PsyTrellis))->EndInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->PsyRD))->EndInit();
					this->x264MBGroupbox->ResumeLayout(false);
					this->x264MBGroupbox->PerformLayout();
					this->x264OtherOptionsGroupbox->ResumeLayout(false);
					this->x264OtherOptionsGroupbox->PerformLayout();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->x264MERange))->EndInit();
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->pictureBox1))->EndInit();
					this->MiscTabPage->ResumeLayout(false);
					this->gbOther->ResumeLayout(false);
					(static_cast<System::ComponentModel::ISupportInitialize*>(this->x264NbThreads))->EndInit();
					this->gbAdjust->ResumeLayout(false);
					this->gbInOut->ResumeLayout(false);
					this->gbInOut->PerformLayout();
					this->gbVUI->ResumeLayout(false);
					this->gbVUI->PerformLayout();
					this->gbQPFile->ResumeLayout(false);
					this->gbQPFile->PerformLayout();
					this->gbx264CustomCmd->ResumeLayout(false);
					this->gbx264CustomCmd->PerformLayout();
					this->avcProfileGroupbox->ResumeLayout(false);
					this->avcLevelGroupbox->ResumeLayout(false);
					this->deviceGroupbox->ResumeLayout(false);
					this->ResumeLayout(false);
					this->PerformLayout();

				}

				void x264ConfigurationPanel::InitializeInstanceFields()
				{
					ContextHelp = new XmlDocument();
					x264DeviceList = std::vector<x264Device*>();
					delete components;
				}
			}
		}
	}
}
