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

#include "pgfutils.h"

// C Ansi includes

extern "C"
{
#ifndef Q_CC_MSVC
#   include <unistd.h>
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
}

// Qt includes

#include <QDebug>
#include <QImage>
#include <QByteArray>
#include <QFile>
#include <qplatformdefs.h>

// Windows includes

#ifdef Q_OS_WIN
#   include <windows.h>
#endif

// LibPGF includes

#if defined(Q_CC_CLANG)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wkeyword-macro"
#endif

#include "PGFimage.h"

#if defined(Q_CC_CLANG)
#   pragma clang diagnostic pop
#endif

namespace Digikam
{

namespace PGFUtils
{

bool readPGFImageData(const QByteArray& data,
                      QImage& img,
                      bool verbose)
{
    try
    {
        if (data.isEmpty())
        {
            qWarning() << "PGFUtils: PGF image data to decode : size is null";

            return false;
        }

        CPGFMemoryStream stream((UINT8*)data.data(), (size_t)data.size());

        if (verbose)
        {
            qInfo() << "PGFUtils: image data stream size is : " << stream.GetSize();
        }

        CPGFImage pgfImg;

        // NOTE: see bug #273765 : Loading PGF thumbs with OpenMP support through a separated thread do not work properly with libppgf 6.11.24

        pgfImg.ConfigureDecoder(false);

        pgfImg.Open(&stream);

        if (verbose)
        {
            qInfo() << "PGFUtils: PGF image is open";
        }

        if (pgfImg.Channels() != 4)
        {
            qWarning() << "PGFUtils: PGF channels not supported";

            return false;
        }

        img = QImage(pgfImg.Width(), pgfImg.Height(), QImage::Format_ARGB32);
        pgfImg.Read();

        if (verbose)
        {
            qInfo() << "PGFUtils: PGF image is read";
        }

        if (QSysInfo::ByteOrder == QSysInfo::BigEndian)
        {
            int map[] = {3, 2, 1, 0};
            pgfImg.GetBitmap(img.bytesPerLine(), (UINT8*)img.bits(), img.depth(), map);
        }
        else
        {
            int map[] = {0, 1, 2, 3};
            pgfImg.GetBitmap(img.bytesPerLine(), (UINT8*)img.bits(), img.depth(), map);
        }

        if (verbose)
        {
            qInfo() << "PGFUtils: PGF image is decoded";
        }
    }
    catch (IOException& e)
    {
        int err = e.error;

        if (err >= AppError)
        {
            err -= AppError;
        }

        qWarning() << "PGFUtils: Error running libpgf (" << err << ")!";

        return false;
    }

    return true;
}

} // namespace PGFUtils

} // namespace Digikam
