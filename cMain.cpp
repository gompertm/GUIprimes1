#include "cMain.h"
#include "utility.h"
#include <sstream>
#include <string>
#include <time.h> 

#include "cApp.h"
enum
{
	// menu items
	Minimal_Quit = wxID_EXIT,

	// it is important for the id corresponding to the "About" command to have
	// this standard value as otherwise it won't be handled properly under Mac
	// (where it is special and put into the "Apple" menu)
	Minimal_About = wxID_ABOUT,
	Minimal_Restart = wxID_HIGHEST + 1
};
// ----------------------------------------------------------------------------
// event tables and other macros for wxWidgets
// ----------------------------------------------------------------------------

// the event tables connect the wxWidgets events with the functions (event
// handlers) which process them. It can be also done at run-time, but for the
// simple menu events like this the static method is much simpler.
BEGIN_EVENT_TABLE(cMain, wxFrame)
EVT_MENU(Minimal_Quit, cMain::OnQuit)
EVT_MENU(Minimal_About, cMain::OnAbout)
EVT_MENU(Minimal_Restart, cMain::OnRestart)
EVT_BUTTON(42, cMain::OnButtonClicked)
EVT_BUTTON(54, cMain::OnReset)
END_EVENT_TABLE()
IMPLEMENT_APP(cApp)

cMain::~cMain()
{

}

void cMain::OnRestart(wxCommandEvent& WXUNUSED(event))
{
	wxGetApp().SetRestart(true);
	wxGetApp().ExitMainLoop();
}

void cMain::OnQuit(wxCommandEvent& WXUNUSED(event))
{
	// true is to force the frame to close
	Close(true);
}
void cMain::OnReset(wxCommandEvent& WXUNUSED(event))
{
	m_count->Clear();
	m_min->Clear();
	m_max->Clear();
	m_reject->Clear();
	m_output->Clear();
	m_seed->Clear();

}

void cMain::OnAbout(wxCommandEvent& WXUNUSED(event))
{
	wxMessageBox(wxString::Format
	(
		"Welcome to GUIprimes!\n"
		"\n"
		"This is my prime number finder utility\n"
		"running under %s.",
		wxVERSION_STRING,
		wxGetOsDescription()
	),
		"GUI primes!",
		wxOK | wxICON_INFORMATION,
		this);
}
void cMain::OnButtonClicked(wxCommandEvent& evt)
{
	long long int random = -9000, reject = -19, x = -100, max = -1100, min = -10, count = -10;
	bool occured = false, maxoccured = false, minoccured = false, countoccured = false, rejectoccured = false, rejectfieldblank = true;
	std::stringstream tempstring;
	std::string string1;
	occured = m_seed->IsEmpty();
	if (!occured)
	{
		m_output->Clear();
		m_seed->Clear();
	}
	occured = false;


		//first grab the count out of the count box and validate it;
		string1 = m_count->GetValue();
		if (is_digits(string1) && string1 != "")
		{
		count = std::stoi(string1);
		}
		else
		{
			countoccured = true;
		}
		if (count < 0)
		{
		    countoccured = true;
		}
		//second grab the min out of the min box and validate it;
		string1 = m_min->GetValue();

		if (is_digits(string1) && string1 != "")
		{
		min= std::stoi(string1);
		}		
		else
		{
			minoccured = true;
		}
		if (min<0)
		{
			minoccured = true;
		}



		//third grab the max out of the max box and validate it;
		string1 = m_max->GetValue();
		if (is_digits(string1) && string1 != "")
		{
		max = std::stoi(string1);
		}
		else
		{
			maxoccured = true;
		}
		//last grab the reject digit out of the reject box and validate it;
		string1 = m_reject->GetValue();
		if (string1 != "")
		{
			rejectfieldblank = false;
			if (is_digits(string1))
			{
				reject = std::stoi(string1);
			}
			if (reject <0 || reject >9 )
			{
				rejectoccured = true;
			}
		}
		else
		{
			rejectfieldblank = true;
		}
		if (max < min)
		{
				occured = true;
		}
		if (!occured && !minoccured && !maxoccured && !countoccured && !rejectoccured)
		{
			srand(time(NULL));
			// seed x with a random number;
			x = (double)rand() / (RAND_MAX) * (max - min) + min;
			string1 = std::to_string(x);
			m_seed->AppendString(string1);
			for (int y = 0; y < count; x++)
			{
				if (IsPrime(x))
				{
					if (reject != -19)
					{
						bool results = check_each_digit_isnt(x, reject);
						if (results)
						{
							string1 = std::to_string(x);
							m_output->AppendString(string1);
							y++;
						}
					}
					else
					{
						string1 = std::to_string(x);
						m_output->AppendString(string1);
						y++;
					}

				}

			}
		}
		else
		{
			bool alreadyhappened = false;
			if (maxoccured && !minoccured && !countoccured && !rejectoccured)
			{
				wxMessageDialog* dial = new wxMessageDialog(NULL, wxT("Improper number entered into the Maximum field"), wxT("Maximum Error"), wxOK | wxICON_ERROR);
				dial->ShowModal();
				alreadyhappened = true;
			}
			if (minoccured && !maxoccured && !countoccured && !rejectoccured)
			{
				wxMessageDialog* dial = new wxMessageDialog(NULL, wxT("Improper number entered into the Minimum field"), wxT("Minimum Error"), wxOK | wxICON_ERROR);
				dial->ShowModal();
				alreadyhappened = true;
			}
			if (countoccured && !minoccured && !maxoccured && !rejectoccured)
			{
				wxMessageDialog* dial = new wxMessageDialog(NULL, wxT("Improper number entered into the Number of results field"), wxT("Count Error"), wxOK | wxICON_ERROR);
				dial->ShowModal();
				alreadyhappened = true;
			}
			if (rejectoccured && !minoccured && !countoccured && !maxoccured)
			{
				wxMessageDialog* dial = new wxMessageDialog(NULL, wxT("Improper number entered into the Digit to Reject field"), wxT("Rejected!"), wxOK | wxICON_ERROR);
				dial->ShowModal();
				alreadyhappened = true;
			}
			if ((occured && !rejectoccured && !minoccured && !countoccured && !maxoccured) || ((occured || rejectoccured || minoccured || countoccured || maxoccured) && !alreadyhappened))
			{
				wxMessageDialog* dial = new wxMessageDialog(NULL, wxT("A generic error has occured"), wxT("Error"), wxOK | wxICON_ERROR);
				dial->ShowModal();

			}


		}
		//cause it to exit when we are done with this program;
	evt.Skip();
}



