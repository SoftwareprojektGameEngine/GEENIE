TEMPLATE = subdirs

SUBDIRS += \
    GEENIE \
    Logger \
    common \
    GEENIE_Core \
    GEENIE_Core_Test \
    Brain \
    Backend

GEENIE.depends = Backend Brain Logger common
Brain.depends = Backend Logger common
Backend.depends = Logger common
Logger.depends = common
GEENIE_Core_Test.depends = GEENIE_Core
