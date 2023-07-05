/****************************************************************************
** Resource object code
**
** Created by: The Resource Compiler for Qt version 5.14.2
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

static const unsigned char qt_resource_data[] = {
  // C:/Users/22987/Desktop/EOSI_Tests/TestIniSetting/config.ini
  0x0,0x0,0x0,0x36,
  0xef,
  0xbb,0xbf,0x5b,0x73,0x79,0x73,0x74,0x65,0x6d,0x5d,0xd,0xa,0x75,0x73,0x65,0x72,
  0x3d,0x61,0x64,0x6d,0x69,0x6e,0xd,0xa,0x70,0x61,0x73,0x73,0x77,0x6f,0x72,0x64,
  0x3d,0x31,0x32,0x33,0x34,0x35,0x36,0xd,0xa,0x64,0x62,0x64,0x69,0x72,0x3d,0x6e,
  0x75,0x6c,0x6c,0xd,0xa,
  
};

static const unsigned char qt_resource_name[] = {
  // config.ini
  0x0,0xa,
  0xc,0xf7,0x4,0xc9,
  0x0,0x63,
  0x0,0x6f,0x0,0x6e,0x0,0x66,0x0,0x69,0x0,0x67,0x0,0x2e,0x0,0x69,0x0,0x6e,0x0,0x69,
  
};

static const unsigned char qt_resource_struct[] = {
  // :
  0x0,0x0,0x0,0x0,0x0,0x2,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x1,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  // :/config.ini
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x0,
0x0,0x0,0x1,0x89,0x25,0x5e,0xfb,0x82,

};

#ifdef QT_NAMESPACE
#  define QT_RCC_PREPEND_NAMESPACE(name) ::QT_NAMESPACE::name
#  define QT_RCC_MANGLE_NAMESPACE0(x) x
#  define QT_RCC_MANGLE_NAMESPACE1(a, b) a##_##b
#  define QT_RCC_MANGLE_NAMESPACE2(a, b) QT_RCC_MANGLE_NAMESPACE1(a,b)
#  define QT_RCC_MANGLE_NAMESPACE(name) QT_RCC_MANGLE_NAMESPACE2( \
        QT_RCC_MANGLE_NAMESPACE0(name), QT_RCC_MANGLE_NAMESPACE0(QT_NAMESPACE))
#else
#   define QT_RCC_PREPEND_NAMESPACE(name) name
#   define QT_RCC_MANGLE_NAMESPACE(name) name
#endif

#ifdef QT_NAMESPACE
namespace QT_NAMESPACE {
#endif

bool qRegisterResourceData(int, const unsigned char *, const unsigned char *, const unsigned char *);
bool qUnregisterResourceData(int, const unsigned char *, const unsigned char *, const unsigned char *);

#ifdef QT_NAMESPACE
}
#endif

int QT_RCC_MANGLE_NAMESPACE(qInitResources_ini)();
int QT_RCC_MANGLE_NAMESPACE(qInitResources_ini)()
{
    int version = 3;
    QT_RCC_PREPEND_NAMESPACE(qRegisterResourceData)
        (version, qt_resource_struct, qt_resource_name, qt_resource_data);
    return 1;
}

int QT_RCC_MANGLE_NAMESPACE(qCleanupResources_ini)();
int QT_RCC_MANGLE_NAMESPACE(qCleanupResources_ini)()
{
    int version = 3;
    QT_RCC_PREPEND_NAMESPACE(qUnregisterResourceData)
       (version, qt_resource_struct, qt_resource_name, qt_resource_data);
    return 1;
}

namespace {
   struct initializer {
       initializer() { QT_RCC_MANGLE_NAMESPACE(qInitResources_ini)(); }
       ~initializer() { QT_RCC_MANGLE_NAMESPACE(qCleanupResources_ini)(); }
   } dummy;
}
