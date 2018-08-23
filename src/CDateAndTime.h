//
// Created by ondra on 5/26/2018.
//

#ifndef SRC_CDATEANDTIME_H
#define SRC_CDATEANDTIME_H

#include <tuple>
#include <iostream>
#include <iomanip>
#include <chrono>

/**
 * @class CDateAndTime
 * store date and hours
 * contain methods that work with date and hours
 */
class CDateAndTime {
public:
//    constructors
    CDateAndTime(const unsigned &year, const unsigned &month, const unsigned &day, const unsigned &hour = 0);

    CDateAndTime(const CDateAndTime &date);

    CDateAndTime();

    friend bool operator<(const CDateAndTime &y, const CDateAndTime &x);

    friend bool operator>(const CDateAndTime &y, const CDateAndTime &x);

    CDateAndTime &operator=(const CDateAndTime &x);

    /**
     * check whether input date is valid or not
     * @param date
     * @return true if date is valid, false otherwise
     */
    bool isDateValid(const CDateAndTime &date) const;

    /**
     * find current date and time
     * @return current date and time
     */
    CDateAndTime currTimeAndDate() const;

    /**
     * transform date into string "print ready format"
     * @param date
     * @param day if true output format is "DD.MM.YYYY 'day of week'" , otherwise "DD.MM.YYYY HH:00"
     * @return date in string format
     */
    std::string dateReformat(const CDateAndTime &date, bool day = false) const;

    /**
     * calculate number of days from date ( Howard Hinnant's algorithm )
     * @param date
     * @return number of days
     */
    unsigned dateToDays(const CDateAndTime &date) const;

    /**
     * find which day of week is current ( Sakamoto's algorithm )
     * @param date
     * @return index for day in week, Monday ==1 , Tuesday == 2, etc. up to 7
     */
    int dayOfWeek(const CDateAndTime &date) const;

    /**
     * return day of Week based on input index
     * @param index - number in interval 1-7
     * @return name of Day as string
     */
    std::string dayByIndex(const int &index) const;

    /**
     * transform number of days to date ( Howard Hinnant's algorithm )
     * @param z number of days
     * @return date
     */
    CDateAndTime daysToDate(unsigned z) const;

    /**
     * calculate number of days in month for given date
     * @param date
     * @return number of days in month
     */
    unsigned daysInMonth(const CDateAndTime &date) const;

    /// output date in format "YYYYMMDDHH""
    friend std::ostream &operator<<(std::ostream &os, const CDateAndTime &date);

    /// read date in format "YYYYMMDDHH""
    friend std::istream &operator>>(std::istream &is, CDateAndTime &date);

//  getters
    unsigned int getDay() const;

    unsigned int getHour() const;
//  setters
    void setDay(unsigned int m_day);

    void setHour(unsigned int m_hour);

private:
    unsigned m_year;
    unsigned m_month;
    unsigned m_day;
    unsigned m_hour;
};

#endif //SRC_CDATEANDTIME_H
