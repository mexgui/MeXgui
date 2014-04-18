#include "MeGUI.Calculator.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Linq;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::ComponentModel;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Diagnostics;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Drawing;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;
using namespace MeGUI::core::details;
using namespace MeGUI::core::util;
using namespace MeGUI::packages::tools::calculator;
using namespace MeGUI::Properties;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;

namespace MeGUI
{

	Calculator::Calculator(MainForm *mainForm)
	{
		InitializeInstanceFields();
		this->mainForm = mainForm;
		this->muxProvider = mainForm->getMuxProvider();
		this->videoCodec->Items->AddRange(CodecManager::VideoEncoderTypes->getValuesArray());
		videoCodec->SelectedItem = CodecManager::VideoEncoderTypes["x264"];
		this->containerFormat->Items->AddRange(muxProvider->GetSupportedContainers().ToArray());
		containerFormat->SelectedItem = ContainerType::MKV;

		// set complexity from settings
		this->complexity->Minimum = 0;
		this->complexity->Maximum = 100;
		this->complexity->Value = (mainForm->getSettings()->getMinComplexity() + mainForm->getSettings()->getMaxComplexity()) / 2;
		this->complexity->Minimum = mainForm->getSettings()->getMinComplexity();
		this->complexity->Maximum = mainForm->getSettings()->getMaxComplexity();

		// wire the input boxes to auto-select text on focus
		AddAutoSelectHandler(this);

		// set focus of calculate by
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
		this->averageBitrateRadio->Click += (s, args) => projectedBitrate->Focus();
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
		this->bppRadio->Click += (s, args) => bpp->Focus();
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
		this->qEstRadio->Click += (s, args) => qest->Focus();
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
		this->fileSizeRadio->Click += (s, args) => targetSize->Focus();

		// smart focus for audio and extras (try to fix render bug w/ scrollbar)
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
		this->audioExtraFlow->ControlRemoved += (s, args) =>
		{
			int idx = static_cast<int>(args::Control->Tag);
			if (idx > 0)
				audioExtraFlow->Controls[idx - 1]->Focus();
			TagIndexes();
		};
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
		this->audioExtraFlow->ControlAdded += (s, args) =>
		{
			args::Control->Focus();
			TagIndexes();
		};
	}

	void Calculator::SetDefaults(unsigned long long nbFrames, double framerate, int hRes, int vRes, VideoCodecSettings *vSettings, std::vector<AudioJob*> &audioStreams)
	{
		fpsChooser->setValue(static_cast<decimal>(framerate));

		if (nbFrames > 0)
			this->nbFrames->Value = nbFrames;

		if (hRes > 0)
			this->width->Value = hRes;
		if (vRes > 0)
			this->height->Value = vRes;

		if (vSettings != 0)
		{
			bframes->Checked = vSettings->getNbBframes() > 0;

			if (videoCodec->Items->Contains(vSettings->getEncoderType()))
				videoCodec->SelectedItem = vSettings->getEncoderType();
		}

		for (std::vector<AudioJob*>::const_iterator job = audioStreams.begin(); job != audioStreams.end(); ++job)
		{
			MeGUI::packages::tools::calculator::AudioTrackSizeTab *a = AddAudio();
			a->SetAudioJob(*job);
		}

		// make sure there is at least one audio displayed
		if (GetAudioStreams()->Count() == 0)
			AddAudio();
	}

	const VideoEncoderType &Calculator::getSelectedVCodec() const
	{
		return static_cast<VideoEncoderType*>(videoCodec->SelectedItem);
	}

	const int &Calculator::getVideoBitrate() const
	{
		return static_cast<int>(projectedBitrate->Value);
	}

	void Calculator::audio_SelectedIndexChanged(object *sender, System::EventArgs *e)
	{
		UpdateContainers();
		Calculate();
	}

	void Calculator::textField_TextChanged(object *sender, System::EventArgs *e)
	{
//C# TO C++ CONVERTER TODO TASK: There is no built-in support for multithreading in native C++:
		lock(this)
		{
			if (dynamic_cast<NumericUpDown*>(sender) != 0 && !this->isUpdating)
			{
				this->isUpdating = true;
				NumericUpDown *tb = static_cast<NumericUpDown*>(sender);
				decimal value = tb->Value;
				if (tb == totalSeconds)
				{
					int hours = static_cast<int>(value) / 3600;
					value -= hours * 3600;
					int minutes = static_cast<int>(value) / 60;
					value -= minutes * 60;
					if (hours <= this->hours->Maximum)
					{
						this->hours->Value = hours;
						this->minutes->Value = minutes;
						this->seconds->Value = value;
					}
					else // We set to max available time and set frames accordingly
					{
						this->hours->Value = this->hours->Maximum;
						this->minutes->Value = this->minutes->Maximum - 1; //59 mins
						this->seconds->Value = this->seconds->Maximum - 1; //59 seconds
					}
					UpdateTotalSeconds();
					SetAudioLength();
					UpdateTotalFrames();

				}
				else if (tb == nbFrames)
				{
					int secs = static_cast<int>(value / fpsChooser->getValue());
					totalSeconds->Text = StringConverterHelper::toString(secs);
					int hours = secs / 3600;
					secs -= hours * 3600;
					int minutes = secs / 60;
					secs -= minutes * 60;
					if (hours < this->hours->Maximum)
					{
						this->hours->Value = hours;
						this->minutes->Value = minutes;
						this->seconds->Value = secs;
					}
					else //Set to max available time and set frames accordingly
					{
						this->hours->Value = this->hours->Maximum;
						this->minutes->Value = this->minutes->Maximum - 1; //59 minutes
						this->seconds->Value = this->seconds->Maximum - 1; //59 seconds
						UpdateTotalFrames();
					}
					UpdateTotalSeconds();
					SetAudioLength();
				}
				else if (tb == projectedBitrate)
				{
					if (averageBitrateRadio->Checked) // only do something here if we're in size calculation mode
						Calculate();
				}
				tb->Select(tb->Text->Length, 0);
				if ((averageBitrateRadio->Checked && tb != projectedBitrate) || !averageBitrateRadio->Checked)
					Calculate();

				this->isUpdating = false;
			}
		}
	}

