#include "Exceptions.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
namespace MeGUI
{
	namespace core
	{
		namespace util
		{

			MeGUIException::MeGUIException(const std::string &message) : Exception(message)
			{
			}

			MeGUIException::MeGUIException(std::exception &inner) : Exception(inner.what(), inner)
			{
			}

			MeGUIException::MeGUIException(const std::string &message, std::exception &inner) : Exception(message, inner)
			{
			}

			JobRunException::JobRunException(const std::string &message) : MeGUIException(message)
			{
			}

			JobRunException::JobRunException(std::exception &inner) : MeGUIException(inner.what(), inner)
			{
			}

			JobRunException::JobRunException(const std::string &message, std::exception &inner) : MeGUIException(message, inner)
			{
			}

			MissingFileException::MissingFileException(const std::string &file) : JobRunException("Required file '" + file + "' is missing.")
			{
				filename = file;
			}

			EncoderMissingException::EncoderMissingException(const std::string &file) : MissingFileException(file)
			{
			}
		}
	}
}
