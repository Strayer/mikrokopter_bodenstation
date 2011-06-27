#include "camerawidget.h"

CameraWidget::CameraWidget() : QGLWidget(QGLFormat(QGL::SampleBuffers))
{
	setMinimumSize(320,240);
	capture = cv::VideoCapture(-1);
	processCam();
}

void CameraWidget::initializeGL()
{
	glClearColor(0.0f,0.0f,0.0f,1.0f);
}

void CameraWidget::paintGL()
{
	glClear (GL_COLOR_BUFFER_BIT);
	glClearColor (0.0,0.0,0.0,1.0);
	if (currFrame.data)
	{
		QImage qframe = QImage((const unsigned char*)(currFrame.data), currFrame.cols, currFrame.rows, currFrame.step, QImage::Format_RGB888);
		qframe = QGLWidget::convertToGLFormat(qframe);
		qframe = qframe.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

		glDisable(GL_DEPTH_TEST);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0,qframe.width(),qframe.height(),0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glEnable(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, qframe.width(), qframe.height(), 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, qframe.bits() );
		glBegin(GL_QUADS);
		glTexCoord2f(0,0); glVertex2f(0,qframe.height());
		glTexCoord2f(0,1); glVertex2f(0,0);
		glTexCoord2f(1,1); glVertex2f(qframe.width(),0);
		glTexCoord2f(1,0); glVertex2f(qframe.width(),qframe.height());
		glEnd();
		glDisable(GL_TEXTURE_2D);

		glFlush();
	}
}

void CameraWidget::resizeGL(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLfloat) w / (GLfloat) h, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

void CameraWidget::processCam()
{
	if (capture.isOpened())
	{
		capture >> currFrame;
		updateGL();
		QTimer::singleShot(25, this, SLOT(processCam()));
	}
}
