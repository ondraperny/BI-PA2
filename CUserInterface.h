//
// Created by ondra on 5/12/2018.
//

#ifndef SRC_CUSERINTERFACE_H
#define SRC_CUSERINTERFACE_H

#include <iostream>
#include <thread>
#include <string>
#include <limits>
#include <sstream>
#include <iomanip>

#include "CCalendar.h"

/**
 * @class CUserInterface
 * store map of CCalendars with users as keys
 * contain methods that provide interaction with user and calculate and prints results for him
 */
class CUserInterface {
public:
    /// opening function that open interface menu for user
    void menuStart();

private:
    /// map of users and their belonging calendar
    std::map<std::string, CCalendar> users;
    /// user's name
    std::string currentUser;

//  functions

    /**
     * checks whether inputted date is in correct format
     * @param format - date in string "DD.MM.YYYY"
     * @return true if format is correct
     */
    bool formatChecker(std::string format) const;

    /**
     * inform user - clear screen and for 2 sec show message
     * @param message for user
     */
    void infoMessage(const std::string &message) const;

//  prompts for user

    /// only wait until user hit enter
    void hitEnter() const;

    /**
     * request from user date in format DD.MM.YYYY ( this format is controlled and followed by validity test on date )
     * @param hourToo - if true prompt user to input hours as well
     * @return valid date
     */
    CDateAndTime promptDate(bool hourToo = false) const;

    /**
     * prompt user to input number of hours ( 0 - 24 )
     * @param specific message to user
     * @return number of hours
     */
    unsigned promptHour(const std::string &message) const;

    /**
     * prompt user to input either "y" or "n" for yes or no
     * @param message question for which will user answer y/n
     * @return true for "y" and false for "n"
     */
    bool promptBool(const std::string &message) const;

    /**
     * prompt user to input number (work in range 0-9)
     * @param minimal number that can be accepted
     * @param maximal number that can be accepted
     * @return 0 - 9 number, or -1 in case of wrong input
     */
    int promptChoice(const int &minimal, const int &maximal) const;

    /**
     * prompt user to write some text ( read whole line )
     * @param prompt message for user
     * @return text that was inputted by user
     */
    std::string promptString(const std::string &message) const;

//  menu functions

//  can't be const because map access is not const
    /// open interface for user for adding new event
    void menuEvent();

    /// open interface for adding user
    void menuUser();

    /// open interface for removing event
    void menuRemoveEvent();

    /// open interface for exporting event
    void menuExport();

    /// open interface for importing event
    void menuImport();

    /// open interface for main menu
    void menuView();

    /// open interface for searching for events
    void searchMenu();

    /// search for first free time in plan since current date and time
    void menuSearchFreeTime();

    /// move event - prompt user to input date of event, and the date where to move event
    void menuMoveEvent();

//  print functions

    /// prints days and events in month interval
    void printMonth(const CDateAndTime &date);

    /// prints days and events in month interval
    void printWeek(const CDateAndTime &date);

    /// prints days and events in month interval
    void printDay(const CDateAndTime &date);

    /// print main user interface ( with options )
    void printStart() const;

    /// print view interface
    void printView() const;

    /// print search interface
    void printSearch() const;

    /// print header for output format
    void printHeader() const;
};


#endif //SRC_CUSERINTERFACE_H
