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

/* gcc time_rus.c example.c -o example && ./example */
#include <stdio.h>
#include <string.h>
#include "time_rus.h"

int main() {

	clock_t start = getClock();
	time_t start_tt = getCurrentTt();

	/* Преобразование time_t(localtime) в struct tm */
	time_t t = getCurrentTt();
	printf("Текущее время: %ld\n", t);
	struct tm * st = ttToLocalTm(&t);
	char buf[TSBUF_SIZE] = {0};
	tmToString(st, buf, TSBUF_SIZE);
	printf("Текущее локальное время: %s\n", buf);
	/* Преобразование struct tm(localtime) в time_t */
	printf("Текущее время из локального: %ld\n", localTmToTt(st));
	/* Преобразование time_t(gmtime) в struct tm */
	struct tm * st_gm = ttToGmTm(&t);
	tmToString(st_gm, buf, TSBUF_SIZE);
	printf("Текущее GM время: %s\n", buf);
	/* Преобразование struct tm(gmtime) в time_t */
	printf("Текущее GM время: %ld\n", gmTmToTt(st));
	/* Преобразование текста в time_t */
	st_gm = stringToTm(buf);
	printf("GM время из текста: %ld\n", gmTmToTt(stringToTm(buf)));

	/* Получение текущего времени */
	st = getCurrentLocalTm();
	tmToString(st, buf, TSBUF_SIZE);
	printf("Текущее локальное время по другому: %s\n", buf);
	st_gm = getCurrentGmTm();
	tmToString(st_gm, buf, TSBUF_SIZE);
	printf("Текущее GM время по другому: %s\n", buf);

	/* Получение разности между временными метками */
	struct tm st1;
	memcpy(&st1, st, sizeof(struct tm));
	st1.tm_sec++;
	tmToString(&st1, buf, TSBUF_SIZE);
	printf("Исправленное текущее локальное время: %s\n", buf);
	printf("Разности между структурами: %lf\n", diffTimeTm(st, &st1));

	/* функция получение из time_t локальный */
	printf("Локальное время по частям: %d.%d.%d %d:%d.%d %d %d %d\n",
		getLocalYear(t), /* год */
		getLocalMon(t), /* месяц (0-11) */
		getLocalMday(t), /* день в месяце (1-31) */
		getLocalHour(t), /* часы (0-23) */
		getLocalMin(t), /* минуты (0-59) */
		getLocalSec(t), /* секунды (0-60) */
		getLocalWday(t), /* день недели (0-6, воскресенье = 0) */
		getLocalYday(t), /* день в году (0-365, 1 январь = 0) */
		getLocalDst(t) /* летнее время */
	);

	/* функция получение из time_t GM */
	printf("GM время по частям: %d.%d.%d %d:%d.%d %d %d %d\n",
		getGmYear(t), /* год */
		getGmMon(t), /* месяц (0-11) */
		getGmMday(t), /* день в месяце (1-31) */
		getGmHour(t), /* часы (0-23) */
		getGmMin(t), /* минуты (0-59) */
		getGmSec(t), /* секунды (0-60) */
		getGmWday(t), /* день недели (0-6, воскресенье = 0) */
		getGmYday(t), /* день в году (0-365, 1 январь = 0) */
		getGmDst(t) /* летнее время */
	);

	clock_t delta = getClock();
	clock_t clocks_per_sec;
	printf("Тиков: %ld\n", diffClock(start, delta, &clocks_per_sec));
	time_t delta_tt = getCurrentTt();
	printf("Секунд: %lf\n", diffTimeTt(start_tt, delta_tt));
	return 0;
}

