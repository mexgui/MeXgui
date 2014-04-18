#include "MeXgui.AviSynthWindow.h"




//using namespace System::Collections::Generic;



//using namespace System::Globalization;



//using namespace System::Text;


using namespace MeXgui::core::util;

namespace MeXgui
{

	AviSynthWindow::AviSynthWindow(MainForm *mainForm)
	{
		InitializeInstanceFields();
		scriptRefresh--;
		eventsOn = false;
		this->mainForm = mainForm;
		InitializeComponent();

		this->controlsToDisable = QVector<Control*>();
		this->controlsToDisable.push_back(reopenOriginal);
		this->controlsToDisable.push_back(filtersGroupbox);
		this->controlsToDisable.push_back(deinterlacingGroupBox);
		this->controlsToDisable.push_back(mpegOptGroupBox);
		this->controlsToDisable.push_back(aviOptGroupBox);
		this->controlsToDisable.push_back(resNCropGroupbox);
		this->controlsToDisable.push_back(previewAvsButton);
		this->controlsToDisable.push_back(saveButton);
		this->controlsToDisable.push_back(arChooser);
		this->controlsToDisable.push_back(inputDARLabel);
		this->controlsToDisable.push_back(signalAR);
		this->controlsToDisable.push_back(avisynthScript);
		this->controlsToDisable.push_back(openDLLButton);
		this->controlsToDisable.push_back(dgOptions);
		enableControls(false);
		script = new StringBuilder();

		this->resizeFilterType->Items->Clear();
		this->resizeFilterType->DataSource = ScriptServer::ListOfResizeFilterType;
		this->resizeFilterType->BindingContext = new BindingContext();
		this->noiseFilterType->Items->Clear();
		this->noiseFilterType->DataSource = ScriptServer::ListOfDenoiseFilterType;
		this->noiseFilterType->BindingContext = new BindingContext();
		this->deintFieldOrder->Items->Clear();
		this->deintFieldOrder->DataSource = ScriptServer::ListOfFieldOrders;
		this->deintFieldOrder->BindingContext = new BindingContext();
		this->deintSourceType->Items->Clear();
		this->deintSourceType->DataSource = ScriptServer::ListOfSourceTypes;
		this->deintSourceType->BindingContext = new BindingContext();
		this->cbNvDeInt->Items->Clear();
		this->cbNvDeInt->DataSource = ScriptServer::ListOfNvDeIntType;
		this->cbNvDeInt->BindingContext = new BindingContext();

		deintFieldOrder->SelectedIndex = -1;
		deintSourceType->SelectedIndex = -1;
		cbNvDeInt->SelectedIndex = 0;
		cbCharset->SelectedIndex = 0;
		modValueBox->SelectedIndex = 0;
		bAllowUpsizing = false;

		this->originalScript = "";
		this->isPreviewMode = false;

//C# TO C++ CONVERTER WARNING: C# to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
		delete player;
		this->crop->Checked = false;
		this->cropLeft->Value = 0;
		this->cropTop->Value = 0;
		this->cropRight->Value = 0;
		this->cropBottom->Value = 0;

		deinterlaceType->DataSource = new DeinterlaceFilter[] {new DeinterlaceFilter("Do nothing (source not detected)", "#blank deinterlace line")};

		avsProfile->setManager(MainForm::Instance->getProfiles());

		eventsOn = true;
		updateEverything(true, true, resize->Checked);
	}

	void AviSynthWindow::ProfileChanged()
	{
		this->setSettings(GetProfileSettings());
	}

	AviSynthWindow::AviSynthWindow(MainForm *mainForm, const QString &videoInput)
	{
		InitializeInstanceFields();
		scriptRefresh--;
		openVideoSource(videoInput, 0);
		updateEverything(true, true, resize->Checked);
	}

	AviSynthWindow::AviSynthWindow(MainForm *mainForm, const QString &videoInput, const QString &indexFile)
	{
		InitializeInstanceFields();
		scriptRefresh--;
		openVideoSource(videoInput, indexFile);
		updateEverything(true, true, resize->Checked);
	}

	void AviSynthWindow::OnClosing(CancelEventArgs *e)
	{
		if (player != 0)
			player->Close();
		if (detector != 0)
			detector->stop();
//C# TO C++ CONVERTER WARNING: C# to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
		delete detector;
		System::Windows::Forms::Form::OnClosing(e);
	}

	void AviSynthWindow::input_FileSelected(FileBar *sender, FileBarEventArgs *args)
	{
		scriptRefresh--;
		openVideoSource(input->getFilename(), 0);
		updateEverything(true, true, resize->Checked);
	}

	void AviSynthWindow::openDLLButton_Click()
	{
		this->openFilterDialog->InitialDirectory = MainForm::Instance->getSettings()->getAvisynthPluginsPath();
		if (this->openFilterDialog->show() == System::Windows::Forms::DialogResult::OK)
		{
			dllPath->Text = openFilterDialog->FileName;
			QString temp = avisynthScript->Text;
			script = new StringBuilder();
			script->Append("LoadPlugin(\"" + openFilterDialog->FileName + "\")\r\n");
			script->Append(temp);
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
			avisynthScript->Text = script->ToString();
		}
	}

	void AviSynthWindow::previewButton_Click()
	{
		// If the player is null, create a new one.
		// Otherwise use the existing player to load the latest preview.
		if (player == 0 || player->IsDisposed)
			player = new VideoPlayer();

		if (player->loadVideo(mainForm, avisynthScript->Text, REGULAR, false, true, player->getCurrentFrame(), true))
		{
			player->disableIntroAndCredits();
			reader = player->getReader();
			isPreviewMode = true;
			sendCropValues();
			if (this->Visible)
				player->Show();
			player->SetScreenSize();
			this->TopMost = player->TopMost = true;
			if (!mainForm->getSettings()->getAlwaysOnTop())
				this->TopMost = player->TopMost = false;
		}
	}

	void AviSynthWindow::saveButton_Click()
	{
		QString fileName = videoOutput->getFilename();
		writeScript(fileName);
		if (onSaveLoadScript->Checked)
		{
			if (player != 0)
				player->Close();
			this->Close();
			OpenScript(fileName);
		}
	}

	QString AviSynthWindow::generateScript()
	{
		script = new StringBuilder();
		//scriptLoad = new StringBuilder(); Better to use AviSynth plugin dir and it is easier for avs templates/profiles

		QString inputLine = "#input";
		QString deinterlaceLines = "#deinterlace";
		QString denoiseLines = "#denoise";
		QString cropLine = "#crop";
		QString resizeLine = "#resize";

		double fps = static_cast<double>(fpsBox->Value);
		inputLine = ScriptServer::GetInputLine(this->input->getFilename(), this->indexFile, deinterlace->Checked, sourceType, colourCorrect->Checked, mpeg2Deblocking->Checked, flipVertical->Checked, fps, dss2->Checked);

		if (nvDeInt->Enabled)
		{
			if (nvDeInt->Checked)
				inputLine += ScriptServer::GetNvDeInterlacerLine(nvDeInt->Checked, &static_cast<NvDeinterlacerType>((dynamic_cast<EnumProxy*>(cbNvDeInt->SelectedItem))->getRealValue()));
			if (nvResize->Checked)
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
				inputLine += ", resize_w=" + horizontalResolution->Value->ToString() + ", resize_h=" + verticalResolution->Value->ToString();
			inputLine += ")";
		}
		if (deinterlace->Checked && dynamic_cast<DeinterlaceFilter*>(deinterlaceType->SelectedItem) != 0)
			deinterlaceLines = (static_cast<DeinterlaceFilter*>(deinterlaceType->SelectedItem))->getScript();
		cropLine = ScriptServer::GetCropLine(crop->Checked, getCropping());

		// resize options
		int iWidth = static_cast<int>(horizontalResolution->Maximum);
		int iHeight = static_cast<int>(verticalResolution->Maximum);
		if (file != 0)
		{
			iWidth = static_cast<int>(file->getVideoInfo()->Width);
			iHeight = static_cast<int>(file->getVideoInfo()->Height);
		}
		if (!nvResize->Checked)
			resizeLine = ScriptServer::GetResizeLine(resize->Checked, static_cast<int>(horizontalResolution->Value), static_cast<int>(verticalResolution->Value), 0, 0, static_cast<ResizeFilterType>((dynamic_cast<EnumProxy*>(resizeFilterType->SelectedItem))->getRealValue()), crop->Checked, getCropping(), iWidth, iHeight);

		denoiseLines = ScriptServer::GetDenoiseLines(noiseFilter->Checked, static_cast<DenoiseFilterType>((dynamic_cast<EnumProxy*>(noiseFilterType->SelectedItem))->getRealValue()));

		QString newScript = ScriptServer::CreateScriptFromTemplate(GetProfileSettings()->getTemplate(), inputLine, cropLine, resizeLine, denoiseLines, deinterlaceLines);

		if (this->signalAR->Checked && suggestedDar.HasValue)
			newScript = QString::Format("# Set DAR in encoder to {0} : {1}. The following line is for automatic signalling\r\nglobal MeXgui_darx = {0}\r\nglobal MeXgui_dary = {1}\r\n", suggestedDar.Value::X, suggestedDar.Value::Y) + newScript;

		if (this->SubtitlesPath->Text != "")
		{
			newScript += "\r\nLoadPlugin(\"" + Path::Combine(MainForm::Instance->getSettings()->getAvisynthPluginsPath(), "VSFilter.dll") + "\")";
			if (cbCharset->Enabled)
			{
				QString charset = CharsetValue();
				newScript += "\r\nTextSub(\"" + SubtitlesPath->Text + "\"" + ", " + charset + ")\r\n";
			}
			else
				newScript += "\r\nVobSub(\"" + SubtitlesPath->Text + "\")\r\n";
		}
		return newScript;
	}

	AviSynthSettings *AviSynthWindow::GetProfileSettings()
	{
		return static_cast<AviSynthSettings*>(avsProfile->getSelectedProfile()->BaseSettings);
	}

	void AviSynthWindow::showScript(bool bForce)
	{
		if (bForce)
			scriptRefresh++;
		if (scriptRefresh < 1)
			return;

		QString oldScript = avisynthScript->Text;
		avisynthScript->Text = this->generateScript();
		if (!oldScript.Equals(avisynthScript->Text))
			chAutoPreview_CheckedChanged(0, 0);
	}

	void AviSynthWindow::openVideoSource(const QString &videoInput, const QString &indexFileTemp)
	{
		QString ext, projectPath, fileNameNoPath;

		indexFile = indexFileTemp;
		projectPath = mainForm->getSettings()->getDefaultOutputDir();
		if (indexFile.empty())
		{
			ext = Path::GetExtension(videoInput)->ToLower(System::Globalization::CultureInfo::InvariantCulture);
			if (projectPath.empty())
				projectPath = Path::GetDirectoryName(videoInput);
			fileNameNoPath = Path::GetFileName(videoInput);
		}
		else
		{
			ext = Path::GetExtension(indexFile)->ToLower(System::Globalization::CultureInfo::InvariantCulture);
			if (projectPath.empty())
				projectPath = Path::GetDirectoryName(indexFile);
			fileNameNoPath = Path::GetFileName(indexFile);
		}
		videoOutput->setFilename(Path::Combine(projectPath, Path::ChangeExtension(fileNameNoPath, ".avs")));

//C# TO C++ CONVERTER NOTE: The following 'switch' operated on a string variable and was converted to C++ 'if-else' logic:
//		switch (ext)
//ORIGINAL LINE: case ".avs":
		if (ext == ".avs")
		{
				sourceType = avs;
				videoOutput->setFilename(Path::Combine(projectPath, Path::ChangeExtension(fileNameNoPath, "_new.avs"))); // to avoid overwritten
				openAVSScript(videoInput);
		}
//ORIGINAL LINE: case ".d2v":
		else if (ext == ".d2v")
		{
				sourceType = d2v;
				openVideo(videoInput);
		}
//ORIGINAL LINE: case ".dga":
		else if (ext == ".dga")
		{
				sourceType = dga;
				openVideo(videoInput);
		}
//ORIGINAL LINE: case ".dgi":
		else if (ext == ".dgi")
		{
				sourceType = dgi;
				openVideo(videoInput);
		}
//ORIGINAL LINE: case ".ffindex":
		else if (ext == ".ffindex")
		{
				sourceType = ffindex;
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'EndsWith' method:
				if (videoInput.ToLower(System::Globalization::CultureInfo::InvariantCulture)->EndsWith(".ffindex"))
					openVideo(videoInput.substr(0, videoInput.length() - 8));
				else
					openVideo(videoInput);
		}
//ORIGINAL LINE: case ".vdr":
		else if (ext == ".vdr")
		{
				sourceType = vdr;
				openVDubFrameServer(videoInput);
		}
		else
		{
				if (File::Exists(videoInput + ".ffindex"))
				{
					sourceType = ffindex;
					openVideo(videoInput);
				}
				else
				{
					int iResult = mainForm->getDialogManager()->AVSCreatorOpen(videoInput);
					switch (iResult)
					{
						case 0:
							OneClickWindow *ocmt = new OneClickWindow(mainForm);
							ocmt->setInput(videoInput);
							ocmt->Show();
							this->Close();
							break;
						case 1:
							FileIndexerWindow *fileIndexer = new FileIndexerWindow(mainForm);
							fileIndexer->setConfig(videoInput, 0, 2, true, true, true, false);
							fileIndexer->Show();
							this->Close();
							break;
						default:
							sourceType = directShow;
							openDirectShow(videoInput);
							break;
					}
				}
		}
		setSourceInterface();
	}