	void Calculator::time_ValueChanged(object *sender, System::EventArgs *e)
	{
//C# TO C++ CONVERTER TODO TASK: There is no built-in support for multithreading in native C++:
		lock (this)
		{
			if (isUpdating)
				return;

			this->isUpdating = true;
			NumericUpDown *ud = static_cast<NumericUpDown*>(sender);

			if (this->hours->Value->Equals(this->hours->Maximum))
			{
				if (this->minutes->Value == 60)
				{
					this->minutes->Value = 59;
					UpdateTotalSeconds();
					UpdateTotalFrames();
					isUpdating = false;
					return; // we can't increase the time
				}
				else if (this->seconds->Value == 60 && this->minutes->Value == 59)
				{
					this->seconds->Value = 59;
					UpdateTotalSeconds();
					UpdateTotalFrames();
					isUpdating = false;
					return; // we can't increase the time
				}
			}
			if (ud->Value == 60) // time to wrap
			{
				ud->Value = 0;
				if (ud == seconds)
				{
					if (minutes->Value == 59)
					{
						minutes->Value = 0;
						if (!this->hours->Value->Equals(this->hours->Maximum))
							hours->Value += 1;
					}
					else
						minutes->Value += 1;
				}
				else if (ud == minutes)
				{
					minutes->Value = 0;
					if (this->hours->Value < this->hours->Maximum)
						hours->Value += 1;
				}
			}
			UpdateTotalSeconds();
			SetAudioLength();
			UpdateTotalFrames();
			Calculate();

			this->isUpdating = false;
		}
	}

	void Calculator::calculationMode_CheckedChanged(object *sender, System::EventArgs *e)
	{
		RadioButton *rb = static_cast<RadioButton*>(sender);
		if (rb->Checked)
		{
			if (rb == averageBitrateRadio)
			{
				targetSize->Enabled = false;
				projectedBitrate->ReadOnly = false;
				bpp->ReadOnly = true;
				qest->ReadOnly = true;
			}
			else if (rb == bppRadio)
			{
				targetSize->Enabled = false;
				projectedBitrate->ReadOnly = true;
				bpp->ReadOnly = false;
				qest->ReadOnly = true;
			}
			else if (rb == qEstRadio)
			{
				targetSize->Enabled = false;
				projectedBitrate->ReadOnly = true;
				bpp->ReadOnly = true;
				qest->ReadOnly = false;
			}
			else
			{
				targetSize->Enabled = true;
				projectedBitrate->ReadOnly = true;
				bpp->ReadOnly = true;
				qest->ReadOnly = true;
			}
		}
	}

	void Calculator::codec_CheckedChanged(object *sender, System::EventArgs *e)
	{
		UpdateContainers();
		Calculate();
	}

	void Calculator::bframes_CheckedChanged(object *sender, System::EventArgs *e)
	{
		Calculate();
	}

	void Calculator::targetSize_SelectionChanged(object *sender, const std::string &val)
	{
		Calculate();
	}

	void Calculator::fpsChooser_SelectionChanged(object *sender, const std::string &val)
	{
		double framerate = static_cast<double>(fpsChooser->getValue());
		int length = static_cast<int>(totalSeconds->Value);
		int numberOfFrames = static_cast<int>(length * framerate);
		nbFrames->Value = numberOfFrames;
		this->Calculate();
	}

	void Calculator::addExtraToolStripMenuItem_Click(object *sender, EventArgs *e)
	{
		AddExtra();
	}

	void Calculator::addAudioToolStripMenuItem_Click(object *sender, EventArgs *e)
	{
		AddAudio();
	}

	void Calculator::addAudioLink_Clicked(object *sender, EventArgs *e)
	{
		contextMenuStrip1->Show(addAudioLink, 0, addAudioLink->Height);
	}

	void Calculator::picTime_Click(object *sender, EventArgs *e)
	{
		Image *i = picTime->Image;
		picTime->Image = picTime->InitialImage;
		picTime->InitialImage = i;

		bool showTotal = hoursLabel->Visible;

		hours->Visible = !showTotal;
		hoursLabel->Visible = !showTotal;
		minutes->Visible = !showTotal;
		minutesLabel->Visible = !showTotal;
		seconds->Visible = !showTotal;
		secondsLabel->Visible = !showTotal;

		totalSeconds->Visible = showTotal;
		totalSecondsLabel->Visible = showTotal;
		timeText->Visible = showTotal;

		this->toolTip1->SetToolTip(this->picTime, showTotal ? "Show hours, minutes, seconds" : "Show total seconds");
	}

	void Calculator::SetAudioLength()
	{
		for (unknown::const_iterator c = audioExtraFlow->Controls.begin(); c != audioExtraFlow->Controls.end(); ++c)
		{
			if (dynamic_cast<AudioTrackSizeTab*>(*c) != 0)
			{
				AudioTrackSizeTab *a = static_cast<AudioTrackSizeTab*>(*c);
				a->setPlayLength(static_cast<int>(totalSeconds->Value));
			}
		}
	}

	void Calculator::UpdateTotalFrames()
	{
		int secs = static_cast<int>(totalSeconds->Value);
		double fps = static_cast<double>(fpsChooser->getValue());
		int frameNumber = static_cast<int>(static_cast<double>(secs) * fps);
		nbFrames->Value = frameNumber;
	}

	void Calculator::UpdateTotalSeconds()
	{
		int secs = static_cast<int>(this->hours->Value) * 3600 + static_cast<int>(this->minutes->Value) * 60 + static_cast<int>(this->seconds->Value);
		totalSeconds->Value = secs;
		timeText->Text = std::string::Format("{0}h {1}m {2}s", this->hours->Value, this->minutes->Value, this->seconds->Value);
	}

	void Calculator::UpdateContainers()
	{
		if (updatingContainers)
			return;

		updatingContainers = true;
		std::vector<MuxableType*> muxableTypes = std::vector<MuxableType*>();
		muxableTypes.AddRange(GetAudioTypes());
		ContainerType *previousContainer = 0;
		try
		{
			previousContainer = dynamic_cast<ContainerType*>(containerFormat->SelectedItem);
		}
		catch (std::exception &e1)
		{
		}

		containerFormat->Items->Clear();
		containerFormat->Items->AddRange(muxProvider->GetSupportedContainers(getSelectedVCodec(), new AudioEncoderType[0], muxableTypes.ToArray()).ToArray());
		if (previousContainer != 0 && containerFormat->Items->Contains(previousContainer))
			containerFormat->SelectedItem = previousContainer;
		updatingContainers = false;
	}

	MeGUI::packages::tools::calculator::AudioTrackSizeTab *Calculator::AddAudio()
	{
		AudioTrackSizeTab *a = new AudioTrackSizeTab();
		a->SomethingChanged += new System::EventHandler(this, &Calculator::audio_SelectedIndexChanged);
		a->setPlayLength(static_cast<int>(totalSeconds->Value));
		audioExtraFlow->Controls->Add(a);
		UpdateContainers();
		Calculate();
		return a;
	}

