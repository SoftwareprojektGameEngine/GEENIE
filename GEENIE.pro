TEMPLATE = subdirs

SUBDIRS += \
    GEENIE \
    Logger \
    common \
    GEENIE_Core \
    Backend

GEENIE.depends = Backend GEENIE_Core Logger common
GEENIE_Core.depends = Logger common
GEENIE_Core_Test.depends = GEENIE_Core
Backend.depends = Logger common GEENIE_Core
Logger.depends = common
