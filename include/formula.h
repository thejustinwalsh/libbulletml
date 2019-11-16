/// 数式クラス
/// Formula Class

#ifndef FORMULA_H_
#define FORMULA_H_

#include "bulletmlcommon.h"

template <typename TVal>
class BULLETML_API AbstractNumber {
public:
    virtual TVal value() const = 0;
    virtual ~AbstractNumber() {}
};

template <typename TVal>
class BULLETML_API Number : public AbstractNumber<TVal> {
public:
    explicit Number(TVal val) : m_val(val) {
    }

    virtual TVal value() const { return m_val; }

private:
    TVal m_val;
};

typedef enum {
    op_null = 0,
    op_add,
    op_sub,
    op_mul,
    op_div
} Operator;

template <typename TVal>
class BULLETML_API Formula : public AbstractNumber<TVal> {
private:
    typedef AbstractNumber<TVal> ANumber;

public:
    virtual ~Formula() {
        delete m_lhs;
        delete m_rhs;
    }

    /// public だけど呼ばないで下さい。
    /// Please do not just call public.
    /**
     * @todo yacc の使いかたを調べて、これを private に
     *       Investigate how to use yacc and make it private
     */
    //@{
    explicit Formula(ANumber *val) :
        m_lhs(val),
        m_rhs(nullptr),
        m_op(op_null),
        m_headsub(false) {
    }

    Formula(ANumber *lhs, Operator op, ANumber *rhs) :
        m_lhs(lhs),
        m_rhs(rhs),
        m_op(op),
        m_headsub(false) {
    }

    Formula *setHeadSub() {
        m_headsub = true;
        return this;
    }
    //@}

    virtual TVal value() const {
        if (m_headsub) {
            return -valueBeforeHeadSub();
        } else {
            return valueBeforeHeadSub();
        }
    }

private:
    TVal valueBeforeHeadSub() const {
        switch (m_op) {
        case op_null:
            return m_lhs->value();
        case op_add:
            return m_lhs->value() + m_rhs->value();
        case op_sub:
            return m_lhs->value() - m_rhs->value();
        case op_mul:
            return m_lhs->value() * m_rhs->value();
        case op_div:
            return m_lhs->value() / m_rhs->value();
        default:
            return 0; // avoid warning
        }
    }

private:
    ANumber *m_lhs, *m_rhs;
    Operator m_op;
    bool m_headsub;
};

#endif // ! FORMULA_H_
