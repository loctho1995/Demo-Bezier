#include "TestScene.h"

/*
bam phim d: de hien/an cac duong line noi cac diem (control points)
bam phim h: de an/hien tat ca (tru sprite arrow)
bam phim m: de dung chuot bam vao man hinh
bam phim b: de ve duong cong bezier

bam numberpad1: de ve bezier bac 2
bam numberpad2: de ve bezier bac 3
bam numberpad3: de ve bezier bac 4
bam numberpad4: de ve bezier bac 12
bam +: de tang toc do
bam -: de giam toc do


*/

TestScene::TestScene()
{
    this->mBackColor = 0x54acd2;
}


TestScene::~TestScene()
{
}


void TestScene::LoadContent()
{
    debugDraw = new GameDebugDraw(GameGlobal::GetCurrentSpriteHandler());
    drawBezier = new GameDebugDraw(GameGlobal::GetCurrentSpriteHandler());
    drawBezier->setLineSize(1.6f);
    debugDraw->setLineSize(3);

    speed = 1.0;
    t = 0;
    frameDelay = 0;
    numSprite = 10;
    xDistance = yDistance = 0;
    dotDistance = 0;
    dotDistanceCounter = 0;
    indexPointClicked = -1;
    isPause = false;
    isDebugDraw = false;
    isUseMouse = false;
    isDrawBezier = false;
    isMouseDown = false;

    dot = new Sprite("dot.png");
    dot2 = new Sprite("dot2.png");

    //khoi tao cac control point - bezier bac 2
    points.push_back(D3DXVECTOR2(100, 100));
    points.push_back(D3DXVECTOR2(400, 300));
    points.push_back(D3DXVECTOR2(200, 600));

    updateFullPoints();

    sprites = new Sprite("test.png");

    previousPoint = CalculateSinglePoint(0, points);
}

void TestScene::Update(float dt)
{
    if (isPause)
        return;

    if (currentFrame > frameDelay)
    {
        currentFrame = 0;
    }
    else
    {
        currentFrame++;
        return;
    }

    if (t > 1)
    {
        t = 0;
        savePoints.clear();
    } 
    else
    {
        t += 0.01f * speed;

        D3DXVECTOR2 vec = CalculateSinglePoint(t, points);

        //tinh toan de xoay sprite
        D3DXVECTOR2 dir = vec - previousPoint;     
        D3DXVec2Normalize(&dir, &dir);

        sprites->SetRotation(acos(dir.x) * (abs(dir.y) / dir.y));

        //GAMELOG("x: %f ; y: %f ; rotation: %f", dir.x, dir.y, D3DXToDegree(sprite->GetRotation()));

        sprites->SetPosition(D3DXVECTOR3(vec.x + 0 * xDistance, vec.y + 0 * yDistance, 0));

        previousPoint = vec;

        //them vi tri ve dot tren man hinh
        if (dotDistanceCounter > dotDistance)
        {
            dotDistanceCounter = 0;
            savePoints.push_back(vec);
        }
        else
        {
            dotDistanceCounter++;
        }
        //GAMELOG("x: %f ; y: %f", sprite->GetPosition().x, sprite->GetPosition().y);
    }    
}

void TestScene::Draw()
{
    if (isDebugDraw)
        debugDraw->DrawLine(&points[0], points.size());

    sprites->Draw();

    if (isDrawBezier)
    {
        if (fullPoints.size() >= 2)
            drawBezier->DrawLine(&fullPoints[0], fullPoints.size());
    }

    if (!isHideAll)
    {
        for (size_t i = 0; i < savePoints.size(); i++)
        {
            D3DXVECTOR3 pos = D3DXVECTOR3(savePoints.at(i).x, savePoints.at(i).y, 0);
            dot->Draw(pos);
        }
    }
    
    if (!isHideAll)
    {
        for (size_t i = 0; i < points.size(); i++)
        {
            D3DXVECTOR3 pos = D3DXVECTOR3(points.at(i).x, points.at(i).y, 0);
            dot2->Draw(pos);
        }
    }
}

