#include "user.h"

// ���ܣ���ʼ����Ա����������user.txt�Լ�task.txt�ļ�
// ������None
// ���أ�None
User::User() {
	// ��Ա�����ĳ�ʼ��
	users.clear();
	userlist.clear();
	userstasklist.clear();
	userspermission.clear();
	currentuser = "\0";

	// �����û���Ϣ
	std::ifstream fin;
	std::string filepath = "./user.txt";
	fin.open(filepath, std::ios::in);
	if (!fin) { // �ж��û��ļ��Ƿ�������
		std::cerr << "Error: Fail to open user.txt file.";
		exit(1);
	}
	std::string username = "\0", password = "\0";
	int permission = 0;
	while (!fin.eof()) { // ���λ�ȡÿһ���ı��е��û������˺š��û�Ȩ��
		fin >> username; fin >> password; fin >> permission;
		users.insert(std::pair<std::string, std::string>(username, password));
		userspermission.insert(std::pair<std::string, int>(username, permission));
		userlist.push_back(username);
	}
	fin.close();

	// �����û������б�
	filepath = "./task.txt";
	fin.open(filepath, std::ios::in); // ���⻰�������д�ļ�һֱ��������
										  // Ҳ�п������ı��ļ���ʽ�𻵣�just more practice�����ܷ���
	if (!fin) { // �ж��û��ļ��Ƿ�������
		std::cerr << "Error: Fail to open task.txt file.";
		exit(1);
	}
	std::string line = "\0"; std::stringstream sstream; // ���ַ����������ո���ַ���
	std::string task = "\0";
	while (getline(fin, line)) {   // ���λ�ȡÿһ���ı��е��û���������
		sstream.str(line); // sstream�е�rdstate()Ϊstd::ios_base::eofbit
						   // ���¸���ʧ��
		sstream >> username;
		while (sstream >> task) {
			userstasklist[username].push_back(task);  // ע��ֱ��д�뵽���Ա����
		}
		sstream.clear();   // .clear()��ձ�־״̬��������״̬����goodbit
		sstream.str("");   // .str("")��ջ������������ڴ�ռ��
						   // �ջ�ԭ�������⻹��ȥ��stackoverflow
	}
	fin.close();
	return;
}

// ���ܣ��ж�����������Ƿ�Ϲ�
// ������command���������
// ���أ�����Ϲ淵��true
inline bool IsLegal(const std::string& command) {
	if (command == "Yes" || command == "No") return true;
	else return false;
}

// �������������
// ���ܣ�����û�
// ������username��ǰ�û���
// ���أ������ǰ�û�Ϊ����Ա���������û�������true
bool User::AddUser(const std::string& username) {
	if (userspermission[username] != 1) {
		std::cerr << "Error: Current doesn't have corresponding operation authority.";
		return false;
	}
	else {
		std::string name = "\0";  std::string password = "\0";
		std::cout << "Please enter new user account name : ";  std::cin >> name;
		std::cout << std::endl;
		std::cout << "Please enter new user account password : ";  std::cin >> password;
		std::cout << std::endl << "Congratulation! Create a new user!";
		return true;
	}
}

// ���ܣ�ȷ���Ƿ���ڸ��û����������û�����
// ������None
// ���أ�������ڸ��û���У������ͨ�����򷵻�true
bool User::UserConfirmed() {
	std::string username = "\0", password = "\0";
	bool flag = false;
	std::cout << "Please enter your username: "; getline(std::cin, username);
	for (std::vector<std::string>::iterator it = userlist.begin(); it != userlist.end(); it++) {
		if (*it == username) {
			flag = true;
			break;
		}
	}
	if (!flag) {
		std::cout << "Error: User \"" << username << "\" doesn't exist." << std::endl;
		return false;
	}
	std::cout << "Please enter your password: "; getline(std::cin, password);
	std::map<std::string, std::string> usermap = GetUsers();
	if (usermap[username] == password) {
		currentuser = username;
		return true;
	}
	else {
		std::cout << "Error: Wrong password. " << std::endl;
		return false;
	}
}

/* ���º����Ƕ��û�������й��� */

// ���ܣ�ѡ������Ҫ��ɵ�����չʾ
// ������numbertask��������ƥ���map
// ���أ�None
void RespondChoose(const std::map<int, std::string>& numbertask) {
	std::vector<std::string> taskchoosed; taskchoosed.clear();
	std::cout << std::endl << "Please enter the serial number of task you wanna finish."
		<< "(Enter 0 to indicate the end of input.)" << std::endl
		<< "$ ";
	int serial = 0;
	while (std::cin >> serial && serial) {
		taskchoosed.push_back(numbertask.at(serial));
		std::cout << "$ ";
	}
	std::cout << std::endl << "Today your task are listed below:" << std::endl;
	serial = 1;
	for (std::vector<std::string>::iterator it = taskchoosed.begin(); it != taskchoosed.end(); it++) {
		std::cout << serial << "." << *it << std::endl;
		serial++;
	}
	return;
}


