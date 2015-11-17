/****************************************************************************
** Meta object code from reading C++ file 'RobotState.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../RobotState.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'RobotState.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_RobotState_t {
    QByteArrayData data[25];
    char stringdata[212];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RobotState_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RobotState_t qt_meta_stringdata_RobotState = {
    {
QT_MOC_LITERAL(0, 0, 10), // "RobotState"
QT_MOC_LITERAL(1, 11, 13), // "statusChanged"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 16), // "timestampChanged"
QT_MOC_LITERAL(4, 43, 8), // "xChanged"
QT_MOC_LITERAL(5, 52, 8), // "yChanged"
QT_MOC_LITERAL(6, 61, 9), // "vxChanged"
QT_MOC_LITERAL(7, 71, 9), // "vyChanged"
QT_MOC_LITERAL(8, 81, 9), // "axChanged"
QT_MOC_LITERAL(9, 91, 9), // "ayChanged"
QT_MOC_LITERAL(10, 101, 12), // "lightChanged"
QT_MOC_LITERAL(11, 114, 14), // "sensorsChanged"
QT_MOC_LITERAL(12, 129, 6), // "status"
QT_MOC_LITERAL(13, 136, 6), // "Status"
QT_MOC_LITERAL(14, 143, 9), // "timestamp"
QT_MOC_LITERAL(15, 153, 1), // "x"
QT_MOC_LITERAL(16, 155, 1), // "y"
QT_MOC_LITERAL(17, 157, 3), // "v_x"
QT_MOC_LITERAL(18, 161, 3), // "v_y"
QT_MOC_LITERAL(19, 165, 3), // "a_x"
QT_MOC_LITERAL(20, 169, 3), // "a_y"
QT_MOC_LITERAL(21, 173, 5), // "light"
QT_MOC_LITERAL(22, 179, 7), // "sensors"
QT_MOC_LITERAL(23, 187, 13), // "QVector<bool>"
QT_MOC_LITERAL(24, 201, 10) // "statusName"

    },
    "RobotState\0statusChanged\0\0timestampChanged\0"
    "xChanged\0yChanged\0vxChanged\0vyChanged\0"
    "axChanged\0ayChanged\0lightChanged\0"
    "sensorsChanged\0status\0Status\0timestamp\0"
    "x\0y\0v_x\0v_y\0a_x\0a_y\0light\0sensors\0"
    "QVector<bool>\0statusName"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RobotState[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
      11,   74, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x06 /* Public */,
       3,    0,   65,    2, 0x06 /* Public */,
       4,    0,   66,    2, 0x06 /* Public */,
       5,    0,   67,    2, 0x06 /* Public */,
       6,    0,   68,    2, 0x06 /* Public */,
       7,    0,   69,    2, 0x06 /* Public */,
       8,    0,   70,    2, 0x06 /* Public */,
       9,    0,   71,    2, 0x06 /* Public */,
      10,    0,   72,    2, 0x06 /* Public */,
      11,    0,   73,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
      12, 0x80000000 | 13, 0x0049510b,
      14, QMetaType::Float, 0x00495103,
      15, QMetaType::Float, 0x00495103,
      16, QMetaType::Float, 0x00495103,
      17, QMetaType::Float, 0x00495003,
      18, QMetaType::Float, 0x00495003,
      19, QMetaType::Float, 0x00495003,
      20, QMetaType::Float, 0x00495003,
      21, QMetaType::Bool, 0x00495103,
      22, 0x80000000 | 23, 0x0049510b,
      24, QMetaType::QString, 0x00495001,

 // properties: notify_signal_id
       0,
       1,
       2,
       3,
       4,
       5,
       6,
       7,
       8,
       9,
       0,

       0        // eod
};