	MeGUI::packages::tools::calculator::ExtraSizeTab *Calculator::AddExtra()
	{
		ExtraSizeTab *a = new ExtraSizeTab();
		a->SomethingChanged += new System::EventHandler(this, &Calculator::audio_SelectedIndexChanged);
		audioExtraFlow->Controls->Add(a);
		UpdateContainers();
		Calculate();
		return a;
	}

	void Calculator::TagIndexes()
	{
		for (int i = 0; i < audioExtraFlow->Controls->Count; i++)
		{
			audioExtraFlow->Controls[i]->Tag = i;
		}
	}

	void Calculator::AddAutoSelectHandler(Control *control)
	{
		// auto select text when focus numeric field
		for (unknown::const_iterator c = control->Controls.begin(); c != control->Controls.end(); ++c)
		{
			if ((*c)->HasChildren)
				AddAutoSelectHandler(*c);
			if (dynamic_cast<NumericUpDown*>(*c) != 0)
			{
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
				(static_cast<NumericUpDown*>(*c))->Enter += (s, args) => (static_cast<NumericUpDown*>(s))->Select(0, (static_cast<NumericUpDown*>(s))->Text->Length);
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
				(static_cast<NumericUpDown*>(*c))->Click += (s, args) => (static_cast<NumericUpDown*>(s))->Select(0, (static_cast<NumericUpDown*>(s))->Text->Length);
			}
		}
	}

	IEnumerable<AudioBitrateCalculationStream*> *Calculator::GetAudioStreams()
	{
		for (unknown::const_iterator c = audioExtraFlow->Controls.begin(); c != audioExtraFlow->Controls.end(); ++c)
		{
			if (dynamic_cast<AudioTrackSizeTab*>(*c) != 0)
			{
				AudioTrackSizeTab *a = static_cast<AudioTrackSizeTab*>(*c);
				if (a->getStream() != 0)
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
					yield return a->getStream();
			}
		}
	}

	MeGUI::core::util::FileSize Calculator::GetTotalExtraSize()
	{
		FileSize size = FileSize::Empty;
		for (unknown::const_iterator c = audioExtraFlow->Controls.begin(); c != audioExtraFlow->Controls.end(); ++c)
		{
			if (dynamic_cast<ExtraSizeTab*>(*c) != 0)
				size += (static_cast<ExtraSizeTab*>(*c))->FileSize;
		}
		return size;
	}

	IEnumerable<MuxableType*> *Calculator::GetAudioTypes()
	{
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++0x inferred typing option is selected:
		for (IEnumerable<AudioBitrateCalculationStream*>::const_iterator s = GetAudioStreams()->begin(); s != GetAudioStreams()->end(); ++s)
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
			yield return new MuxableType((*s)->AType, (*s)->AType->SupportedCodecs[0]);
	}

	void Calculator::Calculate()
	{
		if (calculating)
			return;
		calculating = true;
		try
		{

			Nullable<decimal> tempVar = fpsChooser.getValue();
			CalcData *data = new CalcData(static_cast<long long>(nbFrames->Value), tempVar::HasValue ? tempVar : 0);
			data->setFrameSize(new Size(static_cast<int>(width->Value), static_cast<int>(height->Value)));
			data->setExtraSize(GetTotalExtraSize());
			data->setAudioStreams(GetAudioStreams()->ToArray());
			data->setContainerType(dynamic_cast<ContainerType*>(containerFormat->SelectedItem));
			data->setHasBFrames(bframes->Checked);
			data->setVideoCodec(getSelectedVCodec()->getVCodec());
			data->setQualityCoeffient(static_cast<float>(complexity->Value) / 100);

			if (fileSizeRadio->Checked) // get video, bpp, qest
			{
				data->setTotalSize(FileSize(targetSize->getValue().Value::Bytes));
				data->CalcByTotalSize();
			}
			else if (this->bppRadio->Checked) // get video, quest, total
			{
				data->setBitsPerPixel(static_cast<float>(bpp->Value));
				data->CalcByBitsPerPixel();
			}
			else if (this->qEstRadio->Checked) // get video, bpp, total
			{
				data->setQualityEstimate(static_cast<float>(qest->Value));
				data->CalcByQualityEstimate();
			}
			else // given video size, get total, bpp, quest
			{
				data->setVideoBitrate(projectedBitrate->Value);
				data->CalcByVideoSize();
			}

			targetSize->setValue(FileSize(KB, data->getTotalSize().getKB()));
			projectedBitrate->Value = data->getVideoBitrate();
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
			videoSize->Text = (FileSize(KB, data->getVideoSize().getKB())).ToString();
			bpp->Value = static_cast<decimal>(data->getBitsPerPixel());
			qest->Value = static_cast<decimal>(data->getQualityEstimate());
			applyButton->Enabled = true;
		}
		catch (std::exception &ex)
		{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
			Trace::TraceError(ex.ToString());
			applyButton->Enabled = false;
			videoSize->Text = "";
			if (fileSizeRadio->Checked)
			{
				bpp->Value = 0;
				qest->Value = 0;
				projectedBitrate->Value = 0;
			}
			else if (this->bppRadio->Checked)
			{
				qest->Value = 0;
				projectedBitrate->Value = 0;
				targetSize->setValue(Nullable<FileSize>());
			}
			else if (this->qEstRadio->Checked)
			{
				bpp->Value = 0;
				projectedBitrate->Value = 0;
				targetSize->setValue(Nullable<FileSize>());
			}
			else
			{
				bpp->Value = 0;
				qest->Value = 0;
				targetSize->setValue(Nullable<FileSize>());
			}
		}
		calculating = false;
	}

	Calculator::Calculator()
	{
		InitializeInstanceFields();
		InitializeComponent();
	}

	void Calculator::Dispose(bool disposing)
	{
		if (disposing && (components != 0))
		{
			delete components;
		}
		System::Windows::Forms::Form::Dispose(disposing);
	}

