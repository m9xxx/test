#include "component.h"

IID Constants::IID_IUnknown = {0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}};
IID Constants::IID_IClassFactory = {0x00000001,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}};

IID Constants::IID_IFillVector = {0x00000001,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}};
IID Constants::IID_ISummation = {0x00000002,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}};
IID Constants::IID_ISubtraction = {0x00000003,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}};

IID Constants::IID_IVectorClassFactory = {0x00000011,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}};

//{F55FDC6C-814C-4717-AF91-617F9A4E3EFD}
CLSID Constants::CLSID_MyVector = {0xF55FDC6C, 0x814C, 0x4717, {0xAF, 0x91, 0x61, 0x7F, 0x9A, 0x4E, 0x3E, 0xFD}};

IID Constants::IID_IDispatch =  {0x00020400,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}};
IID Constants::IIDNULL = {0x10000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}};

MyVector::MyVector()
{
    std::cout<<"MyVector::MyVector()"<<std::endl;
    refCount = 0;
}

HRESULT MyVector::QueryInterface(const IID& iid, void** object)
{
    if (iid == Constants::IID_IUnknown)
    {
        *object = (IUnknown*) (Summation*) this;
    }
    else if (iid == Constants::IID_ISummation)
    {
        *object = static_cast<Summation*>(this);
    }
    else if (iid == Constants::IID_ISubtraction)
    {
        *object = static_cast<Subtraction*>(this);
    }
    else if (iid == Constants::IID_IFillVector)
    {
        *object = static_cast<FillVector*>(this);
    }
    else if(iid == Constants::IID_IDispatch) {
        *object = static_cast<IDispatch*>(this);
    }
    else
    {
        *object = NULL;
        return E_NOINTERFACE;
    }

    this->AddRef();

    return S_OK;
}

ULONG MyVector::AddRef()
{
    refCount++;
    //std::cout<<"MyVector::AddRef() "<<refCount<<std::endl;
    return refCount;   
}

ULONG MyVector::Release()
{
    refCount--;

    //std::cout<<"MyVector::Release() "<<refCount<<std::endl;
    if (refCount == 0)
    {
        delete this;
    }

    return refCount;
}

HRESULT MyVector::fill()
{
    std::cout<<"MyVector::fill"<<std::endl;
}

HRESULT MyVector::print()
{
    std::cout<<"MyVector::print"<<std::endl;
}

HRESULT MyVector::sum()
{
    std::cout<<"MyVector::sum"<<std::endl;
}

HRESULT MyVector::subtract()
{
    std::cout<<"MyVector::subtract"<<std::endl;
}

MyVector::~MyVector()
{
    std::cout<<"MyVector destructor"<<std::endl;
}

HRESULT __stdcall MyVector::GetTypeInfoCount(UINT* pctinfo) {
    std::cout << "MyVector::GetTypeInfoCount" << std::endl;
    return S_OK;
}

HRESULT __stdcall MyVector::GetTypeInfo(UINT iTInfo, LCID lcid, ITypeInfo** ppTInfo) {
    std::cout << "MyVector::GetTypeInfo" << std::endl;
}

HRESULT __stdcall MyVector::GetIDsOfNames(REFIID riid, LPOLESTR* rgszNames, UINT cNames,
                                        LCID lcid, DISPID* rgDispId) {

    std::cout << "MyVector::GetIDsOfNames" << std::endl;

    if(cNames != 1) {return E_NOTIMPL;}


   if(wcscmp(rgszNames[0], L"fill")==0) {
        rgDispId[0] = 1;
   }

   else if(wcscmp(rgszNames[0], L"sum")==0) {
        rgDispId[0] = 2;
   }

   else if(wcscmp(rgszNames[0], L"substract")==0) {
        rgDispId[0] = 3;
   }

      else if(wcscmp(rgszNames[0], L"print")==0) {
        rgDispId[0] = 4;
   }

   else {
    return E_NOTIMPL;
   }

   return S_OK;

    }

HRESULT _stdcall MyVector::Invoke(DISPID dispIdMember, REFIID riid, LCID lcid,WORD wFlags, DISPPARAMS* pDispParams,VARIANT* pVarResult,
                             EXCEPINFO* pExcepInfo, UINT* puArgErr) 
                             {

    std::cout << "MyVector::Invoke" << std::endl;

    if(dispIdMember == 1) {
        fill();
    }

    else if (dispIdMember == 2) {
        sum();
    }

    else if (dispIdMember == 3) {
        print();
    }
        else if (dispIdMember == 4) {
        subtract();
    }

    else {
        return E_NOTIMPL;
    }
    return S_OK;
                             }
// ------------------------------------------------------------------------------------------------

MyVecClassFactory::MyVecClassFactory()
{
    std::cout<<"MyVecClassFactory::MyVecClassFactory()"<<std::endl;
    this->refCount = 0;
}

HRESULT MyVecClassFactory::QueryInterface(const IID& iid, void** object)
{
    std::cout<<"MyVecClassFactory::QueryInterface"<<std::endl;

    if (iid == Constants::IID_IClassFactory)
    {
        *object = (IUnknown*) (IClassFactory*) this;
    }
    else if (iid == Constants::IID_IVectorClassFactory)
    {
        *object = (IUnknown*) (IVectorClassFactory*) this;
    }
    else
    {
        *object = NULL;
        return E_NOINTERFACE;
    }

    this->AddRef();
    return S_OK;
}

ULONG MyVecClassFactory::AddRef()
{
    refCount++;
    //std::cout<<"MyVecClassFactory::AddRef() "<<refCount<<std::endl;
    return refCount;
}

ULONG MyVecClassFactory::Release()
{
    refCount--;

    //std::cout<<"MyVecClassFactory::Release() "<<refCount<<std::endl;
    if (refCount == 0)
    {
        delete this;
    }

    return refCount;
}

HRESULT MyVecClassFactory::CreateInstance(IUnknown* pUnknownOuter, const IID& iid, void** object)
{
    std::cout<<"MyVecClassFactory::CreateInstance"<<std::endl;
    IUnknown* s = (IUnknown*) (FillVector*) new MyVector();

    s->AddRef();
    HRESULT res = s->QueryInterface(iid, object);
    s->Release();
    
    return res;
}

HRESULT MyVecClassFactory::CreateInstance(const IID& iid, void** object, int license[])
{
    std::cout<<"MyVecClassFactory::CreateInstance with license"<<std::endl;
    HRESULT res = E_NOTIMPL;

    if (license != NULL)
    {
        IUnknown* s = (IUnknown*) (FillVector*) new MyVector();

        s->AddRef();
        res = s->QueryInterface(iid, object);
        s->Release();
    }
    
    return res;
}

HRESULT MyVecClassFactory::LockServer(BOOL bLock)
{
    return S_OK;
}

MyVecClassFactory::~MyVecClassFactory()
{
    std::cout<<"MyVecClassFactory::~MyVecClassFactory()"<<std::endl;
}
