MeXgui development branch
======

This branch is currently under development files. To be commit use Fork and make your own fork then fork the code and then make pull request. All pull request shall be merged to this branch.

Developer enviroment
======

Under windows suggested is to download QT5 sdk then QtCreator source and combile the the Creator with Qt5 sdk mingw32-make command line. You need to make same steps with with FFMPEG libs and QScintilla. Please use the default mingw32-make install and it shall install the libs to QT5 sdk include and lib folders. For FFMPEG there is available all ready buils libs availbale. The must is have avisynth support enabled. 

Under linux please install Qt5-sdk and ffmpeg that has avisynth included and compile QScintilla source. 

QScintilla compile in both platforms use qmake -r && make -j4 && make install. The -j4 means 4 threads to make combile time faster. In windows you will need MINGW package installed with devel packages. This will also install qt creator qscintilla plugin. In windows you may want to use "make install prefix=c:\Qt\*\tools\QtCreator-mingw" because then it is installed to the right Qt Creator folder. The Plugin is needed to build with same compiler than Creator is build with.

DONATE
======

If you like the idea of having atlast native avisynth encoder in youre system the consider to support by donation.

3% of your donation goes to benefit aid to some part of world.

<a href='https://pledgie.com/campaigns/22683'><img alt='Click here to lend your support to: MeXgui -Croos system MeXgui port and make a donation at pledgie.com !' src='https://pledgie.com/campaigns/22683.png?skin_name=chrome' border='0' ></a>
