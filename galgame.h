#ifndef GALGAME_H
#define GALGAME_H

#include <QWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStringList>

class GameWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

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
        S_EVENING_HOME,          // 回家晚场景（内部使用对话队列）
        S_LOADING_LEVEL2,        // 加载中提示
        S_LV2_HIGH_FAVOR,        // 好感≥50回家同行序列（队列）
        S_LV2_NEXT_MORNING,      // 第二天早上序列（队列）
        S_END,
        S_FAIL
    };

    void setState(StoryState state);
    void updateUI();
    void resetGame();

    // 对话队列辅助
    void startDialogSequence(const QStringList &texts, StoryState nextState);
    void advanceDialogue();

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
