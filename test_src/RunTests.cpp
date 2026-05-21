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
#include "Plank.h"
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
    std::unique_ptr<b2World> world;

protected:
    PigTest() {
        //constructor
    }

    ~PigTest() override {
        //deconstructor
    }

    void SetUp() override {
        b2Vec2 b2_gravity(0.0f, 9.8f);
        world = std::make_unique<b2World>(b2_gravity);
        pig = std::make_unique<Pig>(*world, 0, 0, 0, 50, "../assets/Ang_Birds/Pigs.png", DynamicObject::DynamicObjectType::pig);
        pigSprite.sp_sprites.setTextureRect(sf::IntRect(53, 70, 47, 44));
    }
   
    void TearDown() override {

    }
};

class birdTest : public testing::Test {
public:
    std::unique_ptr<Bird> bird;
    std::unique_ptr<b2World> world;

protected:
    birdTest() {

    }

    ~birdTest() override {

    }

    void SetUp() override {
        world = std::make_unique<b2World>(b2Vec2(0.0f, 9.8f));
        bird = std::make_unique<Bird>(*world, 0, 0, 0, 15, "../assets/Ang_Birds/BlueBird.png", DynamicObject::DynamicObjectType::bluebird);


    }

    void TearDown() override {

    }
};

class groundTest : public testing::Test {
public:
    std::unique_ptr<NonInteractable> ground;
    std::unique_ptr<b2World> world;

protected:
    groundTest() {

    }
    ~groundTest() override{

    }

    void SetUp() override {
        b2Vec2 b2_gravity(0.0f, 9.8f);
        world = std::make_unique<b2World>(b2_gravity);
        ground = std::make_unique<NonInteractable>(*world, 400.0f, 590.0f, 400.0f, 10.0f, sf::Color(34, 139, 34));
    }

    void TearDown() override {

    }
};


// Plank Tests.
TEST_F(groundTest, First_Ground_Test) {
    // need positions in sfml / pixels.
    int xPos = ground->getGroundBody()->GetPosition().x * 30.0f;
    int yPos = ground->getGroundBody()->GetPosition().y * 30.0f;
    ASSERT_EQ(xPos, 400.0f);
    ASSERT_EQ(yPos, 590.0f);

}


//Pig Tests.
TEST_F(PigTest, First_Pig_Test) {
    EXPECT_EQ(pig->getPigType(), DynamicObject::DynamicObjectType::pig);
}

TEST_F(PigTest, SpriteCheckPig1) {
    sf::IntRect Texture = sf::IntRect(53, 70, 47, 44);
    ASSERT_EQ(pigSprite.sp_sprites.getTextureRect(), Texture);
}

//Enemy Test.
//A single test, not a fixture. No setup is called.
TEST(Enemy, First_Enemy_test) {
    Enemy e(9);
    EXPECT_GT(e.getHealth(), 0);
}

//Enemy Test.
//Fixture test, setup created for damage.
TEST_F(PigTest, LethalDamagePopsPig) {
    pig->takeDamage(60);
    EXPECT_TRUE(pig->checkIfPopped());
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