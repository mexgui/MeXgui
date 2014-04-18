#include "x264SettingsHandler.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
using namespace MeGUI::core::util;
namespace MeGUI
{
	namespace packages
	{
		namespace video
		{
			namespace x264
			{

				x264SettingsHandler::x264SettingsHandler(x264Settings *xs, LogItem *log)
				{
					_xs = xs;
					_log = log;
					_device = _xs->getTargetDevice();
				}

				void x264SettingsHandler::CheckInputFile(Nullable<Dar> d, int hres, int vres, int fps_n, int fps_d)
				{
					if (_log == 0)
						return;

					if (_device->getBluRay() == true)
					{
						if ((hres == 1920 || hres == 1440) && vres == 1080)
						{
							std::string fps = fps_n + "/" + fps_d;
							double dfps = double::Parse(StringConverterHelper::toString(fps_n)) / fps_d;
							if (fps.Equals("24000/1001") || dfps == 24)
							{
								if (_xs->getInterlacedMode() != x264Settings::progressive)
								{
									_xs->setInterlacedMode(x264Settings::progressive);
									_log->LogEvent("the selected device does not support interlaced encoding of " + fps_n + "/" + fps_d + " fps. changing interlaced mode to progressive.", Warning);
								}
								_xs->setPicStruct(false);
										_xs->setFakeInterlaced(_xs->getPicStruct());
							}
							else if (dfps == 25 || fps.Equals("30000/1001"))
							{
								if (_xs->getInterlacedMode() == x264Settings::progressive)
									_xs->setPicStruct(true);
											_xs->setFakeInterlaced(_xs->getPicStruct());
								else
									_xs->setPicStruct(false);
											_xs->setFakeInterlaced(_xs->getPicStruct());
							}
							else if (dfps == 30)
							{
								_xs->setPicStruct(false);
										_xs->setFakeInterlaced(_xs->getPicStruct());
								if (_xs->getInterlacedMode() == x264Settings::progressive)
								{
									_xs->setInterlacedMode(x264Settings::tff);
									_log->LogEvent("the selected device does not support progressive encoding of " + fps_n + "/" + fps_d + " fps. changing interlaced mode to tff.", Warning);
								}
							}
							else
								_log->LogEvent("the selected device does not support " + fps_n + "/" + fps_d + " fps with a resolution of " + hres + "x" + vres + ". Supported are 24000/1001, 24/1, 25/1, 30000/1001 and 30/1.", Warning);

							_xs->setColorMatrix(1);
									_xs->setTransfer(_xs->getColorMatrix());
											_xs->setColorPrim(_xs->getTransfer());
							if (hres == 1440)
								_xs->setSampleAR(2);
							else
								_xs->setSampleAR(1);
							_xs->setX264PullDown(0);
						}
						else if (hres == 1280 && vres == 720)
						{
							if (_xs->getInterlacedMode() != x264Settings::progressive)
							{
								_xs->setInterlacedMode(x264Settings::progressive);
								_log->LogEvent("the selected device does not support interlaced encoding of " + hres + "x" + vres + ". changing interlaced mode to progressive.", Warning);
							}
							_xs->setPicStruct(false);
									_xs->setFakeInterlaced(_xs->getPicStruct());
							_xs->setX264PullDown(0);

							std::string fps = fps_n + "/" + fps_d;
							double dfps = double::Parse(StringConverterHelper::toString(fps_n)) / fps_d;
							if (dfps == 25 || fps.Equals("30000/1001"))
							{
								if (_xs->getX264PullDown() != 4)
								{
									_xs->setX264PullDown(4);
									_log->LogEvent("changing --pulldown to double as it is required for encoding of " + hres + "x" + vres + " with " + fps_n + "/" + fps_d + " fps for the selected device.", Information);
								}
							}
							else if (!fps.Equals("24000/1001") && dfps != 24 && dfps != 50 && !fps.Equals("60000/1001"))
								_log->LogEvent("the selected device does not support " + fps_n + "/" + fps_d + " fps with a resolution of " + hres + "x" + vres + ". Supported are 24000/1001, 24/1, 25/1, 30000/1001, 50/1 and 60000/1001.", Warning);

							_xs->setColorMatrix(1);
									_xs->setTransfer(_xs->getColorMatrix());
											_xs->setColorPrim(_xs->getTransfer());
							_xs->setSampleAR(1);
						}
						else if (hres == 720 && vres == 576)
						{
							double dfps = double::Parse(StringConverterHelper::toString(fps_n)) / fps_d;
							if (dfps == 25)
							{
								if (_xs->getInterlacedMode() == x264Settings::progressive)
									_xs->setPicStruct(true);
											_xs->setFakeInterlaced(_xs->getPicStruct());
								else
									_xs->setPicStruct(false);
											_xs->setFakeInterlaced(_xs->getPicStruct());

								if (_xs->getSampleAR() != 5 && _xs->getSampleAR() != 6)
								{
									if (!d.HasValue)
									{
										_xs->setSampleAR(5);
										_log->LogEvent("assume --sar 12:11 as only 16:11 or 12:11 are supported with a resolution of " + hres + "x" + vres + ". for the selected device", Warning);
									}
									else
									{
										Sar s = d.Value::ToSar(hres, vres);
										_log->LogEvent("detected --sar " + s.getX() + ":" + s.getY(), Information);
										double dDiff16 = 16.0 / 11 - double::Parse(StringConverterHelper::toString(s.getX())) / s.getY();
										double dDiff4 = 12.0 / 11 - double::Parse(StringConverterHelper::toString(s.getX())) / s.getY();
										if (dDiff16 <= 0)
										{
											_xs->setSampleAR(6);
											_log->LogEvent("assume --sar 16:11 as only 16:11 or 12:11 are supported with a resolution of " + hres + "x" + vres + " for the selected device.", Warning);
										}
										else if (dDiff4 >= 0)
										{
											_xs->setSampleAR(5);
											_log->LogEvent("assume --sar 12:11 as only 16:11 or 12:11 are supported with a resolution of " + hres + "x" + vres + " for the selected device.", Warning);
										}
										else if (__min(dDiff16, -dDiff4) == dDiff16)
										{
											_xs->setSampleAR(6);
											_log->LogEvent("assume --sar 16:11 as only 16:11 or 12:11 are supported with a resolution of " + hres + "x" + vres + " for the selected device.", Warning);
										}
										else
										{
											_xs->setSampleAR(5);
											_log->LogEvent("assume --sar 12:11 as only 16:11 or 12:11 are supported with a resolution of " + hres + "x" + vres + " for the selected device.", Warning);
										}
									}
								}
							}
							else
								_log->LogEvent("the selected device does not support " + fps_n + "/" + fps_d + " fps with a resolution of " + hres + "x" + vres + ". Supported is 25/1.", Warning);
							_xs->setColorMatrix(3);
									_xs->setTransfer(_xs->getColorMatrix());
											_xs->setColorPrim(_xs->getTransfer());
							_xs->setX264PullDown(0);
						}
						else if (hres == 720 && vres == 480)
						{
							if (_xs->getSampleAR() != 8 && _xs->getSampleAR() != 4)
							{
								_xs->setSampleAR(8);
								_log->LogEvent("assume --sar 40:33 as only 40:33 or 10:11 are supported with a resolution of " + hres + "x" + vres + " for the selected device.", Warning);
							}

							if (_xs->getSampleAR() != 8 && _xs->getSampleAR() != 4)
							{
								if (!d.HasValue)
								{
									_xs->setSampleAR(4);
									_log->LogEvent("assume --sar 10:11 as only 40:33 or 10:11 are supported with a resolution of " + hres + "x" + vres + " for the selected device.", Warning);
								}
								else
								{
									Sar s = d.Value::ToSar(hres, vres);
									_log->LogEvent("detected --sar " + s.getX() + ":" + s.getY(), Information);
									double dDiff16 = 16.0 / 11 - double::Parse(StringConverterHelper::toString(s.getX())) / s.getY();
									double dDiff4 = 12.0 / 11 - double::Parse(StringConverterHelper::toString(s.getX())) / s.getY();
									if (dDiff16 <= 0)
									{
										_xs->setSampleAR(8);
										_log->LogEvent("assume --sar 40:33 as only 40:33 or 10:11 are supported with a resolution of " + hres + "x" + vres + " for the selected device.", Warning);
									}
									else if (dDiff4 >= 0)
									{
										_xs->setSampleAR(4);
										_log->LogEvent("assume --sar 10:11 as only 40:33 or 10:11 are supported with a resolution of " + hres + "x" + vres + " for the selected device.", Warning);
									}
									else if (__min(dDiff16, -dDiff4) == dDiff16)
									{
										_xs->setSampleAR(8);
										_log->LogEvent("assume --sar 40:33 as only 40:33 or 10:11 are supported with a resolution of " + hres + "x" + vres + " for the selected device.", Warning);
									}
									else
									{
										_xs->setSampleAR(4);
										_log->LogEvent("assume --sar 10:11 as only 40:33 or 10:11 are supported with a resolution of " + hres + "x" + vres + " for the selected device.", Warning);
									}
								}
							}

							std::string fps = fps_n + "/" + fps_d;
							if (fps.Equals("30000/1001"))
							{
								_xs->setX264PullDown(0);
								_xs->setPicStruct(false);
										_xs->setFakeInterlaced(_xs->getPicStruct());
								if (_xs->getInterlacedMode() == x264Settings::progressive)
								{
									_xs->setInterlacedMode(x264Settings::tff);
									_log->LogEvent("the selected device does not support progressive encoding of " + fps_n + "/" + fps_d + " fps. changing interlaced mode to tff.", Warning);
								}
							}
							else if (fps.Equals("24000/1001"))
							{
								if (_xs->getX264PullDown() != 2)
								{
									_xs->setX264PullDown(2);
									_log->LogEvent("changing --pulldown to 32 as it is required for encoding of " + hres + "x" + vres + " with " + fps_n + "/" + fps_d + " fps for the selected device.", Warning);
								}
								if (_xs->getInterlacedMode() != x264Settings::progressive)
								{
									_xs->setInterlacedMode(x264Settings::progressive);
									_log->LogEvent("the selected device does not support interlaced encoding of " + hres + "x" + vres + ". changing interlaced mode to progressive.", Warning);
								}
							}
							else
								_log->LogEvent("the selected device does not support " + fps_n + "/" + fps_d + " fps with a resolution of " + hres + "x" + vres + ". Supported are 30000/1001 and 24000/1001.", Warning);
							_xs->setColorMatrix(4);
									_xs->setColorPrim(_xs->getColorMatrix());
							_xs->setTransfer(7);
						}
						else
						{
							_log->LogEvent("the selected device does not support a resolution of " + hres + "x" + vres + ". Supported are 1920x1080, 1440x1080, 1280x720, 720x576 and 720x480.", Warning);
						}
					}
					else
					{
						if (_device->getWidth() > 0 && hres > _device->getWidth())
							_log->LogEvent("the selected device does not support a resolution width of " + hres + ". The maximum value is " + _device->getWidth(), Warning);
						if (_device->getHeight() > 0 && vres > _device->getHeight())
							_log->LogEvent("the selected device does not support a resolution height of " + vres + ". The maximum value is " + _device->getHeight(), Warning);
					}
				}

