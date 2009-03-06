#include "jogtest.h"

Window::Window(QWidget *parent) {
	resize(800, 600);
	ASkinner *skinner = new ASkinner(this, "default");

	QWidget *cw = new QWidget(this);
	setCentralWidget(cw);
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
