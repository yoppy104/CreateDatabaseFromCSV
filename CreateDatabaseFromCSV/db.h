#pragma once

#include "sqlite3.h"

#include <string>
#include <vector>

//データベース管理をラッピングするクラス
class DB {
private:
	sqlite3* db;

	bool makeEmptyTable(std::string table_name, std::vector<std::string> name, std::vector<std::string> type, std::vector<std::string> additional);
	bool insertData(std::string table_name, std::vector<std::string> datas, int num_data);
public:
	DB(std::string file_name);
	~DB();

	void createTable(std::string file_name, bool is_sample=false);
	void showSample(std::string table_name);

	bool checkCorrect() { return db != 0; }
};

//ファイル名を受け取って、データベース用のファイルを作成、または指定する
sqlite3* make_db_file(std::string file_name);