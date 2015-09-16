# Introduction #

This program uses Taglib to parse mp3 files tags. There's some complicicity with driving windows-1251 and utf-8 tags.

I assume that all tags in Unix systems are in utf-8. But when we build the program under Russian Windows we assume that all tags in windows-1251 and try to convert them automatically to utf-8.

That's why under Unix systems windows encoded tags are displayed incorrectly. Just use tag correction program to fix them.