/// BulletMLツリー。
/// BulletML Tree.
/**
 * BulletML に特化していて非常にいんちきくさいのが特徴。
 * Specialized in BulletML, characterized by being extremely cheap.
 */

#ifndef BULLETMLTREE_H_
#define BULLETMLTREE_H_

#include <algorithm>
#include <memory>
#include <string>

#include <vector>

#include "bulletmlcommon.h"
#include "formula.h"
#include "tree.h"

class BULLETML_API BulletMLNode : public TreeNode<BulletMLNode> {
public:
    typedef Formula<double> Number;

    typedef enum {
        none,
        aim,
        absolute,
        relative,
        sequence,
        typeSize
    } Type;

    typedef enum {
        bullet,
        action,
        fire,
        changeDirection,
        changeSpeed,
        accel,
        wait,
        repeat,
        bulletRef,
        actionRef,
        fireRef,
        vanish,
        horizontal,
        vertical,
        term,
        times,
        direction,
        speed,
        param,
        bulletml,
        nameSize
    } Name;

private:
    static Type string2type(const std::string &str);
    static Name string2name(const std::string &str);
    static std::string name2string[nameSize];

public:
    typedef TreeNode<BulletMLNode>::Children Children;
    typedef TreeNode<BulletMLNode>::ChildIterator ChildIterator;

public:
    explicit BulletMLNode(const std::string &name);
    virtual ~BulletMLNode();

    Name getName() const { return m_name; }

    void setValue(const std::string &val);
    double getValue() const { return m_val->value(); }

    void setType(const std::string &type) { m_type = string2type(type); }
    Type getType() const { return m_type; }

    void setRefID(int id) { m_refID = id; }
    int getRefID() const { return m_refID; }

    BulletMLNode *getChild(Name name);
    
    /*
    template <class TOutIter>
    void getAllChildren(Name name, TOutIter outIter);
    */
    void getAllChildrenVec(Name name, std::vector<BulletMLNode *> &outvec);

    /// 子孫の中に指定した名前に一致するものがあるかどうか
    /// Whether there is any match in the descendants with the specified name
    bool findNode(Name name) const;

    BulletMLNode* next();

    virtual void dump();

protected:
    Name m_name;
    Type m_type;
    int m_refID;
    std::unique_ptr<Number> m_val;
};

/*
template <class TOutIter>
void BulletMLNode::getAllChildren(Name name, TOutIter outIter) {
    ChildIterator it;
    for (it = childBegin(); it != childEnd(); it++) {
        if ((*it)->getName() == name) *outIter = *it;
        outIte++;
    }
}
*/

#endif // ! BULLETMLTREE_H_
