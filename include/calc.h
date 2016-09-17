#ifndef CALC_H_
#define CALC_H_

#include "bulletmlcommon.h"
#include "formula.h"

#include <memory>
#include <string>

BULLETML_API std::unique_ptr<Formula<double>> calc(const std::string& str);

#endif // CALC_H_
