/***************************************************************************
 *            screenscraper.cpp
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

#include <QFileInfo>
#include <QJsonDocument>
#include <QProcess>
#include <chrono>
#include <thread>

#include "crc32.h"
#include "screenscraper.h"
#include "strtools.h"

constexpr int RETRIESMAX = 24;
constexpr int MINARTSIZE = 256;

ScreenScraper::ScreenScraper(Settings *config,
                             QSharedPointer<NetManager> manager)
    : AbstractScraper(config, manager) {
  connect(&limitTimer, &QTimer::timeout, &limiter, &QEventLoop::quit);
  limitTimer.setInterval(
      1200); // 1.2 second request limit set a bit above 1.0 as requested by the
             // good folks at ScreenScraper. Don't change!
  limitTimer.setSingleShot(false);
  limitTimer.start();

  baseUrl = "http://www.screenscraper.fr";

  fetchOrder.append(PUBLISHER);
  fetchOrder.append(DEVELOPER);
  fetchOrder.append(PLAYERS);
  fetchOrder.append(AGES);
  fetchOrder.append(RATING);
  fetchOrder.append(DESCRIPTION);
  fetchOrder.append(RELEASEDATE);
  fetchOrder.append(TAGS);
  fetchOrder.append(SCREENSHOT);
  fetchOrder.append(COVER);
  fetchOrder.append(WHEEL);
  fetchOrder.append(MARQUEE);
  fetchOrder.append(VIDEO);
}

void ScreenScraper::getSearchResults(QList<GameEntry> &gameEntries,
                                     QString searchName, QString) {
  QString platformId = getPlatformId(config->platform);
  if (platformId == "na") {
    reqRemaining = 0;
    printf("\033[0;31mPlatform not supported by ScreenScraper or it hasn't yet "
           "been included in Skyscraper for this module...\033[0m\n");
    exit(1);
  }

  QString gameUrl =
      "https://www.screenscraper.fr/api2/"
      "jeuInfos.php?devid=muldjord&devpassword=" +
      StrTools::unMagic(
          "204;198;236;130;203;181;203;126;191;167;200;198;192;228;169;156") +
      "&softname=skyscraper" VERSION +
      (config->user.isEmpty() ? "" : "&ssid=" + config->user) +
      (config->password.isEmpty() ? "" : "&sspassword=" + config->password) +
      (platformId.isEmpty() ? "" : "&systemeid=" + platformId) +
      "&output=json&" + searchName;

  for (int retries = 0; retries < RETRIESMAX; ++retries) {
    limiter.exec();
    netComm->request(gameUrl);
    q.exec();
    data = netComm->getData();

    QByteArray headerData =
        data.left(1024); // Minor optimization with minimal more RAM usage
    // Do error checks on headerData. It's more stable than checking the
    // potentially faulty JSON
    if (headerData.isEmpty()) {
      printf("\033[1;33mRetrying request...\033[0m\n\n");
      continue;
    } else if (headerData.contains("non trouvée")) {
      return;
    } else if (headerData.contains("API totalement fermé")) {
      printf("\033[1;31mThe ScreenScraper API is currently closed, exiting "
             "nicely...\033[0m\n\n");
      exit(1);
    } else if (headerData.contains(
                   "Le logiciel de scrape utilisé a été blacklisté")) {
      printf("\033[1;31mSkyscraper has apparently been blacklisted at "
             "ScreenScraper, exiting nicely...\033[0m\n\n");
      exit(1);
    } else if (headerData.contains("Votre quota de scrape est")) {
      printf("\033[1;31mYour daily ScreenScraper request limit has been "
             "reached, exiting nicely...\033[0m\n\n");
      exit(1);
    } else if (headerData.contains("API fermé pour les non membres") ||
               headerData.contains("API closed for non-registered members") ||
               headerData.contains(
                   "****T****h****e**** "
                   "****m****a****x****i****m****u****m**** "
                   "****t****h****r****e****a****d****s**** "
                   "****a****l****l****o****w****e****d**** ****t****o**** "
                   "****l****e****e****c****h****e****r**** "
                   "****u****s****e****r****s**** ****i****s**** "
                   "****a****l****r****e****a****d****y**** "
                   "****u****s****e****d****")) {
      printf("\033[1;31mThe screenscraper service is currently closed or too "
             "busy to handle requests from unregistered and inactive users. "
             "Sign up for an account at https://www.screenscraper.fr and "
             "contribute to gain more threads. Then use the credentials with "
             "Skyscraper using the '-u user:pass' command line option or by "
             "setting 'userCreds=\"user:pass\"' in "
             "'/home/USER/.skyscraper/config.ini'.\033[0m\n\n");
      if (retries == RETRIESMAX - 1) {
        reqRemaining = 0;
        return;
      }
      continue;
    }

    // Fix faulty JSON that is sometimes received back from ScreenScraper
    data.replace("],\n\t\t}", "]\n\t\t}");

    // Now parse the JSON
    jsonObj = QJsonDocument::fromJson(data).object();

    // Check if we got a valid JSON document back
    if (jsonObj.isEmpty()) {
      // reqRemaining = 0;
      printf("\033[1;31mScreenScraper APIv2 returned invalid / empty Json. "
             "Their servers are probably down. Please try again later or use a "
             "different scraping module with '-s MODULE'. Check 'Skyscraper "
             "--help' for more information.\033[0m\n");
      data.replace(StrTools::unMagic("204;198;236;130;203;181;203;126;191;167;"
                                     "200;198;192;228;169;156"),
                   "****");
      data.replace(config->password.toUtf8(), "****");
      QFile jsonErrorFile("./screenscraper_error.json");
      if (jsonErrorFile.open(QIODevice::WriteOnly)) {
        if (data.length() > 64) {
          jsonErrorFile.write(data);
          printf("The erroneous answer was written to "
                 "'/home/USER/.skyscraper/screenscraper_error.json'. If this "
                 "file contains game data, please consider filing a bug report "
                 "at 'https://github.com/muldjord/skyscraper/issues' and "
                 "attach that file.\n");
        }
        jsonErrorFile.close();
      }
      // exit(1); // DON'T try again! If we don't get a valid JSON document,
               // something is very wrong with the API
      printf("\033[1;31mSleeping for 5 minutes...\033[0m\n");
      std::this_thread::sleep_for(std::chrono::milliseconds(300000));
      continue;
    }

    // Check if the request was successful
    if (jsonObj["header"].toObject()["success"].toString() != "true") {
      printf("Request returned a success state of '%s'. Error was:\n%s\n",
             jsonObj["header"]
                 .toObject()["success"]
                 .toString()
                 .toStdString()
                 .c_str(),
             jsonObj["header"]
                 .toObject()["error"]
                 .toString()
                 .toStdString()
                 .c_str());
      // Try again. We handle important errors above, so something weird is
      // going on here
      continue;
    }

    // Check if user has exceeded daily request limit
    if (!jsonObj["response"]
             .toObject()["ssuser"]
             .toObject()["requeststoday"]
             .toString()
             .isEmpty() &&
        !jsonObj["response"]
             .toObject()["ssuser"]
             .toObject()["maxrequestsperday"]
             .toString()
             .isEmpty()) {
      reqRemaining = jsonObj["response"]
                         .toObject()["ssuser"]
                         .toObject()["maxrequestsperday"]
                         .toString()
                         .toInt() -
                     jsonObj["response"]
                         .toObject()["ssuser"]
                         .toObject()["requeststoday"]
                         .toString()
                         .toInt();
      if (reqRemaining <= 0) {
        printf("\033[1;31mYour daily ScreenScraper request limit has been "
               "reached, exiting nicely...\033[0m\n\n");
      }
    }

    // Check if we got a game entry back
    if (jsonObj["response"].toObject().contains("jeu")) {
      // Game found, stop retrying
      break;
    }
  }

  jsonObj = jsonObj["response"].toObject()["jeu"].toObject();

  GameEntry game;
  game.title = getJsonText(jsonObj["noms"].toArray(), REGION);

  // 'screenscraper' sometimes returns a faulty result with the following names.
  // If we get either result DON'T use it. It will provide faulty data for the
  // cache
  if ((game.title.toLower().contains("hack") &&
       game.title.toLower().contains("link")) ||
      game.title.toLower() == "zzz" ||
      game.title.toLower().contains("notgame")) {
    return;
  }

  // If title still unset, no acceptable rom was found, so return with no
  // results
  if (game.title.isNull()) {
    return;
  }

  game.url = gameUrl;
  game.platform = jsonObj["systeme"].toObject()["text"].toString();

  // Only check if platform is empty, it's always correct when using
  // ScreenScraper
  if (!game.platform.isEmpty())
    gameEntries.append(game);
}

void ScreenScraper::getGameData(GameEntry &game) {
  for (int a = 0; a < fetchOrder.length(); ++a) {
    switch (fetchOrder.at(a)) {
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
    case AGES:
      getAges(game);
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
      if (config->cacheCovers) {
        getCover(game);
      }
      break;
    case SCREENSHOT:
      if (config->cacheScreenshots) {
        getScreenshot(game);
      }
      break;
    case WHEEL:
      if (config->cacheWheels) {
        getWheel(game);
      }
      break;
    case MARQUEE:
      if (config->cacheMarquees) {
        getMarquee(game);
      }
      break;
    case VIDEO:
      if (config->videos) {
        getVideo(game);
      }
      break;
    default:;
    }
  }
}

void ScreenScraper::getReleaseDate(GameEntry &game) {
  game.releaseDate = getJsonText(jsonObj["dates"].toArray(), REGION);
}

void ScreenScraper::getDeveloper(GameEntry &game) {
  game.developer = jsonObj["developpeur"].toObject()["text"].toString();
}

void ScreenScraper::getPublisher(GameEntry &game) {
  game.publisher = jsonObj["editeur"].toObject()["text"].toString();
}

void ScreenScraper::getDescription(GameEntry &game) {
  game.description = getJsonText(jsonObj["synopsis"].toArray(), LANGUE);
}

void ScreenScraper::getPlayers(GameEntry &game) {
  game.players = jsonObj["joueurs"].toObject()["text"].toString();
}

void ScreenScraper::getAges(GameEntry &game) {
  QList<QString> ageBoards;
  ageBoards.append("PEGI");
  ageBoards.append("ESRB");
  ageBoards.append("SS");

  if (!jsonObj["classifications"].isArray())
    return;

  QJsonArray jsonAges = jsonObj["classifications"].toArray();

  for (const auto &ageBoard : ageBoards) {
    for (int a = 0; a < jsonAges.size(); ++a) {
      if (jsonAges.at(a).toObject()["type"].toString() == ageBoard) {
        game.ages = jsonAges.at(a).toObject()["text"].toString();
        return;
      }
    }
  }
}

void ScreenScraper::getRating(GameEntry &game) {
  game.rating = jsonObj["note"].toObject()["text"].toString();
  bool toDoubleOk = false;
  double rating = game.rating.toDouble(&toDoubleOk);
  if (toDoubleOk) {
    game.rating = QString::number(rating / 20.0);
  } else {
    game.rating = "";
  }
}

void ScreenScraper::getTags(GameEntry &game) {
  if (!jsonObj["genres"].isArray())
    return;

  QJsonArray jsonTags = jsonObj["genres"].toArray();

  for (int a = 0; a < jsonTags.size(); ++a) {
    QString tag =
        getJsonText(jsonTags.at(a).toObject()["noms"].toArray(), LANGUE);
    if (!tag.isEmpty()) {
      game.tags.append(tag + ", ");
    }
  }

  game.tags = game.tags.left(game.tags.length() - 2);
}

void ScreenScraper::getCover(GameEntry &game) {
  QString url = "";
  if (config->platform == "arcade" || config->platform == "fbneo" ||
      config->platform == "mame-advmame" ||
      config->platform == "mame-libretro" ||
      config->platform == "mame-mame4all") {
    url = getJsonText(jsonObj["medias"].toArray(), REGION,
                      QList<QString>({"flyer"}));
  } else {
    url = getJsonText(jsonObj["medias"].toArray(), REGION,
                      QList<QString>({"box-2D", "box-texture"}));
  }
  if (!url.isEmpty()) {
    bool moveOn = true;
    for (int retries = 0; retries < RETRIESMAX; ++retries) {
      limiter.exec();
      netComm->request(url);
      q.exec();
      QImage image;
      if (netComm->getError(config->verbosity) == QNetworkReply::NoError &&
          netComm->getData().size() >= MINARTSIZE &&
          image.loadFromData(netComm->getData())) {
        game.coverData = netComm->getData();
      } else {
        moveOn = false;
      }
      if (moveOn)
        break;
    }
  }
}

void ScreenScraper::getScreenshot(GameEntry &game) {
  QString url = getJsonText(jsonObj["medias"].toArray(), REGION,
                            QList<QString>({"ss", "sstitle"}));
  if (!url.isEmpty()) {
    bool moveOn = true;
    for (int retries = 0; retries < RETRIESMAX; ++retries) {
      limiter.exec();
      netComm->request(url);
      q.exec();
      QImage image;
      if (netComm->getError(config->verbosity) == QNetworkReply::NoError &&
          netComm->getData().size() >= MINARTSIZE &&
          image.loadFromData(netComm->getData())) {
        game.screenshotData = netComm->getData();
      } else {
        moveOn = false;
      }
      if (moveOn)
        break;
    }
  }
}

void ScreenScraper::getWheel(GameEntry &game) {
  QString url = getJsonText(jsonObj["medias"].toArray(), REGION,
                            QList<QString>({"wheel", "wheel-hd", "wheel-carbon", "wheel-steel"}));
  if (!url.isEmpty()) {
    bool moveOn = true;
    for (int retries = 0; retries < RETRIESMAX; ++retries) {
      limiter.exec();
      netComm->request(url);
      q.exec();
      QImage image;
      if (netComm->getError(config->verbosity) == QNetworkReply::NoError &&
          netComm->getData().size() >= MINARTSIZE &&
          image.loadFromData(netComm->getData())) {
        game.wheelData = netComm->getData();
      } else {
        moveOn = false;
      }
      if (moveOn)
        break;
    }
  }
}

void ScreenScraper::getMarquee(GameEntry &game) {
  QString url = getJsonText(jsonObj["medias"].toArray(), NONE,
                            QList<QString>({"screenmarquee", "marquee"}));
  if (!url.isEmpty()) {
    bool moveOn = true;
    for (int retries = 0; retries < RETRIESMAX; ++retries) {
      limiter.exec();
      netComm->request(url);
      q.exec();
      QImage image;
      if (netComm->getError(config->verbosity) == QNetworkReply::NoError &&
          netComm->getData().size() >= MINARTSIZE &&
          image.loadFromData(netComm->getData())) {
        game.marqueeData = netComm->getData();
      } else {
        moveOn = false;
      }
      if (moveOn)
        break;
    }
  }
}

void ScreenScraper::getVideo(GameEntry &game) {
  QStringList types;
  if (config->videoPreferNormalized) {
    types.append("video-normalized");
  }
  types.append("video");
  QString url = getJsonText(jsonObj["medias"].toArray(), NONE, types);
  if (!url.isEmpty()) {
    bool moveOn = true;
    for (int retries = 0; retries < RETRIESMAX; ++retries) {
      limiter.exec();
      netComm->request(url);
      q.exec();
      game.videoData = netComm->getData();
      // Make sure received data is actually a video file
      QByteArray contentType = netComm->getContentType();
      if (netComm->getError(config->verbosity) == QNetworkReply::NoError &&
          contentType.contains("video/") && game.videoData.size() > 4096) {
        game.videoFormat = contentType.mid(contentType.indexOf("/") + 1,
                                           contentType.length() -
                                               contentType.indexOf("/") + 1);
      } else {
        game.videoData = "";
        moveOn = false;
      }
      if (moveOn)
        break;
    }
  }
}

QList<QString> ScreenScraper::getSearchNames(const QFileInfo &info) {
  QList<QString> searchNames;

  // For some reason the APIv2 example from their website does not url encode
  // '(' and ')' so I've excluded them
  searchNames.append("romnom=" + QUrl::toPercentEncoding(info.fileName(), "()"));

  return searchNames;
}

QString ScreenScraper::getJsonText(QJsonArray jsonArr, int attr,
                                   QList<QString> types) {
  if (attr == NONE && !types.isEmpty()) {
    for (const auto &type : types) {
      for (const auto &jsonVal : jsonArr) {
        if (jsonVal.toObject()["type"].toString() == type) {
          if (jsonVal.toObject()["url"].isString()) {
            return jsonVal.toObject()["url"].toString();
          } else {
            return jsonVal.toObject()["text"].toString();
          }
        }
      }
    }
  } else if (attr == REGION) {
    // Not using the config->regionPrios since they might have changed due to
    // region autodetection. So using temporary internal one instead.
    for (const auto &region : regionPrios) {
      if (types.isEmpty()) {
        for (const auto &jsonVal : jsonArr) {
          if (jsonVal.toObject()["region"].toString() == region) {
            if (jsonVal.toObject()["url"].isString()) {
              return jsonVal.toObject()["url"].toString();
            } else {
              return jsonVal.toObject()["text"].toString();
            }
          }
        }
      } else {
        for (const auto &type : types) {
          for (const auto &jsonVal : jsonArr) {
            if (jsonVal.toObject()["region"].toString() == region &&
                jsonVal.toObject()["type"].toString() == type) {
              if (jsonVal.toObject()["url"].isString()) {
                return jsonVal.toObject()["url"].toString();
              } else {
                return jsonVal.toObject()["text"].toString();
              }
            }
          }
        }
      }
    }
  } else if (attr == LANGUE) {
    for (const auto &lang : config->langPrios) {
      if (types.isEmpty()) {
        for (const auto &jsonVal : jsonArr) {
          if (jsonVal.toObject()["langue"].toString() == lang) {
            if (jsonVal.toObject()["url"].isString()) {
              return jsonVal.toObject()["url"].toString();
            } else {
              return jsonVal.toObject()["text"].toString();
            }
          }
        }
      } else {
        for (const auto &type : types) {
          for (const auto &jsonVal : jsonArr) {
            if (jsonVal.toObject()["langue"].toString() == lang &&
                jsonVal.toObject()["type"].toString() == type) {
              if (jsonVal.toObject()["url"].isString()) {
                return jsonVal.toObject()["url"].toString();
              } else {
                return jsonVal.toObject()["text"].toString();
              }
            }
          }
        }
      }
    }
  }
  return QString();
}

QString ScreenScraper::getPlatformId(const QString platform) {
  if (platform == "3do" || platform == "3do-t-en") {
    return "29";
  } else if (platform == "3ds" || platform == "3ds-t-en") {
    return "17";
  } else if (platform == "64dd" || platform == "64dd-t-en") {
    return "122";
  } else if (platform == "actionmax") {
    return "81";
  } else if (platform == "adam") {
    return "89";
  } else if (platform == "advision") {
    return "78";
  } else if (platform == "amiga") {
    return "64";
  } else if (platform == "aga") {
    return "111";
  } else if (platform == "amigacd") {
    return "134";
  } else if (platform == "amigacd32") {
    return "130";
  } else if (platform == "amigacdtv") {
    return "129";
  } else if (platform == "amstradcpc") {
    return "65";
  } else if (platform == "apple2") {
    return "86";
  } else if (platform == "apple2gs") {
    return "217";
  } else if (platform == "arcade") {
    return "75";
  } else if (platform == "arcadia") {
    return "94";
  } else if (platform == "archimedes") {
    return "84";
  } else if (platform == "arduboy") {
    return "263";
  } else if (platform == "astrocade") {
    return "44";
  } else if (platform == "atari800") {
    return "43";
  } else if (platform == "atari2600") {
    return "26";
  } else if (platform == "atari5200") {
    return "40";
  } else if (platform == "atari7800") {
    return "41";
  } else if (platform == "atarijaguar") {
    return "27";
  } else if (platform == "atarijaguarcd") {
    return "171";
  } else if (platform == "atarilynx") {
    return "28";
  } else if (platform == "atarist") {
    return "42";
  } else if (platform == "atom") {
    return "36";
  } else if (platform == "atomiswave") {
    return "75";
  } else if (platform == "bbcmicro") {
    return "37";
  } else if (platform == "c16") {
    return "99";
  } else if (platform == "c64") {
    return "66";
  } else if (platform == "c128") {
    return "na";
  } else if (platform == "camplynx") {
    return "88";
  } else if (platform == "cdi") {
    return "133";
  } else if (platform == "channelf") {
    return "80";
  } else if (platform == "coco") {
    return "144";
  } else if (platform == "coleco") {
    return "48";
  } else if (platform == "cps1") {
    return "6";
  } else if (platform == "cps2") {
    return "7";
  } else if (platform == "cps3") {
    return "8";
  } else if (platform == "crvision") {
    return "241";
  } else if (platform == "daphne") {
    return "49";
  } else if (platform == "dragon") {
    return "91";
  } else if (platform == "dreamcast" || platform == "dreamcast-t-en") {
    return "23";
  } else if (platform == "easyrpg") {
    return "231";
  } else if (platform == "exl100") {
    return "96";
  } else if (platform == "fbneo") {
    return "75";
  } else if (platform == "fds" || platform == "fds-t-en") {
    return "106";
  } else if (platform == "fm7") {
    return "97";
  } else if (platform == "fmtowns" || platform == "fmtowns-t-en") {
    return "253";
  } else if (platform == "gameandwatch") {
    return "52";
  } else if (platform == "gamecom") {
    return "121";
  } else if (platform == "gamegear" || platform == "gamegear-t-en") {
    return "21";
  } else if (platform == "gamepock") {
    return "95";
  } else if (platform == "gb" || platform == "gb-t-en") {
    return "9";
  } else if (platform == "gba" || platform == "gba-t-en") {
    return "12";
  } else if (platform == "gbc" || platform == "gbc-t-en") {
    return "10";
  } else if (platform == "gc") {
    return "13";
  } else if (platform == "genesis") {
    return "1";
  } else if (platform == "gmaster") {
    return "103";
  } else if (platform == "gp32") {
    return "101";
  } else if (platform == "gx4000") {
    return "87";
  } else if (platform == "hikaru") {
    return "258";
  } else if (platform == "intellivision") {
    return "115";
  } else if (platform == "mame-advmame") {
    return "75";
  } else if (platform == "mame-libretro") {
    return "75";
  } else if (platform == "mame-mame4all") {
    return "75";
  } else if (platform == "mastersystem" || platform == "mastersystem-t-en") {
    return "2";
  } else if (platform == "megacd") {
    return "20";
  } else if (platform == "megadrive" || platform == "megadrive-msu" || platform == "megadrive-t-en") {
    return "1";
  } else if (platform == "megaduck") {
    return "90";
  } else if (platform == "moto") {
    return "141";
  } else if (platform == "msx" || platform == "msx1" || platform == "msx1-t-en") {
    return "113";
  } else if (platform == "msx2" || platform == "msx2-t-en") {
    return "113";
  } else if (platform == "msx2+") {
    return "117";
  } else if (platform == "msxturbor" || platform == "msxturbor-t-en") {
    return "118";
  } else if (platform == "n64" || platform == "n64-t-en") {
    return "14";
  } else if (platform == "naomi") {
    return "75";
  } else if (platform == "naomi2") {
    return "230";
  } else if (platform == "nds" || platform == "nds-t-en" || platform == "ndsi" || platform == "ndsi-t-en") {
    return "15";
  } else if (platform == "neogeo") {
    return "142";
  } else if (platform == "neogeocd" || platform == "neogeocd-t-en") {
    return "70";
  } else if (platform == "nes") {
    return "3";
  } else if (platform == "ngp") {
    return "25";
  } else if (platform == "ngpc" || platform == "ngpc-t-en") {
    return "82";
  } else if (platform == "openbor") {
    return "214";
  } else if (platform == "oric" || platform == "oricatmos") {
    return "131";
  } else if (platform == "dos") {
    return "135";
  } else if (platform == "pc88" || platform == "pc88-t-en") {
    return "221";
  } else if (platform == "pc98" || platform == "pc98-t-en") {
    return "208";
  } else if (platform == "pcfx" || platform == "pcfx-t-en") {
    return "72";
  } else if (platform == "pcengine" || platform == "pcengine-t-en") {
    return "31";
  } else if (platform == "pcenginecd" || platform == "pcenginecd-t-en") {
    return "114";
  } else if (platform == "pet") {
    return "240";
  } else if(platform == "pico") {
    return "250";
  } else if(platform == "pico8") {
    return "234";
  } else if(platform == "pokemini" || platform == "pokemini-t-en") {
    return "211";
  } else if (platform == "ports") {
    return "135";
  } else if (platform == "ps2" || platform == "ps2-t-en") {
    return "58";
  } else if (platform == "ps3" || platform == "ps3-t-en") {
    return "59";
  } else if (platform == "ps4") {
    return "60";
  } else if (platform == "psp" || platform == "psp-t-en") {
    return "61";
  } else if (platform == "psvita") {
    return "62";
  } else if (platform == "psx" || platform == "psx-t-en") {
    return "57";
  } else if (platform == "pv1000") {
    return "74";
  } else if (platform == "samcoupe") {
    return "213";
  } else if (platform == "satellaview") {
    return "107";
  } else if (platform == "saturn" || platform == "saturn-t-en") {
    return "22";
  } else if (platform == "scummvm") {
    return "123";
  } else if (platform == "scv") {
    return "67";
  } else if (platform == "sega32x") {
    return "19";
  } else if (platform == "segamodel2") {
    return "54";
  } else if (platform == "segamodel3") {
    return "55";
  } else if (platform == "segacd" || platform == "segacd-t-en") {
    return "20";
  } else if (platform == "sg-1000" || platform == "sg-1000-t-en") {
    return "109";
  } else if (platform == "snes" || platform == "snes-t-en") {
    return "4";
  } else if (platform == "snes-msu") {
    return "210";
  } else if (platform == "solarus") {
    return "223";
  } else if (platform == "spectravideo") {
    return "218";
  } else if (platform == "sufami") {
    return "108";
  } else if (platform == "supergrafx") {
    return "105";
  } else if (platform == "supervision") {
    return "207";
  } else if (platform == "switch") {
    return "225";
  } else if (platform == "ti99") {
    return "205";
  } else if (platform == "trs-80") {
    return "144";
  } else if (platform == "vectrex") {
    return "102";
  } else if (platform == "vg5000") {
    return "261";
  } else if (platform == "vic20") {
    return "73";
  } else if (platform == "videopac" || platform == "odyssey2") {
    return "104";
  } else if (platform == "virtualboy" || platform == "virtualboy-t-en") {
    return "11";
  } else if (platform == "vpinball") {
    return "198";
  } else if (platform == "vsmile") {
    return "120";
  } else if (platform == "wii" || platform == "wii-t-en") {
    return "16";
  } else if (platform == "wiiu") {
    return "18";
  } else if (platform == "windows") {
    return "138";
  } else if (platform == "wonderswan" || platform == "wonderswan-t-en") {
    return "45";
  } else if (platform == "wonderswancolor" || platform == "wonderswancolor-t-en") {
    return "46";
  } else if (platform == "x68000" || platform == "x68000-t-en") {
    return "79";
  } else if (platform == "x1" || platform == "x1-t-en") {
    return "220";
  } else if (platform == "xbox" || platform == "xbox-t-en") {
    return "32";
  } else if (platform == "xbox360" || platform == "xbox360-t-en") {
    return "33";
  } else if (platform == "xboxone") {
    return "34";
  } else if (platform == "zmachine") {
    return "215";
  } else if (platform == "zx81") {
    return "77";
  } else if (platform == "zxspectrum") {
    return "76";
  }
  return "na";
}
