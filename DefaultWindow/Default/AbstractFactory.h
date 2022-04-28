#pragma once

#include "Obj.h"
#include "CPattern.h"

template<typename T>
class CAbstractFactory
{
public:

	CAbstractFactory(){}
	~CAbstractFactory(){}

public:
	static CObj*	Create(string _Side)
	{
		CObj*	pObj = new T;
		pObj->Side(_Side);
		pObj->Initialize();

		return pObj;
	}

	//몬스터 파라미터 생성자 
	static CObj* Create(float _fX, float _fY, MOBTYPE eType)
	{
		CObj* pObj = new T(eType);
		pObj->Set_Pos(_fX, _fY);
		pObj->Initialize();

		return pObj;
	}


	static CObj*	Create(float _fX, float _fY, float _fAngle)
	{
		CObj*	pObj = new T;

		pObj->Set_Pos(_fX, _fY);
		pObj->Set_Angle(_fAngle);
		pObj->Initialize();

		return pObj;
	}

	static CObj* Create(float _fX, float _fY, float _fAngle, string _side)
	{
		CObj* pObj = new T;

		pObj->Set_Pos(_fX, _fY);
		pObj->Set_Angle(_fAngle);
		pObj->Side(_side);
		pObj->Initialize();

		return pObj;
	}

	static CObj* Create(float _fX, float _fY, float _fAngle, CPattern* m_Pattern)
	{
		CObj* pObj = new T;

		pObj->Set_Pos(_fX, _fY);
		pObj->Set_Angle(_fAngle);
		dynamic_cast<CMonster*>(pObj)->SetPattern(m_Pattern);
		pObj->Initialize();

		return pObj;
	}
	static CObj* Create(float _fX, float _fY, DIRECTION eDir = DIR_END)
	{
		CObj* pObj = new T;

		pObj->Set_Pos(_fX, _fY);

		if (DIR_END >= eDir)
			pObj->Set_Dir(eDir);

		pObj->Initialize();
		return pObj;
	}
};

