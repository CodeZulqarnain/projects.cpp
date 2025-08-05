#include <iostream>
#include <conio.h>
#include <windows.h>
#include <list>
#include <utility>

using namespace std;

// Game settings
const int WIDTH = 40;
const int HEIGHT = 20;
enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };

class SnakeGame {
public:
    SnakeGame()
      : dir(STOP), score(0), delay(150), gameOver(false) {
        Reset();
    }

    void Reset(){
        snake.clear();
        snake.emplace_back(WIDTH/2, HEIGHT/2);
        PlaceFruit();
        dir = STOP;
        score = 0;
        delay = 150;
        gameOver = false;
    }

    void Draw(){
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0,0});
        // top wall
        for(int i=0;i<WIDTH+2;i++) cout << '#';
        cout << "\n";

        for(int y=0;y<HEIGHT; y++){
            cout << '#';
            for(int x=0;x<WIDTH; x++){
                if (x==snake.front().first && y==snake.front().second) {
                    cout << 'O';
                } else if(x==fruitX && y==fruitY) {
                    cout << '*';
                } else {
                    bool printed=false;
                    for(auto it = next(snake.begin()); it!=snake.end(); ++it){
                        if(it->first==x && it->second==y){
                            cout << 'o';
                            printed=true;
                            break;
                        }
                    }
                    cout << (printed ? "" : " ");
                }
            }
            cout << "#\n";
        }
        for(int i=0;i<WIDTH+2;i++) cout << '#';
        cout << "\nScore: " << score << "  (Q=Quit, R=Restart)\n";
    }

    void Input(){
        if (_kbhit()){
            switch (_getch()){
                case 'a': case 'A': if(dir!=RIGHT) dir=LEFT; break;
                case 'd': case 'D': if(dir!=LEFT) dir=RIGHT; break;
                case 'w': case 'W': if(dir!=DOWN) dir=UP; break;
                case 's': case 'S': if(dir!=UP) dir=DOWN; break;
                case 'q': case 'Q': gameOver=true; break;
                case 'r': case 'R': Reset(); break;
            }
        }
    }

    void Logic(){
        auto head = snake.front();
        int nx = head.first, ny = head.second;
        switch(dir){
            case LEFT:  nx--; break;
            case RIGHT: nx++; break;
            case UP:    ny--; break;
            case DOWN:  ny++; break;
            default: return;
        }
        // screen wrapping
        if(nx<0) nx = WIDTH-1;
        else if(nx>=WIDTH) nx = 0;
        if(ny<0) ny = HEIGHT-1;
        else if(ny>=HEIGHT) ny = 0;

        // self collision
        for(auto &seg: snake){
            if(seg.first==nx && seg.second==ny){
                gameOver = true;
                return;
            }
        }

        snake.emplace_front(nx, ny);

        if(nx==fruitX && ny==fruitY){
            score += 5;
            PlaceFruit();
            if(delay>50) delay -= 5; // speed up
        } else {
            snake.pop_back();
        }
    }

    void Run(){
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO sbInfo;
        GetConsoleScreenBufferInfo(hOut, &sbInfo);
        COORD topLeft = {0,0};
        SetConsoleCursorPosition(hOut, topLeft);

        while(!gameOver){
            Draw();
            Input();
            Logic();
            Sleep(delay);
        }
        cout << "\nGame Over! Final Score: " << score << "\nPress R to restart or Q to quit.\n";

        // wait for R or Q
        while(true){
            if(_kbhit()){
                char c = _getch();
                if(c=='r' || c=='R'){ Reset(); Run(); return; }
                if(c=='q' || c=='Q') return;
            }
        }
    }

private:
    list<pair<int,int>> snake;
    int fruitX{}, fruitY{};
    Direction dir;
    int score;
    int delay;
    bool gameOver;

    void PlaceFruit(){
        fruitX = rand()%WIDTH;
        fruitY = rand()%HEIGHT;
        // ensure not on snake
        for(auto &seg: snake){
            if(seg.first==fruitX && seg.second==fruitY){
                PlaceFruit();
                return;
            }
        }
    }
};

int main(){
    srand((unsigned)(NULL));
    SnakeGame game;
    game.Run();
    return 0;
}
