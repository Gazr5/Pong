#include "subject.h"

void Subject::Attach(IObserver* observer) {
    list_observer_.push_back(observer);
}

void Subject::Detach(IObserver* observer) {
    list_observer_.remove(observer);
}

void Subject::Notify(const std::string& message) {
    for (auto& observer : list_observer_) {
        observer->Update(message);
    }
}