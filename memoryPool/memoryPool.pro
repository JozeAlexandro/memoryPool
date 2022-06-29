TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.c \
        memoryPoolImpl/linearMemoryPool/src/linearMemoryPool.c

HEADERS += \
    memoryPoolIface.h \
    memoryPoolImpl/linearMemoryPool/h/linearMemoryPool.h \
    memoryPoolImpl/linearMemoryPool/src/linearMemoryPoolP.h
