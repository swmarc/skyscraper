/***************************************************************************
 *            openretro.cpp
 *
 *  Wed Jun 18 12:00:00 CEST 2017
 *  Copyright 2017 Lars Muldjord
 *  muldjordlars@gmail.com
 ****************************************************************************/
/*
 *  This file is part of skyscraper.
 *
 *  skyscraper is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  skyscraper is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with skyscraper; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA.
 */

#include "openretro.h"
#include "nametools.h"
#include "strtools.h"

#include <QRegularExpression>

OpenRetro::OpenRetro(Settings *config,
		     QSharedPointer<NetManager> manager)
  : AbstractScraper(config, manager)
{
  baseUrl = "https://openretro.org";

  searchUrlPre = "https://openretro.org";
  searchUrlPost = "&unpublished=1";

  searchResultPre = "<div style='margin-bottom: 4px;'>";
  urlPre.append("<a href=\"/");
  urlPost = "\" target='_parent'>";
  titlePre.append("</div>");
  titlePost = " <span";
  platformPre.append("#aaaaaa'>");
  platformPost = "</span>";
  marqueePre.append(">banner_sha1</td>");
  marqueePre.append("<div><a href=\"");
  marqueePost = "\">";
  // Check getDescription function for special case __long_description scrape
  // For description
  descriptionPre.append(">description</td>");
  descriptionPre.append("<td style='color: black;'><div>");
  // For __long_description
  descriptionPre.append("__long_description</td>");
  descriptionPre.append("<td style='color: black;'><div>");
  descriptionPost = "</div></td>";
  developerPre.append("black;'>developer</td>");
  developerPre.append("<td style='color: black;'><div>");
  developerPost = "</div></td>";
  coverPre.append(">front_sha1</td>");
  coverPre.append("<div><a href=\"");
  coverPost = "\">";
  playersPre.append(">players</td>");
  playersPre.append("<td style='color: black;'><div>");
  playersPost = "</div></td>";
  publisherPre.append(">publisher</td>");
  publisherPre.append("<td style='color: black;'><div>");
  publisherPost = "</div></td>";
  screenshotCounter = "<td style='width: 180px; color: black;'>screen";
  screenshotPre.append("<td style='width: 180px; color: black;'>screen");
  screenshotPre.append("<td style='color: black;'><div><a href=\"");
  screenshotPost = "\">";
  releaseDatePre.append(">year</td>");
  releaseDatePre.append("<td style='color: black;'><div>");
  releaseDatePost = "</div></td>";
  tagsPre.append(">tags</td>");

  fetchOrder.append(MARQUEE);
  fetchOrder.append(DESCRIPTION);
  fetchOrder.append(DEVELOPER);
  fetchOrder.append(COVER);
  fetchOrder.append(PLAYERS);
  fetchOrder.append(PUBLISHER);
  fetchOrder.append(SCREENSHOT);
  fetchOrder.append(TAGS);
  fetchOrder.append(RELEASEDATE);
}

