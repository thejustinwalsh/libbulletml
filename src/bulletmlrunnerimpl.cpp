#include "bulletmlerror.h"
#include "bulletmlparser.h"
#include "bulletmlrunner.h"
#include "bulletmlrunnerimpl.h"
#include "formula-variables.h"

#include <cassert>
#include <cmath>

using namespace std;

BulletMLRunnerImpl::Method BulletMLRunnerImpl::m_commandMap[BulletMLNode::nameSize] = {
    &BulletMLRunnerImpl::runBullet,
    &BulletMLRunnerImpl::runAction,
    &BulletMLRunnerImpl::runFire,
    &BulletMLRunnerImpl::runChangeDirection,
    &BulletMLRunnerImpl::runChangeSpeed,
    &BulletMLRunnerImpl::runAccel,
    &BulletMLRunnerImpl::runWait,
    &BulletMLRunnerImpl::runRepeat,
    &BulletMLRunnerImpl::runBulletRef,
    &BulletMLRunnerImpl::runActionRef,
    &BulletMLRunnerImpl::runFireRef,
    &BulletMLRunnerImpl::runVanish
};

BulletMLRunnerImpl::BulletMLRunnerImpl(BulletMLState *state, BulletMLRunner *runner) :
    m_bulletml(state->getBulletML()),
    m_node(state->getNode().begin(), state->getNode().end()),
    m_actionIter(0),
    m_end(false),
    m_runner(runner) {
    if (state->getParameter().get() != 0) {
        m_parameters = state->getParameter();
    }

    delete state;

    for (vector<BulletMLNode*>::iterator it = m_node.begin(); it != m_node.end(); ++it) {
        (*it)->setParent(0);
    }

    /*
    for_each(node_.begin(), node_.end(), bind2nd(mem_fun(&BulletMLNode::setParent), 0));
    */
    m_actionTurn = -1;
    m_action = m_node[0];
}

BulletMLRunnerImpl::~BulletMLRunnerImpl() {
    while (!m_repeatStack.empty()) {
        delete m_repeatStack.top();
        m_repeatStack.pop();
    }
}

void BulletMLRunnerImpl::run() {
    if (isEnd()) {
        return;
    }

    changes();

    m_endTurn = m_runner->getTurn();

    // 最後の wait, change系を待つだけ
    // Just wait for the last wait, change system
    if (m_action == 0) {
        if (!isTurnEnd()) {
            if (m_changeDir.get() == 0 &&
                m_changeSpeed.get() == 0 &&
                m_accelX.get() == 0 &&
                m_accelY.get() == 0) {
                m_end = true;
            }
        }
        return;
    }

    m_action = m_node[m_actionIter];
    if (m_actionTurn == -1) {
        m_actionTurn = m_runner->getTurn();
    }

    runSub();

    if (m_action == 0) {
        m_actionIter++;
        if (m_node.size() != m_actionIter) {
            m_action = m_node[m_actionIter];
        }
    } else {
        m_node[m_actionIter] = m_action;
    }
}

void BulletMLRunnerImpl::calcChangeDirection(double direction, int term, bool seq) {
    int finalTurn = m_actionTurn + term;

    double dirFirst = m_runner->getBulletDirection();

    if (seq) {
        m_changeDir.reset(new LinearFunc<int, double>(m_actionTurn, finalTurn, dirFirst,
            dirFirst + direction * term));
    } else {
        double dirSpace;

        // ちゃんと近い方を回っていくのは結構難しいね
        // It's pretty difficult to get around this more neatly
        double dirSpace1 = direction - dirFirst;
        double dirSpace2;
        if (dirSpace1 > 0) {
            dirSpace2 = dirSpace1 - 360;
        } else {
            dirSpace2 = dirSpace1 + 360;
        }

        if (abs(dirSpace1) < abs(dirSpace2)) {
            dirSpace = dirSpace1;
        } else {
            dirSpace = dirSpace2;
        }

        m_changeDir.reset(new LinearFunc<int, double>(m_actionTurn, finalTurn, dirFirst,
            dirFirst + dirSpace));
    }
}

void BulletMLRunnerImpl::calcChangeSpeed(double speed, int term) {
    int finalTurn = m_actionTurn + term;

    double spdFirst = m_runner->getBulletSpeed();

    m_changeSpeed.reset(new LinearFunc<int, double>(m_actionTurn, finalTurn, spdFirst, speed));
}

