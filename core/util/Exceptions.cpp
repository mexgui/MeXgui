#include "Exceptions.h"




//using namespace System::Collections::Generic;

//using namespace System::Text;
namespace MeXgui
{
	namespace core
	{
		namespace util
		{

			MeXguiException::MeXguiException(const QString &message) : Exception(message)
			{
			}

			MeXguiException::MeXguiException(std::exception &inner) : Exception(inner.what(), inner)
			{
			}

			MeXguiException::MeXguiException(const QString &message, std::exception &inner) : Exception(message, inner)
			{
			}

			JobRunException::JobRunException(const QString &message) : MeXguiException(message)
			{
			}

			JobRunException::JobRunException(std::exception &inner) : MeXguiException(inner.what(), inner)
			{
			}

			JobRunException::JobRunException(const QString &message, std::exception &inner) : MeXguiException(message, inner)
			{
			}

			MissingFileException::MissingFileException(const QString &file) : JobRunException("Required file '" + file + "' is missing.")
			{
				filename = file;
			}

			EncoderMissingException::EncoderMissingException(const QString &file) : MissingFileException(file)
			{
			}
		}
	}
}
