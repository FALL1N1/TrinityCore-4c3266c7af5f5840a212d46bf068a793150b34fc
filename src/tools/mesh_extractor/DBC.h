#ifndef DBC_H
#define DBC_H
#include <vector>
#include "Common.h"

class Record;

class DBC
{
public:
    DBC(FILE* stream);

    std::string GetStringByOffset(int offset);

    Record* GetRecordById(int id);

    std::string Name;
    std::vector<Record*> Records;
    int RecordCount;
    int Fields;
    int RecordSize;
    uint8* StringBlock;
    uint32 StringBlockSize;
    bool IsFaulty;
};

class Record
{
public:
    Record(DBC* dbc) : Source(dbc) {}

    DBC* Source;
    std::vector<int> Values;

    int operator[](int index)
    {
        return Values[index];
    }

    float GetFloat(int index)
    {
        return *(float*)(&Values[index]);
    }

    std::string GetString(int index)
    {
        return Source->GetStringByOffset(Values[index]);
    }
};

#endif