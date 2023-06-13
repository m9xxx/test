#pragma once

#include "IU.h"

class FillVector : public IUnknown_
{
    public:
        virtual HRESULT_ __stdcall fill(std::vector<int> vector) = 0;
        virtual HRESULT_ __stdcall print() = 0;
};