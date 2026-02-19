/* ============================================================
 *
 * This file is a part of digiKam project
 * https://www.digikam.org
 *
 * Date        : 2009-05-29
 * Description : static helper methods for PGF image format.
 *
 * SPDX-FileCopyrightText: 2009-2026 by Gilles Caulier <caulier dot gilles at gmail dot com>
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 * ============================================================ */

#pragma once

// Qt includes

#include <QString>
#include <QImage>
#include <QByteArray>

// Local includes

#include "digikam_config.h"
#include "digikam_export.h"

namespace Digikam
{

namespace PGFUtils
{

/**
 * @brief PGF image data to QImage using memory stream.
 * @note Only use this method to manage PGF thumbnails stored in database.
 */
DIGIKAM_EXPORT bool readPGFImageData(const QByteArray& data,
                                     QImage& img,
                                     bool verbose=false);

/**
 * @brief QImage to PGF image data using memory stream.
 * @param quality set compression ratio:
 *  0    => lossless compression, as PNG.
 *  1    => Not loss less compression, wavelets based...
 *  2    => ...
 *  3    => ...
 *  4    => Same compression ratio near than JPEG quality=85.
 *          Image quality is valid for  thumbnails.
 *  >= 5 => provide artifacts due to down-sampling. Do not use it...
 * @note Only use this method to manage PGF thumbnails stored in database.
 */
DIGIKAM_EXPORT bool writePGFImageData(const QImage& image,
                                      QByteArray& data,
                                      int quality,
                                      bool verbose=false);

/**
 * @brief QImage to PGF image data using file stream.
 * Uses same params than writePGFImageData() excepted 'filePath'
 * which is PGF target file path.
 */
DIGIKAM_EXPORT bool writePGFImageFile(const QImage& image,
                                      const QString& filePath,
                                      int quality,
                                      bool verbose=false);

/**
 * @brief Load a reduced version of PGF file
 */
DIGIKAM_EXPORT bool loadPGFScaled(QImage& img,
                                  const QString& path,
                                  int maximumSize);

/**
 * @return a libpgf version string
 */
DIGIKAM_EXPORT QString libPGFVersion();

} // namespace PGFUtils

} // namespace Digikam
