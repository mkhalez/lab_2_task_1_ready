#ifndef VALIDSTRING_H
#define VALIDSTRING_H

#include <QString>
#include <QRegularExpression>

class ValidString
{
public:
    ValidString();
    void SetInputDate(QString input_date);
    bool ValidInputDate();

private:
    QString input_date;
    bool isLeapYear(int year);
};

#endif // VALIDSTRING_H
