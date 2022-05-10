#include <iostream>
#include <iomanip>
#include <stdexcept>

using namespace std;

class ChessBoardArray
{
protected:
    unsigned Size, Base;
    int *data;

    class Row
    {
    private:
        ChessBoardArray &chess;
        int row;

    public:
        Row(ChessBoardArray &a, int i)
            : chess(a), row(i) {}
        int &operator[](int i) const
        {
            return chess.select(row, i);
        }
    };

    class ConstRow
    {
    private:
        const ChessBoardArray &chess;
        int row;

    public:
        ConstRow(const ChessBoardArray &a, int i)
            : chess(a), row(i) {}
        int operator[](int i) const
        {
            return chess.select(row, i);
        }
    };

private:
    unsigned int loc(int i, int j) const throw(out_of_range)
    {
        unsigned di = i - Base, dj = j - Base;
        if (di < 0 || di >= Size || dj < 0 || dj >= Size ||
            (di % 2 == 0 && dj % 2 != 0) || (di % 2 != 0 && dj % 2 == 0))
            throw out_of_range("invalid index");
        return (di * Size + dj) / 2;
    }

public:
    ChessBoardArray(unsigned size = 0, unsigned base = 0)
        : Size(size), Base(base), data(new int[(size * size + 1) / 2])
    {
        for (unsigned i = 0; i < (Size * Size + 1) / 2; ++i)
            data[i] = 0;
    }
    ChessBoardArray(const ChessBoardArray &a)
        : Size(a.Size), Base(a.Base), data(new int[(a.Size * a.Size + 1) / 2])
    {
        for (unsigned i = 0; i < (Size * Size + 1) / 2; ++i)
            data[i] = a.data[i];
    }
    ~ChessBoardArray() { delete[] data; }

    ChessBoardArray &operator=(const ChessBoardArray &a)
    {
        delete[] data;
        Size = a.Size;
        Base = a.Base;
        data = new int[(Size * Size + 1) / 2];
        for (unsigned i = 0; i < (Size * Size + 1) / 2; ++i)
            data[i] = a.data[i];
        return *this;
    }

    int &select(int i, int j)
    {
        return data[loc(i, j)];
    }
    int select(int i, int j) const
    {
        return data[loc(i, j)];
    }

    const Row operator[](int i)
    {
        return Row(*this, i);
    }
    const ConstRow operator[](int i) const
    {
        return ConstRow(*this, i);
    }

    friend ostream &operator<<(ostream &out, const ChessBoardArray &a)
    {
        for (unsigned int i = a.Base; i < a.Size + a.Base; ++i)
        {
            for (unsigned int j = a.Base; j < a.Size + a.Base; ++j)
            {
                try
                {
                    out << setw(4) << a.select(i, j);
                }
                catch (out_of_range &e)
                {
                    out << setw(4) << "0";
                }
            }
            out << endl;
        }
        return out;
    }
};

int main()
{
    ChessBoardArray a(4, 0); // size 4x4, rows and columns numbered from 1
    a[0][0] = 5;
    a[3][3] = 7;
    try
    {
        a[2][1] = 7;
    }
    catch (out_of_range &e)
    {
        cout << "a[2][1] is black" << endl;
    }
    try
    {
        cout << a[1][2] << endl;
    }
    catch (out_of_range &e)
    {
        cout << "and so is a[1][2]" << endl;
    }
    cout << a;
}