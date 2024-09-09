#include <iostream>
#include <cstdlib>
#include <ctime>
#include <graphics.h> // 引入图形库头文件
#include <vector> // 添加头文件以支持 vector
#include <cstring>
using namespace std;
#define WINDOWDX 1
#define WIDTH 1544 // 屏幕宽度
#define HEIGHT 756 // 屏幕高度
#define SPEED 1    // 车辆移动速度
#define EMSPEED 30


bool yidong = 0;//判断车辆是否搭载溯源检测系统



// 定义车辆结构体
struct Car {
    int index; // 车辆索引
    int x;
    int y;
    int width;
    int height;
    IMAGE maskImage; // 控制掩码图像
    IMAGE originalImage; // 原图像
    int moveDistance; // 用于记录移动的距离
    bool isvirtual = false;
    bool isStronger = false;
    int emailcount = 0;
    int show = 0;
};
bool isSoureceShow = false;

// 定义信封结构体
struct Email {
    int x;
    int y;
    IMAGE emailmaskImage; // 控制掩码图像
    IMAGE emailoriginalImage; // 原图像
    int startingCarIndex; // 发起车辆的索引
    bool isMovingToYellowCar;
    int emailcount = 0;
};



//游戏页面小按钮结构体
struct smallbutton  //按钮的属性
{
    int x, y, r;   //坐标，半径
    COLORREF color;   //颜色
    char* str;        //按键上的字符
};
struct smallbutton* createSmallButton(int x, int y, int r, COLORREF color, const char* str)    //初始化按钮属性
{
    struct smallbutton* pa = (struct smallbutton*)malloc(sizeof(struct smallbutton));    //动态分配
    if (!pa)
        exit(-1);
    pa->x = x;   //用输入的xyr来初始化
    pa->y = y;
    pa->r = r;
    pa->color = color;
    pa->str = (char*)malloc(strlen(str) + 1);  //传过来的文字长度是可见长度，需加一
    if (!pa->str)
        exit(-1);
    strcpy_s(pa->str, strlen(str) + 1, str); //字符串拷贝
    return pa;
}




// 添加一个标志变量，用于跟踪是否按下了 "start" 按钮
int startClicked = 0;

// 修改 gameButtonDraw1 函数，只显示 start 按钮
void gameButtonDraw1(struct smallbutton* StrongerButton, struct smallbutton* clearButton, struct smallbutton* DwindowButton, struct smallbutton* windowButton, struct smallbutton* startButton,
    struct smallbutton* stopButton, int startClicked, struct smallbutton* sybilButton, struct smallbutton* sourceButton, struct smallbutton* sybilButton2) {
    BeginBatchDraw();

    // 绘制 start 按钮
    IMAGE img_start, img_startb;
    loadimage(&img_start, "./images/start.png");
    loadimage(&img_startb, "./images/startb.png");
    setfillcolor(startButton->color);
    solidcircle(startButton->x + 10, startButton->y + 10, startButton->r);
    setbkmode(TRANSPARENT);

    putimage(20, 20, &img_startb, SRCAND);
    putimage(20, 20, &img_start, SRCPAINT);
    outtextxy(startButton->x - 10, startButton->y + 35, "Attack!");

    // 仅当 start 被点击后才绘制 stop 按钮
    if (startClicked == 1) {
        IMAGE img_stop, img_stopb;
        loadimage(&img_stop, "./images/stop.png");
        loadimage(&img_stopb, "./images/stopb.png");
        setfillcolor(stopButton->color);
        solidcircle(stopButton->x + 10, stopButton->y + 10, stopButton->r);
        setbkmode(TRANSPARENT);
        putimage(80, 20, &img_stopb, SRCAND);
        putimage(80, 20, &img_stop, SRCPAINT);
        outtextxy(stopButton->x - 10, stopButton->y + 35, "SybilCar");

		//////////
        IMAGE img_sybil, img_sybilb;
        loadimage(&img_sybil, "./images/sybil.png");
        loadimage(&img_sybilb, "./images/sybilb.png");
        setfillcolor(sybilButton->color);
        solidcircle(sybilButton->x + 10, sybilButton->y + 10, sybilButton->r);
        setbkmode(TRANSPARENT);
        outtextxy(sybilButton->x - 10, sybilButton->y + 35, "Detect");

        putimage(140, 20, &img_sybilb, SRCAND);
        putimage(140, 20, &img_sybil, SRCPAINT);

		//////////
        IMAGE img_source, img_sourceb;
        loadimage(&img_source, "./images/window.png");
        loadimage(&img_sourceb, "./images/windowb.png");
        setfillcolor(sourceButton->color);
        solidcircle(sourceButton->x + 10, sourceButton->y + 10, sourceButton->r);
        setbkmode(TRANSPARENT);

        putimage(200, 20, &img_sourceb, SRCAND);
        putimage(200, 20, &img_source, SRCPAINT);
        outtextxy(sourceButton->x - 10, sourceButton->y + 35, "Increase");

        //////////
        IMAGE img_window, img_windowb;
        loadimage(&img_window, "./images/Dwindow.png");
        loadimage(&img_windowb, "./images/Dwindowb.png");
        setfillcolor(windowButton->color);
        solidcircle(windowButton->x + 10, windowButton->y + 10, windowButton->r);
        setbkmode(TRANSPARENT);

        putimage(260, 20, &img_windowb, SRCAND);
        putimage(260, 20, &img_window, SRCPAINT);
        outtextxy(windowButton->x - 10, windowButton->y + 35, "Reduce");

        //////////
        IMAGE img_Dwindow, img_Dwindowb;
        loadimage(&img_Dwindow, "./images/shift.jpg");
        loadimage(&img_Dwindowb, "./images/shiftb.jpg");
        setfillcolor(DwindowButton->color);
        solidcircle(DwindowButton->x + 10, DwindowButton->y + 10, DwindowButton->r);
        setbkmode(TRANSPARENT);

        putimage(320, 20, &img_Dwindowb, SRCAND);
        putimage(320, 20, &img_Dwindow, SRCPAINT);
        outtextxy(DwindowButton->x - 10, DwindowButton->y + 35, "Shift");

        //////////
        IMAGE img_clear, img_clearb;
        loadimage(&img_clear, "./images/clear.png");
        loadimage(&img_clearb, "./images/clearb.png");
        setfillcolor(clearButton->color);
        solidcircle(clearButton->x + 10, clearButton->y + 10, clearButton->r);
        setbkmode(TRANSPARENT);

        putimage(380, 20, &img_clearb, SRCAND);
        putimage(380, 20, &img_clear, SRCPAINT);
        outtextxy(clearButton->x - 10, clearButton->y + 35, "Clear");

        //////////
        IMAGE img_Stronger, img_Strongerb;
        loadimage(&img_Stronger, "./images/Stronger.png");
        loadimage(&img_Strongerb, "./images/Strongerb.png");
        setfillcolor(StrongerButton->color);
        solidcircle(StrongerButton->x + 10, StrongerButton->y + 10, StrongerButton->r);
        setbkmode(TRANSPARENT);

        putimage(440, 20, &img_Strongerb, SRCAND);
        putimage(440, 20, &img_Stronger, SRCPAINT);
        outtextxy(StrongerButton->x - 10, StrongerButton->y + 35, "Stronger");

		//////////
		IMAGE img_sybil2, img_sybilb2;
		loadimage(&img_sybil2, "./images/source.png");
		loadimage(&img_sybilb2,"./images/sourceb.png");
		setfillcolor(sybilButton2->color);
		solidcircle(sybilButton2->x + 10, sybilButton2->y + 10, sybilButton2->r);
		setbkmode(TRANSPARENT);

		putimage(500, 20, &img_sybilb2, SRCAND);
		putimage(500, 20, &img_sybil2, SRCPAINT);
		outtextxy(sybilButton2->x - 10, sybilButton2->y + 35, "Tracing");
    }

    FlushBatchDraw();
}


