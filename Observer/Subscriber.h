#include "Observer.h"

#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

class Observer;


class Subscriber {
    public:
    Subscriber(std::string name, Observer *o);
    void subscribeTo(Resource *r) const;
    void unsubscribeTo(Resource *r) const;
    void notify(Resource *r) const;
    ~Subscriber ();
    private:
    Observer* obs;
    std::string name;
};
#endif