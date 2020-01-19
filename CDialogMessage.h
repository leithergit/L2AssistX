#pragma once


// CDialogMessage 对话框

class CDialogMessage : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogMessage)

public:
	CDialogMessage(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDialogMessage();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MESSAGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
