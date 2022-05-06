; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMonConfDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "MonConf.h"

ClassCount=3
Class1=CMonConfApp
Class2=CMonConfDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_MONCONF_DIALOG

[CLS:CMonConfApp]
Type=0
HeaderFile=MonConf.h
ImplementationFile=MonConf.cpp
Filter=N

[CLS:CMonConfDlg]
Type=0
HeaderFile=MonConfDlg.h
ImplementationFile=MonConfDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_EDIT_BRIGHTNESS

[CLS:CAboutDlg]
Type=0
HeaderFile=MonConfDlg.h
ImplementationFile=MonConfDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_MONCONF_DIALOG]
Type=1
Class=CMonConfDlg
ControlCount=11
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT_BRIGHTNESS,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_BUTTON_GET,button,1342242816
Control7=IDC_BUTTON_SET,button,1342242816
Control8=IDC_EDIT_OUTPUT,edit,1352728772
Control9=IDC_STATIC_CONTRACT,static,1342308352
Control10=IDC_EDIT_CONTRACT,edit,1350631552
Control11=IDC_BUTTON_CLEAR,button,1342242816

