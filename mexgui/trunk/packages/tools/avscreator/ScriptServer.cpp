#include "ScriptServer.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Globalization;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;

namespace MeGUI
{

const std::vector ScriptServer::ListOfResizeFilterType = EnumProxy::CreateArray(ResizeFilterType::typeid);
const std::vector ScriptServer::ListOfDenoiseFilterType = EnumProxy::CreateArray(DenoiseFilterType::typeid);
const std::vector ScriptServer::ListOfSourceTypes = EnumProxy::CreateArray(UserSourceType::typeid);
const std::vector ScriptServer::ListOfFieldOrders = EnumProxy::CreateArray(UserFieldOrder::typeid);
const std::vector ScriptServer::ListOfNvDeIntType = EnumProxy::CreateArray(NvDeinterlacerType::typeid);

	std::string ScriptServer::CreateScriptFromTemplate(const std::string &template_Renamed, const std::string &inputLine, const std::string &cropLine, const std::string &resizeLine, const std::string &denoiseLines, const std::string &deinterlaceLines)
	{
		std::string newScript = template_Renamed;
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Replace' method:
		newScript = newScript.Replace("<crop>", cropLine);
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Replace' method:
		newScript = newScript.Replace("<resize>", resizeLine);
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Replace' method:
		newScript = newScript.Replace("<denoise>", denoiseLines);
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Replace' method:
		newScript = newScript.Replace("<deinterlace>", deinterlaceLines);
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Replace' method:
		newScript = newScript.Replace("<input>", inputLine);
		return newScript;
	}

	std::string ScriptServer::GetInputLine(const std::string &input, const std::string &indexFile, bool interlaced, PossibleSources sourceType, bool colormatrix, bool mpeg2deblock, bool flipVertical, double fps, bool dss2)
	{
		std::string inputLine = "#input";
		std::string strDLLPath = "";

		switch (sourceType)
		{
			case avs:
				inputLine = "Import(\"" + input + "\")";
				break;
			case d2v:
				if (indexFile.empty())
					indexFile = input;
				strDLLPath = Path::Combine(Path::GetDirectoryName(MainForm::Instance->getSettings()->getDgIndexPath()), "DGDecode.dll");
				inputLine = "LoadPlugin(\"" + strDLLPath + "\")\r\nDGDecode_mpeg2source(\"" + indexFile + "\"";
				if (mpeg2deblock)
					inputLine += ", cpu=4";
				if (colormatrix)
					inputLine += ", info=3";
				inputLine += ")";
				if (colormatrix)
					inputLine += std::string::Format("\r\nLoadPlugin(\"" + Path::Combine(MainForm::Instance->getSettings()->getAvisynthPluginsPath(), "ColorMatrix.dll") + "\")\r\nColorMatrix(hints=true{0}, threads=0)", interlaced ? ", interlaced=true" : "");
				break;
			case dga:
				if (indexFile.empty())
					indexFile = input;
				strDLLPath = Path::Combine(Path::GetDirectoryName(MainForm::Instance->getSettings()->getDgavcIndexPath()), "DGAVCDecode.dll");
				inputLine = "LoadPlugin(\"" + strDLLPath + "\")\r\nAVCSource(\"" + indexFile + "\")";
				break;
			case dgi:
				if (indexFile.empty())
					indexFile = input;
				strDLLPath = Path::Combine(Path::GetDirectoryName(MainForm::Instance->getSettings()->getDgnvIndexPath()), "DGDecodeNV.dll");
				inputLine = "LoadPlugin(\"" + strDLLPath + "\")\r\nDGSource(\"" + indexFile + "\"";
				if (MainForm::Instance->getSettings()->getAutoForceFilm() && MainForm::Instance->getSettings()->getForceFilmThreshold() <= static_cast<decimal>(dgiFile::GetFilmPercent(indexFile)))
					inputLine += ",fieldop=1";
				else
					inputLine += ",fieldop=0";
				break;
			case ffindex:
				inputLine = VideoUtil::getFFMSInputLine(input, indexFile, fps);
				break;
			case vdr:
				inputLine = "AVISource(\"" + input + "\", audio=false)" + VideoUtil::getAssumeFPS(fps, input);
				break;
			case directShow:
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'EndsWith' method:
				if (input.ToLower(System::Globalization::CultureInfo::InvariantCulture)->EndsWith(".avi"))
				{
					inputLine = "AVISource(\"" + input + "\", audio=false)" + VideoUtil::getAssumeFPS(fps, input);
				}
				else
				{
					if (dss2 && File::Exists(Path::Combine(MeGUISettings::getHaaliMSPath(), "avss.dll")))
					{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
						inputLine = "LoadPlugin(\"" + MeGUISettings::getHaaliMSPath() + "\\avss.dll" + "\")\r\ndss2(\"" + input + "\"" + ((fps > 0) ? ", fps=" + fps.ToString("F3", new CultureInfo("en-us")) : "") + ")" + VideoUtil::getAssumeFPS(fps, input);
					}
					else
					{
						inputLine = "";
						if (MainForm::Instance->getSettings()->getPortableAviSynth())
							inputLine = "LoadPlugin(\"" + Path::Combine(Path::GetDirectoryName(MainForm::Instance->getSettings()->getAviSynthPath()), "directshowsource.dll") + "\")\r\n";
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
						inputLine += "DirectShowSource(\"" + input + "\"" + ((fps > 0) ? ", fps=" + fps.ToString("F3", new CultureInfo("en-us")) : "") + ", audio=false, convertfps=true)" + VideoUtil::getAssumeFPS(fps, input);
					}
					if (flipVertical)
						inputLine = inputLine + "\r\nFlipVertical()";
				}
				break;
		}
		return inputLine;
	}

