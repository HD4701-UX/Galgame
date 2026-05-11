#ifndef GALGAME_H
#define GALGAME_H

#include <QWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStringList>
#include<QLabel>
#include<QPixmap>      //加入图片


class GameWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();
protected:
    void resizeEvent(QResizeEvent *event)override;

private slots:
    void onContinueClicked();
    void onOption1Clicked();
    void onOption2Clicked();
    void onOption3Clicked();
    void onRestartClicked();
    void onQuitClicked();

private:
    enum StoryState {
        S_START,
        S_INTRO,
        S_TRANSFER_ASK,
        S_FIRST_CHOICE,
        S_AFTER_ACCEPT,
        S_SUNLIGHT,
        S_NOTEBOOK,
        S_NEED_HELP,
        S_SECOND_CHOICE,
        S_POST_CHOICE_COMMON,    // 等待继续以进入回家剧情
        S_EVENING_HOME,        // 回家晚场景（内部使用对话队列）
        S_EVENING_BEHOME,      //独自回家BE
        S_EVENING_PART1,        //平常的夜晚
        S_EVENING_PART2_IF_HIGH,//被少女叫住
        S_EVENING_PART2_LOW,     //“以后说不定有什么变化”
        S_EVENING_PART3,        //男主心动
        S_LOADING_LEVEL2,        // 加载中提示
        S_LV2_HIGH_FAVOR,        // 好感≥50回家同行序列（队列）
        S_LV2_HIGH_FAVOR_PART2,  //少女呼白气
        S_LV2_HIGH_FAVOR_PART3,  //二人分别
        S_LV2_NEXT_MORNING,      //第二天早上序列（队列）
        S_LV2_NEXT_MORNING_PART2,//全员被迷住
        S_LV2_NEXT_MORNING_PART3,//主动打招呼
        S_END,
        S_FAIL
    };

    void setState(StoryState state);
    void updateUI();
    void resetGame();

    // 对话队列辅助
    void startDialogSequence(const QStringList &texts, StoryState nextState);
    void advanceDialogue();
    void setBackgroundImage(const QString &imagePath); //切换图片
//    void resizeEvent();
    //新增图片显示控件
    QLabel *backgroundLabel;
    QTextEdit *textDisplay;

    QPushButton *continueButton;
    QPushButton *option1Button;
    QPushButton *option2Button;
    QPushButton *option3Button;
    QPushButton *restartButton;
    QPushButton *quitButton;

    QVBoxLayout *mainLayout;
    QHBoxLayout *buttonLayout;

    int favorability;
    StoryState currentState;

    // 对话队列成员
    QStringList m_dialogueQueue;
    int m_dialogueIndex;
    StoryState m_nextStateAfterDialogue;
    bool m_inDialogue;
};

#endif // GALGAME_H
