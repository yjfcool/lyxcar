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

	QLayout *layout = new QHBoxLayout();
	setLayout(layout);

	QPalette pal = palette();
	QPixmap bgImg("../skins/default/volctl/volctl_panel_bg.png");
	QBrush brush = QBrush();
	brush.setTexture(bgImg);
	pal.setBrush(QPalette::Window, brush);
	setPalette(pal);
	setAutoFillBackground(true);

	// Установить скиновые картинки для кнопок
	vol_up_button = new ALyxButton();
	vol_down_button = new ALyxButton();
	vol_mute_button = new ALyxButton();

	vol_up_button->setUpPixmap(QPixmap("../skins/default/volctl/volctl_volume_up.png"));
	vol_down_button->setUpPixmap(QPixmap("../skins/default/volctl/volctl_volume_down.png"));
	vol_mute_button->setUpPixmap(QPixmap("../skins/default/volctl/volctl_mute.png"));

	layout->addWidget(vol_up_button);
	layout->addWidget(vol_down_button);
	layout->addWidget(vol_mute_button);
}

volCtlModuleApplet::~volCtlModuleApplet() {

}

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
