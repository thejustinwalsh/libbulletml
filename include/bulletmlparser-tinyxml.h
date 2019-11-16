/// BulletML のパーサ・ツリー by tinyxml
/// BulletML Parser Tree by tinyxml
/**
 * tinyxmlによるBulletMLのパーサ
 * BulletML Parser by tinyxml
 */

#ifndef BULLETMLPARSER_TINYXML_H_
#define BULLETMLPARSER_TINYXML_H_

#include <string>

#include "bulletmlcommon.h"
#include "bulletmlparser.h"

class BulletMLNode;

class BULLETML_API BulletMLParserTinyXML : public BulletMLParser {
public:
    BulletMLParserTinyXML(const std::string &filename, const char *filedata = nullptr);
    virtual ~BulletMLParserTinyXML();

    virtual void parse();

protected:
    void parseImpl(class TiXmlDocument *doc);

protected:
    void getTree(class TiXmlNode *node);
    void translateNode(class TiXmlNode *node);

private:
    bool m_loadFromFile;
    std::string m_xmlFile;
    BulletMLNode *m_curNode;
};

#endif // ! BULLETMLPARSER_TINYXML_H_
