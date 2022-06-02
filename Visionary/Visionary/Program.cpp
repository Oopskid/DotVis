#include "VisionApp.h"

int main()
{
	VisionApp w;
	w.appContext(L"bxcxb");
	w.create(L"Bean", 100, 100);
	
	w.show();
	w.run();

	return 0;
}