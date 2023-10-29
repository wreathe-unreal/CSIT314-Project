/****************************************************************************
** Meta object code from reading C++ file 'SysAdminWindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../QtCafeWorkforceManager/SysAdminWindow.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SysAdminWindow.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSSysAdminWindowENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSSysAdminWindowENDCLASS = QtMocHelpers::stringData(
    "SysAdminWindow",
    "on_userTable_clicked",
    "",
    "QModelIndex",
    "index",
    "on_editButton_clicked",
    "on_createButton_clicked",
    "on_profileCombo_currentIndexChanged",
    "on_profileComboCreate_currentIndexChanged",
    "on_deleteButton_clicked",
    "on_searchButton_clicked",
    "OnLogoutTriggered",
    "on_showAllUsersButton_clicked"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSSysAdminWindowENDCLASS_t {
    uint offsetsAndSizes[26];
    char stringdata0[15];
    char stringdata1[21];
    char stringdata2[1];
    char stringdata3[12];
    char stringdata4[6];
    char stringdata5[22];
    char stringdata6[24];
    char stringdata7[36];
    char stringdata8[42];
    char stringdata9[24];
    char stringdata10[24];
    char stringdata11[18];
    char stringdata12[30];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSSysAdminWindowENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSSysAdminWindowENDCLASS_t qt_meta_stringdata_CLASSSysAdminWindowENDCLASS = {
    {
        QT_MOC_LITERAL(0, 14),  // "SysAdminWindow"
        QT_MOC_LITERAL(15, 20),  // "on_userTable_clicked"
        QT_MOC_LITERAL(36, 0),  // ""
        QT_MOC_LITERAL(37, 11),  // "QModelIndex"
        QT_MOC_LITERAL(49, 5),  // "index"
        QT_MOC_LITERAL(55, 21),  // "on_editButton_clicked"
        QT_MOC_LITERAL(77, 23),  // "on_createButton_clicked"
        QT_MOC_LITERAL(101, 35),  // "on_profileCombo_currentIndexC..."
        QT_MOC_LITERAL(137, 41),  // "on_profileComboCreate_current..."
        QT_MOC_LITERAL(179, 23),  // "on_deleteButton_clicked"
        QT_MOC_LITERAL(203, 23),  // "on_searchButton_clicked"
        QT_MOC_LITERAL(227, 17),  // "OnLogoutTriggered"
        QT_MOC_LITERAL(245, 29)   // "on_showAllUsersButton_clicked"
    },
    "SysAdminWindow",
    "on_userTable_clicked",
    "",
    "QModelIndex",
    "index",
    "on_editButton_clicked",
    "on_createButton_clicked",
    "on_profileCombo_currentIndexChanged",
    "on_profileComboCreate_currentIndexChanged",
    "on_deleteButton_clicked",
    "on_searchButton_clicked",
    "OnLogoutTriggered",
    "on_showAllUsersButton_clicked"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSSysAdminWindowENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   68,    2, 0x08,    1 /* Private */,
       5,    0,   71,    2, 0x08,    3 /* Private */,
       6,    0,   72,    2, 0x08,    4 /* Private */,
       7,    1,   73,    2, 0x08,    5 /* Private */,
       8,    1,   76,    2, 0x08,    7 /* Private */,
       9,    0,   79,    2, 0x08,    9 /* Private */,
      10,    0,   80,    2, 0x08,   10 /* Private */,
      11,    0,   81,    2, 0x08,   11 /* Private */,
      12,    0,   82,    2, 0x08,   12 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject SysAdminWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSSysAdminWindowENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSSysAdminWindowENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSSysAdminWindowENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<SysAdminWindow, std::true_type>,
        // method 'on_userTable_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QModelIndex &, std::false_type>,
        // method 'on_editButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_createButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_profileCombo_currentIndexChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_profileComboCreate_currentIndexChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_deleteButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_searchButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'OnLogoutTriggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_showAllUsersButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void SysAdminWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SysAdminWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_userTable_clicked((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1]))); break;
        case 1: _t->on_editButton_clicked(); break;
        case 2: _t->on_createButton_clicked(); break;
        case 3: _t->on_profileCombo_currentIndexChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 4: _t->on_profileComboCreate_currentIndexChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 5: _t->on_deleteButton_clicked(); break;
        case 6: _t->on_searchButton_clicked(); break;
        case 7: _t->OnLogoutTriggered(); break;
        case 8: _t->on_showAllUsersButton_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject *SysAdminWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SysAdminWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSSysAdminWindowENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int SysAdminWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
