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
	SetCapture(); // ������겶��
	// ������ڴ���
	CWnd* pWnd = ChildWindowFromPoint(point);

	// ������Spy_Scan_Icon������ɨ��
	if (pWnd != NULL && pWnd->GetSafeHwnd() == m_hWnd)
	{
		SpyStartScanning();
	}
	CStatic::OnLButtonDown(nFlags, point);
}
void CDetector::OnLButtonUp(UINT nFlags, CPoint point)
{
	ReleaseCapture();
	// ֹͣɨ��
	if (m_bScanning)
	{
		SpyStopScanning();
	}
	
	CStatic::OnLButtonUp(nFlags, point);
}

void CDetector::OnMouseMove(UINT nFlags, CPoint point)
{
	// ɨ����
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
	ClientToScreen(&pt); // ת������Ļ����
	HWND current_window = SpyFindSmallestWindow(pt); //�ҵ���ǰλ�õ���С����

	if (current_window != NULL)
	{
		// ȷ���ҵ��Ĵ��ڲ����Լ��Ĵ��ڣ����ڽ��̲�ͬ
		if (GetWindowThreadProcessId(GetSafeHwnd(), NULL) != GetWindowThreadProcessId(current_window, NULL))
		{
			// �����´��ڣ��ͰѾɴ��ڵı߽�ȥ�������´��ڵı߽�
			if (current_window != m_hPrevWnd)
			{
				SpyInvertBorder(m_hPrevWnd);
				m_hPrevWnd = current_window;
				SpyInvertBorder(m_hPrevWnd);
			}
		}
		else
		{
			// �������Լ���
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

	UpdateData(FALSE); // ��������
}


HWND CDetector::SpyFindSmallestWindow(const CPoint& pt)
{
	HWND hWnd = WindowFromPoint(pt)->GetSafeHwnd(); // ������ڴ���

	if (hWnd != NULL)
	{
		// �õ������ڴ�С�͸����ھ�����Ա�Ƚ�
		CRect rect;
		::GetWindowRect(hWnd, &rect);
		HWND parent = ::GetParent(hWnd); // ������

		// ֻ�иô����и����ڲż����Ƚ�
		if (parent != NULL)
		{
			// ��Z��������
			HWND find = hWnd; // �ݹ���þ��
			CRect rect_find;

			while (TRUE) // ѭ��
			{
				find = ::GetWindow(find, GW_HWNDNEXT); // �õ���һ�����ڵľ��
				::GetWindowRect(find, &rect_find); // �õ���һ�����ڵĴ�С

				if (::PtInRect(&rect_find, pt) // �������λ���Ƿ����´�����
					&& ::GetParent(find) == parent // �´��ڵĸ������Ƿ����������������
					&& ::IsWindowVisible(find)) // �����Ƿ����
				{
					// �Ƚϴ��ڣ����ĸ���С
					if (rect_find.Width() * rect_find.Height() < rect.Width() * rect.Height())
					{
						// �ҵ���С����
						hWnd = find;

						// �����´��ڵĴ�С
						::GetWindowRect(hWnd, &rect);
					}
				}

				// hWnd���Ӵ���findΪNULL����hWndΪ��С����
				if (find == NULL)
				{
					break; // �˳�ѭ��
				}
			}
		}
	}

	return hWnd;
}


void CDetector::SpyInvertBorder(const HWND& hWnd)
{
	// ���Ǵ����򷵻�
	if (!IsWindow(hWnd))
		return;

	CRect rect; // ���ھ���

	// �õ����ھ���
	::GetWindowRect(hWnd, &rect);

	CDC dc; // �����豸������
	dc.Attach(::GetWindowDC(hWnd));

	// ���ô��ڵ�ǰǰ��ɫ�Ļ��ģʽΪR2_NOT
	// R2_NOT - ��ǰ������ֵΪ��Ļ����ֵ��ȡ�����������Ը��ǵ��ϴεĻ�ͼ
	dc.SetROP2(R2_NOT);

	// ��������
	CPen pen;

	// PS_INSIDEFRAME - ���������״�Ŀ����ֱ�ߣ�ָ��һ���޶�����
	// 3 * GetSystemMetrics(SM_CXBORDER) - �����߽��ϸ
	// RGB(false,false,0) - ��ɫ
	pen.CreatePen(PS_INSIDEFRAME, 3 * GetSystemMetrics(SM_CXBORDER), RGB(false, false, 0));

	// ѡ�񻭱�
	HGDIOBJ old_pen = dc.SelectObject(pen);

	// �趨��ˢ
	HGDIOBJ old_brush = dc.SelectObject(GetStockObject(NULL_BRUSH));

	// ������
	dc.Rectangle(false, false, rect.Width(), rect.Height());

	// �ָ�ԭ�����豸����
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
