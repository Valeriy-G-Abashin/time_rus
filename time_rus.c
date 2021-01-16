/* Copyright (C) 2021 Abashin Valerii Gennadievich.

   This Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   This Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#include "time_rus.h"

#define TSBUF_SIZE 40 /* Time String BUFfer_SIZE */


void strCpy(char *dest, const char *src);
void strCat(char *dest, const char *src);
void addValueWithZero(char * buf, int value);

/* Получение текущего времени */
time_t getCurrentTt(void) {
	return time(NULL);
}

struct tm * getCurrentLocalTm(void) {
	time_t ctt = getCurrentTt();
	return ttToLocalTm(&ctt);
}

struct tm * getCurrentGmTm(void) {
	time_t ctt = getCurrentTt();
	return ttToGmTm(&ctt);
}

/* Получение процессорных тиков */
clock_t getClock(void) {
	return clock();
}

/* Сравнение процессорных тиков */
clock_t diffClock(clock_t first, clock_t second, clock_t *clocks_per_sec) {
	*clocks_per_sec = CLOCKS_PER_SEC;
	if (second >= first)
		return second-first;
	return -1;
}

/* Получение разности между временем tt/tm */
double diffTimeTt(time_t first_tt, time_t second_tt) {
	return difftime(second_tt, first_tt);
}
double diffTimeTm(struct tm *first_tm, struct tm *second_tm) {
	time_t first_tt = gmTmToTt(first_tm);
	time_t second_tt = gmTmToTt(second_tm);
	return diffTimeTt(first_tt, second_tt);
}

/* Преобразование time_t в struct tm(localtime) */
struct tm * ttToLocalTm(time_t *t) {
	return localtime(t);
}
/* Преобразование struct tm(localtime) в time_t */
time_t localTmToTt(struct tm *st_tm) {
	return mktime(st_tm);
}
/* Преобразование time_t в struct tm(gmtine) */
struct tm * ttToGmTm(time_t *t) {
	return gmtime(t);
}
/* Преобразование struct tm(gmtime) в time_t */
time_t gmTmToTt(struct tm *st_tm) {
	return timegm(st_tm);
}

/* Преобразование YYYY.MM.DD HH:MM:SS в struct tm */
struct tm * stringToTm(char *buf) {
	int year, mon, day, hour, min, sec;
	year = mon = day = hour = min = sec = 0;
	sscanf(buf, "%d.%d.%d %d:%d:%d", &year, &mon, &day,
			&hour, &min, &sec);
	return YMDHMStoTM(year, mon, day, hour, min, sec);
}

struct tm * YMDHMStoTM(int year, int mon, int day,
		int hour, int min, int sec) {
	time_t t = time(NULL);
	struct tm *st_tm = ttToLocalTm(&t);
	st_tm->tm_year = year - 1900;
	st_tm->tm_mon = mon - 1;
	st_tm->tm_mday = day;
	st_tm->tm_hour = hour;
	st_tm->tm_min = min;
	st_tm->tm_sec = sec;
	return st_tm;
}

/* Преобразование struct tm в YYYY.MM.DD HH:MM:SS*/
char * tmToString(struct tm * st_tm, char * buf, int32_t buf_len) {
	if (buf_len < 40)
		return NULL;
	char temp[10] = {0};
	char zero[4] = "0";
	sprintf(temp, "%d.", st_tm->tm_year + 1900);
	strCpy(buf, temp);
	addValueWithZero(buf, st_tm->tm_mon + 1);
	addValueWithZero(buf, st_tm->tm_mday);
	addValueWithZero(buf, st_tm->tm_hour);
	addValueWithZero(buf, st_tm->tm_min);
	addValueWithZero(buf, st_tm->tm_sec);
	return buf;
}

void addValueWithZero(char * buf, int value) {
	char temp[10] = {0};
	char zero[4] = "0";
	if (value < 10)
		strCat(buf, zero);
	sprintf(temp, "%d:", value);
	strCat(buf, temp);
}

