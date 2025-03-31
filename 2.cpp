#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

// ѧ��������Ϣ�ṹ��
struct Student {
    string id;
    string name;
    string gender;
    int age;
    string dormitory;
    string phone;
    vector<string> selectedCourses;
};

// �γ̻�����Ϣ�ṹ��
struct Course {
    string courseId;
    string courseName;
    string classTime;
    vector<pair<string, double>> scores; // ѧ��ѧ�źͳɼ�
    vector<pair<string, pair<string, double>>> retakeScores; // ѧ��ѧ�ţ�����ѧ�ںͳɼ�
    double credit;
    bool isRetakeAvailable;
};

// ����Ա�ṹ��
struct Admin {
    string username;
    string password;
};

// ��ʦ�ṹ��
struct Teacher {
    string id;
    string name;
    string password;
};

// ȫ�ֱ���
vector<Student> students;
vector<Course> courses;
vector<Admin> admins;
vector<Teacher> teachers;
const string restoreFile = "restore.txt";
const string adminFile = "admins.txt";
const string teacherFile = "teachers.txt";

// ��������
void adminInput();
void studentSelectCourse();
void studentViewSchedule();
void teacherInputScore();
void studentQueryScore();
void statisticsByClass();
void statisticsByCourse();
void studentCreditAndFailedCourses();
void diyFunction();
void saveToFile();
void loadFromFile();
bool adminLogin();
bool teacherLogin();
bool studentLogin();
void saveAdminsToFile();
void loadAdminsFromFile();
void saveTeachersToFile();
void loadTeachersFromFile();
void adminRegister();
void teacherRegister();
void studentRegister();
bool isPasswordValid(const string& password);
bool isStudentIdExists(const string& id);
bool isAdminUsernameExists(const string& username);
bool isTeacherIdExists(const string& id);
void deleteAdminAccount();
void deleteTeacherAccount();
void deleteStudentAccount();

// ����Ա¼����Ϣ
void adminInput() {
    int choice;
    while (true) {
        cout << "1. ¼��ѧ����Ϣ\n2. ¼��γ���Ϣ\n3. �������˵�\n���������ѡ��: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            Student s;
            cout << "������ѧ��: ";
            getline(cin, s.id);
            while (isStudentIdExists(s.id)) {
                cout << "��ѧ���Ѵ��ڣ�����������: ";
                getline(cin, s.id);
            }
            cout << "����������: ";
            getline(cin, s.name);
            cout << "�������Ա�: ";
            getline(cin, s.gender);
            cout << "����������: ";
            cin >> s.age;
            cin.ignore();
            cout << "�������������: ";
            getline(cin, s.dormitory);
            cout << "������绰����: ";
            getline(cin, s.phone);
            students.push_back(s);
        } else if (choice == 2) {
            Course c;
            cout << "������γ̱��: ";
            getline(cin, c.courseId);
            cout << "������γ�����: ";
            getline(cin, c.courseName);
            cout << "�������Ͽ�ʱ��: ";
            getline(cin, c.classTime);
            cout << "������ѧ��: ";
            cin >> c.credit;
            cin.ignore();
            cout << "�Ƿ��������� (1: ��, 0: ��): ";
            cin >> c.isRetakeAvailable;
            cin.ignore();
            courses.push_back(c);
        } else if (choice == 3) {
            break;
        }
    }
    saveToFile();
}

// ѧ��ѡ��
void studentSelectCourse() {
    string studentId;
    cout << "���������ѧ��: ";
    getline(cin, studentId);
    auto it = find_if(students.begin(), students.end(), [&](const Student& s) { return s.id == studentId; });
    if (it == students.end()) {
        cout << "δ�ҵ���ѧ����Ϣ��" << endl;
        return;
    }

    cout << "��ѡ��Ŀγ��б�:" << endl;
    for (const auto& c : courses) {
        cout << "�γ̱��: " << c.courseId << ", �γ�����: " << c.courseName << endl;
    }

    string courseId;
    cout << "������Ҫѡ��Ŀγ̱�� (���� 'q' �˳�): ";
    while (getline(cin, courseId) && courseId != "q") {
        auto courseIt = find_if(courses.begin(), courses.end(), [&](const Course& c) { return c.courseId == courseId; });
        if (courseIt != courses.end()) {
            it->selectedCourses.push_back(courseId);
            cout << "ѡ�γɹ���" << endl;
        } else {
            cout << "δ�ҵ��ÿγ���Ϣ��" << endl;
        }
        cout << "������Ҫѡ��Ŀγ̱�� (���� 'q' �˳�): ";
    }
    saveToFile();
}