void BulletMLRunnerImpl::calcAccelX(double vertical, int term, BulletMLNode::Type type) {
    int finalTurn = m_actionTurn + term;

    double firstSpd = m_runner->getBulletSpeedX();
    double finalSpd;

    if (type == BulletMLNode::sequence) {
        finalSpd = firstSpd + vertical * term;
    } else if (type == BulletMLNode::relative) {
        finalSpd = firstSpd + vertical;
    } else {
        finalSpd = vertical;
    }

    m_accelX.reset(new LinearFunc<int, double>(m_actionTurn, finalTurn, firstSpd, finalSpd));
}

void BulletMLRunnerImpl::calcAccelY(double horizontal, int term, BulletMLNode::Type type) {
    int finalTurn = m_actionTurn + term;

    double firstSpd = m_runner->getBulletSpeedY();
    double finalSpd;

    if (type == BulletMLNode::sequence) {
        finalSpd = firstSpd + horizontal * term;
    } else if (type == BulletMLNode::relative) {
        finalSpd = firstSpd + horizontal;
    } else {
        finalSpd = horizontal;
    }

    m_accelY.reset(new LinearFunc<int, double>(m_actionTurn, finalTurn, firstSpd, finalSpd));
}

void BulletMLRunnerImpl::runBullet() {
    setSpeed();
    setDirection();

    if (!m_speed.isValidate()) {
        m_prevSpeed = m_speed = m_runner->getDefaultSpeed();
    }
    if (!m_direction.isValidate()) {
        m_prevDirection = m_direction = m_runner->getAimDirection();
    }

    if (m_action->getChild(BulletMLNode::action) == 0 &&
        m_action->getChild(BulletMLNode::actionRef) == 0) {
        m_runner->createSimpleBullet(m_direction, m_speed);
    } else {
        vector<BulletMLNode *> acts;
        m_action->getAllChildrenVec(BulletMLNode::action, acts);
        m_action->getAllChildrenVec(BulletMLNode::actionRef, acts);

        /*
        act_->getAllChildren(BulletMLNode::action, back_inserter(acts));
        act_->getAllChildren(BulletMLNode::actionRef, back_inserter(acts));
        */

        BulletMLState *state = new BulletMLState(m_bulletml, acts, m_parameters);

        m_runner->createBullet(state, m_direction, m_speed);
    }

    m_action = 0;
}

void BulletMLRunnerImpl::runAction() {
    if (m_action->childSize() == 0) {
        m_action = 0;
    } else {
        m_action = *m_action->childBegin();
    }
}

void BulletMLRunnerImpl::runFire() {
    shotInit();

    setSpeed();
    setDirection();

    BulletMLNode *bullet = m_action->getChild(BulletMLNode::bullet);
    if (bullet == 0) {
        bullet = m_action->getChild(BulletMLNode::bulletRef);
    }
    BulletMLError::doAssert(bullet != 0, "<fire> must have contents bullet or bulletRef");

    m_action = bullet;
}

void BulletMLRunnerImpl::runWait() {
    int frame = static_cast<int>(getNumberContents(m_action));
    doWait(frame);

    m_action = 0;
}

void BulletMLRunnerImpl::runRepeat() {
    const BulletMLNode *times = m_action->getChild(BulletMLNode::times);
    if (times == 0) {
        return;
    }

    int timesNum = static_cast<int>(getNumberContents(times));

    BulletMLNode *action = m_action->getChild(BulletMLNode::action);
    if (action == 0) {
        action = m_action->getChild(BulletMLNode::actionRef);
    }
    BulletMLError::doAssert(action != 0, "repeat elem must have contents action or actionRef");

    m_repeatStack.push(new RepeatElem(0, timesNum, action));

    m_action = action;
}

void BulletMLRunnerImpl::runBulletRef() {
    shared_ptr<Parameters> prevParameter = m_parameters;
    m_parameters.reset(getParameters());

    m_refStack.push(make_pair(m_action, prevParameter));
    m_action = m_bulletml->getBulletRef(m_action->getRefID());
}

void BulletMLRunnerImpl::runActionRef() {
    shared_ptr<Parameters> prevParameter = m_parameters;
    m_parameters.reset(getParameters());

    m_refStack.push(make_pair(m_action, prevParameter));
    m_action = m_bulletml->getActionRef(m_action->getRefID());
}

