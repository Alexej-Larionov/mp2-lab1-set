// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"


TSet::TSet(int mp) : BitField(mp) , MaxPower(mp)
{
}

// конструктор копирования
TSet::TSet(const TSet& s) : BitField(s.BitField), MaxPower(s.MaxPower)
{
}

// конструктор преобразования типа
TSet::TSet(const TBitField& bf) : BitField(bf) , MaxPower(bf.GetLength())
{
}

TSet::operator TBitField() 
{
    TBitField bf(BitField);
    return bf;
}

int TSet::GetMaxPower(void) const  // получить макс. к-во эл-тов
{
    return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{ 
    if ((Elem < 0) || (Elem >= MaxPower))
    {
        throw "Error: (IsMember) array out of bounds";
    }

    return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem)  // включение элемента множества
{
    if ((Elem < 0) || (Elem >= MaxPower))
    {
        throw "Error:(InsElem) array out of bounds";
    }

    if (!IsMember(Elem))
    {
        BitField.SetBit(Elem);
    }
}

void TSet::DelElem(const int Elem)  // исключение элемента множества
{
    if ((Elem < 0) || (Elem >= MaxPower))
    {
        throw "Error: (DelElem) array out of bounds";
    }

    if (IsMember(Elem))
    {
        BitField.ClrBit(Elem);
    }
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet& s)// присваивание
{ 
    if (&s == this)
        return *this;
    BitField = s.BitField;
    MaxPower = s.MaxPower;
    return *this;
}

int TSet::operator==(const TSet& s) const // сравнение
{ 
        return (BitField == s.BitField);
}

int TSet::operator!=(const TSet& s) const // сравнение
{ 
    return !(*this == s);
}

TSet TSet::operator+(const TSet& s)// объединение
{ 
    TSet temp((*this).BitField | s.BitField);
    return temp;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{ 
    TSet temp(*this);
    temp.InsElem(Elem);
    return temp;
}

TSet TSet::operator-(const int Elem)// разность с элементом
{ 
    TSet temp(*this);
    temp.DelElem(Elem);
    return temp;
}

TSet TSet::operator*(const TSet& s)// пересечение
{ 
    TSet temp(BitField & s.BitField);
    return temp;
}

TSet TSet::operator~(void) // дополнение
{ 
    TSet temp(~(*this).BitField);
    return temp;
}

// перегрузка ввода/вывода

istream& operator>>(istream& istr, TSet& s) // ввод
{ 
    int elem;
    char check;
    char check;
    do 
    {
        istr >> check;
    } while (check != '{');

    do 
    {
        istr >> elem;
        s.InsElem(elem);
        do
            istr >> check;
        while ((check != ',') && (check != '}'));
    }
    while (check != '}');
    return istr;
}

ostream& operator<<(ostream& ostr, const TSet& s) // вывод
{ 
    int el = s.GetMaxPower() - 1;
    while (!s.IsMember(el))
        el--;
    for (int i = 0; i < el; i++)
        if (s.IsMember(i))
            ostr << i << " ";

    ostr << el << endl;
    return ostr;
}