void OpenRetro::getSearchResults(QList<GameEntry> &gameEntries,
				 QString searchName, QString platform)
{
  netComm->request(searchUrlPre + searchName + (searchName.left(6) == "/game/"?"":searchUrlPost));
  q.exec();
  while(!netComm->getRedirUrl().isEmpty()) {
    netComm->request(netComm->getRedirUrl());
    q.exec();
  }
  data = netComm->getData();

  if(data.isEmpty())
    return;

  if(data.contains("Error: 500 Internal Server Error") ||
     data.contains("Error: 404 Not Found"))
    return;

  GameEntry game;

  if(searchName.left(6) == "/game/") {
    QByteArray tempData = data;
    nomNom("<td style='width: 180px; color: black;'>game_name</td>");
    nomNom("<td style='color: black;'><div>");
    // Remove AGA, we already add this automatically in StrTools::addSqrBrackets
    game.title = data.left(data.indexOf("</div></td>")).replace("[AGA]", "").
      replace("[CD32]", "").
      replace("[CDTV]", "").simplified();
    data = tempData;
    game.platform = platform;
    // Check if title is empty. Some games exist but have no data, not even a name. We don't want those results
    if(!game.title.isEmpty())
      gameEntries.append(game);
  } else {
    while(data.indexOf(searchResultPre.toUtf8()) != -1) {
      nomNom(searchResultPre);

      // Digest until url
      for(const auto &nom: urlPre) {
	nomNom(nom);
      }
      game.url = baseUrl + "/" + data.left(data.indexOf(urlPost.toUtf8())) + "/edit";

      // Digest until title
      for(const auto &nom: titlePre) {
	nomNom(nom);
      }
      // Remove AGA, we already add this automatically in StrTools::addSqrBrackets
      game.title = data.left(data.indexOf(titlePost.toUtf8())).replace("[AGA]", "").simplified();

      // Digest until platform
      for(const auto &nom: platformPre) {
	nomNom(nom);
      }
      game.platform = data.left(data.indexOf(platformPost.toUtf8())).replace("&nbsp;", " ");

      if(platformMatch(game.platform, platform)) {
	gameEntries.append(game);
      }
    }
  }
}

void OpenRetro::getGameData(GameEntry &game)
{
  if(!game.url.isEmpty()) {
    netComm->request(game.url);
    q.exec();
    data = netComm->getData();
  }

  // Remove all the variants so we don't choose between their screenshots
  data = data.left(data.indexOf("</table></div><div id='"));

  for(int a = 0; a < fetchOrder.length(); ++a) {
    switch(fetchOrder.at(a)) {
    case DESCRIPTION:
      getDescription(game);
      break;
    case DEVELOPER:
      getDeveloper(game);
      break;
    case PUBLISHER:
      getPublisher(game);
      break;
    case PLAYERS:
      getPlayers(game);
      break;
    case RATING:
      getRating(game);
      break;
    case TAGS:
      getTags(game);
      break;
    case RELEASEDATE:
      getReleaseDate(game);
      break;
    case COVER:
      getCover(game);
      break;
    case SCREENSHOT:
      getScreenshot(game);
      break;
    case WHEEL:
      getWheel(game);
      break;
    case MARQUEE:
      getMarquee(game);
      break;
    case VIDEO:
      if(config->videos) {
	getVideo(game);
      }
      break;
    default:
      ;
    }
  }
}

void OpenRetro::getDescription(GameEntry &game)
{
  if(descriptionPre.isEmpty()) {
    return;
  }
  QByteArray tempData = data;

  if(data.indexOf(descriptionPre.at(0).toUtf8()) != -1) {
    // If description
    nomNom(descriptionPre.at(0));
    nomNom(descriptionPre.at(1));
  } else if(data.indexOf(descriptionPre.at(2).toUtf8()) != -1) {
    // If __long_description
    nomNom(descriptionPre.at(2));
    nomNom(descriptionPre.at(3));
  } else {
    return;
  }

  game.description = data.left(data.indexOf(descriptionPost.toUtf8())).replace("&lt;", "<").replace("&gt;", ">");
  // Revert data back to pre-description
  data = tempData;

  // Remove all html tags within description
  game.description = StrTools::stripHtmlTags(game.description);
}

void OpenRetro::getTags(GameEntry &game)
{
  for(const auto &nom: tagsPre) {
    if(!checkNom(nom)) {
      return;
    }
  }
  for(const auto &nom: tagsPre) {
    nomNom(nom);
  }
  QString tags = "";
  QString tagBegin = "<a href=\"/browse/";
  while(data.indexOf(tagBegin.toUtf8()) != -1) {
    nomNom(tagBegin);
    nomNom("\">");
    tags.append(data.left(data.indexOf("</a>")) + ", ");
  }
  if(!tags.isEmpty()) {
    tags.chop(2); // Remove last ", "
  }

  game.tags = tags;
}

