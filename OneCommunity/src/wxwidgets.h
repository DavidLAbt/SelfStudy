
#ifndef MY_WXWIDGETS_H

#define MY_WXWIDGETS_H

// ============================================================================
// Definitions
// ============================================================================

// ----------------------------------------------------------------------------
// Pre-compiled header stuff
// ----------------------------------------------------------------------------

#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

// ----------------------------------------------------------------------------
// Headers
// ----------------------------------------------------------------------------

#include "wx/mediactrl.h"   // for wxMediaCtrl
#include "wx/filedlg.h"     // for opening files from OpenFile
#include "wx/slider.h"      // for a slider for seeking within media
#include "wx/sizer.h"       // for positioning controls/wxBoxSizer
#include "wx/gbsizer.h"

#include "wx/timer.h"       // timer for updating status bar
#include "wx/textdlg.h"     // for getting user text from OpenURL/Debug
#include "wx/notebook.h"    // for wxNotebook and putting movies in pages
#include "wx/cmdline.h"     // for wxCmdLineParser (optional)
#include "wx/listctrl.h"    // for wxListCtrl
#include "wx/dnd.h"         // drag and drop for the playlist
#include "wx/filename.h"    // For wxFileName::GetName()
#include "wx/config.h"      // for native wxConfig
#include "wx/vector.h"

// Under MSW we have several different backends but when linking statically
// they may be discarded by the linker (this definitely happens with MSVC) so
// force linking them. You don't have to do this in your code if you don't plan
// to use them, of course.
#if defined(__WXMSW__) && !defined(WXUSINGDLL)
    #include "wx/link.h"
    wxFORCE_LINK_MODULE(wxmediabackend_am)
    wxFORCE_LINK_MODULE(wxmediabackend_qt)
    wxFORCE_LINK_MODULE(wxmediabackend_wmp10)
#endif // static wxMSW build

// ----------------------------------------------------------------------------
// Bail out if the user doesn't want one of the
// things we need
// ----------------------------------------------------------------------------

#if !wxUSE_MEDIACTRL || !wxUSE_MENUS || !wxUSE_SLIDER || !wxUSE_TIMER || \
    !wxUSE_NOTEBOOK || !wxUSE_LISTCTRL
#error "Not all required elements are enabled.  Please modify setup.h!"
#endif


// ----------------------------------------------------------------------------
// Enumurations
// ----------------------------------------------------------------------------

// IDs for the controls and the menu commands
enum
{
    // Menu event IDs
    myID_LOAD=1,
    myID_PLAY,
    myID_EDIT_COLS,
    myID_VIEW_SHOW_CTRLS
};



// ----------------------------------------------------------------------------
// resources
// ----------------------------------------------------------------------------
#include "mondrian.xpm"


// ============================================================================
// gstreamer
// ============================================================================
//#include <gst/gst.h>

#endif
