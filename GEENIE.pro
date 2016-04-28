TEMPLATE = subdirs

SUBDIRS += \
    GEENIE \
    Logger

GEENIE.depends = Logger
