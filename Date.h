#ifndef _DATE_H_
#define _DATE_H_

#include <iostream>

using namespace std;

class Date {
public:
	struct YearMonthDay {
		int year;
		int month;
		int day;
	};
	static const int kDaysPerWeek = 7;
	static const int kJulianDayOf1970_01_01;
	
	Date() : julianDayNumber_(0) {}
	Date(int year, int month, int day);
	explicit Date(int julianDayNum) : julianDayNumber_(julianDayNum) {}
	
	struct YearMonthDay yearMonthDay() const;
	int year() const { return yearMonthDay().year; }
	int month() const { return yearMonthDay().month; }
	int day() const { return yearMonthDay().day; }
	int weekDay() const { return (julianDayNumber_ + 1) % kDaysPerWeek; }
	int julianDayNumber() const { return julianDayNumber_; }
private:
	int julianDayNumber_;
};

ostream& operator<<(ostream& os, const Date date);
inline bool operator<(Date x, Date y) { return x.julianDayNumber() < y.julianDayNumber(); }
inline bool operator==(Date x, Date y) { return x.julianDayNumber() == y.julianDayNumber(); }

#endif // _DATE_H_