	void AviSynthWindow::writeScript(const QString &path)
	{
		try
		{
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//			using (StreamWriter sw = new StreamWriter(path, false, Encoding.Default))
			StreamWriter *sw = new StreamWriter(path, false, Encoding::Default);
			try
			{
				sw->Write(avisynthScript->Text);
				sw->Close();
			}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
			finally
			{
				if (sw != 0)
					sw.Dispose();
			}
		}
		catch (IOException *i)
		{
			MessageBox::Show("An error occurred when trying to save the AviSynth script:\r\n" + i->Message);
		}
	}

	void AviSynthWindow::setSourceInterface()
	{
		switch (this->sourceType)
		{
			case d2v:
			case dga:
			case mpeg2:
				this->mpeg2Deblocking->Enabled = true;
				this->colourCorrect->Enabled = true;
				this->fpsBox->Enabled = false;
				this->flipVertical->Enabled = false;
				this->flipVertical->Checked = false;
				this->cbNvDeInt->Enabled = false;
				this->nvDeInt->Enabled = false;
				this->nvDeInt->Checked = false;
				this->nvResize->Enabled = false;
				this->nvResize->Checked = false;
				this->dss2->Enabled = false;
				this->tabSources->SelectedTab = tabPage1;
				break;
			case vdr:
			case avs:
				this->mpeg2Deblocking->Checked = false;
				this->mpeg2Deblocking->Enabled = false;
				this->colourCorrect->Enabled = false;
				this->colourCorrect->Checked = false;
				this->flipVertical->Enabled = false;
				this->flipVertical->Checked = false;
				this->dss2->Enabled = false;
				this->fpsBox->Enabled = false;
				this->cbNvDeInt->Enabled = false;
				this->nvDeInt->Enabled = false;
				this->nvDeInt->Checked = false;
				this->nvResize->Enabled = false;
				this->nvResize->Checked = false;
				this->tabSources->SelectedTab = tabPage1;
				break;
			case ffindex:
				this->mpeg2Deblocking->Checked = false;
				this->mpeg2Deblocking->Enabled = false;
				this->colourCorrect->Enabled = false;
				this->colourCorrect->Checked = false;
				this->dss2->Enabled = false;
				this->fpsBox->Enabled = false;
				this->flipVertical->Enabled = true;
				this->cbNvDeInt->Enabled = false;
				this->nvDeInt->Enabled = false;
				this->nvDeInt->Checked = false;
				this->nvResize->Enabled = false;
				this->nvResize->Checked = false;
				this->tabSources->SelectedTab = tabPage1;
				break;
			case directShow:
				this->mpeg2Deblocking->Checked = false;
				this->mpeg2Deblocking->Enabled = false;
				this->colourCorrect->Enabled = false;
				this->colourCorrect->Checked = false;
				this->dss2->Enabled = true;
				this->fpsBox->Enabled = true;
				this->flipVertical->Enabled = true;
				this->cbNvDeInt->Enabled = false;
				this->nvDeInt->Enabled = false;
				this->nvDeInt->Checked = false;
				this->nvResize->Enabled = false;
				this->nvResize->Checked = false;
				this->tabSources->SelectedTab = tabPage2;
				break;
			case dgi:
				this->mpeg2Deblocking->Checked = false;
				this->mpeg2Deblocking->Enabled = false;
				this->colourCorrect->Enabled = false;
				this->colourCorrect->Checked = false;
				this->flipVertical->Enabled = false;
				this->flipVertical->Checked = false;
				this->dss2->Enabled = false;
				this->fpsBox->Enabled = false;
				this->cbNvDeInt->Enabled = false;
				this->nvDeInt->Enabled = true;
				this->nvDeInt->Checked = false;
				this->nvResize->Enabled = true;
				this->nvResize->Checked = false;
				this->cbNvDeInt->SelectedIndex = 0;
				this->tabSources->SelectedTab = tabPage3;
				break;
		}
	}

	void AviSynthWindow::checkNVCompatibleFile(const QString &input)
	{
		bool flag = false;
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//		using (StreamReader sr = new StreamReader(input))
		StreamReader *sr = new StreamReader(input);
		try
		{
			QString line = sr->ReadLine();
			switch (this->sourceType)
			{
				case dgi:
					if (line.find("DGMPGIndexFileNV") != string::npos)
						flag = true;
					if (line.find("DGAVCIndexFileNV") != string::npos)
						flag = true;
					if (line.find("DGVC1IndexFileNV") != string::npos)
						flag = true;
					break;
			}
		}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
		finally
		{
			if (sr != 0)
				sr.Dispose();
		}
		if (!flag)
		{
			if (MessageBox::Show("You cannot use this option with the " + Path::GetFileName(input) + " file. It's not compatible...", "Information", MessageBoxButtons::OK, MessageBoxIcon::Information) == System::Windows::Forms::DialogResult::OK)
			{
				this->nvDeInt->Checked = false;
				this->nvResize->Checked = false;
			}
		}
	}

	const SourceInfo &AviSynthWindow::getDeintInfo() const
	{
		SourceInfo *info = new SourceInfo();
		try
		{
			info->sourceType = static_cast<SourceType>((static_cast<EnumProxy*>(deintSourceType->SelectedItem))->getTag());
		}
		catch (NullReferenceException *e1)
		{
			info->sourceType = UNKNOWN;
		}
		try
		{
			info->fieldOrder = static_cast<FieldOrder>((static_cast<EnumProxy*>(deintFieldOrder->SelectedItem))->getTag());
		}
		catch (NullReferenceException *e2)
		{
			info->fieldOrder = UNKNOWN;
		}
		info->decimateM = static_cast<int>(deintM->Value);
		try
		{
			info->majorityFilm = (static_cast<UserSourceType>((static_cast<EnumProxy*>(deintSourceType->SelectedItem))->getRealValue())) == HybridFilmInterlaced || (static_cast<UserSourceType>((static_cast<EnumProxy*>(deintSourceType->SelectedItem))->getRealValue())) == HybridProgressiveFilm;
		}
		catch (NullReferenceException *e3)
		{
		}
		info->isAnime = deintIsAnime->Checked;
		return info;
	}