				int x264SettingsHandler::getVBVBufsize(AVCLevels::Levels avcLevel, bool bIsHighProfile)
				{
					std::string strCustomValue;
					int iTemp = _xs->getVBVBufferSize();
					extractCustomCommand("vbv-bufsize", strCustomValue);
					if (int::TryParse(strCustomValue, iTemp))
						_xs->setVBVBufferSize(iTemp);

					if (_device->getVBVBufsize() > -1 && (_xs->getVBVBufferSize() > _device->getVBVBufsize() || _xs->getVBVBufferSize() == 0))
					{
						if (_log != 0)
							_log->LogEvent("changing --vbv-bufsize to " + _device->getVBVBufsize() + " as required for the selected device");
						_xs->setVBVBufferSize(_device->getVBVBufsize());
					}

					if (_log != 0 && avcLevel != AVCLevels::L_UNRESTRICTED)
					{
						AVCLevels *al = new AVCLevels();
						iTemp = al->getMaxCBP(avcLevel, bIsHighProfile);
						if (_xs->getVBVBufferSize() == 0)
							_log->LogEvent("--vbv-bufsize is not restricted. Maximum value for level " + AVCLevels::GetLevelText(avcLevel) + " is " + iTemp + ". Playback may be affected. Reselect AVC level/profile or target playback device in the x264 preset to set the proper value.", Warning);
					}

					return _xs->getVBVBufferSize();
				}

