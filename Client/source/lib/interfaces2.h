#pragma once

#include <windows.h>
#include <iostream>
#include <vector>
#include <string>

class Constants2
{
    public:
     static IID IID_IDispatch;
     static IID IID_IBearVector;
     static IID IID_IBearVectorClassFactory;
     static CLSID CLSID_BearVector;
};

class IBearVectorClassFactory : public IUnknown
{
    public:
        virtual HRESULT __stdcall CreateInstance(const IID& iid, void** object, int license[]) = 0;
};

class IBearVector : public IUnknown
{
    public:
        virtual HRESULT __stdcall BearFill() = 0;
};

extern "C" HRESULT __stdcall __declspec(dllexport) DllGetClassObject(const CLSID& clsid, const IID& iid, void** object);
