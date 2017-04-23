QT += widgets

TARGET = hra2017

HEADERS     += QBoard.h \
            ./board.h \
            ./card.h \
            ./card_deck.h \
            ./card_stack.h \
            ./command.h \
            ./game.h \
            ./move.h

RESOURCES   = solitaire.qrc
SOURCES     += QBoard.cpp \
              main.cpp \
            ./board.cc \
            ./card.cc \
            ./card_deck.cc \
            ./card_stack.cc \
            ./command.cc \
            ./game.cc \
            ./move.cc

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/draganddrop/draggableicons
INSTALLS += target

DISTFILES +=