// 检查车辆是否与已有车辆重叠
bool isOverlap(const Car& car, const std::vector<Car>& cars) {
    for (const auto& otherCar : cars) {
        if (car.x < otherCar.x + otherCar.width &&
            car.x + car.width > otherCar.x &&
            car.y < otherCar.y + otherCar.height &&
            car.y + car.height > otherCar.y) {
            return true; // 有重叠
        }
    }
    return false; // 没有重叠
}

// 检查邮件位置是否与已有车辆或邮件重叠
bool isEmailOverlap(const Email& email, const std::vector<Email>& emails) {

    // 检查邮件位置是否与邮件重叠
    for (const auto& otherEmail : emails) {
        if (&email != &otherEmail && // 排除与自身比较
            email.x < otherEmail.x + 60 &&
            email.x + 60 > otherEmail.x &&
            email.y < otherEmail.y + 60 &&
            email.y + 60 > otherEmail.y) {
            return true; // 有重叠
        }
    }

    return false; // 没有重叠
}


Car yellowcar_build(std::vector<Car>& cars, IMAGE& yellowcarb, IMAGE& yellowcar) {
    // 加载车辆图片
    loadimage(&yellowcarb, "./images/yellowb.png");
    loadimage(&yellowcar, "./images/yellow.png");

    // 随机生成车辆的位置
    srand(time(NULL)); // 使用当前时间作为随机数种子
    int yellowcarWidth = yellowcar.getwidth(); // 获取车辆图片的宽度
    int yellowcarHeight = yellowcar.getheight(); // 获取车辆图片的高度

    Car yellowCar;
    yellowCar.index = cars.size(); // 设置白色车辆的索引为当前向量大小
    do {
		/*
        yellowCar.x = 500 + rand() % 100;
        yellowCar.y = 300 + rand() % 100;
		*/
		yellowCar.x = (WIDTH/5)*3+20;
		yellowCar.y = (HEIGHT/4)*2+ rand() % 30;
        yellowCar.width = yellowcarWidth;
        yellowCar.height = yellowcarHeight;
    } while (isOverlap(yellowCar, cars)); // 检查是否与已有车辆重叠

    // 存储掩码图像和原图像到 Car 结构体中
    yellowCar.maskImage = yellowcarb;
    yellowCar.originalImage = yellowcar;

    // 绘制车辆图片
    putimage(yellowCar.x, yellowCar.y, &yellowCar.maskImage, SRCAND);
    putimage(yellowCar.x, yellowCar.y, &yellowCar.originalImage, SRCPAINT);


    cars.push_back(yellowCar); // 将新车辆加入 vector
    return yellowCar;
}


void whitecar_build(std::vector<Car>& cars, std::vector<Email>& emails, IMAGE& whitecarb, IMAGE& whitecar, IMAGE& email, IMAGE& emailb) {
    // 加载车辆图片
    loadimage(&whitecarb, "./images/whiteb.png");
    loadimage(&whitecar, "./images/white.png");

    loadimage(&emailb, "./images/emailb.png");
    loadimage(&email, "./images/email.png");

    // 获取车辆图片的宽度和高度
    int whitecarWidth = whitecar.getwidth();
    int whitecarHeight = whitecar.getheight();

    Car whiteCar;
    whiteCar.index = cars.size(); // 设置白色车辆的索引为当前向量大小
    Email whiteCarEmail;
    bool positionFound = false;

    srand(time(NULL)); // 使用当前时间作为随机数种子

    whiteCar.width = whitecarWidth;
    whiteCar.height = whitecarHeight;

    while (!positionFound) {
        // 随机选择一个区域
		int region = rand() % 2;
		//cout << "当前rand" << region;
		switch (region) {
		case 0: // 一号道
			whiteCar.x = rand() % (WIDTH- whitecarWidth);
			whiteCarEmail.x = whiteCar.x + whiteCar.width / 2;
			whiteCar.y =0 + rand() % 50;
			whiteCarEmail.y = whiteCar.y + whiteCar.height / 2;
			break;
		case 1: // 二号道
			whiteCar.x = rand() % (WIDTH - whitecarWidth);
			whiteCarEmail.x = whiteCar.x + whiteCar.width / 2;
			whiteCar.y = HEIGHT/4 + rand() % 50;
			whiteCarEmail.y = whiteCar.y + whiteCar.height / 2;
			break;
		}
	    /*
        int region = rand() % 4;
        switch (region) {
        case 0: // 上方区域
            whiteCar.x = rand() % (WIDTH - whitecarWidth);
            whiteCarEmail.x = whiteCar.x + whiteCar.width / 2;
            whiteCar.y = rand() % 130;
            whiteCarEmail.y = whiteCar.y + whiteCar.height / 2;
            break;
        case 1: // 下方区域
            whiteCar.x = rand() % (WIDTH - whitecarWidth);
            whiteCarEmail.x = whiteCar.x + whiteCar.width / 2;
            whiteCar.y = 600 + rand() % (HEIGHT - 600 - whitecarHeight);
            whiteCarEmail.y = whiteCar.y + whiteCar.height / 2;
            break;
        case 2: // 左侧区域
            whiteCar.x = rand() % 130;
            whiteCarEmail.x = whiteCar.x + whiteCar.width / 2;
            whiteCar.y = 130 + rand() % (600 - 130 - whitecarHeight);
            whiteCarEmail.y = whiteCar.y + whiteCar.height / 2;
            break;
        case 3: // 右侧区域
            whiteCar.x = 1200 + rand() % (WIDTH - 1200 - whitecarWidth);
            whiteCarEmail.x = whiteCar.x + whiteCar.width / 2;
            whiteCar.y = 130 + rand() % (600 - 130 - whitecarHeight);
            whiteCarEmail.y = whiteCar.y + whiteCar.height / 2;
            break;
        }
		*/


        // 检查是否与已有车辆重叠
        if (!isOverlap(whiteCar, cars)) {
            positionFound = true;
        }

    }

    // 存储掩码图像和原图像到 Car 结构体中
    whiteCar.maskImage = whitecarb;
    whiteCar.originalImage = whitecar;
    whiteCarEmail.emailmaskImage = emailb;
    whiteCarEmail.emailoriginalImage = email;

    whiteCarEmail.startingCarIndex = whiteCar.index; // 存储发起车辆的索引

    // 绘制车辆图片
    putimage(whiteCar.x, whiteCar.y, &whiteCar.maskImage, SRCAND);
    putimage(whiteCar.x, whiteCar.y, &whiteCar.originalImage, SRCPAINT);

    // 绘制邮件图片
    putimage(whiteCar.x, whiteCar.y, &whiteCarEmail.emailmaskImage, SRCAND);
    putimage(whiteCar.x, whiteCar.y, &whiteCarEmail.emailoriginalImage, SRCPAINT);

    cars.push_back(whiteCar); // 将新车辆加入 vector
    emails.push_back(whiteCarEmail);
}


