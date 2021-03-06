// t2.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Brick.h"
#include "Input.h"
#include "Ball.h"

bool ComputeCollision(Ball *ball, Brick brick) 
{
	if (ball->ComputeCollision(brick.X(), brick.Y(), brick.Width(), brick.Height()))
	{
		if (ball->IsVertical(brick.X(), brick.Width()))
			ball->ReversalY();
		else
			ball->ReversalX();
		return true;
	}
	return false;
}

int main()
{
	int width = 640;
	int height = 480;
	initgraph(width, height);

	Ball ball(width*0.5, 449, 10, GREEN);
	ball.SetSpeed(5);

	int brickSpeed=30;
	Brick brick(width*0.5 - 50, 460, 100, 20, BLUE);
	
	std::vector<Brick*> bricks;
	for (int x = 0; x < 20; x++) 
	{
		for (int y = 0; y < 8; y++) {
			bricks.push_back(new Brick(x * 50, y * 30, 40, 20, BLUE));
		}
	}

	std::string gameEnd;
	std::vector<Brick*>::iterator it;
	while (true) 
	{
		ball.Move(0, width, 0);
		if (ball.Y() > height) {
			gameEnd.append("gameover!");
			break;
		}
		for(it = bricks.begin(); it!=bricks.end();it++)
			if (ComputeCollision(&ball, **it)) {	
				(*it)->Clear();
				bricks.erase(it);
				if (bricks.size() == 0)
				{
					gameEnd.append("victory!");
					goto end;
				}
				break;
			}
		ComputeCollision(&ball, brick);

		Input::Update();
		if (Input::GetKeyDown(KeyCode::Left)) {
			if(brick.X()>25)
				brick.move(brick.X() - brickSpeed, brick.Y());
		}
		else if (Input::GetKeyDown(KeyCode::Right)) {
			if (brick.X()<540)
			brick.move(brick.X() + brickSpeed, brick.Y());
		}
		Sleep(60);
	}
	closegraph();
end:
	printf("gameover!");
	getchar();
    return 0;
}

