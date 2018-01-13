#ifndef BULLETRUNNER_IMPL_H_
#define BULLETRUNNER_IMPL_H_

#include "bulletmltree.h"

#include <memory>
#include <stack>
#include <vector>

class BulletMLRunner;
class BulletMLState;
class BulletMLParser;

typedef std::vector<double> BulletMLParameter;

template<class TC>
class Validatable {
public:
    Validatable() : _isValidated(false) {
	}

    bool isValidate() const { return _isValidated; }

    void validate() { _isValidated = true; }
    void invalidate() { _isValidated = false; }

    operator TC&() { return _val; }

    TC &operator=(const TC &rhs) {
        _isValidated = true;
        _val = rhs;
        return *this;
    }

protected:
    TC _val;
    bool _isValidated;
};

/// xyの初期値・終値から任意のxに対するyの線形補間を得るクラス
/// A class that obtains a linear interpolation of y for arbitrary x
/// from the initial value and the final value of xy
template<class TX = double, class TY = double>
class LinearFunc {
public:
    LinearFunc(const TX &firstX, const TX &lastX, const TY &firstY, const TY &lastY) :
        m_firstX(firstX),
        m_lastX(lastX),
        m_firstY(firstY),
        m_lastY(lastY),
        m_gradient((lastY - firstY) / (lastX - firstX)) {
    }

    TY getValue(const TX &x) { return m_firstY + m_gradient * (x - m_firstX); }

	bool isLast(const TX &x) { return x >= m_lastX; }
	TY getLast() { return m_lastY; }

protected:
    TX m_firstX, m_lastX;
    TY m_firstY, m_lastY;
    TY m_gradient;
};

class BulletMLRunnerImpl {
public:
    explicit BulletMLRunnerImpl(BulletMLState *state, BulletMLRunner *runner);
    virtual ~BulletMLRunnerImpl();

    /// 実行する
	/// Execute
    void run();

public:
    /// 実行が終了しているかどうか
	/// Whether execution has ended
    bool isEnd() const { return m_end; }

public:
    /// 弾の方向変更を登録し、自前で各ターン変更する
	/// Register direction change of bullets and change each turn on your own
    virtual void calcChangeDirection(double direction, int term, bool seq);
    /// 弾の速度変更を登録し、自前で各ターン変更する
	/// Register the speed change of bullets and change each turn on your own
    virtual void calcChangeSpeed(double speed, int term);
    /// 弾の加速を登録し、自前で各ターン変更する
	/// Register acceleration of bullets and change each turn on your own
    /**
     * @todo horizontal, vertical の type は未実装です。
	 *       The horizontal and vertical types are not implemented yet.
     */
    virtual void calcAccelX(double vertical, int term, BulletMLNode::Type type);
    /// 弾の加速を登録し、自前で各ターン変更する
	/// Register acceleration of bullets and change each turn on your own
    /**
     * @todo horizontal, vertical の type は未実装です。
	 *       The horizontal and vertical types are not implemented yet.
     */
    virtual void calcAccelY(double horizontal, int term, BulletMLNode::Type type);

protected:
    /**
     * 本当に挙動が気に入らない場合は仮想関数化して、
     * これらのオーバーライドも考えてください。
	 * If you really do not like this behavior,
	 * virtualize it and think about these overrides.
     */
    //@{
    void runBullet();
    void runAction();
    void runFire();
    void runWait();
    void runRepeat();
    void runBulletRef();
    void runActionRef();
    void runFireRef();
    void runChangeDirection();
    void runChangeSpeed();
    void runAccel();
    void runVanish();
    //@}

private:
    void changes();
    void runSub();

    bool isTurnEnd();
    void doWait(int frame);

    void setDirection();
    void setSpeed();

    void shotInit() {
        m_speed.invalidate();
        m_direction.invalidate();
    }

    double getNumberContents(const BulletMLNode *node);
    std::vector<double> *getParameters();
    double getSpeed(BulletMLNode *spdNode);
    double getDirection(BulletMLNode *dirNode, bool prevChange = true);

private:
    std::unique_ptr<LinearFunc<int, double>> m_changeDir;
    std::unique_ptr<LinearFunc<int, double>> m_changeSpeed;
    std::unique_ptr<LinearFunc<int, double>> m_accelX;
    std::unique_ptr<LinearFunc<int, double>> m_accelY;

protected:
    Validatable<double> m_speed, m_direction, m_prevSpeed, m_prevDirection;

    typedef BulletMLParameter Parameters;
    std::shared_ptr<Parameters> m_parameters;

protected:
    BulletMLParser *m_bulletml;
    BulletMLNode *m_action;
    std::vector<BulletMLNode *> m_node;
    int m_actionTurn;
    std::vector<int> m_actionTurns;
    int m_endTurn;
    size_t m_actionIter;
    bool m_end;

protected:
    struct RepeatElem {
        RepeatElem(int i, int e, BulletMLNode *a) :
            ite(i),
            end(e),
            act(a) {
        }

        int ite, end;
        BulletMLNode *act;
    };

    typedef std::stack<RepeatElem *> RepeatStack;
    RepeatStack m_repeatStack;
    typedef std::stack<std::pair<BulletMLNode *, std::shared_ptr<Parameters>>> RefStack;
    RefStack m_refStack;

    typedef void (BulletMLRunnerImpl::*Method)();
    static Method m_commandMap[BulletMLNode::nameSize];

protected:
    BulletMLRunner *m_runner;
};

#endif // ! BULLETRUNNER_IMPL_H_
