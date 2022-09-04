#pragma once
#ifndef USER_H_
#define USER_H_
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <fstream>
#include <vector>

class User {
private:
	std::map<std::string, std::string> users;   // �û����˺�������
	std::map<std::string, int> userspermission; // �û���Ȩ�ޱ�ʶ��1Ϊ����Ա��2Ϊ��ͨ�û�
	std::map<std::string, std::vector<std::string>> userstasklist;  // �û��������б�

public:
	User();
	std::string currentuser; // ��ǰ�û���
	std::vector<std::string> userlist; // ��¼�����û���
	std::map<std::string, std::vector<std::string>> GetUsersTaskList();
	const std::map<std::string, std::string> GetUsers();
	const std::map<std::string, int> GetUsersPermission();
	void UserTaskDetail(const std::string& username);
	bool UserConfirmed();
	bool AddUser(const std::string& username);
};

#endif
