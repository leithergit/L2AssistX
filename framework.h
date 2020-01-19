#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

// 关闭 MFC 的一些常见且经常可放心忽略的隐藏警告消息
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展


#include <afxdisp.h>        // MFC 自动化类



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC 支持功能区和控制条


#include "Utility.h"
#include "TimeUtility.h"
#include "Markup.h"
#include "Runlog.h"
#include "CriticalSectionProxy.h"
#include "CtrlsForListCtrl.h"
#include <string>
#include <vector>
#include <process.h>
using namespace std;
using namespace std::tr1;

enum RoleType
{
	Role_Fighter = 0,		// 战斗成员
	Role_Healer = 1,		// 治疗师
	Role_Buffer = 2,		// 状态师
	Role_Knight = 3		// 骑士
};

enum ChordType
{
	Chord_Fighter,			// 战士和音
	Chord_Magic,			// 法师和音
	Chord_Knight			// 护卫和音
};

struct GameKeyProp
{
	UINT	nKeyCode;
	UINT	nFireTime;		// 施展时间
	UINT	nCoolDownTime;	// 冷却时间
};

struct KeyProp
{
	CString strName;
	UCHAR	nCode;
	bool	bAlt;
	bool	bUsed;

	/*KeyProp()
	{
		strName = _T("");
		nCode = 0;
		bAlt = FALSE;
	}*/
};
typedef shared_ptr<KeyProp> KeyPropPtr;
struct Role
{
	string		strName;
	RoleType	nRoleType;
	int			nStatus;
};

typedef shared_ptr<Role> RolePtr;


#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif



