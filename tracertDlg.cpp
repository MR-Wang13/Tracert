// tracertDlg.cpp : implementation file
//

#include "stdafx.h"
#include "tracert.h"
#include "tracertDlg.h"
#include "new.h"
#include <Winsock2.h>
#include <winsock.h>
#include <windowsx.h>
#include <algorithm>
#include <shlwapi.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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

/////////////////////////////////////////////////////////////////////////////
// CTracertDlg dialog

CTracertDlg::CTracertDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTracertDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTracertDlg)
	m_ip = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTracertDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTracertDlg)
	DDX_Control(pDX, IDC_ret, m_ret);
	DDX_Text(pDX, IDC_ip, m_ip);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTracertDlg, CDialog)
	//{{AFX_MSG_MAP(CTracertDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_tracert, Ontracert)
	ON_BN_CLICKED(IDC_ping, Onping)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTracertDlg message handlers

BOOL CTracertDlg::OnInitDialog()
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
	//设置文本框字体大小
	CFont *m_Font;
    m_Font = new CFont; 
    m_Font->CreateFont(25,10,0,0,50,
    FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,
    CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FF_SWISS,"Arial");
    CEdit *m_Edit=(CEdit *)GetDlgItem(IDC_ip);
    m_Edit->SetFont(m_Font,FALSE);
    GetDlgItem(IDC_ip)->SetFont(m_Font);

	m_Edit=(CEdit *)GetDlgItem(IDC_ret);
    m_Edit->SetFont(m_Font,FALSE);
    GetDlgItem(IDC_ret)->SetFont(m_Font);

	
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTracertDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTracertDlg::OnPaint() 
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
HCURSOR CTracertDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTracertDlg::Ontracert() 
{
	// TODO: Add your control notification handler code here
	//初始化winsock2环境
	UpdateData();
	WSADATA wsa;
	CString str;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
	//	cerr << "Failed to initialize the WinSock2 DLL\n"
	//		 << "error code: " << WSAGetLastError() << endl;
		str.Format("\nFailed to initialize the WinSock2 DLL\nerror code: %s\n",WSAGetLastError());
		Display(str);
		return ;
	}

	//将命令行参数转换为IP地址
	ULONG DestIp = inet_addr( (LPSTR)(LPCTSTR)m_ip);
	if (DestIp == INADDR_NONE)
	{
		//转换不成功时按域名解析
		hostent* pHost = gethostbyname( (LPSTR)(LPCTSTR)m_ip);
		if (pHost)
		{
			DestIp = (*(in_addr*)pHost->h_addr).s_addr;
		}
		else
		{
			//cout << "Unable to resolve the target name " << argv[1] << endl;
			str.Format("\nUnable to resolve the target name %s\n",m_ip);
			Display(str);
			WSACleanup();
			return ;
		}
	}

	//载入ICMP.DLL动态库
	HMODULE hInst = LoadLibrary("ICMP.dll");
	if (!hInst)
	{
		//cout << "Could not load up the ICMP DLL\n";
		str="\nCould not load up the ICMP DLL!\n";
		Display(str);
		WSACleanup();
		return ;
	}

	//获取所需的ICMP.DLL中的三个函数指针
	//GetProcAddress函数检索指定的动态链接库(DLL)中的输出库函数地址。
	lpIcmpCreateFile IcmpCreateFile = (lpIcmpCreateFile)GetProcAddress(hInst, "IcmpCreateFile");
	lpIcmpSendEcho IcmpSendEcho = (lpIcmpSendEcho)GetProcAddress(hInst, "IcmpSendEcho");
	lpIcmpCloseHandle IcmpCloseHandle = (lpIcmpCloseHandle)GetProcAddress(hInst, "IcmpCloseHandle");
	if (IcmpCreateFile==NULL || IcmpSendEcho==NULL || IcmpCloseHandle==NULL)
	{
		//cout << "Could not find ICMP functions in the ICMP DLL\n";
		str="\nCould not find ICMP functions in the ICMP DLL!\n";
		Display(str);
		WSACleanup();
		return ;
	}

	//打开ICMP句柄
	HANDLE hIcmp = IcmpCreateFile();
	if (hIcmp == INVALID_HANDLE_VALUE)
	{
		//cout << "Could not get a valid ICMP handle\n";
		str="\nCould not get a valid ICMP handle!\n";
		Display(str);
		WSACleanup();
		return ;
	}
	//cout << "\nTracing route to " << argv[1] << " [" << inet_ntoa(*(in_addr*)(&DestIp))
		 //<< "] with a maximum of " << DEF_MAX_HOP << " hops.\n" << endl;
	str.Format("\nTracing route to %s [%s] with a maximum of %d hops. \n\n",m_ip,inet_ntoa(*(in_addr*)(&DestIp)),DEF_MAX_HOP);
	Display(str);

	//设置IP报头TTL值
	IP_OPTION_INFORMATION IpOption; //该结构用来控制所发ICMP数据包的IP报头相应字段值
    ZeroMemory(&IpOption, sizeof(IP_OPTION_INFORMATION));
	IpOption.Ttl = 1;

	//设置要发送的ICMP数据
	char SendData[DATA_SIZE];
	memset(SendData, 'E', sizeof(SendData));

	//设置接收缓冲区
	char ReplyBuffer[sizeof(ICMP_ECHO_REPLY)+DATA_SIZE];
	ICMP_ECHO_REPLY* pEchoReply = (ICMP_ECHO_REPLY*)ReplyBuffer;

	BOOL bLoop = TRUE;
	int iMaxHop = DEF_MAX_HOP;
	while (bLoop && iMaxHop--)
	{
		//打印序号
		//cout << (int)IpOption.Ttl << ":";
		str.Format("%d:",(int)IpOption.Ttl);
		Display(str);
		//发送ICMP回显包并接收应答
		if (IcmpSendEcho(hIcmp, DestIp, SendData, sizeof(SendData), &IpOption, ReplyBuffer, sizeof(ReplyBuffer), TIMEOUT) != 0)
		{
			//正确收到应答包，打印时间和IP地址
			if (pEchoReply->RoundTripTime == 0)
			{
				//cout << "\t<1 ms";
				str="\t<1 ms";
				Display(str);
			}
			else
			{
				//cout << "\t" << pEchoReply->RoundTripTime << " ms";
				str.Format("\t%d ms",pEchoReply->RoundTripTime);
				Display(str);
			}
			//cout << "\t" << inet_ntoa(*(in_addr*)&(pEchoReply->Address)) << endl;
			CString ss;
			ss.Format("%s",inet_ntoa(*(in_addr*)&(pEchoReply->Address)));
			unsigned long addr = inet_addr(ss);
			if(addr != INADDR_NONE)
			{
				hostent *hp=gethostbyaddr((char*)&addr,4, AF_INET);
				if(hp!=NULL)
					str.Format("\t%s [%s]\n",hp->h_name,ss);
				else str.Format("\t%s\n",ss);
			}
			else str.Format("\t%s\n",ss);
			Display(str);

			//判断是否完成路由路径探测
			if (pEchoReply->Address == DestIp)
			{
				//cout << "\nTrace complete.\n" << endl;
				bLoop = FALSE;
			}
		}
		else //超时返回,打印代表超时的"*"
		{
			//cout << "\t" << "*" << "\tRequest timed out." << endl;
			str="\t*\tRequest timed out.\n";
			Display(str);
		}

		//TTL值加1
		IpOption.Ttl++;
	}
	str="\nTrace complete.\n";
	Display(str);
	str="\n";
	Display(str);
	IcmpCloseHandle(hIcmp);
	WSACleanup();
}

