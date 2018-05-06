#include "bulletmlerror.h"
#include "bulletmlparser-tinyxml.h"
#include "bulletmlparser.h"
#include "bulletmltree.h"

#include "tinyxml/tinyxml.h"

#include <string>

using namespace std;

BulletMLParserTinyXML::BulletMLParserTinyXML(const string &filename, const char *filedata) :
    m_loadFromFile(true),
    m_curNode(nullptr) {
    setName(filename);
    
    if (filedata) {
        m_loadFromFile = false;
        m_xmlFile = filedata;
    }
}

BulletMLParserTinyXML::~BulletMLParserTinyXML() {
}

void BulletMLParserTinyXML::parse() {
    TiXmlDocument doc(getName().c_str());

    if (m_loadFromFile) {
        doc.LoadFile();
    } else {
        doc.Parse(m_xmlFile.c_str());
    }

    parseImpl(&doc);
}

void BulletMLParserTinyXML::parseImpl(TiXmlDocument *doc) {
    if (doc->Error()) {
        throw BulletMLError(doc->Value() + ": " + doc->ErrorDesc());
    }

    TiXmlNode *node;
    for (node = doc->FirstChild(); node; node = node->NextSibling()) {
        if (node->ToElement() != nullptr) {
            getTree(node);
            break;
        }
    }
}

void BulletMLParserTinyXML::getTree(TiXmlNode *node) {
    if (node->ToComment() != nullptr) {
        return;
    }
    translateNode(node);

    TiXmlNode *child;
    for (child = node->FirstChild(); child; child = child->NextSibling()) {
        TiXmlText *text;
        if ((text = child->ToText()) != nullptr) {
            m_curNode->setValue(text->Value());
            break;
        }

        getTree(child);
    }

    m_curNode = m_curNode->getParent();
}

void BulletMLParserTinyXML::translateNode(TiXmlNode *node) {
    TiXmlElement *elem = node->ToElement();
    assert(elem != nullptr);

    BulletMLNode *xmlNode = addContent(elem->Value());

    if (xmlNode->getName() == BulletMLNode::bulletml) {
        TiXmlAttribute *attr;
        for (attr = elem->FirstAttribute(); attr; attr = attr->Next()) {
            if (attr->Value() == "horizontal") {
                setHorizontal();
            }
        }
    } else {
        ParserAttributes mattr;
        TiXmlAttribute *attr;
        for (attr = elem->FirstAttribute(); attr; attr = attr->Next()) {
            mattr.push_back(attr->Name());
            mattr.push_back(attr->Value());
        }
        addAttribute(mattr, xmlNode);

        if (m_curNode != nullptr) {
            m_curNode->addChild(xmlNode);
        }
    }

    m_curNode = xmlNode;
}