				int x264SettingsHandler::getVBVMaxrate(AVCLevels::Levels avcLevel, bool bIsHighProfile)
				{
					std::string strCustomValue;
					int iTemp = _xs->getVBVMaxBitrate();
					extractCustomCommand("vbv-maxrate", strCustomValue);
					if (int::TryParse(strCustomValue, iTemp))
						_xs->setVBVMaxBitrate(iTemp);

					if (_device->getVBVMaxrate() > -1 && (_xs->getVBVMaxBitrate() > _device->getVBVMaxrate() || _xs->getVBVMaxBitrate() == 0))
					{
						if (_log != 0)
							_log->LogEvent("changing --vbv-maxrate to " + _device->getVBVMaxrate() + " as required for the selected device");
						_xs->setVBVMaxBitrate(_device->getVBVMaxrate());
					}

					if (_log != 0 && avcLevel != AVCLevels::L_UNRESTRICTED)
					{
						AVCLevels *al = new AVCLevels();
						iTemp = al->getMaxBR(avcLevel, bIsHighProfile);
						if (_xs->getVBVMaxBitrate() == 0)
							_log->LogEvent("--vbv-maxrate is not restricted. Maximum value for level " + AVCLevels::GetLevelText(avcLevel) + " is " + iTemp + ". Playback may be affected. Reselect AVC level/profile or target playback device in the x264 preset to set the proper value.", Warning);
					}

					return _xs->getVBVMaxBitrate();
				}

				int x264SettingsHandler::getSar(Nullable<Dar> d, int hRes, int vRes, std::string &CustomSarValue, const std::string &CustomSarValueInput)
				{
					std::string strCustomValue;
					CustomSarValue = "";
					if (CustomSarValueInput.empty() && extractCustomCommand("sar", strCustomValue))
					{
//C# TO C++ CONVERTER NOTE: The following 'switch' operated on a string variable and was converted to C++ 'if-else' logic:
//						switch (strCustomValue.ToLower(System.Globalization.CultureInfo.InvariantCulture))
//ORIGINAL LINE: case "1:1":
						if (strCustomValue.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "1:1")
						{
								_xs->setSampleAR(1);
						}
//ORIGINAL LINE: case "4:3":
						else if (strCustomValue.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "4:3")
						{
								_xs->setSampleAR(2);
						}
//ORIGINAL LINE: case "8:9":
						else if (strCustomValue.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "8:9")
						{
								_xs->setSampleAR(3);
						}
//ORIGINAL LINE: case "10:11":
						else if (strCustomValue.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "10:11")
						{
								_xs->setSampleAR(4);
						}
//ORIGINAL LINE: case "12:11":
						else if (strCustomValue.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "12:11")
						{
								_xs->setSampleAR(5);
						}
//ORIGINAL LINE: case "16:11":
						else if (strCustomValue.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "16:11")
						{
								_xs->setSampleAR(6);
						}
//ORIGINAL LINE: case "32:27":
						else if (strCustomValue.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "32:27")
						{
								_xs->setSampleAR(7);
						}
//ORIGINAL LINE: case "40:33":
						else if (strCustomValue.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "40:33")
						{
								_xs->setSampleAR(8);
						}
//ORIGINAL LINE: case "64:45":
						else if (strCustomValue.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "64:45")
						{
								_xs->setSampleAR(9);
						}
						else
						{
								CustomSarValue = strCustomValue;
								_xs->setSampleAR(0);
						}
					}

					if (d.HasValue && _xs->getSampleAR() == 0 && CustomSarValue.empty() && CustomSarValueInput.empty())
					{
						Sar s = d.Value::ToSar(hRes, vRes);
//C# TO C++ CONVERTER NOTE: The following 'switch' operated on a string variable and was converted to C++ 'if-else' logic:
//						switch (s.X + ":" + s.Y)
//ORIGINAL LINE: case "1:1":
						if (s.getX() + ":" + s.getY() == "1:1")
						{
								_xs->setSampleAR(1);
						}
//ORIGINAL LINE: case "4:3":
						else if (s.getX() + ":" + s.getY() == "4:3")
						{
								_xs->setSampleAR(2);
						}
//ORIGINAL LINE: case "8:9":
						else if (s.getX() + ":" + s.getY() == "8:9")
						{
								_xs->setSampleAR(3);
						}
//ORIGINAL LINE: case "10:11":
						else if (s.getX() + ":" + s.getY() == "10:11")
						{
								_xs->setSampleAR(4);
						}
//ORIGINAL LINE: case "12:11":
						else if (s.getX() + ":" + s.getY() == "12:11")
						{
								_xs->setSampleAR(5);
						}
//ORIGINAL LINE: case "16:11":
						else if (s.getX() + ":" + s.getY() == "16:11")
						{
								_xs->setSampleAR(6);
						}
//ORIGINAL LINE: case "32:27":
						else if (s.getX() + ":" + s.getY() == "32:27")
						{
								_xs->setSampleAR(7);
						}
//ORIGINAL LINE: case "40:33":
						else if (s.getX() + ":" + s.getY() == "40:33")
						{
								_xs->setSampleAR(8);
						}
//ORIGINAL LINE: case "64:45":
						else if (s.getX() + ":" + s.getY() == "64:45")
						{
								_xs->setSampleAR(9);
						}
						else
						{
								CustomSarValue = s.getX() + ":" + s.getY();
						}
					}

					return _xs->getSampleAR();
				}

