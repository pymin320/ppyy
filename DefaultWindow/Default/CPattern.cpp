#include "stdafx.h"
#include "CPattern.h"
#include "AbstractFactory.h"
CPattern::CPattern()
{
	Initialize();
} 

CPattern::~CPattern()
{
}

void CPattern::Initialize()
{
	m_DelayTime = rand() % (8000 + 1 - 1000) + 4000;
}

void CPattern::Attack(POINT& _Posin, float _fAngle)
{
	m_pBullet->push_back(CAbstractFactory<CBullet>::Create((float)_Posin.x, (float)_Posin.y, _fAngle,"Enemy"));
}

void CPattern::Set_BulletList(list<CObj*>* pBullet)
{
	m_pBullet = pBullet;
}

void CPattern::Update(POINT& _Posin, int i)
{
	int a = GetTickCount();
	switch (i)
	{
		case 1://�ѹ� ���
		{
			DWORD currentTickCount = GetTickCount();
			if (currentTickCount - m_Time >= m_DelayTime || !m_bIsEnd)
			{
				m_Time = GetTickCount();
				Attack(_Posin, m_fAngle);
				m_bIsEnd = true;
			}
		}
			break;
		case 2://360���� ���
		{
			DWORD currentTickCount = GetTickCount();//���� ������
			if (currentTickCount - m_Time >= m_DelayTime || !m_bIsEnd) // �ð��� �Ǿ��ų� �Ȳ�������
			{
				m_Time = GetTickCount();//�ð��� ��ӵ�����

				POINT tempPosin = _Posin;
				tempPosin.y -= 20.f;
				for (int i = 0; i < 36; i++)
				{
					Attack(tempPosin, m_fAngle + (10 * i));
				}
				m_bIsEnd = true;
			}
		}
			break;
		case 3://4������
		{
			DWORD currentTickCount = GetTickCount();//���� ������
			if (currentTickCount - m_Time >= m_DelayTime || !m_bIsEnd) // �ð��� �Ǿ��ų� �Ȳ�������
			{
				m_Time = GetTickCount();//�ð��� ��ӵ�����
				m_fAngle -= 20.f;
				for (int i = 0; i < 4; i++)
				{
					Attack(_Posin, m_fAngle += 10);
				}
				m_bIsEnd = true;
				
			}
		}
			break;
		break;
		default:
			break;
	}
}
