#include	"GameApp.h"

CImeProc* pp = new CImeProc();

int WINAPI _tWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow )
{
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

	Mof::LPFramework pFrame = new Mof::CDX11GameFramework(); 
	Mof::WINDOWSGAMEFRAMEWORKINITIALIZEINFO Info;
	Info.WindowCreateInfo.pProc = pp;
	Info.WindowCreateInfo.Width = 1920;
	Info.WindowCreateInfo.Height = 1080;
	Info.pApplication = new CGameApp();
	//Info.GraphicsCreateInfo.bWindowed = FALSE;
	Info.GraphicsCreateInfo.bWindowed = TRUE;
	Info.GraphicsCreateInfo.bMSAA = FALSE;
	if ( pFrame->Initialize(&Info) )
	{
		pFrame->Run();
	}
	MOF_SAFE_DELETE(pFrame);
	return 0;
}