void greencar_build(std::vector<Car>& cars, std::vector<Email>& emails, IMAGE& greencarb, IMAGE& greencar, IMAGE& email, IMAGE& emailb) {
    // 加载车辆图片
    loadimage(&greencarb, "./images/greenb.png");
    loadimage(&greencar, "./images/green.png");

    loadimage(&emailb, "./images/emailb.png");
    loadimage(&email, "./images/email.png");

    // 获取车辆图片的宽度和高度
    int greencarWidth = greencar.getwidth();
    int greencarHeight = greencar.getheight();

    Car greenCar;
    greenCar.index = cars.size(); // 设置白色车辆的索引为当前向量大小
    Email greenCarEmail;
    bool positionFound = false;

    srand(time(NULL)); // 使用当前时间作为随机数种子

    greenCar.width = greencarWidth;
    greenCar.height = greencarHeight;

    while (!positionFound) {
        // 随机选择一个区域
		int region = rand() % 3;
		switch (region) {
		case 0: // 1号道
			greenCar.x = rand() % (WIDTH - greencarWidth);
			greenCarEmail.x = greenCar.x + greenCar.width / 2;
			greenCar.y = rand() % 50;
			greenCarEmail.y = greenCar.y + greenCar.height / 2;
			break;
		case 1: // 2号道
			greenCar.x = rand() % (WIDTH - greencarWidth);
			greenCarEmail.x = greenCar.x + greenCar.width / 2;
			greenCar.y = HEIGHT/4 + rand() % 50;
			greenCarEmail.y = greenCar.y + greenCar.height / 2;
			break;
		case 2: // 3号道
			greenCar.x = rand() % (WIDTH - greencarWidth);
			greenCarEmail.x = greenCar.x + greenCar.width / 2;
			greenCar.y = (HEIGHT / 4)*2 + rand() % 50;
			greenCarEmail.y = greenCar.y + greenCar.height / 2;
			break;
		}

		/*
        int region = rand() % 4;
        switch (region) {
        case 0: // 上方区域
            greenCar.x = rand() % (WIDTH - greencarWidth);
            greenCarEmail.x = greenCar.x + greenCar.width / 2;
            greenCar.y = rand() % 130;
            greenCarEmail.y = greenCar.y + greenCar.height / 2;
            break;
        case 1: // 下方区域
            greenCar.x = rand() % (WIDTH - greencarWidth);
            greenCarEmail.x = greenCar.x + greenCar.width / 2;
            greenCar.y = 600 + rand() % (HEIGHT - 600 - greencarHeight);
            greenCarEmail.y = greenCar.y + greenCar.height / 2;
            break;
        case 2: // 左侧区域
            greenCar.x = rand() % 130;
            greenCarEmail.x = greenCar.x + greenCar.width / 2;
            greenCar.y = 130 + rand() % (600 - 130 - greencarHeight);
            greenCarEmail.y = greenCar.y + greenCar.height / 2;
            break;
        case 3: // 右侧区域
            greenCar.x = 1200 + rand() % (WIDTH - 1200 - greencarWidth);
            greenCarEmail.x = greenCar.x + greenCar.width / 2;
            greenCar.y = 130 + rand() % (600 - 130 - greencarHeight);
            greenCarEmail.y = greenCar.y + greenCar.height / 2;
            break;
        }
		*/


        // 检查是否与已有车辆重叠
        if (!isOverlap(greenCar, cars)) {
            positionFound = true;
        }

    }

    // 存储掩码图像和原图像到 Car 结构体中
    greenCar.maskImage = greencarb;
    greenCar.originalImage = greencar;
    greenCarEmail.emailmaskImage = emailb;
    greenCarEmail.emailoriginalImage = email;

    greenCarEmail.startingCarIndex = greenCar.index; // 存储发起车辆的索引

    // 绘制车辆图片
    putimage(greenCar.x, greenCar.y, &greenCar.maskImage, SRCAND);
    putimage(greenCar.x, greenCar.y, &greenCar.originalImage, SRCPAINT);

    // 绘制邮件图片
    putimage(greenCar.x, greenCar.y, &greenCarEmail.emailmaskImage, SRCAND);
    putimage(greenCar.x, greenCar.y, &greenCarEmail.emailoriginalImage, SRCPAINT);

    cars.push_back(greenCar); // 将新车辆加入 vector
    emails.push_back(greenCarEmail);
}

static int black_pos;

void blackcar_build(std::vector<Car>& cars, std::vector<Email>& emails, IMAGE& blackcarb, IMAGE& blackcar, IMAGE& email, IMAGE& emailb) {
    // 加载车辆图片
    loadimage(&blackcarb, "./images/blackb.png");
    loadimage(&blackcar, "./images/black.png");

    loadimage(&emailb, "./images/emailb.png");
    loadimage(&email, "./images/email.png");

    // 获取车辆图片的宽度和高度
    int blackcarWidth = blackcar.getwidth();
    int blackcarHeight = blackcar.getheight();

    Car blackCar;
    blackCar.index = cars.size(); // 设置白色车辆的索引为当前向量大小
    Email blackCarEmail;
    bool positionFound = false;

    srand(time(NULL)); // 使用当前时间作为随机数种子

    blackCar.width = blackcarWidth;
    blackCar.height = blackcarHeight;

    while (!positionFound) {
        // 随机选择一个区域
			blackCar.x = (WIDTH / 5) * 3 - 210;
			blackCarEmail.x = blackCar.x + blackCar.width / 2;
			blackCar.y = (HEIGHT / 4) * 3 + rand() % 50;
			blackCarEmail.y = blackCar.y + blackCar.height / 2;
		/*
		int region = rand() % 2;
		switch (region) {
		case 0: // 上方区域
			blackCar.x = rand() % (WIDTH - blackcarWidth);
			blackCarEmail.x = blackCar.x + blackCar.width / 2;
			blackCar.y = (HEIGHT / 4) * 2+rand() % 50;
			blackCarEmail.y = blackCar.y + blackCar.height / 2;
			break;
		case 1: // 下方区域
			blackCar.x = rand() % (WIDTH - blackcarWidth);
			blackCarEmail.x = blackCar.x + blackCar.width / 2;
			blackCar.y = (HEIGHT / 4) * 3+ rand() % 50;
			blackCarEmail.y = blackCar.y + blackCar.height / 2;
			break;
		}
		*/
		/*
        int region = rand() % 4;
        switch (region) {
        case 0: // 上方区域
            blackCar.x = rand() % (WIDTH - blackcarWidth);
            blackCarEmail.x = blackCar.x + blackCar.width / 2;
            blackCar.y = rand() % 130;
            blackCarEmail.y = blackCar.y + blackCar.height / 2;
            break;
        case 1: // 下方区域
            blackCar.x = rand() % (WIDTH - blackcarWidth);
            blackCarEmail.x = blackCar.x + blackCar.width / 2;
            blackCar.y = 600 + rand() % (HEIGHT - 600 - blackcarHeight);
            blackCarEmail.y = blackCar.y + blackCar.height / 2;
            break;
        case 2: // 左侧区域
            blackCar.x = rand() % 130;
            blackCarEmail.x = blackCar.x + blackCar.width / 2;
            blackCar.y = 130 + rand() % (600 - 130 - blackcarHeight);
            blackCarEmail.y = blackCar.y + blackCar.height / 2;
            break;
        case 3: // 右侧区域
            blackCar.x = 1200 + rand() % (WIDTH - 1200 - blackcarWidth);
            blackCarEmail.x = blackCar.x + blackCar.width / 2;
            blackCar.y = 130 + rand() % (600 - 130 - blackcarHeight);
            blackCarEmail.y = blackCar.y + blackCar.height / 2;
            break;
        }
		*/


        // 检查是否与已有车辆重叠
        if (!isOverlap(blackCar, cars)) {
            positionFound = true;
        }

    }

    // 存储掩码图像和原图像到 Car 结构体中
    blackCar.maskImage = blackcarb;
    blackCar.originalImage = blackcar;
    blackCarEmail.emailmaskImage = emailb;
    blackCarEmail.emailoriginalImage = email;

    blackCarEmail.startingCarIndex = blackCar.index; // 存储发起车辆的索引

    // 绘制车辆图片
    putimage(blackCar.x, blackCar.y, &blackCar.maskImage, SRCAND);
    putimage(blackCar.x, blackCar.y, &blackCar.originalImage, SRCPAINT);

    // 绘制邮件图片
    putimage(blackCar.x, blackCar.y, &blackCarEmail.emailmaskImage, SRCAND);
    putimage(blackCar.x, blackCar.y, &blackCarEmail.emailoriginalImage, SRCPAINT);

    cars.push_back(blackCar); // 将新车辆加入 vector
    emails.push_back(blackCarEmail);
}


