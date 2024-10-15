#pragma once
#ifndef __RUNTIME_H___
#define __RUNTIME_H___
#include "dynamic_runtime/macro.h"
_DYNAMIC_RUNTIME_BEGIN_

#define LPCSTR const char*
#define LPCWSTR const wchar_t*
#define UINT unsigned int
#define BOOL int
class DObject;
class DRuntimeClass;



// generate static object constructor for class registration
void DYNAMIC_RUNTIME_API DClassInit(DRuntimeClass* pNewClass);
struct D_CLASSINIT
{
    D_CLASSINIT(DRuntimeClass* pNewClass) { DClassInit(pNewClass); }
};

struct DRuntimeClass
{
// Attributes
    LPCSTR m_lpszClassName;
    int m_nObjectSize;
    UINT m_wSchema; // schema number of the loaded class
    DObject* (* m_pfnCreateObject)(); // NULL => abstract class

    DRuntimeClass* (* m_pfnGetBaseClass)();


// Operations
    DObject* CreateObject();
    BOOL IsDerivedFrom(const DRuntimeClass* pBaseClass) const;

    // dynamic name lookup and creation
    static DRuntimeClass*  FromName(LPCSTR lpszClassName);
    static DRuntimeClass*  FromName(LPCWSTR lpszClassName);
    static DObject*  CreateObject(LPCSTR lpszClassName);
    static DObject*  CreateObject(LPCWSTR lpszClassName);



    // DRuntimeClass objects linked together in simple list
    DRuntimeClass* m_pNextClass;       // linked list of registered classes
    const D_CLASSINIT* m_pClassInit;
};



// class DObject is the root of all compliant objects

class DYNAMIC_RUNTIME_API DObject
{
public:

// Object model (types, destruction, allocation)
    virtual DRuntimeClass* GetRuntimeClass() const;
    virtual ~DObject() = 0;  // virtual destructors are necessary

    // Diagnostic allocations
    void*  operator new(size_t nSize);
    void*  operator new(size_t, void* p);
    void  operator delete(void* p);
    void  operator delete(void* p, void* pPlace);



    // Disable the copy constructor and assignment by default so you will get
    //   compiler errors instead of unexpected behavior if you pass objects
    //   by value or assign objects.
protected:
    DObject();
private:
    DObject(const DObject& objectSrc);              // no implementation
    void operator=(const DObject& objectSrc);       // no implementation

// Attributes
public:
    BOOL IsSerializable() const;
    BOOL IsKindOf(const DRuntimeClass* pClass) const;




// Implementation
public:
    static const DRuntimeClass classDObject;

    static DRuntimeClass*  _GetBaseClass();
    static DRuntimeClass*  GetThisClass();

};

// Helper macros

#define RUNTIME_CLASS(class_name) (class_name::GetThisClass())

#define ASSERT_KINDOF(class_name, object) \
    ASSERT((object)->IsKindOf(RUNTIME_CLASS(class_name)))

// RTTI helper macros/functions
const DObject*  AfxDynamicDownCast(DRuntimeClass* pClass, const DObject* pObject);
DObject*  AfxDynamicDownCast(DRuntimeClass* pClass, DObject* pObject);
#define DYNAMIC_DOWNCAST(class_name, object) \
    (class_name*)AfxDynamicDownCast(RUNTIME_CLASS(class_name), object)

#ifdef _DEBUG
const DObject*  AfxStaticDownCast(DRuntimeClass* pClass, const DObject* pObject);
DObject*  AfxStaticDownCast(DRuntimeClass* pClass, DObject* pObject);
#define STATIC_DOWNCAST(class_name, object) \
    (static_cast<class_name*>(AfxStaticDownCast(RUNTIME_CLASS(class_name), object)))
#else
#define STATIC_DOWNCAST(class_name, object) (static_cast<class_name*>(object))
#endif

/*============================================================================*/
// Helper macros for declaring DRuntimeClass compatible classes


#define DECLARE_DYNAMIC(class_name) \
protected: \
    static DRuntimeClass*  _GetBaseClass(); \
public: \
    static const DRuntimeClass class##class_name; \
    static DRuntimeClass*  GetThisClass(); \
    __pragma(warning(suppress:26433)) \
    virtual DRuntimeClass* GetRuntimeClass() const; \

#define _DECLARE_DYNAMIC(class_name) \
protected: \
    static DRuntimeClass*  _GetBaseClass(); \
public: \
    static DRuntimeClass class##class_name; \
    static DRuntimeClass*  GetThisClass(); \
    __pragma(warning(suppress:26433)) \
    virtual DRuntimeClass* GetRuntimeClass() const; \



// not serializable, but dynamically constructable
#define DECLARE_DYNCREATE(class_name) \
    DECLARE_DYNAMIC(class_name) \
    static DObject*  CreateObject();



#define IMPLEMENT_RUNTIMECLASS(class_name, base_class_name, wSchema, pfnNew, class_init) \
    DRuntimeClass*  class_name::_GetBaseClass() \
        { return RUNTIME_CLASS(base_class_name); } \
     const DRuntimeClass class_name::class##class_name = { \
        #class_name, sizeof(class class_name), wSchema, pfnNew, \
            &class_name::_GetBaseClass, NULL, class_init }; \
    DRuntimeClass*  class_name::GetThisClass() \
        { return _RUNTIME_CLASS(class_name); } \
    DRuntimeClass* class_name::GetRuntimeClass() const \
        { return _RUNTIME_CLASS(class_name); }

#define IMPLEMENT_DYNAMIC(class_name, base_class_name) \
	IMPLEMENT_RUNTIMECLASS(class_name, base_class_name, 0xFFFF, NULL, NULL)

#define IMPLEMENT_DYNCREATE(class_name, base_class_name) \
	CObject* PASCAL class_name::CreateObject() \
		{ return new class_name; } \
	IMPLEMENT_RUNTIMECLASS(class_name, base_class_name, 0xFFFF, \
		class_name::CreateObject, NULL)


_DYNAMIC_RUNTIME_END_
#endif