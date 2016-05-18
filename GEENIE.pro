TEMPLATE = subdirs

SUBDIRS += \
    GEENIE \
    Logger \
    common \
    Brain \
    Backend \
    Assetwindow

GEENIE.depends = Backend Brain Logger common
Brain.depends = Backend Logger common
Backend.depends = Logger common
Logger.depends = common
