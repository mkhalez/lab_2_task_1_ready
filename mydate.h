#ifndef MYDATE_H
#define MYDATE_H

#include <QString>

class MyDate
{
private:
    int day;
    int month;
    int year;
public:
    MyDate(int day, int month, int year);
    MyDate(QString date);
    MyDate()
        {

        };

private:
    int NumberDayInMonth(int month, int year);
    int DayOfWeek(int day, int month, int year);
    int DayFromStart(int day, int month, int year);
    int DayFromJanury(MyDate date);
    int DayFromJanury(int day, int month, int year);

public:
    bool IsLeap(int year);
    bool IsLeap();
    MyDate NextDay();
    short WeekNumber();
    MyDate PreviousDay();
    int DaysTillYourBithday(MyDate birthdaydate);
    int Duration(MyDate date);
    int GetYear();
    int GetMonth();
    int GetDay();


};

#endif // MYDATE_H