void BulletMLRunnerImpl::runFireRef() {
    shared_ptr<Parameters> prevParameter = m_parameters;
    m_parameters.reset(getParameters());

    m_refStack.push(make_pair(m_action, prevParameter));
    m_action = m_bulletml->getFireRef(m_action->getRefID());
}

void BulletMLRunnerImpl::runChangeDirection() {
    int term = static_cast<int>(getNumberContents(m_action->getChild(BulletMLNode::term)));
    BulletMLNode *dirNode = m_action->getChild(BulletMLNode::direction);
    BulletMLNode::Type type = dirNode->getType();

    double dir;
    if (type != BulletMLNode::sequence) {
        dir = getDirection(dirNode, false);
    } else {
        dir = getNumberContents(dirNode);
    }

    calcChangeDirection(dir, term, type == BulletMLNode::sequence);

    m_action = 0;
}

void BulletMLRunnerImpl::runChangeSpeed() {
    int term = static_cast<int>(getNumberContents(m_action->getChild(BulletMLNode::term)));
    BulletMLNode *spdNode = m_action->getChild(BulletMLNode::speed);
    BulletMLNode::Type type = spdNode->getType();

    double spd;
    if (type != BulletMLNode::sequence) {
        spd = getSpeed(spdNode);
    } else {
        spd = getNumberContents(spdNode) * (double)term + m_runner->getBulletSpeed();
    }

    calcChangeSpeed(spd, term);

    m_action = 0;
}

void BulletMLRunnerImpl::runAccel() {
    int term = static_cast<int>(getNumberContents(m_action->getChild(BulletMLNode::term)));
    BulletMLNode *hnode = m_action->getChild(BulletMLNode::horizontal);
    BulletMLNode *vnode = m_action->getChild(BulletMLNode::vertical);

    if (m_bulletml->isHorizontal()) {
        if (vnode != 0) {
            calcAccelX(getNumberContents(vnode), term, vnode->getType());
        }
        if (hnode != 0) {
            calcAccelY(-getNumberContents(hnode), term, hnode->getType());
        }
    } else {
        if (hnode != 0) {
            calcAccelX(getNumberContents(hnode), term, hnode->getType());
        }
        if (vnode != 0) {
            calcAccelY(getNumberContents(vnode), term, vnode->getType());
        }
    }

    m_action = 0;
}

void BulletMLRunnerImpl::runVanish() {
    m_runner->doVanish();

    m_action = 0;
}

void BulletMLRunnerImpl::changes() {
    int now = m_runner->getTurn();

    if (m_changeDir.get() != 0) {
        if (m_changeDir->isLast(now)) {
            m_runner->doChangeDirection(m_changeDir->getLast());
            m_changeDir.reset(nullptr);
        } else {
            m_runner->doChangeDirection(m_changeDir->getValue(now));
        }
    }

    if (m_changeSpeed.get() != 0) {
        if (m_changeSpeed->isLast(now)) {
            m_runner->doChangeSpeed(m_changeSpeed->getLast());
            m_changeSpeed.reset(nullptr);
        } else {
            m_runner->doChangeSpeed(m_changeSpeed->getValue(now));
        }
    }

    if (m_accelX.get() != 0) {
        if (m_accelX->isLast(now)) {
            m_runner->doAccelX(m_accelX->getLast());
            m_accelX.reset(nullptr);
        } else {
            m_runner->doAccelX(m_accelX->getValue(now));
        }
    }

    if (m_accelY.get() != 0) {
        if (m_accelY->isLast(now)) {
            m_runner->doAccelY(m_accelY->getLast());
            m_accelY.reset(nullptr);
        } else {
            m_runner->doAccelY(m_accelY->getValue(now));
        }
    }
}