	std::string ScriptServer::GetCropLine(bool crop, CropValues *cropValues)
	{
		std::string cropLine = "#crop";
		if (crop & cropValues->isCropped())
		{
			cropLine = std::string::Format("crop({0}, {1}, {2}, {3})", cropValues->left, cropValues->top, -cropValues->right, -cropValues->bottom);
		}
		return cropLine;
	}

	std::string ScriptServer::GetResizeLine(bool resize, int hres, int vres, int hresWithBorder, int vresWithBorder, ResizeFilterType type, bool crop, CropValues *cropValues, int originalHRes, int originalVRes)
	{
		int iInputHresAfterCrop = originalHRes;
		int iInputVresAfterCrop = originalVRes;
		if (crop)
		{
			iInputHresAfterCrop = iInputHresAfterCrop - cropValues->left - cropValues->right;
			iInputVresAfterCrop = iInputVresAfterCrop - cropValues->top - cropValues->bottom;
		}

		// only resize if necessary
		if (!resize || (hres == iInputHresAfterCrop && vres == iInputVresAfterCrop))
		{
			if (hresWithBorder > iInputHresAfterCrop || vresWithBorder > iInputVresAfterCrop)
				return getAddBorders(hres, vres, hresWithBorder, vresWithBorder);
			else
				return "#resize";
		}

		EnumProxy *p = EnumProxy::Create(type);
		if (p->getTag() != 0)
			if (hresWithBorder > hres || vresWithBorder > vres)
				return std::string::Format(p->getTag() + "." + getAddBorders(hres, vres, hresWithBorder, vresWithBorder) + " # {2}", hres, vres, p);
			else
				return std::string::Format(p->getTag() + " # {2}", hres, vres, p);
		else
			return "#resize - " + p;
	}

