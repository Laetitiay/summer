#include "PointSet.h"

PointSet::PointSet() {

}

PointSet::~PointSet() {

}

std::string PointSet::toString() const {
    return std::__cxx11::string();
}

bool PointSet::add(const Point &toAdd) {
    return false;
}

bool PointSet::remove(Point &toRemove) {
    return false;
}

int PointSet::size() const {
    return 0;
}

bool PointSet::operator==(const PointSet &rhp) const {
    return false;
}

bool PointSet::operator!=(const PointSet &rhp) const {
    return false;
}

PointSet PointSet::operator-(const PointSet &set1, const PointSet &set2) {
    return PointSet();
}

PointSet PointSet::operator&(const PointSet &set1, const PointSet &set2) {
    return PointSet();
}

PointSet PointSet::operator=(const PointSet &rhs) {
    return PointSet();
}

