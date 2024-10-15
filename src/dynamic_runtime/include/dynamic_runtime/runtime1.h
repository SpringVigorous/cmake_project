
#pragma once
#ifndef __RUNTIME1_H___
#define __RUNTIME1_H___


#include <string>
#include <map>
#include "dynamic_runtime/macro.h"

_DYNAMIC_RUNTIME_BEGIN_

// 假设 ASSERT 是一个断言宏
#define ASSERT(condition) ((void)(condition))

// 假设 AFX_COMDAT 是一个空宏
#define AFX_COMDAT

class DObject;

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
    DObject* (* m_pfnCreateObject)();
    DRuntimeClass* (* m_pfnGetBaseClass)();

    // Operations
    DObject* CreateObject()
    {
        if (m_pfnCreateObject != nullptr)
        {
            return m_pfnCreateObject();
        }
        return nullptr;
    }

    BOOL IsDerivedFrom(const DRuntimeClass* pBaseClass) const
    {
        const DRuntimeClass* current = this;
        while (current != nullptr)
        {
            if (current == pBaseClass)
            {
                return TRUE;
            }
            current = current->m_pfnGetBaseClass ? current->m_pfnGetBaseClass() : nullptr;
        }
        return FALSE;
    }

    // dynamic name lookup and creation
    static DRuntimeClass* FromName(LPCSTR lpszClassName)
    {
        static std::map<LPCSTR, DRuntimeClass*> classMap;
        auto it = classMap.find(lpszClassName);
        if (it != classMap.end())
        {
            return it->second;
        }
        return nullptr;
    }

    static DRuntimeClass* FromName(LPCWSTR lpszClassName)
    {
        static std::map<LPCWSTR, DRuntimeClass*> classMap;
        auto it = classMap.find(lpszClassName);
        if (it != classMap.end())
        {
            return it->second;
        }
        return nullptr;
    }

    static DObject* CreateObject(LPCSTR lpszClassName)
    {
        DRuntimeClass* pClass = FromName(lpszClassName);
        if (pClass)
        {
            return pClass->CreateObject();
        }
        return nullptr;
    }

    static DObject* CreateObject(LPCWSTR lpszClassName)
    {
        DRuntimeClass* pClass = FromName(lpszClassName);
        if (pClass)
        {
            return pClass->CreateObject();
        }
        return nullptr;
    }

    // DRuntimeClass objects linked together in simple list
    DRuntimeClass* m_pNextClass;       // linked list of registered classes
    const D_CLASSINIT* m_pClassInit;

    // Constructor
    DRuntimeClass(LPCSTR className, int objectSize, UINT schema, DObject* (*createObject)(), DRuntimeClass* (*getBaseClass)())
        : m_lpszClassName(className), m_nObjectSize(objectSize), m_wSchema(schema),
          m_pfnCreateObject(createObject), m_pfnGetBaseClass(getBaseClass),
          m_pNextClass(nullptr), m_pClassInit(nullptr)
    {}
};

// generate static object constructor for class registration
void DYNAMIC_RUNTIME_API DClassInit(DRuntimeClass* pNewClass)
{
    // Register the class
    static DRuntimeClass* head = nullptr;
    pNewClass->m_pNextClass = head;
    head = pNewClass;
}

class DObject
{
public:
    // Object model (types, destruction, allocation)
    virtual DRuntimeClass* GetRuntimeClass() const;
    virtual ~DObject() = 0;  // virtual destructors are necessary

    // Diagnostic allocations
    void* operator new(size_t nSize)
    {
        return malloc(nSize);
    }

    void* operator new(size_t nSize, void* p)
    {
        return p;
    }

    void operator delete(void* p)
    {
        free(p);
    }

    void operator delete(void* p, void* pPlace)
    {
        free(p);
    }

    // Disable the copy constructor and assignment by default so you will get
    //   compiler errors instead of unexpected behavior if you pass objects
    //   by value or assign objects.
protected:
    DObject()
    {
    }

private:
    DObject(const DObject& objectSrc);              // no implementation
    void operator=(const DObject& objectSrc);       // no implementation

// Attributes
public:
    BOOL IsSerializable() const
    {
        return FALSE;
    }

    BOOL IsKindOf(const DRuntimeClass* pClass) const
    {
        return GetRuntimeClass()->IsDerivedFrom(pClass);
    }

// Implementation
public:
    static const DRuntimeClass classDObject;

    static DRuntimeClass* _GetBaseClass()
    {
        return nullptr;
    }

    static DRuntimeClass* GetThisClass()
    {
        return &classDObject;
    }
};

const DRuntimeClass DObject::classDObject("DObject", sizeof(DObject), 0xFFFF, nullptr, &DObject::_GetBaseClass);

DRuntimeClass* DObject::GetRuntimeClass() const
{
    return &classDObject;
}



// RTTI helper macros/functions
const DObject* AfxDynamicDownCast(DRuntimeClass* pClass, const DObject* pObject)
{
    return pObject->IsKindOf(pClass) ? pObject : nullptr;
}

DObject* AfxDynamicDownCast(DRuntimeClass* pClass, DObject* pObject)
{
    return pObject->IsKindOf(pClass) ? pObject : nullptr;
}

#define DYNAMIC_DOWNCAST(class_name, object) \
    (class_name*)AfxDynamicDownCast(RUNTIME_CLASS(class_name), object)

#ifdef _DEBUG
const DObject* AfxStaticDownCast(DRuntimeClass* pClass, const DObject* pObject)
{
    ASSERT(pObject->IsKindOf(pClass));
    return pObject;
}

DObject* AfxStaticDownCast(DRuntimeClass* pClass, DObject* pObject)
{
    ASSERT(pObject->IsKindOf(pClass));
    return pObject;
}

#define STATIC_DOWNCAST(class_name, object) \
    (static_cast<class_name*>(AfxStaticDownCast(RUNTIME_CLASS(class_name), object)))
#else
#define STATIC_DOWNCAST(class_name, object) (static_cast<class_name*>(object))
#endif

_DYNAMIC_RUNTIME_END_
#endif