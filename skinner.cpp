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

#include "skinner.h"

ASkinner::ASkinner() {

}

//
// @brief Create a skin object and load skin specified by skinName.
//
ASkinner::ASkinner(QString name) {
	if(loadSkin(name) > 0) {
		// Skin load error
	}
}

int ASkinner::loadSkin(QString name) {
	skinName = name;

	return 0; // Return 1 if loading error
}
