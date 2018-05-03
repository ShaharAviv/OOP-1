#ifdef _DEBUG
#pragma comment(lib, "sfml-main-d.lib")
#elif defined(NDEBUG)
#pragma comment(lib, "sfml-main.lib")
#else
#error "Unrecognized configuration!"
#endif

#include "EditorControler.h"
 int main()
{
	
	 EditorControler editor;
	 editor.run();

	return EXIT_SUCCESS;
}
