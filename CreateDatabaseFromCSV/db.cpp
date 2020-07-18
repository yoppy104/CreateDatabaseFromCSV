#include "db.h"

#include <sys/stat.h>
#include <stdio.h>
#include <direct.h>
#include <fstream>
#include <iostream>

#include "utils.h"

DB::DB(std::string file_name)
	: db(0)
{
	this->db = make_db_file(file_name);
}

DB::~DB() {
	sqlite3_close(this->db);
}

sqlite3* make_db_file(std::string file_name) {
	sqlite3* db;

	//出力ディレクトリがなかったら作成する
	std::string output_dir_name = "Output_DB";
	struct stat statBuf;
	if (!stat(output_dir_name.c_str(), &statBuf) == 0) {
		_mkdir(output_dir_name.c_str());
	}

	//dbファイルを新規に作成する
	// 拡張子が入力されていないなら挿入する
	if (file_name.find(".db") == std::string::npos) {
		file_name.append(".db");
	}

	std::string db_path = output_dir_name.append("\\").append(file_name);

	bool is_up_save = false;

	//ファイルが既に存在する場合には、上書き保存を行ってもよいかを確認する
	std::ifstream ifs(db_path);
	if (ifs.is_open()) {
		std::string save_ok;
		bool is_input_loop = true;

		// Y, Nが入力されるまで、入力処理をループし続ける
		while (is_input_loop) {
			is_input_loop = false;

			//上書き保存の有無を確認する。
			std::cout << "同名のファイルが既に存在します。上書きしてもよろしいでしょうか？[Y/N]" << std::endl;
			std::cin >> save_ok;
			if (CompareString(save_ok, "y")) {
				//既存のファイルを削除する
				if (remove(db_path.c_str())) {
					std::cout << "既存のファイルを削除しました。" << std::endl;
					is_up_save = true;
				}
				else {
					std::cout << "既存のファイルの削除に失敗しました。処理を終了します" << std::endl;
					return 0;
				}
			}
			//上書きをしない場合には、dbファイルの名称を間違えたことを考慮して、処理を終了する
			else if (CompareString(save_ok, "n")) {
				std::cout << "処理を終了します" << std::endl;
				return 0;
			}
			else {
				std::cout << "規定の入力ではありません。[Y/N]で入力してください。" << std::endl;
				is_input_loop = true;
			}
		}
	}

	//dbファイルを作成する
	int rc = sqlite3_open(db_path.c_str(), &db);

	if (is_up_save) {
		std::cout << "既存のデータベースファイルに上書きしました  {" << file_name << "}" << std::endl;
	}
	else {
		std::cout << "新規データベースファイルを作成しました  {" << file_name << "}" << std::endl;
	}

	return db;
}