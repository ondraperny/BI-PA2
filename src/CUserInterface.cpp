//
// Created by ondra on 5/12/2018.
//

#include "CUserInterface.h"

void CUserInterface::printStart() const {
//  clear console
    std::cout << "\033c";
    std::cout << "0. Exit calendar" << std::endl;
    std::cout << "1. Calendar view" << std::endl;
    std::cout << "2. Add new event" << std::endl;
    std::cout << "3. Move event" << std::endl;
    std::cout << "4. Delete event" << std::endl;
    std::cout << "5. Search event" << std::endl;
    std::cout << "6. Export event" << std::endl;
    std::cout << "7. Import event" << std::endl;
    std::cout << "8. Search free date" << std::endl;
    std::cout << "9. Change user" << std::endl;
}


void CUserInterface::printSearch() const {
    std::cout << "\033c";
    std::cout << "Select by what key you want search" << std::endl;
    std::cout << "0. Return to main menu" << std::endl;
    std::cout << "1. Search by place of event" << std::endl;
    std::cout << "2. Search by name of event" << std::endl;
}

void CUserInterface::printHeader() const {
    std::cout << "\033c";
    std::cout << "                    " <<
              "|    Date and Time |" <<
              "     Type of Event |" <<
              "     Name of Event |" <<
              "    Place of Event |" <<
              " Duration of Event |" <<
              " Special attribute |" << std::endl;
    std::cout << "                    ------------------------------------------------------------------"
            "------------------------------------------------------" << std::endl;
}

void CUserInterface::printView() const {
    // clear console
    std::cout << "\033c";
    std::cout << "Select which view you want to print" << std::endl;
    std::cout << "0. Return to main menu" << std::endl;
    std::cout << "1. Day view" << std::endl;
    std::cout << "2. Week view" << std::endl;
    std::cout << "3. Month view" << std::endl;
    std::cout << "4. All Events" << std::endl;
}

//----------------------------------------------------------------------------------------------------------------------

bool CUserInterface::formatChecker(std::string format) const {
    if (format.length() != 10)
        return false;
//  checking the requested format
    if (format[0] >= '0' && format[0] <= '9' &&
        format[1] >= '0' && format[1] <= '9' &&
        format[2] == '.' &&
        format[3] >= '0' && format[3] <= '9' &&
        format[4] >= '0' && format[4] <= '9' &&
        format[5] >= '.' &&
        format[6] >= '0' && format[6] <= '9' &&
        format[7] >= '0' && format[7] <= '9' &&
        format[8] >= '0' && format[8] <= '9' &&
        format[9] >= '0' && format[9] <= '9')
        return true;
    return false;
}


void CUserInterface::hitEnter() const {
    std::cout << std::endl;
    std::string date;
    std::cout << "Hit enter for return to main menu" << std::endl;
    getline(std::cin, date);
}

