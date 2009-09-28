#ifndef _CLOCK_H_
#define _CLOCK_H_

#include "m_interface.h"
#include <QWidget>

class ClockWidget : public QWidget
{
      Q_OBJECT

      public:
         explicit ClockWidget(QWidget * parent = 0);
         virtual ~ClockWidget();

      protected:
         void paintEvent(QPaintEvent * event);
};

class ClockModule : public QObject, public M_Interface
{
      Q_OBJECT
      Q_INTERFACES(M_Interface)

      public:
         explicit ClockModule(QObject * parent = 0);
         virtual ~ClockModule();

         QWidget * activate(QWidget * parent = 0);
         QWidget * activateApplet(QWidget * parent = 0);
         void deactivate(QString deactivateFor);

      signals:
		   void deactivated(QString deactivateFor);

      private:
         QWidget * m_widget;
};

#endif // _CLOCK_H_
