#include "DebugConsole.h"
#include "conioex.h"

#include <iostream>

FILE *fp;

DebugConsole::DebugConsole()
	:rectConsoleSize{0,0,1,1}
{
	m_pPile = NULL;

	AllocConsole();

	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleWindowInfo(hStdout, TRUE, &rectConsoleSize);

	SetConsoleScreenBufferSize(hStdout, coord);
	rectConsoleSize.Right = coord.X - 1;	
	rectConsoleSize.Bottom = coord.Y - 1;	
	SetConsoleWindowInfo(hStdout, TRUE, &rectConsoleSize);
	
	SetConsoleTitle("�f�o�b�O�R���\�[��");
	freopen_s(&fp, "CON", "w", stdout);    
}

DebugConsole::~DebugConsole()
{
	fclose(fp);
	FreeConsole();
}

void DebugConsole::Update()
{
	gotoxy(1, 1);
	if (!m_pPile == NULL)
	{//�Ȃ����N���A�X�N���[���g���Ƌ����������������߁A�󔒂ő�p
		printf("���C��%d        ", m_pPile->Get_Line());
		gotoxy(1, 2);
		printf("�U����%d        ", m_pPile->GetAttack());
	}
}

void DebugConsole::SetPile(PileBanker * pPile)
{
	m_pPile = pPile;
}
