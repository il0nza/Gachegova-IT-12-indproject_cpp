#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "game_header.h"

int main() {
	setlocale(LC_ALL, "Russian");
	bool run = true;
	bool skipMenu = false;
	while (run) {
		std::vector<char> theBoard(10, ' ');
		char currentTurn;
		bool gameIsPlaying = true;
		bool backToMenu = false;
		if (skipMenu) {
			char choiceLetter = ' ';
			while (choiceLetter != 'X' && choiceLetter != 'O') {
				std::cout << "Новая игра! Выберите ваш символ (X или O): ";
				std::cin >> choiceLetter;
				choiceLetter = toupper(choiceLetter);
			}
			currentTurn = choiceLetter;
			skipMenu = false;
		}
		else {
			menu(theBoard, currentTurn, gameIsPlaying, run);
		}

		while (gameIsPlaying) {
			drawBoard(theBoard);
			std::cout << "Сейчас ходит: '" << currentTurn << "'" << std::endl;
			std::cout << "Введите номер клетки (1-9), '0' - сохранить, '-1' - вернуться в меню: ";
			int move;
			std::cin >> move;

			if (std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "\nОшибка! Введите число.\nНажмите Enter...";
				std::cin.get();
				continue;
			}
			
			if (move == 0) {
				saveGame(theBoard, currentTurn);
				continue;
			}
			if (move == -1) {
				backToMenu = true;
				gameIsPlaying = false;
				system("cls || clear");
				continue;
			}

			if (move >= 1 && move <= 9 && theBoard[move] == ' ') {
				theBoard[move] = currentTurn;

				if (isWinner(theBoard, currentTurn)) {
					drawBoard(theBoard);
					std::cout << "ПОБЕДА! Игрок '" << currentTurn << "' выиграл!" << std::endl;
					gameIsPlaying = false;
				}
				else if (isBoardFull(theBoard)) {
					drawBoard(theBoard);
					std::cout << "НИЧЬЯ!" << std::endl;
					gameIsPlaying = false;
				}
				else {
					currentTurn = (currentTurn == 'X') ? 'O' : 'X';
				}
			}
			else {
				std::cout << "\nОшибка! Клетка занята или введено неверное число." << std::endl;
				std::cout << "Нажмите Enter, чтобы продолжить...";
				std::cin.ignore();
				std::cin.get();
			}
		}
		if (!backToMenu && run) {
			playAgain(run, skipMenu);
		}
	}
}