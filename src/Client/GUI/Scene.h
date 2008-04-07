#ifndef _SCENE_H
#define _SCENE_H

#include "irrlicht/irrlicht.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;


class PseuGUI;
class CCursorController;

// base class
class Scene
{
    friend class PseuGUI;
public:
    Scene(PseuGUI *g);
    ~Scene();
    inline void SetState(SceneState sc) { _scenestate = sc; }
    inline SceneState GetState(void) { return _scenestate; }
    virtual void OnUpdate(s32);
    virtual void OnDraw(void);
    virtual void OnDrawBegin(void);
    virtual void OnDelete(void);    
    virtual video::SColor GetBackgroundColor(void);
protected:

    PseuGUI *gui;
    irr::IrrlichtDevice *device;
    irr::video::IVideoDriver* driver;
    irr::scene::ISceneManager* smgr;
    irr::gui::IGUIEnvironment* guienv;
    CCursorController *cursor;
    SceneState _scenestate;
};

class SceneGuiStart : public Scene
{
public:
    SceneGuiStart(PseuGUI *gui);
    void OnDelete(void);
private:
    IGUIImage *irrlogo, *driverlogo;

};


class ShTlTerrainSceneNode;
class MCameraFPS;
class MCameraOrbit;
class MyEventReceiver;
class MapMgr;
class WorldSession;

class SceneWorld : public Scene
{
    struct SceneNodeWithGridPos
    {
        scene::ISceneNode *scenenode;
        uint32 gx,gy;
    };

public:
    SceneWorld(PseuGUI *gui);
    void OnDraw(void);
    void OnDrawBegin(void);
    void OnDelete(void);
    void OnUpdate(s32);
    void UpdateTerrain(void);
    void InitTerrain(void);
    void RelocateCamera(void);
    void UpdateDoodads(void);
    video::SColor GetBackgroundColor(void);

    WorldPosition GetWorldPosition(void);

private:
    ShTlTerrainSceneNode *terrain;
    MCameraFPS *camera;
    MyEventReceiver *eventrecv;
    ZThread::FastMutex mutex;
    PseuGUI *gui;
    uint32 map_gridX, map_gridY;
    s32 mapsize, meshsize;
    f32 tilesize;
    WorldSession *wsession;
    World *world;
    MapMgr *mapmgr;
    IGUIStaticText *debugText;
    bool debugmode;
    std::map<uint32,SceneNodeWithGridPos> _doodads;
    scene::ISceneNode *sky;
    video::SColor envBasicColor;
};



#endif
