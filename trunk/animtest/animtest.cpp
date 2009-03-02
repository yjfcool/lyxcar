#include "animtest.h"

Window::Window(QWidget *parent) {
	resize(800, 600);
	ASkinner *skinner = new ASkinner(this, "default");

	QWidget *cw = new QWidget(this);
	setCentralWidget(cw);

	ALyxScrollLabel *lbl = new ALyxScrollLabel(cw, "My favorite song - Song number one");
//	lbl->setParent(cw);
	lbl->setFont(QFont("Calibri", 20));
	lbl->setText("My favorite song - Song number one");
	lbl->setFixedWidth(200);
	lbl->move(100, 100);
	lbl->startScrollImmediate();
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
