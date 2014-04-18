#include "MeGUI.SourceDetectorConfigWindow.h"




//using namespace System::Collections::Generic;



//using namespace System::Data;



//using namespace System::Text;

//using namespace System::Threading;



namespace MeGUI
{

	SourceDetectorConfigWindow::SourceDetectorConfigWindow()
	{
		InitializeInstanceFields();
		InitializeComponent();
	}

	void SourceDetectorConfigWindow::portionsAllowed_CheckedChanged(QObject *sender, QEvent *e)
	{
		portionThreshold->Enabled = portionsAllowed->Checked;
		maximumPortions->Enabled = portionsAllowed->Checked;
	}

	const SourceDetectorSettings &SourceDetectorConfigWindow::getSettings() const
	{
		SourceDetectorSettings *settings = new SourceDetectorSettings();
		settings->setAnalysePercent(static_cast<int>(analysisPercent->Value));
		settings->setHybridFOPercent(static_cast<int>(hybridFOThreshold->Value));
		settings->setHybridPercent(static_cast<int>(hybridThreshold->Value));
		settings->setMinimumAnalyseSections(static_cast<int>(minAnalyseSections->Value));
		settings->setPortionsAllowed(portionsAllowed->Checked);
		if (settings->getPortionsAllowed())
		{
			settings->setPortionThreshold(static_cast<double>(portionThreshold->Value));
			settings->setMaxPortions(static_cast<int>(maximumPortions->Value));
		}
		settings->setPriority(static_cast<ThreadPriority*>(priority->SelectedIndex));
		return settings;
	}

	void SourceDetectorConfigWindow::setSettings(const SourceDetectorSettings &value)
	{
		analysisPercent->Value = value->getAnalysePercent();
		hybridFOThreshold->Value = value->getHybridFOPercent();
		hybridThreshold->Value = value->getHybridPercent();
		minAnalyseSections->Value = value->getMinimumAnalyseSections();
		portionsAllowed->Checked = value->getPortionsAllowed();
		portionThreshold->Value = static_cast<decimal>(value->getPortionThreshold());
		maximumPortions->Value = value->getMaxPortions();
		priority->SelectedIndex = static_cast<int>(value->getPriority());
	}

	void SourceDetectorConfigWindow::Dispose(bool disposing)
	{
		if (disposing && (components != 0))
		{
			delete components;
		}
		System::Windows::Forms::Form::Dispose(disposing);
	}

