#include "lib/interfaces.h"
#include "lib/interfaces2.h"
#include <windows.h>
#include <iostream>

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

int main()
{
	CoInitialize(NULL);

CLSID CurrentComponent;
CLSID CLSID_MyVector;
CLSID CLSID_BearVector;

{

const wchar_t* progID = L"Rancho";

if(progID = L"Sancho") {

    HRESULT resCLSID_ProgID = CLSIDFromProgID(progID, &CLSID_MyVector);

        if(!(SUCCEEDED(resCLSID_ProgID))) {
            throw "No CLSID form ProgID";
        }
        else {
            std::cout << "CLSID form ProgID OK!" << std::endl;
            CurrentComponent = CLSID_MyVector;
        }
}
else if (progID = L"Rancho") {

    HRESULT resCLSID_ProgID = CLSIDFromProgID(progID, &CLSID_BearVector);

        if(!(SUCCEEDED(resCLSID_ProgID))) {
            throw "No CLSID form ProgID";
        }
        else {
            std::cout << "CLSID form ProgID OK!" << std::endl;
            CurrentComponent = CLSID_BearVector;
        }
    }
}

IClassFactory* PCF = NULL;

HRESULT resFactory = CoGetClassObject(CurrentComponent, CLSCTX_INPROC_SERVER, NULL, Constants::IID_IClassFactory, (void**) &PCF);

if (!SUCCEEDED(resFactory))
{
std::cout << "No factory" << std::endl;
}

FillVector* fv = NULL;
HRESULT resInstance = PCF->CreateInstance(NULL, Constants::IID_IFillVector, (void**) &fv);

if (!SUCCEEDED(resInstance))
{
std::cout << "No instance" << std::endl;
}

Subtraction* sub = NULL;
HRESULT resQuery = fv->QueryInterface(Constants::IID_ISubtraction, (void**) &sub);

if (!SUCCEEDED(resQuery))
{
std::cout << "No QueryInterface" << std::endl;
}

Summation* sum = NULL;
HRESULT resQuery2 = sub->QueryInterface(Constants::IID_ISummation, (void**) &sum);

if (!SUCCEEDED(resQuery2))
{
std::cout << "No QueryInterface 2" << std::endl;
}

fv->fill();
fv->print();

sub->subtract();
sum->sum();
	
sub->Release();
sum->Release();
PCF->Release();
  
IDispatch* pDisp = NULL;
    HRESULT resQueryDisp = fv -> QueryInterface(Constants::IID_IDispatch, (void**)&pDisp);
    if(!(SUCCEEDED(resQueryDisp))) throw "No query dispatch";

    DISPID dispid;

    int namesCount = 1;
    OLECHAR** names = new OLECHAR*[namesCount];
    OLECHAR* name = const_cast<OLECHAR*>(L"fill");
    names[0] = name;

    HRESULT resID_Name = pDisp -> GetIDsOfNames(
                                                    Constants::IIDNULL,
                                                    names,
                                                    namesCount,
                                                    GetUserDefaultLCID(),
                                                    &dispid
    );

    if(!(SUCCEEDED(resID_Name))) {
        std::cout << "No ID of name " << std::endl;
    }
    else {
        DISPPARAMS dispparamsNoArgs = {
                                        NULL,
                                        NULL,
                                        0,
                                        0,
                                       };

        HRESULT resInvoke = pDisp -> Invoke(
                                                dispid,
                                                Constants::IIDNULL,
                                                GetUserDefaultLCID(),
                                                DISPATCH_METHOD,
                                                &dispparamsNoArgs,
                                                NULL,
                                                NULL,
                                                NULL
                                            );

        if(!(SUCCEEDED(resInvoke))) {
            std::cout << "Invoke error!" << std::endl;
        }
    }
  CoUninitialize();  
	return 0;
}