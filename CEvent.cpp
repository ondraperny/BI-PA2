//
// Created by ondra on 5/11/2018.
//

#include "CEvent.h"

// constructors for all types of events
CEvent::CEvent(const std::string &name, const int &duration, const std::string &place) : m_name(name), m_place(place),
                                                                                         m_duration(duration) {}

CMandatory::CMandatory(const std::string &reason, const std::string &name, const int &duration,
                       const std::string &place) :
        CEvent(name, duration, place), m_reason(reason) {
    m_type = 1;
}

COptional::COptional(bool willAttend, const std::string &name, const int &duration, const std::string &place) :
        CEvent(name, duration, place), m_willAttend(willAttend) {
    m_type = 2;
}

CMovable::CMovable(const std::string &moveUntil, const std::string &name, const int &duration, const std::string &place)
        :
        CEvent(name, duration, place), m_moveUntil(moveUntil) {
    m_type = 3;
}

// formatted prints for every event type
void CMandatory::print() const {
    std::cout << std::setfill(' ') << std::setw(20) << "Mandatory |" <<
              std::setfill(' ') << std::setw(18) << m_name << " |" <<
              std::setfill(' ') << std::setw(18) << m_place << " |" <<
              std::setfill(' ') << std::setw(18) << m_duration << " |" <<
              std::setfill(' ') << std::setw(18) << m_reason << " |" << std::endl;
}

void COptional::print() const {
    std::string willAttend;
    if (m_willAttend)
        willAttend = "will attend";
    else
        willAttend = "will NOT attend";
    std::cout << std::setfill(' ') << std::setw(20) << "Optional  |" <<
              std::setfill(' ') << std::setw(18) << m_name << " |" <<
              std::setfill(' ') << std::setw(18) << m_place << " |" <<
              std::setfill(' ') << std::setw(18) << m_duration << " |" <<
              std::setfill(' ') << std::setw(18) << willAttend << " |" << std::endl;
}

void CMovable::print() const {
    std::cout << std::setfill(' ') << std::setw(20) << "Movable   |" <<
              std::setfill(' ') << std::setw(18) << m_name << " |" <<
              std::setfill(' ') << std::setw(18) << m_place << " |" <<
              std::setfill(' ') << std::setw(18) << m_duration << " |" <<
              std::setfill(' ') << std::setw(18) << m_moveUntil << " |" << std::endl;
}


const std::string &CEvent::getName() const {
    return m_name;
}

const std::string &CEvent::getPlace() const {
    return m_place;
}

int CEvent::getDuration() const {
    return m_duration;
}

int CEvent::getType() const {
    return m_type;
}

const std::string CMandatory::getSpecial() const {
    return m_reason;
}

const std::string COptional::getSpecial() const {
    if (m_willAttend)
        return "yes";
    else
        return "no";
}

const std::string CMovable::getSpecial() const {
    return m_moveUntil;
}