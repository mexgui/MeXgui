#pragma once

#include "core/gui/MeXgui.MainForm.h"
#include "AviSynthWindow.h"
#include "packages/reader/dgi/dgiReader.h"
#include "core/util/VideoUtil.h"
#include "core/details/MeXguiSettings.h"
#include "core/util/EnumProxy.h"
#include "core/gui/SourceDetector.h"
#include "core/util/DeinterlaceFilter.h"
#include "packages/reader/d2v/d2vReader.h"
#include "core/util/Resolution.h"
#include <QString>
#include <QVector>
#include <cmath>
#include <stdexcept>

// ****************************************************************************
// 
// Copyright (C) 2005-2013 Doom9 & al
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
// 
// ****************************************************************************






//using namespace System::Collections::Generic;

//using namespace System::Globalization;



//using namespace System::Text;



namespace MeXgui
{
	enum ResizeFilterType
	{

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("Bilinear (Soft)", "BilinearResize({0},{1})")]
		Bilinear = 0,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("Bicubic (Sharp)", "BicubicResize({0},{1},0,0.75)")]
		BicubicSharp,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("Bicubic (Neutral)", "BicubicResize({0},{1},0,0.5)")]
		BicubicNeutral,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("Bicubic (Soft)", "BicubicResize({0},{1},0.333,0.333)")]
		BicubicSoft,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("Lanczos (Sharp)", "LanczosResize({0},{1})")]
		Lanczos,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("Lanczos4 (Sharp)", "Lanczos4Resize({0},{1})")]
		Lanczos4,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("Gauss (Neutral)", "GaussResize({0},{1})")]
		Gauss,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("Point (Sharp)", "PointResize({0},{1})")]
		Point,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("Spline16 (Neutral)", "Spline16Resize({0},{1})")]
		Spline16,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("Spline36 (Neutral)", "Spline36Resize({0},{1})")]
		Spline32,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("Spline64 (Sharp)", "Spline64Resize({0},{1})")]
		Spline64

	};

	enum DenoiseFilterType
	{

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("Minimal Noise", "Undot()")]
		MinimalNoise = 0,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("Little Noise", "mergechroma(blur(1.3))")]
		LittleNoise,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("Medium Noise", "FluxSmoothST(7,7)")]
		MediumNoise,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("Heavy Noise", "Convolution3D(\"movielq\")")]
		HeavyNoise
	};

	enum NvDeinterlacerType
	{
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("No Deinterlacing", ", deinterlace=0")]
		nvDeInterlacerNone = 0,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("Single Rate Deinterlacing", ", deinterlace=1")]
		nvDeInterlacerSingle,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("Bobbing", ", deinterlace=2")]
		nvDeInterlacerDouble
	};

	enum UserSourceType
	{
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("Progressive", SourceType::PROGRESSIVE)]
		Progressive,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("Interlaced", SourceType::INTERLACED)]
		Interlaced,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("Film", SourceType::FILM)]
		Film,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("M-in-5 decimation required", SourceType::DECIMATING)]
		Decimating,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("Hybrid film/interlaced. Mostly film", SourceType::HYBRID_FILM_INTERLACED)]
		HybridFilmInterlaced,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("Hybrid film/interlaced. Mostly interlaced", SourceType::HYBRID_FILM_INTERLACED)]
		HybridInterlacedFilm,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("Partially interlaced", SourceType::HYBRID_PROGRESSIVE_INTERLACED)]
		HybridProgressiveInterlaced,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("Partially film", SourceType::HYBRID_PROGRESSIVE_FILM)]
		HybridProgressiveFilm
	};

	enum UserFieldOrder
	{
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("Top Field First", FieldOrder::TFF)]
		TFF,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("Bottom Field First", FieldOrder::BFF)]
		BFF,
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[EnumTitle("Varying field order", FieldOrder::VARIABLE)]
		Varying
	};

	class ScriptServer
	{
	public:
		static const QVector ListOfResizeFilterType;

		static const QVector ListOfDenoiseFilterType;

		static const QVector ListOfSourceTypes;

		static const QVector ListOfFieldOrders;

		static const QVector ListOfNvDeIntType;

		static MainForm *mainForm;


		static QString CreateScriptFromTemplate(const QString &template_Renamed, const QString &inputLine, const QString &cropLine, const QString &resizeLine, const QString &denoiseLines, const QString &deinterlaceLines);

		static QString GetInputLine(const QString &input, const QString &indexFile, bool interlaced, PossibleSources sourceType, bool colormatrix, bool mpeg2deblock, bool flipVertical, double fps, bool dss2);

		static QString GetCropLine(bool crop, CropValues *cropValues);

		static QString GetResizeLine(bool resize, int hres, int vres, int hresWithBorder, int vresWithBorder, ResizeFilterType type, bool crop, CropValues *cropValues, int originalHRes, int originalVRes);

	private:
		static QString getAddBorders(int hres, int vres, int hresWithBorder, int vresWithBorder);

	public:
		static QString GetDenoiseLines(bool denoise, DenoiseFilterType type);

		static QString GetNvDeInterlacerLine(bool deint, NvDeinterlacerType type);


		static QVector<DeinterlaceFilter*> GetDeinterlacers(SourceInfo *info);

		static int Order(FieldOrder order);

		static void AddYadif(FieldOrder order, QVector<DeinterlaceFilter*> &filters, bool bobber);

		static void AddLeakDeint(FieldOrder order, QVector<DeinterlaceFilter*> &filters);

		static void AddTDeint(FieldOrder order, QVector<DeinterlaceFilter*> &filters, bool processAll, bool eedi2, bool bob);

		static void AddFieldDeint(FieldOrder order, QVector<DeinterlaceFilter*> &filters, bool processAll, bool blend);

		static void AddTMC(FieldOrder order, QVector<DeinterlaceFilter*> &filters);

		static void Portionize(QVector<DeinterlaceFilter*> &filters, const QString &trimLine);

//C# TO C++ CONVERTER NOTE: The parameter d2vFile was renamed since it is named the same as a user-defined type:
		static void AddTIVTC(const QString &d2vFile_Renamed, bool anime, bool hybrid, bool mostlyFilm, bool advancedDeinterlacing, FieldOrder fieldOrder, QVector<DeinterlaceFilter*> &filters);

		static void AddIVTC(FieldOrder order, bool hybrid, bool mostlyFilm, QVector<DeinterlaceFilter*> &filters);


		static void AddTDecimate(int decimateM, QVector<DeinterlaceFilter*> &filters);
	private:
		static const QString DetectionScript;

		static const QString FieldOrderScript;

	public:
		static QString getScript(int scriptType, const QString &originalScript, const QString &trimLine, const QString &logFileName, int selectEvery, int selectLength);

		static void undercrop(CropValues *&crop, modValue mValue);

		static void overcrop(CropValues *&crop, modValue mValue);

		static void cropMod4Horizontal(CropValues *&crop);

	};
}