				int x264SettingsHandler::getColorprim()
				{
					std::string strCustomValue;
					if (extractCustomCommand("colorprim", strCustomValue))
					{
//C# TO C++ CONVERTER NOTE: The following 'switch' operated on a string variable and was converted to C++ 'if-else' logic:
//						switch (strCustomValue.ToLower(System.Globalization.CultureInfo.InvariantCulture))
//ORIGINAL LINE: case "bt709":
						if (strCustomValue.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "bt709")
						{
								_xs->setColorPrim(1);
						}
//ORIGINAL LINE: case "bt470m":
						else if (strCustomValue.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "bt470m")
						{
								_xs->setColorPrim(2);
						}
//ORIGINAL LINE: case "bt470bg":
						else if (strCustomValue.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "bt470bg")
						{
								_xs->setColorPrim(3);
						}
//ORIGINAL LINE: case "smpte170m":
						else if (strCustomValue.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "smpte170m")
						{
								_xs->setColorPrim(4);
						}
//ORIGINAL LINE: case "smpte240m":
						else if (strCustomValue.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "smpte240m")
						{
								_xs->setColorPrim(5);
						}
//ORIGINAL LINE: case "film":
						else if (strCustomValue.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "film")
						{
								_xs->setColorPrim(6);
						}
					}
					return _xs->getColorPrim();
				}

				int x264SettingsHandler::getPulldown()
				{
					std::string strCustomValue;
					if (extractCustomCommand("pulldown", strCustomValue))
					{
//C# TO C++ CONVERTER NOTE: The following 'switch' operated on a string variable and was converted to C++ 'if-else' logic:
//						switch (strCustomValue.ToLower(System.Globalization.CultureInfo.InvariantCulture))
//ORIGINAL LINE: case "none":
						if (strCustomValue.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "none")
						{
								_xs->setX264PullDown(0);
						}
//ORIGINAL LINE: case "22":
						else if (strCustomValue.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "22")
						{
								_xs->setX264PullDown(1);
						}
//ORIGINAL LINE: case "32":
						else if (strCustomValue.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "32")
						{
								_xs->setX264PullDown(2);
						}
//ORIGINAL LINE: case "64":
						else if (strCustomValue.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "64")
						{
								_xs->setX264PullDown(3);
						}
//ORIGINAL LINE: case "double":
						else if (strCustomValue.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "double")
						{
								_xs->setX264PullDown(4);
						}
//ORIGINAL LINE: case "triple":
						else if (strCustomValue.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "triple")
						{
								_xs->setX264PullDown(5);
						}
//ORIGINAL LINE: case "euro":
						else if (strCustomValue.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "euro")
						{
								_xs->setX264PullDown(6);
						}
					}
					return _xs->getX264PullDown();
				}

				int x264SettingsHandler::getTransfer()
				{
					std::string strCustomValue;
					if (extractCustomCommand("transfer", strCustomValue))
					{
//C# TO C++ CONVERTER NOTE: The following 'switch' operated on a string variable and was converted to C++ 'if-else' logic:
//						switch (strCustomValue.ToLower(System.Globalization.CultureInfo.InvariantCulture))
//ORIGINAL LINE: case "bt709":
						if (strCustomValue.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "bt709")
						{
								_xs->setTransfer(1);
						}
//ORIGINAL LINE: case "bt470m":
						else if (strCustomValue.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "bt470m")
						{
								_xs->setTransfer(2);
						}
//ORIGINAL LINE: case "bt470bg":
						else if (strCustomValue.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "bt470bg")
						{
								_xs->setTransfer(3);
						}
//ORIGINAL LINE: case "linear":
						else if (strCustomValue.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "linear")
						{
								_xs->setTransfer(4);
						}
//ORIGINAL LINE: case "log100":
						else if (strCustomValue.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "log100")
						{
								_xs->setTransfer(5);
						}
//ORIGINAL LINE: case "log316":
						else if (strCustomValue.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "log316")
						{
								_xs->setTransfer(6);
						}
//ORIGINAL LINE: case "smpte170m":
						else if (strCustomValue.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "smpte170m")
						{
								_xs->setTransfer(7);
						}
//ORIGINAL LINE: case "smpte240m":
						else if (strCustomValue.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "smpte240m")
						{
								_xs->setTransfer(8);
						}
					}
					return _xs->getTransfer();
				}

