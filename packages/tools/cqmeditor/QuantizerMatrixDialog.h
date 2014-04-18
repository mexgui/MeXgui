#pragma once

#include "core/gui/MeXgui.HelpButton.h"
#include "core/util/LogItem.h"
#include "core/gui/MeXgui.MainForm.h"
#include "core/plugins/interfaces/IPackage.h"
#include <QString>
#include <stdexcept>
#include "stringconverter.h"

// ****************************************************************************
// 
// Copyright (C) 2005-2009  Doom9 & al
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
// 
// ****************************************************************************












//using namespace System::Text;



namespace MeXgui
{
	/// <summary>
	/// Summary description for QuantizerMatrixDialog.
	/// </summary>
	class QuantizerMatrixDialog : public System::Windows::Forms::Form
	{
	private:
//ORIGINAL LINE: private int[,] currentMatrix;
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
		int **currentMatrix;
//ORIGINAL LINE: private int[,] I8x8, P8x8, I4x4L, I4x4CU, I4x4CY, P4x4L, P4x4CU, P4x4CY;
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
		int **I8x8, **P8x8, **I4x4L, **I4x4CU, **I4x4CY, **P4x4L, **P4x4CU, **P4x4CY;
//ORIGINAL LINE: private int[,] jvtI8x8, jvtP8x8, jvtI4x4, jvtP4x4, flat8x8, flat4x4;
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
		int **jvtI8x8, **jvtP8x8, **jvtI4x4, **jvtP4x4, **flat8x8, **flat4x4;
		bool doEvents;
		StringBuilder *sb;
		MatrixConfig currentConfig;

		System::Windows::Forms::ComboBox *predefinedMatrix;
		System::Windows::Forms::Label *predefinedMatrixLabel;
		System::Windows::Forms::TextBox *mat1x1;
		System::Windows::Forms::TextBox *mat1x3;
		System::Windows::Forms::TextBox *mat1x4;
		System::Windows::Forms::TextBox *mat2x4;
		System::Windows::Forms::TextBox *mat2x3;
		System::Windows::Forms::TextBox *mat2x2;
		System::Windows::Forms::TextBox *mat2x1;
		System::Windows::Forms::TextBox *mat4x4;
		System::Windows::Forms::TextBox *mat4x3;
		System::Windows::Forms::TextBox *mat4x2;
		System::Windows::Forms::TextBox *mat4x1;
		System::Windows::Forms::TextBox *mat3x4;
		System::Windows::Forms::TextBox *mat3x3;
		System::Windows::Forms::TextBox *mat3x2;
		System::Windows::Forms::TextBox *mat3x1;
		System::Windows::Forms::TextBox *mat8x4;
		System::Windows::Forms::TextBox *mat8x3;
		System::Windows::Forms::TextBox *mat8x2;
		System::Windows::Forms::TextBox *mat8x1;
		System::Windows::Forms::TextBox *mat7x4;
		System::Windows::Forms::TextBox *mat7x3;
		System::Windows::Forms::TextBox *mat7x2;
		System::Windows::Forms::TextBox *mat7x1;
		System::Windows::Forms::TextBox *mat6x4;
		System::Windows::Forms::TextBox *mat6x3;
		System::Windows::Forms::TextBox *mat6x2;
		System::Windows::Forms::TextBox *mat6x1;
		System::Windows::Forms::TextBox *mat5x4;
		System::Windows::Forms::TextBox *mat5x3;
		System::Windows::Forms::TextBox *mat5x2;
		System::Windows::Forms::TextBox *mat5x1;
		System::Windows::Forms::GroupBox *matrixGroupbox;
		System::Windows::Forms::TextBox *mat1x8;
		System::Windows::Forms::TextBox *mat1x7;
		System::Windows::Forms::TextBox *mat1x6;
		System::Windows::Forms::TextBox *mat1x5;
		System::Windows::Forms::TextBox *mat2x8;
		System::Windows::Forms::TextBox *mat2x7;
		System::Windows::Forms::TextBox *mat2x6;
		System::Windows::Forms::TextBox *mat2x5;
		System::Windows::Forms::TextBox *mat3x8;
		System::Windows::Forms::TextBox *mat3x7;
		System::Windows::Forms::TextBox *mat3x6;
		System::Windows::Forms::TextBox *mat3x5;
		System::Windows::Forms::TextBox *mat4x8;
		System::Windows::Forms::TextBox *mat4x7;
		System::Windows::Forms::TextBox *mat4x6;
		System::Windows::Forms::TextBox *mat4x5;
		System::Windows::Forms::TextBox *mat5x8;
		System::Windows::Forms::TextBox *mat5x7;
		System::Windows::Forms::TextBox *mat5x6;
		System::Windows::Forms::TextBox *mat5x5;
		System::Windows::Forms::TextBox *mat6x8;
		System::Windows::Forms::TextBox *mat6x7;
		System::Windows::Forms::TextBox *mat6x6;
		System::Windows::Forms::TextBox *mat6x5;
		System::Windows::Forms::TextBox *mat7x8;
		System::Windows::Forms::TextBox *mat7x7;
		System::Windows::Forms::TextBox *mat7x6;
		System::Windows::Forms::TextBox *mat7x5;
		System::Windows::Forms::TextBox *mat8x8;
		System::Windows::Forms::TextBox *mat8x7;
		System::Windows::Forms::TextBox *mat8x6;
		System::Windows::Forms::TextBox *mat8x5;
		System::Windows::Forms::ComboBox *matrixType;
		System::Windows::Forms::ComboBox *matrixSize;
		System::Windows::Forms::OpenFileDialog *openFileDialog;
		System::Windows::Forms::SaveFileDialog *saveFileDialog;
		System::Windows::Forms::Label *matrixSizeLabel;
		System::Windows::Forms::Label *matrixTypeLabel;
		System::Windows::Forms::Button *loadMatrixButton;
		System::Windows::Forms::Button *saveMatrixButton;
		System::Windows::Forms::Button *okButton;
		System::Windows::Forms::GroupBox *operationsGroupbox;
		System::Windows::Forms::TextBox *mat1x2;
		MeXgui::core::gui::HelpButton *helpButton1;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container *components;
		public:
		~QuantizerMatrixDialog()
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
		QuantizerMatrixDialog();

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
	private:
		void Dispose(bool disposing);
		void QuantizerMatrixDialog_Load();

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent();
	public:
		void blankMatrix();
		/// <summary>
		/// loads a matrix into the GUI
		/// </summary>
		/// <param name="matrix"></param>
	private:
		void loadMatrix(int matrix[][]);
		/// <summary>
		/// returns the currently configured matrix as an integer array
		/// </summary>
		/// <returns></returns>
		int **getCurrentMatrix();

		void predefinedMatrix_SelectedIndexChanged();
		void matrixSize_SelectedIndexChanged();
		void matrixType_SelectedIndexChanged();
		/// <summary>
		/// enables all quantizer input fields
		/// </summary>
		void enable8x8Matrix();
		/// <summary>
		/// disables but the upper left quadrant of the quantizer matrix
		/// </summary>
		void enable4x4Matrix();

		/// <summary>
		/// disables all quantizer input fields
		/// </summary>
		void disableMatrix();
		/// <summary>
		/// converts a twodimensional matrix into a string that can be used for saving a matrix to file
		/// </summary>
		/// <param name="matrix">the matrix to be converted</param>
		/// <returns>result of the conversion</returns>
		QString convertMatrixToString(int matrix[][]);
		/// <summary>
		/// calles when the 4x4 matrix size has been selected
		/// </summary>
		void i4x4Matrix();
		/// <summary>
		/// converts a comma separated 
		/// </summary>
		/// <param name="matrix"></param>
		/// <param name="size"></param>
		/// <returns></returns>
		int **convertStringToMatrix(const QString &matrix, int size);

		/// <summary>
		/// gets all the data from the GUI to identify which type of matrix we're currently looking at
		/// </summary>
		/// <returns>the struct containing all the data</returns>
		MatrixConfig getCurrentConfig();
		/// <summary>
		/// loads the matrix specified in the current configuration
		/// </summary>
		/// <param name="config">the configuration pointing out which matrix is to be loaded</param>
		void loadMatrix(MatrixConfig config);
		/// <summary>
		/// saves the matrix currently configured in the gui into the appropriate internal matrix
		/// used when changing between a matrix size / subtype
		/// </summary>
		/// <param name="config">the current matrix configuration</param>
		void saveMatrix(MatrixConfig config);
		/// <summary>
		/// saves the currently configured matrix to a file
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		void saveMatrixButton_Click();
		/// <summary>
		/// loads a matrix from file
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		void loadMatrixButton_Click();

	private:
		void InitializeInstanceFields();
	};
	class MatrixConfig
	{
	public:
		int size;
		int type;
		bool onePerSize;
	};

	class CQMEditorTool : public MeXgui::core::plugins::interfaces::ITool
	{

	public:
		const QString &getName() const;

		void Run(MainForm *info);

		const Shortcut *getShortcuts() const;



		const QString &getID() const;

	};
}
