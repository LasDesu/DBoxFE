DROP TABLE IF EXISTS "games";
CREATE TABLE "games" ("gid" VARCHAR(32) PRIMARY KEY  NOT NULL  UNIQUE , "title" VARCHAR(256), "year" INTEGER, "sw_house" VARCHAR(256), "link" VARCHAR(256), "dosbox" VARCHAR(32) NOT NULL  UNIQUE, "compatibility" VARCHAR(32) NOT NULL UNIQUE );
DROP TABLE IF EXISTS "gameversion";
CREATE TABLE "gameversion" ("gid" VARCHAR(32) NOT NULL , "vid" VARCHAR(32) NOT NULL );
DROP TABLE IF EXISTS "compatibility";
CREATE TABLE "compatibility" ("cid" VARCHAR(32) PRIMARY KEY  NOT NULL  UNIQUE , "start" INTEGER NOT NULL, "end" INTEGER NOT NULL, "description" VARCHAR(10) NOT NULL );
INSERT INTO "compatibility" VALUES('750fb86cc34c4eeaae0ce745fc89ffbf',0,0,'Broken');
INSERT INTO "compatibility" VALUES('4328ce54c18a437da4044683e9f8423d',1,28,'Runable');
INSERT INTO "compatibility" VALUES('087942383f764c419b458f7604c636bb',29,63,'Playable');
INSERT INTO "compatibility" VALUES('3d7c4da76667404ab76b7a98a05d154f',63,100,'Supported');
DROP TABLE IF EXISTS "version";
CREATE TABLE "version" ("vid" VARCHAR(32) PRIMARY KEY  NOT NULL  UNIQUE , "version" VARCHAR(10) NOT NULL );
INSERT INTO "version" VALUES('af462a8c43b94477a5ad84edf8ae9f3e','0.73');
INSERT INTO "version" VALUES('9670deb756c648aeb5332cee31aaf13d','0.72');
INSERT INTO "version" VALUES('7ec065e3b9554709ad00a37027cba452','0.71');
INSERT INTO "version" VALUES('429524cac74c402585d1f8817789a3d6','0.70');
INSERT INTO "version" VALUES('c02af32af2a8492889438d4fc57a5be2','0.65');
INSERT INTO "version" VALUES('f94b6ae591b24da8a81592184a321311','0.63');
INSERT INTO "version" VALUES('dec6d26d832543dfae02ed1ce3f29981','0.62');
INSERT INTO "version" VALUES('2082c9a2c88049d3a3c70483f7446e88','0.61');
INSERT INTO "version" VALUES('3ad6ccbbd45e4ecbb9eb5bc95748816e','0.60');
INSERT INTO "version" VALUES('8b8a4efa53844f6b87e80972d86da86a','0.58');
