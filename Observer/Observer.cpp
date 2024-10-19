#include "Observer.h"

Observer::Observer() {}

void Observer::subscribe (const Subscriber *s, Resource *r) {
    std::vector<Subscriber*> &vec = subscriptions[r];
    if (std::find(vec.begin(), vec.end(), const_cast<Subscriber*>(s) ) == vec.end()){
        vec.push_back(const_cast<Subscriber*>(s));
    }
}

void Observer::unsubscribe (const Subscriber *s, Resource *r) {
    std::vector<Subscriber*>& vec = subscriptions[r];
    std::vector<Subscriber*>::iterator end = std::remove(vec.begin(), vec.end(), const_cast<Subscriber*>(s));
    vec.erase(end, vec.end());
}

void Observer::notify(Resource *r) {
    std::vector<Subscriber*>& vec = subscriptions[r];
    for ( Subscriber *s : vec ){
        s->notify(r);
    }
}

void Observer::set(Resource *r, int val){
    r->set(val);
    this->notify(r);
}

Observer::~Observer(){}