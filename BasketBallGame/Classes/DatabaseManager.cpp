#include "DatabaseManager.h"
#include <string>

#define DB_FILE_NAME "db.sqlite"

static DatabaseManager *_sharedSqlite = NULL;

DatabaseManager::DatabaseManager()
{
}


DatabaseManager::~DatabaseManager()
{
	// _sharedSqlite가 있으면
	if (_sharedSqlite != NULL)
	{
		_sharedSqlite->closeDB();
		_sharedSqlite = NULL;
	}
}

// DatabaseManager 객체를 반환한다.
DatabaseManager* DatabaseManager::getInstance()
{
	// _sharedSqlite가 없으면
	if (!_sharedSqlite)
	{
		_sharedSqlite = new DatabaseManager;
		_sharedSqlite->openDB();
	}

	return _sharedSqlite;
}

// Database를 오픈
bool DatabaseManager::openDB()
{
	// 데이터베이스의 path를 가져온다
	std::string path = FileUtils::getInstance()->getWritablePath() + DB_FILE_NAME;

	// 데이터베이스의 path를 출력
	 log("path : %s", path.c_str());

	// 데이터베이스를 open
	_result = sqlite3_open(path.c_str(), &_sqlite);

	if (_result != SQLITE_OK)
	{
		log("failed to create db");
		return false;
	}

	return true;
}

void DatabaseManager::closeDB()
{
	sqlite3_close(_sqlite);
}

void DatabaseManager::createDB()
{
	if (true) // DB 초기화를 위한 개발자 변수 값
	{
		std::string path = FileUtils::getInstance()->getWritablePath() + DB_FILE_NAME;
		// 데이터베이스의 파일이 열려있으면 안되므로 DB를 닫아줌
		closeDB();

		// DB 파일을 삭제
		remove(path.c_str());

		// DB를 닫았으므로 다시 열어줌
		openDB();
	}

	std::string query;
	query = "create table if not exists TB_SCORE(";
	query += "NO integer primary key autoincrement, ";
	query += "NAME varChar(50),";
	query += "SCORE integer)";

	_result = sqlite3_exec(_sqlite, query.c_str(), NULL, NULL, &_errorMSG);

	if (_result == SQLITE_OK)
	{
		log("createDB() SUCCESS");
	}
	else log("ERROR CODE : %d, ERROR MSG : %s", _result, _errorMSG);
}

int DatabaseManager::getLowestRankingScore()
{
	if (checkCount() < 10)
		return 0;
	string query;

	query = "select SCORE from TB_SCORE order by SCORE desc limit 10";

	sqlite3_stmt *stmt = NULL;
	//stmt에 결과를 담는다.
	_result = sqlite3_prepare_v2(_sqlite, query.c_str(), query.length(), &stmt, NULL);

	if (_result == SQLITE_OK)
	{
		int ret = 0;
		log("selectDB() SUCCESS");
		while (sqlite3_step(stmt) == SQLITE_ROW)
		{
			ret = sqlite3_column_int(stmt, 0);
		}
		return ret;
	}
	else
		log("ERROR CODE : %d", _result);

	return 0;
}

bool DatabaseManager::insertDB(const string name, const int score)
{
	// 개수 체크
	sqlite3_stmt *pStmt = NULL;
	string query = "insert into TB_SCORE values (null, '"+ name;
	char tmp[100];
	sprintf(tmp, "', %d)", score);
	query += tmp;

	_result = sqlite3_exec(_sqlite, query.c_str(), NULL, NULL, &_errorMSG);

	if (_result == SQLITE_OK)
	{
		log("insertDB() SUCCESS");
		return true;
	}
	else
	{
		log("ERROR CODE : %d, ERROR MSG : %s", _result, _errorMSG);
		return false;
	}
}

list<Score*> DatabaseManager::selectDB()
{
	string query = "select * from TB_SCORE order by SCORE desc limit 10;";

	sqlite3_stmt *stmt = NULL;
	//stmt에 결과를 담는다.
	_result = sqlite3_prepare_v2(_sqlite, query.c_str(), query.length(), &stmt, NULL);

	list<Score *> scoreList;

	if (_result == SQLITE_OK)
	{
		log("selectDB() SUCCESS");
		while (sqlite3_step(stmt) == SQLITE_ROW)
		{
			Score *pScore = new Score;
			// sqlite3_column_xxx는 첫 번째 매개변수로 sqlite3_stmt를 받고 두 번째 매개변수의 column 번호 값을 가져온다.
			pScore->_name = strdup((char *)sqlite3_column_text(stmt, 1));
			pScore->score = sqlite3_column_int(stmt, 2);

			scoreList.push_back(pScore);
		}
	}
	else
		log("ERROR CODE : %d", _result);

	// sqlite3_stmt를 해제한다.
	sqlite3_finalize(stmt);

	return scoreList;
}

bool DatabaseManager::deleteDB()
{
	string query = "delete from TB_SCORE ";

	char temp[20];
	sprintf(temp, "where SCORE < %d", getLowestRankingScore());

	query += temp;

	_result = sqlite3_exec(_sqlite, query.c_str(), NULL, NULL, &_errorMSG);

	if (_result == SQLITE_OK)
	{
		log("deleteDB() SUCCESS");
		return true;
	}
	else
	{
		log("ERROR CODE : %d, ERROR MSG : %s", _result, _errorMSG);
		return false;
	}
}

int DatabaseManager::checkCount()
{
	int cnt = 0;
	{
		sqlite3_stmt *pStmt = NULL;
		string query = "select count(*) from TB_SCORE";
		_result = sqlite3_prepare_v2(_sqlite, query.c_str(), query.length(), &pStmt, NULL);

		if (_result == SQLITE_OK)
		{
			log("selectDB() SUCCESS");
			if (sqlite3_step(pStmt) == SQLITE_ROW)
			{
				cnt = sqlite3_column_int(pStmt, 0);
			}
		}
		sqlite3_finalize(pStmt);
	}

	return cnt;
}