#pragma once
#include "Obj.h"
class CShield :
	public CObj
{
public:
	CShield();
	~CShield();
public:
	virtual		void	Initialize(void);
	virtual		int		Update(void);
	virtual		void	Late_Update(void);
	virtual		void	Render(HDC hDC);
	virtual		void	Release(void);

public :
	POINT Get_PosinPoint() { return m_tPosin; };

private:
	POINT					m_tPosin;
	float					m_fDiagonal;


};