				int x264SettingsHandler::getColorMatrix()
				{
					std::string strCustomValue;
					if (extractCustomCommand("colormatrix", strCustomValue))
					{
//C# TO C++ CONVERTER NOTE: The following 'switch' operated on a string variable and was converted to C++ 'if-else' logic:
//						switch (strCustomValue.ToLower(System.Globalization.CultureInfo.InvariantCulture))
//ORIGINAL LINE: case "bt709":
						if (strCustomValue.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "bt709")
						{
								_xs->setColorMatrix(1);
						}
//ORIGINAL LINE: case "fcc":
						else if (strCustomValue.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "fcc")
						{
								_xs->setColorMatrix(2);
						}
//ORIGINAL LINE: case "bt470bg":
						else if (strCustomValue.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "bt470bg")
						{
								_xs->setColorMatrix(3);
						}
//ORIGINAL LINE: case "smpte170m":
						else if (strCustomValue.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "smpte170m")
						{
								_xs->setColorMatrix(4);
						}
//ORIGINAL LINE: case "smpte240m":
						else if (strCustomValue.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "smpte240m")
						{
								_xs->setColorMatrix(5);
						}
//ORIGINAL LINE: case "log316":
						else if (strCustomValue.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "log316")
						{
								_xs->setColorMatrix(6);
						}
//ORIGINAL LINE: case "gbr":
						else if (strCustomValue.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "gbr")
						{
								_xs->setColorMatrix(7);
						}
//ORIGINAL LINE: case "ycgco":
						else if (strCustomValue.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "ycgco")
						{
								_xs->setColorMatrix(8);
						}
					}
					return _xs->getColorMatrix();
				}

				int x264SettingsHandler::getProfile()
				{
					std::string strCustomValue;
					extractCustomCommand("profile", strCustomValue);
//C# TO C++ CONVERTER NOTE: The following 'switch' operated on a string variable and was converted to C++ 'if-else' logic:
//					switch (strCustomValue.ToLower(System.Globalization.CultureInfo.InvariantCulture))
//ORIGINAL LINE: case "baseline":
					if (strCustomValue.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "baseline")
					{
							_xs->setProfile(0);
					}
//ORIGINAL LINE: case "main":
					else if (strCustomValue.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "main")
					{
							_xs->setProfile(1);
					}
//ORIGINAL LINE: case "high":
					else if (strCustomValue.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "high")
					{
							_xs->setProfile(2);
					}

					if (_log == 0)
						return _xs->getProfile();

					if (_device->getProfile() > -1 && _xs->getProfile() > _device->getProfile())
					{
						if (_device->getProfile() == 0)
							_log->LogEvent("changing --profile to baseline as required for the selected device");
						else if (_device->getProfile() == 1)
							_log->LogEvent("changing --profile to main as required for the selected device");
						else
							_log->LogEvent("changing --profile to high as required for the selected device");
						_xs->setProfile(_device->getProfile());
					}

					return _xs->getProfile();
				}

				int x264SettingsHandler::getNalHrd()
				{
					std::string strCustomValue;
					extractCustomCommand("nal-hrd", strCustomValue);
//C# TO C++ CONVERTER NOTE: The following 'switch' operated on a string variable and was converted to C++ 'if-else' logic:
//					switch (strCustomValue.ToLower(System.Globalization.CultureInfo.InvariantCulture))
//ORIGINAL LINE: case "none":
					if (strCustomValue.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "none")
					{
							_xs->setNalhrd(0);
					}
//ORIGINAL LINE: case "vbr":
					else if (strCustomValue.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "vbr")
					{
							_xs->setNalhrd(1);
					}
//ORIGINAL LINE: case "cbr":
					else if (strCustomValue.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "cbr")
					{
							_xs->setNalhrd(2);
					}

					if (_log == 0)
						return _xs->getNalhrd();

					if (_device->getBluRay() && _xs->getNalhrd() < 1)
					{
						_log->LogEvent("changing --nal-hrd to vbr as required for the selected device");
						_xs->setNalhrd(1);
					}

					return _xs->getNalhrd();
				}

