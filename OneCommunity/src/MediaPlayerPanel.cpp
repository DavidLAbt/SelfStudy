#include "wxwidgets.h"
#include "MediaPlayerPanel.h"
#include "GstreamerBackend.h"

// ----------------------------------------------------------------------------
// This makes relative paths work in C++ in Xcode by changing directory to the Resources folder inside the .app bundle
#ifdef __APPLE__
#include "CoreFoundation/CoreFoundation.h"
#endif
#define MAX_NUMB_OF_SRC (6)

/*

void CMediaPlayerPanel::ShowCtrls(bool bshow)
{
  for (int i = 0;  i < m_nUsers; i++) {
    m_mediactrls[i]->ShowPlayerControls( bshow ? wxMEDIACTRLPLAYERCONTROLS_DEFAULT : wxMEDIACTRLPLAYERCONTROLS_NONE );
  }
  
}

*/

void CMediaPlayerPanel::SetNumbOfCols(int nCols)
{
  // m_sizer = new wxGridSizer(nCols, 10, 10);
  
  if (m_sizer != NULL && nCols <= m_nUsers) {
    
    m_sizer = new wxGridSizer(nCols, 10, 10);
    for (int i = 0;  i < m_nUsers; i++) {
      m_sizer->Add(m_mediactrls[i], 0, wxALIGN_CENTRE|wxALL|wxEXPAND);
    }
    this->SetSizer(m_sizer, true);//attach the sizer
    SetSizerAndFit(m_sizer);//fit sizer
    PostSizeEventToParent();
  }
  
  
}

void CMediaPlayerPanel::LoadAll(int nUsers)
{	
  // remove all
  
  if(m_sizer != NULL)
  {
    m_sizer->Clear(true);
  }
  
  if (m_mediactrls != NULL){
    delete m_mediactrls;
    m_mediactrls=NULL;
  }
  m_nUsers = nUsers;
  //
  //  Create a grid sizer
  //
  
 
  
  int i, j;
  
  // create wxMediaCtrl
  m_mediactrls = new wxMediaCtrl*[m_nUsers];  
  
  for (i = 0;  i < m_nUsers; i++) {
  	
  	//
  	//  Create a media control and make sure creation was successful    
  	//
  	wxMediaCtrl* mediactrl = new wxMediaCtrl();
    bool bOK = mediactrl->Create(this, wxID_ANY,wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxT("CGStreamerMediaBackend"));                                              
    wxASSERT_MSG(bOK, wxT("Could not create media control!"));  	
    wxUnusedVar(bOK);
    
  	m_mediactrls[i] = mediactrl;
  }
  

  //m_sizer->SetCols(nCols);
  //m_sizer->SetRows(nRows);
  // add wxMediaCtrl to sizer
  int nRows = m_layout[m_nUsers][0];
  int nCols = m_layout[m_nUsers][1];
  
  m_sizer = new wxGridSizer(nRows, nCols, 10, 10);
  for (i = 0;  i < m_nUsers; i++) {
    m_sizer->Add(m_mediactrls[i], 0, wxALIGN_CENTRE|wxALL|wxEXPAND);
  }
  
  
  // open files
	for (int i = 0; i < m_nUsers; i++){
		wxString fn;
    
    
    fn.Printf(wxT("./res/videos/%d.mp4"), i);  
#ifdef __APPLE__    
    // get bundle
    CFBundleRef mainBundle = CFBundleGetMainBundle();
    
    // get resource url
    CFURLRef resourcesURL = CFBundleCopyResourcesDirectoryURL(mainBundle); 
    
    //get file path from url
    char path[PATH_MAX];    
    CFURLGetFileSystemRepresentation(resourcesURL, TRUE, (UInt8 *)path, PATH_MAX); 
    CFRelease(resourcesURL);
    
    //set where is the video
		fn.Printf(wxT("%s/videos/%d.mp4"), path, i % MAX_NUMB_OF_SRC);
    
#endif
    m_mediactrls[i]->Load(fn);
	}
  

  //
 
  this->SetSizer(m_sizer, true);//attach the sizer
  SetSizerAndFit(m_sizer);//fit sizer
  PostSizeEventToParent();
  //this->Refresh();
  //this->Update();
   
}

void  CMediaPlayerPanel::PlayAll()
{
	int i = 0;
	for (i = 0; i < m_nUsers; i++){
		m_mediactrls[i]->Play();
	}
}

CMediaPlayerPanel::CMediaPlayerPanel(wxFrame* parent) : wxPanel(parent, wxID_ANY)
{
  m_sizer  = NULL;
  m_nUsers = -1;
  m_mediactrls = NULL;
  
}


