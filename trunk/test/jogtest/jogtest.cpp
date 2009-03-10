#include "jogtest.h"

Window::Window(QWidget *parent) {
	resize(800, 600);
	ASkinner *skinner = new ASkinner(this, "default");

	QWidget *cw = new QWidget(this);
	setCentralWidget(cw);
	
	ALyxJogdial *jog = new ALyxJogdial(this);
	jog->move(100, 100);
	jog->setFixedSize(210, 200);
	jog->addItem("Harddisk", QPixmap("./skins/default/mp3player/icons/drive-harddisk.png"));
	jog->addItem("USB disk", QPixmap("./skins/default/mp3player/icons/drive-removable-media-usb.png"));
	jog->addItem("CD disc", QPixmap("./skins/default/mp3player/icons/media-optical.png"));
	jog->addItem("Phone", QPixmap("./skins/default/mp3player/icons/phone.png"));
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
