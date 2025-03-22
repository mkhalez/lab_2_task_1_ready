#include "validstring.h"

ValidString::ValidString() {}

void ValidString::SetInputDate(QString input_date)
{
    this->input_date = input_date;
}

bool ValidString::ValidInputDate()
{
    // Регулярное выражение для проверки формата dd.mm.yyyy
    static const QRegularExpression pattern(R"((\d{2})\.(\d{2})\.(\d{4}))");
    if (!pattern.match(input_date).hasMatch()) {
        return false;
    }

    bool ok;
    int day = input_date.mid(0, 2).toInt(&ok);
    if (!ok) return false;

    int month = input_date.mid(3, 2).toInt(&ok);
    if (!ok) return false;

    int year = input_date.mid(6, 4).toInt(&ok);
    if (!ok) return false;

    if (month < 1 || month > 12) return false;

    if (day < 1 || day > 31) return false;

    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
        return false;
    }

    if (month == 2) {
        if (isLeapYear(year)) {
            if (day > 29) return false;
        } else {
            if (day > 28) return false;
        }
    }

    return true;
}


bool ValidString::isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}
