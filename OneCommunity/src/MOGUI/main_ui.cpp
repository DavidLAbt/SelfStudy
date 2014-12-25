
#include <wx/wx.h>
#include "mondrian.xpm"

class CMainFrame : public wxFrame{
public:
  // Constructor
  CMainFrame(const wxString& title);
  
  
  // Event handlers
  void OnQuit(wxCommandEvent& event);
  void OnAbout(wxCommandEvent& event);
  
private:
  // This class handles events
  DECLARE_EVENT_TABLE()
     
}; 



class CMainApp: public wxApp
{
  public:
   virtual bool OnInit();
};

// Implements CMainApp& GetApp()
DECLARE_APP(CMainApp)

// Give wxWidgets the means to create a CMainApp object
IMPLEMENT_APP(CMainApp)
  
//#include "HelloWorldFrame.h"
//# include "mondrian.xpm"

BEGIN_EVENT_TABLE(CMainFrame, wxFrame)
  EVT_MENU(wxID_ABOUT, CMainFrame::OnAbout)
  EVT_MENU(wxID_EXIT, CMainFrame::OnQuit)
END_EVENT_TABLE()
    
void CMainFrame::OnAbout(wxCommandEvent& event)
{
  wxString msg;
  msg.Printf(wxT("Hello and welecome to %s"), wxVERSION_STRING);
  wxMessageBox(msg, wxT("About Hello World"), wxOK | wxICON_INFORMATION, this);
}

void CMainFrame::OnQuit(wxCommandEvent& event)
{
  // Destroy the frame
  Close();
}

CMainFrame::CMainFrame(const wxString& title): wxFrame(NULL, wxID_ANY, title) {
  
  // set the frame icon
  SetIcon(wxIcon(mondrian_xpm));
  
  //create a menu
  wxMenu* fileMenu = new wxMenu;
  fileMenu->Append(wxID_EXIT, wxT("E&xit\tAlt-X"), wxT("Quit this program"));
  
  // the about item should be in the help menu
  wxMenu* helpMenu = new wxMenu;
  helpMenu->Append(wxID_ABOUT, wxT("&About...\tF1"), wxT("Show about dialog"));
  
  //now append the created menu to menubar
  wxMenuBar * menuBar = new wxMenuBar();
  menuBar->Append(fileMenu, wxT("&File"));
  menuBar->Append(helpMenu, wxT("&Help"));
  
  // attach the menu bar to the frame
  SetMenuBar(menuBar);
  
  // create a status bar just for fun
  CreateStatusBar(2);
  SetStatusText(wxT("Weclome to wxWidgets"));
  
}


bool CMainApp::OnInit(){
  
  // create the main application window
  CMainFrame *frame = new CMainFrame(wxT("Hello World App"));
  
  // show it
  frame->Show(true);
  
  // Start the event loop
  return true;
}
