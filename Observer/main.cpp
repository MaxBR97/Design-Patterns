#include "Observer.h"


int main(int argc, char** argv) {
    std::shared_ptr<Observer> o = std::make_shared<Observer>();
    
    std::shared_ptr<Resource> apple = std::make_shared<Resource>(3, std::string("Apple") );
    std::shared_ptr<Resource> orange = std::make_shared<Resource> (5, std::string("Orange"));
    std::shared_ptr<Resource> peach = std::make_shared<Resource>(2 , std::string("Peach"));

    std::shared_ptr<Subscriber> max = std::make_shared<Subscriber>(std::string("Max"), o.get());
    std::shared_ptr<Subscriber> trump = std::make_shared<Subscriber>(std::string("Trump"), o.get());
    std::shared_ptr<Subscriber> stalin = std::make_shared<Subscriber>(std::string("Stalin"), o.get());

    max->subscribeTo(apple.get());
    trump->subscribeTo(apple.get());
    trump->subscribeTo(orange.get());
    stalin->subscribeTo(orange.get());
    stalin->subscribeTo(peach.get());

    std::cout << "-------" << std::endl;
    o->set(apple.get(), 15);
    o->set(orange.get(), 6);
    o->set(peach.get(), 1);

    trump->subscribeTo(peach.get());
    stalin->unsubscribeTo(peach.get());
    max->unsubscribeTo(apple.get());
    
    std::cout << "----------" << std::endl;
    o->set(apple.get(),3);
    o->set(peach.get(), 1);
}