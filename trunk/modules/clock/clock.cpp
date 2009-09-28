#include "clock.h"

#include <QTimer>
#include <QTime>
#include <QPainter>

ClockWidget::ClockWidget(QWidget * parent) : QWidget(parent) {
    QTimer * timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1000);

    setMinimumSize(200, 200);
}

ClockWidget::~ClockWidget() {}

void ClockWidget::paintEvent(QPaintEvent * event) {
      Q_UNUSED(event);
      static const QPoint hourHand[3] = {
         QPoint(7, 8),
         QPoint(-7, 8),
         QPoint(0, -40)
      };
      static const QPoint minuteHand[3] = {
         QPoint(7, 8),
         QPoint(-7, 8),
         QPoint(0, -70)
      };

      QColor hourColor(127, 127, 255);
      QColor minuteColor(255, 255, 255, 127);

      int side = qMin(width(), height());
      QTime time = QTime::currentTime();

      QPainter painter(this);
      painter.setRenderHint(QPainter::Antialiasing);
      painter.translate(width() / 2, height() / 2);
      painter.scale(side / 200.0, side / 200.0);

      painter.setPen(Qt::NoPen);
      painter.setBrush(hourColor);

      painter.save();
      painter.rotate(30.0 * ((time.hour() + time.minute() / 60.0)));
      painter.drawConvexPolygon(hourHand, 3);
      painter.restore();

      painter.setPen(hourColor);

      for (int i = 0; i < 12; ++i) {
         painter.drawLine(88, 0, 96, 0);
         painter.rotate(30.0);
      }

      painter.setPen(Qt::NoPen);
      painter.setBrush(minuteColor);

      painter.save();
      painter.rotate(6.0 * (time.minute() + time.second() / 60.0));
      painter.drawConvexPolygon(minuteHand, 3);
      painter.restore();

      painter.setPen(minuteColor);

    for (int j = 0; j < 60; ++j) {
	if ((j % 5) != 0) painter.drawLine(92, 0, 96, 0);
	painter.rotate(6.0);
    }
	
}

ClockModule::ClockModule(QObject * parent) : QObject(parent) {

}

ClockModule::~ClockModule() {
    delete m_widget;
}
   
QWidget * ClockModule::activate(QWidget * parent) {
    return 0;
}

void ClockModule::deactivate(QString deactivateFor) {
    emit deactivated(deactivateFor);
}

QWidget * ClockModule::activateApplet(QWidget * parent) {
    Q_UNUSED(parent);

    m_widget = new ClockWidget(parent);

    return m_widget;
}

Q_EXPORT_PLUGIN2(clock, ClockModule);

