MeXgui development branch
======

This branch is currently under development files. To be commit use Fork and make your own fork then fork the code and then make pull request. All pull request shall be merged to this branch.

Developer enviroment
======

Under windows suggested is to download QT5 sdk then QtCreator source and compile the the Creator with Qt5 sdk command line. Browse to QtCreator source folder and type: 
```
qmake -r
mingw32-make -j4 -k
mingw32-make install INSTALL_PATH="C:\Qt\5.2.1\tools\QtCreator-Mingw"
```

Download atleast FFMPEG DEV and SHARED from http://ffmpeg.zeranoe.com/builds/

QScintilla compile in both platforms: browse source folder and qsciscintilla folder and type:

```
qmake && mingw32-make -j4 && mingw32-make install
```

Then browse to designer qt4/5 plugin folder and do command:
```
qmake && mingw32-make -j4 && mingw32-make install prefix="C:\Qt\5.2.1\tools\QtCreator-mingw"
```
In linux you do not need to spesify the prefix folder. Qt Creator is build with gnu in linux and comes with the sdk in right path already. 

The Plugin is needed to build with same compiler than Creator is build with in able to make it work. In Windows you need the Qscintilla2.dll in Creator bin directory or system32 so that the plugin can work with the qt creator.

Under linux please install Qt5-sdk and ffmpeg that has avisynth. 

DONATE
======

If you like the idea of having atlast native avisynth encoder in youre system the consider to support by donation.

3% of your donation goes to benefit aid to some part of world.

<a href='https://pledgie.com/campaigns/22683'><img alt='Click here to lend your support to: MeXgui -Croos system MeXgui port and make a donation at pledgie.com !' src='https://pledgie.com/campaigns/22683.png?skin_name=chrome' border='0' ></a>