// ���ܣ�������񵽱����ļ�
// ������fin�ļ�ָ�룬content����������
// ���أ�None
void AddTaskToTXT(const std::string& content, const std::string& username) {
	std::ofstream filewrite;
	filewrite.open("./task.txt", std::ios::app); // ֻ�ܲ���׷�ӵķ�ʽ����д�ļ�
	filewrite << "\n";		// ʹ����ʶ����
	filewrite << username;
	filewrite << " ";		// �����û���������֮���пո�ĸ�ʽҪ��
	filewrite << content;
	return;
}

// ���ܣ�ɾ�������ļ��еĶ�Ӧ���񣨰�ɾ���е������Թ�������д���ļ���
// ������content��ɾ�����������ݣ�username�û���
// ���أ�None
void DeleteTaskInTXT(const std::string& content, const std::string& username) {
	std::ifstream fileread;
	fileread.open("./task.txt", std::ios::in);
	std::string s = "\0";
	std::string target = username + " " + content;
	std::string finalresult = "\0";
	while (getline(fileread, s)) {
		if (s == target) continue; // ���ļ�ʱ������ɾ��������
		else {
			finalresult += s;
			finalresult += "\n";
		}
	}
	fileread.close();
	std::ofstream filewrite;
	filewrite.open("./task.txt", std::ios::out);
	filewrite << finalresult; // ����д���ļ�
	filewrite.close();
	return;
}


// ���ܣ�����û�����(ΪRespondEdit������Ӻ���)
// ������mylistԭ�����б��ᱻ�޸ģ���username�û���
// ���أ�None
void AddTask(std::vector<std::string>& mylist, const std::string& username) {
	std::string addtask = "\0", command = "\0";
	while (1) { // ����ʵ�ֶ���������Ĺ���
		std::cout << std::endl << "Please enter new task into your original task list.";
		std::cout << std::endl << "$ ";
		getline(std::cin, addtask);  mylist.push_back(addtask);
		AddTaskToTXT(addtask, username);
		std::cout << std::endl << "Add new task successfully!" << std::endl
			<< "Do you want to continue adding new task?(Yes/No): ";
		while (getline(std::cin, command)) { // ���˵���Yes��No֮��Ĵ�
			if (IsLegal(command)) break;
			else {
				std::cout << std::endl << "Error: Command is wrong. Please enter Yes or No." << std::endl
					<< "$ ";
			}
		}
		if (command == "Yes") continue; // ��������������
		else break; // ��������������
	}
	return;
}

// ���ܣ�ɾ���û�����(ΪRespondEdit������Ӻ���)
// ������numbertask��������ƥ���map�� mylistԭ�����б��ᱻ�޸ģ���username�û���
// ���أ�None
void DeleteTask(const std::map<int, std::string>& numbertask, std::vector<std::string>& mylist, const std::string& username) {
	int serial = 0;  std::string command = "\0";
	while (1) {
		std::cout << std::endl << "Please enter the serial of task you want to delete."
			<< std::endl << "$ ";
		std::cin >> serial; std::cin.ignore();
		DeleteTaskInTXT(numbertask.at(serial), username);
		// �ҵ���Ӧ��ŵ����񣬲���myList��ɾ��������
		for (std::vector<std::string>::iterator it = mylist.begin(); it != mylist.end(); it++) {
			if (*it == numbertask.at(serial)) { // const STL��[]����������const��Ա������
												// ������STL�µ���Ŀ���ı�STL
				mylist.erase(it);
				break;
			}
		}
		std::cout << std::endl << "Delete task successfully!" << std::endl
			<< "Do you want to continue deleting task?(Yes/No): ";
		while (getline(std::cin, command)) { // ���˵���Yes/No֮��Ĵ�
			if (IsLegal(command)) break;
			else {
				std::cout << std::endl << "Error: Command is wrong. Please enter Yes or No." << std::endl
					<< "$ ";
			}
		}
		if (command == "Yes") continue; // ����ɾ������
		else break; // ����ɾ������
	}
	return;
}


