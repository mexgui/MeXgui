/****************************************************************************
** Meta object code from reading C++ file 'QDecNumberTests.hh'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../QDecNumberTests.hh"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QDecNumberTests.hh' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QDecNumberTests[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       1,   74, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x08,
      37,   16,   16,   16, 0x08,
      58,   16,   16,   16, 0x08,
      76,   16,   16,   16, 0x08,
      89,   16,   16,   16, 0x08,
     108,   16,   16,   16, 0x08,
     128,   16,   16,   16, 0x08,
     145,   16,   16,   16, 0x08,
     162,   16,   16,   16, 0x08,
     178,   16,   16,   16, 0x08,
     191,   16,   16,   16, 0x08,
     204,   16,   16,   16, 0x08,

 // enums: name, flags, count, data
     217, 0x0,    5,   78,

 // enum data: key, value
     229, uint(QDecNumberTests::TC_ignore),
     239, uint(QDecNumberTests::TC_comment),
     250, uint(QDecNumberTests::TC_directive),
     263, uint(QDecNumberTests::TC_test),
     271, uint(QDecNumberTests::TC_unknown),

       0        // eod
};

static const char qt_meta_stringdata_QDecNumberTests[] = {
    "QDecNumberTests\0\0compound_interest()\0"
    "compressed_formats()\0packed_decimals()\0"
    "quad_tests()\0quad_with_number()\0"
    "QDecContext_tests()\0QDecNumber_abs()\0"
    "QDecNumber_add()\0QDecimal_size()\0"
    "conversion()\0regression()\0test_cases()\0"
    "TestCodes_e\0TC_ignore\0TC_comment\0"
    "TC_directive\0TC_test\0TC_unknown\0"
};

void QDecNumberTests::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QDecNumberTests *_t = static_cast<QDecNumberTests *>(_o);
        switch (_id) {
        case 0: _t->compound_interest(); break;
        case 1: _t->compressed_formats(); break;
        case 2: _t->packed_decimals(); break;
        case 3: _t->quad_tests(); break;
        case 4: _t->quad_with_number(); break;
        case 5: _t->QDecContext_tests(); break;
        case 6: _t->QDecNumber_abs(); break;
        case 7: _t->QDecNumber_add(); break;
        case 8: _t->QDecimal_size(); break;
        case 9: _t->conversion(); break;
        case 10: _t->regression(); break;
        case 11: _t->test_cases(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QDecNumberTests::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QDecNumberTests::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QDecNumberTests,
      qt_meta_data_QDecNumberTests, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QDecNumberTests::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QDecNumberTests::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QDecNumberTests::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QDecNumberTests))
        return static_cast<void*>(const_cast< QDecNumberTests*>(this));
    return QObject::qt_metacast(_clname);
}

int QDecNumberTests::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
