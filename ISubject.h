#pragma once
#include "IObserver.h"
#include <iostream>
#include <list>
#include <string>

class ISubject {
public:
	virtual ~ISubject() {};
	virtual void Attach(IObserver* observer) = 0;
	virtual void Detach(IObserver* observer) = 0;
	virtual void Notify(const std::string& message) = 0;
};