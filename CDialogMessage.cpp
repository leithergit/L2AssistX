// CDialogMessage.cpp: 实现文件
//

#include "pch.h"
#include "L2AssistX.h"
#include "CDialogMessage.h"
#include "afxdialogex.h"


// CDialogMessage 对话框

IMPLEMENT_DYNAMIC(CDialogMessage, CDialogEx)

CDialogMessage::CDialogMessage(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_MESSAGE, pParent)
{

}

CDialogMessage::~CDialogMessage()
{
}

void CDialogMessage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialogMessage, CDialogEx)
END_MESSAGE_MAP()


// CDialogMessage 消息处理程序
