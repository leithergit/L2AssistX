#pragma once


// CDetector
#define WM_SPYWND		(WM_USER + 128)			// wparam 为找到的窗口句柄
class CDetector : public CStatic
{
	DECLARE_DYNAMIC(CDetector)

public:
	CDetector();
	virtual ~CDetector();

protected:
	BOOL m_bScanning = FALSE;		// 是否正在扫描
	BOOL m_bBefound = FALSE;		// 是否已经找到
	HICON m_hIconInitial = nullptr;		// origin icon
	HICON m_hIconBlank = nullptr;		// blank icon
	HCURSOR m_hCursorScan = nullptr;	// 鼠标
	HWND m_hWndSaved = nullptr;		// 保存的扫描句柄
	HWND m_hParentWnd = nullptr;	// 父窗口句柄
	HWND m_hPrevWnd = nullptr;		// 扫描的上一个窗口
	HCURSOR m_hOldCurSor = nullptr;
	

// 扫描函数
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


