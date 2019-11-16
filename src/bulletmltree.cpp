#include "bulletmlerror.h"
#include "bulletmltree.h"
#include "calc.h"

#include <algorithm>
#include <functional>
#include <iostream>

using namespace std;

string BulletMLNode::name2string[nameSize] = {
    "bullet",
    "action",
    "fire",
    "changeDirection",
    "changeSpeed",
    "accel",
    "wait",
    "repeat",
    "bulletRef",
    "actionRef",
    "fireRef",
    "vanish",
    "horizontal",
    "vertical",
    "term",
    "times",
    "direction",
    "speed",
    "param",
    "bulletml"
};

BulletMLNode::Type BulletMLNode::string2type(const string &str) {
    if (str == "aim") {
        return aim;
    } else if (str == "absolute") {
        return absolute;
    } else if (str == "relative") {
        return relative;
    } else if (str == "sequence") {
        return sequence;
    }

    BulletMLError::doAssert(string("BulletML parser: unknown type ") + str + ".");

    return typeSize; // never hit
}

BulletMLNode::Name BulletMLNode::string2name(const string &str) {
    if (str == "bulletml") {
        return bulletml;
    } else if (str == "bullet") {
        return bullet;
    } else if (str == "action") {
        return action;
    } else if (str == "fire") {
        return fire;
    } else if (str == "changeDirection") {
        return changeDirection;
    } else if (str == "changeSpeed") {
        return changeSpeed;
    } else if (str == "accel") {
        return accel;
    } else if (str == "vanish") {
        return vanish;
    } else if (str == "wait") {
        return wait;
    } else if (str == "repeat") {
        return repeat;
    } else if (str == "direction") {
        return direction;
    } else if (str == "speed") {
        return speed;
    } else if (str == "horizontal") {
        return horizontal;
    } else if (str == "vertical") {
        return vertical;
    } else if (str == "term") {
        return term;
    } else if (str == "bulletRef") {
        return bulletRef;
    } else if (str == "actionRef") {
        return actionRef;
    } else if (str == "fireRef") {
        return fireRef;
    } else if (str == "param") {
        return param;
    } else if (str == "times") {
        return times;
    }

    BulletMLError::doAssert(string("BulletML parser: unknown tag ") + str + ".");

    return nameSize; // never hit
}

BulletMLNode::BulletMLNode(const string &name) :
    m_name(string2name(name)),
    m_type(none) {
    setReleaseDuty(true);
}

BulletMLNode::~BulletMLNode() {
}

void BulletMLNode::setValue(const string &val) {
    m_val = calc(val);
}

void BulletMLNode::dump() {
#if 0
    cout << "<" << name2string[m_name];
    /*
    AttributeMap::const_iterator it;
    for (it = m_attributes.cbegin(); it != m_attributes.cend(); it++) {
	cout << " " << it->first << "=" << it->second;
    }
    */
    cout << ">" << endl;
    /*
    if (m_val != "") cout << val_ << endl;
    */
    for_each(childBegin(), childEnd(), mem_fun(&BulletMLNode::dump));

    cout << "</" << name2string[m_name] << ">" << endl;
#endif
}

BulletMLNode *BulletMLNode::getChild(Name name) {
    ChildIterator it;
    for (it = childBegin(); it != childEnd(); it++) {
        if ((*it)->getName() == name) {
            return *it;
        }
    }
    return nullptr;
}

bool BulletMLNode::findNode(Name name) const {
    if (getName() == name) {
        return true;
    }

    ConstChildIterator it;
    for (it = childBegin(); it != childEnd(); it++) {
        if ((*it)->findNode(name)) {
            return true;
        }
    }

    return false;
}

BulletMLNode *BulletMLNode::next() {
    BulletMLNode *parent = getParent();
    if (parent == nullptr) {
        return nullptr;
    }

    ChildIterator it = find(parent->childBegin(), parent->childEnd(), this);
    BulletMLError::doAssert(it != parent->childEnd(), m_name + ": not found");
    it++;
    if (it == parent->childEnd()) {
        return nullptr;
    } else {
        return *it;
    }
}

void BulletMLNode::getAllChildrenVec(Name name, vector<BulletMLNode*> &outvec) {
    ChildIterator it;
    for (it = childBegin(); it != childEnd(); it++) {
        if ((*it)->getName() == name) {
            outvec.push_back(*it);
        }
    }
}