void redcar_build(std::vector<Car>& cars, std::vector<Email>& emails, IMAGE& redcarb, IMAGE& redcar, IMAGE& email, IMAGE& emailb) {
    // 加载车辆图片
    loadimage(&redcarb, "./images/redb.png");
    loadimage(&redcar, "./images/red.png");

    loadimage(&emailb, "./images/emailb.png");
    loadimage(&email, "./images/email.png");

    // 随机生成车辆的位置
    srand(time(NULL)); // 使用当前时间作为随机数种子
    int redcarWidth = redcar.getwidth(); // 获取车辆图片的宽度
    int redcarHeight = redcar.getheight(); // 获取车辆图片的高度

    Car redCar;
    redCar.index = cars.size(); // 设置白色车辆的索引为当前向量大小
    Email redCarEmail;
    do {
        redCar.x = 1200;
        redCarEmail.x = redCar.x + redcarWidth / 2 - 30;
		if (rand() % 3 == 0) {
			redCar.y = rand() % 50;
		}
		else if(rand() % 3 == 1){
			redCar.y = HEIGHT / 4+ rand() % 50;
		}
		else {
			redCar.y = (HEIGHT / 4)*2 + rand() % 50;
		}
        redCarEmail.y = redCar.y + redcarHeight / 2 - 30;
        redCar.width = redcarWidth;
        redCar.height = redcarHeight;
    } while (isOverlap(redCar, cars)); // 检查是否与已有车辆重叠

    // 存储掩码图像和原图像到 Car 结构体中
    redCar.maskImage = redcarb;
    redCar.originalImage = redcar;
    redCarEmail.emailmaskImage = emailb;
    redCarEmail.emailoriginalImage = email;

    redCarEmail.startingCarIndex = redCar.index; // 存储发起车辆的索引


    // 绘制车辆图片
    putimage(redCar.x, redCar.y, &redCar.maskImage, SRCAND);
    putimage(redCar.x, redCar.y, &redCar.originalImage, SRCPAINT);

    // 绘制邮件图片
    putimage(redCarEmail.x, redCarEmail.y, &redCarEmail.emailmaskImage, SRCAND);
    putimage(redCarEmail.x, redCarEmail.y, &redCarEmail.emailoriginalImage, SRCPAINT);

    cars.push_back(redCar); // 将新车辆加入 vector
    emails.push_back(redCarEmail);
}


void Strongercar_build(std::vector<Car>& cars, std::vector<Email>& emails, IMAGE& Strongercarb, IMAGE& Strongercar, IMAGE& email, IMAGE& emailb) {
    // 加载车辆图片
    loadimage(&Strongercarb, "./images/StrongerCarb.png");
    loadimage(&Strongercar, "./images/StrongerCar.png");

    loadimage(&emailb, "./images/emailb.png");
    loadimage(&email, "./images/email.png");

    // 随机生成车辆的位置
    srand(time(NULL)); // 使用当前时间作为随机数种子
    int StrongercarWidth = Strongercar.getwidth(); // 获取车辆图片的宽度
    int StrongercarHeight = Strongercar.getheight(); // 获取车辆图片的高度

    Car Strongercar1;
    Strongercar1.index = cars.size(); // 设置白色车辆的索引为当前向量大小
    Strongercar1.isStronger = true;
    Email StrongercarEmail;
    do {
        Strongercar1.x = 1200;
        StrongercarEmail.x = Strongercar1.x + StrongercarWidth / 2 - 30;
        Strongercar1.y = rand() % (HEIGHT - StrongercarHeight);
        StrongercarEmail.y = Strongercar1.y + StrongercarHeight / 2 - 30;
        Strongercar1.width = StrongercarWidth;
        Strongercar1.height = StrongercarHeight;
    } while (isOverlap(Strongercar1, cars)); // 检查是否与已有车辆重叠

    // 存储掩码图像和原图像到 Car 结构体中
    Strongercar1.maskImage = Strongercarb;
    Strongercar1.originalImage = Strongercar;
    StrongercarEmail.emailmaskImage = emailb;
    StrongercarEmail.emailoriginalImage = email;

    StrongercarEmail.startingCarIndex = Strongercar1.index; // 存储发起车辆的索引

    // 绘制车辆图片
    putimage(Strongercar1.x, Strongercar1.y, &Strongercar1.maskImage, SRCAND);
    putimage(Strongercar1.x, Strongercar1.y, &Strongercar1.originalImage, SRCPAINT);

    // 绘制邮件图片
    putimage(StrongercarEmail.x, StrongercarEmail.y, &StrongercarEmail.emailmaskImage, SRCAND);
    putimage(StrongercarEmail.x, StrongercarEmail.y, &StrongercarEmail.emailoriginalImage, SRCPAINT);

    cars.push_back(Strongercar1); // 将新车辆加入 vector
    emails.push_back(StrongercarEmail);
}

bool haveStrongerCar(const std::vector<Car>& cars) {
    for (auto car : cars) {
        if (car.isStronger) {
            return true;
        }
    }
    return false;
}



