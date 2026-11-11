#include <iostream>
#include <vector>
#include <string>

#include <algorithm>
#include <random>
#include <cctype>

bool PaswrdNorm(const std::vector<char>& pwd) {
    if (pwd.size() <= 6) return false;

    bool hasLower = false, hasUpper = false, hasDigit = false, hasSpecial = false;
    bool allIdentical = true;

    if (!pwd.empty()) {
        char firstChar = pwd[0];
        for (char c : pwd) {
            if (c != firstChar) allIdentical = false;
            if (std::islower(c)) hasLower = true;
            else if (std::isupper(c)) hasUpper = true;
            else if (std::isdigit(c)) hasDigit = true;
            else hasSpecial = true;
        }
    }

    if (allIdentical) return false;
    if (hasLower && !hasUpper && !hasDigit && !hasSpecial) return false;
    if (!hasLower && hasUpper && !hasDigit && !hasSpecial) return false;
    if (!hasLower && !hasUpper && hasDigit && !hasSpecial) return false;

    return (hasLower && hasUpper && hasDigit && hasSpecial);
}

std::vector<char> generateStrongPassword() {
    std::string lower = "abcdefghijklmnopqrstuvwxyz";
    std::string upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string digits = "0123456789";
    std::string specials = "!@#$%^&*()_+-=[]{}|;:,.<>?";

    std::random_device rd;
    std::mt19937 gen(rd());

    std::vector<char> pwd;
    pwd.push_back(lower[gen() % lower.size()]);
    pwd.push_back(upper[gen() % upper.size()]);
    pwd.push_back(digits[gen() % digits.size()]);
    pwd.push_back(specials[gen() % specials.size()]);

    std::string allChars = lower + upper + digits + specials;
    for (int i = 0; i < 6; ++i) {
        pwd.push_back(allChars[gen() % allChars.size()]);
    }

    std::shuffle(pwd.begin(), pwd.end(), gen);
    return pwd;
}

int main2() {
    std::string inputStr;
    std::cout << "Пароль: ";
    std::cin >> inputStr;

    std::vector<char> password(inputStr.begin(), inputStr.end());

    if (PaswrdNorm(password)) {
        std::cout << "Надійно\n";
    } else {
        std::cout << "Ненадійний\n";
        std::vector<char> newPassword = generateStrongPassword();
        std::cout << "Новий парольчик: ";
        for (char c : newPassword) std::cout << c;
        std::cout << "\n";
    }

    return 0;
}
