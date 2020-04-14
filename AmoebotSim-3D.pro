QT += 3dcore 3drender 3dinput 3dquick 3dlogic qml quick 3dquickextras widgets

SOURCES += \
    main/main.cpp \
    core/localparticle.cpp \
    core/particle.cpp \
    core/system.cpp \
    interface/simulator.cpp \
    helper/conversion.cpp \
    helper/randomnumbergenerator.cpp \
    helper/utility.cpp

HEADERS += \
    core/localparticle.h \
    core/node.h \
    core/particle.h \
    core/system.h \
    interface/simulator.h \
    helper/conversion.h \
    helper/randomnumbergenerator.h \
    helper/utility.h

RESOURCES += \
    res/qml.qrc

OTHER_FILES +=
