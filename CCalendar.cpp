//
// Created by ondra on 5/18/2018.
//

#include "CCalendar.h"

void CCalendar::addEventMandatory(const std::string &reason, CDateAndTime date, const std::string &name,
                                  const int &duration, const std::string &place) {
    p_events[date] = std::make_unique<CMandatory>(reason, name, duration, place);
}

void CCalendar::addEventOptional(bool willAttend, CDateAndTime date, const std::string &name, const int &duration,
                                 const std::string &place) {
    p_events[date] = std::make_unique<COptional>(willAttend, name, duration, place);
}

void CCalendar::addEventMovable(const std::string &moveUntil, CDateAndTime date, const std::string &name,
                                const int &duration, const std::string &place) {
    p_events[date] = std::make_unique<CMovable>(moveUntil, name, duration, place);
}

void CCalendar::searchByName(std::string name) const {
//  iterate through all events, printing those which fulfills the condition
    for (const auto &x : p_events) {
        if ((x.second->getName()) == name) {
            std::cout << "--------------------" <<
                      std::setfill(' ') << std::setw(18) << x.first.dateReformat(x.first) << " |";
            x.second->print();
        }
    }
}

void CCalendar::searchByPlace(std::string place) const {
//  iterate through all events, printing those which fulfills the condition
    for (const auto &x : p_events) {
        if ((x.second->getPlace()) == place) {
            std::cout << "--------------------" <<
                      std::setfill(' ') << std::setw(18) << x.first.dateReformat(x.first) << " |";
            x.second->print();
        }
    }
}

bool CCalendar::exportEvent(const CDateAndTime &date) {
    int isHere = p_events.count(date);
    if (isHere == 0)
        return false;
//  write all informations into exported file ( if event on given date exists )
    static int counter = 0;
    std::stringstream fileName;
    fileName << "event" << counter++ << ".txt";
    std::ofstream file(fileName.str());
    file << p_events[date]->getType() << std::endl;
    file << p_events[date]->getName() << std::endl;
    file << date << std::endl;
    file << p_events[date]->getDuration() << std::endl;
    file << p_events[date]->getPlace() << std::endl;
    file << p_events[date]->getSpecial() << std::endl;
    file.close();
    return true;
}

bool CCalendar::importEvent(std::string fileName) {
    std::ifstream file(fileName);
    std::string data[6];

    if (!file.is_open())
        return false;
//  read file by lines - each contain one information in specific order:
//  type of event, name, date and time (in string), place, duration, special attribute ( type specific attribute )
    for (size_t i = 0; i < 6; ++i)
        getline(file, data[i]);
//  parse date from string format
    CDateAndTime date(stoi(data[2].substr(0, 4)), stoi(data[2].substr(4, 2)), stoi(data[2].substr(6, 2)),
                      stoi(data[2].substr(8, 2)));
//  create event based on type
    if (data[0] == std::to_string(1))
        addEventMandatory(data[5], date, data[1], stoi(data[3]), data[4]);
    else if (data[0] == std::to_string(2)) {
        bool willAttend;
        if (data[5] == "yes")
            willAttend = true;
        else
            willAttend = false;
        addEventOptional(willAttend, date, data[1], stoi(data[3]), data[4]);
    } else if (data[0] == std::to_string(3)) {
        addEventMovable(data[5], date, data[1], stoi(data[3]), data[4]);
    }
    file.close();
    return true;
}

void CCalendar::printAllEvents() const {
    for (const auto &x : p_events) {
        std::cout << "--------------------" <<
                  std::setfill(' ') << std::setw(18) << x.first.dateReformat(x.first) << " |";
        x.second->print();
    }
}

void CCalendar::printEvents(const CDateAndTime &from, const CDateAndTime &to) const {
    std::map<CDateAndTime, std::unique_ptr<CEvent>>::const_iterator itFrom, itTo;
    itFrom = p_events.lower_bound(from);
    itTo = p_events.upper_bound(to);
//  prints all events in inverval between two iterators
    for (; itFrom != itTo; ++itFrom) {
        std::cout << "--------------------" <<
                  std::setfill(' ') << std::setw(18) << itFrom->first.dateReformat(itFrom->first) << " |";
        itFrom->second->print();
    }
}


int CCalendar::moveEvent(const CDateAndTime &from, const CDateAndTime &to, const CDateAndTime &currTime) {
    std::map<CDateAndTime, std::unique_ptr<CEvent>>::const_iterator it;
    it = p_events.find(from);
    if (it == p_events.end())
        return 1;

    int type = it->second->getType();
//  non-movable types
    if (type == 1 || type == 2)
        return 2;
//  control if time for possible move didn't expired yet ( special attribute for CMovable event )
    std::stringstream out;
    out << currTime;
    if (out.str() > (it->second->getSpecial()))
        return 3;

    addEventMovable(it->second->getSpecial(), to, it->second->getName(), it->second->getDuration(),
                    it->second->getPlace());
    removeEvent(from);
    return 0;
}

bool CCalendar::removeEvent(const CDateAndTime &date) {
    std::map<CDateAndTime, std::unique_ptr<CEvent>>::const_iterator it;
    it = p_events.find(date);
    if (it == p_events.end())
        return false;
    p_events.erase(date);
    return true;
}

void CCalendar::searchFreeTime() const {
    CDateAndTime date = date.currTimeAndDate();
//  events can last maximal 24 hours, so function iterate 2 days before current date
    unsigned days = date.dateToDays(date) - unsigned(2);
    std::map<CDateAndTime, std::unique_ptr<CEvent>>::const_iterator it;
    it = p_events.lower_bound(date.daysToDate(days));
//  if there is no event, current time is printed
    if (it == p_events.end() || it->first > date) {
        std::cout << date.dateReformat(date) << std::endl;
        return;
    }

    int duration;
//  iterate through events, searching for first free time, since current time
    while (true) {
        duration = it->second->getDuration();
        days = date.dateToDays(it->first);
        CDateAndTime firstFree;
//      if hours exceed 24 => + day, - 24 hours
        if ((it->first.getHour() + duration) > 24) {
            firstFree = (date.daysToDate(days + unsigned(1)));
            firstFree.setHour(it->first.getHour() + duration - 24);
        } else {
            firstFree = (date.daysToDate(days));
            firstFree.setHour(it->first.getHour() + duration);
        }

//      date always keeps first possible time
        if (firstFree > date)
            date = firstFree;

        it++;
        if (it == p_events.end() || it->first > date)
            break;
    }
    std::cout << date.dateReformat(date) << std::endl;
}