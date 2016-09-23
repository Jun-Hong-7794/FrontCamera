/****************************************************************************
** Meta object code from reading C++ file 'frontcameradialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../front_camera/frontcameradialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'frontcameradialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CImage_Thread_t {
    QByteArrayData data[8];
    char stringdata0[83];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CImage_Thread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CImage_Thread_t qt_meta_stringdata_CImage_Thread = {
    {
QT_MOC_LITERAL(0, 0, 13), // "CImage_Thread"
QT_MOC_LITERAL(1, 14, 9), // "Get_Image"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 7), // "cv::Mat"
QT_MOC_LITERAL(4, 33, 22), // "Set_Image_Capture_Mode"
QT_MOC_LITERAL(5, 56, 9), // "_cap_mode"
QT_MOC_LITERAL(6, 66, 10), // "_save_mode"
QT_MOC_LITERAL(7, 77, 5) // "_path"

    },
    "CImage_Thread\0Get_Image\0\0cv::Mat\0"
    "Set_Image_Capture_Mode\0_cap_mode\0"
    "_save_mode\0_path"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CImage_Thread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    3,   27,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::UInt, QMetaType::UInt, QMetaType::QString,    5,    6,    7,

       0        // eod
};

void CImage_Thread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CImage_Thread *_t = static_cast<CImage_Thread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Get_Image((*reinterpret_cast< cv::Mat(*)>(_a[1]))); break;
        case 1: _t->Set_Image_Capture_Mode((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CImage_Thread::*_t)(cv::Mat );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CImage_Thread::Get_Image)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject CImage_Thread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_CImage_Thread.data,
      qt_meta_data_CImage_Thread,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CImage_Thread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CImage_Thread::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CImage_Thread.stringdata0))
        return static_cast<void*>(const_cast< CImage_Thread*>(this));
    return QThread::qt_metacast(_clname);
}

int CImage_Thread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void CImage_Thread::Get_Image(cv::Mat _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_FRONT_CAMERA_t {
    QByteArrayData data[11];
    char stringdata0[133];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FRONT_CAMERA_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FRONT_CAMERA_t qt_meta_stringdata_FRONT_CAMERA = {
    {
QT_MOC_LITERAL(0, 0, 12), // "FRONT_CAMERA"
QT_MOC_LITERAL(1, 13, 22), // "Get_Image_Capture_Mode"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 9), // "_cap_mode"
QT_MOC_LITERAL(4, 47, 10), // "_save_mode"
QT_MOC_LITERAL(5, 58, 5), // "_path"
QT_MOC_LITERAL(6, 64, 18), // "Click_Start_Button"
QT_MOC_LITERAL(7, 83, 11), // "File_Dialog"
QT_MOC_LITERAL(8, 95, 19), // "Click_LCM_Data_Send"
QT_MOC_LITERAL(9, 115, 9), // "Set_Image"
QT_MOC_LITERAL(10, 125, 7) // "cv::Mat"

    },
    "FRONT_CAMERA\0Get_Image_Capture_Mode\0"
    "\0_cap_mode\0_save_mode\0_path\0"
    "Click_Start_Button\0File_Dialog\0"
    "Click_LCM_Data_Send\0Set_Image\0cv::Mat"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FRONT_CAMERA[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   46,    2, 0x08 /* Private */,
       7,    0,   47,    2, 0x08 /* Private */,
       8,    0,   48,    2, 0x08 /* Private */,
       9,    1,   49,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::UInt, QMetaType::UInt, QMetaType::QString,    3,    4,    5,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10,    2,

       0        // eod
};

void FRONT_CAMERA::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FRONT_CAMERA *_t = static_cast<FRONT_CAMERA *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Get_Image_Capture_Mode((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 1: _t->Click_Start_Button(); break;
        case 2: _t->File_Dialog(); break;
        case 3: _t->Click_LCM_Data_Send(); break;
        case 4: _t->Set_Image((*reinterpret_cast< cv::Mat(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (FRONT_CAMERA::*_t)(unsigned int , unsigned int , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FRONT_CAMERA::Get_Image_Capture_Mode)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject FRONT_CAMERA::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_FRONT_CAMERA.data,
      qt_meta_data_FRONT_CAMERA,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *FRONT_CAMERA::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FRONT_CAMERA::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_FRONT_CAMERA.stringdata0))
        return static_cast<void*>(const_cast< FRONT_CAMERA*>(this));
    if (!strcmp(_clname, "Ui::frontcamera_dlg"))
        return static_cast< Ui::frontcamera_dlg*>(const_cast< FRONT_CAMERA*>(this));
    return QDialog::qt_metacast(_clname);
}

int FRONT_CAMERA::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void FRONT_CAMERA::Get_Image_Capture_Mode(unsigned int _t1, unsigned int _t2, QString _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
