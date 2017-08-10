// database manager
#define DB_INIT false

#ifndef _DEVCONF_H__
#define _DEVCONF_H__

static int _level = 1;
static int _stage = 1;
static int _score = 0;

// datas for ball
const int BALLTAG = 1;
const int BALLSIZE = 35;

// datas for holder
const int HOLDERTAG[2] = { 50,51 };
const int HOLDERINTAG[2] = { 52,53 };

// datas for ring
const int RINGTAG[4] = { 11, 12, 13, 14 };
const int RINGUPTAG[4] = { 15, 16, 17, 18 };
const int RINGDOWNTAG[4] = { 19, 20, 21, 22 };
const int RINGSIZE[4] = { 140, 120, 100,80 };

static int obstacletag[10], obstaclepos = 0;
static int obstacleindex = 201;
const float OBSTACLESIZE = 80, OBSTACLEHANDFOOTSIZE = 40;

// 무지개색
//const cocos2d::Color3B rainbow[7] = { cocos2d::Color3B(255, 0 , 0), cocos2d::Color3B(255, 127, 0) , cocos2d::Color3B(255, 255, 0) , cocos2d::Color3B(0, 255, 0) , cocos2d::Color3B(0, 0, 255) , cocos2d::Color3B(75, 0, 130) , cocos2d::Color3B(148, 0, 211) };

// tags for obstacle

#endif // __DEVCONF_H__