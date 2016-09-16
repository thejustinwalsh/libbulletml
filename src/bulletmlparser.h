/// BulletML のパーサ
/**
 * c++ 用 RELAX が無かったのでまあ自分で作ることに
 */

#ifndef BULLETMLPARSER_H_
#define BULLETMLPARSER_H_

#include "bulletmlcommon.h"
#include "bulletmltree.h"

#include <string>
#include <vector>

#include <stdio.h>

class BULLETML_API BulletMLParser
{
protected:
    typedef std::vector<std::string> MyAttributes;
    typedef MyAttributes::const_iterator MyAttributeIte;

public:
    BulletMLParser();
    virtual ~BulletMLParser();

public:
    void build();
    virtual void parse() = 0;

public:
    /**
     * BulletML は仕様上ツリー構造の根っこを取れる必要はなく
     * ラベルからこれらのみ取れれば良い
     */
    //@{
    BulletMLNode* getBulletRef(int id);
    BulletMLNode* getActionRef(int id);
    BulletMLNode* getFireRef(int id);
    //@}

    const std::vector<BulletMLNode*>& getTopActions() const { return topActions_; }

    void setHorizontal() { isHorizontal_ = true; }
    bool isHorizontal() const { return isHorizontal_; }

protected:
    BulletMLNode* addContent(const std::string& name);
    void addAttribute(const MyAttributes& attr, BulletMLNode* elem);

protected:
    /// これはgccのバージョン間の互換のためなのだが
    template <class Char_>
    std::string uc2string(Char_* src, size_t len = std::string::npos);

protected:
    BulletMLNode* bulletml_;

    std::vector<BulletMLNode*> topActions_;

    typedef std::vector<BulletMLNode*> MyMap;
    typedef MyMap BulletMap;
    typedef MyMap ActionMap;
    typedef MyMap FireMap;
    BulletMap bulletMap_;
    ActionMap actionMap_;
    FireMap fireMap_;

    bool isHorizontal_;

protected:
    /// 一時的な導入
    void setName(const std::string& name) { name_ = name; }
    std::string name_;

public:
    const std::string& getName() const { return name_; }
};

template <class Char_>
std::string BulletMLParser::uc2string(Char_* src, size_t len)
{
    std::string dst;
    size_t i = 0;
    while (i != len && *src != '\0') {
        dst += *src;
        src++;
        i++;
    }
    return dst;
}

#endif // ! BULLETMLPARSER_H_