// ѧ���鿴�α�
void studentViewSchedule() {
    string studentId;
    cout << "���������ѧ��: ";
    getline(cin, studentId);
    auto it = find_if(students.begin(), students.end(), [&](const Student& s) { return s.id == studentId; });
    if (it == students.end()) {
        cout << "δ�ҵ���ѧ����Ϣ��" << endl;
        return;
    }

    cout << "��Ŀα�����:" << endl;
    for (const auto& courseId : it->selectedCourses) {
        auto courseIt = find_if(courses.begin(), courses.end(), [&](const Course& c) { return c.courseId == courseId; });
        if (courseIt != courses.end()) {
            cout << "�γ̱��: " << courseIt->courseId << ", �γ�����: " << courseIt->courseName << ", �Ͽ�ʱ��: " << courseIt->classTime << endl;
        }
    }
}

// ��ʦ¼��ѧ���ɼ�
void teacherInputScore() {
    string courseId;
    cout << "������Ҫ¼��ɼ��Ŀγ̱��: ";
    getline(cin, courseId);
    auto courseIt = find_if(courses.begin(), courses.end(), [&](const Course& c) { return c.courseId == courseId; });
    if (courseIt == courses.end()) {
        cout << "δ�ҵ��ÿγ���Ϣ��" << endl;
        return;
    }

    for (const auto& s : students) {
        if (find(s.selectedCourses.begin(), s.selectedCourses.end(), courseId) != s.selectedCourses.end()) {
            double score;
            cout << "������ѧ�� " << s.name << " (" << s.id << ") �ĳɼ�: ";
            cin >> score;
            cin.ignore();
            courseIt->scores.emplace_back(s.id, score);
        }
    }
    saveToFile();
}

// ѧ����ѯ���Ƴɼ�
void studentQueryScore() {
    string studentId;
    cout << "���������ѧ��: ";
    getline(cin, studentId);
    auto it = find_if(students.begin(), students.end(), [&](const Student& s) { return s.id == studentId; });
    if (it == students.end()) {
        cout << "δ�ҵ���ѧ����Ϣ��" << endl;
        return;
    }

    cout << "��ĸ��Ƴɼ�����:" << endl;
    for (const auto& courseId : it->selectedCourses) {
        auto courseIt = find_if(courses.begin(), courses.end(), [&](const Course& c) { return c.courseId == courseId; });
        if (courseIt != courses.end()) {
            auto scoreIt = find_if(courseIt->scores.begin(), courseIt->scores.end(), [&](const pair<string, double>& p) { return p.first == studentId; });
            if (scoreIt != courseIt->scores.end()) {
                cout << "�γ�����: " << courseIt->courseName << ", �ɼ�: " << scoreIt->second << endl;
            } else {
                cout << "�γ�����: " << courseIt->courseName << ", �ɼ�δ¼��" << endl;
            }
        }
    }
}

// ����ͳ��ѧ��ѡ����������Գɼ�
void statisticsByClass() {
    // ��ʾ�������谴ѧ��ǰ��λ���ְ༶
    string classPrefix;
    cout << "������༶ǰ׺ (��ѧ��ǰ��λ): ";
    getline(cin, classPrefix);

    cout << "�༶ " << classPrefix << " ��ѡ����������Գɼ�ͳ��:" << endl;
    for (const auto& s : students) {
        if (s.id.find(classPrefix) == 0) {
            cout << "ѧ������: " << s.name << ", ѧ��: " << s.id << endl;
            for (const auto& courseId : s.selectedCourses) {
                auto courseIt = find_if(courses.begin(), courses.end(), [&](const Course& c) { return c.courseId == courseId; });
                if (courseIt != courses.end()) {
                    auto scoreIt = find_if(courseIt->scores.begin(), courseIt->scores.end(), [&](const pair<string, double>& p) { return p.first == s.id; });
                    if (scoreIt != courseIt->scores.end()) {
                        cout << "  �γ�����: " << courseIt->courseName << ", �ɼ�: " << scoreIt->second << endl;
                    } else {
                        cout << "  �γ�����: " << courseIt->courseName << ", �ɼ�δ¼��" << endl;
                    }
                }
            }
        }
    }
}

