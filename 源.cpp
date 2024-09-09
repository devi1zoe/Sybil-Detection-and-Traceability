#include <iostream>
#include <cstdlib>
#include <ctime>
#include <graphics.h> // ����ͼ�ο�ͷ�ļ�
#include <vector> // ���ͷ�ļ���֧�� vector
#include <cstring>
using namespace std;
#define WINDOWDX 1
#define WIDTH 1544 // ��Ļ���
#define HEIGHT 756 // ��Ļ�߶�
#define SPEED 1    // �����ƶ��ٶ�
#define EMSPEED 30


bool yidong = 0;//�жϳ����Ƿ������Դ���ϵͳ



// ���峵���ṹ��
struct Car {
    int index; // ��������
    int x;
    int y;
    int width;
    int height;
    IMAGE maskImage; // ��������ͼ��
    IMAGE originalImage; // ԭͼ��
    int moveDistance; // ���ڼ�¼�ƶ��ľ���
    bool isvirtual = false;
    bool isStronger = false;
    int emailcount = 0;
    int show = 0;
};
bool isSoureceShow = false;

// �����ŷ�ṹ��
struct Email {
    int x;
    int y;
    IMAGE emailmaskImage; // ��������ͼ��
    IMAGE emailoriginalImage; // ԭͼ��
    int startingCarIndex; // ������������
    bool isMovingToYellowCar;
    int emailcount = 0;
};



//��Ϸҳ��С��ť�ṹ��
struct smallbutton  //��ť������
{
    int x, y, r;   //���꣬�뾶
    COLORREF color;   //��ɫ
    char* str;        //�����ϵ��ַ�
};
struct smallbutton* createSmallButton(int x, int y, int r, COLORREF color, const char* str)    //��ʼ����ť����
{
    struct smallbutton* pa = (struct smallbutton*)malloc(sizeof(struct smallbutton));    //��̬����
    if (!pa)
        exit(-1);
    pa->x = x;   //�������xyr����ʼ��
    pa->y = y;
    pa->r = r;
    pa->color = color;
    pa->str = (char*)malloc(strlen(str) + 1);  //�����������ֳ����ǿɼ����ȣ����һ
    if (!pa->str)
        exit(-1);
    strcpy_s(pa->str, strlen(str) + 1, str); //�ַ�������
    return pa;
}




// ���һ����־���������ڸ����Ƿ����� "start" ��ť
int startClicked = 0;

