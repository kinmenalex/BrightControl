// MonConf.h : main header file for the MONCONF application
//

#if !defined(AFX_MONCONF_H__161FA936_0FBB_4BD4_8FB8_A562CE3545FA__INCLUDED_)
#define AFX_MONCONF_H__161FA936_0FBB_4BD4_8FB8_A562CE3545FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMonConfApp:
// See MonConf.cpp for the implementation of this class
//

class CMonConfApp : public CWinApp
{
public:
	CMonConfApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMonConfApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMonConfApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MONCONF_H__161FA936_0FBB_4BD4_8FB8_A562CE3545FA__INCLUDED_)
