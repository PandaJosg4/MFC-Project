
// MFCApplication1Dlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "Player.h"
#include <vector>


// CMFCApplication1Dlg dialog
class CMFCApplication1Dlg : public CDialogEx
{
// Construction
public:
	CMFCApplication1Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Key + Game Data
    bool keysPressed[4]; // left->up->right->down
    Player playerOne;
	std::vector<CStatic*> m_ProjHolders;


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
    virtual BOOL PreTranslateMessage(MSG * pMsg);
	CStatic m_TriangleHolder;
    afx_msg void OnBnClickedStart();

    // Created functions for Dialog
    void MovePlayerDlg(int xChange, int yChange);
	void CreateProjDlg();
};
