/****************************************************************************
** Meta object code from reading C++ file 'configarmas.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/configarmas.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'configarmas.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ConfigArmas_t {
    QByteArrayData data[9];
    char stringdata0[170];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ConfigArmas_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ConfigArmas_t qt_meta_stringdata_ConfigArmas = {
    {
QT_MOC_LITERAL(0, 0, 11), // "ConfigArmas"
QT_MOC_LITERAL(1, 12, 24), // "on_checkBox_stateChanged"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 4), // "arg1"
QT_MOC_LITERAL(4, 43, 23), // "on_spinBox_valueChanged"
QT_MOC_LITERAL(5, 67, 31), // "on_comboBox_currentIndexChanged"
QT_MOC_LITERAL(6, 99, 21), // "on_buttonBox_accepted"
QT_MOC_LITERAL(7, 121, 21), // "on_buttonBox_rejected"
QT_MOC_LITERAL(8, 143, 26) // "on_checkBox_2_stateChanged"

    },
    "ConfigArmas\0on_checkBox_stateChanged\0"
    "\0arg1\0on_spinBox_valueChanged\0"
    "on_comboBox_currentIndexChanged\0"
    "on_buttonBox_accepted\0on_buttonBox_rejected\0"
    "on_checkBox_2_stateChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ConfigArmas[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x08 /* Private */,
       4,    1,   47,    2, 0x08 /* Private */,
       5,    1,   50,    2, 0x08 /* Private */,
       6,    0,   53,    2, 0x08 /* Private */,
       7,    0,   54,    2, 0x08 /* Private */,
       8,    1,   55,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    3,

       0        // eod
};

void ConfigArmas::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ConfigArmas *_t = static_cast<ConfigArmas *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_checkBox_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->on_spinBox_valueChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->on_comboBox_currentIndexChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->on_buttonBox_accepted(); break;
        case 4: _t->on_buttonBox_rejected(); break;
        case 5: _t->on_checkBox_2_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject ConfigArmas::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ConfigArmas.data,
      qt_meta_data_ConfigArmas,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ConfigArmas::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ConfigArmas::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ConfigArmas.stringdata0))
        return static_cast<void*>(const_cast< ConfigArmas*>(this));
    return QDialog::qt_metacast(_clname);
}

int ConfigArmas::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
