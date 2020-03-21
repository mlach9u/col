#ifndef __INCLUSION_COL_STREAM_H__
#define __INCLUSION_COL_STREAM_H__

#include <iostream>
#include <sstream>

#ifdef __linux__
#include <cstring>

#include <string>
#define _XSTRING_
#include <vector>
#define _VECTOR_
#include <list>
#define _LIST_
#include <map>
#define _UTILITY_
#define _MAP_
#include <tuple>
#define _TUPLE_
#endif

#include "../col_base/col_base.h"
#include "../col_type_traits/inclusion_col_type_traits.h"

#endif