	std::string ScriptServer::getAddBorders(int hres, int vres, int hresWithBorder, int vresWithBorder)
	{
		CropValues *borderValues = new CropValues();
		borderValues->left = static_cast<int>(floor((hresWithBorder - hres) / 2.0));
		borderValues->top = static_cast<int>(floor((vresWithBorder - vres) / 2.0));
		borderValues->right = static_cast<int>(ceil((hresWithBorder - hres) / 2.0));
		borderValues->bottom = static_cast<int>(ceil((vresWithBorder - vres) / 2.0));

		// border values must be even for AviSynth 2.6
		if (borderValues->left % 2 != 0 && borderValues->right % 2 != 0)
		{
			borderValues->left -= 1;
			borderValues->right += 1;
		}
		if (borderValues->top % 2 != 0 && borderValues->bottom % 2 != 0)
		{
			borderValues->top -= 1;
			borderValues->bottom += 1;
		}

		return std::string::Format("AddBorders({0},{1},{2},{3})", borderValues->left, borderValues->top, borderValues->right, borderValues->bottom);
	}

	std::string ScriptServer::GetDenoiseLines(bool denoise, DenoiseFilterType type)
	{
		std::string denoiseLines = "#denoise";
		std::string strPath = "";
		if (denoise)
		{
			EnumProxy *p = EnumProxy::Create(type);
			if (p->getTag() != 0)
			{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
				if (p->getTag()->ToString()->ToLower(System::Globalization::CultureInfo::InvariantCulture)->Contains("undot"))
					strPath = "LoadPlugin(\"" + Path::Combine(MainForm::Instance->getSettings()->getAvisynthPluginsPath(), "UnDot.dll") + "\")\r\n";
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
				else if (p->getTag()->ToString()->ToLower(System::Globalization::CultureInfo::InvariantCulture)->Contains("fluxsmoothst"))
					strPath = "LoadPlugin(\"" + Path::Combine(MainForm::Instance->getSettings()->getAvisynthPluginsPath(), "FluxSmooth.dll") + "\")\r\n";
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
				else if (p->getTag()->ToString()->ToLower(System::Globalization::CultureInfo::InvariantCulture)->Contains("convolution3d"))
					strPath = "LoadPlugin(\"" + Path::Combine(MainForm::Instance->getSettings()->getAvisynthPluginsPath(), "Convolution3DYV12.dll") + "\")\r\n";
				denoiseLines = std::string::Format(strPath + p->getTag() + " # " + p);
			}
			else
				denoiseLines = "#denoise - " + p;
		}
		return denoiseLines;
	}

	std::string ScriptServer::GetNvDeInterlacerLine(bool deint, NvDeinterlacerType type)
	{
		std::string nvDeInterlacerLine = "";
		if (deint)
		{
			EnumProxy *p = EnumProxy::Create(type);
			if (p->getTag() != 0)
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
				nvDeInterlacerLine = p->getTag()->ToString();
		}
		return nvDeInterlacerLine;
	}

