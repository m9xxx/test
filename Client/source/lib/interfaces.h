#pragma once

#include <windows.h>
#include <iostream>
#include <vector>
#include <string>

class Constants
{
    public:
     static IID IID_IUnknown;
     static IID IID_IClassFactory;

     static IID IID_IFillVector;
     static IID IID_ISummation;
     static IID IID_ISubtraction;

     static IID IID_IVectorClassFactory;

     static CLSID CLSID_MyVector;
     static IID IID_IDispatch;
     static IID IIDNULL;
};

class IVectorClassFactory : public IUnknown
{
    public:
        virtual HRESULT __stdcall CreateInstance(const IID& iid, void** object, int license[]) = 0;
};

class FillVector : public IUnknown
{
    public:
        virtual HRESULT __stdcall fill() = 0;
        virtual HRESULT __stdcall print() = 0;
};

class Subtraction : public IUnknown
{
	public:
		virtual HRESULT __stdcall subtract() = 0;
};	

class Summation : public IUnknown
{
	public:
		virtual HRESULT __stdcall sum() = 0;
};

extern "C" HRESULT __stdcall __declspec(dllexport) DllGetClassObject(const CLSID& clsid, const IID& iid, void** object);
