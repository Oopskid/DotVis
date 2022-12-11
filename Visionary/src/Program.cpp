#include "VisionApp.h"

int main()
{
	VisionApp w;
	w.appContext(L"bxcxb");
	w.create(L"Bean", 1000, 1000);
	
	w.show();
	w.run();

	return 0;
}