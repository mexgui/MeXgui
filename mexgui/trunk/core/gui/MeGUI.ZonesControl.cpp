#include "MeGUI.ZonesControl.h"

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

namespace MeGUI
{

	ZonesControl::ZonesControl()
	{
		InitializeInstanceFields();
		this->introEndFrame = 0;
		this->creditsStartFrame = 0;
		zones = new Zone[0];
		input = "";
		InitializeComponent();
	}

	const MeGUI::MainForm &ZonesControl::getMainForm() const
	{
		return mainForm;
	}

	void ZonesControl::setMainForm(const MeGUI::MainForm &value)
	{
		mainForm = value;
	}

	void ZonesControl::updateGUI()
	{
		UpdateGUIEvent();
	}

	void ZonesControl::zoneMode_SelectedIndexChanged(object *sender, System::EventArgs *e)
	{
		if (zoneMode->SelectedIndex == 0) // quantizer
		{
			this->modifierLabel->Text = "Quantizer";
			this->zoneModifier->Minimum = 0;
			this->zoneModifier->Maximum = 51;
			this->zoneModifier->Value = 26;
		}
		if (zoneMode->SelectedIndex == 1)
		{
			this->modifierLabel->Text = "Bitrate %";
			this->zoneModifier->Minimum = 1;
			this->zoneModifier->Maximum = 500;
			this->zoneModifier->Value = 100;
		}
	}

	void ZonesControl::removeZoneButton_Click(object *sender, System::EventArgs *e)
	{
		if (this->zoneListView->SelectedItems->Count > 0)
		{
			for (unknown::const_iterator item = zoneListView->SelectedItems.begin(); item != zoneListView->SelectedItems.end(); ++item)
			{
				zoneListView->Items->Remove(*item);
			}
			Zone newZones[zoneListView->Items->Count];
			int index = 0;
			for (unknown::const_iterator item = zoneListView->Items.begin(); item != zoneListView->Items.end(); ++item)
			{
				Zone *z = static_cast<Zone*>((*item)->Tag);
				newZones[index] = z;
				index++;
			}
			zones = newZones;
			showZones(zones);
			updateGUI();
		}
	}

	void ZonesControl::clearZonesButton_Click(object *sender, System::EventArgs *e)
	{
		this->zoneListView->Items->Clear();
		this->zones = new Zone[0];
		updateGUI();
	}

	void ZonesControl::addZoneButton_Click(object *sender, System::EventArgs *e)
	{
		if (startFrame->Text->Equals("") || endFrame->Text->Equals(""))
			MessageBox::Show("You must specify both start and end frame", "Missing input", MessageBoxButtons::OK, MessageBoxIcon::Stop);
		else
		{
			Zone *zone = new Zone();
			zone->startFrame = int::Parse(startFrame->Text);
			zone->endFrame = int::Parse(endFrame->Text);
			if (zone->endFrame <= zone->startFrame)
			{
				MessageBox::Show("The end frame must be larger than the start frame", "Invalid zone configuration", MessageBoxButtons::OK, MessageBoxIcon::Stop);
				return;
			}
			if (zoneMode->SelectedIndex == 0)
				zone->mode = Quantizer;
			else
				zone->mode = Weight;
			zone->modifier = zoneModifier->Value;
			Zone newZones[sizeof(zones) / sizeof(zones[0]) + 1];
			int index = 0;
			if (sizeof(zones) / sizeof(zones[0]) == 0) // no zones defined yet
				newZones[0] = zone;
			bool iterationAborted = false, zoneInserted = false;
			for (MeGUI::Zone::const_iterator z = zones->begin(); z != zones->end(); ++z)
			{
				if (zone->startFrame > (*z)->endFrame) // new zone starts after the current one
				{
					newZones[index] = *z;
				}
				else if (zone->endFrame < (*z)->startFrame) // new zone end before the current one
				{
					if (!zoneInserted)
					{
						newZones[index] = zone;
						zoneInserted = true;
						index++;
					}
					newZones[index] = *z;
				}
				else if ((*z)->endFrame >= zone->startFrame || ((*z)->startFrame <= zone->endFrame && (*z)->endFrame >= zone->endFrame)) // intersection
				{
					std::string errorMessage = "The new zone intersects with an existing zone:\nstart:" + (*z)->startFrame + " end: " + (*z)->endFrame;
					MessageBox::Show(errorMessage, "Invalid zone configuration", MessageBoxButtons::OK, MessageBoxIcon::Stop);
					iterationAborted = true;
					break;
				}
				index++;
			}
			if (!zoneInserted) // in this case the new zone comes after all the others
				newZones[index] = zone;
			if (!iterationAborted)
			{
				zones = newZones;
				this->showZones(zones);
			}
			updateGUI();
		}
	}

