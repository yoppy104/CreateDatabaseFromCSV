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
	char* zErrMsg;

	// 引数の数がdbのファイル名とCSVファイルのパスが1つ以上、最低限必要
	if (argc < 2) {
		std::cout << "インライン引数の数が足りません" << std::endl;
		return 0;
	}

	std::string db_file_name = "sample2"; // argv[1];
	DB db = DB(db_file_name);

	// ファイルをリストに読み込む処理のテスト
	/*std::string file_name = "test_csv";
	read_file_test(file_name);*/



	std::cout << "done.." << std::endl;
}