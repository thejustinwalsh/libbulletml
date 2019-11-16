#ifndef FORMULA_VARIABLE_H_
#define FORMULA_VARIABLE_H_

#include "bulletmlcommon.h"
#include "bulletmlrunner.h"
#include "formula.h"

#include <cstdlib>
#include <vector>

namespace Variables {
    BULLETML_API extern double rank;
    BULLETML_API extern std::vector<double> *parameters;
    BULLETML_API extern BulletMLRunner *runner;
}

template <typename TVal>
class BULLETML_API Random : public AbstractNumber<TVal> {
public:
    virtual TVal value() const { return Variables::runner->getRand(); }
};

template <typename TVal>
class BULLETML_API Rank : public AbstractNumber<TVal> {
public:
    virtual TVal value() const { return Variables::rank; }
};

template <typename TVal>
class BULLETML_API Param : public AbstractNumber<TVal> {
public:
    explicit Param(int id) : m_id(id) {
    }

    virtual TVal value() const {
        if (Variables::parameters &&
            m_id < Variables::parameters->size()) {
            return (*Variables::parameters)[m_id];
        } else {
            return 1;
        }
    }

private:
    int m_id;
};

#endif // ! FORMULA_VARIABLE_H_
