#include "loadend.h"

// ���ܣ�����end.txt�ļ��������ش���������Ӧ�����
// ������day����
// ���أ�string
std::string LoadEndTxt(const int& day) {
	std::string filepath = "./end.txt";
	std::ifstream fin;
	fin.open(filepath, std::ios::in);
	if (!fin) { // ���Ƿ�ɹ����ļ������ж�
		std::cerr << "Error: Fail to open end.txt file.";
		exit(1);
	}
	std::string s = "\0";  int line = 1;
	while (!fin.eof() && line < day) { // ����ǰ�棨day - 1�����ַ���
		std::getline(fin, s);	line++;
	}
	getline(fin, s);
	fin.close();
	return s;
}

// ���ܣ���ӡ��Ӧ���������
// ������day����
// ���أ�None
void GiveSentence(const int& day) {
	std::string ans = LoadEndTxt(day);
	std::cout << ans << std::endl;
	return;
}
