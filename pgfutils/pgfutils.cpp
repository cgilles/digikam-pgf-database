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

// Private method
bool writePGFImageDataToStream(const QImage& image,
                               CPGFStream& stream,
                               int quality,
                               UINT32& nWrittenBytes,
                               bool verbose);

bool readPGFImageData(const QByteArray& data,
                      QImage& img,
                      bool verbose)
{
    try
    {
        if (data.isEmpty())
        {
            qDebug() << "PGFUtils: PGF image data to decode : size is null";

            return false;
        }

        CPGFMemoryStream stream((UINT8*)data.data(), (size_t)data.size());

        if (verbose)
        {
            qDebug() << "PGFUtils: image data stream size is : " << stream.GetSize();
        }

        CPGFImage pgfImg;

        // NOTE: see bug #273765 : Loading PGF thumbs with OpenMP support through a separated thread do not work properly with libppgf 6.11.24

        pgfImg.ConfigureDecoder(false);

        pgfImg.Open(&stream);

        if (verbose)
        {
            qDebug() << "PGFUtils: PGF image is open";
        }

        if (pgfImg.Channels() != 4)
        {
            qDebug() << "PGFUtils: PGF channels not supported";

            return false;
        }

        img = QImage(pgfImg.Width(), pgfImg.Height(), QImage::Format_ARGB32);
        pgfImg.Read();

        if (verbose)
        {
            qDebug() << "PGFUtils: PGF image is read";
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
            qDebug() << "PGFUtils: PGF image is decoded";
        }
    }
    catch (IOException& e)
    {
        int err = e.error;

        if (err >= AppError)
        {
            err -= AppError;
        }

        qDebug() << "PGFUtils: Error running libpgf (" << err << ")!";

        return false;
    }

    return true;
}

