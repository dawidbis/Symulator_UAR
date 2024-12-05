/****************************************************************************
** Meta object code from reading C++ file 'regulatorpid.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../regulatorpid.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'regulatorpid.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN12RegulatorPIDE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN12RegulatorPIDE = QtMocHelpers::stringData(
    "RegulatorPID",
    "wartoscProporcjonalna",
    "",
    "wartoscP",
    "wartoscCalkujaca",
    "wartoscI",
    "wartoscRozniczkujaca",
    "wartoscD",
    "ustawKp",
    "nowaWartosc",
    "ustawKi",
    "ustawKd",
    "ustawAntiWindup",
    "wlaczAntiWindup",
    "wlaczony"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN12RegulatorPIDE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   62,    2, 0x06,    1 /* Public */,
       4,    1,   65,    2, 0x06,    3 /* Public */,
       6,    1,   68,    2, 0x06,    5 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       8,    1,   71,    2, 0x0a,    7 /* Public */,
      10,    1,   74,    2, 0x0a,    9 /* Public */,
      11,    1,   77,    2, 0x0a,   11 /* Public */,
      12,    1,   80,    2, 0x0a,   13 /* Public */,
      13,    1,   83,    2, 0x0a,   15 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    5,
    QMetaType::Void, QMetaType::Double,    7,

 // slots: parameters
    QMetaType::Void, QMetaType::Double,    9,
    QMetaType::Void, QMetaType::Double,    9,
    QMetaType::Void, QMetaType::Double,    9,
    QMetaType::Void, QMetaType::Double,    9,
    QMetaType::Void, QMetaType::Bool,   14,

       0        // eod
};

Q_CONSTINIT const QMetaObject RegulatorPID::staticMetaObject = { {
    QMetaObject::SuperData::link<IO::staticMetaObject>(),
    qt_meta_stringdata_ZN12RegulatorPIDE.offsetsAndSizes,
    qt_meta_data_ZN12RegulatorPIDE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN12RegulatorPIDE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<RegulatorPID, std::true_type>,
        // method 'wartoscProporcjonalna'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'wartoscCalkujaca'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'wartoscRozniczkujaca'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'ustawKp'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'ustawKi'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'ustawKd'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'ustawAntiWindup'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'wlaczAntiWindup'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>
    >,
    nullptr
} };

void RegulatorPID::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<RegulatorPID *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->wartoscProporcjonalna((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 1: _t->wartoscCalkujaca((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 2: _t->wartoscRozniczkujaca((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 3: _t->ustawKp((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 4: _t->ustawKi((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 5: _t->ustawKd((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 6: _t->ustawAntiWindup((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 7: _t->wlaczAntiWindup((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (RegulatorPID::*)(double );
            if (_q_method_type _q_method = &RegulatorPID::wartoscProporcjonalna; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (RegulatorPID::*)(double );
            if (_q_method_type _q_method = &RegulatorPID::wartoscCalkujaca; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _q_method_type = void (RegulatorPID::*)(double );
            if (_q_method_type _q_method = &RegulatorPID::wartoscRozniczkujaca; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject *RegulatorPID::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RegulatorPID::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN12RegulatorPIDE.stringdata0))
        return static_cast<void*>(this);
    return IO::qt_metacast(_clname);
}

int RegulatorPID::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = IO::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void RegulatorPID::wartoscProporcjonalna(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void RegulatorPID::wartoscCalkujaca(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void RegulatorPID::wartoscRozniczkujaca(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
