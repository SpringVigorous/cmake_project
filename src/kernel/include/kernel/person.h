#pragma once
#ifndef __PERSON_H___
#define __PERSON_H___
#include "kernel.h"
#include <string>
_KERNEL_BEGIN_
using namespace std;
class KERNEL_API Person
{
public:
public:
    Person(string _name = "", int _age = 0);

private:
    string name;
    int age;
};

_KERNEL_END_
#endif