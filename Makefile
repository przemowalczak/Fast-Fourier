#############################################################################
# Makefile for building: Fast_Fourier
# Generated by qmake (3.1) (Qt 5.15.3)
# Project:  Fast_Fourier.pro
# Template: app
# Command: /usr/lib/qt5/bin/qmake -o Makefile Fast_Fourier.pro -spec linux-g++ CONFIG+=debug
#############################################################################

MAKEFILE      = Makefile

EQ            = =

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_PRINTSUPPORT_LIB -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB
CFLAGS        = -pipe -g -Wall -Wextra -D_REENTRANT -fPIC $(DEFINES)
CXXFLAGS      = -pipe -fopenmp -Wall -O3 -finline-functions -march=native -g -std=gnu++11 -Wall -Wextra -D_REENTRANT -fPIC $(DEFINES)
INCPATH       = -I. -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtPrintSupport -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets -I/usr/include/x86_64-linux-gnu/qt5/QtGui -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I. -I. -I/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++
QMAKE         = /usr/lib/qt5/bin/qmake
DEL_FILE      = rm -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p
COPY          = cp -f
COPY_FILE     = cp -f
COPY_DIR      = cp -f -R
INSTALL_FILE  = install -m 644 -p
INSTALL_PROGRAM = install -m 755 -p
INSTALL_DIR   = cp -f -R
QINSTALL      = /usr/lib/qt5/bin/qmake -install qinstall
QINSTALL_PROGRAM = /usr/lib/qt5/bin/qmake -install qinstall -exe
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
TAR           = tar -cf
COMPRESS      = gzip -9f
DISTNAME      = Fast_Fourier1.0.0
DISTDIR = /home/przemo/Documents/c++/QT/Fast_Fourier_v4/.tmp/Fast_Fourier1.0.0
LINK          = g++
LFLAGS        = 
LIBS          = $(SUBLIBS) -lgsl -lgslcblas -pthread -lnfft3 -lfftw3 -lm -lc /usr/lib/x86_64-linux-gnu/libQt5PrintSupport.so /usr/lib/x86_64-linux-gnu/libQt5Widgets.so /usr/lib/x86_64-linux-gnu/libQt5Gui.so /usr/lib/x86_64-linux-gnu/libQt5Core.so -lGL -lpthread   
AR            = ar cqs
RANLIB        = 
SED           = sed
STRIP         = strip

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = MainWindow_slots.cpp \
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
		table.cpp qrc_resource.cpp \
		moc_qcustomplot.cpp \
		moc_mainwindow.cpp \
		moc_simstat.cpp
OBJECTS       = MainWindow_slots.o \
		customPlotLc_residuals_slots.o \
		customPlotLc_slots.o \
		customPlot_phase.o \
		customPlot_simulation.o \
		customPlot_slots.o \
		frequency_manager.o \
		init_customPlot.o \
		init_customPlotLc.o \
		init_customPlotLc_residuals.o \
		box_pwh.o \
		fast_LS.o \
		fwpeaks.o \
		gsl_spline_v3_pwh.o \
		histogram_pwh.o \
		klunkry_pwh.o \
		operators_pwh.o \
		qcustomplot.o \
		read_file_pwh.o \
		sort_pwh.o \
		stat_pwh.o \
		main.o \
		mainwindow.o \
		simstat.o \
		simstst_slots.o \
		table.o \
		qrc_resource.o \
		moc_qcustomplot.o \
		moc_mainwindow.o \
		moc_simstat.o
