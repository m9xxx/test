#pragma once

#include "IU.h"

class Subtraction : public IUnknown_
{
	public:
		virtual HRESULT_ __stdcall subtract(std::vector<int> vector, std::vector<int> result) = 0;
};		