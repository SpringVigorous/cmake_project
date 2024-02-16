#pragma once
#ifndef __SERIALIZE_OBJ_H___
#define __SERIALIZE_OBJ_H___
#include "kernel_serialize.h"
#include "kernel/person.h"
using namespace KERNEL;
namespace cereal
{
    template <typename Archive>
    void serialize(Archive &ar, Person &person)
    {
        ar(person.name,
           person.age);
    }
} // namespace cereal

_KERNEL_SERIALIZE_BEGIN_

class KERNEL_SERIALIZE_API serialize_person
{
public:
    serialize_person();
};

_KERNEL_SERIALIZE_END_

#endif