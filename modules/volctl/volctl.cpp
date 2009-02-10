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

#include "volctl.h"

volCtlModuleApplet::volCtlModuleApplet(QWidget *parent) {
	// 220px ширина апплета
	setFixedWidth(220);

	QBoxLayout *layout = new QHBoxLayout();
	setLayout(layout);

	QPalette pal = palette();
	QPixmap bgImg("../skins/default/volctl/volctl_panel_bg.png");
	QBrush brush = QBrush();
	brush.setTexture(bgImg);
	pal.setBrush(QPalette::Window, brush);
	setPalette(pal);
	setAutoFillBackground(true);

	// Установить скиновые картинки для кнопок
	vol_up_button = new ALyxButton(this);
	vol_down_button = new ALyxButton(this);
	vol_mute_button = new ALyxButton(this);

	vol_up_button->setUpPixmap(QPixmap("../skins/default/volctl/volctl_volume_up.png"));
	vol_down_button->setUpPixmap(QPixmap("../skins/default/volctl/volctl_volume_down.png"));
	vol_mute_button->setUpPixmap(QPixmap("../skins/default/volctl/volctl_mute.png"));

	vol_up_button->setDownPixmap(QPixmap("../skins/default/volctl/volctl_volume_up_act.png"));
	vol_down_button->setDownPixmap(QPixmap("../skins/default/volctl/volctl_volume_down_act.png"));
	vol_mute_button->setDownPixmap(QPixmap("../skins/default/volctl/volctl_mute_act.png"));

	connect(vol_up_button, SIGNAL(clicked()), this, SLOT(volume_up()));
	connect(vol_down_button, SIGNAL(clicked()), this, SLOT(volume_down()));
	connect(vol_mute_button, SIGNAL(clicked()), this, SLOT(volume_mute()));

	layout->setSpacing(0);
	layout->setContentsMargins(0, 0, 0, 0);
	layout->addStretch(1);
	layout->addWidget(vol_up_button);
	layout->addWidget(vol_down_button);
	layout->addWidget(vol_mute_button);
	layout->addStretch(1);
}

volCtlModuleApplet::~volCtlModuleApplet() {

}

//
// @brief Volume control functions.
// Functions for increasing and decreasing volume level and for muting.
//
void volCtlModuleApplet::volume_up() {
	qDebug() << "Volume UP button pressed";
}

void volCtlModuleApplet::volume_mute() {
	qDebug() << "Volume MUTE button pressed";
}

void volCtlModuleApplet::volume_down() {
	qDebug() << "Volume DOWN button pressed";
}

//
// @brief Module activation function.
// Module activation stands for executing its code in main area of
// an interface window.
//
void volCtlModule::activate(QWidget *parent) {

}

/*
 * Добавление апплета модуля на панель в указанную позицию
*/
void volCtlModule::appendToPanel(APanel *panel, int position) {
	// Создаем виджет апплета
	appletWidget = new volCtlModuleApplet() ;	

	// Добавляем его на панель
	panel->layout->insertWidget(position, appletWidget, 0);
}

Q_EXPORT_PLUGIN2(volCtl, volCtlModule);
