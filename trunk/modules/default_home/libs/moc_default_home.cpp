/****************************************************************************
** Meta object code from reading C++ file 'default_home.h'
**
** Created: Thu Feb 26 21:16:55 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../default_home.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'default_home.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_homeModuleWidget[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets

       0        // eod
};

static const char qt_meta_stringdata_homeModuleWidget[] = {
    "homeModuleWidget\0"
};

const QMetaObject homeModuleWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_homeModuleWidget,
      qt_meta_data_homeModuleWidget, 0 }
};

const QMetaObject *homeModuleWidget::metaObject() const
{
    return &staticMetaObject;
}

void *homeModuleWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_homeModuleWidget))
        return static_cast<void*>(const_cast< homeModuleWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int homeModuleWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_homeModuleApplet[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets

       0        // eod
};

static const char qt_meta_stringdata_homeModuleApplet[] = {
    "homeModuleApplet\0"
};

const QMetaObject homeModuleApplet::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_homeModuleApplet,
      qt_meta_data_homeModuleApplet, 0 }
};

const QMetaObject *homeModuleApplet::metaObject() const
{
    return &staticMetaObject;
}

void *homeModuleApplet::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_homeModuleApplet))
        return static_cast<void*>(const_cast< homeModuleApplet*>(this));
    return QWidget::qt_metacast(_clname);
}

int homeModuleApplet::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_homeModule[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets

       0        // eod
};

static const char qt_meta_stringdata_homeModule[] = {
    "homeModule\0"
};

const QMetaObject homeModule::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_homeModule,
      qt_meta_data_homeModule, 0 }
};

const QMetaObject *homeModule::metaObject() const
{
    return &staticMetaObject;
}

void *homeModule::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_homeModule))
        return static_cast<void*>(const_cast< homeModule*>(this));
    if (!strcmp(_clname, "M_Interface"))
        return static_cast< M_Interface*>(const_cast< homeModule*>(this));
    if (!strcmp(_clname, "com.trolltech.Lyxcar.M_Interface/1.0"))
        return static_cast< M_Interface*>(const_cast< homeModule*>(this));
    return QObject::qt_metacast(_clname);
}

int homeModule::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
