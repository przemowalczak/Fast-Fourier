QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    MainWindow_slots.cpp \
    customPlotLc_residuals_slots.cpp \
    customPlotLc_slots.cpp \
    customPlot_phase.cpp \
    customPlot_simulation.cpp \
    customPlot_slots.cpp \
    frequency_manager.cpp \
    init_customPlot.cpp \
    init_customPlotLc.cpp \
    init_customPlotLc_residuals.cpp \
    lib/box_pwh.cpp \
    lib/fast_LS.cpp \
    lib/fwpeaks.cpp \
    lib/gsl_spline_v3_pwh.cpp \
    lib/histogram_pwh.cpp \
    lib/klunkry_pwh.cpp \
    lib/operators_pwh.cpp \
    lib/qcustomplot.cpp \
    lib/read_file_pwh.cpp \
    lib/sort_pwh.cpp \
    lib/stat_pwh.cpp \
    main.cpp \
    mainwindow.cpp \
    simstat.cpp \
    simstst_slots.cpp \
    table.cpp

HEADERS += \
    lib/argv_conf2_pw.hpp \
    lib/box_pwh.hpp \
    lib/fast_LS.h \
    lib/fwpeaks.hpp \
    lib/gsl_spline_v3_pwh.hpp \
    lib/histogram_pwh.hpp \
    lib/klunkry_pwh.hpp \
    lib/operators_pwh.hpp \
    lib/qcustomplot.h \
    lib/read_file_pwh.hpp \
    lib/sort_pwh.hpp \
    lib/stat_pwh.hpp \
    mainwindow.h \
    simstat.h

FORMS += \
    mainwindow.ui \
    simstat.ui



LIBS +=-lgsl -lgslcblas -pthread  -lnfft3 -lfftw3 -lm -lc

#QMAKE_CXXFLAGS += -O3
#QMAKE_CXXFLAGS += -lgsl -lgslcblas  -Wreorder -pthread -O3

QMAKE_CXXFLAGS += -fopenmp -Wall -O3 -finline-functions   -march=native


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
