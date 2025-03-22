#include "mydate.h"
#include <map>
#include <QString>

MyDate::MyDate(int day, int month, int year)
{
    this->day = day;
    this->month = month;
    this->year = year;
}

MyDate::MyDate(QString date)
{
    QString helper = "";
    helper = helper + date[0];
    helper = helper + date[1];
    this->day = helper.toInt();
    helper.clear();
    helper += date[3];
    helper += date[4];
    this->month = helper.toInt();
    helper.clear();
    helper += date[6];
    helper += date[7];
    helper += date[8];
    helper += date[9];
    this->year = helper.toInt();
}


int MyDate::NumberDayInMonth(int month, int year)
{
    bool is_leap_year = IsLeap(year);
    int number_of_day_in_month;

    switch (month)
    {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        number_of_day_in_month = 31;
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        number_of_day_in_month = 30;
        break;
    case 2:
        if (is_leap_year)
            number_of_day_in_month = 29;
        else
            number_of_day_in_month = 28;
    }
    return number_of_day_in_month;
}

int MyDate::DayOfWeek(int day, int month, int year)
{
    if (month < 3)
    {
        month += 12;
        year--;
    }

    int q = day;
    int m = month;
    int K = year % 100;
    int J = year / 100;

    // Вычисляем день недели по формуле Зеллера
    int h = (q + (13 * (m + 1)) / 5 + K + (K / 4) + (J / 4) + 5 * J) % 7;
    return (h + 5) % 7 + 1;
}

int MyDate::DayFromStart(int day, int month, int year)
{
    int day_to_date = 0;
    for (int i = 1; i < year; i++)
    {
        if (IsLeap(i))
            day_to_date += 366;
        else
            day_to_date += 365;
    }

    bool is_leap_year = IsLeap(year);

    std::map<int, int> days_in_month = {
                                        {1, 31},
                                        {2, 28},
                                        {3, 31},
                                        {4, 30},
                                        {5, 31},
                                        {6, 30},
                                        {7, 31},
                                        {8, 31},
                                        {9, 30},
                                        {10, 31},
                                        {11, 30},
                                        {12, 31}};

    if (is_leap_year)
        days_in_month[2] = 29;

    for (int i = 1; i < month; i++)
    {
        day_to_date += days_in_month[i];
    }
    day_to_date += day;

    return day_to_date;
}

bool MyDate::IsLeap(int year)
{
    bool is_leap_year;

    if (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0))
        is_leap_year = true;
    else
        is_leap_year = false;

    return is_leap_year;
}

bool MyDate::IsLeap()
{
    bool is_leap_year;

    if (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0))
        is_leap_year = true;
    else
        is_leap_year = false;

    return is_leap_year;
}

MyDate MyDate::NextDay()
{
    int new_day = day, new_month = month, new_year = year;

    int number_of_day_in_month = NumberDayInMonth(month, year);

    if (day + 1 <= number_of_day_in_month)
    {
        new_day = day + 1;
    }
    else
    {

        if (month + 1 <= 12)
        {
            new_day = 1;
            new_month = month + 1;
        }
        else
        {
            new_day = 1;
            new_month = 1;
            new_year = year + 1;
        }
    }

    return MyDate(new_day, new_month, new_year);
}

short MyDate::WeekNumber()
{
    bool is_leap_year = IsLeap(year);

    std::map<int, int> days_in_month = {
                                        {1, 31},
                                        {2, 28},
                                        {3, 31},
                                        {4, 30},
                                        {5, 31},
                                        {6, 30},
                                        {7, 31},
                                        {8, 31},
                                        {9, 30},
                                        {10, 31},
                                        {11, 30},
                                        {12, 31}};

    if (is_leap_year)
        days_in_month[2] = 29;

    int sum = 0;

    for (int i = 1; i < month; i++)
    {
        sum += days_in_month[i];
    }
    sum += day;

    int shift = DayOfWeek(1, 1, year) - 1;

    if ((sum + shift) % 7 == 0)
        return (sum + shift) / 7;
    else
        return (sum + shift) / 7 + 1;
}

MyDate MyDate::PreviousDay()
{
    int new_day = day, new_month = month, new_year = year;

    if (day - 1 >= 1)
    {
        new_day = day - 1;
    }
    else
    {

        if (month - 1 >= 1)
        {
            new_day = NumberDayInMonth(month - 1, year);
            new_month = month - 1;
        }
        else
        {
            new_day = 31;
            new_month = 12;
            new_year = year - 1;
        }
    }

    return MyDate(new_day, new_month, new_year);
}


int MyDate::DayFromJanury(MyDate date)
{
    int sum = 0;

    bool is_leap_year = IsLeap(date.GetYear());

    std::map<int, int> days_in_month = {
                                        {1, 31},
                                        {2, 28},
                                        {3, 31},
                                        {4, 30},
                                        {5, 31},
                                        {6, 30},
                                        {7, 31},
                                        {8, 31},
                                        {9, 30},
                                        {10, 31},
                                        {11, 30},
                                        {12, 31}};

    if (is_leap_year)
        days_in_month[2] = 29;

    for (int i = 1; i < date.GetMonth(); i++)
    {
        sum += days_in_month[i];
    }
    sum += date.GetDay();

    return sum;
}

int MyDate::DayFromJanury(int day, int month, int year)
{
    int sum = 0;

    bool is_leap_year = IsLeap(year);

    std::map<int, int> days_in_month = {
                                        {1, 31},
                                        {2, 28},
                                        {3, 31},
                                        {4, 30},
                                        {5, 31},
                                        {6, 30},
                                        {7, 31},
                                        {8, 31},
                                        {9, 30},
                                        {10, 31},
                                        {11, 30},
                                        {12, 31}};

    if (is_leap_year)
        days_in_month[2] = 29;

    for (int i = 1; i < month; i++)
    {
        sum += days_in_month[i];
    }
    sum += day;

    return sum;
}


int MyDate::DaysTillYourBithday(MyDate birthdaydate)
{
    int sum = 0;
    for(int i = 0; i < birthdaydate.GetYear(); i++)
    {
        if(IsLeap(i)) sum += 366;
        else sum += 365;
    }
    sum += DayFromJanury(birthdaydate);

    int sum_2 = 0;
    for(int i = 0; i < this->year; i++)
    {
        if(IsLeap(i)) sum_2 += 366;
        else sum_2 += 365;
    }

    sum_2 += DayFromJanury(this->day, this->month, this->year);

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

int MyDate::Duration(MyDate date)
{

    int sum = 0;
    for(int i = 0; i < date.GetYear(); i++)
    {
        if(IsLeap(i)) sum += 366;
        else sum += 365;
    }
    sum += DayFromJanury(date);

    int sum_2 = 0;
    for(int i = 0; i < this->year; i++)
    {
        if(IsLeap(i)) sum_2 += 366;
        else sum_2 += 365;
    }

    sum_2 += DayFromJanury(this->day, this->month, this->year);

    return qAbs(sum - sum_2);



    /*
    int current_year, current_month, current_day;
    GetCurrentDate(current_day, current_month, current_year);
    return DayFromStart(current_day, current_month, current_year) - DayFromStart(date.day, date.month, date.year);
    */
}

int MyDate::GetDay()
{
    return day;
}

int MyDate::GetMonth()
{
    return month;
}


int MyDate::GetYear()
{
    return year;
}
