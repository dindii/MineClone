#pragma once

#define BIT(x) (1 << x)

#if(_MSC_VER >= 1915)
#define no_init_all deprecated
#endif