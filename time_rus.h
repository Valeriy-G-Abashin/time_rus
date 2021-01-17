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

/* NOTES:
time_t always GM. Localtime/GM only struct tm.
system struct tm * - only one for thread!
tt(Tt) - time_t
tm(Tm) - struct tm
string(String) - char *
*/
#include <time.h>
#include <stdint.h>

#define TSBUF_SIZE 40 /* Time String BUFfer_SIZE */


/* Получение текущего времени */
time_t getCurrentTt(void);
struct tm * getCurrentLocalTm(void);
struct tm * getCurrentGmTm(void);

/* Получение разности между временными метками */
/* ПРЕДУПРЕЖДЕНИЕ: Не сравнивать местное и GM время */
double diffTimeTt(const time_t first_tt, const time_t second_tt);
double diffTimeTm(struct tm *first_tm, struct tm *second_tm);

/* Получение процессорных тиков. Использовать в пределах секунды. */
clock_t getClock(void);
/* Сравнение процессорных тиков */
clock_t diffClock(const clock_t first, const clock_t second,
	clock_t *clocks_per_sec);

/* Преобразование time_t в struct tm(localtime) */
struct tm * ttToLocalTm(const time_t *t);
/* Преобразование struct tm(localtime) в time_t */
time_t localTmToTt(struct tm *st_tm);
/* Преобразование time_t в struct tm(gmtine) */
struct tm * ttToGmTm(const time_t *t);
/* Преобразование struct tm(gmtime) в time_t */
time_t gmTmToTt(struct tm *st_tm);
/* Преобразование YYYY.MM.DD HH:MM:SS в struct tm */
struct tm * stringToTm(const char *buf);
struct tm * YMDHMStoTM(const int year, const int mon, const int day,
		const int hour, const int min, const int sec);
/* Преобразование struct tm в YYYY.MM.DD HH:MM:SS*/
char * tmToString(struct tm * st_tm, char * buf, const int32_t buf_len);
/* Преобразование time_t в YYYY.MM.DD HH:MM:SS*/
char * ttToLocalString(const time_t *t, char *buf, const int32_t buf_len);
char * ttToGmString(const time_t *t, char *buf, const int32_t buf_len);

/* функция получение из time_t локальный */
int getLocalSec(const time_t tt); /* секунды (0-60) */
int getLocalMin(const time_t tt); /* минуты (0-59) */
int getLocalHour(const time_t tt); /* часы (0-23) */
int getLocalMday(const time_t tt); /* день в месяце (1-31) */
int getLocalMon(const time_t tt); /* месяц (0-11) */
int getLocalYear(const time_t tt); /* год */
int getLocalWday(const time_t tt); /* день недели (0-6, воскресенье = 0) */
int getLocalYday(const time_t tt); /* день в году (0-365, 1 январь = 0) */
int getLocalDst(const time_t tt); /* летнее время */
/* функция получение из time_t GM */
int getGmSec(const time_t tt); /* секунды (0-60) */
int getGmMin(const time_t tt); /* минуты (0-59) */
int getGmHour(const time_t tt); /* часы (0-23) */
int getGmMday(const time_t tt); /* день в месяце (1-31) */
int getGmMon(const time_t tt); /* месяц (0-11) */
int getGmYear(const time_t tt); /* год */
int getGmWday(const time_t tt); /* день недели (0-6, воскресенье = 0) */
int getGmYday(const time_t tt); /* день в году (0-365, 1 январь = 0) */
int getGmDst(const time_t tt); /* летнее время */

