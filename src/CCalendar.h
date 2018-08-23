//
// Created by ondra on 5/18/2018.
//

#ifndef SRC_CCALENDAR_H
#define SRC_CCALENDAR_H

#include <map>
#include <string>
#include <memory>
#include <fstream>
#include <sstream>

#include "CDateAndTime.h"
#include "CEvent.h"

/**
 * @class CCalendar
 * store ell events in map with event CDateAndTime as key
 * contain methods that works with events
 */
class CCalendar {
public:
//  functions

    /// functions for adding all 3 types of events, all parameters are informations about event
    void addEventMandatory(const std::string &reason, CDateAndTime date, const std::string &name, const int &duration,
                           const std::string &place);

    void addEventOptional(bool willAttend, CDateAndTime date, const std::string &name, const int &duration,
                          const std::string &place);

    void addEventMovable(const std::string &moveUntil, CDateAndTime date, const std::string &name, const int &duration,
                         const std::string &place);

    /**
     * search and print all events that match searching criteria
     * @param name of searched event
     */
    void searchByName(std::string name) const;

    /**
     * search and print all events that match searching criteria
     * @param place of searched event
     */
    void searchByPlace(std::string place) const;

    /// search and print first free time ( date and hour ) since current time, when user have free time in calendar
    void searchFreeTime() const;

    /**
     * print all events in given interval
     * @param from start of interval
     * @param to end of interval
     */
    void printEvents(const CDateAndTime &from, const CDateAndTime &to) const;

    /// prints all events
    void printAllEvents() const;

    /**
     * move event from one time to another ( that is if given event can be moved )
     * @param date from
     * @param date to
     * @param date currTime
     * @return 0 = can be moved, 1 = event was not found, 2 = event is not movable, 3 = date for movable type expired
     */
    int moveEvent(const CDateAndTime &from, const CDateAndTime &to, const CDateAndTime &currTime);

    /**
     * remove event
     * @param date
     * @return true if event was succesfully removed
     */
    bool removeEvent(const CDateAndTime &date);

    /**
     * export event
     * @param date
     * @return true if event was succesfully exported
     */
    bool exportEvent(const CDateAndTime &date);

    /**
     * import event
     * @param fileName
     * @return true if event was succesfully imported
     */
    bool importEvent(std::string fileName);

private:
    /// map with date as a key and pointer to event second attribute
    std::map<CDateAndTime, std::unique_ptr<CEvent>> p_events;
};

#endif //SRC_CCALENDAR_H
