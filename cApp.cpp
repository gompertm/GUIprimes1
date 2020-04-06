#include "cApp.h"


cApp::cApp()
{
    m_restart = false;
}

cApp::~cApp()
{
  if (m_restart)
    {
     // argv[0] contains the full path to the executable
     wxExecute(argv[0]);
    }
}

bool cApp::OnInit()
{
    m_restart = false;

    // call the base class initialization method, currently it only parses a
    // few common command-line options but it could be do more in the future
    if (!wxApp::OnInit())
        return false;

    // create the main application window
    m_frame1 = new cMain();

    // and show it (the frames, unlike simple controls, are not shown when
    // created initially)
    m_frame1->Show(true);

    // success: wxApp::OnRun() will be called which will enter the main message
    // loop and the application will run. If we returned false here, the
    // application would exit immediately.
    return true;

}
