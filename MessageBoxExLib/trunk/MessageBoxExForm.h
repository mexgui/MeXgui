#pragma once

#include "MessageBoxExButton.h"
#include "TimeoutResult.h"
#include "MessageBoxExButtons.h"
#include "MessageBoxExResult.h"
#include <string>
#include <cmath>
#include <stdexcept>

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Drawing;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::ComponentModel;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Diagnostics;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Runtime::InteropServices;

namespace Utils
{
	namespace MessageBoxExLib
	{
		/// <summary>
		/// An advanced MessageBox that supports customizations like Font, Icon,
		/// Buttons and Saved Responses
		/// </summary>
		class MessageBoxExForm : public System::Windows::Forms::Form
		{
		private:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[StructLayout(LayoutKind::Sequential, CharSet=CharSet::Auto)]
			class LOGFONT
			{
			public:
				int lfHeight;
				int lfWidth;
				int lfEscapement;
				int lfOrientation;
				int lfWeight;
				unsigned char lfItalic;
				unsigned char lfUnderline;
				unsigned char lfStrikeOut;
				unsigned char lfCharSet;
				unsigned char lfOutPrecision;
				unsigned char lfClipPrecision;
				unsigned char lfQuality;
				unsigned char lfPitchAndFamily;
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[MarshalAs(UnmanagedType::ByValTStr, SizeConst = 32)]
				std::string lfFaceSize;
			};

		private:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//[StructLayout(LayoutKind::Sequential, CharSet=CharSet::Auto)]
			class NONCLIENTMETRICS
			{
			public:
				int cbSize;
				int iBorderWidth;
				int iScrollWidth;
				int iScrollHeight;
				int iCaptionWidth;
				int iCaptionHeight;
				LOGFONT lfCaptionFont;
				int iSmCaptionWidth;
				int iSmCaptionHeight;
				LOGFONT lfSmCaptionFont;
				int iMenuWidth;
				int iMenuHeight;
				LOGFONT lfMenuFont;
				LOGFONT lfStatusFont;
				LOGFONT lfMessageFont;
			};

		private:
			static const int LEFT_PADDING = 12;
			static const int RIGHT_PADDING = 12;
			static const int TOP_PADDING = 12;
			static const int BOTTOM_PADDING = 12;

			static const int BUTTON_LEFT_PADDING = 4;
			static const int BUTTON_RIGHT_PADDING = 4;
			static const int BUTTON_TOP_PADDING = 4;
			static const int BUTTON_BOTTOM_PADDING = 4;

			static const int MIN_BUTTON_HEIGHT = 23;
			static const int MIN_BUTTON_WIDTH = 74;

			static const int ITEM_PADDING = 10;
			static const int ICON_MESSAGE_PADDING = 15;

			static const int BUTTON_PADDING = 5;

			static const int CHECKBOX_WIDTH = 20;

			static const int IMAGE_INDEX_EXCLAMATION = 0;
			static const int IMAGE_INDEX_QUESTION = 1;
			static const int IMAGE_INDEX_STOP = 2;
			static const int IMAGE_INDEX_INFORMATION = 3;


			System::ComponentModel::IContainer *components;
			System::Windows::Forms::CheckBox *chbSaveResponse;
			System::Windows::Forms::ImageList *imageListIcons;
			System::Windows::Forms::ToolTip *buttonToolTip;

			ArrayList *_buttons;
			bool _allowSaveResponse;
			bool _playAlert;
			MessageBoxExButton *_cancelButton;
			Button *_defaultButtonControl;

			int _maxLayoutWidth;
			int _maxLayoutHeight;

			int _maxWidth;
			int _maxHeight;

			bool _allowCancel;
			std::string _result;

			/// <summary>
			/// Used to determine the alert sound to play
			/// </summary>
			MessageBoxIcon *_standardIcon;
			Icon *_iconImage;

			Timer *timerTimeout;
			int _timeout;
			Utils::MessageBoxExLib::TimeoutResult _timeoutResult;
			System::Windows::Forms::Panel *panelIcon;
			System::Windows::Forms::RichTextBox *rtbMessage;

			/// <summary>
			/// Maps MessageBoxEx buttons to Button controls
			/// </summary>
			Hashtable *_buttonControlsTable;

			public:
			~MessageBoxExForm()
			{
				this->Dispose(true);
			}

//C# TO C++ CONVERTER WARNING: Unlike C#, there is no automatic call to this finalizer method in native C++:
			private:
			void Finalize()
			{
				this->Dispose(false);
			}

		public:
			void setMessage(const std::string &value);

			void setCaption(const std::string &value);

			void setCustomFont(const Font &value);

			const ArrayList &getButtons() const;

			const bool &getAllowSaveResponse() const;
			void setAllowSaveResponse(const bool &value);

			const bool &getSaveResponse() const;
			void setSaveResponse(const bool &value);

			void setSaveResponseText(const std::string &value);

			void setStandardIcon(const MessageBoxIcon &value);

			void setCustomIcon(const Icon &value);

			void setCustomCancelButton(const MessageBoxExButton &value);

			const std::string &getResult() const;

			const bool &getPlayAlertSound() const;
			void setPlayAlertSound(const bool &value);

			const int &getTimeout() const;
			void setTimeout(const int &value);

			const Utils::MessageBoxExLib::TimeoutResult &getTimeoutResult() const;
			void setTimeoutResult(const Utils::MessageBoxExLib::TimeoutResult &value);

			MessageBoxExForm();

			/// <summary>
			/// Clean up any resources being used.
			/// </summary>
		private:
			void Dispose(bool disposing);

