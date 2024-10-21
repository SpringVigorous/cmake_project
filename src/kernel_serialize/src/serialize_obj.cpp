#include "kernel_serialize/serialize_obj.h"
#include <iostream>
_KERNEL_SERIALIZE_BEGIN_
serialize_person::serialize_person()
{
using namespace std;
cout<<__FUNCTION__<<endl;
}

_KERNEL_SERIALIZE_END_