#include "x264Device.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;

namespace MeGUI
{

	std::vector<x264Device*> x264Device::CreateDeviceList()
	{
		std::vector<x264Device*> x264DeviceList = std::vector<x264Device*>();
		x264DeviceList.push_back(new x264Device(0, "Default", -1, AVCLevels::L_UNRESTRICTED, -1, -1, -1, -1, -1, -1));
		x264DeviceList.push_back(new x264Device(2, "AVCHD", 2, AVCLevels::L_41, 14000, 14000, 3, 6, 1920, 1080, true, -1, -1));
		x264DeviceList.push_back(new x264Device(3, "Blu-ray", 2, AVCLevels::L_41, 30000, 40000, 3, 6, 1920, 1080, true, 1, -1));
		x264DeviceList.push_back(new x264Device(4, "DivX Plus HD", 2, AVCLevels::L_40, 25000, 20000, 3, -1, 1920, 1080, false, 4, -1));
		x264DeviceList.push_back(new x264Device(5, "DXVA", 2, AVCLevels::L_41, -1, -1, -1, -1, -1, -1));
		x264DeviceList.push_back(new x264Device(7, "iPhone 2G", 0, AVCLevels::L_13, -1, -1, 0, 1, 640, 480));
		x264DeviceList.push_back(new x264Device(9, "iPhone 3G/3GS, iPod classic, iPod touch 1/2/3, iPod nano 3/4/5", 0, AVCLevels::L_30, -1, -1, 0, 1, 640, 480));
		x264DeviceList.push_back(new x264Device(8, "iPhone 4, iPad 1/2, iPod touch 4/5", 1, AVCLevels::L_31, -1, -1, -1, -1, 1280, 720));
		x264DeviceList.push_back(new x264Device(15, "iPhone 4S/5, iPad 3/4/mini, WDTV", 2, AVCLevels::L_41, -1, -1, -1, -1, 1920, 1080));
		x264DeviceList.push_back(new x264Device(17, "iPod nano 7", 2, AVCLevels::L_30, -1, -1, -1, -1, 720, 576));
		x264DeviceList.push_back(new x264Device(12, "PS3", 2, AVCLevels::L_41, 31250, 31250, -1, -1, 1920, 1080));
		x264DeviceList.push_back(new x264Device(13, "PSP", 1, AVCLevels::L_30, 10000, 10000, -1, 3, 480, 272, false, -1, 0));
		x264DeviceList.push_back(new x264Device(14, "Xbox 360", 2, AVCLevels::L_41, 24000, 24000, 3, 3, 1920, 1080));
		return x264DeviceList;
	}

	x264Device::x264Device(int iID, const std::string &strName, int iProfile, AVCLevels::Levels avcLevel, int iVBVBufsize, int iVBVMaxrate, int iBframes, int iReframes, int iMaxWidth, int iMaxHeight)
	{
	}

	x264Device::x264Device(int iID, const std::string &strName, int iProfile, AVCLevels::Levels avcLevel, int iVBVBufsize, int iVBVMaxrate, int iBframes, int iReframes, int iMaxWidth, int iMaxHeight, bool bBluRay, int iMaxGop, int iBPyramid)
	{
		this->iID = iID;
		this->strName = strName;
		this->iProfile = iProfile;
		this->avcLevel = avcLevel;
		this->iVBVBufsize = iVBVBufsize;
		this->iVBVMaxrate = iVBVMaxrate;
		this->iBframes = iBframes;
		this->iReframes = iReframes;
		this->iMaxWidth = iMaxWidth;
		this->iMaxHeight = iMaxHeight;
		this->bBluRay = bBluRay;
		this->iBPyramid = iBPyramid;
		this->iMaxGop = iMaxGop;
	}

	const int &x264Device::getID() const
	{
		return iID;
	}

	const std::string &x264Device::getName() const
	{
		return strName;
	}

	const int &x264Device::getProfile() const
	{
		return iProfile;
	}

	const AVCLevels::Levels &x264Device::getAVCLevel() const
	{
		return avcLevel;
	}

	const int &x264Device::getVBVBufsize() const
	{
		return iVBVBufsize;
	}

	const int &x264Device::getVBVMaxrate() const
	{
		return iVBVMaxrate;
	}

	const int &x264Device::getBFrames() const
	{
		return iBframes;
	}

	const int &x264Device::getReferenceFrames() const
	{
		return iReframes;
	}

	const int &x264Device::getHeight() const
	{
		return iMaxHeight;
	}

	const int &x264Device::getWidth() const
	{
		return iMaxWidth;
	}

	const int &x264Device::getMaxGOP() const
	{
		return iMaxGop;
	}

	void x264Device::setMaxGOP(const int &value)
	{
		iMaxGop = value;
	}

	const bool &x264Device::getBluRay() const
	{
		return bBluRay;
	}

	void x264Device::setBluRay(const bool &value)
	{
		bBluRay = value;
	}

	const int &x264Device::getBPyramid() const
	{
		return iBPyramid;
	}

	void x264Device::setBPyramid(const int &value)
	{
		iBPyramid = value;
	}

	std::string x264Device::ToString()
	{
		return strName;
	}
}
