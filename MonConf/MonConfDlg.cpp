// MonConfDlg.cpp : implementation file
//

#include "stdafx.h"
#include"targetver.h"
#include<Windows.h>
#include<HighLevelMonitorConfigurationAPI.h>
#include<PhysicalMonitorEnumerationAPI.h>
#include "MonConf.h"
#include "MonConfDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define Product_str "BrightControl"
#define Version_str "0.38"
const char * BrightControlTitle_str = Product_str " " Version_str;

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CString str;
	str.Format("%s version %s", Product_str,Version_str);
	SetDlgItemText(IDC_VERSION,str);
	
	return TRUE;  
}

/////////////////////////////////////////////////////////////////////////////
// CMonConfDlg dialog

CMonConfDlg::CMonConfDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMonConfDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMonConfDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMonConfDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMonConfDlg)
	DDX_Control(pDX, IDC_EDIT_OUTPUT, edOutput);
	DDX_Control(pDX, IDC_EDIT_CONTRAST, edContrast);
	DDX_Control(pDX, IDC_EDIT_BRIGHTNESS, edBrightness);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_BUTTON_BRI0, btnBri0);
	DDX_Control(pDX, IDC_BUTTON_BRI1, btnBri1);
	DDX_Control(pDX, IDC_BUTTON_BRI2, btnBri2);
	DDX_Control(pDX, IDC_BUTTON_BRI3, btnBri3);
	DDX_Control(pDX, IDC_BUTTON_BRI4, btnBri4);
	DDX_Control(pDX, IDC_BUTTON_BRI5, btnBri5);
	DDX_Control(pDX, IDC_BUTTON_BRI6, btnBri6);
	DDX_Control(pDX, IDC_SLIDER_BRI, sliderBri);
}

BEGIN_MESSAGE_MAP(CMonConfDlg, CDialog)
	//{{AFX_MSG_MAP(CMonConfDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_GET, OnButtonGet)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, OnButtonClear)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_SET, &CMonConfDlg::OnBnClickedButtonSet)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CMonConfDlg::OnNMCustomdrawSlider1)
	ON_BN_CLICKED(IDC_BUTTON_BRI0, &CMonConfDlg::OnBnClickedButtonBri0)
	ON_BN_CLICKED(IDC_BUTTON_BRI1, &CMonConfDlg::OnBnClickedButtonBri1)
	ON_BN_CLICKED(IDC_BUTTON_BRI2, &CMonConfDlg::OnBnClickedButtonBri2)
	ON_BN_CLICKED(IDC_BUTTON_BRI3, &CMonConfDlg::OnBnClickedButtonBri3)
	ON_BN_CLICKED(IDC_BUTTON_BRI4, &CMonConfDlg::OnBnClickedButtonBri4)
	ON_BN_CLICKED(IDC_BUTTON_BRI5, &CMonConfDlg::OnBnClickedButtonBri5)
	ON_BN_CLICKED(IDC_BUTTON_BRI6, &CMonConfDlg::OnBnClickedButtonBri6)
//	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_BRI, &CMonConfDlg::OnNMCustomdrawSliderBri)
ON_WM_HSCROLL()
//ON_WM_CLOSE()
ON_WM_CLOSE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMonConfDlg message handlers
//TCHAR currName[MAX_PATH];
TCHAR path[MAX_PATH];    // image path
//TCHAR appPath[MAX_PATH];

void copyQuotStr(TCHAR * dest,TCHAR * src,TCHAR det, TCHAR **nextStr=NULL)
{
	TCHAR c=*src;
	while(c && c!=det)
	{
		if( c == TEXT('"') )
		{
			c = * ++src;
			while( c && c != TEXT('"') )
			{
				*dest++ = c;
				c = * ++src;
			}
		}
		else
			*dest++ = c;
		c = * ++src;
	}
	*dest = 0;
	
    if( nextStr )
   	{
		*nextStr = src + 1;
   	}
}

