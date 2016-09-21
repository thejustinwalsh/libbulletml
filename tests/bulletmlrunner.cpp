#include "bulletmlparser.h"
#include "bulletmlparser-tinyxml.h"
#include "bulletmlrunner.h"
#include "bulletmlerror.h"

#include "tinyxml/tinyxml.h"

#include "gtest/gtest.h"

namespace
{
    std::list<BulletMLRunner*> bullets;
    int terms = 0;
    const int MAX_TERMS = 12000;
    
    class BulletMLRunnerTestParser : public BulletMLParserTinyXML
    {
    public:
        BulletMLRunnerTestParser() : BulletMLParserTinyXML("") {}
        
        virtual void parse() override
        {
            TiXmlDocument doc("TestPattern");
            
            doc.Parse(R"(<?xml version="1.0"?>
                      <!DOCTYPE bulletml SYSTEM "bulletmlx.dtd">
                      <bulletml type="vertical">
                        <action label="top">
                          <fire>
                            <direction type="absolute">180</direction>
                            <bulletRef label="basic"/>
                          </fire>
                        </action>
                        <bullet label="basic">
                          <speed>1</speed>
                        </bullet>
                      </bulletml>)");
            
            parseImpl(&doc);
        }
    };
    
    class BulletMLRunnerTest : public ::testing::Test
    {
    protected:
        BulletMLRunnerTest() {}
        virtual ~BulletMLRunnerTest() {}
    };
    
    TEST_F(BulletMLRunnerTest, Parse)
    {
        const std::string NO_ERROR("No Error");
        
        BulletMLParser* parser = new BulletMLRunnerTestParser();
        std::string errorText = NO_ERROR;
        
        try
        {
            parser->build();
        }
        catch (BulletMLError error)
        {
            errorText = error.what();
        }
        
        EXPECT_EQ(NO_ERROR, errorText);
        delete parser;
    }
    
    TEST_F(BulletMLRunnerTest, Run)
    {
        class TestRunner : public BulletMLRunner
        {
        public:
            TestRunner(BulletMLParser* parser, int bullet, double direction, double speed)
                : BulletMLRunner(parser), bullet(bullet), direction(direction), speed(speed) {}
            
            TestRunner(BulletMLState* state, int bullet, double direction, double speed)
                : BulletMLRunner(state), bullet(bullet), direction(direction), speed(speed) {}
            
            virtual double getBulletDirection() override
            {
                return direction;
            }
            
            virtual double getAimDirection() override
            {
                return 0.0;
            }
            
            virtual double getBulletSpeed() override
            {
                return speed;
            }
            
            virtual double getDefaultSpeed() override
            {
                return 1.0;
            }
            
            virtual double getRank() override
            {
                return 0.0;
            }
            
            
            virtual void createSimpleBullet(double direction, double speed) override
            {
                // Simple Shot is a fire and forget bullet with no more scripting logic
                EXPECT_FLOAT_EQ(direction, 180.0);
                EXPECT_FLOAT_EQ(speed, 1.0);
            }
            
            virtual void createBullet(BulletMLState* state, double direction, double speed) override
            {
                auto runner = new TestRunner(state, (int)getRand(), direction, speed);
                bullets.push_back(runner);
            }
            
            virtual int getTurn() override
            {
                return terms;
            }
            
            
            virtual void doVanish() override
            {
                auto bullet = std::find(bullets.begin(), bullets.end(), this);
                if (bullets.end() != bullet)
                {
                    auto bulletPtr = *bullet;
                    bullets.erase(bullet);
                    delete bulletPtr;
                }
            }
            
        public:
            int bullet;
            double direction;
            double speed;
        };
        
        BulletMLParser* parser = new BulletMLRunnerTestParser();
        parser->build();
        
        BulletMLRunner* runner = new TestRunner(parser, 0, 0.0, 1.0);
        while (terms++ < MAX_TERMS)
        {
            runner->run();
        }
        
        for (auto bullet : bullets) { delete bullet; }
        bullets.clear();
        
        delete runner;
        delete parser;
    }
}
