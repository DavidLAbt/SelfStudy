#include "wxwidgets.h"
#include "MainFrame.h"
#include "MediaPlayerPanel.h"
#include <wx/numdlg.h> 

CMainFrame::CMainFrame(const wxString& title): wxFrame(NULL, wxID_ANY, title) {
  
  // set the frame icon
  SetIcon(wxIcon(mondrian_xpm));
  
  // build the menu bar
  this->BuildMeunbar();
 
  // draw client area
  m_player = new CMediaPlayerPanel(this);
   
  // create a status bar just for fun
  CreateStatusBar(2);
  SetStatusText(wxT("Weclome to wxWidgets"));

}


void CMainFrame::BuildMeunbar() {
  //created menubar
  wxMenuBar * menuBar = new wxMenuBar();
  
  //create file menu
  wxMenu* fileMenu = new wxMenu;
  fileMenu->Append(wxID_EXIT, wxT("E&xit\tAlt-X"), wxT("Quit this program"));
  
  fileMenu->Append(myID_LOAD, wxT("C&onnect\tAlt-C"), wxT("Connect to video source"));
  fileMenu->Append(myID_PLAY, wxT("P&lay\tAlt-P"), wxT("Play"));
  fileMenu->Append(myID_EDIT_COLS, wxT("Rearrange"), wxT("Set the arrangement of windows"));
  
  // the about item should be in the help menu
  wxMenu* helpMenu = new wxMenu;
  helpMenu->Append(wxID_ABOUT, wxT("&About...\tF1"), wxT("Show about dialog"));
  
  //append the created menu to menubar
  menuBar->Append(fileMenu, wxT("&File"));
  menuBar->Append(helpMenu, wxT("&Help"));
  
  // attach the menu bar to the frame
  SetMenuBar(menuBar);
	
  //
  // Menu events
  //
  this->Connect(wxID_EXIT, wxEVT_MENU, wxCommandEventHandler(CMainFrame::OnQuit));
  this->Connect(wxID_ABOUT, wxEVT_MENU,wxCommandEventHandler(CMainFrame::OnAbout));
  this->Connect(myID_LOAD, wxEVT_MENU, wxCommandEventHandler(CMainFrame::OnLoad));
  this->Connect(myID_PLAY, wxEVT_MENU,wxCommandEventHandler(CMainFrame::OnPlay));
  this->Connect(myID_EDIT_COLS, wxEVT_MENU,wxCommandEventHandler(CMainFrame::OnEditCols));
}



    
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

void CMainFrame::OnLoad(wxCommandEvent& event)
{
  int numb =  wxGetNumberFromUser(	wxT("Setting the number of attendees"), "#attendees:", "Attendees", 6, 2, 10, this);	
  if (numb != -1){
    m_player->LoadAll(numb);
  }
  
}


void CMainFrame::OnPlay(wxCommandEvent& event)
{
  m_player->PlayAll();
}

void CMainFrame::OnEditCols(wxCommandEvent& event)
{

  int numb =  wxGetNumberFromUser	(	wxT("Please input the number of windows in a row"), "#columns:", "Rearrange windows", 3, 1, 5, this);	
  if (numb != -1){
    m_player->SetNumbOfCols(numb);
  }
 
}