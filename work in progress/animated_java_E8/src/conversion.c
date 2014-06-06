#include "pebble.h"
#include "conversion.h"

int conversion_from_time_to_hour(void) {

	time_t now = time(NULL);
	struct tm *t = localtime(&now);
	int hour = t->tm_hour;
	return hour;
}
int conversion_from_time_to_minute(void) {
	
	time_t now = time(NULL);
	struct tm *t = localtime(&now);
	int minute = t->tm_min;
	return minute;
}

int convert_to_ten_of_hour(int h){
	int ten_of_hour;
	int one_of_h = h % 10;
	ten_of_hour = h - one_of_h;
	ten_of_hour = ten_of_hour / 10;
	return ten_of_hour;
}
int convert_to_one_of_hour(int h){
	int one_of_hour = h % 10;
	return one_of_hour;
}
int convert_to_ten_of_minute(int m){
	int ten_of_minute;
	int one_of_min = m % 10;
	ten_of_minute = m - one_of_min;
	ten_of_minute = ten_of_minute / 10;
	return ten_of_minute;
}
int convert_to_one_of_minute(int m){
	int one_of_minute = m % 10;
	return one_of_minute;
}