// ���γ�ͳ��ѧ�����������Գɼ�
void statisticsByCourse() {
    string courseId;
    cout << "������Ҫͳ�ƵĿγ̱��: ";
    getline(cin, courseId);
    auto courseIt = find_if(courses.begin(), courses.end(), [&](const Course& c) { return c.courseId == courseId; });
    if (courseIt == courses.end()) {
        cout << "δ�ҵ��ÿγ���Ϣ��" << endl;
        return;
    }

    cout << "�γ� " << courseIt->courseName << " ��ѧ�����������Գɼ�ͳ��:" << endl;
    for (const auto& score : courseIt->scores) {
        auto studentIt = find_if(students.begin(), students.end(), [&](const Student& s) { return s.id == score.first; });
        if (studentIt != students.end()) {
            cout << "ѧ������: " << studentIt->name << ", ѧ��: " << studentIt->id << ", �ɼ�: " << score.second << endl;
        }
    }
}

// ͳ�Ʋ����ÿ��ͬѧ����ѧ�ּ�������γ�
void studentCreditAndFailedCourses() {
    for (const auto& s : students) {
        double totalCredit = 0;
        cout << "ѧ������: " << s.name << ", ѧ��: " << s.id << endl;
        cout << "  ������γ�: ";
        bool hasFailed = false;
        for (const auto& courseId : s.selectedCourses) {
            auto courseIt = find_if(courses.begin(), courses.end(), [&](const Course& c) { return c.courseId == courseId; });
            if (courseIt != courses.end()) {
                auto scoreIt = find_if(courseIt->scores.begin(), courseIt->scores.end(), [&](const pair<string, double>& p) { return p.first == s.id; });
                if (scoreIt != courseIt->scores.end()) {
                    if (scoreIt->second < 60) {
                        if (hasFailed) cout << ", ";
                        cout << courseIt->courseName;
                        hasFailed = true;
                    } else {
                        totalCredit += courseIt->credit;
                    }
                }
            }
        }
        if (!hasFailed) cout << "��";
        cout << endl;
        cout << "  ����ѧ��: " << totalCredit << endl;
    }
}

// DIY ���ܣ��鿴ĳ�ſγ̵�����ѧ������
void diyFunction() {
    string courseId;
    cout << "������Ҫ�鿴�Ŀγ̱��: ";
    getline(cin, courseId);
    auto courseIt = find_if(courses.begin(), courses.end(), [&](const Course& c) { return c.courseId == courseId; });
    if (courseIt == courses.end()) {
        cout << "δ�ҵ��ÿγ���Ϣ��" << endl;
        return;
    }

    if (courseIt->retakeScores.empty()) {
        cout << "�ÿγ���������ѧ����" << endl;
    } else {
        cout << "�γ� " << courseIt->courseName << " ������ѧ������:" << endl;
        for (const auto& retake : courseIt->retakeScores) {
            auto studentIt = find_if(students.begin(), students.end(), [&](const Student& s) { return s.id == retake.first; });
            if (studentIt != students.end()) {
                cout << "ѧ������: " << studentIt->name << ", ѧ��: " << studentIt->id << ", ����ѧ��: " << retake.second.first << ", ���޳ɼ�: " << retake.second.second << endl;
            }
        }
    }
}

