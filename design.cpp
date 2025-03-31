#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
void show_menu_Register();
void show_menu_login();
void Register_admin();
void Register_teacher();
void Register_student();
void login_admin();
void login_teacher();
void login_student();
void show_menu0()
{
    cout << "================== 教务信息管理系统 ==================" << endl;
    cout << "1. 管理员登录" << endl;
    cout << "2. 学生登录" << endl;
    cout << "3. 教师登录" << endl;
    cout << "4. 退出" << endl;
    cout << "====================================================" << endl;
    cout << "请输入你的选择: ";
}
void show_menu_admin()
{
    cout << "================== 教务信息管理系统 ==================" << endl;
    cout << "1. 录入学生信息" << endl;
    cout << "2. 录入课程信息" << endl;
    cout << "====================================================" << endl;
    cout << "请输入你的选择: ";
}
void show_menu_student()
{
    cout << "================== 教务信息管理系统 ==================" << endl;
    cout << "1. 选课" << endl;
    cout << "2. 查询各科成绩" << endl;
    cout << "====================================================" << endl;
    cout << "请输入你的选择: ";
}
void show_menu_teacher()
{
    cout << "================== 教务信息管理系统 ==================" << endl;
    cout << "1. 录入学生成绩" << endl;
    cout << "2. 按班统计学生选课情况及考试成绩" << endl;
    cout << "3. 按课程统计学生名单及考试成绩" << endl;
    cout << "4. 统计并输出每个同学已修学分及不及格课程" << endl;
    cout << "====================================================" << endl;
    cout << "请输入你的选择: ";
}
void show_menu_start()
{
    cout << "================== 教务信息管理系统 ==================" << endl;
    cout << "1. 注册" << endl;
    cout << "2. 登录" << endl;
    cout << "3. 退出" << endl;
    cout << "====================================================" << endl;
    cout << "请输入你的选择: ";
    int choice;
    cin >> choice;
    switch (choice)
    {
    case 1:
        show_menu_Register();
        break;
    case 2:
        show_menu_login();
        break;
    case 3:
        exit(0);
    }
}
void show_menu_Register()
{
    cout << "================== 教务信息管理系统 ==================" << endl;
    cout << "1. 注册管理员账户" << endl;
    cout << "2. 注册教师账户" << endl;
    cout << "3. 注册学生账户" << endl;
    cout << "====================================================" << endl;
    cout << "请输入你的选择: ";
    int choice;
    cin >> choice;
    switch (choice)
    {
    case 1:
        Register_admin();
        break;
    case 2:Register_teacher();
        break;
    case 3: Register_student();
        break;
    }
}
 void show_menu_login()
{
    cout << "================== 教务信息管理系统 ==================" << endl;
    cout << "1. 登录管理员账户" << endl;
    cout << "2. 登录教师账户" << endl;
    cout << "3. 登录学生账户" << endl;
    cout << "====================================================" << endl;
    int choice;
    cin >> choice;
    switch (choice)
    {
    case 1:
        login_admin();
        break;
    case 2:
        login_teacher();
        break;
    case 3:
        login_student();
        break;
    }
}
void Register_admin()
{
    string username, password, confirm_password;
    cout << "================== 教务信息管理系统 ==================" << endl;
    cout << "请输入用户名: ";
    cin >> username;
    cout << "请输入密码: ";
    cin >> password;
    cout << "请再次输入密码: ";
    cin >> confirm_password;
    if (password != confirm_password)
    {
        cout << "两次输入的密码不一致，请重新注册！" << endl;
        return;
    }
    // 注册逻辑
    cout << "注册成功！" << endl;
  
}
void Register_teacher()
{
    string username, password, confirm_password;
    cout << "================== 教务信息管理系统 ==================" << endl;
    cout << "请输入用户名: ";
    cin >> username;
    cout << "请输入密码: ";
    cin >> password;
    cout << "请再次输入密码: ";
    cin >> confirm_password;
    if (password != confirm_password)
    {
        cout << "两次输入的密码不一致，请重新注册！" << endl;
        return;
    }
    // 注册逻辑
    cout << "注册成功！" << endl;
}
void Register_student()
{
    string username, password, confirm_password;
    cout << "================== 教务信息管理系统 ==================" << endl;
    cout << "请输入用户名: ";
    cin >> username;
    cout << "请输入密码: ";
    cin >> password;
    cout << "请再次输入密码: ";
    cin >> confirm_password;
    if (password != confirm_password)
    {
        cout << "两次输入的密码不一致，请重新注册！" << endl;
        return;
    }
    // 注册逻辑
    cout << "注册成功！" << endl;
}
void login_student()
{
    string username, password;
    cout << "请输入学生用户名: ";
    cin >> username;
    cout << "请输入学生密码: ";
    cin >> password;
    // 验证学生登录信息
    if (username == "student" && password == "student123")
    {
        cout << "学生登录成功！" << endl;
        show_menu_student();
    }
    else
    {
        cout << "学生登录失败！" << endl;
    }
}
void login_admin()
{
    string username, password;
    cout << "请输入管理员用户名: ";
    cin >> username;
    cout << "请输入管理员密码: ";
    cin >> password;
    // 验证管理员登录信息
    if (username == "admin" && password == "admin123")
    {
        cout << "管理员登录成功！" << endl;
        show_menu_admin();
    }
    else
    {
        cout << "管理员登录失败！" << endl;
    }
}
void login_teacher()
{
    string username, password;
    cout << "请输入教师用户名: ";
    cin >> username;
    cout << "请输入教师密码: ";
    cin >> password;
    // 验证教师登录信息
    if (username == "teacher" && password == "teacher123")
    {
        cout << "教师登录成功！" << endl;
        show_menu_teacher();
    }
    else
    {
        cout << "教师登录失败！" << endl;
    }
}
void show_menu1()
{
    cout << "================== 教务信息管理系统 ==================" << endl;
    cout << "1. 管理员录入学生信息" << endl;
    cout << "2. 管理员录入课程信息" << endl;
    cout << "3. 学生选课" << endl;
    cout << "4. 教师录入学生成绩" << endl;
    cout << "5. 学生查询各科成绩" << endl;
    cout << "6. 按班统计学生选课情况及考试成绩" << endl;
    cout << "7. 按课程统计学生名单及考试成绩" << endl;
    cout << "8. 统计并输出每个同学已修学分及不及格课程" << endl;
    cout << "9. 退出" << endl;
    cout << "====================================================" << endl;
    cout << "请输入你的选择: ";
}
int main()
{

    int choice;
   do
    {
        show_menu_start();
        cin >> choice;

        switch (choice)
        {
        case 1:
            show_menu_Register();
            break;
        case 2:
         show_menu_login();
            break;
        case 3:
            exit(0);
       
        }
    }while(true);

    return 0;
}