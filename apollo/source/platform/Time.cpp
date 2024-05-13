#include "../include/APpch.h"
#include "../include/platform/Time.h"
#include "../include/core/Log.h"

namespace Apollo {
namespace Internal {
	AP_INTERNAL_FUNC ::Apollo::Pltfrm::TimePoint CurrentTime()
	{
#if defined(APOLLO_PLATFORM_WINDOWS)
		SYSTEMTIME systemTime;
		GetLocalTime(&systemTime);
		return Pltfrm::TimePoint(
			systemTime.wHour,
			systemTime.wMinute,
			systemTime.wSecond,
			systemTime.wMilliseconds
		);
#endif
		return Pltfrm::TimePoint(0, 0, 0, 0);
	}

}

namespace Pltfrm {

	AP_GLOBAL_VAR const APf32 g_SMsCFLP = 1000.0f;
	AP_GLOBAL_VAR const APf32 g_SMcsCFLP = 1000000.0f;
	AP_GLOBAL_VAR const APf32 g_SNsCFLP = 1000000000.0f;
	AP_GLOBAL_VAR const APf32 g_MsMcsCFLP = 1000.0f;
	AP_GLOBAL_VAR const APf32 g_MsNsCFLP = 1000000.0f;
	AP_GLOBAL_VAR const APf32 g_McsNsCFLP = 1000.0f;

	AP_GLOBAL_VAR const APf32 g_SMsCFHP = 1000.0;
	AP_GLOBAL_VAR const APf32 g_SMcsCFHP = 1000000.0;
	AP_GLOBAL_VAR const APf32 g_SNsCFHP = 1000000.0;
	AP_GLOBAL_VAR const APf32 g_MsMcsCFHP = 1000.0;
	AP_GLOBAL_VAR const APf32 g_MsNsCFHP = 1000000.0;
	AP_GLOBAL_VAR const APf32 g_McsNsCFHP = 1000.0;

	struct Timings
	{
		TimePoint InitTime;
		TimePoint LastEpochCallTime;
	};

	AP_GLOBAL_VAR Timings g_Timings;

	TimePoint TimePoint::operator -(const TimePoint &tp)
	{
		return TimePoint(
			this->H - tp.H,
			this->M - tp.M,
			this->S - tp.S,
			this->MS - tp.MS
		);
	}

	void TimePoint::operator = (const TimePoint &tp)
	{
		H = tp.H;
		M = tp.M;
		S = tp.S;
		MS = tp.MS;
	}

	std::vector<Timer> Time::s_Timers = std::vector<Timer>(0);

	Time::Time()
	{
	}

	Time::~Time()
	{
	}

	void Time::Initialize()
	{
		g_Timings.InitTime = Time::GetCurrentTime();
	}

	void Time::Terminate()
	{
	}

	TimePoint Time::GetCurrentTime()
	{
		return Internal::CurrentTime();
	}

	TimePoint Time::GetEpoch()
	{
		TimePoint currentTime = Time::GetCurrentTime();
		g_Timings.LastEpochCallTime = currentTime;
		return currentTime - g_Timings.InitTime;
	}

	const TimePoint &Time::TimeElapsedFromLastGetEpochCall()
	{
		return g_Timings.LastEpochCallTime;
	}

	Time::LowP Time::SecondToMillisecond(LowP t)
	{
		return t * g_SMsCFLP;
	}

	Time::LowP Time::SecondToMicrosecond(LowP t)
	{
		return t * g_SMcsCFLP;
	}

	Time::LowP Time::SecondToNanosecond(LowP t)
	{
		return t * g_SNsCFLP;
	}

	Time::LowP Time::MillsecondToSecond(LowP t)
	{
		return t / g_SMsCFLP;
	}

	Time::LowP Time::MillsecondToMicrosecond(LowP t)
	{
		return t * g_MsMcsCFLP;
	}

	Time::LowP Time::MillsecondToNanosecond(LowP t)
	{
		return t * g_MsNsCFLP;
	}

	Time::LowP Time::MicrosecondToSecond(LowP t)
	{
		return t / g_SMcsCFLP;
	}

	Time::LowP Time::MicrosecondToMillisecond(LowP t)
	{
		return t / g_MsMcsCFLP;
	}

