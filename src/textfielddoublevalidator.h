#ifndef TEXTFIELDDOUBLEVALIDATOR_H
#define TEXTFIELDDOUBLEVALIDATOR_H

#include <QValidator>

class TextFieldDoubleValidator : public QDoubleValidator
{
public:
    TextFieldDoubleValidator(QObject *parent = nullptr);
    TextFieldDoubleValidator(double bottom, double top, int decimals, QObject *parent = nullptr);

    QValidator::State validate(QString &s, int &pos) const;
};
#endif // TEXTFIELDDOUBLEVALIDATOR_H
