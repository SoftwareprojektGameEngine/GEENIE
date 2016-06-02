_pwd = $${PWD}
_pwd ~= s,/,\\,g
_out_pwd = $${OUT_PWD}
_out_pwd ~= s,/,\\,g
_qtdir = $$[QT_INSTALL_BINS]
_qtdir ~= s,/,\\,g

osgDir = $${_pwd}/OpenSceneGraph/bin
osgDir ~= s,/,\\,g

win32:CONFIG(release, debug|release){
    QMAKE_POST_LINK += $$quote(copy /y \"$${_qtdir}\\Qt5Core.dll\" \"$${_out_pwd}\\..\\bin\"$$escape_expand(\n\t))
    QMAKE_POST_LINK += $$quote(copy /y \"$${_qtdir}\\Qt5Gui.dll\" \"$${_out_pwd}\\..\\bin\"$$escape_expand(\n\t))
    QMAKE_POST_LINK += $$quote(copy /y \"$${_qtdir}\\Qt5Widgets.dll\" \"$${_out_pwd}\\..\\bin\"$$escape_expand(\n\t))
    QMAKE_POST_LINK += $$quote(copy /y \"$${_qtdir}\\Qt5Test.dll\" \"$${_out_pwd}\\..\\bin\"$$escape_expand(\n\t))
    QMAKE_POST_LINK += $$quote(copy /y \"$${osgDir}\\osg130-osg.dll\" \"$${_out_pwd}\\..\\bin\"$$escape_expand(\n\t))
    QMAKE_POST_LINK += $$quote(copy /y \"$${osgDir}\\osg130-osgDB.dll\" \"$${_out_pwd}\\..\\bin\"$$escape_expand(\n\t))
    QMAKE_POST_LINK += $$quote(copy /y \"$${osgDir}\\osg130-osgGA.dll\" \"$${_out_pwd}\\..\\bin\"$$escape_expand(\n\t))
    QMAKE_POST_LINK += $$quote(copy /y \"$${osgDir}\\osg130-osgViewer.dll\" \"$${_out_pwd}\\..\\bin\"$$escape_expand(\n\t))
    QMAKE_POST_LINK += $$quote(copy /y \"$${osgDir}\\osg130-osgUtil.dll\" \"$${_out_pwd}\\..\\bin\"$$escape_expand(\n\t))
    QMAKE_POST_LINK += $$quote(copy /y \"$${osgDir}\\ot20-OpenThreads.dll\" \"$${_out_pwd}\\..\\bin\"$$escape_expand(\n\t))
}else:win32:CONFIG(debug, debug|release){
    QMAKE_POST_LINK += $$quote(copy /y \"$${_qtdir}\\Qt5Cored.dll\" \"$${_out_pwd}\\..\\bin\"$$escape_expand(\n\t))
    QMAKE_POST_LINK += $$quote(copy /y \"$${_qtdir}\\Qt5Guid.dll\" \"$${_out_pwd}\\..\\bin\"$$escape_expand(\n\t))
    QMAKE_POST_LINK += $$quote(copy /y \"$${_qtdir}\\Qt5Widgetsd.dll\" \"$${_out_pwd}\\..\\bin\"$$escape_expand(\n\t))
    QMAKE_POST_LINK += $$quote(copy /y \"$${_qtdir}\\Qt5Testd.dll\" \"$${_out_pwd}\\..\\bin\"$$escape_expand(\n\t))
    QMAKE_POST_LINK += $$quote(copy /y \"$${osgDir}\\osg130-osgd.dll\" \"$${_out_pwd}\\..\\bin\"$$escape_expand(\n\t))
    QMAKE_POST_LINK += $$quote(copy /y \"$${osgDir}\\osg130-osgDBd.dll\" \"$${_out_pwd}\\..\\bin\"$$escape_expand(\n\t))
    QMAKE_POST_LINK += $$quote(copy /y \"$${osgDir}\\osg130-osgGAd.dll\" \"$${_out_pwd}\\..\\bin\"$$escape_expand(\n\t))
    QMAKE_POST_LINK += $$quote(copy /y \"$${osgDir}\\osg130-osgViewerd.dll\" \"$${_out_pwd}\\..\\bin\"$$escape_expand(\n\t))
    QMAKE_POST_LINK += $$quote(copy /y \"$${osgDir}\\osg130-osgUtild.dll\" \"$${_out_pwd}\\..\\bin\"$$escape_expand(\n\t))
    QMAKE_POST_LINK += $$quote(copy /y \"$${osgDir}\\osg130-osgTextd.dll\" \"$${_out_pwd}\\..\\bin\"$$escape_expand(\n\t))
    QMAKE_POST_LINK += $$quote(copy /y \"$${osgDir}\\ot20-OpenThreadsd.dll\" \"$${_out_pwd}\\..\\bin\"$$escape_expand(\n\t))
    QMAKE_POST_LINK += $$quote(copy /y \"$${osgDir}\\zlibd.dll\" \"$${_out_pwd}\\..\\bin\"$$escape_expand(\n\t))
}

INCLUDEPATH += $$PWD/OpenScenegraph/include
DEPENDPATH += $$PWD/OpenScenegraph/include
