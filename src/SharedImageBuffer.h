/************************************************************************/
/* qt-opencv-multithreaded:                                             */
/* A multithreaded OpenCV application using the Qt framework.           */
/*                                                                      */
/* SharedImageBuffer.h                                                  */
/*                                                                      */
/* Nick D'Ademo <nickdademo@gmail.com>                                  */
/*                                                                      */
/* Copyright (c) 2012-2016 Nick D'Ademo                                 */
/*                                                                      */
/* Permission is hereby granted, free of charge, to any person          */
/* obtaining a copy of this software and associated documentation       */
/* files (the "Software"), to deal in the Software without restriction, */
/* including without limitation the rights to use, copy, modify, merge, */
/* publish, distribute, sublicense, and/or sell copies of the Software, */
/* and to permit persons to whom the Software is furnished to do so,    */
/* subject to the following conditions:                                 */
/*                                                                      */
/* The above copyright notice and this permission notice shall be       */
/* included in all copies or substantial portions of the Software.      */
/*                                                                      */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,      */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF   */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND                */
/* NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS  */
/* BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN   */
/* ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN    */
/* CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE     */
/* SOFTWARE.                                                            */
/*                                                                      */
/************************************************************************/

#ifndef SHAREDIMAGEBUFFER_H
#define SHAREDIMAGEBUFFER_H

#include <QHash>
#include <QSet>
#include <QWaitCondition>
#include <QMutex>

#include <opencv2/opencv.hpp>

#include "Buffer.h"

class SharedImageBuffer
{
    public:
        SharedImageBuffer();
        void add(int deviceNumber, Buffer<cv::Mat> *imageBuffer, bool sync = false);
        Buffer<cv::Mat>* get(int deviceNumber);
        void remove(int deviceNumber);
        void sync(int deviceNumber);
        void wakeAll();
        void setSyncStarted(bool start);
        bool isSyncStarted()
        {
            return m_doSync;
        }
        bool isSyncEnabled(int deviceNumber);
        bool contains(int deviceNumber);

    private:
        QHash<int, Buffer<cv::Mat>*> m_imageBufferMap;
        QSet<int> m_syncSet;
        QWaitCondition m_waitCondition;
        QMutex m_mutex;
        int m_nArrived;
        bool m_doSync;
};

#endif // SHAREDIMAGEBUFFER_H
