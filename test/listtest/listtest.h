#include <QtGui>
#include <QMainWindow>

#include "../../lyxlib/lists.h"

class Window : public QMainWindow {
	Q_OBJECT
	public:
		Window(QWidget *parent = 0);
		~Window();
};