DIST          = /usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/spec_pre.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/unix.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/linux.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/sanitize.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/gcc-base.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/gcc-base-unix.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/g++-base.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/g++-unix.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/qconfig.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_Attica.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_KAuth.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_KAuthCore.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_KCodecs.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_KConfigCore.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_KConfigGui.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_KConfigWidgets.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_KCoreAddons.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_KGlobalAccel.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_KGuiAddons.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_KI18n.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_KIconThemes.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_KItemViews.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_KWidgetsAddons.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_KWindowSystem.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_KXmlGui.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_accessibility_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_bootstrap_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_concurrent.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_concurrent_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_core.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_core_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_datavisualization.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_dbus.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_dbus_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_devicediscovery_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_edid_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_egl_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_eglfs_kms_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_eglfsdeviceintegration_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_eventdispatcher_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_fb_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_fontdatabase_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_glx_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_gui.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_gui_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_input_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_kms_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_linuxaccessibility_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_network.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_network_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_opengl.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_opengl_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_openglextensions.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_openglextensions_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_platformcompositor_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_printsupport.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_printsupport_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_script.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_scripttools.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_service_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_sql.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_sql_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_testlib.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_testlib_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_theme_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_vulkan_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_widgets.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_widgets_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xcb_qpa_lib_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xkbcommon_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xml.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xml_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qt_functions.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qt_config.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++/qmake.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/spec_post.prf \
		.qmake.stash \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/exclusive_builds.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/toolchain.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/default_pre.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/resolve_config.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/default_post.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/warn_on.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qt.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/resources_functions.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/resources.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/moc.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/unix/opengl.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/uic.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/unix/thread.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qmake_use.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/file_copies.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/testcase_targets.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/exceptions.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/yacc.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/lex.prf \
		Fast_Fourier.pro lib/argv_conf2_pw.hpp \
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
		simstat.h MainWindow_slots.cpp \
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
QMAKE_TARGET  = Fast_Fourier
DESTDIR       = 
TARGET        = Fast_Fourier


first: all
####### Build rules

Fast_Fourier: ui_mainwindow.h ui_simstat.h $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: Fast_Fourier.pro /usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++/qmake.conf /usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/spec_pre.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/unix.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/linux.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/sanitize.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/gcc-base.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/gcc-base-unix.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/g++-base.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/g++-unix.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/qconfig.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_Attica.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_KAuth.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_KAuthCore.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_KCodecs.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_KConfigCore.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_KConfigGui.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_KConfigWidgets.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_KCoreAddons.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_KGlobalAccel.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_KGuiAddons.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_KI18n.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_KIconThemes.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_KItemViews.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_KWidgetsAddons.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_KWindowSystem.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_KXmlGui.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_accessibility_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_bootstrap_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_concurrent.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_concurrent_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_core.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_core_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_datavisualization.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_dbus.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_dbus_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_devicediscovery_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_edid_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_egl_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_eglfs_kms_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_eglfsdeviceintegration_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_eventdispatcher_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_fb_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_fontdatabase_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_glx_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_gui.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_gui_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_input_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_kms_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_linuxaccessibility_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_network.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_network_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_opengl.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_opengl_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_openglextensions.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_openglextensions_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_platformcompositor_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_printsupport.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_printsupport_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_script.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_scripttools.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_service_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_sql.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_sql_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_testlib.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_testlib_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_theme_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_vulkan_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_widgets.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_widgets_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xcb_qpa_lib_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xkbcommon_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xml.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xml_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qt_functions.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qt_config.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++/qmake.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/spec_post.prf \
		.qmake.stash \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/exclusive_builds.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/toolchain.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/default_pre.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/resolve_config.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/default_post.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/warn_on.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qt.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/resources_functions.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/resources.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/moc.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/unix/opengl.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/uic.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/unix/thread.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qmake_use.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/file_copies.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/testcase_targets.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/exceptions.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/yacc.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/lex.prf \
		Fast_Fourier.pro \
		resource.qrc
	$(QMAKE) -o Makefile Fast_Fourier.pro -spec linux-g++ CONFIG+=debug
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/spec_pre.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/unix.conf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/linux.conf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/sanitize.conf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/gcc-base.conf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/gcc-base-unix.conf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/g++-base.conf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/g++-unix.conf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/qconfig.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_Attica.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_KAuth.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_KAuthCore.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_KCodecs.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_KConfigCore.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_KConfigGui.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_KConfigWidgets.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_KCoreAddons.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_KGlobalAccel.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_KGuiAddons.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_KI18n.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_KIconThemes.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_KItemViews.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_KWidgetsAddons.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_KWindowSystem.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_KXmlGui.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_accessibility_support_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_bootstrap_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_concurrent.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_concurrent_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_core.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_core_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_datavisualization.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_dbus.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_dbus_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_devicediscovery_support_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_edid_support_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_egl_support_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_eglfs_kms_support_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_eglfsdeviceintegration_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_eventdispatcher_support_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_fb_support_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_fontdatabase_support_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_glx_support_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_gui.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_gui_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_input_support_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_kms_support_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_linuxaccessibility_support_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_network.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_network_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_opengl.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_opengl_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_openglextensions.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_openglextensions_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_platformcompositor_support_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_printsupport.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_printsupport_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_script.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_scripttools.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_service_support_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_sql.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_sql_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_testlib.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_testlib_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_theme_support_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_vulkan_support_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_widgets.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_widgets_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xcb_qpa_lib_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xkbcommon_support_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xml.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xml_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qt_functions.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qt_config.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++/qmake.conf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/spec_post.prf:
.qmake.stash:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/exclusive_builds.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/toolchain.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/default_pre.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/resolve_config.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/default_post.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/warn_on.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qt.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/resources_functions.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/resources.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/moc.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/unix/opengl.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/uic.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/unix/thread.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qmake_use.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/file_copies.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/testcase_targets.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/exceptions.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/yacc.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/lex.prf:
Fast_Fourier.pro:
resource.qrc:
qmake: FORCE
	@$(QMAKE) -o Makefile Fast_Fourier.pro -spec linux-g++ CONFIG+=debug

