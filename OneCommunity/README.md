
============================
Contents
============================
  ./bin  : excutable files
  
  ./docs : documents
  
  ./src  : source code 
  
  ./libs : third-party libraries  library
  
  ./res  : resource, like video, images, etc.


============================
./libs/wx
============================

  ./include                     : Required header files for both Mac and Win
  
  ./osx_cocoa-unicode-static-3  : Required header files for Mac 
  
  ./mswud                       : Required header files for Win
  
  ./mac                         : Required Lib files for mac
  
  ./win                         : Required Lib files for Win


================================
Compile wxWidgets on Mac
================================

    # download and unzip the source code
    # open terminal and change working directory to wxwidgets
     
    # Build the library for Cocoa and supporting C++11
    mkdir build-cocoa-debug
    cd build-cocoa-debug
    ../configure --disable-shared --enable-monolithic --enable-unicode --with-cocoa --enable-any --with-macosx-version-min=10.7 --with-macosx-sdk=/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.9.sdk CXXFLAGS="-std=c++0x -stdlib=libc++" CPPFLAGS="-stdlib=libc++" LIBS=-lc++
    make
    
    # install wxwidgets
    make
    sudo make install
    
    # Build the samples and demos
    cd samples; make; cd ..
    cd demos;   make; cd ..
    

============================
Compile wxWidgets on Windows
============================

    # download and unzip the source code
    # Open solution with VS
    # Build the solution

============================
Use wxWidgets on Windows
============================
	#define Micro
	WxLibDir: ../libs/wx
  	
	#Additional Dependencies:  
	wxmsw30ud_media.lib;wxmsw30ud_core.lib;wxbase30ud.lib;wxtiffd.lib;wxjpegd.lib;wxpngd.lib;wxzlibd.lib;wxregexud.lib;wxexpatd.lib;winmm.lib;comctl32.lib;rpcrt4.lib;wsock32.lib;wininet.lib;%(AdditionalDependencies)
	
  	#Preprocessor Definitions
  	WIN32;_DEBUG;__WXMSW__;_WINDOWS;NOPCH;_CRT_SECURE_NO_DEPRECATE;WXUSINGDLL;__WXDEBUG__;WxLibDir="../libs/wx";%(PreprocessorDefinitions)
  	
  	#Additional Include Directories
  	$(WxLibDir)\include;$(WxLibDir)\mswud;%(AdditionalIncludeDirectories)
  	
  	#Additional Library Directories: 
  	$(WxLibDir)\win;%(AdditionalLibraryDirectories)
    
    #SubSystem
  	Set Windows (/SUBSYSTEM:WINDOWS)
		
Notes: Directly edit .vxcproj to create user defined micro:
Insert to <Project> </Project>
<PropertyGroup>
<WxLibDir>$([System.IO.Path]::Combine('$([System.IO.Path]::GetDirectoryName( `$([System.IO.Path]::GetDirectoryName($(SolutionDir)))`))',"libs", "wx"))</WxLibDir>
</PropertyGroup>

============================
Reference
============================
[1]WXWIDGETS, C++ LIBRARIES AND C++11
   http://www.appletonaudio.com/blog/2013/wxwidgets-c-libraries-and-c11/

[2]Microsoft Visual C++ Guide
   https://wiki.wxwidgets.org/Microsoft_Visual_C++_Guide 
