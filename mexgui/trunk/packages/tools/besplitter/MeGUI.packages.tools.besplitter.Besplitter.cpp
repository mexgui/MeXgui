#include "MeGUI.packages.tools.besplitter.Besplitter.h"

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
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;
using namespace MeGUI::core::details;
using namespace MeGUI::core::plugins::interfaces;
using namespace MeGUI::core::util;
namespace MeGUI
{
	namespace packages
	{
		namespace tools
		{
			namespace besplitter
			{

				Besplitter::Besplitter(MainForm *info)
				{
					InitializeInstanceFields();
					this->info = info;
					InitializeComponent();

					filters = new OutputFileType[] {AudioType::AC3, AudioType::DTS, AudioType::MP2, AudioType::MP3, AudioType::RAWAAC, AudioType::WAV, AudioType::PCM};

					input->setFilter(VideoUtil::GenerateCombinedFilter(filters));
					output->setFilter(input->getFilter());
				}

				void Besplitter::goButton_Click(object *sender, EventArgs *e)
				{
					if (input->getFilename().empty() || output->getFilename().empty() || cuts->getFilename().empty())
					{
						MessageBox::Show("Can't create job: input not configured.", "Can't create job", MessageBoxButtons::OK, MessageBoxIcon::Error);
						return;
					}

//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'EndsWith' method:
					if (!output->getFilename().ToLower(System::Globalization::CultureInfo::InvariantCulture)->EndsWith(Path::GetExtension(input->getFilename())->ToLower(System::Globalization::CultureInfo::InvariantCulture)))
					{
						MessageBox::Show("Can't create job: input and output have different types.", "Can't create job", MessageBoxButtons::OK, MessageBoxIcon::Error);
						return;
					}

					Cuts *c = 0;
					try
					{
						c = FilmCutter::ReadCutsFromFile(cuts->getFilename());
					}
					catch (std::exception &e1)
					{
						MessageBox::Show("Error reading cutlist. Is it the correct format?", "Error reading cutlist", MessageBoxButtons::OK, MessageBoxIcon::Error);
						return;
					}

					std::string prefix = getAcceptableFilename(output->getFilename(), c->getAllCuts().size()*2);
//ORIGINAL LINE: string[] tempfiles = generateNumberedFilenames(prefix, Path.GetExtension(output.Filename), c.AllCuts.Count * 2);
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
					std::string *tempfiles = generateNumberedFilenames(prefix, Path::GetExtension(output->getFilename()), c->getAllCuts().size() * 2);

					AudioSplitJob *split = new AudioSplitJob(input->getFilename(), prefix, c);
					for (int i = 1; i < sizeof(tempfiles) / sizeof(tempfiles[0]); i += 2)
						split->FilesToDelete.push_back(tempfiles[i]);

					int length = sizeof(tempfiles) / sizeof(tempfiles[0]) / 2;
					if (sizeof(tempfiles) / sizeof(tempfiles[0]) % 2 != 0)
						length++;
					std::string evens[length];
					for (int i = 0; i < sizeof(evens) / sizeof(evens[0]); i++)
						evens[i] = tempfiles[2 * i];

					AudioJoinJob *join = new AudioJoinJob(evens, output->getFilename());
					join->FilesToDelete.AddRange(evens);
					// generate the join commandline later

					join->setClipLength(TimeSpan::FromSeconds(static_cast<double>(c->getTotalFrames()) / c->Framerate));

					info->getJobs()->addJobsWithDependencies(new SequentialChain(split, join), true);
					delete this;
				}

				std::string *Besplitter::generateNumberedFilenames(const std::string &prefix, const std::string &ext, int num)
				{
					std::string ans[num];
					for (int i = 1; i <= num; i++)
					{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
						ans[i - 1] = prefix + i.ToString("00") + ext;
					}
					return ans;
				}

				std::string Besplitter::getAcceptableFilename(const std::string &p, int p_2)
				{
					std::string ext = Path::GetExtension(p);
					std::string name = Path::Combine(Path::GetDirectoryName(p), Path::GetFileNameWithoutExtension(p));
					int suffix = 0;
					while (true)
					{
						std::string test = name + "_" + suffix + "_";
						bool failed = false;
						for (std::string::const_iterator s = generateNumberedFilenames(test, ext, p_2)->begin(); s != generateNumberedFilenames(test, ext, p_2)->end(); ++s)
							if (File::Exists(*s))
							{
								failed = true;
								break;
							}

						if (!failed)
							return test;
						suffix++;
					}
				}

				void Besplitter::input_FileSelected(FileBar *sender, FileBarEventArgs *args)
				{
					for (MeGUI::OutputFileType::const_iterator type = filters->begin(); type != filters->end(); ++type)
					{
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'EndsWith' method:
						if (sender->getFilename().ToLower(System::Globalization::CultureInfo::InvariantCulture)->EndsWith((*type)->getExtension()))
						{
							output->setFilter((*type)->getOutputFilterString());
							break;
						}
					}
				}

				void Besplitter::Dispose(bool disposing)
				{
					if (disposing && (components != 0))
					{
						delete components;
					}
					System::Windows::Forms::Form::Dispose(disposing);
				}

