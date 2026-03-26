// For compilers that support precompilation, also includes the "wx.h" file.
#include <wx/wx.h>

// Declare the public applicasion class.
class MyApp : public wxApp
{
  public:
    // Called on app startup
    virtual bool OnInit() override;
};

class MyFrame : public wxFrame
{
  public:
    // ctor(s)
    MyFrame(const wxString &title);

    // event handlers (these functions shouldn't be virtual)
    void      OnQuit(wxCommandEvent &event);
    void      OnAbout(wxCommandEvent &event);
    void      OnEdit(wxCommandEvent &event);

    void      OnStartButtonClicked(wxCommandEvent &event);
    void      OnStopButtonClicked(wxCommandEvent &event);

    wxButton *BtnStart;
    wxButton *BtnStop;

  private:
    // any class wishing to process wxWidgets events must use this macro
    wxDECLARE_EVENT_TABLE();
};

// ----------------------------------------------------------------------------
// constants
// ----------------------------------------------------------------------------

// IDs for the controls and the menu commands
enum
{
    // menu items
    Minimal_Quit = wxID_EXIT,

    Minimal_Edit,

    // it is important for the id corresponding to the "About" command to have
    // this standard value as otherwise it won't be handled properly under Mac
    // (where it is special and put into the "Apple" menu)
    Minimal_About = wxID_ABOUT,

    // Button ids.
    Btn_Start = wxID_HIGHEST + 1, // declares an id which will be used to call our button
    Btn_Stop  = wxID_HIGHEST + 2, // declares an id which will be used to call our button
};

// ----------------------------------------------------------------------------
// event tables and other macros for wxWidgets
// ----------------------------------------------------------------------------

// the event tables connect the wxWidgets events with the functions (event
// handlers) which process them. It can be also done at run-time, but for the
// simple menu events like this the static method is much simpler.
wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(Minimal_Quit, MyFrame::OnQuit)
        EVT_MENU(Minimal_Edit, MyFrame::OnEdit)
            EVT_MENU(Minimal_About, MyFrame::OnAbout)
                EVT_MENU(Btn_Start, MyFrame::OnStartButtonClicked)
                    EVT_MENU(Btn_Stop, MyFrame::OnStopButtonClicked)
                        wxEND_EVENT_TABLE()

    // Create a new application object: this macro will allow wxWidgets to create
    // the application object during program execution (it's better than using a
    // static object for many reasons) and also implements the accessor function
    // wxGetApp() which will return the reference of the right type (i.e. MyApp and
    // not wxApp)
    wxIMPLEMENT_APP(MyApp);

// ============================================================================
// implementation
// ============================================================================

// ----------------------------------------------------------------------------
// the application class
// ----------------------------------------------------------------------------

// 'Main program' equivalent: the program execution "starts" here
bool MyApp::OnInit()
{
    // call the base class initialization method, currently it only parses a
    // few common command-line options but it could be do more in the future
    if (!wxApp::OnInit())
        return false;

    // create the main application window
    MyFrame *frame = new MyFrame("wxWidgets Application!");

    // and show it (the frames, unlike simple controls, are not shown when
    // created initially)
    frame->Show(true);

    // success: wxApp::OnRun() will be called which will enter the main message
    // loop and the application will run. If we returned false here, the
    // application would exit immediately.
    return true;
}

// ----------------------------------------------------------------------------
// main frame
// ----------------------------------------------------------------------------

// frame constructor
MyFrame::MyFrame(const wxString &title)
    : wxFrame(nullptr, wxID_ANY, title)
{
    // set the frame icon
    // SetIcon(wxICON(sample));

#if wxUSE_MENUBAR
    // create a menu bar
    wxMenu *fileMenu = new wxMenu;

    // the "About" item should be in the help menu
    wxMenu *helpMenu = new wxMenu;
    helpMenu->Append(Minimal_About, "&About\tF1", "Show about dialog");

    wxMenu *editMenu = new wxMenu;
    editMenu->Append(Minimal_Edit, "&Copy\tCtrl+c", "Copy to clipboard");

    fileMenu->Append(Minimal_Quit, "E&xit\tAlt-X", "Quit this program");

    // now append the freshly created menu to the menu bar...
    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(fileMenu, "&File");
    menuBar->Append(editMenu, "&Edit");
    menuBar->Append(helpMenu, "&Help");
    // ... and attach this menu bar to the frame
    SetMenuBar(menuBar);

    // Now for the Button.
    BtnStart = new wxButton(this, Btn_Start, _T("START"),
                            wxPoint(0, 0), wxSize(100, 30), 0);
    BtnStop  = new wxButton(this, Btn_Stop, _T("STOP"),
                            wxPoint(100, 0), wxSize(100, 30), 0);

    BtnStart->Bind(wxEVT_BUTTON, &MyFrame::OnStartButtonClicked, this);
    BtnStop->Bind(wxEVT_BUTTON, &MyFrame::OnStopButtonClicked, this);

#else  // !wxUSE_MENUBAR
    // If menus are not available add a button to access the about box
    wxSizer  *sizer    = new wxBoxSizer(wxHORIZONTAL);
    wxButton *aboutBtn = new wxButton(this, wxID_ANY, "About...");
    aboutBtn->Bind(wxEVT_BUTTON, &MyFrame::OnAbout, this);
    sizer->Add(aboutBtn, wxSizerFlags().Center());
    SetSizer(sizer);
#endif // wxUSE_MENUBAR/!wxUSE_MENUBAR

#if wxUSE_STATUSBAR
    // create a status bar just for fun (by default with 1 pane only)
    CreateStatusBar(2);
    SetStatusText("Welcome to wxWidgets!");
#endif // wxUSE_STATUSBAR
}

// event handlers

void MyFrame::OnQuit(wxCommandEvent &WXUNUSED(event))
{
    // true is to force the frame to close
    Close(true);
}

void MyFrame::OnEdit(wxCommandEvent &WXUNUSED(event))
{
    SetStatusText("Copied to clipboard!");
}

void MyFrame::OnAbout(wxCommandEvent &WXUNUSED(event))
{
    wxMessageBox(wxString::Format(
                     "Welcome to %s!\n"
                     "\n"
                     "This is the minimal wxWidgets sample\n"
                     "running under %s.",
                     wxVERSION_STRING,
                     wxGetOsDescription()),
                 "About wxWidgets minimal sample",
                 wxOK | wxICON_INFORMATION,
                 this);
}

// Button Event handlers
void MyFrame::OnStartButtonClicked(wxCommandEvent &event)
{
    SetStatusText("Start Button Pressed!");
}

void MyFrame::OnStopButtonClicked(wxCommandEvent &event)
{
    SetStatusText("Stop Button Pressed!");
}
