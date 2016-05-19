_pwd = $${PWD}
_pwd ~= s,/,\\,g
_out_pwd = $${OUT_PWD}
_out_pwd ~= s,/,\\,g
_qtdir = $$[QT_INSTALL_BINS]
_qtdir ~= s,/,\\,g

win32:CONFIG(release, debug|release){
    QMAKE_POST_LINK += $$quote(cmd /c copy /y \"$${_qtdir}\\Qt5Core.dll\" \"$${_out_pwd}\\..\\bin\"$$escape_expand(\n\t))
    QMAKE_POST_LINK += $$quote(cmd /c copy /y \"$${_qtdir}\\Qt5Gui.dll\" \"$${_out_pwd}\\..\\bin\"$$escape_expand(\n\t))
    QMAKE_POST_LINK += $$quote(cmd /c copy /y \"$${_qtdir}\\Qt5Widgets.dll\" \"$${_out_pwd}\\..\\bin\"$$escape_expand(\n\t))
    QMAKE_POST_LINK += $$quote(cmd /c copy /y \"$${_qtdir}\\Qt5Test.dll\" \"$${_out_pwd}\\..\\bin\"$$escape_expand(\n\t))
}else:win32:CONFIG(debug, debug|release){
    QMAKE_POST_LINK += $$quote(cmd /c copy /y \"$${_qtdir}\\Qt5Cored.dll\" \"$${_out_pwd}\\..\\bin\"$$escape_expand(\n\t))
    QMAKE_POST_LINK += $$quote(cmd /c copy /y \"$${_qtdir}\\Qt5Guid.dll\" \"$${_out_pwd}\\..\\bin\"$$escape_expand(\n\t))
    QMAKE_POST_LINK += $$quote(cmd /c copy /y \"$${_qtdir}\\Qt5Widgetsd.dll\" \"$${_out_pwd}\\..\\bin\"$$escape_expand(\n\t))
    QMAKE_POST_LINK += $$quote(cmd /c copy /y \"$${_qtdir}\\Qt5Testd.dll\" \"$${_out_pwd}\\..\\bin\"$$escape_expand(\n\t))
}

INCLUDEPATH += $$PWD/../osg/include
DEPENDPATH += $$PWD/../osg/include