// ������Ϣ���ļ�
void saveToFile() {
    ofstream file(restoreFile);
    if (file.is_open()) {
        // ����ѧ����Ϣ
        file << "Students:" << endl;
        for (const auto& s : students) {
            file << s.id << "," << s.name << "," << s.gender << "," << s.age << "," << s.dormitory << "," << s.phone;
            for (const auto& courseId : s.selectedCourses) {
                file << "," << courseId;
            }
            file << endl;
        }
        // ����γ���Ϣ
        file << "Courses:" << endl;
        for (const auto& c : courses) {
            file << c.courseId << "," << c.courseName << "," << c.classTime << "," << c.credit << "," << c.isRetakeAvailable;
            for (const auto& score : c.scores) {
                file << "," << score.first << ":" << score.second;
            }
            for (const auto& retake : c.retakeScores) {
                file << "," << retake.first << ":" << retake.second.first << ":" << retake.second.second;
            }
            file << endl;
        }
        file.close();
    } else {
        cout << "�޷����ļ���" << endl;
    }
}

// ���ļ�������Ϣ
void loadFromFile() {
    ifstream file(restoreFile);
    if (file.is_open()) {
        string line;
        bool isStudentSection = false;
        while (getline(file, line)) {
            if (line == "Students:") {
                isStudentSection = true;
                continue;
            } else if (line == "Courses:") {
                isStudentSection = false;
                continue;
            }

            if (isStudentSection) {
                Student s;
                size_t pos = 0;
                string token;
                int index = 0;
                while ((pos = line.find(',')) != string::npos) {
                    token = line.substr(0, pos);
                    if (index == 0) s.id = token;
                    else if (index == 1) s.name = token;
                    else if (index == 2) s.gender = token;
                    else if (index == 3) s.age = stoi(token);
                    else if (index == 4) s.dormitory = token;
                    else if (index == 5) s.phone = token;
                    else s.selectedCourses.push_back(token);
                    line.erase(0, pos + 1);
                    index++;
                }
                s.selectedCourses.push_back(line);
                students.push_back(s);
            } else {
                Course c;
                size_t pos = 0;
                string token;
                int index = 0;
                while ((pos = line.find(',')) != string::npos) {
                    token = line.substr(0, pos);
                    if (index == 0) c.courseId = token;
                    else if (index == 1) c.courseName = token;
                    else if (index == 2) c.classTime = token;
                    else if (index == 3) c.credit = stod(token);
                    else if (index == 4) c.isRetakeAvailable = stoi(token);
                    else {
                        size_t colonPos = token.find(':');
                        if (colonPos != string::npos) {
                            string studentId = token.substr(0, colonPos);
                            string scoreStr = token.substr(colonPos + 1);
                            size_t secondColonPos = scoreStr.find(':');
                            if (secondColonPos != string::npos) {
                                string retakeSemester = scoreStr.substr(0, secondColonPos);
                                double retakeScore = stod(scoreStr.substr(secondColonPos + 1));
                                c.retakeScores.emplace_back(studentId, make_pair(retakeSemester, retakeScore));
                            } else {
                                double score = stod(scoreStr);
                                c.scores.emplace_back(studentId, score);
                            }
                        }
                    }
                    line.erase(0, pos + 1);
                    index++;
                }
                size_t colonPos = line.find(':');
                if (colonPos != string::npos) {
                    string studentId = line.substr(0, colonPos);
                    string scoreStr = line.substr(colonPos + 1);
                    size_t secondColonPos = scoreStr.find(':');
                    if (secondColonPos != string::npos) {
                        string retakeSemester = scoreStr.substr(0, secondColonPos);
                        double retakeScore = stod(scoreStr.substr(secondColonPos + 1));
                        c.retakeScores.emplace_back(studentId, make_pair(retakeSemester, retakeScore));
                    } else {
                        double score = stod(scoreStr);
                        c.scores.emplace_back(studentId, score);
                    }
                }
                courses.push_back(c);
            }
        }
        file.close();
    }
}

// ����Ա��¼
bool adminLogin() {
    string username, password;
    cout << "���������Ա�û���: ";
    getline(cin, username);
    cout << "���������Ա����: ";
    getline(cin, password);
    for (const auto& admin : admins) {
        if (admin.username == username && admin.password == password) {
            return true;
        }
    }
    cout << "�û������������" << endl;
    return false;
}

