/****************************************************************************
** Meta object code from reading C++ file 'CafeOwnerWindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../QtCafeWorkforceManager/CafeOwnerWindow.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CafeOwnerWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.3. It"
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

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSCafeOwnerWindowENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSCafeOwnerWindowENDCLASS = QtMocHelpers::stringData(
    "CafeOwnerWindow",
    "on_createButton_clicked",
    "",
    "on_deleteButton_clicked",
    "on_slotTable_clicked",
    "QModelIndex",
    "index",
    "on_editButton_clicked",
    "on_searchButton_clicked",
    "on_showAllButton_clicked"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSCafeOwnerWindowENDCLASS_t {
    uint offsetsAndSizes[20];
    char stringdata0[16];
    char stringdata1[24];
    char stringdata2[1];
    char stringdata3[24];
    char stringdata4[21];
    char stringdata5[12];
    char stringdata6[6];
    char stringdata7[22];
    char stringdata8[24];
    char stringdata9[25];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSCafeOwnerWindowENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSCafeOwnerWindowENDCLASS_t qt_meta_stringdata_CLASSCafeOwnerWindowENDCLASS = {
    {
        QT_MOC_LITERAL(0, 15),  // "CafeOwnerWindow"
        QT_MOC_LITERAL(16, 23),  // "on_createButton_clicked"
        QT_MOC_LITERAL(40, 0),  // ""
        QT_MOC_LITERAL(41, 23),  // "on_deleteButton_clicked"
        QT_MOC_LITERAL(65, 20),  // "on_slotTable_clicked"
        QT_MOC_LITERAL(86, 11),  // "QModelIndex"
        QT_MOC_LITERAL(98, 5),  // "index"
        QT_MOC_LITERAL(104, 21),  // "on_editButton_clicked"
        QT_MOC_LITERAL(126, 23),  // "on_searchButton_clicked"
        QT_MOC_LITERAL(150, 24)   // "on_showAllButton_clicked"
    },
    "CafeOwnerWindow",
    "on_createButton_clicked",
    "",
    "on_deleteButton_clicked",
    "on_slotTable_clicked",
    "QModelIndex",
    "index",
    "on_editButton_clicked",
    "on_searchButton_clicked",
    "on_showAllButton_clicked"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSCafeOwnerWindowENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   50,    2, 0x08,    1 /* Private */,
       3,    0,   51,    2, 0x08,    2 /* Private */,
       4,    1,   52,    2, 0x08,    3 /* Private */,
       7,    0,   55,    2, 0x08,    5 /* Private */,
       8,    0,   56,    2, 0x08,    6 /* Private */,
       9,    0,   57,    2, 0x08,    7 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject CafeOwnerWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSCafeOwnerWindowENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSCafeOwnerWindowENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSCafeOwnerWindowENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<CafeOwnerWindow, std::true_type>,
        // method 'on_createButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_deleteButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_slotTable_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QModelIndex &, std::false_type>,
        // method 'on_editButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_searchButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_showAllButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void CafeOwnerWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CafeOwnerWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_createButton_clicked(); break;
        case 1: _t->on_deleteButton_clicked(); break;
        case 2: _t->on_slotTable_clicked((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1]))); break;
        case 3: _t->on_editButton_clicked(); break;
        case 4: _t->on_searchButton_clicked(); break;
        case 5: _t->on_showAllButton_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject *CafeOwnerWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CafeOwnerWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSCafeOwnerWindowENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int CafeOwnerWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
