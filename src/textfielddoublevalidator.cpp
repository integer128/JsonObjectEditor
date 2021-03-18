#include "textfielddoublevalidator.h"

TextFieldDoubleValidator::TextFieldDoubleValidator(QObject *parent)
    : QDoubleValidator{parent} {}

TextFieldDoubleValidator::TextFieldDoubleValidator(double bottom, double top, int decimals, QObject *parent)
    : QDoubleValidator{bottom, top, decimals, parent} {}

QValidator::State TextFieldDoubleValidator::validate(QString &s, int &pos) const
{
    if (s.isEmpty() || (s.startsWith("-") && s.length() == 1))
    {
        // разрешаем пустое поле или знак минус
        return QValidator::Intermediate;
    }

    // проверяем длину десятичных разрядов
    QChar point = locale().decimalPoint();
    if (s.indexOf(point) != -1) {
        int lengthDecimals = s.length() - s.indexOf(point) - 1;
        if (lengthDecimals > decimals())
        {
            return QValidator::Invalid;
        }
    }

    // проверяем диапазон значений
    bool isNumber;
    double value = locale().toDouble(s, &isNumber);
    if (isNumber && bottom() <= value && value <= top())
    {
        return QValidator::Acceptable;
    }
    return QValidator::Invalid;
}
