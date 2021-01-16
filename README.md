# time_rus
Copyright (C) 2021 Abashin Valerii Gennadievich.

Contains functions:

	- Getting the current time
		time_t getCurrentTt(void);
		struct tm * getCurrentLocalTm(void);
		struct tm * getCurrentGmTm(void);
	- Getting the difference between timestamps
		(WARNING: Don't compare local and GM time)
		double diffTimeTt(time_t first_tt, time_t second_tt);
		double diffTimeTm(struct tm *first_tm, struct tm *second_tm);
	- Getting the CPU ticks. Use within a few seconds.
		clock_t getClock(void);
	- Comparison of processor ticks
		clock_t diffClock(clock_t first, clock_t second, clock_t *clocks_per_sec);
	- Converting time_t to struct tm(localtime)
		struct tm * ttToLocalTm(time_t *t);
	- Converting struct tm(localtime) to time_t
		time_t localTmToTt(struct tm *st_tm);
	- Converting time_t to struct tm(gmtine)
		struct tm * ttToGmTm(time_t *t);
	- Converting struct tm(gmtime) to time_t
		time_t gmTmToTt(struct tm *st_tm);
	- Converting YYYY.MM.DD HH:MM:SS to struct tm
		struct tm * stringToTm(char *buf);
		struct tm * YMDHMStoTM(int year, int mon, int day,
			int hour, int min, int sec);
	-Converting struct tm to YYYY.MM.DD HH:MM:SS
		char * tmToString(struct tm * st_tm, char * buf, int32_t buf_len);
	- Converting time_t to YYYY.MM.DD HH:MM:SS
		char * ttToLocalString(time_t *t, char *buf, int32_t buf_len);
		char * ttToGmString(time_t *t, char *buf, int32_t buf_len);
	- Functions of receiving from a local time_t values
		int getLocalSec(time_t tt); /* (0-60) */
		int getLocalMin(time_t tt); /* (0-59) */
		int getLocalHour(time_t tt); /* (0-23) */
		int getLocalMday(time_t tt); /* (1-31) */
		int getLocalMon(time_t tt); /* (0-11) */
		int getLocalYear(time_t tt); /* year */
		int getLocalWday(time_t tt); /* (0-6, sunday = 0) */
		int getLocalYday(time_t tt); /* (0-365, 1 january = 0) */
		int getLocalDst(time_t tt); /* daylight saving time */
	- Functions of receiving from a GM time_t values
		int getGmSec(time_t tt); /* (0-60) */
		int getGmMin(time_t tt); /* (0-59) */
		int getGmHour(time_t tt); /* (0-23) */
		int getGmMday(time_t tt); /* (1-31) */
		int getGmMon(time_t tt); /* (0-11) */
		int getGmYear(time_t tt); /* year */
		int getGmWday(time_t tt); /* (0-6, sunday = 0) */
		int getGmYday(time_t tt); /* (0-365, 1 january = 0) */
		int getGmDst(time_t tt); /* daylight saving time */
