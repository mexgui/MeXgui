#pragma once

#include "trunk/MediaInfoWrapperDll/MediaInfoMain.h"
#include "trunk/MediaInfoWrapperDll/GeneralTrack.h"
#include "trunk/MediaInfoWrapperDll/VideoTrack.h"
#include "trunk/MediaInfoWrapperDll/AudioTrack.h"
#include "trunk/MediaInfoWrapperDll/TextTrack.h"
#include "trunk/MediaInfoWrapperDll/ChaptersTrack.h"
#include <string>
#include <vector>

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::ComponentModel;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Data;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Drawing;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Reflection;
using namespace MediaInfoWrapper;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
namespace MediaInfoWrapperTest
{
   class MediaInfoForm : public System::Windows::Forms::Form
   {
   private:
	   std::string FileName;
	   MediaInfo *M;
	   /// <summary>
	   /// Constructor
	   /// </summary>
	   public:
	   ~MediaInfoForm()
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
	   MediaInfoForm();
	   /// <summary>
	   /// Constructor with the form initialized to the specified file
	   /// </summary>
	   /// <param name="filepath"></param>
	   MediaInfoForm(const std::string &filepath);




	private:
		void Form1_Load(object *sender, EventArgs *e);


	   void toolStripButton1_Click(object *sender, EventArgs *e);

	   void toolStripButton2_Click(object *sender, EventArgs *e);

	   void toolStripButton3_Click(object *sender, EventArgs *e);

	   void toolStripButton4_Click(object *sender, EventArgs *e);

	   void toolStripButton5_Click(object *sender, EventArgs *e);

	   void toolStripButton6_Click(object *sender, EventArgs *e);

	   void toolStripTextBox1_KeyDown(object *sender, KeyEventArgs *e);


	   // Can be replaced by InfoCustom property of mediainfo
	   std::string InfoCustom(const std::string &filepath);

	   template<typename T1>
	   std::string ListEveryAvailablePropery(std::vector<T1> &L);







		/// <summary>
		/// Variable nécessaire au concepteur.
		/// </summary>
		System::ComponentModel::IContainer *components;

		/// <summary>
		/// Nettoyage des ressources utilisées.
		/// </summary>
		/// <param name="disposing">true si les ressources managées doivent être supprimées ; sinon, false.</param>
		void Dispose(bool disposing);


		/// <summary>
		/// Méthode requise pour la prise en charge du concepteur - ne modifiez pas
		/// le contenu de cette méthode avec l'éditeur de code.
		/// </summary>
		void InitializeComponent();


		System::Windows::Forms::ToolStripContainer *toolStripContainer1;
		System::Windows::Forms::RichTextBox *T;
		System::Windows::Forms::ToolStrip *toolStrip1;
		System::Windows::Forms::ToolStripTextBox *toolStripTextBox1;
		System::Windows::Forms::ToolStripButton *toolStripButton1;
		System::Windows::Forms::ToolStripButton *toolStripButton2;
		System::Windows::Forms::ToolStripButton *toolStripButton3;
		System::Windows::Forms::ToolStripButton *toolStripButton4;
		System::Windows::Forms::ToolStripButton *toolStripButton5;
		System::Windows::Forms::ToolStripButton *toolStripButton6;

   private:
	   void InitializeInstanceFields();
   };
}
