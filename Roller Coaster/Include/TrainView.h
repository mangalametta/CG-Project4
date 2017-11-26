#pragma once
#ifndef TRAINVIEW_H  
#define TRAINVIEW_H
#include <QtOpenGL/QGLWidget> 
#include <QtGui/QtGui>  
#include <QtOpenGL/QtOpenGL>  
#include <GL/GLU.h>
#include <QtGui/QOpenGLFunctions_4_3_Core>
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib") 
#include "Utilities/ArcBallCam.H"
#include "Utilities/3DUtils.H"
#include "Track.H"
class AppMain;
class CTrack;

enum spline_t {
    spline_Linear,
    spline_Cardinal,
    spline_Cubic
};

//#######################################################################
// TODO
// You might change the TrainView in order to add different objects to
// be drawn, or adjust the lighting, or ...
//#######################################################################


class TrainView : public QGLWidget, protected QOpenGLFunctions_4_3_Core
{  
	Q_OBJECT  
public:  
	explicit TrainView(QWidget *parent = 0);  
	~TrainView();  

public:
	// overrides of important window things
	//virtual int handle(int);
	virtual void paintGL();

	// all of the actual drawing happens in this routine
	// it has to be encapsulated, since we draw differently if
	// we're drawing shadows (no colors, for example)
	void drawStuff(bool doingShadows=false);
	// setup the projection - assuming that the projection stack has been
	// cleared for you
	void setProjection();

	// Reset the Arc ball control
	void resetArcball();

	// pick a point (for when the mouse goes down)
	void doPick(int mx, int my);

	void initializeGL();

private:
    inline Pnt3f Linear(Pnt3f p1, Pnt3f p2, float t);
    inline Pnt3f Cardinal(Pnt3f p0, Pnt3f p1, Pnt3f p2, Pnt3f p3, float t);
    inline Pnt3f Cubic(Pnt3f p0, Pnt3f p1, Pnt3f p2, Pnt3f p3, float t);
    void drawTrack(bool);
    void drawTrain();
    void trainCamView(float);

public:
	ArcBallCam		arcball;			// keep an ArcBall for the UI
	int				selectedCube;  // simple - just remember which cube is selected

	CTrack*			m_pTrack;		// The track of the entire scene

	int camera;
	int curve;
	int track;
	bool isrun;
    float t_time;
	float arclen;
    const int DIVIDE_LINE = 40;
	const float interval = 5.0;
};  

#endif // TRAINVIEW_H  