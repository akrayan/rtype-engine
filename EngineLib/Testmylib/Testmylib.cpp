// Testmylib.cpp : définit le point d'entrée pour l'application console.
//

#include "Header.h"

int main()
{
	Application App;

	App.SetDefaultScene("Scene/test.scene");
	App.AddAScript<SScroll>("SScroll");
	App.AddAScript<SPlayer>("SPlayer");
	App.AddAScript<SLevel>("SLevel");
	App.AddAScript<SLevel>("SMob");
	App.AddAScript<SBullet>("SBullet");
	App.AddAScript<SGround>("SGround");
	App.initServer();
	App.runApp();
	//App.Launch();

	//GameObject *g = new GameObject(m, "pute");
	// Create the main window

}