// ��ʦ��¼
bool teacherLogin() {
    string id, password;
    cout << "�������ʦ���: ";
    getline(cin, id);
    cout << "�������ʦ����: ";
    getline(cin, password);
    for (const auto& teacher : teachers) {
        if (teacher.id == id && teacher.password == password) {
            return true;
        }
    }
    cout << "��Ż��������" << endl;
    return false;
}

// ѧ����¼
bool studentLogin() {
    string id;
    cout << "������ѧ��ѧ��: ";
    getline(cin, id);
    for (const auto& student : students) {
        if (student.id == id) {
            return true;
        }
    }
    cout << "δ�ҵ���ѧ����Ϣ��" << endl;
    return false;
}

// �������Ա��Ϣ���ļ�
void saveAdminsToFile() {
    ofstream file(adminFile);
    if (file.is_open()) {
        for (const auto& admin : admins) {
            file << admin.username << "," << admin.password << endl;
        }
        file.close();
    } else {
        cout << "�޷��򿪹���Ա�ļ���" << endl;
    }
}

// ���ļ����ع���Ա��Ϣ
void loadAdminsFromFile() {
    ifstream file(adminFile);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            size_t pos = line.find(',');
            if (pos != string::npos) {
                Admin admin;
                admin.username = line.substr(0, pos);
                admin.password = line.substr(pos + 1);
                admins.push_back(admin);
            }
        }
        file.close();
    }
}

// �����ʦ��Ϣ���ļ�
void saveTeachersToFile() {
    ofstream file(teacherFile);
    if (file.is_open()) {
        for (const auto& teacher : teachers) {
            file << teacher.id << "," << teacher.name << "," << teacher.password << endl;
        }
        file.close();
    } else {
        cout << "�޷��򿪽�ʦ�ļ���" << endl;
    }
}

// ���ļ����ؽ�ʦ��Ϣ
void loadTeachersFromFile() {
    ifstream file(teacherFile);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            size_t pos1 = line.find(',');
            size_t pos2 = line.find(',', pos1 + 1);
            if (pos1 != string::npos && pos2 != string::npos) {
                Teacher teacher;
                teacher.id = line.substr(0, pos1);
                teacher.name = line.substr(pos1 + 1, pos2 - pos1 - 1);
                teacher.password = line.substr(pos2 + 1);
                teachers.push_back(teacher);
            }
        }
        file.close();
    }
}

// ������븴�Ӷ�
bool isPasswordValid(const string& password) {
    if (password.length() < 8) return false;
    bool hasUpper = false, hasLower = false, hasDigit = false;
    for (char c : password) {
        if (isupper(c)) hasUpper = true;
        if (islower(c)) hasLower = true;
        if (isdigit(c)) hasDigit = true;
    }
    return hasUpper && hasLower && hasDigit;
}

// ���ѧ��ѧ���Ƿ��Ѵ���
bool isStudentIdExists(const string& id) {
    for (const auto& student : students) {
        if (student.id == id) {
            return true;
        }
    }
    return false;
}

// ������Ա�û����Ƿ��Ѵ���
bool isAdminUsernameExists(const string& username) {
    for (const auto& admin : admins) {
        if (admin.username == username) {
            return true;
        }
    }
    return false;
}

// ����ʦ����Ƿ��Ѵ���
bool isTeacherIdExists(const string& id) {
    for (const auto& teacher : teachers) {
        if (teacher.id == id) {
            return true;
        }
    }
    return false;
}

// ����Աע��
void adminRegister() {
    Admin newAdmin;
    cout << "���������Ա�û���: ";
    getline(cin, newAdmin.username);
    while (isAdminUsernameExists(newAdmin.username)) {
        cout << "���û����Ѵ��ڣ�����������: ";
        getline(cin, newAdmin.username);
    }
    string password, confirmPassword;
    do {
        cout << "���������Ա����: ";
        getline(cin, password);
        while (!isPasswordValid(password)) {
            cout << "���볤������Ϊ 8 λ�����������д��ĸ��Сд��ĸ�����֣�����������: ";
            getline(cin, password);
        }
        cout << "���ٴ��������Ա�������ȷ��: ";
        getline(cin, confirmPassword);
        if (password != confirmPassword) {
            cout << "������������벻һ�£����������룡" << endl;
        }
    } while (password != confirmPassword);
    newAdmin.password = password;
    admins.push_back(newAdmin);
    saveAdminsToFile();
    cout << "����Աע��ɹ���" << endl;
}

