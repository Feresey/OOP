#ifndef Sqr_H
#define Sqr_H

#include <cstdlib>
#include <iostream>
#include "Figure.hpp"

class Sqr : public Figure
{
public:
  Sqr();
  Sqr(std::istream &is);
  Sqr(size_t a);
  Sqr(const Sqr &orig);

  double Square() override;
  void Print() override;

  virtual ~Sqr();

private:
  size_t side_a;
};

#endif //Sqr_H