// ���ܣ�ѯ���û��Ƿ�����޸�����
// ������None
// ���أ��˳��޸����񷵻�true
bool WhetherContinue() {
	std::string command = "\0";
	std::cout << "Do you want to quit editing task?(Yes/No): ";
	while (1) { // ���˵���Yes / No������
		getline(std::cin, command);
		if (IsLegal(command)) break;
		else {
			std::cout << std::endl << "Error: Command is wrong. Please enter Yes or No." << std::endl
				<< "$ ";
		}
	}
	if (command == "Yes") return true;
	else return false;
}

// ���ܣ��޸�ԭ�����б�ִ�����ӻ�ɾ������Ĳ��������չʾ����������б�
// ������numbertask��������ƥ���map���ᱻ�޸ģ���mylistԭ�����б��ᱻ�޸ģ���username�û���
// ���أ�None
void RespondEdit(std::map<int, std::string>& numbertask, std::vector<std::string>& mylist, const std::string& username) {
	std::string command = "\0"; int serial = 0;
	while (1) {
		std::cout << std::endl << "Now enter one of these commands to continue. " << std::endl
			<< "1.add task" << std::endl
			<< "2.delete task" << std::endl
			<< "$ ";
		getline(std::cin, command);
		// ������ɾ�����������������ܷ��������Զ�Ӧ����ʵ��
		if (command == "add task") {
			AddTask(mylist, username);
			if (WhetherContinue()) break;
			else continue;
		} else if (command == "delete task") {
			  DeleteTask(numbertask, mylist, username);
			  if (WhetherContinue()) break;
			  else continue;
		} else {
			  std::cout << std::endl << "Error: Command is wrong. Please enter again.";
		}
	}
	// ���ӻ�ɾ�����񶼸ı���ԭ�����б�������±��
	numbertask.clear();  serial = 1;
	for (std::vector<std::string>::iterator it = mylist.begin(); it != mylist.end(); it++) {
		numbertask.insert(std::pair<int, std::string>(serial, *it));  serial++;
	}
	std::cout << std::endl << "After editing, your task list is: " << std::endl;
	serial = 1;
	for (std::vector<std::string>::iterator it = mylist.begin(); it != mylist.end(); it++) {
		std::cout << serial << "." << *it << std::endl; serial++;
	}
	RespondChoose(numbertask);
	return;
}


// ���ܣ����������б�ѡ���������񲢱�ǣ�ִ�����ӡ��޸Ļ�ɾ������Ĳ���
// ������username�û���
// ���أ�None
void User::UserTaskDetail(const std::string& username) {
	std::map<std::string, std::vector<std::string>> mytask = GetUsersTaskList();
	std::vector<std::string> mylist = mytask[username];
	std::cout << std::endl << "Dear user: " << username << std::endl
		<< "Your indentity has been confirmed. " << std::endl
		<< "Your original task are listed below: " << std::endl;
	std::map<int, std::string> numbertask; // ���������Ŷ�Ӧ
	numbertask.clear();
	int serial = 1;
	for (std::vector<std::string>::iterator it = mylist.begin(); it != mylist.end(); it++) {
		std::cout << serial << "." << *it << std::endl;
		numbertask.insert(std::pair<int, std::string>(serial, *it));
		serial++;
	}
	std::cout << std::endl << "Now enter one of these commands to continue: " << std::endl
		<< "1.choose today's task" << std::endl
		<< "2.edit task list" << std::endl
		<< "$ ";
	std::string command = "\0";
	while (1) { // ��choose��edit��������Ч�����������Զ�Ӧ����ʵ��
		getline(std::cin, command); // ע�⻺������֮ǰ���������Ƿ����
		if (command == "choose today's task") {
			RespondChoose(numbertask);
			break;
		}
		else if (command == "edit task list") {
			RespondEdit(numbertask, mylist, username);
			break;
		}
		else {
			std::cout << std::endl << "Error: Command is wrong. Please enter again." << std::endl
				<< "$ ";
		}
	}
	std::cout << std::endl << "Ending. Good luck!" << std::endl;
	return;
}

/* ���º��������ṩ��˽�����ݳ�Ա�ĵ��ýӿ�*/

// ���ܣ��ṩ˽�г�Ա����users���ýӿ�
// ������None
// ���أ�None
const std::map<std::string, std::string> User::GetUsers() {
	return this->users;
}

// ���ܣ��ṩ˽�г�Ա����usersPermission���ýӿ�
// ������None
// ���أ�None
const std::map<std::string, int> User::GetUsersPermission() {
	return this->userspermission;
}

// ���ܣ��ṩ˽�г�Ա����usersTaskList���ýӿ�
// ������None
// ���أ�None
std::map<std::string, std::vector<std::string>> User::GetUsersTaskList() {
	return this->userstasklist;
}