int countVirtualCars(const std::vector<Car>& cars) {
    int count = 0;
    for (const auto& car : cars) {
        if (car.isvirtual) {
            count++;
        }
    }
    return count;
}
Car findRedCar(const std::vector<Car>& cars) {
    for (const auto& car : cars) {
        if (car.isStronger == true) {
            return car;
        }
        else if (car.index == 5) {
            return car;
        }
    }
    // 如果未找到红车，则返回一个默认构造的车辆对象
    return Car{};
}


void virtualcar_build(std::vector<Car>& cars, std::vector<Email>& emails, IMAGE& virtualcarb, IMAGE& virtualcar, const Car& yellowCar, IMAGE& email, IMAGE& emailb) {
    if (haveStrongerCar(cars)) {
        // 加载车辆图片
        loadimage(&virtualcarb, "./images/Strongervirtualb.png");
        loadimage(&virtualcar, "./images/Strongervirtual.png");
    }
    else {
        // 加载车辆图片
        loadimage(&virtualcarb, "./images/virtualb.png");
        loadimage(&virtualcar, "./images/virtual.png");

    }

    // 获取车辆图片的宽度和高度
    int virtualcarWidth = virtualcar.getwidth();
    int virtualcarHeight = virtualcar.getheight();

    // 遍历四个方向生成虚拟车辆
    for (int i = 0; i < 3; ++i) {
        Car virtualCar;
        virtualCar.index = cars.size(); // 设置白色车辆的索引为当前向量大小
        bool positionFound = false;

        // 设置虚拟车辆的初始位置
        switch (i) {
        case 0: // 上方区域
            virtualCar.x = yellowCar.x;
            virtualCar.y = yellowCar.y - virtualcarHeight - 20;
            virtualCar.isvirtual = true;
            break;
		/*
        case 1: // 下方区域
            virtualCar.x = yellowCar.x;
            virtualCar.y = yellowCar.y + yellowCar.height + 20;
            virtualCar.isvirtual = true;
            break;
		*/
        case 1: // 左侧区域
            virtualCar.x = yellowCar.x - virtualcarWidth - 20;
            virtualCar.y = yellowCar.y;
            virtualCar.isvirtual = true;
            break;
        case 2: // 右侧区域
            virtualCar.x = yellowCar.x + yellowCar.width + 20;
            virtualCar.y = yellowCar.y;
            virtualCar.isvirtual = true;
            break;
        }

        // 调整位置以确保在屏幕内
        virtualCar.x = max(0, min(WIDTH - virtualcarWidth, virtualCar.x));
        virtualCar.y = max(0, min(HEIGHT - virtualcarHeight, virtualCar.y));

        virtualCar.width = virtualcarWidth;
        virtualCar.height = virtualcarHeight;

        // 检查是否与已有车辆重叠
        if (!isOverlap(virtualCar, cars)) {
            // 如果未重叠，则将虚拟车辆添加到 vector 中
            virtualCar.maskImage = virtualcarb;
            virtualCar.originalImage = virtualcar;
            putimage(virtualCar.x, virtualCar.y, &virtualCar.maskImage, SRCAND);
            putimage(virtualCar.x, virtualCar.y, &virtualCar.originalImage, SRCPAINT);
            cars.push_back(virtualCar);



        }
    }


    // 获取当前时间作为随机种子
    unsigned int seed = static_cast<unsigned int>(std::time(nullptr));

    // 设置随机种子
    srand(seed);

    int numEmails = countVirtualCars(cars);
    /*std::cout << numEmails;*/
    for (int j = 0; j < numEmails; ++j) {
        Email virtualCarEmail;

        // 生成虚拟车辆关联的邮件位置
        Car redCar = findRedCar(cars);
        int offsetX, offsetY;
        offsetX = rand() % 100; // 随机生成偏移量
        offsetY = rand() % 100; // 随机生成偏移量
        virtualCarEmail.x = redCar.x + redCar.width / 2 - 30 + offsetX; // 假设邮件宽度为60
        virtualCarEmail.y = redCar.y + redCar.height / 2 - 30 + offsetY; // 假设邮件高度为60


        // 存储掩码图像和原图像到 Email 结构体中
        virtualCarEmail.emailmaskImage = emailb;
        virtualCarEmail.emailoriginalImage = email;

        // 设置邮件的发起车辆索引
        virtualCarEmail.startingCarIndex = 5;

        // 将邮件加入 vector
        emails.push_back(virtualCarEmail);
    }

}

