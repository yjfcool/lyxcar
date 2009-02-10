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

#include "module_template.h"

templateModuleApplet::templateModuleApplet(QWidget *parent) {

}

templateModuleApplet::~templateModuleApplet() {

}

void templateModule::activate(QWidget *parent) {

}

void templateModule::activatePeriodically(QWidget *parent) {

}

//
// @brief Adding an applet to panel into specified position.
//
void templateModule::appendToPanel(QWidget *parent, int position) {

}

Q_EXPORT_PLUGIN2(template, templateModule);
