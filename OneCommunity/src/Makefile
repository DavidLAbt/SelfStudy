


# set the dependence of lib


# gstreamer
GST_HEADERS=-I/Library/Frameworks/GStreamer.framework/Versions/1.0/Headers/
GST_LIBS=-L../libs/gstreamer/mac  -lgstreamer-1.0 -lglib-2.0 -lgobject-2.0 -lgstbase-1.0 -lgstvideo-1.0

GST_CPPFLAGS=$(GST_HEADERS)
GST_LDFLGS=$(GST_LIBS)


# wxwidgets
WX_DIR=../libs/wx


#wxWdigets ++ compile flags
WX_HEADERS=-I$(WX_DIR)/osx_cocoa-unicode-static-3.0 -I$(WX_DIR)/include 
WX_COMPILE= -D__WXOSX_COCOA__  -D_FILE_OFFSET_BITS=64 -Wundef -Wunused-parameter -Wno-ctor-dtor-privacy -Woverloaded-virtual -Wno-deprecated-declarations -stdlib=libc++ -DWX_PRECOMP -O2 -fno-strict-aliasing -std=c++0x -stdlib=libc++ -fno-common 

#wxWdigets C++ link flags
WX_LIBS=-L$(WX_DIR)/mac
# QTKit required by mediactrl
WX_DEP_FRAMEWORKS=-framework IOKit -framework Carbon -framework Cocoa -framework AudioToolbox -framework System -framework OpenGL  -framework QTKit -framework WebKit 
WX_DEP_LIBS=-lwx_osx_cocoau-3.0 -lwxscintilla-3.0 -lwxtiff-3.0 -lwxjpeg-3.0 -lwxpng-3.0 -lwxregexu-3.0 -lz -lpthread -liconv -lc++ -llzma  -lexpat

WX_CPPFLAGS=$(WX_HEADERS) $(WX_COMPILE)
WX_LDFLGS=$(WX_LIBS) $(WX_DEP_FRAMEWORKS) $(WX_DEP_LIBS)

# compiler setting
CPP=g++
#
I_SYSROOT=-isysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.9.sdk
CPPFLAGS=-c -Wall $(I_SYSROOT) $(WX_CPPFLAGS) $(GST_CPPFLAGS)
LDFLAGS=$(I_SYSROOT) $(WX_LDFLGS) $(GST_LDFLGS)


# targets setting
SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=adjustable


	
	
#create app
APP_PATH=./bin/$(EXECUTABLE).app

print:
	@echo $(SOURCES)
	@echo $(OBJECTS)
	@echo $(APP_PATH)/Contents/MacOS/$(EXECUTABLE)
	@echo "./$(EXECUTABLE)" "$(APP_PATH)/Contents/MacOS/$(EXECUTABLE)"
	@echo "../res/wxmac.icns" "$(APP_PATH)/Contents/Resources/wxmac.icns"


all: $(SOURCES) $(EXECUTABLE) 
	SetFile -t APPL $(EXECUTABLE)
	mkdir -p $(APP_PATH)/Contents
	mkdir -p $(APP_PATH)/Contents/MacOS
	mkdir -p $(APP_PATH)/Contents/Resources
	mkdir -p $(APP_PATH)/Contents/Resources/videos
	cp -f ./$(EXECUTABLE) $(APP_PATH)/Contents/MacOS/$(EXECUTABLE)
	cp -f ../res/wxmac.icns $(APP_PATH)/Contents/Resources/wxmac.icns
	cp -R ../res/videos/* $(APP_PATH)/Contents/Resources/videos
	
$(EXECUTABLE): $(OBJECTS) 
	$(CPP) $(LDFLAGS) $(OBJECTS) -o $@


.cpp.o: 
	$(CPP) $(CPPFLAGS) $< -o $@
	
clean:
	rm -f ./*.o
	rm -f $(EXECUTABLE)
	rm -r $(APP_PATH)
	
%: 
	$(CPP) $(LDFLAGS)  $*.o -o $*