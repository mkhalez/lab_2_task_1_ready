#include "validstring.h"

const int kNumberMonthInYear = 12;

const int kNumberMonth2 = 2;
const int kNumberMonth4 = 4;
const int kNumberMonth6 = 6;
const int kNumberMonth9 = 9;
const int kNumberMonth11 = 11;

const int kLeapCondition100 = 100;
const int kLeapCondition400 = 400;


const int kLongMonth = 31;
const int kShortMonth = 30;
const int kLongFebruary = 29;
const int kShortFebruary = 28;


ValidString::ValidString() {}

void ValidString::SetInputDate(QString input_date) {
    this->input_date_ = std::move(input_date);
}

bool ValidString::ValidInputDate() {
    // Регулярное выражение для проверки формата dd.mm.yyyy
    static const QRegularExpression kPattern(R"((\d{2})\.(\d{2})\.(\d{4}))");
    if (!kPattern.match(input_date_).hasMatch()) {
        return false;
    }

    bool ok;
    int day = input_date_.mid(0, 2).toInt(&ok);


    if (!ok) {
        return false;
    }

    int month = input_date_.mid(3, 2).toInt(&ok);


    if (!ok) {
        return false;
    }

    int year = input_date_.mid(6, 4).toInt(&ok);


    if (!ok) {
        return false;
    }


    if (month < 1 || month > kNumberMonthInYear) {
        return false;
    }


    if (day < 1 || day > kLongMonth) {
        return false;
    }

    if ((month == kNumberMonth4 || month == kNumberMonth6 ||
         month == kNumberMonth9 || month == kNumberMonth11) &&
        day > kShortMonth) {
        {
            return false;
        }
    }


    if (month == kNumberMonth2) {
        if (isLeapYear(year)) {
            if (day > kLongFebruary) {
                return false;
            }
        } else {
            if (day > kShortFebruary) {
                return false;
            }
        }
    }

    return true;
}


bool ValidString::isLeapYear(int year) {
    return (year % 4 == 0 && year % kLeapCondition100 != 0) ||
           (year % kLeapCondition400 == 0);
}
