
// MFCApplication1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication1Dlg dialog



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCApplication1Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDB_TRIANGLE, m_TriangleHolder);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START, &CMFCApplication1Dlg::OnBnClickedStart)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CMFCApplication1Dlg message handlers

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}


// Moves the Player Dialog (triangle) on screen
void CMFCApplication1Dlg::MovePlayerDlg(int xChange, int yChange)
{
    CRect rect;
    CWnd *pWnd = this->GetDlgItem(IDB_TRIANGLE);
    pWnd->GetWindowRect(&rect);
    this->ScreenToClient(&rect);
    m_TriangleHolder.MoveWindow(rect.left + xChange, rect.top + yChange, rect.Width(), rect.Height());
}


// Starts game
void CMFCApplication1Dlg::OnBnClickedStart()
{
    // Set initial coordinates for Player
    CRect rect;
    CWnd *pWnd = this->GetDlgItem(IDB_TRIANGLE);
    pWnd->GetWindowRect(&rect);
    this->ScreenToClient(&rect);
    playerOne.SetCoordinates(rect.left, rect.top);

    SetTimer(1, 30, NULL);
}


// Timer where game events happen every tick
void CMFCApplication1Dlg::OnTimer(UINT_PTR nIDEvent)
{
    
    // Handle Player movement
    int xChange = 0, 
        yChange = 0;

    // Check which keys are down -> find which direction to move Player
    if (keysPressed[0] == true) // left
        xChange--;
    if (keysPressed[1] == true) // up
        yChange--;
    if (keysPressed[2] == true) // right
        xChange++;
    if (keysPressed[3] == true) // down
        yChange++;

    // Update Player coordinates + reflect this on dialog
    xChange = xChange * playerOne.multiplier;
    yChange = yChange * playerOne.multiplier;
    MovePlayerDlg(xChange, yChange);
    playerOne.Move(xChange, yChange);
    Point coord = playerOne.Coordinates();


    // Update UserPos Text Control with coordinates of Player
    // ### Only include for debugging ###
    CWnd *UserWnd = this->GetDlgItem(IDC_USERPOS);
    CString up;
    up.Format(_T("User Position: %d, %d"), coord.x, coord.y);
    SetDlgItemText(IDC_USERPOS, up);

	CDialogEx::OnTimer(nIDEvent);
}



/*
    Need to override PreTranslateMessage function to get key input
    - pMsg holds info on what type of ->message was called (WM_KEYDOWN, WM_KEYUP, etc)
    - pMsg also holds additional info through ->wParam (which key was pressed)
    - pMsg also has access to cursor location relative to screen through ->pt
*/
BOOL CMFCApplication1Dlg::PreTranslateMessage(MSG* pMsg)
{
    if (pMsg->message == WM_KEYDOWN) // Has a key been pressed? (->message == 256)
    {
        // Check for arrow keys, change keysPressed accordingly
        
        switch (pMsg->wParam)
        {
        case 37:    // kP[0] for left arrow
            keysPressed[0] = true;
            break;
        case 38:    // kP[1] for up arrow
            keysPressed[1] = true;
            break;
        case 39:    // kP[2] for right arrow
            keysPressed[2] = true;
            break;
        case 40:    // kP[3] for down arrow
            keysPressed[3] = true;
            break;
        }


        // Update KeyPress Text Control with pMsg info
        // ### Only include for debugging ###
        CWnd *UserWnd = this->GetDlgItem(IDC_KEYPRESS);
        CString lkp;
        lkp.Format(_T("Last Key Pressed: \n message: %d \n wParam: %d \n CursorCoord: %d, %d"),
            pMsg->message, pMsg->wParam, pMsg->pt.x, pMsg->pt.y);
        SetDlgItemText(IDC_KEYPRESS, lkp);
    }

    else if (pMsg->message == WM_KEYUP) // Has a key been released? (->message == 257)
    {
        // Check for arrow keys, update keysPressed accordingly
        switch (pMsg->wParam)
        {
        case 37:    // Timer 1 for left arrow
            keysPressed[0] = false;
            break;
        case 38:    // Timer 2 for up arrow
            keysPressed[1] = false;
            break;
        case 39:    // Timer 3 for right arrow
            keysPressed[2] = false;
            break;
        case 40:    // Timer 4 for down arrow
            keysPressed[3] = false;
            break;
        }


        // Update KeyPress Text Control with pMsg info
        // ### Only include for debugging ###
        CWnd *UserWnd = this->GetDlgItem(IDC_KEYPRESS);
        CString lkp;
        lkp.Format(_T("Last Key Pressed: \n message: %d \n wParam: %d \n CursorCoord: %d, %d"),
            pMsg->message, pMsg->wParam, pMsg->pt.x, pMsg->pt.y);
        SetDlgItemText(IDC_KEYPRESS, lkp);
    }

    return CDialog::PreTranslateMessage(pMsg);
}


