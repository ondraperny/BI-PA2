//
// Created by ondra on 5/11/2018.
//

#ifndef SRC_CEVENT_H
#define SRC_CEVENT_H

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

/**
 * @class CEvent
 * parent class for specific types of events, store informations that are same for all types of events
 */
class CEvent {
public:
    /**
     * constructor with required informations
     * @param duration
     * @param name
     */
    explicit CEvent(const std::string &name, const int &duration, const std::string &place);

    /// prints informations about given event - virtual method
    virtual void print() const = 0;

    // getters
    const std::string &getName() const;

    const std::string &getPlace() const;

    int getDuration() const;

    int getType() const;

    /// virtual getter - get type specific attribute from different types of events
    virtual const std::string getSpecial() const = 0;

protected:
    std::string m_name;
    std::string m_place;
    int m_duration;
    /// type of event - 1.mandatory/2.optional/3.movable
    int m_type;
};

/**
 * @class CMandatory
 * child class
 * as special atrribute contain reason why is event mandatory
 */
class CMandatory : public CEvent {
private:
    /// reason why this event is mandatory
    std::string m_reason;

public:
    explicit CMandatory(const std::string &reason, const std::string &name, const int &duration,
                        const std::string &place);

    void print() const override;

    const std::string getSpecial() const override;
};

/**
 * @class COptional
 * child class
 * as special atrribute contain bool value whether is user interested in this event or not
 */
class COptional : public CEvent {
private:
    /// preferences whether this event will be attended or not
    bool m_willAttend;

public:
    explicit COptional(bool willAttend, const std::string &name, const int &duration, const std::string &place);

    void print() const override;

    const std::string getSpecial() const override;
};

/**
 * @class CMovable
 * child class
 * as special atrribute contain date ( in string format ) , until when can be this event moved
 */
class CMovable : public CEvent {
private:
    /// date until when can be event moved
    std::string m_moveUntil;

public:
    explicit CMovable(const std::string &moveUntil, const std::string &name, const int &duration,
                      const std::string &place);

    void print() const override;

    const std::string getSpecial() const override;
};

#endif //SRC_CEVENT_H
