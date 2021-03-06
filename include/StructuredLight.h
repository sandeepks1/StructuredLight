/*
-----------------------------------------------------------------------------
Filename:    StructuredLight.h
-----------------------------------------------------------------------------


This source file is generated by the
   ___                   _              __    __ _                  _ 
  /___\__ _ _ __ ___    /_\  _ __  _ __/ / /\ \ (_)______ _ _ __ __| |
 //  // _` | '__/ _ \  //_\\| '_ \| '_ \ \/  \/ / |_  / _` | '__/ _` |
/ \_// (_| | | |  __/ /  _  \ |_) | |_) \  /\  /| |/ / (_| | | | (_| |
\___/ \__, |_|  \___| \_/ \_/ .__/| .__/ \/  \/ |_/___\__,_|_|  \__,_|
      |___/                 |_|   |_|                                 
      Ogre 1.7.x Application Wizard for VC10 (July 2011)
      http://code.google.com/p/ogreappwizards/
-----------------------------------------------------------------------------
*/
#ifndef __StructuredLight_h_
#define __StructuredLight_h_
#include "stdafx.h"
#include "BaseApplication.h"
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#include "../res/resource.h"
#endif
#define SENSOR_INPUT 0

class StructuredLight : public BaseApplication
{
public:
    StructuredLight(void);
    virtual ~StructuredLight(void);
	void createStructuredTexture();
	Ogre::TexturePtr structuredTexture;
	void refillTexture(bool verticalOrHorizontal,int divider);
	virtual bool keyPressed( const OIS::KeyEvent &arg );
    virtual bool keyReleased( const OIS::KeyEvent &arg );
    // OIS::MouseListener
    virtual bool mouseMoved( const OIS::MouseEvent &arg );
    virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

	#if SENSOR_INPUT
	void updatePoints(bool yOrX);
	bool shownBlack;
	bool shownWhite;
	bool signalBuffer;
	void setFlag(bool blackOrWhite);
	#endif

protected:
    virtual void createScene(void);
	int maxPowerX;
	int maxPowerY;
	int currentX;
	int currentY;
	bool start;

	int initialWidth;
	int initialHeight;

	int mouseX;
	int mouseY;

	Ogre::Vector2 topLeft;
	Ogre::Vector2 topRight;
	Ogre::Vector2 bottomRight;
	Ogre::Vector2 bottomLeft;

	int currentTarget;

	int targetX;
	int targetY;

	int targetCorner;

	Ogre::Entity* videoWall;

	std::vector<Ogre::Entity*> qrEntities;
	std::vector<Ogre::SceneNode*> qrNodes;

	Ogre::SceneNode* videoNode;
	Ogre::SceneNode* baseNode;
	Ogre::MeshPtr videoMesh;
	Ogre::MeshPtr qrMesh;
	Ogre::Matrix4 trueProjection;


	std::vector<Ogre::Vector2*> points;
	void updatePoint(int* point);

	//void createNewPlane();
	//void transformPlane();
	void mapPlane();
	//vector<vector<bool>> points;
	Ogre::OverlayElement* structurePanel;
	float passedTime;
	Ogre::TexturePtr videoTexture;
	CvCapture* videoCapture;
	float videoWidth,
	videoHeight,
	videoFPS,
	frameDelay;
	int pix_size;
	int empty_byte;
	void SetupVideoMaterial();
	void convertIplToTexture(IplImage* img,Ogre::TexturePtr texture);
	void reloadVideo();

	int xUpdateCount;
	int yUpdateCount;

	std::vector<int> lowThreshold;
	std::vector<int> highThreshold;
	std::vector<int> midThreshold;

};

#endif // #ifndef __StructuredLight_h_