BOOL CMonConfDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
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
	SetWindowText(BrightControlTitle_str);


	LPTSTR p, nextStr;
	p = GetCommandLine();
	int i, n, nBri;

	copyQuotStr(path,p,TEXT(' '), &nextStr);

	p = nextStr;

	cmdBri[0] = -1;
	cmdBri[1] = 15;
	cmdBri[2] = 20;
	cmdBri[3] = 30;
	cmdBri[4] = 40;
	cmdBri[5] = 50;
	cmdBri[6] = 80;

	nBri = 0;
	while(*p) {
		while(*p && *p != TEXT('/') ) p++;

		if( p[1] == TEXT('b') || p[1] == TEXT('B'))			// "/b1=0 /b2=10 /b3=30 /b4=50 /b5=70 /b6=100"
		{
			i = atoi(p+2);
			p+=3;

			while(*p && *p != TEXT('=') ) p++;

			n = atoi(p+1);
			if( i>= 0 && i <= MAXBRI) {
				cmdBri[i] = n;
				nBri++;
			}
			p+=2;
		}
		p++;
	}

	if( cmdBri[0] != -1 && nBri == 1)
	{
		SetMonitorBright(this->m_hWnd,cmdBri[0]);
		OnOK();			// return 
	}
	else {
		// Restoring the window placement
		WINDOWPLACEMENT *lwp;
		UINT nl;

		if(AfxGetApp()->GetProfileBinary("BrightControl", "WinPos", (LPBYTE*)&lwp, &nl))
		{
			SetWindowPlacement(lwp);
			delete [] lwp;
		}
		//
		if (cmdBri[0] < 0) { cmdBri[0] = 0; }
		CString str;
		str.Format(_T("%d%%"), cmdBri[0]);
		btnBri0.SetWindowText(str);
		str.Format(_T("%d%%"), cmdBri[1]);
		btnBri1.SetWindowText(str);
		str.Format(_T("%d%%"), cmdBri[2]);
		btnBri2.SetWindowText(str);
		str.Format(_T("%d%%"), cmdBri[3]);
		btnBri3.SetWindowText(str);
		str.Format(_T("%d%%"), cmdBri[4]);
		btnBri4.SetWindowText(str);
		str.Format(_T("%d%%"), cmdBri[5]);
		btnBri5.SetWindowText(str);
		str.Format(_T("%d%%"), cmdBri[6]);
		btnBri6.SetWindowText(str);

		dbg_printf(_T("用使方法：\r\r\n"));

		dbg_printf(_T("1. 設定常用亮度：建立捷徑後加上參數\r\r\n"));
		dbg_printf(_T("Ex: BrightControl.exe /b0=%d /b1=%d /b2=%d /b3=%d /b4=%d /b5=%d /b6=%d\r\r\n"),
				   cmdBri[0], cmdBri[1], cmdBri[2], cmdBri[3], cmdBri[3], cmdBri[5], cmdBri[6]);
		dbg_printf(_T("2. 直接設定亮度後離開：建立捷徑後加上參數 /b0=亮度\r\r\nEx: BrightControl.exe /b0=50\r\r\n"));

		OnButtonGet();
	}
	

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMonConfDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMonConfDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMonConfDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}



int CMonConfDlg::dbg_printf(const char *fmt,...)
{
	va_list args;
	int len;
	char buf[1024];
	
	va_start(args,fmt);
	len = vsprintf_s(buf,sizeof(buf), fmt, args);
	va_end(args);


	int nLine = edOutput.GetLineCount();
	if( nLine < 200) {
		stOutput += buf;
	}
	else {
		stOutput = buf;
	}
	edOutput.SetWindowText(stOutput);
	edOutput.LineScroll(edOutput.GetLineCount());

	return len;
}