				void Besplitter::InitializeComponent()
				{
					System::ComponentModel::ComponentResourceManager *resources = new System::ComponentModel::ComponentResourceManager(Besplitter::typeid);
					this->label1 = new System::Windows::Forms::Label();
					this->label2 = new System::Windows::Forms::Label();
					this->label3 = new System::Windows::Forms::Label();
					this->input = new MeGUI::FileBar();
					this->cuts = new MeGUI::FileBar();
					this->output = new MeGUI::FileBar();
					this->goButton = new System::Windows::Forms::Button();
					this->helpButton1 = new MeGUI::core::gui::HelpButton();
					this->SuspendLayout();
					// 
					// label1
					// 
					this->label1->AutoSize = true;
					this->label1->Location = new System::Drawing::Point(12, 9);
					this->label1->Name = "label1";
					this->label1->Size = new System::Drawing::Size(50, 13);
					this->label1->TabIndex = 0;
					this->label1->Text = "Input file";
					// 
					// label2
					// 
					this->label2->AutoSize = true;
					this->label2->Location = new System::Drawing::Point(12, 54);
					this->label2->Name = "label2";
					this->label2->Size = new System::Drawing::Size(41, 13);
					this->label2->TabIndex = 1;
					this->label2->Text = "Cut file";
					// 
					// label3
					// 
					this->label3->AutoSize = true;
					this->label3->Location = new System::Drawing::Point(12, 99);
					this->label3->Name = "label3";
					this->label3->Size = new System::Drawing::Size(58, 13);
					this->label3->TabIndex = 2;
					this->label3->Text = "Output file";
					// 
					// input
					// 
					this->input->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
					this->input->setFilename("");
					this->input->setFilter("");
					this->input->setFilterIndex(0);
					this->input->setFolderMode(false);
					this->input->Location = new System::Drawing::Point(12, 25);
					this->input->Name = "input";
					this->input->setReadOnly(true);
					this->input->setSaveMode(false);
					this->input->Size = new System::Drawing::Size(285, 26);
					this->input->TabIndex = 3;
					this->input->setTitle("");
					this->input->FileSelected += new MeGUI::FileBarEventHandler(this, &Besplitter::input_FileSelected);
					// 
					// cuts
					// 
					this->cuts->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
					this->cuts->setFilename("");
					this->cuts->setFilter("MeGUI cutlist files (*.clt)|*.clt");
					this->cuts->setFilterIndex(0);
					this->cuts->setFolderMode(false);
					this->cuts->Location = new System::Drawing::Point(12, 70);
					this->cuts->Name = "cuts";
					this->cuts->setReadOnly(true);
					this->cuts->setSaveMode(false);
					this->cuts->Size = new System::Drawing::Size(285, 26);
					this->cuts->TabIndex = 4;
					this->cuts->setTitle("");
					// 
					// output
					// 
					this->output->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
					this->output->setFilename("");
					this->output->setFilter("");
					this->output->setFilterIndex(0);
					this->output->setFolderMode(false);
					this->output->Location = new System::Drawing::Point(12, 115);
					this->output->Name = "output";
					this->output->setReadOnly(false);
					this->output->setSaveMode(true);
					this->output->Size = new System::Drawing::Size(285, 26);
					this->output->TabIndex = 5;
					this->output->setTitle("");
					// 
					// goButton
					// 
					this->goButton->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right)));
					this->goButton->AutoSize = true;
					this->goButton->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
					this->goButton->Location = new System::Drawing::Point(229, 156);
					this->goButton->Name = "goButton";
					this->goButton->Size = new System::Drawing::Size(68, 23);
					this->goButton->TabIndex = 6;
					this->goButton->Text = "Create job";
					this->goButton->UseVisualStyleBackColor = true;
					this->goButton->Click += new System::EventHandler(this, &Besplitter::goButton_Click);
					// 
					// helpButton1
					// 
					this->helpButton1->setArticleName("Audio Cutter");
					this->helpButton1->AutoSize = true;
					this->helpButton1->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
					this->helpButton1->Location = new System::Drawing::Point(12, 156);
					this->helpButton1->Name = "helpButton1";
					this->helpButton1->Size = new System::Drawing::Size(38, 23);
					this->helpButton1->TabIndex = 7;
					// 
					// Besplitter
					// 
					this->AutoScaleDimensions = new System::Drawing::SizeF(6, 13);
					this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
					this->ClientSize = new System::Drawing::Size(309, 191);
					this->Controls->Add(this->helpButton1);
					this->Controls->Add(this->goButton);
					this->Controls->Add(this->output);
					this->Controls->Add(this->cuts);
					this->Controls->Add(this->input);
					this->Controls->Add(this->label3);
					this->Controls->Add(this->label2);
					this->Controls->Add(this->label1);
					this->Font = new System::Drawing::Font("Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, (static_cast<unsigned char>(0)));
					this->Icon = (static_cast<System::Drawing::Icon*>(resources->GetObject("$this.Icon")));
					this->Name = "Besplitter";
					this->Text = "MeGUI - Audio Cutter";
					this->ResumeLayout(false);
					this->PerformLayout();

				}

				void Besplitter::InitializeInstanceFields()
				{
					delete components;
				}
			}
		}
	}
}
