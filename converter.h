#ifndef CONVERTER_H
#define CONVERTER_H

#include <QObject>

class Converter : public QObject
{
    Q_OBJECT
public:
    explicit Converter(QObject *parent = nullptr);
    void convert(const std::pair<QString, QString> &myPair, double amount);

signals:
    double resultReady(double result);
    void convertError();

private:
    std::map<std::pair<QString, QString>, double> currencies{
        {{"USD", "RUB"}, 81.097899}, {{"RUB", "USD"}, 0.0123316}
    };

};

#endif // CONVERTER_H