			/// <summary>
			/// Required method for Designer support - do not modify
			/// the contents of this method with the code editor.
			/// </summary>
			void InitializeComponent();

			/// <summary>
			/// This will get called everytime we call ShowDialog on the form
			/// </summary>
			/// <param name="e"></param>
		protected:
			virtual void OnLoad(EventArgs *e);


			virtual bool ProcessCmdKey(System::Messaging::Message *&msg, Keys *keyData);


			virtual void OnClosing(CancelEventArgs *e);

			virtual void OnPaint(PaintEventArgs *e);


			/// <summary>
			/// Measures a string using the Graphics object for this form with
			/// the specified font
			/// </summary>
			/// <param name="str">The string to measure</param>
			/// <param name="maxWidth">The maximum width available to display the string</param>
			/// <param name="font">The font with which to measure the string</param>
			/// <returns></returns>
		private:
			Size *MeasureString(const std::string &str, int maxWidth, Font *font);

			/// <summary>
			/// Measures a string using the Graphics object for this form and the
			/// font of this form
			/// </summary>
			/// <param name="str"></param>
			/// <param name="maxWidth"></param>
			/// <returns></returns>
			Size *MeasureString(const std::string &str, int maxWidth);

			/// <summary>
			/// Gets the longest button text
			/// </summary>
			/// <returns></returns>
			std::string GetLongestButtonText();

			/// <summary>
			/// Sets the size and visibility of the Message
			/// </summary>
			void SetMessageSizeAndVisibility();

			/// <summary>
			/// Sets the size and visibility of the Icon
			/// </summary>
			void SetIconSizeAndVisibility();

			/// <summary>
			/// Sets the size and visibility of the save response checkbox
			/// </summary>
			void SetCheckboxSizeAndVisibility();

			/// <summary>
			/// Calculates the button size based on the text of the longest
			/// button text
			/// </summary>
			/// <returns></returns>
			Size *GetButtonSize();

			/// <summary>
			/// Set the icon
			/// </summary>
			/// <param name="icon"></param>
			void SetStandardIcon(MessageBoxIcon *icon);

			void AddOkButtonIfNoButtonsPresent();


			/// <summary>
			/// Centers the form on the screen
			/// </summary>
			void CenterForm();

			/// <summary>
			/// Sets the optimum size for the form based on the controls that
			/// need to be displayed
			/// </summary>
			void SetOptimumSize();

			/// <summary>
			/// Returns the width that will be occupied by all buttons including
			/// the inter-button padding
			/// </summary>
			int GetWidthOfAllButtons();

			/// <summary>
			/// Gets the width of the caption
			/// </summary>
			Size *GetCaptionSize();

			/// <summary>
			/// Layout all the controls 
			/// </summary>
			void LayoutControls();

			/// <summary>
			/// Gets the button control for the specified MessageBoxExButton, if the
			/// control has not been created this method creates the control
			/// </summary>
			/// <param name="button"></param>
			/// <param name="size"></param>
			/// <param name="location"></param>
			/// <returns></returns>
			Button *GetButton(MessageBoxExButton *button, Size *size, Point *location);

			/// <summary>
			/// Creates a button control based on info from MessageBoxExButton
			/// </summary>
			/// <param name="button"></param>
			/// <param name="size"></param>
			/// <param name="location"></param>
			/// <returns></returns>
			Button *CreateButton(MessageBoxExButton *button, Size *size, Point *location);

			void DisableCloseIfMultipleButtonsAndNoCancelButton();

			/// <summary>
			/// Plays the alert sound based on the icon set for the message box
			/// </summary>
			void PlayAlert();

			void SelectDefaultButton();

			void StartTimerIfTimeoutGreaterThanZero();

			void SetResultAndClose(const std::string &result);


			void OnButtonClicked(object *sender, EventArgs *e);

			void timerTimeout_Tick(object *sender, EventArgs *e);

			Font *GetCaptionFont();

			static const int SPI_GETNONCLIENTMETRICS = 41;
			static const int LF_FACESIZE = 32;

//C# TO C++ CONVERTER NOTE: The following .NET DllImport attribute was converted using the Microsoft-specific __declspec(dllimport):
//[DllImport("user32.dll", SetLastError=true, CharSet=CharSet::Auto)]
			__declspec(dllimport) static bool SystemParametersInfo(int uiAction, int uiParam, NONCLIENTMETRICS &ncMetrics, int fWinIni);


//C# TO C++ CONVERTER NOTE: The following .NET DllImport attribute was converted using the Microsoft-specific __declspec(dllimport):
//[DllImport("user32.dll", CharSet=CharSet::Auto)]
			__declspec(dllimport) static IntPtr GetSystemMenu(IntPtr hWnd, bool bRevert);

//C# TO C++ CONVERTER NOTE: The following .NET DllImport attribute was converted using the Microsoft-specific __declspec(dllimport):
//[DllImport("user32.dll", CharSet=CharSet::Auto)]
			__declspec(dllimport) static bool EnableMenuItem(IntPtr hMenu, unsigned int uIDEnableItem, unsigned int uEnable);

			static const int SC_CLOSE = 0xF060;
			static const int MF_BYCOMMAND = 0x0;
			static const int MF_GRAYED = 0x1;
			static const int MF_ENABLED = 0x0;

			void DisableCloseButton(Form *form);

//C# TO C++ CONVERTER NOTE: The following .NET DllImport attribute was converted using the Microsoft-specific __declspec(dllimport):
//[DllImport("user32.dll", CharSet=CharSet::Auto)]
			__declspec(dllimport) static bool MessageBeep(unsigned int type);

		private:
			void InitializeInstanceFields();
		};
	}
}
