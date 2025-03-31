#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

// 学生基本信息结构体
struct Student {
    string id;
    string name;
    string gender;
    int age;
    string dormitory;
    string phone;
    vector<string> selectedCourses;
};

// 课程基本信息结构体
struct Course {
    string courseId;
    string courseName;
    string classTime;
    vector<pair<string, double>> scores; // 学生学号和成绩
    vector<pair<string, pair<string, double>>> retakeScores; // 学生学号，重修学期和成绩
    double credit;
    bool isRetakeAvailable;
};

// 管理员结构体
struct Admin {
    string username;
    string password;
};

// 教师结构体
struct Teacher {
    string id;
    string name;
    string password;
};

// 全局变量
vector<Student> students;
vector<Course> courses;
vector<Admin> admins;
vector<Teacher> teachers;
const string restoreFile = "restore.txt";
const string adminFile = "admins.txt";
const string teacherFile = "teachers.txt";

// 函数声明
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

// 管理员录入信息
void adminInput() {
    int choice;
    while (true) {
        cout << "1. 录入学生信息\n2. 录入课程信息\n3. 返回主菜单\n请输入你的选择: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            Student s;
            cout << "请输入学号: ";
            getline(cin, s.id);
            while (isStudentIdExists(s.id)) {
                cout << "该学号已存在，请重新输入: ";
                getline(cin, s.id);
            }
            cout << "请输入姓名: ";
            getline(cin, s.name);
            cout << "请输入性别: ";
            getline(cin, s.gender);
            cout << "请输入年龄: ";
            cin >> s.age;
            cin.ignore();
            cout << "请输入宿舍号码: ";
            getline(cin, s.dormitory);
            cout << "请输入电话号码: ";
            getline(cin, s.phone);
            students.push_back(s);
        } else if (choice == 2) {
            Course c;
            cout << "请输入课程编号: ";
            getline(cin, c.courseId);
            cout << "请输入课程名称: ";
            getline(cin, c.courseName);
            cout << "请输入上课时间: ";
            getline(cin, c.classTime);
            cout << "请输入学分: ";
            cin >> c.credit;
            cin.ignore();
            cout << "是否允许重修 (1: 是, 0: 否): ";
            cin >> c.isRetakeAvailable;
            cin.ignore();
            courses.push_back(c);
        } else if (choice == 3) {
            break;
        }
    }
    saveToFile();
}

// 学生选课
void studentSelectCourse() {
    string studentId;
    cout << "请输入你的学号: ";
    getline(cin, studentId);
    auto it = find_if(students.begin(), students.end(), [&](const Student& s) { return s.id == studentId; });
    if (it == students.end()) {
        cout << "未找到该学生信息！" << endl;
        return;
    }

    cout << "可选择的课程列表:" << endl;
    for (const auto& c : courses) {
        cout << "课程编号: " << c.courseId << ", 课程名称: " << c.courseName << endl;
    }

    string courseId;
    cout << "请输入要选择的课程编号 (输入 'q' 退出): ";
    while (getline(cin, courseId) && courseId != "q") {
        auto courseIt = find_if(courses.begin(), courses.end(), [&](const Course& c) { return c.courseId == courseId; });
        if (courseIt != courses.end()) {
            it->selectedCourses.push_back(courseId);
            cout << "选课成功！" << endl;
        } else {
            cout << "未找到该课程信息！" << endl;
        }
        cout << "请输入要选择的课程编号 (输入 'q' 退出): ";
    }
    saveToFile();
}

// 学生查看课表
void studentViewSchedule() {
    string studentId;
    cout << "请输入你的学号: ";
    getline(cin, studentId);
    auto it = find_if(students.begin(), students.end(), [&](const Student& s) { return s.id == studentId; });
    if (it == students.end()) {
        cout << "未找到该学生信息！" << endl;
        return;
    }

    cout << "你的课表如下:" << endl;
    for (const auto& courseId : it->selectedCourses) {
        auto courseIt = find_if(courses.begin(), courses.end(), [&](const Course& c) { return c.courseId == courseId; });
        if (courseIt != courses.end()) {
            cout << "课程编号: " << courseIt->courseId << ", 课程名称: " << courseIt->courseName << ", 上课时间: " << courseIt->classTime << endl;
        }
    }
}