				MeGUI::AVCLevels::Levels x264SettingsHandler::getLevel()
				{
					std::string strCustomValue;
					extractCustomCommand("level", strCustomValue);
//C# TO C++ CONVERTER NOTE: The following 'switch' operated on a string variable and was converted to C++ 'if-else' logic:
//					switch (strCustomValue.ToLower(System.Globalization.CultureInfo.InvariantCulture).Replace(".", "").Trim())
//ORIGINAL LINE: case "1":
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Replace' method:
					if (strCustomValue.ToLower(System::Globalization::CultureInfo::InvariantCulture)->Replace(".", "")->Trim() == "1" || strCustomValue.ToLower(System::Globalization::CultureInfo::InvariantCulture)->Replace(".", "")->Trim() == "10")
					{
							_xs->setAVCLevel(AVCLevels::L_10);
					}
//ORIGINAL LINE: case "11":
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Replace' method:
					else if (strCustomValue.ToLower(System::Globalization::CultureInfo::InvariantCulture)->Replace(".", "")->Trim() == "11")
					{
							_xs->setAVCLevel(AVCLevels::L_11);
					}
//ORIGINAL LINE: case "12":
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Replace' method:
					else if (strCustomValue.ToLower(System::Globalization::CultureInfo::InvariantCulture)->Replace(".", "")->Trim() == "12")
					{
							_xs->setAVCLevel(AVCLevels::L_12);
					}
//ORIGINAL LINE: case "13":
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Replace' method:
					else if (strCustomValue.ToLower(System::Globalization::CultureInfo::InvariantCulture)->Replace(".", "")->Trim() == "13")
					{
							_xs->setAVCLevel(AVCLevels::L_13);
					}
//ORIGINAL LINE: case "1b":
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Replace' method:
					else if (strCustomValue.ToLower(System::Globalization::CultureInfo::InvariantCulture)->Replace(".", "")->Trim() == "1b")
					{
							_xs->setAVCLevel(AVCLevels::L_1B);
					}
//ORIGINAL LINE: case "2":
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Replace' method:
					else if (strCustomValue.ToLower(System::Globalization::CultureInfo::InvariantCulture)->Replace(".", "")->Trim() == "2" || strCustomValue.ToLower(System::Globalization::CultureInfo::InvariantCulture)->Replace(".", "")->Trim() == "20")
					{
							_xs->setAVCLevel(AVCLevels::L_20);
					}
//ORIGINAL LINE: case "21":
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Replace' method:
					else if (strCustomValue.ToLower(System::Globalization::CultureInfo::InvariantCulture)->Replace(".", "")->Trim() == "21")
					{
							_xs->setAVCLevel(AVCLevels::L_21);
					}
//ORIGINAL LINE: case "22":
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Replace' method:
					else if (strCustomValue.ToLower(System::Globalization::CultureInfo::InvariantCulture)->Replace(".", "")->Trim() == "22")
					{
							_xs->setAVCLevel(AVCLevels::L_22);
					}
//ORIGINAL LINE: case "3":
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Replace' method:
					else if (strCustomValue.ToLower(System::Globalization::CultureInfo::InvariantCulture)->Replace(".", "")->Trim() == "3" || strCustomValue.ToLower(System::Globalization::CultureInfo::InvariantCulture)->Replace(".", "")->Trim() == "30")
					{
							_xs->setAVCLevel(AVCLevels::L_30);
					}
//ORIGINAL LINE: case "31":
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Replace' method:
					else if (strCustomValue.ToLower(System::Globalization::CultureInfo::InvariantCulture)->Replace(".", "")->Trim() == "31")
					{
							_xs->setAVCLevel(AVCLevels::L_31);
					}
//ORIGINAL LINE: case "32":
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Replace' method:
					else if (strCustomValue.ToLower(System::Globalization::CultureInfo::InvariantCulture)->Replace(".", "")->Trim() == "32")
					{
							_xs->setAVCLevel(AVCLevels::L_32);
					}
//ORIGINAL LINE: case "4":
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Replace' method:
					else if (strCustomValue.ToLower(System::Globalization::CultureInfo::InvariantCulture)->Replace(".", "")->Trim() == "4" || strCustomValue.ToLower(System::Globalization::CultureInfo::InvariantCulture)->Replace(".", "")->Trim() == "40")
					{
							_xs->setAVCLevel(AVCLevels::L_40);
					}
//ORIGINAL LINE: case "41":
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Replace' method:
					else if (strCustomValue.ToLower(System::Globalization::CultureInfo::InvariantCulture)->Replace(".", "")->Trim() == "41")
					{
							_xs->setAVCLevel(AVCLevels::L_41);
					}
//ORIGINAL LINE: case "42":
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Replace' method:
					else if (strCustomValue.ToLower(System::Globalization::CultureInfo::InvariantCulture)->Replace(".", "")->Trim() == "42")
					{
							_xs->setAVCLevel(AVCLevels::L_42);
					}
//ORIGINAL LINE: case "5":
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Replace' method:
					else if (strCustomValue.ToLower(System::Globalization::CultureInfo::InvariantCulture)->Replace(".", "")->Trim() == "5" || strCustomValue.ToLower(System::Globalization::CultureInfo::InvariantCulture)->Replace(".", "")->Trim() == "50")
					{
							_xs->setAVCLevel(AVCLevels::L_50);
					}
//ORIGINAL LINE: case "51":
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Replace' method:
					else if (strCustomValue.ToLower(System::Globalization::CultureInfo::InvariantCulture)->Replace(".", "")->Trim() == "51")
					{
							_xs->setAVCLevel(AVCLevels::L_51);
					}
//ORIGINAL LINE: case "52":
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Replace' method:
					else if (strCustomValue.ToLower(System::Globalization::CultureInfo::InvariantCulture)->Replace(".", "")->Trim() == "52")
					{
							_xs->setAVCLevel(AVCLevels::L_52);
					}

					if (_log == 0)
						return _xs->getAVCLevel();

					if (_xs->getAVCLevel().compare(_device->getAVCLevel()) > 0)
					{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
						_log->LogEvent("changing --level to " + _device->getAVCLevel().ToString());
						_xs->setProfile(_device->getProfile());
					}

					return _xs->getAVCLevel();
				}

				int x264SettingsHandler::getKeyInt(int fps_n, int fps_d)
				{
					std::string strCustomValue;
					extractCustomCommand("keyint", strCustomValue);
					if (strCustomValue.ToLower(System::Globalization::CultureInfo::InvariantCulture)->Equals("infinite"))
						_xs->setKeyframeInterval(0);
					else
					{
						int iTemp = _xs->getKeyframeInterval();
						if (int::TryParse(strCustomValue, iTemp))
							_xs->setKeyframeInterval(iTemp);
					}

					if (_log == 0)
						return _xs->getKeyframeInterval();

					if (_xs->getx264GOPCalculation() == 1) // calculate min-keyint based on 25fps
						_xs->setKeyframeInterval(static_cast<int>(Math::Round(static_cast<double>(_xs->getKeyframeInterval()) / 25.0 * (static_cast<double>(fps_n) / fps_d), 0)));

					int fps = static_cast<int>(Math::Round(static_cast<decimal>(fps_n) / fps_d, 0));
					if (_device->getMaxGOP() > -1 && _xs->getKeyframeInterval() > fps * _device->getMaxGOP())
					{
						_log->LogEvent("changing --keyint to " + (fps * _device->getMaxGOP()) + " as required for the selected device");
						_xs->setKeyframeInterval(fps * _device->getMaxGOP());
					}

					return _xs->getKeyframeInterval();
				}

