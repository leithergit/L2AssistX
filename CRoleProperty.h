#pragma once
#include "CDetector.h"

// CRoleProperty 对话框

class CRoleProperty : public CDialogEx
{
	DECLARE_DYNAMIC(CRoleProperty)

public:
	CRoleProperty(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CRoleProperty();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PROPERTY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	vector<KeyProp> m_vecKeyList;
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnNMDblclkListFight(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMRClickListFight(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMDblclkListBuffer(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMRClickListBuffer(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg LRESULT OnSpyWnd(WPARAM W, LPARAM l)
	{
		if (W)
			m_hDestWnd = (HWND)W;
	}
	CListCtrl m_ctlListFightSkill;
	CListCtrl m_ctlListBuffer;
	CDetector m_ctlDetector;
	afx_msg void OnBnClickedButtonUpdatetitle();
	// 队伍中的人数
	CComboBox m_nFollowPartnerNo;
	// 是自主动邀请设置的人员组队
	BOOL m_bInvitePartners[6];
	// 是否延时退组，适用于LG陪练，加完buff退组
	BOOL m_bExitTeamDelay;
	// 跟随攻击的按键宏的快捷键
	CString m_strKeyFollowAttak;
	// 队伍中的人数
	int m_nTeamMembers;
	// 在队伍中的角色，0为开怪，1为跟随
	BOOL	m_bRoleInTeam;
	HWND	m_hDestWnd = nullptr;
	// 是否开启队友HP保护开关
	BOOL m_bCheck_HP[3];
	// 是否开启队友MP保护开关
	BOOL m_bCheckMP1;
	// 队友HP阀值
	UINT m_nPartnerHP[3];
	// 队友MP1阀值1
	UINT m_nParntnerMP1;
	// 邀请队友等延时，建议值5-15秒
	UINT m_nInvitePartnerDelay;
	// 延时退组时间，适合用于LG陪练
	UINT m_nExitTeamDelay;
	// 退组键，适用于LG陪练
	CString m_strKeyExitTeam;
	// 邀请队友组合按键宏	
	CString m_strKeyInvitePartner[6];
	// HP1技能冷却时间
	UINT m_nHPKeyCD[3];
	// 几个队友HP小于阀值时使用HP恢复技能
	UINT m_nHPPartners;
	// 几个队友MP小于阀值时使用MP恢复技能
	UINT m_nMPPartners;
	// 队友HP小于阀值使用的技能
	CString m_strKeyHP[3];
	// 团队HP小于阀值时的技能
	CString m_strKeyTeamHP;
	// 队友MP小于阀值时的技能
	CString m_strKeyMP;
	// 队伍中多人HP小于阀值的技能
	CString m_strKeyTeamMP;
	// 恢复单个队友MP技能CD
	UINT m_nMP1KeyCD;
	// 攻击特定怪物技能CD
	UINT m_nKeySpecificCD[3];
	// 要攻击的目标范围,为空时对攻击所有可视目标
	BOOL m_bCheckAttackRange;
	// 设置排除目标，若为这侧攻击所有可视目标
	BOOL m_bCheckExcludeRange;
	// 目标死亡后是否使用技能如回收,死体吸收
	BOOL m_bCheckMonterDied;
	// 目标死亡后使用的技能，如回收，死体吸收
	CString m_strKeyMonsterDied;
	// 限定攻击的怪物列表，以分号，逗号或空格分开
	CString m_strMonstorsList;
	// 排除攻击的怪物列表，以分号，逗号或空格分开
	CString m_strExcludeMonstors;
	// 怪物不掉血则换怪时间，单位秒
	UINT m_nAttackNoHurtTime;
	// 是否启用对特定怪使用特定技能
	BOOL m_bCheckAttackSpecific;
	// 需要使用特定技能攻击的怪物列表，以逗号，分号或空格分开
	CString m_strSpecificMonstors;
	// 对特定怪物攻击的技能
	CString m_strKeySpecific[3];
	// 是否自动标星
	BOOL m_bCheckMakrStart;
	// 标星按键
	CString m_strKeyMarkStart;
	// 是否只接受满经验复活// 是否只接受满经验复活
	BOOL m_bRecvFullResurgence;
	// 是否复活队友
	BOOL m_bResurgencePartners;
	// 复活死否重新加buffer
	BOOL m_bResurgenceRebuffer;
	// 复活后是重新贵族幸运还是加拯救徽章，0为加贵族，1为加徽章
	BOOL m_bNobilitylucy;
	// 加贵族状态键
	CString m_strKeyNobilityLucy;
	// 加拯救徽章快捷键
	CString m_strKeyRecureEmblem;
	// 物品拾取键
	CString m_strKeyPickup;
	// 物品拾取次数，太高可能会影响打怪效率
	UINT m_nPickupTimes;
	// 拾取物品时间间隔，建议250ms
	UINT m_nPickupInerval;
	// 是否自动开活力
	BOOL m_bEableEngergy;
	// 开启活力的次数
	int m_nEnableEnergyTimes;
	// 游戏窗口名称
	CString m_strLineageWndTitle;
	afx_msg void OnNMClickListFight(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMClickListBuffer(NMHDR* pNMHDR, LRESULT* pResult);
};
