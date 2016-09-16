#ifndef FORMULA_VARIABLE_H_
#define FORMULA_VARIABLE_H_

#include "formula.h"
#include "bulletmlrunner.h"
#include "bulletmlcommon.h"

#include <cstdlib>
#include <vector>

namespace Variables {
	BULLETML_API extern double rank;
	BULLETML_API extern std::vector<double>* parameters;
	BULLETML_API extern BulletMLRunner* runner;
}

template <typename Val_>
class BULLETML_API Random : public AbstractNumber<Val_> {
public:
	virtual Val_ value() const {
		return Variables::runner->getRand();
	}
};

template <typename Val_>
class BULLETML_API Rank : public AbstractNumber<Val_> {
public:
	virtual Val_ value() const {
		return Variables::rank;
	}
};

template <typename Val_>
class BULLETML_API Param : public AbstractNumber<Val_> {
public:
	explicit Param(int id) : id_(id) {}
	virtual Val_ value() const {
		if (Variables::parameters && id_ < Variables::parameters->size()) {
			return (*Variables::parameters)[id_];
		}
		else {
			return 1;
		}
	}

private:
	int id_;
};

#endif // ! FORMULA_VARIABLE_H_