// ��ʦע��
void teacherRegister() {
    Teacher newTeacher;
    cout << "�������ʦ���: ";
    getline(cin, newTeacher.id);
    while (isTeacherIdExists(newTeacher.id)) {
        cout << "�ý�ʦ����Ѵ��ڣ�����������: ";
        getline(cin, newTeacher.id);
    }
    cout << "�������ʦ����: ";
    getline(cin, newTeacher.name);
    string password, confirmPassword;
    do {
        cout << "�������ʦ����: ";
        getline(cin, password);
        while (!isPasswordValid(password)) {
            cout << "���볤������Ϊ 8 λ�����������д��ĸ��Сд��ĸ�����֣�����������: ";
            getline(cin, password);
        }
        cout << "���ٴ������ʦ�������ȷ��: ";
        getline(cin, confirmPassword);
        if (password != confirmPassword) {
            cout << "������������벻һ�£����������룡" << endl;
        }
    } while (password != confirmPassword);
    newTeacher.password = password;
    teachers.push_back(newTeacher);
    saveTeachersToFile();
    cout << "��ʦע��ɹ���" << endl;
}

// ѧ��ע��
void studentRegister() {
    Student newStudent;
    cout << "������ѧ��: ";
    getline(cin, newStudent.id);
    while (isStudentIdExists(newStudent.id)) {
        cout << "��ѧ���Ѵ��ڣ�����������: ";
        getline(cin, newStudent.id);
    }
    cout << "����������: ";
    getline(cin, newStudent.name);
    cout << "�������Ա�: ";
    getline(cin, newStudent.gender);
    cout << "����������: ";
    cin >> newStudent.age;
    cin.ignore();
    cout << "�������������: ";
    getline(cin, newStudent.dormitory);
    cout << "������绰����: ";
    getline(cin, newStudent.phone);
    students.push_back(newStudent);
    saveToFile();
    cout << "ѧ��ע��ɹ���" << endl;
}

// ɾ������Ա�˻�
void deleteAdminAccount() {
    if (admins.empty()) {
        cout << "û�п�ɾ���Ĺ���Ա�˻���" << endl;
        return;
    }
    string username;
    cout << "������Ҫɾ���Ĺ���Ա�û���: ";
    getline(cin, username);
    auto it = find_if(admins.begin(), admins.end(), [&](const Admin& a) { return a.username == username; });
    if (it != admins.end()) {
        admins.erase(it);
        saveAdminsToFile();
        cout << "����Ա�˻�ɾ���ɹ���" << endl;
    } else {
        cout << "δ�ҵ��ù���Ա�˻���" << endl;
    }
}

// ɾ����ʦ�˻�
void deleteTeacherAccount() {
    if (teachers.empty()) {
        cout << "û�п�ɾ���Ľ�ʦ�˻���" << endl;
        return;
    }
    string id;
    cout << "������Ҫɾ���Ľ�ʦ���: ";
    getline(cin, id);
    auto it = find_if(teachers.begin(), teachers.end(), [&](const Teacher& t) { return t.id == id; });
    if (it != teachers.end()) {
        teachers.erase(it);
        saveTeachersToFile();
        cout << "��ʦ�˻�ɾ���ɹ���" << endl;
    } else {
        cout << "δ�ҵ��ý�ʦ�˻���" << endl;
    }
}

// ɾ��ѧ���˻�
void deleteStudentAccount() {
    if (students.empty()) {
        cout << "û�п�ɾ����ѧ���˻���" << endl;
        return;
    }
    string id;
    cout << "������Ҫɾ����ѧ��ѧ��: ";
    getline(cin, id);
    auto it = find_if(students.begin(), students.end(), [&](const Student& s) { return s.id == id; });
    if (it != students.end()) {
        // �Ƴ���ѧ�������пγ��еĳɼ���¼
        for (auto& course : courses) {
            auto scoreIt = remove_if(course.scores.begin(), course.scores.end(), [&](const pair<string, double>& p) { return p.first == id; });
            course.scores.erase(scoreIt, course.scores.end());

            auto retakeIt = remove_if(course.retakeScores.begin(), course.retakeScores.end(), [&](const pair<string, pair<string, double>>& p) { return p.first == id; });
            course.retakeScores.erase(retakeIt, course.retakeScores.end());
        }
        students.erase(it);
        saveToFile();
        cout << "ѧ���˻�ɾ���ɹ���" << endl;
    } else {
        cout << "δ�ҵ���ѧ���˻���" << endl;
    }
}

