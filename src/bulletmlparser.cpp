#include "bulletmlerror.h"
#include "bulletmlparser.h"

#include <map>

using namespace std;

namespace {
    /// 内部のみで使用するクラス。
    /// Class to only use internally.
    class IDPool {
    public:
        static int getID(BulletMLNode::Name domain, const string &key) {
            KeyToID &kti = g_map[domain];
            KeyToID::iterator it = kti.find(key);
            if (it == kti.end()) {
                int id = g_maxMap[domain]++;
                g_map[domain][key] = id;
                return id;
            } else {
                return it->second;
            }
        }

        static void init() {
            g_map.insert(make_pair(BulletMLNode::bullet, KeyToID()));
            g_map.insert(make_pair(BulletMLNode::action, KeyToID()));
            g_map.insert(make_pair(BulletMLNode::fire, KeyToID()));
            g_maxMap.insert(make_pair(BulletMLNode::bullet, 0));
            g_maxMap.insert(make_pair(BulletMLNode::action, 0));
            g_maxMap.insert(make_pair(BulletMLNode::fire, 0));
        }

        static void quit() {
            g_map.clear();
            g_maxMap.clear();
        }

    private:
        typedef map<string, unsigned int> KeyToID;
        typedef map<BulletMLNode::Name, KeyToID> DomainToIDMap;
        typedef map<BulletMLNode::Name, int> DomainToMaxID;
        static DomainToIDMap g_map;
        static DomainToMaxID g_maxMap;
    };
}

IDPool::DomainToIDMap IDPool::g_map;
IDPool::DomainToMaxID IDPool::g_maxMap;

BulletMLParser::BulletMLParser() :
    m_bulletml(nullptr),
    m_isHorizontal(false) {
}

BulletMLParser::~BulletMLParser() {
    // BulletMLNode はルートノードだけ破壊すれば良い
    // BulletMLNode only needs to destroy the root node
    delete m_bulletml;
}

void BulletMLParser::build() {
    IDPool::init();
    parse();
    IDPool::quit();
}

BulletMLNode *BulletMLParser::getBulletRef(int id) {
    BulletMLError::doAssert((int)m_bulletMap.size() > id &&
        m_bulletMap[id] != nullptr, "bulletRef key doesn't exist.");
    return m_bulletMap[id];
}

BulletMLNode *BulletMLParser::getActionRef(int id) {
    BulletMLError::doAssert((int)m_actionMap.size() > id &&
        m_actionMap[id] != nullptr, "actionRef key doesn't exist.");
    return m_actionMap[id];
}

BulletMLNode *BulletMLParser::getFireRef(int id) {
    BulletMLError::doAssert((int)m_fireMap.size() > id &&
        m_fireMap[id] != nullptr, "fireRef key doesn't exist.");
    return m_fireMap[id];
}

BulletMLNode *BulletMLParser::addContent(const string &name) {
    // ルートノードは別処理
    // Root node is handled differently
    if (name == "bulletml") {
        m_bulletml = new BulletMLNode(name);
        return m_bulletml;
    }
    BulletMLError::doAssert(m_bulletml != nullptr, "<bulletml> doesn't exist.");

    return new BulletMLNode(name);
}

void BulletMLParser::addAttribute(const ParserAttributes &attr, BulletMLNode *elem) {
    if (!attr.empty()) {
        ParserAttributeIter it = attr.cbegin();
        while (it != attr.cend()) {
            const string key(*it);
            it++;
            const string val(*it);
            it++;

            if (key == "type") {
                elem->setType(val);
            }  else if (key == "label") {
                BulletMLNode::Name name = elem->getName();
                BulletMLNode::Name domain;
                if (name == BulletMLNode::bulletRef) {
                    domain = BulletMLNode::bullet;
                } else if (name == BulletMLNode::actionRef) {
                    domain = BulletMLNode::action;
                } else if (name == BulletMLNode::fireRef) {
                    domain = BulletMLNode::fire;
                } else {
                    domain = name;
                }

                int id = IDPool::getID(domain, val);
                if (name == BulletMLNode::bullet) {
                    if ((int)m_bulletMap.size() <= id) {
                        m_bulletMap.resize(id + 1, 0);
                    }
                    m_bulletMap[id] = elem;
                } else if (name == BulletMLNode::action) {
                    if ((int)m_actionMap.size() <= id) {
                        m_actionMap.resize(id + 1, 0);
                    }
                    m_actionMap[id] = elem;
                } else if (name == BulletMLNode::fire) {
                    if ((int)m_fireMap.size() <= id) {
                        m_fireMap.resize(id + 1, 0);
                    }
                    m_fireMap[id] = elem;
                } else if (name == BulletMLNode::bulletRef ||
                    name == BulletMLNode::actionRef ||
                    name == BulletMLNode::fireRef) {
                    elem->setRefID(id);
                } else {
                    BulletMLError::doAssert("this cannot have the attribute \"label\".");
                }

                if (elem->getName() == BulletMLNode::action &&
                    val.length() >= 3 &&
                    val.substr(0, 3) == "top") {
                    m_topActions.push_back(elem);
                }
            }
        }
    }
}
