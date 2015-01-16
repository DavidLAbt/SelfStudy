/////////////////////////////////////////////////////////////////////////////
// Purpose:     GStreamer backend playing streaming media for wxWidgets 
// Modified by: Jing Chen <jxc761@case.edu>
//              01/01/2015
// Copyright:   (c) 2015-2016 Jing Chen
// Licence:     
/////////////////////////////////////////////////////////////////////////////
//
// Notes: This backend is edited from following source code.
// 
// Here is origin source code information:
/////////////////////////////////////////////////////////////////////////////
// Name:        src/unix/mediactrl.cpp
// Purpose:     GStreamer backend for Unix
// Author:      Ryan Norton <wxprojects@comcast.net>
// Modified by:
// Created:     02/04/05
// Copyright:   (c) 2004-2005 Ryan Norton
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef MY_GSTREAMER_BACKEND_H
#define MY_GSTREAMER_BACKEND_H
// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#include "wx/mediactrl.h"


#include <gst/gst.h>                // main gstreamer header

// xoverlay/video stuff, gst-gconf for 0.8
//#if GST_VERSION_MAJOR > 0 || GST_VERSION_MINOR >= 10
//#   include <gst/interfaces/xoverlay.h>
//#else
//#   include <gst/xoverlay/xoverlay.h>
//#   include <gst/gconf/gconf.h>        // gstreamer glib configuration
//#endif

#include <gst/video/videooverlay.h>

#ifndef  WX_PRECOMP
    #include "wx/log.h"             // wxLogDebug/wxLogSysError/wxLogTrace
    #include "wx/app.h"             // wxTheApp->argc, wxTheApp->argv
    #include "wx/timer.h"           // wxTimer
#endif

#include "wx/filesys.h"             // FileNameToURL()
#include "wx/thread.h"              // wxMutex/wxMutexLocker
#include "wx/vector.h"              // wxVector<wxString>

#ifdef __WXGTK__
    #include <gtk/gtk.h>
    #include <gdk/gdkx.h>
    #include "wx/gtk/private/gtk2-compat.h"
#endif

//-----------------------------------------------------------------------------
// Discussion of internals
//-----------------------------------------------------------------------------

/*
   This is the GStreamer backend for unix. Currently we require 0.8 or
   0.10. Here we use the "playbin" GstElement for ease of use.

   Note that now we compare state change functions to GST_STATE_FAILURE
   now rather than GST_STATE_SUCCESS as newer gstreamer versions return
   non-success values for returns that are otherwise successful but not
   immediate.

   Also this probably doesn't work with anything other than wxGTK at the
   moment but with a tad bit of work it could theorectically work in
   straight wxX11 et al.

   One last note is that resuming from pausing/seeking can result
   in erratic video playback (GStreamer-based bug, happens in totem as well)
   - this is better in 0.10, however. One thing that might make it worse
   here is that we don't preserve the aspect ratio of the video and stretch
   it to the whole window.

   Note that there are some things used here that could be undocumented -
   for reference see the media player Kiss and Totem as well as some
   other sources. There was a backend for a kde media player as well
   that attempted thread-safety...

   Then there is the issue of m_asynclock. This serves several purposes:
   1) It prevents the C callbacks from sending wx state change events
      so that we don't get duplicate ones in 0.8
   2) It makes the sync and async handlers in 0.10 not drop any
      messages so that while we are polling it we get the messages in
      SyncStateChange instead of the queue.
   3) Keeps the pausing in Stop() synchronous

   RN: Note that I've tried to follow the wxGTK conventions here as close
   as possible. In the implementation the C Callbacks come first, then
   the internal functions, then the public ones. Set your vi to 80
   characters people :).
*/

//=============================================================================
//  Declarations
//=============================================================================

//-----------------------------------------------------------------------------
//  GStreamer (most version compatibility) macros
//-----------------------------------------------------------------------------

// In 0.9 there was a HUGE change to GstQuery and the
// gst_element_query function changed dramatically and split off
// into two separate ones
#if GST_VERSION_MAJOR == 0 && GST_VERSION_MINOR <= 8
#    define wxGst_element_query_duration(e, f, p) \
                gst_element_query(e, GST_QUERY_TOTAL, f, p)
#    define wxGst_element_query_position(e, f, p) \
                gst_element_query(e, GST_QUERY_POSITION, f, p)
#elif GST_VERSION_MAJOR == 0 && GST_VERSION_MINOR == 9
// However, the actual 0.9 version has a slightly different definition
// and instead of gst_element_query_duration it has two parameters to
// gst_element_query_position instead
#    define wxGst_element_query_duration(e, f, p) \
                gst_element_query_position(e, f, 0, p)
#    define wxGst_element_query_position(e, f, p) \
                gst_element_query_position(e, f, p, 0)
#else
#define wxGst_element_query_duration gst_element_query_duration
#define wxGst_element_query_position gst_element_query_position
#endif

// Other 0.10 macros
#if GST_VERSION_MAJOR > 0 || GST_VERSION_MINOR >= 10
#   define GST_STATE_FAILURE GST_STATE_CHANGE_FAILURE
#   define GST_STATE_SUCCESS GST_STATE_CHANGE_SUCCESS
#   define GstElementState GstState
#   define gst_gconf_get_default_video_sink() \
        gst_element_factory_make ("gconfvideosink", "video-sink");