	std::vector<DeinterlaceFilter*> ScriptServer::GetDeinterlacers(SourceInfo *info)
	{
		std::vector<DeinterlaceFilter*> filters = std::vector<DeinterlaceFilter*>();
		if (info->sourceType == PROGRESSIVE)
		{
			filters.push_back(new DeinterlaceFilter("Do nothing", "#Not doing anything because the source is progressive"));
		}
		else if (info->sourceType == DECIMATING)
		{
			ScriptServer::AddTDecimate(info->decimateM, filters);
		}
		else if (info->sourceType == INTERLACED)
		{
			ScriptServer::AddYadif(info->fieldOrder, filters, false);
			ScriptServer::AddYadif(info->fieldOrder, filters, true);
			ScriptServer::AddTDeint(info->fieldOrder, filters, true, false, false);
			ScriptServer::AddTDeint(info->fieldOrder, filters, true, false, true);
			ScriptServer::AddTDeint(info->fieldOrder, filters, true, true, false);
			ScriptServer::AddTDeint(info->fieldOrder, filters, true, true, true);
			if (info->fieldOrder != VARIABLE)
				ScriptServer::AddLeakDeint(info->fieldOrder, filters);
			ScriptServer::AddTMC(info->fieldOrder, filters);
			ScriptServer::AddFieldDeint(info->fieldOrder, filters, true, true);
			ScriptServer::AddFieldDeint(info->fieldOrder, filters, true, false);
		}
		else if (info->sourceType == FILM)
		{
			ScriptServer::AddTIVTC("", info->isAnime, false, true, false, info->fieldOrder, filters);
			ScriptServer::AddIVTC(info->fieldOrder, false, true, filters);
		}
		else if (info->sourceType == HYBRID_FILM_INTERLACED || info->sourceType == HYBRID_PROGRESSIVE_FILM)
		{
			ScriptServer::AddTIVTC("", info->isAnime, true, info->majorityFilm, false, info->fieldOrder, filters);
			ScriptServer::AddTIVTC("", info->isAnime, true, info->majorityFilm, true, info->fieldOrder, filters);
			ScriptServer::AddIVTC(info->fieldOrder, true, info->majorityFilm, filters);
		}
		else if (info->sourceType == HYBRID_PROGRESSIVE_INTERLACED)
		{
			ScriptServer::AddYadif(info->fieldOrder, filters, false);
			ScriptServer::AddYadif(info->fieldOrder, filters, true);
			ScriptServer::AddTDeint(info->fieldOrder, filters, false, false, false);
			ScriptServer::AddTDeint(info->fieldOrder, filters, true, false, true);
			ScriptServer::AddTDeint(info->fieldOrder, filters, true, true, false);
			ScriptServer::AddTDeint(info->fieldOrder, filters, false, true, true);
			ScriptServer::AddFieldDeint(info->fieldOrder, filters, false, true);
			ScriptServer::AddFieldDeint(info->fieldOrder, filters, false, false);
			if (info->fieldOrder != VARIABLE)
				ScriptServer::AddLeakDeint(info->fieldOrder, filters);
			ScriptServer::AddTMC(info->fieldOrder, filters);
		}
		return filters;
	}

	int ScriptServer::Order(FieldOrder order)
	{
		int i_order = -1;
		if (order == BFF)
			i_order = 0;
		if (order == TFF)
			i_order = 1;
		return i_order;
	}

	void ScriptServer::AddYadif(FieldOrder order, std::vector<DeinterlaceFilter*> &filters, bool bobber)
	{
		filters.push_back(new DeinterlaceFilter(bobber ? "Yadif (with Bob)" : "Yadif", std::string::Format("Load_Stdcall_Plugin(\"{0}\"){1}Yadif({2}order={3})", MainForm::Instance->getSettings()->getYadifPath(), "\r\n", bobber ? "mode=1, " : "", Order(order))));
	}

	void ScriptServer::AddLeakDeint(FieldOrder order, std::vector<DeinterlaceFilter*> &filters)
	{
		filters.push_back(new DeinterlaceFilter("LeakKernelDeint", std::string::Format("LoadPlugin(\"{0}\"){1}LeakKernelDeint(order={2},sharp=true)", Path::Combine(MainForm::Instance->getSettings()->getAvisynthPluginsPath(), "LeakKernelDeint.dll"), "\r\n", Order(order))));
	}

	void ScriptServer::AddTDeint(FieldOrder order, std::vector<DeinterlaceFilter*> &filters, bool processAll, bool eedi2, bool bob)
	{
		StringBuilder *script = new StringBuilder();
		script->Append("LoadPlugin(\"" + Path::Combine(MainForm::Instance->getSettings()->getAvisynthPluginsPath(), "TDeint.dll") + "\")\r\n");
		if (eedi2)
		{
			script->Append("LoadPlugin(\"" + Path::Combine(MainForm::Instance->getSettings()->getAvisynthPluginsPath(), "EEDI2.dll") + "\")\r\n");
			script->Append("edeintted = last.");
			if (order == TFF)
				script->Append("AssumeTFF().");
			else if (order == BFF)
				script->Append("AssumeBFF().");
			script->Append("SeparateFields().EEDI2(field=-1)\r\n");
		}
		script->Append("TDeint(");

		if (bob)
			script->Append("mode=1,");
		if (order != VARIABLE)
			script->Append("order=" + Order(order) + ",");
		if (!processAll) // For hybrid clips
			script->Append("full=false,");
		if (eedi2)
			script->Append("edeint=edeintted,");

//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'TrimEnd' method:
		script = new StringBuilder(script->ToString()->TrimEnd(new wchar_t[] {','}));
		script->Append(")");
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		filters.push_back(new DeinterlaceFilter(bob ? (eedi2 ? "TDeint (with EDI + Bob)" : "TDeint (with Bob)") : (eedi2 ? "TDeint (with EDI)" : "TDeint"), script->ToString()));
	}

