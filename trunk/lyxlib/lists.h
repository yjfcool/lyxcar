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

#ifndef __LISTS_H__
#define __LISTS_H__

#include <QWidget>
#include <QStringList>
#include <QLabel>
#include <QList>
#include <QScrollArea>
#include <QBoxLayout>
#include <QTimer>

#include "list_pix.h"
#include "skinner.h"
#include "scrollbar.h"
#include "control.h"

class ALyxListWidgetItem : public QObject {
	Q_OBJECT
	public:
		ALyxListWidgetItem(QObject *parent = 0, QString text = "", QPixmap pixmap = QPixmap()) :
			QObject(parent) {
			m_visible = true;
			m_text = text;
			m_pixmap = pixmap;
			m_textColor = QColor("black");
		}
		~ALyxListWidgetItem() { qDebug() << "ALyxListWidgetItem destroyed"; }

		QString text() { return m_text; }
		void setText(QString t) { m_text = t; }

		QPixmap pixmap() { return m_pixmap; }
		void setPixmap(QPixmap p) { m_pixmap = p; }

		int height() { return m_height; }
		void setHeight(int h) { m_height = h; }
		
		int width() { return m_width; }
		void setWidth(int w) { m_width = w; }

		void setVisible(bool visible) {
			m_visible = visible;
		}
		bool visible() { return m_visible; }

		QRect rect() { return m_rect; }
		void setRect(QRect rect) { m_rect = rect; }

		QColor textColor() { return m_textColor; }
		void setTextColor(QColor color) { m_textColor = color; }
	private:
		QRect m_rect;
		QString m_text;
		QPixmap m_pixmap;
		int m_height;
		int m_width;
		bool m_visible;
		QColor m_textColor;
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

		//! \brief Gets currently selected item index
		int selectedIndex();
		//! \brief Gets currently selected item
		ALyxListWidgetItem *selectedItem();

		//! \brief Clears the list widget
		void clear();

		//! \brief Sets list skinned parametres
		void setSkin(ASkinner *s, QString moduleName, QString listName);

	private:
		QTimer	*animationTimer;

		QFont l_font;

		ASkinner *m_skinner;

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
		void scroll(int position, int steps);
		
	protected:
		void paintEvent(QPaintEvent *e);
		void resizeEvent(QResizeEvent *e);
		void mousePressEvent(QMouseEvent *e);
};

#endif

