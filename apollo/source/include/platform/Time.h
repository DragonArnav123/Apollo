/*
Initialization: Provide methods for initializing the time system, such as starting the timer or setting the initial time point.
Frame Timing: Methods for measuring the time elapsed between frames, allowing you to maintain a consistent frame rate and update your game or simulation accordingly.
Time Retrieval: Functions for retrieving the current time, either as an absolute value or as a delta from a previous time point.
Frame Rate Calculation: Ability to calculate the frame rate based on the elapsed time between frames.
Sleeping: Capability to pause execution for a specified period, useful for controlling the frame rate or introducing delays.
Time Conversions: Functions for converting between different time units (e.g., seconds, milliseconds, microseconds) to suit various needs within your engine.
High Precision Timing: If your engine requires high precision timing, consider providing methods for accessing high-resolution timers available on the platform.
Time Scaling: Optional functionality to scale time, allowing for effects like slow motion or time dilation within your engine.
Timer Events: Support for timer events or callbacks that trigger at specified intervals.
Platform Abstraction: Ensure that the Time class is abstracted away from platform-specific implementations, allowing you to swap out implementations for different platforms without affecting the rest of your codebase.
*/
#pragma once

#include "../core/Core.h"

namespace Apollo {
namespace Pltfrm {

	struct APOLLO_API TimePoint
	{
		APi32 H;
		APi32 M;
		APi32 S;
		APi32 MS;

		TimePoint()
		{
		}

		TimePoint(APi32 h, APi32 m, APi32 s, APi32 ms)
			: 
			H(h), M(m), S(s), MS(ms)
		{
		}
		
		TimePoint operator -(const TimePoint &tp);
		void operator = (const TimePoint &tp);
	};

	struct APOLLO_API Timer
	{
		using Handle = APsize;

		TimePoint StartPoint;
		TimePoint EndPoint;

		Timer()
		{
		}

		Timer(const TimePoint &startPoint, const TimePoint &endPoint)
			:
			StartPoint(startPoint),
			EndPoint(endPoint)
		{
		}
	};

	class APOLLO_API Time
	{
	public:
		using HighP = APf64;
		using LowP = APf32;

	public:
		Time();
		virtual ~Time();

		static void Initialize();
		static void Terminate();

		static TimePoint GetCurrentTime();
		static TimePoint GetEpoch();
		static const TimePoint &TimeElapsedFromLastGetEpochCall();

		static LowP SecondToMillisecond(LowP t);
		static LowP SecondToMicrosecond(LowP t);
		static LowP SecondToNanosecond(LowP t);
		static LowP MillsecondToSecond(LowP t);
		static LowP MillsecondToMicrosecond(LowP t);
		static LowP MillsecondToNanosecond(LowP t);
		static LowP MicrosecondToSecond(LowP t);
		static LowP MicrosecondToMillisecond(LowP t);
		static LowP MicrosecondToNanosecond(LowP t);
		static LowP NanosecondToSecond(LowP t);
		static LowP NanosecondToMillisecond(LowP t);
		static LowP NanosecondToMicrosecond(LowP t);

		static HighP SecondToMillisecond(HighP t);
		static HighP SecondToMicrosecond(HighP t);
		static HighP SecondToNanosecond(HighP t);
		static HighP MillsecondToSecond(HighP t);
		static HighP MillsecondToMicrosecond(HighP t);
		static HighP MillsecondToNanosecond(HighP t);
		static HighP MicrosecondToSecond(HighP t);
		static HighP MicrosecondToMillisecond(HighP t);
		static HighP MicrosecondToNanosecond(HighP t);
		static HighP NanosecondToSecond(HighP t);
		static HighP NanosecondToMillisecond(HighP t);
		static HighP NanosecondToMicrosecond(HighP t);

		static LowP TimePointToHourLowP(const TimePoint &tp);
		static LowP TimePointToMinuteLowP(const TimePoint &tp);
		static LowP TimePointToSecondLowP(const TimePoint &tp);
		static APi32 TimePointToMillisecond(const TimePoint &tp);
		static HighP TimePointToHourHighP(const TimePoint &tp);
		static HighP TimePointToMinuteHighP(const TimePoint &tp);
		static HighP TimePointToSecondHighP(const TimePoint &tp);


		static Timer::Handle AddTimer(const Timer &timer);
		static void RemoveTimer(Timer::Handle handle);
		static void AlterTimer(Timer::Handle handle, const TimePoint &startPoint, const TimePoint &endPoint);

		static void PrintTime();
		static void PrintTime(const TimePoint &tp);

	private:
		static std::vector<Timer> s_Timers;
		static TimePoint s_LastCallToGetEpoch;
	};

}
}