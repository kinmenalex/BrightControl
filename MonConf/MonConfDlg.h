// MonConfDlg.h : header file
//

#include "afxwin.h"
#include "afxcmn.h"
#if !defined(AFX_MONCONFDLG_H__B13073D3_2EF7_47A5_B2D2_58138B89F182__INCLUDED_)
#define AFX_MONCONFDLG_H__B13073D3_2EF7_47A5_B2D2_58138B89F182__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMonConfDlg dialog

class CMonConfDlg : public CDialog
{
	#define MAX_RETRY 5
	#define RETRY_SLEEP 100
	#define MAXBRI 6
	int cmdBri[MAXBRI+1];

// Construction
public:
	CMonConfDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMonConfDlg)
	enum { IDD = IDD_MONCONF_DIALOG };
	CEdit	edOutput;
	CEdit	edContrast;
	CEdit	edBrightness;
	CString stOutput;
	int dbg_printf(const char *fmt,...);
	long GetMonitorBright(HWND hWnd);
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMonConfDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMonConfDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonGet();
	afx_msg void OnButtonClear();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonSet();
	int SetMonitorBright(HWND hWnd , DWORD cBrightness);
	afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonBri0();
	afx_msg void OnBnClickedButtonBri1();
	afx_msg void OnBnClickedButtonBri2();
	afx_msg void OnBnClickedButtonBri3();
	afx_msg void OnBnClickedButtonBri4();
	afx_msg void OnBnClickedButtonBri5();
	afx_msg void OnBnClickedButtonBri6();
	CButton btnBri0;
	CButton btnBri1;
	CButton btnBri2;
	CButton btnBri3;
	CButton btnBri4;
	CButton btnBri5;
	CButton btnBri6;
	int QuickSetBright(int cBright);
	int GetMonitorContrastEx(HWND hWnd);
	void GetErrorMessage(LPTSTR lpszFunction);
	CSliderCtrl sliderBri;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	int SetWindowTitle(int cBri);
//	afx_msg void OnClose();
	afx_msg void OnClose();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MONCONFDLG_H__B13073D3_2EF7_47A5_B2D2_58138B89F182__INCLUDED_)
