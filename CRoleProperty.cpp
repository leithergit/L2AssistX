// CRoleProperty.cpp: 实现文件
//

#include "pch.h"
#include "L2AssistX.h"
#include "CRoleProperty.h"
#include "afxdialogex.h"


// CRoleProperty 对话框

IMPLEMENT_DYNAMIC(CRoleProperty, CDialogEx)

CRoleProperty::CRoleProperty(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_PROPERTY, pParent)
	, m_bRoleInTeam(FALSE)
	, m_bExitTeamDelay(FALSE)
	, m_strKeyFollowAttak(_T(""))
	, m_nTeamMembers(0)
	, m_bCheckMP1(FALSE)
	, m_nParntnerMP1(0)
	, m_nInvitePartnerDelay(0)
	, m_nExitTeamDelay(0)
	, m_strKeyExitTeam(_T(""))
	, m_strKeyTeamHP(_T(""))
	, m_strKeyMP(_T(""))
	, m_strKeyTeamMP(_T(""))
	, m_nMP1KeyCD(0)
	, m_bCheckAttackRange(FALSE)
	, m_bCheckExcludeRange(FALSE)
	, m_bCheckMonterDied(FALSE)
	, m_strKeyMonsterDied(_T(""))
	, m_strMonstorsList(_T(""))
	, m_strExcludeMonstors(_T(""))
	, m_nAttackNoHurtTime(0)
	, m_bCheckAttackSpecific(FALSE)
	, m_strSpecificMonstors(_T(""))
	, m_bCheckMakrStart(FALSE)
	, m_strKeyMarkStart(_T(""))
	, m_bRecvFullResurgence(FALSE)
	, m_bResurgencePartners(FALSE)
	, m_bResurgenceRebuffer(FALSE)
	, m_bNobilitylucy(FALSE)
	, m_strKeyNobilityLucy(_T(""))
	, m_strKeyRecureEmblem(_T(""))
	, m_strKeyPickup(_T(""))
	, m_nPickupTimes(0)
	, m_nPickupInerval(0)
	, m_bEableEngergy(FALSE)
	, m_nEnableEnergyTimes(0)
	, m_strLineageWndTitle(_T(""))
{
	ZeroMemory(m_bCheck_HP, sizeof(BOOL) * 3);
	ZeroMemory(m_nPartnerHP, sizeof(UINT) * 3);
	ZeroMemory(m_bInvitePartners, sizeof(BOOL) * 6);
	ZeroMemory(m_nHPKeyCD, sizeof(UINT) * 3);
	ZeroMemory(m_nKeySpecificCD, sizeof(UINT) * 3);
	for (int i = 0; i < 6; i++)
		m_strKeyInvitePartner[i] = (_T(""));
	for (int i = 0; i < 3; i++)
	{
		m_strKeyHP[i] = _T("");
		m_strKeySpecific[i] = _T("");
	}
	
}

CRoleProperty::~CRoleProperty()
{
}

void CRoleProperty::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_FIGHT, m_ctlListFightSkill);
	DDX_Control(pDX, IDC_LIST_BUFFER, m_ctlListBuffer);
	DDX_Control(pDX, IDC_STATIC_DETECTOR, m_ctlDetector);
	DDX_Check(pDX, IDC_CHECK_EXITTEAMDELAY, m_bExitTeamDelay);
	DDX_CBString(pDX, IDC_COMBO_KEY_FOLLOWATTACK, m_strKeyFollowAttak);
	DDX_CBIndex(pDX, IDC_COMBO_TEAMCOUNT, m_nTeamMembers);
	DDX_Radio(pDX, IDC_RADIO_ATTACKMONSTOR, m_bRoleInTeam);
	DDX_Check(pDX, IDC_CHECK_HP1, m_bCheck_HP[0]);
	DDX_Check(pDX, IDC_CHECK_HP2, m_bCheck_HP[1]);
	DDX_Check(pDX, IDC_CHECK_HP3, m_bCheck_HP[2]);
	DDX_Check(pDX, IDC_CHECK_MP1, m_bCheckMP1);
	DDX_Text(pDX, IDC_EDIT_HP1, m_nPartnerHP[0]);
	DDV_MinMaxUInt(pDX, m_nPartnerHP[0], 0, 100);
	DDX_Text(pDX, IDC_EDIT_HP2, m_nPartnerHP[1]);
	DDV_MinMaxUInt(pDX, m_nPartnerHP[1], 0, 100);
	DDX_Text(pDX, IDC_EDIT_HP3, m_nPartnerHP[2]);
	DDV_MinMaxUInt(pDX, m_nPartnerHP[2], 0, 100);
	DDX_Text(pDX, IDC_EDIT_MP1, m_nParntnerMP1);
	DDV_MinMaxUInt(pDX, m_nParntnerMP1, 5, 100);
	DDX_Text(pDX, IDC_EDIT_INVITEPARTNER_DELAY, m_nInvitePartnerDelay);
	DDV_MinMaxUInt(pDX, m_nInvitePartnerDelay, 1, 15);
	DDX_Text(pDX, IDC_EDIT_EXITTEAM_DELAY, m_nExitTeamDelay);
	DDV_MinMaxUInt(pDX, m_nExitTeamDelay, 1, 4294967295);
	DDX_CBString(pDX, IDC_COMBO_KEY_EXITTEAM, m_strKeyExitTeam);
	DDX_Check(pDX, IDC_CHECK_INVITEPARTNER1, m_bInvitePartners[0]);
	DDX_Check(pDX, IDC_CHECK_INVITEPARTNER2, m_bInvitePartners[1]);
	DDX_Check(pDX, IDC_CHECK_INVITEPARTNER3, m_bInvitePartners[2]);
	DDX_Check(pDX, IDC_CHECK_INVITEPARTNER4, m_bInvitePartners[3]);
	DDX_Check(pDX, IDC_CHECK_INVITEPARTNER5, m_bInvitePartners[4]);
	DDX_Check(pDX, IDC_CHECK_INVITEPARTNER6, m_bInvitePartners[5]);
	DDX_CBString(pDX, IDC_COMBO_KEY_INVITEPARTNER1, m_strKeyInvitePartner[0]);
	DDX_CBString(pDX, IDC_COMBO_KEY_INVITEPARTNER2, m_strKeyInvitePartner[1]);
	DDX_CBString(pDX, IDC_COMBO_KEY_INVITEPARTNER3, m_strKeyInvitePartner[2]);
	DDX_CBString(pDX, IDC_COMBO_KEY_INVITEPARTNER4, m_strKeyInvitePartner[3]);
	DDX_CBString(pDX, IDC_COMBO_KEY_INVITEPARTNER5, m_strKeyInvitePartner[4]);
	DDX_CBString(pDX, IDC_COMBO_KEY_INVITEPARTNER6, m_strKeyInvitePartner[5]);
	DDX_Text(pDX, IDC_EDIT_HP1KEYCD, m_nHPKeyCD[0]);
	DDX_Text(pDX, IDC_EDIT_HP2KEYCD, m_nHPKeyCD[1]);
	DDX_Text(pDX, IDC_EDIT_HP2KEYCD, m_nHPKeyCD[2]);
	DDV_MinMaxUInt(pDX, m_nHPKeyCD[0], 0, 3600);
	DDV_MinMaxUInt(pDX, m_nHPKeyCD[1], 0, 3600);
	DDV_MinMaxUInt(pDX, m_nHPKeyCD[2], 0, 3600);
	DDX_CBString(pDX, IDC_COMBO_KEY_HP1, m_strKeyHP[0]);
	DDX_CBString(pDX, IDC_COMBO_KEY_HP2, m_strKeyHP[1]);
	DDX_CBString(pDX, IDC_COMBO_KEY_HP3, m_strKeyHP[2]);
	DDX_CBString(pDX, IDC_COMBO_KEY_TEAMHP, m_strKeyTeamHP);
	DDX_CBString(pDX, IDC_COMBO_KEY_MP, m_strKeyMP);
	DDX_CBString(pDX, IDC_COMBO_KEY_TEAMMP, m_strKeyTeamMP);
	DDX_Text(pDX, IDC_EDIT_MP1KEYCD, m_nMP1KeyCD);
	DDV_MinMaxUInt(pDX, m_nMP1KeyCD, 0, 15);
	DDX_Text(pDX, IDC_EDIT_HPPARTNERS, m_nHPPartners);
	DDV_MinMaxUInt(pDX, m_nHPPartners, 0, 6);
	DDX_Text(pDX, IDC_EDIT_MPPARTNERS, m_nMPPartners);
	DDV_MinMaxUInt(pDX, m_nMPPartners, 0, 6);
	DDX_Text(pDX, IDC_EDIT_KEY_SPECIFIC1CD, m_nKeySpecificCD[0]);
	DDV_MinMaxUInt(pDX, m_nKeySpecificCD[0], 0, 1800);
	DDX_Text(pDX, IDC_EDIT_KEY_SPECIFIC2CD, m_nKeySpecificCD[1]);
	DDV_MinMaxUInt(pDX, m_nKeySpecificCD[1], 0, 1800);
	DDX_Text(pDX, IDC_EDIT_KEY_SPECIFIC2CD, m_nKeySpecificCD[2]);
	DDV_MinMaxUInt(pDX, m_nKeySpecificCD[2], 0, 1800);
	DDX_Check(pDX, IDC_CHECK_ATTACKRANGE, m_bCheckAttackRange);
	DDX_Check(pDX, IDC_CHECK_EXCLUDERANGE, m_bCheckExcludeRange);
	DDX_Check(pDX, IDC_CHECK_MONSTERDIED, m_bCheckMonterDied);
	DDX_CBString(pDX, IDC_COMBO_KEY_MONSTERDIED, m_strKeyMonsterDied);
	DDX_Text(pDX, IDC_EDIT_MONSTORS, m_strMonstorsList);
	DDX_Text(pDX, IDC_EDIT_MONSTOREXCEPT, m_strExcludeMonstors);
	DDX_Text(pDX, IDC_EDIT_ATTACKTIME, m_nAttackNoHurtTime);
	DDV_MinMaxUInt(pDX, m_nAttackNoHurtTime, 0, 5);
	DDX_Check(pDX, IDC_CHECK_ATTACKSPECIFIC, m_bCheckAttackSpecific);
	DDX_Text(pDX, IDC_EDIT_MONSTORSPECIFIC, m_strSpecificMonstors);
	DDX_CBString(pDX, IDC_COMBO_KEY_SPECIFIC1, m_strKeySpecific[0]);
	DDX_CBString(pDX, IDC_COMBO_KEY_SPECIFIC2, m_strKeySpecific[1]);
	DDX_CBString(pDX, IDC_COMBO_KEY_SPECIFIC3, m_strKeySpecific[2]);
	DDX_Check(pDX, IDC_CHECK_MARKSTAR, m_bCheckMakrStart);
	DDX_CBString(pDX, IDC_COMBO_KEY_MARKSTAR, m_strKeyMarkStart);
	DDX_Check(pDX, IDC_CHECK_RESURGENCE, m_bRecvFullResurgence);
	DDX_Check(pDX, IDC_CHECK_RESURGENCEPARTY, m_bResurgencePartners);
	DDX_Check(pDX, IDC_CHECK_RESURGENCEREBUFFER, m_bResurgenceRebuffer);
	DDX_Radio(pDX, IDC_RADIO_NOBILITYLUCKY, m_bNobilitylucy);
	DDX_CBString(pDX, IDC_COMBO_KEY_NOBILITYLUCKY, m_strKeyNobilityLucy);
	DDX_CBString(pDX, IDC_COMBO_KEY_RECUREEMBLEM, m_strKeyRecureEmblem);
	DDX_CBString(pDX, IDC_COMBO_KEY_PICKUP, m_strKeyPickup);
	DDX_Text(pDX, IDC_EDIT_PICKUPCOUNT, m_nPickupTimes);
	DDV_MinMaxUInt(pDX, m_nPickupTimes, 0, 99);
	DDX_Text(pDX, IDC_EDIT_PICKUPINTERVAL, m_nPickupInerval);
	DDV_MinMaxUInt(pDX, m_nPickupInerval, 100, 5000);
	DDX_Check(pDX, IDC_CHECK_ENERGY, m_bEableEngergy);
	DDX_CBIndex(pDX, IDC_COMBO_ENERGY, m_nEnableEnergyTimes);
	DDX_Text(pDX, IDC_EDIT_DESTTITLE, m_strLineageWndTitle);
}


BEGIN_MESSAGE_MAP(CRoleProperty, CDialogEx)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_FIGHT, &CRoleProperty::OnNMDblclkListFight)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_FIGHT, &CRoleProperty::OnNMRClickListFight)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_BUFFER, &CRoleProperty::OnNMDblclkListBuffer)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_BUFFER, &CRoleProperty::OnNMRClickListBuffer)
	ON_BN_CLICKED(IDC_BUTTON_UPDATETITLE, &CRoleProperty::OnBnClickedButtonUpdatetitle)
	ON_NOTIFY(NM_CLICK, IDC_LIST_FIGHT, &CRoleProperty::OnNMClickListFight)
	ON_NOTIFY(NM_CLICK, IDC_LIST_BUFFER, &CRoleProperty::OnNMClickListBuffer)
END_MESSAGE_MAP()


// CRoleProperty 消息处理程序

BOOL CRoleProperty::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ctlListFightSkill.SetExtendedStyle(m_ctlListFightSkill.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

	int nCols = 0;
	m_ctlListFightSkill.InsertColumn(nCols++, _T("序号"), LVCFMT_LEFT, 50);
	m_ctlListFightSkill.InsertColumn(nCols++, _T("按键"), LVCFMT_LEFT, 80);
	m_ctlListFightSkill.InsertColumn(nCols++, _T("施展(ms)"), LVCFMT_LEFT, 100);
	m_ctlListFightSkill.InsertColumn(nCols++, _T("冷却(ms)"), LVCFMT_LEFT, 100);
	m_ctlListFightSkill.InsertColumn(nCols++, _T("重复"), LVCFMT_LEFT, 100);

	m_ctlListBuffer.SetExtendedStyle(m_ctlListBuffer.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

	nCols = 0;
	m_ctlListBuffer.InsertColumn(nCols++, _T("序号"), LVCFMT_LEFT, 50);
	m_ctlListBuffer.InsertColumn(nCols++, _T("按键"), LVCFMT_LEFT, 80);
	m_ctlListBuffer.InsertColumn(nCols++, _T("施展时间(ms)"), LVCFMT_LEFT, 100);
	m_ctlListBuffer.InsertColumn(nCols++, _T("冷却时间(ms)"), LVCFMT_LEFT, 100);
	m_ctlDetector.InitIcon();
	m_ctlDetector.m_hDestWndText = ::GetDlgItem(m_hWnd, IDC_EDIT_DESTTITLE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CRoleProperty::PreTranslateMessage(MSG* pMsg)
{
	if (IsCancelDialogMessage(pMsg))
		return true;
	else
		return CDialog::PreTranslateMessage(pMsg);
}

void CRoleProperty::OnNMDblclkListFight(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

void CRoleProperty::OnNMRClickListFight(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

void CRoleProperty::OnNMDblclkListBuffer(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

void CRoleProperty::OnNMRClickListBuffer(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

void CRoleProperty::OnBnClickedButtonUpdatetitle()
{
	// TODO: Add your control notification handler code here
}


void CRoleProperty::OnNMClickListFight(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CRoleProperty::OnNMClickListBuffer(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}
