#include <time.h>
#include <stdio.h>

#define MARCH		2
#define OCTOBER		9
#define SATURDAY	6
#define SUNDAY		0

int is_last_sunday_october(struct tm *time);
int is_last_sunday_april(struct tm *time);
struct tm *tomorrow();

int main()
{
	time_t currentTime;

	time(&currentTime);
	struct tm *timeinfo = localtime(&currentTime);

	int lastOct = is_last_sunday_october(timeinfo),
	    lastApr = is_last_sunday_april(timeinfo);

	char zero = (timeinfo->tm_min < 10) ? '0' : 0;

	switch(lastOct)
	{
		case 0:
			printf("\x1b[31;1mCette nuit, on change d'heure ! À 3h, il sera 2h !\e[m\n\n");
			break;
		case 1:
			printf("\x1b[31;1mCette nuit, on a changé d'heure !\nReculez vos horloges d'une heure, il est %dh%c%d !\e[m\n\n", timeinfo->tm_hour, zero, timeinfo->tm_min);
			break;
	}

	switch(lastApr)
	{
		case 0:
			printf("\x1b[31:1mCette nuit, on change d'heure ! À 2h, il sera 3h !\e[m\n\n");
			break;
		case 1:
			printf("\x1b[31;1mCette nuit, on a changé d'heure !\nAvancez vos horloges d'une heure, il est %dh%c%d !\e[m\n\n", timeinfo->tm_hour, zero, timeinfo->tm_min);
			break;
	}

	return 0;
}

/*
   The functions below return:
   	0 if we are the Saturday before the change of hour;
	1 if we have just changed hour
	-1 otherwise
*/
int is_last_sunday_october(struct tm *time)
{
	int month = time->tm_mon;
	int dayofweek = time->tm_wday;
	int dayofmonth = time->tm_mday;

	if(month == OCTOBER && dayofweek == SATURDAY &&
			is_last_sunday_october(tomorrow()) == 1)
		return 0;
	else if(month == OCTOBER && dayofweek == SUNDAY && dayofmonth + 7 > 31)
		return 1;
	else
		return -1;
}

int is_last_sunday_april(struct tm *time)
{
	int month = time->tm_mon;
	int dayofweek = time->tm_wday;
	int dayofmonth = time->tm_mday;

	if(month == MARCH && dayofweek == SATURDAY &&
		is_last_sunday_april(tomorrow()) == 1)
		return 0;
	if(month == MARCH && dayofweek == SUNDAY && dayofmonth + 7 > 30)
		return 1;
	else
		return -1;
}

struct tm *tomorrow()
{
	time_t t;
	t = time(&t);
	t += 24 * 3600;

	return localtime(&t);
}

