#include "galgame.h"

GameWindow::GameWindow(QWidget *parent)
    : QWidget(parent),
    favorability(30),
    currentState(S_START),
    m_inDialogue(false)
{
    setWindowTitle("旮旯根木不会发生到我身上！");
    setMinimumSize(600,200 );

    // 文本显示区域
    textDisplay = new QTextEdit(this);
    textDisplay->setReadOnly(true);
    textDisplay->setStyleSheet("font-size: 14px; font-family: 'Microsoft YaHei';");

    // 按钮
    continueButton = new QPushButton("继续 (F)", this);
    option1Button = new QPushButton("选项1", this);
    option2Button = new QPushButton("选项2", this);
    option3Button = new QPushButton("选项3", this);
    restartButton = new QPushButton("重新开始", this);
    quitButton = new QPushButton("退出", this);

    // 布局
    mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(textDisplay);

    buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(continueButton);
    buttonLayout->addWidget(option1Button);
    buttonLayout->addWidget(option2Button);
    buttonLayout->addWidget(option3Button);
    buttonLayout->addWidget(restartButton);
    buttonLayout->addWidget(quitButton);
    buttonLayout->addStretch();
    mainLayout->addLayout(buttonLayout);

    // 信号连接
    connect(continueButton, &QPushButton::clicked, this, &GameWindow::onContinueClicked);
    connect(option1Button, &QPushButton::clicked, this, &GameWindow::onOption1Clicked);
    connect(option2Button, &QPushButton::clicked, this, &GameWindow::onOption2Clicked);
    connect(option3Button, &QPushButton::clicked, this, &GameWindow::onOption3Clicked);
    connect(restartButton, &QPushButton::clicked, this, &GameWindow::onRestartClicked);
    connect(quitButton, &QPushButton::clicked, this, &GameWindow::onQuitClicked);

    resetGame();
}

GameWindow::~GameWindow()
{
}

void GameWindow::resetGame()
{
    favorability = 30;
    m_dialogueQueue.clear();
    m_inDialogue = false;
    setState(S_START);
}

void GameWindow::setState(StoryState state)
{
    currentState = state;
    updateUI();
}

