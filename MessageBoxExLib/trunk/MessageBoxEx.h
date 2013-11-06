#pragma once

#include "MessageBoxExForm.h"
#include "TimeoutResult.h"
#include "MessageBoxExButton.h"
#include "MessageBoxExButtons.h"
#include "MessageBoxExManager.h"
#include <string>

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Drawing;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;

namespace Utils
{
	namespace MessageBoxExLib
	{
		/// <summary>
		/// An extended MessageBox with lot of customizing capabilities.
		/// </summary>
		class MessageBoxEx
		{
		private:
			MessageBoxExForm *_msgBox;
			/// <summary>
			/// Sets the caption of the message box
			/// </summary>
		public:
			void setCaption(const std::string &value);

			/// <summary>
			/// Sets the text of the message box
			/// </summary>
			void setText(const std::string &value);

			/// <summary>
			/// Sets the icon to show in the message box
			/// </summary>
			void setCustomIcon(const System::Drawing::Icon &value);

			/// <summary>
			/// Sets the icon to show in the message box
			/// </summary>
			void setIcon(const MessageBoxIcon &value);

			/// <summary>
			/// Sets the font for the text of the message box
			/// </summary>
			void setFont(const System::Drawing::Font &value);

			/// <summary>
			/// Sets or Gets the ability of the  user to save his/her response
			/// </summary>
			const bool &getAllowSaveResponse() const;
			void setAllowSaveResponse(const bool &value);

			/// <summary>
			/// Sets the text to show to the user when saving his/her response
			/// </summary>
			void setSaveResponseText(const std::string &value);

			/// <summary>
			/// Sets or Gets wether an alert sound is played while showing the message box.
			/// The sound played depends on the the Icon selected for the message box
			/// </summary>
			const bool &getPlayAlertSound() const;
			void setPlayAlertSound(const bool &value);

			/// <summary>
			/// Sets or Gets the time in milliseconds for which the message box is displayed.
			/// </summary>
			const int &getTimeout() const;
			void setTimeout(const int &value);

			/// <summary>
			/// Controls the result that will be returned when the message box times out.
			/// </summary>
			const Utils::MessageBoxExLib::TimeoutResult &getTimeoutResult() const;
			void setTimeoutResult(const Utils::MessageBoxExLib::TimeoutResult &value);

			/// <summary>
			/// Gets or sets the value of the save response checkbox
			/// </summary>
			const bool &getSaveResponseChecked() const;
			void setSaveResponseChecked(const bool &value);

			/// <summary>
			/// Shows the message box
			/// </summary>
			/// <returns></returns>
			std::string Show();

			/// <summary>
			/// Shows the messsage box with the specified owner
			/// </summary>
			/// <param name="owner"></param>
			/// <returns></returns>
			std::string Show(IWin32Window *owner);

			/// <summary>
			/// Add a custom button to the message box
			/// </summary>
			/// <param name="button">The button to add</param>
			void AddButton(MessageBoxExButton *button);

			/// <summary>
			/// Add a custom button to the message box
			/// </summary>
			/// <param name="text">The text of the button</param>
			/// <param name="val">The return value in case this button is clicked</param>
			void AddButton(const std::string &text, const std::string &val);

			/// <summary>
			/// Add a standard button to the message box
			/// </summary>
			/// <param name="buttons">The standard button to add</param>
			void AddButton(MessageBoxExButtons button);

			/// <summary>
			/// Add standard buttons to the message box.
			/// </summary>
			/// <param name="buttons">The standard buttons to add</param>
			void AddButtons(MessageBoxButtons *buttons);

			/// <summary>
			/// Ctor is internal because this can only be created by MBManager
			/// </summary>
			MessageBoxEx();

			/// <summary>
			/// Called by the manager when it is disposed
			/// </summary>
			~MessageBoxEx();

		private:
			void InitializeInstanceFields();
		};
	}
}
