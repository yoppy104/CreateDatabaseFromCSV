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
	// �����̐���db�̃t�@�C������CSV�t�@�C���̃p�X��1�ȏ�A�Œ���K�v
	if (argc < 2) {
		std::cout << "�C�����C�������̐�������܂���" << std::endl;
		return 0;
	}

	std::string db_file_name = argv[1];
	DB db = DB(db_file_name);

	if (!db.checkCorrect()) return 0;

	for (int i = 2; i < argc; i++) {
		// �t�@�C�������X�g�ɓǂݍ��ޏ����̃e�X�g
		std::string file_name = argv[i];
		db.createTable(file_name, true);
	}

	std::cout << "done.." << std::endl;
}