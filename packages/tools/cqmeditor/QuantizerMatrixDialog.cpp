#include "QuantizerMatrixDialog.h"












//using namespace System::Text;



namespace MeXgui
{

	QuantizerMatrixDialog::QuantizerMatrixDialog()
	{
		//
		// Required for Windows Form Designer support
		//
		InitializeInstanceFields();
		InitializeComponent();
		currentMatrix = new int[16][16];
		jvtI4x4 = new int[][] {{6,13,20,28}, {13,20,28,32}, {20,28,32,37}, {28,32,37,42}};
		jvtP4x4 = new int[][] {{10,14,20,24}, {14,20,24,27}, {20,24,27,30}, {24,27,30,34}};
		jvtI8x8 = new int[][] {{6,10,13,16,18,23,25,27}, {10,11,16,18,23,25,27,29}, {13,16,18,23,25,27,29,31}, {16,18,23,25,27,29,31,33}, {18,23,25,27,29,31,33,36}, {23,25,27,29,31,33,36,38}, {25,27,29,31,33,36,38,40}, {27,29,31,33,36,38,40,42}};
		jvtP8x8 = new int[][] {{9,13,15,17,19,21,22,24}, {13,13,17,19,21,22,24,25}, {15,17,19,21,22,24,25,27}, {17,19,21,22,24,25,27,28}, {19,21,22,24,25,27,28,30}, {21,22,24,25,27,28,30,32}, {22,24,25,27,28,30,32,33}, {24,25,27,28,30,32,33,35}};
		flat4x4 = new int[][] {{16,16,16,16},{16,16,16,16},{16,16,16,16}, {16,16,16,16}};
		flat8x8 = new int[][] {{16,16,16,16,16,16,16,16},{16,16,16,16,16,16,16,16}, {16,16,16,16,16,16,16,16},{16,16,16,16,16,16,16,16}, {16,16,16,16,16,16,16,16},{16,16,16,16,16,16,16,16}, {16,16,16,16,16,16,16,16},{16,16,16,16,16,16,16,16}};
		sb = new StringBuilder();
	}

	void QuantizerMatrixDialog::Dispose(bool disposing)
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

	void QuantizerMatrixDialog::QuantizerMatrixDialog_Load()
	{
		this->predefinedMatrix->SelectedIndex = 0;
	}

