#ifndef MAIN_FRAME_H
#define MAIN_FRAME_H

#include "wxwidgets.h"

#include "MediaPlayerPanel.h"

class CMainFrame : public wxFrame{

public:
  // Constructor
  CMainFrame(const wxString& title);
  
  
  // Event handlers
  void OnQuit(wxCommandEvent& event);
  void OnAbout(wxCommandEvent& event);
  void OnLoad(wxCommandEvent& event);
  void OnPlay(wxCommandEvent& event);
  
  void OnEditCols(wxCommandEvent& event);
private:

	void BuildMeunbar();
	CMediaPlayerPanel *m_player;
	
  //This class handles events
  //DECLARE_EVENT_TABLE()     
}; 


#endif