#include <windows.h> // 包含 Windows API 函数声明
// 函数：重新启动当前应用程序
void RestartApplication() {
	TCHAR szFilePath[MAX_PATH];
	GetModuleFileName(NULL, szFilePath, MAX_PATH); // 获取当前进程的路径

	// 创建新进程
	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi;
	if (CreateProcess(szFilePath, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
		// 关闭句柄
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
		ExitProcess(0); // 退出当前进程
	}
}
int boomm = 0;
void move_cars2(std::vector<Car>& cars) {
	std::vector<Car> carss(cars.begin() + 1, cars.end());
	for (int i = 0; i < cars.size(); i++) {
		if (i == 0 && cars.size() > 6) {
			if (isOverlap(cars[0], carss)) {
				boomm = 1;
				yidong = 0;
				/*
				HWND hwnd = GetForegroundWindow(); // 获取当前活动窗口的句柄
				SetForegroundWindow(hwnd);         // 将该窗口设置为前景窗口
				int result=MessageBox(hwnd, "发生车祸碰撞", "警告", MB_OK | MB_ICONWARNING);
				if (result == IDOK) {
					cars[4].x-=500;
					cars[0].y -= 80;
					yidong = 0;
				}
				*/
			}

			if (cars[0].y + cars[0].height > (HEIGHT / 4) * 3 + 150) {
				cars[0].x -= SPEED;
				if (cars[0].x + cars[0].width < 0) {
					cars[0].x = WIDTH;
				}
				continue;
			}
			cars[0].y += SPEED * 5;

		}
		cars[i].x -= SPEED;
		cars[i].moveDistance += SPEED;
		if (cars[i].x + cars[i].width < 0) {
			cars[i].x = WIDTH;
		}
	}
}

void move_cars(std::vector<Car>& cars) {
	for (int i = 0; i < cars.size(); i++) {
		cars[i].x -= SPEED;
		cars[i].moveDistance += SPEED;
		if (cars[i].x + cars[i].width < 0) {
			cars[i].x = WIDTH;
		}
	}
}
	/*
    for (auto& car : cars) {
        car.x -= SPEED; // 每辆车向右移动，速度为 SPEED
		if (cars[5]) {
			cars[0].y += SPEED;
			if (cars[0].y + cars[0].height < 0) {
				cars[0]. = WIDTH; // 将车辆移到窗口右侧
			}
		}
        car.moveDistance += SPEED; // 记录移动的距离
        // 检查车辆是否超出窗口边界，如果超出，将车辆移到窗口另一端
        if (car.x + car.width < 0) {
            car.x = WIDTH; // 将车辆移到窗口右侧
        }
    }
	*/

Car findYellowCar(const std::vector<Car>& cars, const Car& yellowcar) {
    for (const auto& car : cars) {
        if (car.width == yellowcar.width && car.height == yellowcar.height) {
            return car;
        }
    }
}

Car findSendingCar(const std::vector<Car>& cars, const Email& email) {
    for (const auto& car : cars) {
        if (car.index == email.startingCarIndex) {
            return car;
        }
    }
}



bool malicious=0;//判断是否按溯源按钮

bool canPause1 = 0, canPause2 = 0;
// 修改 allmousePeek 函数，处理按钮点击事件
void allmousePeek(struct smallbutton* StrongerButton, IMAGE& Strongercarb, IMAGE& Strongercar, struct smallbutton* clearButton, int& startClear, int& startSybil, int& startSource, int& NumWindow, std::vector<Car>& cars, std::vector<Email>& emails,
    IMAGE& redcarb, IMAGE& redcar, struct smallbutton* startButton, struct smallbutton* stopButton, struct smallbutton* sybilButton, struct smallbutton* sybilButton2,
    struct smallbutton* DwindowButton, struct smallbutton* windowButton, struct smallbutton* sourceButton, const Car& yellowCar, int& startClicked, IMAGE& email, IMAGE& emailb) {
    ExMessage mssg;
    while (peekmessage(&mssg, EM_MOUSE)) {
        switch (mssg.message) {
        case WM_LBUTTONDOWN:
            if (!canPause1 && (mssg.x - startButton->x) * (mssg.x - startButton->x) + (mssg.y - startButton->y) * (mssg.y - startButton->y) <= startButton->r * startButton->r) {

				// 如果点击了 start 按钮，执行 start 按钮的操作
                startClear = 0;
                startClicked = 1;
                canPause1 = 1;
                redcar_build(cars, emails, redcarb, redcar, email, emailb);
                
            }
            else if (startClicked == 1 && (mssg.x - sybilButton->x) * (mssg.x - sybilButton->x) + (mssg.y - sybilButton->y) * (mssg.y - sybilButton->y) <= sybilButton->r * sybilButton->r) {
                //std::cout << "点击检测按钮了"<<endl;
                startSybil = 1;
            }
            else if (startClicked == 1 && isSoureceShow == true && (mssg.x - sourceButton->x) * (mssg.x - sourceButton->x) + (mssg.y - sourceButton->y) * (mssg.y - sourceButton->y) <= sourceButton->r * sourceButton->r) {
				//MessageBox(NULL, "发生车祸碰撞", "警告", MB_OK | MB_ICONWARNING);
				malicious = 1;
				startSource = 1;
            }
            else if (startClicked == 1 && (mssg.x - windowButton->x) * (mssg.x - windowButton->x) + (mssg.y - windowButton->y) * (mssg.y - windowButton->y) <= windowButton->r * windowButton->r) {
				
				startSybil = 0; 
                NumWindow++;
            }
            else if (startClicked == 1 && (mssg.x - DwindowButton->x) * (mssg.x - DwindowButton->x) + (mssg.y - DwindowButton->y) * (mssg.y - DwindowButton->y) <= DwindowButton->r * DwindowButton->r) {

				startSybil = 0; 
                NumWindow--;
            }
			else if (startClicked == 1 && (mssg.x - sybilButton2->x) * (mssg.x - sybilButton2->x) + (mssg.y - sybilButton2->y) * (mssg.y - sybilButton2->y) <= sybilButton2->r * sybilButton2->r) {
				yidong = !yidong;
				black_pos ++;
			}
            else if ((mssg.x - clearButton->x) * (mssg.x - clearButton->x) + (mssg.y - clearButton->y) * (mssg.y - clearButton->y) <= clearButton->r * clearButton->r) {
                startClear = 1;
                startSybil = 0;
                startSource = 0;
                canPause1 = 0;
                canPause2 = 0;
                Car cc = findRedCar(cars);

                for (auto car: cars) {
                    car.show = 0;
                }

                // 删除与该车辆相关的邮件
                for (auto it = emails.begin(); it != emails.end(); ) {
                    if (it->startingCarIndex == cc.index) {
                        it = emails.erase(it); // 使用迭代器删除元素
                    }
                    else {
                        ++it;
                    }
                }   

                // 删除与该车辆相关的虚拟车
                for (auto it = cars.begin(); it != cars.end(); ) {
                    if (it->isvirtual == true) {
                        it->isvirtual = false;
                        it = cars.erase(it); // 使用迭代器删除元素
                    }
                    else {
                        ++it;
                    }
                }
                // 删除车辆
                cars.erase(cars.begin() + cc.index);


            }
            else if (startClear == 1 && (mssg.x - StrongerButton->x) * (mssg.x - StrongerButton->x) + (mssg.y - StrongerButton->y) * (mssg.y - StrongerButton->y) <= StrongerButton->r * StrongerButton->r) {
               Strongercar_build(cars, emails, Strongercarb, Strongercar, email, emailb);
               startClicked == 1;
               canPause2 = 0;
            }
            else if (!canPause2 && startClicked == 1 && (mssg.x - stopButton->x) * (mssg.x - stopButton->x) + (mssg.y - stopButton->y) * (mssg.y - stopButton->y) <= stopButton->r * stopButton->r) {
                canPause2 = 1;
                // 获取当前黄车位置
                Car currentYellowCar = findYellowCar(cars, yellowCar);
                // 如果点击了 stop 按钮，执行 stop 按钮的操作
                if (haveStrongerCar(cars)) {
                    //MessageBox(NULL, "可以检测到超强攻击者，下一步是创建Sybil。", "错误", MB_OK | MB_ICONERROR);
                    virtualcar_build(cars, emails, Strongercarb, Strongercar, currentYellowCar, email, emailb);
                    startClicked == 1;
                }
                else
                    virtualcar_build(cars, emails, redcarb, redcar, currentYellowCar, email, emailb);
            }
            break;
            // 其他鼠标消息类型的处理
        default:
            break;
        }
    }
}

void drawConnections(const std::vector<Car>& cars, const Car& yellowCar) {
    setlinecolor(RGB(255, 255, 255)); // 设置连线颜色为白色
    setlinestyle(PS_SOLID, 3); // 设置连线样式为实线，粗细为3像素

    // 获取黄车当前位置
    Car currentYellowCar = findYellowCar(cars, yellowCar);
    int yellowCarX = currentYellowCar.x + currentYellowCar.width / 2;
    int yellowCarY = currentYellowCar.y + currentYellowCar.height / 2;

    for (const auto& car : cars) {
        if (car.x != currentYellowCar.x && car.y != currentYellowCar.y && car.isvirtual != true) { // 排除黄车
            // 计算终点坐标（车辆中心点）
            int endX = car.x + car.width / 2;
            int endY = car.y + car.height / 2;

            // 绘制连线
            line(yellowCarX, yellowCarY, endX, endY);
        }
    }
}


void move_emails(int& NumWindow, std::vector<Email>& emails, std::vector<Car>& cars, const Car& yellowCar, int& startSybil, int& startClear) {
    // 获取黄车的中心坐标
    int yellowCarCenterX = yellowCar.x + yellowCar.width / 2;
    int yellowCarCenterY = yellowCar.y + yellowCar.height / 2;

    for (auto& email : emails) {

        // 计算邮件中心坐标
        int emailCenterX = email.x + 30; // 假设邮件的宽度为60，所以中心点偏移量为30
        int emailCenterY = email.y + 30; // 假设邮件的高度为60，所以中心点偏移量为30

        // 计算方向向量
        int deltaX = yellowCarCenterX - emailCenterX;
        int deltaY = yellowCarCenterY - emailCenterY;

        // 计算向量长度
        float length = sqrt(deltaX * deltaX + deltaY * deltaY);

        // 归一化方向向量
        float normalizedX = deltaX / length;
        float normalizedY = deltaY / length;

        // 移动距离，可以根据需要调整速度
        float moveDistance = EMSPEED;

        // 更新邮件位置
        email.x += static_cast<int>(normalizedX * moveDistance);
        email.y += static_cast<int>(normalizedY * moveDistance);

        // 检查邮件是否到达黄车附近，可以设置一个容忍范围
        if (abs(emailCenterX - yellowCarCenterX) < moveDistance && abs(emailCenterY - yellowCarCenterY) < moveDistance) {
            Car sendingCar = findSendingCar(cars, email);
            //std::cout << "startSybil" << startSybil << std::endl;
            if (startSybil == 1) {
                startClear = 0;
                //startSource = 1;
                cout << "email.emailcount" << email.emailcount << endl;
                email.emailcount++;
            }
            if (startClear == 1){
                for (auto& email : emails) {
                    email.emailcount = 0;
                }
                for (auto& car : cars) {
                    car.show = 0;
                }
            }

            if (email.emailcount >= NumWindow) {
                cars[sendingCar.index].show = 1;
                std::cout << "sendingCar.index:" << sendingCar.index << " "<<endl;
            }
            // 将邮件位置设定为发起车当前位置
            int offsetX = rand() % 50; // 随机生成偏移量
            int offsetY = rand() % 50; // 随机生成偏移量
            email.x = sendingCar.x + sendingCar.width / 2 - 25 + offsetX;
            email.y = sendingCar.y + sendingCar.height / 2 - 25 + offsetY;

        }


        // 检查邮件是否超出窗口边界，如果超出，将邮件移到窗口另一端
        if (email.x + 600 < 0) {
            email.x = WIDTH; // 将邮件移到窗口右侧
        }

    }
}

std::vector<Car> getVirtualCars(const std::vector<Car>& cars) {
    std::vector<Car> virtualCars;
    for (const auto& car : cars) {
        if (car.isvirtual) {
            virtualCars.push_back(car);
        }
    }
    return virtualCars;
}

#include <fstream>
#include <sstream> // 添加头文件以使用 std::stringstream
// 结果结构体
struct Result {
    int no;
    int index;
    int label;
};

// 读取结果文件
std::vector<Result> readResults(const std::string& filePath) {
    int idx = 1;
    std::ifstream file(filePath);
    std::vector<Result> results;
    if (file.is_open()) {
        Result result;
        while (file >> result.index >> result.label) {
            result.no = idx++;
            results.push_back(result);
        }
        file.close();
    }
    return results;
}

#include <string>
// 获取车辆对应的结果
std::string getLabelForCar(const std::vector<Result>& results, int carIndex) {
    for (const auto& result : results) {
        if (result.no == carIndex) {
            if (result.label == 0) return "车辆类型：正常车辆";
            if (result.label == 1) return "车辆类型：女巫车辆";
            if (result.label == 2) return malicious==0? "车辆类型：正常车辆":"车辆类型：恶意车辆";

        }
    }
    return "-1"; // 没有找到对应的结果
}

std::string getRealLabelForCar(const std::vector<Result>& results, int carIndex) {
    for (const auto& result : results) {
        if (result.no == carIndex) {
            return "Sender:" + std::to_string(result.index).substr(2, 5) + "  label:" + std::to_string(result.label);
        }
    }
    return "-1"; // 没有找到对应的结果
}

std::string getPreLabelForCar(const std::vector<Result>& results, int carIndex) {
    for (const auto& result : results) {
        if (result.no == carIndex) {
            return "label:" + std::to_string(result.label);
        }
    }
    return "-1"; // 没有找到对应的结果
}

#include <thread>

// 定义一个函数来运行Python脚本
void runPythonScript1() {
    system("python test.py");
}


void extractScores(const std::string& filename, int NumWindow, string& precision, string& recall, string& accuracy, string& f1_score) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "无法打开文件: " << filename << std::endl;
        return;
    }

    std::vector<string> scores;
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            scores.push_back(line);
        }
    }

    file.close();

    if (scores.size() < 36) {
        std::cerr << "文件中的分数数据不足。" << std::endl;
        return;
    }

    int baseIndex = NumWindow - 2;
    precision = scores[baseIndex + 0 * 9];
    recall = scores[baseIndex + 1 * 9];
    accuracy = scores[baseIndex + 2 * 9];
    f1_score = scores[baseIndex + 3 * 9];
}

