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
 
 Properties:
 
 - padding from frame to selector
 - padding from selector to item text
 
*/

#define MIN_ACCELERATION 6

#include "lists.h"
#include <QPushButton>

ALyxListWidget::ALyxListWidget(QWidget *parent, ASkinner *s) : ALyxControl(parent) {
	m_skinner = s;

	l_font = QFont("Calibri", 12);
	l_paddingTop = 15;
	l_paddingLeft = 15;
	l_paddingRight = 25;
	l_paddingSelector = 5;
	l_verticalSpacing = 0;
	
	// Scrollbar paddings
	m_scrollBarPaddingTop = 15;
	m_scrollBarPaddingBottom = 15;
	m_scrollBarPaddingEdge = 15;
	m_scrollPosition = 0;

	m_defaultItemHeight = 65;
	m_acceleration = MIN_ACCELERATION;
	m_selectorPosition.setX(l_paddingSelector);
	m_selectorPosition.setY(0);
	m_selectedItem = 0;
	m_selectedIndex = -1;
	animationStep = 0;

	m_scrollBar = new ALyxScrollBar(this, s);
	m_scrollBar->setSingleStep(10);
	m_scrollBar->setMinimumPosition(0);
	m_scrollBar->setMaximumPosition(10);

	connect(m_scrollBar, SIGNAL(changed(int, int)), this, SLOT(scroll(int, int)));
	
	setAttribute(Qt::WA_NoSystemBackground, true);

	corner_ul = QPixmap(list_ul_xpm);
	corner_bl = QPixmap(list_bl_xpm);
	corner_br = QPixmap(list_br_xpm);
	corner_ur = QPixmap(list_ur_xpm);
	top = QPixmap(list_u_xpm);
	bottom = QPixmap(list_b_xpm);
	right = QPixmap(list_r_xpm);
	left = QPixmap(list_l_xpm);
	selector = QPixmap();
	selector_fill = QPixmap();

	animationTimer = new QTimer(this);
	animationTimer->setInterval(10);
	connect(animationTimer, SIGNAL(timeout()), this, SLOT(animateSelector()));
}

ALyxListWidget::~ALyxListWidget() {}

void ALyxListWidget::setSkin(ASkinner *skinner, QString moduleName, QString listName) {
	ASkinner *t_skinner; // Temporary object
	if(skinner != NULL) {
		t_skinner = skinner;
	} else {
		t_skinner = m_skinner;
	}

	if(t_skinner == NULL) {
		qDebug() << "Error: skinned object is undefined";
		return;
	}

	QDomElement listElement = t_skinner->skinModuleElementByName(moduleName, "list", listName);

	QDomElement rectElement = listElement.firstChildElement("rect");
	if(!rectElement.isNull()) {
		move(rectElement.attribute("x").toInt(), rectElement.attribute("y").toInt());
		setFixedSize(rectElement.attribute("width").toInt(), rectElement.attribute("height").toInt());
	} else {
	 	qDebug() << "Warning: no initial rectangle for" << objectName() << "defined";
	}

	QDomElement bordersElement = listElement.firstChildElement("borders");
	if(!bordersElement.isNull()) {
		corner_ul = QPixmap(t_skinner->skinModuleImagePath(moduleName)+bordersElement.attribute("upper-left"));
		corner_bl = QPixmap(t_skinner->skinModuleImagePath(moduleName)+bordersElement.attribute("bottom-left"));
		corner_br = QPixmap(t_skinner->skinModuleImagePath(moduleName)+bordersElement.attribute("bottom-right"));
		corner_ur = QPixmap(t_skinner->skinModuleImagePath(moduleName)+bordersElement.attribute("upper-right"));
		top = QPixmap(t_skinner->skinModuleImagePath(moduleName)+bordersElement.attribute("top"));
		bottom = QPixmap(t_skinner->skinModuleImagePath(moduleName)+bordersElement.attribute("bottom"));
		right = QPixmap(t_skinner->skinModuleImagePath(moduleName)+bordersElement.attribute("right"));
		left = QPixmap(t_skinner->skinModuleImagePath(moduleName)+bordersElement.attribute("left"));
	} else {
	 	qDebug() << "Warning: no borders defined for list" << objectName();
	}

	QDomElement selectorElement = listElement.firstChildElement("selector");
	if(!selectorElement.isNull()) {
		selector = QPixmap(t_skinner->skinModuleImagePath(moduleName)+selectorElement.attribute("image"));
		selector_fill = QPixmap(t_skinner->skinModuleImagePath(moduleName)+selectorElement.attribute("fill"));
	} else {
	 	qDebug() << "Warning: no selector defined for list" << objectName();
	}
}

