#pragma once

#include "Obj.h"
#include "MainGame.h"

class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();

public:
	static bool		Check_Sphere(CObj* pDest, CObj* pSour);
	static void		Collision_Rect(list<CObj*> _Dest, list<CObj*> _Sour);
	static void		Collision_Sphere(list<CObj*> _Dest, list<CObj*> _Sour);
	/*static int		Item_Percent();*/
};

