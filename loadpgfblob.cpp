/* ============================================================
 *
 * This file is a part of digiKam project
 * https://www.digikam.org
 *
 * Date        : 2009-02-04
 * Description : a command line tool to load PGF data blob from digiKam
 *               database and convert to PNG using QImage
 *
 * SPDX-FileCopyrightText: 2011-2026 by Gilles Caulier <caulier dot gilles at gmail dot com>
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 * ============================================================ */

// Qt includes

#include <QFile>
#include <QIODevice>
#include <QImage>
#include <QDebug>
#include <QByteArray>
#include <QCoreApplication>

// Local includes

#include "pgfutils.h"

using namespace Digikam;

int main(int argc, char** argv)
{
    QCoreApplication(argc, argv);

    if (argc != 2)
    {
        qInfo() << "loadpgfdata - Load PGF blob data and save to PNG";
        qInfo() << "Usage: <pgf_blob_file>";
        return -1;
    }

    QImage img;

    // Write PGF file.

    QString fname(QString::fromUtf8(argv[1]));
    QFile   file(fname);

    if (!file.open(QIODevice::ReadOnly))
    {
        qWarning() << "Cannot open PGF file to read...";
        return -1;
    }

    QByteArray data(file.size(), '\x00');
    QDataStream stream(&file);
    stream.readRawData(data.data(), data.size());

    // PGF => QImage conversion

    if (!PGFUtils::readPGFImageData(data, img))
    {
        qWarning() << "loadPGFScaled failed...";
        return -1;
    }

    img.save(file.fileName() + QString::fromUtf8("-converted.png"), "PNG");

    qInfo() << file.fileName() << "converted as PNG";

    return 0;
}
