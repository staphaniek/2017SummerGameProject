#ifndef __DATABASEMANAGER_H__
#define __DATABASEMANAGER_H__

#include "sqlite3.h"
#include <string>
#include "cocos2d.h"

// Same as USING_NS_CC;
using namespace cocos2d;

// std의 namespace 사용
using namespace std;

struct Score
{
public:
	int score;
	char* _name;
};

class DatabaseManager
{
private:
	bool openDB();
	void closeDB();
	sqlite3 *_sqlite;
public:
	DatabaseManager();
	~DatabaseManager();

	// 에러메시지를 담을 변수
	char *_errorMSG;
	// 결과의 상태를 담을 변수
	int _result;

	static DatabaseManager *getInstance();
	void createDB();
	int getLowestRankingScore();
	bool insertDB(const string name, const int score);
	list<Score*> selectDB();
	bool deleteDB();

//	int insertCharacterDB(*characterInfo);
//	void deleteCharacterDB(int no);
};

#endif // __DATABASEMANAGER_H__