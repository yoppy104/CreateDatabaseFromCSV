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

// �C�����C�������́A�ŏ��̗v�f���쐬����f�[�^�x�[�X�̃t�@�C�����A����ȍ~��CSV�t�@�C���̃p�X
int main(int argc, char* argv[]) {
	char* zErrMsg;

	// �����̐���db�̃t�@�C������CSV�t�@�C���̃p�X��1�ȏ�A�Œ���K�v
	if (argc < 2) {
		std::cout << "�C�����C�������̐�������܂���" << std::endl;
		return 0;
	}

	std::string db_file_name = "sample2"; // argv[1];
	DB db = DB(db_file_name);

	// �t�@�C�������X�g�ɓǂݍ��ޏ����̃e�X�g
	/*std::string file_name = "test_csv";
	read_file_test(file_name);*/



	std::cout << "done.." << std::endl;
}