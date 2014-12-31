#ifndef MAIN_APP_H

#define MAIN_APP_H

#include "wxwidgets.h"

class CMainApp: public wxApp
{
public:
   virtual bool OnInit();
};


// Implements CMainApp& GetApp()
DECLARE_APP(CMainApp)

#endif
