 TEMPLATE = app

 QT += multimedia

 HEADERS = \
     videoplayer.h \
     videowidget.h \
     videowidgetsurface.h

 SOURCES = \
     main.cpp \
     videoplayer.cpp \
     videowidget.cpp \
     videowidgetsurface.cpp

 # install
 target.path = $$[QT_INSTALL_EXAMPLES]/multimedia/videowidget
 sources.files = $$SOURCES $$HEADERS $$FORMS $$RESOURCES *.pro *.png images
 sources.path = $$[QT_INSTALL_EXAMPLES]/multimedia/videowidget
 INSTALLS += target sources