void CTracertDlg::Display(CString str)
{
	LPCTSTR pDisplay;
	pDisplay = _T(str);//转换成LPCTSTR数据类型
	int nlength = m_ret.GetWindowTextLength();//获取编辑框的字符数
	m_ret.SetSel(nlength, nlength);//定位光标
	m_ret.ReplaceSel(pDisplay);//光标处显示
}

void CTracertDlg::Onping() 
{
	// TODO: Add your control notification handler code here
	Ping();
}

int CTracertDlg::Ping()
{
	UpdateData();
	WSADATA wsa;
	CString str;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		str.Format("\nFailed to initialize the WinSock2 DLL\nerror code: %s\n",WSAGetLastError());
		Display(str);
		return 1;
	}

	//将命令行参数转换为IP地址
	ULONG DestIp = inet_addr( (LPSTR)(LPCTSTR)m_ip);
	if (DestIp == INADDR_NONE)
	{
		//转换不成功时按域名解析
		hostent* pHost = gethostbyname( (LPSTR)(LPCTSTR)m_ip);
		if (pHost)
		{
			DestIp = (*(in_addr*)pHost->h_addr).s_addr;
		}
		else
		{
			//cout << "Unable to resolve the target name " << argv[1] << endl;
			str.Format("\nUnable to resolve the target name %s\n",m_ip);
			Display(str);
			WSACleanup();
			return -1;
		}
	}

	//载入ICMP.DLL动态库
	HINSTANCE hInst = LoadLibrary("ICMP.dll");
	if (!hInst)
	{
		//cout << "Could not load up the ICMP DLL\n";
		str="\nCould not load up the ICMP DLL!";
		Display(str);
		WSACleanup();
		return 2;
	}
	// 查找给定机器的IP地址信息
	struct hostent* phe;
	if ((phe = gethostbyname(m_ip)) == 0) 
	{
		//cerr << "Could not find IP address for " << argv[1] << endl;
		str.Format("\nCould not find IP address for %s\n",m_ip);
		Display(str);
		return 3;
	}

	//获取所需的ICMP.DLL中的三个函数指针
	//GetProcAddress函数检索指定的动态链接库(DLL)中的输出库函数地址。
	lpIcmpCreateFile IcmpCreateFile = (lpIcmpCreateFile)GetProcAddress(hInst, "IcmpCreateFile");
	lpIcmpSendEcho IcmpSendEcho = (lpIcmpSendEcho)GetProcAddress(hInst, "IcmpSendEcho");
	lpIcmpCloseHandle IcmpCloseHandle = (lpIcmpCloseHandle)GetProcAddress(hInst, "IcmpCloseHandle");
	if (IcmpCreateFile==NULL || IcmpSendEcho==NULL || IcmpCloseHandle==NULL)
	{
		//cout << "Could not find ICMP functions in the ICMP DLL\n";
		str="\nCould not find ICMP functions in the ICMP DLL!";
		Display(str);
		WSACleanup();
		return 4;
	}

	//打开ICMP句柄
	HANDLE hIcmp = IcmpCreateFile();
	if (hIcmp == INVALID_HANDLE_VALUE)
	{
		//cout << "Could not get a valid ICMP handle\n";
		str="\nCould not get a valid ICMP handle!";
		Display(str);
		WSACleanup();
		return 5;
	}
	str.Format("\n\n正在 Ping %s [%s] 具有 64 字节的数据: \n\n",m_ip,inet_ntoa(*(in_addr*)(&DestIp)));
	Display(str);

	// 构造ping数据包
	char acPingBuffer[64];
	memset(acPingBuffer, '\xAA', sizeof(acPingBuffer));
	//分配内存空间
	PICMP_ECHO_REPLY pIpe = (PICMP_ECHO_REPLY)GlobalAlloc( GMEM_FIXED | GMEM_ZEROINIT,
	sizeof(ICMP_ECHO_REPLY) + sizeof(acPingBuffer)); 
	if (pIpe == 0) 
	{
		//cerr << "Failed to allocate global ping packet buffer." << endl;
		str="Failed to allocate global ping packet buffer.";
		Display(str);
		WSACleanup();
		return 6;
	}
	pIpe->Data = acPingBuffer;
	pIpe->DataSize = sizeof(acPingBuffer);

	int num=0,ma=0,mi=9999,sum=0;
	for(int i=1;i<=MAX_PING;i++)
	{
		// 发送ping数据包
		//IcmpSendEcho(hIcmp, DestIp, SendData, sizeof(SendData), &IpOption, ReplyBuffer, sizeof(ReplyBuffer), TIMEOUT) != 0
		DWORD dwStatus = IcmpSendEcho(hIcmp, *((DWORD*)phe->h_addr_list[0]),acPingBuffer,
		sizeof(acPingBuffer),NULL,pIpe,sizeof(ICMP_ECHO_REPLY) + sizeof(acPingBuffer),TIMEOUT);
		if (dwStatus != 0) 
		{
		//	str.Format("来自 %d.%d.%d.%d 的回复,RTT: %dms, TTL: %d \n",int(LOBYTE(LOWORD(pIpe->Address))),int(HIBYTE(LOWORD(pIpe->Address))),
		//		int(LOBYTE(HIWORD(pIpe->Address))),int(HIBYTE(HIWORD(pIpe->Address))),int(pIpe->RoundTripTime),int(pIpe->Options.Ttl));
			str.Format("来自 %s 的回复: 字节=%d 时间=%dms TTL=%d\n",inet_ntoa(*(in_addr*)(&pIpe->Address)),int(pIpe->DataSize),
				int(pIpe->RoundTripTime),int(pIpe->Options.Ttl));
			Display(str);
			num++;
			ma=max(ma,int(pIpe->RoundTripTime));
			mi=min(mi,int(pIpe->RoundTripTime));
			sum+=int(pIpe->RoundTripTime);
		}
		else 
		{
			//cerr << "Error obtaining info from ping packet." << endl;
			str="请求超时。\n";
			Display(str);
		}
	}
	str.Format(" %s 的 Ping 统计信息: \n",inet_ntoa(*(in_addr*)(&DestIp)));
	Display(str);
	str.Format("    数据包: 已发送 = %d，已接收 = %d，丢失 = %d (%.0lf%%丢失)\n",MAX_PING,num,MAX_PING-num,100.0*(MAX_PING-num)/(double)MAX_PING);
	Display(str);
	if(num>0)
	{
		str.Format(" 往返行程的估计时间(以毫秒为单位):\n");
		Display(str);
		str.Format("    最短 = %dms，最长 = %dms，平均 = %.0lfms\n",mi,ma,sum*1.0/num);
		Display(str);
	}
	str="\n";
	Display(str);
	// 关闭,回收资源
	GlobalFree(pIpe);
	IcmpCloseHandle(hIcmp);
	WSACleanup();
	return 0;
}

BOOL CTracertDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_RETURN) 
	{
		return true;
	}
	return CDialog::PreTranslateMessage(pMsg);
}