				int x264SettingsHandler::getMinKeyint(int fps_n, int fps_d)
				{
					std::string strCustomValue;
					extractCustomCommand("min-keyint", strCustomValue);
					int iTemp = _xs->getKeyframeInterval();
					if (int::TryParse(strCustomValue, iTemp))
						_xs->setMinGOPSize(iTemp);

					if (_log == 0)
						return _xs->getMinGOPSize();

					double fps = static_cast<double>(fps_n) / fps_d;
					if (_xs->getx264GOPCalculation() == 1) // calculate min-keyint based on 25fps
						_xs->setMinGOPSize(static_cast<int>(static_cast<double>(_xs->getMinGOPSize()) / 25.0 * fps));

					int iMaxValue = _xs->getKeyframeInterval() / 2 + 1;
					if (_device->getMaxGOP() > -1 && _xs->getMinGOPSize() > iMaxValue)
					{
						int iDefault = _xs->getKeyframeInterval() / 10;
						_log->LogEvent("changing --min-keyint to " + iDefault + " as required for the selected device");
						_xs->setMinGOPSize(iDefault);
					}

					return _xs->getMinGOPSize();
				}

				int x264SettingsHandler::getWeightp()
				{
					std::string strCustomValue;
					extractCustomCommand("weightp", strCustomValue);
					int iTemp = _xs->getWeightedPPrediction();
					if (int::TryParse(strCustomValue, iTemp))
						_xs->setWeightedPPrediction(iTemp);

					if (_log == 0)
						return _xs->getWeightedPPrediction();

					if (_device->getBluRay() && _xs->getWeightedPPrediction() > 1)
					{
						_log->LogEvent("changing --weightp to 1 as required for the selected device");
						_xs->setWeightedPPrediction(1);
					}

					return _xs->getWeightedPPrediction();
				}

				bool x264SettingsHandler::getBlurayCompat()
				{
					std::string strCustomValue;
					if (extractCustomCommand("bluray-compat", strCustomValue))
						_xs->setBlurayCompat(true);

					if (_log == 0)
						return _xs->getBlurayCompat();

					if (_device->getBluRay() && _xs->getBlurayCompat() == false)
					{
						_log->LogEvent("enabling --bluray-compat as required for the selected device");
						_xs->setBlurayCompat(true);
					}

					return _xs->getBlurayCompat();
				}

				bool x264SettingsHandler::getPicStruct()
				{
					std::string strCustomValue;
					if (extractCustomCommand("pic-struct", strCustomValue))
						_xs->setPicStruct(true);
					return _xs->getPicStruct();
				}

				bool x264SettingsHandler::getFakeInterlaced()
				{
					std::string strCustomValue;
					if (extractCustomCommand("fake-interlaced", strCustomValue))
						_xs->setFakeInterlaced(true);
					return _xs->getFakeInterlaced();
				}

				MeGUI::x264Settings::x264InterlacedModes x264SettingsHandler::getInterlacedMode()
				{
					std::string strCustomValue;
					if (extractCustomCommand("tff", strCustomValue))
						_xs->setInterlacedMode(x264Settings::tff);
					if (extractCustomCommand("bff", strCustomValue))
						_xs->setInterlacedMode(x264Settings::bff);
					return _xs->getInterlacedMode();
				}

				bool x264SettingsHandler::getAud()
				{
					std::string strCustomValue;
					if (extractCustomCommand("aud", strCustomValue))
						_xs->setX264Aud(true);

					if (_log == 0)
						return _xs->getX264Aud();

					if (_device->getBluRay() && _xs->getX264Aud() == false)
					{
						_log->LogEvent("enabling --aud as required for the selected device");
						_xs->setX264Aud(true);
					}

					return _xs->getX264Aud();
				}

				int x264SettingsHandler::getBFrames()
				{
					std::string strCustomValue;
					extractCustomCommand("bframes", strCustomValue);
					int iTemp = _xs->getNbBframes();
					if (int::TryParse(strCustomValue, iTemp))
						_xs->setNbBframes(iTemp);

					if (_log == 0)
						return _xs->getNbBframes();

					if (_device->getBFrames() > -1 && _xs->getNbBframes() > _device->getBFrames())
					{
						_log->LogEvent("changing --bframes to " + _device->getBFrames() + " as required for the selected device");
						_xs->setNbBframes(_device->getBFrames());
					}

					return _xs->getNbBframes();
				}

				int x264SettingsHandler::getBPyramid()
				{
					std::string strCustomValue;
					extractCustomCommand("b-pyramid", strCustomValue);
//C# TO C++ CONVERTER NOTE: The following 'switch' operated on a string variable and was converted to C++ 'if-else' logic:
//					switch (strCustomValue.ToLower(System.Globalization.CultureInfo.InvariantCulture))
//ORIGINAL LINE: case "none":
					if (strCustomValue.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "none")
					{
							_xs->setx264BFramePyramid(0);
					}
//ORIGINAL LINE: case "normal":
					else if (strCustomValue.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "normal")
					{
							_xs->setx264BFramePyramid(2);
					}
//ORIGINAL LINE: case "strict":
					else if (strCustomValue.ToLower(System::Globalization::CultureInfo::InvariantCulture) == "strict")
					{
							_xs->setx264BFramePyramid(1);
					}

					if (_log == 0)
						return _xs->getx264BFramePyramid();

					if (_device->getBluRay() && _xs->getx264BFramePyramid() > 1)
					{
						_log->LogEvent("changing --b-pyramid to strict as required for the selected device");
						_xs->setx264BFramePyramid(1);
					}

					if (_device->getBPyramid() > -1 && _xs->getx264BFramePyramid() != _device->getBPyramid())
					{
						std::string strMode = "normal";
						if (_device->getBPyramid() == 0)
							strMode = "none";
						else if (_device->getBPyramid() == 1)
							strMode = "strict";
						_log->LogEvent("changing --b-pyramid to " + strMode + " as required for the selected device");
						_xs->setx264BFramePyramid(_device->getBPyramid());
					}

					return _xs->getx264BFramePyramid();
				}