void OpenRetro::getCover(GameEntry &game)
{
  if(coverPre.isEmpty()) {
    return;
  }
  for(const auto &nom: coverPre) {
    if(!checkNom(nom)) {
      return;
    }
  }
  for(const auto &nom: coverPre) {
    nomNom(nom);
  }
  QString coverUrl = data.left(data.indexOf(coverPost.toUtf8())).replace("&amp;", "&") + "?s=512";
  if(coverUrl.left(4) != "http") {
    coverUrl.prepend(baseUrl + (coverUrl.left(1) == "/"?"":"/"));
  }
  netComm->request(coverUrl);
  q.exec();
  QImage image;
  if(netComm->getError() == QNetworkReply::NoError &&
     image.loadFromData(netComm->getData())) {
    game.coverData = netComm->getData();
  }
}

void OpenRetro::getMarquee(GameEntry &game)
{
  if(marqueePre.isEmpty()) {
    return;
  }
  for(const auto &nom: marqueePre) {
    if(!checkNom(nom)) {
      return;
    }
  }
  for(const auto &nom: marqueePre) {
    nomNom(nom);
  }
  QString marqueeUrl = data.left(data.indexOf(marqueePost.toUtf8())).replace("&amp;", "&") + "?s=512";
  if(marqueeUrl.left(4) != "http") {
    marqueeUrl.prepend(baseUrl + (marqueeUrl.left(1) == "/"?"":"/"));
  }
  netComm->request(marqueeUrl);
  q.exec();
  QImage image;
  if(netComm->getError() == QNetworkReply::NoError &&
     image.loadFromData(netComm->getData())) {
    game.marqueeData = netComm->getData();
  }
}

QList<QString> OpenRetro::getSearchNames(const QFileInfo &info)
{
  QString baseName = info.completeBaseName();
  QList<QString> searchNames;
  bool isAga = false;
  // Look for '_aga_' or '[aga]' with the last char optional
  if(QRegularExpression("[_[]{1}(Aga|AGA)[_\\]]{0,1}").match(baseName).hasMatch()) {
    isAga = true;
  }

  if(config->scraper != "import") {
    if(!config->aliasMap[baseName].isEmpty()) {
      baseName = config->aliasMap[baseName];
    } else if(info.suffix() == "lha") {
      // Pass 1 is uuid from whdload_db.xml
      if(!config->whdLoadMap[baseName].second.isEmpty()) {
	searchNames.append("/game/" + config->whdLoadMap[baseName].second);
      }
      // Pass 2 is either from <name> tag in whdload_db.xml or by adding spaces
      QString nameWithSpaces = config->whdLoadMap[baseName].first;
      if(nameWithSpaces.isEmpty()) {
	baseName = NameTools::getNameWithSpaces(baseName);
      } else {
	baseName = nameWithSpaces;
      }
    } else if(config->platform == "scummvm") {
      baseName = NameTools::getScummName(baseName, config->scummIni);
    } else if((config->platform == "neogeo" ||
	       config->platform == "arcade" ||
	       config->platform == "mame-advmame" ||
	       config->platform == "mame-libretro" ||
	       config->platform == "mame-mame4all" ||
	       config->platform == "fbneo") && !config->mameMap[baseName].isEmpty()) {
      baseName = config->mameMap[baseName];
    }
  }

  baseName = NameTools::getUrlQueryName(baseName, 2);

  if(!baseName.isEmpty()) {
    if(isAga) {
      searchNames.append("/browse?q=" + baseName + "+aga");
    }
    searchNames.append("/browse?q=" + baseName);
  }

  if(baseName.indexOf(":") != -1 || baseName.indexOf("-") != -1) {
    baseName = baseName.left(baseName.indexOf(":")).simplified();
    baseName = baseName.left(baseName.indexOf("-")).simplified();
    searchNames.append("/browse?q=" + baseName);
  }

  return searchNames;
}