bool qqqq(std::vector<Email>& emails, int& NumWindow) {
    for (auto email : emails) {
        if (email.emailcount < NumWindow) {
            return false;
        }
    }
    return true;
}






// 修改主循环中的按钮绘制和点击检测
int main() {
	// 初始化图形模式
	initgraph(WIDTH, HEIGHT);

	// 创建双缓冲区图像
	IMAGE backBuffer;
	initgraph(WIDTH, HEIGHT);

	// 加载图片
	IMAGE home_background;
	loadimage(&home_background, "./images/road.jpg");

	// 绘制图片
	putimage(0, 0, &home_background);
	std::vector<Result> results = readResults("result.txt");

	// 定义车辆图片变量
	IMAGE yellowcar, yellowcarb, whitecar, whitecarb, whitecarb1, whitecar1, redcarb, redcar, greencar, greencarb, blackcarb, blackcar, Strongercarb, Strongercar;
	IMAGE email, emailb;
	std::vector<Car> cars;
	std::vector<Email> emails;

	// 创建黄色车辆并保存其引用
	Car yellowCar = yellowcar_build(cars, yellowcarb, yellowcar);
	yellowCar.index = 0; // 设置黄色车辆的索引为0

	whitecar_build(cars, emails, whitecarb, whitecar, email, emailb);
	whitecar_build(cars, emails, whitecarb1, whitecar1, email, emailb);
	greencar_build(cars, emails, greencarb, greencar, email, emailb);
	blackcar_build(cars, emails, blackcarb, blackcar, email, emailb);
	int NumWindow = 2;

	// 创建第一个按钮
	struct smallbutton* startButton = createSmallButton(25, 25, 25, RGB(23, 23, 23), "redcar");
	// 创建第二个按钮
	struct smallbutton* stopButton = createSmallButton(85, 25, 25, RGB(23, 23, 23), "virtualcar");
	// 创建第三个按钮
	struct smallbutton* sybilButton = createSmallButton(145, 25, 25, RGB(23, 23, 23), "sybil");
	// 创建第四个按钮
	struct smallbutton* sourceButton = createSmallButton(205, 25, 25, RGB(23, 23, 23), "Increase");
	// 创建第五个按钮
	struct smallbutton* windowButton = createSmallButton(265, 25, 25, RGB(23, 23, 23), "Reduce");
	// 创建第六个按钮
	struct smallbutton* DwindowButton = createSmallButton(325, 25, 25, RGB(23, 23, 23), "shift");
	// 创建第七个按钮
	struct smallbutton* clearButton = createSmallButton(385, 25, 25, RGB(23, 23, 23), "Clear");
	// 创建第八个按钮
	struct smallbutton* StrongerButton = createSmallButton(445, 25, 25, RGB(23, 23, 23), "Stronger");
	// 创建第九个按钮
	struct smallbutton* sybilButton2 = createSmallButton(505, 25, 25, RGB(23, 23, 23), "source");

	// 标志变量初始化
	int startClicked = 0;

	bool isMovingToYellowCar = true; // 初始状态为向黄车移动

	// 启动一个新线程来运行Python脚本
	std::thread pythonThread1(runPythonScript1);

	// 在这里等待Python脚本执行完毕，但不阻塞主线程
	pythonThread1.detach();

	int startSybil = 0, startSource = 0, startClear = 0;

	//爆炸效果
	IMAGE boom, boomb;
	loadimage(&boomb, "./images/boomb.jpg");
	loadimage(&boom, "./images/boom.jpg");
	// 初始图像的缩放因子
	static double scale = 0.2;
	// 图像放大的步长
	static double scaleStep = 0.1;
	// 最大缩放因子
	static double maxScale = 4.0;
	static int cnt = 0;
	int centerX = (cars[0].x + cars[4].x) / 2;
	int centerY = cars[4].y;

	while (1) {
		// 清空双缓冲区
		cleardevice();

		// 绘制背景图到双缓冲区
		putimage(0, 0, &home_background, SRCCOPY);

		// 移动车辆
		if (yidong == 0) {
			move_cars(cars);
		}
		else {
			move_cars2(cars);
		}

		Car cc = findRedCar(cars);
		// 获取黄车当前位置
		int RedCarX = cc.x - 10;
		int RedCarY = cc.y - 10;
		// 计算终点坐标（车辆中心点）
		int endX = cc.x + cc.width + 10;
		int endY = cc.y + cc.height + 10;
		//std::cout << " " << RedCarX << " " << RedCarY << " " << endX << " " << endY << std::endl;
		// 绘制连线
		if (startSource == 1) rectangle(RedCarX, RedCarY, endX, endY);



		int ss = 0;
		// 绘制车辆到双缓冲区
		for (const auto& car : cars) {

			putimage(car.x, car.y, &car.maskImage, SRCAND);
			putimage(car.x, car.y, &car.originalImage, SRCPAINT);
			//std::cout << car.show << " ";
			if (car.show == 1 || (car.isvirtual == true && cc.show == 1)) {
				// 获取车辆对应的结果
				std::string label = getLabelForCar(results, car.index);
				// 在车辆中心位置显示结果
				if (label != "-1") {
					int centerX = car.x + 30;
					int centerY = car.y + car.height - 5;
					// 在图形窗口中显示结果，这里假设你使用的是 EasyX 图形库
					// 在车辆中心位置显示结果
					std::string labelStr = label;
					if (startClear == 0 and !haveStrongerCar(cars) || (haveStrongerCar(cars) and NumWindow > 5)) outtextxy(centerX, centerY, labelStr.c_str());
					else outtextxy(centerX, centerY, "车辆类型：正常车辆");
					//std::cout << car.emailcount << " ";
					if (car.index == 5) isSoureceShow = 1;
				}
			}

		}

		//爆炸效果
		if (boomm == 1 && scale <= maxScale) {
			if (scale <= maxScale) {
				IMAGE a;
				IMAGE b;
				int scaledWidth = boom.getwidth() * scale;
				int scaledHeight = boom.getheight() * scale;

				loadimage(&a, "./images/boom.jpg", scaledWidth, scaledHeight);
				loadimage(&b, "./images/boomb.jpg", scaledWidth, scaledHeight);

				int xx = centerX - (a.getwidth() * scale) / 2;
				int yy = centerY - (a.getheight() * scale) / 2;
				// 调整图像大小
				putimage(xx, yy, &b, SRCAND);
				putimage(xx, yy, &a, SRCPAINT);
				// 刷新画面
				Sleep(0);
				// 增加缩放因子
				scale += scaleStep;
				cnt++;
			}
		}
		if (cnt == 10) {
			HWND hwnd = GetForegroundWindow(); // 获取当前活动窗口的句柄
			SetForegroundWindow(hwnd);         // 将该窗口设置为前景窗口
			int result = MessageBox(hwnd, "发生车祸碰撞", "警告", MB_OK | MB_ICONWARNING);
			if (result == IDOK) {
				//cars[4].x -= 500;
				cars[0].y -= 80;
				boomm = 0;
				cnt = 0;
			}
		}

		if (startSybil && qqqq(emails, NumWindow) == true) {
			if (haveStrongerCar(cars) and NumWindow <= 5) {
				outtextxy(1400, 25, "未检测出Sybil攻击");
			}else{
				std::string filename = "score.txt";
				string precision, recall, accuracy, f1_score;
				extractScores(filename, NumWindow, precision, recall, accuracy, f1_score);
				char buffer1[50], buffer2[50], buffer3[50], buffer4[50];
				sprintf_s(buffer1, "Precision: %s", precision.c_str());
				outtextxy(1400, 25, buffer1);
				sprintf_s(buffer2, "Recall: %s", recall.c_str());
				outtextxy(1400, 40, buffer2);
				sprintf_s(buffer3, "Accuracy: %s", accuracy.c_str());
				outtextxy(1400, 55, buffer3);
				sprintf_s(buffer4, "F1-score: %s", f1_score.c_str());
				outtextxy(1400, 70, buffer4);
			}

		}


		char buffer[50]; // 定义一个足够大的缓冲区
		sprintf_s(buffer, "初始窗口数量为 %d", NumWindow); // 拼接字符串和整数
		outtextxy(1400, 10, buffer); // 将拼接后的字符串显示出来

		Car currentYellowCar = findYellowCar(cars, yellowCar);

		// 移动邮件
		move_emails(NumWindow, emails, cars, currentYellowCar, startSybil, startClear);


		// 绘制邮件到双缓冲区
		for (auto& email : emails) {
			putimage(email.x, email.y, &email.emailmaskImage, SRCAND);
			putimage(email.x, email.y, &email.emailoriginalImage, SRCPAINT);
		}

		// 绘制按钮
		gameButtonDraw1(StrongerButton, clearButton, DwindowButton, windowButton, startButton, stopButton, startClicked, sybilButton, sourceButton, sybilButton2);

		// 检测按钮点击
		allmousePeek(StrongerButton, Strongercarb, Strongercar, clearButton, startClear, startSybil, startSource, NumWindow, cars, emails, redcarb, redcar, startButton, stopButton, sybilButton,
			DwindowButton, windowButton, sourceButton, sybilButton2, yellowCar, startClicked, email, emailb);



		Sleep(100); // 控制车辆移动的速度
	}

	// 关闭图形模式
	closegraph();

	return 0;
}