	void ScriptServer::AddFieldDeint(FieldOrder order, std::vector<DeinterlaceFilter*> &filters, bool processAll, bool blend)
	{
		std::string name = "FieldDeinterlace";
		if (!blend)
			name = "FieldDeinterlace (no blend)";

		StringBuilder *script = new StringBuilder();
		script->Append("LoadPlugin(\"" + Path::Combine(MainForm::Instance->getSettings()->getAvisynthPluginsPath(), "Decomb.dll") + "\")\r\n");
		if (order == TFF)
			script->Append("AssumeTFF().");
		else if (order == BFF)
			script->Append("AssumeBFF().");

		script->Append("FieldDeinterlace(");

		if (!blend)
			script->Append("blend=false");

		if (!processAll)
		{
			if (!blend)
				script->Append(",");
			script->Append("full=false");
		}
		script->Append(")");
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		filters.push_back(new DeinterlaceFilter(name, script->ToString()));
	}

	void ScriptServer::AddTMC(FieldOrder order, std::vector<DeinterlaceFilter*> &filters)
	{
		filters.push_back(new DeinterlaceFilter("TomsMoComp", std::string::Format("LoadPlugin(\"{0}\"){1}TomsMoComp({2},5,1)", Path::Combine(MainForm::Instance->getSettings()->getAvisynthPluginsPath(), "TomsMoComp.dll"), "\r\n", Order(order))));
	}

	void ScriptServer::Portionize(std::vector<DeinterlaceFilter*> &filters, const std::string &trimLine)
	{
		for (int i = 0; i < filters.size(); i++)
		{
			std::string script = filters[i]->getScript();
			StringBuilder *newScript = new StringBuilder();
			newScript->AppendLine("original = last");
			newScript->Append("deintted = original.");
			newScript->AppendLine(script);
			newScript->Append(trimLine);
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
			filters[i]->setScript(newScript->ToString());
		}
	}

	void ScriptServer::AddTIVTC(const std::string &d2vFile_Renamed, bool anime, bool hybrid, bool mostlyFilm, bool advancedDeinterlacing, FieldOrder fieldOrder, std::vector<DeinterlaceFilter*> &filters)
	{
		StringBuilder *script = new StringBuilder();
		script->Append("LoadPlugin(\"" + Path::Combine(MainForm::Instance->getSettings()->getAvisynthPluginsPath(), "TIVTC.dll") + "\")\r\n");
		if (advancedDeinterlacing)
		{
			script->Append("LoadPlugin(\"" + Path::Combine(MainForm::Instance->getSettings()->getAvisynthPluginsPath(), "EEDI2.dll") + "\")\r\n");
			script->Append("LoadPlugin(\"" + Path::Combine(MainForm::Instance->getSettings()->getAvisynthPluginsPath(), "TDeint.dll") + "\")\r\n");
			script->Append("edeintted = ");
			if (fieldOrder == TFF)
				script->Append("AssumeTFF().");
			else if (fieldOrder == BFF)
				script->Append("AssumeBFF().");
			script->AppendFormat("SeparateFields().SelectEven().EEDI2(field=-1)\r\n");
			script->Append("tdeintted = TDeint(edeint=edeintted");
			if (fieldOrder != VARIABLE)
				script->Append(",order=" + Order(fieldOrder));
			script->Append(")\r\n");
		}

		script->Append("tfm(");
		if (d2vFile_Renamed.length() <= 0)
			script->AppendFormat("order={0}", Order(fieldOrder));
		if (advancedDeinterlacing)
		{
			if (d2vFile_Renamed.length() <= 0)
				script->Append(",");
			script->Append("clip2=tdeintted");
		}
		script->Append(")");

		script->Append(".tdecimate(");
		if (anime)
			script->Append("mode=1");
		if (hybrid)
		{
			if (anime)
				script->Append(",");
			if (mostlyFilm)
				script->Append("hybrid=1");
			else
				script->Append("hybrid=3");

		}
		script->Append(")");
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		filters.push_back(new DeinterlaceFilter(advancedDeinterlacing ? "TIVTC + TDeint(EDI) -- slow" : "TIVTC", script->ToString()));
	}

