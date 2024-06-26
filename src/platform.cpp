/***************************************************************************
 *            platform.cpp
 *
 *  Sat Dec 23 10:00:00 CEST 2017
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

#include <QDir>
#include <QFile>
#include <QProcess>
#include <iostream>

#include "platform.h"

Platform::Platform() {}

Platform::~Platform() {}

QStringList Platform::getPlatforms() {
  QStringList platforms;
  platforms.append("3do");
  platforms.append("3do-t-en");
  platforms.append("3ds");
  platforms.append("3ds-t-en");
  platforms.append("64dd");
  platforms.append("64dd-t-en");
  platforms.append("actionmax");
  platforms.append("adam");
  platforms.append("advision");
  platforms.append("amiga");
  platforms.append("amigacd");
  platforms.append("amigacd32");
  platforms.append("amigacdtv");
  platforms.append("amstradcpc");
  platforms.append("apple2");
  platforms.append("apple2gs");
  platforms.append("arcade");
  platforms.append("arcadia");
  platforms.append("archimedes");
  platforms.append("arduboy");
  platforms.append("astrocade");
  platforms.append("atari800");
  platforms.append("atari2600");
  platforms.append("atari5200");
  platforms.append("atari7800");
  platforms.append("atarijaguar");
  platforms.append("atarijaguarcd");
  platforms.append("atarilynx");
  platforms.append("atarist");
  platforms.append("atom");
  platforms.append("atomiswave");
  platforms.append("bbcmicro");
  platforms.append("c16");
  platforms.append("c64");
  platforms.append("c128");
  platforms.append("camplynx");
  platforms.append("cdi");
  platforms.append("channelf");
  platforms.append("coco");
  platforms.append("coleco");
  platforms.append("cps1");
  platforms.append("cps2");
  platforms.append("cps3");
  platforms.append("crvision");
  platforms.append("daphne");
  platforms.append("dos");
  platforms.append("dragon");
  platforms.append("dreamcast");
  platforms.append("dreamcast-t-en");
  platforms.append("easyrpg");
  platforms.append("exl100");
  platforms.append("fbneo");
  platforms.append("fds");
  platforms.append("fds-t-en");
  platforms.append("fm7");
  platforms.append("fmtowns");
  platforms.append("fmtowns-t-en");
  platforms.append("gameandwatch");
  platforms.append("gamecom");
  platforms.append("gamegear");
  platforms.append("gamegear-t-en");
  platforms.append("gamepock");
  platforms.append("gb");
  platforms.append("gb-t-en");
  platforms.append("gba");
  platforms.append("gba-t-en");
  platforms.append("gbc");
  platforms.append("gbc-t-en");
  platforms.append("gc");
  platforms.append("genesis");
  platforms.append("gmaster");
  platforms.append("gp32");
  platforms.append("gx4000");
  platforms.append("hikaru");
  platforms.append("intellivision");
  platforms.append("mame-advmame");
  platforms.append("mame-libretro");
  platforms.append("mame-mame4all");
  platforms.append("mastersystem");
  platforms.append("mastersystem-t-en");
  platforms.append("megacd");
  platforms.append("megadrive");
  platforms.append("megadrive-msu");
  platforms.append("megadrive-t-en");
  platforms.append("megaduck");
  platforms.append("moto");
  platforms.append("msx");
  platforms.append("msx1");
  platforms.append("msx1-t-en");
  platforms.append("msx2");
  platforms.append("msx2-t-en");
  platforms.append("msx2+");
  platforms.append("msxturbor");
  platforms.append("msxturbor-t-en");
  platforms.append("n64");
  platforms.append("n64-t-en");
  platforms.append("naomi");
  platforms.append("naomi2");
  platforms.append("nds");
  platforms.append("nds-t-en");
  platforms.append("ndsi-t-en");
  platforms.append("neogeo");
  platforms.append("neogeocd");
  platforms.append("neogeocd-t-en");
  platforms.append("nes");
  platforms.append("ngp");
  platforms.append("ngpc");
  platforms.append("ngpc-t-en");
  platforms.append("openbor");
  platforms.append("oric");
  platforms.append("oricatmos");
  platforms.append("pc88");
  platforms.append("pc88-t-en");
  platforms.append("pc98");
  platforms.append("pc98-t-en");
  platforms.append("pcfx");
  platforms.append("pcfx-t-en");
  platforms.append("pcengine");
  platforms.append("pcengine-t-en");
  platforms.append("pcenginecd");
  platforms.append("pcenginecd-t-en");
  platforms.append("pet");
  platforms.append("pico");
  platforms.append("pico8");
  platforms.append("pokemini");
  platforms.append("pokemini-t-en");
  platforms.append("ports");
  platforms.append("ps2");
  platforms.append("ps2-t-en");
  platforms.append("ps3");
  platforms.append("ps3-t-en");
  platforms.append("ps4");
  platforms.append("psp");
  platforms.append("psp-t-en");
  platforms.append("psvita");
  platforms.append("psx");
  platforms.append("psx-t-en");
  platforms.append("pv1000");
  platforms.append("samcoupe");
  platforms.append("satellaview");
  platforms.append("saturn");
  platforms.append("saturn-t-en");
  platforms.append("scummvm");
  platforms.append("scv");
  platforms.append("sega32x");
  platforms.append("segamodel2");
  platforms.append("segamodel3");
  platforms.append("segacd");
  platforms.append("segacd-t-en");
  platforms.append("sg-1000");
  platforms.append("sg-1000-t-en");
  platforms.append("snes");
  platforms.append("snes-msu");
  platforms.append("snes-t-en");
  platforms.append("solarus");
  platforms.append("spectravideo");
  platforms.append("steam");
  platforms.append("sufami");
  platforms.append("supergrafx");
  platforms.append("supervision");
  platforms.append("switch");
  platforms.append("ti99");
  platforms.append("trs-80");
  platforms.append("vectrex");
  platforms.append("vg5000");
  platforms.append("vic20");
  platforms.append("videopac");
  platforms.append("odyssey2");
  platforms.append("virtualboy");
  platforms.append("virtualboy-t-en");
  platforms.append("vpinball");
  platforms.append("vsmile");
  platforms.append("wii");
  platforms.append("wii-t-en");
  platforms.append("wiiu");
  platforms.append("windows");
  platforms.append("wonderswan");
  platforms.append("wonderswan-t-en");
  platforms.append("wonderswancolor");
  platforms.append("wonderswancolor-t-en");
  platforms.append("x68000");
  platforms.append("x68000-t-en");
  platforms.append("x1");
  platforms.append("x1-t-en");
  platforms.append("xbox");
  platforms.append("xbox-t-en");
  platforms.append("xbox360");
  platforms.append("xbox360-t-en");
  platforms.append("xboxone");
  platforms.append("zmachine");
  platforms.append("zx81");
  platforms.append("zxspectrum");

  return platforms;
}

QStringList Platform::getScrapers(QString platform) {
  QStringList scrapers;
  if (platform == "3do" || platform == "3do-t-en") {
    scrapers.append("screenscraper");
  } else if (platform == "3ds" || platform == "3ds-t-en") {
    scrapers.append("screenscraper");
  } else if (platform == "64dd" || platform == "64dd-t-en") {
    scrapers.append("screenscraper");
  } else if (platform == "actionmax") {
    scrapers.append("screenscraper");
  } else if (platform == "adam") {
    scrapers.append("screenscraper");
  } else if (platform == "advision") {
    scrapers.append("screenscraper");
  } else if (platform == "amiga") {
    scrapers.append("openretro");
    scrapers.append("screenscraper");
  } else if (platform == "amigacd") {
    scrapers.append("screenscraper");
  } else if (platform == "amigacd32" || platform == "amigacdtv") {
    scrapers.append("screenscraper");
  } else if (platform == "amstradcpc") {
    scrapers.append("screenscraper");
  } else if (platform == "apple2") {
    scrapers.append("screenscraper");
  } else if (platform == "apple2gs") {
    scrapers.append("screenscraper");
  } else if (platform == "arcade") {
    scrapers.append("arcadedb");
    scrapers.append("screenscraper");
  } else if (platform == "arcadia") {
    scrapers.append("screenscraper");
  } else if (platform == "archimedes") {
    scrapers.append("screenscraper");
  } else if (platform == "arduboy") {
    scrapers.append("screenscraper");
  } else if (platform == "astrocde") {
    scrapers.append("screenscraper");
  } else if (platform == "atari800") {
    scrapers.append("screenscraper");
  } else if (platform == "atari2600") {
    scrapers.append("screenscraper");
  } else if (platform == "atari5200") {
    scrapers.append("screenscraper");
  } else if (platform == "atari7800") {
    scrapers.append("screenscraper");
  } else if (platform == "atarijaguar") {
    scrapers.append("screenscraper");
  } else if (platform == "atarijaguarcd") {
    scrapers.append("screenscraper");
  } else if (platform == "atarilynx") {
    scrapers.append("screenscraper");
  } else if (platform == "atarist") {
    scrapers.append("screenscraper");
  } else if (platform == "atom") {
    scrapers.append("screenscraper");
  } else if (platform == "atomiswave") {
    scrapers.append("screenscraper");
  } else if (platform == "bbcmicro") {
    scrapers.append("screenscraper");
  } else if (platform == "c16") {
    scrapers.append("screenscraper");
  } else if (platform == "c64") {
    scrapers.append("screenscraper");
  } else if (platform == "c128") {
    scrapers.append("igdb");
    scrapers.append("thegamesdb");
  } else if (platform == "camplynx") {
    scrapers.append("screenscraper");
  } else if (platform == "cdi") {
    scrapers.append("screenscraper");
  } else if (platform == "channelf") {
    scrapers.append("screenscraper");
  } else if (platform == "coco") {
    scrapers.append("screenscraper");
  } else if (platform == "coleco") {
    scrapers.append("screenscraper");
  } else if (platform == "cps1") {
    scrapers.append("screenscraper");
  } else if (platform == "cps2") {
    scrapers.append("screenscraper");
  } else if (platform == "cps3") {
    scrapers.append("screenscraper");
  } else if (platform == "crvision") {
    scrapers.append("screenscraper");
  } else if (platform == "daphne") {
    scrapers.append("screenscraper");
  } else if (platform == "dragon") {
    scrapers.append("screenscraper");
  } else if (platform == "dreamcast" || platform == "dreamcast-t-en") {
    scrapers.append("screenscraper");
  } else if (platform == "easyrpg") {
    scrapers.append("screenscraper");
  } else if (platform == "exl100") {
    scrapers.append("screenscraper");
  } else if (platform == "fbneo") {
    scrapers.append("arcadedb");
    scrapers.append("screenscraper");
  } else if (platform == "fds" || platform == "fds-t-en") {
    scrapers.append("screenscraper");
  } else if (platform == "fm7") {
    scrapers.append("screenscraper");
  } else if (platform == "fmtowns" || platform == "fmtowns-t-en") {
    scrapers.append("screenscraper");
  } else if (platform == "gameandwatch") {
    scrapers.append("screenscraper");
  } else if (platform == "gamecom") {
    scrapers.append("screenscraper");
  } else if (platform == "gamegear" || platform == "gamegear-t-en") {
    scrapers.append("screenscraper");
  } else if (platform == "gamemaster") {
    scrapers.append("screenscraper");
  } else if (platform == "gamepock") {
    scrapers.append("screenscraper");
  } else if (platform == "gb" || platform == "gb-t-en") {
    scrapers.append("screenscraper");
  } else if (platform == "gba" || platform == "gba-t-en") {
    scrapers.append("screenscraper");
  } else if (platform == "gbc" || platform == "gbc-t-en") {
    scrapers.append("screenscraper");
  } else if (platform == "gc") {
    scrapers.append("screenscraper");
  } else if (platform == "genesis") {
    scrapers.append("screenscraper");
  } else if (platform == "gp32") {
    scrapers.append("screenscraper");
  } else if (platform == "gx4000") {
    scrapers.append("screenscraper");
  } else if (platform == "hikaru") {
    scrapers.append("screenscraper");
  } else if (platform == "intellivision") {
    scrapers.append("screenscraper");
  } else if (platform == "mame-advmame") {
    scrapers.append("arcadedb");
    scrapers.append("screenscraper");
  } else if (platform == "mame-libretro") {
    scrapers.append("arcadedb");
    scrapers.append("screenscraper");
  } else if (platform == "mame-mame4all") {
    scrapers.append("arcadedb");
    scrapers.append("screenscraper");
  } else if (platform == "mastersystem" || platform == "mastersystem-t-en") {
    scrapers.append("screenscraper");
  } else if (platform == "megacd") {
    scrapers.append("screenscraper");
  } else if (platform == "megadrive" || platform == "megadrive-msu" || platform == "megadrive-t-en") {
    scrapers.append("screenscraper");
  } else if (platform == "megaduck") {
    scrapers.append("screenscraper");
  } else if (platform == "moto") {
    scrapers.append("screenscraper");
  } else if (platform == "msx" || platform == "msx1" || platform == "msx1-t-en") {
    scrapers.append("screenscraper");
  } else if (platform == "msx2" || platform == "msx2-t-en") {
    scrapers.append("screenscraper");
  } else if (platform == "msx2+") {
    scrapers.append("screenscraper");
  } else if (platform == "n64" || platform == "n64-t-en") {
    scrapers.append("screenscraper");
  } else if (platform == "naomi") {
    scrapers.append("screenscraper");
  } else if (platform == "naomi2") {
    scrapers.append("screenscraper");
  } else if (platform == "nds" || platform == "nds-t-en" || platform == "ndsi" || platform == "ndsi-t-en") {
    scrapers.append("screenscraper");
  } else if (platform == "neogeo") {
    scrapers.append("arcadedb");
    scrapers.append("screenscraper");
  } else if (platform == "neogeocd" || platform == "neogeocd-t-en") {
    scrapers.append("screenscraper");
  } else if (platform == "nes") {
    scrapers.append("screenscraper");
  } else if (platform == "ngp") {
    scrapers.append("screenscraper");
  } else if (platform == "ngpc" || platform == "ngpc-t-en") {
    scrapers.append("screenscraper");
  } else if (platform == "openbor") {
    scrapers.append("screenscraper");
  } else if (platform == "oric" || platform == "oricatmos") {
    scrapers.append("screenscraper");
  } else if (platform == "pc") {
    scrapers.append("thegamesdb");
  } else if (platform == "pc88" || platform == "pc88-t-en") {
    scrapers.append("screenscraper");
    scrapers.append("thegamesdb");
  } else if (platform == "pc98" || platform == "pc98-t-en") {
    scrapers.append("screenscraper");
    scrapers.append("thegamesdb");
  } else if (platform == "pcfx" || platform == "pcfx-t-en") {
    scrapers.append("screenscraper");
  } else if (platform == "pcengine" || platform == "pcengine-t-en") {
    scrapers.append("screenscraper");
  } else if (platform == "pcenginecd" || platform == "pcenginecd-t-en") {
    scrapers.append("screenscraper");
  } else if(platform == "pico") {
    scrapers.append("screenscraper");
  } else if(platform == "pico8") {
    scrapers.append("screenscraper");
  } else if(platform == "pokemini" || platform == "pokemini-t-en") {
    scrapers.append("screenscraper");
  } else if (platform == "ports") {
    scrapers.append("thegamesdb");
  } else if (platform == "ps2" || platform == "ps2-t-en") {
    scrapers.append("screenscraper");
    scrapers.append("thegamesdb");
  } else if (platform == "ps3" || platform == "ps3-t-en") {
    scrapers.append("screenscraper");
  } else if (platform == "ps4") {
    scrapers.append("screenscraper");
  } else if (platform == "psp" || platform == "psp-t-en") {
    scrapers.append("screenscraper");
  } else if (platform == "psvita") {
    scrapers.append("screenscraper");
  } else if (platform == "psx" || platform == "psx-t-en") {
    scrapers.append("screenscraper");
    scrapers.append("thegamesdb");
  } else if (platform == "pv1000") {
    scrapers.append("screenscraper");
  } else if (platform == "samcoupe") {
    scrapers.append("screenscraper");
  } else if (platform == "saturn" || platform == "saturn-t-en") {
    scrapers.append("screenscraper");
  } else if (platform == "scummvm") {
    scrapers.append("screenscraper");
    scrapers.append("thegamesdb");
  } else if (platform == "scv") {
    scrapers.append("screenscraper");
  } else if (platform == "sega32x") {
    scrapers.append("screenscraper");
  } else if (platform == "segamodel2") {
    scrapers.append("screenscraper");
  } else if (platform == "segamodel3") {
    scrapers.append("screenscraper");
  } else if (platform == "segacd" || platform == "segacd-t-en") {
    scrapers.append("screenscraper");
  } else if (platform == "sg-1000" || platform == "sg-1000-t-en") {
    scrapers.append("screenscraper");
  } else if (platform == "snes" || platform == "snes-t-en") {
    scrapers.append("screenscraper");
  } else if (platform == "snes-msu") {
    scrapers.append("screenscraper");
  } else if (platform == "solarus") {
    scrapers.append("screenscraper");
  } else if (platform == "spectravideo") {
    scrapers.append("screenscraper");
  } else if (platform == "supergrafx") {
    scrapers.append("screenscraper");
  } else if (platform == "supervision") {
    scrapers.append("screenscraper");
  } else if (platform == "switch") {
    scrapers.append("screenscraper");
  } else if (platform == "ti99") {
    scrapers.append("screenscraper");
  } else if (platform == "steam") {
    scrapers.append("screenscraper");
  } else if (platform == "ti99") {
    scrapers.append("screenscraper");
  } else if (platform == "trs-80") {
    scrapers.append("screenscraper");
  } else if (platform == "vectrex") {
    scrapers.append("screenscraper");
  } else if (platform == "vg5000") {
    scrapers.append("screenscraper");
  } else if (platform == "vic20") {
    scrapers.append("screenscraper");
  } else if (platform == "videopac" || platform == "odyssey2") {
    scrapers.append("screenscraper");
  } else if (platform == "virtualboy" || platform == "virtualboy-t-en") {
    scrapers.append("screenscraper");
  } else if (platform == "vpinball") {
    scrapers.append("screenscraper");
  } else if (platform == "vsmile") {
    scrapers.append("screenscraper");
  } else if (platform == "wii" || platform == "wii-t-en") {
    scrapers.append("thegamesdb");
    scrapers.append("screenscraper");
  } else if (platform == "wiiu") {
    scrapers.append("thegamesdb");
    scrapers.append("screenscraper");
  } else if (platform == "windows") {
    scrapers.append("screenscraper");
  } else if (platform == "wonderswan" || platform == "wonderswan-t-en") {
    scrapers.append("screenscraper");
  } else if (platform == "wonderswancolor" || platform == "wonderswancolor-t-en") {
    scrapers.append("screenscraper");
  } else if (platform == "x68000" || platform == "x68000-t-en") {
    scrapers.append("screenscraper");
  } else if (platform == "x1" || platform == "x1-t-en") {
    scrapers.append("screenscraper");
  } else if (platform == "xbox" || platform == "xbox-t-en") {
    scrapers.append("screenscraper");
  } else if (platform == "zmachine") {
    scrapers.append("thegamesdb");
  } else if (platform == "zx81") {
    scrapers.append("screenscraper");
  } else if (platform == "zxspectrum") {
    scrapers.append("screenscraper");
  }

  // Always add 'cache' as the last one
  scrapers.append("cache");

  return scrapers;
}

QString Platform::getFormats(QString platform, QString extensions,
                             QString addExtensions) {
  if (!extensions.isEmpty() && extensions.contains("*.")) {
    return extensions;
  }

  QString formats = "*.zip *.7z *.ml "; // The last ' ' IS IMPORTANT!!!!!
  if (!addExtensions.isEmpty() && addExtensions.contains("*.")) {
    formats.append(addExtensions);
  }
  if (formats.right(1) != " ") {
    formats.append(" ");
  }
  if (platform == "3do" || platform == "3do-t-en") {
    formats.append("*.iso *.cue *.chd");
  } else if (platform == "3ds" || platform == "3ds-t-en") {
    formats.append("*.3ds");
  } else if (platform == "64dd" || platform == "64dd-t-en") {
    formats.append("*.ndd");
  } else if (platform == "actionmax") {
    formats.append("*.actionmax");
  } else if (platform == "adam") {
    formats.append("*.ndd");
  } else if (platform == "advision") {
    formats.append("*.bin");
  } else if (platform == "amiga") {
    formats.append(
        "*.uae *.adf *.dms *.adz *.rp9 *.lha *.cue *.img *.iso *.hdf");
  } else if (platform == "amigacd") {
    formats.append("*.cue *.img *.iso *.hdf *.chd");
  } else if (platform == "amigacd32" || platform == "amigacdtv") {
    formats.append(
        "*.uae *.adf *.dms *.adz *.rp9 *.lha *.cue *.img *.iso *.hdf *.chd");
  } else if (platform == "amstradcpc") {
    formats.append("*.dsk *.cpc");
  } else if (platform == "apple2") {
    formats.append("*.nib *.do *.po *.dsk");
  } else if (platform == "apple2gs") {
    formats.append("*.2mg *.po");
  } else if (platform == "arcade") {
    formats.append("*.bin *.dat");
  } else if (platform == "arcadia") {
    formats.append("*.bin");
  } else if (platform == "archimedes") {
    formats.append("*.adf *.jfd");
  } else if (platform == "astrocade") {
    formats.append("*.bin");
  } else if (platform == "atari800") {
    formats.append(
        "*.a52 *.bas *.bin *.car *.cas *.cdm *.xex *.atr *.atx *.xfd *.dcm *.atr.gz *.xfd.gz *.rom");
  } else if (platform == "atari2600") {
    formats.append("*.bin *.a26 *.rom *.gz");
  } else if (platform == "atari5200") {
    formats.append(
        "*.a52 *.bas *.bin *.car *.xex *.atr *.xfd *.dcm *.atr.gz *.xfd.gz");
  } else if (platform == "atari7800") {
    formats.append("*.a78 *.bin");
  } else if (platform == "atarijaguar") {
    formats.append("*.j64 *.jag");
  } else if (platform == "atarijaguarcd") {
    formats.append("*.j64 *.jag *.cue *.chd");
  } else if (platform == "atarilynx") {
    formats.append("*.lnx");
  } else if (platform == "atarist") {
    formats.append("*.st *.stx *.img *.rom *.raw *.ipf *.ctr");
  } else if (platform == "atom") {
    formats.append("*.tap *.csw *.uef *.dsk");
  } else if (platform == "atomiswave") {
    formats.append("*.bin *.dat *.chd");
  } else if (platform == "bbcmicro") {
    formats.append("*.adl *.bin *.dsd *.ssd *.uef");
  } else if (platform == "c16") {
    formats.append("*.crt *.d64 *.prg *.tap *.t64 *.g64 *.x64 *.vsf");
  } else if (platform == "c64") {
    formats.append("*.crt *.d64 *.prg *.tap *.t64 *.g64 *.x64 *.vsf");
  } else if (platform == "c128") {
    formats.append("*.crt *.d64 *.prg *.tap *.t64 *.g64 *.x64 *.vsf");
  } else if (platform == "camplynx") {
    formats.append("*.bin");
  } else if (platform == "cdi") {
    formats.append("*.cue *.bin *.chd");
  } else if (platform == "channelf") {
    formats.append("*.bin *.rom");
  } else if (platform == "coco") {
    formats.append("*.cas *.wav *.bas *.asc *.dmk *.jvc *.os9 *.dsk *.vdk "
                   "*.rom *.ccc *.sna");
  } else if (platform == "coleco") {
    formats.append("*.bin *.col *.rom");
  } else if (platform == "crvision") {
    formats.append("*.rom");
  } else if (platform == "daphne") {
    formats.append("*.daphne");
  } else if (platform == "dragon") {
    formats.append("*.cas *.wav *.bas *.asc *.dmk *.jvc *.os9 *.dsk *.vdk "
                   "*.rom *.ccc *.sna");
  } else if (platform == "dreamcast" || platform == "dreamcast-t-en") {
    formats.append("*.cdi *.gdi *.iso *.chd *.cue *.m3u");
  } else if (platform == "easyrpg") {
    formats.append("*.ini");
  } else if (platform == "exl100") {
    formats.append("*.bin *.k7 *.rom *.wav");
  } else if (platform == "fbneo") {
    formats.append("");
  } else if (platform == "fds" || platform == "fds-t-en") {
    formats.append("*.fds *.nes");
  } else if (platform == "fm7") {
    formats.append("*.d88 *.d77 *.t77 *.wav");
  } else if (platform == "fmtowns" || platform == "fmtowns-t-en") {
    formats.append("*.m3u *.d88 *.d77 *.xdf *.cue *.iso *.game *.cd *.chd");
  } else if (platform == "gameandwatch") {
    formats.append("*.mgw");
  } else if (platform == "gamecom") {
    formats.append("*.tgc");
  } else if (platform == "gamegear" || platform == "gamegear-t-en") {
    formats.append("*.gg");
  } else if (platform == "gamepock") {
    formats.append("*.bin");
  } else if (platform == "gb" || platform == "gb-t-en") {
    formats.append("*.gb");
  } else if (platform == "gba" || platform == "gba-t-en") {
    formats.append("*.gba");
  } else if (platform == "gbc" || platform == "gbc-t-en") {
    formats.append("*.gbc");
  } else if (platform == "gc") {
    formats.append("*.iso *.cso *.gcz *.gcm *.m3u *.rvz");
  } else if (platform == "genesis") {
    formats.append("*.smd *.bin *.gen *.md *.sg");
  } else if (platform == "gmaster") {
    formats.append("*.bin");
  } else if (platform == "gp32") {
    formats.append("*.smc");
  } else if (platform == "gx4000") {
    formats.append("*.cpr");
  } else if (platform == "intellivision") {
    formats.append("*.int *.bin");
  } else if (platform == "mame-advmame") {
    formats.append("");
  } else if (platform == "mame-libretro") {
    formats.append("");
  } else if (platform == "mame-mame4all") {
    formats.append("");
  } else if (platform == "mastersystem" || platform == "mastersystem-t-en") {
    formats.append("*.sms");
  } else if (platform == "megacd") {
    formats.append("*.cue *.iso *.chd");
  } else if (platform == "megadrive" || platform == "megadrive-msu" || platform == "megadrive-t-en") {
    formats.append("*.smd *.bin *.gen *.md *.sg");
  } else if (platform == "megaduck") {
    formats.append("*.bin");
  } else if (platform == "moto") {
    formats.append("*.fd *.sap *.k7 *.m5 *.m7 *.rom");
  } else if (platform == "msx" || platform == "msx1" || platform == "msx1-t-en") {
    formats.append("*.rom *.mx1 *.mx2 *.col *.dsk");
  } else if (platform == "msx2" || platform == "msx2-t-en") {
    formats.append("*.rom *.mx1 *.mx2 *.col *.dsk");
  } else if (platform == "msx2+") {
    formats.append("*.rom *.ri *.mx1 *.mx2 *.col *.dsk *.cas *.sg *.sc *.m3u");
  } else if (platform == "msxturbor" || platform == "msxturbor-t-en") {
    formats.append("*.rom *.ri *.mx1 *.mx2 *.col *.dsk *.cas *.wav *.ogv *.sg *.sc *.m3u");
  } else if (platform == "n64" || platform == "n64-t-en") {
    formats.append("*.z64 *.n64 *.v64");
  } else if (platform == "naomi") {
    formats.append("*.cue *.bin *.dat *.chd");
  } else if (platform == "naomi2") {
    formats.append("*.cue *.bin *.dat *.chd");
  } else if (platform == "nds" || platform == "nds-t-en" || platform == "ndsi" || platform == "ndsi-t-en") {
    formats.append("*.nds *.dsi *.ids *.srl *.zip *.7z *.rar *.tar *.tar.gz *.tar.xz *.tar.bz2");
  } else if (platform == "neogeo") {
    formats.append("");
  } else if (platform == "neogeocd" || platform == "neogeocd-t-en") {
    formats.append("*.cue *.chd *.iso");
  } else if (platform == "nes") {
    formats.append("*.nes *.smc *.sfc *.fig *.swc *.mgd");
  } else if (platform == "ngp") {
    formats.append(" *.ngp");
  } else if (platform == "ngpc" || platform == "ngpc-t-en") {
    formats.append(" *.ngc");
  } else if (platform == "openbor") {
    formats.append(" *.pak");
  } else if (platform == "oric" || platform == "oricatmos") {
    formats.append(" *.dsk *.tap");
  } else if (platform == "pc") {
    formats.append("*.com *.sh *.bat *.exe *.conf");
  } else if (platform == "pc88" || platform == "pc88-t-en") {
    formats.append("*.d88 *.88d *.cmt *.t88");
  } else if (platform == "pc98" || platform == "pc98-t-en") {
    formats.append("*.d88 *.d98 *.88d *.98d *.fdi *.xdf *.hdm *.dup *.2hd "
                   "*.tfd *.hdi *.thd *.nhd *.hdd *.fdd *.cmd *.hdn");
  } else if (platform == "pcfx" || platform == "pcfx-t-en") {
    formats.append("*.img *.iso *.ccd *.cue *.chd");
  } else if (platform == "pcengine" || platform == "pcengine-t-en") {
    formats.append("*.pce *.chd *.cue");
  } else if (platform == "pcenginecd" || platform == "pcenginecd-t-en") {
    formats.append("*.pce *.chd *.cue");
  } else if (platform == "pet") {
    formats.append("*.a0 *.b0 *.crt *.d64 *.d81 *.prg *.tap *.t64 *.m3u");
  } else if(platform == "pico") {
    formats.append("*.md");
  } else if(platform == "pico8") {
    formats.append("*.png *.p8");
  } else if(platform == "pokemini" || platform == "pokemini-t-en") {
    formats.append("*.min");
  } else if (platform == "ports") {
    formats.append("*.com *.sh *.bat *.exe *.conf");
  } else if (platform == "ps2" || platform == "ps2-t-en") {
    formats.append(
        "*.iso *.cue *.img *.mdf *.z *.z2 *.bz2 *.dump *.cso *.ima *.gz *.chd");
  } else if (platform == "psp" || platform == "psp-t-en") {
    formats.append("*.cso *.iso *.pbp");
  } else if(platform == "psx" || platform == "psx-t-en") {
    formats.append("*.cue *.cbn *.img *.iso *.m3u *.mdf *.pbp *.toc *.z *.znx *.chd");
  } else if(platform == "pv1000") {
    formats.append("*.bin");
  } else if (platform == "samcoupe") {
    formats.append("*.dsk *.sad *.mgt *.sbt *.cpm *.gz");
  } else if(platform == "saturn" || platform == "saturn-t-en") {
    formats.append("*.cue *.iso *.mdf *.chd *.m3u");
  } else if(platform == "scummvm") {
    formats.append("*.svm *.scummvm");
  } else if(platform == "scv") {
    formats.append("*.bin");
  } else if (platform == "sega32x") {
    formats.append("*.32x *.bin *.md *.smd");
  } else if(platform == "segacd" || platform == "segacd-t-en") {
    formats.append("*.cue *.iso *.chd *.m3u");
  } else if(platform == "sg-1000" || platform == "sg-1000-t-en") {
    formats.append("*.bin *.sg");
  } else if (platform == "snes" || platform == "snes-t-en") {
    formats.append("*.smc *.sfc *.fig *.swc *.mgd *.bin");
  } else if (platform == "snes-msu") {
    formats.append("*.smc *.sfc *.bml *.m3u");
  } else if (platform == "solarus") {
    formats.append("*.solarus");
  } else if (platform == "spectravideo") {
    formats.append("*.cas *.bin");
  } else if (platform == "supergrafx") {
    formats.append("*.sgx");
  } else if (platform == "supervision") {
    formats.append("*.sv *.bin");
  } else if (platform == "switch") {
    formats.append("*.xci *.nsp");
  } else if (platform == "ti99") {
    formats.append("*.ctg");
  } else if (platform == "trs-80") {
    formats.append("*.dsk");
  } else if (platform == "vectrex") {
    formats.append("*.bin *.gam *.vec");
  } else if (platform == "vg5000") {
    formats.append("*.k7");
  } else if (platform == "vic20") {
    formats.append("*.crt *.d64 *.prg *.tap *.t64 *.g64 *.x64 *.vsf");
  } else if (platform == "videopac" || platform == "odyssey2") {
    formats.append("*.bin");
  } else if (platform == "virtualboy" || platform == "virtualboy-t-en") {
    formats.append("*.vb");
  } else if (platform == "vpinball") {
    formats.append("*.bin");
  } else if (platform == "vsmile") {
    formats.append("*.bin");
  } else if (platform == "wii" || platform == "wii-t-en") {
    formats.append("*.iso *.cso *.gcz *.wbfs *.rvz");
  } else if (platform == "wiiu") {
    formats.append("*.iso *.cso *.gcz *.wbfs *.wud *.wux *.wua *.rpx *.app");
  } else if (platform == "windows") {
    formats.append("*.lnk .bat .exe");
  } else if (platform == "wonderswan" || platform == "wonderswan-t-en") {
    formats.append("*.ws");
  } else if (platform == "wonderswancolor" || platform == "wonderswancolor-t-en") {
    formats.append("*.wsc");
  } else if (platform == "x68000" || platform == "x68000-t-en") {
    formats.append("*.dim *.m3u");
  } else if (platform == "x1" || platform == "x1-t-en") {
    formats.append(
        "*.dx1 *.2d *.2hd *.tfd *.d88 *.88d *.hdm *.xdf *.dup *.cmd");
  } else if (platform == "x1") {
    formats.append("*.iso");
  } else if (platform == "xbox" || platform == "xbox-t-en") {
    formats.append("*.iso");
  } else if (platform == "xbox360" || platform == "xbox360-t-en") {
    formats.append("*.iso");
  } else if (platform == "zmachine") {
    formats.append("*.dat *.z1 *.z2 *.z3 *.z4 *.z5 *.z6 *.z7 *.z8");
  } else if (platform == "zx81") {
    formats.append("*.p *.tzx *.t81");
  } else if (platform == "zxspectrum") {
    formats.append("*.sna *.szx *.z80 *.tap *.tzx *.gz *.udi *.mgt *.img *.trd "
                   "*.scl *.dsk");
  }
  return formats;
}

// If user provides no scraping source with '-s' this sets the default for the
// platform
QString Platform::getDefaultScraper(QString platform) {
  QString scraper = "cache";

  if (platform.isEmpty() == true) {
    scraper.clear();

    return scraper;
  }

  return scraper;
}

// This contains all known platform aliases as listed on each of the scraping
// source sites
QStringList Platform::getAliases(QString platform) {
  QStringList aliases;
  // Platform name itself is always appended as the first alias
  aliases.append(platform);

  // If you don't find the platform listed below, it's probably because the
  // needed alias is the same as the platform name and has already been appended
  // above.
  if (platform == "3ds") {
    aliases.append("nintendo 3ds");
  } else if (platform == "amiga") {
    aliases.append("amiga (aga)");
    aliases.append("amiga cdtv");
    aliases.append("amiga cd32");
    aliases.append("amiga cd32 (hack)");
    aliases.append("amiga cd");
  } else if (platform == "amigacd32" || platform == "amigacdtv") {
    aliases.append("amiga (aga)");
    aliases.append("amiga cdtv");
    aliases.append("amiga cd32");
    aliases.append("amiga cd32 (hack)");
    aliases.append("amiga cd");
  } else if (platform == "amstradcpc") {
    aliases.append("amstrad cpc");
    aliases.append("cpc");
  } else if (platform == "apple2") {
    aliases.append("apple ii");
  } else if (platform == "arcade") {
    aliases.append("neo geo");
    aliases.append("neo-geo");
    aliases.append("neo geo cd");
    aliases.append("neo-geo cd");
    aliases.append("neo-geo mvs");
    aliases.append("capcom play system");
    aliases.append("capcom play system 2");
    aliases.append("capcom play system 3");
    aliases.append("another arcade emulator");
    aliases.append("cave");
    aliases.append("daphne");
    aliases.append("atomiswave");
    aliases.append("model 2");
    aliases.append("model 3");
    aliases.append("naomi");
    aliases.append("sega st-v");
    aliases.append("mame");
    aliases.append("type x");
    aliases.append("sega classics");
    aliases.append("irem classics");
    aliases.append("seta");
    aliases.append("midway classics");
    aliases.append("capcom classics");
    aliases.append("eighting / raizing");
    aliases.append("tecmo");
    aliases.append("snk classics");
    aliases.append("namco classics");
    aliases.append("namco system 22");
    aliases.append("taito classics");
    aliases.append("konami classics");
    aliases.append("jaleco");
    aliases.append("atari classics");
    aliases.append("nintendo classics");
    aliases.append("data east classics");
    aliases.append("nmk");
    aliases.append("sammy classics");
    aliases.append("exidy");
    aliases.append("acclaim");
    aliases.append("psikyo");
    aliases.append("non jeu");
    aliases.append("technos");
    aliases.append("american laser games");
    aliases.append("dynax");
    aliases.append("kaneko");
    aliases.append("video system co.");
    aliases.append("igs");
    aliases.append("comad");
    aliases.append("amcoe");
    aliases.append("century electronics");
    aliases.append("nichibutsu");
    aliases.append("visco");
    aliases.append("alpha denshi co.");
    aliases.append("coleco");
    aliases.append("playchoice");
    aliases.append("atlus");
    aliases.append("banpresto");
    aliases.append("semicom");
    aliases.append("universal");
    aliases.append("mitchell");
    aliases.append("seibu kaihatsu");
    aliases.append("toaplan");
    aliases.append("cinematronics");
    aliases.append("incredible technologies");
    aliases.append("gaelco");
    aliases.append("mega-tech");
    aliases.append("mega-play");
  } else if (platform == "arcadia") {
    aliases.append("arcadia 2001");
    aliases.append("emerson arcadia 2001");
  } else if (platform == "astrocde") {
    aliases.append("astrocade");
    aliases.append("bally astrocade");
  } else if (platform == "atari800") {
    aliases.append("atari 800");
    aliases.append("atari 8-bit");
    aliases.append("atari 5200");
  } else if (platform == "atari2600") {
    aliases.append("atari 2600");
  } else if (platform == "atari5200") {
    aliases.append("atari 5200");
  } else if (platform == "atari7800") {
    aliases.append("atari 7800");
  } else if (platform == "atarijaguar") {
    aliases.append("atari jaguar");
    aliases.append("jaguar");
  } else if (platform == "atarijaguarcd") {
    aliases.append("atari jaguar");
    aliases.append("jaguar");
    aliases.append("atari jaguar cd");
    aliases.append("jaguar cd");
  } else if (platform == "atarilynx") {
    aliases.append("atari lynx");
    aliases.append("lynx");
  } else if (platform == "atarist") {
    aliases.append("atari st");
    aliases.append("atari st/ste");
  } else if (platform == "atomiswave") {
    aliases.append("model 2");
    aliases.append("model 3");
    aliases.append("naomi");
    aliases.append("sega st-v");
    aliases.append("mame");
    aliases.append("type x");
    aliases.append("sega classics");
    aliases.append("irem classics");
    aliases.append("seta");
    aliases.append("midway classics");
    aliases.append("capcom classics");
    aliases.append("eighting / raizing");
    aliases.append("tecmo");
    aliases.append("snk classics");
    aliases.append("namco classics");
    aliases.append("namco system 22");
    aliases.append("taito classics");
    aliases.append("konami classics");
    aliases.append("jaleco");
    aliases.append("atari classics");
    aliases.append("nintendo classics");
    aliases.append("data east classics");
    aliases.append("nmk");
    aliases.append("sammy classics");
    aliases.append("exidy");
    aliases.append("acclaim");
    aliases.append("psikyo");
    aliases.append("non jeu");
    aliases.append("technos");
    aliases.append("american laser games");
    aliases.append("dynax");
    aliases.append("kaneko");
    aliases.append("video system co.");
    aliases.append("igs");
    aliases.append("comad");
    aliases.append("amcoe");
    aliases.append("century electronics");
    aliases.append("nichibutsu");
    aliases.append("visco");
    aliases.append("alpha denshi co.");
    aliases.append("coleco");
    aliases.append("playchoice");
    aliases.append("atlus");
    aliases.append("banpresto");
    aliases.append("semicom");
    aliases.append("universal");
    aliases.append("mitchell");
    aliases.append("seibu kaihatsu");
    aliases.append("toaplan");
    aliases.append("cinematronics");
    aliases.append("incredible technologies");
    aliases.append("gaelco");
    aliases.append("mega-tech");
    aliases.append("mega-play");
  } else if (platform == "c16") {
    aliases.append("plus/4");
    aliases.append("commodore plus/4");
    aliases.append("commodore 16");
    aliases.append("commodore 16, plus/4");
  } else if (platform == "c64") {
    aliases.append("commodore 64");
    aliases.append("commodore c64/128");
  } else if (platform == "c128") {
    aliases.append("commodore 128");
    aliases.append("commodore 64");
    aliases.append("commodore c64/128");
  } else if (platform == "amigacd32") {
    aliases.append("amiga cd32");
    aliases.append("amiga cd32 (hack)");
  } else if (platform == "amigacdtv") {
    aliases.append("amiga cdtv");
  } else if (platform == "channelf") {
    aliases.append("fairchild channel f");
    aliases.append("channel f");
  } else if (platform == "coco") {
    aliases.append("trs-80 color computer");
    aliases.append("trs-80 coco");
  } else if (platform == "coleco") {
    aliases.append("colecovision");
  } else if (platform == "daphne") {
    aliases.append("pioneer laseractive");
    aliases.append("laseractive");
    aliases.append("american laser games");
  } else if (platform == "dragon") {
    aliases.append("dragon 32/64");
  } else if (platform == "dreamcast") {
    aliases.append("sega dreamcast");
  } else if (platform == "fbneo") {
    aliases.append("arcade");
    aliases.append("neo geo");
    aliases.append("neo-geo");
    aliases.append("neo geo cd");
    aliases.append("neo-geo cd");
    aliases.append("neo-geo mvs");
    aliases.append("capcom play system");
    aliases.append("capcom play system 2");
    aliases.append("capcom play system 3");
    aliases.append("another arcade emulator");
    aliases.append("cave");
    aliases.append("daphne");
    aliases.append("atomiswave");
    aliases.append("model 2");
    aliases.append("model 3");
    aliases.append("naomi");
    aliases.append("sega st-v");
    aliases.append("mame");
    aliases.append("type x");
    aliases.append("sega classics");
    aliases.append("irem classics");
    aliases.append("seta");
    aliases.append("midway classics");
    aliases.append("capcom classics");
    aliases.append("eighting / raizing");
    aliases.append("tecmo");
    aliases.append("snk classics");
    aliases.append("namco classics");
    aliases.append("namco system 22");
    aliases.append("taito classics");
    aliases.append("konami classics");
    aliases.append("jaleco");
    aliases.append("atari classics");
    aliases.append("nintendo classics");
    aliases.append("data east classics");
    aliases.append("nmk");
    aliases.append("sammy classics");
    aliases.append("exidy");
    aliases.append("acclaim");
    aliases.append("psikyo");
    aliases.append("non jeu");
    aliases.append("technos");
    aliases.append("american laser games");
    aliases.append("dynax");
    aliases.append("kaneko");
    aliases.append("video system co.");
    aliases.append("igs");
    aliases.append("comad");
    aliases.append("amcoe");
    aliases.append("century electronics");
    aliases.append("nichibutsu");
    aliases.append("visco");
    aliases.append("alpha denshi co.");
    aliases.append("coleco");
    aliases.append("playchoice");
    aliases.append("atlus");
    aliases.append("banpresto");
    aliases.append("semicom");
    aliases.append("universal");
    aliases.append("mitchell");
    aliases.append("seibu kaihatsu");
    aliases.append("toaplan");
    aliases.append("cinematronics");
    aliases.append("incredible technologies");
    aliases.append("gaelco");
    aliases.append("mega-tech");
    aliases.append("mega-play");
  } else if (platform == "fds") {
    aliases.append("famicom disk system");
    aliases.append("family computer disk system");
    aliases.append("famiri konpyuta disuku shisutemu");
    aliases.append("nintendo entertainment system (nes)");
    aliases.append("nintendo");
  } else if (platform == "gameandwatch") {
    aliases.append("game & watch");
  } else if (platform == "gamegear") {
    aliases.append("sega game gear");
    aliases.append("game gear");
  } else if (platform == "gb") {
    aliases.append("nintendo game boy");
    aliases.append("game boy");
  } else if (platform == "gba") {
    aliases.append("nintendo game boy advance");
    aliases.append("game boy advance");
  } else if (platform == "gbc") {
    aliases.append("nintendo game boy color");
    aliases.append("game boy color");
    // Workaround: ScreenScraper sometimes returns gbc results with gb platform
    // applied This might bite me in the ass if other modules now return gb
    // results for gbc games...
    aliases.append("game boy");
  } else if (platform == "gc") {
    aliases.append("gamecube");
    aliases.append("nintendo gamecube");
  } else if (platform == "genesis") {
    aliases.append("megadrive");
    aliases.append("sega genesis");
    aliases.append("mega drive");
    aliases.append("sega mega drive");
    aliases.append("sega mega drive/genesis");
  } else if (platform == "gp32") {
    aliases.append("gamepark");
  } else if (platform == "mame-advmame") {
    aliases.append("arcade");
    aliases.append("neo geo");
    aliases.append("neo-geo");
    aliases.append("neo geo cd");
    aliases.append("neo-geo cd");
    aliases.append("neo-geo mvs");
    aliases.append("capcom play system");
    aliases.append("capcom play system 2");
    aliases.append("capcom play system 3");
    aliases.append("another arcade emulator");
    aliases.append("cave");
    aliases.append("daphne");
    aliases.append("atomiswave");
    aliases.append("model 2");
    aliases.append("model 3");
    aliases.append("naomi");
    aliases.append("sega st-v");
    aliases.append("mame");
    aliases.append("type x");
    aliases.append("sega classics");
    aliases.append("irem classics");
    aliases.append("seta");
    aliases.append("midway classics");
    aliases.append("capcom classics");
    aliases.append("eighting / raizing");
    aliases.append("tecmo");
    aliases.append("snk classics");
    aliases.append("namco classics");
    aliases.append("namco system 22");
    aliases.append("taito classics");
    aliases.append("konami classics");
    aliases.append("jaleco");
    aliases.append("atari classics");
    aliases.append("nintendo classics");
    aliases.append("data east classics");
    aliases.append("nmk");
    aliases.append("sammy classics");
    aliases.append("exidy");
    aliases.append("acclaim");
    aliases.append("psikyo");
    aliases.append("non jeu");
    aliases.append("technos");
    aliases.append("american laser games");
    aliases.append("dynax");
    aliases.append("kaneko");
    aliases.append("video system co.");
    aliases.append("igs");
    aliases.append("comad");
    aliases.append("amcoe");
    aliases.append("century electronics");
    aliases.append("nichibutsu");
    aliases.append("visco");
    aliases.append("alpha denshi co.");
    aliases.append("coleco");
    aliases.append("playchoice");
    aliases.append("atlus");
    aliases.append("banpresto");
    aliases.append("semicom");
    aliases.append("universal");
    aliases.append("mitchell");
    aliases.append("seibu kaihatsu");
    aliases.append("toaplan");
    aliases.append("cinematronics");
    aliases.append("incredible technologies");
    aliases.append("gaelco");
    aliases.append("mega-tech");
    aliases.append("mega-play");
  } else if (platform == "mame-libretro") {
    aliases.append("arcade");
    aliases.append("neo geo");
    aliases.append("neo-geo");
    aliases.append("neo geo cd");
    aliases.append("neo-geo cd");
    aliases.append("neo-geo mvs");
    aliases.append("capcom play system");
    aliases.append("capcom play system 2");
    aliases.append("capcom play system 3");
    aliases.append("another arcade emulator");
    aliases.append("cave");
    aliases.append("daphne");
    aliases.append("atomiswave");
    aliases.append("model 2");
    aliases.append("model 3");
    aliases.append("naomi");
    aliases.append("sega st-v");
    aliases.append("mame");
    aliases.append("type x");
    aliases.append("sega classics");
    aliases.append("irem classics");
    aliases.append("seta");
    aliases.append("midway classics");
    aliases.append("capcom classics");
    aliases.append("eighting / raizing");
    aliases.append("tecmo");
    aliases.append("snk classics");
    aliases.append("namco classics");
    aliases.append("namco system 22");
    aliases.append("taito classics");
    aliases.append("konami classics");
    aliases.append("jaleco");
    aliases.append("atari classics");
    aliases.append("nintendo classics");
    aliases.append("data east classics");
    aliases.append("nmk");
    aliases.append("sammy classics");
    aliases.append("exidy");
    aliases.append("acclaim");
    aliases.append("psikyo");
    aliases.append("non jeu");
    aliases.append("technos");
    aliases.append("american laser games");
    aliases.append("dynax");
    aliases.append("kaneko");
    aliases.append("video system co.");
    aliases.append("igs");
    aliases.append("comad");
    aliases.append("amcoe");
    aliases.append("century electronics");
    aliases.append("nichibutsu");
    aliases.append("visco");
    aliases.append("alpha denshi co.");
    aliases.append("coleco");
    aliases.append("playchoice");
    aliases.append("atlus");
    aliases.append("banpresto");
    aliases.append("semicom");
    aliases.append("universal");
    aliases.append("mitchell");
    aliases.append("seibu kaihatsu");
    aliases.append("toaplan");
    aliases.append("cinematronics");
    aliases.append("incredible technologies");
    aliases.append("gaelco");
    aliases.append("mega-tech");
    aliases.append("mega-play");
  } else if (platform == "mame-mame4all") {
    aliases.append("arcade");
    aliases.append("neo geo");
    aliases.append("neo-geo");
    aliases.append("neo geo cd");
    aliases.append("neo-geo cd");
    aliases.append("neo-geo mvs");
    aliases.append("capcom play system");
    aliases.append("capcom play system 2");
    aliases.append("capcom play system 3");
    aliases.append("another arcade emulator");
    aliases.append("cave");
    aliases.append("daphne");
    aliases.append("atomiswave");
    aliases.append("model 2");
    aliases.append("model 3");
    aliases.append("naomi");
    aliases.append("sega st-v");
    aliases.append("mame");
    aliases.append("type x");
    aliases.append("sega classics");
    aliases.append("irem classics");
    aliases.append("seta");
    aliases.append("midway classics");
    aliases.append("capcom classics");
    aliases.append("eighting / raizing");
    aliases.append("tecmo");
    aliases.append("snk classics");
    aliases.append("namco classics");
    aliases.append("namco system 22");
    aliases.append("taito classics");
    aliases.append("konami classics");
    aliases.append("jaleco");
    aliases.append("atari classics");
    aliases.append("nintendo classics");
    aliases.append("data east classics");
    aliases.append("nmk");
    aliases.append("sammy classics");
    aliases.append("exidy");
    aliases.append("acclaim");
    aliases.append("psikyo");
    aliases.append("non jeu");
    aliases.append("technos");
    aliases.append("american laser games");
    aliases.append("dynax");
    aliases.append("kaneko");
    aliases.append("video system co.");
    aliases.append("igs");
    aliases.append("comad");
    aliases.append("amcoe");
    aliases.append("century electronics");
    aliases.append("nichibutsu");
    aliases.append("visco");
    aliases.append("alpha denshi co.");
    aliases.append("coleco");
    aliases.append("playchoice");
    aliases.append("atlus");
    aliases.append("banpresto");
    aliases.append("semicom");
    aliases.append("universal");
    aliases.append("mitchell");
    aliases.append("seibu kaihatsu");
    aliases.append("toaplan");
    aliases.append("cinematronics");
    aliases.append("incredible technologies");
    aliases.append("gaelco");
    aliases.append("mega-tech");
    aliases.append("mega-play");
  } else if (platform == "mastersystem") {
    aliases.append("sega master system");
    aliases.append("master system");
  } else if (platform == "megacd") {
    aliases.append("segacd");
    aliases.append("sega cd");
    aliases.append("mega-cd");
  } else if (platform == "megadrive") {
    aliases.append("genesis");
    aliases.append("sega mega drive");
    aliases.append("sega mega drive/genesis");
    aliases.append("mega drive");
  } else if (platform == "moto") {
    aliases.append("thomson");
    aliases.append("thomson mo");
    aliases.append("thomson to");
    aliases.append("thomson mo5");
    aliases.append("thomson mo/to");
    aliases.append("thomson to7,thomson mo5");
  } else if (platform == "msx") {
    aliases.append("msx1");
    aliases.append("msx2");
    aliases.append("msx2+");
    aliases.append("msx r turbo");
  } else if (platform == "msx2") {
    aliases.append("msx");
    aliases.append("msx2");
    aliases.append("msx r turbo");
  } else if (platform == "n64") {
    aliases.append("nintendo 64");
  } else if (platform == "naomi") {
    aliases.append("neo geo");
    aliases.append("neo-geo");
    aliases.append("neo geo cd");
    aliases.append("neo-geo cd");
    aliases.append("neo-geo mvs");
    aliases.append("capcom play system");
    aliases.append("capcom play system 2");
    aliases.append("capcom play system 3");
    aliases.append("another arcade emulator");
    aliases.append("cave");
    aliases.append("daphne");
    aliases.append("atomiswave");
    aliases.append("model 2");
    aliases.append("model 3");
    aliases.append("sega st-v");
    aliases.append("mame");
    aliases.append("type x");
    aliases.append("sega classics");
    aliases.append("irem classics");
    aliases.append("seta");
    aliases.append("midway classics");
    aliases.append("capcom classics");
    aliases.append("eighting / raizing");
    aliases.append("tecmo");
    aliases.append("snk classics");
    aliases.append("namco classics");
    aliases.append("namco system 22");
    aliases.append("taito classics");
    aliases.append("konami classics");
    aliases.append("jaleco");
    aliases.append("atari classics");
    aliases.append("nintendo classics");
    aliases.append("data east classics");
    aliases.append("nmk");
    aliases.append("sammy classics");
    aliases.append("exidy");
    aliases.append("acclaim");
    aliases.append("psikyo");
    aliases.append("non jeu");
    aliases.append("technos");
    aliases.append("american laser games");
    aliases.append("dynax");
    aliases.append("kaneko");
    aliases.append("video system co.");
    aliases.append("igs");
    aliases.append("comad");
    aliases.append("amcoe");
    aliases.append("century electronics");
    aliases.append("nichibutsu");
    aliases.append("visco");
    aliases.append("alpha denshi co.");
    aliases.append("coleco");
    aliases.append("playchoice");
    aliases.append("atlus");
    aliases.append("banpresto");
    aliases.append("semicom");
    aliases.append("universal");
    aliases.append("mitchell");
    aliases.append("seibu kaihatsu");
    aliases.append("toaplan");
    aliases.append("cinematronics");
    aliases.append("incredible technologies");
    aliases.append("gaelco");
    aliases.append("mega-tech");
    aliases.append("mega-play");
  } else if (platform == "nds") {
    aliases.append("nintendo ds");
  } else if (platform == "neogeo") {
    aliases.append("neo-geo");
    aliases.append("neo geo");
    aliases.append("neo geo aes");
    aliases.append("neo geo mvs");
    aliases.append("neo geo cd");
    aliases.append("neo-geo cd");
    aliases.append("arcade");
  } else if (platform == "neogeocd") {
    aliases.append("neo-geo");
    aliases.append("neo geo");
    aliases.append("neo geo aes");
    aliases.append("neo geo mvs");
    aliases.append("neo geo cd");
    aliases.append("neo-geo cd");
    aliases.append("arcade");
  } else if (platform == "nes") {
    aliases.append("nintendo entertainment system (nes)");
    aliases.append("nintendo");
    aliases.append("nintendo power");
  } else if (platform == "ngp") {
    aliases.append("neo geo pocket");
    aliases.append("neo-geo pocket");
  } else if (platform == "ngpc") {
    aliases.append("neo geo pocket color");
    aliases.append("neo-geo pocket color");
  } else if (platform == "oric") {
    aliases.append("oric 1 / atmos");
  } else if (platform == "pc") {
    aliases.append("pc dos");
    aliases.append("pc win3.xx");
    aliases.append("dos");
    aliases.append("windows");
    aliases.append("windows 3.x");
    aliases.append("windows apps");
    aliases.append("pc (microsoft windows)");
    aliases.append("steamos");
  } else if (platform == "pc88") {
    aliases.append("pc-88");
    aliases.append("pc-8801");
  } else if (platform == "pc98") {
    aliases.append("pc-98");
    aliases.append("nec pc-9801");
  } else if (platform == "pcfx") {
    aliases.append("pc-fx");
  } else if (platform == "pcengine") {
    aliases.append("turbografx 16");
    aliases.append("turbografx cd");
    aliases.append("turbografx-16");
    aliases.append("turbografx-16/pc engine");
    aliases.append("turbografx-16/pc engine cd");
    aliases.append("pc engine");
    aliases.append("pc engine cd-rom");
    aliases.append("pc engine supergrafx");
  } else if (platform == "pcenginecd") {
    aliases.append("turbografx 16");
    aliases.append("turbografx cd");
    aliases.append("turbografx-16");
    aliases.append("turbografx-16/pc engine");
    aliases.append("turbografx-16/pc engine cd");
    aliases.append("pc engine");
    aliases.append("pc engine cd-rom");
    aliases.append("pc engine supergrafx");
  } else if(platform == "pico8") {
    aliases.append("pico-8");
    aliases.append("pico 8");
  } else if(platform == "pokemini") {
    aliases.append("nintendo pokémon mini");
    aliases.append("pokémon mini");
  } else if (platform == "ports") {
    aliases.append("pc dos");
    aliases.append("pc win3.xx");
    aliases.append("dos");
    aliases.append("windows");
    aliases.append("pc (microsoft windows)");
  } else if (platform == "psx") {
    aliases.append("sony playstation");
    aliases.append("playstation");
  } else if (platform == "ps2") {
    aliases.append("playstation 2");
    aliases.append("sony playstation 2");
  } else if (platform == "psp") {
    aliases.append("sony playstation portable");
    aliases.append("playstation portable");
  } else if (platform == "samcoupe") {
    aliases.append("sam coupe");
  } else if (platform == "saturn") {
    aliases.append("sega saturn");
  } else if (platform == "scummvm") {
    aliases.append("pc dos");
    aliases.append("pc win3.xx");
    aliases.append("pc");
    aliases.append("amiga");
    aliases.append("amiga cd32");
    aliases.append("dos");
    aliases.append("cd32");
    aliases.append("pc (microsoft windows)");
    aliases.append("windows");
    aliases.append("windows apps");
  } else if (platform == "sega32x") {
    aliases.append("sega 32x");
    aliases.append("megadrive 32x");
  } else if (platform == "segacd") {
    aliases.append("megacd");
    aliases.append("sega cd");
    aliases.append("mega-cd");
  } else if (platform == "sg-1000") {
    aliases.append("sega sg-1000");
  } else if (platform == "snes" || platform == "snes-t-en") {
    aliases.append("super nintendo (snes)");
    aliases.append("super nintendo entertainment system (snes)");
    aliases.append("super nintendo");
    aliases.append("super famicom");
    // The following are for screenscraper, but the platform check is currently
    // disabled for that module, so they don't really do anything.
    aliases.append("nintendo power");
    aliases.append("satellaview");
    aliases.append("sufami turbo");
    aliases.append("snes - super mario world hacks");
    aliases.append("super nintendo msu-1");
  } else if (platform == "steam") {
    aliases.append("pc dos");
    aliases.append("pc win3.xx");
    aliases.append("dos");
    aliases.append("windows");
    aliases.append("windows apps");
    aliases.append("pc (microsoft windows)");
    aliases.append("steamos");
    // Adding these consoles because 'thegamesdb' often only return these
    // instead of PC versions
    aliases.append("microsoft xbox one");
    aliases.append("sony playstation 4");
  } else if (platform == "switch") {
    aliases.append("nintendo switch");
  } else if (platform == "ti99") {
    aliases.append("ti-99/4a");
    aliases.append("texas instruments ti-99");
    aliases.append("texas instruments ti-99/4a");
  } else if (platform == "trs-80") {
    aliases.append("trs-80 color computer");
  } else if (platform == "vic20") {
    aliases.append("commodore vic-20");
    aliases.append("vic-20");
  } else if (platform == "videopac") {
    aliases.append("odyssey 2");
    aliases.append("magnavox odyssey 2");
    aliases.append("videopac g7000");
    aliases.append("philips videopac g7000");
    aliases.append("videopac+ g7400");
    aliases.append("magnavox odyssey²");
  } else if (platform == "virtualboy") {
    aliases.append("nintendo virtual boy");
    aliases.append("virtual boy");
  } else if (platform == "windows") {
    aliases.append("pc (microsoft windows)");
  } else if (platform == "wii") {
    aliases.append("nintendo wii");
    aliases.append("wiiware");
  } else if (platform == "wiiu") {
    aliases.append("nintendo wii u");
    aliases.append("wii u");
    aliases.append("wiiware");
  } else if (platform == "wonderswancolor" || platform == "wonderswancolor-t-en") {
    aliases.append("wonderswan color");
  } else if (platform == "x68000") {
    aliases.append("sharp x68000");
  } else if (platform == "zmachine") {
    aliases.append("x1");
  } else if (platform == "sharp x1") {
    aliases.append("z-machine");
  } else if (platform == "zxspectrum") {
    aliases.append("sinclair zx spectrum");
    aliases.append("zx spectrum");
  }
  return aliases;
}

// --- Console colors ---
// Black        0;30     Dark Gray     1;30
// Red          0;31     Light Red     1;31
// Green        0;32     Light Green   1;32
// Brown/Orange 0;33     Yellow        1;33
// Blue         0;34     Light Blue    1;34
// Purple       0;35     Light Purple  1;35
// Cyan         0;36     Light Cyan    1;36
// Light Gray   0;37     White         1;37
