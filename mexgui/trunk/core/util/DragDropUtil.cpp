#include "DragDropUtil.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;
namespace MeGUI
{
	namespace core
	{
		namespace util
		{

			void DragDropUtil::RegisterSingleFileDragDrop(Control *c, SingleFileReceiver r)
			{
				RegisterSingleFileDragDrop(c, r, "All files|*.*");
			}

			void DragDropUtil::RegisterSingleFileDragDrop(Control *c, SingleFileReceiver r, const std::string &filter)
			{
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
				RegisterSingleFileDragDrop(c, r, delegate()
				{
					return filter;
				}
			   );
			}

			void DragDropUtil::RegisterSingleFileDragDrop(Control *c, SingleFileReceiver r, Getter<std::string> filter)
			{
				c->AllowDrop = true;
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
				c->DragEnter += delegate(object sender, DragEventArgs e)
				{
						e->Effect = DragDropEffects::None;

						if (e::Data::GetDataPresent(DataFormats::FileDrop))
						{
//ORIGINAL LINE: string[] files = (string[])e.Data.GetData(DataFormats.FileDrop, false);
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
							std::string *files = static_cast<std::string[]>(e::Data::GetData(DataFormats::FileDrop, false));
							if (sizeof(files) / sizeof(files[0]) == 1 && FileUtil::MatchesFilter(filter(), files[0]))
								e->Effect = DragDropEffects::All;
						}
				};
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
				c->DragDrop += delegate(object sender, DragEventArgs e)
				{
						r((static_cast<std::string[]>(e::Data::GetData(DataFormats::FileDrop, false)))[0]);
				};
			}

			void DragDropUtil::RegisterMultiFileDragDrop(Control *c, MultiFileReceiver r)
			{
				RegisterMultiFileDragDrop(c, r, "All files|*.*");
			}

			void DragDropUtil::RegisterMultiFileDragDrop(Control *c, MultiFileReceiver r, const std::string &filter)
			{
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
				RegisterMultiFileDragDrop(c, r, delegate()
				{
					return filter;
				}
			   );
			}

			void DragDropUtil::RegisterMultiFileDragDrop(Control *c, MultiFileReceiver r, Getter<std::string> filter)
			{
				c->AllowDrop = true;
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
				c->DragEnter += delegate(object sender, DragEventArgs e)
				{
						e->Effect = DragDropEffects::None;

						if (e::Data::GetDataPresent(DataFormats::FileDrop))
						{
//ORIGINAL LINE: string[] files = (string[])e.Data.GetData(DataFormats.FileDrop, false);
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
							std::string *files = static_cast<std::string[]>(e::Data::GetData(DataFormats::FileDrop, false));
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
							if (sizeof(files) / sizeof(files[0]) > 0 && Array::Exists<std::string>(files, delegate(std::string s) {return FileUtil::MatchesFilter(filter(), s);}))
								e->Effect = DragDropEffects::All;
						}
				};

//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
				c->DragDrop += delegate(object sender, DragEventArgs e)
				{
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
						r(Array::FindAll<std::string>((static_cast<std::string[]>(e::Data::GetData(DataFormats::FileDrop, false))), delegate(std::string s)
						{
							return FileUtil::MatchesFilter(filter(), s);
						}
					   ));
				};

			}
		}
	}
}
