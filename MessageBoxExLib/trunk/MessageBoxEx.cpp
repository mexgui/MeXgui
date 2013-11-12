#include<Qt>
#include "MessageBoxEx.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
using namespace System::Drawing;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
using namespace System::Windows::Forms;

namespace Utils
{
	namespace MessageBoxExLib
	{

		void MessageBoxEx::setCaption(const std::string &value)
		{
			_msgBox->setCaption(value);
		}

		void MessageBoxEx::setText(const std::string &value)
		{
			_msgBox->setMessage(value);
		}

		void MessageBoxEx::setCustomIcon(const System::Drawing::Icon &value)
		{
			_msgBox->setCustomIcon(value);
		}

		void MessageBoxEx::setIcon(const MessageBoxIcon &value)
		{
			_msgBox->setStandardIcon(value);
		}

		void MessageBoxEx::setFont(const System::Drawing::Font &value)
		{
			_msgBox->Font = value;
		}

		const bool &MessageBoxEx::getAllowSaveResponse() const
		{
			return _msgBox->getAllowSaveResponse();
		}

		void MessageBoxEx::setAllowSaveResponse(const bool &value)
		{
			_msgBox->setAllowSaveResponse(value);
		}

		void MessageBoxEx::setSaveResponseText(const std::string &value)
		{
			_msgBox->setSaveResponseText(value);
		}

		const bool &MessageBoxEx::getPlayAlertSound() const
		{
			return _msgBox->getPlayAlertSound();
		}

		void MessageBoxEx::setPlayAlertSound(const bool &value)
		{
			_msgBox->setPlayAlertSound(value);
		}

		const int &MessageBoxEx::getTimeout() const
		{
			return _msgBox->getTimeout();
		}

		void MessageBoxEx::setTimeout(const int &value)
		{
			_msgBox->setTimeout(value);
		}

		const Utils::MessageBoxExLib::TimeoutResult &MessageBoxEx::getTimeoutResult() const
		{
			return _msgBox->getTimeoutResult();
		}

		void MessageBoxEx::setTimeoutResult(const Utils::MessageBoxExLib::TimeoutResult &value)
		{
			_msgBox->setTimeoutResult(value);
		}

		const bool &MessageBoxEx::getSaveResponseChecked() const
		{
			return _msgBox->getSaveResponse();
		}

		void MessageBoxEx::setSaveResponseChecked(const bool &value)
		{
			_msgBox->setSaveResponse(value);
		}

		std::string MessageBoxEx::Show()
		{
			return Show(0);
		}

		std::string MessageBoxEx::Show(IWin32Window *owner)
		{
			if (owner == 0)
			{
				_msgBox->ShowDialog();
			}
			else
			{
				_msgBox->ShowDialog(owner);
			}
			delete this;

			return _msgBox->getResult();
		}

		void MessageBoxEx::AddButton(MessageBoxExButton *button)
		{
			if (button == 0)
				throw new ArgumentNullException("button","A null button cannot be added");

			_msgBox->getButtons()->Add(button);

			if (button->getIsCancelButton())
			{
				_msgBox->setCustomCancelButton(button);
			}
		}

		void MessageBoxEx::AddButton(const std::string &text, const std::string &val)
		{
			if (text == "")
				throw new ArgumentNullException("text","Text of a button cannot be null");

			if (val == "")
				throw new ArgumentNullException("val","Value of a button cannot be null");

			MessageBoxExButton *button = new MessageBoxExButton();
			button->setText(text);
			button->setValue(val);

			AddButton(button);
		}

		void MessageBoxEx::AddButton(MessageBoxExButtons button)
		{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
			std::string buttonText = MessageBoxExManager::GetLocalizedString(button.ToString());
			if (buttonText == "")
			{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
				buttonText = button.ToString();
			}

//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
			std::string buttonVal = button.ToString();

			MessageBoxExButton *btn = new MessageBoxExButton();
			btn->setText(buttonText);
			btn->setValue(buttonVal);

			if (button == Cancel)
			{
				btn->setIsCancelButton(true);
			}

			AddButton(btn);
		}

		void MessageBoxEx::AddButtons(MessageBoxButtons *buttons)
		{
			switch (buttons)
			{
				case MessageBoxButtons::OK:
					AddButton(Ok);
					break;

				case MessageBoxButtons::AbortRetryIgnore:
					AddButton(Abort);
					AddButton(Retry);
					AddButton(Ignore);
					break;

				case MessageBoxButtons::OKCancel:
					AddButton(Ok);
					AddButton(Cancel);
					break;

				case MessageBoxButtons::RetryCancel:
					AddButton(Retry);
					AddButton(Cancel);
					break;

				case MessageBoxButtons::YesNo:
					AddButton(Yes);
					AddButton(No);
					break;

				case MessageBoxButtons::YesNoCancel:
					AddButton(Yes);
					AddButton(No);
					AddButton(Cancel);
					break;
			}
		}

		MessageBoxEx::MessageBoxEx()
		{
			InitializeInstanceFields();
		}

		MessageBoxEx::~MessageBoxEx()
		{
			InitializeInstanceFields();
			if (_msgBox != 0)
			{
				delete _msgBox;
			}
		}

		void MessageBoxEx::InitializeInstanceFields()
		{
			_msgBox = new MessageBoxExForm();
		}
	}
}
