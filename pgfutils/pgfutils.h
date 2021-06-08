/* ============================================================
 *
 * This file is a part of digiKam project
 * https://www.digikam.org
 *
 * Date        : 2009-05-29
 * Description : static helper methods for PGF image format.
 *
 * Copyright (C) 2009-2021 by Gilles Caulier <caulier dot gilles at gmail dot com>
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

} // namespace PGFUtils

} // namespace Digikam

#endif // DIGIKAM_PGF_UTILS_H