void CUserInterface::infoMessage(const std::string &message) const {
    std::cout << "\033c";
    std::cout << message << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

std::string CUserInterface::promptString(const std::string &message) const {
    std::string eventPlace;
    std::cout << message << std::endl << std::flush;
    getline(std::cin, eventPlace);
    return eventPlace;
}

int CUserInterface::promptChoice(const int &minimal, const int &maximal) const {
    std::string input;
    int out = -1;
    std::string min = std::to_string(minimal);
    std::string max = std::to_string(maximal);

    std::cin >> input;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//  check whether input number satisfy conditions
    if (input.length() == 1 && input >= min && input <= max) {
        out = stoi(input);
    }
    return out;
}

CDateAndTime CUserInterface::promptDate(bool hourToo) const {
    std::stringstream out;
    std::string input;

    while (true) {
        std::cout << "Input date in format DD.MM.YYYY ( e.g. \"10.06.2018\" ) " << std::endl;
        std::cin >> input;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (formatChecker(input)) {
            int y = stoi(input.substr(6, 4));
            int m = stoi(input.substr(3, 2));
            int d = stoi(input.substr(0, 2));
            int h = 0;
//          prompt user to input hours as well if hourToo = true ( false by default )
            if (hourToo)
                h = promptHour("Write hours ( 0 - 24 )");
            CDateAndTime date(y, m, d, h);
            if (date.isDateValid(date))
                return date;
        }
        std::cout << "WRONG INPUT ( date does not exist ), try it again" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

unsigned CUserInterface::promptHour(const std::string &message) const {
    unsigned input;
    std::cout << message << std::endl;
//  read until user input correct information
    while (!(std::cin >> input) || input < 0 || input > 24) {
        std::cout << "WRONG INPUT, try it again" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return input;
}

bool CUserInterface::promptBool(const std::string &message) const {
    char input;
    bool willAttend;
    std::cout << message << std::endl;
    while (!(std::cin >> input && (input == 'y' || input == 'n'))) {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "WRONG INPUT, try it again" << std::endl;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (input == 'y')
        willAttend = true;
    else
        willAttend = false;
    return willAttend;
}

//----------------------------------------------------------------------------------------------------------------------

void CUserInterface::printMonth(const CDateAndTime &date) {
    std::string in;

    printHeader();
//    howManyDays from date returns number of days in given month
    for (size_t i = 1; i <= date.daysInMonth(date); ++i) {
        CDateAndTime dateIn = date;
        CDateAndTime dateOut = date;
        dateIn.setHour(0);
        dateOut.setHour(24);
        dateIn.setDay(i);
        dateOut.setDay(i);

        std::cout << dateIn.dateReformat(dateIn, true) << std::endl;
        users[currentUser].printEvents(dateIn, dateOut);
    }
}

void CUserInterface::printWeek(const CDateAndTime &date) {
    int days = date.dateToDays(date) - date.dayOfWeek(date);
    std::string in;

    printHeader();
    for (size_t i = 0; i < 7; ++i) {
        CDateAndTime dateIn = dateIn.daysToDate(days + i);
        CDateAndTime dateOut = dateOut.daysToDate(days + i);

        std::cout << dateIn.dateReformat(dateIn, true) << std::endl;
        users[currentUser].printEvents(dateIn, dateOut);
    }
}

void CUserInterface::printDay(const CDateAndTime &date) {
    printHeader();
    CDateAndTime dateIn = date;
    CDateAndTime dateOut = date;
    dateIn.setHour(0);
    dateOut.setHour(24);

    std::cout << dateIn.dateReformat(dateIn, true) << std::endl;
    users[currentUser].printEvents(dateIn, dateOut);
}

//----------------------------------------------------------------------------------------------------------------------

void CUserInterface::menuUser() {
    std::string username;
    std::cout << "\033c";
    std::cout << "List of users: " << std::endl;
//  print all users that have calendars
    for (const auto &user : users)
        std::cout << user.first << std::endl;
    username = promptString("Input your username");
//  if user has already calendar - it is loaded, otherwise will create new one and add him to users
    if (users.find(username) == users.end())
        users[username] = CCalendar();
    currentUser = username;
}

void CUserInterface::menuView() {
    int input;

    printView();
    while ((input = promptChoice(0, 4)) == -1) {
        infoMessage("WRONG INPUT, try it again");
        printView();
    }
//  calling printing function - by user's request
    if (input == 0) {
        return;
    } else if (input == 1) {
        printDay(promptDate());
    } else if (input == 2) {
        printWeek(promptDate());
    } else if (input == 3) {
        printMonth(promptDate());
    } else if (input == 4) {
        printHeader();
        users[currentUser].printAllEvents();
    }
    hitEnter();

}

void CUserInterface::searchMenu() {
    int input;

    printSearch();
    while ((input = promptChoice(0, 2)) == -1) {
        infoMessage("WRONG INPUT, try it again");
        printSearch();
    }

//  search and print events either by name or place
    if (input == 0) {
        return;
    } else if (input == 1) {
        std::string eventPlace = promptString("Input place of the event:");
        printHeader();
        users[currentUser].searchByPlace(eventPlace);
    } else if (input == 2) {
        std::string eventName = promptString("Input name of the event:");
        printHeader();
        users[currentUser].searchByName(eventName);
    }
    hitEnter();
}

void CUserInterface::menuExport() {
    std::stringstream res;
    CDateAndTime date = promptDate(true);

//  check if event was exported, if yes, message "Event was exported" will appear
    if (users[currentUser].exportEvent(date)) {
        infoMessage("Event was exported");
    } else
        infoMessage("No event was found in given date and time");
}

void CUserInterface::menuImport() {
    std::string input = promptString("Name of file to be imported:");

//  check if file with event exist, if yes then it will be imported and message "Event was imported" will appear
    if (users[currentUser].importEvent(input))
        infoMessage("Event was imported");
    else
        infoMessage("Event was NOT imported ( Wrong file input filename)");
}


void CUserInterface::menuSearchFreeTime() {
    std::cout << "\033c";
    users[currentUser].searchFreeTime();
    hitEnter();
}

void CUserInterface::menuRemoveEvent() {
    std::stringstream res;
    CDateAndTime date = promptDate(true);

    bool wasFound = users[currentUser].removeEvent(date);
    if (wasFound)
        infoMessage("Event was erased");
    else
        infoMessage("No event was found in given date and time");
}

void CUserInterface::menuMoveEvent() {
    std::cout << "Time and date of the event you want to move" << std::endl;
    CDateAndTime from = promptDate(true);

    std::cout << "Time and date where you want the event move to" << std::endl;
    CDateAndTime to = promptDate(true);

//  try to move event, based on result print info message
    int flag = users[currentUser].moveEvent(from, to, from.currTimeAndDate());

    if (flag == 0)
        infoMessage("Event was moved");
    else if (flag == 1)
        infoMessage("Event was NOT moved ( No event found on input date )");
    else if (flag == 2)
        infoMessage("Event was NOT moved ( This type of event cannot be moved )");
    else if (flag == 3)
        infoMessage("Event was NOT moved ( Time to move event already expired )");
}

void CUserInterface::menuEvent() {
    std::string eventName;
    std::string eventPlace;
    int type;
    bool eventWillAttend, repeat;
    unsigned times = 1, interval = 1, days, duration;
    std::stringstream dateOut;
    std::string eventReason;

//  prompt users for all info needed for new event
    CDateAndTime eventMoveUntil = CDateAndTime();
    repeat = promptBool("Do you want make this event repeatable ? (y/n)");
    if (repeat) {
        std::cout << "Input number how many times you want to repeat this event ( 0 - 1000 )" << std::endl;
        while (!(std::cin >> times) || times < 0 || times > 1000) {
            std::cout << "WRONG INPUT, try it again" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Input number in what intervals you want event to be repeated ( 0 - 400 )" << std::endl;
        while (!(std::cin >> interval) || interval < 0 || interval > 400) {
            std::cout << "WRONG INPUT, try it again" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    eventName = promptString("Input name of the event:");
    eventPlace = promptString("Input place of the event:");
    CDateAndTime date = promptDate(true);
    duration = promptHour("Input duration of event in hours ( 0 - 24 ):");
    std::cout << "Choose type of event ( 1 - Mandatory, 2 - Optional, 3 - Movable): " << std::endl;
    while ((type = promptChoice(1, 3)) == -1)
        std::cout << "WRONG INPUT, try it again" << std::endl;
//  special attributes based on different types of events
    if (type == 1) {
        eventReason = promptString("The reason of mandatory event:");
    } else if (type == 2) {
        eventWillAttend = promptBool("Will you participate in this event? (y/n): ");
    } else if (type == 3) {
        eventMoveUntil = promptDate();
    }
//  cycle for adding events that are repeated
    days = date.dateToDays(date);
    for (size_t i = 0; i < times; ++i, days += interval) {
        CDateAndTime outDate = outDate.daysToDate(days);
        outDate.setHour(date.getHour());
        if (type == 1) {
            users[currentUser].addEventMandatory(eventReason, outDate, eventName, duration, eventPlace);
        } else if (type == 2) {
            users[currentUser].addEventOptional(eventWillAttend, outDate, eventName, duration, eventPlace);
        } else if (type == 3) {
            std::stringstream out;
            out << eventMoveUntil;
            users[currentUser].addEventMovable(out.str(), outDate, eventName, duration, eventPlace);
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------

void CUserInterface::menuStart() {
    int choice;
    menuUser();
    while (true) {

        printStart();
        while ((choice = promptChoice(0, 9)) == -1) {
            infoMessage("WRONG INPUT, try it again");
            printStart();
        }

        if (choice == 0) {
            std::cout << "\033c";
            break;
        } else if (choice == 1) {
            menuView();
        } else if (choice == 2) {
            menuEvent();
        } else if (choice == 3) {
            menuMoveEvent();
        } else if (choice == 4) {
            menuRemoveEvent();
        } else if (choice == 5) {
            searchMenu();
        } else if (choice == 6) {
            menuExport();
        } else if (choice == 7) {
            menuImport();
        } else if (choice == 8) {
            menuSearchFreeTime();
        } else if (choice == 9) {
            menuUser();
        }
    }
}
