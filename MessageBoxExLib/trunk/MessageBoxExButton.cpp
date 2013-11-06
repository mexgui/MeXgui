#include "MessageBoxExButton.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
namespace Utils
{
	namespace MessageBoxExLib
	{

		const std::string &MessageBoxExButton::getText() const
		{
			return _text;
		}

		void MessageBoxExButton::setText(const std::string &value)
		{
			_text = value;
		}

		const std::string &MessageBoxExButton::getValue() const
		{
			return _value;
		}

		void MessageBoxExButton::setValue(const std::string &value)
		{
			_value = value;
		}

		const std::string &MessageBoxExButton::getHelpText() const
		{
			return _helpText;
		}

		void MessageBoxExButton::setHelpText(const std::string &value)
		{
			_helpText = value;
		}

		const bool &MessageBoxExButton::getIsCancelButton() const
		{
			return _isCancelButton;
		}

		void MessageBoxExButton::setIsCancelButton(const bool &value)
		{
			_isCancelButton = value;
		}

		void MessageBoxExButton::InitializeInstanceFields()
		{
			_text = "";
			_value = "";
			_helpText = "";
			_isCancelButton = false;
		}
	}
}
