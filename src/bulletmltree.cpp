#include "bulletmlerror.h"
#include "bulletmltree.h"
#include "calc.h"

#include <algorithm>
#include <functional>
#include <iostream>

std::string BulletMLNode::name2string[nameSize] = {
    "bullet", "action",    "fire",      "changeDirection", "changeSpeed", "accel",      "wait",
    "repeat", "bulletRef", "actionRef", "fireRef",         "vanish",      "horizontal", "vertical",
    "term",   "times",     "direction", "speed",           "param",       "bulletml"};

BulletMLNode::Type BulletMLNode::string2type(const std::string& str)
{
    if (str == "aim") return aim;
    if (str == "absolute") return absolute;
    if (str == "relative") return relative;
    if (str == "sequence") return sequence;

    BulletMLError::doAssert(std::string("BulletML parser: unknown type ") + str + ".");
    return typeSize; // not reach
}

BulletMLNode::Name BulletMLNode::string2name(const std::string& str)
{
    if (str == "bulletml") return bulletml;
    if (str == "bullet") return bullet;
    if (str == "action") return action;
    if (str == "fire") return fire;
    if (str == "changeDirection") return changeDirection;
    if (str == "changeSpeed") return changeSpeed;
    if (str == "accel") return accel;
    if (str == "vanish") return vanish;
    if (str == "wait") return wait;
    if (str == "repeat") return repeat;
    if (str == "direction") return direction;
    if (str == "speed") return speed;
    if (str == "horizontal") return horizontal;
    if (str == "vertical") return vertical;
    if (str == "term") return term;
    if (str == "bulletRef") return bulletRef;
    if (str == "actionRef") return actionRef;
    if (str == "fireRef") return fireRef;
    if (str == "param") return param;
    if (str == "times") return times;

    BulletMLError::doAssert(std::string("BulletML parser: unknown tag ") + str + ".");
    return nameSize; // not reach
}

BulletMLNode::BulletMLNode(const std::string& name) : name_(string2name(name)), type_(none)
{
    setReleaseDuty(true);
}

BulletMLNode::~BulletMLNode() {}

void BulletMLNode::setValue(const std::string& val) { val_ = calc(val); }

void BulletMLNode::dump()
{
#if 0
    std::cout << "<" << name2string[name_];
/*
    AttributeMap::const_iterator ite;
    for (ite = attributes_.begin(); ite != attributes_.end(); ite++) {
	std::cout << " " << ite->first << "=" << ite->second;
    }
*/
    std::cout << ">" << std::endl;
/*
    if (val_ != "") std::cout << val_ << std::endl;
*/
    std::for_each(childBegin(), childEnd(), std::mem_fun(&BulletMLNode::dump));

    std::cout << "</" << name2string[name_] << ">" << std::endl;
#endif
}

BulletMLNode* BulletMLNode::getChild(Name name)
{
    ChildIterator ite;
    for (ite = childBegin(); ite != childEnd(); ite++) {
        if ((*ite)->getName() == name) return *ite;
    }
    return 0;
}

bool BulletMLNode::findNode(Name name) const
{
    if (getName() == name) return true;
    ConstChildIterator ite;
    for (ite = childBegin(); ite != childEnd(); ite++) {
        if ((*ite)->findNode(name)) return true;
    }
    return false;
}

BulletMLNode* BulletMLNode::next()
{
    BulletMLNode* parent = getParent();
    if (parent == 0) return 0;
    ChildIterator ite = std::find(parent->childBegin(), parent->childEnd(), this);
    BulletMLError::doAssert(ite != parent->childEnd(), name_ + ": not found");
    ite++;
    if (ite == parent->childEnd())
        return 0;
    else
        return *ite;
}

void BulletMLNode::getAllChildrenVec(Name name, std::vector<BulletMLNode*>& outvec)
{
    ChildIterator ite;
    for (ite = childBegin(); ite != childEnd(); ite++) {
        if ((*ite)->getName() == name) outvec.push_back(*ite);
    }
}