void GameWindow::updateUI()
{
    // 隐藏所有按钮
    continueButton->hide();
    option1Button->hide();
    option2Button->hide();
    option3Button->hide();
    restartButton->hide();
    quitButton->hide();

    // 如果正处于对话队列，保持文本并只显示继续按钮
    if (m_inDialogue) {
        continueButton->show();
        return;
    }

    switch (currentState) {
    case S_START:
        textDisplay->setText(
            ">>欢迎试玩本款校园实感剧情向游戏，本故事实有loophole，难调众口。如有巧合，纯属雷同。<<\n\n");
        continueButton->show();
        break;

    case S_INTRO:
        textDisplay->setText(
            "你是一个fvv大学生，突然有一天，你的班里来了一位转校生...\n");
        continueButton->show();
        break;

    case S_TRANSFER_ASK:
        textDisplay->setText(
            "\"你好，同学，没有别的位置了，我可以做你旁边吗...\"\n"
            "\"啊...我吗...\"\n");
        continueButton->show();
        break;

    case S_FIRST_CHOICE:
        textDisplay->setText(
            "1.欣然答应 \n2.犹豫不决后再答应 \n3.严词拒绝\n");
        option1Button->setText("欣然答应");
        option2Button->setText("犹豫后再答应");
        option3Button->setText("严词拒绝");
        option1Button->show();
        option2Button->show();
        option3Button->show();
        break;

    case S_AFTER_ACCEPT:
        textDisplay->setText(
            "\"当然可以啦。\" 你望着面前的同学说道。\n"
            "\"谢谢同学，以后请多关照哦...\"\n");
        continueButton->show();
        break;

    case S_SUNLIGHT:
        textDisplay->setText(
            "阳光斜切过墨绿黑板，粉笔灰在光柱里缓缓沉降。\n");
        continueButton->show();
        break;

    case S_NOTEBOOK:
        textDisplay->setText(
            "我盯着笔记本上洇开的墨点出神，余光里她的指尖无意摩挲着橡皮，"
            "洗发水的淡淡香气混着旧书页的味道漫过来，衣袖不经意擦过我的手背，"
            "留下一点温热的痒。笔尖在纸上沙沙走着，像某种细小的、共享的心跳。\n");
        continueButton->show();
        break;

    case S_NEED_HELP:
        textDisplay->setText(
            "\"哎，如果要是谁能给我补一补之前的功课就好了...\" 她喃喃道。\n");
        continueButton->show();
        break;

    case S_SECOND_CHOICE:
        textDisplay->setText(
            "1.（主动请缨）\"我来吧，我正好有空暇。\"\n"
            "2.（旁敲侧击）内心默默记下，在暗中帮助她。\n"
            "3.（无视）\"是这样呢，不好好补课可不行。\"\n");
        option1Button->setText("主动请缨");
        option2Button->setText("暗中帮助");
        option3Button->setText("无视");
        option1Button->show();
        option2Button->show();
        option3Button->show();
        break;

    case S_POST_CHOICE_COMMON:
        // 无新文本，仅显示继续按钮
        continueButton->show();
        break;

    case S_EVENING_HOME:
    {
        QStringList sequence;
        // 第一段回家话
        sequence << "一个平常的夜晚，你照常上完晚自习准备回家，独处的你早就习惯了一个人走着空寂的巷子。";
        if (favorability >= 50) {
            sequence << "但这一次，沈冰悦叫住了你。\n"
                        "\"那个...我记得你家是在镇上住吧...我家也在那里，要不要一起回去？\" "
                        "她微微低着头，发梢遮住了她的眼睛，却遮不住她内心的羞涩。\n";
            sequence << "你看着眼前的羞涩的她，内心不由得生起一丝心动...";
        } else {
            sequence << "以后说不定有什么变化呢...";
        }
        sequence << "Level 1 Complete!";
        startDialogSequence(sequence, S_LOADING_LEVEL2);
        break;
    }

    case S_LOADING_LEVEL2:
        textDisplay->setText(
            "        正在加载中...（记得按'F'继续对话）\n"
            "（小贴士：当女生对一个人有好感时，她会比男生想的更加主动！）\n");
        continueButton->show();
        break;

    case S_LV2_HIGH_FAVOR:
    {
        QStringList high;
        high << "你走在寂静的巷子中，不同以往的是，你的身边多了一个女生...";
        high << "天津的春天比以往的任何时候都要更冷一些,她唇间呼出的水汽蒸腾在昏黄的路灯下，渐渐地，渐渐地，消失在夜色之中。";
        high << "\"是不是有点冷？\" 你看着身边的沈冰悦，缓缓开口道。\n"
                "\"哦哦，没事的，谢谢你的关心。\" 她的手凑近了脸，利用呼出的余温让手暖和一些。";
        high << "你们在路上有一句没一句的聊天，你开始对她有一定的了解了，但似乎今天的路程比平时要短上不少，"
                "很快你便看到了不远处熟悉的灯火。\n"
                "\"看起来我要到家了...\" 你转过头对她说，\"早点休息，明天见。\"";
        high << "\"这样啊...\" 她的脸似乎僵住了，\"那个...\" 像是被什么东西咽住了，沈冰悦有些手足无措。\n"
                "\"怎么了吗？\"\n"
                "\"那个...关于上课的事情...谢谢你...\" 她脸有些微微发烫，显得很是可人。";
        high << "\"没事没事，‘举手’之劳。\"\n"
                "\"那...明天再见。\" 她留下一句话，就自己跑开了...后面的事你就记不清了，只记得那个晚上，她真的很漂亮。";
        startDialogSequence(high, S_LV2_NEXT_MORNING);
        break;
    }

    case S_LV2_NEXT_MORNING:
    {
        QStringList morning;
        morning << ">>第二天早上";
        // 根据好感度添加不同语句
        if (favorability >= 50) {
            morning.last() += "\n昨天的事情...像是一场梦一样...你的脸似乎也不由自主的开始发烫";
        } else {
            morning.last() += "\n似乎并没有与之前有什么不同...";
        }
        morning << "沈冰悦进入了教室，看起来，她比往常更加的漂亮了。";
        morning << "教室中男生的喧闹声随着她的经过变得逐渐安静，"
                   "男生们面面相觑，彼此心照不宣，几秒钟之后，却又开始笑话起彼此了。";
        morning << "沈冰悦走到我的面前，指甲轻触实木课桌，淡淡却又难以寻味的说：\"早上好啊...\" "
                   "你礼貌性的回复了她，却不由得多想一些了...\n";
        startDialogSequence(morning, S_END);
        break;
    }

    case S_END:
        textDisplay->setText("（剧情暂告一段落，感谢游玩！）");
        restartButton->show();
        quitButton->show();
        break;

    case S_FAIL:
        textDisplay->setText(
            "\"不好意思...让你困扰了吗...\"\n"
            "\"啊...我是...\"\n"
            "\"我还是去做到讲台旁边好了...\"\n\n"
            ">>你失败了！\n是否重来？");
        restartButton->show();
        quitButton->show();
        break;
    }
}

