#include "Subscriber.h"

Subscriber::Subscriber(std::string name, Observer *o) : name(name), obs(o) {
    this->name = name;
    obs = o;
}

void Subscriber::subscribeTo(Resource *r) const {
    obs->subscribe(this, r);
}

void Subscriber::unsubscribeTo(Resource *r) const {
    obs->unsubscribe(this, r);
}

void Subscriber::notify(Resource *r)  const {
    std::cout << "subscriber " << this->name << " notified about: " << r->name << std::endl;
}

Subscriber::~Subscriber() {}