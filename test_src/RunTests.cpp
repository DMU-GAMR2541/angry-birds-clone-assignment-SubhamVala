#include <gtest/gtest.h>
#include "Enemy.h"
#include "Slingshot.h"
#include "Pig.h"
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <iostream>
#include "DynamicObject.h"
#include "StaticObject.h"
#include "Bird.h"
#include "Plank.h""
#include "Non-Interactable.h"
#include "Catapult.h"
#include "ContactListener.h"
#include "UI.h"

/// <summary>
///Taken from the GoogleTest primer. 
/// </summary>

// The fixture for testing class For.
class EnemyTest : public testing::Test {
public:
    std::unique_ptr<Enemy> enemy;
protected:
    // You can remove any or all of the following functions if their bodies would
    // be empty.

    EnemyTest() {
        // You can do set-up work for each test here .
                    
    }

    ~EnemyTest() override {
        // You can do clean-up work that doesn't throw exceptions here.
    }

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    void SetUp() override {
        // Code here will be called immediately after the constructor (right
        // before each test).
        enemy = std::make_unique<Enemy>(50); // All enemys in this test suite start with 50 HP.
                    
    }

    void TearDown() override {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }


};

class SlingshotTest : public testing::Test {
public:
    std::unique_ptr<Slingshot> slingshot;
    

protected:

    SlingshotTest() {
        //constructor

    }

    ~SlingshotTest() override {
        //deconstructor

    }


    void SetUp() override {
        slingshot = std::make_unique<Slingshot>(100, "Red");
        
    }

    void TearDown() override {

    }
};

class PigTest : public testing::Test {
public:
    std::unique_ptr<Pig> pig;
    Pig pigSprite;

protected:
    PigTest() {
        //constructor
    }

    ~PigTest() override {
        //deconstructor
    }

    void SetUp() override {
        b2Vec2 b2_gravity(0.0f, 9.8f); // Earth-like gravity
        b2World world(b2_gravity);
        pig = std::make_unique<Pig>(world, 0, 0, 0, 50, "../assets/Ang_Birds/Pigs.png", DynamicObject::DynamicObjectType::pig);
        pigSprite.sp_sprites.setTextureRect(sf::IntRect(53, 70, 47, 44));
    }
   
    void TearDown() override {

    }
};


//Pig Tests.
TEST(Pig, First_Pig_Test) {
    b2Vec2 b2_gravity(0.0f, 9.8f); // Earth-like gravity
    b2World world(b2_gravity);
    Pig p(world, 0, 0, 0, 50, "../assets/Ang_Birds/Pigs.png", DynamicObject::DynamicObjectType::pig);
    EXPECT_EQ(p.getPigType(), DynamicObject::DynamicObjectType::pig);
}

TEST_F(PigTest, SpriteCheckPig1) {
    sf::IntRect Texture = sf::IntRect(53, 70, 47, 44);
    ASSERT_EQ(pigSprite.sp_sprites.getTextureRect(), Texture);
}

//Enemy Test.
//A single test, not a fixture. No setup is called.
TEST(Enemy, First_Enemy_test) {
    Enemy e(100);
    //EXPECT_GT(e.getHealth(), 100);
    EXPECT_GT(e.getHealth(), 100);
    /*SUCCEED() << "Test test passed";
    FAIL() << "Test didn't pass";*/
}

//Enemy Test.
//Fixture test, setup created for damage.
TEST_F(EnemyTest, LethalDamagePopsPig) {
    enemy->takeDamage(60);
    EXPECT_TRUE(enemy->checkIfPopped());
}

//Enemy Test.
//Second test, not a fixture. No setup is called,
TEST(Enemy, Second_Enemy_test) {
    Enemy d(0);
    ASSERT_NE(d.getHealth(), 0);
}


//Slingshot Test.
//First test, not fixture. Not setup is called.
TEST(Slingshot, First_Slingshot_Test) {
    Slingshot t(99, "");
    EXPECT_LT(t.getTension(), 100);
    
}
//Slingshot Test.
//Second slingshot test, check bird colour
TEST_F(SlingshotTest, BirdColour) {
    slingshot->loadBird("Red");
    std::string str = "Red";
    const char* c = str.c_str();
    EXPECT_EQ(slingshot->getBirdType(), c);
    
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}