	void ScriptServer::AddIVTC(FieldOrder order, bool hybrid, bool mostlyFilm, std::vector<DeinterlaceFilter*> &filters)
	{
		StringBuilder *script = new StringBuilder();
		script->Append("LoadPlugin(\"" + Path::Combine(MainForm::Instance->getSettings()->getAvisynthPluginsPath(), "Decomb.dll") + "\")\r\n");
		if (order == TFF)
			script->Append("AssumeTFF().");
		else if (order == BFF)
			script->Append("AssumeBFF().");

		script->Append("Telecide(guide=1).Decimate(");

		if (hybrid)
		{
			if (mostlyFilm)
				script->Append("mode=3,");
			else
				script->Append("mode=1,");

			script->Append("threshold=2.0");
		}

		script->Append(")");
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		filters.push_back(new DeinterlaceFilter("Decomb IVTC", script->ToString()));
	}

	void ScriptServer::AddTDecimate(int decimateM, std::vector<DeinterlaceFilter*> &filters)
	{
		filters.push_back(new DeinterlaceFilter("Tritical Decimate", std::string::Format("LoadPlugin(\"{0}\"){1}TDecimate(cycleR={2})", Path::Combine(MainForm::Instance->getSettings()->getAvisynthPluginsPath(), "TIVTC.dll"), "\r\n", decimateM)));
	}

const std::string ScriptServer::DetectionScript = "{0} #original script" + "\r\n" + "{1} #trimming" + "\r\n" + "{5} #LoadPlugin" + "\r\n" + "global unused_ = blankclip(pixel_type=\"yv12\", length=10).TFM()" + "\r\n" + "file=\"{2}\\" + "\r\n" + "global sep=\"-\\" + "\r\n" + "function IsMoving() {{" + "\r\n" + "  global b = (diff < 1.0) ? false : true}}" + "\r\n" + "ConvertToYV12()" + "\r\n" + "c = last" + "\r\n" + "global clip = last" + "\r\n" + "c = WriteFile(c, file, \"a\", \"sep\", \"b\")" + "\r\n" + "c = FrameEvaluate(c, \"global a = IsCombedTIVTC(clip, cthresh=9)\")" + "\r\n" + "c = FrameEvaluate(c, \"IsMoving\")" + "\r\n" + "c = FrameEvaluate(c,\"global diff = 0.50*YDifferenceFromPrevious(clip) + 0.25*UDifferenceFromPrevious(clip) + 0.25*VDifferenceFromPrevious(clip)\")" + "\r\n" + "crop(c,0,0,16,16)" + "\r\n" + "SelectRangeEvery({3},{4},0)";
const std::string ScriptServer::FieldOrderScript = "{0} # original script" + "\r\n" + "{1} #trimming" + "\r\n" + "file=\"{2}\\" + "\r\n" + "global sep=\"-\\" + "\r\n" + "ConvertToYV12()" + "\r\n" + "d = last" + "\r\n" + "global abff = d.assumebff().separatefields()" + "\r\n" + "global atff = d.assumetff().separatefields()" + "\r\n" + "c = d.loop(2)" + "\r\n" + "c = WriteFile(c, file, \"diffa\", \"sep\", \"diffb\")" + "\r\n" + "c = FrameEvaluate(c,\"global diffa = 0.50*YDifferenceFromPrevious(abff) + 0.25*UDifferenceFromPrevious(abff) + 0.25*VDifferenceFromPrevious(abff)\")" + "\r\n" + "c = FrameEvaluate(c,\"global diffb = 0.50*YDifferenceFromPrevious(atff) + 0.25*UDifferenceFromPrevious(atff) + 0.25*VDifferenceFromPrevious(atff)\")" + "\r\n" + "crop(c,0,0,16,16)" + "\r\n" + "SelectRangeEvery({3},{4},0)" + "\r\n" + "";

