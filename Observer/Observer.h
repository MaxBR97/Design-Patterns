#ifndef OBSERVER_H
#define OBSERVER_H
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include "Resource.cpp"
#include "Subscriber.h"

class Subscriber;

class Observer {
    public:
    std::unordered_map<Resource *, std::vector<Subscriber *>> subscriptions;
    Observer();
    void subscribe(const Subscriber*, Resource*);
    void unsubscribe(const Subscriber*, Resource*);
    void notify(Resource*);
    void set(Resource*, int);
    ~Observer();
};
#endif