// 教师录入学生成绩
void teacherInputScore() {
    string courseId;
    cout << "请输入要录入成绩的课程编号: ";
    getline(cin, courseId);
    auto courseIt = find_if(courses.begin(), courses.end(), [&](const Course& c) { return c.courseId == courseId; });
    if (courseIt == courses.end()) {
        cout << "未找到该课程信息！" << endl;
        return;
    }

    for (const auto& s : students) {
        if (find(s.selectedCourses.begin(), s.selectedCourses.end(), courseId) != s.selectedCourses.end()) {
            double score;
            cout << "请输入学生 " << s.name << " (" << s.id << ") 的成绩: ";
            cin >> score;
            cin.ignore();
            courseIt->scores.emplace_back(s.id, score);
        }
    }
    saveToFile();
}

// 学生查询各科成绩
void studentQueryScore() {
    string studentId;
    cout << "请输入你的学号: ";
    getline(cin, studentId);
    auto it = find_if(students.begin(), students.end(), [&](const Student& s) { return s.id == studentId; });
    if (it == students.end()) {
        cout << "未找到该学生信息！" << endl;
        return;
    }

    cout << "你的各科成绩如下:" << endl;
    for (const auto& courseId : it->selectedCourses) {
        auto courseIt = find_if(courses.begin(), courses.end(), [&](const Course& c) { return c.courseId == courseId; });
        if (courseIt != courses.end()) {
            auto scoreIt = find_if(courseIt->scores.begin(), courseIt->scores.end(), [&](const pair<string, double>& p) { return p.first == studentId; });
            if (scoreIt != courseIt->scores.end()) {
                cout << "课程名称: " << courseIt->courseName << ", 成绩: " << scoreIt->second << endl;
            } else {
                cout << "课程名称: " << courseIt->courseName << ", 成绩未录入" << endl;
            }
        }
    }
}

// 按班统计学生选课情况及考试成绩
void statisticsByClass() {
    // 简单示例，假设按学号前几位区分班级
    string classPrefix;
    cout << "请输入班级前缀 (如学号前几位): ";
    getline(cin, classPrefix);

    cout << "班级 " << classPrefix << " 的选课情况及考试成绩统计:" << endl;
    for (const auto& s : students) {
        if (s.id.find(classPrefix) == 0) {
            cout << "学生姓名: " << s.name << ", 学号: " << s.id << endl;
            for (const auto& courseId : s.selectedCourses) {
                auto courseIt = find_if(courses.begin(), courses.end(), [&](const Course& c) { return c.courseId == courseId; });
                if (courseIt != courses.end()) {
                    auto scoreIt = find_if(courseIt->scores.begin(), courseIt->scores.end(), [&](const pair<string, double>& p) { return p.first == s.id; });
                    if (scoreIt != courseIt->scores.end()) {
                        cout << "  课程名称: " << courseIt->courseName << ", 成绩: " << scoreIt->second << endl;
                    } else {
                        cout << "  课程名称: " << courseIt->courseName << ", 成绩未录入" << endl;
                    }
                }
            }
        }
    }
}

// 按课程统计学生名单及考试成绩
void statisticsByCourse() {
    string courseId;
    cout << "请输入要统计的课程编号: ";
    getline(cin, courseId);
    auto courseIt = find_if(courses.begin(), courses.end(), [&](const Course& c) { return c.courseId == courseId; });
    if (courseIt == courses.end()) {
        cout << "未找到该课程信息！" << endl;
        return;
    }

    cout << "课程 " << courseIt->courseName << " 的学生名单及考试成绩统计:" << endl;
    for (const auto& score : courseIt->scores) {
        auto studentIt = find_if(students.begin(), students.end(), [&](const Student& s) { return s.id == score.first; });
        if (studentIt != students.end()) {
            cout << "学生姓名: " << studentIt->name << ", 学号: " << studentIt->id << ", 成绩: " << score.second << endl;
        }
    }
}

