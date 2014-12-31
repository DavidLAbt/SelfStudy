#ifndef MEDIA_PLAYER_PANEL_H
#define MEDIA_PLAYER_PANEL_H


#include "wxwidgets.h"


class CMediaPlayerPanel : public wxPanel {

public:
	CMediaPlayerPanel(wxFrame* parent);
	void LoadAll();
	void PlayAll();

private:
	wxMediaCtrl** m_mediactrls;   
   
};

#endif