long CMonConfDlg::GetMonitorBright(HWND hWnd)
{
	HMONITOR hMonitor = NULL;
	DWORD cPhysicalMonitors;
	DWORD minb=0;
	DWORD curb=-1;
	DWORD maxb=0;
	LPPHYSICAL_MONITOR pPhysicalMonitors = NULL;
	// Get the monitor handle.
	hMonitor = MonitorFromWindow(hWnd, MONITOR_DEFAULTTOPRIMARY);

	//dbg_printf("MonitorFromWindow, hMonitor = 0x%x\r\r\n", hMonitor);

	// Get the number of physical monitors.
	BOOL bSuccess = GetNumberOfPhysicalMonitorsFromHMONITOR(
		hMonitor, &cPhysicalMonitors);

	//dbg_printf("GetNumberOfPhysicalMonitorsFromHMONITOR, bSuccess = %d\r\r\n", bSuccess);
	if (bSuccess)
	{
	//dbg_printf("MonitorFromWindow, cPhysicalMonitors = 0x%x\r\r\n", cPhysicalMonitors);


		// Allocate the array of PHYSICAL_MONITOR structures.
		pPhysicalMonitors = (LPPHYSICAL_MONITOR)malloc(
			cPhysicalMonitors* sizeof(PHYSICAL_MONITOR));
		if (pPhysicalMonitors != NULL)
		{
			// Get the array.
			bSuccess = GetPhysicalMonitorsFromHMONITOR(hMonitor, cPhysicalMonitors, pPhysicalMonitors);
			// Use the monitor handles (not shown).
			//dbg_printf("GetPhysicalMonitorsFromHMONITOR, bSuccess = %d\r\r\n", bSuccess);

			int n = 0;
			do {
				bSuccess = GetMonitorBrightness(pPhysicalMonitors->hPhysicalMonitor , &minb, &curb, &maxb);
				if( !bSuccess ) {
					dbg_printf("GetMonitorBrightness, n = %d, bSuccess = %d\r\r\n", n, bSuccess);
			        GetErrorMessage(TEXT("GetMonitorBrightness"));
					Sleep(RETRY_SLEEP);
				}
				n++;
			} while( !bSuccess && n < MAX_RETRY);
			

			if( bSuccess ) {
				dbg_printf("GetMonitorBrightness, bSuccess = %d\r\r\n", bSuccess);
				dbg_printf("minb = %d, curb=%d, maxb=%d\r\r\n", minb, curb, maxb);
				sliderBri.SetRange(minb,maxb,FALSE);
				sliderBri.SetPos(curb);
				SetWindowTitle(curb);
			}

			// Close the monitor handles.
	        bSuccess = DestroyPhysicalMonitors( cPhysicalMonitors, pPhysicalMonitors);

			// Free the array.
			free(pPhysicalMonitors);
		}
	}
	return curb;
}

int CMonConfDlg::GetMonitorContrastEx(HWND hWnd)
{
	HMONITOR hMonitor = NULL;
	DWORD cPhysicalMonitors;
	DWORD minc=0;
	DWORD curc=0;
	DWORD maxc=0;
	LPPHYSICAL_MONITOR pPhysicalMonitors = NULL;
	// Get the monitor handle.
	hMonitor = MonitorFromWindow(hWnd, MONITOR_DEFAULTTOPRIMARY);

	// Get the number of physical monitors.
	BOOL bSuccess = GetNumberOfPhysicalMonitorsFromHMONITOR(
		hMonitor, &cPhysicalMonitors);

	if (bSuccess)
	{
		// Allocate the array of PHYSICAL_MONITOR structures.
		pPhysicalMonitors = (LPPHYSICAL_MONITOR)malloc(
					cPhysicalMonitors* sizeof(PHYSICAL_MONITOR));
		if (pPhysicalMonitors != NULL)
		{
			// Get the array.
			bSuccess = GetPhysicalMonitorsFromHMONITOR(hMonitor, cPhysicalMonitors, pPhysicalMonitors);

			int n = 0;
			do {
				bSuccess = GetMonitorContrast(pPhysicalMonitors->hPhysicalMonitor , &minc, &curc, &maxc);
				if( !bSuccess ) {
					dbg_printf("GetMonitorContrast, n = %d, bSuccess = %d\r\r\n", n, bSuccess);
			        GetErrorMessage(TEXT("GetMonitorContrast"));
					Sleep(RETRY_SLEEP);
				}
				n++;
			} while( !bSuccess && n < MAX_RETRY);

			//dbg_printf("GetMonitorContrast, bSuccess = %d\r\r\n", bSuccess);
			if( bSuccess ) {
				    dbg_printf("GetMonitorContrast, bSuccess = %d\r\r\n", bSuccess);
				    dbg_printf("minc = %d, curc=%d, maxc=%d\r\r\n", minc, curc, maxc);
			}

			// Close the monitor handles.
	        bSuccess = DestroyPhysicalMonitors( cPhysicalMonitors, pPhysicalMonitors);
	
			// Free the array.
			free(pPhysicalMonitors);
		}
	}
	return curc;
}



