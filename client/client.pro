SOURCES += \
    src/main.cpp \
    src/robocup_ssl_client.cpp \
    src/Robot.cpp \
    src/grSim_Commands.pb.cc \
    src/grSim_Packet.pb.cc \
    src/grSim_Replacement.pb.cc \
    src/messages_robocup_ssl_detection.pb.cc \
    src/messages_robocup_ssl_geometry.pb.cc \
    src/messages_robocup_ssl_refbox_log.pb.cc \
    src/messages_robocup_ssl_wrapper.pb.cc \
    src/ClientMaster.cpp \
    src/Master.cpp \
    src/Ball.cpp \
    src/Command.cpp \
    src/TestCommand.cpp

HEADERS += \
    src/robocup_ssl_client.h \
    src/Robot.h \
    src/grSim_Commands.pb.h \
    src/grSim_Packet.pb.h \
    src/grSim_Replacement.pb.h \
    src/messages_robocup_ssl_detection.pb.h \
    src/messages_robocup_ssl_geometry.pb.h \
    src/messages_robocup_ssl_refbox_log.pb.h \
    src/messages_robocup_ssl_wrapper.pb.h \
    src/ClientMaster.h \
    src/Master.h \
    src/Ball.h \
    src/Command.h \
    src/Team.h \
    src/TestCommand.h

QT += network

unix:!macx: LIBS += -lprotobuf

RESOURCES += \
    res/resources.qrc
