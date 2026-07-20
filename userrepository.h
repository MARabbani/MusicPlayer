// در فایل userrepository.h
#pragma once
#include <unordered_map>
#include <string>
#include <fstream>
#include <sstream>
#include "user.h" // فرض بر این است که کلاس یا استراکت User اینجاست

class UserRepository {
private:
    std::unordered_map<int, User> users;
    int nextId = 1;
    const std::string filename = "users_data.txt"; // نام فایل

    void loadFromFile(); // تابع خواندن
    void saveToFile();   // تابع نوشتن

public:
    UserRepository();
    ~UserRepository();

    // بقیه متدهای شما (مثل add, get, ...)
};