void BulletMLRunnerImpl::runSub() {
    // 見たくもないコードだね。
    // Code that you don't want to see.
    while (m_action != 0 && !isTurnEnd()) {
        BulletMLNode *prev = m_action;
        Method fp = m_commandMap[m_action->getName()];
        (this->*fp)();

        // ref から戻る
        // Return from ref
        if (m_action == 0 && prev->getParent() != 0 &&
            prev->getParent()->getName() == BulletMLNode::bulletml) {
            assert(!m_refStack.empty());
            prev = m_refStack.top().first;
            m_parameters = m_refStack.top().second;
            m_refStack.pop();
        }

        // 次の node を探す
        // Find the next node
        if (m_action == 0) {
            m_action = prev->next();
        }

        // 上に遡って次の node を探す
        // Go up and search for the next node
        while (m_action == 0) {
            if (prev->getParent() != 0 &&
                prev->getParent()->getName() == BulletMLNode::repeat) {
                RepeatElem *rep = m_repeatStack.top();
                rep->ite++;
                if (rep->ite < rep->end) {
                    m_action = rep->act;
                    break;
                } else {
                    delete rep;
                    m_repeatStack.pop();
                }
            }

            m_action = prev->getParent();
            if (m_action == 0) {
                break;
            }

            prev = m_action;

            if (prev->getParent() != 0 &&
                prev->getParent()->getName() == BulletMLNode::bulletml) {
                assert(!m_refStack.empty());
                prev = m_action = m_refStack.top().first;
                m_parameters = m_refStack.top().second;
                m_refStack.pop();
            }

            m_action = m_action->next();
        }
    }
}

bool BulletMLRunnerImpl::isTurnEnd() {
    return isEnd() || m_actionTurn > m_endTurn;
}

void BulletMLRunnerImpl::doWait(int frame) {
    if (frame <= 0) {
        return;
    }
    m_actionTurn += frame;
}

void BulletMLRunnerImpl::setDirection() {
    BulletMLNode *dir = m_action->getChild(BulletMLNode::direction);
    if (dir == 0) {
        return;
    }

    m_direction = getDirection(dir);
}

void BulletMLRunnerImpl::setSpeed() {
    BulletMLNode *spd = m_action->getChild(BulletMLNode::speed);
    if (spd == 0) {
        return;
    }

    m_speed = getSpeed(spd);
}

double BulletMLRunnerImpl::getNumberContents(const BulletMLNode *node) {
    assert(node);

    Variables::rank = m_runner->getRank();
    Variables::parameters = m_parameters.get();
    Variables::runner = m_runner;

    return node->getValue();
}

double BulletMLRunnerImpl::getSpeed(BulletMLNode *spdNode) {
    double spd;

    spd = getNumberContents(spdNode);
    if (spdNode->getType() != BulletMLNode::none) {
        BulletMLNode::Type type = spdNode->getType();

        if (type == BulletMLNode::relative) {
            spd += m_runner->getBulletSpeed();
        } else if (type == BulletMLNode::sequence) {
            if (!m_prevSpeed.isValidate()) {
                spd = 1;
            } else {
                spd += m_prevSpeed;
            }
        }
    }

    // デフォルトでは何もしない
    // By default it does nothing
    m_prevSpeed = spd;

    return spd;
}

double BulletMLRunnerImpl::getDirection(BulletMLNode *dirNode, bool prevChange) {
    double dir;

    bool isDefault = true;
    dir = getNumberContents(dirNode);

    if (dirNode->getType() != BulletMLNode::none) {
        BulletMLNode::Type type = dirNode->getType();
        isDefault = false;

        if (type == BulletMLNode::absolute) {
            if (m_bulletml->isHorizontal()) {
                dir -= 90;
            }
        } else if (type == BulletMLNode::relative) {
            dir += m_runner->getBulletDirection();
        } else if (type == BulletMLNode::sequence) {
            if (!m_prevDirection.isValidate()) {
                dir = 0;
                isDefault = true;
            } else {
                dir += m_prevDirection;
            }
        } else {
            isDefault = true;
        }
    }

    if (isDefault) {
        // 明らかに非効率
        // Obviously inefficient
        dir += m_runner->getAimDirection();
    }

    while (dir > 360) {
        dir -= 360;
    }
    while (dir < 0) {
        dir += 360;
    }

    if (prevChange) {
        m_prevDirection = dir;
    }

    return dir;
}

BulletMLRunnerImpl::Parameters *BulletMLRunnerImpl::getParameters() {
    Parameters *params = 0;
    bool first = true;

    BulletMLNode::ChildIterator it;
    for (it = m_action->childBegin(); it != m_action->childEnd(); it++) {
        BulletMLNode *node = *it;
        if (node->getName() != BulletMLNode::param) {
            continue;
        }

        if (first) {
            first = false;
            params = new Parameters;
            // 0番要素は使わない
            // Do not use the 0th element
            params->push_back(0);
        }

        params->push_back(getNumberContents(node));
    }

    return params;
}
