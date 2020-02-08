#include "Figure.hpp"

bool Figure::empty() { return true; }

Figure::Figure() {}
Figure::~Figure() {}
std::ostream *Figure::Show(std::ostream &os) { return &os; }