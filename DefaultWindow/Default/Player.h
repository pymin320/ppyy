#pragma once
#include "Obj.h"
#include "Bullet.h"
#include "Bullet_Default.h"
#include "BulletBomb.h"
#include "CPattern.h"
#include "UI.h"

class CPlayer : public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	int		Get_Heart() { return m_iHeart; }
	void	Set_EnemyList(list<CObj*>* pEnemy) { m_EnemyList = pEnemy; }
	int		Get_BoostCount() { return m_iBoostCount; }
	int		Get_BombCount() { return m_iBombCount; }
	void	Set_BulletList(list<CObj*>* _pBulletList) { m_pBulletList = _pBulletList; }
	void	Set_ItemList(list<CObj*>* _pItemList) { m_pItemList = _pItemList; }
	void	Set_ItemShield() { m_bShield = true; }
	void	Set_ItemSpeed() { m_fSpeed *= 1.3f; }
	void	Set_HDC(HDC hDC) { m_hDC = hDC; }
	void	Set_ItemAbility(CObj* _item);
public:
	virtual void Initialize(void) override;
	virtual int	 Update(void) override;
	virtual	void Late_Update(void);
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	virtual void OnTriggerEnter(CObj* _Object) override;

private:
	void		Key_Input();
private:
	HDC				m_hDC;
	list<CObj*>*	m_pBulletList;					//메인에서 가져온거
	list<CObj*>*	m_pItemList;					//메인에서 가져온거
	list <CObj*>	m_ShieldList;
	list<CObj*>*	m_pShieldList = &m_ShieldList;
	list<CObj*>*	m_EnemyList;				// 지우는건지 확인필요

	// 모양 관련
	POINT			PolygonPoint[6];
	POINT			m_tPosin;
	float			m_fDiagonal;

	// 쉴드 관련
	CObj*			m_pShield;
	float			m_fAngle_Shield;
	POINT			m_tPosin_Shield;
	float			m_fDiagonal_Shield;

	// 부가기능
	BOOL			m_bBoost;		// 부스트 모드 여부
	BOOL			m_bShield;		// 쉴드 모드 여부
	int				m_iHeart;		// 플레이어 목숨
	int				m_iBoostCount;
	int				m_iBombCount;
	/*int				m_iBoostFail;*/
	int				m_iGageScore;
	DWORD			m_Time;
	DWORD			m_Time2;
	DWORD			m_Time3;
	DWORD			m_Time4;

	

	//hong modify
	int m_helth = 10;
	DWORD m_CollisionTime = GetTickCount();
	bool m_bCollision = true;
	// end
//	CPattern*			m_pPattern;
};