// �޸� gameButtonDraw1 ������ֻ��ʾ start ��ť
void gameButtonDraw1(struct smallbutton* StrongerButton, struct smallbutton* clearButton, struct smallbutton* DwindowButton, struct smallbutton* windowButton, struct smallbutton* startButton,
    struct smallbutton* stopButton, int startClicked, struct smallbutton* sybilButton, struct smallbutton* sourceButton, struct smallbutton* sybilButton2) {
    BeginBatchDraw();

    // ���� start ��ť
    IMAGE img_start, img_startb;
    loadimage(&img_start, "./images/start.png");
    loadimage(&img_startb, "./images/startb.png");
    setfillcolor(startButton->color);
    solidcircle(startButton->x + 10, startButton->y + 10, startButton->r);
    setbkmode(TRANSPARENT);

    putimage(20, 20, &img_startb, SRCAND);
    putimage(20, 20, &img_start, SRCPAINT);
    outtextxy(startButton->x - 10, startButton->y + 35, "Attack!");

    // ���� start �������Ż��� stop ��ť
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


// ��鳵���Ƿ������г����ص�
bool isOverlap(const Car& car, const std::vector<Car>& cars) {
    for (const auto& otherCar : cars) {
        if (car.x < otherCar.x + otherCar.width &&
            car.x + car.width > otherCar.x &&
            car.y < otherCar.y + otherCar.height &&
            car.y + car.height > otherCar.y) {
            return true; // ���ص�
        }
    }
    return false; // û���ص�
}

// ����ʼ�λ���Ƿ������г������ʼ��ص�
bool isEmailOverlap(const Email& email, const std::vector<Email>& emails) {

    // ����ʼ�λ���Ƿ����ʼ��ص�
    for (const auto& otherEmail : emails) {
        if (&email != &otherEmail && // �ų�������Ƚ�
            email.x < otherEmail.x + 60 &&
            email.x + 60 > otherEmail.x &&
            email.y < otherEmail.y + 60 &&
            email.y + 60 > otherEmail.y) {
            return true; // ���ص�
        }
    }

    return false; // û���ص�
}


Car yellowcar_build(std::vector<Car>& cars, IMAGE& yellowcarb, IMAGE& yellowcar) {
    // ���س���ͼƬ
    loadimage(&yellowcarb, "./images/yellowb.png");
    loadimage(&yellowcar, "./images/yellow.png");

    // ������ɳ�����λ��
    srand(time(NULL)); // ʹ�õ�ǰʱ����Ϊ���������
    int yellowcarWidth = yellowcar.getwidth(); // ��ȡ����ͼƬ�Ŀ��
    int yellowcarHeight = yellowcar.getheight(); // ��ȡ����ͼƬ�ĸ߶�

    Car yellowCar;
    yellowCar.index = cars.size(); // ���ð�ɫ����������Ϊ��ǰ������С
    do {
		/*
        yellowCar.x = 500 + rand() % 100;
        yellowCar.y = 300 + rand() % 100;
		*/
		yellowCar.x = (WIDTH/5)*3+20;
		yellowCar.y = (HEIGHT/4)*2+ rand() % 30;
        yellowCar.width = yellowcarWidth;
        yellowCar.height = yellowcarHeight;
    } while (isOverlap(yellowCar, cars)); // ����Ƿ������г����ص�

    // �洢����ͼ���ԭͼ�� Car �ṹ����
    yellowCar.maskImage = yellowcarb;
    yellowCar.originalImage = yellowcar;

    // ���Ƴ���ͼƬ
    putimage(yellowCar.x, yellowCar.y, &yellowCar.maskImage, SRCAND);
    putimage(yellowCar.x, yellowCar.y, &yellowCar.originalImage, SRCPAINT);


    cars.push_back(yellowCar); // ���³������� vector
    return yellowCar;
}


void whitecar_build(std::vector<Car>& cars, std::vector<Email>& emails, IMAGE& whitecarb, IMAGE& whitecar, IMAGE& email, IMAGE& emailb) {
    // ���س���ͼƬ
    loadimage(&whitecarb, "./images/whiteb.png");
    loadimage(&whitecar, "./images/white.png");

    loadimage(&emailb, "./images/emailb.png");
    loadimage(&email, "./images/email.png");

    // ��ȡ����ͼƬ�Ŀ�Ⱥ͸߶�
    int whitecarWidth = whitecar.getwidth();
    int whitecarHeight = whitecar.getheight();

    Car whiteCar;
    whiteCar.index = cars.size(); // ���ð�ɫ����������Ϊ��ǰ������С
    Email whiteCarEmail;
    bool positionFound = false;

    srand(time(NULL)); // ʹ�õ�ǰʱ����Ϊ���������

    whiteCar.width = whitecarWidth;
    whiteCar.height = whitecarHeight;

    while (!positionFound) {
        // ���ѡ��һ������
		int region = rand() % 2;
		//cout << "��ǰrand" << region;
		switch (region) {
		case 0: // һ�ŵ�
			whiteCar.x = rand() % (WIDTH- whitecarWidth);
			whiteCarEmail.x = whiteCar.x + whiteCar.width / 2;
			whiteCar.y =0 + rand() % 50;
			whiteCarEmail.y = whiteCar.y + whiteCar.height / 2;
			break;
		case 1: // ���ŵ�
			whiteCar.x = rand() % (WIDTH - whitecarWidth);
			whiteCarEmail.x = whiteCar.x + whiteCar.width / 2;
			whiteCar.y = HEIGHT/4 + rand() % 50;
			whiteCarEmail.y = whiteCar.y + whiteCar.height / 2;
			break;
		}
	    /*
        int region = rand() % 4;
        switch (region) {
        case 0: // �Ϸ�����
            whiteCar.x = rand() % (WIDTH - whitecarWidth);
            whiteCarEmail.x = whiteCar.x + whiteCar.width / 2;
            whiteCar.y = rand() % 130;
            whiteCarEmail.y = whiteCar.y + whiteCar.height / 2;
            break;
        case 1: // �·�����
            whiteCar.x = rand() % (WIDTH - whitecarWidth);
            whiteCarEmail.x = whiteCar.x + whiteCar.width / 2;
            whiteCar.y = 600 + rand() % (HEIGHT - 600 - whitecarHeight);
            whiteCarEmail.y = whiteCar.y + whiteCar.height / 2;
            break;
        case 2: // �������
            whiteCar.x = rand() % 130;
            whiteCarEmail.x = whiteCar.x + whiteCar.width / 2;
            whiteCar.y = 130 + rand() % (600 - 130 - whitecarHeight);
            whiteCarEmail.y = whiteCar.y + whiteCar.height / 2;
            break;
        case 3: // �Ҳ�����
            whiteCar.x = 1200 + rand() % (WIDTH - 1200 - whitecarWidth);
            whiteCarEmail.x = whiteCar.x + whiteCar.width / 2;
            whiteCar.y = 130 + rand() % (600 - 130 - whitecarHeight);
            whiteCarEmail.y = whiteCar.y + whiteCar.height / 2;
            break;
        }
		*/


        // ����Ƿ������г����ص�
        if (!isOverlap(whiteCar, cars)) {
            positionFound = true;
        }

    }

    // �洢����ͼ���ԭͼ�� Car �ṹ����
    whiteCar.maskImage = whitecarb;
    whiteCar.originalImage = whitecar;
    whiteCarEmail.emailmaskImage = emailb;
    whiteCarEmail.emailoriginalImage = email;

    whiteCarEmail.startingCarIndex = whiteCar.index; // �洢������������

    // ���Ƴ���ͼƬ
    putimage(whiteCar.x, whiteCar.y, &whiteCar.maskImage, SRCAND);
    putimage(whiteCar.x, whiteCar.y, &whiteCar.originalImage, SRCPAINT);

    // �����ʼ�ͼƬ
    putimage(whiteCar.x, whiteCar.y, &whiteCarEmail.emailmaskImage, SRCAND);
    putimage(whiteCar.x, whiteCar.y, &whiteCarEmail.emailoriginalImage, SRCPAINT);

    cars.push_back(whiteCar); // ���³������� vector
    emails.push_back(whiteCarEmail);
}


void greencar_build(std::vector<Car>& cars, std::vector<Email>& emails, IMAGE& greencarb, IMAGE& greencar, IMAGE& email, IMAGE& emailb) {
    // ���س���ͼƬ
    loadimage(&greencarb, "./images/greenb.png");
    loadimage(&greencar, "./images/green.png");

    loadimage(&emailb, "./images/emailb.png");
    loadimage(&email, "./images/email.png");

    // ��ȡ����ͼƬ�Ŀ�Ⱥ͸߶�
    int greencarWidth = greencar.getwidth();
    int greencarHeight = greencar.getheight();

    Car greenCar;
    greenCar.index = cars.size(); // ���ð�ɫ����������Ϊ��ǰ������С
    Email greenCarEmail;
    bool positionFound = false;

    srand(time(NULL)); // ʹ�õ�ǰʱ����Ϊ���������

    greenCar.width = greencarWidth;
    greenCar.height = greencarHeight;

    while (!positionFound) {
        // ���ѡ��һ������
		int region = rand() % 3;
		switch (region) {
		case 0: // 1�ŵ�
			greenCar.x = rand() % (WIDTH - greencarWidth);
			greenCarEmail.x = greenCar.x + greenCar.width / 2;
			greenCar.y = rand() % 50;
			greenCarEmail.y = greenCar.y + greenCar.height / 2;
			break;
		case 1: // 2�ŵ�
			greenCar.x = rand() % (WIDTH - greencarWidth);
			greenCarEmail.x = greenCar.x + greenCar.width / 2;
			greenCar.y = HEIGHT/4 + rand() % 50;
			greenCarEmail.y = greenCar.y + greenCar.height / 2;
			break;
		case 2: // 3�ŵ�
			greenCar.x = rand() % (WIDTH - greencarWidth);
			greenCarEmail.x = greenCar.x + greenCar.width / 2;
			greenCar.y = (HEIGHT / 4)*2 + rand() % 50;
			greenCarEmail.y = greenCar.y + greenCar.height / 2;
			break;
		}

		/*
        int region = rand() % 4;
        switch (region) {
        case 0: // �Ϸ�����
            greenCar.x = rand() % (WIDTH - greencarWidth);
            greenCarEmail.x = greenCar.x + greenCar.width / 2;
            greenCar.y = rand() % 130;
            greenCarEmail.y = greenCar.y + greenCar.height / 2;
            break;
        case 1: // �·�����
            greenCar.x = rand() % (WIDTH - greencarWidth);
            greenCarEmail.x = greenCar.x + greenCar.width / 2;
            greenCar.y = 600 + rand() % (HEIGHT - 600 - greencarHeight);
            greenCarEmail.y = greenCar.y + greenCar.height / 2;
            break;
        case 2: // �������
            greenCar.x = rand() % 130;
            greenCarEmail.x = greenCar.x + greenCar.width / 2;
            greenCar.y = 130 + rand() % (600 - 130 - greencarHeight);
            greenCarEmail.y = greenCar.y + greenCar.height / 2;
            break;
        case 3: // �Ҳ�����
            greenCar.x = 1200 + rand() % (WIDTH - 1200 - greencarWidth);
            greenCarEmail.x = greenCar.x + greenCar.width / 2;
            greenCar.y = 130 + rand() % (600 - 130 - greencarHeight);
            greenCarEmail.y = greenCar.y + greenCar.height / 2;
            break;
        }
		*/


        // ����Ƿ������г����ص�
        if (!isOverlap(greenCar, cars)) {
            positionFound = true;
        }

    }

    // �洢����ͼ���ԭͼ�� Car �ṹ����
    greenCar.maskImage = greencarb;
    greenCar.originalImage = greencar;
    greenCarEmail.emailmaskImage = emailb;
    greenCarEmail.emailoriginalImage = email;

    greenCarEmail.startingCarIndex = greenCar.index; // �洢������������

    // ���Ƴ���ͼƬ
    putimage(greenCar.x, greenCar.y, &greenCar.maskImage, SRCAND);
    putimage(greenCar.x, greenCar.y, &greenCar.originalImage, SRCPAINT);

    // �����ʼ�ͼƬ
    putimage(greenCar.x, greenCar.y, &greenCarEmail.emailmaskImage, SRCAND);
    putimage(greenCar.x, greenCar.y, &greenCarEmail.emailoriginalImage, SRCPAINT);

    cars.push_back(greenCar); // ���³������� vector
    emails.push_back(greenCarEmail);
}

static int black_pos;

void blackcar_build(std::vector<Car>& cars, std::vector<Email>& emails, IMAGE& blackcarb, IMAGE& blackcar, IMAGE& email, IMAGE& emailb) {
    // ���س���ͼƬ
    loadimage(&blackcarb, "./images/blackb.png");
    loadimage(&blackcar, "./images/black.png");

    loadimage(&emailb, "./images/emailb.png");
    loadimage(&email, "./images/email.png");

    // ��ȡ����ͼƬ�Ŀ�Ⱥ͸߶�
    int blackcarWidth = blackcar.getwidth();
    int blackcarHeight = blackcar.getheight();

    Car blackCar;
    blackCar.index = cars.size(); // ���ð�ɫ����������Ϊ��ǰ������С
    Email blackCarEmail;
    bool positionFound = false;

    srand(time(NULL)); // ʹ�õ�ǰʱ����Ϊ���������

    blackCar.width = blackcarWidth;
    blackCar.height = blackcarHeight;

    while (!positionFound) {
        // ���ѡ��һ������
			blackCar.x = (WIDTH / 5) * 3 - 210;
			blackCarEmail.x = blackCar.x + blackCar.width / 2;
			blackCar.y = (HEIGHT / 4) * 3 + rand() % 50;
			blackCarEmail.y = blackCar.y + blackCar.height / 2;
		/*
		int region = rand() % 2;
		switch (region) {
		case 0: // �Ϸ�����
			blackCar.x = rand() % (WIDTH - blackcarWidth);
			blackCarEmail.x = blackCar.x + blackCar.width / 2;
			blackCar.y = (HEIGHT / 4) * 2+rand() % 50;
			blackCarEmail.y = blackCar.y + blackCar.height / 2;
			break;
		case 1: // �·�����
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
        case 0: // �Ϸ�����
            blackCar.x = rand() % (WIDTH - blackcarWidth);
            blackCarEmail.x = blackCar.x + blackCar.width / 2;
            blackCar.y = rand() % 130;
            blackCarEmail.y = blackCar.y + blackCar.height / 2;
            break;
        case 1: // �·�����
            blackCar.x = rand() % (WIDTH - blackcarWidth);
            blackCarEmail.x = blackCar.x + blackCar.width / 2;
            blackCar.y = 600 + rand() % (HEIGHT - 600 - blackcarHeight);
            blackCarEmail.y = blackCar.y + blackCar.height / 2;
            break;
        case 2: // �������
            blackCar.x = rand() % 130;
            blackCarEmail.x = blackCar.x + blackCar.width / 2;
            blackCar.y = 130 + rand() % (600 - 130 - blackcarHeight);
            blackCarEmail.y = blackCar.y + blackCar.height / 2;
            break;
        case 3: // �Ҳ�����
            blackCar.x = 1200 + rand() % (WIDTH - 1200 - blackcarWidth);
            blackCarEmail.x = blackCar.x + blackCar.width / 2;
            blackCar.y = 130 + rand() % (600 - 130 - blackcarHeight);
            blackCarEmail.y = blackCar.y + blackCar.height / 2;
            break;
        }
		*/


        // ����Ƿ������г����ص�
        if (!isOverlap(blackCar, cars)) {
            positionFound = true;
        }

    }

    // �洢����ͼ���ԭͼ�� Car �ṹ����
    blackCar.maskImage = blackcarb;
    blackCar.originalImage = blackcar;
    blackCarEmail.emailmaskImage = emailb;
    blackCarEmail.emailoriginalImage = email;

    blackCarEmail.startingCarIndex = blackCar.index; // �洢������������

    // ���Ƴ���ͼƬ
    putimage(blackCar.x, blackCar.y, &blackCar.maskImage, SRCAND);
    putimage(blackCar.x, blackCar.y, &blackCar.originalImage, SRCPAINT);

    // �����ʼ�ͼƬ
    putimage(blackCar.x, blackCar.y, &blackCarEmail.emailmaskImage, SRCAND);
    putimage(blackCar.x, blackCar.y, &blackCarEmail.emailoriginalImage, SRCPAINT);

    cars.push_back(blackCar); // ���³������� vector
    emails.push_back(blackCarEmail);
}


void redcar_build(std::vector<Car>& cars, std::vector<Email>& emails, IMAGE& redcarb, IMAGE& redcar, IMAGE& email, IMAGE& emailb) {
    // ���س���ͼƬ
    loadimage(&redcarb, "./images/redb.png");
    loadimage(&redcar, "./images/red.png");

    loadimage(&emailb, "./images/emailb.png");
    loadimage(&email, "./images/email.png");

    // ������ɳ�����λ��
    srand(time(NULL)); // ʹ�õ�ǰʱ����Ϊ���������
    int redcarWidth = redcar.getwidth(); // ��ȡ����ͼƬ�Ŀ��
    int redcarHeight = redcar.getheight(); // ��ȡ����ͼƬ�ĸ߶�

    Car redCar;
    redCar.index = cars.size(); // ���ð�ɫ����������Ϊ��ǰ������С
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
    } while (isOverlap(redCar, cars)); // ����Ƿ������г����ص�

    // �洢����ͼ���ԭͼ�� Car �ṹ����
    redCar.maskImage = redcarb;
    redCar.originalImage = redcar;
    redCarEmail.emailmaskImage = emailb;
    redCarEmail.emailoriginalImage = email;

    redCarEmail.startingCarIndex = redCar.index; // �洢������������


    // ���Ƴ���ͼƬ
    putimage(redCar.x, redCar.y, &redCar.maskImage, SRCAND);
    putimage(redCar.x, redCar.y, &redCar.originalImage, SRCPAINT);

    // �����ʼ�ͼƬ
    putimage(redCarEmail.x, redCarEmail.y, &redCarEmail.emailmaskImage, SRCAND);
    putimage(redCarEmail.x, redCarEmail.y, &redCarEmail.emailoriginalImage, SRCPAINT);

    cars.push_back(redCar); // ���³������� vector
    emails.push_back(redCarEmail);
}


