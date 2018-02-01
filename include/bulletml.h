#ifndef BULLETML_H
#define BULLETML_H

/*
extern "C" {
typedef int BulletMLParserTinyXML;
int* BulletMLParserTinyXML_new(char*);
void BulletMLParserTinyXML_parse(int* );
void BulletMLParserTinyXML_delete(int*);
typedef int BulletMLParser;
typedef int BulletMLState;
typedef int BulletMLRunner;
typedef int BulletMLRunnerD;
int* BulletMLRunner_new_parser(BulletMLParser*);
int* BulletMLRunner_new_state(BulletMLState*);
void BulletMLRunner_delete(int*);
void BulletMLRunner_run(int* );
bool BulletMLRunner_isEnd(int* );
void BulletMLRunner_delete(BulletMLRunner*);
void BulletMLRunner_run(BulletMLRunner* );
bool BulletMLRunner_isEnd(BulletMLRunner* );
void BulletMLRunner_set_getBulletDirection(int*, double (*fp) (int* ));
void BulletMLRunner_set_getAimDirection(int*, double (*fp) (int* ));
void BulletMLRunner_set_getBulletSpeed(int*, double (*fp) (int* ));
void BulletMLRunner_set_getDefaultSpeed(int*, double (*fp) (int* ));
void BulletMLRunner_set_getRank(int*, double (*fp) (int* ));
void BulletMLRunner_set_createSimpleBullet(int*, void (*fp) (int* , double, double));
void BulletMLRunner_set_createBullet(int*, void (*fp) (int* , BulletMLState*, double, double));
void BulletMLRunner_set_getTurn(int*, int (*fp) (int* ));
void BulletMLRunner_set_doVanish(int*, void (*fp) (int* ));
void BulletMLRunner_set_doChangeDirection(int*, void (*fp) (int* , double));
void BulletMLRunner_set_doChangeSpeed(int*, void (*fp) (int* , double));
void BulletMLRunner_set_doAccelX(int*, void (*fp) (int* , double));
void BulletMLRunner_set_doAccelY(int*, void (*fp) (int* , double));
void BulletMLRunner_set_getBulletSpeedX(int*, double (*fp) (int* ));
void BulletMLRunner_set_getBulletSpeedY(int*, double (*fp) (int* ));
void BulletMLRunner_set_getRand(int*, double (*fp) (int* ));
}
*/

class BulletMLParserTinyXML;
class BulletMLParser;
class BulletMLState;
class BulletMLRunner;

extern "C" {
    //  typedef int BulletMLParserTinyXML;
    BulletMLParserTinyXML* BulletMLParserTinyXML_new(char*);
    void BulletMLParserTinyXML_parse(BulletMLParserTinyXML*);
    void BulletMLParserTinyXML_delete(BulletMLParserTinyXML*);
    //  typedef int BulletMLParser;
    //  typedef int BulletMLState;
    //  typedef int BulletMLRunner;
    //  typedef int BulletMLRunnerD;
    //  BulletMLParser* BulletMLRunner_new_parser(BulletMLParser*);
    BulletMLRunner* BulletMLRunner_new_parser(BulletMLParser*);
    BulletMLRunner* BulletMLRunner_new_state(BulletMLState*);
    void BulletMLRunner_delete(BulletMLRunner*);
    void BulletMLRunner_run(BulletMLRunner*);
    bool BulletMLRunner_isEnd(BulletMLRunner*);
    void BulletMLRunner_delete(BulletMLRunner*);
    void BulletMLRunner_run(BulletMLRunner*);
    bool BulletMLRunner_isEnd(BulletMLRunner*);
    void BulletMLRunner_set_getBulletDirection(BulletMLRunner*, double(*fp) (BulletMLRunner*));
    void BulletMLRunner_set_getAimDirection(BulletMLRunner*, double(*fp) (BulletMLRunner*));
    void BulletMLRunner_set_getBulletSpeed(BulletMLRunner*, double(*fp) (BulletMLRunner*));
    void BulletMLRunner_set_getDefaultSpeed(BulletMLRunner*, double(*fp) (BulletMLRunner*));
    void BulletMLRunner_set_getRank(BulletMLRunner*, double(*fp) (BulletMLRunner*));
    void BulletMLRunner_set_createSimpleBullet(BulletMLRunner*, void(*fp) (BulletMLRunner*, double, double));
    void BulletMLRunner_set_createBullet(BulletMLRunner*, void(*fp) (BulletMLRunner*, BulletMLState*, double, double));
    void BulletMLRunner_set_getTurn(BulletMLRunner*, int(*fp) (BulletMLRunner*));
    void BulletMLRunner_set_doVanish(BulletMLRunner*, void(*fp) (BulletMLRunner*));
    void BulletMLRunner_set_doChangeDirection(BulletMLRunner*, void(*fp) (BulletMLRunner*, double));
    void BulletMLRunner_set_doChangeSpeed(BulletMLRunner*, void(*fp) (BulletMLRunner*, double));
    void BulletMLRunner_set_doAccelX(BulletMLRunner*, void(*fp) (BulletMLRunner*, double));
    void BulletMLRunner_set_doAccelY(BulletMLRunner*, void(*fp) (BulletMLRunner*, double));
    void BulletMLRunner_set_getBulletSpeedX(BulletMLRunner*, double(*fp) (BulletMLRunner*));
    void BulletMLRunner_set_getBulletSpeedY(BulletMLRunner*, double(*fp) (BulletMLRunner*));
    void BulletMLRunner_set_getRand(BulletMLRunner*, double(*fp) (BulletMLRunner*));
}

#endif