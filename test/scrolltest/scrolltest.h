#include <QtGui>
#include <QMainWindow>

#include "../../lyxlib/scrollbar.h"

class Window : public QMainWindow {
	Q_OBJECT
	public:
		Window(QWidget *parent = 0);
		~Window();
};