void Strongercar_build(std::vector<Car>& cars, std::vector<Email>& emails, IMAGE& Strongercarb, IMAGE& Strongercar, IMAGE& email, IMAGE& emailb) {
    // ���س���ͼƬ
    loadimage(&Strongercarb, "./images/StrongerCarb.png");
    loadimage(&Strongercar, "./images/StrongerCar.png");

    loadimage(&emailb, "./images/emailb.png");
    loadimage(&email, "./images/email.png");

    // ������ɳ�����λ��
    srand(time(NULL)); // ʹ�õ�ǰʱ����Ϊ���������
    int StrongercarWidth = Strongercar.getwidth(); // ��ȡ����ͼƬ�Ŀ��
    int StrongercarHeight = Strongercar.getheight(); // ��ȡ����ͼƬ�ĸ߶�

    Car Strongercar1;
    Strongercar1.index = cars.size(); // ���ð�ɫ����������Ϊ��ǰ������С
    Strongercar1.isStronger = true;
    Email StrongercarEmail;
    do {
        Strongercar1.x = 1200;
        StrongercarEmail.x = Strongercar1.x + StrongercarWidth / 2 - 30;
        Strongercar1.y = rand() % (HEIGHT - StrongercarHeight);
        StrongercarEmail.y = Strongercar1.y + StrongercarHeight / 2 - 30;
        Strongercar1.width = StrongercarWidth;
        Strongercar1.height = StrongercarHeight;
    } while (isOverlap(Strongercar1, cars)); // ����Ƿ������г����ص�

    // �洢����ͼ���ԭͼ�� Car �ṹ����
    Strongercar1.maskImage = Strongercarb;
    Strongercar1.originalImage = Strongercar;
    StrongercarEmail.emailmaskImage = emailb;
    StrongercarEmail.emailoriginalImage = email;

    StrongercarEmail.startingCarIndex = Strongercar1.index; // �洢������������

    // ���Ƴ���ͼƬ
    putimage(Strongercar1.x, Strongercar1.y, &Strongercar1.maskImage, SRCAND);
    putimage(Strongercar1.x, Strongercar1.y, &Strongercar1.originalImage, SRCPAINT);

    // �����ʼ�ͼƬ
    putimage(StrongercarEmail.x, StrongercarEmail.y, &StrongercarEmail.emailmaskImage, SRCAND);
    putimage(StrongercarEmail.x, StrongercarEmail.y, &StrongercarEmail.emailoriginalImage, SRCPAINT);

    cars.push_back(Strongercar1); // ���³������� vector
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
    // ���δ�ҵ��쳵���򷵻�һ��Ĭ�Ϲ���ĳ�������
    return Car{};
}