int main() {
    loadFromFile();
    loadAdminsFromFile();
    loadTeachersFromFile();
    int choice;
    while (true) {
        cout << "������Ϣ����ϵͳ�˵�:" << endl;
        cout << "1. ����Ա��¼\n2. ��ʦ��¼\n3. ѧ����¼\n4. ����Աע��\n5. ��ʦע��\n6. ѧ��ע��\n7. ɾ������Ա�˻�\n8. ɾ����ʦ�˻�\n9. ɾ��ѧ���˻�\n10. �˳�\n���������ѡ��: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                if (adminLogin()) {
                    int adminChoice;
                    while (true) {
                        cout << "����Ա�˵�:" << endl;
                        cout << "1. ¼����Ϣ\n2. ����ͳ��ѧ��ѡ����������Գɼ�\n3. ���γ�ͳ��ѧ�����������Գɼ�\n4. ͳ�Ʋ����ÿ��ͬѧ����ѧ�ּ��������γ�\n5. DIY ����: �鿴ĳ�ſγ̵�����ѧ������\n6. �������˵�\n���������ѡ��: ";
                        cin >> adminChoice;
                        cin.ignore();
                        switch (adminChoice) {
                            case 1:
                                adminInput();
                                break;
                            case 2:
                                statisticsByClass();
                                break;
                            case 3:
                                statisticsByCourse();
                                break;
                            case 4:
                                studentCreditAndFailedCourses();
                                break;
                            case 5:
                                diyFunction();
                                break;
                            case 6:
                                break;
                            default:
                                cout << "��Ч��ѡ�����������룡" << endl;
                        }
                        if (adminChoice == 6) break;
                    }
                }
                break;
            case 2:
                if (teacherLogin()) {
                    int teacherChoice;
                    while (true) {
                        cout << "��ʦ�˵�:" << endl;
                        cout << "1. ¼��ѧ���ɼ�\n2. �������˵�\n���������ѡ��: ";
                        cin >> teacherChoice;
                        cin.ignore();
                        switch (teacherChoice) {
                            case 1:
                                teacherInputScore();
                                break;
                            case 2:
                                break;
                            default:
                                cout << "��Ч��ѡ�����������룡" << endl;
                        }
                        if (teacherChoice == 2) break;
                    }
                }
                break;
            case 3:
                if (studentLogin()) {
                    int studentChoice;
                    while (true) {
                        cout << "ѧ���˵�:" << endl;
                        cout << "1. ѡ��\n2. �鿴�α�\n3. ��ѯ���Ƴɼ�\n4. �������˵�\n���������ѡ��: ";
                        cin >> studentChoice;
                        cin.ignore();
                        switch (studentChoice) {
                            case 1:
                                studentSelectCourse();
                                break;
                            case 2:
                                studentViewSchedule();
                                break;
                            case 3:
                                studentQueryScore();
                                break;
                            case 4:
                                break;
                            default:
                                cout << "��Ч��ѡ�����������룡" << endl;
                        }
                        if (studentChoice == 4) break;
                    }
                }
                break;
            case 4:
                adminRegister();
                break;
            case 5:
                teacherRegister();
                break;
            case 6:
                studentRegister();
                break;
            case 7:
                deleteAdminAccount();
                break;
            case 8:
                deleteTeacherAccount();
                break;
            case 9:
                deleteStudentAccount();
                break;
            case 10:
                saveToFile();
                saveAdminsToFile();
                saveTeachersToFile();
                return 0;
            default:
                cout << "��Ч��ѡ�����������룡" << endl;
        }
    }
    return 0;
}    