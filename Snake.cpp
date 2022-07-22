#include <conio.h>
#include <direct.h>
#include <iostream>
#include <time.h>
#include <windows.h>

#define MAXSNAKESIZE 100

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

void goToXY(int x, int y)
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}

class Point
{
	int m_x{};
	int m_y{};

public:
	Point()
	{
		m_x = m_y = 10;
	} 
	Point(int x, int y)
	{
		this->m_x = x;
		this->m_y = y;
	}

	void setPoint(int x, int y)
	{
		this->m_x = x;
		this->m_y = y;
	}

	int getX() {return m_x;}
	int getY() {return m_y;}

	void moveUp() {m_y--;}
	void moveDown() {m_y++;}
	void moveLeft() {m_x--;}
	void moveRight() {m_x++;}

	void draw()
	{
		goToXY(m_x, m_y);
		std::cout << "*";
	}
	void erase()
	{
		goToXY(m_x, m_y);
		std::cout << " ";
	}
	void copyPos(Point* p)
	{
		p->m_x = m_x;
		p->m_y = m_y;
	}
	void debug()
	{
		std::cout << "(" << m_x << "," << m_y << ") ";
	}
};

class Snake
{
	Point* m_cell[MAXSNAKESIZE]; // array of points to represent snake
	int m_size; // current size of snake
	char m_dir; // current direction of snake
	Point m_fruit;

public:
	Snake()
	{
		m_size = 1; // default size
		m_cell[0] = new Point(20,20); // 20,20 is default position
		for(int i=1; i<MAXSNAKESIZE; i++)
		{
			m_cell[i] = NULL;
		}
		m_fruit.setPoint(rand()%50, rand()%25); 
	}

	void addCell(int x, int y)
	{
		m_cell[m_size++] = new Point(x,y);
	}

	void turnUp()
	{
		m_dir = 'w'; // w is control key for turning upward
	}
	void turnDown()
	{
		m_dir = 's'; // w is control key for turning downward
	}
	void turnLeft()
	{
		m_dir = 'a'; // w is control key for turning left
	}
	void turnRight()
	{
		m_dir = 'd'; // w is control key for turning right
	}

	void move()
	{
		// Clear screen
		system("cls");
		
		// making snake body follow its head
		for(int i=m_size-1; i>0; i--)
		{
			m_cell[i-1]->copyPos(m_cell[i]);
		}
		
		// turning snake's head
		switch(m_dir)
		{
			case 'w':
				m_cell[0]->moveUp();
				break;
			case 's':
				m_cell[0]->moveDown();
				break;
			case 'a':
				m_cell[0]->moveLeft();
				break;
			case 'd':
				m_cell[0]->moveRight();
				break;
		}
		
		// Collision with fruit
		if(m_fruit.getX() == m_cell[0]->getX() && m_fruit.getY() == m_cell[0]->getY())
		{
			addCell(0,0);
			m_fruit.setPoint(rand()%50, rand()%25); 	
		}
		
		//drawing snake
		for(int i=0; i<m_size; i++)
			m_cell[i]->draw();
		m_fruit.draw();
		
		//debug();
		
		Sleep(100);
	}
	void debug()
	{
		for( int i=0; i<m_size; i++)
		{
			m_cell[i]->debug();
		}
	}
};

int main()
{
	//random no generation
	srand((unsigned)time(NULL));
	
	// Testing snake 
	Snake snake;
	char op = 'l';
	do
	{
		if(kbhit())
		{
			op = getch();
		}
		switch(op)
		{
			case 'w':
			case 'W':
				snake.turnUp();
				break;
			
			case 's':
			case 'S':
				snake.turnDown();
				break;
			
			case 'a':
			case 'A':
				snake.turnLeft();
				break;
			
			case 'd':
			case 'D':
				snake.turnRight();
				break;
		}
		snake.move();
	} while(op != 'e');
	
	return 0;
}

// THE END
