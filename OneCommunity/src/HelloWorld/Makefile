
CPP=gcc 

# set the dependence of lib
WX_INCLUDE=-I/usr/local/lib/wx/include/osx_cocoa-unicode-static-3.0 -I/usr/local/include/wx-3.0 -D_FILE_OFFSET_BITS=64 -D__WXMAC__ -D__WXOSX__ -D__WXOSX_COCOA__
WX_LIBS=-L/usr/local/lib -framework IOKit -framework Carbon -framework Cocoa -framework AudioToolbox -framework System -framework OpenGL /usr/local/lib/libwx_osx_cocoau_xrc-3.0.a /usr/local/lib/libwx_osx_cocoau_webview-3.0.a /usr/local/lib/libwx_osx_cocoau_qa-3.0.a /usr/local/lib/libwx_baseu_net-3.0.a /usr/local/lib/libwx_osx_cocoau_html-3.0.a /usr/local/lib/libwx_osx_cocoau_adv-3.0.a /usr/local/lib/libwx_osx_cocoau_core-3.0.a /usr/local/lib/libwx_baseu_xml-3.0.a /usr/local/lib/libwx_baseu-3.0.a -framework WebKit -lexpat -lwxregexu-3.0 -lwxtiff-3.0 -lwxjpeg-3.0 -lwxpng-3.0 -lz -lpthread -liconv -lc++ -llzma 
CPPFLAGS=-Wall ${WX_INCLUDE} ${WX_LIBS} 


all : main


HelloWorldFrame.o : mondrian.xpm HelloWorldFrame.cc
	${CPP} -c ${CPPFLAGS}  HelloWorldFrame.cc

		
main : HelloWorldFrame.o 
	${CPP}  -o main HelloWorldFrame.o ${WX_LIBS}  


#
#../configure --disable-shared --enable-unicode --with-cocoa --with-macosx-version-min=10.7 --with-macosx-sdk=/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.9.sdk CXXFLAGS="-std=c++0x -stdlib=libc++" CPPFLAGS="-stdlib=libc++" LIBS=-lc++	
#
# I'm guessing you have "C++ Standard Library" set to "libc++". 
# If this is the case, you want <type_traits>, not <tr1/type_traits>. 
# libc++ gives you a C++11 library, whereas libstdc++ (which is also the default in Xcode 4.5) gives you a C++03 library with tr1 support.