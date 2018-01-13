#include "bulletmlerror.h"
#include "bulletmlparser.h"
#include "bulletmlrunner.h"
#include "bulletmlrunnerimpl.h"
#include "formula-variables.h"

using namespace std;

BulletMLRunner::BulletMLRunner(BulletMLParser *bulletml) {
    const vector<BulletMLNode *> &actions = bulletml->getTopActions();
    for (size_t i = 0; i < actions.size(); i++) {
        vector<BulletMLNode *> action;
        action.push_back(actions[i]);
        BulletMLState *state = new BulletMLState(bulletml, action, shared_ptr<BulletMLParameter>());
        m_impl.push_back(makeImpl(state));
    }
}

BulletMLRunner::BulletMLRunner(BulletMLState *state) {
	m_impl.push_back(makeImpl(state));
}

BulletMLRunner::~BulletMLRunner() {
    for (size_t i = 0; i < m_impl.size(); i++) {
        delete m_impl[i];
    }
}

void BulletMLRunner::run() {
    /*
    for_each(_impl.begin(), _impl.end(), mem_fun(&BulletMLRunnerImpl::run));
    */
    for (vector<BulletMLRunnerImpl *>::const_iterator it = m_impl.begin(); it != m_impl.end(); ++it) {
        (*it)->run();
    }
}

bool BulletMLRunner::isEnd() const {
    /*
    return find_if(_impl.begin(), _impl.end(), not1(mem_fun(&BulletMLRunnerImpl::isEnd))) == _impl.end();
    */
    for (vector<BulletMLRunnerImpl *>::const_iterator it = m_impl.begin(); it != m_impl.end(); ++it) {
		if ((*it)->isEnd()) {
			return true;
		}
    }
    return false;
}

BulletMLRunnerImpl *BulletMLRunner::makeImpl(BulletMLState *state) {
    return new BulletMLRunnerImpl(state, this);
}
