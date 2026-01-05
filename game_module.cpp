#include <iostream>
#include <vector>
#include <string>
#include <fstream>

// отрисовка поля
void drawBoard(const std::vector<char>& board) {
	system("clear || cls");
	std::cout << "--- Крестики-Нолики ---" << std::endl;
	std::cout << " " << board[7] << " | " << board[8] << " | " << board[9] << std::endl;
	std::cout << "-----------" << std::endl;
	std::cout << " " << board[4] << " | " << board[5] << " | " << board[6] << std::endl;
	std::cout << "-----------" << std::endl;
	std::cout << " " << board[1] << " | " << board[2] << " | " << board[3] << std::endl;
}

// проверка победителя
bool isWinner(const std::vector<char>& bo, char le) {
	return ((bo[7] == le && bo[8] == le && bo[9] == le) ||
		(bo[4] == le && bo[5] == le && bo[6] == le) ||
		(bo[1] == le && bo[2] == le && bo[3] == le) ||
		(bo[7] == le && bo[4] == le && bo[1] == le) ||
		(bo[8] == le && bo[5] == le && bo[2] == le) ||
		(bo[9] == le && bo[6] == le && bo[3] == le) ||
		(bo[7] == le && bo[5] == le && bo[3] == le) ||
		(bo[9] == le && bo[5] == le && bo[1] == le));
}

// заполнено ли поле?
bool isBoardFull(const std::vector<char>& board) {
	for (int i = 1; i <= 9; i++) {
		if (board[i] == ' ') {
			return false;
		}
	}
	return true;
}

// сохранение
void saveGame(const std::vector<char>& board, char turn) {
	std::ofstream file("savegame.txt");
	if (file.is_open()) {
		file << turn << std::endl;
		for (int i = 1; i <= 9; i++) {
			file << (board[i] == ' ' ? '.' : board[i]);
		}
		file.close();
		std::cout << "\nИгра сохранена в savegame.txt!" << std::endl;
		std::cout << "Нажмите Enter, чтобы продолжить...";
		std::cin.ignore();
		std::cin.get();
	}
}

// загрузка
bool loadGame(std::vector<char>& board, char& turn) {
	std::ifstream file("savegame.txt");
	if (file.is_open()) {
		file >> turn;
		std::string bStr;
		file >> bStr;
		for (int i = 0; i < 9; i++) {
			board[i + 1] = (bStr[i] == '.' ? ' ' : bStr[i]);
		}
		file.close();
		return true;
	}
	return false;
}

void rules() {
	system("clear || cls");
	std::cout << "Инструкция по игре «Крестики-Нолики» для двух игроков\n" << std::endl;
	std::cout << "В начале вам будет предложено четыре варианта:\n1.Новая игра — начать матч с пустого поля\n2.Загрузить игру — восстановить последнюю сохраненную партию из файла savegame.txt\n3.Ознакомиться с правилами игры\n4.Выход\n" << std::endl;
	std::cout << "Если вы выбрали «Новую игру», Игрок 1 должен выбрать свой символ : X(крестик) или O(нолик).\nВторой игрок автоматически получает оставшийся символ.\nПоле представлено в виде сетки 3x3, где каждая клетка соответствует цифре от 1 до 9:\n";
	std::cout << " 7 | 8 | 9 \n";
	std::cout << "-----------\n";
	std::cout << " 4 | 5 | 6 \n";
	std::cout << "-----------\n";
	std::cout << " 1 | 2 | 3 \n";
	std::cout << "Чтобы сделать ход, введите цифру от 1 до 9 и нажмите Enter.\nЧтобы сохранить текущий прогресс и продолжить позже, введите 0.\nЧтобы вернуться в меню, введите - 1.\n" << std::endl;
	std::cout << "Правила игры\n";
	std::cout << "Цель : Первым выстроить три своих символа в ряд(по горизонтали, вертикали или диагонали).\nХоды : Игроки ходят по очереди.Нельзя ставить символ в уже занятую клетку.\nПобеда : Как только один из игроков выстроил линию, игра завершается объявлением победителя.\nНичья : Если все клетки заполнены, а линии не образованы, объявляется ничья.\n" << std::endl;
	std::cout << "После окончания партии программа спросит: «Хотите сыграть еще раз?».\nВведите 1, чтобы начать новую игру, 2, чтобы вернуться в меню, 3, чтобы завершить игру.\n";
	std::cout << "\nНажмите Enter, чтобы продолжить...";
	std::cin.ignore();
	std::cin.get();
	system("clear || cls");
	std::cout << "1. Новая игра\n2. Загрузить сохраненную игру\n3. Ознакомиться с правилами\n4. Выход\nВыберите вариант: ";
}

void menu(std::vector<char>& theBoard, char& currentTurn, bool& gameIsPlaying, bool& run) {
	std::string choice = "0";
	std::cout << "1. Новая игра\n2. Загрузить сохраненную игру\n3. Ознакомиться с правилами\n4. Выход\nВыберите вариант: ";
	while (choice != "1" && choice != "2") {
		std::cin >> choice;
		if (choice != "1" && choice != "2" && choice != "3" && choice != "4") {
			std::cout << "Некорректный ввод. Попробуйте снова." << "\n";
		}
		if (choice == "3") {
			rules();
			choice = "0";
		}
		if (choice == "4") {
			std::cout << "\nСпасибо за игру!\n";
			std::cout << "Выход из программы..." << std::endl;
			run = false;
			gameIsPlaying = false;
			return;
		}
		if (choice == "2") {
			if (!loadGame(theBoard, currentTurn)) {
				std::cout << "\nФайл сохранения не найден! Начинаем новую игру.\n";
				choice = "1";
			}
		}
		if (choice == "1") {
			char choiceLetter = ' ';
			while (choiceLetter != 'X' && choiceLetter != 'O') {
				std::cout << "\nИгрок 1, выберите символ (X или O): ";
				std::string input;
				std::cin >> input;
				if (input.length() == 1) {
					choiceLetter = toupper(input[0]);
				}
				else {
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}
			}
			currentTurn = choiceLetter;
		}
	}
}

void playAgain(bool& run, bool& skipMenu) {
	std::string again = "0";
	std::cout << "\nХотите сыграть еще раз? \n1. Да (Начать новую партию) \n2. Нет (Выйти в меню)\n3. Закрыть программу\nВыберите вариант: ";
	while (again != "1" && again != "2" && again != "3") {
		std::cin >> again;
		if (again != "1" && again != "2" && again != "3") {
			std::cout << "Некорректный ввод. Попробуйте снова." << "\n";
		}
		if (again == "1") {
			skipMenu = true;
			std::cout << "\nНачинаем новую игру!\n";
			std::cout << "Нажмите Enter, чтобы продолжить...";
			std::cin.ignore();
			std::cin.get();
			system("clear || cls");
		}
		else if (again == "2") {
			skipMenu = false;
			system("clear || cls");
		}
		else if (again == "3") {
			run = false;
			std::cout << "Спасибо за игру!\n";
		}
	}
}