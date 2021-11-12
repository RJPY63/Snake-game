#include <iostream>
#include <stdlib.h>
#include <vector>
#include<Windows.h>
#include<time.h>
#include <string>
#include <fstream> 
#include<algorithm>

typedef std::basic_fstream<char> fstream;

struct snake {
    int length = 0;
    std::vector<std::vector<int>> position;
    bool isDead = false;
};

struct food {
    int x;
    int y;
    bool isEaten;
};

char c = 'd';

char A[10][10];
bool eat;

std::vector<int> highScoreArr;
int highScore = 0;



void initialization() {
    memset(A, ' ', sizeof A);
    for (int i = 1; i < 9; i++) {
        A[0][i] = '-';
    }
    for (int i = 1; i < 9; i++) {
        A[9][i] = '-';
    }
    for (int i = 0; i < 10; i++) {
        A[i][9] = '|';
    }
    for (int i = 0; i < 10; i++) {
        A[i][0] = '|';
    }
}
void alocate(struct food* foo, struct snake* Snake) {
    int flag;
    for (;;) {
        flag = 1;
        foo->x = rand() % (8 - 1) + 1;
        foo->y = rand() % (8 - 1) + 1;
        int len = Snake->length;
        for (auto x : Snake->position) {
            if (x[0] == foo->x && x[1] == foo->y) {
                flag = 0;
            }
        }
        if (flag)
            break;
    }
}



void update(struct food* foo, struct snake* Snake, char c) {
    int len = Snake->position.size();
    std::vector<int> prev = { Snake->position[0][0] ,Snake->position[0][1] };
    if (!foo->isEaten) {
        A[foo->x][foo->y] = 'O';
    }
    for (int i = 0; i < Snake->length; i++) {
        A[Snake->position[i][0]][Snake->position[i][1]] = ' ';

    }

    //For right movement

    if (c == 'a') {
        int l = (Snake->position[len - 1][1] - 1 < 1) ? 8 : Snake->position[len - 1][1] - 1;
        A[Snake->position[0][0]][Snake->position[0][1]] = ' ';

        for (int i = 0; i < Snake->length - 1; i++) {
            Snake->position[i] = Snake->position[i + 1];
        }
        Snake->position[len - 1][1] = l;

        for (int i = 0; i < Snake->length - 1; i++) {
            A[Snake->position[i][0]][Snake->position[i][1]] = 'x';
        }

    }
    //For left movement
    else if (c == 'd') {
        int l = (Snake->position[len - 1][1] + 1 >= 9) ? 1 : Snake->position[len - 1][1] + 1;
        A[Snake->position[0][0]][Snake->position[0][1]] = ' ';

        for (int i = 0; i < Snake->length - 1; i++) {
            Snake->position[i] = Snake->position[i + 1];
        }
        Snake->position[len - 1][1] = l;

        for (int i = 0; i < Snake->length; i++) {
            A[Snake->position[i][0]][Snake->position[i][1]] = 'x';
        }

    }
    //For upper movement
    else if (c == 'w') {
        int l = (Snake->position[len - 1][0] - 1 < 1) ? 8 : Snake->position[len - 1][0] - 1;
        A[Snake->position[0][0]][Snake->position[0][1]] = ' ';

        for (int i = 0; i < Snake->length - 1; i++) {
            Snake->position[i] = Snake->position[i + 1];
        }
        Snake->position[len - 1][0] = l;

        for (int i = 0; i < Snake->length; i++) {
            A[Snake->position[i][0]][Snake->position[i][1]] = 'x';
        }
    }
    // For down movement
    else if (c == 's') {
        int l = (Snake->position[len - 1][0] + 1 >= 9) ? 1 : Snake->position[len - 1][0] + 1;
        A[Snake->position[0][0]][Snake->position[0][1]] = ' ';

        for (int i = 0; i < Snake->length - 1; i++) {
            Snake->position[i] = Snake->position[i + 1];
        }
        Snake->position[len - 1][0] = l;

        for (int i = 0; i < Snake->length; i++) {
            A[Snake->position[i][0]][Snake->position[i][1]] = 'x';

        }
    }


    for (int i = 0; i < Snake->length; i++) {
        A[Snake->position[i][0]][Snake->position[i][1]] = 'x';

    }
    for (int i = 0; i < Snake->length - 1; i++) {
        if (Snake->position[i] == Snake->position[Snake->length - 1]) {
            Snake->isDead = true;
            return;
        }
    }

    if (foo->x == Snake->position[len - 1][0] && foo->y == Snake->position[len - 1][1]) {
        std::vector<int> p{ 2,0 };
        Snake->position.push_back(p);
        Snake->length++;
        highScore++;
        for (int i = Snake->length - 1; i > 0; i--) {
            Snake->position[i] = Snake->position[i - 1];
        }
        Snake->position[0] = prev;
        A[Snake->position[0][0]][Snake->position[0][1]] = 'x';
        foo->isEaten = true;

    }


}

void render(struct snake* Snake) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            std::cout << A[i][j];
        }
        std::cout << "\n";
    }

}
bool checkHighScore(int score) {
    if (score > highScoreArr[0]) {
        return true;
    }
    else return false;
}

