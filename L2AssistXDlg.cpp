
// L2AssistXDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "L2AssistX.h"
#include "L2AssistXDlg.h"
#include "afxdialogex.h"

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


// CL2AssistXDlg 对话框



CL2AssistXDlg::CL2AssistXDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_L2ASSISTX_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CL2AssistXDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CL2AssistXDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(NM_RCLICK, IDC_LIST_ROLE, &CL2AssistXDlg::OnNMRClickListRole) 	
 	ON_NOTIFY(NM_CLICK, IDC_LIST_ROLE, &CL2AssistXDlg::OnNMClickListRole) 	
	ON_COMMAND(ID_KEY_ADD, &CL2AssistXDlg::OnKeyAdd)
	ON_COMMAND(ID_KEY_DEL, &CL2AssistXDlg::OnKeyDel)
	ON_COMMAND(ID_KEY_DELALL, &CL2AssistXDlg::OnKeyDelall)
	ON_COMMAND(ID_ROLE_ADD, &CL2AssistXDlg::OnRoleAdd)
	ON_COMMAND(ID_ROLE_COPY, &CL2AssistXDlg::OnRoleCopy)
	ON_COMMAND(ID_ROLE_DEL, &CL2AssistXDlg::OnRoleDel)
	ON_COMMAND(ID_ROLE_DELALL, &CL2AssistXDlg::OnRoleDelall)
	ON_COMMAND(ID_ROLE_START, &CL2AssistXDlg::OnRoleStart)
	ON_COMMAND(ID_ROLE_STOP, &CL2AssistXDlg::OnRoleStop)
	ON_COMMAND(ID_ROLE_STARTALL, &CL2AssistXDlg::OnRoleStartall)
	ON_COMMAND(ID_ROLE_STOPALL, &CL2AssistXDlg::OnRoleStopall)
	ON_COMMAND(ID_ROLE_SAVE, &CL2AssistXDlg::OnRoleSave)
	ON_COMMAND(ID_ROLE_LOAD, &CL2AssistXDlg::OnRoleLoad)
	ON_BN_CLICKED(IDC_CHECK_SHOWMESSAGE, &CL2AssistXDlg::OnBnClickedCheckShowmessage)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_ROLE, &CL2AssistXDlg::OnNMDblclkListRole)
END_MESSAGE_MAP()


// CL2AssistXDlg 消息处理程序

BOOL CL2AssistXDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	m_wndListRole.SubclassDlgItem(IDC_LIST_ROLE, this);
	m_wndListRole.SetExtendedStyle(m_wndListRole.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

	int nCols = 0;
	m_wndListRole.InsertColumn(nCols++, _T("序号"), LVCFMT_LEFT, 40);
	m_wndListRole.InsertColumn(nCols++, _T("名称"), LVCFMT_LEFT, 100);
	m_wndListRole.InsertColumn(nCols++, _T("类型"), LVCFMT_LEFT, 80);
	m_wndListRole.InsertColumn(nCols++, _T("状态"), LVCFMT_LEFT, 60);
	m_wndListRole.InsertColumn(nCols++, _T("HP"), LVCFMT_LEFT, 30);
	m_wndListRole.InsertColumn(nCols++, _T("MP"), LVCFMT_LEFT, 30);

	CRoleProperty* pDlg = new CRoleProperty();
	m_vecDialog.push_back(pDlg);
	RECT rt;
	GetDlgItemRect(IDC_STATIC_FRAME, rt);
	pDlg->Create(IDD_DIALOG_PROPERTY, this);
	pDlg->MoveWindow(&rt);
	pDlg->ShowWindow(SW_SHOW);
	m_pCurRoleDialog = pDlg;
	m_pDialogMessaage = new CDialogMessage();
	m_pDialogMessaage->Create(IDD_DIALOG_MESSAGE, this);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CL2AssistXDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CL2AssistXDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CL2AssistXDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CL2AssistXDlg::OnNMRClickListRole(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	CMenu PopMenu;
	PopMenu.LoadMenu(IDR_MENU_ROLE);
	POINT pt;
	GetCursorPos(&pt);
	CMenu* pMenu = PopMenu.GetSubMenu(0);

	pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, this);
	*pResult = 0;
}

void CL2AssistXDlg::OnNMRClickListProperty(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	CMenu PopMenu;
	PopMenu.LoadMenu(IDR_MENU_PROP);
	POINT pt;
	GetCursorPos(&pt);
	CMenu* pMenu = PopMenu.GetSubMenu(0);

	pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, this);
	*pResult = 0;
}

void CL2AssistXDlg::OnNMClickListRole(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

void CL2AssistXDlg::OnNMClickListProperty(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}


void CL2AssistXDlg::OnKeyAdd()
{
	// TODO: Add your command handler code here
}

void CL2AssistXDlg::OnKeyDel()
{
	// TODO: Add your command handler code here
}

void CL2AssistXDlg::OnKeyDelall()
{
	// TODO: Add your command handler code here
}

void CL2AssistXDlg::OnRoleAdd()
{
	// TODO: Add your command handler code here
}

void CL2AssistXDlg::OnRoleCopy()
{
	// TODO: Add your command handler code here
}

void CL2AssistXDlg::OnRoleDel()
{
	// TODO: Add your command handler code here
}

void CL2AssistXDlg::OnRoleDelall()
{
	// TODO: Add your command handler code here
}

void CL2AssistXDlg::OnRoleStart()
{
	// TODO: Add your command handler code here
}

void CL2AssistXDlg::OnRoleStop()
{
	// TODO: Add your command handler code here
}

void CL2AssistXDlg::OnRoleStartall()
{
	// TODO: Add your command handler code here
}

void CL2AssistXDlg::OnRoleStopall()
{
	// TODO: Add your command handler code here
}

void CL2AssistXDlg::OnRoleSave()
{
	// TODO: Add your command handler code here
}

void CL2AssistXDlg::OnRoleLoad()
{
	// TODO: Add your command handler code here
}

BOOL CL2AssistXDlg::PreTranslateMessage(MSG* pMsg)
{
	if (IsCancelDialogMessage(pMsg))
		return true;
	else
		return CDialog::PreTranslateMessage(pMsg);
}

void CL2AssistXDlg::OnBnClickedCheckShowmessage()
{
	int nCmdShow = SW_SHOW;
	if (IsDlgButtonChecked(IDC_CHECK_SHOWMESSAGE) != BST_CHECKED)
		nCmdShow = SW_HIDE;
	m_pDialogMessaage->ShowWindow(nCmdShow);
}


void CL2AssistXDlg::OnNMDblclkListRole(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	*pResult = 0;
}
