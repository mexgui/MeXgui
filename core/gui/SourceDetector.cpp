#include "SourceDetector.h"




//using namespace System::Collections::Generic;



//using namespace System::Data;

//using namespace System::Diagnostics;





//using namespace System::Globalization;

//using namespace System::Text;

//using namespace System::Threading;



namespace MeGUI
{

	SourceDetector::SourceDetector(const QString &avsScript, const QString &d2vFile_Renamed, bool isAnime, SourceDetectorSettings *settings, UpdateSourceDetectionStatus updateMethod, FinishedAnalysis finishedMethod)
	{

		InitializeInstanceFields();
		this->script = avsScript;
		this->d2vFileName = d2vFile_Renamed;
		this->settings = settings;
		this->isAnime = isAnime;
		analyseUpdate += updateMethod;
		finishedAnalysis += finishedMethod;

		//
		trimmedFilteredLine = "";
		type = UNKNOWN;
		majorityFilm = false;
		usingPortions = false;
		error = false;
		continueWorking = true;
	}

	QString SourceDetector::findPortions(QVector<int[]> &portions, int selectEvery, int selectLength, int numPortions, int sectionCount, int inputFrames, const QString &type, QString &trimLine, int &frameCount)
	{
		frameCount = 0;
		trimLine = "";
		trimmedFilteredLine = "";
		QString outputText = QString::Format("There are {0} {1} portions.\r\n", numPortions, type);

		int lastEndFrame = -1;
		for (int i = 0; i < numPortions; i++)
		{
			int portionStart = portions[i][0];
			int portionEnd = portions[i][1];
			int startFrame = __max(0, (portionStart) * selectEvery);
			if (portionEnd == 0)
				portionEnd = sectionCount;
			int endFrame = __min(inputFrames - 1, (portionEnd + 1) * selectEvery);
			frameCount += endFrame - startFrame;
			trimLine += QString::Format("trim({0},{1}) ++ ", startFrame, endFrame);
			outputText += QString::Format("Portion number {0} goes from frame {1} to frame {2}.\r\n", i + 1, startFrame, endFrame);
			trimmedFilteredLine += QString::Format("original.trim({0},{1}) ++ deintted.trim({2},{3}) ++ ", lastEndFrame + 1, startFrame - 1, startFrame, endFrame);
			lastEndFrame = endFrame;
		}
		if (lastEndFrame < inputFrames - 1)
			trimmedFilteredLine += QString::Format("original.trim({0},{1})", lastEndFrame + 1, inputFrames);
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'TrimEnd' method:
		trimLine = trimLine.TrimEnd(new wchar_t[] {' ', '+'});
		return outputText;
	}

	QString SourceDetector::getLogFileName(const QString &logFileName)
	{
		return Path::Combine(Path::GetTempPath(), logFileName);
	}

	void SourceDetector::Process(const QString &scriptBlock)
	{
		try
		{
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//			using (AvsFile af = AvsFile.ParseScript(scriptBlock))
			AvsFile *af = AvsFile::ParseScript(scriptBlock);
			try
			{
				int i = 0;
				int frameCount = static_cast<int>(af->getVideoInfo()->FrameCount);
				bool running = true;
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
				new Thread(new ThreadStart(delegate
					if (analyseUpdate != 0)
					{
						while (running && continueWorking)
						{
							analyseUpdate(i, frameCount);
							delay(500);
						}
					}
			}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
			finally
			{
				if (af != 0)
					af.Dispose();
			}
			   )).Start();


				void* zero = new void*(0);
				for (i = 0; i < frameCount && continueWorking; i++)
				{
					af->getClip()->ReadFrame(zero, 0, i);
				}
				running = false;
		}
	}

	private *SourceDetector::catch_Renamed(std::exception &ex)
	{
		error = true;
		errorMessage = "Error opening analysis script:\r\n" + ex.what();
		finishProcessing();
	}

	void SourceDetector::InitializeInstanceFields()
	{
		error = false
		continueWorking = true;
		errorMessage = "";
		tffCount = 0
		bffCount = 0;
		fieldOrder = UNKNOWN;
		filters = QVector<DeinterlaceFilter*>();
	}

