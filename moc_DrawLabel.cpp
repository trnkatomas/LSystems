/****************************************************************************
** Meta object code from reading C++ file 'DrawLabel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "DrawLabel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DrawLabel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_DrawLabel_t {
    QByteArrayData data[6];
    char stringdata[41];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DrawLabel_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DrawLabel_t qt_meta_stringdata_DrawLabel = {
    {
QT_MOC_LITERAL(0, 0, 9), // "DrawLabel"
QT_MOC_LITERAL(1, 10, 7), // "clicked"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 4), // "open"
QT_MOC_LITERAL(4, 24, 11), // "std::string"
QT_MOC_LITERAL(5, 36, 4) // "save"

    },
    "DrawLabel\0clicked\0\0open\0std::string\0"
    "save"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DrawLabel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06 /* Public */,
       3,    1,   30,    2, 0x06 /* Public */,
       5,    0,   33,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void,

       0        // eod
};

void DrawLabel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DrawLabel *_t = static_cast<DrawLabel *>(_o);
        switch (_id) {
        case 0: _t->clicked(); break;
        case 1: _t->open((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 2: _t->save(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (DrawLabel::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DrawLabel::clicked)) {
                *result = 0;
            }
        }
        {
            typedef void (DrawLabel::*_t)(std::string );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DrawLabel::open)) {
                *result = 1;
            }
        }
        {
            typedef void (DrawLabel::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DrawLabel::save)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject DrawLabel::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_DrawLabel.data,
      qt_meta_data_DrawLabel,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *DrawLabel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DrawLabel::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_DrawLabel.stringdata))
        return static_cast<void*>(const_cast< DrawLabel*>(this));
    return QLabel::qt_metacast(_clname);
}

int DrawLabel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void DrawLabel::clicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void DrawLabel::open(std::string _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DrawLabel::save()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
