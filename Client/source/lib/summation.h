#pragma once

#include "IU.h"

class Summation : public IUnknown_
{
	public:
		virtual HRESULT_ __stdcall sum(std::vector<int> vector, std::vector<int> result) = 0;
};