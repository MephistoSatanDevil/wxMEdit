///////////////////////////////////////////////////////////////////////////////
// Name:        wxm_find_in_files_dialog.cpp
// Description: find or replace in files dialog
// Author:      madedit@gmail.com  (creator)
//              wxmedit@gmail.com  (current maintainer)
// Licence:     GPL
///////////////////////////////////////////////////////////////////////////////

#include "wxm_find_in_files_dialog.h"
#include "wxm_searchreplace_dialog.h"

#include "../wxmedit_frame.h"
#include "../wxmedit/wxmedit.h"

#include <wx/progdlg.h>
#include <wx/dir.h>
#include <wx/tokenzr.h>
#include <wx/filename.h>

//(*InternalHeaders(WXMFindInFilesDialog)
#include <wx/intl.h>
#include <wx/string.h>
//*)


#ifdef _DEBUG
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK ,__FILE__, __LINE__)
#endif

#define static static const
#include "../../images/down.xpm"
#undef static

WXMFindInFilesDialog *g_FindInFilesDialog=NULL;

//(*IdInit(WXMFindInFilesDialog)
const long WXMFindInFilesDialog::ID_WXCHECKBOXCASESENSITIVE = wxNewId();
const long WXMFindInFilesDialog::ID_WXCHECKBOXWHOLEWORD = wxNewId();
const long WXMFindInFilesDialog::ID_WXCHECKBOXREGEX = wxNewId();
const long WXMFindInFilesDialog::ID_WXCHECKBOXFINDHEX = wxNewId();
const long WXMFindInFilesDialog::ID_WXCHECKBOXLISTFIRSTONLY = wxNewId();
const long WXMFindInFilesDialog::ID_WXBUTTONFIND = wxNewId();
const long WXMFindInFilesDialog::ID_WXBUTTONREPLACE = wxNewId();
const long WXMFindInFilesDialog::ID_WXCHECKBOXENABLEREPLACE = wxNewId();
const long WXMFindInFilesDialog::ID_STATICLINE1 = wxNewId();
const long WXMFindInFilesDialog::ID_WXRADIOBUTTONOPENEDFILES = wxNewId();
const long WXMFindInFilesDialog::ID_WXRADIOBUTTONDIR = wxNewId();
const long WXMFindInFilesDialog::ID_COMBOBOX1 = wxNewId();
const long WXMFindInFilesDialog::ID_WXBUTTONDIR = wxNewId();
const long WXMFindInFilesDialog::ID_WXBUTTONACTIVEDIR = wxNewId();
const long WXMFindInFilesDialog::ID_STATICTEXT1 = wxNewId();
const long WXMFindInFilesDialog::ID_WXCOMBOBOXFILTER = wxNewId();
const long WXMFindInFilesDialog::ID_STATICTEXT2 = wxNewId();
const long WXMFindInFilesDialog::ID_STATICTEXT3 = wxNewId();
const long WXMFindInFilesDialog::ID_STATICTEXT4 = wxNewId();
const long WXMFindInFilesDialog::ID_WXCOMBOBOXEXCLUDE = wxNewId();
const long WXMFindInFilesDialog::ID_STATICTEXT5 = wxNewId();
const long WXMFindInFilesDialog::ID_STATICTEXT6 = wxNewId();
const long WXMFindInFilesDialog::ID_STATICTEXT7 = wxNewId();
const long WXMFindInFilesDialog::ID_WXCOMBOBOXENCODING = wxNewId();
const long WXMFindInFilesDialog::ID_WXCHECKBOXSUBDIR = wxNewId();
//*)

const long WXMFindInFilesDialog::ID_MADEDIT1 = wxNewId();
const long WXMFindInFilesDialog::ID_MADEDIT2 = wxNewId();
const long WXMFindInFilesDialog::ID_WXBITMAPBUTTONRECENTFINDTEXT = wxNewId();
const long WXMFindInFilesDialog::ID_WXBITMAPBUTTONRECENTREPLACETEXT = wxNewId();

BEGIN_EVENT_TABLE(WXMFindInFilesDialog,wxDialog)
	//(*EventTable(WXMFindInFilesDialog)
	//*)
	EVT_ACTIVATE(WXMFindInFilesDialog::WXMFindInFilesDialogActivate)

	EVT_BUTTON(ID_WXBITMAPBUTTONRECENTFINDTEXT, WXMFindInFilesDialog::WxBitmapButtonRecentFindTextClick)
	EVT_BUTTON(ID_WXBITMAPBUTTONRECENTREPLACETEXT, WXMFindInFilesDialog::WxBitmapButtonRecentReplaceTextClick)
	EVT_MENU_RANGE(ID_RECENTFINDTEXT1, ID_RECENTFINDTEXT20, WXMFindInFilesDialog::OnRecentFindText)
	EVT_MENU_RANGE(ID_RECENTREPLACETEXT1, ID_RECENTREPLACETEXT20, WXMFindInFilesDialog::OnRecentReplaceText)
END_EVENT_TABLE()

WXMFindInFilesDialog::WXMFindInFilesDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(WXMFindInFilesDialog)
	wxBoxSizer* BoxSizer4;
	wxBoxSizer* BoxSizer6;
	wxBoxSizer* BoxSizer5;
	wxBoxSizer* BoxSizer7;
	wxBoxSizer* BoxSizer8;
	wxBoxSizer* BoxSizer2;
	wxBoxSizer* BoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;
	wxBoxSizer* BoxSizer3;

	Create(parent, wxID_ANY, _("Find/Replace In Files"), wxDefaultPosition, wxDefaultSize, wxCAPTION|wxSYSTEM_MENU|wxRESIZE_BORDER|wxCLOSE_BOX|wxDIALOG_NO_PARENT, _T("wxID_ANY"));
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	BoxSizer4 = new wxBoxSizer(wxVERTICAL);
	BoxSizer6 = new wxBoxSizer(wxHORIZONTAL);
	BoxSizer4->Add(BoxSizer6, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	BoxSizer7 = new wxBoxSizer(wxHORIZONTAL);
	BoxSizer4->Add(BoxSizer7, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	BoxSizer8 = new wxBoxSizer(wxVERTICAL);
	WxCheckBoxCaseSensitive = new wxCheckBox(this, ID_WXCHECKBOXCASESENSITIVE, _("&Case Sensitive"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_WXCHECKBOXCASESENSITIVE"));
	WxCheckBoxCaseSensitive->SetValue(false);
	BoxSizer8->Add(WxCheckBoxCaseSensitive, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 2);
	WxCheckBoxWholeWord = new wxCheckBox(this, ID_WXCHECKBOXWHOLEWORD, _("&Whole Word Only"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_WXCHECKBOXWHOLEWORD"));
	WxCheckBoxWholeWord->SetValue(false);
	BoxSizer8->Add(WxCheckBoxWholeWord, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 2);
	WxCheckBoxRegex = new wxCheckBox(this, ID_WXCHECKBOXREGEX, _("Use Regular E&xpressions"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_WXCHECKBOXREGEX"));
	WxCheckBoxRegex->SetValue(false);
	BoxSizer8->Add(WxCheckBoxRegex, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 2);
	WxCheckBoxFindHex = new wxCheckBox(this, ID_WXCHECKBOXFINDHEX, _("Find &Hex String (Example: BE 00 3A or BE003A)"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_WXCHECKBOXFINDHEX"));
	WxCheckBoxFindHex->SetValue(false);
	BoxSizer8->Add(WxCheckBoxFindHex, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 2);
	WxCheckBoxListFirstOnly = new wxCheckBox(this, ID_WXCHECKBOXLISTFIRSTONLY, _("&List the First Found Item Only"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_WXCHECKBOXLISTFIRSTONLY"));
	WxCheckBoxListFirstOnly->SetValue(false);
	BoxSizer8->Add(WxCheckBoxListFirstOnly, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 2);
	BoxSizer4->Add(BoxSizer8, 0, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 0);
	BoxSizer2->Add(BoxSizer4, 1, wxALL|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 0);
	BoxSizer5 = new wxBoxSizer(wxVERTICAL);
	WxButtonFind = new wxButton(this, ID_WXBUTTONFIND, _("&Find"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_WXBUTTONFIND"));
	BoxSizer5->Add(WxButtonFind, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	WxButtonReplace = new wxButton(this, ID_WXBUTTONREPLACE, _("&Replace"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_WXBUTTONREPLACE"));
	BoxSizer5->Add(WxButtonReplace, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	WxCheckBoxEnableReplace = new wxCheckBox(this, ID_WXCHECKBOXENABLEREPLACE, _("&Enable Replace"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_WXCHECKBOXENABLEREPLACE"));
	WxCheckBoxEnableReplace->SetValue(false);
	BoxSizer5->Add(WxCheckBoxEnableReplace, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	WxButtonClose = new wxButton(this, wxID_CANCEL, _("Close"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("wxID_CANCEL"));
	BoxSizer5->Add(WxButtonClose, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	BoxSizer2->Add(BoxSizer5, 0, wxALL|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 0);
	BoxSizer1->Add(BoxSizer2, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 0);
	StaticLine1 = new wxStaticLine(this, ID_STATICLINE1, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE1"));
	BoxSizer1->Add(StaticLine1, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	BoxSizer3 = new wxBoxSizer(wxVERTICAL);
	WxRadioButtonOpenedFiles = new wxRadioButton(this, ID_WXRADIOBUTTONOPENEDFILES, _("Opened Files in Editor"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_WXRADIOBUTTONOPENEDFILES"));
	BoxSizer3->Add(WxRadioButtonOpenedFiles, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 2);
	FlexGridSizer1 = new wxFlexGridSizer(0, 4, 0, 0);
	WxRadioButtonDir = new wxRadioButton(this, ID_WXRADIOBUTTONDIR, _("Selected Directory:"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_WXRADIOBUTTONDIR"));
	FlexGridSizer1->Add(WxRadioButtonDir, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 2);
	WxComboBoxDir = new wxComboBox(this, ID_COMBOBOX1, wxEmptyString, wxDefaultPosition, wxSize(330,-1), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX1"));
	FlexGridSizer1->Add(WxComboBoxDir, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 2);
	WxButtonDir = new wxButton(this, ID_WXBUTTONDIR, _("..."), wxDefaultPosition, wxSize(40,-1), 0, wxDefaultValidator, _T("ID_WXBUTTONDIR"));
	FlexGridSizer1->Add(WxButtonDir, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	WxButtonActiveDir = new wxButton(this, ID_WXBUTTONACTIVEDIR, _("<<"), wxDefaultPosition, wxSize(40,-1), 0, wxDefaultValidator, _T("ID_WXBUTTONACTIVEDIR"));
	FlexGridSizer1->Add(WxButtonActiveDir, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("File Filters:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer1->Add(StaticText1, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 2);
	WxComboBoxFilter = new wxComboBox(this, ID_WXCOMBOBOXFILTER, wxEmptyString, wxDefaultPosition, wxSize(330,-1), 0, 0, 0, wxDefaultValidator, _T("ID_WXCOMBOBOXFILTER"));
	FlexGridSizer1->Add(WxComboBoxFilter, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 2);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	FlexGridSizer1->Add(StaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 8);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	FlexGridSizer1->Add(StaticText3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Exclude Filters:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	FlexGridSizer1->Add(StaticText4, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 2);
	WxComboBoxExclude = new wxComboBox(this, ID_WXCOMBOBOXEXCLUDE, wxEmptyString, wxDefaultPosition, wxSize(330,-1), 0, 0, 0, wxDefaultValidator, _T("ID_WXCOMBOBOXEXCLUDE"));
	FlexGridSizer1->Add(WxComboBoxExclude, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 2);
	StaticText5 = new wxStaticText(this, ID_STATICTEXT5, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	FlexGridSizer1->Add(StaticText5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 8);
	StaticText6 = new wxStaticText(this, ID_STATICTEXT6, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
	FlexGridSizer1->Add(StaticText6, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	StaticText7 = new wxStaticText(this, ID_STATICTEXT7, _("File Encoding:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
	FlexGridSizer1->Add(StaticText7, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 2);
	WxComboBoxEncoding = new wxComboBox(this, ID_WXCOMBOBOXENCODING, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_WXCOMBOBOXENCODING"));
	FlexGridSizer1->Add(WxComboBoxEncoding, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 2);
	BoxSizer3->Add(FlexGridSizer1, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 0);
	WxCheckBoxSubDir = new wxCheckBox(this, ID_WXCHECKBOXSUBDIR, _("Include Subdirectories"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_WXCHECKBOXSUBDIR"));
	WxCheckBoxSubDir->SetValue(false);
	BoxSizer3->Add(WxCheckBoxSubDir, 0, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 2);
	BoxSizer1->Add(BoxSizer3, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 0);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);
	Center();

	Connect(ID_WXCHECKBOXFINDHEX,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&WXMFindInFilesDialog::WxCheckBoxFindHexClick);
	Connect(ID_WXBUTTONFIND,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&WXMFindInFilesDialog::WxButtonFindClick);
	Connect(ID_WXBUTTONREPLACE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&WXMFindInFilesDialog::WxButtonReplaceClick);
	Connect(ID_WXCHECKBOXENABLEREPLACE,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&WXMFindInFilesDialog::WxCheckBoxEnableReplaceClick);
	Connect(ID_WXBUTTONDIR,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&WXMFindInFilesDialog::WxButtonDirClick);
	Connect(ID_WXBUTTONACTIVEDIR,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&WXMFindInFilesDialog::WxButtonActiveDirClick);
	Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&WXMFindInFilesDialog::WXMFindInFilesDialogClose);
	//*)

	int bw, bh;
	// find
	WxButtonFind->GetSize(&bw, &bh);

	m_FindText=new MadEdit(this, ID_MADEDIT1, wxPoint(0, 0), wxSize(400, bh));
	m_FindText->SetSingleLineMode(true);
	m_FindText->SetEncoding(wxT("UTF-32LE"));
	m_FindText->SetFixedWidthMode(false);
	m_FindText->SetRecordCaretMovements(false);
	m_FindText->SetInsertSpacesInsteadOfTab(false);
	m_FindText->SetWantTab(false);
	m_FindText->LoadDefaultSyntaxScheme();

	BoxSizer6->Add(m_FindText,1,wxEXPAND|wxALIGN_LEFT | wxALL,2);
	BoxSizer6->SetItemMinSize(m_FindText, 400, bh);

	wxBitmap WxBitmapButtonRecentFindText_BITMAP (down_xpm);
	WxBitmapButtonRecentFindText = new wxBitmapButton(this, ID_WXBITMAPBUTTONRECENTFINDTEXT, WxBitmapButtonRecentFindText_BITMAP, wxPoint(0,0), wxSize(bh,bh), wxBU_AUTODRAW, wxDefaultValidator, _("WxBitmapButtonRecentFindText"));
	BoxSizer6->Add(WxBitmapButtonRecentFindText,0,wxALIGN_CENTER_HORIZONTAL | wxALL,2);

	// replace
	WxButtonReplace->GetSize(&bw, &bh);

	m_ReplaceText=new MadEdit(this, ID_MADEDIT2, wxPoint(0, 0), wxSize(400, bh));
	m_ReplaceText->SetSingleLineMode(true);
	m_ReplaceText->SetEncoding(wxT("UTF-32LE"));
	m_ReplaceText->SetFixedWidthMode(false);
	m_ReplaceText->SetRecordCaretMovements(false);
	m_ReplaceText->SetInsertSpacesInsteadOfTab(false);
	m_ReplaceText->SetWantTab(false);
	m_ReplaceText->LoadDefaultSyntaxScheme();

	BoxSizer7->Add(m_ReplaceText,1,wxEXPAND|wxALIGN_LEFT | wxALL,2);
	BoxSizer7->SetItemMinSize(m_ReplaceText, 400, bh);

	WxBitmapButtonRecentReplaceText = new wxBitmapButton(this, ID_WXBITMAPBUTTONRECENTREPLACETEXT, WxBitmapButtonRecentFindText_BITMAP, wxPoint(0,0), wxSize(bh,bh), wxBU_AUTODRAW, wxDefaultValidator, _("WxBitmapButtonRecentReplaceText"));
	BoxSizer7->Add(WxBitmapButtonRecentReplaceText,0,wxALIGN_CENTER_HORIZONTAL | wxALL,2);

	// build encoding list
	wxString systemenc(_("Automatic Detection"));
	WxComboBoxEncoding->Append(systemenc);
	size_t cnt=wxm::WXMEncodingCreator::Instance().GetEncodingsCount();
	for(size_t i=0;i<cnt;i++)
	{
		WxComboBoxEncoding->Append(wxm::WXMEncodingCreator::Instance().GetEncodingName(i));//enc+des);
	}
	WxComboBoxEncoding->SetValue(systemenc);

	//
	m_RecentFindDir = new wxRecentList();
	m_RecentFindFilter = new wxRecentList();
	m_RecentFindExclude = new wxRecentList();
	wxConfigBase *m_Config=wxConfigBase::Get(false);
	wxString oldpath=m_Config->GetPath();
	m_Config->SetPath(wxT("/RecentFindDir"));
	m_RecentFindDir->Load(*m_Config);
	m_Config->SetPath(wxT("/RecentFindFilter"));
	m_RecentFindFilter->Load(*m_Config);
	m_Config->SetPath(wxT("/RecentFindExcludeFilter"));
	m_RecentFindExclude->Load(*m_Config);
	m_Config->SetPath(oldpath);

	size_t count=m_RecentFindDir->GetCount();
	if(count>0)
	{
		wxString text=m_RecentFindDir->GetHistoryFile(0);
		WxComboBoxDir->SetValue(text);
		WxComboBoxDir->Append(text);
		for(size_t i=1; i<count; ++i) WxComboBoxDir->Append(m_RecentFindDir->GetHistoryFile(i));
	}
	count=m_RecentFindFilter->GetCount();
	if(count>0)
	{
		wxString text=m_RecentFindFilter->GetHistoryFile(0);
		WxComboBoxFilter->SetValue(text);
		WxComboBoxFilter->Append(text);
		for(size_t i=1; i<count; ++i) WxComboBoxFilter->Append(m_RecentFindFilter->GetHistoryFile(i));
	}
	count=m_RecentFindExclude->GetCount();
	if(count>0)
	{
		wxString text=m_RecentFindExclude->GetHistoryFile(0);
		//WxComboBoxExclude->SetValue(text);
		WxComboBoxExclude->Append(text);
		for(size_t i=1; i<count; ++i) WxComboBoxExclude->Append(m_RecentFindExclude->GetHistoryFile(i));
	}

	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);
	Center();

	//
	if(g_SearchReplaceDialog->m_RecentFindText->GetCount()>0)
	{
		m_FindText->SetText(g_SearchReplaceDialog->m_RecentFindText->GetHistoryFile(0));
	}
	if(g_SearchReplaceDialog->m_RecentReplaceText->GetCount()>0)
	{
		m_ReplaceText->SetText(g_SearchReplaceDialog->m_RecentReplaceText->GetHistoryFile(0));
	}

	WxButtonClose->SetFocus();
}

WXMFindInFilesDialog::~WXMFindInFilesDialog()
{
	//(*Destroy(WXMFindInFilesDialog)
	//*)
}

void WXMFindInFilesDialog::WXMFindInFilesDialogClose(wxCloseEvent& event)
{
	if(event.CanVeto())
	{
		event.Veto();
		Show(false);
		return;
	}

	g_FindInFilesDialog=NULL;
	Destroy();
}

void WXMFindInFilesDialog::UpdateCheckBoxByCBHex(bool check)
{
	if(check)
	{
		WxCheckBoxCaseSensitive->Disable();
		WxCheckBoxWholeWord->Disable();
		WxCheckBoxRegex->Disable();
	}
	else
	{
		WxCheckBoxCaseSensitive->Enable();
		WxCheckBoxWholeWord->Enable();
		WxCheckBoxRegex->Enable();
	}
}

void WXMFindInFilesDialog::WxBitmapButtonRecentFindTextClick(wxCommandEvent& event)
{
	PopupMenu(&g_SearchReplaceDialog->WxPopupMenuRecentFindText);
}

void WXMFindInFilesDialog::WxBitmapButtonRecentReplaceTextClick(wxCommandEvent& event)
{
	PopupMenu(&g_SearchReplaceDialog->WxPopupMenuRecentReplaceText);
}

void WXMFindInFilesDialog::OnRecentFindText(wxCommandEvent& event)
{
	int idx=event.GetId()-ID_RECENTFINDTEXT1;
	wxString text=g_SearchReplaceDialog->m_RecentFindText->GetHistoryFile(idx);
	if(!text.IsEmpty())
	{
		m_FindText->SetText(text);
		m_FindText->SetFocus();
	}
}

void WXMFindInFilesDialog::OnRecentReplaceText(wxCommandEvent& event)
{
	int idx=event.GetId()-ID_RECENTREPLACETEXT1;
	wxString text=g_SearchReplaceDialog->m_RecentReplaceText->GetHistoryFile(idx);
	if(!text.IsEmpty())
	{
		m_ReplaceText->SetText(text);
		m_ReplaceText->SetFocus();
	}
}

void WXMFindInFilesDialog::WxCheckBoxFindHexClick(wxCommandEvent& event)
{
	UpdateCheckBoxByCBHex(event.IsChecked());
}

void WXMFindInFilesDialog::WxButtonFindClick(wxCommandEvent& event)
{
	wxString text;
	m_FindText->GetText(text);
	if(!text.IsEmpty())
	{
		g_SearchReplaceDialog->m_RecentFindText->AddItemToHistory(text);
		FindReplaceInFiles(false);
	}
}

void WXMFindInFilesDialog::WxButtonReplaceClick(wxCommandEvent& event)
{
	wxString text, text2;
	m_FindText->GetText(text);
	m_ReplaceText->GetText(text2);
	if(!text.IsEmpty())
	{
		g_SearchReplaceDialog->m_RecentFindText->AddItemToHistory(text);
		if(!text2.IsEmpty())
		{
			g_SearchReplaceDialog->m_RecentReplaceText->AddItemToHistory(text2);
		}
		FindReplaceInFiles(true);
	}
}

void WXMFindInFilesDialog::WxButtonDirClick(wxCommandEvent& event)
{
	wxString defdir=WxComboBoxDir->GetValue();
	if(defdir.IsEmpty()) defdir=wxGetCwd();
	wxDirDialog dlg(this, _("Choose a directory"), defdir);
	if(dlg.ShowModal()==wxID_OK)
	{
		WxComboBoxDir->SetValue(dlg.GetPath());
	}
}

void WXMFindInFilesDialog::WXMFindInFilesDialogActivate(wxActivateEvent& event)
{
	wxConfigBase *m_Config=wxConfigBase::Get(false);
	wxString oldpath=m_Config->GetPath();

	if(event.GetActive())
	{
		WxButtonReplace->Disable();
		WxCheckBoxEnableReplace->SetValue(false);

		bool bb;
		m_Config->Read(wxT("/wxMEdit/SearchCaseSensitive"), &bb, false);
		WxCheckBoxCaseSensitive->SetValue(bb);

		m_Config->Read(wxT("/wxMEdit/SearchWholeWord"), &bb, false);
		WxCheckBoxWholeWord->SetValue(bb);

		m_Config->Read(wxT("/wxMEdit/SearchRegex"), &bb, false);
		WxCheckBoxRegex->SetValue(bb);

		m_Config->Read(wxT("/wxMEdit/SearchHex"), &bb, false);
		WxCheckBoxFindHex->SetValue(bb);
		UpdateCheckBoxByCBHex(bb);

		m_Config->Read(wxT("/wxMEdit/SearchListFileOnly"), &bb, false);
		WxCheckBoxListFirstOnly->SetValue(bb);

		m_Config->Read(wxT("/wxMEdit/FindListFileOnly"), &bb, false);
		WxCheckBoxListFirstOnly->SetValue(bb);

		m_Config->Read(wxT("/wxMEdit/FindOpenedFiles"), &bb, true);
		WxRadioButtonOpenedFiles->SetValue(bb);

		m_Config->Read(wxT("/wxMEdit/FindDir"), &bb, false);
		WxRadioButtonDir->SetValue(bb);

		m_Config->Read(wxT("/wxMEdit/FindSubDir"), &bb, true);
		WxCheckBoxSubDir->SetValue(bb);
	}
	else
	{
		m_Config->Write(wxT("/wxMEdit/SearchCaseSensitive"), WxCheckBoxCaseSensitive->GetValue());
		m_Config->Write(wxT("/wxMEdit/SearchWholeWord"), WxCheckBoxWholeWord->GetValue());
		m_Config->Write(wxT("/wxMEdit/SearchRegex"), WxCheckBoxRegex->GetValue());
		m_Config->Write(wxT("/wxMEdit/SearchHex"), WxCheckBoxFindHex->GetValue());
		m_Config->Write(wxT("/wxMEdit/FindListFileOnly"), WxCheckBoxListFirstOnly->GetValue());
		m_Config->Write(wxT("/wxMEdit/FindOpenedFiles"), WxRadioButtonOpenedFiles->GetValue());
		m_Config->Write(wxT("/wxMEdit/FindDir"), WxRadioButtonDir->GetValue());
		m_Config->Write(wxT("/wxMEdit/FindSubDir"), WxCheckBoxSubDir->GetValue());
	}

	m_Config->SetPath(oldpath);
}

//=========================================================

wxProgressDialog *g_ProgressDialog=NULL;
bool g_Continue;
wxLongLong g_Time;

wxString fmtmsg1;

WX_DECLARE_HASH_SET( wxString, wxStringHash, wxStringEqual, MadFileNameList );
MadFileNameList g_FileNameList; // the filenames matched the filename filter

vector<wxString> g_ExcludeFilters;

class DirTraverser : public wxDirTraverser
{
public:
	wxDirTraverseResult Continue()
	{
		wxLongLong t=wxGetLocalTimeMillis();
		wxLongLong delta=t-g_Time;
		if(delta.ToLong()>=350)
		{
			g_Time=t;
			g_Continue=g_ProgressDialog->Update(0, wxString::Format(fmtmsg1, g_FileNameList.size()));
			if(!g_Continue) return wxDIR_STOP;
		}
		return wxDIR_CONTINUE;
	}
	virtual wxDirTraverseResult OnFile(const wxString& filename)
	{
		bool exclude=false;
		if(!g_ExcludeFilters.empty())
		{
			wxFileName fn;
			size_t count=g_ExcludeFilters.size();
			for(size_t i=0; i<count; i++)
			{
				fn.Assign(filename);
#ifdef __WXMSW__
				if(fn.GetFullName().Lower().Matches(g_ExcludeFilters[i].c_str()))
#else
				if(fn.GetFullName().Matches(g_ExcludeFilters[i].c_str()))
#endif
				{
					exclude=true;
					break;
				}
			}
		}
		if(!exclude && g_FileNameList.find(filename) == g_FileNameList.end())
		{
			g_FileNameList.insert(filename);
		}
		return Continue();
	}
	virtual wxDirTraverseResult OnDir(const wxString& WXUNUSED(dirname))
	{
		return Continue();
	}
};

class CaretPosData: public wxClientData
{
public:
	wxString filename;
	int pageid; // >=0 for 'NoName'
	wxFileOffset bpos, epos;
	CaretPosData(const wxString &fn, int pid, const wxFileOffset &b, wxFileOffset &e)
		: filename(fn), pageid(pid), bpos(b), epos(e) {}
};

void WXMFindInFilesDialog::FindReplaceInFiles(bool bReplace)
{
	//wxLogNull nolog;

#ifdef SHOW_RESULT_COUNT
	int ResultCount=0;
#endif

	const int max=1000;
	fmtmsg1 = _("Found %d file(s) matched the filters...");
	fmtmsg1 += wxT("                                        \n");
	wxProgressDialog dialog(this->GetTitle(),
				wxString::Format(fmtmsg1, 0),
				max,    // range
				this,   // parent
				wxPD_CAN_ABORT |
				wxPD_AUTO_HIDE |
				wxPD_APP_MODAL);
	g_ProgressDialog=&dialog;

	g_MainFrame->ResetFindInFilesResults();
	g_MainFrame->m_AuiManager.GetPane(g_MainFrame->m_InfoNotebook).Show();
	g_MainFrame->m_AuiManager.Update();

	g_Continue=true;
	g_Time=wxGetLocalTimeMillis();

	size_t totalfiles;
	if(WxRadioButtonOpenedFiles->GetValue())
	{
		totalfiles= ((wxAuiNotebook*)g_MainFrame->m_Notebook)->GetPageCount();
	}
	else
	{
		// test the existence of the dir
		wxString str=WxComboBoxDir->GetValue();
		if(!wxDirExists(str))
		{
			dialog.Update(max);
			wxMessageBox(_("The selected directory does not exist."), wxT("wxMEdit"), wxOK|wxICON_ERROR);
			return;
		}
		m_RecentFindDir->AddItemToHistory(str);
		if(WxComboBoxDir->GetCount()==0 || WxComboBoxDir->GetString(0)!=str)
		{
			WxComboBoxDir->Insert(str, 0);
		}
		
		// get the filename filters
		str=WxComboBoxFilter->GetValue();
		str.Trim(true);
		str.Trim(false);
		wxStringTokenizer tkz(str, wxT(" \t;"));
		vector<wxString> filters;
		wxString tok;
		for(;;)
		{
			tok=tkz.GetNextToken();
			if(tok.IsEmpty()) break;
			filters.push_back(tok);
		}
		if(!filters.empty())
		{
			m_RecentFindFilter->AddItemToHistory(str);
			if(WxComboBoxFilter->GetCount()==0 || WxComboBoxFilter->GetString(0)!=str)
			{
				WxComboBoxFilter->Insert(str, 0);
			}
		}
		str=WxComboBoxExclude->GetValue();
		str.Trim(true);
		str.Trim(false);
		wxStringTokenizer tkz2(str, wxT(" \t;"));
		g_ExcludeFilters.clear();
		for(;;)
		{
			tok=tkz2.GetNextToken();
			if(tok.IsEmpty()) break;
#ifdef __WXMSW__
			tok.MakeLower();
#endif
			g_ExcludeFilters.push_back(tok);
		}
		if(!g_ExcludeFilters.empty())
		{
			m_RecentFindExclude->AddItemToHistory(str);
			if(WxComboBoxExclude->GetCount()==0 || WxComboBoxExclude->GetString(0)!=str)
			{
				WxComboBoxExclude->Insert(str, 0);
			}
		}

		// get the files matched the filters
		g_FileNameList.clear();

		DirTraverser traverser;
		wxDir dir(WxComboBoxDir->GetValue());
		int flags=wxDIR_FILES|wxDIR_HIDDEN;
		if(WxCheckBoxSubDir->GetValue()) flags|=wxDIR_DIRS;

		if(filters.empty())
		{
			dir.Traverse(traverser, wxEmptyString, flags);
		}
		else
		{
			for(size_t i=0; i<filters.size(); i++)
			{
				dir.Traverse(traverser, filters[i], flags);
			}
		}
		
		totalfiles=g_FileNameList.size();
	}

	if(g_Continue)
	{
		MadEdit *madedit, *tempedit=NULL;
		if(WxRadioButtonDir->GetValue())
		{
			madedit=tempedit=new MadEdit(this, -1, wxPoint(-1024,-1024));
			tempedit->StopRepaint();
			tempedit->SetStorePropertiesToGlobalConfig(false);
			tempedit->SetFixedWidthMode(false);
			tempedit->SetWordWrapMode(wwmNoWrap);
			tempedit->SetSearchOptions(true, WxCheckBoxWholeWord->GetValue());
		}

		wxString fmt(_("Processing %d of %d files..."));
		vector<wxFileOffset> begpos, endpos;
		MadFileNameList::iterator fnit=g_FileNameList.begin();
		bool cont = true;
		for(size_t i = 0; i < totalfiles && cont; i++)
		{
			// prepare madedit
			if(WxRadioButtonOpenedFiles->GetValue())
			{
				madedit=(MadEdit*) ((wxAuiNotebook*)g_MainFrame->m_Notebook)->GetPage(i);
			}
			else
			{
				int id;
				madedit=g_MainFrame->GetEditByFileName(*fnit, id);

				if(madedit==NULL)
				{
					madedit=tempedit;
					wxString enc=WxComboBoxEncoding->GetValue();
					if(enc==WxComboBoxEncoding->GetString(0))
					{
						enc.Clear();
					}
					madedit->LoadFromFile(*fnit, enc);
				}
				++fnit;
			}

			wxLongLong t=wxGetLocalTimeMillis();
			wxLongLong delta=t-g_Time;
			if(delta.ToLong()>=350)
			{
				g_Time=t;
				int idx = int(i*max / totalfiles);
				wxString str=wxString::Format(fmt, i, totalfiles);
				wxString fn=madedit->GetFileName();
				if(!fn.IsEmpty())
				{
					str+= wxT('\n');
					str+=fn;
				}
				cont = dialog.Update(idx, str);
				if(!cont) break;
			}

			// get all matched data in madedit
			begpos.clear();
			endpos.clear();
			wxString expr, fmt;
			int ok;
			if(bReplace)
			{
				m_FindText->GetText(expr);
				m_ReplaceText->GetText(fmt);
				if(WxCheckBoxFindHex->GetValue())
				{
					ok = madedit->ReplaceHexAll(expr, fmt, &begpos, &endpos);
				}
				else
				{
					ok = madedit->ReplaceTextAll(expr, fmt, 
						WxCheckBoxRegex->GetValue(),
						WxCheckBoxCaseSensitive->GetValue(),
						WxCheckBoxWholeWord->GetValue(), 
						&begpos, &endpos);
				}

				if(ok<0) break;

				expr=madedit->GetFileName();
				int id = ((wxAuiNotebook*)g_MainFrame->m_Notebook)->GetPageIndex(madedit);
				if(madedit->IsModified() && !expr.IsEmpty() && id<0)
				{
					madedit->SaveToFile(expr);
				}
			}
			else
			{
				m_FindText->GetText(expr);
				if(WxCheckBoxFindHex->GetValue())
				{
					ok = madedit->FindHexAll(expr, WxCheckBoxListFirstOnly->GetValue(),
						&begpos, &endpos);
				}
				else
				{
					ok = madedit->FindTextAll(expr,
						WxCheckBoxRegex->GetValue(),
						WxCheckBoxCaseSensitive->GetValue(),
						WxCheckBoxWholeWord->GetValue(),
						WxCheckBoxListFirstOnly->GetValue(),
						&begpos, &endpos);
				}

				if(ok<0) break;
			}

			if(begpos.size()>0) // found data
			{
				int pid=-1;
				expr=madedit->GetFileName();
				if(expr.IsEmpty())
				{
					pid=((wxAuiNotebook*)g_MainFrame->m_Notebook)->GetPageIndex(madedit);
					if(pid>=0)
					{
						expr=((wxAuiNotebook*)g_MainFrame->m_Notebook)->GetPageText(pid);
						if(expr[expr.Len()-1]==wxT('*'))
							expr.Truncate(expr.Len()-1);
					}
				}
				if(!expr.IsEmpty())
				{
					size_t count=begpos.size(), idx=0;
					if(WxCheckBoxListFirstOnly->GetValue()) count=1;
					int line=-1, oldline;
					wxString linetext, loc;
					g_MainFrame->m_FindInFilesResults->Freeze();
					do
					{
						if(madedit->IsTextFile())
						{
							oldline=line;
							line=madedit->GetLineByPos(begpos[idx]);
							if(line!=oldline)
							{
								linetext.Empty();
								madedit->GetLine(linetext, line, 512);
							}
							loc.Printf(_("Line(%d): "), line+1);
						}
						else
						{
							loc.Printf(_("Offset(%s): "), wxLongLong(begpos[idx]).ToString().c_str());
							linetext = _("Binary file matches");
						}

						fmt = loc +linetext;
						g_MainFrame->AddItemToFindInFilesResults(fmt, idx, expr, pid, begpos[idx], endpos[idx]);
#ifdef SHOW_RESULT_COUNT
						++ResultCount;
#endif
					}
					while(++idx < count);
					g_MainFrame->m_FindInFilesResults->Thaw();
				}
			}
		}
		
		if(tempedit) delete tempedit;
	}

	dialog.Update(max);
	g_ProgressDialog=NULL;
	g_FileNameList.clear();

#ifdef SHOW_RESULT_COUNT
	wxString smsg;
	smsg.Printf(_("%d results"), ResultCount);
	wxMessageBox(smsg.c_str(), wxT("wxMEdit"), wxOK);
#endif
}

void WXMFindInFilesDialog::WxCheckBoxEnableReplaceClick(wxCommandEvent& event)
{
	WxButtonReplace->Enable(event.IsChecked());
}

void WXMFindInFilesDialog::WxButtonActiveDirClick(wxCommandEvent& event)
{
	extern MadEdit *g_ActiveMadEdit;
	if(g_ActiveMadEdit!=NULL)
	{
		wxString str=g_ActiveMadEdit->GetFileName();
		if(!str.IsEmpty())
		{
			wxFileName fn(str);
			WxComboBoxDir->SetValue(fn.GetPath(wxPATH_GET_VOLUME|wxPATH_GET_SEPARATOR));
		}
	}
}