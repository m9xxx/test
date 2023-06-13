#pragma once

#include "interfaces2.h"
#include "./lib/interfaces.h"
 
class BearVector: public FillVector, public Summation, public Subtraction, public IDispatch, public IBearVector
{
    private:
        std::vector<int> array;
        int refCount;
        FillVector* fillVector;
        Subtraction* subtraction;
        Summation* summation;
        IBearVector* bear_vector;
    public:
        BearVector();

        virtual HRESULT __stdcall QueryInterface(const IID& iid, void** object);
        virtual ULONG __stdcall AddRef();
        virtual ULONG __stdcall Release();

        virtual HRESULT __stdcall BearFill();
        virtual HRESULT __stdcall fill();
        virtual HRESULT __stdcall print();

        virtual HRESULT __stdcall sum();
        virtual HRESULT __stdcall subtract();
        
        virtual HRESULT __stdcall GetIDsOfNames(REFIID riid, LPOLESTR* rgszNames, UINT cNames, LCID lcid, DISPID* rgDispId);
        virtual HRESULT __stdcall Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS* pDIspParams,
                                        VARIANT* pVarResult, EXCEPINFO* pExcepInfo, UINT* puArgErr);

        virtual HRESULT __stdcall GetTypeInfoCount(UINT* pctinfo);
        virtual HRESULT __stdcall GetTypeInfo(UINT iTInfo, LCID lcid, ITypeInfo** ppTInfo);
        ~BearVector();
};

class BearVectorClassFactory : public IClassFactory, public IBearVectorClassFactory
{
    private:
        int refCount;
    public:
        BearVectorClassFactory();

        virtual HRESULT __stdcall QueryInterface(const IID& iid, void** object);
        virtual ULONG __stdcall AddRef();
        virtual ULONG __stdcall Release();

        virtual HRESULT __stdcall CreateInstance(IUnknown* pUnknownOuter, const IID& iid, void** object);
        
        virtual HRESULT __stdcall CreateInstance(const IID& iid, void** object, int license[]);

        virtual HRESULT __stdcall LockServer(BOOL bLock);

        ~BearVectorClassFactory();
};