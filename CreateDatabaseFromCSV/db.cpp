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

void DB::createTable(std::string file_name) {
	// �t�@�C����1�s�����X�g�ɓ����
	std::vector<std::string> lines = read_file(file_name);

	int num_lines = lines.size();
	int volume_data = num_lines - 4;

	if (volume_data < 0) {
		std::cout << "���Y�t�@�C���̒��ɕK�v�ȏ�񂪋L�ڂ���Ă��܂��� : " << file_name << std::endl;
		return;
	}

	/*
	memo : �ŏ���4�s�̓e�[�u���쐬�R�}���h�Ɏg�p����B
				1�s�ځF�e�[�u���̖��O
				2�s�ځF�e�J�����̗v�f��
				3�s�ځF�e�J�����̌^
				4�s�ځF��������Ȃǂ̒ǉ����
				  �ȍ~�F�e�f�[�^
	*/

	std::string table_name = lines[0];												// �e�[�u���̖��O
	std::vector<std::string> column_name = Split(&lines[1], ",");		// �J�����̖���
	std::vector<std::string> column_type = Split(&lines[2], ",");			// �J�����̌^
	std::vector<std::string> column_addinfo = Split(&lines[3], ",");	// �J�����̐���������̒ǉ����


	//�f�[�^�x�[�X��Ƀe�[�u�����쐬����
	///todo///

	// �e�f�[�^�̑}����Ƃ��s��
	std::vector<std::string> data;
	for (int i = 4; i < num_lines; i++) {
		data = Split(&lines[i], ",");

		data.clear();
	}
}


sqlite3* make_db_file(std::string file_name) {
	sqlite3* db;

	//�o�̓f�B���N�g�����Ȃ�������쐬����
	std::string output_dir_name = "Output_DB";
	struct stat statBuf;
	if (!stat(output_dir_name.c_str(), &statBuf) == 0) {
		_mkdir(output_dir_name.c_str());
	}

	//db�t�@�C����V�K�ɍ쐬����
	// �g���q�����͂���Ă��Ȃ��Ȃ�}������
	if (file_name.find(".db") == std::string::npos) {
		file_name.append(".db");
	}

	std::string db_path = output_dir_name.append("\\").append(file_name);

	bool is_up_save = false;

	//�t�@�C�������ɑ��݂���ꍇ�ɂ́A�㏑���ۑ����s���Ă��悢�����m�F����
	std::ifstream ifs(db_path);
	if (ifs.is_open()) {
		std::string save_ok;
		bool is_input_loop = true;

		// Y, N�����͂����܂ŁA���͏��������[�v��������
		while (is_input_loop) {
			is_input_loop = false;

			//�㏑���ۑ��̗L�����m�F����B
			std::cout << "�����̃t�@�C�������ɑ��݂��܂��B�㏑�����Ă���낵���ł��傤���H[Y/N]" << std::endl;
			std::cin >> save_ok;
			if (CompareString(save_ok, "y")) {
				//�����̃t�@�C�����폜����
				if (remove(db_path.c_str())) {
					std::cout << "�����̃t�@�C�����폜���܂����B" << std::endl;
					is_up_save = true;
				}
				else {
					std::cout << "�����̃t�@�C���̍폜�Ɏ��s���܂����B�������I�����܂�" << std::endl;
					return 0;
				}
			}
			//�㏑�������Ȃ��ꍇ�ɂ́Adb�t�@�C���̖��̂��ԈႦ�����Ƃ��l�����āA�������I������
			else if (CompareString(save_ok, "n")) {
				std::cout << "�������I�����܂�" << std::endl;
				return 0;
			}
			else {
				std::cout << "�K��̓��͂ł͂���܂���B[Y/N]�œ��͂��Ă��������B" << std::endl;
				is_input_loop = true;
			}
		}
	}

	//db�t�@�C�����쐬����
	int rc = sqlite3_open(db_path.c_str(), &db);

	if (is_up_save) {
		std::cout << "�����̃f�[�^�x�[�X�t�@�C���ɏ㏑�����܂���  {" << file_name << "}" << std::endl;
	}
	else {
		std::cout << "�V�K�f�[�^�x�[�X�t�@�C�����쐬���܂���  {" << file_name << "}" << std::endl;
	}

	return db;
}