/*
 * Copyright (C) 2008 Pavlov Denis
 *
 * This is a skin engine implementation.
 * Engine is used by EVERY module to make it look like a main window
 * of an application.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or any later version.
 *
 */

#ifndef __SKINNER_H__
#define __SKINNER_H__

#include <QtXml>
#include <QtGui>
#include <QString>

//! Skinner is a skin microengine class for this application.
/*!
  Skinner uses XML file for skin description, then reads it and provides methods for reading
  interface objects skin properties.
  */
class ASkinner : public QObject {
   public:
      //! \brief Constructor
      /*!
        \param parent specifies parent object
        \param skinName specifies skin directory name
        */
      ASkinner(QObject *parent = 0, QString skinName = "");
      ~ASkinner() {}

      //! \brief Loads skin specified by the name
      /*!
        \param name specifies skin directory name
        */
      int loadSkin(QString name);

      //! \brief Gets value from skin configuration file
      /*!
        The value is determined my three parameters.
        \param part is a part of configuration
        \param root is an object, e.g. "panel" or "" for main window.
        \param attribute determines the name of an attribute to read
        */
      QString	skinValue(QString part = "", QString root = "", QString attribute = "");
      //! \brief Gets value from module-specific skin configuration file
      /*!
        The value is determined my three parameters.
        \param module is a name of module.
        \param object is an object, e.g. "volume_up_button" or "background".
        \param attribute determines the name of an attribute to read
        */
      QString	skinModuleValue(QString module = "", QString object = "", QString attribute = "");
      //! \brief Gets value from skin configuration file. The same as skinValue but thinks that parameter is an image link.
      QString	skinImage(QString part = "", QString root = "", QString attribute = "");
      //! \brief Gets value from module-specific skin configuration file. The same as skinModuleValue but thinks that parameter is an image link.
      QString	skinModuleImage(QString module = "", QString object = "", QString attribute = "");
      //! \brief Gets skin images storage by module name.
      /*
         \param module is a module name.
         */
      QString skinModuleImagePath(QString module = "");
      //! \brief Gets DOM container from module-specific skin configuration file. Gets a Dom element of module object's configuration.
      /*!
        \param module is a name of module.
        \param elementName is a name of element to get.
        */
      QDomElement skinModuleElement(QString module, QString elementName);

      //! \brief Gets DOM container from module-specific skin configuration file by object type (tag name) and object name (the "name" attribute).
      /*!
        \param module is a name of module
        \param element is a type of object (tag name)
        \param elementName is a name of an element (the "name" attribute)
        */
      QDomElement skinModuleElementByName(QString module, QString element, QString elementName);

   private:
      QString	skinsPath;
      QString	skinName;

      QDomDocument * skin;

      QDomElement skinRoot;
      QDomElement panel;
      QDomElement modules;
};

#endif