	void SourceDetectorConfigWindow::InitializeComponent()
	{
		System::ComponentModel::ComponentResourceManager *resources = new System::ComponentModel::ComponentResourceManager(SourceDetectorConfigWindow::typeid);
		this->analysisPercentLabel = new System::Windows::Forms::Label();
		this->analysisPercent = new System::Windows::Forms::NumericUpDown();
		this->minAnalyseSectionsLabel = new System::Windows::Forms::Label();
		this->minAnalyseSections = new System::Windows::Forms::NumericUpDown();
		this->hybridThresholdLabel = new System::Windows::Forms::Label();
		this->hybridThreshold = new System::Windows::Forms::NumericUpDown();
		this->hybridFOThresholdLabel = new System::Windows::Forms::Label();
		this->hybridFOThreshold = new System::Windows::Forms::NumericUpDown();
		this->portionThresholdLabel = new System::Windows::Forms::Label();
		this->portionThreshold = new System::Windows::Forms::NumericUpDown();
		this->maximumPortionsLabel = new System::Windows::Forms::Label();
		this->maximumPortions = new System::Windows::Forms::NumericUpDown();
		this->portionsAllowed = new System::Windows::Forms::CheckBox();
		this->saveButton = new System::Windows::Forms::Button();
		this->cancelButton = new System::Windows::Forms::Button();
		this->priority = new System::Windows::Forms::ComboBox();
		this->priorityLabel = new System::Windows::Forms::Label();
		this->helpButton1 = new MeGUI::core::gui::HelpButton();
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->analysisPercent))->BeginInit();
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->minAnalyseSections))->BeginInit();
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->hybridThreshold))->BeginInit();
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->hybridFOThreshold))->BeginInit();
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->portionThreshold))->BeginInit();
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->maximumPortions))->BeginInit();
		this->SuspendLayout();
		// 
		// analysisPercentLabel
		// 
		this->analysisPercentLabel->AutoSize = true;
		this->analysisPercentLabel->Location = new System::Drawing::Point(12, 11);
		this->analysisPercentLabel->Name = "analysisPercentLabel";
		this->analysisPercentLabel->Size = new System::Drawing::Size(90, 13);
		this->analysisPercentLabel->TabIndex = 0;
		this->analysisPercentLabel->Text = "Analysis Percent:";
		// 
		// analysisPercent
		// 
		this->analysisPercent->Location = new System::Drawing::Point(213, 7);
		this->analysisPercent->Minimum = decimal(new int[4] {1, 0, 0, 0});
		this->analysisPercent->Name = "analysisPercent";
		this->analysisPercent->Size = new System::Drawing::Size(120, 21);
		this->analysisPercent->TabIndex = 1;
		this->analysisPercent->Value = decimal(new int[4] {1, 0, 0, 0});
		// 
		// minAnalyseSectionsLabel
		// 
		this->minAnalyseSectionsLabel->AutoSize = true;
		this->minAnalyseSectionsLabel->Location = new System::Drawing::Point(12, 37);
		this->minAnalyseSectionsLabel->Name = "minAnalyseSectionsLabel";
		this->minAnalyseSectionsLabel->Size = new System::Drawing::Size(134, 13);
		this->minAnalyseSectionsLabel->TabIndex = 0;
		this->minAnalyseSectionsLabel->Text = "Minimum analysis sections:";
		// 
		// minAnalyseSections
		// 
		this->minAnalyseSections->Location = new System::Drawing::Point(213, 33);
		this->minAnalyseSections->Maximum = decimal(new int[4] {10000, 0, 0, 0});
		this->minAnalyseSections->Minimum = decimal(new int[4] {1, 0, 0, 0});
		this->minAnalyseSections->Name = "minAnalyseSections";
		this->minAnalyseSections->Size = new System::Drawing::Size(120, 21);
		this->minAnalyseSections->TabIndex = 1;
		this->minAnalyseSections->Value = decimal(new int[4] {150, 0, 0, 0});
		// 
		// hybridThresholdLabel
		// 
		this->hybridThresholdLabel->AutoSize = true;
		this->hybridThresholdLabel->Location = new System::Drawing::Point(12, 63);
		this->hybridThresholdLabel->Name = "hybridThresholdLabel";
		this->hybridThresholdLabel->Size = new System::Drawing::Size(114, 13);
		this->hybridThresholdLabel->TabIndex = 0;
		this->hybridThresholdLabel->Text = "Hybrid Threshold (%):";
		// 
		// hybridThreshold
		// 
		this->hybridThreshold->Location = new System::Drawing::Point(213, 59);
		this->hybridThreshold->Minimum = decimal(new int[4] {1, 0, 0, 0});
		this->hybridThreshold->Name = "hybridThreshold";
		this->hybridThreshold->Size = new System::Drawing::Size(120, 21);
		this->hybridThreshold->TabIndex = 1;
		this->hybridThreshold->Value = decimal(new int[4] {5, 0, 0, 0});
		// 
		// hybridFOThresholdLabel
		// 
		this->hybridFOThresholdLabel->AutoSize = true;
		this->hybridFOThresholdLabel->Location = new System::Drawing::Point(12, 89);
		this->hybridFOThresholdLabel->Name = "hybridFOThresholdLabel";
		this->hybridFOThresholdLabel->Size = new System::Drawing::Size(170, 13);
		this->hybridFOThresholdLabel->TabIndex = 0;
		this->hybridFOThresholdLabel->Text = "Hybrid Field Order Threshold (%):";
		// 
		// hybridFOThreshold
		// 
		this->hybridFOThreshold->Location = new System::Drawing::Point(213, 85);
		this->hybridFOThreshold->Minimum = decimal(new int[4] {1, 0, 0, 0});
		this->hybridFOThreshold->Name = "hybridFOThreshold";
		this->hybridFOThreshold->Size = new System::Drawing::Size(120, 21);
		this->hybridFOThreshold->TabIndex = 1;
		this->hybridFOThreshold->Value = decimal(new int[4] {10, 0, 0, 0});
		// 
		// portionThresholdLabel
		// 
		this->portionThresholdLabel->AutoSize = true;
		this->portionThresholdLabel->Location = new System::Drawing::Point(12, 161);
		this->portionThresholdLabel->Name = "portionThresholdLabel";
		this->portionThresholdLabel->Size = new System::Drawing::Size(95, 13);
		this->portionThresholdLabel->TabIndex = 0;
		this->portionThresholdLabel->Text = "Portion Threshold:";
		// 
		// portionThreshold
		// 
		this->portionThreshold->DecimalPlaces = 1;
		this->portionThreshold->Enabled = false;
		this->portionThreshold->Location = new System::Drawing::Point(213, 159);
		this->portionThreshold->Minimum = decimal(new int[4] {1, 0, 0, 0});
		this->portionThreshold->Name = "portionThreshold";
		this->portionThreshold->Size = new System::Drawing::Size(120, 21);
		this->portionThreshold->TabIndex = 1;
		this->portionThreshold->Value = decimal(new int[4] {5, 0, 0, 0});
		// 
		// maximumPortionsLabel
		// 
		this->maximumPortionsLabel->AutoSize = true;
		this->maximumPortionsLabel->Location = new System::Drawing::Point(12, 187);
		this->maximumPortionsLabel->Name = "maximumPortionsLabel";
		this->maximumPortionsLabel->Size = new System::Drawing::Size(150, 13);
		this->maximumPortionsLabel->TabIndex = 0;
		this->maximumPortionsLabel->Text = "Maximum Number of Portions:";
		// 
		// maximumPortions
		// 
		this->maximumPortions->Enabled = false;
		this->maximumPortions->Location = new System::Drawing::Point(213, 185);
		this->maximumPortions->Minimum = decimal(new int[4] {1, 0, 0, 0});
		this->maximumPortions->Name = "maximumPortions";
		this->maximumPortions->Size = new System::Drawing::Size(120, 21);
		this->maximumPortions->TabIndex = 1;
		this->maximumPortions->Value = decimal(new int[4] {5, 0, 0, 0});
		// 
		// portionsAllowed
		// 
		this->portionsAllowed->AutoSize = true;
		this->portionsAllowed->Location = new System::Drawing::Point(15, 136);
		this->portionsAllowed->Name = "portionsAllowed";
		this->portionsAllowed->Size = new System::Drawing::Size(105, 17);
		this->portionsAllowed->TabIndex = 2;
		this->portionsAllowed->Text = "Portions Allowed";
		this->portionsAllowed->UseVisualStyleBackColor = true;
		this->portionsAllowed->CheckedChanged += new System::EventHandler(this, &SourceDetectorConfigWindow::portionsAllowed_CheckedChanged);
		// 
		// saveButton
		// 
		this->saveButton->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right)));
		this->saveButton->DialogResult = System::Windows::Forms::DialogResult::OK;
		this->saveButton->Location = new System::Drawing::Point(189, 211);
		this->saveButton->Name = "saveButton";
		this->saveButton->Size = new System::Drawing::Size(69, 24);
		this->saveButton->TabIndex = 3;
		this->saveButton->Text = "Save";
		this->saveButton->UseVisualStyleBackColor = true;
		// 
		// cancelButton
		// 
		this->cancelButton->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right)));
		this->cancelButton->DialogResult = System::Windows::Forms::DialogResult::Cancel;
		this->cancelButton->Location = new System::Drawing::Point(264, 211);
		this->cancelButton->Name = "cancelButton";
		this->cancelButton->Size = new System::Drawing::Size(69, 24);
		this->cancelButton->TabIndex = 3;
		this->cancelButton->Text = "Cancel";
		this->cancelButton->UseVisualStyleBackColor = true;
		// 
		// priority
		// 
		this->priority->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->priority->Items->AddRange(new object[5] {"Lowest", "Below Normal", "Normal", "Above Normal", "Highest"});
		this->priority->Location = new System::Drawing::Point(213, 111);
		this->priority->Name = "priority";
		this->priority->Size = new System::Drawing::Size(120, 21);
		this->priority->TabIndex = 15;
		// 
		// priorityLabel
		// 
		this->priorityLabel->Location = new System::Drawing::Point(12, 110);
		this->priorityLabel->Name = "priorityLabel";
		this->priorityLabel->Size = new System::Drawing::Size(88, 23);
		this->priorityLabel->TabIndex = 14;
		this->priorityLabel->Text = "Process Priority";
		this->priorityLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
		// 
		// helpButton1
		// 
		this->helpButton1->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) | System::Windows::Forms::AnchorStyles::Left)));
		this->helpButton1->setArticleName("Source Detector");
		this->helpButton1->AutoSize = true;
		this->helpButton1->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
		this->helpButton1->Location = new System::Drawing::Point(15, 212);
		this->helpButton1->Name = "helpButton1";
		this->helpButton1->Size = new System::Drawing::Size(38, 23);
		this->helpButton1->TabIndex = 16;
		// 
		// SourceDetectorConfigWindow
		// 
		this->AutoScaleDimensions = new System::Drawing::SizeF(6, 13);
		this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		this->ClientSize = new System::Drawing::Size(345, 242);
		this->Controls->Add(this->helpButton1);
		this->Controls->Add(this->priority);
		this->Controls->Add(this->priorityLabel);
		this->Controls->Add(this->cancelButton);
		this->Controls->Add(this->saveButton);
		this->Controls->Add(this->portionsAllowed);
		this->Controls->Add(this->maximumPortions);
		this->Controls->Add(this->maximumPortionsLabel);
		this->Controls->Add(this->portionThreshold);
		this->Controls->Add(this->portionThresholdLabel);
		this->Controls->Add(this->hybridFOThreshold);
		this->Controls->Add(this->hybridFOThresholdLabel);
		this->Controls->Add(this->hybridThreshold);
		this->Controls->Add(this->hybridThresholdLabel);
		this->Controls->Add(this->minAnalyseSections);
		this->Controls->Add(this->minAnalyseSectionsLabel);
		this->Controls->Add(this->analysisPercent);
		this->Controls->Add(this->analysisPercentLabel);
		this->Font = new System::Drawing::Font("Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, (static_cast<unsigned char>(0)));
		this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
		this->Icon = (static_cast<System::Drawing::Icon*>(resources->GetObject("$this.Icon")));
		this->MaximizeBox = false;
		this->MinimizeBox = false;
		this->Name = "SourceDetectorConfigWindow";
		this->ShowInTaskbar = false;
		this->Text = "MeGUI - Source Detector Configuration";
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->analysisPercent))->EndInit();
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->minAnalyseSections))->EndInit();
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->hybridThreshold))->EndInit();
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->hybridFOThreshold))->EndInit();
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->portionThreshold))->EndInit();
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->maximumPortions))->EndInit();
		this->ResumeLayout(false);
		this->PerformLayout();

	}

	void SourceDetectorConfigWindow::InitializeInstanceFields()
	{
		delete components;
	}
}
