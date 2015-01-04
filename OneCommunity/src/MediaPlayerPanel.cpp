#include "wxwidgets.h"
#include "MediaPlayerPanel.h"


// ----------------------------------------------------------------------------
// This makes relative paths work in C++ in Xcode by changing directory to the Resources folder inside the .app bundle
#ifdef __APPLE__
#include "CoreFoundation/CoreFoundation.h"
#endif

void CMediaPlayerPanel::LoadAll()
{	
	int nUsers= 6;
	
	for (int i = 0; i < nUsers; i++){
		wxString fn;

/*		if (_NSGetExecutablePath(path, &size) == 0)
    	fn.Printf("executable path is %s\n", path);
		else
    	fn.Printf("buffer too small; need size %u\n", size);
    */
    
    #ifdef __APPLE__    
    CFBundleRef mainBundle = CFBundleGetMainBundle();
    CFURLRef resourcesURL = CFBundleCopyResourcesDirectoryURL(mainBundle);
    char path[PATH_MAX];
    if (!CFURLGetFileSystemRepresentation(resourcesURL, TRUE, (UInt8 *)path, PATH_MAX))
    {
        // error!
    }
    CFRelease(resourcesURL);

    //chdir(path);
    //std::cout << "Current Path: " << path << std::endl;
    
    // fn.Printf(wxT("%s"), path);
		// wxMessageBox(fn);
		fn.Printf(wxT("%s/videos/%d.mp4"), path, i);
		// wxMessageBox(fn);
		m_mediactrls[i]->Load(fn);
		//bool bok = 
#endif

	
	}
}

void  CMediaPlayerPanel::PlayAll()
{

	int nUsers= 6;
	int i = 0;
	
	for (i = 0; i < nUsers; i++){
		
		 m_mediactrls[i]->Play();
	}
}


CMediaPlayerPanel::CMediaPlayerPanel(wxFrame* parent) : wxPanel(parent, wxID_ANY)
{
	int nUsers = 6;
	int i;
	
	  //
    //  Create a grid sizer
    //
    wxGridSizer* sizer = new wxGridSizer(2, 3, wxSize(10, 10));
    // sizer->AddGrowableCol(0);
    
    
    m_mediactrls = new wxMediaCtrl*[nUsers];  
    for (i = 0;  i < nUsers; i++) {
    	
    	//
    	//  Create a media control
    	//
    	wxMediaCtrl* mediactrl = new wxMediaCtrl();

 	   	//  Make sure creation was successful
 
      // str now contains "1 2 3"
    	bool bOK = mediactrl->Create(this, wxID_ANY);
    	wxASSERT_MSG(bOK, wxT("Could not create media control!"));
    	wxUnusedVar(bOK);
    	
    	m_mediactrls[i] = mediactrl;
    	sizer->Add(m_mediactrls[i], 0, wxALIGN_CENTRE|wxALL|wxEXPAND);
    }
 
    
    //attach the sizer
    this->SetSizer(sizer);
    SetSizerAndFit(sizer);
}
