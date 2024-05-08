#include <functional>
#include "Subscriber.h"

enum comparatorTags { COMPARATOR_SURNAME = 0, COMPARATOR_NAME, COMPARATOR_TARIFF, COMPARATOR_PHONE, COMPARATOR_KEY };

static std::function<bool(const Subscriber&, const Subscriber&)> compareNames = [](const Subscriber& a, const Subscriber& b)->bool {return a.getName() < b.getName(); };
static std::function<bool(const Subscriber&, const Subscriber&)> compareSurnames = [](const Subscriber& a, const Subscriber& b)->bool {return a.getSurname() < b.getSurname(); };
static std::function<bool(const Subscriber&, const Subscriber&)> compareTariffs = [](const Subscriber& a, const Subscriber& b)->bool {return a.getTariff() < b.getTariff(); };
static std::function<bool(const Subscriber&, const Subscriber&)> comparePhones = [](const Subscriber& a, const Subscriber& b)->bool {return a.getPhone() < b.getPhone(); };
static std::function<bool(const Subscriber&, const Subscriber&)> compareKeys = [](const Subscriber& a, const Subscriber& b)->bool {return (a.getName() + a.getSurname()) < (b.getName() + b.getSurname()); };

static std::function<bool(const Subscriber&, const Subscriber&)> comparators[5] = {compareSurnames, compareNames, compareTariffs, comparePhones, compareKeys};
