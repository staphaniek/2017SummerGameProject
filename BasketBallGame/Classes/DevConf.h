#pragma once
#include "cocos2d.h"
#ifndef __DEVCONF_H__
#define __DEVCONF_H__

int _level = 1;
int _stage = 1;

// datas for ball
const int BALLTAG = 1;
const int BALLSIZE = 30;

// datas for holder
const int HOLDERTAG[2] = { 50,51 };
const int HOLDERINTAG[2] = { 52,53 };

// datas for ring
const int RINGTAG[4] = { 11, 12, 13, 14 };
const int RINGUPTAG[4] = { 15, 16, 17, 18 };
const int RINGDOWNTAG[4] = { 19, 20, 21, 22 };
const int RINGSIZE[4] = { 200, 180, 160, 140 };

// tags for obstacle

#endif // __DEVCONF_H__