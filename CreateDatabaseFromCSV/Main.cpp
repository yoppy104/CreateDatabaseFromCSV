#include "sqlite3.h"

#include <string>
#include <sys/stat.h>
#include <stdio.h>
#include <direct.h>
#include <fstream>
#include <iostream>

#include "utils.h"
#include "db.h"
#include "test.h"

// インライン引数は、最初の要素が作成するデータベースのファイル名、それ以降がCSVファイルのパス
int main(int argc, char* argv[]) {
	// 引数の数がdbのファイル名とCSVファイルのパスが1つ以上、最低限必要
	if (argc < 2) {
		std::cout << "インライン引数の数が足りません" << std::endl;
		return 0;
	}

	std::string db_file_name = argv[1];
	DB db = DB(db_file_name);

	if (!db.checkCorrect()) return 0;

	for (int i = 2; i < argc; i++) {
		// ファイルをリストに読み込む処理のテスト
		std::string file_name = argv[i];
		db.createTable(file_name, true);
	}

	std::cout << "done.." << std::endl;
}