// 统计并输出每个同学已修学分及不及格课程
void studentCreditAndFailedCourses() {
    for (const auto& s : students) {
        double totalCredit = 0;
        cout << "学生姓名: " << s.name << ", 学号: " << s.id << endl;
        cout << "  不及格课程: ";
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
        if (!hasFailed) cout << "无";
        cout << endl;
        cout << "  已修学分: " << totalCredit << endl;
    }
}

// DIY 功能：查看某门课程的重修学生名单
void diyFunction() {
    string courseId;
    cout << "请输入要查看的课程编号: ";
    getline(cin, courseId);
    auto courseIt = find_if(courses.begin(), courses.end(), [&](const Course& c) { return c.courseId == courseId; });
    if (courseIt == courses.end()) {
        cout << "未找到该课程信息！" << endl;
        return;
    }

    if (courseIt->retakeScores.empty()) {
        cout << "该课程暂无重修学生。" << endl;
    } else {
        cout << "课程 " << courseIt->courseName << " 的重修学生名单:" << endl;
        for (const auto& retake : courseIt->retakeScores) {
            auto studentIt = find_if(students.begin(), students.end(), [&](const Student& s) { return s.id == retake.first; });
            if (studentIt != students.end()) {
                cout << "学生姓名: " << studentIt->name << ", 学号: " << studentIt->id << ", 重修学期: " << retake.second.first << ", 重修成绩: " << retake.second.second << endl;
            }
        }
    }
}

// 保存信息到文件
void saveToFile() {
    ofstream file(restoreFile);
    if (file.is_open()) {
        // 保存学生信息
        file << "Students:" << endl;
        for (const auto& s : students) {
            file << s.id << "," << s.name << "," << s.gender << "," << s.age << "," << s.dormitory << "," << s.phone;
            for (const auto& courseId : s.selectedCourses) {
                file << "," << courseId;
            }
            file << endl;
        }
        // 保存课程信息
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
        cout << "无法打开文件！" << endl;
    }
}

// 从文件加载信息
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

// 管理员登录
bool adminLogin() {
    string username, password;
    cout << "请输入管理员用户名: ";
    getline(cin, username);
    cout << "请输入管理员密码: ";
    getline(cin, password);
    for (const auto& admin : admins) {
        if (admin.username == username && admin.password == password) {
            return true;
        }
    }
    cout << "用户名或密码错误！" << endl;
    return false;
}

// 教师登录
bool teacherLogin() {
    string id, password;
    cout << "请输入教师编号: ";
    getline(cin, id);
    cout << "请输入教师密码: ";
    getline(cin, password);
    for (const auto& teacher : teachers) {
        if (teacher.id == id && teacher.password == password) {
            return true;
        }
    }
    cout << "编号或密码错误！" << endl;
    return false;
}

// 学生登录
bool studentLogin() {
    string id;
    cout << "请输入学生学号: ";
    getline(cin, id);
    for (const auto& student : students) {
        if (student.id == id) {
            return true;
        }
    }
    cout << "未找到该学生信息！" << endl;
    return false;
}

// 保存管理员信息到文件
void saveAdminsToFile() {
    ofstream file(adminFile);
    if (file.is_open()) {
        for (const auto& admin : admins) {
            file << admin.username << "," << admin.password << endl;
        }
        file.close();
    } else {
        cout << "无法打开管理员文件！" << endl;
    }
}

// 从文件加载管理员信息
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

// 保存教师信息到文件
void saveTeachersToFile() {
    ofstream file(teacherFile);
    if (file.is_open()) {
        for (const auto& teacher : teachers) {
            file << teacher.id << "," << teacher.name << "," << teacher.password << endl;
        }
        file.close();
    } else {
        cout << "无法打开教师文件！" << endl;
    }
}

