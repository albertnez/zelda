#pragma once

#include "cTexture.h"
#include "Globals.h"
#include "utils.h"
#include "cMap.h"
#include "cAnim.h"
#include <unordered_map>

extern const int FRAME_DELAY;
extern const int STEP_LENGTH;

class cBicho
{
public:
	enum State {
		Look = 0,
		Walk,
	};
	cBicho(void);
	cBicho(int x,int y,int w,int h);
	~cBicho(void);

	void SetPosition(int x,int y);
	void GetPosition(int *x, int *y) const;
	void SetTile(int tx,int ty);
	void GetTile(int *tx, int *ty) const;
	void SetWidthHeight(int w,int h);
	void GetWidthHeight(int *w, int *h) const;
	void SetHitpoints(int hp);
	int GetHitpoints() const;
	void SetMaxHitpoints(int hp);
	int GetMaxHitpoints() const;
	void Heal(int hp);
	bool Damage(int hp);
	void SetAttack(int attack);
	int GetAttack() const;
	bool IsDead() const;

	bool Collides(const cRect &rect);
	// Checks collision with tiles
	bool CollidesMap(const cMap &map);
    bool CollidesDoor(const cMap & map, int& tileX, int& tileY);
    // Returns whether reaches the limit of the map.
	bool ReachesMapLimit(const cMap &map, int scene_x, int scene_y);
	// Called when cBicho reaches limit of map. Returns true if
	// it can go through the limit (like link going to next view).
	virtual bool ReachLimit(Direction dir);
	// Reset Animation.
	void ResetAnimation();
	virtual void SetAnimation(const std::string& name);
	std::string GetAnimation() const;


    virtual cRect GetArea() const;
    void Draw(int texId, int texWidth, int texHeight);
    virtual void SpecificDraw(int texId, int texWidth, int texHeight);
	void DrawRect(int tex_id,float xo,float yo,float xf,float yf);
	
	// Returns True if it can move, false otherwise.
	virtual bool Move(const cMap &map, Direction dir, int sceneX = 0, int sceneY = 0);
	void Stop();
	void Logic(const cMap &map);
    virtual void SpecificLogic(const cMap &map);

	Direction GetDirection() const;
	void SetDirection(Direction dir);
	State GetState() const;
	void SetState(State state);
    bool AtDoor(const cMap &map, int& tileX, int& tileY);
    void NextFrame(int max);
    void SetSpawnObjects(bool spawn);
    bool SpawnObjects() const;
	
protected:
    void UpdateProtected();
    virtual void InDungeonDoor();
    float x,y;
    int w,h;
    float stepLength;
    State state;
    Direction direction;
    int hitpoints;
    int maxHitpoints;
    int attack;
    bool isProtected;
    int protectionTime;
    int maxProtectionTime;
    bool spawnObjects;

	std::string currentAnimation;
	std::unordered_map<std::string, cAnim> animations;

 private:

    void Init();
};
