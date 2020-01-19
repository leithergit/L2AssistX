// CDetector.cpp : implementation file
//

#include "stdafx.h"
#include "L2AssistX.h"
#include "CDetector.h"


// CDetector

IMPLEMENT_DYNAMIC(CDetector, CStatic)

CDetector::CDetector()
{


}

CDetector::~CDetector()
{

}


BEGIN_MESSAGE_MAP(CDetector, CStatic)
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



// CDetector message handlers
void CDetector::OnLButtonDown(UINT nFlags, CPoint point)
{
	SetCapture(); // 设置鼠标捕获
	// 鼠标所在窗口
	CWnd* pWnd = ChildWindowFromPoint(point);

	// 若单击Spy_Scan_Icon，启动扫描
	if (pWnd != NULL && pWnd->GetSafeHwnd() == m_hWnd)
	{
		SpyStartScanning();
	}
	CStatic::OnLButtonDown(nFlags, point);
}
void CDetector::OnLButtonUp(UINT nFlags, CPoint point)
{
	ReleaseCapture();
	// 停止扫描
	if (m_bScanning)
	{
		SpyStopScanning();
	}
	
	CStatic::OnLButtonUp(nFlags, point);
}

void CDetector::OnMouseMove(UINT nFlags, CPoint point)
{
	// 扫描中
	if (m_bScanning)
	{
		SpyExecScanning(point);
	}
	CStatic::OnMouseMove(nFlags, point);
}


void CDetector::SpyStartScanning()
{
	m_bScanning = TRUE;
	SetIcon(m_hIconBlank);
	m_hOldCurSor = ::SetCursor(m_hCursorScan);
}


void CDetector::SpyStopScanning()
{
	m_bScanning = FALSE;
	SetIcon(m_hIconInitial);
	SpyInvertBorder(m_hWndSaved);
	
	m_hSpyWnd = m_hWndSaved;
	
	::SetCursor(m_hOldCurSor);
	if (m_hSpyWnd && 
		m_hDestWndText && 
		IsWindow(m_hDestWndText))
	{
		TCHAR szText[1024] = { 0 };
		::GetWindowText(m_hSpyWnd, szText, 1024);
		::SetWindowText(m_hDestWndText, szText);
		::PostMessage(m_hParentWnd, WM_SPYWND, (WPARAM)m_hSpyWnd,0);
	}
}


void CDetector::SpyExecScanning(CPoint& pt)
{
	ClientToScreen(&pt); // 转换到屏幕坐标
	HWND current_window = SpyFindSmallestWindow(pt); //找到当前位置的最小窗口

	if (current_window != NULL)
	{
		// 确保找到的窗口不是自己的窗口，窗口进程不同
		if (GetWindowThreadProcessId(GetSafeHwnd(), NULL) != GetWindowThreadProcessId(current_window, NULL))
		{
			// 若是新窗口，就把旧窗口的边界去掉，画新窗口的边界
			if (current_window != m_hPrevWnd)
			{
				SpyInvertBorder(m_hPrevWnd);
				m_hPrevWnd = current_window;
				SpyInvertBorder(m_hPrevWnd);
			}
		}
		else
		{
			// 窗口是自己的
			SpyInvertBorder(m_hPrevWnd);
			m_hPrevWnd = NULL;
		}
	}

	m_hWndSaved = m_hPrevWnd;

	if (m_hWndSaved &&
		m_hDestWndText &&
		IsWindow(m_hDestWndText))
	{
		TCHAR szText[1024] = { 0 };
		::GetWindowText(m_hSpyWnd, szText, 1024);
		::SetWindowText(m_hDestWndText, szText);
	}

	UpdateData(FALSE); // 更新数据
}


HWND CDetector::SpyFindSmallestWindow(const CPoint& pt)
{
	HWND hWnd = WindowFromPoint(pt)->GetSafeHwnd(); // 鼠标所在窗口

	if (hWnd != NULL)
	{
		// 得到本窗口大小和父窗口句柄，以便比较
		CRect rect;
		::GetWindowRect(hWnd, &rect);
		HWND parent = ::GetParent(hWnd); // 父窗口

		// 只有该窗口有父窗口才继续比较
		if (parent != NULL)
		{
			// 按Z方向搜索
			HWND find = hWnd; // 递归调用句柄
			CRect rect_find;

			while (TRUE) // 循环
			{
				find = ::GetWindow(find, GW_HWNDNEXT); // 得到下一个窗口的句柄
				::GetWindowRect(find, &rect_find); // 得到下一个窗口的大小

				if (::PtInRect(&rect_find, pt) // 鼠标所在位置是否在新窗口里
					&& ::GetParent(find) == parent // 新窗口的父窗口是否是鼠标所在主窗口
					&& ::IsWindowVisible(find)) // 窗口是否可视
				{
					// 比较窗口，看哪个更小
					if (rect_find.Width() * rect_find.Height() < rect.Width() * rect.Height())
					{
						// 找到更小窗口
						hWnd = find;

						// 计算新窗口的大小
						::GetWindowRect(hWnd, &rect);
					}
				}

				// hWnd的子窗口find为NULL，则hWnd为最小窗口
				if (find == NULL)
				{
					break; // 退出循环
				}
			}
		}
	}

	return hWnd;
}


void CDetector::SpyInvertBorder(const HWND& hWnd)
{
	// 若非窗口则返回
	if (!IsWindow(hWnd))
		return;

	CRect rect; // 窗口矩形

	// 得到窗口矩形
	::GetWindowRect(hWnd, &rect);

	CDC dc; // 窗口设备上下文
	dc.Attach(::GetWindowDC(hWnd));

	// 设置窗口当前前景色的混合模式为R2_NOT
	// R2_NOT - 当前的像素值为屏幕像素值的取反，这样可以覆盖掉上次的绘图
	dc.SetROP2(R2_NOT);

	// 创建画笔
	CPen pen;

	// PS_INSIDEFRAME - 产生封闭形状的框架内直线，指定一个限定矩形
	// 3 * GetSystemMetrics(SM_CXBORDER) - 三倍边界粗细
	// RGB(false,false,0) - 黑色
	pen.CreatePen(PS_INSIDEFRAME, 3 * GetSystemMetrics(SM_CXBORDER), RGB(false, false, 0));

	// 选择画笔
	HGDIOBJ old_pen = dc.SelectObject(pen);

	// 设定画刷
	HGDIOBJ old_brush = dc.SelectObject(GetStockObject(NULL_BRUSH));

	// 画矩形
	dc.Rectangle(false, false, rect.Width(), rect.Height());

	// 恢复原来的设备环境
	dc.SelectObject(old_pen);
	dc.SelectObject(old_brush);

	pen.DeleteObject();
}

void CDetector::InitIcon()
{
	m_hIconInitial = AfxGetApp()->LoadIcon(IDI_ICON_INIT);
	m_hIconBlank = AfxGetApp()->LoadIcon(IDI_ICON_BLANK);
	m_hCursorScan = AfxGetApp()->LoadCursor(IDC_CURSOR_SCAN);
	m_hParentWnd = GetParent()->GetSafeHwnd();
}