qmake_all: FORCE


all: Makefile Fast_Fourier

dist: distdir FORCE
	(cd `dirname $(DISTDIR)` && $(TAR) $(DISTNAME).tar $(DISTNAME) && $(COMPRESS) $(DISTNAME).tar) && $(MOVE) `dirname $(DISTDIR)`/$(DISTNAME).tar.gz . && $(DEL_FILE) -r $(DISTDIR)

distdir: FORCE
	@test -d $(DISTDIR) || mkdir -p $(DISTDIR)
	$(COPY_FILE) --parents $(DIST) $(DISTDIR)/
	$(COPY_FILE) --parents resource.qrc $(DISTDIR)/
	$(COPY_FILE) --parents /usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/data/dummy.cpp $(DISTDIR)/
	$(COPY_FILE) --parents lib/argv_conf2_pw.hpp lib/box_pwh.hpp lib/fast_LS.h lib/fwpeaks.hpp lib/gsl_spline_v3_pwh.hpp lib/histogram_pwh.hpp lib/klunkry_pwh.hpp lib/operators_pwh.hpp lib/qcustomplot.h lib/read_file_pwh.hpp lib/sort_pwh.hpp lib/stat_pwh.hpp mainwindow.h simstat.h $(DISTDIR)/
	$(COPY_FILE) --parents MainWindow_slots.cpp customPlotLc_residuals_slots.cpp customPlotLc_slots.cpp customPlot_phase.cpp customPlot_simulation.cpp customPlot_slots.cpp frequency_manager.cpp init_customPlot.cpp init_customPlotLc.cpp init_customPlotLc_residuals.cpp lib/box_pwh.cpp lib/fast_LS.cpp lib/fwpeaks.cpp lib/gsl_spline_v3_pwh.cpp lib/histogram_pwh.cpp lib/klunkry_pwh.cpp lib/operators_pwh.cpp lib/qcustomplot.cpp lib/read_file_pwh.cpp lib/sort_pwh.cpp lib/stat_pwh.cpp main.cpp mainwindow.cpp simstat.cpp simstst_slots.cpp table.cpp $(DISTDIR)/
	$(COPY_FILE) --parents mainwindow.ui simstat.ui $(DISTDIR)/


clean: compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


distclean: clean 
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) .qmake.stash
	-$(DEL_FILE) Makefile


####### Sub-libraries

mocclean: compiler_moc_header_clean compiler_moc_objc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_objc_header_make_all compiler_moc_source_make_all

check: first

benchmark: first

compiler_rcc_make_all: qrc_resource.cpp
compiler_rcc_clean:
	-$(DEL_FILE) qrc_resource.cpp
