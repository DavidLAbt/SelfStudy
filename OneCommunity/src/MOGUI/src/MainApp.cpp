#include "wxwidgets.h"
#include "MainApp.h"
#include "MainFrame.h"


  
// Give wxWidgets the means to create a CMainApp object
IMPLEMENT_APP(CMainApp)
  

bool CMainApp::OnInit(){
  
  // create the main application window
  CMainFrame *frame = new CMainFrame(wxT("Video Conferencing System"));
  
  // show it
  frame->Show(true);
  
  // Start the event loop
  return true;
}
