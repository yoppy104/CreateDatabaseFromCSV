#include "sqlite3.h"

#include <string>
#include <sys/stat.h>
#include <stdio.h>
#include <direct.h>
#include <fstream>
#include <iostream>

#include "utils.h"

// �C�����C�������́A�ŏ��̗v�f���쐬����f�[�^�x�[�X�̃t�@�C�����A����ȍ~��CSV�t�@�C���̃p�X
int main(int argc, char* argv[]) {
	sqlite3* db;
	char* zErrMsg;

	//�o�̓f�B���N�g�����Ȃ�������쐬����
	std::string output_dir_name = "Output_DB";
	struct stat statBuf;

	if (!stat(output_dir_name.c_str(), &statBuf) == 0) {
		_mkdir(output_dir_name.c_str());
	}

	//db�t�@�C����V�K�ɍ쐬����
	std::string db_file_name = std::string(argv[1]);
	if (db_file_name.find(".db") == std::string::npos) {
		db_file_name.append(".db");
	}

	std::string db_path = output_dir_name.append("\\").append(db_file_name);

	//�t�@�C�������ɑ��݂���ꍇ�ɂ́A�㏑���ۑ����s���Ă��悢�����m�F����
	std::ifstream ifs(db_path);
	if (ifs.is_open()) {
		std::string save_ok;
		std::cout << "�����̃t�@�C�������ɑ��݂��܂��B�㏑�����Ă���낵���ł��傤���H[Y/N]" << std::endl;
		std::cin >> save_ok;
		if (!CompareString(save_ok, "y")) {
			std::cout << "�������I�����܂�" << std::endl;
			return 0;
		}
		else {
			//�����̃t�@�C�����폜����
			if (remove(db_path.c_str())) {
				std::cout << "�����̃t�@�C�����폜���܂����B" << std::endl;
			}
			else {
				std::cout << "�����̃t�@�C���̍폜�Ɏ��s���܂����B�������I�����܂�" << std::endl;
				return 0;
			}
		}
	}

	//db�t�@�C�����쐬����
	int rc = sqlite3_open(db_path.c_str(), &db);

	//�I��
	sqlite3_close(db);
}