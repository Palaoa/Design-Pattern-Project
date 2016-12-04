/****************************************************************************
** Meta object code from reading C++ file 'myFileSystem.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../myFileSystem.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'myFileSystem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MyFileSystem_t {
    QByteArrayData data[10];
    char stringdata0[116];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MyFileSystem_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MyFileSystem_t qt_meta_stringdata_MyFileSystem = {
    {
QT_MOC_LITERAL(0, 0, 12), // "MyFileSystem"
QT_MOC_LITERAL(1, 13, 11), // "onOpenClick"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 11), // "onBackClick"
QT_MOC_LITERAL(4, 38, 12), // "onWriteClick"
QT_MOC_LITERAL(5, 51, 13), // "onCreateClick"
QT_MOC_LITERAL(6, 65, 13), // "onDeleteClick"
QT_MOC_LITERAL(7, 79, 11), // "onFindClick"
QT_MOC_LITERAL(8, 91, 11), // "onCopyClick"
QT_MOC_LITERAL(9, 103, 12) // "onPasteClick"

    },
    "MyFileSystem\0onOpenClick\0\0onBackClick\0"
    "onWriteClick\0onCreateClick\0onDeleteClick\0"
    "onFindClick\0onCopyClick\0onPasteClick"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyFileSystem[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x0a /* Public */,
       3,    0,   55,    2, 0x0a /* Public */,
       4,    0,   56,    2, 0x0a /* Public */,
       5,    0,   57,    2, 0x0a /* Public */,
       6,    0,   58,    2, 0x0a /* Public */,
       7,    0,   59,    2, 0x0a /* Public */,
       8,    0,   60,    2, 0x0a /* Public */,
       9,    0,   61,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MyFileSystem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MyFileSystem *_t = static_cast<MyFileSystem *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onOpenClick(); break;
        case 1: _t->onBackClick(); break;
        case 2: _t->onWriteClick(); break;
        case 3: _t->onCreateClick(); break;
        case 4: _t->onDeleteClick(); break;
        case 5: _t->onFindClick(); break;
        case 6: _t->onCopyClick(); break;
        case 7: _t->onPasteClick(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject MyFileSystem::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MyFileSystem.data,
      qt_meta_data_MyFileSystem,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MyFileSystem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyFileSystem::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MyFileSystem.stringdata0))
        return static_cast<void*>(const_cast< MyFileSystem*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MyFileSystem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