qrc_resource.cpp: resource.qrc \
		/usr/lib/qt5/bin/rcc \
		img/ancient_one_by_creativeportobello_deyorca-fullview.jpg \
		img/icons8-opened-folder-48.png \
		img/pdf-icon-16.png \
		img/up-arrow_608336.png \
		img/winfo-icon-exit-16.png \
		img/download-arrow_109609.png \
		img/return.png \
		img/arrow.png
	/usr/lib/qt5/bin/rcc -name resource resource.qrc -o qrc_resource.cpp

compiler_moc_predefs_make_all: moc_predefs.h
compiler_moc_predefs_clean:
	-$(DEL_FILE) moc_predefs.h
moc_predefs.h: /usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/data/dummy.cpp
	g++ -pipe -fopenmp -Wall -O3 -finline-functions -march=native -g -std=gnu++11 -Wall -Wextra -dM -E -o moc_predefs.h /usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/data/dummy.cpp

compiler_moc_header_make_all: moc_qcustomplot.cpp moc_mainwindow.cpp moc_simstat.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_qcustomplot.cpp moc_mainwindow.cpp moc_simstat.cpp
moc_qcustomplot.cpp: lib/qcustomplot.h \
		moc_predefs.h \
		/usr/lib/qt5/bin/moc
	/usr/lib/qt5/bin/moc $(DEFINES) --include /home/przemo/Documents/c++/QT/Fast_Fourier_v4/moc_predefs.h -I/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++ -I/home/przemo/Documents/c++/QT/Fast_Fourier_v4 -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtPrintSupport -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets -I/usr/include/x86_64-linux-gnu/qt5/QtGui -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I/usr/include/c++/11 -I/usr/include/x86_64-linux-gnu/c++/11 -I/usr/include/c++/11/backward -I/usr/lib/gcc/x86_64-linux-gnu/11/include -I/usr/local/include -I/usr/include/x86_64-linux-gnu -I/usr/include lib/qcustomplot.h -o moc_qcustomplot.cpp

moc_mainwindow.cpp: mainwindow.h \
		lib/qcustomplot.h \
		lib/operators_pwh.hpp \
		lib/klunkry_pwh.hpp \
		lib/box_pwh.hpp \
		lib/sort_pwh.hpp \
		lib/histogram_pwh.hpp \
		lib/stat_pwh.hpp \
		lib/read_file_pwh.hpp \
		lib/fwpeaks.hpp \
		lib/gsl_spline_v3_pwh.hpp \
		simstat.h \
		lib/fast_LS.h \
		moc_predefs.h \
		/usr/lib/qt5/bin/moc
	/usr/lib/qt5/bin/moc $(DEFINES) --include /home/przemo/Documents/c++/QT/Fast_Fourier_v4/moc_predefs.h -I/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++ -I/home/przemo/Documents/c++/QT/Fast_Fourier_v4 -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtPrintSupport -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets -I/usr/include/x86_64-linux-gnu/qt5/QtGui -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I/usr/include/c++/11 -I/usr/include/x86_64-linux-gnu/c++/11 -I/usr/include/c++/11/backward -I/usr/lib/gcc/x86_64-linux-gnu/11/include -I/usr/local/include -I/usr/include/x86_64-linux-gnu -I/usr/include mainwindow.h -o moc_mainwindow.cpp

moc_simstat.cpp: simstat.h \
		moc_predefs.h \
		/usr/lib/qt5/bin/moc
	/usr/lib/qt5/bin/moc $(DEFINES) --include /home/przemo/Documents/c++/QT/Fast_Fourier_v4/moc_predefs.h -I/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++ -I/home/przemo/Documents/c++/QT/Fast_Fourier_v4 -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtPrintSupport -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets -I/usr/include/x86_64-linux-gnu/qt5/QtGui -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I/usr/include/c++/11 -I/usr/include/x86_64-linux-gnu/c++/11 -I/usr/include/c++/11/backward -I/usr/lib/gcc/x86_64-linux-gnu/11/include -I/usr/local/include -I/usr/include/x86_64-linux-gnu -I/usr/include simstat.h -o moc_simstat.cpp

compiler_moc_objc_header_make_all:
compiler_moc_objc_header_clean:
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: ui_mainwindow.h ui_simstat.h
compiler_uic_clean:
	-$(DEL_FILE) ui_mainwindow.h ui_simstat.h
