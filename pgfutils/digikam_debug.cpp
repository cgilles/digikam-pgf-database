/* ============================================================
 *
 * This file is a part of digiKam project
 * https://www.digikam.org
 *
 * Date        : 2014-09-08
 * Description : digiKam debug spaces
 *
 * SPDX-FileCopyrightText: 2014-2026 by Gilles Caulier <caulier dot gilles at gmail dot com>
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 * ============================================================ */

#include "digikam_debug.h"

// Local includes

#include "digikam_config.h"

Q_LOGGING_CATEGORY(DIGIKAM_GENERAL_LOG,                 "digikam.general",                  QtInfoMsg)
Q_LOGGING_CATEGORY(DIGIKAM_WIDGETS_LOG,                 "digikam.widgets",                  QtInfoMsg)
Q_LOGGING_CATEGORY(DIGIKAM_IOJOB_LOG,                   "digikam.iojob",                    QtInfoMsg)
Q_LOGGING_CATEGORY(DIGIKAM_SHOWFOTO_LOG,                "digikam.showfoto",                 QtInfoMsg)
Q_LOGGING_CATEGORY(DIGIKAM_WEBSERVICES_LOG,             "digikam.webservices",              QtInfoMsg)
Q_LOGGING_CATEGORY(DIGIKAM_DATABASESERVER_LOG,          "digikam.databaseserver",           QtInfoMsg)
Q_LOGGING_CATEGORY(DIGIKAM_IMPORTUI_LOG,                "digikam.import",                   QtInfoMsg)
Q_LOGGING_CATEGORY(DIGIKAM_METAENGINE_LOG,              "digikam.metaengine",               QtInfoMsg)
Q_LOGGING_CATEGORY(DIGIKAM_RAWENGINE_LOG,               "digikam.rawengine",                QtInfoMsg)
Q_LOGGING_CATEGORY(DIGIKAM_FACESENGINE_LOG,             "digikam.facesengine",              QtInfoMsg)
Q_LOGGING_CATEGORY(DIGIKAM_AUTOROTATE_LOG,              "digikam.autorotate",               QtInfoMsg)
Q_LOGGING_CATEGORY(DIGIKAM_AUTOTAGSENGINE_LOG,          "digikam.autotagsengine",           QtInfoMsg)
Q_LOGGING_CATEGORY(DIGIKAM_MLPIPELINEFOUNDATION_LOG,    "digikam.mlpipelinefoundation",     QtInfoMsg)
Q_LOGGING_CATEGORY(DIGIKAM_GEOIFACE_LOG,                "digikam.geoiface",                 QtInfoMsg)
Q_LOGGING_CATEGORY(DIGIKAM_GEOENGINE_LOG,               "digikam.geocore",                  QtInfoMsg)
Q_LOGGING_CATEGORY(DIGIKAM_DNNMODELMNGR_LOG,            "digikam.dnnmodelmanager",          QtInfoMsg)
Q_LOGGING_CATEGORY(DIGIKAM_DETECTOR_LOG,                "digikam.detectors",                QtInfoMsg)
Q_LOGGING_CATEGORY(DIGIKAM_QTOPENCVIMG_LOG,             "digikam.qtopencvimg",              QtInfoMsg)
Q_LOGGING_CATEGORY(DIGIKAM_MAINTENANCE_LOG,             "digikam.maintenance",              QtInfoMsg)

Q_LOGGING_CATEGORY(DIGIKAM_TESTS_LOG,                   "digikam.tests",                    QtInfoMsg)

Q_LOGGING_CATEGORY(DIGIKAM_DPLUGIN_RAWIMPORT_LOG,       "digikam.dplugin.rawimport",        QtInfoMsg)
Q_LOGGING_CATEGORY(DIGIKAM_DPLUGIN_GENERIC_LOG,         "digikam.dplugin.generic",          QtInfoMsg)
Q_LOGGING_CATEGORY(DIGIKAM_DPLUGIN_EDITOR_LOG,          "digikam.dplugin.editor",           QtInfoMsg)
Q_LOGGING_CATEGORY(DIGIKAM_DPLUGIN_BQM_LOG,             "digikam.dplugin.bqm",              QtInfoMsg)
Q_LOGGING_CATEGORY(DIGIKAM_DPLUGIN_LOG,                 "digikam.dplugin",                  QtInfoMsg)

