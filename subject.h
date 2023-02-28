#pragma once
#include <list>
#include "ISubject.h"

class Subject : ISubject {
public:
    void Attach(IObserver* observer) override;

    void Detach(IObserver* observer) override;

    void Notify(const std::string& message) override;

private:
    std::list<IObserver*> list_observer_;
};