#include	"GameApp.h"

CImeProc* pp = new CImeProc();
int WINAPI _tWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow )
{
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

	Mof::LPFramework pFrame = new Mof::CDX11GameFramework(); 
	Mof::WINDOWSGAMEFRAMEWORKINITIALIZEINFO Info;
	Info.WindowCreateInfo.pProc = pp;
	Info.pApplication = new CGameApp();
	Info.GraphicsCreateInfo.bWindowed = TRUE;
	Info.GraphicsCreateInfo.bMSAA = FALSE;
	Info.WindowCreateInfo.Width = 1280;
	Info.WindowCreateInfo.Height = 720;
	if ( pFrame->Initialize(&Info) )
	{
		pFrame->Run();
	}
	MOF_SAFE_DELETE(pFrame);
	return 0;
}