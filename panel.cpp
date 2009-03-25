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

#include "panel.h"
#include "mainmenu.h"

APanel::APanel(QWidget *parent, ASkinner *s) : QWidget(parent) {

	skinner = s;

	setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
	setFixedHeight(skinner->skinValue("", "panel", "height").toInt());

	QHBoxLayout *layout = new QHBoxLayout(this); setLayout(layout);
	infoBar = new QWidget(this);

	QPalette pal = palette();
	QPixmap bgImg(skinner->skinImage("", "panel", "background"));
	pal.setBrush(QPalette::Window, QBrush(bgImg));
	setPalette(pal);
	setAutoFillBackground(true);

	layout->setSpacing(0);
	layout->setContentsMargins(skinner->skinValue("", "panel", "padding-left").toInt(), 0,
         skinner->skinValue("", "panel", "padding-right").toInt(), 0);
//        layout->insertWidget(0, new QWidget(), 5);
        layout->insertStretch(0, 5);

//	button = new AMainMenuButton(this);
//	layout->insertWidget(0, button);

/*	widget = new AMainMenuWidget(parent);
	widget->setParent(parent);
	widget->setAutoFillBackground(true);
	widget->move(0, 600-500-79);
	widget->hide();             

	QPalette pal_menu = palette();
	QPixmap bgImg2("../skins/default/mbg2.png");
	brush.setTexture(bgImg2);
	pal_menu.setBrush(QPalette::Window, brush);
	widget->setPalette(pal_menu);

	connect(button, SIGNAL(activated()), this, SLOT(popup()));*/
}

APanel::~APanel() {}

void APanel::fill() {

	//
	// !!!! Вынести в меню !!!!
	//

	scroller = new QScrollArea(widget);
	scroller->move(0, 95);
	scroller->resize(393, 375);
	scroller->setWidgetResizable(true);

	QWidget *menuArea = new QWidget(scroller);
	menuArea->setPalette(QPalette(QPalette::Normal));
	scroller->setPalette(QPalette(QPalette::Normal));

	menuArea->setLayout(new QVBoxLayout());

	QDir	dir("./conf/menus");
	QStringList itemFiles = dir.entryList(QDir::Files);
	foreach(QString itemFile, itemFiles) {

		QString itemName;
		QString itemIcon;
		QString itemDesc;

		QFile file("./conf/menus/"+itemFile);
		file.open(QIODevice::ReadOnly | QIODevice::Text);
		while(!file.atEnd()) {
			QString line = file.readLine();

			QRegExp re("^([a-zA-Z]+)=(.*)\n$");
			re.indexIn(line, 0);
			if(re.cap(1) == "Name") { itemName = re.cap(2); }
			if(re.cap(1) == "Icon") { itemIcon = re.cap(2); }
			if(re.cap(1) == "Description") { itemDesc = re.cap(2); }
		}

		items << new QToolButton(menuArea);
		items.last()->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		items.last()->setText(itemName+"\n"+itemDesc);
		items.last()->setIcon(QIcon("./skins/default/icons/"+itemIcon));
		items.last()->setIconSize(QSize(32, 32));
		items.last()->setAutoRaise(true);
		items.last()->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
		((QBoxLayout *)menuArea->layout())->addWidget(items.last());
	}

	scroller->setWidget(menuArea);
}

void APanel::popup() {
	if(widget->isVisible()) {
		widget->hide();
		emit repaintModuleArea();
	} else {
		widget->show();
		widget->raise();
	}
}
