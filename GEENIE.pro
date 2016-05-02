TEMPLATE = subdirs

SUBDIRS += \
    GEENIE \
    Logger \
    common

GEENIE.depends = Logger common
Logger.depends = common