void RobotState::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        RobotState *_t = static_cast<RobotState *>(_o);
        switch (_id) {
        case 0: _t->statusChanged(); break;
        case 1: _t->timestampChanged(); break;
        case 2: _t->xChanged(); break;
        case 3: _t->yChanged(); break;
        case 4: _t->vxChanged(); break;
        case 5: _t->vyChanged(); break;
        case 6: _t->axChanged(); break;
        case 7: _t->ayChanged(); break;
        case 8: _t->lightChanged(); break;
        case 9: _t->sensorsChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (RobotState::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RobotState::statusChanged)) {
                *result = 0;
            }
        }
        {
            typedef void (RobotState::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RobotState::timestampChanged)) {
                *result = 1;
            }
        }
        {
            typedef void (RobotState::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RobotState::xChanged)) {
                *result = 2;
            }
        }
        {
            typedef void (RobotState::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RobotState::yChanged)) {
                *result = 3;
            }
        }
        {
            typedef void (RobotState::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RobotState::vxChanged)) {
                *result = 4;
            }
        }
        {
            typedef void (RobotState::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RobotState::vyChanged)) {
                *result = 5;
            }
        }
        {
            typedef void (RobotState::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RobotState::axChanged)) {
                *result = 6;
            }
        }
        {
            typedef void (RobotState::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RobotState::ayChanged)) {
                *result = 7;
            }
        }
        {
            typedef void (RobotState::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RobotState::lightChanged)) {
                *result = 8;
            }
        }
        {
            typedef void (RobotState::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RobotState::sensorsChanged)) {
                *result = 9;
            }
        }
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 9:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<bool> >(); break;
        }
    }

}

const QMetaObject RobotState::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_RobotState.data,
      qt_meta_data_RobotState,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *RobotState::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RobotState::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_RobotState.stringdata))
        return static_cast<void*>(const_cast< RobotState*>(this));
    return QObject::qt_metacast(_clname);
}

int RobotState::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< Status*>(_v) = status(); break;
        case 1: *reinterpret_cast< float*>(_v) = timestamp(); break;
        case 2: *reinterpret_cast< float*>(_v) = x(); break;
        case 3: *reinterpret_cast< float*>(_v) = y(); break;
        case 4: *reinterpret_cast< float*>(_v) = v_x(); break;
        case 5: *reinterpret_cast< float*>(_v) = v_y(); break;
        case 6: *reinterpret_cast< float*>(_v) = a_x(); break;
        case 7: *reinterpret_cast< float*>(_v) = a_y(); break;
        case 8: *reinterpret_cast< bool*>(_v) = light(); break;
        case 9: *reinterpret_cast< QVector<bool>*>(_v) = sensors(); break;
        case 10: *reinterpret_cast< QString*>(_v) = getStatusName(); break;
        default: break;
        }
        _id -= 11;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setStatus(*reinterpret_cast< Status*>(_v)); break;
        case 1: setTimestamp(*reinterpret_cast< float*>(_v)); break;
        case 2: setX(*reinterpret_cast< float*>(_v)); break;
        case 3: setY(*reinterpret_cast< float*>(_v)); break;
        case 4: setVx(*reinterpret_cast< float*>(_v)); break;
        case 5: setVy(*reinterpret_cast< float*>(_v)); break;
        case 6: setAx(*reinterpret_cast< float*>(_v)); break;
        case 7: setAy(*reinterpret_cast< float*>(_v)); break;
        case 8: setLight(*reinterpret_cast< bool*>(_v)); break;
        case 9: setSensors(*reinterpret_cast< QVector<bool>*>(_v)); break;
        default: break;
        }
        _id -= 11;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 11;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 11;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 11;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 11;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 11;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 11;
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void RobotState::statusChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void RobotState::timestampChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void RobotState::xChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void RobotState::yChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}

// SIGNAL 4
void RobotState::vxChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, Q_NULLPTR);
}

// SIGNAL 5
void RobotState::vyChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, Q_NULLPTR);
}

// SIGNAL 6
void RobotState::axChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, Q_NULLPTR);
}

// SIGNAL 7
void RobotState::ayChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 7, Q_NULLPTR);
}

// SIGNAL 8
void RobotState::lightChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 8, Q_NULLPTR);
}

// SIGNAL 9
void RobotState::sensorsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 9, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
