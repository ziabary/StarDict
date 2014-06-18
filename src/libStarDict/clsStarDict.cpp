/*************************************************************************
 * libStarDict - A C++ library to read stardict files
 * Copyright (C) 2013  S.M.Mohammadzadeh <mehran.m@aut.ac.ir>
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *************************************************************************/
/**
 @author S.Mohammad M. Ziabary <mehran.m@aut.ac.ir>
 */

#include "clsStarDict.h"
#include "Private/clsStarDict_p.h"

clsSDict::clsSDict()
{
    this->pPrivate = new clsSDictPrivate();
}

std::string clsSDict::lookupWords(const std::string& _phrase, bool _json)
{
    (void)_json;
    std::string Result;
    if (_phrase[0]=='\0')
        return Result;

    SearchResultList_t res_list;

    this->pPrivate->SimpleLookup(_phrase, res_list);
    if (!res_list.empty()) {
        for (SearchResultIter ptr=res_list.begin(); ptr!=res_list.end(); ++ptr)
        {
            Result = (ptr)->exp.substr(1);
            break;
        }
    }
    return Result;
}

void clsSDict::loadDics(const std::string& _dicDir)
{
    strlist_t dicts_dir_list;
    dicts_dir_list.push_back(_dicDir);

    strlist_t empty_list;
    this->pPrivate->load(dicts_dir_list, empty_list, empty_list);
}


