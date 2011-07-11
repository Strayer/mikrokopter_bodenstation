#ifndef CAMERAWIDGET_H
#define CAMERAWIDGET_H

#include <QGLWidget>
#include <QtOpenGL>
#include <opencv/cv.h>
#include <opencv/highgui.h>

class CameraWidget : public QGLWidget
{
	Q_OBJECT

public:
    CameraWidget();
	void sendImage(cv::Mat *img);

	int heightForWidth(int w) const;

private slots:
	void processCam();

protected:
	void initializeGL();
	void paintGL();
	void resizeGL(int width, int height);

private:
	cv::Mat currFrame;
	cv::VideoCapture capture;
};

#endif // CAMERAWIDGET_H
