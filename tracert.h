// tracert.h : main header file for the TRACERT application
//

#if !defined(AFX_TRACERT_H__E8DB8B5A_6800_4382_84E2_EEB303B5F403__INCLUDED_)
#define AFX_TRACERT_H__E8DB8B5A_6800_4382_84E2_EEB303B5F403__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTracertApp:
// See tracert.cpp for the implementation of this class
//

class CTracertApp : public CWinApp
{
public:
	CTracertApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTracertApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTracertApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRACERT_H__E8DB8B5A_6800_4382_84E2_EEB303B5F403__INCLUDED_)
