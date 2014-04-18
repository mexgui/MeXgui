#include "HttpProxy.h"




//using namespace System::Net;
namespace MeXgui
{
	namespace core
	{
		namespace util
		{

			IWebProxy *HttpProxy::GetProxy(MeXguiSettings *settings)
			{
				// if None then return null
				if (settings->getHttpProxyMode() == None)
				{
					return 0;
				}

				// if SystemProxy then return the System proxy details with the logged in credentials
				if (settings->getHttpProxyMode() == SystemProxy)
				{
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++0x inferred typing option is selected:
					var systemProxy = WebRequest::GetSystemWebProxy();
					systemProxy->Credentials = CredentialCache::DefaultCredentials;
					return systemProxy;
				}

				// CustomProxy and CustomProxyWithLogin both require a Url
				if (settings->getHttpProxyAddress().empty())
				{
					return 0;
				}

//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++0x inferred typing option is selected:
				var address = settings->getHttpProxyPort().empty() ? settings->getHttpProxyAddress() : QString::Format("{0}:{1}", settings->getHttpProxyAddress(), settings->getHttpProxyPort());

				// if CustomProxyWithLogin then generate the credentials
				ICredentials *credentials;
				if (settings->getHttpProxyMode() == CustomProxy || settings->getHttpProxyUid().empty())
				{
//C# TO C++ CONVERTER WARNING: C# to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
					delete credentials;
				}
				else
				{
					credentials = new NetworkCredential(settings->getHttpProxyUid(), settings->getHttpProxyPwd());
				}

				WebProxy *proxy = new WebProxy(address, true, 0, credentials);

				return proxy;
			}
		}
	}
}
