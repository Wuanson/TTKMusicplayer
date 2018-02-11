#ifndef MUSICCATEGORYCONFIGMANAGER_H
#define MUSICCATEGORYCONFIGMANAGER_H

/* =================================================
 * This file is part of the TTK Music Player project
 * Copyright (C) 2015 - 2018 Greedysky Studio

 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along
 * with this program; If not, see <http://www.gnu.org/licenses/>.
 ================================================= */

#include "musicabstractxml.h"

/*! @brief The class of the results category item.
 * @author Greedysky <greedysky@163.com>
 */
typedef struct MUSIC_CORE_EXPORT MusicResultsCategoryItem
{
    QString m_id;
    QString m_name;

    MusicResultsCategoryItem()
    {

    }

    MusicResultsCategoryItem(const QString &id, const QString &name)
    {
        m_id = id;
        m_name = name;
    }
}MusicResultsCategoryItem;
MUSIC_DECLARE_LISTS(MusicResultsCategoryItem)


/*! @brief The class of the results category core.
 * @author Greedysky <greedysky@163.com>
 */
typedef struct MUSIC_CORE_EXPORT MusicResultsCategory
{
    QString m_category;
    MusicResultsCategoryItems m_items;
}MusicResultsCategory;
MUSIC_DECLARE_LISTS(MusicResultsCategory)


/*! @brief The class of the category Config Manager.
 * @author Greedysky <greedysky@163.com>
 */
class MUSIC_CORE_EXPORT MusicCategoryConfigManager : public MusicAbstractXml
{
    Q_OBJECT
public:
    enum Type
    {
        Playlist,       /*!< Playlist Category*/
        Toplist,        /*!< Toplist Category*/
        ArtistList,     /*!< ArtistList Category*/
        MovieList,      /*!< MovieList Category*/
    };
    /*!
     * Object contsructor.
     */
    explicit MusicCategoryConfigManager(QObject *parent = 0);

    /*!
     * Get class object name.
     */
    static QString getClassName();
    /*!
     * Read user datas from xml file by given name.
     */
    bool readCategoryConfig(Type type);
    /*!
     * Read user datas from xml file.
     */
    void readCategoryConfig(MusicResultsCategorys &records, const QString &key);

};

#endif // MUSICCATEGORYCONFIGMANAGER_H
