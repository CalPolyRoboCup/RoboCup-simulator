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
    src/tests/TestCommand.cpp \
    src/CommandSeries.cpp \
    src/tests/TestCommandSeries.cpp \
    src/PID.cpp \
    src/tests/OrientRobot.cpp \
    src/commands/PassToRobot.cpp \
    src/commands/AimAtRobot.cpp \
    src/MathHelper.cpp \
    src/commands/PassBall.cpp \
    src/commands/SetKicker.cpp \
    src/commands/Delay.cpp \
    src/commands/CatchBall.cpp \
    src/commands/GetOpen.cpp \
    src/commands/QuickPass.cpp \
    src/commands/OneTimerPass.cpp

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
    src/tests/TestCommand.h \
    src/CommandSeries.h \
    src/tests/TestCommandSeries.h \
    src/PID.h \
    src/tests/OrientRobot.h \
    src/commands/PassToRobot.h \
    src/commands/AimAtRobot.h \
    src/MathHelper.h \
    src/commands/PassBall.h \
    src/commands/SetKicker.h \
    src/commands/Delay.h \
    src/commands/CatchBall.h \
    src/commands/GetOpen.h \
    src/commands/QuickPass.h \
    src/commands/OneTimerPass.h

QT += network

unix:!macx: LIBS += -lprotobuf

RESOURCES += \
    res/resources.qrc
