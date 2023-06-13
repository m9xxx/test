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

IID Constants2::IID_IBearVector = {0x00000004,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}};
IID Constants2::IID_IBearVectorClassFactory = {0x00000005,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}};
CLSID Constants2::CLSID_BearVector = {0xD9BB0984, 0xE8BE, 0x4250, {0xB5,0x59, 0x73, 0x68, 0x5F, 0xE1, 0xB5, 0xDC}};
BearVector::BearVector()
{
    std::cout<<"BearVector::BearVector()"<<std::endl;
    refCount = 0;
    CoInitialize(NULL);

    IClassFactory* pCF = NULL;

    HRESULT resFactory = CoGetClassObject(Constants2::CLSID_BearVector, CLSCTX_INPROC_SERVER, NULL, Constants::IID_IClassFactory, (void**)&pCF);

    if(!SUCCEEDED(resFactory)) {
    std::cout << "No factory detected. Please, try again." << std::endl;
    }

    HRESULT resInstance = pCF -> CreateInstance(NULL, Constants::IID_IFillVector, (void**)&fillVector);

    if (!SUCCEEDED(resInstance)) {
    std::cout << "No such function detected. Please, try again." << std::endl;
    }

    HRESULT resQuery = fillVector-> QueryInterface(Constants::IID_ISummation, (void**)&summation);
    resQuery = fillVector-> QueryInterface(Constants::IID_ISubtraction, (void**)&subtraction);
    resQuery = fillVector-> QueryInterface(Constants2::IID_IBearVector, (void**)&bear_vector);

    if(!SUCCEEDED(resQuery)) {
    std::cout << "Error while trying to perform server2/component.cpp:fillVector -> QueryInterface " << std::endl;
    }

    pCF -> Release();
    CoUninitialize();
}

HRESULT BearVector::QueryInterface(const IID& iid, void** object)
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
    else if (iid == Constants2::IID_IBearVector)
    {
        *object = static_cast<IBearVector*>(this);
    }
    else
    {
        *object = NULL;
        return E_NOINTERFACE;
    }

    this->AddRef();

    return S_OK;
}

ULONG BearVector::AddRef()
{
    refCount++;
    //std::cout<<"BearVector::AddRef() "<<refCount<<std::endl;
    return refCount;   
}

ULONG BearVector::Release()
{
    refCount--;

    //std::cout<<"BearVector::Release() "<<refCount<<std::endl;
    if (refCount == 0)
    {
        delete this;
    }

    return refCount;
}

HRESULT BearVector::fill()
{
    std::cout << "BearVector::fill" << std::endl;
    return fillVector-> fill();
}
HRESULT BearVector::BearFill()
{
    std::cout << "BearVector::BearFill" << std::endl;
}
HRESULT BearVector::print()
{
    std::cout << "BearVector::print" << std::endl;
    return fillVector-> print();
}

HRESULT BearVector::sum()
{
    std::cout << "BearVector::sum" << std::endl;
    return summation-> sum();
}

HRESULT BearVector::subtract()
{
    std::cout<<"BearVector::subtract"<<std::endl;
    return subtraction-> subtract();
}

BearVector::~BearVector()
{
    std::cout<<"BearVector destructor"<<std::endl;
    fillVector-> Release();
    summation -> Release();
    subtraction -> Release();
    bear_vector -> Release();
}

HRESULT __stdcall BearVector::GetTypeInfoCount(UINT* pctinfo) {
    std::cout << "BearVector::GetTypeInfoCount" << std::endl;
    return S_OK;
}

HRESULT __stdcall BearVector::GetTypeInfo(UINT iTInfo, LCID lcid, ITypeInfo** ppTInfo) {
    std::cout << "BearVector::GetTypeInfo" << std::endl;
}

HRESULT __stdcall BearVector::GetIDsOfNames(REFIID riid, LPOLESTR* rgszNames, UINT cNames,
                                        LCID lcid, DISPID* rgDispId) {

    std::cout << "BearVector::GetIDsOfNames" << std::endl;

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
    else if(wcscmp(rgszNames[0], L"BearFill") == 0) {
        rgDispId[0] == 5;
}

   else {
    return E_NOTIMPL;
   }

   return S_OK;

    }

HRESULT _stdcall BearVector::Invoke(DISPID dispIdMember, REFIID riid, LCID lcid,WORD wFlags, DISPPARAMS* pDispParams,VARIANT* pVarResult,
                             EXCEPINFO* pExcepInfo, UINT* puArgErr) 
                             {

    std::cout << "BearVector::Invoke" << std::endl;

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
        else if (dispIdMember == 5) {
        BearFill();
    }

    else {
        return E_NOTIMPL;
    }
    return S_OK;
                             }

// ------------------------------------------------------------------------------------------------

BearVectorClassFactory::BearVectorClassFactory()
{
    std::cout<<"BearVectorClassFactory::BearVectorClassFactory()"<<std::endl;
    this->refCount = 0;
}

HRESULT BearVectorClassFactory::QueryInterface(const IID& iid, void** object)
{
    std::cout<<"BearVectorClassFactory::QueryInterface"<<std::endl;

    if (iid == Constants::IID_IClassFactory)
    {
        *object = (IUnknown*) (IClassFactory*) this;
    }
    else if (iid == Constants2::IID_IBearVectorClassFactory)
    {
        *object = (IUnknown*) (IBearVectorClassFactory*) this;
    }
    else
    {
        *object = NULL;
        return E_NOINTERFACE;
    }

    this->AddRef();
    return S_OK;
}

ULONG BearVectorClassFactory::AddRef()
{
    refCount++;
    //std::cout<<"BearVectorClassFactory::AddRef() "<<refCount<<std::endl;
    return refCount;
}

ULONG BearVectorClassFactory::Release()
{
    refCount--;

    //std::cout<<"BearVectorClassFactory::Release() "<<refCount<<std::endl;
    if (refCount == 0)
    {
        delete this;
    }

    return refCount;
}

HRESULT BearVectorClassFactory::CreateInstance(IUnknown* pUnknownOuter, const IID& iid, void** object)
{
    std::cout<<"BearVectorClassFactory::CreateInstance"<<std::endl;
    IUnknown* s = (IUnknown*) (FillVector*) new BearVector();

    s->AddRef();
    HRESULT res = s->QueryInterface(iid, object);
    s->Release();
    
    return res;
}

HRESULT BearVectorClassFactory::CreateInstance(const IID& iid, void** object, int license[])
{
    std::cout<<"BearVectorClassFactory::CreateInstance with license"<<std::endl;
    HRESULT res = E_NOTIMPL;

    if (license != NULL)
    {
        IUnknown* s = (IUnknown*) (FillVector*) new BearVector();

        s->AddRef();
        res = s->QueryInterface(iid, object);
        s->Release();
    }
    
    return res;
}

HRESULT BearVectorClassFactory::LockServer(BOOL bLock)
{
    return S_OK;
}

BearVectorClassFactory::~BearVectorClassFactory()
{
    std::cout<<"BearVectorClassFactory::~BearVectorClassFactory()"<<std::endl;
}