int topten(int score) {
    int flag = 1;
    for (int i = 0; i < highScoreArr.size(); i++) {
        if (score > highScoreArr[i]) {
            flag = 0;
            break;
        }
    }
    if (flag) {
        return 0;
    }
    highScoreArr[9] = score;
    std::sort(highScoreArr.begin(), highScoreArr.end());
    std::reverse(highScoreArr.begin(), highScoreArr.end());
    for (int i = 0; i < highScoreArr.size(); i++) {
        if (score == highScoreArr[i]) {
            return i + 1;
        }
    }
}
void start() {
    initialization();
    highScore = 0;
    int fr = 1000 / 15;
    int t;
    struct snake Snake;
    Snake.length = 2;
    Snake.isDead = false;

    std::vector<std::vector<int>> a = { {1,1},{1,2} };
    for (int i = 0; i < 2; i++) {
        Snake.position.push_back(a[i]);
    }
    char prev;
    struct food foo;
    foo.isEaten = true;
    while (1) {
        t = clock();
        int l = 0;
        prev = c;
        if (GetAsyncKeyState('a') || (GetAsyncKeyState('A'))) {
            if (prev == 'd')
                c = 'd';
            else c = 'a';
        }
        else if (GetAsyncKeyState('d') || (GetAsyncKeyState('D'))) {
            if (prev == 'a')
                c = 'a';
            else c = 'd';
        }
        else if (GetAsyncKeyState('w') || (GetAsyncKeyState('W'))) {
            if (prev == 's')
                c = 's';
            else c = 'w';
        }
        else if (GetAsyncKeyState('s') || (GetAsyncKeyState('S'))) {
            if (prev == 'w')
                c = 'w';
            else c = 's';
        }
        else if (GetAsyncKeyState(VK_ESCAPE)) {
        	Snake.isDead = true;
        }

        if (foo.isEaten) {
            alocate(&foo, &Snake);
            foo.isEaten = false;
        }

		std::cout<<"Press w a s d fro control\n";
        update(&foo, &Snake, c);

        render(&Snake);
        if (Snake.isDead) {
            std::cout << "\nYou died\n";
            std::cout << " Your score is " << highScore << "\n";
            int a = topten(highScore);
            if (checkHighScore(highScore)) {
                std::cout << "Congrats it's a new high score\n";
            }
            else if (a) {

            }
            std::cout << "Press x to continue\n";
            while(getchar()!='x');
            return;
        }


        do {
            l = clock() - t;
        } while (l < fr);

        system("CLS");
    }
}

void Extract() {
    std::fstream file;
    int number_of_lines = 0;
    std::string line;
    file.open("highScore.txt", std::ios::in | std::ios::out);

    int  i = 0;
    while (file >> line)
        ++number_of_lines;
    file.close();
    file.open("highScore.txt", std::ios::in | std::ios::out);
    char buffer[256];
    if(number_of_lines == 0){
    	
    	while (i < 10){
    		
   			sprintf(buffer, "%d", highScoreArr[i]);
	        file << buffer << std::endl;
	        i++;
	    }
	    file.close();
		return ;
	
    	
	}
	
	int num;
	i=0;
    while (file>>line)
    {
        if (i == 10 || i >= number_of_lines) {
            break;
        }
        strcpy(buffer, line.c_str());
        
        num = atoi (buffer);
		highScoreArr[i] = num;
        i++;
    }
    
    file.close();
    std::sort(highScoreArr.begin(), highScoreArr.end());
    std::reverse(highScoreArr.begin(), highScoreArr.end());

}


void highScoreResult() {
    for (int i = 0; i < 10; i++) {
        std::cout << highScoreArr[i] << std::endl;
    }
    std::cout << std::endl;

}

void store() {
    std::ofstream ofs;
    ofs.open("highScore.txt", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
    std::fstream file;
    file.open("highScore.txt", std::ios::in | std::ios::out);

    int  i = 0;
    while (i < 10)
    {
        file << highScoreArr[i] << std::endl;
        i++;
    }
    file.close();
}


int main(){
	system("CLS");
	for(int i=0;i<10;i++){
		highScoreArr.push_back(0);
	}
    int state = 0;
    int prev_state = -1;
    int exit_status = 1;
    int nav = -1;
    int time;
    char c = ' ';
    Extract();
    char string[3][20] = { ">1. start", ".2. highscore", ".3. exit" };
    while (exit_status) {
        time = clock();
        if (prev_state != state || nav == 10) {
            for (int i = 0; i < 3; i++) {
                std::cout << string[i] << std::endl;
            }
            prev_state = state;
            nav=0;
        }
        
        
       if (c == ' ') {
       		if(nav != -1){
		        if ((GetAsyncKeyState(VK_UP) & 0x8000)) {
		            nav = 2;
		        }
		        else if ((GetAsyncKeyState(VK_DOWN) & 0x8000) ) {
		            nav = 1;
		        }
		        else if ((GetAsyncKeyState(VK_RETURN) & 0x8000 ) ) {
		            nav = 3;
		        }
			}
			else nav =0;
        }
        else c = ' ';
        

        //std::cout << nav << " "<<prev_state <<" "<< state<<" "<<nav<<std::endl;// << state << std::endl;
        if (nav == 1) {
            string[state][0] = '.';
            if (state == 2) {
                state = 0;
            }
            else state++;
            string[state][0] = '>';
            nav = 0;
        }
        else if (nav == 2) {
            string[state][0] = '.';
            if (state == 0) {
                state = 2;
            }
            else state--;
            string[state][0] = '>';
            nav = 0;
        }
        else if (nav == 3) {
            switch (state) {
            case 0: {
                system("CLS");
                start();
                c='a';
                store();
                system("CLS");
                break;
            }
            case 1: {
                system("CLS");
                printf("The high scores are:- \n");
                highScoreResult();
                printf("Press x to continue ...\n");

                while(std::getchar()!='x');
                c='a';
                system("CLS");
                break;
            }
            case 2: {
                printf("Thank you for playing");
                exit_status = 0;
            }
            }
            nav = 10;
        }
        if (exit_status == 1) {
            while (clock() - time < 300) {
                continue;
            }
            if (prev_state != state) {
                system("CLS");
            }
        }

    }



}

