#pragma once
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
class CMMEvent
{
	MMRESULT nTimerID;				///< ��ý�嶨ʱ��ID����Ҫʹ�ö�ý�嶨ʱ��	
	HANDLE	 &hEvent;				///< ֪ͨ�¼�
public:
	int		 nPeriod;
	CMMEvent(HANDLE &hEventInput, int nPeriodInput = 40)
		:hEvent(hEventInput),
		nPeriod(nPeriodInput)
	{
		nPeriod = nPeriodInput;
		nTimerID = timeSetEvent(nPeriod, 1, (LPTIMECALLBACK)hEvent, (DWORD_PTR)this, TIME_PERIODIC | TIME_KILL_SYNCHRONOUS | TIME_CALLBACK_EVENT_SET);
	}

	void UpdateInterval(int nPeriodInput = 40)
	{
		timeKillEvent(nTimerID);
		nPeriod = nPeriodInput;
		nTimerID = timeSetEvent(nPeriod, 1, (LPTIMECALLBACK)hEvent, (DWORD_PTR)this, TIME_PERIODIC | TIME_KILL_SYNCHRONOUS | TIME_CALLBACK_EVENT_SET);
	}
	~CMMEvent()
	{
		timeKillEvent(nTimerID);
		nTimerID = 0;
	}
};