	Time::LowP Time::MicrosecondToNanosecond(LowP t)
	{
		return t / g_McsNsCFLP;
	}

	Time::LowP Time::NanosecondToSecond(LowP t)
	{
		return t / g_SNsCFLP;
	}

	Time::LowP Time::NanosecondToMillisecond(LowP t)
	{
		return t / g_MsNsCFLP;
	}

	Time::LowP Time::NanosecondToMicrosecond(LowP t)
	{
		return t / g_McsNsCFLP;
	}

	Time::HighP Time::SecondToMillisecond(HighP t)
	{
		return t * g_SMsCFHP;
	}

	Time::HighP Time::SecondToMicrosecond(HighP t)
	{		
		return t * g_SMcsCFHP;
	}

	Time::HighP Time::SecondToNanosecond(HighP t)
	{
		return t * g_SNsCFHP;
	}

	Time::HighP Time::MillsecondToSecond(HighP t)
	{
		return t / g_SMsCFHP;
	}

	Time::HighP Time::MillsecondToMicrosecond(HighP t)
	{
		return t * g_MsMcsCFHP;
	}

	Time::HighP Time::MillsecondToNanosecond(HighP t)
	{
		return t * g_MsNsCFHP;
	}

	Time::HighP Time::MicrosecondToSecond(HighP t)
	{
		return t / g_SMcsCFHP;
	}

	Time::HighP Time::MicrosecondToMillisecond(HighP t)
	{
		return t / g_MsMcsCFHP;
	}

	Time::HighP Time::MicrosecondToNanosecond(HighP t)
	{
		return t * g_McsNsCFHP;
	}

	Time::HighP Time::NanosecondToSecond(HighP t)
	{
		return t / g_SNsCFHP;
	}

	Time::HighP Time::NanosecondToMillisecond(HighP t)
	{
		return t / g_MsNsCFHP;
	}

	Time::HighP Time::NanosecondToMicrosecond(HighP t)
	{
		return t / g_McsNsCFHP;
	}

	Time::LowP Time::TimePointToHourLowP(const TimePoint &tp)
	{
		return (LowP) (tp.H + tp.M / 60 + tp.S / 3600 + tp.MS / (1000 * 3600));
	}

	Time::LowP Time::TimePointToMinuteLowP(const TimePoint &tp)
	{
		return (LowP) (tp.H * 60 + tp.M + tp.S / 60 + tp.MS / (1000 * 60));
	}

	Time::LowP Time::TimePointToSecondLowP(const TimePoint &tp)
	{
		return (LowP) (tp.H * 3600 + tp.M *60 + tp.S + tp.MS / 1000);
	}

	APi32 Time::TimePointToMillisecond(const TimePoint &tp)
	{
		return (LowP) (1000.0f * (tp.H * 3600 + tp.M *60 + tp.S + tp.MS / 1000));
	}

	Time::HighP Time::TimePointToHourHighP(const TimePoint &tp)
	{
		return (HighP) (tp.H + tp.M / 60 + tp.S / 3600 + tp.MS / (1000 * 3600));
	}

	Time::HighP Time::TimePointToMinuteHighP(const TimePoint &tp)
	{
		return (HighP) (tp.H * 60 + tp.M + tp.S / 60 + tp.MS / (1000 * 60));
	}

	Time::HighP Time::TimePointToSecondHighP(const TimePoint &tp)
	{
		return (HighP) (tp.H * 3600 + tp.M *60 + tp.S + tp.MS / 1000);
	}

	Timer::Handle Time::AddTimer(const Timer &timer)
	{
		s_Timers.push_back(timer);
		return s_Timers.size() - 1;
	}

	void Time::RemoveTimer(Timer::Handle handle)
	{
		s_Timers.erase(s_Timers.begin() + handle);
	}

	void Time::AlterTimer(Timer::Handle handle, const TimePoint &startPoint, const TimePoint &endPoint)
	{
		s_Timers[handle] = Timer(
			startPoint,
			endPoint
		);
	}

	void Time::PrintTime()
	{
		Time::PrintTime(Time::GetCurrentTime());
	}

	void Time::PrintTime(const TimePoint &tp)
	{
		AP_CORE_INFO("H:{} M:{} S:{} MS:{} ", tp.H, tp.M, tp.S, tp.MS);
	}

}
}