bool writePGFImageFile(const QImage& image,
                       const QString& filePath,
                       int quality,
                       bool verbose)
{
#ifdef Q_OS_WIN

    HANDLE fd = CreateFile((LPCWSTR)filePath.utf16(), GENERIC_READ, 0, 0, OPEN_EXISTING, 0, 0);

    if (fd == INVALID_HANDLE_VALUE)
    {
        qDebug() << "PGFUtils: Error: Could not open destination file.";

        return false;
    }

#else

    int fd = QT_OPEN(filePath.toUtf8().constData(),
                     O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

    if (fd == -1)
    {
        qDebug() << "PGFUtils: Error: Could not open destination file.";

        return false;
    }

#endif

    CPGFFileStream stream(fd);
    UINT32 nWrittenBytes = 0;
    bool ret             = writePGFImageDataToStream(image, stream, quality, nWrittenBytes, verbose);

    if (!nWrittenBytes)
    {
        qDebug() << "PGFUtils: Written PGF file : data size is null";
        ret = false;
    }
    else
    {
        if (verbose)
        {
            qDebug() << "PGFUtils: file size written : " << nWrittenBytes;
        }
    }

#ifdef Q_OS_WIN

    CloseHandle(fd);

#else

    close(fd);

#endif

    return ret;
}

bool writePGFImageData(const QImage& image, QByteArray& data, int quality, bool verbose)
{
    try
    {
        // We will use uncompressed image bytes size to allocate PGF stream in memory. In all case, due to PGF compression ratio,
        // PGF data will be so far lesser than image raw size.

#if (QT_VERSION >= QT_VERSION_CHECK(5, 10, 0))

        int rawSize          = image.sizeInBytes();

#else

        int rawSize          = image.byteCount();

#endif

        CPGFMemoryStream stream(rawSize);

        if (verbose)
            qDebug() << "PGFUtils: PGF stream memory allocation in bytes: " << rawSize;

        UINT32 nWrittenBytes = 0;
        bool ret             = writePGFImageDataToStream(image, stream, quality, nWrittenBytes, verbose);
        int pgfsize          =

#ifdef PGFCodecVersionID

#   if PGFCodecVersionID == 0x061224

                               // Wrap around libpgf 6.12.24 about CPGFMemoryStream bytes size generated to make PGF file data.
                               // It miss 16 bytes at end. This solution fix the problem. Problem have been fixed in 6.12.27.

                               nWrittenBytes + 16;

#   else

                               nWrittenBytes;

#   endif

#else

                               nWrittenBytes;

#endif

        data                 = QByteArray((const char*)stream.GetBuffer(), pgfsize);

        if (!pgfsize)
        {
            qDebug() << "PGFUtils: Encoded PGF image : data size is null";
            ret = false;
        }
        else
        {
            if (verbose)
            {
                qDebug() << "PGFUtils: data size written : " << pgfsize;
            }
        }

        return ret;
    }
    catch (IOException& e)
    {
        int err = e.error;

        if (err >= AppError)
        {
            err -= AppError;
        }

        qDebug() << "PGFUtils: Error running libpgf (" << err << ")!";

        return false;
    }
}

bool writePGFImageDataToStream(const QImage& image,
                               CPGFStream& stream,
                               int quality,
                               UINT32& nWrittenBytes,
                               bool verbose)
{
    try
    {
        if (image.isNull())
        {
            qDebug() << "PGFUtils: Thumb image is null";

            return false;
        }

        QImage img;

        // Convert image with Alpha channel.

        if (image.format() != QImage::Format_ARGB32)
        {
            img = image.convertToFormat(QImage::Format_ARGB32);

            if (verbose)
            {
                qDebug() << "PGFUtils: RGB => ARGB";
            }
        }
        else
        {
            img = image;
        }

        CPGFImage pgfImg;
        PGFHeader header;
        header.width                = img.width();
        header.height               = img.height();
        header.nLevels              = 0;             // Auto.
        header.quality              = quality;
        header.bpp                  = img.depth();
        header.channels             = 4;
        header.mode                 = ImageModeRGBA;
        header.usedBitsPerChannel   = 0;             // Auto

#ifdef PGFCodecVersionID

#   if PGFCodecVersionID < 0x061142

        header.background.rgbtBlue  = 0;
        header.background.rgbtGreen = 0;
        header.background.rgbtRed   = 0;

#   endif

#endif
        pgfImg.SetHeader(header);

        // NOTE: see bug #273765 : Loading PGF thumbs with OpenMP support through a separated thread do not work properly with libppgf 6.11.24

        pgfImg.ConfigureEncoder(false);

        if (verbose)
        {
            qDebug() << "PGFUtils: PGF image settings:";
            qDebug() << "PGFUtils:    width: "              << header.width;
            qDebug() << "PGFUtils:    height: "             << header.height;
            qDebug() << "PGFUtils:    nLevels: "            << header.nLevels;
            qDebug() << "PGFUtils:    quality: "            << header.quality;
            qDebug() << "PGFUtils:    bpp: "                << header.bpp;
            qDebug() << "PGFUtils:    channels: "           << header.channels;
            qDebug() << "PGFUtils:    mode: "               << header.mode;
            qDebug() << "PGFUtils:    usedBitsPerChannel: " << header.usedBitsPerChannel;
        }

        if (QSysInfo::ByteOrder == QSysInfo::BigEndian)
        {
            int map[] = {3, 2, 1, 0};
            pgfImg.ImportBitmap(img.bytesPerLine(), (UINT8*)img.bits(), img.depth(), map);
        }
        else
        {
            int map[] = {0, 1, 2, 3};
            pgfImg.ImportBitmap(img.bytesPerLine(), (UINT8*)img.bits(), img.depth(), map);
        }

        nWrittenBytes = 0;

#ifdef PGFCodecVersionID

#   if PGFCodecVersionID >= 0x061124

        pgfImg.Write(&stream, &nWrittenBytes);

#   else

        pgfImg.Write(&stream, 0, 0, &nWrittenBytes);

#   endif

#else
        pgfImg.Write(&stream, 0, 0, &nWrittenBytes);
#endif

    }
    catch (IOException& e)
    {
        int err = e.error;

        if (err >= AppError)
        {
            err -= AppError;
        }

        qDebug() << "PGFUtils: Error running libpgf (" << err << ")!";

        return false;
    }

    return true;
}

bool loadPGFScaled(QImage& img, const QString& path, int maximumSize)
{
#ifdef Q_OS_WIN

    FILE* const file = _wfopen((const wchar_t*)path.utf16(), L"rb");

#else

    FILE* const file = fopen(path.toUtf8().constData(), "rb");

#endif

    if (!file)
    {
        qDebug() << "PGFUtils: Error: Could not open source file.";
        return false;
    }

    unsigned char header[3];

    if (fread(&header, 3, 1, file) != 1)
    {
        fclose(file);

        return false;
    }

    unsigned char pgfID[3] = { 0x50, 0x47, 0x46 };

    if (memcmp(&header[0], &pgfID, 3) != 0)
    {
        // not a PGF file

        fclose(file);

        return false;
    }

    fclose(file);

    // -------------------------------------------------------------------
    // Initialize PGF API.

#ifdef Q_OS_WIN

    HANDLE fd = CreateFile((LPCWSTR)path.utf16(), GENERIC_READ, 0, 0, OPEN_EXISTING, 0, 0);

    if (fd == INVALID_HANDLE_VALUE)
    {
        return false;
    }

#else

    int fd = QT_OPEN(path.toUtf8().constData(), O_RDONLY);

    if (fd == -1)
    {
        return false;
    }

#endif

    try
    {
        CPGFFileStream stream(fd);
        CPGFImage      pgf;
        pgf.Open(&stream);

        // Try to find the right PGF level to get reduced image accordingly
        // with preview size wanted.

        int i = 0;

        if (pgf.Levels() > 0)
        {
            for (i = pgf.Levels()-1 ; i >= 0 ; --i)
            {
                if (qMin((int)pgf.Width(i), (int)pgf.Height(i)) >= maximumSize)
                {
                    break;
                }
            }
        }

        if (i < 0)
        {
            i = 0;
        }

        pgf.Read(i);  // Read PGF image at reduced level i.
        img = QImage(pgf.Width(i), pgf.Height(i), QImage::Format_RGB32);

/*
        const PGFHeader* header = pgf.GetHeader();
        qDebug() << "PGFUtils: PGF width    = " << header->width;
        qDebug() << "PGFUtils: PGF height   = " << header->height;
        qDebug() << "PGFUtils: PGF bbp      = " << header->bpp;
        qDebug() << "PGFUtils: PGF channels = " << header->channels;
        qDebug() << "PGFUtils: PGF quality  = " << header->quality;
        qDebug() << "PGFUtils: PGF mode     = " << header->mode;
        qDebug() << "PGFUtils: PGF levels   = " << header->nLevels;
        qDebug() << "PGFUtils: Level (w x h)= " << i << "(" << pgf.Width(i)
                                      << " x " << pgf.Height(i) << ")";
        qDebug() << "PGFUtils: QImage depth = " << img.depth();
*/

        if (QSysInfo::ByteOrder == QSysInfo::BigEndian)
        {
            int map[] = {3, 2, 1, 0};
            pgf.GetBitmap(img.bytesPerLine(), (UINT8*)img.bits(), img.depth(), map);
        }
        else
        {
            int map[] = {0, 1, 2, 3};
            pgf.GetBitmap(img.bytesPerLine(), (UINT8*)img.bits(), img.depth(), map);
        }
    }
    catch (IOException& e)
    {
        int err = e.error;

        if (err >= AppError)
        {
            err -= AppError;
        }

        qDebug() << "PGFUtils: Error running libpgf (" << err << ")!";

        return false;
    }

    return true;
}

QString libPGFVersion()
{
    return (QLatin1String(PGFCodecVersion));
}

} // namespace PGFUtils

} // namespace Digikam
