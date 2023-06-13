#pragma once

#include "IU.h"

class IVectorClassFactory : public IUnknown_
{
    public:
        virtual HRESULT_ __stdcall CreateInstance(const IID_& iid, void** object, int license[]) = 0;
};