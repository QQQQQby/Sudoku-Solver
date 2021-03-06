QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    game/sudoku.cpp \
    ui/sudokuframe.cpp \
    utils/dlx.cpp \
    utils/dlxnode.cpp \
    solver/dfssolver.cpp \
    solver/dlxsolver.cpp \
    ui/mainwindow.cpp \
    ui/digitdialog.cpp

HEADERS += \
    game/sudoku.h \
    ui/sudokuframe.h \
    utils/dlx.h \
    utils/dlxnode.h \
    solver/solver.h \
    solver/dfssolver.h \
    solver/dlxsolver.h \
    ui/mainwindow.h \
    ui/digitdialog.h

FORMS += \
    ui/mainwindow.ui \
    ui/digitdialog.ui

TRANSLATIONS += \
    SudokuSolver_zh_CN.ts

RESOURCES += \
    resources.qrc

RC_FILE += \
    app.rc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