void strCpy(char *dest, const char *src) {
	int count = 0;
	while (src[count] != 0) {
		dest[count] = src[count];
		count++;
	}
	dest[count] = 0;
}

void strCat(char *dest, const char *src) {
	int count_dest = 0;
	int count_src = 0;
	while (dest[count_dest] != 0)
		count_dest++;
	while (src[count_src] != 0) {
		dest[count_dest] = src[count_src];
		count_src++;
		count_dest++;
	}
	dest[count_dest] = 0;
}

/* Преобразование time_t в YYYY.MM.DD HH:MM:SS*/
char * ttToLocalString(time_t *t, char *buf, int32_t buf_len) {
	return tmToString(ttToLocalTm(t), buf, buf_len);
}

char * ttToGmString(time_t *t, char *buf, int32_t buf_len) {
	return tmToString(ttToGmTm(t), buf, buf_len);
}

/* функция получение из time_t локальный */
int getLocalSec(time_t tt) { /* секунды (0-60) */
	struct tm * stm = ttToLocalTm(&tt);
	return stm->tm_sec;
}
int getLocalMin(time_t tt) { /* минуты (0-59) */
	struct tm * stm = ttToLocalTm(&tt);
	return stm->tm_min;
}
int getLocalHour(time_t tt) { /* часы (0-23) */
	struct tm * stm = ttToLocalTm(&tt);
	return stm->tm_hour;
}
int getLocalMday(time_t tt) { /* день в месяце (1-31) */
	struct tm * stm = ttToLocalTm(&tt);
	return stm->tm_mday;
}
int getLocalMon(time_t tt) { /* месяц (0-11) */
	struct tm * stm = ttToLocalTm(&tt);
	return stm->tm_mon;
}
int getLocalYear(time_t tt) { /* год */
	struct tm * stm = ttToLocalTm(&tt);
	return stm->tm_year + 1900;
}
int getLocalWday(time_t tt) { /* день недели (0-6, воскресенье = 0) */
	struct tm * stm = ttToLocalTm(&tt);
	return stm->tm_wday;
}
int getLocalYday(time_t tt) { /* день в году (0-365, 1 январь = 0) */
	struct tm * stm = ttToLocalTm(&tt);
	return stm->tm_yday;
}
int getLocalDst(time_t tt) { /* летнее время */
	struct tm * stm = ttToLocalTm(&tt);
	return stm->tm_isdst;
}

/* функция получение из time_t GM */
int getGmSec(time_t tt) { /* секунды (0-60) */
	struct tm * stm = ttToGmTm(&tt);
	return stm->tm_sec;
}
int getGmMin(time_t tt) { /* минуты (0-59) */
	struct tm * stm = ttToGmTm(&tt);
	return stm->tm_min;
}
int getGmHour(time_t tt) { /* часы (0-23) */
	struct tm * stm = ttToGmTm(&tt);
	return stm->tm_hour;
}
int getGmMday(time_t tt) { /* день в месяце (1-31) */
	struct tm * stm = ttToGmTm(&tt);
	return stm->tm_mday;
}
int getGmMon(time_t tt) { /* месяц (0-11) */
	struct tm * stm = ttToGmTm(&tt);
	return stm->tm_mon;
}
int getGmYear(time_t tt) { /* год - 1900 */
	struct tm * stm = ttToGmTm(&tt);
	return stm->tm_year + 1900;
}
int getGmWday(time_t tt) { /* день недели (0-6, воскресенье = 0) */
	struct tm * stm = ttToGmTm(&tt);
	return stm->tm_wday;
}
int getGmYday(time_t tt) { /* день в году (0-365, 1 январь = 0) */
	struct tm * stm = ttToGmTm(&tt);
	return stm->tm_yday;
}
int getGmDst(time_t tt) { /* летнее время */
	struct tm * stm = ttToGmTm(&tt);
	return stm->tm_isdst;
}

