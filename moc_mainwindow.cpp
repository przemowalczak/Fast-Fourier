/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Worker_t {
    QByteArrayData data[7];
    char stringdata0[61];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Worker_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Worker_t qt_meta_stringdata_Worker = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Worker"
QT_MOC_LITERAL(1, 7, 11), // "resultReady"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 15), // "Worker_data_out"
QT_MOC_LITERAL(4, 36, 7), // "results"
QT_MOC_LITERAL(5, 44, 6), // "doWork"
QT_MOC_LITERAL(6, 51, 9) // "parameter"

    },
    "Worker\0resultReady\0\0Worker_data_out\0"
    "results\0doWork\0parameter"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Worker[] = {

 // content:
       8,       // revision
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
       5,    1,   27,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    6,

       0        // eod
};

void Worker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Worker *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->resultReady((*reinterpret_cast< Worker_data_out(*)>(_a[1]))); break;
        case 1: _t->doWork((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Worker_data_out >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Worker::*)(Worker_data_out );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Worker::resultReady)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Worker::staticMetaObject = { {
    QMetaObject::SuperData::link<QThread::staticMetaObject>(),
    qt_meta_stringdata_Worker.data,
    qt_meta_data_Worker,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Worker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Worker::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Worker.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int Worker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void Worker::resultReady(Worker_data_out _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_Worker_linear_t {
    QByteArrayData data[7];
    char stringdata0[82];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Worker_linear_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Worker_linear_t qt_meta_stringdata_Worker_linear = {
    {
QT_MOC_LITERAL(0, 0, 13), // "Worker_linear"
QT_MOC_LITERAL(1, 14, 18), // "resultReady_linear"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 22), // "Worker_data_out_linear"
QT_MOC_LITERAL(4, 57, 7), // "results"
QT_MOC_LITERAL(5, 65, 6), // "doWork"
QT_MOC_LITERAL(6, 72, 9) // "parameter"

    },
    "Worker_linear\0resultReady_linear\0\0"
    "Worker_data_out_linear\0results\0doWork\0"
    "parameter"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Worker_linear[] = {

 // content:
       8,       // revision
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
       5,    1,   27,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    6,

       0        // eod
};

void Worker_linear::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Worker_linear *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->resultReady_linear((*reinterpret_cast< Worker_data_out_linear(*)>(_a[1]))); break;
        case 1: _t->doWork((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Worker_data_out_linear >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Worker_linear::*)(Worker_data_out_linear );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Worker_linear::resultReady_linear)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Worker_linear::staticMetaObject = { {
    QMetaObject::SuperData::link<QThread::staticMetaObject>(),
    qt_meta_stringdata_Worker_linear.data,
    qt_meta_data_Worker_linear,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Worker_linear::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Worker_linear::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Worker_linear.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int Worker_linear::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void Worker_linear::resultReady_linear(Worker_data_out_linear _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[218];
    char stringdata0[4494];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 7), // "operate"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 14), // "operate_linear"
QT_MOC_LITERAL(4, 35, 13), // "handleResults"
QT_MOC_LITERAL(5, 49, 15), // "Worker_data_out"
QT_MOC_LITERAL(6, 65, 20), // "handleResults_linear"
QT_MOC_LITERAL(7, 86, 22), // "Worker_data_out_linear"
QT_MOC_LITERAL(8, 109, 28), // "fitsin_nonlinear_thread_init"
QT_MOC_LITERAL(9, 138, 25), // "fitsin_linear_thread_init"
QT_MOC_LITERAL(10, 164, 18), // "show_phase_clicked"
QT_MOC_LITERAL(11, 183, 17), // "get_phase_diagram"
QT_MOC_LITERAL(12, 201, 28), // "data_spectral_window_clicked"
QT_MOC_LITERAL(13, 230, 18), // "simulation_analyse"
QT_MOC_LITERAL(14, 249, 37), // "combo_settings_action_General..."
QT_MOC_LITERAL(15, 287, 27), // "spinB_General_nfreq_changed"
QT_MOC_LITERAL(16, 315, 25), // "spinB_General_n_s_changed"
QT_MOC_LITERAL(17, 341, 25), // "spinB_General_n_h_changed"
QT_MOC_LITERAL(18, 367, 28), // "spinB_General_n_c2_1_changed"
QT_MOC_LITERAL(19, 396, 28), // "spinB_General_n_c2_2_changed"
QT_MOC_LITERAL(20, 425, 28), // "spinB_General_n_c3_1_changed"
QT_MOC_LITERAL(21, 454, 28), // "spinB_General_n_c3_2_changed"
QT_MOC_LITERAL(22, 483, 28), // "spinB_General_n_c3_3_changed"
QT_MOC_LITERAL(23, 512, 26), // "spinB_NLSF_maxiter_changed"
QT_MOC_LITERAL(24, 539, 33), // "radio_General_use_h_peaks_cha..."
QT_MOC_LITERAL(25, 573, 30), // "radio_General_use_h_SN_changed"
QT_MOC_LITERAL(26, 604, 39), // "spinB_General_auto_stop_crit_..."
QT_MOC_LITERAL(27, 644, 10), // "show_peaks"
QT_MOC_LITERAL(28, 655, 10), // "hide_peaks"
QT_MOC_LITERAL(29, 666, 18), // "show_peaks_clicked"
QT_MOC_LITERAL(30, 685, 12), // "add_max_peak"
QT_MOC_LITERAL(31, 698, 12), // "auto_clicked"
QT_MOC_LITERAL(32, 711, 17), // "full_auto_clicked"
QT_MOC_LITERAL(33, 729, 37), // "radio_General_use_combination..."
QT_MOC_LITERAL(34, 767, 37), // "radio_General_use_independent..."
QT_MOC_LITERAL(35, 805, 35), // "radio_General_use_all_peaks_c..."
QT_MOC_LITERAL(36, 841, 40), // "radio_General_use_selected_pe..."
QT_MOC_LITERAL(37, 882, 30), // "skipp_peaks_resolution_changed"
QT_MOC_LITERAL(38, 913, 22), // "main_save_data_clicked"
QT_MOC_LITERAL(39, 936, 21), // "main_save_pdf_clicked"
QT_MOC_LITERAL(40, 958, 15), // "set_const_xAxis"
QT_MOC_LITERAL(41, 974, 17), // "set_rescale_xAxis"
QT_MOC_LITERAL(42, 992, 12), // "trf_save_trf"
QT_MOC_LITERAL(43, 1005, 26), // "simulation_spinBox_changed"
QT_MOC_LITERAL(44, 1032, 25), // "simulation_slider_changed"
QT_MOC_LITERAL(45, 1058, 21), // "pushB_fitsin_function"
QT_MOC_LITERAL(46, 1080, 15), // "fitsin_function"
QT_MOC_LITERAL(47, 1096, 13), // "get_residuals"
QT_MOC_LITERAL(48, 1110, 16), // "add_fitted_curve"
QT_MOC_LITERAL(49, 1127, 30), // "fitsin_only_linear_thread_init"
QT_MOC_LITERAL(50, 1158, 21), // "check_for_combination"
QT_MOC_LITERAL(51, 1180, 27), // "info_table_selectionChanged"
QT_MOC_LITERAL(52, 1208, 29), // "spinbox_comb_res_valueChanged"
QT_MOC_LITERAL(53, 1238, 24), // "info_table_doubleclicked"
QT_MOC_LITERAL(54, 1263, 17), // "table_cellChanged"
QT_MOC_LITERAL(55, 1281, 23), // "horizontalHeaderClicked"
QT_MOC_LITERAL(56, 1305, 15), // "sort_info_table"
QT_MOC_LITERAL(57, 1321, 18), // "table_back_clicked"
QT_MOC_LITERAL(58, 1340, 21), // "table_forward_clicked"
QT_MOC_LITERAL(59, 1362, 18), // "selectionColumn_ud"
QT_MOC_LITERAL(60, 1381, 4), // "icol"
QT_MOC_LITERAL(61, 1386, 11), // "resizeEvent"
QT_MOC_LITERAL(62, 1398, 13), // "QResizeEvent*"
QT_MOC_LITERAL(63, 1412, 5), // "event"
QT_MOC_LITERAL(64, 1418, 13), // "keyPressEvent"
QT_MOC_LITERAL(65, 1432, 10), // "QKeyEvent*"
QT_MOC_LITERAL(66, 1443, 15), // "keyReleaseEvent"
QT_MOC_LITERAL(67, 1459, 9), // "open_file"
QT_MOC_LITERAL(68, 1469, 4), // "exit"
QT_MOC_LITERAL(69, 1474, 4), // "help"
QT_MOC_LITERAL(70, 1479, 5), // "reset"
QT_MOC_LITERAL(71, 1485, 7), // "plot_lc"
QT_MOC_LITERAL(72, 1493, 21), // "change_selection_mode"
QT_MOC_LITERAL(73, 1515, 15), // "calculate_trend"
QT_MOC_LITERAL(74, 1531, 27), // "spinbox_no_box_valueChanged"
QT_MOC_LITERAL(75, 1559, 26), // "slider_no_box_valueChanged"
QT_MOC_LITERAL(76, 1586, 21), // "pushB_detrend_clicked"
QT_MOC_LITERAL(77, 1608, 21), // "pushB_restore_clicked"
QT_MOC_LITERAL(78, 1630, 8), // "plot_trf"
QT_MOC_LITERAL(79, 1639, 15), // "calculate_noise"
QT_MOC_LITERAL(80, 1655, 21), // "pushB_calculate_noise"
QT_MOC_LITERAL(81, 1677, 10), // "plot_noise"
QT_MOC_LITERAL(82, 1688, 30), // "spinbox_box_width_valueChanged"
QT_MOC_LITERAL(83, 1719, 9), // "plot_line"
QT_MOC_LITERAL(84, 1729, 1), // "x"
QT_MOC_LITERAL(85, 1731, 13), // "spinbox_setf0"
QT_MOC_LITERAL(86, 1745, 13), // "spinbox_setfe"
QT_MOC_LITERAL(87, 1759, 13), // "spinbox_setdf"
QT_MOC_LITERAL(88, 1773, 33), // "pushB_open_simulation_dialog_..."
QT_MOC_LITERAL(89, 1807, 27), // "pushB_start_simulation_slot"
QT_MOC_LITERAL(90, 1835, 33), // "pushB_start_simulation_slot_g..."
QT_MOC_LITERAL(91, 1869, 35), // "pushB_start_simulation_slot_n..."
QT_MOC_LITERAL(92, 1905, 26), // "table_ContextMenuRequested"
QT_MOC_LITERAL(93, 1932, 22), // "table_selectionChanged"
QT_MOC_LITERAL(94, 1955, 23), // "table_currentItemChange"
QT_MOC_LITERAL(95, 1979, 21), // "table_remove_last_row"
QT_MOC_LITERAL(96, 2001, 21), // "table_remove_this_row"
QT_MOC_LITERAL(97, 2023, 21), // "table_remove_all_rows"
QT_MOC_LITERAL(98, 2045, 15), // "table_save_data"
QT_MOC_LITERAL(99, 2061, 17), // "plot_lc_residuals"
QT_MOC_LITERAL(100, 2079, 34), // "combo_settings_action_NLSF_cl..."
QT_MOC_LITERAL(101, 2114, 15), // "get_trf_fwpeaks"
QT_MOC_LITERAL(102, 2130, 22), // "get_trf_FastFourier_WS"
QT_MOC_LITERAL(103, 2153, 9), // "update_sn"
QT_MOC_LITERAL(104, 2163, 16), // "titleDoubleClick"
QT_MOC_LITERAL(105, 2180, 12), // "QMouseEvent*"
QT_MOC_LITERAL(106, 2193, 20), // "axisLabelDoubleClick"
QT_MOC_LITERAL(107, 2214, 8), // "QCPAxis*"
QT_MOC_LITERAL(108, 2223, 4), // "axis"
QT_MOC_LITERAL(109, 2228, 23), // "QCPAxis::SelectablePart"
QT_MOC_LITERAL(110, 2252, 4), // "part"
QT_MOC_LITERAL(111, 2257, 17), // "legendDoubleClick"
QT_MOC_LITERAL(112, 2275, 10), // "QCPLegend*"
QT_MOC_LITERAL(113, 2286, 6), // "legend"
QT_MOC_LITERAL(114, 2293, 22), // "QCPAbstractLegendItem*"
QT_MOC_LITERAL(115, 2316, 4), // "item"
QT_MOC_LITERAL(116, 2321, 16), // "selectionChanged"
QT_MOC_LITERAL(117, 2338, 10), // "mousePress"
QT_MOC_LITERAL(118, 2349, 16), // "mouseDoubleClick"
QT_MOC_LITERAL(119, 2366, 10), // "mouseWheel"
QT_MOC_LITERAL(120, 2377, 19), // "removeSelectedGraph"
QT_MOC_LITERAL(121, 2397, 15), // "removeAllGraphs"
QT_MOC_LITERAL(122, 2413, 18), // "contextMenuRequest"
QT_MOC_LITERAL(123, 2432, 3), // "pos"
QT_MOC_LITERAL(124, 2436, 10), // "moveLegend"
QT_MOC_LITERAL(125, 2447, 12), // "graphClicked"
QT_MOC_LITERAL(126, 2460, 21), // "QCPAbstractPlottable*"
QT_MOC_LITERAL(127, 2482, 9), // "plottable"
QT_MOC_LITERAL(128, 2492, 9), // "dataIndex"
QT_MOC_LITERAL(129, 2502, 18), // "graphDoubleClicked"
QT_MOC_LITERAL(130, 2521, 11), // "onMouseMove"
QT_MOC_LITERAL(131, 2533, 12), // "mouseRelease"
QT_MOC_LITERAL(132, 2546, 19), // "clear_selected_data"
QT_MOC_LITERAL(133, 2566, 13), // "reverse_xAxis"
QT_MOC_LITERAL(134, 2580, 13), // "reverse_yAxis"
QT_MOC_LITERAL(135, 2594, 7), // "savepdf"
QT_MOC_LITERAL(136, 2602, 18), // "set_logscale_yAxis"
QT_MOC_LITERAL(137, 2621, 18), // "titleDoubleClickLc"
QT_MOC_LITERAL(138, 2640, 22), // "axisLabelDoubleClickLc"
QT_MOC_LITERAL(139, 2663, 19), // "legendDoubleClickLc"
QT_MOC_LITERAL(140, 2683, 18), // "selectionChangedLc"
QT_MOC_LITERAL(141, 2702, 12), // "mousePressLc"
QT_MOC_LITERAL(142, 2715, 18), // "mouseDoubleClickLc"
QT_MOC_LITERAL(143, 2734, 12), // "mouseWheelLc"
QT_MOC_LITERAL(144, 2747, 21), // "removeSelectedGraphLc"
QT_MOC_LITERAL(145, 2769, 17), // "removeAllGraphsLc"
QT_MOC_LITERAL(146, 2787, 20), // "contextMenuRequestLc"
QT_MOC_LITERAL(147, 2808, 12), // "moveLegendLc"
QT_MOC_LITERAL(148, 2821, 14), // "graphClickedLc"
QT_MOC_LITERAL(149, 2836, 20), // "graphDoubleClickedLc"
QT_MOC_LITERAL(150, 2857, 13), // "onMouseMoveLc"
QT_MOC_LITERAL(151, 2871, 14), // "mouseReleaseLc"
QT_MOC_LITERAL(152, 2886, 21), // "clear_selected_dataLc"
QT_MOC_LITERAL(153, 2908, 15), // "reverse_xAxisLc"
QT_MOC_LITERAL(154, 2924, 15), // "reverse_yAxisLc"
QT_MOC_LITERAL(155, 2940, 9), // "savepdfLc"
QT_MOC_LITERAL(156, 2950, 20), // "remove_selected_data"
QT_MOC_LITERAL(157, 2971, 10), // "lc_save_lc"
QT_MOC_LITERAL(158, 2982, 28), // "titleDoubleClickLc_residuals"
QT_MOC_LITERAL(159, 3011, 32), // "axisLabelDoubleClickLc_residuals"
QT_MOC_LITERAL(160, 3044, 29), // "legendDoubleClickLc_residuals"
QT_MOC_LITERAL(161, 3074, 28), // "selectionChangedLc_residuals"
QT_MOC_LITERAL(162, 3103, 22), // "mousePressLc_residuals"
QT_MOC_LITERAL(163, 3126, 28), // "mouseDoubleClickLc_residuals"
QT_MOC_LITERAL(164, 3155, 22), // "mouseWheelLc_residuals"
QT_MOC_LITERAL(165, 3178, 31), // "removeSelectedGraphLc_residuals"
QT_MOC_LITERAL(166, 3210, 27), // "removeAllGraphsLc_residuals"
QT_MOC_LITERAL(167, 3238, 30), // "contextMenuRequestLc_residuals"
QT_MOC_LITERAL(168, 3269, 22), // "moveLegendLc_residuals"
QT_MOC_LITERAL(169, 3292, 24), // "graphClickedLc_residuals"
QT_MOC_LITERAL(170, 3317, 30), // "graphDoubleClickedLc_residuals"
QT_MOC_LITERAL(171, 3348, 23), // "onMouseMoveLc_residuals"
QT_MOC_LITERAL(172, 3372, 24), // "mouseReleaseLc_residuals"
QT_MOC_LITERAL(173, 3397, 31), // "clear_selected_dataLc_residuals"
QT_MOC_LITERAL(174, 3429, 25), // "reverse_xAxisLc_residuals"
QT_MOC_LITERAL(175, 3455, 25), // "reverse_yAxisLc_residuals"
QT_MOC_LITERAL(176, 3481, 19), // "savepdfLc_residuals"
QT_MOC_LITERAL(177, 3501, 32), // "remove_selected_dataLc_residuals"
QT_MOC_LITERAL(178, 3534, 16), // "resid_save_resid"
QT_MOC_LITERAL(179, 3551, 24), // "titleDoubleClickLc_phase"
QT_MOC_LITERAL(180, 3576, 28), // "axisLabelDoubleClickLc_phase"
QT_MOC_LITERAL(181, 3605, 25), // "legendDoubleClickLc_phase"
QT_MOC_LITERAL(182, 3631, 24), // "selectionChangedLc_phase"
QT_MOC_LITERAL(183, 3656, 18), // "mousePressLc_phase"
QT_MOC_LITERAL(184, 3675, 24), // "mouseDoubleClickLc_phase"
QT_MOC_LITERAL(185, 3700, 18), // "mouseWheelLc_phase"
QT_MOC_LITERAL(186, 3719, 27), // "removeSelectedGraphLc_phase"
QT_MOC_LITERAL(187, 3747, 23), // "removeAllGraphsLc_phase"
QT_MOC_LITERAL(188, 3771, 26), // "contextMenuRequestLc_phase"
QT_MOC_LITERAL(189, 3798, 18), // "moveLegendLc_phase"
QT_MOC_LITERAL(190, 3817, 20), // "graphClickedLc_phase"
QT_MOC_LITERAL(191, 3838, 26), // "graphDoubleClickedLc_phase"
QT_MOC_LITERAL(192, 3865, 19), // "onMouseMoveLc_phase"
QT_MOC_LITERAL(193, 3885, 20), // "mouseReleaseLc_phase"
QT_MOC_LITERAL(194, 3906, 27), // "clear_selected_dataLc_phase"
QT_MOC_LITERAL(195, 3934, 21), // "reverse_xAxisLc_phase"
QT_MOC_LITERAL(196, 3956, 21), // "reverse_yAxisLc_phase"
QT_MOC_LITERAL(197, 3978, 15), // "savepdfLc_phase"
QT_MOC_LITERAL(198, 3994, 28), // "remove_selected_dataLc_phase"
QT_MOC_LITERAL(199, 4023, 16), // "phase_save_phase"
QT_MOC_LITERAL(200, 4040, 27), // "titleDoubleClick_simulation"
QT_MOC_LITERAL(201, 4068, 31), // "axisLabelDoubleClick_simulation"
QT_MOC_LITERAL(202, 4100, 28), // "legendDoubleClick_simulation"
QT_MOC_LITERAL(203, 4129, 27), // "selectionChanged_simulation"
QT_MOC_LITERAL(204, 4157, 21), // "mousePress_simulation"
QT_MOC_LITERAL(205, 4179, 27), // "mouseDoubleClick_simulation"
QT_MOC_LITERAL(206, 4207, 21), // "mouseWheel_simulation"
QT_MOC_LITERAL(207, 4229, 26), // "removeAllGraphs_simulation"
QT_MOC_LITERAL(208, 4256, 29), // "contextMenuRequest_simulation"
QT_MOC_LITERAL(209, 4286, 21), // "moveLegend_simulation"
QT_MOC_LITERAL(210, 4308, 23), // "graphClicked_simulation"
QT_MOC_LITERAL(211, 4332, 29), // "graphDoubleClicked_simulation"
QT_MOC_LITERAL(212, 4362, 22), // "onMouseMove_simulation"
QT_MOC_LITERAL(213, 4385, 23), // "mouseRelease_simulation"
QT_MOC_LITERAL(214, 4409, 24), // "reverse_xAxis_simulation"
QT_MOC_LITERAL(215, 4434, 24), // "reverse_yAxis_simulation"
QT_MOC_LITERAL(216, 4459, 18), // "savepdf_simulation"
QT_MOC_LITERAL(217, 4478, 15) // "simulation_save"

    },
    "MainWindow\0operate\0\0operate_linear\0"
    "handleResults\0Worker_data_out\0"
    "handleResults_linear\0Worker_data_out_linear\0"
    "fitsin_nonlinear_thread_init\0"
    "fitsin_linear_thread_init\0show_phase_clicked\0"
    "get_phase_diagram\0data_spectral_window_clicked\0"
    "simulation_analyse\0"
    "combo_settings_action_General_clicked\0"
    "spinB_General_nfreq_changed\0"
    "spinB_General_n_s_changed\0"
    "spinB_General_n_h_changed\0"
    "spinB_General_n_c2_1_changed\0"
    "spinB_General_n_c2_2_changed\0"
    "spinB_General_n_c3_1_changed\0"
    "spinB_General_n_c3_2_changed\0"
    "spinB_General_n_c3_3_changed\0"
    "spinB_NLSF_maxiter_changed\0"
    "radio_General_use_h_peaks_changed\0"
    "radio_General_use_h_SN_changed\0"
    "spinB_General_auto_stop_crit_SN_changed\0"
    "show_peaks\0hide_peaks\0show_peaks_clicked\0"
    "add_max_peak\0auto_clicked\0full_auto_clicked\0"
    "radio_General_use_combination_changed\0"
    "radio_General_use_independent_changed\0"
    "radio_General_use_all_peaks_changed\0"
    "radio_General_use_selected_peaks_changed\0"
    "skipp_peaks_resolution_changed\0"
    "main_save_data_clicked\0main_save_pdf_clicked\0"
    "set_const_xAxis\0set_rescale_xAxis\0"
    "trf_save_trf\0simulation_spinBox_changed\0"
    "simulation_slider_changed\0"
    "pushB_fitsin_function\0fitsin_function\0"
    "get_residuals\0add_fitted_curve\0"
    "fitsin_only_linear_thread_init\0"
    "check_for_combination\0info_table_selectionChanged\0"
    "spinbox_comb_res_valueChanged\0"
    "info_table_doubleclicked\0table_cellChanged\0"
    "horizontalHeaderClicked\0sort_info_table\0"
    "table_back_clicked\0table_forward_clicked\0"
    "selectionColumn_ud\0icol\0resizeEvent\0"
    "QResizeEvent*\0event\0keyPressEvent\0"
    "QKeyEvent*\0keyReleaseEvent\0open_file\0"
    "exit\0help\0reset\0plot_lc\0change_selection_mode\0"
    "calculate_trend\0spinbox_no_box_valueChanged\0"
    "slider_no_box_valueChanged\0"
    "pushB_detrend_clicked\0pushB_restore_clicked\0"
    "plot_trf\0calculate_noise\0pushB_calculate_noise\0"
    "plot_noise\0spinbox_box_width_valueChanged\0"
    "plot_line\0x\0spinbox_setf0\0spinbox_setfe\0"
    "spinbox_setdf\0pushB_open_simulation_dialog_slot\0"
    "pushB_start_simulation_slot\0"
    "pushB_start_simulation_slot_graph\0"
    "pushB_start_simulation_slot_nograph\0"
    "table_ContextMenuRequested\0"
    "table_selectionChanged\0table_currentItemChange\0"
    "table_remove_last_row\0table_remove_this_row\0"
    "table_remove_all_rows\0table_save_data\0"
    "plot_lc_residuals\0combo_settings_action_NLSF_clicked\0"
    "get_trf_fwpeaks\0get_trf_FastFourier_WS\0"
    "update_sn\0titleDoubleClick\0QMouseEvent*\0"
    "axisLabelDoubleClick\0QCPAxis*\0axis\0"
    "QCPAxis::SelectablePart\0part\0"
    "legendDoubleClick\0QCPLegend*\0legend\0"
    "QCPAbstractLegendItem*\0item\0"
    "selectionChanged\0mousePress\0"
    "mouseDoubleClick\0mouseWheel\0"
    "removeSelectedGraph\0removeAllGraphs\0"
    "contextMenuRequest\0pos\0moveLegend\0"
    "graphClicked\0QCPAbstractPlottable*\0"
    "plottable\0dataIndex\0graphDoubleClicked\0"
    "onMouseMove\0mouseRelease\0clear_selected_data\0"
    "reverse_xAxis\0reverse_yAxis\0savepdf\0"
    "set_logscale_yAxis\0titleDoubleClickLc\0"
    "axisLabelDoubleClickLc\0legendDoubleClickLc\0"
    "selectionChangedLc\0mousePressLc\0"
    "mouseDoubleClickLc\0mouseWheelLc\0"
    "removeSelectedGraphLc\0removeAllGraphsLc\0"
    "contextMenuRequestLc\0moveLegendLc\0"
    "graphClickedLc\0graphDoubleClickedLc\0"
    "onMouseMoveLc\0mouseReleaseLc\0"
    "clear_selected_dataLc\0reverse_xAxisLc\0"
    "reverse_yAxisLc\0savepdfLc\0"
    "remove_selected_data\0lc_save_lc\0"
    "titleDoubleClickLc_residuals\0"
    "axisLabelDoubleClickLc_residuals\0"
    "legendDoubleClickLc_residuals\0"
    "selectionChangedLc_residuals\0"
    "mousePressLc_residuals\0"
    "mouseDoubleClickLc_residuals\0"
    "mouseWheelLc_residuals\0"
    "removeSelectedGraphLc_residuals\0"
    "removeAllGraphsLc_residuals\0"
    "contextMenuRequestLc_residuals\0"
    "moveLegendLc_residuals\0graphClickedLc_residuals\0"
    "graphDoubleClickedLc_residuals\0"
    "onMouseMoveLc_residuals\0"
    "mouseReleaseLc_residuals\0"
    "clear_selected_dataLc_residuals\0"
    "reverse_xAxisLc_residuals\0"
    "reverse_yAxisLc_residuals\0savepdfLc_residuals\0"
    "remove_selected_dataLc_residuals\0"
    "resid_save_resid\0titleDoubleClickLc_phase\0"
    "axisLabelDoubleClickLc_phase\0"
    "legendDoubleClickLc_phase\0"
    "selectionChangedLc_phase\0mousePressLc_phase\0"
    "mouseDoubleClickLc_phase\0mouseWheelLc_phase\0"
    "removeSelectedGraphLc_phase\0"
    "removeAllGraphsLc_phase\0"
    "contextMenuRequestLc_phase\0"
    "moveLegendLc_phase\0graphClickedLc_phase\0"
    "graphDoubleClickedLc_phase\0"
    "onMouseMoveLc_phase\0mouseReleaseLc_phase\0"
    "clear_selected_dataLc_phase\0"
    "reverse_xAxisLc_phase\0reverse_yAxisLc_phase\0"
    "savepdfLc_phase\0remove_selected_dataLc_phase\0"
    "phase_save_phase\0titleDoubleClick_simulation\0"
    "axisLabelDoubleClick_simulation\0"
    "legendDoubleClick_simulation\0"
    "selectionChanged_simulation\0"
    "mousePress_simulation\0mouseDoubleClick_simulation\0"
    "mouseWheel_simulation\0removeAllGraphs_simulation\0"
    "contextMenuRequest_simulation\0"
    "moveLegend_simulation\0graphClicked_simulation\0"
    "graphDoubleClicked_simulation\0"
    "onMouseMove_simulation\0mouseRelease_simulation\0"
    "reverse_xAxis_simulation\0"
    "reverse_yAxis_simulation\0savepdf_simulation\0"
    "simulation_save"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
     196,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  994,    2, 0x06 /* Public */,
       3,    1,  997,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1, 1000,    2, 0x0a /* Public */,
       6,    1, 1003,    2, 0x0a /* Public */,
       8,    0, 1006,    2, 0x08 /* Private */,
       9,    0, 1007,    2, 0x08 /* Private */,
      10,    0, 1008,    2, 0x08 /* Private */,
      11,    0, 1009,    2, 0x08 /* Private */,
      12,    0, 1010,    2, 0x08 /* Private */,
      13,    1, 1011,    2, 0x08 /* Private */,
      14,    0, 1014,    2, 0x08 /* Private */,
      15,    1, 1015,    2, 0x08 /* Private */,
      16,    1, 1018,    2, 0x08 /* Private */,
      17,    1, 1021,    2, 0x08 /* Private */,
      18,    1, 1024,    2, 0x08 /* Private */,
      19,    1, 1027,    2, 0x08 /* Private */,
      20,    1, 1030,    2, 0x08 /* Private */,
      21,    1, 1033,    2, 0x08 /* Private */,
      22,    1, 1036,    2, 0x08 /* Private */,
      23,    1, 1039,    2, 0x08 /* Private */,
      24,    1, 1042,    2, 0x08 /* Private */,
      25,    1, 1045,    2, 0x08 /* Private */,
      26,    1, 1048,    2, 0x08 /* Private */,
      27,    0, 1051,    2, 0x08 /* Private */,
      28,    0, 1052,    2, 0x08 /* Private */,
      29,    0, 1053,    2, 0x08 /* Private */,
      30,    0, 1054,    2, 0x08 /* Private */,
      31,    0, 1055,    2, 0x08 /* Private */,
      32,    0, 1056,    2, 0x08 /* Private */,
      33,    1, 1057,    2, 0x08 /* Private */,
      34,    1, 1060,    2, 0x08 /* Private */,
      35,    1, 1063,    2, 0x08 /* Private */,
      36,    1, 1066,    2, 0x08 /* Private */,
      37,    1, 1069,    2, 0x08 /* Private */,
      38,    0, 1072,    2, 0x08 /* Private */,
      39,    0, 1073,    2, 0x08 /* Private */,
      40,    0, 1074,    2, 0x08 /* Private */,
      41,    0, 1075,    2, 0x08 /* Private */,
      42,    0, 1076,    2, 0x08 /* Private */,
      43,    1, 1077,    2, 0x08 /* Private */,
      44,    1, 1080,    2, 0x08 /* Private */,
      45,    0, 1083,    2, 0x08 /* Private */,
      46,    0, 1084,    2, 0x08 /* Private */,
      47,    0, 1085,    2, 0x08 /* Private */,
      48,    0, 1086,    2, 0x08 /* Private */,
      49,    0, 1087,    2, 0x08 /* Private */,
      50,    0, 1088,    2, 0x08 /* Private */,
      51,    0, 1089,    2, 0x08 /* Private */,
      52,    1, 1090,    2, 0x08 /* Private */,
      53,    2, 1093,    2, 0x08 /* Private */,
      54,    2, 1098,    2, 0x08 /* Private */,
      55,    1, 1103,    2, 0x08 /* Private */,
      56,    0, 1106,    2, 0x08 /* Private */,
      57,    0, 1107,    2, 0x08 /* Private */,
      58,    0, 1108,    2, 0x08 /* Private */,
      59,    1, 1109,    2, 0x08 /* Private */,
      61,    1, 1112,    2, 0x08 /* Private */,
      64,    1, 1115,    2, 0x08 /* Private */,
      66,    1, 1118,    2, 0x08 /* Private */,
      67,    0, 1121,    2, 0x08 /* Private */,
      68,    0, 1122,    2, 0x08 /* Private */,
      69,    0, 1123,    2, 0x08 /* Private */,
      70,    0, 1124,    2, 0x08 /* Private */,
      71,    0, 1125,    2, 0x08 /* Private */,
      72,    1, 1126,    2, 0x08 /* Private */,
      73,    0, 1129,    2, 0x08 /* Private */,
      74,    1, 1130,    2, 0x08 /* Private */,
      75,    1, 1133,    2, 0x08 /* Private */,
      76,    0, 1136,    2, 0x08 /* Private */,
      77,    0, 1137,    2, 0x08 /* Private */,
      78,    0, 1138,    2, 0x08 /* Private */,
      79,    0, 1139,    2, 0x08 /* Private */,
      80,    0, 1140,    2, 0x08 /* Private */,
      81,    0, 1141,    2, 0x08 /* Private */,
      82,    1, 1142,    2, 0x08 /* Private */,
      83,    1, 1145,    2, 0x08 /* Private */,
      85,    1, 1148,    2, 0x08 /* Private */,
      86,    1, 1151,    2, 0x08 /* Private */,
      87,    1, 1154,    2, 0x08 /* Private */,
      88,    0, 1157,    2, 0x08 /* Private */,
      89,    0, 1158,    2, 0x08 /* Private */,
      90,    0, 1159,    2, 0x08 /* Private */,
      91,    0, 1160,    2, 0x08 /* Private */,
      92,    1, 1161,    2, 0x08 /* Private */,
      93,    0, 1164,    2, 0x08 /* Private */,
      94,    4, 1165,    2, 0x08 /* Private */,
      95,    0, 1174,    2, 0x08 /* Private */,
      96,    0, 1175,    2, 0x08 /* Private */,
      97,    0, 1176,    2, 0x08 /* Private */,
      98,    0, 1177,    2, 0x08 /* Private */,
      99,    0, 1178,    2, 0x08 /* Private */,
     100,    0, 1179,    2, 0x08 /* Private */,
     101,    0, 1180,    2, 0x08 /* Private */,
     102,    0, 1181,    2, 0x08 /* Private */,
     103,    0, 1182,    2, 0x08 /* Private */,
     104,    1, 1183,    2, 0x08 /* Private */,
     106,    2, 1186,    2, 0x08 /* Private */,
     111,    2, 1191,    2, 0x08 /* Private */,
     116,    0, 1196,    2, 0x08 /* Private */,
     117,    1, 1197,    2, 0x08 /* Private */,
     118,    1, 1200,    2, 0x08 /* Private */,
     119,    0, 1203,    2, 0x08 /* Private */,
     120,    0, 1204,    2, 0x08 /* Private */,
     121,    0, 1205,    2, 0x08 /* Private */,
     122,    1, 1206,    2, 0x08 /* Private */,
     124,    0, 1209,    2, 0x08 /* Private */,
     125,    2, 1210,    2, 0x08 /* Private */,
     129,    2, 1215,    2, 0x08 /* Private */,
     130,    1, 1220,    2, 0x08 /* Private */,
     131,    1, 1223,    2, 0x08 /* Private */,
     132,    0, 1226,    2, 0x08 /* Private */,
     133,    0, 1227,    2, 0x08 /* Private */,
     134,    0, 1228,    2, 0x08 /* Private */,
     135,    0, 1229,    2, 0x08 /* Private */,
     136,    0, 1230,    2, 0x08 /* Private */,
     137,    1, 1231,    2, 0x08 /* Private */,
     138,    2, 1234,    2, 0x08 /* Private */,
     139,    2, 1239,    2, 0x08 /* Private */,
     140,    0, 1244,    2, 0x08 /* Private */,
     141,    1, 1245,    2, 0x08 /* Private */,
     142,    1, 1248,    2, 0x08 /* Private */,
     143,    0, 1251,    2, 0x08 /* Private */,
     144,    0, 1252,    2, 0x08 /* Private */,
     145,    0, 1253,    2, 0x08 /* Private */,
     146,    1, 1254,    2, 0x08 /* Private */,
     147,    0, 1257,    2, 0x08 /* Private */,
     148,    2, 1258,    2, 0x08 /* Private */,
     149,    2, 1263,    2, 0x08 /* Private */,
     150,    1, 1268,    2, 0x08 /* Private */,
     151,    1, 1271,    2, 0x08 /* Private */,
     152,    0, 1274,    2, 0x08 /* Private */,
     153,    0, 1275,    2, 0x08 /* Private */,
     154,    0, 1276,    2, 0x08 /* Private */,
     155,    0, 1277,    2, 0x08 /* Private */,
     156,    0, 1278,    2, 0x08 /* Private */,
     157,    0, 1279,    2, 0x08 /* Private */,
     158,    1, 1280,    2, 0x08 /* Private */,
     159,    2, 1283,    2, 0x08 /* Private */,
     160,    2, 1288,    2, 0x08 /* Private */,
     161,    0, 1293,    2, 0x08 /* Private */,
     162,    1, 1294,    2, 0x08 /* Private */,
     163,    1, 1297,    2, 0x08 /* Private */,
     164,    0, 1300,    2, 0x08 /* Private */,
     165,    0, 1301,    2, 0x08 /* Private */,
     166,    0, 1302,    2, 0x08 /* Private */,
     167,    1, 1303,    2, 0x08 /* Private */,
     168,    0, 1306,    2, 0x08 /* Private */,
     169,    2, 1307,    2, 0x08 /* Private */,
     170,    2, 1312,    2, 0x08 /* Private */,
     171,    1, 1317,    2, 0x08 /* Private */,
     172,    1, 1320,    2, 0x08 /* Private */,
     173,    0, 1323,    2, 0x08 /* Private */,
     174,    0, 1324,    2, 0x08 /* Private */,
     175,    0, 1325,    2, 0x08 /* Private */,
     176,    0, 1326,    2, 0x08 /* Private */,
     177,    0, 1327,    2, 0x08 /* Private */,
     178,    0, 1328,    2, 0x08 /* Private */,
     179,    1, 1329,    2, 0x08 /* Private */,
     180,    2, 1332,    2, 0x08 /* Private */,
     181,    2, 1337,    2, 0x08 /* Private */,
     182,    0, 1342,    2, 0x08 /* Private */,
     183,    1, 1343,    2, 0x08 /* Private */,
     184,    1, 1346,    2, 0x08 /* Private */,
     185,    0, 1349,    2, 0x08 /* Private */,
     186,    0, 1350,    2, 0x08 /* Private */,
     187,    0, 1351,    2, 0x08 /* Private */,
     188,    1, 1352,    2, 0x08 /* Private */,
     189,    0, 1355,    2, 0x08 /* Private */,
     190,    2, 1356,    2, 0x08 /* Private */,
     191,    2, 1361,    2, 0x08 /* Private */,
     192,    1, 1366,    2, 0x08 /* Private */,
     193,    1, 1369,    2, 0x08 /* Private */,
     194,    0, 1372,    2, 0x08 /* Private */,
     195,    0, 1373,    2, 0x08 /* Private */,
     196,    0, 1374,    2, 0x08 /* Private */,
     197,    0, 1375,    2, 0x08 /* Private */,
     198,    0, 1376,    2, 0x08 /* Private */,
     199,    0, 1377,    2, 0x08 /* Private */,
     200,    1, 1378,    2, 0x08 /* Private */,
     201,    2, 1381,    2, 0x08 /* Private */,
     202,    2, 1386,    2, 0x08 /* Private */,
     203,    0, 1391,    2, 0x08 /* Private */,
     204,    1, 1392,    2, 0x08 /* Private */,
     205,    1, 1395,    2, 0x08 /* Private */,
     206,    0, 1398,    2, 0x08 /* Private */,
     207,    0, 1399,    2, 0x08 /* Private */,
     208,    1, 1400,    2, 0x08 /* Private */,
     209,    0, 1403,    2, 0x08 /* Private */,
     210,    2, 1404,    2, 0x08 /* Private */,
     211,    2, 1409,    2, 0x08 /* Private */,
     212,    1, 1414,    2, 0x08 /* Private */,
     213,    1, 1417,    2, 0x08 /* Private */,
     214,    0, 1420,    2, 0x08 /* Private */,
     215,    0, 1421,    2, 0x08 /* Private */,
     216,    0, 1422,    2, 0x08 /* Private */,
     217,    0, 1423,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, 0x80000000 | 7,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   60,
    QMetaType::Void, 0x80000000 | 62,   63,
    QMetaType::Void, 0x80000000 | 65,   63,
    QMetaType::Void, 0x80000000 | 65,   63,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,   84,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,    2,    2,    2,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 105,   63,
    QMetaType::Void, 0x80000000 | 107, 0x80000000 | 109,  108,  110,
    QMetaType::Void, 0x80000000 | 112, 0x80000000 | 114,  113,  115,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 105,   63,
    QMetaType::Void, 0x80000000 | 105,   63,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,  123,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 126, QMetaType::Int,  127,  128,
    QMetaType::Void, 0x80000000 | 126, QMetaType::Int,  127,  128,
    QMetaType::Void, 0x80000000 | 105,   63,
    QMetaType::Void, 0x80000000 | 105,   63,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 105,   63,
    QMetaType::Void, 0x80000000 | 107, 0x80000000 | 109,  108,  110,
    QMetaType::Void, 0x80000000 | 112, 0x80000000 | 114,  113,  115,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 105,   63,
    QMetaType::Void, 0x80000000 | 105,   63,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,  123,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 126, QMetaType::Int,  127,  128,
    QMetaType::Void, 0x80000000 | 126, QMetaType::Int,  127,  128,
    QMetaType::Void, 0x80000000 | 105,   63,
    QMetaType::Void, 0x80000000 | 105,   63,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 105,   63,
    QMetaType::Void, 0x80000000 | 107, 0x80000000 | 109,  108,  110,
    QMetaType::Void, 0x80000000 | 112, 0x80000000 | 114,  113,  115,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 105,   63,
    QMetaType::Void, 0x80000000 | 105,   63,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,  123,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 126, QMetaType::Int,  127,  128,
    QMetaType::Void, 0x80000000 | 126, QMetaType::Int,  127,  128,
    QMetaType::Void, 0x80000000 | 105,   63,
    QMetaType::Void, 0x80000000 | 105,   63,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 105,   63,
    QMetaType::Void, 0x80000000 | 107, 0x80000000 | 109,  108,  110,
    QMetaType::Void, 0x80000000 | 112, 0x80000000 | 114,  113,  115,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 105,   63,
    QMetaType::Void, 0x80000000 | 105,   63,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,  123,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 126, QMetaType::Int,  127,  128,
    QMetaType::Void, 0x80000000 | 126, QMetaType::Int,  127,  128,
    QMetaType::Void, 0x80000000 | 105,   63,
    QMetaType::Void, 0x80000000 | 105,   63,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 105,   63,
    QMetaType::Void, 0x80000000 | 107, 0x80000000 | 109,  108,  110,
    QMetaType::Void, 0x80000000 | 112, 0x80000000 | 114,  113,  115,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 105,   63,
    QMetaType::Void, 0x80000000 | 105,   63,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,  123,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 126, QMetaType::Int,  127,  128,
    QMetaType::Void, 0x80000000 | 126, QMetaType::Int,  127,  128,
    QMetaType::Void, 0x80000000 | 105,   63,
    QMetaType::Void, 0x80000000 | 105,   63,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->operate((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->operate_linear((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->handleResults((*reinterpret_cast< const Worker_data_out(*)>(_a[1]))); break;
        case 3: _t->handleResults_linear((*reinterpret_cast< const Worker_data_out_linear(*)>(_a[1]))); break;
        case 4: _t->fitsin_nonlinear_thread_init(); break;
        case 5: _t->fitsin_linear_thread_init(); break;
        case 6: _t->show_phase_clicked(); break;
        case 7: _t->get_phase_diagram(); break;
        case 8: _t->data_spectral_window_clicked(); break;
        case 9: _t->simulation_analyse((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->combo_settings_action_General_clicked(); break;
        case 11: _t->spinB_General_nfreq_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->spinB_General_n_s_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->spinB_General_n_h_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->spinB_General_n_c2_1_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->spinB_General_n_c2_2_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->spinB_General_n_c3_1_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: _t->spinB_General_n_c3_2_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: _t->spinB_General_n_c3_3_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 19: _t->spinB_NLSF_maxiter_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 20: _t->radio_General_use_h_peaks_changed((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 21: _t->radio_General_use_h_SN_changed((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 22: _t->spinB_General_auto_stop_crit_SN_changed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 23: _t->show_peaks(); break;
        case 24: _t->hide_peaks(); break;
        case 25: _t->show_peaks_clicked(); break;
        case 26: _t->add_max_peak(); break;
        case 27: _t->auto_clicked(); break;
        case 28: _t->full_auto_clicked(); break;
        case 29: _t->radio_General_use_combination_changed((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 30: _t->radio_General_use_independent_changed((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 31: _t->radio_General_use_all_peaks_changed((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 32: _t->radio_General_use_selected_peaks_changed((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 33: _t->skipp_peaks_resolution_changed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 34: _t->main_save_data_clicked(); break;
        case 35: _t->main_save_pdf_clicked(); break;
        case 36: _t->set_const_xAxis(); break;
        case 37: _t->set_rescale_xAxis(); break;
        case 38: _t->trf_save_trf(); break;
        case 39: _t->simulation_spinBox_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 40: _t->simulation_slider_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 41: _t->pushB_fitsin_function(); break;
        case 42: _t->fitsin_function(); break;
        case 43: _t->get_residuals(); break;
        case 44: _t->add_fitted_curve(); break;
        case 45: _t->fitsin_only_linear_thread_init(); break;
        case 46: _t->check_for_combination(); break;
        case 47: _t->info_table_selectionChanged(); break;
        case 48: _t->spinbox_comb_res_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 49: _t->info_table_doubleclicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 50: _t->table_cellChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 51: _t->horizontalHeaderClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 52: _t->sort_info_table(); break;
        case 53: _t->table_back_clicked(); break;
        case 54: _t->table_forward_clicked(); break;
        case 55: _t->selectionColumn_ud((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 56: _t->resizeEvent((*reinterpret_cast< QResizeEvent*(*)>(_a[1]))); break;
        case 57: _t->keyPressEvent((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 58: _t->keyReleaseEvent((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 59: _t->open_file(); break;
        case 60: _t->exit(); break;
        case 61: _t->help(); break;
        case 62: _t->reset(); break;
        case 63: _t->plot_lc(); break;
        case 64: _t->change_selection_mode((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 65: _t->calculate_trend(); break;
        case 66: _t->spinbox_no_box_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 67: _t->slider_no_box_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 68: _t->pushB_detrend_clicked(); break;
        case 69: _t->pushB_restore_clicked(); break;
        case 70: _t->plot_trf(); break;
        case 71: _t->calculate_noise(); break;
        case 72: _t->pushB_calculate_noise(); break;
        case 73: _t->plot_noise(); break;
        case 74: _t->spinbox_box_width_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 75: _t->plot_line((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 76: _t->spinbox_setf0((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 77: _t->spinbox_setfe((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 78: _t->spinbox_setdf((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 79: _t->pushB_open_simulation_dialog_slot(); break;
        case 80: _t->pushB_start_simulation_slot(); break;
        case 81: _t->pushB_start_simulation_slot_graph(); break;
        case 82: _t->pushB_start_simulation_slot_nograph(); break;
        case 83: _t->table_ContextMenuRequested((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 84: _t->table_selectionChanged(); break;
        case 85: _t->table_currentItemChange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 86: _t->table_remove_last_row(); break;
        case 87: _t->table_remove_this_row(); break;
        case 88: _t->table_remove_all_rows(); break;
        case 89: _t->table_save_data(); break;
        case 90: _t->plot_lc_residuals(); break;
        case 91: _t->combo_settings_action_NLSF_clicked(); break;
        case 92: _t->get_trf_fwpeaks(); break;
        case 93: _t->get_trf_FastFourier_WS(); break;
        case 94: _t->update_sn(); break;
        case 95: _t->titleDoubleClick((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 96: _t->axisLabelDoubleClick((*reinterpret_cast< QCPAxis*(*)>(_a[1])),(*reinterpret_cast< QCPAxis::SelectablePart(*)>(_a[2]))); break;
        case 97: _t->legendDoubleClick((*reinterpret_cast< QCPLegend*(*)>(_a[1])),(*reinterpret_cast< QCPAbstractLegendItem*(*)>(_a[2]))); break;
        case 98: _t->selectionChanged(); break;
        case 99: _t->mousePress((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 100: _t->mouseDoubleClick((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 101: _t->mouseWheel(); break;
        case 102: _t->removeSelectedGraph(); break;
        case 103: _t->removeAllGraphs(); break;
        case 104: _t->contextMenuRequest((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 105: _t->moveLegend(); break;
        case 106: _t->graphClicked((*reinterpret_cast< QCPAbstractPlottable*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 107: _t->graphDoubleClicked((*reinterpret_cast< QCPAbstractPlottable*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 108: _t->onMouseMove((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 109: _t->mouseRelease((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 110: _t->clear_selected_data(); break;
        case 111: _t->reverse_xAxis(); break;
        case 112: _t->reverse_yAxis(); break;
        case 113: _t->savepdf(); break;
        case 114: _t->set_logscale_yAxis(); break;
        case 115: _t->titleDoubleClickLc((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 116: _t->axisLabelDoubleClickLc((*reinterpret_cast< QCPAxis*(*)>(_a[1])),(*reinterpret_cast< QCPAxis::SelectablePart(*)>(_a[2]))); break;
        case 117: _t->legendDoubleClickLc((*reinterpret_cast< QCPLegend*(*)>(_a[1])),(*reinterpret_cast< QCPAbstractLegendItem*(*)>(_a[2]))); break;
        case 118: _t->selectionChangedLc(); break;
        case 119: _t->mousePressLc((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 120: _t->mouseDoubleClickLc((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 121: _t->mouseWheelLc(); break;
        case 122: _t->removeSelectedGraphLc(); break;
        case 123: _t->removeAllGraphsLc(); break;
        case 124: _t->contextMenuRequestLc((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 125: _t->moveLegendLc(); break;
        case 126: _t->graphClickedLc((*reinterpret_cast< QCPAbstractPlottable*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 127: _t->graphDoubleClickedLc((*reinterpret_cast< QCPAbstractPlottable*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 128: _t->onMouseMoveLc((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 129: _t->mouseReleaseLc((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 130: _t->clear_selected_dataLc(); break;
        case 131: _t->reverse_xAxisLc(); break;
        case 132: _t->reverse_yAxisLc(); break;
        case 133: _t->savepdfLc(); break;
        case 134: _t->remove_selected_data(); break;
        case 135: _t->lc_save_lc(); break;
        case 136: _t->titleDoubleClickLc_residuals((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 137: _t->axisLabelDoubleClickLc_residuals((*reinterpret_cast< QCPAxis*(*)>(_a[1])),(*reinterpret_cast< QCPAxis::SelectablePart(*)>(_a[2]))); break;
        case 138: _t->legendDoubleClickLc_residuals((*reinterpret_cast< QCPLegend*(*)>(_a[1])),(*reinterpret_cast< QCPAbstractLegendItem*(*)>(_a[2]))); break;
        case 139: _t->selectionChangedLc_residuals(); break;
        case 140: _t->mousePressLc_residuals((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 141: _t->mouseDoubleClickLc_residuals((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 142: _t->mouseWheelLc_residuals(); break;
        case 143: _t->removeSelectedGraphLc_residuals(); break;
        case 144: _t->removeAllGraphsLc_residuals(); break;
        case 145: _t->contextMenuRequestLc_residuals((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 146: _t->moveLegendLc_residuals(); break;
        case 147: _t->graphClickedLc_residuals((*reinterpret_cast< QCPAbstractPlottable*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 148: _t->graphDoubleClickedLc_residuals((*reinterpret_cast< QCPAbstractPlottable*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 149: _t->onMouseMoveLc_residuals((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 150: _t->mouseReleaseLc_residuals((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 151: _t->clear_selected_dataLc_residuals(); break;
        case 152: _t->reverse_xAxisLc_residuals(); break;
        case 153: _t->reverse_yAxisLc_residuals(); break;
        case 154: _t->savepdfLc_residuals(); break;
        case 155: _t->remove_selected_dataLc_residuals(); break;
        case 156: _t->resid_save_resid(); break;
        case 157: _t->titleDoubleClickLc_phase((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 158: _t->axisLabelDoubleClickLc_phase((*reinterpret_cast< QCPAxis*(*)>(_a[1])),(*reinterpret_cast< QCPAxis::SelectablePart(*)>(_a[2]))); break;
        case 159: _t->legendDoubleClickLc_phase((*reinterpret_cast< QCPLegend*(*)>(_a[1])),(*reinterpret_cast< QCPAbstractLegendItem*(*)>(_a[2]))); break;
        case 160: _t->selectionChangedLc_phase(); break;
        case 161: _t->mousePressLc_phase((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 162: _t->mouseDoubleClickLc_phase((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 163: _t->mouseWheelLc_phase(); break;
        case 164: _t->removeSelectedGraphLc_phase(); break;
        case 165: _t->removeAllGraphsLc_phase(); break;
        case 166: _t->contextMenuRequestLc_phase((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 167: _t->moveLegendLc_phase(); break;
        case 168: _t->graphClickedLc_phase((*reinterpret_cast< QCPAbstractPlottable*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 169: _t->graphDoubleClickedLc_phase((*reinterpret_cast< QCPAbstractPlottable*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 170: _t->onMouseMoveLc_phase((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 171: _t->mouseReleaseLc_phase((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 172: _t->clear_selected_dataLc_phase(); break;
        case 173: _t->reverse_xAxisLc_phase(); break;
        case 174: _t->reverse_yAxisLc_phase(); break;
        case 175: _t->savepdfLc_phase(); break;
        case 176: _t->remove_selected_dataLc_phase(); break;
        case 177: _t->phase_save_phase(); break;
        case 178: _t->titleDoubleClick_simulation((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 179: _t->axisLabelDoubleClick_simulation((*reinterpret_cast< QCPAxis*(*)>(_a[1])),(*reinterpret_cast< QCPAxis::SelectablePart(*)>(_a[2]))); break;
        case 180: _t->legendDoubleClick_simulation((*reinterpret_cast< QCPLegend*(*)>(_a[1])),(*reinterpret_cast< QCPAbstractLegendItem*(*)>(_a[2]))); break;
        case 181: _t->selectionChanged_simulation(); break;
        case 182: _t->mousePress_simulation((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 183: _t->mouseDoubleClick_simulation((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 184: _t->mouseWheel_simulation(); break;
        case 185: _t->removeAllGraphs_simulation(); break;
        case 186: _t->contextMenuRequest_simulation((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 187: _t->moveLegend_simulation(); break;
        case 188: _t->graphClicked_simulation((*reinterpret_cast< QCPAbstractPlottable*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 189: _t->graphDoubleClicked_simulation((*reinterpret_cast< QCPAbstractPlottable*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 190: _t->onMouseMove_simulation((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 191: _t->mouseRelease_simulation((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 192: _t->reverse_xAxis_simulation(); break;
        case 193: _t->reverse_yAxis_simulation(); break;
        case 194: _t->savepdf_simulation(); break;
        case 195: _t->simulation_save(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Worker_data_out >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Worker_data_out_linear >(); break;
            }
            break;
        case 96:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPAxis* >(); break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPAxis::SelectablePart >(); break;
            }
            break;
        case 97:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPAbstractLegendItem* >(); break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPLegend* >(); break;
            }
            break;
        case 106:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPAbstractPlottable* >(); break;
            }
            break;
        case 107:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPAbstractPlottable* >(); break;
            }
            break;
        case 116:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPAxis* >(); break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPAxis::SelectablePart >(); break;
            }
            break;
        case 117:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPAbstractLegendItem* >(); break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPLegend* >(); break;
            }
            break;
        case 126:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPAbstractPlottable* >(); break;
            }
            break;
        case 127:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPAbstractPlottable* >(); break;
            }
            break;
        case 137:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPAxis* >(); break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPAxis::SelectablePart >(); break;
            }
            break;
        case 138:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPAbstractLegendItem* >(); break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPLegend* >(); break;
            }
            break;
        case 147:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPAbstractPlottable* >(); break;
            }
            break;
        case 148:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPAbstractPlottable* >(); break;
            }
            break;
        case 158:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPAxis* >(); break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPAxis::SelectablePart >(); break;
            }
            break;
        case 159:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPAbstractLegendItem* >(); break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPLegend* >(); break;
            }
            break;
        case 168:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPAbstractPlottable* >(); break;
            }
            break;
        case 169:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPAbstractPlottable* >(); break;
            }
            break;
        case 179:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPAxis* >(); break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPAxis::SelectablePart >(); break;
            }
            break;
        case 180:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPAbstractLegendItem* >(); break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPLegend* >(); break;
            }
            break;
        case 188:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPAbstractPlottable* >(); break;
            }
            break;
        case 189:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPAbstractPlottable* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainWindow::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::operate)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::operate_linear)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 196)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 196;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 196)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 196;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::operate(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::operate_linear(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
