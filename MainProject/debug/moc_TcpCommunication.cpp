/****************************************************************************
** Meta object code from reading C++ file 'TcpCommunication.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../TcpCommunication/TcpCommunication.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TcpCommunication.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TcpCommunication_t {
    QByteArrayData data[10];
    char stringdata[128];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TcpCommunication_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TcpCommunication_t qt_meta_stringdata_TcpCommunication = {
    {
QT_MOC_LITERAL(0, 0, 16), // "TcpCommunication"
QT_MOC_LITERAL(1, 17, 13), // "errorOccurred"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 9), // "dataReady"
QT_MOC_LITERAL(4, 42, 12), // "QDataStream&"
QT_MOC_LITERAL(5, 55, 6), // "stream"
QT_MOC_LITERAL(6, 62, 12), // "dataReceived"
QT_MOC_LITERAL(7, 75, 11), // "handleError"
QT_MOC_LITERAL(8, 87, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(9, 116, 11) // "socketError"

    },
    "TcpCommunication\0errorOccurred\0\0"
    "dataReady\0QDataStream&\0stream\0"
    "dataReceived\0handleError\0"
    "QAbstractSocket::SocketError\0socketError"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TcpCommunication[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       3,    1,   37,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   40,    2, 0x09 /* Protected */,
       7,    1,   41,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, 0x80000000 | 4,    5,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,

       0        // eod
};

void TcpCommunication::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TcpCommunication *_t = static_cast<TcpCommunication *>(_o);
        switch (_id) {
        case 0: _t->errorOccurred((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->dataReady((*reinterpret_cast< QDataStream(*)>(_a[1]))); break;
        case 2: _t->dataReceived(); break;
        case 3: _t->handleError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TcpCommunication::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TcpCommunication::errorOccurred)) {
                *result = 0;
            }
        }
        {
            typedef void (TcpCommunication::*_t)(QDataStream & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TcpCommunication::dataReady)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject TcpCommunication::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_TcpCommunication.data,
      qt_meta_data_TcpCommunication,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TcpCommunication::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TcpCommunication::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TcpCommunication.stringdata))
        return static_cast<void*>(const_cast< TcpCommunication*>(this));
    return QObject::qt_metacast(_clname);
}

int TcpCommunication::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void TcpCommunication::errorOccurred(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TcpCommunication::dataReady(QDataStream & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
