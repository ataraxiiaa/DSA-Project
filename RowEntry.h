#pragma once
#include "String.h"
#include "Vector.h"
#include <filesystem>
using namespace std;


struct RowEntry
{
	long long rowIndex;
    Vector<String> cells;

    friend ostream& operator<<(ostream& os, RowEntry& row)
    {
        for (int i = 0; i < row.cells.getCurr(); ++i)
        {
            if (i > 0) os << ',';
            os << row.cells[i];
        }
        return os;
    }

    friend istream& operator>>(istream& is, RowEntry& row)
    {
        row.cells.clear();
        String line;
        getline(is, line);
        if (!(!line))
        {
            int index = 0;
            while (index < line.getSize())
            {
                row.cells.push_back(parseField(line, index));
            }
        }
        return is;
    }

    static String parseField(String& row, int& index)
    {
        String field;
        bool quoted = false;

        if (row[index] == '"')
        {
            quoted = true;
            ++index;
        }

        while (index < row.getSize())
        {
            if (quoted)
            {
                if (row[index] == '"')
                {
                    ++index;
                    if (index < row.getSize() && row[index] == ',')
                    {
                        ++index;
                    }
                    break;
                }
                else
                {
                    if (isAlphabet(row[index]))
                        field += convertToUppercase(row[index++]);
                    else
                        field += row[index++];
                }
            }
            else
            {
                if (row[index] == ',')
                {
                    ++index;
                    break;
                }
                else
                {
                    if (isAlphabet(row[index]))
                        field += convertToUppercase(row[index++]);
                    else
                        field += row[index++];
                }
            }
        }

        return field;
    }

    void readRow(long long rowIndex, String& row)
    {
        this->rowIndex = rowIndex;
        cells.clear();
        int index = 0;
        while (index < row.getSize())
        {
            cells.push_back(parseField(row, index));
        }
    }
};