ui_mainwindow.h: mainwindow.ui \
		/usr/lib/qt5/bin/uic
	/usr/lib/qt5/bin/uic mainwindow.ui -o ui_mainwindow.h

ui_simstat.h: simstat.ui \
		/usr/lib/qt5/bin/uic
	/usr/lib/qt5/bin/uic simstat.ui -o ui_simstat.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_rcc_clean compiler_moc_predefs_clean compiler_moc_header_clean compiler_uic_clean 

####### Compile

MainWindow_slots.o: MainWindow_slots.cpp mainwindow.h \
		lib/qcustomplot.h \
		lib/operators_pwh.hpp \
		lib/klunkry_pwh.hpp \
		lib/box_pwh.hpp \
		lib/sort_pwh.hpp \
		lib/histogram_pwh.hpp \
		lib/stat_pwh.hpp \
		lib/read_file_pwh.hpp \
		lib/fwpeaks.hpp \
		lib/gsl_spline_v3_pwh.hpp \
		simstat.h \
		lib/fast_LS.h \
		ui_mainwindow.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o MainWindow_slots.o MainWindow_slots.cpp

customPlotLc_residuals_slots.o: customPlotLc_residuals_slots.cpp mainwindow.h \
		lib/qcustomplot.h \
		lib/operators_pwh.hpp \
		lib/klunkry_pwh.hpp \
		lib/box_pwh.hpp \
		lib/sort_pwh.hpp \
		lib/histogram_pwh.hpp \
		lib/stat_pwh.hpp \
		lib/read_file_pwh.hpp \
		lib/fwpeaks.hpp \
		lib/gsl_spline_v3_pwh.hpp \
		simstat.h \
		lib/fast_LS.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o customPlotLc_residuals_slots.o customPlotLc_residuals_slots.cpp

customPlotLc_slots.o: customPlotLc_slots.cpp mainwindow.h \
		lib/qcustomplot.h \
		lib/operators_pwh.hpp \
		lib/klunkry_pwh.hpp \
		lib/box_pwh.hpp \
		lib/sort_pwh.hpp \
		lib/histogram_pwh.hpp \
		lib/stat_pwh.hpp \
		lib/read_file_pwh.hpp \
		lib/fwpeaks.hpp \
		lib/gsl_spline_v3_pwh.hpp \
		simstat.h \
		lib/fast_LS.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o customPlotLc_slots.o customPlotLc_slots.cpp

customPlot_phase.o: customPlot_phase.cpp mainwindow.h \
		lib/qcustomplot.h \
		lib/operators_pwh.hpp \
		lib/klunkry_pwh.hpp \
		lib/box_pwh.hpp \
		lib/sort_pwh.hpp \
		lib/histogram_pwh.hpp \
		lib/stat_pwh.hpp \
		lib/read_file_pwh.hpp \
		lib/fwpeaks.hpp \
		lib/gsl_spline_v3_pwh.hpp \
		simstat.h \
		lib/fast_LS.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o customPlot_phase.o customPlot_phase.cpp

customPlot_simulation.o: customPlot_simulation.cpp mainwindow.h \
		lib/qcustomplot.h \
		lib/operators_pwh.hpp \
		lib/klunkry_pwh.hpp \
		lib/box_pwh.hpp \
		lib/sort_pwh.hpp \
		lib/histogram_pwh.hpp \
		lib/stat_pwh.hpp \
		lib/read_file_pwh.hpp \
		lib/fwpeaks.hpp \
		lib/gsl_spline_v3_pwh.hpp \
		simstat.h \
		lib/fast_LS.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o customPlot_simulation.o customPlot_simulation.cpp

customPlot_slots.o: customPlot_slots.cpp mainwindow.h \
		lib/qcustomplot.h \
		lib/operators_pwh.hpp \
		lib/klunkry_pwh.hpp \
		lib/box_pwh.hpp \
		lib/sort_pwh.hpp \
		lib/histogram_pwh.hpp \
		lib/stat_pwh.hpp \
		lib/read_file_pwh.hpp \
		lib/fwpeaks.hpp \
		lib/gsl_spline_v3_pwh.hpp \
		simstat.h \
		lib/fast_LS.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o customPlot_slots.o customPlot_slots.cpp