void CMonConfDlg::OnButtonGet() 
{
	// TODO: Add your control notification handler code here
	char buf[256];
	int curBrightness = 0;
	int curContrast = 0;

	curBrightness = GetMonitorBright(this->m_hWnd);

	if( curBrightness >= 0 ) {
		_itoa_s(curBrightness,buf,sizeof(buf),10);
		edBrightness.SetWindowText(buf);
	}
/*
	curContrast = GetMonitorContrastEx(this->m_hWnd);

	if( curContrast >= 0 ) {
		_itoa_s(curContrast,buf,sizeof(buf),10);
		edContrast.SetWindowText(buf);
	}
*/
}

void CMonConfDlg::OnButtonClear() 
{
	stOutput = "";
	edOutput.SetWindowText(stOutput);
}


int CMonConfDlg::SetMonitorBright(HWND hWnd , DWORD cBrightness)
{
	HMONITOR hMonitor = NULL;
	DWORD cPhysicalMonitors;
	DWORD minb=0;
	DWORD curb=0;
	DWORD maxb=0;
	LPPHYSICAL_MONITOR pPhysicalMonitors = NULL;
	// Get the monitor handle.
	hMonitor = MonitorFromWindow(hWnd, MONITOR_DEFAULTTOPRIMARY);

	// Get the number of physical monitors.
	BOOL bSuccess = GetNumberOfPhysicalMonitorsFromHMONITOR(
		hMonitor, &cPhysicalMonitors);

	if (bSuccess)
	{
		// Allocate the array of PHYSICAL_MONITOR structures.
		pPhysicalMonitors = (LPPHYSICAL_MONITOR)malloc(
			cPhysicalMonitors* sizeof(PHYSICAL_MONITOR));
		if (pPhysicalMonitors != NULL)
		{
			// Get the array.
			bSuccess = GetPhysicalMonitorsFromHMONITOR(hMonitor, cPhysicalMonitors, pPhysicalMonitors);

			int n = 0;
			do {
				bSuccess = GetMonitorBrightness(pPhysicalMonitors->hPhysicalMonitor , &minb, &curb, &maxb);
				if( !bSuccess ) {
					dbg_printf("GetMonitorBrightness, n = %d, bSuccess = %d\r\r\n", n, bSuccess);
			        GetErrorMessage(TEXT("GetMonitorBrightness"));
					Sleep(RETRY_SLEEP);
				}
				n++;
			} while( !bSuccess && n < MAX_RETRY);

			//dbg_printf("GetMonitorBrightness, bSuccess = %d\r\r\n", bSuccess);
			if( bSuccess ) {
				if( curb != cBrightness && minb <= cBrightness && cBrightness <= maxb ) {
					int n = 0;
					do {
						bSuccess = SetMonitorBrightness(pPhysicalMonitors->hPhysicalMonitor , cBrightness);
						if( !bSuccess ) {
							dbg_printf("SetMonitorBrightness, n = %d, bSuccess = %d\r\r\n", n, bSuccess);
					        GetErrorMessage(TEXT("SetMonitorBrightness"));
							Sleep(RETRY_SLEEP);
						}
						n++;
					} while( !bSuccess && n < MAX_RETRY);
					
					dbg_printf("SetMonitorBrightness(%d), bSuccess = %d\r\r\n",cBrightness, bSuccess);
				    dbg_printf("minb = %d, curb=%d, maxb=%d\r\r\n", minb, cBrightness, maxb);
				}
			}

			// Close the monitor handles.
	        bSuccess = DestroyPhysicalMonitors( cPhysicalMonitors, pPhysicalMonitors);
	
			// Free the array.
			free(pPhysicalMonitors);
		}
	}
	return curb;
}

