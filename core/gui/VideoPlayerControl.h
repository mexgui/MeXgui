#pragma once

#include "core/util/LogItem.h"
#include "VideoPlayer.h"
#include "MeGUI.MainForm.h"
#include "core/plugins/interfaces/IMediaFile.h"
#include "packages/reader/video/VideoReader.h"
#include <stdexcept>

// ****************************************************************************
// 
// Copyright (C) 2005-2012 Doom9 & al
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






//using namespace System::Threading;



//using System::Threading::Timer;

namespace MeGUI
{
	namespace core
	{
		namespace gui
		{
			class VideoPlayerControl : public UserControl
			{
				public:
				~VideoPlayerControl()
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
				VideoPlayerControl();

				//ensures that UnloadVideo only returns if the reader is not used by other threads any more
			private:
				ReaderWriterLock *const readerWriterLock;

//C# TO C++ CONVERTER TODO TASK: There is no direct equivalent to .NET events in native C++:
//				public event EventHandler PositionChanged;
			public:
				void OnPositionChanged();
			private:
				object *positionLock;

				bool OffsetPosition(int offset, bool update);

			public:
				bool OffsetPosition(int offset);

			private:
				bool setPositionInternal(int value);

			public:
				void InvokeOnPositionChanged();

				void UpdateVideo();

				/// <summary>
				/// Resizes the video frame
				/// http://www.peterprovost.org/archive/2003/05/29/516.aspx
				/// </summary>
				/// <param name="b"></param>
				/// <param name="nWidth"></param>
				/// <param name="nHeight"></param>
				/// <returns>A resized bitQMap (needs disposal)</returns>
			private:
				BitQMap *resizeBitQMap(BitQMap *b, int nWidth, int nHeight);

				//Is no done by resize BitQMap
				///// <summary>
				///// crops the image given as a reference by the values that were previously transmitted
				///// </summary>
				///// <param name="b">the image to where the cropping has to be applied</param>
				//private unsafe void cropImage(BitQMap b)
				//{
				//    BitQMapData image = b.LockBits(new Rectangle(0, 0, b.Width, b.Height), ImageLockMode.ReadWrite, PixelFormat.Format24bppRgb);
				//    byte* pointer = (byte*)image.Scan0.ToPointer();
				//    byte* pixel;
				//    int stride = image.Stride;
				//    byte white = (byte)Color.White.R;

				//    pixel = pointer;
				//    int width = b.Width;
				//    int height = b.Height;
				//    int width3 = 3 * width;
				//    int left3 = 3 * cropMargin.Left;
				//    int right3 = 3 * cropMargin.Right;

				//    int lineGap = stride - width3;
				//    int centerJump = width3 - left3 - right3;
				//    for (int j = 0; j < cropMargin.Top; j++)
				//    {
				//        for (int i = 0; i < width3; i++)
				//        {
				//            *pixel = white;
				//            pixel++;
				//        }
				//        pixel += lineGap;
				//    }
				//    int heightb = height - cropMargin.Bottom;
				//    for (int j = cropMargin.Top; j < heightb; j++)
				//    {
				//        for (int i = 0; i < left3; i++)
				//        {
				//            *pixel = white;
				//            pixel++;
				//        }
				//        pixel += centerJump;
				//        for (int i = 0; i < right3; i++)
				//        {
				//            *pixel = white;
				//            pixel++;
				//        }
				//        pixel += lineGap;
				//    }
				//    for (int j = b.Height - cropMargin.Bottom; j < height; j++)
				//    {
				//        for (int i = 0; i < width3; i++)
				//        {
				//            *pixel = white;
				//            pixel++;
				//        }
				//        pixel += lineGap;
				//    }
				//    b.UnlockBits(image);
				//}

				//asynchronous Timer to update video in fixed interval
				Timer *const playTimer;

				/// <summary>
				/// Is Invoked by playTimer to render the next frame for the video
				/// It will trigger the playThread to render the next frame.
				/// This solution is more complex than a simple Thread.Sleep, but
				/// has the advantage that the playback will be smoother if the frames
				/// take long to render.
				/// </summary>
				void playNextFrame(object *state);

				//is set by the timer to indicate that the position must be advanced in addition to the rendering.
				//if the position would be incremented directly in playNextFrame, slow computers would drop frames.
				//with this method the computer will always display every frame
				AutoResetEvent *const nextFrameEvent;

				//is set to trigger the rendering of the current frame
				AutoResetEvent *const renderEvent;

				void renderThreadLoop();

				BitQMap *getFrame(int pos);

				bool isPlaying;

				/// <summary>
				/// Start the playing of the video
				/// </summary>
			public:
				void Play();

				/// <summary>
				/// Stops the playing of the video
				/// </summary>
				void Stop();

				void LoadVideo(IVideoReader *reader);

				void LoadVideo(IVideoReader *reader, double fps);

				void LoadVideo(IVideoReader *reader, double fps, int startPosition);
				void UnloadVideo();


			private:
				void VideoPlayerControl_Resize(QObject *sender, QEvent *e);
				void VideoPlayerControl_Load(QObject *sender, QEvent *e);

				int position;
			public:
				const int &getPosition() const;
				void setPosition(const int &value);

			private:
				IVideoReader *videoReader;
			public:
				const IVideoReader &getVideoReader() const;

			private:
				double framerate;
			public:
				const double &getFramerate() const;
				void setFramerate(const double &value);

				const int &getFrameCount() const;

			private:
				Padding *cropMargin;
			public:
				const Padding &getCropMargin() const;
				void setCropMargin(const Padding &value);

			private:
				bool displayActualFramerate;
				//if set the actual framerate of the video playback will be displayed
				//in the top left corner of the video frame
			public:
				const bool &getDisplayActualFramerate() const;
				void setDisplayActualFramerate(const bool &value);

			private:
				bool ensureCorrectPlaybackSpeed;
				//if set frames will be dropped to ensure a more correct playing speed
			public:
				const bool &getEnsureCorrectPlaybackSpeed() const;
				void setEnsureCorrectPlaybackSpeed(const bool &value);

			private:
				double speedUp;
				//Set this to speed up or slow down the playback
			public:
				const double &getSpeedUp() const;
				void setSpeedUp(const double &value);


			private:
				bool initalized;
				Thread *renderThread;

				double actualFramerate;
			public:
				const double &getActualFramerate() const;

				/// <summary> 
				/// Release Ressources.
				/// </summary>
				/// <param name="disposing">True, if managed ressources should be released; otherwise false.</param>
			private:
				void Dispose(bool disposing);



				/// <summary> 
				/// Required designer variable.
				/// </summary>
				System::ComponentModel::IContainer *components;


				/// <summary> 
				/// Required for windows forms designer
				/// Do not change manually.
				/// </summary>
				void InitializeComponent();


				System::Windows::Forms::PictureBox *videoPreview;

			private:
				void InitializeInstanceFields();
			};
		}
	}
}
