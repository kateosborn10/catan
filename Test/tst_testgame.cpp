#include <QString>
#include <QtTest>

class TestGame : public QObject
{
    Q_OBJECT

public:
    TestGame();

private Q_SLOTS:
    void testCase1();
};

TestGame::TestGame()
{
}

void TestGame::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(TestGame)

#include "tst_testgame.moc"
