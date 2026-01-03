void drawBoard(const std::vector<char>& board);
bool isWinner(const std::vector<char>& bo, char le);
bool isBoardFull(const std::vector<char>& board);
void saveGame(const std::vector<char>& board, char turn);
bool loadGame(std::vector<char>& board, char& turn);
void rules();
void menu(std::vector<char>& theBoard, char& currentTurn, bool& gameIsPlaying, bool& run);
void playAgain(bool& run, bool& skipMenu);