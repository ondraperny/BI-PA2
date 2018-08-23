//
// Created by ondra on 5/26/2018.
//

#include "CDateAndTime.h"

CDateAndTime::CDateAndTime(const unsigned &year, const unsigned &month, const unsigned &day, const unsigned &hour) :
        m_year(year), m_month(month), m_day(day), m_hour(hour) {}

CDateAndTime::CDateAndTime(const CDateAndTime &date) : m_year(date.m_year), m_month(date.m_month), m_day(date.m_day),
                                                       m_hour(date.m_hour) {}

CDateAndTime::CDateAndTime() {
    m_hour = 0;
}

bool operator<(const CDateAndTime &x, const CDateAndTime &y) {
    return std::make_tuple(x.m_year, x.m_month, x.m_day, x.m_hour) <
           std::make_tuple(y.m_year, y.m_month, y.m_day, y.m_hour);
}

bool operator>(const CDateAndTime &x, const CDateAndTime &y) {
    return std::make_tuple(x.m_year, x.m_month, x.m_day, x.m_hour) >
           std::make_tuple(y.m_year, y.m_month, y.m_day, y.m_hour);
}

CDateAndTime &CDateAndTime::operator=(const CDateAndTime &x) {
    m_year = x.m_year;
    m_month = x.m_month;
    m_day = x.m_day;
    m_hour = x.m_hour;
    return *this;
}

CDateAndTime CDateAndTime::currTimeAndDate() const {
    std::stringstream out;
//  getting current time3

    struct tm *currTime;
    time_t currT;
    time(&currT);
    currTime = localtime(&currT);
    int y = currTime->tm_year + 1900;
    int m = currTime->tm_mon + 1;
    int d = currTime->tm_mday;
    int h = currTime->tm_hour;
    return CDateAndTime(y, m, d, h);
}

unsigned CDateAndTime::daysInMonth(const CDateAndTime &date) const {
    unsigned monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
//  if is leap year => february = 29 days
    if ((date.m_year % 4 == 0 && date.m_year % 100 != 0) || (date.m_year % 400 == 0 && date.m_year % 4000 != 0))
        monthDays[1] = 29;
    return monthDays[date.m_month - 1];
}

bool CDateAndTime::isDateValid(const CDateAndTime &date) const {
    unsigned monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
//  if is leap year => february = 29 days
    if ((date.m_year % 4 == 0 && date.m_year % 100 != 0) || (date.m_year % 400 == 0 && date.m_year % 4000 != 0))
        monthDays[1] = 29;
//  control if date is valid
    if (date.m_day > monthDays[date.m_month - 1] || date.m_month > 12 || date.m_month < 1 || date.m_day < 1)
        return false;
    return true;
}

int CDateAndTime::dayOfWeek(const CDateAndTime &date) const {
    unsigned t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    unsigned y = date.m_year;
    y -= date.m_month < 3;
    return (y + y / 4 - y / 100 + y / 400 + t[date.m_month - 1] + date.m_day) % 7;
}

std::string CDateAndTime::dayByIndex(const int &index) const {
    if (index == 1)
        return "Monday";
    else if (index == 2)
        return "Tuesday";
    else if (index == 3)
        return "Wednesday";
    else if (index == 4)
        return "Thursday";
    else if (index == 5)
        return "Friday";
    else if (index == 6)
        return "Saturday";
    else
        return "Sunday";
}

unsigned CDateAndTime::dateToDays(const CDateAndTime &date) const {
    unsigned y = date.m_year;
    y -= date.m_month <= 2;
    unsigned era = (y >= 0 ? y : y - 399) / 400;
    unsigned yoe = (y - era * 400);      // [0, 399]
    unsigned doy = (153 * (date.m_month + (date.m_month > 2 ? -3 : 9)) + 2) / 5 + date.m_day - 1;  // [0, 365]
    unsigned doe = yoe * 365 + yoe / 4 - yoe / 100 + doy;         // [0, 146096]
    return era * 146097 + (doe) - 719468;
}

CDateAndTime CDateAndTime::daysToDate(unsigned z) const {
    z += 719468;
    unsigned era = (z >= 0 ? z : z - 146096) / 146097;
    unsigned doe = (z - era * 146097);
    unsigned yoe = (doe - doe / 1460 + doe / 36524 - doe / 146096) / 365;
    unsigned y = (yoe) + era * 400;
    unsigned doy = doe - (365 * yoe + yoe / 4 - yoe / 100);
    unsigned mp = (5 * doy + 2) / 153;
    unsigned d = doy - (153 * mp + 2) / 5 + 1;
    unsigned m = mp + (mp < 10 ? 3 : -9);

    return CDateAndTime(y + (m <= 2), m, d);
}

std::string CDateAndTime::dateReformat(const CDateAndTime &date, bool day) const {
    std::stringstream out;
//  transform date into string format ready for print
    out << std::setfill(' ') << std::setw(2) << date.m_day << "." << std::setfill(' ') << std::setw(2) << date.m_month
        << "." <<
        std::setfill(' ') << std::setw(2) << date.m_year;
    if (day)
        out << " " << dayByIndex(dayOfWeek(date));
    else
        out << " " << std::setfill(' ') << std::setw(2) << date.m_hour << ":00";
    return out.str();
}

std::ostream &operator<<(std::ostream &os, const CDateAndTime &date) {
    os << std::setfill('0') << std::setw(4) << date.m_year << std::setfill('0') << std::setw(2) << date.m_month
       << std::setfill('0') << std::setw(2) << date.m_day << std::setfill('0') << std::setw(2) << date.m_hour;
    return os;
}

std::istream &operator>>(std::istream &is, CDateAndTime &date) {
    std::string in;
    is >> in;
    date.m_year = (unsigned) stoi(in.substr(0, 4));
    date.m_month = (unsigned) stoi(in.substr(4, 2));
    date.m_day = (unsigned) stoi(in.substr(6, 2));
    date.m_hour = (unsigned) stoi(in.substr(8, 2));
    return is;
}

unsigned int CDateAndTime::getDay() const {
    return m_day;
}

unsigned int CDateAndTime::getHour() const {
    return m_hour;
}

void CDateAndTime::setDay(unsigned int m_day) {
    CDateAndTime::m_day = m_day;
}

void CDateAndTime::setHour(unsigned int m_hour) {
    CDateAndTime::m_hour = m_hour;
}
