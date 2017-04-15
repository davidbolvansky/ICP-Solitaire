/****************************************************************************
** Meta object code from reading C++ file 'solitaire.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../gui/solitaire.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'solitaire.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Solitaire_t {
    QByteArrayData data[14];
    char stringdata0[169];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Solitaire_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Solitaire_t qt_meta_stringdata_Solitaire = {
    {
QT_MOC_LITERAL(0, 0, 9), // "Solitaire"
QT_MOC_LITERAL(1, 10, 15), // "handleStockDeck"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 15), // "handleWasteDeck"
QT_MOC_LITERAL(4, 43, 17), // "handleTargetDeck1"
QT_MOC_LITERAL(5, 61, 17), // "handleTargetDeck2"
QT_MOC_LITERAL(6, 79, 17), // "handleTargetDeck3"
QT_MOC_LITERAL(7, 97, 17), // "handleTargetDeck4"
QT_MOC_LITERAL(8, 115, 13), // "handleWorking"
QT_MOC_LITERAL(9, 129, 4), // "save"
QT_MOC_LITERAL(10, 134, 4), // "load"
QT_MOC_LITERAL(11, 139, 8), // "showTime"
QT_MOC_LITERAL(12, 148, 4), // "undo"
QT_MOC_LITERAL(13, 153, 15) // "on_hint_clicked"

    },
    "Solitaire\0handleStockDeck\0\0handleWasteDeck\0"
    "handleTargetDeck1\0handleTargetDeck2\0"
    "handleTargetDeck3\0handleTargetDeck4\0"
    "handleWorking\0save\0load\0showTime\0undo\0"
    "on_hint_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Solitaire[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x08 /* Private */,
       3,    0,   75,    2, 0x08 /* Private */,
       4,    0,   76,    2, 0x08 /* Private */,
       5,    0,   77,    2, 0x08 /* Private */,
       6,    0,   78,    2, 0x08 /* Private */,
       7,    0,   79,    2, 0x08 /* Private */,
       8,    0,   80,    2, 0x08 /* Private */,
       9,    0,   81,    2, 0x08 /* Private */,
      10,    0,   82,    2, 0x08 /* Private */,
      11,    0,   83,    2, 0x08 /* Private */,
      12,    0,   84,    2, 0x08 /* Private */,
      13,    0,   85,    2, 0x08 /* Private */,

 // slots: parameters
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
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Solitaire::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Solitaire *_t = static_cast<Solitaire *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->handleStockDeck(); break;
        case 1: _t->handleWasteDeck(); break;
        case 2: _t->handleTargetDeck1(); break;
        case 3: _t->handleTargetDeck2(); break;
        case 4: _t->handleTargetDeck3(); break;
        case 5: _t->handleTargetDeck4(); break;
        case 6: _t->handleWorking(); break;
        case 7: _t->save(); break;
        case 8: _t->load(); break;
        case 9: _t->showTime(); break;
        case 10: _t->undo(); break;
        case 11: _t->on_hint_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject Solitaire::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Solitaire.data,
      qt_meta_data_Solitaire,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Solitaire::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Solitaire::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Solitaire.stringdata0))
        return static_cast<void*>(const_cast< Solitaire*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Solitaire::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
