#include "converter.h"

Converter::Converter(QObject *parent)
    : QObject{parent}
{

}

void Converter::convert(const std::pair<QString, QString> &myPair, double amount)
{
    auto search = currencies.find(myPair);
    if (search != currencies.end())
    {
        double result = amount * search->second;
        emit resultReady(result);
    }
    else
    {
        emit convertError();
    }
}
