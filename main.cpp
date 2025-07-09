#include <iostream>
#include <bitset>
#include <limits>
#include <vector>
#include <unordered_map>

const int INF = 1000;

std::bitset<9> xBoard;
std::bitset<9> oBoard;

void printBoard(std::bitset<9> xBoard, std::bitset<9> oBoard)
{
    for (int i = 0; i < 9; ++i)
    {
        if (xBoard[i] == 1) std::cout << "X";
        else if (oBoard[i] == 1) std::cout << "O";
        else std::cout << ".";
        if ((i + 1) % 3 == 0) std::cout << "\n";
        else std::cout << " ";
    }
}

bool movesToPlay(std::bitset<9> xBoard, std::bitset<9> oBoard)
{
    for (int i = 0; i < 9; ++i)
    {
        if (!xBoard[i] && !oBoard[i]) return true;
    }
    return false;
}
std::bitset<9> winPatterns[8] = 
{
    std::bitset<9> (0b111000000),
    std::bitset<9> (0b000111000),
    std::bitset<9> (0b000000111),
    std::bitset<9> (0b100100100),
    std::bitset<9> (0b010010010),
    std::bitset<9> (0b001001001),
    std::bitset<9> (0b100010001),
    std::bitset<9> (0b001010100),
};

char  defWinner(std::bitset<9> xBoard, std::bitset<9> oBoard)
{
    for (int i = 0; i < 8; ++i)
    {
        if ((xBoard & winPatterns[i]) == winPatterns[i]) return 'X';
        if ((oBoard & winPatterns[i]) == winPatterns[i]) return 'O';
    }
    return '.';
}

int evaluate(std::bitset<9> xBoard, std::bitset<9> oBoard)
{
    for (int i = 0; i < 8; ++i)
    {
        if ((xBoard & winPatterns[i]) == winPatterns[i]) return -1;
        if ((oBoard & winPatterns[i]) == winPatterns[i]) return 1;
    }
    return 0;
}

std::vector<int> getLegalMoves(std::bitset<9> xBoard, std::bitset<9> oBoard)
{
    std::vector<int> moves;
    for (int i = 0; i < 9; ++i)
    {
        if (!xBoard[i] && !oBoard[i])
        {
            moves.push_back(i);
        }
    }
    return moves;
}

int minimax (std::bitset<9> xBoard, std::bitset<9> oBoard, bool isOTurn)
{
    int score = evaluate(xBoard, oBoard);
    if (score != 0 || getLegalMoves(xBoard, oBoard).empty())
    {
        return score;
    }

    if (isOTurn)
    {
        int best = -2;
        for (int move : getLegalMoves(xBoard, oBoard))
        {
            std::bitset<9> newO = oBoard;
            newO.set(move);
            best = std::max(best, minimax(xBoard, newO, false));
        }
        return best;
    }
    
    else
    {
        int best = 2;
        for (int move : getLegalMoves(xBoard, oBoard))
        {
            std::bitset<9> newX = xBoard;
            newX.set(move);
            best = std::min(best, minimax(newX, oBoard, true));
        }
        return best;
    }
}

int findBestMove(std::bitset<9> xBoard, std::bitset<9> oBoard)
{
    int bestScore = -2;
    int bestMove = -1;

    for (int move : getLegalMoves(xBoard, oBoard))
    {
        std::bitset<9> newO = oBoard;
        newO.set(move);
        int score = minimax(xBoard, newO, false);
        if (score > bestScore)
        {
            bestScore = score;
            bestMove = move;
        }
    }
    return bestMove;
}

std::unordered_map<std::string, int> moveMap =
{
    {"topleft", 0}, {"top", 1}, {"topright", 2},
    {"left", 3}, {"center", 4}, {"right", 5},
    {"bottomleft", 6}, {"bottom", 7}, {"bottomright", 8}
};

int main()
{
    char winner = '.';

    while (true)
    {
        printBoard(xBoard, oBoard);

        std::string moveStr;
        std::cout << "Enter your move (X): ";
        std::cin >> moveStr;

        if (moveMap.find(moveStr) == moveMap.end())
        {
            std::cout << "Invalid move!\n";
            continue;
        }

        int move = moveMap[moveStr];

        if (xBoard[move] || oBoard[move])
        {
            std::cout << "Square is taken!\n";
            continue;
        }

        xBoard.set(move);

        winner = defWinner(xBoard, oBoard);
        if (winner == 'X')
        {
            printBoard(xBoard, oBoard);
            std::cout << "X wins!";
            break;
        }

        if (getLegalMoves(xBoard, oBoard).empty())
        {
            printBoard(xBoard, oBoard);
            std::cout << "Draw!";
            break;
        }

        int oMove = findBestMove(xBoard, oBoard);
        oBoard.set(oMove);

        winner = defWinner(xBoard, oBoard);
        if (winner == 'O')
        {
            printBoard(xBoard, oBoard);
            std::cout << "O wins!";
            break;
        }

        if (getLegalMoves(xBoard, oBoard).empty())
        {
            printBoard(xBoard, oBoard);
            std::cout << "Draw!";
            break;
        }
    }

    return 0;
}