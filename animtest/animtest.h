#include <QtGui>
#include <QMainWindow>

#include "../buttons.h"
#include "../animated.h"
#include "../skinner.h"

class Window : public QMainWindow {
	Q_OBJECT
	public:
		Window(QWidget *parent = 0);
		~Window();
};