frequency_manager.o: frequency_manager.cpp mainwindow.h \
		lib/qcustomplot.h \
		lib/operators_pwh.hpp \
		lib/klunkry_pwh.hpp \
		lib/box_pwh.hpp \
		lib/sort_pwh.hpp \
		lib/histogram_pwh.hpp \
		lib/stat_pwh.hpp \
		lib/read_file_pwh.hpp \
		lib/fwpeaks.hpp \
		lib/gsl_spline_v3_pwh.hpp \
		simstat.h \
		lib/fast_LS.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o frequency_manager.o frequency_manager.cpp

init_customPlot.o: init_customPlot.cpp mainwindow.h \
		lib/qcustomplot.h \
		lib/operators_pwh.hpp \
		lib/klunkry_pwh.hpp \
		lib/box_pwh.hpp \
		lib/sort_pwh.hpp \
		lib/histogram_pwh.hpp \
		lib/stat_pwh.hpp \
		lib/read_file_pwh.hpp \
		lib/fwpeaks.hpp \
		lib/gsl_spline_v3_pwh.hpp \
		simstat.h \
		lib/fast_LS.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o init_customPlot.o init_customPlot.cpp

init_customPlotLc.o: init_customPlotLc.cpp mainwindow.h \
		lib/qcustomplot.h \
		lib/operators_pwh.hpp \
		lib/klunkry_pwh.hpp \
		lib/box_pwh.hpp \
		lib/sort_pwh.hpp \
		lib/histogram_pwh.hpp \
		lib/stat_pwh.hpp \
		lib/read_file_pwh.hpp \
		lib/fwpeaks.hpp \
		lib/gsl_spline_v3_pwh.hpp \
		simstat.h \
		lib/fast_LS.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o init_customPlotLc.o init_customPlotLc.cpp

init_customPlotLc_residuals.o: init_customPlotLc_residuals.cpp mainwindow.h \
		lib/qcustomplot.h \
		lib/operators_pwh.hpp \
		lib/klunkry_pwh.hpp \
		lib/box_pwh.hpp \
		lib/sort_pwh.hpp \
		lib/histogram_pwh.hpp \
		lib/stat_pwh.hpp \
		lib/read_file_pwh.hpp \
		lib/fwpeaks.hpp \
		lib/gsl_spline_v3_pwh.hpp \
		simstat.h \
		lib/fast_LS.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o init_customPlotLc_residuals.o init_customPlotLc_residuals.cpp

box_pwh.o: lib/box_pwh.cpp lib/box_pwh.hpp \
		lib/klunkry_pwh.hpp \
		lib/operators_pwh.hpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o box_pwh.o lib/box_pwh.cpp

fast_LS.o: lib/fast_LS.cpp lib/fast_LS.h \
		lib/sort_pwh.hpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o fast_LS.o lib/fast_LS.cpp

fwpeaks.o: lib/fwpeaks.cpp lib/fwpeaks.hpp \
		lib/operators_pwh.hpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o fwpeaks.o lib/fwpeaks.cpp

gsl_spline_v3_pwh.o: lib/gsl_spline_v3_pwh.cpp lib/gsl_spline_v3_pwh.hpp \
		lib/klunkry_pwh.hpp \
		lib/operators_pwh.hpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o gsl_spline_v3_pwh.o lib/gsl_spline_v3_pwh.cpp

histogram_pwh.o: lib/histogram_pwh.cpp lib/histogram_pwh.hpp \
		lib/operators_pwh.hpp \
		lib/klunkry_pwh.hpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o histogram_pwh.o lib/histogram_pwh.cpp

klunkry_pwh.o: lib/klunkry_pwh.cpp lib/klunkry_pwh.hpp \
		lib/operators_pwh.hpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o klunkry_pwh.o lib/klunkry_pwh.cpp

operators_pwh.o: lib/operators_pwh.cpp lib/operators_pwh.hpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o operators_pwh.o lib/operators_pwh.cpp

qcustomplot.o: lib/qcustomplot.cpp lib/qcustomplot.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o qcustomplot.o lib/qcustomplot.cpp