// 从文件加载教师信息
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

// 检查密码复杂度
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

// 检查学生学号是否已存在
bool isStudentIdExists(const string& id) {
    for (const auto& student : students) {
        if (student.id == id) {
            return true;
        }
    }
    return false;
}

// 检查管理员用户名是否已存在
bool isAdminUsernameExists(const string& username) {
    for (const auto& admin : admins) {
        if (admin.username == username) {
            return true;
        }
    }
    return false;
}

// 检查教师编号是否已存在
bool isTeacherIdExists(const string& id) {
    for (const auto& teacher : teachers) {
        if (teacher.id == id) {
            return true;
        }
    }
    return false;
}

// 管理员注册
void adminRegister() {
    Admin newAdmin;
    cout << "请输入管理员用户名: ";
    getline(cin, newAdmin.username);
    while (isAdminUsernameExists(newAdmin.username)) {
        cout << "该用户名已存在，请重新输入: ";
        getline(cin, newAdmin.username);
    }
    string password, confirmPassword;
    do {
        cout << "请输入管理员密码: ";
        getline(cin, password);
        while (!isPasswordValid(password)) {
            cout << "密码长度至少为 8 位，且需包含大写字母、小写字母和数字，请重新输入: ";
            getline(cin, password);
        }
        cout << "请再次输入管理员密码进行确认: ";
        getline(cin, confirmPassword);
        if (password != confirmPassword) {
            cout << "两次输入的密码不一致，请重新输入！" << endl;
        }
    } while (password != confirmPassword);
    newAdmin.password = password;
    admins.push_back(newAdmin);
    saveAdminsToFile();
    cout << "管理员注册成功！" << endl;
}

// 教师注册
void teacherRegister() {
    Teacher newTeacher;
    cout << "请输入教师编号: ";
    getline(cin, newTeacher.id);
    while (isTeacherIdExists(newTeacher.id)) {
        cout << "该教师编号已存在，请重新输入: ";
        getline(cin, newTeacher.id);
    }
    cout << "请输入教师姓名: ";
    getline(cin, newTeacher.name);
    string password, confirmPassword;
    do {
        cout << "请输入教师密码: ";
        getline(cin, password);
        while (!isPasswordValid(password)) {
            cout << "密码长度至少为 8 位，且需包含大写字母、小写字母和数字，请重新输入: ";
            getline(cin, password);
        }
        cout << "请再次输入教师密码进行确认: ";
        getline(cin, confirmPassword);
        if (password != confirmPassword) {
            cout << "两次输入的密码不一致，请重新输入！" << endl;
        }
    } while (password != confirmPassword);
    newTeacher.password = password;
    teachers.push_back(newTeacher);
    saveTeachersToFile();
    cout << "教师注册成功！" << endl;
}

// 学生注册
void studentRegister() {
    Student newStudent;
    cout << "请输入学号: ";
    getline(cin, newStudent.id);
    while (isStudentIdExists(newStudent.id)) {
        cout << "该学号已存在，请重新输入: ";
        getline(cin, newStudent.id);
    }
    cout << "请输入姓名: ";
    getline(cin, newStudent.name);
    cout << "请输入性别: ";
    getline(cin, newStudent.gender);
    cout << "请输入年龄: ";
    cin >> newStudent.age;
    cin.ignore();
    cout << "请输入宿舍号码: ";
    getline(cin, newStudent.dormitory);
    cout << "请输入电话号码: ";
    getline(cin, newStudent.phone);
    students.push_back(newStudent);
    saveToFile();
    cout << "学生注册成功！" << endl;
}

// 删除管理员账户
void deleteAdminAccount() {
    if (admins.empty()) {
        cout << "没有可删除的管理员账户！" << endl;
        return;
    }
    string username;
    cout << "请输入要删除的管理员用户名: ";
    getline(cin, username);
    auto it = find_if(admins.begin(), admins.end(), [&](const Admin& a) { return a.username == username; });
    if (it != admins.end()) {
        admins.erase(it);
        saveAdminsToFile();
        cout << "管理员账户删除成功！" << endl;
    } else {
        cout << "未找到该管理员账户！" << endl;
    }
}