Q_LOGGING_CATEGORY(DIGIKAM_DATABASE_LOG,                "digikam.database",                 QtInfoMsg)
Q_LOGGING_CATEGORY(DIGIKAM_DBENGINE_LOG,                "digikam.dbengine",                 QtInfoMsg)
Q_LOGGING_CATEGORY(DIGIKAM_DBJOB_LOG,                   "digikam.dbjob",                    QtInfoMsg)
Q_LOGGING_CATEGORY(DIGIKAM_COREDB_LOG,                  "digikam.coredb",                   QtInfoMsg)
Q_LOGGING_CATEGORY(DIGIKAM_FACEDB_LOG,                  "digikam.facedb",                   QtInfoMsg)
Q_LOGGING_CATEGORY(DIGIKAM_THUMBSDB_LOG,                "digikam.thumbsdb",                 QtInfoMsg)
Q_LOGGING_CATEGORY(DIGIKAM_SIMILARITYDB_LOG,            "digikam.similaritydb",             QtInfoMsg)

// NOTE: per default only warnings and more severe messages are logged for other than general category

Q_LOGGING_CATEGORY(DIGIKAM_DIMG_LOG,                    "digikam.dimg",                     QtInfoMsg)
Q_LOGGING_CATEGORY(DIGIKAM_DIMG_LOG_JPEG,               "digikam.dimg.jpeg",                QtWarningMsg)
Q_LOGGING_CATEGORY(DIGIKAM_DIMG_LOG_JP2K,               "digikam.dimg.jp2k",                QtWarningMsg)
Q_LOGGING_CATEGORY(DIGIKAM_DIMG_LOG_PGF,                "digikam.dimg.pgf",                 QtWarningMsg)
Q_LOGGING_CATEGORY(DIGIKAM_DIMG_LOG_PNG,                "digikam.dimg.png",                 QtWarningMsg)
Q_LOGGING_CATEGORY(DIGIKAM_DIMG_LOG_PPM,                "digikam.dimg.ppm",                 QtWarningMsg)
Q_LOGGING_CATEGORY(DIGIKAM_DIMG_LOG_TIFF,               "digikam.dimg.tiff",                QtWarningMsg)
Q_LOGGING_CATEGORY(DIGIKAM_DIMG_LOG_RAW,                "digikam.dimg.raw",                 QtWarningMsg)
Q_LOGGING_CATEGORY(DIGIKAM_DIMG_LOG_QIMAGE,             "digikam.dimg.qimage",              QtWarningMsg)
Q_LOGGING_CATEGORY(DIGIKAM_DIMG_LOG_HEIF,               "digikam.dimg.heif",                QtWarningMsg)
Q_LOGGING_CATEGORY(DIGIKAM_DIMG_LOG_MAGICK,             "digikam.dimg.magick",              QtWarningMsg)

Q_LOGGING_CATEGORY(DIGIKAM_MEDIASRV_LOG,                "digikam.mediaserver",              QtInfoMsg)
Q_LOGGING_CATEGORY(DIGIKAM_MEDIASRV_LOG_INFO,           "digikam.mediaserver.info",         QtInfoMsg)
Q_LOGGING_CATEGORY(DIGIKAM_MEDIASRV_LOG_DEBUG,          "digikam.mediaserver.debug",        QtInfoMsg)
Q_LOGGING_CATEGORY(DIGIKAM_MEDIASRV_LOG_WARN,           "digikam.mediaserver.warn",         QtWarningMsg)
Q_LOGGING_CATEGORY(DIGIKAM_MEDIASRV_LOG_CRITICAL,       "digikam.mediaserver.critical",     QtWarningMsg)
Q_LOGGING_CATEGORY(DIGIKAM_MEDIASRV_LOG_FATAL,          "digikam.mediaserver.fatal",        QtCriticalMsg)

void digikamSetDebugFilterRules(bool on)
{
    if (on)
    {
        QLoggingCategory::setFilterRules(QLatin1String("digikam.*=true\n"
                                                       "digikam.dimg.jpeg=false\n"
                                                       "digikam.geocore=false"));        // to much verbose at the console
    }
}
