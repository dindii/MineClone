#pragma once

#define BIT(x) (1 << x)

#if(_MSC_VER >= 1915)
#define no_init_all deprecated
#endif

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

namespace MC
{
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}