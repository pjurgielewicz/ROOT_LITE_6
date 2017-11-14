######################################################################
# Automatically generated by qmake (1.07a) Mon Jun 20 18:27:55 2005
######################################################################


TEMPLATE = lib

CONFIG += thread dll
CONFIG += create_prl

TARGET = QtRoot

QTROOTSYSPATHINSTALL = $(QTROOTSYSDIR)

isEmpty(DESTDIR) {
  DESTDIR=..
}
isEmpty(QTROOTSYSPATHINSTALL) {
  QTROOTSYSPATHINSTALL = $$DESTDIR
}

QTROOTSYSDIR=$$DESTDIR

GQTDIRI   = ../qt/inc

QTROOTDIRS   = src
QTROOTDIRI   = inc

DEPENDPATH += $$QTROOTDIRI $$QTROOTDIRS
INCLUDEPATH +=  $$QTROOTDIRI $$GQTDIRI

unix {
  LIBS += -L..
}
# Input
HEADERS += $$QTROOTDIRI/TQtRootGuiFactory.h
SOURCES += $$QTROOTDIRS/TQtRootGuiFactory.cxx

CREATE_ROOT_DICT_FOR_CLASSES  = $$HEADERS $$QTROOTDIRI/LinkDef.h

!exists ($$GQTDIRI/rootcintrule.pri){
     message "The rootcintrule.pri was not found"
}
exists ($$GQTDIRI/rootcintrule.pri){
    include ($$GQTDIRI/rootcintrule.pri)
}

mac {
    !exists ($$GQTDIRI/rootlibs.pri){
        message "The rootlibs.pri was not found"
    }
    exists ($$GQTDIRI/rootlibs.pri){
       include ($$GQTDIRI/rootlibs.pri)
    }
#    LIBS -= -lGQt
}

headerfiles.path   = $$QTROOTSYSPATHINSTALL/include
headerfiles.files = $$QTROOTDIRI/*.*
headerfiles.files -= $$QTROOTDIRI/LinkDef.h
target.path = $$QTROOTSYSPATHINSTALL/lib

INSTALLS += headerfiles target


DISTFILES += LICENSE.QPL Module.mk

unix {
#  -- working directory

  ROOTCINT_DIR = .rootcint
  UI_DIR = .ui
  MOC_DIR = .moc
  OBJECTS_DIR = .obj

}
#The following line was inserted by qt3to4
QT += qt3support
