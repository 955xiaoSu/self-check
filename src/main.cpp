#include <time.h>
#include "loadend.h" // �ջ񣺶��ú���ʹ��.h�ļ���.cpp�ļ�
#include "user.h"
using namespace std;

string current_user = "\0";
string s = "\0";
User* usermanage = new User(); // ����ָ��֮��һ��Ҫʵ����

// ���ܣ�������Ŀ������Ŀ��
// ������None
// ���أ�None
void README() {
	cout << "README: " << endl
		<< "  This Self-check program was launched by Sbk on September 1st, 2022." << endl
		<< "  The purpose of this program is to stimulate users to finish their" << endl
		<< "  task on time and they will become better certainly. " << endl << endl;
}

// ���ܣ��û���¼����ȡ�û���Ӧ�����б���¼�û���������
// ������None
// ���أ�None
void Comunicate() {
	while (1) {
		if (usermanage->UserConfirmed()) break;
		else continue;
	}
	usermanage->UserTaskDetail(usermanage->currentuser);
	return;
}

// ���ܣ���ʾ��ǰʱ�䣬��������Ӧ�����Ľ�����˳�����
// ������None
// ���أ�None
void End() {
	time_t result = time(NULL);
	char str[26];
	cout << "Current time: ";
	ctime_s(str, sizeof(str), &result); // ������ʱ��ת��Ϊ����������ת��Ϊ�ı���ʾ
	for (int index = 0; index < 26; index++) cout << str[index];
	cout << "Mutual encouragement: ";
	GiveSentence(str[9] - '1');
	return;
}

int main() {
	README();
	Comunicate();
	End();
	delete usermanage;
	return 0;
}