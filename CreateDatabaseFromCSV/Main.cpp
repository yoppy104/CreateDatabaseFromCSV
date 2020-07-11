#include "sqlite3.h"

#include <string>
#include <sys/stat.h>
#include <stdio.h>
#include <direct.h>
#include <fstream>
#include <iostream>

#include "utils.h"

// インライン引数は、最初の要素が作成するデータベースのファイル名、それ以降がCSVファイルのパス
int main(int argc, char* argv[]) {
	sqlite3* db;
	char* zErrMsg;

	//出力ディレクトリがなかったら作成する
	std::string output_dir_name = "Output_DB";
	struct stat statBuf;

	if (!stat(output_dir_name.c_str(), &statBuf) == 0) {
		_mkdir(output_dir_name.c_str());
	}

	//dbファイルを新規に作成する
	std::string db_file_name = std::string(argv[1]);
	if (db_file_name.find(".db") == std::string::npos) {
		db_file_name.append(".db");
	}

	std::string db_path = output_dir_name.append("\\").append(db_file_name);

	//ファイルが既に存在する場合には、上書き保存を行ってもよいかを確認する
	std::ifstream ifs(db_path);
	if (ifs.is_open()) {
		std::string save_ok;
		std::cout << "同名のファイルが既に存在します。上書きしてもよろしいでしょうか？[Y/N]" << std::endl;
		std::cin >> save_ok;
		if (!CompareString(save_ok, "y")) {
			std::cout << "処理を終了します" << std::endl;
			return 0;
		}
		else {
			//既存のファイルを削除する
			if (remove(db_path.c_str())) {
				std::cout << "既存のファイルを削除しました。" << std::endl;
			}
			else {
				std::cout << "既存のファイルの削除に失敗しました。処理を終了します" << std::endl;
				return 0;
			}
		}
	}

	//dbファイルを作成する
	int rc = sqlite3_open(db_path.c_str(), &db);

	//終了
	sqlite3_close(db);
}