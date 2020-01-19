
// L2AssistXDlg.h: 头文件
//

#pragma once
#include "CRoleProperty.h"
#include "CDetector.h"
#include "CDialogMessage.h"


// CL2AssistXDlg 对话框
class CL2AssistXDlg : public CDialogEx
{
// 构造
public:
	CL2AssistXDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_L2ASSISTX_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNMRClickListRole(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMRClickListProperty(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMClickListRole(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMClickListProperty(NMHDR* pNMHDR, LRESULT* pResult);

	afx_msg void OnKeyAdd();
	afx_msg void OnKeyDel();
	afx_msg void OnKeyDelall();
	afx_msg void OnRoleAdd();
	afx_msg void OnRoleCopy();
	afx_msg void OnRoleDel();
	afx_msg void OnRoleDelall();
	afx_msg void OnRoleStart();
	afx_msg void OnRoleStop();
	afx_msg void OnRoleStartall();
	afx_msg void OnRoleStopall();
	afx_msg void OnRoleSave();
	afx_msg void OnRoleLoad();
	CListCtrl	m_wndListRole;
	CListBox	m_wndListText;
	vector<CRoleProperty*> m_vecDialog;
	CRoleProperty* m_pCurRoleDialog = nullptr;
	CDialogMessage* m_pDialogMessaage = nullptr;

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedCheckShowmessage();
	afx_msg void OnNMDblclkListRole(NMHDR* pNMHDR, LRESULT* pResult);
};
