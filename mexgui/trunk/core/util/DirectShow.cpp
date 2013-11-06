#include "DirectShow.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Runtime::InteropServices;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;

namespace MeGUI
{

	DsOptInt64::DsOptInt64(long long Value)
	{
		this->Value = Value;
	}

Guid *const Clsid::SystemDeviceEnum = new Guid(0x62BE5D10, 0x60EB, 0x11d0, 0xBD, 0x3B, 0x00, 0xA0, 0xC9, 0x11, 0xCE, 0x86);
Guid *const Clsid::FilterGraph = new Guid(0xe436ebb3, 0x524f, 0x11ce, 0x9f, 0x53, 0x00, 0x20, 0xaf, 0x0b, 0xa7, 0x70);
Guid *const Clsid::CaptureGraphBuilder2 = new Guid(0xBF87B6E1, 0x8C27, 0x11d0, 0xB3, 0xF0, 0x0, 0xAA, 0x00, 0x37, 0x61, 0xC5);
Guid *const Clsid::SampleGrabber = new Guid(0xC1F400A0, 0x3F08, 0x11D3, 0x9F, 0x0B, 0x00, 0x60, 0x08, 0x03, 0x9E, 0x37);
Guid *const Clsid::DvdGraphBuilder = new Guid(0xFCC152B7, 0xF372, 0x11d0, 0x8E, 0x00, 0x00, 0xC0, 0x4F, 0xD7, 0xC0, 0x8B);

	bool DirectShow::checkRender(const std::string &fileName)
	{
		Type *comtype = 0;
		object *comobj = 0;
		try
		{
			comtype = Type::GetTypeFromCLSID(Clsid::FilterGraph);
			if (comtype == 0)
				throw new NotSupportedException("DirectX (8.1 or higher) not installed?");
			comobj = Activator::CreateInstance(comtype);
			graphBuilder = static_cast<IGraphBuilder*>(comobj);
//C# TO C++ CONVERTER WARNING: C# to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
			delete comobj;
			int hr = graphBuilder->RenderFile(fileName, 0);
			if (hr >= 0)
				return true;
			else
				return false;
		}
		catch (std::exception &e1)
		{
			return false;
			//throw (e); // May add more handling here later
		}
	}
}
