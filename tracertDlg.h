// tracertDlg.h : header file
//

#if !defined(AFX_TRACERTDLG_H__A23E5CBB_5FAD_4DDB_84AF_123BB6DE6676__INCLUDED_)
#define AFX_TRACERTDLG_H__A23E5CBB_5FAD_4DDB_84AF_123BB6DE6676__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTracertDlg dialog

class CTracertDlg : public CDialog
{
// Construction
public:
	int Ping();
	void Display(CString str);
	CTracertDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTracertDlg)
	enum { IDD = IDD_TRACERT_DIALOG };
	CEdit	m_ret;
	CString	m_ip;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTracertDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTracertDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void Ontracert();
	afx_msg void Onping();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRACERTDLG_H__A23E5CBB_5FAD_4DDB_84AF_123BB6DE6676__INCLUDED_)
