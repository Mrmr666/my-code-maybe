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
    cout << "================== ������Ϣ����ϵͳ ==================" << endl;
    cout << "1. ����Ա��¼" << endl;
    cout << "2. ѧ����¼" << endl;
    cout << "3. ��ʦ��¼" << endl;
    cout << "4. �˳�" << endl;
    cout << "====================================================" << endl;
    cout << "���������ѡ��: ";
}
void show_menu_admin()
{
    cout << "================== ������Ϣ����ϵͳ ==================" << endl;
    cout << "1. ¼��ѧ����Ϣ" << endl;
    cout << "2. ¼��γ���Ϣ" << endl;
    cout << "====================================================" << endl;
    cout << "���������ѡ��: ";
}
void show_menu_student()
{
    cout << "================== ������Ϣ����ϵͳ ==================" << endl;
    cout << "1. ѡ��" << endl;
    cout << "2. ��ѯ���Ƴɼ�" << endl;
    cout << "====================================================" << endl;
    cout << "���������ѡ��: ";
}
void show_menu_teacher()
{
    cout << "================== ������Ϣ����ϵͳ ==================" << endl;
    cout << "1. ¼��ѧ���ɼ�" << endl;
    cout << "2. ����ͳ��ѧ��ѡ����������Գɼ�" << endl;
    cout << "3. ���γ�ͳ��ѧ�����������Գɼ�" << endl;
    cout << "4. ͳ�Ʋ����ÿ��ͬѧ����ѧ�ּ�������γ�" << endl;
    cout << "====================================================" << endl;
    cout << "���������ѡ��: ";
}
void show_menu_start()
{
    cout << "================== ������Ϣ����ϵͳ ==================" << endl;
    cout << "1. ע��" << endl;
    cout << "2. ��¼" << endl;
    cout << "3. �˳�" << endl;
    cout << "====================================================" << endl;
    cout << "���������ѡ��: ";
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
    cout << "================== ������Ϣ����ϵͳ ==================" << endl;
    cout << "1. ע�����Ա�˻�" << endl;
    cout << "2. ע���ʦ�˻�" << endl;
    cout << "3. ע��ѧ���˻�" << endl;
    cout << "====================================================" << endl;
    cout << "���������ѡ��: ";
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
    cout << "================== ������Ϣ����ϵͳ ==================" << endl;
    cout << "1. ��¼����Ա�˻�" << endl;
    cout << "2. ��¼��ʦ�˻�" << endl;
    cout << "3. ��¼ѧ���˻�" << endl;
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
    cout << "================== ������Ϣ����ϵͳ ==================" << endl;
    cout << "�������û���: ";
    cin >> username;
    cout << "����������: ";
    cin >> password;
    cout << "���ٴ���������: ";
    cin >> confirm_password;
    if (password != confirm_password)
    {
        cout << "������������벻һ�£�������ע�ᣡ" << endl;
        return;
    }
    // ע���߼�
    cout << "ע��ɹ���" << endl;
  
}
void Register_teacher()
{
    string username, password, confirm_password;
    cout << "================== ������Ϣ����ϵͳ ==================" << endl;
    cout << "�������û���: ";
    cin >> username;
    cout << "����������: ";
    cin >> password;
    cout << "���ٴ���������: ";
    cin >> confirm_password;
    if (password != confirm_password)
    {
        cout << "������������벻һ�£�������ע�ᣡ" << endl;
        return;
    }
    // ע���߼�
    cout << "ע��ɹ���" << endl;
}
void Register_student()
{
    string username, password, confirm_password;
    cout << "================== ������Ϣ����ϵͳ ==================" << endl;
    cout << "�������û���: ";
    cin >> username;
    cout << "����������: ";
    cin >> password;
    cout << "���ٴ���������: ";
    cin >> confirm_password;
    if (password != confirm_password)
    {
        cout << "������������벻һ�£�������ע�ᣡ" << endl;
        return;
    }
    // ע���߼�
    cout << "ע��ɹ���" << endl;
}
void login_student()
{
    string username, password;
    cout << "������ѧ���û���: ";
    cin >> username;
    cout << "������ѧ������: ";
    cin >> password;
    // ��֤ѧ����¼��Ϣ
    if (username == "student" && password == "student123")
    {
        cout << "ѧ����¼�ɹ���" << endl;
        show_menu_student();
    }
    else
    {
        cout << "ѧ����¼ʧ�ܣ�" << endl;
    }
}
void login_admin()
{
    string username, password;
    cout << "���������Ա�û���: ";
    cin >> username;
    cout << "���������Ա����: ";
    cin >> password;
    // ��֤����Ա��¼��Ϣ
    if (username == "admin" && password == "admin123")
    {
        cout << "����Ա��¼�ɹ���" << endl;
        show_menu_admin();
    }
    else
    {
        cout << "����Ա��¼ʧ�ܣ�" << endl;
    }
}
void login_teacher()
{
    string username, password;
    cout << "�������ʦ�û���: ";
    cin >> username;
    cout << "�������ʦ����: ";
    cin >> password;
    // ��֤��ʦ��¼��Ϣ
    if (username == "teacher" && password == "teacher123")
    {
        cout << "��ʦ��¼�ɹ���" << endl;
        show_menu_teacher();
    }
    else
    {
        cout << "��ʦ��¼ʧ�ܣ�" << endl;
    }
}
void show_menu1()
{
    cout << "================== ������Ϣ����ϵͳ ==================" << endl;
    cout << "1. ����Ա¼��ѧ����Ϣ" << endl;
    cout << "2. ����Ա¼��γ���Ϣ" << endl;
    cout << "3. ѧ��ѡ��" << endl;
    cout << "4. ��ʦ¼��ѧ���ɼ�" << endl;
    cout << "5. ѧ����ѯ���Ƴɼ�" << endl;
    cout << "6. ����ͳ��ѧ��ѡ����������Գɼ�" << endl;
    cout << "7. ���γ�ͳ��ѧ�����������Գɼ�" << endl;
    cout << "8. ͳ�Ʋ����ÿ��ͬѧ����ѧ�ּ�������γ�" << endl;
    cout << "9. �˳�" << endl;
    cout << "====================================================" << endl;
    cout << "���������ѡ��: ";
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