void TestScene::OnKeyDown(int keyCode)
{
    if (keyCode == DIK_SPACE)
        isPause = !isPause;

    if (keyCode == DIK_D)
        isDebugDraw = !isDebugDraw;

    if (keyCode == DIK_H)
        isHideAll = !isHideAll;

    if (keyCode == DIK_M)
    {
        isUseMouse = !isUseMouse;
        points.clear();
    }

    if (keyCode == DIK_B)
    {
        isDrawBezier = !isDrawBezier;
    }
        

    //chay bezier bac 2
    if (keyCode == DIK_NUMPAD1)
    {
        points.clear();
        savePoints.clear();
        t = 0;

        points.push_back(D3DXVECTOR2(100, 100));
        points.push_back(D3DXVECTOR2(400, 300));
        points.push_back(D3DXVECTOR2(200, 600));

        updateFullPoints();
    }

    //chay bezier bac 3
    if (keyCode == DIK_NUMPAD2)
    {
        points.clear();
        savePoints.clear();
        t = 0;

        points.push_back(D3DXVECTOR2(100, 100));
        points.push_back(D3DXVECTOR2(400, 200));
        points.push_back(D3DXVECTOR2(200, 400));
        points.push_back(D3DXVECTOR2(500, 600));

        updateFullPoints();
    }

    //chay bezier bac 4
    if (keyCode == DIK_NUMPAD3)
    {
        points.clear();
        savePoints.clear();
        t = 0;

        points.push_back(D3DXVECTOR2(100, 100));
        points.push_back(D3DXVECTOR2(400, 200));
        points.push_back(D3DXVECTOR2(200, 400));
        points.push_back(D3DXVECTOR2(400, 600));
        points.push_back(D3DXVECTOR2(650, 250));

        updateFullPoints();
    }

    //bac 12
    if (keyCode == DIK_NUMPAD4)
    {
        points.clear();
        savePoints.clear();
        t = 0;

        points.push_back(D3DXVECTOR2(0, 0));
        points.push_back(D3DXVECTOR2(300, 80));
        points.push_back(D3DXVECTOR2(450, 150));
        points.push_back(D3DXVECTOR2(200, 200));
        points.push_back(D3DXVECTOR2(10, 250));
        points.push_back(D3DXVECTOR2(50, 350));
        points.push_back(D3DXVECTOR2(300, 450));
        points.push_back(D3DXVECTOR2(350, 250));
        points.push_back(D3DXVECTOR2(850, 150));
        points.push_back(D3DXVECTOR2(600, 350));
        points.push_back(D3DXVECTOR2(400, 450));
        points.push_back(D3DXVECTOR2(150, 650));
        points.push_back(D3DXVECTOR2(900, 680));

        updateFullPoints();
    }

    if (keyCode == DIK_ADD)
    {
        speed += 0.1f;         
        
    }

    if (keyCode == DIK_SUBTRACT)
    {
        speed -= 0.1f;

        if (speed <= 0)
            speed = 0.1f;
    }

    GAMELOG("speed: %f", speed);
}

void TestScene::OnKeyUp(int keyCode)
{

}

void TestScene::OnMouseDown(float x, float y)
{
    isMouseDown = true;

    for (size_t i = 0; i < points.size(); i++)
    {
        if (isClickOnNode(x, y, points.at(i)))
        {
            indexPointClicked = i;
            return;
        }
    }

    indexPointClicked = -1;

    if (!isUseMouse)
        return;

    points.push_back(D3DXVECTOR2(x, y));
    savePoints.clear();

    sprites->SetPosition(points.at(0));

    updateFullPoints();
}

void TestScene::OnMouseUp(float x, float y)
{
    isMouseDown = false;
}

void TestScene::OnMouseMove(float x, float y)
{
    if (isMouseDown && indexPointClicked != -1)
    {
        points[indexPointClicked] = D3DXVECTOR2(x, y);
        updateFullPoints();
    }
}

bool TestScene::isClickOnNode(float x, float y, D3DXVECTOR2 point)
{
    float nodeWidth = 15.0f / 2;
    float nodeHeight = 15.0f / 2;

    if (x < point.x - nodeWidth || x > point.x + nodeWidth || y < point.y - nodeHeight || y >point.y > nodeHeight)
    {
        return false;
    }

    return true;
}

void TestScene::updateFullPoints()
{
    fullPoints.clear();

    for (float x = 0.01; x <= 1; x += 0.01f)
    {
        fullPoints.push_back(CalculateSinglePoint(x, points));
    }
}

//tinh giai thua
unsigned int TestScene::Factorial(int n)
{
    unsigned int retval = 1;

    for (int i = n; i > 1; --i)
        retval *= i;

    return retval;
}

//tinh toan he so (cua tam giac pascal)
unsigned int TestScene::CalculateCoefficient(int n, int i)
{
    return Factorial(n) / (Factorial(i) * Factorial(n - i));
}

//lay diem tuong ung
D3DXVECTOR2 TestScene::CalculateSinglePoint(float t, std::vector< D3DXVECTOR2 > pointVector)
{
    int n = pointVector.size() - 1;
    D3DXVECTOR2 result(0, 0);

    for (int i = 0; i <= n; i++)
    {
        D3DXVECTOR2 temp = pointVector.at(i);
        float coefficient = CalculateCoefficient(n, i) * pow(1 - t, n - i) * pow(t, i);
        float x = coefficient * temp.x;
        float y = coefficient * temp.y;
        result = result + D3DXVECTOR2(x, y);
    }

    return result;
}
