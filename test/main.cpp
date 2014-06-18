/* 
 * This file part of sdcv - console version of Stardict program
 * http://sdcv.sourceforge.net
 * Copyright (C) 2003-2006 Evgeniy <dushistov@mail.ru>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Library General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#include <cerrno>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <clocale>
#include <string>
#include <vector>
#include <memory>
#include <iostream>

#include "clsStarDict.h"

int main(int argc, char *argv[])
{
    if (argc < 3){
        std::cerr<<"Invalid count of arguments"<<std::endl;
        std::cerr<<"USAGE: test <stardict file> <word>"<<std::endl;
        exit(0);
    }

    clsSDict StarDict;
    StarDict.loadDics(argv[1]);

    std::cout<<StarDict.lookupWords(argv[2])<<std::endl;
	return EXIT_SUCCESS;
}