void virtualcar_build(std::vector<Car>& cars, std::vector<Email>& emails, IMAGE& virtualcarb, IMAGE& virtualcar, const Car& yellowCar, IMAGE& email, IMAGE& emailb) {
    if (haveStrongerCar(cars)) {
        // ���س���ͼƬ
        loadimage(&virtualcarb, "./images/Strongervirtualb.png");
        loadimage(&virtualcar, "./images/Strongervirtual.png");
    }
    else {
        // ���س���ͼƬ
        loadimage(&virtualcarb, "./images/virtualb.png");
        loadimage(&virtualcar, "./images/virtual.png");

    }

    // ��ȡ����ͼƬ�Ŀ�Ⱥ͸߶�
    int virtualcarWidth = virtualcar.getwidth();
    int virtualcarHeight = virtualcar.getheight();

    // �����ĸ������������⳵��
    for (int i = 0; i < 3; ++i) {
        Car virtualCar;
        virtualCar.index = cars.size(); // ���ð�ɫ����������Ϊ��ǰ������С
        bool positionFound = false;

        // �������⳵���ĳ�ʼλ��
        switch (i) {
        case 0: // �Ϸ�����
            virtualCar.x = yellowCar.x;
            virtualCar.y = yellowCar.y - virtualcarHeight - 20;
            virtualCar.isvirtual = true;
            break;
		/*
        case 1: // �·�����
            virtualCar.x = yellowCar.x;
            virtualCar.y = yellowCar.y + yellowCar.height + 20;
            virtualCar.isvirtual = true;
            break;
		*/
        case 1: // �������
            virtualCar.x = yellowCar.x - virtualcarWidth - 20;
            virtualCar.y = yellowCar.y;
            virtualCar.isvirtual = true;
            break;
        case 2: // �Ҳ�����
            virtualCar.x = yellowCar.x + yellowCar.width + 20;
            virtualCar.y = yellowCar.y;
            virtualCar.isvirtual = true;
            break;
        }

        // ����λ����ȷ������Ļ��
        virtualCar.x = max(0, min(WIDTH - virtualcarWidth, virtualCar.x));
        virtualCar.y = max(0, min(HEIGHT - virtualcarHeight, virtualCar.y));

        virtualCar.width = virtualcarWidth;
        virtualCar.height = virtualcarHeight;

        // ����Ƿ������г����ص�
        if (!isOverlap(virtualCar, cars)) {
            // ���δ�ص��������⳵����ӵ� vector ��
            virtualCar.maskImage = virtualcarb;
            virtualCar.originalImage = virtualcar;
            putimage(virtualCar.x, virtualCar.y, &virtualCar.maskImage, SRCAND);
            putimage(virtualCar.x, virtualCar.y, &virtualCar.originalImage, SRCPAINT);
            cars.push_back(virtualCar);



        }
    }


    // ��ȡ��ǰʱ����Ϊ�������
    unsigned int seed = static_cast<unsigned int>(std::time(nullptr));

    // �����������
    srand(seed);

    int numEmails = countVirtualCars(cars);
    /*std::cout << numEmails;*/
    for (int j = 0; j < numEmails; ++j) {
        Email virtualCarEmail;

        // �������⳵���������ʼ�λ��
        Car redCar = findRedCar(cars);
        int offsetX, offsetY;
        offsetX = rand() % 100; // �������ƫ����
        offsetY = rand() % 100; // �������ƫ����
        virtualCarEmail.x = redCar.x + redCar.width / 2 - 30 + offsetX; // �����ʼ����Ϊ60
        virtualCarEmail.y = redCar.y + redCar.height / 2 - 30 + offsetY; // �����ʼ��߶�Ϊ60


        // �洢����ͼ���ԭͼ�� Email �ṹ����
        virtualCarEmail.emailmaskImage = emailb;
        virtualCarEmail.emailoriginalImage = email;

        // �����ʼ��ķ���������
        virtualCarEmail.startingCarIndex = 5;

        // ���ʼ����� vector
        emails.push_back(virtualCarEmail);
    }

}

