#include "mydate.h"
#include <QString>
#include <map>

const int kNumberMonth1 = 1;
const int kNumberMonth2 = 2;
const int kNumberMonth3 = 3;
const int kNumberMonth4 = 4;
const int kNumberMonth5 = 5;
const int kNumberMonth6 = 6;
const int kNumberMonth7 = 7;
const int kNumberMonth8 = 8;
const int kNumberMonth9 = 9;
const int kNumberMonth10 = 10;
const int kNumberMonth11 = 11;
const int kNumberMonth12 = 12;

const int kNumberDay31 = 31;

const int kLongMonth = 31;
const int kShortMonth = 30;
const int kLongFebruary = 29;
const int kShortFebruary = 28;
const int kLongYear = 366;
const int kShortYear = 365;

const int kNumberMonthInYear = 12;
const int kNumberDayInWeek = 7;
const int kHelperProcent = 100;
const int kZellerHelper13 = 13;
const int kZellerHelper5 = 5;
const int kZellerHelper7 = 7;

const int kLeapCondition400 = 400;
const int kLeapCondition100 = 100;


MyDate::MyDate(int day, int month, int year) {
    this->day_ = day;
    this->month_ = month;
    this->year_ = year;
}

MyDate::MyDate(const QString& date) {
    this->day_ = date.mid(0, 2).toInt();
    this->month_ = date.mid(3, 2).toInt();
    this->year_ = date.mid(6, 4).toInt();
}


int MyDate::NumberDayInMonth(int month, int year) {
    bool is_leap_year = IsLeap(year);
    int number_of_day_in_month;


    switch (month) {
        case kNumberMonth1:
        case kNumberMonth3:
        case kNumberMonth5:
        case kNumberMonth7:
        case kNumberMonth8:
        case kNumberMonth10:
        case kNumberMonth12:
            number_of_day_in_month = kLongMonth;
            break;
        case kNumberMonth4:
        case kNumberMonth6:
        case kNumberMonth9:
        case kNumberMonth11:
            number_of_day_in_month = kShortMonth;
            break;
        case kNumberMonth2:
            if (is_leap_year) {
                number_of_day_in_month = kLongFebruary;
            } else {
                number_of_day_in_month = kShortFebruary;
            }
    }
    return number_of_day_in_month;
}

int MyDate::DayOfWeek(int day, int month, int year) {


    if (month < 3) {
        month += kNumberMonthInYear;
        year--;
    }

    int q = day;
    int m = month;
    int k = year % kHelperProcent;
    int j = year / kHelperProcent;

    // Вычисляем день недели по формуле Зеллера
    int h = (q + (kZellerHelper13 * (m + 1)) / kZellerHelper5 + k + (k / 4) +
             (j / 4) + kZellerHelper5 * j) %
            kZellerHelper7;
    return (h + kZellerHelper5) % kZellerHelper7 + 1;
}

int MyDate::DayFromStart(int day, int month, int year) {
    int day_to_date = 0;


    for (int i = 1; i < year; i++) {
        if (IsLeap(i)) {
            day_to_date += kLongYear;
        } else {
            day_to_date += kShortYear;
        }
    }

    bool is_leap_year = IsLeap(year);

    std::map<int, int> days_in_month = {
        {kNumberMonth1, kLongMonth},   {kNumberMonth2, kShortFebruary},
        {kNumberMonth3, kLongMonth},   {kNumberMonth4, kShortMonth},
        {kNumberMonth5, kLongMonth},   {kNumberMonth6, kShortMonth},
        {kNumberMonth7, kLongMonth},   {kNumberMonth8, kLongMonth},
        {kNumberMonth9, kShortMonth},  {kNumberMonth10, kLongMonth},
        {kNumberMonth11, kShortMonth}, {kNumberMonth12, kLongMonth}};


    if (is_leap_year) {
        days_in_month[kNumberMonth2] = kLongFebruary;
    }


    for (int i = 1; i < month; i++) {
        day_to_date += days_in_month[i];
    }
    day_to_date += day;

    return day_to_date;
}

bool MyDate::IsLeap(int year) {
    bool is_leap_year = false;

    if (year % kLeapCondition400 == 0 ||
        (year % kLeapCondition100 != 0 && year % 4 == 0)) {
        is_leap_year = true;
    }

    return is_leap_year;
}

bool MyDate::IsLeap() {
    bool is_leap_year = false;

    if (year_ % kLeapCondition400 == 0 ||
        (year_ % kLeapCondition100 != 0 && year_ % 4 == 0)) {
        is_leap_year = true;
    }

    return is_leap_year;
}

MyDate MyDate::NextDay() {
    int new_day = day_, new_month = month_, new_year = year_;

    int number_of_day_in_month = NumberDayInMonth(month_, year_);


    if (day_ + 1 <= number_of_day_in_month) {
        new_day = day_ + 1;
    } else {

        if (month_ + 1 <= kNumberMonthInYear) {
            new_day = 1;
            new_month = month_ + 1;
        } else {
            new_day = 1;
            new_month = 1;
            new_year = year_ + 1;
        }
    }

    return MyDate(new_day, new_month, new_year);
}

