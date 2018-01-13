/// 一般的なツリー。再生産だね
/// General tree. It is a reproduction

#ifndef TREE_H_
#define TREE_H_

#include "bulletmlcommon.h"

#include <list>

/// ツリーのクラス
/// Tree Class
/**
 * ツリーってのはコンテナが存在しない集合体であると思う。
 * The tree is an aggregate that does not contain containers.
 * んで、ノードっていう属性を帯びたクラスの集合がコンテナであると。
 * A collection of classes with attributes like nodes is a container.
 * でインターフェイスは、
 * In its interface,
 * class YourNode : public TreeNode<YourNode>;
 * って具合い。
 * What is it like?
 * ポインタ管理を前提としている。
 * It assumes pointer management.
 * インスタンスの管理は普段はしないけど、
 * It does not usually manage instances,
 * setReleaseDuty を呼ばれたノードが破壊されると、
 * When the node called setReleaseDuty is destroyed,
 * それの息子以下の世代は全て破壊される。
 * All generations below that child will be destroyed.
 */
template <class TC>
class BULLETML_API TreeNode {
public:
    // これをテンプレート引数で差し換えうる設計にしたいのだが
    // I'd like to design this as a template argument
    typedef std::list<TC *> Children;
    typedef typename Children::iterator ChildIterator;
    typedef typename Children::const_iterator ConstChildIterator;

public:
    TreeNode() { m_releaseDuty = false; }
    virtual ~TreeNode();

    void addChild(TC *c) {
        c->setParent(dynamic_cast<TC *>(this));
        m_children.push_back(c);
    }

    void setReleaseDuty(bool bl) { m_releaseDuty = bl; }
    void setParent(TC* c) { m_parent = c; }

    ChildIterator childBegin() { return m_children.begin(); }
    ChildIterator childEnd() { return m_children.end(); }
    size_t childSize() { return m_children.size(); }
    ConstChildIterator childBegin() const { return m_children.begin(); }
    ConstChildIterator childEnd() const { return m_children.end(); }
    TC *getParent() { return m_parent; }

private:
    Children m_children;
    TC *m_parent;
    bool m_releaseDuty;
};

template <class TC>
TreeNode<TC>::~TreeNode() {
    if (m_releaseDuty) {
        ChildIterator it;
        for (it = m_children.begin(); it != m_children.end(); it++) {
            (*it)->setReleaseDuty(true);
            delete *it;
        }
    }
}

#endif // ! TREE_H_
