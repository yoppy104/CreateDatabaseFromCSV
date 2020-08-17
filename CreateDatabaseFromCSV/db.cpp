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

void DB::createTable(std::string file_name, bool is_sample) {
	// ファイルを1行ずつリストに入れる
	std::vector<std::string> lines = read_file(file_name);

	int num_lines = lines.size();
	int volume_data = num_lines - 4;

	if (volume_data < 0) {
		std::cout << "当該ファイルの中に必要な情報が記載されていません : " << file_name << std::endl;
		return;
	}

	/*
	memo : 最初の4行はテーブル作成コマンドに使用する。
				1行目：テーブルの名前
				2行目：各カラムの要素名
				3行目：各カラムの型
				4行目：制約条件などの追加情報
				  以降：各データ
	*/

	std::string table_name = Split(&lines[0], ",")[0];							// テーブルの名前
	std::vector<std::string> column_name = Split(&lines[1], ",");		// カラムの名称
	std::vector<std::string> column_type = Split(&lines[2], ",");			// カラムの型
	std::vector<std::string> column_addinfo = Split(&lines[3], ",");	// カラムの制約条件等の追加情報


	//データベース上にテーブルを作成する
	bool is_ok = this->makeEmptyTable(
		table_name,
		column_name,
		column_type,
		column_addinfo
	);
	if (!is_ok) {
		return;
	}

	// 各データの挿入作業を行う
	std::vector<std::string> datas;

	for (int i = 4; i < num_lines; i++) {
		datas = Split(&lines[i], ",");

		this->insertData(table_name, datas, column_name.size());

		datas.clear();
	}

	// サンプル表示
	this->showSample(table_name);
}

void DB::showSample(std::string table_name) {
	char* errorMessage;
	std::string command = "SELECT * FROM " + table_name + ";";
	sqlite3_exec(this->db, command.c_str(), nullptr, nullptr, &errorMessage);
}

bool DB::insertData(std::string table_name, std::vector<std::string> datas, int num_data) {
	int data_count = datas.size();
	if (data_count < num_data) {
		std::cout << "データの個数が少ないです" << std::endl;
		return false;
	}

	std::string command = "INSERT INTO " + table_name + " VALUES (";
	std::string comma = "";
	for (int i = 0; i < data_count; i++) {
		command += comma + datas[i];
		if (comma.empty()) {
			comma = ", ";
		}
	}
	command += ");";

	//コマンドを実行する
	char* errorMessage;
	auto status = sqlite3_exec(this->db, command.c_str(), nullptr, nullptr, &errorMessage);
	if (status != SQLITE_OK) {
		std::cout << "データの挿入に失敗しました : " << errorMessage << std::endl;
		sqlite3_free(errorMessage);
		return false;
	}

	return true;
}


bool DB::makeEmptyTable(std::string table_name, std::vector<std::string> name, std::vector<std::string> type, std::vector<std::string> additional) {
	int num_data = name.size();

	// 全ての配列の長さが等しくないなら処理を終了する
	if (!(num_data == type.size() && num_data == additional.size())) {
		std::cout << "テーブル作成用のデータの数が合いません" << std::endl;
		return false;
	}

	std::string data_str = "";

	for (int i = 0; i < num_data; i++) {
		if (i != 0){
			data_str += ",";
		}
		data_str += name[i] + " " + type[i] + " " + additional[i];
	}

	std::string create_command = "create table if not exists " + table_name + " (" + data_str + ")";

	//テーブルを作成する処理を実行する
	char* errorMessage;
	auto status = sqlite3_exec(this->db, create_command.c_str(), nullptr, nullptr, &errorMessage);
	if (status != SQLITE_OK) {
		std::cout << "テーブルの作成に失敗しました : " << errorMessage << std::endl;
		sqlite3_free(errorMessage);
		return false;
	}

	return true;
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

		ifs.close();

		// Y, Nが入力されるまで、入力処理をループし続ける
		while (is_input_loop) {
			is_input_loop = false;

			//上書き保存の有無を確認する。
			std::cout << "同名のファイルが既に存在します。上書きしてもよろしいでしょうか？[Y/N]" << std::endl;
			std::cin >> save_ok;
			if (CompareString(save_ok, "y")) {
				//既存のファイルを削除する
				int check = remove(db_path.c_str());
				if (check == 0) {
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