#   define gst_gconf_get_default_audio_sink() \
        gst_element_factory_make ("gconfaudiosink", "audio-sink");
#endif

// Max wait time for element state waiting - GST_CLOCK_TIME_NONE for inf
#define wxGSTREAMER_TIMEOUT (100 * GST_MSECOND) // Max 100 milliseconds

//-----------------------------------------------------------------------------
//  wxLogTrace mask string
//-----------------------------------------------------------------------------
#define wxTRACE_GStreamer wxT("GStreamer")

///
// ADD by Jing
#define GstXOverlay GstVideoOverlay
#define GST_IS_X_OVERLAY GST_IS_VIDEO_OVERLAY
#define GST_TYPE_X_OVERLAY GST_TYPE_VIDEO_OVERLAY   
#define  GST_X_OVERLAY     GST_VIDEO_OVERLAY
        
#define gst_x_overlay_set_xwindow_id gst_video_overlay_set_window_handle
//-----------------------------------------------------------------------------
//
//  CGStreamerMediaBackend
//
//-----------------------------------------------------------------------------
class WXDLLIMPEXP_MEDIA
    CGStreamerMediaBackend : public wxMediaBackendCommonBase
{
private:
  bool InitGstreamer();
  bool BuildPipeline();
  
public:

    CGStreamerMediaBackend();
    virtual ~CGStreamerMediaBackend();

    virtual bool CreateControl(wxControl* ctrl, wxWindow* parent,
                                     wxWindowID id,
                                     const wxPoint& pos,
                                     const wxSize& size,
                                     long style,
                                     const wxValidator& validator,
                                     const wxString& name);

    virtual bool Play();
    virtual bool Pause();
    virtual bool Stop();

    virtual bool Load(const wxString& fileName);
    virtual bool Load(const wxURI& location);
    virtual bool Load(const wxURI& location,
                      const wxURI& proxy)
        { return wxMediaBackendCommonBase::Load(location, proxy); }


    virtual wxMediaState GetState();

    virtual bool SetPosition(wxLongLong where);
    virtual wxLongLong GetPosition();
    virtual wxLongLong GetDuration();

    virtual void Move(int x, int y, int w, int h);
    wxSize GetVideoSize() const;

    virtual double GetPlaybackRate();
    virtual bool SetPlaybackRate(double dRate);

    virtual wxLongLong GetDownloadProgress();
    virtual wxLongLong GetDownloadTotal();

    virtual bool SetVolume(double dVolume);
    virtual double GetVolume();

    //------------implementation from now on-----------------------------------
    bool CheckForErrors();
    bool DoLoad(const wxString& locstring);
    wxMediaCtrl* GetControl() { return m_ctrl; } // for C Callbacks
    void HandleStateChange(GstElementState oldstate, GstElementState newstate);
    bool QueryVideoSizeFromElement(GstElement* element);
    bool QueryVideoSizeFromPad(GstPad* caps);
    void SetupXOverlay();
    bool SyncStateChange(GstElement* element, GstElementState state,
                         gint64 llTimeout = wxGSTREAMER_TIMEOUT);
    bool TryAudioSink(GstElement* audiosink);
    bool TryVideoSink(GstElement* videosink);

    GstElement*     m_playbin;      // GStreamer media element
    wxSize          m_videoSize;    // Cached actual video size
    double          m_dRate;        // Current playback rate -
                                    // see GetPlaybackRate for notes
    wxLongLong      m_llPausedPos;  // Paused position - see Pause()
    GstXOverlay*    m_xoverlay;     // X Overlay that contains the GST video
    wxMutex         m_asynclock;    // See "discussion of internals"
    class CGStreamerMediaEventHandler* m_eventHandler; // see below

    // Mutex protecting just the variables below which are set from
    // gst_error_callback() called from a different thread.
    wxMutex m_mutexErr;
    struct Error
    {
        Error(const gchar* message, const gchar* debug)
            : m_message(message, wxConvUTF8),
              m_debug(debug, wxConvUTF8)
        {
        }

        wxString m_message,
                 m_debug;
    };

    wxVector<Error> m_errors;
    


    friend class CGStreamerMediaEventHandler;
    friend class wxGStreamerLoadWaitTimer;
    DECLARE_DYNAMIC_CLASS(CGStreamerMediaBackend)
      

};

//-----------------------------------------------------------------------------
// CGStreamerMediaEventHandler
//
// OK, this will take an explanation - basically gstreamer callbacks
// are issued in a separate thread, and in this thread we may not set
// the state of the playbin, so we need to send a wx event in that
// callback so that we set the state of the media and other stuff
// like GUI calls.
//-----------------------------------------------------------------------------
class CGStreamerMediaEventHandler : public wxEvtHandler
{
    public:
    CGStreamerMediaEventHandler(CGStreamerMediaBackend* be) : m_be(be)
    {
        this->Connect(wxID_ANY, wxEVT_MEDIA_FINISHED,
           wxMediaEventHandler(CGStreamerMediaEventHandler::OnMediaFinish));
    }

    void OnMediaFinish(wxMediaEvent& event);

    CGStreamerMediaBackend* m_be;
};


//#endif //wxUSE_GSTREAMER
  
#endif //MY_GSTREAMER_BACKEND_H

