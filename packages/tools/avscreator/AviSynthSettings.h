#pragma once

#include "core/gui/Profiles.h"
#include "ScriptServer.h"
#include "AviSynthWindow.h"
#include <QString>
#include <QMap>

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




//using namespace System::Text;

using namespace MeXgui::core::plugins::interfaces;

namespace MeXgui
{
	/// <summary>
	/// Summary description for AviSynthSettings.
	/// </summary>
	class AviSynthSettings : public GenericSettings
	{
	public:
		static QString ID;
		const QString &getSettingsID() const;

	private:
		QString template_Renamed;
		ResizeFilterType resizeMethod;
		DenoiseFilterType denoiseMethod;
		mod16Method mod16Method;
		modValue modValueUsed;
		bool deinterlace, denoise, ivtc, mpeg2deblock, colourCorrect, dss2, resize, upsize;
		decimal acceptableAspectError;

	public:
		void FixFileNames(QMap<QString, QString> &_);

		AviSynthSettings();

		AviSynthSettings(const QString &template_Renamed, ResizeFilterType resizeMethod, bool resize, bool upsize, DenoiseFilterType denoiseMethod, bool denoise, bool mpeg2deblock, bool colourCorrect, mod16Method method, bool dss2, modValue modValueUsed, decimal acceptableAspectError);

		bool Equals(object *obj);

		bool Equals(GenericSettings *other);

		int GetHashCode();

	private:
		object *ICloneable_Clone();

		GenericSettings *GenericSettings_Clone();

	public:
		AviSynthSettings *Clone();

		const mod16Method &getMod16Method() const;
		void setMod16Method(const mod16Method &value);

		const modValue &getModValue() const;
		void setModValue(const modValue &value);

		const bool &getResize() const;
		void setResize(const bool &value);

		const bool &getUpsize() const;
		void setUpsize(const bool &value);

		const QString &getTemplate() const;
		void setTemplate(const QString &value);

		const ResizeFilterType &getResizeMethod() const;
		void setResizeMethod(const ResizeFilterType &value);

		const DenoiseFilterType &getDenoiseMethod() const;
		void setDenoiseMethod(const DenoiseFilterType &value);

		const bool &getDeinterlace() const;
		void setDeinterlace(const bool &value);

		const bool &getDenoise() const;
		void setDenoise(const bool &value);

		const bool &getIVTC() const;
		void setIVTC(const bool &value);

		const bool &getMPEG2Deblock() const;
		void setMPEG2Deblock(const bool &value);

		const bool &getColourCorrect() const;
		void setColourCorrect(const bool &value);

		const bool &getDSS2() const;
		void setDSS2(const bool &value);

		/// <summary>
		/// Maximum aspect error (%) to allow in anamorphic resizing.
		/// </summary>
		const decimal &getAcceptableAspectError() const;
		void setAcceptableAspectError(const decimal &value);



		const QString *getRequiredFiles() const;

		const QString *getRequiredProfiles() const;

	};
}
