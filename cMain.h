#pragma once
#include "wx/wx.h"

class cMain : public wxFrame
{
public:
	//utlities;
	cMain();
	~cMain();

	//items;
	wxButton* m_btn1 = nullptr;
	wxButton* m_reset = nullptr;
	wxTextCtrl* m_min = nullptr;
	wxTextCtrl* m_max = nullptr;
	wxTextCtrl* m_count = nullptr;
	wxTextCtrl* m_reject = nullptr;
	wxListBox* m_output = nullptr;
	wxListBox* m_seed = nullptr;
	wxStaticText* m_seedlabel = nullptr;
	wxStaticText* m_minlabel = nullptr;
	wxStaticText* m_maxlabel = nullptr;
	wxStaticText* m_countlabel = nullptr;
	wxStaticText* m_rejectlabel = nullptr;

	//functions;
	void OnButtonClicked(wxCommandEvent& evt);
	void OnResetClicked(wxCommandEvent& evt);
	void OnQuit(wxCommandEvent& event);
	void OnRestart(wxCommandEvent& event);
	void OnReset(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	DECLARE_EVENT_TABLE();


};


