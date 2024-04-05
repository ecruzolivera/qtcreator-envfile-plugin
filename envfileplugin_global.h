#pragma once

#include <qglobal.h>

#if defined(ENVFILEPLUGIN_LIBRARY)
#  define ENVFILEPLUGIN_EXPORT Q_DECL_EXPORT
#else
#  define ENVFILEPLUGIN_EXPORT Q_DECL_IMPORT
#endif
