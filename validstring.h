#ifndef VALIDSTRING_H
#define VALIDSTRING_H

#include <QRegularExpression>
#include <QString>

class ValidString {
   public:
    ValidString();
    void SetInputDate(QString input_date);
    bool ValidInputDate();

   private:
    QString input_date_;
    bool isLeapYear(int year);
};

#endif	// VALIDSTRING_H
