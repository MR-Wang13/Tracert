; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CTracertDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "tracert.h"

ClassCount=3
Class1=CTracertApp
Class2=CTracertDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_TRACERT_DIALOG

[CLS:CTracertApp]
Type=0
HeaderFile=tracert.h
ImplementationFile=tracert.cpp
Filter=N

[CLS:CTracertDlg]
Type=0
HeaderFile=tracertDlg.h
ImplementationFile=tracertDlg.cpp
Filter=D
LastObject=CTracertDlg
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=tracertDlg.h
ImplementationFile=tracertDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_TRACERT_DIALOG]
Type=1
Class=CTracertDlg
ControlCount=5
Control1=IDC_ip,edit,1350631424
Control2=IDC_STATIC,static,1342308866
Control3=IDC_tracert,button,1342242816
Control4=IDC_ping,button,1342242816
Control5=IDC_ret,edit,1352730692

