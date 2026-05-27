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
    std::unique_ptr<Bird> blueBird;
    std::unique_ptr<b2World> world;

protected:
    birdTest() {

    }

    ~birdTest() override {

    }

    void SetUp() override {
        b2Vec2 b2_gravity(0.0f, 9.8f);
        world = std::make_unique<b2World>(b2_gravity);
        blueBird = std::make_unique<Bird>(*world, 100.0f, 500.0f, 15.0f, 5.0f, "../assets/Ang_Birds/BlueBird.png", DynamicObject::DynamicObjectType::bluebird);


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
    // windows X value
    ASSERT_LT(xPos, 800.0f);
    // windows Y value
    ASSERT_LT(yPos, 600.0f);

}

// Bird Tests
//Fixture test, setup created for bird initial position.
TEST_F(birdTest, First_Bird_Test) {

    Catapult catapult(*world, 150.0f, 520.0f, 10.0f, 60.0f, "../assets/Ang_Birds/Slingshot.png");
    blueBird->launch(catapult.getShotPos());

    world->Step(1.0f / 60.0f, 8, 3);
    
    // Birds spawn x position.
    ASSERT_GT(blueBird->getBody()->GetLinearVelocity().x, 0);
    // Ground y position.
    ASSERT_LT(blueBird->getBody()->GetLinearVelocity().y, 0);

}

TEST_F(birdTest, PositionInRelationTo3Others) {
    Pig pig(*world, 522.0f, 590.0f , 15.0f, 50, "../assets/Ang_Birds/Pigs.png", DynamicObject::DynamicObjectType::pig);
    int PigxPos = pig.getBody()->GetPosition().x * 30.0f;

    Catapult catapult(*world, 150.0f, 520.0f, 10.0f, 60.0f, "../assets/Ang_Birds/Slingshot.png");
    int catapultxPos = catapult.getBody()->GetPosition().x * 30.0f;

    Plank plank(*world, 500.0f, 530.0f, 10.0f, 60.0f, "../assets/Ang_Birds/Plank.png", 1, DynamicObject::DynamicObjectType::VerticalPlank);
    int plankxPos = plank.getBody()->GetPosition().x * 30.0f;

    int xPos = blueBird->getBody()->GetPosition().x * 30.0f;

    EXPECT_LT(xPos, PigxPos);
    EXPECT_LT(xPos, catapultxPos);
    EXPECT_LT(xPos, plankxPos);
}

// Test to check if sprites and textures can be loaded.
TEST(Bird, SpriteLoads) {
    sf::Texture texture;
    sf::String sprite = "../assets/Ang_Birds/BlueBird.png";
    bool isSpriteLoaded = texture.loadFromFile(sprite);
    ASSERT_TRUE(isSpriteLoaded);

}

TEST_F(birdTest, birdtype) {
    EXPECT_EQ(blueBird->getBirdType(), DynamicObject::DynamicObjectType::bluebird);
}

TEST(Bird, BirdAbilityUsed) {
    Bird bird;
    EXPECT_FALSE(bird.hasUsedAbility());
}

//Pig Tests.
//Checks to see if the pig is the correct pigType.
TEST_F(PigTest, First_Pig_Test) {
    EXPECT_EQ(pig->getPigType(), DynamicObject::DynamicObjectType::pig);

}

// Checks the correctness of the sequence of destructor calls.
TEST_F(PigTest, SequenceOfDestructorCalls) {
    pig->takeDamage(100);
    ASSERT_TRUE(pig->checkIfPopped());
    // Deconstructor order sequence in console. Pig -> DynamicObject -> GameObject.

}

// checks if pig is marked for deletion on game start
// Fatal test, since if is marked for deletion bird cannot damage on start.
TEST(Pig, IsMarkedForDeletion) {
    Pig pig;
    ASSERT_FALSE(pig.isMarkedForDeletion());
}

//Checks to see if the correct sprite is taken from the spritesheet.
TEST_F(PigTest, CheckSpriteSheetSprite) {
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