// Adds new item to the list
void ALyxListWidget::addItem(ALyxListWidgetItem *item) {
	item->setHeight(m_defaultItemHeight);
	l_items << item;

	int t_totalHeight = 0;
	foreach(ALyxListWidgetItem *item, l_items) {
		t_totalHeight+= item->height();
	}

	if(t_totalHeight > height()) {
		t_totalHeight-=height()-l_paddingTop;
		m_scrollBar->setMaximumPosition(t_totalHeight);
	} 


	repaint();
}

// Sets currently selected item by item object
void ALyxListWidget::setSelectedItem(ALyxListWidgetItem *item) {
	m_selectedItem = item;
	m_selectedIndex = l_items.indexOf(item);
	repaint();
}

void ALyxListWidget::resizeEvent(QResizeEvent *e) {
	Q_UNUSED(e);
	m_scrollBar->setFixedSize(60, height()-m_scrollBarPaddingTop-m_scrollBarPaddingBottom);
	m_scrollBar->move(width()-m_scrollBar->width(), m_scrollBarPaddingTop);
}

void ALyxListWidget::mousePressEvent(QMouseEvent *e) {
	Q_UNUSED(e);
	// ¬ычисл€ем куда двигать селектор и устанавливаем animationStep в -1 или 1.
	// ”станавливаем m_selectedItem и запускаем анимацию селектора.
	foreach (ALyxListWidgetItem *item, items()) {
		// “рансформируем Y-координату в соответствии с позицией прокрутки, т.е. учитываем
		// прокрутку при определении кликнутого пункта.
		QPoint t_pos = e->pos();
		t_pos.setY(t_pos.y());
		if(item->rect().contains(t_pos)) {
			int prev_selectedIndex = m_selectedIndex;
			setSelectedItem(item);
			emit selected(item);
			emit clicked();
			if(prev_selectedIndex < m_selectedIndex) {
				animationStep = 1;
			} else if(prev_selectedIndex > m_selectedIndex) {
				animationStep = -1;
			}
			animationTimer->start();
		}
	}	
}

void ALyxListWidget::mouseDoubleClickEvent(QMouseEvent *e) {
	Q_UNUSED(e);
	emit doubleClicked();
}

void ALyxListWidget::animateSelector() {
	// ≈сли заведена анимашка, рисуем селектор в позиции m_selectorPosition
	// при этом мен€ем ее в зависимости от animationStep.
	// ѕри достижении селектором верхнего левого угла выбраного пункта списка m_selectedItem анимацию завершаем!
	// ѕункт выбираетс€ сразу после нажати€ на него мышкой устанавлива€ m_selectedItem в указатель на нажатый объект!
	
	// —електор по любому рисуетс€ только в позиции того пункта который выбран. ј в ней уже заложен скрол!
	if(animationStep != 0) {
		m_selectorPosition.setY(m_selectorPosition.y()+(m_acceleration*animationStep));
		m_acceleration++;
		if(((m_selectorPosition.y() <= m_selectedItem->rect().y() && animationStep < 0)) || 
		   ((m_selectorPosition.y() >= m_selectedItem->rect().y() && animationStep > 0))) {
			animationTimer->stop();
			m_acceleration = MIN_ACCELERATION;
			m_selectorPosition.setY(m_selectedItem->rect().y());
		}
		repaint();
	}
}

