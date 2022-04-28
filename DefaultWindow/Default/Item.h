#pragma once
#include "Obj.h"
#include "UI.h"
class CItem :
    public CObj
{
public :

    CItem();
    ~CItem();

	virtual		int		Update(void)		override;
	virtual		void	Late_Update(void)	override;
	virtual		void	Render(HDC hDC)		override;
	virtual		void	Release(void)		override;
	virtual		void	Initialize(void)	override;

public :
	void		Set_pPlayer(CObj* _pPlayer) { m_pPlayer = _pPlayer; }
	//void		Set_pObjList(list<CObj*>* _ObjList) {  }
	int			Get_ItemType() { return m_ItemType; }

private :
	CObj* m_pPlayer;
	int m_ItemType;
};

