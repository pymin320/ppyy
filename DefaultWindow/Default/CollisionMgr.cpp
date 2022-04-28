#include "stdafx.h"
#include "CollisionMgr.h"


CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}


//void CCollisionMgr::Collision_Rect(list<CObj*> _Dest, list<CObj*> _Sour)
//{
//	RECT		rc{};
//
//	for (auto& Dest : _Dest)
//	{
//		for (auto& Sour : _Sour)
//		{
//			if (Dest == Sour || (Dest->Get_Side() == Sour->Get_Side()))
//			{
//				continue;
//			}
//			if (IntersectRect(&rc, &(Dest->Get_Rect()), &(Sour->Get_Rect())))		// 충돌 체크 함수		rc에 충돌된 범위가 들어가고 bool을 반환
//			{
//				//같은객체면 continue
//				
//				//hong modify
//				//충돌했을때 서로의 정보를 넘겨주고 서로의 OnTriggerEnter를 실행
//				Dest->OnTriggerEnter(Sour);
//				Sour->OnTriggerEnter(Dest);
//				//end
//			}
//		}
//	}
//}

void CCollisionMgr::Collision_Rect(list<CObj*> _Dest, list<CObj*> _Sour)
{
	RECT		rc{};

	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			if (IntersectRect(&rc, &(Dest->Get_Rect()), &(Sour->Get_Rect())))		// 충돌 체크 함수		rc에 충돌된 범위가 들어가고 bool을 반환
			{
				if ((Dest->Get_Side()) != (Sour->Get_Side()))
				{
					++g_iScore;
					Sour->Set_Dead();

					// 서진 추가
					// 아이템일떄 플레이어 안죽게
					if (Sour->Get_Side() != "ITEM")
						Dest->Set_Dead();

					// 아이템 먹기
					if (Sour->Get_Side() == "ITEM")
					{
						dynamic_cast<CPlayer*>(Dest)->Set_ItemAbility(Sour);
					}
				}
			}
		}
	}
}
bool CCollisionMgr::Check_Sphere(CObj* pDest, CObj* pSour)
{
	// abs : 절대값을 구해주는 함수
	float	fWidth = fabs(pDest->Get_Info().fX - pSour->Get_Info().fX);
	float	fHeight = fabs(pDest->Get_Info().fY - pSour->Get_Info().fY);

	// sqrt : 루트를 씌워주는 함수
	float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

	float	fRadius = (pDest->Get_Info().fCX + pSour->Get_Info().fCX) * 0.5f;

	return fRadius > fDiagonal;
}

void CCollisionMgr::Collision_Sphere(list<CObj*> _Dest, list<CObj*> _Sour)
{

	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			if (Check_Sphere(Dest, Sour))
			{
				Dest->Set_Dead();
				Sour->Set_Dead();
			}
		}
	}
}

//int CCollisionMgr::Item_Percent()
//{
//	return rand() % 100 + 1;
//}

