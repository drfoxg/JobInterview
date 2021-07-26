#ifndef STRPARSER_H
#define STRPARSER_H

#include <QObject>
#include <QStringList>

namespace strparser{
class StrParser
{
public:
    StrParser();
    ~StrParser();

    int getCode();
    int getParentCode();
    QString getData();
    int Parse(QString raw_data);
private:
    QString mRawData;
    QString mData;
    int mCode;
    int mParentCod;
};
}

#endif // STRPARSER_H