int CMonConfDlg::SetWindowTitle(int cBri)
{

	CString str;
	str.Format("%d%% - %s", cBri, BrightControlTitle_str);
	SetWindowText(str);
	return 0;
}

void CMonConfDlg::OnBnClickedButtonSet()
{
	char buf[256];
	int curBrightness = 0;
	int curContract = 0;

	edBrightness.GetWindowText(buf,sizeof(buf));
//	dbg_printf("bri = %s\r\r\n", buf);
	
	curBrightness = atoi(buf);
	if( curBrightness >= 0 ) {
		SetMonitorBright(this->m_hWnd,curBrightness);
		sliderBri.SetPos(curBrightness);
		SetWindowTitle(curBrightness);
	}

    //edContract.GetWindowText(buf,sizeof(buf));
	//dbg_printf("con = %s\r\r\n", buf);

}
void CMonConfDlg::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此加入控制項告知處理常式程式碼
	*pResult = 0;
}

int CMonConfDlg::QuickSetBright(int cBright)
{
	CString str;
	str.Format(_T("%d"),cBright);
	edBrightness.SetWindowText(str);
	OnBnClickedButtonSet();
	return 0;
}


void CMonConfDlg::OnBnClickedButtonBri0()
{
	QuickSetBright(cmdBri[0]);
}

void CMonConfDlg::OnBnClickedButtonBri1()
{
	QuickSetBright(cmdBri[1]);
}

void CMonConfDlg::OnBnClickedButtonBri2()
{
	QuickSetBright(cmdBri[2]);
}

void CMonConfDlg::OnBnClickedButtonBri3()
{
	QuickSetBright(cmdBri[3]);
}

void CMonConfDlg::OnBnClickedButtonBri4()
{
	QuickSetBright(cmdBri[4]);
}

void CMonConfDlg::OnBnClickedButtonBri5()
{
	QuickSetBright(cmdBri[5]);
}


void CMonConfDlg::OnBnClickedButtonBri6()
{
	QuickSetBright(cmdBri[6]);
}


void CMonConfDlg::GetErrorMessage(LPTSTR lpszFunction)
{ 
    // Retrieve the system error message for the last-error code

    LPVOID lpMsgBuf;
//    LPVOID lpDisplayBuf;
    DWORD dw = GetLastError(); 

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf,
        0, NULL );

    // Display the error message and exit the process

//    lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, 
//        (lstrlen((LPCTSTR)lpMsgBuf)+lstrlen((LPCTSTR)lpszFunction)+40)*sizeof(TCHAR)); 

	dbg_printf(TEXT("%s GetLastError %d: %s"), 
        lpszFunction, dw, lpMsgBuf); 

//	StringCchPrintf((LPTSTR)lpDisplayBuf, 
//        LocalSize(lpDisplayBuf),
//        TEXT("%s GetLastError %d: %s"), 
//        lpszFunction, dw, lpMsgBuf); 
//    MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK); 


    LocalFree(lpMsgBuf);
//    LocalFree(lpDisplayBuf);
}



void CMonConfDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);

	char buf[256];
	int curBrightness = 0;
//	int curContract = 0;

	edBrightness.GetWindowText(buf,sizeof(buf));
	curBrightness = atoi(buf);

	int bri = sliderBri.GetPos();

	if( abs(bri-curBrightness) >= 5 ) {
		CString str;
		str.Format(_T("%d"),bri);
		edBrightness.SetWindowText(str);
		OnBnClickedButtonSet();
		Sleep(50);
	}

}




void CMonConfDlg::OnClose()
{
    WINDOWPLACEMENT wp;
    GetWindowPlacement(&wp);
    AfxGetApp()->WriteProfileBinary("BrightControl", "WinPos", (LPBYTE)&wp, sizeof(wp));

	CDialog::OnClose();
}
