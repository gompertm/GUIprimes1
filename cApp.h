#pragma once

#include "wx/wx.h"
#include "cMain.h"


class cApp : public wxApp
{
public:
	cApp();

	virtual bool OnInit();
	void SetRestart(bool flag)
	{
		m_restart = flag;
	}

private:
	cMain* m_frame1 = nullptr;  

protected:
	virtual ~cApp();
	bool m_restart;
};


