/* Copyright (c) 2012 Patrick Ruoff
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 */

#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QTime>
#include <opencv2/opencv.hpp>
#include <memory>
#include <QWidget>
#include <QMutex>
#include <QMutexLocker>
#include <QLabel>
#include <QPainter>
#include <QPaintEvent>

// ----------------------------------------------------------------------------
class VideoWidget : public QWidget
{
	Q_OBJECT

public:
    VideoWidget(QWidget *parent) : QWidget(parent), mtx() {
	}
    void update_image(cv::Mat frame, std::auto_ptr< std::vector<cv::Vec2f> >);
protected slots:
    void paintEvent( QPaintEvent* e ) {
        QMutexLocker foo(&mtx);
        QPainter painter(this);
        painter.drawPixmap(e->rect(), pixmap, e->rect());
    }

private:
    QMutex mtx;
    QPixmap pixmap;
};

#endif // VIDEOWIDGET_H
