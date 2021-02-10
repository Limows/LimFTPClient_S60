/****************************************************************************
** Meta object code from reading C++ file 'paramsdialog.h'
**
** Created: Wed 10. Feb 23:16:29 2021
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../paramsdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'paramsdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ParamsDialog[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x08,
      42,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ParamsDialog[] = {
    "ParamsDialog\0\0on_ParamsDialog_destroyed()\0"
    "on_ExitAction_triggered()\0"
};

const QMetaObject ParamsDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ParamsDialog,
      qt_meta_data_ParamsDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ParamsDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ParamsDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ParamsDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ParamsDialog))
        return static_cast<void*>(const_cast< ParamsDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int ParamsDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_ParamsDialog_destroyed(); break;
        case 1: on_ExitAction_triggered(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
