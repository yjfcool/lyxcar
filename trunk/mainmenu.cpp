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

#include <QMessageBox>

#include "mainmenu.h"

AMainMenuButton::AMainMenuButton(QWidget * parent) {
	buttonImages.append(QPixmap("../skins/default/menu_u.png")); // Default
	buttonImages.append(QPixmap("../skins/default/menu_o.png")); // Over
	buttonImages.append(QPixmap("../skins/default/menu_p.png")); // Pressed

	setPixmap(buttonImages[0]);
	setMouseTracking(true);
}

void AMainMenuButton::mousePressEvent(QMouseEvent * ev) {
	setPixmap(buttonImages[2]);
}
void AMainMenuButton::mouseReleaseEvent(QMouseEvent * ev) {
	setPixmap(buttonImages[0]);
	emit activated();
}

/***********************************************************/

AMainMenuWidget::AMainMenuWidget(QWidget * parent) {
	resize(400, 500);
	setAutoFillBackground(true);
	setWindowFlags(Qt::SubWindow);
}


/***********************************************************/

