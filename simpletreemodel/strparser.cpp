#include "strparser.h"

namespace strparser {

const int CODE = 0;
const int PARENTCODE = 2;
const int DATA = 1;
const int CODESIZE = 6;
const int PARENTCODESIZE = 6;
const int DATASIZE = 50;


StrParser::StrParser():
    mCode(0),
    mParentCod(0)
{
    mRawData = "";
    mData = "";
}

StrParser::~StrParser()
{
}

int StrParser::getCode()
{
    return mCode;
}

int StrParser::getParentCode()
{
    return mParentCod;
}

QString StrParser::getData()
{
    return mData;
}

int StrParser::Parse(QString raw_data)
{
    QStringList parts = raw_data.split("#", QString::SkipEmptyParts);
    QStringList::const_iterator constIterator;
    int count;
    for (constIterator = parts.constBegin(), count = 0; constIterator != parts.constEnd(); constIterator++, count++) {
        switch (count) {
        case CODE:
            if ((*constIterator).count() <= CODESIZE)
                mCode = (*constIterator).toInt();
            else return 0;
        break;
        case DATA:
            if ((*constIterator).count() <= DATASIZE)
                mData = *constIterator;
            else return 0;
        break;
        case PARENTCODE:
            if ((*constIterator).count() <= PARENTCODESIZE) {
                mParentCod = (*constIterator).toInt();
                // если это верхний уровень иерархии
                if (mParentCod == 0)
                    mParentCod = 0;
            }
            else return 0;
        break;
        }
    }
    return 1;
}
}
