#ifndef __COL_BASE_H__
#define __COL_BASE_H__

#include "inclusion_col_base.h"

#define COL_GLUE2(a, b) a##b
#define COL_GLUE1(a, b) COL_GLUE2(a, b)
#define COL_GLUE(a, b) COL_GLUE1(a, b)

#define COL_STRING2(a) #a
#define COL_STRING1(a) COL_STRING2(a)
#define COL_STRING(a) COL_STRING1(a)

#endif
