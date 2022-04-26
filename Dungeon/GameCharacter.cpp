#include "GameCharacter.h"

GameCharacter::GameCharacter():Object() {}


GameCharacter::GameCharacter(string name, string d_tag, int maxHealth, int attack, int defense)
:Object(name, d_tag) //** tag is d_tag
{
    this->d_tag = d_tag;  //**set first maybe I need it to use~
    this->maxHealth = maxHealth;
    this->attack = attack;
    this->defense = defense;
    currentHealth = maxHealth;  //initialize currentHealth
}

bool GameCharacter::checkIsDead()  //monster and player both need to check
{
    if( this->currentHealth <= 0 )
        return true; //is dead
    else
        return false;
}

int GameCharacter::takeDamage( int d ) //take damage and return current health
{
    this->currentHealth -= d; // 操作放在這程式較好寫 (about access 私有成員
    return this->currentHealth;
}


void GameCharacter::setMaxHealth(int maxHealth) //名字不要打錯...
{
    this->maxHealth = maxHealth;
}
void GameCharacter::setCurrentHealth(int currentHealth)
{
    this->currentHealth = currentHealth;
}
void GameCharacter::setAttack(int attack)
{
    this->attack = attack;
}
void GameCharacter::setDefense(int defense)
{
    this->defense = defense;
}


int GameCharacter::getMaxHealth()
{
    return this->maxHealth;
}
int GameCharacter::getCurrentHealth()
{
    return this->currentHealth;
}
int GameCharacter::getAttack()
{
    return this->attack;
}
int GameCharacter::getDefense()
{
    return this->defense;
}
