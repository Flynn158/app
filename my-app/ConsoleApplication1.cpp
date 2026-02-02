#include <windows.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <conio.h>

using namespace std;

struct Task {
    int id;
    string description;
    bool completed;
};

class TaskManager {
private:
    vector<Task> tasks;
    string filename = "tasks.txt";
    int nextId = 1;

    void SetConsoleColor(int color) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, color);
    }

public:
    TaskManager() {
        LoadTasks();
    }

    ~TaskManager() {
        SaveTasks();
    }

    void LoadTasks() {
        ifstream file(filename);
        if (file.is_open()) {
            Task task;
            while (file >> task.id >> task.completed) {
                file.ignore();
                getline(file, task.description);
                tasks.push_back(task);
                if (task.id >= nextId) nextId = task.id + 1;
            }
            file.close();
        }
    }

    void SaveTasks() {
        ofstream file(filename);
        if (file.is_open()) {
            for (const auto& task : tasks) {
                file << task.id << " " << task.completed << " "
                    << task.description << endl;
            }
            file.close();
        }
    }

    void AddTask() {
        Task task;
        task.id = nextId++;

        SetConsoleColor(14);
        cout << "Введите описание задачи: ";
        SetConsoleColor(7); 

        cin.ignore();
        getline(cin, task.description);

        task.completed = false;
        tasks.push_back(task);

        SetConsoleColor(10); 
        cout << "Задача добавлена! ID: " << task.id << endl;
        SetConsoleColor(7);
    }

    void ShowTasks() {
        if (tasks.empty()) {
            SetConsoleColor(12); 
            cout << "Список задач пуст!" << endl;
            SetConsoleColor(7);
            return;
        }

        SetConsoleColor(11); 
        cout << "\n=== СПИСОК ЗАДАЧ ===" << endl;

        for (const auto& task : tasks) {
            if (task.completed) {
                SetConsoleColor(8); 
                cout << "[✓] ";
            }
            else {
                SetConsoleColor(15); 
                cout << "[ ] ";
            }
            cout << task.id << ". " << task.description << endl;
        }
        SetConsoleColor(7);
    }

    void CompleteTask() {
        int id;
        cout << "Введите ID задачи для отметки выполнения: ";
        cin >> id;

        for (auto& task : tasks) {
            if (task.id == id) {
                task.completed = !task.completed;
                SetConsoleColor(task.completed ? 10 : 14);
                cout << "Задача " << (task.completed ? "выполнена!" : "возвращена в работу!") << endl;
                SetConsoleColor(7);
                return;
            }
        }

        SetConsoleColor(12);
        cout << "Задача не найдена!" << endl;
        SetConsoleColor(7);
    }

    void DeleteTask() {
        int id;
        cout << "Введите ID задачи для удаления: ";
        cin >> id;

        for (auto it = tasks.begin(); it != tasks.end(); ++it) {
            if (it->id == id) {
                tasks.erase(it);
                SetConsoleColor(12);
                cout << "Задача удалена!" << endl;
                SetConsoleColor(7);
                return;
            }
        }

        SetConsoleColor(12);
        cout << "Задача не найдена!" << endl;
        SetConsoleColor(7);
    }

    void ClearScreen() {
        system("cls");
    }
};

int main() {
    
    // кодировка для русского языка
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    TaskManager manager;
    int choice;

    do {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 14); 

        cout << "\n=== МЕНЕДЖЕР ЗАДАЧ ===" << endl;
        cout << "1. Показать задачи" << endl;
        cout << "2. Добавить задачу" << endl;
        cout << "3. Отметить выполнение" << endl;
        cout << "4. Удалить задачу" << endl;
        cout << "5. Очистить экран" << endl;
        cout << "0. Выход" << endl;
        cout << "Выберите действие: ";

        SetConsoleTextAttribute(hConsole, 15); 
        cin >> choice;

        switch (choice) {
        case 1:
            manager.ShowTasks();
            break;
        case 2:
            manager.AddTask();
            break;
        case 3:
            manager.CompleteTask();
            break;
        case 4:
            manager.DeleteTask();
            break;
        case 5:
            manager.ClearScreen();
            break;
        case 0:
            cout << "Выход..." << endl;
            break;
        default:
            SetConsoleTextAttribute(hConsole, 12); 
            cout << "Неверный выбор!" << endl;
            SetConsoleTextAttribute(hConsole, 7);
        }

    } while (choice != 0);

    return 0;
}