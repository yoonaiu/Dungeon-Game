#include "Object.h"  //**.cpp �u�ninclude �ۤv�����Y�ɴN�n


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
    return this->name;  //**���gthis �|�X���� : ���ӬO���|
}
string Object::getTag()
{
    return this->tag;
}
