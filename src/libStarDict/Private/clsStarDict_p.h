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
/*
 * Copyright 2011 kubtek <kubtek@mail.com>
 *
 * This file is part of StarDict.
 *
 * StarDict is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * StarDict is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with StarDict.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __SD_LIB_H__
#define __SD_LIB_H__

#include <cstdio>
#include <list>
#include <memory>
#include <string>
#include <vector>

#include "dictziplib.hpp"

const int MAX_MATCH_ITEM_PER_LIB=100;
const int MAX_FUZZY_DISTANCE= 3; // at most MAX_FUZZY_DISTANCE-1 differences allowed when find similar words

//this structure is wrapper and it need for unification
//results of search whith return Dicts class
struct stuSearchResult {
    std::string bookname;
    std::string def;
    std::string exp;

    stuSearchResult(const std::string& bookname_, const std::string& def_, const std::string& exp_)
        : bookname(bookname_), def(def_), exp(exp_)
    {
    }
};

typedef std::vector<stuSearchResult> SearchResultList_t;
typedef SearchResultList_t::iterator SearchResultIter;

struct cacheItem {
    guint32 offset;
    gchar *data;
    //write code here to make it inline
    cacheItem() {data= NULL;}
    ~cacheItem() {g_free(data);}
};

const int WORDDATA_CACHE_NUM = 10;
const int INVALID_INDEX=-100;

class DictBase {
public:
    DictBase();
    ~DictBase();
    gchar * GetWordData(guint32 idxitem_offset, guint32 idxitem_size);
    bool containSearchData();
    bool SearchData(std::vector<std::string> &SearchWords, guint32 idxitem_offset, guint32 idxitem_size, gchar *origin_data);
protected:
    std::string sametypesequence;
    FILE *dictfile;
    std::auto_ptr<dictData> dictdzfile;
private:
    cacheItem cache[WORDDATA_CACHE_NUM];
    gint cache_cur;
};

//this structure contain all information about dictionary
struct DictInfo {
    std::string ifo_file_name;
    guint32 wordcount;
    std::string bookname;
    std::string author;
    std::string email;
    std::string website;
    std::string date;
    std::string description;
    guint32 index_file_size;
    std::string sametypesequence;
    bool load_from_ifo_file(const std::string& ifofilename, bool istreedict);
};

class index_file {
public:
    guint32 wordentry_offset;
    guint32 wordentry_size;

    virtual ~index_file() {}
    virtual bool load(const std::string& url, gulong wc, gulong fsize) = 0;
    virtual const gchar *get_key(glong idx) = 0;
    virtual void get_data(glong idx) = 0;
    virtual  const gchar *get_key_and_data(glong idx) = 0;
    virtual bool lookup(const char *str, glong &idx) = 0;
};

class Dict : public DictBase {
private:	
    std::string ifo_file_name;
    gulong wordcount;
    std::string bookname;

    std::auto_ptr<index_file> idx_file;

    bool load_ifofile(const std::string& ifofilename, gulong &idxfilesize);
public:
    Dict() {}
    bool load(const std::string& ifofilename);

    gulong narticles() { return wordcount; }
    const std::string& dict_name() { return bookname; }
    const std::string& ifofilename() { return ifo_file_name; }

    const gchar *get_key(glong index)	{	return idx_file->get_key(index);	}
    gchar *get_data(glong index)
    {
        idx_file->get_data(index);
        return DictBase::GetWordData(idx_file->wordentry_offset, idx_file->wordentry_size);
    }
    void get_key_and_data(glong index, const gchar **key, guint32 *offset, guint32 *size)
    {
        *key = idx_file->get_key_and_data(index);
        *offset = idx_file->wordentry_offset;
        *size = idx_file->wordentry_size;
    }
    bool Lookup(const char *str, glong &idx) { return idx_file->lookup(str, idx);	}

    bool LookupWithRule(GPatternSpec *pspec, glong *aIndex, int iBuffLen);
};

typedef std::list<std::string> strlist_t;

class clsSDictPrivate {
public:
    typedef void (*progress_func_t)(void);

    clsSDictPrivate(progress_func_t f=NULL);
    ~clsSDictPrivate();
    void load_dict(const std::string& url);
    void load(const strlist_t& dicts_dirs,
              const strlist_t& order_list,
              const strlist_t& disable_list);
    void reload(const strlist_t& dicts_dirs,
                const strlist_t& order_list,
                const strlist_t& disable_list);

    glong narticles(int idict) { return oLib[idict]->narticles(); }
    const std::string& dict_name(int idict) { return oLib[idict]->dict_name(); }
    gint ndicts() { return oLib.size(); }

    const gchar * poGetWord(glong iIndex,int iLib) {
        return oLib[iLib]->get_key(iIndex);
    }
    gchar * poGetWordData(glong iIndex,int iLib) {
        if (iIndex==INVALID_INDEX)
            return NULL;
        return oLib[iLib]->get_data(iIndex);
    }
    const gchar *poGetCurrentWord(glong *iCurrent);
    const gchar *poGetNextWord(const gchar *word, glong *iCurrent);
    const gchar *poGetPreWord(glong *iCurrent);
    bool LookupWord(const gchar* sWord, glong& iWordIndex, int iLib) {
        return oLib[iLib]->Lookup(sWord, iWordIndex);
    }
    bool LookupSimilarWord(const gchar* sWord, glong & iWordIndex, int iLib);
    bool SimpleLookupWord(const gchar* sWord, glong & iWordIndex, int iLib);


    bool LookupWithFuzzy(const gchar *sWord, gchar *reslist[], gint reslist_size);
    gint LookupWithRule(const gchar *sWord, gchar *reslist[]);
    bool LookupData(const gchar *sWord, std::vector<gchar *> *reslist);
    void SimpleLookup(const std::string &str, SearchResultList_t &res_list);
private:
    std::vector<Dict *> oLib; // word Libs.
    int iMaxFuzzyDistance;
    progress_func_t progress_func;
};


typedef enum {
    qtSIMPLE, qtREGEXP, qtFUZZY, qtDATA
} query_t;

extern query_t analyze_query(const char *s, std::string& res); 

#endif//!__SD_LIB_H__
