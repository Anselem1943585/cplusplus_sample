#include <iostream>
#include <iomanip>

using namespace std;

class Date
{
private:
    int day;
    int month;
    int year;
    static inline const int daysPerMonth[]{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31,30,31 };
    static const int stdYear{ 1970 };
    static bool isLeapYear(int year) { return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0; }
    void checkDate();

public:
    explicit Date(int d = 1, int m = 1, int y = stdYear) : day{ d }, month{ m }, year{ y }
    {
        checkDate();
    }

    Date(const Date& d2) : day{ d2.day }, month{ d2.month }, year{ d2.year }{}
    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }
    void setDate(int d, int m, int y)
    {
        day = d;
        month = m;
        year = y;
        checkDate();
    }

    Date& incDay();
    Date& decDay();
    Date& operator++(int);
    void print() const { cout << day << "." << month << "." << year << endl; }
    string dayOfTheWeek() const;
};

void Date::checkDate()
{
    if (year < 1 || month < 1 || month > 12 || day < 1 || (day > daysPerMonth[month - 1]
        && !(day == 29 && month == 2 && isLeapYear(year))))
    {
        day = month = 1;
        year = stdYear;
    }
}

Date& Date::incDay()
{
    ++day;
    if (day > daysPerMonth[month - 1] && !(day == 29 && month == 2 && isLeapYear(year)))
    {
        day = 1;
        if (++month == 13)
        {
            month = 1;
            ++year;
        }
    }
    return *this;
}
Date& Date::decDay()
{
    --day;
    if (day == 0)
    {
        if (--month == 0)
        {
            month = 12;
            --year;
        }
        if (month == 2 && isLeapYear(year))
            day = 29;
        else
            day = daysPerMonth[month - 1];
    }
    return *this;
}

Date& Date::operator++(int)
{
    Date temp{ *this };
    incDay();
    return temp;
}

ostream& operator<<(ostream& os, const Date& d)
{
    os << setw(2) << setfill('0') << d.getDay() << "."
        << setw(2) << d.getMonth() << "." << d.getYear() << setfill(' ');
    return os;
}

istream& operator>>(istream& is, Date& d)
{
    int dd, mm, yy;
    is >> dd;
    is.ignore(1, '.');
    is >> mm;
    is.ignore(1, '.');
    is >> yy;
    d.setDate(dd, mm, yy);
    return is;
}

string Date::dayOfTheWeek() const
{
    int d{ day };
    int m{ (month + 9) % 12 + 1 };
    int y{ year % 100 };
    if (month <= 2)
        --y;
    int c{ year / 100 };
    if (y == -1)
    {
        y = 99;
        --c;
    }
    int w{ (d + (int)floor(2.6 * m - 0.2) + y + y / 4 + c / 4 + 5 * c) % 7 };
    switch (w)
    {
    case 1:
        return "Monday";
    case 2:
        return "Tuesday";
    case 3:
        return "Wednesday";
    case 4:
        return "Thursday";
    case 5:
        return "Friday";
    case 6:
        return "Saturday";
    default: // 0
        return "Sunday";
    }
}

int main()
{

    int main() {
        if (__cplusplus == 201703L) std::cout << "C++17\n";
        else if (__cplusplus == 201402L) std::cout << "C++14\n";
        else if (__cplusplus == 201103L) std::cout << "C++11\n";
        else if (__cplusplus == 199711L) std::cout << "C++98\n";
        else std::cout << "pre-standard C++\n";

   /* Date d;

    cout << "Enter a date: \n";
    cin >> d;
    cout << "You entered: " << d << endl;
    cout << "It is a " << d.dayOfTheWeek() << endl;
    d.decDay().decDay().decDay();
    cout << "Three days before: " << d << endl;*/

    return 0;
}