cMain::cMain() :wxFrame(nullptr, wxID_ANY, "GUIPRIMES", wxPoint(40, 40), wxSize(450, 600))
{
	// set the frame icon
        wxIcon titlebaricon = wxIcon("icon.png");
	SetIcon(titlebaricon);

#if wxUSE_MENUS
	// create a menu bar
	wxMenu* fileMenu = new wxMenu;

	// the "About" item should be in the help menu
	wxMenu* helpMenu = new wxMenu;
	helpMenu->Append(Minimal_About, "&About\tF1", "Show about dialog");

	fileMenu->Append(Minimal_Restart, "&Restart\tAlt-R", "Restart this program");
	fileMenu->Append(Minimal_Quit, "E&xit\tAlt-X", "Quit this program");

	// now append the freshly created menu to the menu bar...
	wxMenuBar* menuBar = new wxMenuBar();
	menuBar->Append(fileMenu, "&File");
	menuBar->Append(helpMenu, "&Help");

	// ... and attach this menu bar to the frame
	SetMenuBar(menuBar);
#endif // wxUSE_MENUS

#if wxUSE_STATUSBAR
	// create a status bar just for fun (by default with 1 pane only)
	CreateStatusBar(2);
	SetStatusText("GuiPrimes");
#endif // wxUSE_STATUSBAR
	//create the buttons(must have matching lines in the .h file)
	m_btn1 = new wxButton(this, 42, "Run", wxPoint(10, 10), wxSize(150, 50));
	m_reset = new wxButton(this, 54, "Reset", wxPoint(200, 10), wxSize(150, 50));
	//create the text entry fields(must have matching lines in the .h file)
	m_min = new wxTextCtrl(this, 43, "", wxPoint(10, 100), wxSize(100, 30));
	m_max = new wxTextCtrl(this, 44, "", wxPoint(110, 100), wxSize(100, 30));
	m_count = new wxTextCtrl(this, 45, "", wxPoint(210, 100), wxSize(100, 30));
	m_reject = new wxTextCtrl(this, 52, "", wxPoint(310, 100), wxSize(100, 30));
	//create the text output listboxs(must have matching lines in the .h file)
	m_output = new wxListBox(this, 46, wxPoint(10, 130), wxSize(300, 300));
	m_seed = new wxListBox(this, 47, wxPoint(320, 230), wxSize(100, 25));
	// Create the StaticText controls(must hav matching linbes in the .h file)
	m_seedlabel = new wxStaticText(this, 48,  "Seed Value", wxPoint(320, 200),wxSize(90,30),0,"what is this one for?");
	m_minlabel = new wxStaticText(this, 49, "Minimum Seed", wxPoint(20, 70), wxSize(90, 30), 0, "what is this one for?");
	m_maxlabel = new wxStaticText(this, 50, "Maximum Seed", wxPoint(120, 70), wxSize(90, 30), 0, "what is this one for?");
	m_countlabel = new wxStaticText(this, 51, "Number of results", wxPoint(220, 70), wxSize(90, 30), 0, "what is this one for?");
	m_rejectlabel = new wxStaticText(this, 53, "Digit to Reject", wxPoint(320, 70), wxSize(90, 30), 0, "what is this one for?");

}

