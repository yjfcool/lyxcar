/*
 * Copyright (C) 2008 Pavlov Denis
 *
 * Comments unavailable.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or any later version.
 *
*/

#include <QWidget>
#include <QStringList>
#include <QLabel>
#include <QList>
#include <QScrollArea>
#include <QBoxLayout>
#include <QTimer>

#include "skinner.h"
#include "scrollbar.h"
#include "control.h"

class ALyxListWidgetItem : public QObject {
	Q_OBJECT
	public:
		ALyxListWidgetItem(QObject *parent = 0) {}
		~ALyxListWidgetItem() {}

		QString text() { return m_text; }
		void setText(QString t) { m_text = t; }

		QPixmap pixmap() { return m_pixmap; }
		void setPixmap(QPixmap p) { m_pixmap = p; }

		int height() { return m_height; }
		void setHeight(int h) { m_height = h; }

		QRect rect;
	private:
		QString m_text;
		QPixmap m_pixmap;
		int m_height;
};

typedef QList<ALyxListWidgetItem *> ALyxListWidgetItems;

//! \brief This class implements skinned listbox for LyxCar.
class ALyxListWidget : public ALyxControl {
	Q_OBJECT
	public:

		//! \brief Constructs listWidget with the skin specified by s
		/*!
			\param parent is a parent widget
			\param s is an ASkinner object
		*/
		ALyxListWidget(QWidget *parent = 0, ASkinner *s = 0);
		~ALyxListWidget();

		//! \brief Returns list of items contained in a Widget.
		ALyxListWidgetItems items() { return l_items; }

		//! \brief Add an item to the list widget
		void addItem(ALyxListWidgetItem *item);
		//! \brief Sets item specified as a currently selected item
		void setSelectedItem(ALyxListWidgetItem *item);
	
	private:
		QTimer	*animationTimer;

		QFont l_font;
		int l_verticalSpacing;	// Item top and bottom spacing
		int l_paddingLeft;
		int l_paddingRight;
		int l_paddingTop;
		int l_paddingBottom;

		int l_paddingSelector; // Padding from window left to selector

		int m_scrollBarPaddingEdge;
		int m_scrollBarPaddingTop;
		int m_scrollBarPaddingBottom;

		int m_scrollPosition; // Current scroller position
		int m_scrollMax; // Maximum scrolling position

		ALyxListWidgetItems l_items;
		int m_defaultItemHeight;

		ALyxListWidgetItem *m_selectedItem;
		int m_selectedIndex;

		int animationStep;	// -1 move up, 1 move down, 0 stop
		QPoint m_selectorPosition; // Position of top left corner
		int m_acceleration;

		void drawFrame();

		QPixmap corner_ul;
		QPixmap corner_ur;
		QPixmap corner_bl;
		QPixmap corner_br;
		QPixmap top;
		QPixmap bottom;
		QPixmap left;
		QPixmap right;
		QPixmap selector;
		QPixmap selector_fill;

		ALyxScrollBar *m_scrollBar;

	signals:
		void selected(ALyxListWidgetItem *item);

	public slots:
		void selectItem(int itemIndex);
		void selectItem(ALyxListWidgetItem *item);

	private slots:
		void animateSelector();

		
	protected:
		void paintEvent(QPaintEvent *e);
		void mousePressEvent(QMouseEvent *e);
};