	void AviSynthWindow::setDeintInfo(const SourceInfo &value)
	{
		if (value->sourceType == UNKNOWN || value->sourceType == NOT_ENOUGH_SECTIONS)
		{
			MessageBox::Show("Source detection couldn't determine the source type!", "Source detection failed", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}
		for (unknown::const_iterator o = deintSourceType->Items.begin(); o != deintSourceType->Items.end(); ++o)
		{
			if (static_cast<SourceType>((*o)->getTag()) == value->sourceType)
				deintSourceType->SelectedItem = *o;
		}
		for (unknown::const_iterator o = deintFieldOrder->Items.begin(); o != deintFieldOrder->Items.end(); ++o)
		{
			if (static_cast<FieldOrder>((*o)->getTag()) == value->fieldOrder)
				deintFieldOrder->SelectedItem = *o;
		}
		if (value->fieldOrder == UNKNOWN)
			deintFieldOrder->SelectedIndex = -1;
		deintM->Value = value->decimateM;
		if (value->sourceType == HYBRID_FILM_INTERLACED)
		{
			if (value->majorityFilm)
				deintSourceType->SelectedItem = ScriptServer::ListOfSourceTypes[static_cast<int>(HybridFilmInterlaced)];
			else
				deintSourceType->SelectedItem = ScriptServer::ListOfSourceTypes[static_cast<int>(HybridInterlacedFilm)];
		}
		this->deinterlaceType->DataSource = ScriptServer::GetDeinterlacers(value);
		this->deinterlaceType->BindingContext = new BindingContext();
	}

	void AviSynthWindow::openDirectShow(const QString &fileName)
	{
		if (!File::Exists(fileName))
		{
			MessageBox::Show(fileName + " could not be found", "File Not Found", MessageBoxButtons::OK);
			return;
		}
		else
		{
			DirectShow *ds = new DirectShow();
			if (!ds->checkRender(fileName)) // make sure graphedit can render the file
			{
				MessageBox::Show("Unable to render the file.\r\nYou probably don't have the correct filters installed", "Direct Show Error", MessageBoxButtons::OK);
				return;
			}

			QString tempAvs;
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'EndsWith' method:
			if (fileName.ToLower(System::Globalization::CultureInfo::InvariantCulture)->EndsWith(".avi"))
			{
				tempAvs = "AVISource(\"" + fileName + "\", audio=false)" + VideoUtil::getAssumeFPS(0, fileName);
			}
			else
			{
				QString frameRateString = "";
				try
				{
					MediaInfoFile *info = new MediaInfoFile(fileName);
					if (info->getVideoInfo()->HasVideo && info->getVideoInfo()->FPS > 0)
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
						frameRateString = info->getVideoInfo()->FPS.ToString(System::Globalization::CultureInfo::InvariantCulture);
				}
				catch (std::exception &e1)
				{
				}

				tempAvs = QString::Format("DirectShowSource(\"{0}\", audio=false{1}, convertfps=true){2}{3}", fileName, frameRateString == "" ? "" : (", fps=" + frameRateString), VideoUtil::getAssumeFPS(0, fileName), this->flipVertical->Checked ? ".FlipVertical()" : "");
				if (MainForm::Instance->getSettings()->getPortableAviSynth())
					tempAvs = "LoadPlugin(\"" + Path::Combine(Path::GetDirectoryName(MainForm::Instance->getSettings()->getAviSynthPath()), "directshowsource.dll") + "\")\r\n" + tempAvs;
			}
			if (file != 0)
				delete file;
			openVideo(tempAvs, fileName, true);

		}
	}

	void AviSynthWindow::openVDubFrameServer(const QString &fileName)
	{
		if (!File::Exists(fileName))
		{
			MessageBox::Show(fileName + " could not be found","File Not Found",MessageBoxButtons::OK);
			return;
		}
		openVideo("AviSource(\"" + fileName + ", audio=false\")\r\n", fileName, true);
	}

	void AviSynthWindow::openAVSScript(const QString &fileName)
	{
		if (!File::Exists(fileName))
		{
			MessageBox::Show(fileName + " could not be found", "File Not Found", MessageBoxButtons::OK);
			return;
		}
		openVideo("Import(\"" + fileName + "\")\r\n", fileName, true);
	}

	void AviSynthWindow::enableControls(bool enable)
	{
		for (QVector<Control*>::const_iterator ctrl = this->controlsToDisable.begin(); ctrl != this->controlsToDisable.end(); ++ctrl)
			(*ctrl)->Enabled = enable;

		if (deintSourceType->SelectedIndex < 1)
		{
			deinterlace->Enabled = false;
			deinterlace->Checked = false;
		}
		else
			deinterlace->Enabled = true;
	}

	void AviSynthWindow::openVideo(const QString &videoInput)
	{
		if (indexFile.empty())
			openVideo(videoInput, videoInput, false);
		else
			openVideo(videoInput + "|" + indexFile, videoInput, false);
	}

	bool AviSynthWindow::showOriginal()
	{
		int iCurrentFrame = -1;
		if (player == 0 || player->IsDisposed)
			player = new VideoPlayer();
		else
			iCurrentFrame = player->getCurrentFrame();
		this->isPreviewMode = false;
		if (player->loadVideo(mainForm, originalScript, REGULAR, false, originalInlineAvs, iCurrentFrame, true))
		{
			reader = player->getReader();
			sendCropValues();
			if (this->Visible)
				player->Show();
			player->SetScreenSize();
			this->TopMost = player->TopMost = true;
			if (!mainForm->getSettings()->getAlwaysOnTop())
				this->TopMost = player->TopMost = false;
			return true;
		}
		else
		{
			player->Close();
//C# TO C++ CONVERTER WARNING: C# to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
			delete player;
			return false;
		}
	}

	void AviSynthWindow::openVideo(const QString &videoInputScript, const QString &strSourceFileName, bool inlineAvs)
	{
		this->crop->Checked = false;
		this->input->setFilename("");
		this->originalScript = videoInputScript;
		this->originalInlineAvs = inlineAvs;
		if (player != 0)
			delete player;
		bool videoLoaded = showOriginal();
		enableControls(videoLoaded);
		if (videoLoaded)
		{
			eventsOn = false;
			this->input->setFilename(strSourceFileName);
			file = player->getFile();
			reader = player->getReader();
			this->fpsBox->Value = static_cast<decimal>(file->getVideoInfo()->FPS);
			if (file->getVideoInfo()->FPS.Equals(25.0)) // disable ivtc for pal sources
				this->tvTypeLabel->Text = "PAL";
			else
				this->tvTypeLabel->Text = "NTSC";

			if (horizontalResolution->Maximum < file->getVideoInfo()->Width)
				horizontalResolution->Maximum = file->getVideoInfo()->Width;
			horizontalResolution->Value = file->getVideoInfo()->Width;
			if (verticalResolution->Maximum < file->getVideoInfo()->Height)
				verticalResolution->Maximum = file->getVideoInfo()->Height;
			verticalResolution->Value = file->getVideoInfo()->Height;

			if (File::Exists(strSourceFileName))
			{
				MediaInfoFile *oInfo = new MediaInfoFile(strSourceFileName);
				arChooser->setValue(oInfo->getVideoInfo()->DAR);
			}
			else
				arChooser->setValue(file->getVideoInfo()->DAR);

			cropLeft->Maximum = cropRight->Maximum = file->getVideoInfo()->Width;
			cropTop->Maximum = cropBottom->Maximum = file->getVideoInfo()->Height;
			eventsOn = true;
		}
	}

	void AviSynthWindow::calcAspectError()
	{
		if (file == 0)
		{
			lblAspectError->BackColor = System::Drawing::SystemColors::Window;
			lblAspectError->Text = "0.00000%";
			return;
		}

		// get output dimension
		int outputHeight = static_cast<int>(verticalResolution->Value);
		int outputWidth = static_cast<int>(horizontalResolution->Value);
		if (!resize->Checked)
		{
			outputHeight = static_cast<int>(file->getVideoInfo()->Height) - getCropping()->top - getCropping()->bottom;
			outputWidth = static_cast<int>(file->getVideoInfo()->Width) - getCropping()->left - getCropping()->right;
		}

		decimal aspectError = Resolution::GetAspectRatioError(static_cast<int>(file->getVideoInfo()->Width), static_cast<int>(file->getVideoInfo()->Height), outputWidth, outputHeight, getCropping(), arChooser->getValue(), signalAR->Checked, suggestedDar);
		lblAspectError->Text = QString::Format("{0:0.00000%}", aspectError);
		if (!signalAR->Checked || floor(abs(aspectError) * 100000000) <= this->GetProfileSettings()->getAcceptableAspectError() * 1000000)
			lblAspectError->ForeColor = System::Drawing::SystemColors::WindowText;
		else
			lblAspectError->ForeColor = System::Drawing::Color::Red;
	}

	void AviSynthWindow::changeNumericUpDownColor(NumericUpDown *oControl, bool bMarkRed)
	{
		if (oControl->Enabled)
		{
			if (bMarkRed)
				oControl->ForeColor = System::Drawing::Color::Red;
			else
				oControl->ForeColor = System::Drawing::SystemColors::WindowText;
			oControl->BackColor = System::Drawing::SystemColors::Window;
		}
		else
		{
			if (bMarkRed)
				oControl->BackColor = System::Drawing::Color::FromArgb(255, 255, 180, 180);
			else
				oControl->BackColor = System::Drawing::SystemColors::Window;
			oControl->ForeColor = System::Drawing::SystemColors::WindowText;
		}
	}

	void AviSynthWindow::sendCropValues()
	{
		if (player == 0 || !player->Visible)
			return;

		if (isPreviewMode)
			player->crop(0, 0, 0, 0);
		else
			player->crop(getCropping());
	}

	void AviSynthWindow::deinterlace_CheckedChanged()
	{
		if (deinterlace->Checked)
		{
			deinterlaceType->Enabled = true;
			if (deinterlaceType->SelectedIndex == -1)
				deinterlaceType->SelectedIndex = 0; // make sure something is selected
		}
		else
			deinterlaceType->Enabled = false;

		if (sender != 0 && e != 0)
			showScript(false);
	}

	void AviSynthWindow::noiseFilter_CheckedChanged()
	{
		if (noiseFilter->Checked)
		{
			this->noiseFilterType->Enabled = true;
		}
		else
			this->noiseFilterType->Enabled = false;

		if (sender != 0 && e != 0)
			showScript(false);
	}

	void AviSynthWindow::autoCropButton_Click()
	{
		if (isPreviewMode || player == 0 || !player->Visible)
		{
			MessageBox::Show(this, "No AutoCropping without the original video window open", "AutoCropping not possible",MessageBoxButtons::OK,MessageBoxIcon::Error);
			return;
		}

		// don't lock up the GUI, start a new thread
		this->Cursor = System::Windows::Forms::Cursors::WaitCursor;
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
		System::Threading::Thread *t = new System::Threading::Thread(new System::Threading::ThreadStart(delegate
		{
			CropValues *final = Autocrop::autocrop(reader);
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
			Invoke(new MethodInvoker(delegate
			{
				setCropValues(final);
			}
		   ));
		}
	   ));
		t->IsBackground = true;
		t->Start();
	}

	void AviSynthWindow::setCropValues(CropValues *cropValues)
	{
		this->Cursor = System::Windows::Forms::Cursors::Default;
		bool error = (cropValues->left < 0);
		if (!error)
		{
			eventsOn = false;
			cropLeft->Value = cropValues->left;
			cropTop->Value = cropValues->top;
			cropRight->Value = cropValues->right;
			cropBottom->Value = cropValues->bottom;
			if (!crop->Checked)
				crop->Checked = true;
			eventsOn = true;
			updateEverything(true, false, false);
		}
		else
			MessageBox::Show("I'm afraid I was unable to find more than 5 frames that have matching crop values");
	}

	void AviSynthWindow::setSettings(const AviSynthSettings &value)
	{
		eventsOn = false;
		this->resizeFilterType->SelectedItem = EnumProxy::Create(value->getResizeMethod());
		this->noiseFilterType->SelectedItem = EnumProxy::Create(value->getDenoiseMethod());
		this->mpeg2Deblocking->Checked = value->getMPEG2Deblock();
		this->colourCorrect->Checked = value->getColourCorrect();
		this->deinterlace->Checked = value->getDeinterlace();
		this->noiseFilter->Checked = value->getDenoise();
		this->resize->Checked = value->getResize();
		this->mod16Box->SelectedIndex = static_cast<int>(value->getMod16Method());
		this->signalAR->Checked = (value->getMod16Method() != none);
		this->dss2->Checked = value->getDSS2();
		this->bAllowUpsizing = value->getUpsize();
		if (!bAllowUpsizing && file != 0)
		{
			horizontalResolution->Maximum = file->getVideoInfo()->Width;
			verticalResolution->Maximum = file->getVideoInfo()->Height;
		}
		else
			horizontalResolution->Maximum = verticalResolution->Maximum = 9999;
		this->modValueBox->SelectedIndex = static_cast<int>(value->getModValue());
		eventsOn = true;
		updateEverything(true, false, value->getResize());
	}

	const CropValues &AviSynthWindow::getCropping() const
	{
		CropValues *returnValue = new CropValues();
		if (crop->Checked)
		{
			returnValue->bottom = static_cast<int>(cropBottom->Value);
			returnValue->top = static_cast<int>(cropTop->Value);
			returnValue->left = static_cast<int>(cropLeft->Value);
			returnValue->right = static_cast<int>(cropRight->Value);
			if (getMod16Method() == overcrop)
				ScriptServer::overcrop(returnValue, static_cast<modValue>(modValueBox->SelectedIndex));
			else if (getMod16Method() == mod4Horizontal)
				ScriptServer::cropMod4Horizontal(returnValue);
			else if (getMod16Method() == undercrop)
				ScriptServer::undercrop(returnValue, static_cast<modValue>(modValueBox->SelectedIndex));
		}
		return returnValue;
	}

	const mod16Method &AviSynthWindow::getMod16Method() const
	{
		mod16Method m = static_cast<mod16Method>(mod16Box->SelectedIndex);
		if (!mod16Box->Enabled)
			m = none;
		return m;
	}

	void AviSynthWindow::analyseButton_Click()
	{
		if (input->getFilename().length() > 0)
		{
			if (detector == 0) // We want to start the analysis
			{
				QString source = ScriptServer::GetInputLine(input->getFilename(), indexFile, false, sourceType, false, false, false, 25, false);
				if (nvDeInt->Enabled)
					source += ")";
				detector = new SourceDetector(source, input->getFilename(), deintIsAnime->Checked, mainForm->getSettings()->getSourceDetectorSettings(), new UpdateSourceDetectionStatus(this, &AviSynthWindow::analyseUpdate), new FinishedAnalysis(this, &AviSynthWindow::finishedAnalysis));
					detector->analyse();
					deintStatusLabel->Text = "Analysing...";
					analyseButton->Text = "Abort";
			}
			else // We want to cancel the analysis
			{
				detector->stop();
				deintStatusLabel->Text = "Analysis aborted!";
//C# TO C++ CONVERTER WARNING: C# to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
				delete detector;
				analyseButton->Text = "Analyse";
				this->deintProgressBar->Value = 0;
			}
		}
		else
			MessageBox::Show("Can't run any analysis as there is no selected video to analyse.", "Please select a video input file", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}

	void AviSynthWindow::finishedAnalysis(SourceInfo *info, bool error, const QString &errorMessage)
	{
		if (error)
		{
			detector->stop();
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
			Invoke(new MethodInvoker(delegate
			{
				MessageBox::Show(this, errorMessage, "Error in analysis", MessageBoxButtons::OK, MessageBoxIcon::Error);
				deintStatusLabel->Text = "Analysis failed!";
				analyseButton->Text = "Analyse";
				this->deintProgressBar->Value = 0;
			}
		   ));
		}
		else
		{
			try
			{
				info->isAnime = deintIsAnime->Checked;
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
				Invoke(new MethodInvoker(delegate
				{
					deintProgressBar->Enabled = false;
					this->setDeintInfo(info);
					if (deintSourceType->SelectedIndex < 1)
					{
						deinterlace->Enabled = false;
						deinterlace->Checked = false;
					}
					else
						deinterlace->Enabled = true;
						if (deinterlaceType->Text == "Do nothing")
							deinterlace->Checked = false;
							else
								deinterlace->Checked = true;
								deintStatusLabel->Text = "Analysis finished!";
								analyseButton->Text = "Analyse";
				}
			   ));
			}
			catch (std::exception &e1) // If we get any errors, it's most likely because the window was closed, so just ignore
			{
			}
		}
//C# TO C++ CONVERTER WARNING: C# to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
		delete detector;

		this->_oLog = mainForm->getAVSScriptCreatorLog();
		if (_oLog == 0)
		{
			_oLog = mainForm->getLog()->Info("AVS Script Creator");
			mainForm->setAVSScriptCreatorLog(_oLog);
		}
		_oLog->LogValue("Source detection: " + Path::GetFileName(input->getFilename()), info->analysisResult, error ? Warning : Information);
	}

	void AviSynthWindow::analyseUpdate(int amountDone, int total)
	{
		try
		{
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
			Invoke(new MethodInvoker(delegate
			{
				this->deintProgressBar->Value = amountDone;
				this->deintProgressBar->Maximum = total;
			}
		   ));
		}
		catch (std::exception &e1) // If we get any errors, just ignore -- it's only a cosmetic thing.
		{
		}
	}

	void AviSynthWindow::deintSourceType_SelectedIndexChanged()
	{
		deintM->Enabled = (deintSourceType->SelectedItem == ScriptServer::ListOfSourceTypes[static_cast<int>(Decimating)]);
		deintFieldOrder->Enabled = !(deintSourceType->SelectedItem == ScriptServer::ListOfSourceTypes[static_cast<int>(Progressive)]);
		deinterlaceType->DataSource = ScriptServer::GetDeinterlacers(getDeintInfo());
		deinterlaceType->BindingContext = new BindingContext();
		if (deintSourceType->SelectedIndex < 1)
		{
			deinterlace->Enabled = false;
			deinterlace->Checked = false;
		}
		else
			deinterlace->Enabled = true;

		if (sender != 0 && e != 0)
			showScript(false);
	}

	void AviSynthWindow::reopenOriginal_Click()
	{
		reopenOriginal->Enabled = false;
		reopenOriginal->Text = "Please wait...";
		if (chAutoPreview->Checked)
			chAutoPreview->Checked = false;
		else
			showOriginal();
		reopenOriginal->Enabled = true;
		reopenOriginal->Text = "Re-open original video player";
	}

	void AviSynthWindow::chAutoPreview_CheckedChanged()
	{
		if (chAutoPreview->Checked)
			previewButton_Click(0, 0);
		else if (this->isPreviewMode == true)
			showOriginal();
	}

	void AviSynthWindow::nvDeInt_CheckedChanged()
	{
		if (nvDeInt->Checked)
			cbNvDeInt->Enabled = true;
		else
			cbNvDeInt->Enabled = false;
		if (sender != 0 && e != 0)
			showScript(false);
	}

	void AviSynthWindow::nvDeInt_Click()
	{
		// just to be sure
		checkNVCompatibleFile(input->getFilename());
	}

	void AviSynthWindow::openSubtitlesButton_Click()
	{
		if (this->openSubsDialog->show() != System::Windows::Forms::DialogResult::OK)
			return;

		if (this->SubtitlesPath->Text != openSubsDialog->FileName)
		{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
			QString ext = Path::GetExtension(openSubsDialog->FileName)->ToString()->ToLower(System::Globalization::CultureInfo::InvariantCulture);
			this->SubtitlesPath->Text = openSubsDialog->FileName;
			if (ext == ".idx")
				cbCharset->Enabled = false;
			MessageBox::Show("Subtitles successfully added to the script...", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}
		else
			MessageBox::Show("The subtitles you chosen was already added...", "Warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		if (sender != 0 && e != 0)
			showScript(false);
	}

	QString AviSynthWindow::CharsetValue()
	{
		QString c = "";

		if (!SubtitlesPath->Text->empty())
		{
			switch (cbCharset->SelectedIndex)
			{
				case 1:
					c = "0";
					break;
				case 2:
					c = "2";
					break;
				case 3:
					c = "128";
					break;
				case 4:
				case 5:
					c = "129";
					break;
				case 6:
					c = "134";
					break;
				case 7:
					c = "136";
					break;
				case 8:
					c = "255";
					break;
				case 9:
					c = "130";
					break;
				case 10:
					c = "177";
					break;
				case 11:
					c = "178";
					break;
				case 12:
					c = "161";
					break;
				case 13:
					c = "162";
					break;
				case 14:
					c = "163";
					break;
				case 15:
					c = "222";
					break;
				case 16:
					c = "238";
					break;
				case 17:
					c = "204";
					break;
				case 18:
					c = "77";
					break;
				case 19:
					c = "186";
					break;
				default:
					c = "1";
					break;
			}
		}
		return c;
	}

	void AviSynthWindow::inputDARChanged(object *sender, const QString &val)
	{
		updateEverything(sender != 0, false, false);
	}

	void AviSynthWindow::updateEverything()
	{
		updateEverything(sender != 0, false, false);
	}

	void AviSynthWindow::updateEverything(bool bShowScript, bool bForceScript, bool bResizeEnabled)
	{
		if (!eventsOn)
			return;
		eventsOn = false;

		// update events may be triggered
		setModType();
		setCrop();
		setOutputResolution(bResizeEnabled);

		// no update events triggered
		calcAspectError();
		checkControls();

		eventsOn = true;
		if (bShowScript)
			showScript(bForceScript);
	}

	void AviSynthWindow::setModType()
	{
		if (!bAllowUpsizing && file != 0)
		{
			horizontalResolution->Maximum = file->getVideoInfo()->Width;
			verticalResolution->Maximum = file->getVideoInfo()->Height;
		}
		else
			horizontalResolution->Maximum = verticalResolution->Maximum = 9999;

		if (signalAR->Checked)
		{
			mod16Box->Enabled = true;
			if (mod16Box->SelectedIndex == -1)
				mod16Box->SelectedIndex = 0;
		}
		else
			mod16Box->Enabled = false;

		if (getMod16Method() == overcrop)
			crop->Text = "Crop (will be rounded up to selected mod)";
		else if (getMod16Method() == undercrop)
			crop->Text = "Crop (will be rounded down to sel. mod)";
		else
			crop->Text = "Crop";

		if (getMod16Method() == resize)
		{
			resize->Enabled = false;
			resize->Checked = true;
			suggestResolution->Enabled = false;
			suggestResolution->Checked = true;
		}
		else if (getMod16Method() == none)
		{
			resize->Enabled = true;
			suggestResolution->Enabled = resize->Checked;
			if (!suggestResolution->Enabled)
				suggestResolution->Checked = true;
		}
		else
		{
			resize->Checked = false;
			resize->Enabled = false;
			suggestResolution->Enabled = false;
			suggestResolution->Checked = true;
		}

		if (resize->Checked || (signalAR->Checked && (getMod16Method() == resize || getMod16Method() == overcrop || getMod16Method() == undercrop)))
			modValueBox->Enabled = true;
		else
			modValueBox->Enabled = false;
	}

	void AviSynthWindow::setCrop()
	{
		if (crop->Checked)
		{
			this->cropLeft->Enabled = true;
			this->cropTop->Enabled = true;
			this->cropRight->Enabled = true;
			this->cropBottom->Enabled = true;
			sendCropValues();
		}
		else
		{
			this->cropLeft->Enabled = false;
			this->cropTop->Enabled = false;
			this->cropRight->Enabled = false;
			this->cropBottom->Enabled = false;
			if (player != 0 && player->Visible)
				player->crop(0, 0, 0, 0);
		}

		if (file != 0)
		{
			int inputHeight = static_cast<int>(file->getVideoInfo()->Height) - getCropping()->top - getCropping()->bottom;
			int inputWidth = static_cast<int>(file->getVideoInfo()->Width) - getCropping()->left - getCropping()->right;
			if (!resize->Checked)
			{
				if (verticalResolution->Maximum < inputHeight)
					verticalResolution->Maximum = inputHeight;
				verticalResolution->Value = inputHeight;

				if (horizontalResolution->Maximum < inputWidth)
					horizontalResolution->Maximum = inputWidth;
				horizontalResolution->Value = inputWidth;
			}
			if (!bAllowUpsizing)
			{
				verticalResolution->Maximum = inputHeight;
				horizontalResolution->Maximum = inputWidth;
			}
			if (crop->Checked)
			{
				int mod = Resolution::GetModValue(static_cast<modValue>(modValueBox->SelectedIndex), static_cast<mod16Method>(mod16Box->SelectedIndex), signalAR->Checked);
				cropLeft->Maximum = static_cast<int>(file->getVideoInfo()->Width) - getCropping()->right - mod;
				cropRight->Maximum = static_cast<int>(file->getVideoInfo()->Width) - getCropping()->left - mod;
				cropTop->Maximum = static_cast<int>(file->getVideoInfo()->Height) - getCropping()->bottom - mod;
				cropBottom->Maximum = static_cast<int>(file->getVideoInfo()->Height) - getCropping()->top - mod;
			}
		}
	}

	void AviSynthWindow::setOutputResolution(bool bResizeEnabled)
	{
		if (resize->Checked)
		{
			this->horizontalResolution->Enabled = true;
			this->verticalResolution->Enabled = !suggestResolution->Checked;
		}
		else
			this->horizontalResolution->Enabled = this->verticalResolution->Enabled = false;

		suggestedDar = Nullable<Dar>();
		bool signalAR = this->signalAR->Checked;
		if (file == 0 || (!resize->Checked && !signalAR))
			return;

		int mod = Resolution::GetModValue(static_cast<modValue>(modValueBox->SelectedIndex), static_cast<mod16Method>(mod16Box->SelectedIndex), signalAR);
		horizontalResolution->Increment = verticalResolution->Increment = mod;

		int outputWidth = static_cast<int>(horizontalResolution->Value);
		int outputHeight = static_cast<int>(verticalResolution->Value);

		// remove upsizing or undersizing if value cannot be changed
		if (!resize->Checked && !((!bAllowUpsizing || bResizeEnabled) && static_cast<int>(file->getVideoInfo()->Width) - getCropping()->left - getCropping()->right < outputWidth))
			outputWidth = outputWidth - getCropping()->left - getCropping()->right;

		CropValues *paddingValues;
		CropValues *cropValues = getCropping()->Clone();

		bool resizeEnabled = resize->Checked;
		Resolution::GetResolution(static_cast<int>(file->getVideoInfo()->Width), static_cast<int>(file->getVideoInfo()->Height), arChooser->getRealValue(), cropValues, crop->Checked, mod, resizeEnabled, bAllowUpsizing, signalAR, suggestResolution->Checked, this->GetProfileSettings()->getAcceptableAspectError(), 0, 0, outputWidth, outputHeight, paddingValues, suggestedDar, 0);

		if (!resize->Checked && !suggestResolution->Checked) // just to make sure
			outputHeight = static_cast<int>(file->getVideoInfo()->Height) - getCropping()->top - getCropping()->bottom;

		if (outputWidth != static_cast<int>(horizontalResolution->Value))
		{
			if (horizontalResolution->Maximum < outputWidth)
				horizontalResolution->Maximum = outputWidth;
			horizontalResolution->Value = outputWidth;
		}
		if (outputHeight != static_cast<int>(verticalResolution->Value))
		{
			if (verticalResolution->Maximum < outputHeight)
				verticalResolution->Maximum = outputHeight;
			verticalResolution->Value = outputHeight;
		}

		if (suggestResolution->Checked)
			verticalResolution->Enabled = false;
		else
			verticalResolution->Enabled = resize->Checked;
	}

	void AviSynthWindow::checkControls()
	{
		if (resize->Checked && file != 0 && static_cast<int>(file->getVideoInfo()->Height) - getCropping()->top - getCropping()->bottom < verticalResolution->Value)
			changeNumericUpDownColor(verticalResolution, true);
		else
			changeNumericUpDownColor(verticalResolution, false);

		if (resize->Checked && file != 0 && static_cast<int>(file->getVideoInfo()->Width) - getCropping()->left - getCropping()->right < horizontalResolution->Value)
			changeNumericUpDownColor(horizontalResolution, true);
		else
			changeNumericUpDownColor(horizontalResolution, false);
	}

	void AviSynthWindow::refreshScript()
	{
		if (sender != 0 && e != 0)
			showScript(false);
	}

	void AviSynthWindow::AviSynthWindow_Shown()
	{
		if (player != 0 && !player->Visible)
			player->Show();
	}

	void AviSynthWindow::resize_CheckedChanged()
	{
		if (sender != 0 && e != 0 && resize->Checked)
			updateEverything(sender != 0, false, true);
		else
			updateEverything(sender != 0, false, false);
	}

	void AviSynthWindow::Dispose(bool disposing)
	{
		if (disposing && (components != 0))
		{
			delete components;
		}
		System::Windows::Forms::Form::Dispose(disposing);
	}

	void AviSynthWindow::InitializeComponent()
	{
		System::Windows::Forms::Label *label2;
		System::Windows::Forms::Label *label3;
		System::Windows::Forms::Label *label4;
		System::Windows::Forms::Label *label5;
		System::ComponentModel::ComponentResourceManager *resources = new System::ComponentModel::ComponentResourceManager(AviSynthWindow::typeid);
		this->resNCropGroupbox = new System::Windows::Forms::GroupBox();
		this->lblAspectError = new System::Windows::Forms::Label();
		this->lblAR = new System::Windows::Forms::Label();
		this->modValueBox = new System::Windows::Forms::ComboBox();
		this->chAutoPreview = new System::Windows::Forms::CheckBox();
		this->signalAR = new System::Windows::Forms::CheckBox();
		this->mod16Box = new System::Windows::Forms::ComboBox();
		this->resize = new System::Windows::Forms::CheckBox();
		this->suggestResolution = new System::Windows::Forms::CheckBox();
		this->cropLeft = new System::Windows::Forms::NumericUpDown();
		this->cropRight = new System::Windows::Forms::NumericUpDown();
		this->cropBottom = new System::Windows::Forms::NumericUpDown();
		this->cropTop = new System::Windows::Forms::NumericUpDown();
		this->autoCropButton = new QPushButton;
		this->crop = new System::Windows::Forms::CheckBox();
		this->verticalResolution = new System::Windows::Forms::NumericUpDown();
		this->horizontalResolution = new System::Windows::Forms::NumericUpDown();
		this->tabControl1 = new System::Windows::Forms::TabControl();
		this->optionsTab = new System::Windows::Forms::TabPage();
		this->gbOutput = new System::Windows::Forms::GroupBox();
		this->label7 = new System::Windows::Forms::Label();
		this->videoGroupBox = new System::Windows::Forms::GroupBox();
		this->reopenOriginal = new QPushButton;
		this->tvTypeLabel = new System::Windows::Forms::Label();
		this->label6 = new System::Windows::Forms::Label();
		this->inputDARLabel = new System::Windows::Forms::Label();
		this->videoInputLabel = new System::Windows::Forms::Label();
		this->filterTab = new System::Windows::Forms::TabPage();
		this->tabSources = new System::Windows::Forms::TabControl();
		this->tabPage1 = new System::Windows::Forms::TabPage();
		this->mpegOptGroupBox = new System::Windows::Forms::GroupBox();
		this->colourCorrect = new System::Windows::Forms::CheckBox();
		this->mpeg2Deblocking = new System::Windows::Forms::CheckBox();
		this->tabPage2 = new System::Windows::Forms::TabPage();
		this->aviOptGroupBox = new System::Windows::Forms::GroupBox();
		this->dss2 = new System::Windows::Forms::CheckBox();
		this->fpsBox = new System::Windows::Forms::NumericUpDown();
		this->fpsLabel = new System::Windows::Forms::Label();
		this->flipVertical = new System::Windows::Forms::CheckBox();
		this->tabPage3 = new System::Windows::Forms::TabPage();
		this->dgOptions = new System::Windows::Forms::GroupBox();
		this->nvResize = new System::Windows::Forms::CheckBox();
		this->cbNvDeInt = new System::Windows::Forms::ComboBox();
		this->nvDeInt = new System::Windows::Forms::CheckBox();
		this->deinterlacingGroupBox = new System::Windows::Forms::GroupBox();
		this->deintM = new System::Windows::Forms::NumericUpDown();
		this->deintFieldOrder = new System::Windows::Forms::ComboBox();
		this->deintSourceType = new System::Windows::Forms::ComboBox();
		this->deintIsAnime = new System::Windows::Forms::CheckBox();
		this->analyseButton = new QPushButton;
		this->deinterlace = new System::Windows::Forms::CheckBox();
		this->deinterlaceType = new System::Windows::Forms::ComboBox();
		this->filtersGroupbox = new System::Windows::Forms::GroupBox();
		this->cbCharset = new System::Windows::Forms::ComboBox();
		this->label8 = new System::Windows::Forms::Label();
		this->openSubtitlesButton = new QPushButton;
		this->SubtitlesPath = new System::Windows::Forms::TextBox();
		this->SubtitlesLabel = new System::Windows::Forms::Label();
		this->noiseFilterType = new System::Windows::Forms::ComboBox();
		this->noiseFilter = new System::Windows::Forms::CheckBox();
		this->resizeFilterType = new System::Windows::Forms::ComboBox();
		this->resizeFilterLabel = new System::Windows::Forms::Label();
		this->editTab = new System::Windows::Forms::TabPage();
		this->openDLLButton = new QPushButton;
		this->dllPath = new System::Windows::Forms::TextBox();
		this->label1 = new System::Windows::Forms::Label();
		this->avisynthScript = new System::Windows::Forms::TextBox();
		this->saveAvisynthScriptDialog = new System::Windows::Forms::SaveFileDialog();
		this->openFilterDialog = new System::Windows::Forms::OpenFileDialog();
		this->openSubsDialog = new System::Windows::Forms::OpenFileDialog();
		this->statusStrip1 = new System::Windows::Forms::StatusStrip();
		this->deintProgressBar = new System::Windows::Forms::ToolStripProgressBar();
		this->deintStatusLabel = new System::Windows::Forms::ToolStripStatusLabel();
		this->onSaveLoadScript = new System::Windows::Forms::CheckBox();
		this->saveButton = new QPushButton;
		this->previewAvsButton = new QPushButton;
		this->helpButton1 = new MeXgui::core::gui::HelpButton();
		this->videoOutput = new MeXgui::FileBar();
		this->input = new MeXgui::FileBar();
		this->avsProfile = new MeXgui::core::gui::ConfigableProfilesControl();
		this->arChooser = new MeXgui::core::gui::ARChooser();
		label2 = new System::Windows::Forms::Label();
		label3 = new System::Windows::Forms::Label();
		label4 = new System::Windows::Forms::Label();
		label5 = new System::Windows::Forms::Label();
		this->resNCropGroupbox->SuspendLayout();
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->cropLeft))->BeginInit();
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->cropRight))->BeginInit();
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->cropBottom))->BeginInit();
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->cropTop))->BeginInit();
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->verticalResolution))->BeginInit();
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->horizontalResolution))->BeginInit();
		this->tabControl1->SuspendLayout();
		this->optionsTab->SuspendLayout();
		this->gbOutput->SuspendLayout();
		this->videoGroupBox->SuspendLayout();
		this->filterTab->SuspendLayout();
		this->tabSources->SuspendLayout();
		this->tabPage1->SuspendLayout();
		this->mpegOptGroupBox->SuspendLayout();
		this->tabPage2->SuspendLayout();
		this->aviOptGroupBox->SuspendLayout();
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->fpsBox))->BeginInit();
		this->tabPage3->SuspendLayout();
		this->dgOptions->SuspendLayout();
		this->deinterlacingGroupBox->SuspendLayout();
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->deintM))->BeginInit();
		this->filtersGroupbox->SuspendLayout();
		this->editTab->SuspendLayout();
		this->statusStrip1->SuspendLayout();
		this->SuspendLayout();
		// 
		// label2
		// 
		label2->AutoSize = true;
		label2->Location = new System::Drawing::Point(9, 22);
		label2->Name = "label2";
		label2->Size = new System::Drawing::Size(258, 13);
		label2->TabIndex = 11;
		label2->Text = "Source Info (Click on \'Analyse...\' for autodetection):";
		// 
		// label3
		// 
		label3->AutoSize = true;
		label3->Location = new System::Drawing::Point(9, 50);
		label3->Name = "label3";
		label3->Size = new System::Drawing::Size(69, 13);
		label3->TabIndex = 13;
		label3->Text = "Source type:";
		// 
		// label4
		// 
		label4->AutoSize = true;
		label4->Location = new System::Drawing::Point(9, 79);
		label4->Name = "label4";
		label4->Size = new System::Drawing::Size(62, 13);
		label4->TabIndex = 14;
		label4->Text = "Field order:";
		// 
		// label5
		// 
		label5->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
		label5->AutoSize = true;
		label5->Location = new System::Drawing::Point(342, 50);
		label5->Name = "label5";
		label5->Size = new System::Drawing::Size(19, 13);
		label5->TabIndex = 17;
		label5->Text = "M:";
		// 
		// resNCropGroupbox
		// 
		this->resNCropGroupbox->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
		this->resNCropGroupbox->Controls->Add(this->lblAspectError);
		this->resNCropGroupbox->Controls->Add(this->lblAR);
		this->resNCropGroupbox->Controls->Add(this->modValueBox);
		this->resNCropGroupbox->Controls->Add(this->chAutoPreview);
		this->resNCropGroupbox->Controls->Add(this->signalAR);
		this->resNCropGroupbox->Controls->Add(this->mod16Box);
		this->resNCropGroupbox->Controls->Add(this->resize);
		this->resNCropGroupbox->Controls->Add(this->suggestResolution);
		this->resNCropGroupbox->Controls->Add(this->cropLeft);
		this->resNCropGroupbox->Controls->Add(this->cropRight);
		this->resNCropGroupbox->Controls->Add(this->cropBottom);
		this->resNCropGroupbox->Controls->Add(this->cropTop);
		this->resNCropGroupbox->Controls->Add(this->autoCropButton);
		this->resNCropGroupbox->Controls->Add(this->crop);
		this->resNCropGroupbox->Controls->Add(this->verticalResolution);
		this->resNCropGroupbox->Controls->Add(this->horizontalResolution);
		this->resNCropGroupbox->Enabled = false;
		this->resNCropGroupbox->Location = new System::Drawing::Point(3, 157);
		this->resNCropGroupbox->Name = "resNCropGroupbox";
		this->resNCropGroupbox->Size = new System::Drawing::Size(450, 197);
		this->resNCropGroupbox->TabIndex = 0;
		this->resNCropGroupbox->TabStop = false;
		this->resNCropGroupbox->Text = "Crop && Resize";
		// 
		// lblAspectError
		// 
		this->lblAspectError->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->lblAspectError->Location = new System::Drawing::Point(340, 160);
		this->lblAspectError->Name = "lblAspectError";
		this->lblAspectError->Size = new System::Drawing::Size(75, 21);
		this->lblAspectError->TabIndex = 14;
		this->lblAspectError->Text = "0.00000%";
		this->lblAspectError->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
		// 
		// lblAR
		// 
		this->lblAR->AutoSize = true;
		this->lblAR->Location = new System::Drawing::Point(236, 164);
		this->lblAR->Name = "lblAR";
		this->lblAR->Size = new System::Drawing::Size(95, 13);
		this->lblAR->TabIndex = 13;
		this->lblAR->Text = "Aspect Ratio Error";
		// 
		// modValueBox
		// 
		this->modValueBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->modValueBox->FormattingEnabled = true;
		this->modValueBox->Items->AddRange(new object[4] {"mod16", "mod8", "mod4", "mod2"});
		this->modValueBox->Location = new System::Drawing::Point(340, 119);
		this->modValueBox->Name = "modValueBox";
		this->modValueBox->Size = new System::Drawing::Size(75, 21);
		this->modValueBox->TabIndex = 11;
		this->modValueBox->SelectedIndexChanged += new System::EventHandler(this, &AviSynthWindow::updateEverything);
		// 
		// chAutoPreview
		// 
		this->chAutoPreview->AutoSize = true;
		this->chAutoPreview->Location = new System::Drawing::Point(11, 161);
		this->chAutoPreview->Name = "chAutoPreview";
		this->chAutoPreview->Size = new System::Drawing::Size(119, 17);
		this->chAutoPreview->TabIndex = 10;
		this->chAutoPreview->Text = "Apply auto Preview";
		this->chAutoPreview->UseVisualStyleBackColor = true;
		this->chAutoPreview->CheckedChanged += new System::EventHandler(this, &AviSynthWindow::chAutoPreview_CheckedChanged);
		// 
		// signalAR
		// 
		this->signalAR->AutoSize = true;
		this->signalAR->Location = new System::Drawing::Point(11, 31);
		this->signalAR->Name = "signalAR";
		this->signalAR->Size = new System::Drawing::Size(190, 17);
		this->signalAR->TabIndex = 11;
		this->signalAR->Text = "Clever (TM) anamorphic encoding:";
		this->signalAR->CheckedChanged += new System::EventHandler(this, &AviSynthWindow::updateEverything);
		// 
		// mod16Box
		// 
		this->mod16Box->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->mod16Box->Enabled = false;
		this->mod16Box->FormattingEnabled = true;
		this->mod16Box->Items->AddRange(new object[5] {"Resize to selected mod", "Overcrop to achieve selected mod", "Encode non-mod16", "Crop mod4 horizontally", "Undercrop to achieve selected mod"});
		this->mod16Box->Location = new System::Drawing::Point(222, 29);
		this->mod16Box->Name = "mod16Box";
		this->mod16Box->Size = new System::Drawing::Size(222, 21);
		this->mod16Box->TabIndex = 19;
		this->mod16Box->SelectedIndexChanged += new System::EventHandler(this, &AviSynthWindow::updateEverything);
		// 
		// resize
		// 
		this->resize->AutoSize = true;
		this->resize->Checked = true;
		this->resize->CheckState = System::Windows::Forms::CheckState::Checked;
		this->resize->Location = new System::Drawing::Point(11, 121);
		this->resize->Name = "resize";
		this->resize->Size = new System::Drawing::Size(57, 17);
		this->resize->TabIndex = 9;
		this->resize->Text = "Resize";
		this->resize->UseVisualStyleBackColor = true;
		this->resize->CheckedChanged += new System::EventHandler(this, &AviSynthWindow::resize_CheckedChanged);
		// 
		// suggestResolution
		// 
		this->suggestResolution->AutoSize = true;
		this->suggestResolution->Checked = true;
		this->suggestResolution->CheckState = System::Windows::Forms::CheckState::Checked;
		this->suggestResolution->Location = new System::Drawing::Point(222, 120);
		this->suggestResolution->Name = "suggestResolution";
		this->suggestResolution->Size = new System::Drawing::Size(118, 17);
		this->suggestResolution->TabIndex = 8;
		this->suggestResolution->Text = "Suggest Resolution";
		this->suggestResolution->CheckedChanged += new System::EventHandler(this, &AviSynthWindow::updateEverything);
		// 
		// cropLeft
		// 
		this->cropLeft->Enabled = false;
		this->cropLeft->Increment = decimal(new int[4] {2, 0, 0, 0});
		this->cropLeft->Location = new System::Drawing::Point(114, 73);
		this->cropLeft->Maximum = decimal(new int[4] {200, 0, 0, 0});
		this->cropLeft->Name = "cropLeft";
		this->cropLeft->Size = new System::Drawing::Size(48, 21);
		this->cropLeft->TabIndex = 7;
		this->cropLeft->ValueChanged += new System::EventHandler(this, &AviSynthWindow::updateEverything);
		// 
		// cropRight
		// 
		this->cropRight->Enabled = false;
		this->cropRight->Increment = decimal(new int[4] {2, 0, 0, 0});
		this->cropRight->Location = new System::Drawing::Point(222, 73);
		this->cropRight->Maximum = decimal(new int[4] {200, 0, 0, 0});
		this->cropRight->Name = "cropRight";
		this->cropRight->Size = new System::Drawing::Size(48, 21);
		this->cropRight->TabIndex = 6;
		this->cropRight->ValueChanged += new System::EventHandler(this, &AviSynthWindow::updateEverything);
		// 
		// cropBottom
		// 
		this->cropBottom->Enabled = false;
		this->cropBottom->Increment = decimal(new int[4] {2, 0, 0, 0});
		this->cropBottom->Location = new System::Drawing::Point(168, 87);
		this->cropBottom->Maximum = decimal(new int[4] {200, 0, 0, 0});
		this->cropBottom->Name = "cropBottom";
		this->cropBottom->Size = new System::Drawing::Size(48, 21);
		this->cropBottom->TabIndex = 5;
		this->cropBottom->ValueChanged += new System::EventHandler(this, &AviSynthWindow::updateEverything);
		// 
		// cropTop
		// 
		this->cropTop->Enabled = false;
		this->cropTop->Increment = decimal(new int[4] {2, 0, 0, 0});
		this->cropTop->Location = new System::Drawing::Point(168, 60);
		this->cropTop->Maximum = decimal(new int[4] {200, 0, 0, 0});
		this->cropTop->Name = "cropTop";
		this->cropTop->Size = new System::Drawing::Size(48, 21);
		this->cropTop->TabIndex = 4;
		this->cropTop->ValueChanged += new System::EventHandler(this, &AviSynthWindow::updateEverything);
		// 
		// autoCropButton
		// 
		this->autoCropButton->Location = new System::Drawing::Point(340, 73);
		this->autoCropButton->Name = "autoCropButton";
		this->autoCropButton->Size = new System::Drawing::Size(75, 23);
		this->autoCropButton->TabIndex = 3;
		this->autoCropButton->Text = "Auto Crop";
		this->autoCropButton->Click += new System::EventHandler(this, &AviSynthWindow::autoCropButton_Click);
		// 
		// crop
		// 
		this->crop->Location = new System::Drawing::Point(11, 64);
		this->crop->Name = "crop";
		this->crop->Size = new System::Drawing::Size(97, 42);
		this->crop->TabIndex = 2;
		this->crop->Text = "Crop";
		this->crop->CheckedChanged += new System::EventHandler(this, &AviSynthWindow::updateEverything);
		// 
		// verticalResolution
		// 
		this->verticalResolution->Enabled = false;
		this->verticalResolution->Increment = decimal(new int[4] {16, 0, 0, 0});
		this->verticalResolution->Location = new System::Drawing::Point(168, 117);
		this->verticalResolution->Maximum = decimal(new int[4] {9999, 0, 0, 0});
		this->verticalResolution->Name = "verticalResolution";
		this->verticalResolution->Size = new System::Drawing::Size(48, 21);
		this->verticalResolution->TabIndex = 1;
		this->verticalResolution->ValueChanged += new System::EventHandler(this, &AviSynthWindow::updateEverything);
		// 
		// horizontalResolution
		// 
		this->horizontalResolution->Increment = decimal(new int[4] {16, 0, 0, 0});
		this->horizontalResolution->Location = new System::Drawing::Point(114, 117);
		this->horizontalResolution->Maximum = decimal(new int[4] {9999, 0, 0, 0});
		this->horizontalResolution->Name = "horizontalResolution";
		this->horizontalResolution->Size = new System::Drawing::Size(48, 21);
		this->horizontalResolution->TabIndex = 0;
		this->horizontalResolution->ValueChanged += new System::EventHandler(this, &AviSynthWindow::updateEverything);
		// 
		// tabControl1
		// 
		this->tabControl1->Controls->Add(this->optionsTab);
		this->tabControl1->Controls->Add(this->filterTab);
		this->tabControl1->Controls->Add(this->editTab);
		this->tabControl1->Dock = System::Windows::Forms::DockStyle::Top;
		this->tabControl1->Location = new System::Drawing::Point(0, 0);
		this->tabControl1->Name = "tabControl1";
		this->tabControl1->SelectedIndex = 0;
		this->tabControl1->Size = new System::Drawing::Size(463, 459);
		this->tabControl1->TabIndex = 5;
		// 
		// optionsTab
		// 
		this->optionsTab->Controls->Add(this->gbOutput);
		this->optionsTab->Controls->Add(this->videoGroupBox);
		this->optionsTab->Controls->Add(this->resNCropGroupbox);
		this->optionsTab->Location = new System::Drawing::Point(4, 22);
		this->optionsTab->Name = "optionsTab";
		this->optionsTab->Size = new System::Drawing::Size(455, 433);
		this->optionsTab->TabIndex = 0;
		this->optionsTab->Text = "I/O";
		this->optionsTab->UseVisualStyleBackColor = true;
		// 
		// gbOutput
		// 
		this->gbOutput->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
		this->gbOutput->Controls->Add(this->videoOutput);
		this->gbOutput->Controls->Add(this->label7);
		this->gbOutput->Location = new System::Drawing::Point(3, 360);
		this->gbOutput->Name = "gbOutput";
		this->gbOutput->Size = new System::Drawing::Size(450, 55);
		this->gbOutput->TabIndex = 13;
		this->gbOutput->TabStop = false;
		this->gbOutput->Text = "Output";
		// 
		// label7
		// 
		this->label7->Location = new System::Drawing::Point(8, 24);
		this->label7->Name = "label7";
		this->label7->Size = new System::Drawing::Size(80, 13);
		this->label7->TabIndex = 6;
		this->label7->Text = "Video Output";
		// 
		// videoGroupBox
		// 
		this->videoGroupBox->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
		this->videoGroupBox->Controls->Add(this->input);
		this->videoGroupBox->Controls->Add(this->avsProfile);
		this->videoGroupBox->Controls->Add(this->arChooser);
		this->videoGroupBox->Controls->Add(this->reopenOriginal);
		this->videoGroupBox->Controls->Add(this->tvTypeLabel);
		this->videoGroupBox->Controls->Add(this->label6);
		this->videoGroupBox->Controls->Add(this->inputDARLabel);
		this->videoGroupBox->Controls->Add(this->videoInputLabel);
		this->videoGroupBox->Location = new System::Drawing::Point(3, 8);
		this->videoGroupBox->Name = "videoGroupBox";
		this->videoGroupBox->Size = new System::Drawing::Size(450, 143);
		this->videoGroupBox->TabIndex = 5;
		this->videoGroupBox->TabStop = false;
		this->videoGroupBox->Text = "Input";
		// 
		// reopenOriginal
		// 
		this->reopenOriginal->AutoSize = true;
		this->reopenOriginal->Location = new System::Drawing::Point(96, 47);
		this->reopenOriginal->Name = "reopenOriginal";
		this->reopenOriginal->Size = new System::Drawing::Size(183, 23);
		this->reopenOriginal->TabIndex = 20;
		this->reopenOriginal->Text = "Re-open original video player";
		this->reopenOriginal->UseVisualStyleBackColor = true;
		this->reopenOriginal->Click += new System::EventHandler(this, &AviSynthWindow::reopenOriginal_Click);
		// 
		// tvTypeLabel
		// 
		this->tvTypeLabel->Location = new System::Drawing::Point(316, 82);
		this->tvTypeLabel->Name = "tvTypeLabel";
		this->tvTypeLabel->Size = new System::Drawing::Size(48, 23);
		this->tvTypeLabel->TabIndex = 10;
		// 
		// label6
		// 
		this->label6->AutoSize = true;
		this->label6->Location = new System::Drawing::Point(8, 115);
		this->label6->Name = "label6";
		this->label6->Size = new System::Drawing::Size(82, 13);
		this->label6->TabIndex = 7;
		this->label6->Text = "Avisynth profile";
		// 
		// inputDARLabel
		// 
		this->inputDARLabel->Location = new System::Drawing::Point(8, 83);
		this->inputDARLabel->Name = "inputDARLabel";
		this->inputDARLabel->Size = new System::Drawing::Size(72, 13);
		this->inputDARLabel->TabIndex = 7;
		this->inputDARLabel->Text = "Input DAR";
		// 
		// videoInputLabel
		// 
		this->videoInputLabel->Location = new System::Drawing::Point(8, 21);
		this->videoInputLabel->Name = "videoInputLabel";
		this->videoInputLabel->Size = new System::Drawing::Size(80, 13);
		this->videoInputLabel->TabIndex = 0;
		this->videoInputLabel->Text = "Video Input";
		// 
		// filterTab
		// 
		this->filterTab->Controls->Add(this->tabSources);
		this->filterTab->Controls->Add(this->deinterlacingGroupBox);
		this->filterTab->Controls->Add(this->filtersGroupbox);
		this->filterTab->Location = new System::Drawing::Point(4, 22);
		this->filterTab->Name = "filterTab";
		this->filterTab->Size = new System::Drawing::Size(455, 433);
		this->filterTab->TabIndex = 2;
		this->filterTab->Text = "Filters";
		this->filterTab->UseVisualStyleBackColor = true;
		// 
		// tabSources
		// 
		this->tabSources->Controls->Add(this->tabPage1);
		this->tabSources->Controls->Add(this->tabPage2);
		this->tabSources->Controls->Add(this->tabPage3);
		this->tabSources->Location = new System::Drawing::Point(3, 3);
		this->tabSources->Name = "tabSources";
		this->tabSources->SelectedIndex = 0;
		this->tabSources->Size = new System::Drawing::Size(449, 116);
		this->tabSources->TabIndex = 14;
		// 
		// tabPage1
		// 
		this->tabPage1->Controls->Add(this->mpegOptGroupBox);
		this->tabPage1->Location = new System::Drawing::Point(4, 22);
		this->tabPage1->Name = "tabPage1";
		this->tabPage1->Padding = new System::Windows::Forms::Padding(3);
		this->tabPage1->Size = new System::Drawing::Size(441, 90);
		this->tabPage1->TabIndex = 0;
		this->tabPage1->Text = "MPEG2 Source";
		this->tabPage1->UseVisualStyleBackColor = true;
		// 
		// mpegOptGroupBox
		// 
		this->mpegOptGroupBox->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
		this->mpegOptGroupBox->Controls->Add(this->colourCorrect);
		this->mpegOptGroupBox->Controls->Add(this->mpeg2Deblocking);
		this->mpegOptGroupBox->Enabled = false;
		this->mpegOptGroupBox->Location = new System::Drawing::Point(6, 3);
		this->mpegOptGroupBox->Name = "mpegOptGroupBox";
		this->mpegOptGroupBox->Size = new System::Drawing::Size(426, 80);
		this->mpegOptGroupBox->TabIndex = 22;
		this->mpegOptGroupBox->TabStop = false;
		// 
		// colourCorrect
		// 
		this->colourCorrect->Location = new System::Drawing::Point(10, 43);
		this->colourCorrect->Name = "colourCorrect";
		this->colourCorrect->Size = new System::Drawing::Size(111, 17);
		this->colourCorrect->TabIndex = 9;
		this->colourCorrect->Text = "Colour Correction";
		this->colourCorrect->CheckedChanged += new System::EventHandler(this, &AviSynthWindow::refreshScript);
		// 
		// mpeg2Deblocking
		// 
		this->mpeg2Deblocking->Location = new System::Drawing::Point(10, 20);
		this->mpeg2Deblocking->Name = "mpeg2Deblocking";
		this->mpeg2Deblocking->Size = new System::Drawing::Size(124, 17);
		this->mpeg2Deblocking->TabIndex = 8;
		this->mpeg2Deblocking->Text = "Mpeg2 Deblocking";
		this->mpeg2Deblocking->CheckedChanged += new System::EventHandler(this, &AviSynthWindow::refreshScript);
		// 
		// tabPage2
		// 
		this->tabPage2->Controls->Add(this->aviOptGroupBox);
		this->tabPage2->Location = new System::Drawing::Point(4, 22);
		this->tabPage2->Name = "tabPage2";
		this->tabPage2->Padding = new System::Windows::Forms::Padding(3);
		this->tabPage2->Size = new System::Drawing::Size(441, 90);
		this->tabPage2->TabIndex = 1;
		this->tabPage2->Text = "AVI Source / DSSource";
		this->tabPage2->UseVisualStyleBackColor = true;
		// 
		// aviOptGroupBox
		// 
		this->aviOptGroupBox->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
		this->aviOptGroupBox->Controls->Add(this->dss2);
		this->aviOptGroupBox->Controls->Add(this->fpsBox);
		this->aviOptGroupBox->Controls->Add(this->fpsLabel);
		this->aviOptGroupBox->Controls->Add(this->flipVertical);
		this->aviOptGroupBox->Enabled = false;
		this->aviOptGroupBox->Location = new System::Drawing::Point(6, 3);
		this->aviOptGroupBox->Name = "aviOptGroupBox";
		this->aviOptGroupBox->Size = new System::Drawing::Size(426, 80);
		this->aviOptGroupBox->TabIndex = 23;
		this->aviOptGroupBox->TabStop = false;
		// 
		// dss2
		// 
		this->dss2->AutoSize = true;
		this->dss2->Location = new System::Drawing::Point(120, 20);
		this->dss2->Name = "dss2";
		this->dss2->Size = new System::Drawing::Size(185, 17);
		this->dss2->TabIndex = 4;
		this->dss2->Text = "Prefer DSSource2 over DSSource";
		this->dss2->UseVisualStyleBackColor = true;
		this->dss2->CheckedChanged += new System::EventHandler(this, &AviSynthWindow::refreshScript);
		// 
		// fpsBox
		// 
		this->fpsBox->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
		this->fpsBox->DecimalPlaces = 3;
		this->fpsBox->Location = new System::Drawing::Point(40, 43);
		this->fpsBox->Maximum = decimal(new int[4] {1000, 0, 0, 0});
		this->fpsBox->Minimum = decimal(new int[4] {1, 0, 0, 196608});
		this->fpsBox->Name = "fpsBox";
		this->fpsBox->Size = new System::Drawing::Size(130, 21);
		this->fpsBox->TabIndex = 3;
		this->fpsBox->Value = decimal(new int[4] {1, 0, 0, 196608});
		this->fpsBox->ValueChanged += new System::EventHandler(this, &AviSynthWindow::refreshScript);
		// 
		// fpsLabel
		// 
		this->fpsLabel->Location = new System::Drawing::Point(9, 45);
		this->fpsLabel->Name = "fpsLabel";
		this->fpsLabel->Size = new System::Drawing::Size(25, 13);
		this->fpsLabel->TabIndex = 2;
		this->fpsLabel->Text = "FPS";
		// 
		// flipVertical
		// 
		this->flipVertical->Location = new System::Drawing::Point(10, 20);
		this->flipVertical->Name = "flipVertical";
		this->flipVertical->Size = new System::Drawing::Size(90, 17);
		this->flipVertical->TabIndex = 0;
		this->flipVertical->Text = "Vertical Flip";
		this->flipVertical->CheckedChanged += new System::EventHandler(this, &AviSynthWindow::refreshScript);
		// 
		// tabPage3
		// 
		this->tabPage3->Controls->Add(this->dgOptions);
		this->tabPage3->Location = new System::Drawing::Point(4, 22);
		this->tabPage3->Name = "tabPage3";
		this->tabPage3->Padding = new System::Windows::Forms::Padding(3);
		this->tabPage3->Size = new System::Drawing::Size(441, 90);
		this->tabPage3->TabIndex = 2;
		this->tabPage3->Text = "DGx Source";
		this->tabPage3->UseVisualStyleBackColor = true;
		// 
		// dgOptions
		// 
		this->dgOptions->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
		this->dgOptions->Controls->Add(this->nvResize);
		this->dgOptions->Controls->Add(this->cbNvDeInt);
		this->dgOptions->Controls->Add(this->nvDeInt);
		this->dgOptions->Location = new System::Drawing::Point(6, 3);
		this->dgOptions->Name = "dgOptions";
		this->dgOptions->Size = new System::Drawing::Size(426, 80);
		this->dgOptions->TabIndex = 14;
		this->dgOptions->TabStop = false;
		// 
		// nvResize
		// 
		this->nvResize->AutoSize = true;
		this->nvResize->Location = new System::Drawing::Point(10, 52);
		this->nvResize->Name = "nvResize";
		this->nvResize->Size = new System::Drawing::Size(93, 17);
		this->nvResize->TabIndex = 2;
		this->nvResize->Text = "Nvidia Resizer";
		this->nvResize->UseVisualStyleBackColor = true;
		this->nvResize->CheckedChanged += new System::EventHandler(this, &AviSynthWindow::refreshScript);
		this->nvResize->Click += new System::EventHandler(this, &AviSynthWindow::nvDeInt_Click);
		// 
		// cbNvDeInt
		// 
		this->cbNvDeInt->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
		this->cbNvDeInt->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->cbNvDeInt->Enabled = false;
		this->cbNvDeInt->FormattingEnabled = true;
		this->cbNvDeInt->Location = new System::Drawing::Point(155, 18);
		this->cbNvDeInt->Name = "cbNvDeInt";
		this->cbNvDeInt->Size = new System::Drawing::Size(265, 21);
		this->cbNvDeInt->TabIndex = 1;
		this->cbNvDeInt->SelectedIndexChanged += new System::EventHandler(this, &AviSynthWindow::refreshScript);
		// 
		// nvDeInt
		// 
		this->nvDeInt->AutoSize = true;
		this->nvDeInt->Enabled = false;
		this->nvDeInt->Location = new System::Drawing::Point(10, 20);
		this->nvDeInt->Name = "nvDeInt";
		this->nvDeInt->Size = new System::Drawing::Size(116, 17);
		this->nvDeInt->TabIndex = 0;
		this->nvDeInt->Text = "Nvidia Deinterlacer";
		this->nvDeInt->UseVisualStyleBackColor = true;
		this->nvDeInt->CheckedChanged += new System::EventHandler(this, &AviSynthWindow::nvDeInt_CheckedChanged);
		this->nvDeInt->Click += new System::EventHandler(this, &AviSynthWindow::nvDeInt_Click);
		// 
		// deinterlacingGroupBox
		// 
		this->deinterlacingGroupBox->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
		this->deinterlacingGroupBox->Controls->Add(label5);
		this->deinterlacingGroupBox->Controls->Add(this->deintM);
		this->deinterlacingGroupBox->Controls->Add(this->deintFieldOrder);
		this->deinterlacingGroupBox->Controls->Add(label4);
		this->deinterlacingGroupBox->Controls->Add(label3);
		this->deinterlacingGroupBox->Controls->Add(this->deintSourceType);
		this->deinterlacingGroupBox->Controls->Add(label2);
		this->deinterlacingGroupBox->Controls->Add(this->deintIsAnime);
		this->deinterlacingGroupBox->Controls->Add(this->analyseButton);
		this->deinterlacingGroupBox->Controls->Add(this->deinterlace);
		this->deinterlacingGroupBox->Controls->Add(this->deinterlaceType);
		this->deinterlacingGroupBox->Enabled = false;
		this->deinterlacingGroupBox->Location = new System::Drawing::Point(3, 121);
		this->deinterlacingGroupBox->Name = "deinterlacingGroupBox";
		this->deinterlacingGroupBox->Size = new System::Drawing::Size(449, 164);
		this->deinterlacingGroupBox->TabIndex = 12;
		this->deinterlacingGroupBox->TabStop = false;
		this->deinterlacingGroupBox->Text = "Deinterlacing";
		// 
		// deintM
		// 
		this->deintM->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
		this->deintM->Location = new System::Drawing::Point(367, 47);
		this->deintM->Name = "deintM";
		this->deintM->Size = new System::Drawing::Size(76, 21);
		this->deintM->TabIndex = 16;
		this->deintM->ValueChanged += new System::EventHandler(this, &AviSynthWindow::deintSourceType_SelectedIndexChanged);
		// 
		// deintFieldOrder
		// 
		this->deintFieldOrder->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
		this->deintFieldOrder->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->deintFieldOrder->FormattingEnabled = true;
		this->deintFieldOrder->Location = new System::Drawing::Point(97, 76);
		this->deintFieldOrder->Name = "deintFieldOrder";
		this->deintFieldOrder->Size = new System::Drawing::Size(239, 21);
		this->deintFieldOrder->TabIndex = 15;
		this->deintFieldOrder->SelectedIndexChanged += new System::EventHandler(this, &AviSynthWindow::deintSourceType_SelectedIndexChanged);
		// 
		// deintSourceType
		// 
		this->deintSourceType->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
		this->deintSourceType->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->deintSourceType->FormattingEnabled = true;
		this->deintSourceType->Location = new System::Drawing::Point(97, 47);
		this->deintSourceType->Name = "deintSourceType";
		this->deintSourceType->Size = new System::Drawing::Size(239, 21);
		this->deintSourceType->TabIndex = 12;
		this->deintSourceType->SelectedIndexChanged += new System::EventHandler(this, &AviSynthWindow::deintSourceType_SelectedIndexChanged);
		// 
		// deintIsAnime
		// 
		this->deintIsAnime->AutoSize = true;
		this->deintIsAnime->Location = new System::Drawing::Point(9, 133);
		this->deintIsAnime->Name = "deintIsAnime";
		this->deintIsAnime->Size = new System::Drawing::Size(297, 17);
		this->deintIsAnime->TabIndex = 10;
		this->deintIsAnime->Text = "Source is Anime (not automatically detected by Analysis)";
		this->deintIsAnime->UseVisualStyleBackColor = true;
		this->deintIsAnime->CheckedChanged += new System::EventHandler(this, &AviSynthWindow::deintSourceType_SelectedIndexChanged);
		// 
		// analyseButton
		// 
		this->analyseButton->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
		this->analyseButton->Location = new System::Drawing::Point(345, 17);
		this->analyseButton->Name = "analyseButton";
		this->analyseButton->Size = new System::Drawing::Size(98, 23);
		this->analyseButton->TabIndex = 8;
		this->analyseButton->Text = "Analyse...";
		this->analyseButton->UseVisualStyleBackColor = true;
		this->analyseButton->Click += new System::EventHandler(this, &AviSynthWindow::analyseButton_Click);
		// 
		// deinterlace
		// 
		this->deinterlace->Location = new System::Drawing::Point(9, 103);
		this->deinterlace->Name = "deinterlace";
		this->deinterlace->Size = new System::Drawing::Size(82, 24);
		this->deinterlace->TabIndex = 2;
		this->deinterlace->Text = "Deinterlace";
		this->deinterlace->CheckedChanged += new System::EventHandler(this, &AviSynthWindow::deinterlace_CheckedChanged);
		// 
		// deinterlaceType
		// 
		this->deinterlaceType->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
		this->deinterlaceType->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->deinterlaceType->Enabled = false;
		this->deinterlaceType->Items->AddRange(new object[4] {"Leak Kernel Deinterlace", "Field Deinterlace", "Field Deinterlace (no blend)", "Telecide for PAL"});
		this->deinterlaceType->Location = new System::Drawing::Point(97, 105);
		this->deinterlaceType->Name = "deinterlaceType";
		this->deinterlaceType->Size = new System::Drawing::Size(239, 21);
		this->deinterlaceType->TabIndex = 4;
		this->deinterlaceType->SelectedIndexChanged += new System::EventHandler(this, &AviSynthWindow::refreshScript);
		// 
		// filtersGroupbox
		// 
		this->filtersGroupbox->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
		this->filtersGroupbox->Controls->Add(this->cbCharset);
		this->filtersGroupbox->Controls->Add(this->label8);
		this->filtersGroupbox->Controls->Add(this->openSubtitlesButton);
		this->filtersGroupbox->Controls->Add(this->SubtitlesPath);
		this->filtersGroupbox->Controls->Add(this->SubtitlesLabel);
		this->filtersGroupbox->Controls->Add(this->noiseFilterType);
		this->filtersGroupbox->Controls->Add(this->noiseFilter);
		this->filtersGroupbox->Controls->Add(this->resizeFilterType);
		this->filtersGroupbox->Controls->Add(this->resizeFilterLabel);
		this->filtersGroupbox->Enabled = false;
		this->filtersGroupbox->Location = new System::Drawing::Point(3, 291);
		this->filtersGroupbox->Name = "filtersGroupbox";
		this->filtersGroupbox->Size = new System::Drawing::Size(449, 139);
		this->filtersGroupbox->TabIndex = 9;
		this->filtersGroupbox->TabStop = false;
		this->filtersGroupbox->Text = "Filters";
		// 
		// cbCharset
		// 
		this->cbCharset->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->cbCharset->FormattingEnabled = true;
		this->cbCharset->Items->AddRange(new object[20] {"Default", "ANSI", "Symbol", "Shiftjis", "Hangeul", "Hangul", "GB2312", "Chinese Big 5", "OEM", "Johab", "Hebrew", "Arabic", "Greek", "Turkish", "Vietnamese", "Thai", "East Europe", "Russian", "Mac", "Baltic"});
		this->cbCharset->Location = new System::Drawing::Point(151, 108);
		this->cbCharset->Name = "cbCharset";
		this->cbCharset->Size = new System::Drawing::Size(121, 21);
		this->cbCharset->TabIndex = 11;
		this->cbCharset->SelectedIndexChanged += new System::EventHandler(this, &AviSynthWindow::refreshScript);
		// 
		// label8
		// 
		this->label8->AutoSize = true;
		this->label8->Location = new System::Drawing::Point(96, 111);
		this->label8->Name = "label8";
		this->label8->Size = new System::Drawing::Size(49, 13);
		this->label8->TabIndex = 10;
		this->label8->Text = "Charset:";
		// 
		// openSubtitlesButton
		// 
		this->openSubtitlesButton->Location = new System::Drawing::Point(416, 80);
		this->openSubtitlesButton->Name = "openSubtitlesButton";
		this->openSubtitlesButton->Size = new System::Drawing::Size(27, 22);
		this->openSubtitlesButton->TabIndex = 9;
		this->openSubtitlesButton->Text = "...";
		this->openSubtitlesButton->UseVisualStyleBackColor = true;
		this->openSubtitlesButton->Click += new System::EventHandler(this, &AviSynthWindow::openSubtitlesButton_Click);
		// 
		// SubtitlesPath
		// 
		this->SubtitlesPath->BackColor = System::Drawing::SystemColors::Control;
		this->SubtitlesPath->Location = new System::Drawing::Point(97, 80);
		this->SubtitlesPath->Name = "SubtitlesPath";
		this->SubtitlesPath->ReadOnly = true;
		this->SubtitlesPath->Size = new System::Drawing::Size(313, 21);
		this->SubtitlesPath->TabIndex = 8;
		// 
		// SubtitlesLabel
		// 
		this->SubtitlesLabel->AutoSize = true;
		this->SubtitlesLabel->Location = new System::Drawing::Point(9, 83);
		this->SubtitlesLabel->Name = "SubtitlesLabel";
		this->SubtitlesLabel->Size = new System::Drawing::Size(52, 13);
		this->SubtitlesLabel->TabIndex = 7;
		this->SubtitlesLabel->Text = "Subtitles:";
		// 
		// noiseFilterType
		// 
		this->noiseFilterType->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
		this->noiseFilterType->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->noiseFilterType->Enabled = false;
		this->noiseFilterType->Location = new System::Drawing::Point(97, 44);
		this->noiseFilterType->Name = "noiseFilterType";
		this->noiseFilterType->Size = new System::Drawing::Size(239, 21);
		this->noiseFilterType->TabIndex = 5;
		this->noiseFilterType->SelectedIndexChanged += new System::EventHandler(this, &AviSynthWindow::refreshScript);
		// 
		// noiseFilter
		// 
		this->noiseFilter->Location = new System::Drawing::Point(9, 44);
		this->noiseFilter->Name = "noiseFilter";
		this->noiseFilter->Size = new System::Drawing::Size(104, 24);
		this->noiseFilter->TabIndex = 3;
		this->noiseFilter->Text = "Noise Filter";
		this->noiseFilter->CheckedChanged += new System::EventHandler(this, &AviSynthWindow::noiseFilter_CheckedChanged);
		// 
		// resizeFilterType
		// 
		this->resizeFilterType->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
		this->resizeFilterType->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->resizeFilterType->Location = new System::Drawing::Point(97, 17);
		this->resizeFilterType->Name = "resizeFilterType";
		this->resizeFilterType->Size = new System::Drawing::Size(239, 21);
		this->resizeFilterType->TabIndex = 1;
		this->resizeFilterType->SelectedIndexChanged += new System::EventHandler(this, &AviSynthWindow::refreshScript);
		// 
		// resizeFilterLabel
		// 
		this->resizeFilterLabel->Location = new System::Drawing::Point(9, 17);
		this->resizeFilterLabel->Name = "resizeFilterLabel";
		this->resizeFilterLabel->Size = new System::Drawing::Size(100, 23);
		this->resizeFilterLabel->TabIndex = 0;
		this->resizeFilterLabel->Text = "Resize Filter";
		this->resizeFilterLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
		// 
		// editTab
		// 
		this->editTab->Controls->Add(this->openDLLButton);
		this->editTab->Controls->Add(this->dllPath);
		this->editTab->Controls->Add(this->label1);
		this->editTab->Controls->Add(this->avisynthScript);
		this->editTab->Location = new System::Drawing::Point(4, 22);
		this->editTab->Name = "editTab";
		this->editTab->Size = new System::Drawing::Size(455, 433);
		this->editTab->TabIndex = 1;
		this->editTab->Text = "Script";
		this->editTab->UseVisualStyleBackColor = true;
		// 
		// openDLLButton
		// 
		this->openDLLButton->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right)));
		this->openDLLButton->Location = new System::Drawing::Point(420, 399);
		this->openDLLButton->Name = "openDLLButton";
		this->openDLLButton->Size = new System::Drawing::Size(27, 21);
		this->openDLLButton->TabIndex = 3;
		this->openDLLButton->Text = "...";
		this->openDLLButton->Click += new System::EventHandler(this, &AviSynthWindow::openDLLButton_Click);
		// 
		// dllPath
		// 
		this->dllPath->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
		this->dllPath->Location = new System::Drawing::Point(65, 399);
		this->dllPath->Name = "dllPath";
		this->dllPath->ReadOnly = true;
		this->dllPath->Size = new System::Drawing::Size(338, 21);
		this->dllPath->TabIndex = 2;
		// 
		// label1
		// 
		this->label1->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left)));
		this->label1->Location = new System::Drawing::Point(9, 402);
		this->label1->Name = "label1";
		this->label1->Size = new System::Drawing::Size(66, 13);
		this->label1->TabIndex = 1;
		this->label1->Text = "Load DLL";
		// 
		// avisynthScript
		// 
		this->avisynthScript->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
		this->avisynthScript->Font = new System::Drawing::Font("Courier New", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, (static_cast<unsigned char>(0)));
		this->avisynthScript->Location = new System::Drawing::Point(8, 15);
		this->avisynthScript->Multiline = true;
		this->avisynthScript->Name = "avisynthScript";
		this->avisynthScript->ScrollBars = System::Windows::Forms::ScrollBars::Both;
		this->avisynthScript->Size = new System::Drawing::Size(439, 356);
		this->avisynthScript->TabIndex = 0;
		// 
		// saveAvisynthScriptDialog
		// 
		this->saveAvisynthScriptDialog->DefaultExt = "avs";
		this->saveAvisynthScriptDialog->Filter = "AviSynth Script Files|*.avs";
		this->saveAvisynthScriptDialog->Title = "Select a name for the AviSynth script";
		// 
		// openFilterDialog
		// 
		this->openFilterDialog->Filter = "AviSynth Filters|*.dll";
		this->openFilterDialog->Title = "Select an AviSynth Filter";
		// 
		// openSubsDialog
		// 
		this->openSubsDialog->Filter = "Subs Files|*.srt;*.ass;*.ssa;*.idx";
		this->openSubsDialog->Title = "Select a subtitle file";
		// 
		// statusStrip1
		// 
		this->statusStrip1->Items->AddRange(new System::Windows::Forms::ToolStripItem[2] {this->deintProgressBar, this->deintStatusLabel});
		this->statusStrip1->Location = new System::Drawing::Point(0, 511);
		this->statusStrip1->Name = "statusStrip1";
		this->statusStrip1->Size = new System::Drawing::Size(463, 22);
		this->statusStrip1->TabIndex = 6;
		this->statusStrip1->Text = "statusStrip1";
		// 
		// deintProgressBar
		// 
		this->deintProgressBar->Name = "deintProgressBar";
		this->deintProgressBar->Size = new System::Drawing::Size(100, 16);
		// 
		// deintStatusLabel
		// 
		this->deintStatusLabel->Name = "deintStatusLabel";
		this->deintStatusLabel->Size = new System::Drawing::Size(0, 17);
		// 
		// onSaveLoadScript
		// 
		this->onSaveLoadScript->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right)));
		this->onSaveLoadScript->AutoSize = true;
		this->onSaveLoadScript->Checked = true;
		this->onSaveLoadScript->CheckState = System::Windows::Forms::CheckState::Checked;
		this->onSaveLoadScript->Location = new System::Drawing::Point(84, 478);
		this->onSaveLoadScript->Name = "onSaveLoadScript";
		this->onSaveLoadScript->Size = new System::Drawing::Size(210, 17);
		this->onSaveLoadScript->TabIndex = 18;
		this->onSaveLoadScript->Text = "On Save close and load to be encoded";
		// 
		// saveButton
		// 
		this->saveButton->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right)));
		this->saveButton->AutoSize = true;
		this->saveButton->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
		this->saveButton->Location = new System::Drawing::Point(413, 475);
		this->saveButton->Name = "saveButton";
		this->saveButton->Size = new System::Drawing::Size(41, 23);
		this->saveButton->TabIndex = 20;
		this->saveButton->Text = "Save";
		this->saveButton->Click += new System::EventHandler(this, &AviSynthWindow::saveButton_Click);
		// 
		// previewAvsButton
		// 
		this->previewAvsButton->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right)));
		this->previewAvsButton->AutoSize = true;
		this->previewAvsButton->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
		this->previewAvsButton->Location = new System::Drawing::Point(300, 475);
		this->previewAvsButton->Name = "previewAvsButton";
		this->previewAvsButton->Size = new System::Drawing::Size(107, 23);
		this->previewAvsButton->TabIndex = 19;
		this->previewAvsButton->Text = "Preview AVS Script";
		this->previewAvsButton->Click += new System::EventHandler(this, &AviSynthWindow::previewButton_Click);
		// 
		// helpButton1
		// 
		this->helpButton1->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left)));
		this->helpButton1->setArticleName("Avisynth script Creator");
		this->helpButton1->AutoSize = true;
		this->helpButton1->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
		this->helpButton1->Location = new System::Drawing::Point(15, 472);
		this->helpButton1->Name = "helpButton1";
		this->helpButton1->Size = new System::Drawing::Size(38, 23);
		this->helpButton1->TabIndex = 17;
		// 
		// videoOutput
		// 
		this->videoOutput->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
		this->videoOutput->setFilename("");
		this->videoOutput->setFilter("AVI Synth Scripts|*.avs");
		this->videoOutput->setFilterIndex(0);
		this->videoOutput->setFolderMode(false);
		this->videoOutput->Location = new System::Drawing::Point(96, 17);
		this->videoOutput->Name = "videoOutput";
		this->videoOutput->setReadOnly(true);
		this->videoOutput->setSaveMode(true);
		this->videoOutput->Size = new System::Drawing::Size(348, 26);
		this->videoOutput->TabIndex = 7;
		this->videoOutput->setTitle("");
		// 
		// input
		// 
		this->input->AllowDrop = true;
		this->input->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
		this->input->setFilename("");
		this->input->setFilter(resources->GetString("input.Filter"));
		this->input->setFilterIndex(6);
		this->input->setFolderMode(false);
		this->input->Location = new System::Drawing::Point(96, 15);
		this->input->Name = "input";
		this->input->setReadOnly(true);
		this->input->setSaveMode(false);
		this->input->Size = new System::Drawing::Size(348, 26);
		this->input->TabIndex = 1;
		this->input->setTitle("Select a source file");
		this->input->FileSelected += new MeXgui::FileBarEventHandler(this, &AviSynthWindow::input_FileSelected);
		// 
		// avsProfile
		// 
		this->avsProfile->Location = new System::Drawing::Point(96, 111);
		this->avsProfile->Name = "avsProfile";
		this->avsProfile->setProfileSet("AviSynth");
		this->avsProfile->Size = new System::Drawing::Size(348, 22);
		this->avsProfile->TabIndex = 22;
		this->avsProfile->SelectedProfileChanged += new System::EventHandler(this, &AviSynthWindow::ProfileChanged);
		// 
		// arChooser
		// 
		this->arChooser->setCustomDARs(new MeXgui::core::util::Dar[0]);
		this->arChooser->setHasLater(false);
		this->arChooser->Location = new System::Drawing::Point(96, 76);
		this->arChooser->MaximumSize = new System::Drawing::Size(1000, 29);
		this->arChooser->MinimumSize = new System::Drawing::Size(64, 29);
		this->arChooser->Name = "arChooser";
		this->arChooser->setSelectedIndex(0);
		this->arChooser->Size = new System::Drawing::Size(214, 29);
		this->arChooser->TabIndex = 21;
		this->arChooser->SelectionChanged += new MeXgui::StringChanged(this, &AviSynthWindow::inputDARChanged);
		// 
		// AviSynthWindow
		// 
		this->AutoScaleBaseSize = new System::Drawing::Size(5, 14);
		this->ClientSize = new System::Drawing::Size(463, 533);
		this->Controls->Add(this->onSaveLoadScript);
		this->Controls->Add(this->saveButton);
		this->Controls->Add(this->previewAvsButton);
		this->Controls->Add(this->helpButton1);
		this->Controls->Add(this->statusStrip1);
		this->Controls->Add(this->tabControl1);
		this->Font = new System::Drawing::Font("Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, (static_cast<unsigned char>(0)));
		this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
		this->Icon = (static_cast<System::Drawing::Icon*>(resources->GetObject("$this.Icon")));
		this->MaximizeBox = false;
		this->Name = "AviSynthWindow";
		this->Text = "MeXgui - AviSynth script creator";
		this->Shown += new System::EventHandler(this, &AviSynthWindow::AviSynthWindow_Shown);
		this->resNCropGroupbox->ResumeLayout(false);
		this->resNCropGroupbox->PerformLayout();
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->cropLeft))->EndInit();
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->cropRight))->EndInit();
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->cropBottom))->EndInit();
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->cropTop))->EndInit();
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->verticalResolution))->EndInit();
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->horizontalResolution))->EndInit();
		this->tabControl1->ResumeLayout(false);
		this->optionsTab->ResumeLayout(false);
		this->gbOutput->ResumeLayout(false);
		this->videoGroupBox->ResumeLayout(false);
		this->videoGroupBox->PerformLayout();
		this->filterTab->ResumeLayout(false);
		this->tabSources->ResumeLayout(false);
		this->tabPage1->ResumeLayout(false);
		this->mpegOptGroupBox->ResumeLayout(false);
		this->tabPage2->ResumeLayout(false);
		this->aviOptGroupBox->ResumeLayout(false);
		this->aviOptGroupBox->PerformLayout();
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->fpsBox))->EndInit();
		this->tabPage3->ResumeLayout(false);
		this->dgOptions->ResumeLayout(false);
		this->dgOptions->PerformLayout();
		this->deinterlacingGroupBox->ResumeLayout(false);
		this->deinterlacingGroupBox->PerformLayout();
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->deintM))->EndInit();
		this->filtersGroupbox->ResumeLayout(false);
		this->filtersGroupbox->PerformLayout();
		this->editTab->ResumeLayout(false);
		this->editTab->PerformLayout();
		this->statusStrip1->ResumeLayout(false);
		this->statusStrip1->PerformLayout();
		this->ResumeLayout(false);
		this->PerformLayout();

	}

	void AviSynthWindow::InitializeInstanceFields()
	{
		isPreviewMode = false;
		eventsOn = true;
		scriptRefresh = 1;
		delete components;
	}
}