				int x264SettingsHandler::getSlices()
				{
					std::string strCustomValue;
					extractCustomCommand("slices", strCustomValue);
					int iTemp = _xs->getSlicesNb();
					if (int::TryParse(strCustomValue, iTemp))
						_xs->setSlicesNb(iTemp);

					if (_log == 0)
						return _xs->getSlicesNb();

					if (_device->getBluRay() && _xs->getSlicesNb() != 4)
					{
						_log->LogEvent("changing --slices to 4 as required for the selected device");
						_xs->setSlicesNb(4);
					}

					return _xs->getSlicesNb();
				}

				int x264SettingsHandler::getRefFrames(int hRes, int vRes)
				{
					std::string strCustomValue;
					extractCustomCommand("ref", strCustomValue);
					int iTemp = _xs->getNbRefFrames();
					if (int::TryParse(strCustomValue, iTemp))
						_xs->setNbRefFrames(iTemp);

					if (_log == 0)
						return _xs->getNbRefFrames();

					if (_device->getReferenceFrames() > -1 && _xs->getNbRefFrames() > _device->getReferenceFrames())
					{
						_log->LogEvent("changing --ref to " + _device->getReferenceFrames() + " as required for the selected device");
						_xs->setNbRefFrames(_device->getReferenceFrames());
					}

					int iMaxRefForLevel = getMaxRefForLevel(_xs->getAVCLevel(), hRes, vRes);
					if (iMaxRefForLevel > -1 && iMaxRefForLevel < _xs->getNbRefFrames())
					{
						_log->LogEvent("changing --ref to " + iMaxRefForLevel);
						_xs->setNbRefFrames(iMaxRefForLevel);
					}

					return _xs->getNbRefFrames();
				}

				int x264SettingsHandler::getMaxRefForLevel(AVCLevels::Levels avcLevel, int hRes, int vRes)
				{
					if (hRes <= 0 || vRes <= 0 || avcLevel == AVCLevels::L_UNRESTRICTED) // Unrestricted/Autoguess
						return -1;

					int maxDPB = 0; // the maximum picture decoded buffer for the given level
					switch (avcLevel)
					{
						case AVCLevels::L_10:
							maxDPB = 396;
							break;
						case AVCLevels::L_1B:
							maxDPB = 396;
							break;
						case AVCLevels::L_11:
							maxDPB = 900;
							break;
						case AVCLevels::L_12:
							maxDPB = 2376;
							break;
						case AVCLevels::L_13:
							maxDPB = 2376;
							break;
						case AVCLevels::L_20:
							maxDPB = 2376;
							break;
						case AVCLevels::L_21:
							maxDPB = 4752;
							break;
						case AVCLevels::L_22:
							maxDPB = 8100;
							break;
						case AVCLevels::L_30:
							maxDPB = 8100;
							break;
						case AVCLevels::L_31:
							maxDPB = 18000;
							break;
						case AVCLevels::L_32:
							maxDPB = 20480;
							break;
						case AVCLevels::L_40:
							maxDPB = 32768;
							break;
						case AVCLevels::L_41:
							maxDPB = 32768;
							break;
						case AVCLevels::L_42:
							maxDPB = 34816;
							break;
						case AVCLevels::L_50:
							maxDPB = 110400;
							break;
						case AVCLevels::L_51:
							maxDPB = 184320;
							break;
						case AVCLevels::L_52:
							maxDPB = 184320;
							break;
					}

					int frameHeightInMbs = static_cast<int>(ceil(static_cast<double>(vRes) / 16));
					int frameWidthInMbs = static_cast<int>(ceil(static_cast<double>(hRes) / 16));
					int maxRef = static_cast<int>(floor(static_cast<double>(maxDPB) / (frameHeightInMbs * frameWidthInMbs)));
					return __min(maxRef, 16);
				}

				bool x264SettingsHandler::extractCustomCommand(const std::string &strCommandToExtract, std::string &strCommandValue)
				{
					std::string strNewCommandLine = "";
					bool bFound = false;
					strCommandValue = "";

//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Split' method:
					for (unknown::const_iterator strCommand = System::Text::RegularExpressions::Regex->Split(_xs->getCustomEncoderOptions(), "--").begin(); strCommand != System::Text::RegularExpressions::Regex->Split(_xs->getCustomEncoderOptions(), "--").end(); ++strCommand)
					{
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'StartsWith' method:
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
						if ((*strCommand).Trim()->ToLower(System::Globalization::CultureInfo::InvariantCulture)->StartsWith(strCommandToExtract.ToLower(System::Globalization::CultureInfo::InvariantCulture)))
						{
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
							strCommandValue = (*strCommand).substr(strCommandToExtract.length())->Trim();
							bFound = true;
						}
						else
						{
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
							if (!((*strCommand).Trim())->empty())
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
								strNewCommandLine += " --" + (*strCommand).Trim();
						}
					}

//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
					_xs->setCustomEncoderOptions(strNewCommandLine.Trim());
					return bFound;
				}

				std::string x264SettingsHandler::getCustomCommandLine()
				{
					return _xs->getCustomEncoderOptions();
				}
			}
		}
	}
}
