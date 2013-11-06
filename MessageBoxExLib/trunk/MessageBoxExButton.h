#pragma once

#include <string>

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;

namespace Utils
{
	namespace MessageBoxExLib
	{
		/// <summary>
		/// Internal DataStructure used to represent a button
		/// </summary>
		class MessageBoxExButton
		{
		private:
			std::string _text;
			/// <summary>
			/// Gets or Sets the text of the button
			/// </summary>
		public:
			const std::string &getText() const;
			void setText(const std::string &value);

		private:
			std::string _value;
			/// <summary>
			/// Gets or Sets the return value when this button is clicked
			/// </summary>
		public:
			const std::string &getValue() const;
			void setValue(const std::string &value);

		private:
			std::string _helpText;
			/// <summary>
			/// Gets or Sets the tooltip that is displayed for this button
			/// </summary>
		public:
			const std::string &getHelpText() const;
			void setHelpText(const std::string &value);

		private:
			bool _isCancelButton;
			/// <summary>
			/// Gets or Sets wether this button is a cancel button. i.e. the button
			/// that will be assumed to have been clicked if the user closes the message box
			/// without pressing any button.
			/// </summary>
		public:
			const bool &getIsCancelButton() const;
			void setIsCancelButton(const bool &value);

		private:
			void InitializeInstanceFields();

public:
			MessageBoxExButton()
			{
				InitializeInstanceFields();
			}
		};
	}
}
