/*
 * Copyright (C) 2008-2009 Pavlov Denis
 *
 * Comments unavailable.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or any later version.
 *
*/

#ifndef __JOGDIAL_H__
#define __JOGDIAL_H__

#include "control.h"
#include "skinner.h"

class ALyxJogdial : public ALyxControl {
    Q_OBJECT
    public:
	ALyxJogdial(QWidget *parent = 0, ASkinner *s = 0);
	~ALyxJogdial();
};

#endif
