/*
  Copyright (c) 2014, Martin Björkström
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice, this
    list of conditions and the following disclaimer.

  * Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "sepiafilter.h"

class SepiaFilterWorker : public AbstractImageFilterWorker
{
public:
    void doWork(const QImage &origin) {
        QImage newImage(origin);
        QRgb *bits = (QRgb *)newImage.bits();
        int pixel = 0;
        int width = newImage.width();
        int height = newImage.height();

        for(int y = 0; y<height; y++){
            for(int x = 0; x<width; x++){
                pixel = (y*width)+x;

                bits[pixel] = qRgb(qBound(0,(int)((qRed(bits[pixel]) * .393) + (qGreen(bits[pixel]) *.769) + (qRed(bits[pixel]) * .189)),255),
                                   qBound(0,(int)((qRed(bits[pixel]) * .349) + (qGreen(bits[pixel]) *.686) + (qRed(bits[pixel]) * .168)),255),
                                   qBound(0,(int)((qRed(bits[pixel]) * .272) + (qGreen(bits[pixel]) *.534) + (qRed(bits[pixel]) * .131)),255));
            }
        }

        emit resultReady(newImage);
    }
};

SepiaFilter::SepiaFilter(QObject *parent) :
    AbstractImageFilter(parent)
{
}

QString SepiaFilter::name() const
{
    return QLatin1String("Sepia");
}

AbstractImageFilterWorker *SepiaFilter::createWorker()
{
    return new SepiaFilterWorker();
}
