TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11
SOURCES += \
    acg.cpp \
    acg_node.cpp \
    aga.cpp \
    aga_individual.cpp \
    algorithms.cpp \
    ga.cpp \
    graph.cpp \
    individual.cpp \
    main.cpp \
    mapping_result.cpp \
    nag.cpp \
    nag_node.cpp \
    node.cpp \
    tgff_manager.cpp

OTHER_FILES += \
    tgff \
    LICENSE \
    README.md

HEADERS += \
    acg.h \
    acg_node.h \
    aga.h \
    aga_individual.h \
    algorithms.h \
    ga.h \
    graph.h \
    individual.h \
    mapping_result.h \
    nag.h \
    nag_node.h \
    node.h \
    tgff_manager.h