	void <missing_class_definition>::runScript(int scriptType, int frameCount, const QString &trimLine)
	{
		int numFrames = 0;
		try
		{
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//			using (AvsFile af = AvsFile.ParseScript(script))
			AvsFile *af = AvsFile::ParseScript(script);
			try
			{
				numFrames = static_cast<int>(af->getVideoInfo()->FrameCount);
			}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
			finally
			{
				if (af != 0)
					af.Dispose();
			}
		}
		catch (std::exception &e)
		{
			error = true;
			errorMessage = "The input clip for source detection could not be opened.\r\n" + e.what();
			finishProcessing();
			return;
		}

		if (frameCount > 0)
			numFrames = frameCount;

		const int selectLength = 5; // This used to be variable, but I found no need to. It's useful to keep this name, though
		int selectEvery = static_cast<int>((100.0 * static_cast<double>(selectLength)) / (static_cast<double>(settings::AnalysePercent)));

		int minAnalyseSections = settings::MinimumAnalyseSections;
		if (scriptType == 1) // Field order script. For this, we separatefields, so we have twice as many frames anyway
			// It saves time, and costs nothing to halve the minimum sections to analyse for this example
			minAnalyseSections = minAnalyseSections / 2 + 1; // We add one to prevent getting 0;

		// Check if we need to modify the SelectRangeEvery parameters:
		if ((static_cast<double>(selectLength) * static_cast<double>(numFrames) / static_cast<double>(selectEvery)) < static_cast<int>(minAnalyseSections) * 5)
		{
			if (numFrames >= minAnalyseSections * 5) // If there are actually enough frames
			{
				selectEvery = static_cast<int>(((static_cast<double>(numFrames)) / (static_cast<double>(minAnalyseSections) * 5.0)) * static_cast<double>(selectLength));
			}
			else
				// if there aren't enough frames, analyse everything -- that's got to be good enough
				selectEvery = selectLength;
		}

//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		QString logFileName = getLogFileName((scriptType == 1) ? "ff_interlace-" + Guid::NewGuid()->ToString("N") + ".log" : "interlace-" + Guid::NewGuid()->ToString("N") + ".log");

		if (File::Exists(logFileName))
			File::Delete(logFileName);

		QString resultScript = ScriptServer::getScript(scriptType, script, trimLine, logFileName, selectEvery, selectLength);

		// stax
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
		MethodInvoker *mi = delegate
		{
			try
			{
				Process(resultScript); // stax
				if (error)
					return;
				if (!continueWorking)
					return;
				if (scriptType == 0) // detection
					analyse(logFileName, selectEvery, selectLength, numFrames);
				else if (scriptType == 1) // field order
					analyseFF(logFileName);
			}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
			finally
			{
				try
				{
					File::Delete(logFileName);
				}
				catch (std::exception &e1)
				{
				}
			}
		};

		Thread *t = new Thread(new ThreadStart(mi));
		t->Priority = settings::Priority;
		t->Start();
	}

	bool <missing_class_definition>::checkDecimate(int data[])
	{
		int dataCopy[6];
		Array::Copy(data, dataCopy, 6);
		Array::Sort(dataCopy);

					int numMovingFrames = -1;

		for (int i = 0; i < sizeof(data) / sizeof(data[0]); i++)
		{
			if (dataCopy[5] == data[i])
				numMovingFrames = i;
		}

		if (dataCopy[5] > (double)dataCopy[4] * settings::DecimationThreshold && numMovingFrames != 5 && numMovingFrames != 0)
			// If there are 5 moving frames, then it needs no decimation
			// If there are 0 moving frames, then we have a problem.
		{
			type = DECIMATING;
			decimateM = 5 - numMovingFrames;
			return true;
		}
		return false;
	}

	void <missing_class_definition>::analyseFF(const QString &filename)
	{
		CultureInfo *ci = new CultureInfo("en-us");
		StreamReader *instream;
		try
		{
			instream = new StreamReader(filename);
		}
		catch (std::exception &e1)
		{
//C# TO C++ CONVERTER WARNING: C# to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
			delete instream;
			error = true;
			errorMessage = "Opening the field order analysis file failed.";
			finishProcessing();
			return;
		}
		int countA = 0, countB = 0, countEqual = 0;
		int localCountA = 0, localCountB = 0, sectionCountA = 0, sectionCountB = 0;
		double sumA = 0, sumB = 0;
		double valueA, valueB;
		int count = 0;

		QString line = instream->ReadLine();
		while (line != "")
		{
			if (count != 0 && line.find("-1.#IND00") == -1) //Scene change or unexptected value -> ignore
			{
//ORIGINAL LINE: string[] contents = line.Split(new char[] { '-' });
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Split' method:
				QString *contents = line.Split(new wchar_t[] {'-'});
				try
				{
					valueA = double::Parse(contents[0], ci);
					valueB = double::Parse(contents[1], ci);
				}
				catch (std::exception &e2)
				{
					error = true;
					errorMessage = "Unexpected value in file " + filename + "\r\n" + "This error should not have occurred. Please report it on \r\n" + "post it on http://sourceforge.net/projects/megui with the file named above.";
					errorMessage += "\r\nMore debugging info:\r\n" + "Line contents: " + line + "\r\n";
					finishProcessing();
					return;
				}
				if (valueA > valueB)
				{
					countA++;
					localCountA++;
				}
				else if (valueB > valueA)
				{
					countB++;
					localCountB++;
				}
				else
					countEqual++;
				sumA += valueA;
				sumB += valueB;
			}
			count++;
			if (count == 10)
			{
				count = 0;
				// Truly interlaced sections should always make one of the counts be 5 and the other 0.
				// Progressive sections will be randomly distributed between localCountA and localCountB,
				// so this algorithm successfully ignores those sections.
				// Film sections will always have two frames which show the actual field order, and the other
				// frames will show an arbitrary field order. This algorithm (luckily) seems to work very well
				// with film sections as well. Using this thresholding as opposed to just comparing countB to countA
				// produces _much_ more heavily-sided results.
				if (localCountA > localCountB && localCountB == 0)
					sectionCountA++;
				if (localCountB > localCountA && localCountA == 0)
					sectionCountB++;
				localCountA = 0;
				localCountB = 0;
			}
			line = instream->ReadLine();
		}
		instream->Close();
		if (((static_cast<double>(sectionCountA) + static_cast<double>(sectionCountB)) / 100.0 * static_cast<double>(settings::HybridFOPercent)) > sectionCountB)
		{
			analysis += "Source is declared tff by a margin of " + sectionCountA + " to " + sectionCountB + ".";
			fieldOrder = TFF;
		}
		else if (((static_cast<double>(sectionCountA) + static_cast<double>(sectionCountB)) / 100.0 * static_cast<double>(settings::HybridFOPercent)) > sectionCountA)
		{
			analysis += "Source is declared bff by a margin of " + sectionCountB + " to " + sectionCountA + ".";
			fieldOrder = BFF;
		}
		else
		{
			analysis += "Source is hybrid bff and tff at " + sectionCountB + " bff and " + sectionCountA + " tff.";
			fieldOrder = VARIABLE;
		}

		tffCount = countA;
		bffCount = countB;
		finishProcessing();
	}

	void <missing_class_definition>::analyse(const QString &logFileName, int selectEvery, int selectLength, int inputFrames)
	{
		bool stillWorking = false;
		StreamReader *instream;
		try
		{
			instream = new StreamReader(logFileName);
		}
		catch (IOException *e1)
		{
			error = true;
			errorMessage = "Can't open analysis log file, \"" + logFileName + "\"\r\n" + "Make sure that TIVTC.dll is in your AviSynth plugins dir.";
			finishProcessing();
			return;
		}
		bool data[5][2];
		int count = 0;
		int numTC = 0, numProg = 0, numInt = 0, numUseless = 0;
		int sectionCount = 0;

		// Decimation data
		int totalCombed = 0;
		int sectionsWithMovingFrames[6];

		int maxPortions = settings::MaxPortions;
		// interlaced portions
//ORIGINAL LINE: List<int[]>[] portions = new List<int[]>[2];
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
		QVector<int[]> *portions = new QVector<int[]>[2];
		portions[0] = QVector<int[]>();
		portions[1] = QVector<int[]>();

		int portionLength[2];
		int nextPortionIndex[2];
		bool inPortion[2];
		int numPortions[2];
		int portionStatus[2];


		QString line = instream->ReadLine();
		while (line != "")
		{
			if (line.length() > 11)
			{
				error = true;
				errorMessage = "Unexpected value in file " + logFileName + "\r\n" + "Make sure you have TIVTC.dll in your AviSynth plugins directory.";
			}
//ORIGINAL LINE: string[] contents = line.Split(new char[] { '-' });
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Split' method:
			QString *contents = line.Split(new wchar_t[] {'-'});
			data[count][0] = (contents[0].Equals("true"));
			data[count][1] = (contents[1].Equals("true"));
			count++;

			if (count == 5)
			{
				sectionCount++;
				int numComb = 0;
				int numMoving = 0;
				int combA = -1, combB = -1;
				for (int i = 0; i < 5; i++)
				{
					if (data[i][0])
					{
						numComb++;
						if (combA == -1)
							combA = i;
						else
							combB = i;
					}
					if (data[i][1])
						numMoving++;
				}
				totalCombed += numComb;
				sectionsWithMovingFrames[numMoving]++;
				if (numMoving < 5)
				{
					numUseless++;
					portionStatus[0] = 1;
					portionStatus[1] = 1;
				}
				else if (numComb == 2 && ((combB - combA == 1) || (combB - combA == 4)))
				{
					numTC++;
					portionStatus[0] = 0;
					portionStatus[1] = 2;
				}
				else if (numComb > 0)
				{
					numInt++;
					portionStatus[0] = 2;
					portionStatus[1] = 0;
				}
				else
				{
					numProg++;
					portionStatus[0] = 0;
					portionStatus[1] = 0;
				}
				// Manage film and interlaced portions
				for (int i = 0; i < 2; i++)
				{
					if (portionStatus[i] == 0) // Stop any portions we are in.
					{
						if (inPortion[i])
						{
							(static_cast<int[]>(portions[i][nextPortionIndex[i]]))[1] = sectionCount;
							/*                                if (portionLength[i] == 1) // This should help reduce random fluctuations, by removing length 1 portions
	 * I've now changed my mind about random fluctuations. I believe they are good, because they occur when TIVTC is on the verge of making
	 * a wrong decision. Instead of continuing with this decision, which would then regard this section of the film as progressive, leaving combing
	 * this now has the effect of dramatically increasing the number of portions, forcing the whole thing to be deinterlaced, which is better,
	 * as it leaves no residual combing.
	 * 
	 * Edit again: i've left this section commented out, but the other section which removes length 1 progressive sections, I've left in, as it is
	 * safer to deinterlace progressive stuff than vice versa.
							{
							    portions[i].RemoveAt(nextPortionIndex[i]);
							    nextPortionIndex[i]--;
							    numPortions[i]--;
							}
	*/
							nextPortionIndex[i]++;
							inPortion[i] = false;
						}
						portionLength[i] = 0;
					}
					else if (portionStatus[i] == 1) // Continue all portions, but don't start a new one.
					{
						portionLength[i]++;
					}
					else if (portionStatus[i] == 2) // Start a new portion, or continue an old one.
					{
						if (inPortion[i])
							portionLength[i]++;
						else
						{
							int startIndex = sectionCount - portionLength[i];
							int lastEndIndex = -2;
							if (nextPortionIndex[i] > 0)
								lastEndIndex = (static_cast<int[]>(portions[i][nextPortionIndex[i] - 1]))[1];
							if (startIndex - lastEndIndex > 1) // If the last portion ended more than 1 section ago. This culls trivial portions
							{
								portions[i].push_back(new int[2]);
								(static_cast<int[]>(portions[i][nextPortionIndex[i]]))[0] = startIndex;
								portionLength[i]++;
								numPortions[i]++;
							}
							else
							{
								nextPortionIndex[i]--;
							}
							inPortion[i] = true;
						}
					}
				}
				count = 0;
			}
			line = instream->ReadLine();
		}
		instream->Close();

		int array_Renamed[3] = {numInt, numProg, numTC};
		Array::Sort(array_Renamed);

		analysis = QString::Format("Progressive sections: {0}\r\nInterlaced sections: {1}\r\nPartially Static Sections: {2}\r\nFilm Sections: {3}\r\n", numProg, numInt, numUseless, numTC);

		if (numInt + numProg + numTC < settings::MinimumUsefulSections)
		{
			if (checkDecimate(sectionsWithMovingFrames))
			{
				analysis += "Source is declared as repetition-upconverted. Decimation is required\r\n";
				finishProcessing();
				return;
			}
			else
			{
				analysis += "Source does not have enough data. This either comes from an internal error or an unexpected source type.\r\n";
				type = NOT_ENOUGH_SECTIONS;
				finishProcessing();
				return;
			}
		}

		if (array_Renamed[1] < static_cast<double>(array_Renamed[0] + array_Renamed[1] + array_Renamed[2]) / 100.0 * settings::HybridPercent)
		{
			if (array_Renamed[2] == numProg)
			{
				analysis += "Source is declared progressive.\r\n";
				type = PROGRESSIVE;
				checkDecimate(sectionsWithMovingFrames);
			}
			else if (array_Renamed[2] == numInt)
			{
				analysis += "Source is declared interlaced.\r\n";
				type = INTERLACED;
				stillWorking = true;
				runScript(1, -1, "#no trimming"); //field order script
			}
			else
			{
				analysis += "Source is declared telecined.\r\n";
				type = FILM;
				stillWorking = true;
				runScript(1, -1, "#no trimming"); //field order script
			}
		}
		else
		{
			if (array_Renamed[0] == numProg) // We have a hybrid film/ntsc. This is the most common
			{
				analysis += "Source is declared hybrid film/ntsc. Majority is ";
				if (array_Renamed[2] == numTC)
				{
					analysis += "film.\r\n";
					majorityFilm = true;
				}
				else
				{
					analysis += "ntsc (interlaced).\r\n";
					majorityFilm = false;
				}
				type = HYBRID_FILM_INTERLACED;
				stillWorking = true;
				runScript(1, -1, "#no trimming");

			}
			else if (array_Renamed[0] == numInt)
			{
				if (array_Renamed[0] > (double)(array_Renamed[0] + array_Renamed[1] + array_Renamed[2]) / 100.0 * settings::HybridPercent) // There is also a section of interlaced
				{
					analysis += "Source is declared hybrid film/ntsc. Majority is film.\r\n";
					type = HYBRID_FILM_INTERLACED;
					majorityFilm = true;
					stillWorking = true;
					runScript(1, -1, "#no trimming");
				}
				else
				{
					analysis += "Source is declared hybrid film/progressive.\r\n";
					majorityFilm = (array_Renamed[2] == numTC);
					type = HYBRID_PROGRESSIVE_FILM;

					// Although we don't actually end up using portions for this situation, 
					// it is good to only analyse the sections which are actually film.
					int frameCount = -1;
					QString trimLine = "#no trimming";
					QString textLines = "The number of portions is " + numPortions[1] + ".\r\n";
					if (numPortions[1] <= maxPortions)
					{
						textLines = findPortions(portions[1], selectEvery, selectLength, numPortions[1], sectionCount, inputFrames, "telecined", trimLine, frameCount);
					}
					stillWorking = true;
					runScript(1, frameCount, trimLine);
				}
			}
			else if (array_Renamed[0] == numTC)
			{
				if (array_Renamed[0] > (double)(array_Renamed[0] + array_Renamed[1] + array_Renamed[2]) / 100.0 * settings::HybridPercent) // There is also a section of film
				{
					analysis += "Source is declared hybrid film/interlaced. Majority is interlaced.\r\n";
					type = HYBRID_FILM_INTERLACED;
					majorityFilm = false;

					stillWorking = true;
					runScript(1, -1, "#no trimming");
				}
				else
				{
					analysis += "Source is declared hybrid progressive/interlaced. ";

					type = HYBRID_PROGRESSIVE_INTERLACED;

					usingPortions = false;
					int frameCount = -1;
					QString trimLine = "#no trimming";
					QString textLines = "The number of portions is " + numPortions[0] + ".\r\n";

					if (settings::PortionsAllowed && numPortions[0] <= maxPortions && array_Renamed[2] < (static_cast<double>(array_Renamed[1]) * settings::PortionThreshold))
					{
						textLines = findPortions(portions[0], selectEvery, selectLength, numPortions[0], sectionCount, inputFrames, "interlaced", trimLine, frameCount);
						usingPortions = true;
						analysis += textLines;
					}
					else
					{
						analysis += "This should be deinterlaced by a deinterlacer that tries to weave it before deinterlacing.\r\n";
					}
					stillWorking = true;
					runScript(1, frameCount, trimLine); //field order script
				}
			}
		}
		if (!stillWorking)
			finishProcessing();
	}

	void <missing_class_definition>::finishProcessing()
	{
		if (error)
		{
			finishedAnalysis(0, true, errorMessage);
			return;
		}

		if (!continueWorking)
		{
			return;
		}

		if (fieldOrder == VARIABLE && d2vFileName->Length == 0) // We are stuck for field order information, lets just go for what we have most of
			fieldOrder = (bffCount > tffCount) ? BFF : TFF;

		SourceInfo *info = new SourceInfo();
		info->sourceType = type;
		info->decimateM = decimateM;
		info->fieldOrder = fieldOrder;
		info->majorityFilm = majorityFilm;
		info->analysisResult = analysis;

		finishedAnalysis(info, false, 0);

	}

	void <missing_class_definition>::analyse()
	{
		runScript(0, -1, "#no trimming");
	}

	void <missing_class_definition>::stop()
	{
		continueWorking = false;
	}
}
