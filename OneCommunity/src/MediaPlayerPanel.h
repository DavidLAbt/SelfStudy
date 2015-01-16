#ifndef MEDIA_PLAYER_PANEL_H
#define MEDIA_PLAYER_PANEL_H


#include "wxwidgets.h"


class CMediaPlayerPanel : public wxPanel {

public:
	
  CMediaPlayerPanel(wxFrame* parent);
	void LoadAll(int nUsers);
	void PlayAll();
  
  void SetNumbOfCols(int nCols);
  void ShowCtrls(bool bshow);

private:
  
	wxMediaCtrl** m_mediactrls; 
  wxGridSizer* m_sizer;
  
  int m_nUsers;   
   
  // 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
  const int m_layout[11][2] = { {1, 1}, {1, 1}, {1, 2}, {1, 3}, {2, 2}, {2, 3}, {2, 3}, {2,4}, {2, 4}, {3, 3}, {2, 5} };
  void CreateMediaCtrls();
  
};

#endif