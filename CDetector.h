#pragma once


// CDetector
#define WM_SPYWND		(WM_USER + 128)			// wparam Ϊ�ҵ��Ĵ��ھ��
class CDetector : public CStatic
{
	DECLARE_DYNAMIC(CDetector)

public:
	CDetector();
	virtual ~CDetector();

protected:
	BOOL m_bScanning = FALSE;		// �Ƿ�����ɨ��
	BOOL m_bBefound = FALSE;		// �Ƿ��Ѿ��ҵ�
	HICON m_hIconInitial = nullptr;		// origin icon
	HICON m_hIconBlank = nullptr;		// blank icon
	HCURSOR m_hCursorScan = nullptr;	// ���
	HWND m_hWndSaved = nullptr;		// �����ɨ����
	HWND m_hParentWnd = nullptr;	// �����ھ��
	HWND m_hPrevWnd = nullptr;		// ɨ�����һ������
	HCURSOR m_hOldCurSor = nullptr;
	

// ɨ�躯��
	void SpyStartScanning(); // beginning of scan
	void SpyStopScanning(); // end of scan
	void SpyExecScanning(CPoint& pt); // process of scan
	HWND SpyFindSmallestWindow(const CPoint& pt); // find the smallest window
	void SpyInvertBorder(const HWND& hWnd); // invert the window border
	DECLARE_MESSAGE_MAP()
public:
	HWND m_hSpyWnd =  nullptr;
	HWND m_hDestWndText = nullptr ;
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	void InitIcon();
};