short MyDate::WeekNumber() {
    bool is_leap_year = IsLeap(year_);

    std::map<int, int> days_in_month = {
        {kNumberMonth1, kLongMonth},   {kNumberMonth2, kShortFebruary},
        {kNumberMonth3, kLongMonth},   {kNumberMonth4, kShortMonth},
        {kNumberMonth5, kLongMonth},   {kNumberMonth6, kShortMonth},
        {kNumberMonth7, kLongMonth},   {kNumberMonth8, kLongMonth},
        {kNumberMonth9, kShortMonth},  {kNumberMonth10, kLongMonth},
        {kNumberMonth11, kShortMonth}, {kNumberMonth12, kLongMonth}};


    if (is_leap_year) {
        days_in_month[2] = kShortFebruary;
    }

    int sum = 0;


    for (int i = 1; i < month_; i++) {
        sum += days_in_month[i];
    }
    sum += day_;

    int shift = DayOfWeek(1, 1, year_) - 1;

    if ((sum + shift) % kNumberDayInWeek == 0) {
        return (sum + shift) / kNumberDayInWeek;
    } else {
        return (sum + shift) / kNumberDayInWeek + 1;
    }
}

MyDate MyDate::PreviousDay() {
    int new_day = day_, new_month = month_, new_year = year_;


    if (day_ - 1 >= 1) {
        new_day = day_ - 1;
    } else {

        if (month_ - 1 >= 1) {
            new_day = NumberDayInMonth(month_ - 1, year_);
            new_month = month_ - 1;
        } else {
            new_day = kNumberDay31;
            new_month = kNumberMonth12;
            new_year = year_ - 1;
        }
    }

    return MyDate(new_day, new_month, new_year);
}


int MyDate::DayFromJanury(MyDate date) {
    int sum = 0;

    bool is_leap_year = IsLeap(date.GetYear());

    std::map<int, int> days_in_month = {
        {kNumberMonth1, kLongMonth},   {kNumberMonth2, kShortFebruary},
        {kNumberMonth3, kLongMonth},   {kNumberMonth4, kShortMonth},
        {kNumberMonth5, kLongMonth},   {kNumberMonth6, kShortMonth},
        {kNumberMonth7, kLongMonth},   {kNumberMonth8, kLongMonth},
        {kNumberMonth9, kShortMonth},  {kNumberMonth10, kLongMonth},
        {kNumberMonth11, kShortMonth}, {kNumberMonth12, kLongMonth}};


    if (is_leap_year) {
        days_in_month[2] = kShortFebruary;
    }

    for (int i = 1; i < date.GetMonth(); i++) {
        sum += days_in_month[i];
    }
    sum += date.GetDay();

    return sum;
}

int MyDate::DayFromJanury(int day, int month, int year) {
    int sum = 0;

    bool is_leap_year = IsLeap(year);

    std::map<int, int> days_in_month = {
        {kNumberMonth1, kLongMonth},   {kNumberMonth2, kShortFebruary},
        {kNumberMonth3, kLongMonth},   {kNumberMonth4, kShortMonth},
        {kNumberMonth5, kLongMonth},   {kNumberMonth6, kShortMonth},
        {kNumberMonth7, kLongMonth},   {kNumberMonth8, kLongMonth},
        {kNumberMonth9, kShortMonth},  {kNumberMonth10, kLongMonth},
        {kNumberMonth11, kShortMonth}, {kNumberMonth12, kLongMonth}};


    if (is_leap_year) {
        days_in_month[2] = kShortFebruary;
    }


    for (int i = 1; i < month; i++) {
        sum += days_in_month[i];
    }
    sum += day;

    return sum;
}


int MyDate::DaysTillYourBithday(MyDate birthdaydate) {
    int sum = 0;
    for (int i = 0; i < birthdaydate.GetYear(); i++) {
        if (IsLeap(i)) {
            sum += kLongYear;
        } else {
            sum += kShortYear;
        }
    }
    sum += DayFromJanury(birthdaydate);

    int sum_2 = 0;


    for (int i = 0; i < this->year_; i++) {
        if (IsLeap(i)) {
            sum_2 += kLongYear;
        } else {
            sum_2 += kShortYear;
        }
    }

    sum_2 += DayFromJanury(this->day_, this->month_, this->year_);

    return qAbs(sum - sum_2);


    /*int current_year, current_month, current_day;
    GetCurrentDate(current_year, current_month, current_day);

    MyDate currentDate(current_day, current_month, current_year);
    MyDate nextBirthday(birthdaydate.day, birthdaydate.month, current_year);

    if (nextBirthday.DayFromStart(nextBirthday.day, nextBirthday.month, nextBirthday.year) < currentDate.DayFromStart(nextBirthday.day, nextBirthday.month, nextBirthday.year))
    {
        nextBirthday.year += 1;
    }

    return nextBirthday.DayFromStart(nextBirthday.day, nextBirthday.month, nextBirthday.year) - currentDate.DayFromStart(nextBirthday.day, nextBirthday.month, nextBirthday.year);
*/
}

int MyDate::Duration(MyDate date) {

    int sum = 0;
    for (int i = 0; i < date.GetYear(); i++) {
        if (IsLeap(i)) {
            {
                sum += kLongYear;
            }
        } else {
            { sum += kShortYear; }
        }
    }
    sum += DayFromJanury(date);

    int sum_2 = 0;


    for (int i = 0; i < this->year_; i++) {
        if (IsLeap(i)) {
            {
                sum_2 += kLongYear;
            }
        } else {
            { sum_2 += kShortYear; }
        }
    }

    sum_2 += DayFromJanury(this->day_, this->month_, this->year_);

    return qAbs(sum - sum_2);


    /*
    int current_year, current_month, current_day;
    GetCurrentDate(current_day, current_month, current_year);
    return DayFromStart(current_day, current_month, current_year) - DayFromStart(date.day, date.month, date.year);
    */
}

int MyDate::GetDay() {
    return day_;
}

int MyDate::GetMonth() {
    return month_;
}


int MyDate::GetYear() {
    return year_;
}
