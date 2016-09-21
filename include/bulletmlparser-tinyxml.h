/// BulletML のパーサ・ツリー by tinyxml
/**
 * tinyxmlによるBulletMLのパーサ
 */

#ifndef BULLETMLPARSER_TINYXML_H_
#define BULLETMLPARSER_TINYXML_H_

#include <string>

#include "bulletmlcommon.h"
#include "bulletmlparser.h"

class BulletMLNode;

class BULLETML_API BulletMLParserTinyXML : public BulletMLParser
{
public:
    BulletMLParserTinyXML(const std::string& filename);
    virtual ~BulletMLParserTinyXML();

    virtual void parse();

protected:
    void parseImpl(class TiXmlDocument* doc);

protected:
    void getTree(class TiXmlNode* node);
    void translateNode(class TiXmlNode* node);

private:
    std::string xmlFile_;
    BulletMLNode* curNode_;
};

#endif // ! BULLETMLPARSER_TINYXML_H_