void GameWindow::startDialogSequence(const QStringList &texts, StoryState nextState)
{
    m_dialogueQueue = texts;
    m_dialogueIndex = 0;
    m_nextStateAfterDialogue = nextState;
    m_inDialogue = true;
    // 显示第一段文本
    if (!m_dialogueQueue.isEmpty()) {
        textDisplay->setText(m_dialogueQueue.at(0));
        m_dialogueIndex = 1;
    }
    continueButton->show();
    option1Button->hide();
    option2Button->hide();
    option3Button->hide();
}

void GameWindow::advanceDialogue()
{
    if (!m_inDialogue)
        return;

    if (m_dialogueIndex < m_dialogueQueue.size()) {
        textDisplay->setText(m_dialogueQueue.at(m_dialogueIndex));
        m_dialogueIndex++;
    } else {
        // 对话队列结束
        m_inDialogue = false;
        m_dialogueQueue.clear();
        setState(m_nextStateAfterDialogue);
    }
}

// ---- 槽函数 ----
void GameWindow::onContinueClicked()
{
    if (m_inDialogue) {
        advanceDialogue();
        return;
    }

    // 根据当前状态跳转
    switch (currentState) {
    case S_START:         setState(S_INTRO); break;
    case S_INTRO:         setState(S_TRANSFER_ASK); break;
    case S_TRANSFER_ASK:  setState(S_FIRST_CHOICE); break;
    case S_AFTER_ACCEPT:  setState(S_SUNLIGHT); break;
    case S_SUNLIGHT:      setState(S_NOTEBOOK); break;
    case S_NOTEBOOK:      setState(S_NEED_HELP); break;
    case S_NEED_HELP:     setState(S_SECOND_CHOICE); break;
    case S_POST_CHOICE_COMMON:  setState(S_EVENING_HOME); break;
    case S_LOADING_LEVEL2:
        // 根据好感度决定下一段剧情
        if (favorability >= 50) {
            setState(S_LV2_HIGH_FAVOR);
        } else {
            setState(S_LV2_NEXT_MORNING);
        }
        break;
    default: break;
    }
}

void GameWindow::onOption1Clicked()
{
    if (currentState == S_FIRST_CHOICE) {
        favorability += 10;
        textDisplay->setText(
            "\"当然可以啦。\" 你望着面前的同学说道。\n"
            "\"谢谢同学，以后请多关照哦...\"\n");
        setState(S_AFTER_ACCEPT);
    }
    else if (currentState == S_SECOND_CHOICE) {
        favorability += 5;
        textDisplay->setText(
            "\"我可以给你补。\" 你不假思索的对沈冰悦说道。\n"
            "\"啊...谢谢...\"\n");
        setState(S_POST_CHOICE_COMMON);
    }
}

void GameWindow::onOption2Clicked()
{
    if (currentState == S_FIRST_CHOICE) {
        // 犹豫后答应 → 失败
        setState(S_FAIL);
    }
    else if (currentState == S_SECOND_CHOICE) {
        favorability += 20;
        textDisplay->setText(
            "于是你开始不断创造帮助她的机会，上课时你看到她眉头紧锁，"
            "便主动举手向老师请教。久而久之，她似乎也察觉到了什么...\n");
        setState(S_POST_CHOICE_COMMON);
    }
}

void GameWindow::onOption3Clicked()
{
    if (currentState == S_FIRST_CHOICE) {
        // 严词拒绝 → 失败
        setState(S_FAIL);
    }
    else if (currentState == S_SECOND_CHOICE) {
        favorability -= 5;
        textDisplay->setText(
            "\"嗯呐，不好好补课可不行。\" 你忙着写题，有一句没一句的回应着。\n"
            "\"嗯...\"\n");
        setState(S_POST_CHOICE_COMMON);
    }
}

void GameWindow::onRestartClicked()
{
    resetGame();
}

void GameWindow::onQuitClicked()
{
    close();
}