// 删除教师账户
void deleteTeacherAccount() {
    if (teachers.empty()) {
        cout << "没有可删除的教师账户！" << endl;
        return;
    }
    string id;
    cout << "请输入要删除的教师编号: ";
    getline(cin, id);
    auto it = find_if(teachers.begin(), teachers.end(), [&](const Teacher& t) { return t.id == id; });
    if (it != teachers.end()) {
        teachers.erase(it);
        saveTeachersToFile();
        cout << "教师账户删除成功！" << endl;
    } else {
        cout << "未找到该教师账户！" << endl;
    }
}

// 删除学生账户
void deleteStudentAccount() {
    if (students.empty()) {
        cout << "没有可删除的学生账户！" << endl;
        return;
    }
    string id;
    cout << "请输入要删除的学生学号: ";
    getline(cin, id);
    auto it = find_if(students.begin(), students.end(), [&](const Student& s) { return s.id == id; });
    if (it != students.end()) {
        // 移除该学生在所有课程中的成绩记录
        for (auto& course : courses) {
            auto scoreIt = remove_if(course.scores.begin(), course.scores.end(), [&](const pair<string, double>& p) { return p.first == id; });
            course.scores.erase(scoreIt, course.scores.end());

            auto retakeIt = remove_if(course.retakeScores.begin(), course.retakeScores.end(), [&](const pair<string, pair<string, double>>& p) { return p.first == id; });
            course.retakeScores.erase(retakeIt, course.retakeScores.end());
        }
        students.erase(it);
        saveToFile();
        cout << "学生账户删除成功！" << endl;
    } else {
        cout << "未找到该学生账户！" << endl;
    }
}

int main() {
    loadFromFile();
    loadAdminsFromFile();
    loadTeachersFromFile();
    int choice;
    while (true) {
        cout << "教务信息管理系统菜单:" << endl;
        cout << "1. 管理员登录\n2. 教师登录\n3. 学生登录\n4. 管理员注册\n5. 教师注册\n6. 学生注册\n7. 删除管理员账户\n8. 删除教师账户\n9. 删除学生账户\n10. 退出\n请输入你的选择: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                if (adminLogin()) {
                    int adminChoice;
                    while (true) {
                        cout << "管理员菜单:" << endl;
                        cout << "1. 录入信息\n2. 按班统计学生选课情况及考试成绩\n3. 按课程统计学生名单及考试成绩\n4. 统计并输出每个同学已修学分及不及级课程\n5. DIY 功能: 查看某门课程的重修学生名单\n6. 返回主菜单\n请输入你的选择: ";
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
                                cout << "无效的选择，请重新输入！" << endl;
                        }
                        if (adminChoice == 6) break;
                    }
                }
                break;
            case 2:
                if (teacherLogin()) {
                    int teacherChoice;
                    while (true) {
                        cout << "教师菜单:" << endl;
                        cout << "1. 录入学生成绩\n2. 返回主菜单\n请输入你的选择: ";
                        cin >> teacherChoice;
                        cin.ignore();
                        switch (teacherChoice) {
                            case 1:
                                teacherInputScore();
                                break;
                            case 2:
                                break;
                            default:
                                cout << "无效的选择，请重新输入！" << endl;
                        }
                        if (teacherChoice == 2) break;
                    }
                }
                break;
            case 3:
                if (studentLogin()) {
                    int studentChoice;
                    while (true) {
                        cout << "学生菜单:" << endl;
                        cout << "1. 选课\n2. 查看课表\n3. 查询各科成绩\n4. 返回主菜单\n请输入你的选择: ";
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
                                cout << "无效的选择，请重新输入！" << endl;
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
                cout << "无效的选择，请重新输入！" << endl;
        }
    }
    return 0;
}    