	void ZonesControl::showZones(Zone zones[])
	{
		this->zoneListView->Items->Clear();
		for (MeGUI::Zone::const_iterator z = zones->begin(); z != zones->end(); ++z)
		{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
			ListViewItem *item = new ListViewItem(new std::string[] {(*z)->startFrame->ToString(), (*z)->endFrame->ToString(), (*z)->mode->ToString(), (*z)->modifier->ToString()});
			item->Tag = *z;
			zoneListView->Items->Add(item);
		}
	}

	void ZonesControl::zoneListView_SelectedIndexChanged(object *sender, System::EventArgs *e)
	{
		if (zoneListView->SelectedIndices->Count != 0)
		{
			if (zoneListView->SelectedIndices->Count == 1)
			{
				ListViewItem *item = zoneListView->SelectedItems[0];
				Zone *z = static_cast<Zone*>(item->Tag);
				startFrame->Text = StringConverterHelper::toString(z->startFrame);
				endFrame->Text = StringConverterHelper::toString(z->endFrame);
				if (z->mode == Quantizer)
					zoneMode->SelectedIndex = 0;
				else
					zoneMode->SelectedIndex = 1;
				zoneModifier->Value = static_cast<decimal>(z->modifier);
			}
		}
	}

	void ZonesControl::updateZoneButton_Click(object *sender, System::EventArgs *e)
	{
		if (this->zoneListView->SelectedIndices->Count == 1)
		{
			ListViewItem *item = zoneListView->SelectedItems[0];
			Zone *zone = static_cast<Zone*>(item->Tag);
			if (startFrame->Text->Equals("") || endFrame->Text->Equals(""))
				MessageBox::Show("You must specify both start and end frame", "Missing input", MessageBoxButtons::OK, MessageBoxIcon::Stop);
			else
			{
				zone->startFrame = int::Parse(startFrame->Text);
				zone->endFrame = int::Parse(endFrame->Text);
				if (zone->endFrame <= zone->startFrame)
				{
					MessageBox::Show("The end frame must be larger than the start frame", "Invalid zone configuration", MessageBoxButtons::OK, MessageBoxIcon::Stop);
					return;
				}
				if (zoneMode->SelectedIndex == 0)
					zone->mode = Quantizer;
				else
					zone->mode = Weight;
				zone->modifier = zoneModifier->Value;
				zones[item->Index] = zone;
				this->showZones(zones);
				updateGUI();
			}
		}
	}

	void ZonesControl::player_ZoneSet(int start, int end)
	{
		startFrame->Text = StringConverterHelper::toString(start);
		endFrame->Text = StringConverterHelper::toString(end);
		addZoneButton_Click(0, 0);
	}

	void ZonesControl::player_Closed(object *sender, EventArgs *e)
	{
//C# TO C++ CONVERTER WARNING: C# to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
		delete player;
	}

	void ZonesControl::showVideoButton_Click(object *sender, System::EventArgs *e)
	{
		if (!this->input.Equals(""))
		{
			if (player == 0)
			{
				player = new VideoPlayer();
				bool videoLoaded = player->loadVideo(mainForm, input, ZONES, false);
				if (videoLoaded)
				{
					player->ZoneSet += new ZoneSetCallback(this, &ZonesControl::player_ZoneSet);
					player->Closed += new EventHandler(this, &ZonesControl::player_Closed);
					if (introEndFrame > 0)
						player->setIntroEnd(this->introEndFrame);
					if (creditsStartFrame > 0)
						player->setCreditsStart(this->creditsStartFrame);
					player->Show();
					player->SetScreenSize();
				}
				else
					return;
			}
			if (zoneListView->SelectedItems->Count == 1) // a zone has been selected, show that zone
			{
				Zone *zone = static_cast<Zone*>(zoneListView->SelectedItems[0]->Tag);
				player->setZoneStart(zone->startFrame);
				player->setZoneEnd(zone->endFrame);
			}
			else // no zone has been selected.. but if start and / or end frame have been configured show them in the preview
			{
				if (!startFrame->Text->Equals(""))
				{
					player->setZoneStart(int::Parse(startFrame->Text));
				}
				if (!endFrame->Text->Equals(""))
				{
					player->setZoneEnd(int::Parse(endFrame->Text));
				}
			}
		}
		else
			MessageBox::Show("Please configure video input first", "No video input found", MessageBoxButtons::OK, MessageBoxIcon::Stop);
	}

	const int &ZonesControl::getIntroEndFrame() const
	{
		return introEndFrame;
	}

	void ZonesControl::setIntroEndFrame(const int &value)
	{
		introEndFrame = value;
	}

	const int &ZonesControl::getCreditsStartFrame() const
	{
		return creditsStartFrame;
	}

	void ZonesControl::setCreditsStartFrame(const int &value)
	{
		creditsStartFrame = value;
	}

	const Zone &ZonesControl::getZones() const
	{
		return zones;
	}

	void ZonesControl::setZones(const Zone &value[])
	{
		zones = value;
		showZones(zones);
	}

	void ZonesControl::setInput(const std::string &value)
	{
		input = value;
		showVideoButton->Enabled = !value.empty();
	}

	const std::string &ZonesControl::getInput() const
	{
		return input;
	}

	void ZonesControl::closePlayer()
	{
		if (player != 0)
			player->Close();
	}

	void ZonesControl::ZonesControl_Load(object *sender, EventArgs *e)
	{
		zoneMode->SelectedIndex = 0;
	}

	void ZonesControl::Dispose(bool disposing)
	{
		if (disposing && (components != 0))
		{
			delete components;
		}
		UserControl::Dispose(disposing);
	}

	void ZonesControl::InitializeComponent()
	{
		this->zonesGroupbox = new System::Windows::Forms::GroupBox();
		this->zoneListView = new System::Windows::Forms::ListView();
		this->startFrameColumn = new System::Windows::Forms::ColumnHeader();
		this->endFrameColumn = new System::Windows::Forms::ColumnHeader();
		this->modeColumn = new System::Windows::Forms::ColumnHeader();
		this->modifierColumn = new System::Windows::Forms::ColumnHeader();
		this->tableLayoutPanel1 = new System::Windows::Forms::TableLayoutPanel();
		this->startFrame = new System::Windows::Forms::TextBox();
		this->endFrame = new System::Windows::Forms::TextBox();
		this->endFrameLabel = new System::Windows::Forms::Label();
		this->zoneLabel = new System::Windows::Forms::Label();
		this->zoneModifier = new System::Windows::Forms::NumericUpDown();
		this->zoneMode = new System::Windows::Forms::ComboBox();
		this->startFrameLabel = new System::Windows::Forms::Label();
		this->modifierLabel = new System::Windows::Forms::Label();
		this->flowLayoutPanel1 = new System::Windows::Forms::FlowLayoutPanel();
		this->showVideoButton = new System::Windows::Forms::Button();
		this->removeZoneButton = new System::Windows::Forms::Button();
		this->updateZoneButton = new System::Windows::Forms::Button();
		this->clearZonesButton = new System::Windows::Forms::Button();
		this->addZoneButton = new System::Windows::Forms::Button();
		this->zonesGroupbox->SuspendLayout();
		this->tableLayoutPanel1->SuspendLayout();
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->zoneModifier))->BeginInit();
		this->flowLayoutPanel1->SuspendLayout();
		this->SuspendLayout();
		// 
		// zonesGroupbox
		// 
		this->zonesGroupbox->Controls->Add(this->zoneListView);
		this->zonesGroupbox->Controls->Add(this->tableLayoutPanel1);
		this->zonesGroupbox->Controls->Add(this->flowLayoutPanel1);
		this->zonesGroupbox->Dock = System::Windows::Forms::DockStyle::Fill;
		this->zonesGroupbox->Location = new System::Drawing::Point(0, 0);
		this->zonesGroupbox->Name = "zonesGroupbox";
		this->zonesGroupbox->Size = new System::Drawing::Size(295, 412);
		this->zonesGroupbox->TabIndex = 2;
		this->zonesGroupbox->TabStop = false;
		this->zonesGroupbox->Text = "Zones";
		// 
		// zoneListView
		// 
		this->zoneListView->Columns->AddRange(new System::Windows::Forms::ColumnHeader[4] {this->startFrameColumn, this->endFrameColumn, this->modeColumn, this->modifierColumn});
		this->zoneListView->Dock = System::Windows::Forms::DockStyle::Fill;
		this->zoneListView->FullRowSelect = true;
		this->zoneListView->HideSelection = false;
		this->zoneListView->Location = new System::Drawing::Point(3, 16);
		this->zoneListView->Name = "zoneListView";
		this->zoneListView->Size = new System::Drawing::Size(289, 311);
		this->zoneListView->TabIndex = 0;
		this->zoneListView->UseCompatibleStateImageBehavior = false;
		this->zoneListView->View = System::Windows::Forms::View::Details;
		// 
		// startFrameColumn
		// 
		this->startFrameColumn->Text = "Start";
		// 
		// endFrameColumn
		// 
		this->endFrameColumn->Text = "End";
		// 
		// modeColumn
		// 
		this->modeColumn->Text = "Mode";
		this->modeColumn->Width = 80;
		// 
		// modifierColumn
		// 
		this->modifierColumn->Text = "Modifier";
		// 
		// tableLayoutPanel1
		// 
		this->tableLayoutPanel1->AutoSize = true;
		this->tableLayoutPanel1->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
		this->tableLayoutPanel1->ColumnCount = 4;
		this->tableLayoutPanel1->ColumnStyles->Add(new System::Windows::Forms::ColumnStyle());
		this->tableLayoutPanel1->ColumnStyles->Add(new System::Windows::Forms::ColumnStyle());
		this->tableLayoutPanel1->ColumnStyles->Add(new System::Windows::Forms::ColumnStyle());
		this->tableLayoutPanel1->ColumnStyles->Add(new System::Windows::Forms::ColumnStyle());
		this->tableLayoutPanel1->Controls->Add(this->startFrame, 1, 0);
		this->tableLayoutPanel1->Controls->Add(this->endFrame, 1, 1);
		this->tableLayoutPanel1->Controls->Add(this->endFrameLabel, 0, 1);
		this->tableLayoutPanel1->Controls->Add(this->zoneLabel, 2, 1);
		this->tableLayoutPanel1->Controls->Add(this->zoneModifier, 3, 0);
		this->tableLayoutPanel1->Controls->Add(this->zoneMode, 3, 1);
		this->tableLayoutPanel1->Controls->Add(this->startFrameLabel, 0, 0);
		this->tableLayoutPanel1->Controls->Add(this->modifierLabel, 2, 0);
		this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Bottom;
		this->tableLayoutPanel1->Location = new System::Drawing::Point(3, 327);
		this->tableLayoutPanel1->Name = "tableLayoutPanel1";
		this->tableLayoutPanel1->RowCount = 2;
		this->tableLayoutPanel1->RowStyles->Add(new System::Windows::Forms::RowStyle());
		this->tableLayoutPanel1->RowStyles->Add(new System::Windows::Forms::RowStyle());
		this->tableLayoutPanel1->Size = new System::Drawing::Size(289, 53);
		this->tableLayoutPanel1->TabIndex = 10;
		// 
		// startFrame
		// 
		this->startFrame->Location = new System::Drawing::Point(73, 3);
		this->startFrame->Name = "startFrame";
		this->startFrame->Size = new System::Drawing::Size(48, 20);
		this->startFrame->TabIndex = 1;
		// 
		// endFrame
		// 
		this->endFrame->Location = new System::Drawing::Point(73, 29);
		this->endFrame->Name = "endFrame";
		this->endFrame->Size = new System::Drawing::Size(48, 20);
		this->endFrame->TabIndex = 2;
		// 
		// endFrameLabel
		// 
		this->endFrameLabel->Dock = System::Windows::Forms::DockStyle::Fill;
		this->endFrameLabel->Location = new System::Drawing::Point(3, 26);
		this->endFrameLabel->Name = "endFrameLabel";
		this->endFrameLabel->Size = new System::Drawing::Size(64, 27);
		this->endFrameLabel->TabIndex = 2;
		this->endFrameLabel->Text = "End Frame";
		this->endFrameLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
		// 
		// zoneLabel
		// 
		this->zoneLabel->Dock = System::Windows::Forms::DockStyle::Fill;
		this->zoneLabel->Location = new System::Drawing::Point(127, 26);
		this->zoneLabel->Name = "zoneLabel";
		this->zoneLabel->Size = new System::Drawing::Size(56, 27);
		this->zoneLabel->TabIndex = 5;
		this->zoneLabel->Text = "Mode";
		this->zoneLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
		// 
		// zoneModifier
		// 
		this->zoneModifier->Dock = System::Windows::Forms::DockStyle::Fill;
		this->zoneModifier->Location = new System::Drawing::Point(189, 3);
		this->zoneModifier->Maximum = decimal(new int[4] {51, 0, 0, 0});
		this->zoneModifier->Name = "zoneModifier";
		this->zoneModifier->Size = new System::Drawing::Size(97, 20);
		this->zoneModifier->TabIndex = 3;
		this->zoneModifier->Value = decimal(new int[4] {26, 0, 0, 0});
		// 
		// zoneMode
		// 
		this->zoneMode->Dock = System::Windows::Forms::DockStyle::Fill;
		this->zoneMode->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->zoneMode->Items->AddRange(new object[2] {"Quantizer", "Weight"});
		this->zoneMode->Location = new System::Drawing::Point(189, 29);
		this->zoneMode->Name = "zoneMode";
		this->zoneMode->Size = new System::Drawing::Size(97, 21);
		this->zoneMode->TabIndex = 4;
		this->zoneMode->SelectedIndexChanged += new System::EventHandler(this, &ZonesControl::zoneMode_SelectedIndexChanged);
		// 
		// startFrameLabel
		// 
		this->startFrameLabel->Dock = System::Windows::Forms::DockStyle::Fill;
		this->startFrameLabel->Location = new System::Drawing::Point(3, 0);
		this->startFrameLabel->Name = "startFrameLabel";
		this->startFrameLabel->Size = new System::Drawing::Size(64, 26);
		this->startFrameLabel->TabIndex = 1;
		this->startFrameLabel->Text = "Start Frame";
		this->startFrameLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
		// 
		// modifierLabel
		// 
		this->modifierLabel->Dock = System::Windows::Forms::DockStyle::Fill;
		this->modifierLabel->Location = new System::Drawing::Point(127, 0);
		this->modifierLabel->Name = "modifierLabel";
		this->modifierLabel->Size = new System::Drawing::Size(56, 26);
		this->modifierLabel->TabIndex = 6;
		this->modifierLabel->Text = "Quantizer";
		this->modifierLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
		// 
		// flowLayoutPanel1
		// 
		this->flowLayoutPanel1->AutoSize = true;
		this->flowLayoutPanel1->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
		this->flowLayoutPanel1->Controls->Add(this->showVideoButton);
		this->flowLayoutPanel1->Controls->Add(this->removeZoneButton);
		this->flowLayoutPanel1->Controls->Add(this->updateZoneButton);
		this->flowLayoutPanel1->Controls->Add(this->clearZonesButton);
		this->flowLayoutPanel1->Controls->Add(this->addZoneButton);
		this->flowLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Bottom;
		this->flowLayoutPanel1->Location = new System::Drawing::Point(3, 380);
		this->flowLayoutPanel1->Name = "flowLayoutPanel1";
		this->flowLayoutPanel1->Size = new System::Drawing::Size(289, 29);
		this->flowLayoutPanel1->TabIndex = 11;
		// 
		// showVideoButton
		// 
		this->showVideoButton->AutoSize = true;
		this->showVideoButton->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
		this->showVideoButton->Enabled = false;
		this->showVideoButton->Location = new System::Drawing::Point(3, 3);
		this->showVideoButton->Name = "showVideoButton";
		this->showVideoButton->Size = new System::Drawing::Size(55, 23);
		this->showVideoButton->TabIndex = 9;
		this->showVideoButton->Text = "Preview";
		this->showVideoButton->Click += new System::EventHandler(this, &ZonesControl::showVideoButton_Click);
		// 
		// removeZoneButton
		// 
		this->removeZoneButton->AutoSize = true;
		this->removeZoneButton->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
		this->removeZoneButton->Location = new System::Drawing::Point(64, 3);
		this->removeZoneButton->Name = "removeZoneButton";
		this->removeZoneButton->Size = new System::Drawing::Size(57, 23);
		this->removeZoneButton->TabIndex = 6;
		this->removeZoneButton->Text = "Remove";
		this->removeZoneButton->Click += new System::EventHandler(this, &ZonesControl::removeZoneButton_Click);
		// 
		// updateZoneButton
		// 
		this->updateZoneButton->AutoSize = true;
		this->updateZoneButton->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
		this->updateZoneButton->Location = new System::Drawing::Point(127, 3);
		this->updateZoneButton->Name = "updateZoneButton";
		this->updateZoneButton->Size = new System::Drawing::Size(52, 23);
		this->updateZoneButton->TabIndex = 9;
		this->updateZoneButton->Text = "Update";
		this->updateZoneButton->Click += new System::EventHandler(this, &ZonesControl::updateZoneButton_Click);
		// 
		// clearZonesButton
		// 
		this->clearZonesButton->AutoSize = true;
		this->clearZonesButton->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
		this->clearZonesButton->Location = new System::Drawing::Point(185, 3);
		this->clearZonesButton->Name = "clearZonesButton";
		this->clearZonesButton->Size = new System::Drawing::Size(41, 23);
		this->clearZonesButton->TabIndex = 5;
		this->clearZonesButton->Text = "Clear";
		this->clearZonesButton->Click += new System::EventHandler(this, &ZonesControl::clearZonesButton_Click);
		// 
		// addZoneButton
		// 
		this->addZoneButton->AutoSize = true;
		this->addZoneButton->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
		this->addZoneButton->Location = new System::Drawing::Point(232, 3);
		this->addZoneButton->Name = "addZoneButton";
		this->addZoneButton->Size = new System::Drawing::Size(36, 23);
		this->addZoneButton->TabIndex = 7;
		this->addZoneButton->Text = "Add";
		this->addZoneButton->Click += new System::EventHandler(this, &ZonesControl::addZoneButton_Click);
		// 
		// ZonesControl
		// 
		this->AutoScaleDimensions = new System::Drawing::SizeF(6, 13);
		this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		this->Controls->Add(this->zonesGroupbox);
		this->Name = "ZonesControl";
		this->Size = new System::Drawing::Size(295, 412);
		this->Load += new System::EventHandler(this, &ZonesControl::ZonesControl_Load);
		this->zonesGroupbox->ResumeLayout(false);
		this->zonesGroupbox->PerformLayout();
		this->tableLayoutPanel1->ResumeLayout(false);
		this->tableLayoutPanel1->PerformLayout();
		(static_cast<System::ComponentModel::ISupportInitialize*>(this->zoneModifier))->EndInit();
		this->flowLayoutPanel1->ResumeLayout(false);
		this->flowLayoutPanel1->PerformLayout();
		this->ResumeLayout(false);

	}

	void ZonesControl::InitializeInstanceFields()
	{
		delete components;
	}
}
