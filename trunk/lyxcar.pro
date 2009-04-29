TEMPLATE = subdirs
SUBDIRS = lyxlib \
	  3rdparty/phonon \
	  app \
	  modules/clock \
	  modules/volctl \
          modules/default_home \
	  modules/mp3player \
	  modules/phone

CONFIG += ordered release
