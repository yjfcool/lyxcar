#include "listtest.h"

Window::Window(QWidget *parent) {
	resize(400, 300);
	ASkinner *skinner = new ASkinner(this, "default");

	ALyxListWidget *list = new ALyxListWidget(this, skinner);
	setCentralWidget(list);

	ALyxListWidgetItem *item1 = new ALyxListWidgetItem(list);
	item1->setText("Hello1\nSecond string");
	list->addItem(item1);

	ALyxListWidgetItem *item2 = new ALyxListWidgetItem(list);
	item2->setText("Hello2\nOK Song");
	list->addItem(item2);

	ALyxListWidgetItem *item3 = new ALyxListWidgetItem(list);
	item3->setText("Hello3");
	list->addItem(item3);

	ALyxListWidgetItem *item4 = new ALyxListWidgetItem(list);
	item4->setText("Rammstein\nIch Will");
	list->addItem(item4);

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
