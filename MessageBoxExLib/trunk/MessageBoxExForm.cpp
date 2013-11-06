#include "MessageBoxExForm.h"

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

		void MessageBoxExForm::setMessage(const std::string &value)
		{
			rtbMessage->Text = value;
		}

		void MessageBoxExForm::setCaption(const std::string &value)
		{
			this->Text = value;
		}

		void MessageBoxExForm::setCustomFont(const Font &value)
		{
			this->Font = value;
		}

		const ArrayList &MessageBoxExForm::getButtons() const
		{
			return _buttons;
		}

		const bool &MessageBoxExForm::getAllowSaveResponse() const
		{
			return _allowSaveResponse;
		}

		void MessageBoxExForm::setAllowSaveResponse(const bool &value)
		{
			_allowSaveResponse = value;
		}

		const bool &MessageBoxExForm::getSaveResponse() const
		{
			return chbSaveResponse->Checked;
		}

		void MessageBoxExForm::setSaveResponse(const bool &value)
		{
			chbSaveResponse->Checked = value;
		}

		void MessageBoxExForm::setSaveResponseText(const std::string &value)
		{
			chbSaveResponse->Text = value;
		}

		void MessageBoxExForm::setStandardIcon(const MessageBoxIcon &value)
		{
			SetStandardIcon(value);
		}

		void MessageBoxExForm::setCustomIcon(const Icon &value)
		{
			_standardIcon = MessageBoxIcon::None;
			_iconImage = value;
		}

		void MessageBoxExForm::setCustomCancelButton(const MessageBoxExButton &value)
		{
			_cancelButton = value;
		}

		const std::string &MessageBoxExForm::getResult() const
		{
			return _result;
		}

		const bool &MessageBoxExForm::getPlayAlertSound() const
		{
			return _playAlert;
		}

		void MessageBoxExForm::setPlayAlertSound(const bool &value)
		{
			_playAlert = value;
		}

		const int &MessageBoxExForm::getTimeout() const
		{
			return _timeout;
		}

		void MessageBoxExForm::setTimeout(const int &value)
		{
			_timeout = value;
		}

		const Utils::MessageBoxExLib::TimeoutResult &MessageBoxExForm::getTimeoutResult() const
		{
			return _timeoutResult;
		}

		void MessageBoxExForm::setTimeoutResult(const Utils::MessageBoxExLib::TimeoutResult &value)
		{
			_timeoutResult = value;
		}

		MessageBoxExForm::MessageBoxExForm()
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeInstanceFields();
			InitializeComponent();

			_maxWidth = static_cast<int>(SystemInformation::WorkingArea->Width * 0.60);
			_maxHeight = static_cast<int>(SystemInformation::WorkingArea->Height * 0.90);
		}

		void MessageBoxExForm::Dispose(bool disposing)
		{
			if (disposing)
			{
				if (components != 0)
				{
					delete components;
				}
			}
			System::Windows::Forms::Form::Dispose(disposing);
		}

		void MessageBoxExForm::InitializeComponent()
		{
			this->components = new System::ComponentModel::Container();
			System::Resources::ResourceManager *resources = new System::Resources::ResourceManager(MessageBoxExForm::typeid);
			this->panelIcon = new System::Windows::Forms::Panel();
			this->chbSaveResponse = new System::Windows::Forms::CheckBox();
			this->imageListIcons = new System::Windows::Forms::ImageList(this->components);
			this->buttonToolTip = new System::Windows::Forms::ToolTip(this->components);
			this->rtbMessage = new System::Windows::Forms::RichTextBox();
			this->SuspendLayout();
			// 
			// panelIcon
			// 
			this->panelIcon->BackColor = System::Drawing::Color::Transparent;
			this->panelIcon->Location = new System::Drawing::Point(8, 8);
			this->panelIcon->Name = "panelIcon";
			this->panelIcon->Size = new System::Drawing::Size(32, 32);
			this->panelIcon->TabIndex = 3;
			this->panelIcon->Visible = false;
			// 
			// chbSaveResponse
			// 
			this->chbSaveResponse->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->chbSaveResponse->Location = new System::Drawing::Point(56, 56);
			this->chbSaveResponse->Name = "chbSaveResponse";
			this->chbSaveResponse->Size = new System::Drawing::Size(104, 16);
			this->chbSaveResponse->TabIndex = 0;
			// 
			// imageListIcons
			// 
			this->imageListIcons->ColorDepth = System::Windows::Forms::ColorDepth::Depth16Bit;
			this->imageListIcons->ImageSize = new System::Drawing::Size(32, 32);
			this->imageListIcons->ImageStream = (static_cast<System::Windows::Forms::ImageListStreamer*>(resources->GetObject("imageListIcons.ImageStream")));
			this->imageListIcons->TransparentColor = System::Drawing::Color::Transparent;
			// 
			// rtbMessage
			// 
			this->rtbMessage->BackColor = System::Drawing::SystemColors::Control;
			this->rtbMessage->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->rtbMessage->Location = new System::Drawing::Point(200, 8);
			this->rtbMessage->Name = "rtbMessage";
			this->rtbMessage->ReadOnly = true;
			this->rtbMessage->Size = new System::Drawing::Size(100, 48);
			this->rtbMessage->TabIndex = 4;
			this->rtbMessage->Text = "";
			this->rtbMessage->Visible = false;
			// 
			// MessageBoxExForm
			// 
			this->AutoScale = false;
			this->AutoScaleBaseSize = new System::Drawing::Size(5, 14);
			this->ClientSize = new System::Drawing::Size(322, 224);
			this->Controls->Add(this->rtbMessage);
			this->Controls->Add(this->chbSaveResponse);
			this->Controls->Add(this->panelIcon);
			this->Font = new System::Drawing::Font("Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, (static_cast<unsigned char>(0)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = "MessageBoxExForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
			this->ResumeLayout(false);

		}

		void MessageBoxExForm::OnLoad(EventArgs *e)
		{
			//Reset result
			_result = "";

			this->Size = new Size(_maxWidth, _maxHeight);

			//This is the rectangle in which all items will be layed out
			_maxLayoutWidth = this->ClientSize->Width - LEFT_PADDING - RIGHT_PADDING;
			_maxLayoutHeight = this->ClientSize->Height - TOP_PADDING - BOTTOM_PADDING;

			AddOkButtonIfNoButtonsPresent();
			DisableCloseIfMultipleButtonsAndNoCancelButton();

			SetIconSizeAndVisibility();
			SetMessageSizeAndVisibility();
			SetCheckboxSizeAndVisibility();

			SetOptimumSize();

			LayoutControls();

			CenterForm();

			PlayAlert();

			SelectDefaultButton();

			StartTimerIfTimeoutGreaterThanZero();

			System::Windows::Forms::Form::OnLoad(e);
		}

		bool MessageBoxExForm::ProcessCmdKey(System::Messaging::Message *&msg, Keys *keyData)
		{
			if (static_cast<int>(keyData) == static_cast<int>(Keys::Alt | Keys::F4) && !_allowCancel)
			{
				return true;
			}

			return System::Windows::Forms::Form::ProcessCmdKey(msg, keyData);
		}

		void MessageBoxExForm::OnClosing(CancelEventArgs *e)
		{
			if (_result == "")
			{
				if (_allowCancel)
				{
					_result = _cancelButton->getValue();
				}
				else
				{
					e->Cancel = true;
					return;
				}
			}

			if (timerTimeout != 0)
			{
				timerTimeout->Stop();
			}

			System::Windows::Forms::Form::OnClosing(e);
		}

		void MessageBoxExForm::OnPaint(PaintEventArgs *e)
		{
			System::Windows::Forms::Form::OnPaint(e);

			if (_iconImage != 0)
			{
				e->Graphics->DrawIcon(_iconImage, new Rectangle(panelIcon->Location, new Size(32, 32)));
			}
		}

		Size *MessageBoxExForm::MeasureString(const std::string &str, int maxWidth, Font *font)
		{
			Graphics *g = this->CreateGraphics();
			SizeF *strRectSizeF = g->MeasureString(str, font, maxWidth);
			delete g;

			return new Size(static_cast<int>(ceil(strRectSizeF->Width)), static_cast<int>(ceil(strRectSizeF->Height)));
		}

		Size *MessageBoxExForm::MeasureString(const std::string &str, int maxWidth)
		{
			return MeasureString(str, maxWidth, this->Font);
		}

		std::string MessageBoxExForm::GetLongestButtonText()
		{
			int maxLen = 0;
			std::string maxStr = "";
			for (ArrayList::const_iterator button = _buttons->begin(); button != _buttons->end(); ++button)
			{
				if ((*button)->getText() != "" && (*button)->getText()->length() > maxLen)
				{
					maxLen = (*button)->getText()->length();
					maxStr = (*button)->getText();
				}
			}

			return maxStr;
		}

		void MessageBoxExForm::SetMessageSizeAndVisibility()
		{
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
			if (rtbMessage->Text == 0 || rtbMessage->Text->Trim()->Length == 0)
			{
				rtbMessage->Size = Size::Empty;
				rtbMessage->Visible = false;
			}
			else
			{
				int maxWidth = _maxLayoutWidth;
				if (panelIcon->Size->Width != 0)
				{
					maxWidth = maxWidth - (panelIcon->Size->Width + ICON_MESSAGE_PADDING);
				}

				//We need to account for scroll bar width and height, otherwise for certains
				//kinds of text the scroll bar shows up unnecessarily
				maxWidth = maxWidth - SystemInformation::VerticalScrollBarWidth;
				Size *messageRectSize = MeasureString(rtbMessage->Text, maxWidth);

				messageRectSize->Width += SystemInformation::VerticalScrollBarWidth;
				messageRectSize->Height = __max(panelIcon->Height, messageRectSize->Height) + SystemInformation::HorizontalScrollBarHeight;

				rtbMessage->Size = messageRectSize;
				rtbMessage->Visible = true;
			}
		}

		void MessageBoxExForm::SetIconSizeAndVisibility()
		{
			if (_iconImage == 0)
			{
				panelIcon->Visible = false;
				panelIcon->Size = Size::Empty;
			}
			else
			{
				panelIcon->Size = new Size(32,32);
				panelIcon->Visible = true;
			}
		}

		void MessageBoxExForm::SetCheckboxSizeAndVisibility()
		{
			if (!getAllowSaveResponse())
			{
				chbSaveResponse->Visible = false;
				chbSaveResponse->Size = Size::Empty;
			}
			else
			{
				Size *saveResponseTextSize = MeasureString(chbSaveResponse->Text, _maxLayoutWidth);
				saveResponseTextSize->Width += CHECKBOX_WIDTH;
				chbSaveResponse->Size = saveResponseTextSize;
				chbSaveResponse->Visible = true;
			}
		}

		Size *MessageBoxExForm::GetButtonSize()
		{
			std::string longestButtonText = GetLongestButtonText();
			if (longestButtonText == "")
			{
				//TODO:Handle this case
			}

			Size *buttonTextSize = MeasureString(longestButtonText, _maxLayoutWidth);
			Size *buttonSize = new Size(buttonTextSize->Width + BUTTON_LEFT_PADDING + BUTTON_RIGHT_PADDING, buttonTextSize->Height + BUTTON_TOP_PADDING + BUTTON_BOTTOM_PADDING);

			if (buttonSize->Width < MIN_BUTTON_WIDTH)
				buttonSize->Width = MIN_BUTTON_WIDTH;
			if (buttonSize->Height < MIN_BUTTON_HEIGHT)
				buttonSize->Height = MIN_BUTTON_HEIGHT;

			return buttonSize;
		}

		void MessageBoxExForm::SetStandardIcon(MessageBoxIcon *icon)
		{
			_standardIcon = icon;

			switch (icon)
			{
				case MessageBoxIcon::Asterisk:
					_iconImage = SystemIcons::Asterisk;
					break;
				case MessageBoxIcon::Error:
					_iconImage = SystemIcons::Error;
					break;
				case MessageBoxIcon::Exclamation:
					_iconImage = SystemIcons::Exclamation;
					break;
			//				case MessageBoxIcon.Hand:
			//					_iconImage = SystemIcons.Hand;
			//					break;
			//				case MessageBoxIcon.Information:
			//					_iconImage = SystemIcons.Information;
			//					break;
				case MessageBoxIcon::Question:
					_iconImage = SystemIcons::Question;
					break;
			//				case MessageBoxIcon.Stop:
			//					_iconImage = SystemIcons.Stop;
			//					break;
			//				case MessageBoxIcon.Warning:
			//					_iconImage = SystemIcons.Warning;
			//					break;

				case MessageBoxIcon::None:
//C# TO C++ CONVERTER WARNING: C# to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
					delete _iconImage;
					break;
			}
		}

		void MessageBoxExForm::AddOkButtonIfNoButtonsPresent()
		{
			if (_buttons->Count == 0)
			{
				MessageBoxExButton *okButton = new MessageBoxExButton();
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
				okButton->setText(Ok->ToString());
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
				okButton->setValue(Ok->ToString());

				_buttons->Add(okButton);
			}
		}

		void MessageBoxExForm::CenterForm()
		{
			int x = (SystemInformation::WorkingArea->Width - this->Width) / 2;
			int y = (SystemInformation::WorkingArea->Height - this->Height) / 2;

			this->Location = new Point(x,y);
		}

		void MessageBoxExForm::SetOptimumSize()
		{
			int ncWidth = this->Width - this->ClientSize->Width;
			int ncHeight = this->Height - this->ClientSize->Height;

			int iconAndMessageRowWidth = rtbMessage->Width + ICON_MESSAGE_PADDING + panelIcon->Width;
			int saveResponseRowWidth = chbSaveResponse->Width + static_cast<int>(panelIcon->Width / 2);
			int buttonsRowWidth = GetWidthOfAllButtons();
			int captionWidth = GetCaptionSize()->Width;

			int maxItemWidth = __max(saveResponseRowWidth, __max(iconAndMessageRowWidth, buttonsRowWidth));

			int requiredWidth = LEFT_PADDING + maxItemWidth + RIGHT_PADDING + ncWidth;
			//Since Caption width is not client width, we do the check here
			if (requiredWidth < captionWidth)
				requiredWidth = captionWidth;

			int requiredHeight = TOP_PADDING + __max(rtbMessage->Height,panelIcon->Height) + ITEM_PADDING + chbSaveResponse->Height + ITEM_PADDING + GetButtonSize()->Height + BOTTOM_PADDING + ncHeight;

			//Fix the bug where if the message text is huge then the buttons are overwritten.
			//Incase the required height is more than the max height then adjust that in the
			//message height
			if (requiredHeight > _maxHeight)
			{
				rtbMessage->Height -= requiredHeight - _maxHeight;
			}

			int height = __min(requiredHeight, _maxHeight);
			int width = __min(requiredWidth, _maxWidth);
			this->Size = new Size(width, height);
		}

		int MessageBoxExForm::GetWidthOfAllButtons()
		{
			Size *buttonSize = GetButtonSize();
			int allButtonsWidth = buttonSize->Width*_buttons->Count + BUTTON_PADDING*(_buttons->Count - 1);

			return allButtonsWidth;
		}

		Size *MessageBoxExForm::GetCaptionSize()
		{
			Font *captionFont = GetCaptionFont();
			if (captionFont == 0)
			{
				//some error occured while determining system font
				captionFont = new Font("Tahoma",11);
			}

			int availableWidth = _maxWidth - SystemInformation::CaptionButtonSize->Width - SystemInformation::Border3DSize->Width * 2;
			Size *captionSize = MeasureString(this->Text, availableWidth, captionFont);

			captionSize->Width += SystemInformation::CaptionButtonSize->Width + SystemInformation::Border3DSize->Width * 2;
			return captionSize;
		}

		void MessageBoxExForm::LayoutControls()
		{
			panelIcon->Location = new Point(LEFT_PADDING, TOP_PADDING);
			rtbMessage->Location = new Point(LEFT_PADDING + panelIcon->Width + ICON_MESSAGE_PADDING * (panelIcon->Width == 0 ? 0 : 1), TOP_PADDING);

			chbSaveResponse->Location = new Point(LEFT_PADDING + static_cast<int>(panelIcon->Width / 2), TOP_PADDING + __max(panelIcon->Height, rtbMessage->Height) + ITEM_PADDING);

			Size *buttonSize = GetButtonSize();
			int allButtonsWidth = GetWidthOfAllButtons();

			int firstButtonX = (static_cast<int>(this->ClientSize->Width - allButtonsWidth) / 2);
			int firstButtonY = this->ClientSize->Height - BOTTOM_PADDING - buttonSize->Height;
			Point *nextButtonLocation = new Point(firstButtonX,firstButtonY);

			bool foundDefaultButton = false;
			for (ArrayList::const_iterator button = _buttons->begin(); button != _buttons->end(); ++button)
			{
				Button *buttonCtrl = GetButton(*button, buttonSize, nextButtonLocation);

				if (!foundDefaultButton)
				{
					_defaultButtonControl = buttonCtrl;
					foundDefaultButton = true;
				}

				nextButtonLocation->X += buttonSize->Width + BUTTON_PADDING;
			}
		}

		Button *MessageBoxExForm::GetButton(MessageBoxExButton *button, Size *size, Point *location)
		{
			Button *buttonCtrl = 0;
			if (_buttonControlsTable->ContainsKey(button))
			{
				buttonCtrl = dynamic_cast<Button*>(_buttonControlsTable[button]);
				buttonCtrl->Size = size;
				buttonCtrl->Location = location;
			}
			else
			{
				buttonCtrl = CreateButton(button, size, location);
				_buttonControlsTable[button] = buttonCtrl;
				this->Controls->Add(buttonCtrl);
			}

			return buttonCtrl;
		}

		Button *MessageBoxExForm::CreateButton(MessageBoxExButton *button, Size *size, Point *location)
		{
			Button *buttonCtrl = new Button();
			buttonCtrl->Size = size;
			buttonCtrl->Text = button->getText();
			buttonCtrl->TextAlign = ContentAlignment::MiddleCenter;
			buttonCtrl->FlatStyle = FlatStyle::System;
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Trim' method:
			if (button->getHelpText() != "" && button->getHelpText().Trim()->Length != 0)
			{
				buttonToolTip->SetToolTip(buttonCtrl, button->getHelpText());
			}
			buttonCtrl->Location = location;
			buttonCtrl->Click += new EventHandler(this, &MessageBoxExForm::OnButtonClicked);
			buttonCtrl->Tag = button->getValue();

			return buttonCtrl;
		}

		void MessageBoxExForm::DisableCloseIfMultipleButtonsAndNoCancelButton()
		{
			if (_buttons->Count > 1)
			{
				if (_cancelButton != 0)
					return;

				//See if standard cancel button is present
				for (ArrayList::const_iterator button = _buttons->begin(); button != _buttons->end(); ++button)
				{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
					if ((*button)->getText() == Cancel->ToString() && (*button)->getValue() == Cancel->ToString())
					{
						_cancelButton = *button;
						return;
					}
				}

				//Standard cancel button is not present, Disable
				//close button
				DisableCloseButton(this);
				_allowCancel = false;

			}
			else if (_buttons->Count == 1)
			{
				_cancelButton = dynamic_cast<MessageBoxExButton*>(_buttons[0]);
			}
			else
			{
				//This condition should never get called
				_allowCancel = false;
			}
		}

		void MessageBoxExForm::PlayAlert()
		{
			if (_playAlert)
			{
				if (_standardIcon != MessageBoxIcon::None)
				{
					MessageBeep(static_cast<unsigned int>(_standardIcon));
				}
				else
				{
					MessageBeep(0); //MB_OK
				}
			}
		}

		void MessageBoxExForm::SelectDefaultButton()
		{
			if (_defaultButtonControl != 0)
			{
				_defaultButtonControl->Select();
			}
		}

		void MessageBoxExForm::StartTimerIfTimeoutGreaterThanZero()
		{
			if (_timeout > 0)
			{
				if (timerTimeout == 0)
				{
					timerTimeout = new Timer(this->components);
					timerTimeout->Tick += new EventHandler(this, &MessageBoxExForm::timerTimeout_Tick);
				}

				if (!timerTimeout->Enabled)
				{
					timerTimeout->Interval = _timeout;
					timerTimeout->Start();
				}
			}
		}

		void MessageBoxExForm::SetResultAndClose(const std::string &result)
		{
			_result = result;
			this->DialogResult = System::Windows::Forms::DialogResult::OK;
		}

		void MessageBoxExForm::OnButtonClicked(object *sender, EventArgs *e)
		{
			Button *btn = dynamic_cast<Button*>(sender);
			if (btn == 0 || btn->Tag == 0)
				return;

			std::string result = dynamic_cast<std::string>(btn->Tag);
			SetResultAndClose(result);
		}

		void MessageBoxExForm::timerTimeout_Tick(object *sender, EventArgs *e)
		{
			timerTimeout->Stop();

			switch (_timeoutResult)
			{
				case Default:
					_defaultButtonControl->PerformClick();
					break;

				case Cancel:
					if (_cancelButton != 0)
					{
						SetResultAndClose(_cancelButton->getValue());
					}
					else
					{
						_defaultButtonControl->PerformClick();
					}
					break;

				case getTimeout():
					SetResultAndClose(MessageBoxExResult::Timeout);
					break;
			}
		}

		Font *MessageBoxExForm::GetCaptionFont()
		{

			NONCLIENTMETRICS ncm = NONCLIENTMETRICS();
			ncm.cbSize = Marshal::SizeOf(NONCLIENTMETRICS::typeid);
			try
			{
				bool result = SystemParametersInfo(SPI_GETNONCLIENTMETRICS, ncm.cbSize, ncm, 0);

				if (result)
				{
					return Font::FromLogFont(ncm.lfCaptionFont);

				}
				else
				{
					int lastError = Marshal::GetLastWin32Error();
					return 0;
				}
			}
			catch (std::exception &e1) //ex
			{
				//System.Console.WriteLine(ex.Message);
			}

			return 0;
		}

		void MessageBoxExForm::DisableCloseButton(Form *form)
		{
			try
			{
				EnableMenuItem(GetSystemMenu(form->Handle, false), SC_CLOSE, MF_BYCOMMAND | MF_GRAYED);
			}
			catch (std::exception &e1) //ex
			{
				//System.Console.WriteLine(ex.Message);
			}
		}

		void MessageBoxExForm::InitializeInstanceFields()
		{
			_buttons = new ArrayList();
			_playAlert = true;
			delete _cancelButton;
			delete _defaultButtonControl;
			_allowCancel = true;
			_result = "";
			_standardIcon = MessageBoxIcon::None;
			delete _iconImage;
			delete timerTimeout;
			_timeout = 0;
			_timeoutResult = Default;
			_buttonControlsTable = new Hashtable();
		}
	}
}
