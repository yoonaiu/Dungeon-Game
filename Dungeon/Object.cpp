#include "Object.h"  //**.cpp 只要include 自己的標頭檔就好


Object::Object() {}

Object::Object(string name, string tag)
{
    this->name = name;
    this->tag = tag;
}


void Object::setName(string name)
{
    this->name = name;
}
void Object::setTag(string tag)
{
    this->tag = tag;
}


string Object::getName()
{
    return this->name;  //**不寫this 會出錯嗎 : 應該是不會
}
string Object::getTag()
{
    return this->tag;
}
