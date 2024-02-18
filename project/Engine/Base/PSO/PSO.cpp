#include "PSO.h"
#include "../../Utility/MyUtility.h"

#include <cassert>

using namespace Microsoft::WRL;

PSO::PSO()
{
	state_ = nullptr;
	rootSignature_ = nullptr;
}

PSO::~PSO()
{
}
