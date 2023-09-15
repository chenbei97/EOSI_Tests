#ifndef BUTTONDLL_GLOBAL_H
#define BUTTONDLL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(BUTTONDLL_LIBRARY)
#  define BUTTONDLL_EXPORT Q_DECL_EXPORT
#else
#  define BUTTONDLL_EXPORT Q_DECL_IMPORT
#endif

#endif // BUTTONDLL_GLOBAL_H
