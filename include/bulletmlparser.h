/// BulletML のパーサ
/// BulletML Parser
/**
 * c++ 用 RELAX が無かったのでまあ自分で作ることに
 * I did not have RELAX for C++ so I decided to make it myself
 */

#ifndef BULLETMLPARSER_H_
#define BULLETMLPARSER_H_

#include "bulletmlcommon.h"
#include "bulletmltree.h"

#include <string>
#include <vector>

#include <stdio.h>

class BULLETML_API BulletMLParser {
protected:
    typedef std::vector<std::string> ParserAttributes;
    typedef ParserAttributes::const_iterator ParserAttributeIter;

public:
    BulletMLParser();
    virtual ~BulletMLParser();

public:
    void build();
    virtual void parse() = 0;

public:
    /**
     * BulletML は仕様上ツリー構造の根っこを取れる必要はなく
     * BulletML does not need to take the root of the tree structure by specification
     * ラベルからこれらのみ取れれば良い
     * You only have these from the label
     */
    //@{
    BulletMLNode *getBulletRef(int id);
    BulletMLNode *getActionRef(int id);
    BulletMLNode *getFireRef(int id);
    //@}

    const std::vector<BulletMLNode *> &getTopActions() const { return m_topActions; }

    void setHorizontal() { m_isHorizontal = true; }
    bool isHorizontal() const { return m_isHorizontal; }

protected:
    BulletMLNode *addContent(const std::string &name);
    void addAttribute(const ParserAttributes &attr, BulletMLNode *elem);

protected:
    /// これはgccのバージョン間の互換のためなのだが
    /// This is for compatibility between versions of gcc
    template <class TChar>
    std::string uc2string(TChar *src, size_t len = std::string::npos);

protected:
    BulletMLNode *m_bulletml;

    std::vector<BulletMLNode *> m_topActions;

    typedef std::vector<BulletMLNode *> ParserMap;
    typedef ParserMap BulletMap;
    typedef ParserMap ActionMap;
    typedef ParserMap FireMap;
    BulletMap m_bulletMap;
    ActionMap m_actionMap;
    FireMap m_fireMap;

    bool m_isHorizontal;

protected:
    /// 一時的な導入
    /// Temporary introduction
    void setName(const std::string &name) { m_name = name; }
    std::string m_name;

public:
    const std::string &getName() const { return m_name; }
};

template <class TChar>
std::string BulletMLParser::uc2string(TChar *src, size_t len) {
    std::string dst;
    size_t i = 0;
    while (i != len &&
        *src != '\0') {
        dst += *src;
        src++;
        i++;
    }
    return dst;
}

#endif // ! BULLETMLPARSER_H_