read_file_pwh.o: lib/read_file_pwh.cpp lib/read_file_pwh.hpp \
		lib/operators_pwh.hpp \
		lib/klunkry_pwh.hpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o read_file_pwh.o lib/read_file_pwh.cpp

sort_pwh.o: lib/sort_pwh.cpp lib/sort_pwh.hpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o sort_pwh.o lib/sort_pwh.cpp

stat_pwh.o: lib/stat_pwh.cpp lib/stat_pwh.hpp \
		lib/operators_pwh.hpp \
		lib/klunkry_pwh.hpp \
		lib/sort_pwh.hpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o stat_pwh.o lib/stat_pwh.cpp

main.o: main.cpp mainwindow.h \
		lib/qcustomplot.h \
		lib/operators_pwh.hpp \
		lib/klunkry_pwh.hpp \
		lib/box_pwh.hpp \
		lib/sort_pwh.hpp \
		lib/histogram_pwh.hpp \
		lib/stat_pwh.hpp \
		lib/read_file_pwh.hpp \
		lib/fwpeaks.hpp \
		lib/gsl_spline_v3_pwh.hpp \
		simstat.h \
		lib/fast_LS.h \
		lib/argv_conf2_pw.hpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

mainwindow.o: mainwindow.cpp mainwindow.h \
		lib/qcustomplot.h \
		lib/operators_pwh.hpp \
		lib/klunkry_pwh.hpp \
		lib/box_pwh.hpp \
		lib/sort_pwh.hpp \
		lib/histogram_pwh.hpp \
		lib/stat_pwh.hpp \
		lib/read_file_pwh.hpp \
		lib/fwpeaks.hpp \
		lib/gsl_spline_v3_pwh.hpp \
		simstat.h \
		lib/fast_LS.h \
		ui_mainwindow.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o mainwindow.o mainwindow.cpp

simstat.o: simstat.cpp simstat.h \
		ui_simstat.h \
		mainwindow.h \
		lib/qcustomplot.h \
		lib/operators_pwh.hpp \
		lib/klunkry_pwh.hpp \
		lib/box_pwh.hpp \
		lib/sort_pwh.hpp \
		lib/histogram_pwh.hpp \
		lib/stat_pwh.hpp \
		lib/read_file_pwh.hpp \
		lib/fwpeaks.hpp \
		lib/gsl_spline_v3_pwh.hpp \
		lib/fast_LS.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o simstat.o simstat.cpp

simstst_slots.o: simstst_slots.cpp simstat.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o simstst_slots.o simstst_slots.cpp

table.o: table.cpp mainwindow.h \
		lib/qcustomplot.h \
		lib/operators_pwh.hpp \
		lib/klunkry_pwh.hpp \
		lib/box_pwh.hpp \
		lib/sort_pwh.hpp \
		lib/histogram_pwh.hpp \
		lib/stat_pwh.hpp \
		lib/read_file_pwh.hpp \
		lib/fwpeaks.hpp \
		lib/gsl_spline_v3_pwh.hpp \
		simstat.h \
		lib/fast_LS.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o table.o table.cpp

qrc_resource.o: qrc_resource.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o qrc_resource.o qrc_resource.cpp

moc_qcustomplot.o: moc_qcustomplot.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_qcustomplot.o moc_qcustomplot.cpp

moc_mainwindow.o: moc_mainwindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_mainwindow.o moc_mainwindow.cpp

moc_simstat.o: moc_simstat.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_simstat.o moc_simstat.cpp

####### Install

install_target: first FORCE
	@test -d $(INSTALL_ROOT)/opt/Fast_Fourier/bin || mkdir -p $(INSTALL_ROOT)/opt/Fast_Fourier/bin
	$(QINSTALL_PROGRAM) $(QMAKE_TARGET) $(INSTALL_ROOT)/opt/Fast_Fourier/bin/$(QMAKE_TARGET)

uninstall_target: FORCE
	-$(DEL_FILE) $(INSTALL_ROOT)/opt/Fast_Fourier/bin/$(QMAKE_TARGET)
	-$(DEL_DIR) $(INSTALL_ROOT)/opt/Fast_Fourier/bin/ 


install: install_target  FORCE

uninstall: uninstall_target  FORCE

FORCE:

