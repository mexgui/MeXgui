#include "MeGUI.core.gui.VideoPlayerControl.h"






//using namespace System::Threading;



//using System::Threading::Timer;
namespace MeGUI
{
	namespace core
	{
		namespace gui
		{

			VideoPlayerControl::VideoPlayerControl() : playTimer(new Timer(playNextFrame)) : readerWriterLock(new ReaderWriterLock()), nextFrameEvent(new AutoResetEvent(false)), renderEvent(new AutoResetEvent(false))
			{
				InitializeInstanceFields();
				InitializeComponent();
			}

			void VideoPlayerControl::OnPositionChanged()
			{
				PositionChanged(this, new QEvent());
			}

			bool VideoPlayerControl::OffsetPosition(int offset, bool update)
			{
				bool success;
				//ensures that the correct offset is always added even
				//if multiple threads are calling this methods (e.g. playback)
//C# TO C++ CONVERTER TODO TASK: There is no built-in support for multithreading in native C++:
				lock (positionLock)
				{
					//Position property ensures that position does not get out of bounds
					success = setPositionInternal(position + offset);
				}

				InvokeOnPositionChanged();

				if (update)
					UpdateVideo();

				return success;
			}

			bool VideoPlayerControl::OffsetPosition(int offset)
			{
				return OffsetPosition(offset, true);
			}

			bool VideoPlayerControl::setPositionInternal(int value)
			{
				int max = getFrameCount() - 1;

				//Prevent setting the position out of range
				if (value < 0)
					value = 0;
				else if (value > max)
					value = max;

				//position unchanged
				if (position == value)
					return false;

				position = value;

				return true;
			}

			void VideoPlayerControl::InvokeOnPositionChanged()
			{
				//HACK: Invoke does not work before handle is created
				if (initalized)
					Invoke(new SimpleDelegate(OnPositionChanged));
				else
					OnPositionChanged();
			}

			void VideoPlayerControl::UpdateVideo()
			{
				renderEvent->Set();
			}

			BitQMap *VideoPlayerControl::resizeBitQMap(BitQMap *b, int nWidth, int nHeight)
			{
				float factorX = nWidth / static_cast<float>(b->Width);
				float factorY = nHeight / static_cast<float>(b->Height);

				//calculate source and destination rectangles with applied cropping values
				RectangleF *src = new RectangleF(cropMargin->Left, cropMargin->Top, b->Width - cropMargin->Horizontal, b->Height - cropMargin->Vertical);
				RectangleF *dst = new RectangleF(cropMargin->Left * factorX, cropMargin->Top * factorY, (b->Width - cropMargin->Horizontal) * factorX, (b->Height - cropMargin->Vertical) * factorY);

				BitQMap *result = new BitQMap(nWidth, nHeight);
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//				using (Graphics g = Graphics.FromImage(result))
				Graphics *g = Graphics::FromImage(result);
				try
				{
					//apply cropping
					Region *reg = new Region();
					reg->MakeInfinite();
					reg->Exclude(dst);
					g->FillRegion(Brushes::White, reg);

					g->InterpolationMode = System::Drawing::Drawing2D::InterpolationMode::Bilinear;
					//                g.DrawImage(b, 0, 0, nWidth, nHeight);
					g->DrawImage(b, dst, src, GraphicsUnit::Pixel);

					if (getDisplayActualFramerate())
					{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
						g->DrawString(getActualFramerate().ToString("0.00 fps"), Font, Brushes::Green, 0, 0);
					}
				}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
				finally
				{
					if (g != 0)
						g.Dispose();
				}
				return result;
			}

			void VideoPlayerControl::playNextFrame(object *state)
			{
				try
				{
					//playback speed is correct, but frames may be dropped if computer is too slow
					if (getEnsureCorrectPlaybackSpeed())
					{
						if (!OffsetPosition(1, false))
							Stop();
						else
							InvokeOnPositionChanged();

						UpdateVideo();
					}
					//no frames will be dropped, but the playback speed might be slower than realtime
					else
					{
						nextFrameEvent->Set();
					}

					//Console.WriteLine("Frame {0} requested", Position);
				}
				catch (std::exception &e)
				{
					MeGUI::core::util::LogItem *_oLog = MainForm::Instance->getLog()->Info("Error");
					_oLog->LogValue("playNextFrame", e, MeGUI::core::util::Error);
				}
			}

			void VideoPlayerControl::renderThreadLoop()
			{
				int framesPlayed = 0;
				DateTime start = DateTime::Now;
				do
				{
					DateTime end = DateTime::Now;
					TimeSpan *renderTime = end - start;

					//do not update current framerate more often than 200ms
					if (renderTime->Milliseconds > 200 && framesPlayed > 0)
					{
						//average results
						actualFramerate = 0.9 * actualFramerate + 0.1 * (TimeSpan::TicksPerSecond / static_cast<double>(renderTime->Ticks)) * framesPlayed;
						start = end;
						framesPlayed = 0;
					}

					if (WaitHandle::WaitAny(new WaitHandle[] {nextFrameEvent, renderEvent}) == 0)
					{
						if (!OffsetPosition(1, false))
							Stop();
						else
							InvokeOnPositionChanged();
					}

					BitQMap *finalBitQMap;
					int pos = position;

					try
					{
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//						using (BitQMap b = getFrame(pos))
						BitQMap *b = getFrame(pos);
						try
						{
							if (b == 0)
								continue;

							//if (cropMargin != Padding.Empty) // only crop when necessary            
							//    cropImage(b);

							finalBitQMap = resizeBitQMap(b, videoPreview->Width, videoPreview->Height);
						}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
						finally
						{
							if (b != 0)
								b.Dispose();
						}
					}
					catch (std::exception &ex)
					{
						MessageBox::Show(ex.what(), "Video Player Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
						if (MainForm::Instance->getSettings()->getOpenAVSInThreadDuringSession())
						{
							   MainForm::Instance->getSettings()->setOpenAVSInThreadDuringSession(false);
							MessageBox::Show("As a result during this session the option \"Improved AVS opening\" in the settings is now disabled. Please disable it there completly if necessary.", "Video Player Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
						}
						break;
					}

//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//					using(videoPreview.Image)
					try
					{
						//do the actual rendering on GUI thread
//C# TO C++ CONVERTER TODO TASK: Lambda expressions and anonymous methods are not converted to native C++ unless the option to convert to C++0x lambdas is selected:
						Invoke((SimpleDelegate)(delegate
							videoPreview->Image = finalBitQMap;
					}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
					finally
					{
						if (videoPreview.Image != 0)
							videoPreview.Image.Dispose();
					}
					   ));
				}
					//Console.WriteLine("Frame {0} updated", pos);

					//needed for fps display
					framesPlayed++;
			} while (!IsDisposed);
		}

			BitQMap *VideoPlayerControl::getFrame(int pos)
			{
				readerWriterLock->AcquireReaderLock(Timeout::Infinite);
				try
				{
					IVideoReader *reader = getVideoReader();
					if (reader == 0)
						return 0;
					return reader->ReadFrameBitQMap(pos);
				}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
				finally
				{
					readerWriterLock->ReleaseReaderLock();
				}
			}

			void VideoPlayerControl::Play()
			{
				if (videoReader == 0)
					throw new InvalidOperationException("Video must be loaded before playback can be started");

				playTimer->Change(0, static_cast<int>(1000 / (getFramerate() * getSpeedUp())));
				isPlaying = true;

				actualFramerate = getFramerate()*getSpeedUp();
			}

			void VideoPlayerControl::Stop()
			{
				playTimer->Change(Timeout::Infinite, Timeout::Infinite);
				nextFrameEvent->Reset();
				renderEvent->Reset();
				isPlaying = false;

				actualFramerate = 0;
			}

			void VideoPlayerControl::LoadVideo(IVideoReader *reader)
			{
				LoadVideo(reader, 25, 0);
			}

			void VideoPlayerControl::LoadVideo(IVideoReader *reader, double fps)
			{
				LoadVideo(reader, fps, 0);
			}

			void VideoPlayerControl::LoadVideo(IVideoReader *reader, double fps, int startPosition)
			{
				UnloadVideo();

				//just to be sure... shouldn't be necessary because after UnloadVideo
				//videoReader will be null
				readerWriterLock->AcquireWriterLock(Timeout::Infinite);
				try
				{
					videoReader = reader;
				}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
				finally
				{
					readerWriterLock->ReleaseWriterLock();
				}

				setFramerate(fps);
				setPosition(startPosition);
			}

			void VideoPlayerControl::UnloadVideo()
			{
				Stop();
				//ensures that no other thread uses the reader at the moment,
				//so that the video file can be safely disposed when the method returns
				readerWriterLock->AcquireWriterLock(Timeout::Infinite);
				try
				{
//C# TO C++ CONVERTER WARNING: C# to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
					delete videoReader;
				}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
				finally
				{
					readerWriterLock->ReleaseWriterLock();
				}
				position = 0;
			}

			void VideoPlayerControl::VideoPlayerControl_Resize(QObject *sender, QEvent *e)
			{
				UpdateVideo();
			}

			void VideoPlayerControl::VideoPlayerControl_Load(QObject *sender, QEvent *e)
			{
				initalized = true;

				//Thread for video playing
				renderThread = new Thread(renderThreadLoop);
				renderThread->Name = "Render Thread";
				renderThread->Start();
			}

			const int &VideoPlayerControl::getPosition() const
			{
				return position;
			}

			void VideoPlayerControl::setPosition(const int &value)
			{
				if (setPositionInternal(value))
				{
					UpdateVideo();
					InvokeOnPositionChanged();
				}
			}

			const MeGUI::IVideoReader &VideoPlayerControl::getVideoReader() const
			{
				return videoReader;
			}

			const double &VideoPlayerControl::getFramerate() const
			{
				return framerate;
			}

			void VideoPlayerControl::setFramerate(const double &value)
			{
				if (value <= 0)
					throw new ArgumentOutOfRangeException("value", "FPS cannot be zero or lower");
				framerate = value;

				//Restart video to adjust playback speed for new framerate value
				if (isPlaying)
					Play();
			}

			const int &VideoPlayerControl::getFrameCount() const
			{
				readerWriterLock->AcquireReaderLock(Timeout::Infinite);
				try
				{
					IVideoReader *reader = getVideoReader();

					if (reader == 0)
						return 0;

					return reader->getFrameCount();
				}
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
				finally
				{
					readerWriterLock->ReleaseReaderLock();
				}
			}

			const Padding &VideoPlayerControl::getCropMargin() const
			{
				return cropMargin;
			}

			void VideoPlayerControl::setCropMargin(const Padding &value)
			{
				cropMargin = value;
				UpdateVideo();
			}

			const bool &VideoPlayerControl::getDisplayActualFramerate() const
			{
				return displayActualFramerate;
			}

			void VideoPlayerControl::setDisplayActualFramerate(const bool &value)
			{
				displayActualFramerate = value;
				UpdateVideo();
			}

			const bool &VideoPlayerControl::getEnsureCorrectPlaybackSpeed() const
			{
				return ensureCorrectPlaybackSpeed;
			}

			void VideoPlayerControl::setEnsureCorrectPlaybackSpeed(const bool &value)
			{
				ensureCorrectPlaybackSpeed = value;
			}

			const double &VideoPlayerControl::getSpeedUp() const
			{
				return speedUp;
			}

			void VideoPlayerControl::setSpeedUp(const double &value)
			{
				speedUp = value;

				//Restart video to adjust playback speed for new speed up value
				if (isPlaying)
					Play();
			}

			const double &VideoPlayerControl::getActualFramerate() const
			{
				return actualFramerate;
			}

			void VideoPlayerControl::Dispose(bool disposing)
			{
				Stop();
				delete playTimer;
				if (renderThread != 0)
				{
					renderThread->Abort();
					renderThread->Join();
				}

				if (videoPreview->Image != 0)
					delete videoPreview->Image; // get rid of bitQMap

				if (disposing && (components != 0))
				{
					delete components;
				}
				UserControl::Dispose(disposing);
			}

			void VideoPlayerControl::InitializeComponent()
			{
				this->videoPreview = new System::Windows::Forms::PictureBox();
				(static_cast<System::ComponentModel::ISupportInitialize*>(this->videoPreview))->BeginInit();
				this->SuspendLayout();
				// 
				// videoPreview
				// 
				this->videoPreview->Dock = System::Windows::Forms::DockStyle::Fill;
				this->videoPreview->Location = new System::Drawing::Point(0, 0);
				this->videoPreview->Name = "videoPreview";
				this->videoPreview->Size = new System::Drawing::Size(150, 150);
				this->videoPreview->TabIndex = 0;
				this->videoPreview->TabStop = false;
				// 
				// VideoPlayerControl
				// 
				this->AutoScaleDimensions = new System::Drawing::SizeF(6, 13);
				this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				this->Controls->Add(this->videoPreview);
				this->Name = "VideoPlayerControl";
				this->Load += new System::EventHandler(this, &VideoPlayerControl::VideoPlayerControl_Load);
				this->Resize += new System::EventHandler(this, &VideoPlayerControl::VideoPlayerControl_Resize);
				(static_cast<System::ComponentModel::ISupportInitialize*>(this->videoPreview))->EndInit();
				this->ResumeLayout(false);

			}

			void VideoPlayerControl::InitializeInstanceFields()
			{
				positionLock = new object();
				framerate = 25;
				speedUp = 1;
				delete components;
			}
	}
}
}