	std::string ScriptServer::getScript(int scriptType, const std::string &originalScript, const std::string &trimLine, const std::string &logFileName, int selectEvery, int selectLength)
	{
		if (scriptType == 0) // detection
			return std::string::Format(DetectionScript, originalScript, trimLine, logFileName, selectEvery, selectLength, "LoadPlugin(\"" + Path::Combine(MainForm::Instance->getSettings()->getAvisynthPluginsPath(), "TIVTC.dll") + "\")");
		else if (scriptType == 1) // field order
			return std::string::Format(FieldOrderScript, originalScript, trimLine, logFileName, selectEvery, selectLength);
		else
			return 0;
	}

	void ScriptServer::undercrop(CropValues *&crop, modValue mValue)
	{
		int mod = MeGUI::core::util::Resolution::GetModValue(mValue, undercrop, true);

		if (crop->left % 2 != 0 && crop->top % 2 != 0 && crop->bottom % 2 != 0 && crop->right % 2 != 0)
			throw std::exception("Cropping by odd numbers not supported in undercropping to mod" + mod);

		while ((crop->left + crop->right) % mod > 0)
		{
			if (crop->left > crop->right)
			{
				if (crop->left > 1)
					crop->left -= 2;
				else
					crop->left = 0;
			}
			else
			{
				if (crop->right > 1)
					crop->right -= 2;
				else
					crop->right = 0;
			}
		}
		while ((crop->top + crop->bottom) % mod > 0)
		{
			if (crop->top > crop->bottom)
			{
				if (crop->top > 1)
					crop->top -= 2;
				else
					crop->top = 0;
			}
			else
			{
				if (crop->bottom > 1)
					crop->bottom -= 2;
				else
					crop->bottom = 0;
			}
		}
	}

	void ScriptServer::overcrop(CropValues *&crop, modValue mValue)
	{
		int mod = MeGUI::core::util::Resolution::GetModValue(mValue, overcrop, true);

		if (crop->left % 2 != 0 && crop->top % 2 != 0 && crop->bottom % 2 != 0 && crop->right % 2 != 0)
			throw std::exception("Cropping by odd numbers not supported in overcropping to mod" + mod);

		bool doLeftNext = true;
		while ((crop->left + crop->right) % mod != 0)
		{
			if (doLeftNext)
				crop->left += 2;
			else
				crop->right += 2;
			doLeftNext = !doLeftNext;
		}

		bool doTopNext = true;
		while ((crop->top + crop->bottom) % mod != 0)
		{
			if (doTopNext)
				crop->top += 2;
			else
				crop->bottom += 2;
			doTopNext = !doTopNext;
		}
	}

	void ScriptServer::cropMod4Horizontal(CropValues *&crop)
	{
		if (crop->left % 2 != 0 && crop->top % 2 != 0 && crop->bottom % 2 != 0 && crop->right % 2 != 0)
			throw std::exception("Cropping by odd numbers not supported in mod4 horizontal cropping");
		while ((crop->left + crop->right) % 4 > 0)
		{
			if (crop->left > crop->right)
			{
				if (crop->left > 1)
				{
					crop->left -= 2;
				}
				else
				{
					crop->left = 0;
				}
			}
			else
			{
				if (crop->right > 1)
				{
					crop->right -= 2;
				}
				else
				{
					crop->right = 0;
				}
			}
		}
	}
}