	void QuantizerMatrixDialog::InitializeComponent()
	{
		System::ComponentModel::ComponentResourceManager *resources = new System::ComponentModel::ComponentResourceManager(QuantizerMatrixDialog::typeid);
		this->predefinedMatrixLabel = new System::Windows::Forms::Label();
		this->predefinedMatrix = new System::Windows::Forms::ComboBox();
		this->mat1x1 = new System::Windows::Forms::TextBox();
		this->mat1x2 = new System::Windows::Forms::TextBox();
		this->mat1x3 = new System::Windows::Forms::TextBox();
		this->mat1x4 = new System::Windows::Forms::TextBox();
		this->mat2x4 = new System::Windows::Forms::TextBox();
		this->mat2x3 = new System::Windows::Forms::TextBox();
		this->mat2x2 = new System::Windows::Forms::TextBox();
		this->mat2x1 = new System::Windows::Forms::TextBox();
		this->mat4x4 = new System::Windows::Forms::TextBox();
		this->mat4x3 = new System::Windows::Forms::TextBox();
		this->mat4x2 = new System::Windows::Forms::TextBox();
		this->mat4x1 = new System::Windows::Forms::TextBox();
		this->mat3x4 = new System::Windows::Forms::TextBox();
		this->mat3x3 = new System::Windows::Forms::TextBox();
		this->mat3x2 = new System::Windows::Forms::TextBox();
		this->mat3x1 = new System::Windows::Forms::TextBox();
		this->mat8x4 = new System::Windows::Forms::TextBox();
		this->mat8x3 = new System::Windows::Forms::TextBox();
		this->mat8x2 = new System::Windows::Forms::TextBox();
		this->mat8x1 = new System::Windows::Forms::TextBox();
		this->mat7x4 = new System::Windows::Forms::TextBox();
		this->mat7x3 = new System::Windows::Forms::TextBox();
		this->mat7x2 = new System::Windows::Forms::TextBox();
		this->mat7x1 = new System::Windows::Forms::TextBox();
		this->mat6x4 = new System::Windows::Forms::TextBox();
		this->mat6x3 = new System::Windows::Forms::TextBox();
		this->mat6x2 = new System::Windows::Forms::TextBox();
		this->mat6x1 = new System::Windows::Forms::TextBox();
		this->mat5x4 = new System::Windows::Forms::TextBox();
		this->mat5x3 = new System::Windows::Forms::TextBox();
		this->mat5x2 = new System::Windows::Forms::TextBox();
		this->mat5x1 = new System::Windows::Forms::TextBox();
		this->matrixGroupbox = new System::Windows::Forms::GroupBox();
		this->mat8x8 = new System::Windows::Forms::TextBox();
		this->mat8x7 = new System::Windows::Forms::TextBox();
		this->mat8x6 = new System::Windows::Forms::TextBox();
		this->mat8x5 = new System::Windows::Forms::TextBox();
		this->mat7x8 = new System::Windows::Forms::TextBox();
		this->mat7x7 = new System::Windows::Forms::TextBox();
		this->mat7x6 = new System::Windows::Forms::TextBox();
		this->mat7x5 = new System::Windows::Forms::TextBox();
		this->mat6x8 = new System::Windows::Forms::TextBox();
		this->mat6x7 = new System::Windows::Forms::TextBox();
		this->mat6x6 = new System::Windows::Forms::TextBox();
		this->mat6x5 = new System::Windows::Forms::TextBox();
		this->mat5x8 = new System::Windows::Forms::TextBox();
		this->mat5x7 = new System::Windows::Forms::TextBox();
		this->mat5x6 = new System::Windows::Forms::TextBox();
		this->mat5x5 = new System::Windows::Forms::TextBox();
		this->mat4x8 = new System::Windows::Forms::TextBox();
		this->mat4x7 = new System::Windows::Forms::TextBox();
		this->mat4x6 = new System::Windows::Forms::TextBox();
		this->mat4x5 = new System::Windows::Forms::TextBox();
		this->mat3x8 = new System::Windows::Forms::TextBox();
		this->mat3x7 = new System::Windows::Forms::TextBox();
		this->mat3x6 = new System::Windows::Forms::TextBox();
		this->mat3x5 = new System::Windows::Forms::TextBox();
		this->mat2x8 = new System::Windows::Forms::TextBox();
		this->mat2x7 = new System::Windows::Forms::TextBox();
		this->mat2x6 = new System::Windows::Forms::TextBox();
		this->mat2x5 = new System::Windows::Forms::TextBox();
		this->mat1x8 = new System::Windows::Forms::TextBox();
		this->mat1x7 = new System::Windows::Forms::TextBox();
		this->mat1x6 = new System::Windows::Forms::TextBox();
		this->mat1x5 = new System::Windows::Forms::TextBox();
		this->matrixType = new System::Windows::Forms::ComboBox();
		this->matrixSize = new System::Windows::Forms::ComboBox();
		this->matrixSizeLabel = new System::Windows::Forms::Label();
		this->matrixTypeLabel = new System::Windows::Forms::Label();
		this->openFileDialog = new System::Windows::Forms::OpenFileDialog();
		this->saveFileDialog = new System::Windows::Forms::SaveFileDialog();
		this->loadMatrixButton = new QPushButton;
		this->saveMatrixButton = new QPushButton;
		this->operationsGroupbox = new System::Windows::Forms::GroupBox();
		this->okButton = new QPushButton;
		this->helpButton1 = new MeXgui::core::gui::HelpButton();
		this->matrixGroupbox->SuspendLayout();
		this->operationsGroupbox->SuspendLayout();
		this->SuspendLayout();
		// 
		// predefinedMatrixLabel
		// 
		this->predefinedMatrixLabel->Location = new System::Drawing::Point(12, 15);
		this->predefinedMatrixLabel->Name = "predefinedMatrixLabel";
		this->predefinedMatrixLabel->Size = new System::Drawing::Size(72, 13);
		this->predefinedMatrixLabel->TabIndex = 0;
		this->predefinedMatrixLabel->Text = "Select Matrix";
		// 
		// predefinedMatrix
		// 
		this->predefinedMatrix->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->predefinedMatrix->Items->AddRange(new object[4] {"None", "jvt", "flat", "Custom"});
		this->predefinedMatrix->Location = new System::Drawing::Point(90, 12);
		this->predefinedMatrix->Name = "predefinedMatrix";
		this->predefinedMatrix->Size = new System::Drawing::Size(121, 21);
		this->predefinedMatrix->TabIndex = 1;
		this->predefinedMatrix->SelectedIndexChanged += new System::EventHandler(this, &QuantizerMatrixDialog::predefinedMatrix_SelectedIndexChanged);
		// 
		// mat1x1
		// 
		this->mat1x1->Location = new System::Drawing::Point(8, 16);
		this->mat1x1->MaxLength = 3;
		this->mat1x1->Name = "mat1x1";
		this->mat1x1->Size = new System::Drawing::Size(24, 21);
		this->mat1x1->TabIndex = 0;
		this->mat1x1->Text = "16";
		// 
		// mat1x2
		// 
		this->mat1x2->Location = new System::Drawing::Point(32, 16);
		this->mat1x2->MaxLength = 3;
		this->mat1x2->Name = "mat1x2";
		this->mat1x2->Size = new System::Drawing::Size(24, 21);
		this->mat1x2->TabIndex = 1;
		this->mat1x2->Text = "16";
		// 
		// mat1x3
		// 
		this->mat1x3->Location = new System::Drawing::Point(56, 16);
		this->mat1x3->MaxLength = 3;
		this->mat1x3->Name = "mat1x3";
		this->mat1x3->Size = new System::Drawing::Size(24, 21);
		this->mat1x3->TabIndex = 2;
		this->mat1x3->Text = "16";
		// 
		// mat1x4
		// 
		this->mat1x4->Location = new System::Drawing::Point(80, 16);
		this->mat1x4->MaxLength = 3;
		this->mat1x4->Name = "mat1x4";
		this->mat1x4->Size = new System::Drawing::Size(24, 21);
		this->mat1x4->TabIndex = 3;
		this->mat1x4->Text = "16";
		// 
		// mat2x4
		// 
		this->mat2x4->Location = new System::Drawing::Point(80, 38);
		this->mat2x4->MaxLength = 3;
		this->mat2x4->Name = "mat2x4";
		this->mat2x4->Size = new System::Drawing::Size(24, 21);
		this->mat2x4->TabIndex = 11;
		this->mat2x4->Text = "16";
		// 
		// mat2x3
		// 
		this->mat2x3->Location = new System::Drawing::Point(56, 38);
		this->mat2x3->MaxLength = 3;
		this->mat2x3->Name = "mat2x3";
		this->mat2x3->Size = new System::Drawing::Size(24, 21);
		this->mat2x3->TabIndex = 10;
		this->mat2x3->Text = "16";
		// 
		// mat2x2
		// 
		this->mat2x2->Location = new System::Drawing::Point(32, 38);
		this->mat2x2->MaxLength = 3;
		this->mat2x2->Name = "mat2x2";
		this->mat2x2->Size = new System::Drawing::Size(24, 21);
		this->mat2x2->TabIndex = 9;
		this->mat2x2->Text = "16";
		// 
		// mat2x1
		// 
		this->mat2x1->Location = new System::Drawing::Point(8, 38);
		this->mat2x1->MaxLength = 3;
		this->mat2x1->Name = "mat2x1";
		this->mat2x1->Size = new System::Drawing::Size(24, 21);
		this->mat2x1->TabIndex = 8;
		this->mat2x1->Text = "16";
		// 
		// mat4x4
		// 
		this->mat4x4->Location = new System::Drawing::Point(80, 82);
		this->mat4x4->MaxLength = 3;
		this->mat4x4->Name = "mat4x4";
		this->mat4x4->Size = new System::Drawing::Size(24, 21);
		this->mat4x4->TabIndex = 27;
		this->mat4x4->Text = "16";
		// 
		// mat4x3
		// 
		this->mat4x3->Location = new System::Drawing::Point(56, 82);
		this->mat4x3->MaxLength = 3;
		this->mat4x3->Name = "mat4x3";
		this->mat4x3->Size = new System::Drawing::Size(24, 21);
		this->mat4x3->TabIndex = 26;
		this->mat4x3->Text = "16";
		// 
		// mat4x2
		// 
		this->mat4x2->Location = new System::Drawing::Point(32, 82);
		this->mat4x2->MaxLength = 3;
		this->mat4x2->Name = "mat4x2";
		this->mat4x2->Size = new System::Drawing::Size(24, 21);
		this->mat4x2->TabIndex = 25;
		this->mat4x2->Text = "16";
		// 
		// mat4x1
		// 
		this->mat4x1->Location = new System::Drawing::Point(8, 82);
		this->mat4x1->MaxLength = 3;
		this->mat4x1->Name = "mat4x1";
		this->mat4x1->Size = new System::Drawing::Size(24, 21);
		this->mat4x1->TabIndex = 24;
		this->mat4x1->Text = "16";
		// 
		// mat3x4
		// 
		this->mat3x4->Location = new System::Drawing::Point(80, 60);
		this->mat3x4->MaxLength = 3;
		this->mat3x4->Name = "mat3x4";
		this->mat3x4->Size = new System::Drawing::Size(24, 21);
		this->mat3x4->TabIndex = 19;
		this->mat3x4->Text = "16";
		// 
		// mat3x3
		// 
		this->mat3x3->Location = new System::Drawing::Point(56, 60);
		this->mat3x3->MaxLength = 3;
		this->mat3x3->Name = "mat3x3";
		this->mat3x3->Size = new System::Drawing::Size(24, 21);
		this->mat3x3->TabIndex = 18;
		this->mat3x3->Text = "16";
		// 
		// mat3x2
		// 
		this->mat3x2->Location = new System::Drawing::Point(32, 60);
		this->mat3x2->MaxLength = 3;
		this->mat3x2->Name = "mat3x2";
		this->mat3x2->Size = new System::Drawing::Size(24, 21);
		this->mat3x2->TabIndex = 17;
		this->mat3x2->Text = "16";
		// 
		// mat3x1
		// 
		this->mat3x1->Location = new System::Drawing::Point(8, 60);
		this->mat3x1->MaxLength = 3;
		this->mat3x1->Name = "mat3x1";
		this->mat3x1->Size = new System::Drawing::Size(24, 21);
		this->mat3x1->TabIndex = 16;
		this->mat3x1->Text = "16";
		// 
		// mat8x4
		// 
		this->mat8x4->Location = new System::Drawing::Point(80, 170);
		this->mat8x4->MaxLength = 3;
		this->mat8x4->Name = "mat8x4";
		this->mat8x4->Size = new System::Drawing::Size(24, 21);
		this->mat8x4->TabIndex = 59;
		this->mat8x4->Text = "16";
		// 
		// mat8x3
		// 
		this->mat8x3->Location = new System::Drawing::Point(56, 170);
		this->mat8x3->MaxLength = 3;
		this->mat8x3->Name = "mat8x3";
		this->mat8x3->Size = new System::Drawing::Size(24, 21);
		this->mat8x3->TabIndex = 58;
		this->mat8x3->Text = "16";
		// 
		// mat8x2
		// 
		this->mat8x2->Location = new System::Drawing::Point(32, 170);
		this->mat8x2->MaxLength = 3;
		this->mat8x2->Name = "mat8x2";
		this->mat8x2->Size = new System::Drawing::Size(24, 21);
		this->mat8x2->TabIndex = 57;
		this->mat8x2->Text = "16";
		// 
		// mat8x1
		// 
		this->mat8x1->Location = new System::Drawing::Point(8, 170);
		this->mat8x1->MaxLength = 3;
		this->mat8x1->Name = "mat8x1";
		this->mat8x1->Size = new System::Drawing::Size(24, 21);
		this->mat8x1->TabIndex = 56;
		this->mat8x1->Text = "16";
		// 
		// mat7x4
		// 
		this->mat7x4->Location = new System::Drawing::Point(80, 148);
		this->mat7x4->MaxLength = 3;
		this->mat7x4->Name = "mat7x4";
		this->mat7x4->Size = new System::Drawing::Size(24, 21);
		this->mat7x4->TabIndex = 51;
		this->mat7x4->Text = "16";
		// 
		// mat7x3
		// 
		this->mat7x3->Location = new System::Drawing::Point(56, 148);
		this->mat7x3->MaxLength = 3;
		this->mat7x3->Name = "mat7x3";
		this->mat7x3->Size = new System::Drawing::Size(24, 21);
		this->mat7x3->TabIndex = 50;
		this->mat7x3->Text = "16";
		// 
		// mat7x2
		// 
		this->mat7x2->Location = new System::Drawing::Point(32, 148);
		this->mat7x2->MaxLength = 3;
		this->mat7x2->Name = "mat7x2";
		this->mat7x2->Size = new System::Drawing::Size(24, 21);
		this->mat7x2->TabIndex = 49;
		this->mat7x2->Text = "16";
		// 
		// mat7x1
		// 
		this->mat7x1->Location = new System::Drawing::Point(8, 148);
		this->mat7x1->MaxLength = 3;
		this->mat7x1->Name = "mat7x1";
		this->mat7x1->Size = new System::Drawing::Size(24, 21);
		this->mat7x1->TabIndex = 48;
		this->mat7x1->Text = "16";
		// 
		// mat6x4
		// 
		this->mat6x4->Location = new System::Drawing::Point(80, 126);
		this->mat6x4->MaxLength = 3;
		this->mat6x4->Name = "mat6x4";
		this->mat6x4->Size = new System::Drawing::Size(24, 21);
		this->mat6x4->TabIndex = 43;
		this->mat6x4->Text = "16";
		// 
		// mat6x3
		// 
		this->mat6x3->Location = new System::Drawing::Point(56, 126);
		this->mat6x3->MaxLength = 3;
		this->mat6x3->Name = "mat6x3";
		this->mat6x3->Size = new System::Drawing::Size(24, 21);
		this->mat6x3->TabIndex = 42;
		this->mat6x3->Text = "16";
		// 
		// mat6x2
		// 
		this->mat6x2->Location = new System::Drawing::Point(32, 126);
		this->mat6x2->MaxLength = 3;
		this->mat6x2->Name = "mat6x2";
		this->mat6x2->Size = new System::Drawing::Size(24, 21);
		this->mat6x2->TabIndex = 41;
		this->mat6x2->Text = "16";
		// 
		// mat6x1
		// 
		this->mat6x1->Location = new System::Drawing::Point(8, 126);
		this->mat6x1->MaxLength = 3;
		this->mat6x1->Name = "mat6x1";
		this->mat6x1->Size = new System::Drawing::Size(24, 21);
		this->mat6x1->TabIndex = 40;
		this->mat6x1->Text = "16";
		// 
		// mat5x4
		// 
		this->mat5x4->Location = new System::Drawing::Point(80, 104);
		this->mat5x4->MaxLength = 3;
		this->mat5x4->Name = "mat5x4";
		this->mat5x4->Size = new System::Drawing::Size(24, 21);
		this->mat5x4->TabIndex = 35;
		this->mat5x4->Text = "16";
		// 
		// mat5x3
		// 
		this->mat5x3->Location = new System::Drawing::Point(56, 104);
		this->mat5x3->MaxLength = 3;
		this->mat5x3->Name = "mat5x3";
		this->mat5x3->Size = new System::Drawing::Size(24, 21);
		this->mat5x3->TabIndex = 34;
		this->mat5x3->Text = "16";
		// 
		// mat5x2
		// 
		this->mat5x2->Location = new System::Drawing::Point(32, 104);
		this->mat5x2->MaxLength = 3;
		this->mat5x2->Name = "mat5x2";
		this->mat5x2->Size = new System::Drawing::Size(24, 21);
		this->mat5x2->TabIndex = 33;
		this->mat5x2->Text = "16";
		// 
		// mat5x1
		// 
		this->mat5x1->Location = new System::Drawing::Point(8, 104);
		this->mat5x1->MaxLength = 3;
		this->mat5x1->Name = "mat5x1";
		this->mat5x1->Size = new System::Drawing::Size(24, 21);
		this->mat5x1->TabIndex = 32;
		this->mat5x1->Text = "16";
		// 
		// matrixGroupbox
		// 
		this->matrixGroupbox->Controls->Add(this->mat8x8);
		this->matrixGroupbox->Controls->Add(this->mat8x7);
		this->matrixGroupbox->Controls->Add(this->mat8x6);
		this->matrixGroupbox->Controls->Add(this->mat8x5);
		this->matrixGroupbox->Controls->Add(this->mat7x8);
		this->matrixGroupbox->Controls->Add(this->mat7x7);
		this->matrixGroupbox->Controls->Add(this->mat7x6);
		this->matrixGroupbox->Controls->Add(this->mat7x5);
		this->matrixGroupbox->Controls->Add(this->mat6x8);
		this->matrixGroupbox->Controls->Add(this->mat6x7);
		this->matrixGroupbox->Controls->Add(this->mat6x6);
		this->matrixGroupbox->Controls->Add(this->mat6x5);
		this->matrixGroupbox->Controls->Add(this->mat5x8);
		this->matrixGroupbox->Controls->Add(this->mat5x7);
		this->matrixGroupbox->Controls->Add(this->mat5x6);
		this->matrixGroupbox->Controls->Add(this->mat5x5);
		this->matrixGroupbox->Controls->Add(this->mat4x8);
		this->matrixGroupbox->Controls->Add(this->mat4x7);
		this->matrixGroupbox->Controls->Add(this->mat4x6);
		this->matrixGroupbox->Controls->Add(this->mat4x5);
		this->matrixGroupbox->Controls->Add(this->mat3x8);
		this->matrixGroupbox->Controls->Add(this->mat3x7);
		this->matrixGroupbox->Controls->Add(this->mat3x6);
		this->matrixGroupbox->Controls->Add(this->mat3x5);
		this->matrixGroupbox->Controls->Add(this->mat2x8);
		this->matrixGroupbox->Controls->Add(this->mat2x7);
		this->matrixGroupbox->Controls->Add(this->mat2x6);
		this->matrixGroupbox->Controls->Add(this->mat2x5);
		this->matrixGroupbox->Controls->Add(this->mat1x8);
		this->matrixGroupbox->Controls->Add(this->mat1x7);
		this->matrixGroupbox->Controls->Add(this->mat1x6);
		this->matrixGroupbox->Controls->Add(this->mat1x5);
		this->matrixGroupbox->Controls->Add(this->mat5x3);
		this->matrixGroupbox->Controls->Add(this->mat7x2);
		this->matrixGroupbox->Controls->Add(this->mat6x1);
		this->matrixGroupbox->Controls->Add(this->mat6x2);
		this->matrixGroupbox->Controls->Add(this->mat3x4);
		this->matrixGroupbox->Controls->Add(this->mat3x3);
		this->matrixGroupbox->Controls->Add(this->mat7x1);
		this->matrixGroupbox->Controls->Add(this->mat4x4);
		this->matrixGroupbox->Controls->Add(this->mat4x3);
		this->matrixGroupbox->Controls->Add(this->mat4x2);
		this->matrixGroupbox->Controls->Add(this->mat7x3);
		this->matrixGroupbox->Controls->Add(this->mat5x4);
		this->matrixGroupbox->Controls->Add(this->mat3x2);
		this->matrixGroupbox->Controls->Add(this->mat2x3);
		this->matrixGroupbox->Controls->Add(this->mat7x4);
		this->matrixGroupbox->Controls->Add(this->mat4x1);
		this->matrixGroupbox->Controls->Add(this->mat3x1);
		this->matrixGroupbox->Controls->Add(this->mat1x1);
		this->matrixGroupbox->Controls->Add(this->mat8x4);
		this->matrixGroupbox->Controls->Add(this->mat6x3);
		this->matrixGroupbox->Controls->Add(this->mat1x3);
		this->matrixGroupbox->Controls->Add(this->mat1x2);
		this->matrixGroupbox->Controls->Add(this->mat6x4);
		this->matrixGroupbox->Controls->Add(this->mat1x4);
		this->matrixGroupbox->Controls->Add(this->mat2x4);
		this->matrixGroupbox->Controls->Add(this->mat8x3);
		this->matrixGroupbox->Controls->Add(this->mat2x2);
		this->matrixGroupbox->Controls->Add(this->mat2x1);
		this->matrixGroupbox->Controls->Add(this->mat8x2);
		this->matrixGroupbox->Controls->Add(this->mat8x1);
		this->matrixGroupbox->Controls->Add(this->mat5x1);
		this->matrixGroupbox->Controls->Add(this->mat5x2);
		this->matrixGroupbox->Enabled = false;
		this->matrixGroupbox->Location = new System::Drawing::Point(8, 39);
		this->matrixGroupbox->Name = "matrixGroupbox";
		this->matrixGroupbox->Size = new System::Drawing::Size(208, 200);
		this->matrixGroupbox->TabIndex = 2;
		this->matrixGroupbox->TabStop = false;
		this->matrixGroupbox->Text = "Matrix Coefficients";
		// 
		// mat8x8
		// 
		this->mat8x8->Location = new System::Drawing::Point(176, 170);
		this->mat8x8->MaxLength = 3;
		this->mat8x8->Name = "mat8x8";
		this->mat8x8->Size = new System::Drawing::Size(24, 21);
		this->mat8x8->TabIndex = 63;
		this->mat8x8->Text = "16";
		// 
		// mat8x7
		// 
		this->mat8x7->Location = new System::Drawing::Point(152, 170);
		this->mat8x7->MaxLength = 3;
		this->mat8x7->Name = "mat8x7";
		this->mat8x7->Size = new System::Drawing::Size(24, 21);
		this->mat8x7->TabIndex = 62;
		this->mat8x7->Text = "16";
		// 
		// mat8x6
		// 
		this->mat8x6->Location = new System::Drawing::Point(128, 170);
		this->mat8x6->MaxLength = 3;
		this->mat8x6->Name = "mat8x6";
		this->mat8x6->Size = new System::Drawing::Size(24, 21);
		this->mat8x6->TabIndex = 61;
		this->mat8x6->Text = "16";
		// 
		// mat8x5
		// 
		this->mat8x5->Location = new System::Drawing::Point(104, 170);
		this->mat8x5->MaxLength = 3;
		this->mat8x5->Name = "mat8x5";
		this->mat8x5->Size = new System::Drawing::Size(24, 21);
		this->mat8x5->TabIndex = 60;
		this->mat8x5->Text = "16";
		// 
		// mat7x8
		// 
		this->mat7x8->Location = new System::Drawing::Point(176, 148);
		this->mat7x8->MaxLength = 3;
		this->mat7x8->Name = "mat7x8";
		this->mat7x8->Size = new System::Drawing::Size(24, 21);
		this->mat7x8->TabIndex = 55;
		this->mat7x8->Text = "16";
		// 
		// mat7x7
		// 
		this->mat7x7->Location = new System::Drawing::Point(152, 148);
		this->mat7x7->MaxLength = 3;
		this->mat7x7->Name = "mat7x7";
		this->mat7x7->Size = new System::Drawing::Size(24, 21);
		this->mat7x7->TabIndex = 54;
		this->mat7x7->Text = "16";
		// 
		// mat7x6
		// 
		this->mat7x6->Location = new System::Drawing::Point(128, 148);
		this->mat7x6->MaxLength = 3;
		this->mat7x6->Name = "mat7x6";
		this->mat7x6->Size = new System::Drawing::Size(24, 21);
		this->mat7x6->TabIndex = 53;
		this->mat7x6->Text = "16";
		// 
		// mat7x5
		// 
		this->mat7x5->Location = new System::Drawing::Point(104, 148);
		this->mat7x5->MaxLength = 3;
		this->mat7x5->Name = "mat7x5";
		this->mat7x5->Size = new System::Drawing::Size(24, 21);
		this->mat7x5->TabIndex = 52;
		this->mat7x5->Text = "16";
		// 
		// mat6x8
		// 
		this->mat6x8->Location = new System::Drawing::Point(176, 126);
		this->mat6x8->MaxLength = 3;
		this->mat6x8->Name = "mat6x8";
		this->mat6x8->Size = new System::Drawing::Size(24, 21);
		this->mat6x8->TabIndex = 47;
		this->mat6x8->Text = "16";
		// 
		// mat6x7
		// 
		this->mat6x7->Location = new System::Drawing::Point(152, 126);
		this->mat6x7->MaxLength = 3;
		this->mat6x7->Name = "mat6x7";
		this->mat6x7->Size = new System::Drawing::Size(24, 21);
		this->mat6x7->TabIndex = 46;
		this->mat6x7->Text = "16";
		// 
		// mat6x6
		// 
		this->mat6x6->Location = new System::Drawing::Point(128, 126);
		this->mat6x6->MaxLength = 3;
		this->mat6x6->Name = "mat6x6";
		this->mat6x6->Size = new System::Drawing::Size(24, 21);
		this->mat6x6->TabIndex = 45;
		this->mat6x6->Text = "16";
		// 
		// mat6x5
		// 
		this->mat6x5->Location = new System::Drawing::Point(104, 126);
		this->mat6x5->MaxLength = 3;
		this->mat6x5->Name = "mat6x5";
		this->mat6x5->Size = new System::Drawing::Size(24, 21);
		this->mat6x5->TabIndex = 44;
		this->mat6x5->Text = "16";
		// 
		// mat5x8
		// 
		this->mat5x8->Location = new System::Drawing::Point(176, 104);
		this->mat5x8->MaxLength = 3;
		this->mat5x8->Name = "mat5x8";
		this->mat5x8->Size = new System::Drawing::Size(24, 21);
		this->mat5x8->TabIndex = 39;
		this->mat5x8->Text = "16";
		// 
		// mat5x7
		// 
		this->mat5x7->Location = new System::Drawing::Point(152, 104);
		this->mat5x7->MaxLength = 3;
		this->mat5x7->Name = "mat5x7";
		this->mat5x7->Size = new System::Drawing::Size(24, 21);
		this->mat5x7->TabIndex = 38;
		this->mat5x7->Text = "16";
		// 
		// mat5x6
		// 
		this->mat5x6->Location = new System::Drawing::Point(128, 104);
		this->mat5x6->MaxLength = 3;
		this->mat5x6->Name = "mat5x6";
		this->mat5x6->Size = new System::Drawing::Size(24, 21);
		this->mat5x6->TabIndex = 37;
		this->mat5x6->Text = "16";
		// 
		// mat5x5
		// 
		this->mat5x5->Location = new System::Drawing::Point(104, 104);
		this->mat5x5->MaxLength = 3;
		this->mat5x5->Name = "mat5x5";
		this->mat5x5->Size = new System::Drawing::Size(24, 21);
		this->mat5x5->TabIndex = 36;
		this->mat5x5->Text = "16";
		// 
		// mat4x8
		// 
		this->mat4x8->Location = new System::Drawing::Point(176, 82);
		this->mat4x8->MaxLength = 3;
		this->mat4x8->Name = "mat4x8";
		this->mat4x8->Size = new System::Drawing::Size(24, 21);
		this->mat4x8->TabIndex = 31;
		this->mat4x8->Text = "16";
		// 
		// mat4x7
		// 
		this->mat4x7->Location = new System::Drawing::Point(152, 82);
		this->mat4x7->MaxLength = 3;
		this->mat4x7->Name = "mat4x7";
		this->mat4x7->Size = new System::Drawing::Size(24, 21);
		this->mat4x7->TabIndex = 30;
		this->mat4x7->Text = "16";
		// 
		// mat4x6
		// 
		this->mat4x6->Location = new System::Drawing::Point(128, 82);
		this->mat4x6->MaxLength = 3;
		this->mat4x6->Name = "mat4x6";
		this->mat4x6->Size = new System::Drawing::Size(24, 21);
		this->mat4x6->TabIndex = 29;
		this->mat4x6->Text = "16";
		// 
		// mat4x5
		// 
		this->mat4x5->Location = new System::Drawing::Point(104, 82);
		this->mat4x5->MaxLength = 3;
		this->mat4x5->Name = "mat4x5";
		this->mat4x5->Size = new System::Drawing::Size(24, 21);
		this->mat4x5->TabIndex = 28;
		this->mat4x5->Text = "16";
		// 
		// mat3x8
		// 
		this->mat3x8->Location = new System::Drawing::Point(176, 60);
		this->mat3x8->MaxLength = 3;
		this->mat3x8->Name = "mat3x8";
		this->mat3x8->Size = new System::Drawing::Size(24, 21);
		this->mat3x8->TabIndex = 23;
		this->mat3x8->Text = "16";
		// 
		// mat3x7
		// 
		this->mat3x7->Location = new System::Drawing::Point(152, 60);
		this->mat3x7->MaxLength = 3;
		this->mat3x7->Name = "mat3x7";
		this->mat3x7->Size = new System::Drawing::Size(24, 21);
		this->mat3x7->TabIndex = 22;
		this->mat3x7->Text = "16";
		// 
		// mat3x6
		// 
		this->mat3x6->Location = new System::Drawing::Point(128, 60);
		this->mat3x6->MaxLength = 3;
		this->mat3x6->Name = "mat3x6";
		this->mat3x6->Size = new System::Drawing::Size(24, 21);
		this->mat3x6->TabIndex = 21;
		this->mat3x6->Text = "16";
		// 
		// mat3x5
		// 
		this->mat3x5->Location = new System::Drawing::Point(104, 60);
		this->mat3x5->MaxLength = 3;
		this->mat3x5->Name = "mat3x5";
		this->mat3x5->Size = new System::Drawing::Size(24, 21);
		this->mat3x5->TabIndex = 20;
		this->mat3x5->Text = "16";
		// 
		// mat2x8
		// 
		this->mat2x8->Location = new System::Drawing::Point(176, 38);
		this->mat2x8->MaxLength = 3;
		this->mat2x8->Name = "mat2x8";
		this->mat2x8->Size = new System::Drawing::Size(24, 21);
		this->mat2x8->TabIndex = 15;
		this->mat2x8->Text = "16";
		// 
		// mat2x7
		// 
		this->mat2x7->Location = new System::Drawing::Point(152, 38);
		this->mat2x7->MaxLength = 3;
		this->mat2x7->Name = "mat2x7";
		this->mat2x7->Size = new System::Drawing::Size(24, 21);
		this->mat2x7->TabIndex = 14;
		this->mat2x7->Text = "16";
		// 
		// mat2x6
		// 
		this->mat2x6->Location = new System::Drawing::Point(128, 38);
		this->mat2x6->MaxLength = 3;
		this->mat2x6->Name = "mat2x6";
		this->mat2x6->Size = new System::Drawing::Size(24, 21);
		this->mat2x6->TabIndex = 13;
		this->mat2x6->Text = "16";
		// 
		// mat2x5
		// 
		this->mat2x5->Location = new System::Drawing::Point(104, 38);
		this->mat2x5->MaxLength = 3;
		this->mat2x5->Name = "mat2x5";
		this->mat2x5->Size = new System::Drawing::Size(24, 21);
		this->mat2x5->TabIndex = 12;
		this->mat2x5->Text = "16";
		// 
		// mat1x8
		// 
		this->mat1x8->Location = new System::Drawing::Point(176, 16);
		this->mat1x8->MaxLength = 3;
		this->mat1x8->Name = "mat1x8";
		this->mat1x8->Size = new System::Drawing::Size(24, 21);
		this->mat1x8->TabIndex = 7;
		this->mat1x8->Text = "16";
		// 
		// mat1x7
		// 
		this->mat1x7->Location = new System::Drawing::Point(152, 16);
		this->mat1x7->MaxLength = 3;
		this->mat1x7->Name = "mat1x7";
		this->mat1x7->Size = new System::Drawing::Size(24, 21);
		this->mat1x7->TabIndex = 6;
		this->mat1x7->Text = "16";
		// 
		// mat1x6
		// 
		this->mat1x6->Location = new System::Drawing::Point(128, 16);
		this->mat1x6->MaxLength = 3;
		this->mat1x6->Name = "mat1x6";
		this->mat1x6->Size = new System::Drawing::Size(24, 21);
		this->mat1x6->TabIndex = 5;
		this->mat1x6->Text = "16";
		// 
		// mat1x5
		// 
		this->mat1x5->Location = new System::Drawing::Point(104, 16);
		this->mat1x5->MaxLength = 3;
		this->mat1x5->Name = "mat1x5";
		this->mat1x5->Size = new System::Drawing::Size(24, 21);
		this->mat1x5->TabIndex = 4;
		this->mat1x5->Text = "16";
		// 
		// matrixType
		// 
		this->matrixType->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->matrixType->Items->AddRange(new object[2] {"Global", "Luma/Chroma"});
		this->matrixType->Location = new System::Drawing::Point(72, 47);
		this->matrixType->Name = "matrixType";
		this->matrixType->Size = new System::Drawing::Size(98, 21);
		this->matrixType->TabIndex = 0;
		this->matrixType->SelectedIndexChanged += new System::EventHandler(this, &QuantizerMatrixDialog::matrixType_SelectedIndexChanged);
		// 
		// matrixSize
		// 
		this->matrixSize->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->matrixSize->Items->AddRange(new object[2] {"4x4", "8x8"});
		this->matrixSize->Location = new System::Drawing::Point(72, 20);
		this->matrixSize->Name = "matrixSize";
		this->matrixSize->Size = new System::Drawing::Size(98, 21);
		this->matrixSize->TabIndex = 1;
		this->matrixSize->SelectedIndexChanged += new System::EventHandler(this, &QuantizerMatrixDialog::matrixSize_SelectedIndexChanged);
		// 
		// matrixSizeLabel
		// 
		this->matrixSizeLabel->Location = new System::Drawing::Point(16, 23);
		this->matrixSizeLabel->Name = "matrixSizeLabel";
		this->matrixSizeLabel->Size = new System::Drawing::Size(48, 23);
		this->matrixSizeLabel->TabIndex = 2;
		this->matrixSizeLabel->Text = "Size";
		// 
		// matrixTypeLabel
		// 
		this->matrixTypeLabel->Location = new System::Drawing::Point(16, 50);
		this->matrixTypeLabel->Name = "matrixTypeLabel";
		this->matrixTypeLabel->Size = new System::Drawing::Size(48, 23);
		this->matrixTypeLabel->TabIndex = 3;
		this->matrixTypeLabel->Text = "Type";
		// 
		// openFileDialog
		// 
		this->openFileDialog->DefaultExt = "txt";
		this->openFileDialog->Filter = "Quantizer Matrix Files (*.cfg)|*.cfg|All Files (*.*)|*.*";
		// 
		// saveFileDialog
		// 
		this->saveFileDialog->DefaultExt = "txt";
		this->saveFileDialog->Filter = "Quantizer Matrix Files (*.cfg)|*.cfg|All Files (*.*)|*.*";
		// 
		// loadMatrixButton
		// 
		this->loadMatrixButton->Location = new System::Drawing::Point(305, 126);
		this->loadMatrixButton->Name = "loadMatrixButton";
		this->loadMatrixButton->Size = new System::Drawing::Size(48, 23);
		this->loadMatrixButton->TabIndex = 4;
		this->loadMatrixButton->Text = "Load";
		this->loadMatrixButton->Click += new System::EventHandler(this, &QuantizerMatrixDialog::loadMatrixButton_Click);
		// 
		// saveMatrixButton
		// 
		this->saveMatrixButton->Location = new System::Drawing::Point(359, 126);
		this->saveMatrixButton->Name = "saveMatrixButton";
		this->saveMatrixButton->Size = new System::Drawing::Size(48, 23);
		this->saveMatrixButton->TabIndex = 5;
		this->saveMatrixButton->Text = "Save";
		this->saveMatrixButton->Click += new System::EventHandler(this, &QuantizerMatrixDialog::saveMatrixButton_Click);
		// 
		// operationsGroupbox
		// 
		this->operationsGroupbox->Controls->Add(this->matrixSize);
		this->operationsGroupbox->Controls->Add(this->matrixType);
		this->operationsGroupbox->Controls->Add(this->matrixTypeLabel);
		this->operationsGroupbox->Controls->Add(this->matrixSizeLabel);
		this->operationsGroupbox->Enabled = false;
		this->operationsGroupbox->Location = new System::Drawing::Point(224, 39);
		this->operationsGroupbox->Name = "operationsGroupbox";
		this->operationsGroupbox->Size = new System::Drawing::Size(183, 81);
		this->operationsGroupbox->TabIndex = 3;
		this->operationsGroupbox->TabStop = false;
		this->operationsGroupbox->Text = "Operations";
		// 
		// okButton
		// 
		this->okButton->DialogResult = System::Windows::Forms::DialogResult::OK;
		this->okButton->Location = new System::Drawing::Point(375, 245);
		this->okButton->Name = "okButton";
		this->okButton->Size = new System::Drawing::Size(32, 23);
		this->okButton->TabIndex = 7;
		this->okButton->Text = "OK";
		// 
		// helpButton1
		// 
		this->helpButton1->setArticleName("x264 Quantizer matrix editor");
		this->helpButton1->AutoSize = true;
		this->helpButton1->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
		this->helpButton1->Location = new System::Drawing::Point(8, 245);
		this->helpButton1->Name = "helpButton1";
		this->helpButton1->Size = new System::Drawing::Size(38, 23);
		this->helpButton1->TabIndex = 6;
		// 
		// QuantizerMatrixDialog
		// 
		this->AutoScaleBaseSize = new System::Drawing::Size(5, 14);
		this->CancelButton = this->okButton;
		this->ClientSize = new System::Drawing::Size(415, 277);
		this->Controls->Add(this->helpButton1);
		this->Controls->Add(this->okButton);
		this->Controls->Add(this->operationsGroupbox);
		this->Controls->Add(this->matrixGroupbox);
		this->Controls->Add(this->predefinedMatrix);
		this->Controls->Add(this->predefinedMatrixLabel);
		this->Controls->Add(this->loadMatrixButton);
		this->Controls->Add(this->saveMatrixButton);
		this->Font = new System::Drawing::Font("Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, (static_cast<unsigned char>(0)));
		this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
		this->Icon = (static_cast<System::Drawing::Icon*>(resources->GetObject("$this.Icon")));
		this->MaximizeBox = false;
		this->Name = "QuantizerMatrixDialog";
		this->Text = "MeXgui - Quantizer Matrix Editor";
		this->Load += new System::EventHandler(this, &QuantizerMatrixDialog::QuantizerMatrixDialog_Load);
		this->matrixGroupbox->ResumeLayout(false);
		this->matrixGroupbox->PerformLayout();
		this->operationsGroupbox->ResumeLayout(false);
		this->ResumeLayout(false);
		this->PerformLayout();

	}

	void QuantizerMatrixDialog::blankMatrix()
	{
		mat1x5->Text = "0";
		mat1x6->Text = "0";
		mat1x7->Text = "0";
		mat1x8->Text = "0";
		mat2x5->Text = "0";
		mat2x6->Text = "0";
		mat2x7->Text = "0";
		mat2x8->Text = "0";
		mat3x5->Text = "0";
		mat3x6->Text = "0";
		mat3x7->Text = "0";
		mat3x8->Text = "0";
		mat4x5->Text = "0";
		mat4x6->Text = "0";
		mat4x7->Text = "0";
		mat4x8->Text = "0";
		mat5x1->Text = "0";
		mat5x2->Text = "0";
		mat5x3->Text = "0";
		mat5x4->Text = "0";
		mat5x5->Text = "0";
		mat5x6->Text = "0";
		mat5x7->Text = "0";
		mat5x8->Text = "0";
		mat6x1->Text = "0";
		mat6x2->Text = "0";
		mat6x3->Text = "0";
		mat6x4->Text = "0";
		mat6x5->Text = "0";
		mat6x6->Text = "0";
		mat6x7->Text = "0";
		mat6x8->Text = "0";
		mat7x1->Text = "0";
		mat7x2->Text = "0";
		mat7x3->Text = "0";
		mat7x4->Text = "0";
		mat7x5->Text = "0";
		mat7x6->Text = "0";
		mat7x7->Text = "0";
		mat7x8->Text = "0";
		mat8x1->Text = "0";
		mat8x2->Text = "0";
		mat8x3->Text = "0";
		mat8x4->Text = "0";
		mat8x5->Text = "0";
		mat8x6->Text = "0";
		mat8x7->Text = "0";
		mat8x8->Text = "0";

		mat1x1->Text = "0";
		mat1x2->Text = "0";
		mat1x3->Text = "0";
		mat1x4->Text = "0";
		mat2x1->Text = "0";
		mat2x2->Text = "0";
		mat2x3->Text = "0";
		mat2x4->Text = "0";
		mat3x1->Text = "0";
		mat3x2->Text = "0";
		mat3x3->Text = "0";
		mat3x4->Text = "0";
		mat4x1->Text = "0";
		mat4x2->Text = "0";
		mat4x3->Text = "0";
		mat4x4->Text = "0";
	}

	void QuantizerMatrixDialog::loadMatrix(int matrix[][])
	{
		switch (sizeof(matrix) / sizeof(matrix[0]))
		{
			case 64:
				mat1x5->Text = StringConverterHelper::toString(matrix[0][4]);
				mat1x6->Text = StringConverterHelper::toString(matrix[0][5]);
				mat1x7->Text = StringConverterHelper::toString(matrix[0][6]);
				mat1x8->Text = StringConverterHelper::toString(matrix[0][7]);
				mat2x5->Text = StringConverterHelper::toString(matrix[1][4]);
				mat2x6->Text = StringConverterHelper::toString(matrix[1][5]);
				mat2x7->Text = StringConverterHelper::toString(matrix[1][6]);
				mat2x8->Text = StringConverterHelper::toString(matrix[1][7]);
				mat3x5->Text = StringConverterHelper::toString(matrix[2][4]);
				mat3x6->Text = StringConverterHelper::toString(matrix[2][5]);
				mat3x7->Text = StringConverterHelper::toString(matrix[2][6]);
				mat3x8->Text = StringConverterHelper::toString(matrix[2][7]);
				mat4x5->Text = StringConverterHelper::toString(matrix[3][4]);
				mat4x6->Text = StringConverterHelper::toString(matrix[3][5]);
				mat4x7->Text = StringConverterHelper::toString(matrix[3][6]);
				mat4x8->Text = StringConverterHelper::toString(matrix[3][7]);
				mat5x1->Text = StringConverterHelper::toString(matrix[4][0]);
				mat5x2->Text = StringConverterHelper::toString(matrix[4][1]);
				mat5x3->Text = StringConverterHelper::toString(matrix[4][2]);
				mat5x4->Text = StringConverterHelper::toString(matrix[4][3]);
				mat5x5->Text = StringConverterHelper::toString(matrix[4][4]);
				mat5x6->Text = StringConverterHelper::toString(matrix[4][5]);
				mat5x7->Text = StringConverterHelper::toString(matrix[4][6]);
				mat5x8->Text = StringConverterHelper::toString(matrix[4][7]);
				mat6x1->Text = StringConverterHelper::toString(matrix[4][0]);
				mat6x2->Text = StringConverterHelper::toString(matrix[5][1]);
				mat6x3->Text = StringConverterHelper::toString(matrix[5][2]);
				mat6x4->Text = StringConverterHelper::toString(matrix[5][3]);
				mat6x5->Text = StringConverterHelper::toString(matrix[5][4]);
				mat6x6->Text = StringConverterHelper::toString(matrix[5][5]);
				mat6x7->Text = StringConverterHelper::toString(matrix[5][6]);
				mat6x8->Text = StringConverterHelper::toString(matrix[5][7]);
				mat7x1->Text = StringConverterHelper::toString(matrix[6][0]);
				mat7x2->Text = StringConverterHelper::toString(matrix[6][1]);
				mat7x3->Text = StringConverterHelper::toString(matrix[6][2]);
				mat7x4->Text = StringConverterHelper::toString(matrix[6][3]);
				mat7x5->Text = StringConverterHelper::toString(matrix[6][4]);
				mat7x6->Text = StringConverterHelper::toString(matrix[6][5]);
				mat7x7->Text = StringConverterHelper::toString(matrix[6][6]);
				mat7x8->Text = StringConverterHelper::toString(matrix[6][7]);
				mat8x1->Text = StringConverterHelper::toString(matrix[7][0]);
				mat8x2->Text = StringConverterHelper::toString(matrix[7][1]);
				mat8x3->Text = StringConverterHelper::toString(matrix[7][2]);
				mat8x4->Text = StringConverterHelper::toString(matrix[7][3]);
				mat8x5->Text = StringConverterHelper::toString(matrix[7][4]);
				mat8x6->Text = StringConverterHelper::toString(matrix[7][5]);
				mat8x7->Text = StringConverterHelper::toString(matrix[7][6]);
				mat8x8->Text = StringConverterHelper::toString(matrix[7][7]);

				mat1x1->Text = StringConverterHelper::toString(matrix[0][0]);
				mat1x2->Text = StringConverterHelper::toString(matrix[0][1]);
				mat1x3->Text = StringConverterHelper::toString(matrix[0][2]);
				mat1x4->Text = StringConverterHelper::toString(matrix[0][3]);
				mat2x1->Text = StringConverterHelper::toString(matrix[1][0]);
				mat2x2->Text = StringConverterHelper::toString(matrix[1][1]);
				mat2x3->Text = StringConverterHelper::toString(matrix[1][2]);
				mat2x4->Text = StringConverterHelper::toString(matrix[1][3]);
				mat3x1->Text = StringConverterHelper::toString(matrix[2][0]);
				mat3x2->Text = StringConverterHelper::toString(matrix[2][1]);
				mat3x3->Text = StringConverterHelper::toString(matrix[2][2]);
				mat3x4->Text = StringConverterHelper::toString(matrix[2][3]);
				mat4x1->Text = StringConverterHelper::toString(matrix[3][0]);
				mat4x2->Text = StringConverterHelper::toString(matrix[3][1]);
				mat4x3->Text = StringConverterHelper::toString(matrix[3][2]);
				mat4x4->Text = StringConverterHelper::toString(matrix[3][3]);
				break;
			case 16:
				this->blankMatrix();
				mat1x1->Text = StringConverterHelper::toString(matrix[0][0]);
				mat1x2->Text = StringConverterHelper::toString(matrix[0][1]);
				mat1x3->Text = StringConverterHelper::toString(matrix[0][2]);
				mat1x4->Text = StringConverterHelper::toString(matrix[0][3]);
				mat2x1->Text = StringConverterHelper::toString(matrix[1][0]);
				mat2x2->Text = StringConverterHelper::toString(matrix[1][1]);
				mat2x3->Text = StringConverterHelper::toString(matrix[1][2]);
				mat2x4->Text = StringConverterHelper::toString(matrix[1][3]);
				mat3x1->Text = StringConverterHelper::toString(matrix[2][0]);
				mat3x2->Text = StringConverterHelper::toString(matrix[2][1]);
				mat3x3->Text = StringConverterHelper::toString(matrix[2][2]);
				mat3x4->Text = StringConverterHelper::toString(matrix[2][3]);
				mat4x1->Text = StringConverterHelper::toString(matrix[3][0]);
				mat4x2->Text = StringConverterHelper::toString(matrix[3][1]);
				mat4x3->Text = StringConverterHelper::toString(matrix[3][2]);
				mat4x4->Text = StringConverterHelper::toString(matrix[3][3]);
				break;
		}
	}

	int **QuantizerMatrixDialog::getCurrentMatrix()
	{
		if (matrixSize->SelectedIndex == 0) // 4x4
		{
			int retval[4][4];
			if (!mat1x1->Text->Equals(""))
				retval[0][0] = int::Parse(mat1x1->Text);
			if (!mat1x2->Text->Equals(""))
				retval[0][1] = int::Parse(mat1x2->Text);
			if (!mat1x3->Text->Equals(""))
				retval[0][2] = int::Parse(mat1x3->Text);
			if (!mat1x4->Text->Equals(""))
				retval[0][3] = int::Parse(mat1x4->Text);
			if (!mat2x1->Text->Equals(""))
				retval[1][0] = int::Parse(mat2x1->Text);
			if (!mat2x2->Text->Equals(""))
				retval[1][1] = int::Parse(mat2x2->Text);
			if (!mat2x3->Text->Equals(""))
				retval[1][2] = int::Parse(mat2x3->Text);
			if (!mat2x4->Text->Equals(""))
				retval[1][3] = int::Parse(mat2x4->Text);
			if (!mat3x1->Text->Equals(""))
				retval[2][0] = int::Parse(mat3x1->Text);
			if (!mat3x2->Text->Equals(""))
				retval[2][1] = int::Parse(mat3x2->Text);
			if (!mat3x3->Text->Equals(""))
				retval[2][2] = int::Parse(mat3x3->Text);
			if (!mat3x4->Text->Equals(""))
				retval[2][3] = int::Parse(mat3x4->Text);
			if (!mat4x1->Text->Equals(""))
				retval[3][0] = int::Parse(mat4x1->Text);
			if (!mat4x2->Text->Equals(""))
				retval[3][1] = int::Parse(mat4x2->Text);
			if (!mat4x3->Text->Equals(""))
				retval[3][2] = int::Parse(mat4x3->Text);
			if (!mat4x4->Text->Equals(""))
				retval[3][3] = int::Parse(mat4x4->Text);
			return retval;
		}
		else // 8x8 matrix
		{
			int retval[8][8];
			if (!mat1x1->Text->Equals(""))
				retval[0][0] = int::Parse(mat1x1->Text);
			if (!mat1x2->Text->Equals(""))
				retval[0][1] = int::Parse(mat1x2->Text);
			if (!mat1x3->Text->Equals(""))
				retval[0][2] = int::Parse(mat1x3->Text);
			if (!mat1x4->Text->Equals(""))
				retval[0][3] = int::Parse(mat1x4->Text);
			if (!mat1x5->Text->Equals(""))
				retval[0][4] = int::Parse(mat1x5->Text);
			if (!mat1x6->Text->Equals(""))
				retval[0][5] = int::Parse(mat1x6->Text);
			if (!mat1x7->Text->Equals(""))
				retval[0][6] = int::Parse(mat1x7->Text);
			if (!mat1x8->Text->Equals(""))
				retval[0][7] = int::Parse(mat1x8->Text);
			if (!mat2x1->Text->Equals(""))
				retval[1][0] = int::Parse(mat2x1->Text);
			if (!mat2x2->Text->Equals(""))
				retval[1][1] = int::Parse(mat2x2->Text);
			if (!mat2x3->Text->Equals(""))
				retval[1][2] = int::Parse(mat2x3->Text);
			if (!mat2x4->Text->Equals(""))
				retval[1][3] = int::Parse(mat2x4->Text);
			if (!mat2x5->Text->Equals(""))
				retval[1][4] = int::Parse(mat2x5->Text);
			if (!mat2x6->Text->Equals(""))
				retval[1][5] = int::Parse(mat2x6->Text);
			if (!mat2x7->Text->Equals(""))
				retval[1][6] = int::Parse(mat2x7->Text);
			if (!mat2x8->Text->Equals(""))
				retval[1][7] = int::Parse(mat2x8->Text);
			if (!mat3x1->Text->Equals(""))
				retval[2][0] = int::Parse(mat3x1->Text);
			if (!mat3x2->Text->Equals(""))
				retval[2][1] = int::Parse(mat3x2->Text);
			if (!mat3x3->Text->Equals(""))
				retval[2][2] = int::Parse(mat3x3->Text);
			if (!mat3x4->Text->Equals(""))
				retval[2][3] = int::Parse(mat3x4->Text);
			if (!mat3x5->Text->Equals(""))
				retval[2][4] = int::Parse(mat3x5->Text);
			if (!mat3x6->Text->Equals(""))
				retval[2][5] = int::Parse(mat3x6->Text);
			if (!mat3x7->Text->Equals(""))
				retval[2][6] = int::Parse(mat3x7->Text);
			if (!mat3x8->Text->Equals(""))
				retval[2][7] = int::Parse(mat3x8->Text);
			if (!mat4x1->Text->Equals(""))
				retval[3][0] = int::Parse(mat4x1->Text);
			if (!mat4x2->Text->Equals(""))
				retval[3][1] = int::Parse(mat4x2->Text);
			if (!mat4x3->Text->Equals(""))
				retval[3][2] = int::Parse(mat4x3->Text);
			if (!mat4x4->Text->Equals(""))
				retval[3][3] = int::Parse(mat4x4->Text);
			if (!mat4x5->Text->Equals(""))
				retval[3][4] = int::Parse(mat4x5->Text);
			if (!mat4x6->Text->Equals(""))
				retval[3][5] = int::Parse(mat4x6->Text);
			if (!mat4x7->Text->Equals(""))
				retval[3][6] = int::Parse(mat4x7->Text);
			if (!mat4x8->Text->Equals(""))
				retval[3][7] = int::Parse(mat4x8->Text);
			if (!mat5x1->Text->Equals(""))
				retval[4][0] = int::Parse(mat5x1->Text);
			if (!mat5x2->Text->Equals(""))
				retval[4][1] = int::Parse(mat5x2->Text);
			if (!mat5x3->Text->Equals(""))
				retval[4][2] = int::Parse(mat5x3->Text);
			if (!mat5x4->Text->Equals(""))
				retval[4][3] = int::Parse(mat5x4->Text);
			if (!mat5x5->Text->Equals(""))
				retval[4][4] = int::Parse(mat5x5->Text);
			if (!mat5x6->Text->Equals(""))
				retval[4][5] = int::Parse(mat5x6->Text);
			if (!mat5x7->Text->Equals(""))
				retval[4][6] = int::Parse(mat5x7->Text);
			if (!mat5x8->Text->Equals(""))
				retval[4][7] = int::Parse(mat5x8->Text);
			if (!mat6x1->Text->Equals(""))
				retval[5][0] = int::Parse(mat6x1->Text);
			if (!mat6x2->Text->Equals(""))
				retval[5][1] = int::Parse(mat6x2->Text);
			if (!mat6x3->Text->Equals(""))
				retval[5][2] = int::Parse(mat6x3->Text);
			if (!mat6x4->Text->Equals(""))
				retval[5][3] = int::Parse(mat6x4->Text);
			if (!mat6x5->Text->Equals(""))
				retval[5][4] = int::Parse(mat6x5->Text);
			if (!mat6x6->Text->Equals(""))
				retval[5][5] = int::Parse(mat6x6->Text);
			if (!mat6x7->Text->Equals(""))
				retval[5][6] = int::Parse(mat6x7->Text);
			if (!mat6x8->Text->Equals(""))
				retval[5][7] = int::Parse(mat6x8->Text);
			if (!mat7x1->Text->Equals(""))
				retval[6][0] = int::Parse(mat7x1->Text);
			if (!mat7x3->Text->Equals(""))
				retval[6][1] = int::Parse(mat7x2->Text);
			if (!mat7x4->Text->Equals(""))
				retval[6][2] = int::Parse(mat7x3->Text);
			if (!mat7x4->Text->Equals(""))
				retval[6][3] = int::Parse(mat7x4->Text);
			if (!mat7x5->Text->Equals(""))
				retval[6][4] = int::Parse(mat7x5->Text);
			if (!mat7x6->Text->Equals(""))
				retval[6][5] = int::Parse(mat7x6->Text);
			if (!mat7x7->Text->Equals(""))
				retval[6][6] = int::Parse(mat7x7->Text);
			if (!mat7x8->Text->Equals(""))
				retval[6][7] = int::Parse(mat7x8->Text);
			if (!mat8x1->Text->Equals(""))
				retval[7][0] = int::Parse(mat8x1->Text);
			if (!mat8x2->Text->Equals(""))
				retval[7][1] = int::Parse(mat8x2->Text);
			if (!mat8x3->Text->Equals(""))
				retval[7][2] = int::Parse(mat8x3->Text);
			if (!mat8x4->Text->Equals(""))
				retval[7][3] = int::Parse(mat8x4->Text);
			if (!mat8x5->Text->Equals(""))
				retval[7][4] = int::Parse(mat8x5->Text);
			if (!mat8x6->Text->Equals(""))
				retval[7][5] = int::Parse(mat8x6->Text);
			if (!mat8x7->Text->Equals(""))
				retval[7][6] = int::Parse(mat8x7->Text);
			if (!mat8x8->Text->Equals(""))
				retval[7][7] = int::Parse(mat8x8->Text);
			return retval;
		}
	}

	void QuantizerMatrixDialog::predefinedMatrix_SelectedIndexChanged()
	{
		doEvents = false; // block other event handlers until everything is set up
		switch (predefinedMatrix->SelectedIndex)
		{
			case 0: // none
				disableMatrix();
				matrixGroupbox->Enabled = false;
				operationsGroupbox->Enabled = false;
				break;
			case 1: // jvt
				disableMatrix();
				this->I8x8 = this->jvtI8x8;
				this->P8x8 = this->jvtP8x8;
				this->I4x4L = this->jvtI4x4;
				this->I4x4CU = this->jvtI4x4;
				this->I4x4CY = this->jvtI4x4;
				this->P4x4L = this->jvtP4x4;
				this->P4x4CU = this->jvtP4x4;
				this->P4x4CY = this->jvtP4x4;
				matrixGroupbox->Enabled = true;
				operationsGroupbox->Enabled = true;
				matrixSize->Enabled = true;
				matrixSize->SelectedIndex = 0;
				matrixType->Enabled = true;
				matrixType->SelectedIndex = 0;
				this->loadMatrix(I4x4L);
				this->i4x4Matrix();
				break;
			case 2: // flat
				disableMatrix();
				this->I8x8 = this->flat8x8;
				this->P8x8 = this->flat8x8;
				this->I4x4L = this->flat4x4;
				this->I4x4CU = this->flat4x4;
				this->I4x4CY = this->flat4x4;
				this->P4x4L = this->flat4x4;
				this->P4x4CU = this->flat4x4;
				this->P4x4CY = this->flat4x4;
				matrixGroupbox->Enabled = true;
				operationsGroupbox->Enabled = true;
				matrixSize->Enabled = true;
				matrixSize->SelectedIndex = 0;
				matrixType->Enabled = true;
				matrixType->SelectedIndex = 0;
				this->loadMatrix(I4x4L);
				this->i4x4Matrix();
				break;
			case 3: // custom
				matrixGroupbox->Enabled = true;
				operationsGroupbox->Enabled = true;
				matrixSize->Enabled = true;
				matrixSize->SelectedIndex = 0;
				matrixType->Enabled = true;
				matrixType->SelectedIndex = 0;
				enable4x4Matrix();
				this->I8x8 = this->flat8x8;
				this->P8x8 = this->flat8x8;
				this->I4x4L = this->flat4x4;
				this->I4x4CU = this->flat4x4;
				this->I4x4CY = this->flat4x4;
				this->P4x4L = this->flat4x4;
				this->P4x4CU = this->flat4x4;
				this->P4x4CY = this->flat4x4;
				this->i4x4Matrix();
				break;
		}
		doEvents = true;
	}

	void QuantizerMatrixDialog::matrixSize_SelectedIndexChanged()
	{
		if (doEvents)
		{
			if (predefinedMatrix->SelectedIndex == 3) // save previous matrix before showing the new one
				this->saveMatrix(this->currentConfig);
			MatrixConfig conf = getCurrentConfig();
			if (matrixSize->SelectedIndex == 0) // 4x4
			{
				if (predefinedMatrix->SelectedIndex == 3) // custom 4x4
					enable4x4Matrix();
				i4x4Matrix();
				loadMatrix(this->I4x4L);
			}
			else if (matrixSize->SelectedIndex == 1) // 8x8
			{
				if (predefinedMatrix->SelectedIndex == 3)
					enable8x8Matrix();
				matrixType->Items->Clear();
				matrixType->Items->Add("I");
				matrixType->Items->Add("P");
				matrixType->SelectedIndex = 0;
				loadMatrix(this->I8x8);
			}
		}
		this->currentConfig = this->getCurrentConfig();
	}

	void QuantizerMatrixDialog::matrixType_SelectedIndexChanged()
	{
		if (doEvents)
		{
			if (predefinedMatrix->SelectedIndex == 3) // save previous matrix before showing the new one
				this->saveMatrix(this->currentConfig);
			if (matrixSize->SelectedIndex == 0) // 4x4
			{
				switch (matrixType->SelectedIndex)
				{
					case 0: // I luma
						loadMatrix(this->I4x4L);
						break;
					case 1:
						loadMatrix(this->I4x4CU);
						break;
					case 2:
						loadMatrix(this->I4x4CY);
						break;
					case 3:
						loadMatrix(this->P4x4L);
						break;
					case 4:
						loadMatrix(this->P4x4CU);
						break;
					case 5:
						loadMatrix(this->P4x4CY);
						break;
				}
			}
			else // 8x8
			{
				switch (matrixType->SelectedIndex)
				{
					case 0:
						this->loadMatrix(this->I8x8);
						break;
					case 1:
						this->loadMatrix(this->P8x8);
						break;
				}
			}
			this->currentConfig = this->getCurrentConfig();
		}
	}

	void QuantizerMatrixDialog::enable8x8Matrix()
	{
		mat1x1->Enabled = true;
		mat1x2->Enabled = true;
		mat1x3->Enabled = true;
		mat1x4->Enabled = true;
		mat1x5->Enabled = true;
		mat1x6->Enabled = true;
		mat1x7->Enabled = true;
		mat1x8->Enabled = true;
		mat2x5->Enabled = true;
		mat2x6->Enabled = true;
		mat2x7->Enabled = true;
		mat2x8->Enabled = true;
		mat3x5->Enabled = true;
		mat3x6->Enabled = true;
		mat3x7->Enabled = true;
		mat3x8->Enabled = true;
		mat4x5->Enabled = true;
		mat4x6->Enabled = true;
		mat4x7->Enabled = true;
		mat4x8->Enabled = true;
		mat5x1->Enabled = true;
		mat5x2->Enabled = true;
		mat5x3->Enabled = true;
		mat5x4->Enabled = true;
		mat5x5->Enabled = true;
		mat5x6->Enabled = true;
		mat5x7->Enabled = true;
		mat5x8->Enabled = true;
		mat6x1->Enabled = true;
		mat6x2->Enabled = true;
		mat6x3->Enabled = true;
		mat6x4->Enabled = true;
		mat6x5->Enabled = true;
		mat6x6->Enabled = true;
		mat6x7->Enabled = true;
		mat6x8->Enabled = true;
		mat7x1->Enabled = true;
		mat7x2->Enabled = true;
		mat7x3->Enabled = true;
		mat7x4->Enabled = true;
		mat7x5->Enabled = true;
		mat7x6->Enabled = true;
		mat7x7->Enabled = true;
		mat7x8->Enabled = true;
		mat8x1->Enabled = true;
		mat8x2->Enabled = true;
		mat8x3->Enabled = true;
		mat8x4->Enabled = true;
		mat8x5->Enabled = true;
		mat8x6->Enabled = true;
		mat8x7->Enabled = true;
		mat8x8->Enabled = true;
	}

	void QuantizerMatrixDialog::enable4x4Matrix()
	{
		mat1x1->Enabled = true;
		mat1x2->Enabled = true;
		mat1x3->Enabled = true;
		mat1x4->Enabled = true;
		mat2x1->Enabled = true;
		mat2x2->Enabled = true;
		mat2x3->Enabled = true;
		mat2x4->Enabled = true;
		mat3x1->Enabled = true;
		mat3x2->Enabled = true;
		mat3x3->Enabled = true;
		mat3x4->Enabled = true;
		mat4x1->Enabled = true;
		mat4x2->Enabled = true;
		mat4x3->Enabled = true;
		mat4x4->Enabled = true;
		mat1x5->Enabled = false;
		mat1x6->Enabled = false;
		mat1x7->Enabled = false;
		mat1x8->Enabled = false;
		mat2x5->Enabled = false;
		mat2x6->Enabled = false;
		mat2x7->Enabled = false;
		mat2x8->Enabled = false;
		mat3x5->Enabled = false;
		mat3x6->Enabled = false;
		mat3x7->Enabled = false;
		mat3x8->Enabled = false;
		mat4x5->Enabled = false;
		mat4x6->Enabled = false;
		mat4x7->Enabled = false;
		mat4x8->Enabled = false;
		mat5x1->Enabled = false;
		mat5x2->Enabled = false;
		mat5x3->Enabled = false;
		mat5x4->Enabled = false;
		mat5x5->Enabled = false;
		mat5x6->Enabled = false;
		mat5x7->Enabled = false;
		mat5x8->Enabled = false;
		mat6x1->Enabled = false;
		mat6x2->Enabled = false;
		mat6x3->Enabled = false;
		mat6x4->Enabled = false;
		mat6x5->Enabled = false;
		mat6x6->Enabled = false;
		mat6x7->Enabled = false;
		mat6x8->Enabled = false;
		mat7x1->Enabled = false;
		mat7x2->Enabled = false;
		mat7x3->Enabled = false;
		mat7x4->Enabled = false;
		mat7x5->Enabled = false;
		mat7x6->Enabled = false;
		mat7x7->Enabled = false;
		mat7x8->Enabled = false;
		mat8x1->Enabled = false;
		mat8x2->Enabled = false;
		mat8x3->Enabled = false;
		mat8x4->Enabled = false;
		mat8x5->Enabled = false;
		mat8x6->Enabled = false;
		mat8x7->Enabled = false;
		mat8x8->Enabled = false;
	}

	void QuantizerMatrixDialog::disableMatrix()
	{
		this->enable4x4Matrix();
		mat1x1->Enabled = false;
		mat1x2->Enabled = false;
		mat1x3->Enabled = false;
		mat1x4->Enabled = false;
		mat2x1->Enabled = false;
		mat2x2->Enabled = false;
		mat2x3->Enabled = false;
		mat2x4->Enabled = false;
		mat3x1->Enabled = false;
		mat3x2->Enabled = false;
		mat3x3->Enabled = false;
		mat3x4->Enabled = false;
		mat4x1->Enabled = false;
		mat4x2->Enabled = false;
		mat4x3->Enabled = false;
		mat4x4->Enabled = false;
	}

	QString QuantizerMatrixDialog::convertMatrixToString(int matrix[][])
	{
		QString retval = "";
		int wrapAfterElements = 4;
		if (sizeof(matrix) / sizeof(matrix[0]) == 64) // 8x8 matrix
			wrapAfterElements = 8;
		int count = 1;
		for (int::const_iterator val = matrix->begin(); val != matrix->end(); ++val)
		{
			retval += *val + ",";
			if (count == wrapAfterElements)
			{
				retval += "\r\n";
				count = 1;
			}
			else
				count++;
		}
		retval = retval.substr(0, retval.length() - 3); // strip last newline
		return retval;
	}

	void QuantizerMatrixDialog::i4x4Matrix()
	{
		matrixType->Items->Clear();
		matrixType->Items->Add("I Luma");
		matrixType->Items->Add("I Chroma U");
		matrixType->Items->Add("I Chroma Y");
		matrixType->Items->Add("P Luma");
		matrixType->Items->Add("P Chroma U");
		matrixType->Items->Add("P Chroma Y");
		matrixType->SelectedIndex = 0;
	}

	int **QuantizerMatrixDialog::convertStringToMatrix(const QString &matrix, int size)
	{
		int retval[size][size];
		wchar_t splitChars[1] = {','};
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Replace' method:
		matrix = matrix.Replace("\r", ""); // removes newlines
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Replace' method:
		matrix = matrix.Replace("\n", "");
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Replace' method:
		matrix = matrix.Replace("\t", ""); // remove tabs
//ORIGINAL LINE: string[] quantizers = matrix.Split(splitChars);
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Split' method:
		QString *quantizers = matrix.Split(splitChars);
		int column = 0;
		int line = 0;
		for (QString::const_iterator quantizer = quantizers->begin(); quantizer != quantizers->end(); ++quantizer)
		{
			int val = 16;
			try
			{
				val = int::Parse(*quantizer);
			}
			catch (std::exception &e)
			{
				MeXgui::core::util::LogItem *_oLog = MainForm::Instance->getLog()->Info("Error");
				_oLog->LogValue("convertStringToMatrix: " + matrix, e, MeXgui::core::util::Error);
				MessageBox::Show("Invalid quantizer detected: " + *quantizer + "\nUsing 16 instead", "Invalid quantizer", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			}
			retval[line][column] = val;
			if (column == size - 1)
			{
				line++;
				column = 0;
			}
			else
				column++;
		}
		return retval;
	}

	MatrixConfig QuantizerMatrixDialog::getCurrentConfig()
	{
		MatrixConfig conf = MatrixConfig();
		conf.size = matrixSize->SelectedIndex;
		conf.type = matrixType->SelectedIndex;
		return conf;
	}

	void QuantizerMatrixDialog::loadMatrix(MatrixConfig config)
	{
		if (config.size == 0) // 4x4 matrix
		{
			switch (config.type)
			{
				case 0: // I4x4L
					this->loadMatrix(this->I4x4L);
					break;
				case 1: // I4x4CU
					this->loadMatrix(this->I4x4CU);
					break;
				case 2: // I4x4CY
					this->loadMatrix(this->I4x4CY);
					break;
				case 3:
					this->loadMatrix(this->P4x4L);
					break;
				case 4:
					this->loadMatrix(this->P4x4CU);
					break;
				case 5:
					this->loadMatrix(this->P4x4CY);
					break;
			}
		}
		else if (config.size == 1) // 8x8 matrix
		{
			if (config.type == 0) // I8x8
				this->loadMatrix(this->I8x8);
			else if (config.type == 1) // P8x8
				this->loadMatrix(this->P8x8);
		}
	}

	void QuantizerMatrixDialog::saveMatrix(MatrixConfig config)
	{
		if (config.size == 0) // 4x4 matrix
		{
			switch (config.type)
			{
				case 0: // I4x4L
					this->I4x4L = this->getCurrentMatrix();
					break;
				case 1: // I4x4CU
					this->I4x4CU = this->getCurrentMatrix();
					break;
				case 2: // I4x4CY
					this->I4x4CY = this->getCurrentMatrix();
					break;
				case 3:
					this->P4x4L = this->getCurrentMatrix();
					break;
				case 4:
					this->P4x4CU = this->getCurrentMatrix();
					break;
				case 5:
					this->P4x4CY = this->getCurrentMatrix();
					break;
				case -1: // first time, load I4x4L
					this->I4x4L = this->getCurrentMatrix();
					break;
			}
		}
		else if (config.size == 1) // 8x8 matrix
		{
			if (config.type == 0) // I8x8
				this->I8x8 = this->getCurrentMatrix();
			else if (config.type == 1) // P8x8
				this->P8x8 = this->getCurrentMatrix();
			else
				this->I8x8 = this->getCurrentMatrix();
		}
	}

	void QuantizerMatrixDialog::saveMatrixButton_Click()
	{
		if (this->saveFileDialog->show() == System::Windows::Forms::DialogResult::OK)
		{
			StreamWriter *sw = 0;
			try
			{
				sb = new StringBuilder();
				sb->Append("#" + Path::GetFileNameWithoutExtension(saveFileDialog->FileName) + "\r\n\r\nINTRA4X4_LUMA =\r\n");
				sb->Append(convertMatrixToString(this->I4x4L));
				sb->Append("\r\n\r\nINTRA4X4_CHROMAU =\r\n");
				sb->Append(convertMatrixToString(this->I4x4CU));
				sb->Append("\r\n\r\nINTRA4X4_CHROMAV =\r\n");
				sb->Append(convertMatrixToString(this->I4x4CY));
				sb->Append("\r\n\r\nINTER4X4_LUMA =\r\n");
				sb->Append(convertMatrixToString(this->P4x4L));
				sb->Append("\r\n\r\nINTER4X4_CHROMAU =\r\n");
				sb->Append(convertMatrixToString(this->P4x4CU));
				sb->Append("\r\n\r\nINTER4X4_CHROMAV =\r\n");
				sb->Append(convertMatrixToString(this->P4x4CY));
				sb->Append("\r\n\r\nINTRA8X8_LUMA =\r\n");
				sb->Append(convertMatrixToString(this->I8x8));
				sb->Append("\r\n\r\nINTER8X8_LUMA =\r\n");
				sb->Append(convertMatrixToString(this->P8x8));

				sw = new StreamWriter(saveFileDialog->FileName, false);
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
				sw->Write(sb->ToString());
			}
			catch (std::exception &f)
			{
				MeXgui::core::util::LogItem *_oLog = MainForm::Instance->getLog()->Info("Error");
				_oLog->LogValue("Error", f, MeXgui::core::util::Error);
			}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
			finally
			{
				if (sw != 0)
				{
					try
					{
						sw->Close();
					}
					catch (std::exception &f)
					{
						MeXgui::core::util::LogItem *_oLog = MainForm::Instance->getLog()->Info("Error");
						_oLog->LogValue("Error", f, MeXgui::core::util::Error);
					}
				}
			}
		}
	}

	void QuantizerMatrixDialog::loadMatrixButton_Click()
	{
		if (openFileDialog->show() == System::Windows::Forms::DialogResult::OK)
		{
			StreamReader *sr = 0;
			QString matrix = "", line = "";
			try
			{
				sr = new StreamReader(openFileDialog->FileName);
				while ((line = sr->ReadLine()) != 0)
				{
					if (line.find("4X4") != -1) // 4x3 matrix
					{
						matrix = sr->ReadLine();
						matrix += sr->ReadLine();
						matrix += sr->ReadLine();
						matrix += sr->ReadLine();
//ORIGINAL LINE: int[,] matrixRead = convertStringToMatrix(matrix, 4);
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
						int **matrixRead = convertStringToMatrix(matrix, 4);
						if (line.find("INTRA4X4_LUMA") != -1) // I4x4L matrix
							this->I4x4L = matrixRead;
						else if (line.find("INTRA4X4_CHROMAU") != -1)
							this->I4x4CU = matrixRead;
						else if (line.find("INTRA4X4_CHROMAV") != -1)
							this->I4x4CY = matrixRead;
						else if (line.find("INTER4X4_LUMA") != -1)
							this->P4x4L = matrixRead;
						else if (line.find("INTER4X4_CHROMAU") != -1)
							this->P4x4CU = matrixRead;
						else if (line.find("INTER4X4_CHROMAV") != -1)
							this->P4x4CY = matrixRead;
					}
					if (line.find("8X8") != -1) // 8x8 matrix
					{
						matrix = sr->ReadLine();
						matrix += sr->ReadLine();
						matrix += sr->ReadLine();
						matrix += sr->ReadLine();
						matrix += sr->ReadLine();
						matrix += sr->ReadLine();
						matrix += sr->ReadLine();
						matrix += sr->ReadLine();
//ORIGINAL LINE: int[,] matrixRead = convertStringToMatrix(matrix, 8);
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
						int **matrixRead = convertStringToMatrix(matrix, 8);
						if (line.find("INTRA8X8_LUMA") != -1)
							this->I8x8 = matrixRead;
						else if (line.find("INTER8X8_LUMA") != -1)
							this->P8x8 = matrixRead;
					}
				}
				this->loadMatrix(getCurrentConfig());
				this->predefinedMatrix->SelectedIndex = 3;

			}
			catch (std::exception &f)
			{
				MeXgui::core::util::LogItem *_oLog = MainForm::Instance->getLog()->Info("Error");
				_oLog->LogValue("Error", f, MeXgui::core::util::Error);
			}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
			finally
			{
				if (sr != 0)
				{
					try
					{
						sr->Close();
					}
					catch (std::exception &f)
					{
						MeXgui::core::util::LogItem *_oLog = MainForm::Instance->getLog()->Info("Error");
						_oLog->LogValue("Error", f, MeXgui::core::util::Error);
					}
				}
			}
		}
	}

	void QuantizerMatrixDialog::InitializeInstanceFields()
	{
		doEvents = true;
		delete components;
	}

	const QString &CQMEditorTool::getName() const
	{
		return "AVC Quant Matrix Editor";
	}

	void CQMEditorTool::Run(MainForm *info)
	{
		(new QuantizerMatrixDialog())->Show();
	}

	const Shortcut &CQMEditorTool::getShortcuts() const
	{
		return new Shortcut[] {Shortcut::CtrlQ};
	}

	const QString &CQMEditorTool::getID() const
	{
		return "cqmEditor";
	}
}