	void Calculator::InitializeComponent()
	{
		this->components = new System::ComponentModel::Container();
		System::ComponentModel::ComponentResourceManager *resources = new System::ComponentModel::ComponentResourceManager(Calculator::typeid);
		this->videoGroupbox = new System::Windows::Forms::GroupBox();
		this->label3 = new System::Windows::Forms::Label();
		this->label7 = new System::Windows::Forms::Label();
		this->label9 = new System::Windows::Forms::Label();
		this->height = new System::Windows::Forms::NumericUpDown();
		this->label10 = new System::Windows::Forms::Label();
		this->width = new System::Windows::Forms::NumericUpDown();
		this->label8 = new System::Windows::Forms::Label();
		this->label2 = new System::Windows::Forms::Label();
		this->videoCodec = new System::Windows::Forms::ComboBox();
		this->fpsChooser = new MeGUI::core::gui::FPSChooser();
		this->nbFrames = new System::Windows::Forms::NumericUpDown();
		this->bframes = new System::Windows::Forms::CheckBox();
		this->nbFramesLabel = new System::Windows::Forms::Label();
		this->framerateLabel = new System::Windows::Forms::Label();
		this->secondsLabel = new System::Windows::Forms::Label();
		this->minutesLabel = new System::Windows::Forms::Label();
		this->hoursLabel = new System::Windows::Forms::Label();
		this->seconds = new System::Windows::Forms::NumericUpDown();
		this->minutes = new System::Windows::Forms::NumericUpDown();
		this->hours = new System::Windows::Forms::NumericUpDown();
		this->complexity = new System::Windows::Forms::TrackBar();
		this->picTime = new System::Windows::Forms::PictureBox();
		this->totalSecondsLabel = new System::Windows::Forms::Label();
		this->totalSeconds = new System::Windows::Forms::NumericUpDown();
		this->timeText = new System::Windows::Forms::TextBox();
		this->applyButton = new System::Windows::Forms::Button();
		this->containerFormat = new System::Windows::Forms::ComboBox();
		this->sizeGroupbox = new System::Windows::Forms::GroupBox();
		this->qEstRadio = new System::Windows::Forms::RadioButton();
		this->qest = new System::Windows::Forms::NumericUpDown();
		this->bppRadio = new System::Windows::Forms::RadioButton();
		this->bpp = new System::Windows::Forms::NumericUpDown();
		this->videoSize = new System::Windows::Forms::TextBox();
		this->targetSize = new MeGUI::core::gui::TargetSizeSCBox();
		this->projectedBitrate = new System::Windows::Forms::NumericUpDown();
		this->fileSizeRadio = new System::Windows::Forms::RadioButton();
		this->AverageBitrateLabel = new System::Windows::Forms::Label();
		this->averageBitrateRadio = new System::Windows::Forms::RadioButton();
		this->cancelButton = new System::Windows::Forms::Button();
		this->openFileDialog = new System::Windows::Forms::OpenFileDialog();
		this->contextMenuStrip1 = new System::Windows::Forms::ContextMenuStrip(this->components);
		this->addAudioToolStripMenuItem = new System::Windows::Forms::ToolStripMenuItem();
		this->addExtraToolStripMenuItem = new System::Windows::Forms::ToolStripMenuItem();
		this->containerGroupbox = new System::Windows::Forms::GroupBox();
		this->audioExtraGroupbox = new System::Windows::Forms::GroupBox();
		this->addAudioLink = new System::Windows::Forms::LinkLabel();
		this->audioExtraFlow = new System::Windows::Forms::FlowLayoutPanel();
		this->addToolTip = new System::Windows::Forms::ToolTip(this->components);
		this->toolTip1 = new System::Windows::Forms::ToolTip(this->components);
		this->helpButton1 = new MeGUI::core::gui::HelpButton();
		this->videoGroupbox->SuspendLayout();
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->height))->BeginInit();
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->width))->BeginInit();
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->nbFrames))->BeginInit();
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->seconds))->BeginInit();
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->minutes))->BeginInit();
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->hours))->BeginInit();
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->complexity))->BeginInit();
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->picTime))->BeginInit();
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->totalSeconds))->BeginInit();
		this->sizeGroupbox->SuspendLayout();
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->qest))->BeginInit();
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->bpp))->BeginInit();
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->projectedBitrate))->BeginInit();
		this->contextMenuStrip1->SuspendLayout();
		this->containerGroupbox->SuspendLayout();
		this->audioExtraGroupbox->SuspendLayout();
		this->SuspendLayout();
		// 
		// videoGroupbox
		// 
		this->videoGroupbox->Controls->Add(this->label3);
		this->videoGroupbox->Controls->Add(this->label7);
		this->videoGroupbox->Controls->Add(this->label9);
		this->videoGroupbox->Controls->Add(this->height);
		this->videoGroupbox->Controls->Add(this->label10);
		this->videoGroupbox->Controls->Add(this->width);
		this->videoGroupbox->Controls->Add(this->label8);
		this->videoGroupbox->Controls->Add(this->label2);
		this->videoGroupbox->Controls->Add(this->videoCodec);
		this->videoGroupbox->Controls->Add(this->fpsChooser);
		this->videoGroupbox->Controls->Add(this->nbFrames);
		this->videoGroupbox->Controls->Add(this->bframes);
		this->videoGroupbox->Controls->Add(this->nbFramesLabel);
		this->videoGroupbox->Controls->Add(this->framerateLabel);
		this->videoGroupbox->Controls->Add(this->secondsLabel);
		this->videoGroupbox->Controls->Add(this->minutesLabel);
		this->videoGroupbox->Controls->Add(this->hoursLabel);
		this->videoGroupbox->Controls->Add(this->seconds);
		this->videoGroupbox->Controls->Add(this->minutes);
		this->videoGroupbox->Controls->Add(this->hours);
		this->videoGroupbox->Controls->Add(this->complexity);
		this->videoGroupbox->Controls->Add(this->picTime);
		this->videoGroupbox->Controls->Add(this->totalSecondsLabel);
		this->videoGroupbox->Controls->Add(this->totalSeconds);
		this->videoGroupbox->Controls->Add(this->timeText);
		this->videoGroupbox->Location = new System::Drawing::Point(8, 9);
		this->videoGroupbox->Name = "videoGroupbox";
		this->videoGroupbox->Size = new System::Drawing::Size(470, 150);
		this->videoGroupbox->TabIndex = 0;
		this->videoGroupbox->TabStop = false;
		this->videoGroupbox->Text = "Video";
		// 
		// label3
		// 
		this->label3->AutoSize = true;
		this->label3->Location = new System::Drawing::Point(291, 122);
		this->label3->Name = "label3";
		this->label3->Size = new System::Drawing::Size(28, 13);
		this->label3->TabIndex = 26;
		this->label3->Text = "High";
		this->label3->TextAlign = System::Drawing::ContentAlignment::TopCenter;
		// 
		// label7
		// 
		this->label7->AutoSize = true;
		this->label7->Location = new System::Drawing::Point(136, 76);
		this->label7->Name = "label7";
		this->label7->Size = new System::Drawing::Size(60, 13);
		this->label7->TabIndex = 20;
		this->label7->Text = "Complexity";
		// 
		// label9
		// 
		this->label9->AutoSize = true;
		this->label9->Location = new System::Drawing::Point(401, 77);
		this->label9->Name = "label9";
		this->label9->Size = new System::Drawing::Size(38, 13);
		this->label9->TabIndex = 25;
		this->label9->Text = "Height";
		// 
		// height
		// 
		this->height->Increment = decimal(new int[4] {8, 0, 0, 0});
		this->height->Location = new System::Drawing::Point(404, 96);
		this->height->Maximum = decimal(new int[4] {10000, 0, 0, 0});
		this->height->Name = "height";
		this->height->Size = new System::Drawing::Size(50, 21);
		this->height->TabIndex = 11;
		this->height->Value = decimal(new int[4] {720, 0, 0, 0});
		this->height->ValueChanged += new System::EventHandler(this, &Calculator::textField_TextChanged);
		// 
		// label10
		// 
		this->label10->AutoSize = true;
		this->label10->Location = new System::Drawing::Point(336, 77);
		this->label10->Name = "label10";
		this->label10->Size = new System::Drawing::Size(35, 13);
		this->label10->TabIndex = 23;
		this->label10->Text = "Width";
		// 
		// width
		// 
		this->width->Increment = decimal(new int[4] {8, 0, 0, 0});
		this->width->Location = new System::Drawing::Point(339, 96);
		this->width->Maximum = decimal(new int[4] {10000, 0, 0, 0});
		this->width->Name = "width";
		this->width->Size = new System::Drawing::Size(50, 21);
		this->width->TabIndex = 10;
		this->width->Value = decimal(new int[4] {1280, 0, 0, 0});
		this->width->ValueChanged += new System::EventHandler(this, &Calculator::textField_TextChanged);
		// 
		// label8
		// 
		this->label8->AutoSize = true;
		this->label8->Location = new System::Drawing::Point(139, 122);
		this->label8->Name = "label8";
		this->label8->Size = new System::Drawing::Size(26, 13);
		this->label8->TabIndex = 21;
		this->label8->Text = "Low";
		this->label8->TextAlign = System::Drawing::ContentAlignment::TopCenter;
		// 
		// label2
		// 
		this->label2->AutoSize = true;
		this->label2->Location = new System::Drawing::Point(11, 76);
		this->label2->Name = "label2";
		this->label2->Size = new System::Drawing::Size(37, 13);
		this->label2->TabIndex = 14;
		this->label2->Text = "Codec";
		// 
		// videoCodec
		// 
		this->videoCodec->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->videoCodec->FormattingEnabled = true;
		this->videoCodec->Location = new System::Drawing::Point(14, 95);
		this->videoCodec->Name = "videoCodec";
		this->videoCodec->Size = new System::Drawing::Size(103, 21);
		this->videoCodec->TabIndex = 7;
		this->videoCodec->SelectedIndexChanged += new System::EventHandler(this, &Calculator::audio_SelectedIndexChanged);
		// 
		// fpsChooser
		// 
		this->fpsChooser->Location = new System::Drawing::Point(243, 40);
		this->fpsChooser->MaximumSize = new System::Drawing::Size(1000, 29);
		this->fpsChooser->MinimumSize = new System::Drawing::Size(64, 29);
		this->fpsChooser->Name = "fpsChooser";
		this->fpsChooser->setNullString("");
		this->fpsChooser->setSelectedIndex(0);
		this->fpsChooser->Size = new System::Drawing::Size(98, 29);
		this->fpsChooser->TabIndex = 4;
		this->fpsChooser->SelectionChanged += new MeGUI::StringChanged(this, &Calculator::fpsChooser_SelectionChanged);
		// 
		// nbFrames
		// 
		this->nbFrames->Location = new System::Drawing::Point(374, 45);
		this->nbFrames->Maximum = decimal(new int[4] {10000000, 10000000, 10000000, 0});
		this->nbFrames->Name = "nbFrames";
		this->nbFrames->Size = new System::Drawing::Size(80, 21);
		this->nbFrames->TabIndex = 5;
		this->nbFrames->ThousandsSeparator = true;
		this->nbFrames->ValueChanged += new System::EventHandler(this, &Calculator::textField_TextChanged);
		// 
		// bframes
		// 
		this->bframes->Checked = true;
		this->bframes->CheckState = System::Windows::Forms::CheckState::Checked;
		this->bframes->Location = new System::Drawing::Point(14, 121);
		this->bframes->Name = "bframes";
		this->bframes->Size = new System::Drawing::Size(75, 17);
		this->bframes->TabIndex = 8;
		this->bframes->Text = "B-frames";
		this->bframes->CheckedChanged += new System::EventHandler(this, &Calculator::bframes_CheckedChanged);
		// 
		// nbFramesLabel
		// 
		this->nbFramesLabel->AutoSize = true;
		this->nbFramesLabel->Location = new System::Drawing::Point(371, 26);
		this->nbFramesLabel->Name = "nbFramesLabel";
		this->nbFramesLabel->Size = new System::Drawing::Size(69, 13);
		this->nbFramesLabel->TabIndex = 10;
		this->nbFramesLabel->Text = "Total Frames";
		// 
		// framerateLabel
		// 
		this->framerateLabel->AutoSize = true;
		this->framerateLabel->Location = new System::Drawing::Point(243, 26);
		this->framerateLabel->Name = "framerateLabel";
		this->framerateLabel->Size = new System::Drawing::Size(57, 13);
		this->framerateLabel->TabIndex = 8;
		this->framerateLabel->Text = "Framerate";
		// 
		// secondsLabel
		// 
		this->secondsLabel->AutoSize = true;
		this->secondsLabel->Location = new System::Drawing::Point(165, 26);
		this->secondsLabel->Name = "secondsLabel";
		this->secondsLabel->Size = new System::Drawing::Size(47, 13);
		this->secondsLabel->TabIndex = 4;
		this->secondsLabel->Text = "Seconds";
		// 
		// minutesLabel
		// 
		this->minutesLabel->AutoSize = true;
		this->minutesLabel->Location = new System::Drawing::Point(107, 26);
		this->minutesLabel->Name = "minutesLabel";
		this->minutesLabel->Size = new System::Drawing::Size(44, 13);
		this->minutesLabel->TabIndex = 2;
		this->minutesLabel->Text = "Minutes";
		// 
		// hoursLabel
		// 
		this->hoursLabel->AutoSize = true;
		this->hoursLabel->Location = new System::Drawing::Point(49, 26);
		this->hoursLabel->Name = "hoursLabel";
		this->hoursLabel->Size = new System::Drawing::Size(35, 13);
		this->hoursLabel->TabIndex = 0;
		this->hoursLabel->Text = "Hours";
		// 
		// seconds
		// 
		this->seconds->Location = new System::Drawing::Point(168, 45);
		this->seconds->Maximum = decimal(new int[4] {60, 0, 0, 0});
		this->seconds->Name = "seconds";
		this->seconds->Size = new System::Drawing::Size(45, 21);
		this->seconds->TabIndex = 3;
		this->seconds->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
		this->seconds->ValueChanged += new System::EventHandler(this, &Calculator::time_ValueChanged);
		// 
		// minutes
		// 
		this->minutes->Location = new System::Drawing::Point(110, 45);
		this->minutes->Maximum = decimal(new int[4] {60, 0, 0, 0});
		this->minutes->Name = "minutes";
		this->minutes->Size = new System::Drawing::Size(45, 21);
		this->minutes->TabIndex = 2;
		this->minutes->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
		this->minutes->ValueChanged += new System::EventHandler(this, &Calculator::time_ValueChanged);
		// 
		// hours
		// 
		this->hours->Location = new System::Drawing::Point(52, 45);
		this->hours->Maximum = decimal(new int[4] {24, 0, 0, 0});
		this->hours->Name = "hours";
		this->hours->Size = new System::Drawing::Size(45, 21);
		this->hours->TabIndex = 1;
		this->hours->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
		this->hours->ValueChanged += new System::EventHandler(this, &Calculator::time_ValueChanged);
		// 
		// complexity
		// 
		this->complexity->LargeChange = 2;
		this->complexity->Location = new System::Drawing::Point(134, 95);
		this->complexity->Maximum = 78;
		this->complexity->Minimum = 72;
		this->complexity->Name = "complexity";
		this->complexity->Size = new System::Drawing::Size(188, 45);
		this->complexity->TabIndex = 9;
		this->complexity->TickFrequency = 5;
		this->complexity->TickStyle = System::Windows::Forms::TickStyle::None;
		this->complexity->Value = 75;
		this->complexity->ValueChanged += new System::EventHandler(this, &Calculator::bframes_CheckedChanged);
		// 
		// picTime
		// 
		this->picTime->Cursor = System::Windows::Forms::Cursors::Hand;
		this->picTime->Image = (static_cast<System::Drawing::Image*>(resources->GetObject("picTime.Image")));
		this->picTime->InitialImage = (static_cast<System::Drawing::Image*>(resources->GetObject("picTime.InitialImage")));
		this->picTime->Location = new System::Drawing::Point(12, 32);
		this->picTime->Name = "picTime";
		this->picTime->Size = new System::Drawing::Size(32, 32);
		this->picTime->SizeMode = System::Windows::Forms::PictureBoxSizeMode::CenterImage;
		this->picTime->TabIndex = 27;
		this->picTime->TabStop = false;
		this->toolTip1->SetToolTip(this->picTime, "Show total seconds");
		this->picTime->Click += new System::EventHandler(this, &Calculator::picTime_Click);
		// 
		// totalSecondsLabel
		// 
		this->totalSecondsLabel->Location = new System::Drawing::Point(49, 26);
		this->totalSecondsLabel->Name = "totalSecondsLabel";
		this->totalSecondsLabel->Size = new System::Drawing::Size(126, 15);
		this->totalSecondsLabel->TabIndex = 6;
		this->totalSecondsLabel->Text = "Total Length in Seconds";
		this->totalSecondsLabel->Visible = false;
		// 
		// totalSeconds
		// 
		this->totalSeconds->Location = new System::Drawing::Point(52, 45);
		this->totalSeconds->Maximum = decimal(new int[4] {90000, 0, 0, 0});
		this->totalSeconds->Name = "totalSeconds";
		this->totalSeconds->Size = new System::Drawing::Size(65, 21);
		this->totalSeconds->TabIndex = 1;
		this->totalSeconds->ThousandsSeparator = true;
		this->totalSeconds->Visible = false;
		this->totalSeconds->ValueChanged += new System::EventHandler(this, &Calculator::textField_TextChanged);
		// 
		// timeText
		// 
		this->timeText->Location = new System::Drawing::Point(123, 45);
		this->timeText->Name = "timeText";
		this->timeText->ReadOnly = true;
		this->timeText->Size = new System::Drawing::Size(89, 21);
		this->timeText->TabIndex = 28;
		this->timeText->TabStop = false;
		this->timeText->Text = "0h 0m 0s";
		this->timeText->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
		this->timeText->Visible = false;
		// 
		// applyButton
		// 
		this->applyButton->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right)));
		this->applyButton->DialogResult = System::Windows::Forms::DialogResult::OK;
		this->applyButton->Enabled = false;
		this->applyButton->Location = new System::Drawing::Point(597, 319);
		this->applyButton->Name = "applyButton";
		this->applyButton->Size = new System::Drawing::Size(78, 23);
		this->applyButton->TabIndex = 23;
		this->applyButton->Text = "Apply";
		// 
		// containerFormat
		// 
		this->containerFormat->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
		this->containerFormat->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->containerFormat->FormattingEnabled = true;
		this->containerFormat->ItemHeight = 13;
		this->containerFormat->Location = new System::Drawing::Point(16, 26);
		this->containerFormat->Name = "containerFormat";
		this->containerFormat->Size = new System::Drawing::Size(175, 21);
		this->containerFormat->TabIndex = 14;
		this->containerFormat->SelectedIndexChanged += new System::EventHandler(this, &Calculator::audio_SelectedIndexChanged);
		// 
		// sizeGroupbox
		// 
		this->sizeGroupbox->Controls->Add(this->qEstRadio);
		this->sizeGroupbox->Controls->Add(this->qest);
		this->sizeGroupbox->Controls->Add(this->bppRadio);
		this->sizeGroupbox->Controls->Add(this->bpp);
		this->sizeGroupbox->Controls->Add(this->videoSize);
		this->sizeGroupbox->Controls->Add(this->targetSize);
		this->sizeGroupbox->Controls->Add(this->projectedBitrate);
		this->sizeGroupbox->Controls->Add(this->fileSizeRadio);
		this->sizeGroupbox->Controls->Add(this->AverageBitrateLabel);
		this->sizeGroupbox->Controls->Add(this->averageBitrateRadio);
		this->sizeGroupbox->Location = new System::Drawing::Point(484, 89);
		this->sizeGroupbox->Name = "sizeGroupbox";
		this->sizeGroupbox->Size = new System::Drawing::Size(209, 224);
		this->sizeGroupbox->TabIndex = 15;
		this->sizeGroupbox->TabStop = false;
		this->sizeGroupbox->Text = "Calculate By";
		// 
		// qEstRadio
		// 
		this->qEstRadio->AutoSize = true;
		this->qEstRadio->Location = new System::Drawing::Point(117, 94);
		this->qEstRadio->Name = "qEstRadio";
		this->qEstRadio->Size = new System::Drawing::Size(77, 17);
		this->qEstRadio->TabIndex = 17;
		this->qEstRadio->TabStop = true;
		this->qEstRadio->Text = "Q Estimate";
		this->qEstRadio->UseVisualStyleBackColor = true;
		this->qEstRadio->CheckedChanged += new System::EventHandler(this, &Calculator::calculationMode_CheckedChanged);
		// 
		// qest
		// 
		this->qest->DecimalPlaces = 2;
		this->qest->Increment = decimal(new int[4] {1, 0, 0, 65536});
		this->qest->Location = new System::Drawing::Point(121, 117);
		this->qest->Name = "qest";
		this->qest->ReadOnly = true;
		this->qest->Size = new System::Drawing::Size(68, 21);
		this->qest->TabIndex = 17;
		this->qest->TabStop = false;
		this->qest->Value = decimal(new int[4] {640, 0, 0, 131072});
		this->qest->ValueChanged += new System::EventHandler(this, &Calculator::textField_TextChanged);
		// 
		// bppRadio
		// 
		this->bppRadio->AutoSize = true;
		this->bppRadio->Location = new System::Drawing::Point(16, 94);
		this->bppRadio->Name = "bppRadio";
		this->bppRadio->Size = new System::Drawing::Size(86, 17);
		this->bppRadio->TabIndex = 16;
		this->bppRadio->TabStop = true;
		this->bppRadio->Text = "Bits Per Pixel";
		this->bppRadio->UseVisualStyleBackColor = true;
		this->bppRadio->CheckedChanged += new System::EventHandler(this, &Calculator::calculationMode_CheckedChanged);
		// 
		// bpp
		// 
		this->bpp->DecimalPlaces = 3;
		this->bpp->Increment = decimal(new int[4] {1, 0, 0, 131072});
		this->bpp->Location = new System::Drawing::Point(19, 117);
		this->bpp->Name = "bpp";
		this->bpp->ReadOnly = true;
		this->bpp->Size = new System::Drawing::Size(68, 21);
		this->bpp->TabIndex = 16;
		this->bpp->TabStop = false;
		this->bpp->Value = decimal(new int[4] {25, 0, 0, 131072});
		this->bpp->ValueChanged += new System::EventHandler(this, &Calculator::textField_TextChanged);
		// 
		// videoSize
		// 
		this->videoSize->Location = new System::Drawing::Point(127, 48);
		this->videoSize->Name = "videoSize";
		this->videoSize->ReadOnly = true;
		this->videoSize->Size = new System::Drawing::Size(62, 21);
		this->videoSize->TabIndex = 15;
		this->videoSize->TabStop = false;
		// 
		// targetSize
		// 
		this->targetSize->setCustomSizes(new MeGUI::core::util::FileSize[0]);
		this->targetSize->Font = new System::Drawing::Font("Tahoma", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, (static_cast<unsigned char>(0)));
		this->targetSize->Location = new System::Drawing::Point(19, 180);
		this->targetSize->Margin = new System::Windows::Forms::Padding(3, 4, 3, 4);
		this->targetSize->MaximumSize = new System::Drawing::Size(1000, 29);
		this->targetSize->MinimumSize = new System::Drawing::Size(64, 29);
		this->targetSize->Name = "targetSize";
		this->targetSize->setNullString("Not calculated");
		this->targetSize->setSelectedIndex(0);
		this->targetSize->Size = new System::Drawing::Size(173, 29);
		this->targetSize->TabIndex = 18;
		this->targetSize->TabStop = false;
		this->targetSize->SelectionChanged += new MeGUI::StringChanged(this, &Calculator::targetSize_SelectionChanged);
		// 
		// projectedBitrate
		// 
		this->projectedBitrate->Increment = decimal(new int[4] {50, 0, 0, 0});
		this->projectedBitrate->Location = new System::Drawing::Point(19, 48);
		this->projectedBitrate->Maximum = decimal(new int[4] {100000, 0, 0, 0});
		this->projectedBitrate->Name = "projectedBitrate";
		this->projectedBitrate->ReadOnly = true;
		this->projectedBitrate->Size = new System::Drawing::Size(68, 21);
		this->projectedBitrate->TabIndex = 15;
		this->projectedBitrate->TabStop = false;
		this->projectedBitrate->ThousandsSeparator = true;
		this->projectedBitrate->ValueChanged += new System::EventHandler(this, &Calculator::textField_TextChanged);
		// 
		// fileSizeRadio
		// 
		this->fileSizeRadio->Checked = true;
		this->fileSizeRadio->Font = new System::Drawing::Font("Tahoma", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, (static_cast<unsigned char>(0)));
		this->fileSizeRadio->Location = new System::Drawing::Point(16, 161);
		this->fileSizeRadio->Name = "fileSizeRadio";
		this->fileSizeRadio->Size = new System::Drawing::Size(132, 20);
		this->fileSizeRadio->TabIndex = 18;
		this->fileSizeRadio->TabStop = true;
		this->fileSizeRadio->Text = "Total File Size";
		this->fileSizeRadio->CheckedChanged += new System::EventHandler(this, &Calculator::calculationMode_CheckedChanged);
		// 
		// AverageBitrateLabel
		// 
		this->AverageBitrateLabel->AutoSize = true;
		this->AverageBitrateLabel->Location = new System::Drawing::Point(87, 50);
		this->AverageBitrateLabel->Name = "AverageBitrateLabel";
		this->AverageBitrateLabel->Size = new System::Drawing::Size(33, 13);
		this->AverageBitrateLabel->TabIndex = 2;
		this->AverageBitrateLabel->Text = "kbit/s";
		// 
		// averageBitrateRadio
		// 
		this->averageBitrateRadio->AutoSize = true;
		this->averageBitrateRadio->Location = new System::Drawing::Point(16, 25);
		this->averageBitrateRadio->Name = "averageBitrateRadio";
		this->averageBitrateRadio->Size = new System::Drawing::Size(86, 17);
		this->averageBitrateRadio->TabIndex = 15;
		this->averageBitrateRadio->TabStop = true;
		this->averageBitrateRadio->Text = "Video Bitrate";
		this->averageBitrateRadio->CheckedChanged += new System::EventHandler(this, &Calculator::calculationMode_CheckedChanged);
		// 
		// cancelButton
		// 
		this->cancelButton->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right)));
		this->cancelButton->DialogResult = System::Windows::Forms::DialogResult::Cancel;
		this->cancelButton->Location = new System::Drawing::Point(503, 319);
		this->cancelButton->Name = "cancelButton";
		this->cancelButton->Size = new System::Drawing::Size(78, 23);
		this->cancelButton->TabIndex = 24;
		this->cancelButton->Text = "Cancel";
		// 
		// contextMenuStrip1
		// 
		this->contextMenuStrip1->Items->AddRange(new System::Windows::Forms::ToolStripItem[2] {this->addAudioToolStripMenuItem, this->addExtraToolStripMenuItem});
		this->contextMenuStrip1->Name = "contextMenuStrip1";
		this->contextMenuStrip1->Size = new System::Drawing::Size(132, 48);
		// 
		// addAudioToolStripMenuItem
		// 
		this->addAudioToolStripMenuItem->Name = "addAudioToolStripMenuItem";
		this->addAudioToolStripMenuItem->Size = new System::Drawing::Size(131, 22);
		this->addAudioToolStripMenuItem->Text = "Add &Audio";
		this->addAudioToolStripMenuItem->Click += new System::EventHandler(this, &Calculator::addAudioToolStripMenuItem_Click);
		// 
		// addExtraToolStripMenuItem
		// 
		this->addExtraToolStripMenuItem->Name = "addExtraToolStripMenuItem";
		this->addExtraToolStripMenuItem->Size = new System::Drawing::Size(131, 22);
		this->addExtraToolStripMenuItem->Text = "Add &Extra";
		this->addExtraToolStripMenuItem->Click += new System::EventHandler(this, &Calculator::addExtraToolStripMenuItem_Click);
		// 
		// containerGroupbox
		// 
		this->containerGroupbox->Controls->Add(this->containerFormat);
		this->containerGroupbox->Location = new System::Drawing::Point(484, 9);
		this->containerGroupbox->Name = "containerGroupbox";
		this->containerGroupbox->Size = new System::Drawing::Size(207, 66);
		this->containerGroupbox->TabIndex = 14;
		this->containerGroupbox->TabStop = false;
		this->containerGroupbox->Text = "Container";
		// 
		// audioExtraGroupbox
		// 
		this->audioExtraGroupbox->ContextMenuStrip = this->contextMenuStrip1;
		this->audioExtraGroupbox->Controls->Add(this->addAudioLink);
		this->audioExtraGroupbox->Controls->Add(this->audioExtraFlow);
		this->audioExtraGroupbox->Location = new System::Drawing::Point(8, 168);
		this->audioExtraGroupbox->Name = "audioExtraGroupbox";
		this->audioExtraGroupbox->Size = new System::Drawing::Size(470, 145);
		this->audioExtraGroupbox->TabIndex = 13;
		this->audioExtraGroupbox->TabStop = false;
		this->audioExtraGroupbox->Text = "Audio && Extra";
		// 
		// addAudioLink
		// 
		this->addAudioLink->Cursor = System::Windows::Forms::Cursors::Hand;
		this->addAudioLink->Image = (static_cast<System::Drawing::Image*>(resources->GetObject("addAudioLink.Image")));
		this->addAudioLink->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
		this->addAudioLink->Location = new System::Drawing::Point(387, 0);
		this->addAudioLink->Name = "addAudioLink";
		this->addAudioLink->Padding = new System::Windows::Forms::Padding(16, 3, 2, 3);
		this->addAudioLink->Size = new System::Drawing::Size(49, 18);
		this->addAudioLink->TabIndex = 12;
		this->addAudioLink->TabStop = true;
		this->addAudioLink->Text = "Add";
		this->addAudioLink->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
		this->addToolTip->SetToolTip(this->addAudioLink, "Audio track or extra data");
		this->addAudioLink->Click += new System::EventHandler(this, &Calculator::addAudioLink_Clicked);
		// 
		// audioExtraFlow
		// 
		this->audioExtraFlow->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) | System::Windows::Forms::AnchorStyles::Left) | System::Windows::Forms::AnchorStyles::Right)));
		this->audioExtraFlow->AutoScroll = true;
		this->audioExtraFlow->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
		this->audioExtraFlow->Location = new System::Drawing::Point(3, 18);
		this->audioExtraFlow->Name = "audioExtraFlow";
		this->audioExtraFlow->Size = new System::Drawing::Size(462, 124);
		this->audioExtraFlow->TabIndex = 13;
		this->audioExtraFlow->ControlRemoved += new System::Windows::Forms::ControlEventHandler(this, &Calculator::audio_SelectedIndexChanged);
		// 
		// addToolTip
		// 
		this->addToolTip->AutomaticDelay = 300;
		this->addToolTip->ToolTipTitle = "Add";
		// 
		// helpButton1
		// 
		this->helpButton1->Anchor = (static_cast<System::Windows::Forms::AnchorStyles*>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left)));
		this->helpButton1->setArticleName("Bitrate Calculator");
		this->helpButton1->Location = new System::Drawing::Point(22, 319);
		this->helpButton1->Name = "helpButton1";
		this->helpButton1->Size = new System::Drawing::Size(78, 23);
		this->helpButton1->TabIndex = 25;
		// 
		// Calculator
		// 
		this->AutoScaleBaseSize = new System::Drawing::Size(5, 14);
		this->CancelButton = this->cancelButton;
		this->ClientSize = new System::Drawing::Size(701, 349);
		this->Controls->Add(this->audioExtraGroupbox);
		this->Controls->Add(this->containerGroupbox);
		this->Controls->Add(this->videoGroupbox);
		this->Controls->Add(this->sizeGroupbox);
		this->Controls->Add(this->helpButton1);
		this->Controls->Add(this->cancelButton);
		this->Controls->Add(this->applyButton);
		this->Font = new System::Drawing::Font("Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, (static_cast<unsigned char>(0)));
		this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
		this->Icon = (static_cast<System::Drawing::Icon*>(resources->GetObject("$this.Icon")));
		this->MaximizeBox = false;
		this->MinimizeBox = false;
		this->Name = "Calculator";
		this->Text = "MeGUI - Bitrate Calculator";
		this->videoGroupbox->ResumeLayout(false);
		this->videoGroupbox->PerformLayout();
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->height))->EndInit();
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->width))->EndInit();
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->nbFrames))->EndInit();
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->seconds))->EndInit();
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->minutes))->EndInit();
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->hours))->EndInit();
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->complexity))->EndInit();
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->picTime))->EndInit();
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->totalSeconds))->EndInit();
		this->sizeGroupbox->ResumeLayout(false);
		this->sizeGroupbox->PerformLayout();
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->qest))->EndInit();
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->bpp))->EndInit();
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->projectedBitrate))->EndInit();
		this->contextMenuStrip1->ResumeLayout(false);
		this->containerGroupbox->ResumeLayout(false);
		this->audioExtraGroupbox->ResumeLayout(false);
		this->ResumeLayout(false);

	}

	void Calculator::InitializeInstanceFields()
	{
		updatingContainers = false;
		codecs = new CodecManager();
		isUpdating = false;
		calculating = false;
		delete components;
	}
}
