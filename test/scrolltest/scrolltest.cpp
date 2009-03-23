#include "scrolltest.h"

Window::Window(QWidget *parent) {
	resize(400, 300);
	ASkinner *skinner = new ASkinner(this, "default");

	ALyxScrollBar *bar = new ALyxScrollBar(this, skinner);
	bar->setMinimumPosition(10);
	bar->setMaximumPosition(100);
	setCentralWidget(bar);

}

Window::~Window() {

}

int main(int argc, char * argv[]) {
	QApplication app(argc, argv);

	Window win(qobject_cast<QWidget *>(QApplication::desktop()));
	win.show();

	app.exec();
	
	return 0;
}