void ALyxListWidget::paintEvent(QPaintEvent *e) {
   Q_UNUSED(e);
	QPainter p(this);

	// Draw skinned frame of the listWidget
	/*** “ут все завершено! ***/
	p.drawPixmap(0, 0, corner_ul); // Upper left
	p.drawPixmap(corner_ul.width(), 0, top.scaled(width() - corner_ul.width() - corner_ur.width() - l_paddingRight, corner_ul.height())); // Top
	p.drawPixmap(0, height()-corner_bl.height(), corner_bl); // Bottom left
	p.drawPixmap(corner_bl.width(), height() - corner_bl.height(), bottom.scaled(width() - corner_bl.width() - corner_br.width()-l_paddingRight, corner_bl.height())); // Bottom
	p.drawPixmap(width()-corner_br.width()-l_paddingRight, height()-corner_br.height(), corner_br); // Bottom right
	p.drawPixmap(width()-corner_ur.width()-l_paddingRight, 0, corner_ur); // Upper right
	p.drawPixmap(width()-corner_ur.width()-l_paddingRight, corner_ur.height(), right.scaled(corner_ur.width(), height() - corner_ur.height() - corner_br.height())); // Right
	p.drawPixmap(0, corner_ul.height(), left.scaled(corner_ur.width(), height() - corner_ur.height() - corner_br.height())); // Left

	// Fill the center of a rect
	/*** “ут все завершено! ***/
	p.setBrush(QBrush(QColor("white")));
	p.setPen(QColor("white"));
	p.drawRect(corner_ul.width(),
		corner_ul.height(),
		width() - corner_ul.width() - corner_ur.width() -l_paddingRight, 
		height() - corner_ur.height() - corner_br.height());

	QImage temporaryImage(width(), height(), QImage::Format_ARGB32_Premultiplied);
	QPainter temporary(&temporaryImage);

	// Clear transparency
	/*** “ут все завершено! ***/
	temporary.setBrush(QColor("white"));
	temporary.setCompositionMode(QPainter::CompositionMode_Clear);
	temporary.drawRect(0, 0, width(), height());
	temporary.setFont(l_font);
	temporary.setCompositionMode(QPainter::CompositionMode_SourceOver);

	// Draw selector
	if(m_selectedItem) {
		QPoint position = m_selectorPosition;
		position.setY(m_selectorPosition.y());
		temporary.drawPixmap(position, selector);
		temporary.drawTiledPixmap(position.x()+selector.width(),
				  position.y(),
				  width()-position.x()-selector.width()-l_paddingSelector-l_paddingRight,
				  selector.height(),
				  selector_fill);
	}

	//	
	// Draw items
	//
	temporary.setPen(QColor("black"));
	int cpos = l_paddingTop-m_scrollPosition;
	foreach (ALyxListWidgetItem *item, items()) {

		// Set item rect to real item position in list
		// ƒвигаем пр€моугольники при отрисокве если надо, то есть запоминаем 
		// все координаты пунктов при отрисовке с учетом скрола.
		item->setRect(QRect(l_paddingLeft, cpos, width(), item->height()));
		if(item->visible() && (item->rect().intersects(rect()))) {
			//
			// Draw item pixmap
			//
			int pixmap_offset = 0;
			if(!item->pixmap().isNull()) {
				temporary.drawPixmap(l_paddingLeft,
				   cpos+(item->height()-item->pixmap().height()) / 2, 
				   item->pixmap()
				);
				pixmap_offset = item->pixmap().width()+l_paddingLeft;
			}
			//
			// Draw item text
			//
			temporary.drawText(l_paddingLeft+pixmap_offset,
				   cpos, 
				   width(),
				   item->height(),
				   Qt::AlignVCenter,
				   item->text()
			);
		}
		cpos+=l_verticalSpacing+item->height();
	}

	//
	// Start blending
	//	
	temporary.setCompositionMode(QPainter::CompositionMode_DestinationIn);
	temporary.setPen(QColor(0, 255, 0, 255));
	
	// Blend bottom	
	QLinearGradient linearGrad(QPointF(0, height()-30), QPointF(0, height()-10));
	linearGrad.setColorAt(1, QColor(0, 255, 0, 0));
	linearGrad.setColorAt(0, QColor(0, 255, 0, 255));
	temporary.setBrush(QBrush(linearGrad));
	temporary.drawRect(0, height()-30, width(), height());

	// Blend top
	QLinearGradient linearGrad2(QPointF(0, 10), QPointF(0, 30));
	linearGrad2.setColorAt(0, QColor(0, 255, 0, 0));
	linearGrad2.setColorAt(1, QColor(0, 255, 0, 255));
	temporary.setBrush(QBrush(linearGrad2));
	temporary.drawRect(0, 0, width(), 30);

	// Restore composition mode
	temporary.setCompositionMode(QPainter::CompositionMode_SourceOver);
	temporary.end();

	p.drawImage(0, 0, temporaryImage);
	p.end();
}

void ALyxListWidget::selectItem(int itemIndex) {
	setSelectedItem(l_items[itemIndex]);
}

void ALyxListWidget::selectItem(ALyxListWidgetItem *item) {
	setSelectedItem(item);
}

ALyxListWidgetItem *ALyxListWidget::selectedItem() {
	return m_selectedItem;
}

int ALyxListWidget::selectedIndex() {
	return m_selectedIndex;
}

void ALyxListWidget::clear() {
	setSelectedItem(NULL);
	l_items.clear();
	repaint();
}

void ALyxListWidget::scroll(int position, int steps) {
//	qDebug() << "min:" << m_scrollBar->minimumPosition() << "max:" << m_scrollBar->maximumPosition() << "cur:" << position;

	if(m_scrollPosition > position) {
		m_selectorPosition.setY(m_selectorPosition.y()+m_scrollBar->singleStep());
	} else {
		m_selectorPosition.setY(m_selectorPosition.y()-m_scrollBar->singleStep());
	}
	m_scrollPosition = position;
	repaint();
}
