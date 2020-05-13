/* ============================================================
 *
 * This file is a part of digiKam project
 * https://www.digikam.org
 *
 * Date        : 2009-05-29
 * Description : static helper methods for PGF image format.
 *
 * Copyright (C) 2009-2020 by Gilles Caulier <caulier dot gilles at gmail dot com>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software Foundation;
 * either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * ============================================================ */

#ifndef DIGIKAM_PGF_UTILS_H
#define DIGIKAM_PGF_UTILS_H

// Qt includes

#include <QString>
#include <QImage>
#include <QByteArray>

namespace Digikam
{

namespace PGFUtils
{

/**
 * PGF image data to QImage using memory stream.
 * NOTE: Only use this method to manage PGF thumbnails stored in database.
 */
 bool readPGFImageData(const QByteArray& data,
                                     QImage& img,
                                     bool verbose=false);

/**
 * QImage to PGF image data using memory stream. 'quality' argument set compression ratio:
 *  0    => lossless compression, as PNG.
 *  1    => Not loss less compression, wavelets based...
 *  2    => ...
 *  3    => ...
 *  4    => Same compression ratio near than JPEG quality=85.
 *          Image quality is valid for  thumbnails.
 *  >= 5 => provide artifacts due to down-sampling. Do not use it...
 * NOTE: Only use this method to manage PGF thumbnails stored in database.
 */
 bool writePGFImageData(const QImage& image,
                                      QByteArray& data,
                                      int quality,
                                      bool verbose=false);

/**
 * QImage to PGF image data using file stream.
 * Same arguments than writePGFImageData() excepted 'filePath'
 * which is PGF target file path.
 */
 bool writePGFImageFile(const QImage& image,
                                      const QString& filePath,
                                      int quality,
                                      bool verbose=false);

/**
 * Load a reduced version of PGF file
 */
 bool loadPGFScaled(QImage& img,
                                  const QString& path,
                                  int maximumSize);

/**
 * Return a libpgf version string
 */
 QString libPGFVersion();

} // namespace PGFUtils

} // namespace Digikam

#endif // DIGIKAM_PGF_UTILS_H
