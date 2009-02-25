#include "animtest.h"

Window::Window(QWidget *parent) {
	resize(800, 600);
	ASkinner *skinner = new ASkinner(this, "default");

	QWidget *cw = new QWidget(this);
	setCentralWidget(cw);

	ALyxButton *btn1 = new ALyxButton(this);
	btn1->setParent(cw);
	btn1->setUpPixmap(QPixmap("./skins/default/btn1_up.png"));
	btn1->setDownPixmap(QPixmap("./skins/default/btn1_down.png"));
	ALyxAnimation *anim = new ALyxAnimation(cw, btn1);

	anim->setAnimationTime(20);
	anim->stops << ALyxAnimationStop(0, 0, 0, 0, 0);
	anim->stops << ALyxAnimationStop(15, 20, 20, 432, 190);
	anim->stops << ALyxAnimationStop(18, 30, 30, 432, 190);
	anim->stops << ALyxAnimationStop(20, 20, 20, 432, 190);

	anim->start();

	ALyxButton *btn2 = new ALyxButton(this);
	btn2->setParent(cw);
	btn2->setUpPixmap(QPixmap("./skins/default/btn1_up.png"));
	btn2->setDownPixmap(QPixmap("./skins/default/btn1_down.png"));
	ALyxAnimation *anim2 = new ALyxAnimation(cw, btn2);

	anim2->setAnimationTime(30);
	anim2->stops << ALyxAnimationStop(0, 0, 200, 0, 0);
	anim2->stops << ALyxAnimationStop(10, 0, 200, 0, 0);
	anim2->stops << ALyxAnimationStop(25, 20, 230, 432, 190);
	anim2->stops << ALyxAnimationStop(28, 30, 240, 432, 190);
	anim2->stops << ALyxAnimationStop(30, 20, 230, 432, 190);

	anim2->start();

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