#include <windows.h> // ���� Windows API ��������
// ����������������ǰӦ�ó���
void RestartApplication() {
	TCHAR szFilePath[MAX_PATH];
	GetModuleFileName(NULL, szFilePath, MAX_PATH); // ��ȡ��ǰ���̵�·��

	// �����½���
	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi;
	if (CreateProcess(szFilePath, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
		// �رվ��
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
		ExitProcess(0); // �˳���ǰ����
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
				HWND hwnd = GetForegroundWindow(); // ��ȡ��ǰ����ڵľ��
				SetForegroundWindow(hwnd);         // ���ô�������Ϊǰ������
				int result=MessageBox(hwnd, "����������ײ", "����", MB_OK | MB_ICONWARNING);
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
        car.x -= SPEED; // ÿ���������ƶ����ٶ�Ϊ SPEED
		if (cars[5]) {
			cars[0].y += SPEED;
			if (cars[0].y + cars[0].height < 0) {
				cars[0]. = WIDTH; // �������Ƶ������Ҳ�
			}
		}
        car.moveDistance += SPEED; // ��¼�ƶ��ľ���
        // ��鳵���Ƿ񳬳����ڱ߽磬����������������Ƶ�������һ��
        if (car.x + car.width < 0) {
            car.x = WIDTH; // �������Ƶ������Ҳ�
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



bool malicious=0;//�ж��Ƿ���Դ��ť

bool canPause1 = 0, canPause2 = 0;
// �޸� allmousePeek ����������ť����¼�
void allmousePeek(struct smallbutton* StrongerButton, IMAGE& Strongercarb, IMAGE& Strongercar, struct smallbutton* clearButton, int& startClear, int& startSybil, int& startSource, int& NumWindow, std::vector<Car>& cars, std::vector<Email>& emails,
    IMAGE& redcarb, IMAGE& redcar, struct smallbutton* startButton, struct smallbutton* stopButton, struct smallbutton* sybilButton, struct smallbutton* sybilButton2,
    struct smallbutton* DwindowButton, struct smallbutton* windowButton, struct smallbutton* sourceButton, const Car& yellowCar, int& startClicked, IMAGE& email, IMAGE& emailb) {
    ExMessage mssg;
    while (peekmessage(&mssg, EM_MOUSE)) {
        switch (mssg.message) {
        case WM_LBUTTONDOWN:
            if (!canPause1 && (mssg.x - startButton->x) * (mssg.x - startButton->x) + (mssg.y - startButton->y) * (mssg.y - startButton->y) <= startButton->r * startButton->r) {

				// �������� start ��ť��ִ�� start ��ť�Ĳ���
                startClear = 0;
                startClicked = 1;
                canPause1 = 1;
                redcar_build(cars, emails, redcarb, redcar, email, emailb);
                
            }
            else if (startClicked == 1 && (mssg.x - sybilButton->x) * (mssg.x - sybilButton->x) + (mssg.y - sybilButton->y) * (mssg.y - sybilButton->y) <= sybilButton->r * sybilButton->r) {
                //std::cout << "�����ⰴť��"<<endl;
                startSybil = 1;
            }
            else if (startClicked == 1 && isSoureceShow == true && (mssg.x - sourceButton->x) * (mssg.x - sourceButton->x) + (mssg.y - sourceButton->y) * (mssg.y - sourceButton->y) <= sourceButton->r * sourceButton->r) {
				//MessageBox(NULL, "����������ײ", "����", MB_OK | MB_ICONWARNING);
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

                // ɾ����ó�����ص��ʼ�
                for (auto it = emails.begin(); it != emails.end(); ) {
                    if (it->startingCarIndex == cc.index) {
                        it = emails.erase(it); // ʹ�õ�����ɾ��Ԫ��
                    }
                    else {
                        ++it;
                    }
                }   

                // ɾ����ó�����ص����⳵
                for (auto it = cars.begin(); it != cars.end(); ) {
                    if (it->isvirtual == true) {
                        it->isvirtual = false;
                        it = cars.erase(it); // ʹ�õ�����ɾ��Ԫ��
                    }
                    else {
                        ++it;
                    }
                }
                // ɾ������
                cars.erase(cars.begin() + cc.index);


            }
            else if (startClear == 1 && (mssg.x - StrongerButton->x) * (mssg.x - StrongerButton->x) + (mssg.y - StrongerButton->y) * (mssg.y - StrongerButton->y) <= StrongerButton->r * StrongerButton->r) {
               Strongercar_build(cars, emails, Strongercarb, Strongercar, email, emailb);
               startClicked == 1;
               canPause2 = 0;
            }
            else if (!canPause2 && startClicked == 1 && (mssg.x - stopButton->x) * (mssg.x - stopButton->x) + (mssg.y - stopButton->y) * (mssg.y - stopButton->y) <= stopButton->r * stopButton->r) {
                canPause2 = 1;
                // ��ȡ��ǰ�Ƴ�λ��
                Car currentYellowCar = findYellowCar(cars, yellowCar);
                // �������� stop ��ť��ִ�� stop ��ť�Ĳ���
                if (haveStrongerCar(cars)) {
                    //MessageBox(NULL, "���Լ�⵽��ǿ�����ߣ���һ���Ǵ���Sybil��", "����", MB_OK | MB_ICONERROR);
                    virtualcar_build(cars, emails, Strongercarb, Strongercar, currentYellowCar, email, emailb);
                    startClicked == 1;
                }
                else
                    virtualcar_build(cars, emails, redcarb, redcar, currentYellowCar, email, emailb);
            }
            break;
            // ���������Ϣ���͵Ĵ���
        default:
            break;
        }
    }
}

void drawConnections(const std::vector<Car>& cars, const Car& yellowCar) {
    setlinecolor(RGB(255, 255, 255)); // ����������ɫΪ��ɫ
    setlinestyle(PS_SOLID, 3); // ����������ʽΪʵ�ߣ���ϸΪ3����

    // ��ȡ�Ƴ���ǰλ��
    Car currentYellowCar = findYellowCar(cars, yellowCar);
    int yellowCarX = currentYellowCar.x + currentYellowCar.width / 2;
    int yellowCarY = currentYellowCar.y + currentYellowCar.height / 2;

    for (const auto& car : cars) {
        if (car.x != currentYellowCar.x && car.y != currentYellowCar.y && car.isvirtual != true) { // �ų��Ƴ�
            // �����յ����꣨�������ĵ㣩
            int endX = car.x + car.width / 2;
            int endY = car.y + car.height / 2;

            // ��������
            line(yellowCarX, yellowCarY, endX, endY);
        }
    }
}


void move_emails(int& NumWindow, std::vector<Email>& emails, std::vector<Car>& cars, const Car& yellowCar, int& startSybil, int& startClear) {
    // ��ȡ�Ƴ�����������
    int yellowCarCenterX = yellowCar.x + yellowCar.width / 2;
    int yellowCarCenterY = yellowCar.y + yellowCar.height / 2;

    for (auto& email : emails) {

        // �����ʼ���������
        int emailCenterX = email.x + 30; // �����ʼ��Ŀ��Ϊ60���������ĵ�ƫ����Ϊ30
        int emailCenterY = email.y + 30; // �����ʼ��ĸ߶�Ϊ60���������ĵ�ƫ����Ϊ30

        // ���㷽������
        int deltaX = yellowCarCenterX - emailCenterX;
        int deltaY = yellowCarCenterY - emailCenterY;

        // ������������
        float length = sqrt(deltaX * deltaX + deltaY * deltaY);

        // ��һ����������
        float normalizedX = deltaX / length;
        float normalizedY = deltaY / length;

        // �ƶ����룬���Ը�����Ҫ�����ٶ�
        float moveDistance = EMSPEED;

        // �����ʼ�λ��
        email.x += static_cast<int>(normalizedX * moveDistance);
        email.y += static_cast<int>(normalizedY * moveDistance);

        // ����ʼ��Ƿ񵽴�Ƴ���������������һ�����̷�Χ
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
            // ���ʼ�λ���趨Ϊ���𳵵�ǰλ��
            int offsetX = rand() % 50; // �������ƫ����
            int offsetY = rand() % 50; // �������ƫ����
            email.x = sendingCar.x + sendingCar.width / 2 - 25 + offsetX;
            email.y = sendingCar.y + sendingCar.height / 2 - 25 + offsetY;

        }


        // ����ʼ��Ƿ񳬳����ڱ߽磬������������ʼ��Ƶ�������һ��
        if (email.x + 600 < 0) {
            email.x = WIDTH; // ���ʼ��Ƶ������Ҳ�
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
#include <sstream> // ���ͷ�ļ���ʹ�� std::stringstream
// ����ṹ��
struct Result {
    int no;
    int index;
    int label;
};

// ��ȡ����ļ�
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
// ��ȡ������Ӧ�Ľ��
std::string getLabelForCar(const std::vector<Result>& results, int carIndex) {
    for (const auto& result : results) {
        if (result.no == carIndex) {
            if (result.label == 0) return "�������ͣ���������";
            if (result.label == 1) return "�������ͣ�Ů�׳���";
            if (result.label == 2) return malicious==0? "�������ͣ���������":"�������ͣ����⳵��";

        }
    }
    return "-1"; // û���ҵ���Ӧ�Ľ��
}

std::string getRealLabelForCar(const std::vector<Result>& results, int carIndex) {
    for (const auto& result : results) {
        if (result.no == carIndex) {
            return "Sender:" + std::to_string(result.index).substr(2, 5) + "  label:" + std::to_string(result.label);
        }
    }
    return "-1"; // û���ҵ���Ӧ�Ľ��
}

std::string getPreLabelForCar(const std::vector<Result>& results, int carIndex) {
    for (const auto& result : results) {
        if (result.no == carIndex) {
            return "label:" + std::to_string(result.label);
        }
    }
    return "-1"; // û���ҵ���Ӧ�Ľ��
}

#include <thread>

// ����һ������������Python�ű�
void runPythonScript1() {
    system("python test.py");
}


void extractScores(const std::string& filename, int NumWindow, string& precision, string& recall, string& accuracy, string& f1_score) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "�޷����ļ�: " << filename << std::endl;
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
        std::cerr << "�ļ��еķ������ݲ��㡣" << std::endl;
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






// �޸���ѭ���еİ�ť���ƺ͵�����
int main() {
	// ��ʼ��ͼ��ģʽ
	initgraph(WIDTH, HEIGHT);

	// ����˫������ͼ��
	IMAGE backBuffer;
	initgraph(WIDTH, HEIGHT);

	// ����ͼƬ
	IMAGE home_background;
	loadimage(&home_background, "./images/road.jpg");

	// ����ͼƬ
	putimage(0, 0, &home_background);
	std::vector<Result> results = readResults("result.txt");

	// ���峵��ͼƬ����
	IMAGE yellowcar, yellowcarb, whitecar, whitecarb, whitecarb1, whitecar1, redcarb, redcar, greencar, greencarb, blackcarb, blackcar, Strongercarb, Strongercar;
	IMAGE email, emailb;
	std::vector<Car> cars;
	std::vector<Email> emails;

	// ������ɫ����������������
	Car yellowCar = yellowcar_build(cars, yellowcarb, yellowcar);
	yellowCar.index = 0; // ���û�ɫ����������Ϊ0

	whitecar_build(cars, emails, whitecarb, whitecar, email, emailb);
	whitecar_build(cars, emails, whitecarb1, whitecar1, email, emailb);
	greencar_build(cars, emails, greencarb, greencar, email, emailb);
	blackcar_build(cars, emails, blackcarb, blackcar, email, emailb);
	int NumWindow = 2;

	// ������һ����ť
	struct smallbutton* startButton = createSmallButton(25, 25, 25, RGB(23, 23, 23), "redcar");
	// �����ڶ�����ť
	struct smallbutton* stopButton = createSmallButton(85, 25, 25, RGB(23, 23, 23), "virtualcar");
	// ������������ť
	struct smallbutton* sybilButton = createSmallButton(145, 25, 25, RGB(23, 23, 23), "sybil");
	// �������ĸ���ť
	struct smallbutton* sourceButton = createSmallButton(205, 25, 25, RGB(23, 23, 23), "Increase");
	// �����������ť
	struct smallbutton* windowButton = createSmallButton(265, 25, 25, RGB(23, 23, 23), "Reduce");
	// ������������ť
	struct smallbutton* DwindowButton = createSmallButton(325, 25, 25, RGB(23, 23, 23), "shift");
	// �������߸���ť
	struct smallbutton* clearButton = createSmallButton(385, 25, 25, RGB(23, 23, 23), "Clear");
	// �����ڰ˸���ť
	struct smallbutton* StrongerButton = createSmallButton(445, 25, 25, RGB(23, 23, 23), "Stronger");
	// �����ھŸ���ť
	struct smallbutton* sybilButton2 = createSmallButton(505, 25, 25, RGB(23, 23, 23), "source");

	// ��־������ʼ��
	int startClicked = 0;

	bool isMovingToYellowCar = true; // ��ʼ״̬Ϊ��Ƴ��ƶ�

	// ����һ�����߳�������Python�ű�
	std::thread pythonThread1(runPythonScript1);

	// ������ȴ�Python�ű�ִ����ϣ������������߳�
	pythonThread1.detach();

	int startSybil = 0, startSource = 0, startClear = 0;

	//��ըЧ��
	IMAGE boom, boomb;
	loadimage(&boomb, "./images/boomb.jpg");
	loadimage(&boom, "./images/boom.jpg");
	// ��ʼͼ�����������
	static double scale = 0.2;
	// ͼ��Ŵ�Ĳ���
	static double scaleStep = 0.1;
	// �����������
	static double maxScale = 4.0;
	static int cnt = 0;
	int centerX = (cars[0].x + cars[4].x) / 2;
	int centerY = cars[4].y;

	while (1) {
		// ���˫������
		cleardevice();

		// ���Ʊ���ͼ��˫������
		putimage(0, 0, &home_background, SRCCOPY);

		// �ƶ�����
		if (yidong == 0) {
			move_cars(cars);
		}
		else {
			move_cars2(cars);
		}

		Car cc = findRedCar(cars);
		// ��ȡ�Ƴ���ǰλ��
		int RedCarX = cc.x - 10;
		int RedCarY = cc.y - 10;
		// �����յ����꣨�������ĵ㣩
		int endX = cc.x + cc.width + 10;
		int endY = cc.y + cc.height + 10;
		//std::cout << " " << RedCarX << " " << RedCarY << " " << endX << " " << endY << std::endl;
		// ��������
		if (startSource == 1) rectangle(RedCarX, RedCarY, endX, endY);



		int ss = 0;
		// ���Ƴ�����˫������
		for (const auto& car : cars) {

			putimage(car.x, car.y, &car.maskImage, SRCAND);
			putimage(car.x, car.y, &car.originalImage, SRCPAINT);
			//std::cout << car.show << " ";
			if (car.show == 1 || (car.isvirtual == true && cc.show == 1)) {
				// ��ȡ������Ӧ�Ľ��
				std::string label = getLabelForCar(results, car.index);
				// �ڳ�������λ����ʾ���
				if (label != "-1") {
					int centerX = car.x + 30;
					int centerY = car.y + car.height - 5;
					// ��ͼ�δ�������ʾ��������������ʹ�õ��� EasyX ͼ�ο�
					// �ڳ�������λ����ʾ���
					std::string labelStr = label;
					if (startClear == 0 and !haveStrongerCar(cars) || (haveStrongerCar(cars) and NumWindow > 5)) outtextxy(centerX, centerY, labelStr.c_str());
					else outtextxy(centerX, centerY, "�������ͣ���������");
					//std::cout << car.emailcount << " ";
					if (car.index == 5) isSoureceShow = 1;
				}
			}

		}

		//��ըЧ��
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
				// ����ͼ���С
				putimage(xx, yy, &b, SRCAND);
				putimage(xx, yy, &a, SRCPAINT);
				// ˢ�»���
				Sleep(0);
				// ������������
				scale += scaleStep;
				cnt++;
			}
		}
		if (cnt == 10) {
			HWND hwnd = GetForegroundWindow(); // ��ȡ��ǰ����ڵľ��
			SetForegroundWindow(hwnd);         // ���ô�������Ϊǰ������
			int result = MessageBox(hwnd, "����������ײ", "����", MB_OK | MB_ICONWARNING);
			if (result == IDOK) {
				//cars[4].x -= 500;
				cars[0].y -= 80;
				boomm = 0;
				cnt = 0;
			}
		}

		if (startSybil && qqqq(emails, NumWindow) == true) {
			if (haveStrongerCar(cars) and NumWindow <= 5) {
				outtextxy(1400, 25, "δ����Sybil����");
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


		char buffer[50]; // ����һ���㹻��Ļ�����
		sprintf_s(buffer, "��ʼ��������Ϊ %d", NumWindow); // ƴ���ַ���������
		outtextxy(1400, 10, buffer); // ��ƴ�Ӻ���ַ�����ʾ����

		Car currentYellowCar = findYellowCar(cars, yellowCar);

		// �ƶ��ʼ�
		move_emails(NumWindow, emails, cars, currentYellowCar, startSybil, startClear);


		// �����ʼ���˫������
		for (auto& email : emails) {
			putimage(email.x, email.y, &email.emailmaskImage, SRCAND);
			putimage(email.x, email.y, &email.emailoriginalImage, SRCPAINT);
		}

		// ���ư�ť
		gameButtonDraw1(StrongerButton, clearButton, DwindowButton, windowButton, startButton, stopButton, startClicked, sybilButton, sourceButton, sybilButton2);

		// ��ⰴť���
		allmousePeek(StrongerButton, Strongercarb, Strongercar, clearButton, startClear, startSybil, startSource, NumWindow, cars, emails, redcarb, redcar, startButton, stopButton, sybilButton,
			DwindowButton, windowButton, sourceButton, sybilButton2, yellowCar, startClicked, email, emailb);



		Sleep(100); // ���Ƴ����ƶ����ٶ�
	}

	// �ر�ͼ��ģʽ
	closegraph();

	return 0;
}