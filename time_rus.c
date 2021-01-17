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
int strToInt(const char *value);
char * intToStr(const int value, char *str);
int digit(const int value);
void addValueWithZero(char *buf, const int value);

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
clock_t diffClock(const clock_t first, const clock_t second,
		clock_t *clocks_per_sec) {
	*clocks_per_sec = CLOCKS_PER_SEC;
	if (second >= first)
		return second-first;
	return -1;
}

/* Получение разности между временем tt/tm */
double diffTimeTt(const time_t first_tt, const time_t second_tt) {
	return difftime(second_tt, first_tt);
}
double diffTimeTm(struct tm *first_tm, struct tm *second_tm) {
	time_t first_tt = gmTmToTt(first_tm);
	time_t second_tt = gmTmToTt(second_tm);
	return diffTimeTt(first_tt, second_tt);
}

/* Преобразование time_t в struct tm(localtime) */
struct tm * ttToLocalTm(const time_t *t) {
	return localtime(t);
}
/* Преобразование struct tm(localtime) в time_t */
time_t localTmToTt(struct tm *st_tm) {
	return mktime(st_tm);
}
/* Преобразование time_t в struct tm(gmtine) */
struct tm * ttToGmTm(const time_t *t) {
	return gmtime(t);
}
/* Преобразование struct tm(gmtime) в time_t */
time_t gmTmToTt(struct tm *st_tm) {
	time_t result = 0;
	/* Подсчет секунд в полных годах */
	int year = 1970;
	int cur_year = st_tm->tm_year + 1900;
	for ( ; year < cur_year; year++) {
		if (year % 4 == 0)
			result += 31622400; /* 31622400 - год 366 дней */
		else
			result += 31536000; /* 31536000 - год 365 дней */
	}
	/* дней в году, часов, минут, секунд */
	result += st_tm->tm_yday * 86400 +
		st_tm->tm_hour * 3600 +
		st_tm->tm_min * 60 +
		st_tm->tm_sec;
	return result;
}

/* Преобразование YYYY.MM.DD HH:MM.SS в struct tm */
struct tm * stringToTm(const char *buf) {
	int year, mon, day, hour, min, sec;
	year = mon = day = hour = min = sec = 0;
	char temp[10] = {0};
	temp[0] = buf[0];
	temp[1] = buf[1];
	temp[2] = buf[2];
	temp[3] = buf[3];
	temp[4] = 0;
	year = strToInt(temp);
	temp[0] = buf[5];
	temp[1] = buf[6];
	temp[2] = 0;
	mon = strToInt(temp);
	temp[0] = buf[8];
	temp[1] = buf[9];
	temp[2] = 0;
	day = strToInt(temp);
	temp[0] = buf[11];
	temp[1] = buf[12];
	temp[2] = 0;
	hour = strToInt(temp);
	temp[0] = buf[14];
	temp[1] = buf[15];
	temp[2] = 0;
	min = strToInt(temp);
	temp[0] = buf[17];
	temp[1] = buf[18];
	temp[2] = 0;
	sec = strToInt(temp);
	return YMDHMStoTM(year, mon, day, hour, min, sec);
}

struct tm * YMDHMStoTM(const int year, const int mon, const int day,
		const int hour, const int min, const int sec) {
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
char * tmToString(struct tm * st_tm, char * buf, const int32_t buf_len) {
	if (buf_len < 40)
		return NULL;
	char temp[10] = {0};
	char dot[] = ".";
	intToStr(st_tm->tm_year + 1900, temp);
	strCpy(buf, temp);
	strCat(buf, dot);
	addValueWithZero(buf, st_tm->tm_mon + 1);
	strCat(buf, dot);
	addValueWithZero(buf, st_tm->tm_mday);
	strCat(buf, " ");
	addValueWithZero(buf, st_tm->tm_hour);
	strCat(buf, ":");
	addValueWithZero(buf, st_tm->tm_min);
	strCat(buf, dot);
	addValueWithZero(buf, st_tm->tm_sec);
	return buf;
}

/* Преобразование time_t в YYYY.MM.DD HH:MM:SS*/
char * ttToLocalString(const time_t *t, char *buf, const int32_t buf_len) {
	return tmToString(ttToLocalTm(t), buf, buf_len);
}

char * ttToGmString(const time_t *t, char *buf, const int32_t buf_len) {
	return tmToString(ttToGmTm(t), buf, buf_len);
}

/* функция получение из time_t локальный */
int getLocalSec(const time_t tt) { /* секунды (0-60) */
	struct tm * stm = ttToLocalTm(&tt);
	return stm->tm_sec;
}
int getLocalMin(const time_t tt) { /* минуты (0-59) */
	struct tm * stm = ttToLocalTm(&tt);
	return stm->tm_min;
}
int getLocalHour(const time_t tt) { /* часы (0-23) */
	struct tm * stm = ttToLocalTm(&tt);
	return stm->tm_hour;
}
int getLocalMday(const time_t tt) { /* день в месяце (1-31) */
	struct tm * stm = ttToLocalTm(&tt);
	return stm->tm_mday;
}
int getLocalMon(const time_t tt) { /* месяц (0-11) */
	struct tm * stm = ttToLocalTm(&tt);
	return stm->tm_mon;
}
int getLocalYear(const time_t tt) { /* год */
	struct tm * stm = ttToLocalTm(&tt);
	return stm->tm_year + 1900;
}
int getLocalWday(const time_t tt) { /* день недели (0-6, воскресенье = 0) */
	struct tm * stm = ttToLocalTm(&tt);
	return stm->tm_wday;
}
int getLocalYday(const time_t tt) { /* день в году (0-365, 1 январь = 0) */
	struct tm * stm = ttToLocalTm(&tt);
	return stm->tm_yday;
}
int getLocalDst(const time_t tt) { /* летнее время */
	struct tm * stm = ttToLocalTm(&tt);
	return stm->tm_isdst;
}

/* функция получение из time_t GM */
int getGmSec(const time_t tt) { /* секунды (0-60) */
	struct tm * stm = ttToGmTm(&tt);
	return stm->tm_sec;
}
int getGmMin(const time_t tt) { /* минуты (0-59) */
	struct tm * stm = ttToGmTm(&tt);
	return stm->tm_min;
}
int getGmHour(const time_t tt) { /* часы (0-23) */
	struct tm * stm = ttToGmTm(&tt);
	return stm->tm_hour;
}
int getGmMday(const time_t tt) { /* день в месяце (1-31) */
	struct tm * stm = ttToGmTm(&tt);
	return stm->tm_mday;
}
int getGmMon(const time_t tt) { /* месяц (0-11) */
	struct tm * stm = ttToGmTm(&tt);
	return stm->tm_mon;
}
int getGmYear(const time_t tt) { /* год - 1900 */
	struct tm * stm = ttToGmTm(&tt);
	return stm->tm_year + 1900;
}
int getGmWday(const time_t tt) { /* день недели (0-6, воскресенье = 0) */
	struct tm * stm = ttToGmTm(&tt);
	return stm->tm_wday;
}
int getGmYday(const time_t tt) { /* день в году (0-365, 1 январь = 0) */
	struct tm * stm = ttToGmTm(&tt);
	return stm->tm_yday;
}
int getGmDst(const time_t tt) { /* летнее время */
	struct tm * stm = ttToGmTm(&tt);
	return stm->tm_isdst;
}

/* Library function */
char * intToStr(const int value, char *str) {
	/* получить все разряды */
	int value_ = value;
	int count = 0;
	do {
		switch (value_ % 10) {
			case 0: str[count] = '0'; break;
			case 1: str[count] = '1'; break;
			case 2: str[count] = '2'; break;
			case 3: str[count] = '3'; break;
			case 4: str[count] = '4'; break;
			case 5: str[count] = '5'; break;
			case 6: str[count] = '6'; break;
			case 7: str[count] = '7'; break;
			case 8: str[count] = '8'; break;
			case 9: str[count] = '9'; break;
		}
		count++;
	} while ((value_ /= 10) != 0);
	str[count] = 0;
	/* Перевернуть число в правильный порядок */
	char temp = 0;
	int top, bottom;
	top = count - 1;
	bottom = 0;
	for ( ; bottom < top; top--, bottom++) {
		temp = str[top];
		str[top] = str[bottom];
		str[bottom] = temp;
	}
	return str;
}

int digit(const int value) {
	int result = 1;
	int count = 0;
	for (count = 0; count < value; count++)
		result *= 10;
	return result;
}

int strToInt(const char *value) {
	int result = 0;
	int count = 0;
	while (value[count] != 0)
		count++;
	if (count)
		count--;
	int count_digit = 0;
	for ( ; count >= 0; count--) {
		switch(value[count]) {
			case '1': result += 1 * digit(count_digit); break;
			case '2': result += 2 * digit(count_digit); break;
			case '3': result += 3 * digit(count_digit); break;
			case '4': result += 4 * digit(count_digit); break;
			case '5': result += 5 * digit(count_digit); break;
			case '6': result += 6 * digit(count_digit); break;
			case '7': result += 7 * digit(count_digit); break;
			case '8': result += 8 * digit(count_digit); break;
			case '9': result += 9 * digit(count_digit); break;
		}
		count_digit++;
	}
	return result;
}

void addValueWithZero(char *buf, const int value) {
	char temp[10] = {0};
	if (value < 10)
		strCat(buf, "0");
	intToStr(value, temp);
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

