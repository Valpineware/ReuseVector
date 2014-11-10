#include <QString>
#include <QtTest>
#include <ReuseVector.h>
#include <string>

class ReuseVectorTests : public QObject
{
	Q_OBJECT

public:
	ReuseVectorTests();

private Q_SLOTS:
	void resizeCheckCapacity()
	{
		testResizeCapacity(0);
		testResizeCapacity(50);
		testResizeCapacity(8000);
	}


	void pushBackCheckSize()
	{
		ReuseVector<int> rv;
		QCOMPARE(rv.size(), 0U);

		rv.pushBack(45);
		QCOMPARE(rv.size(), 1U);

		rv.pushBack(77);
		QCOMPARE(rv.size(), 2U);
	}


	void frontAccess1()
	{
		ReuseVector<int> rv;
		rv.pushBack(4);
		rv.pushBack(77);
		QCOMPARE(rv.front(), 4);
	}


	void frontAccess2()
	{
		ReuseVector<std::string> rv;
		rv.pushBack("abc");
		rv.pushBack("bcd");
		rv.pushBack("cde");
		QCOMPARE(rv.front(), std::string("abc"));
	}


	void backAccess1()
	{
		ReuseVector<int> rv;
		rv.pushBack(45);
		QCOMPARE(rv.back(), 45);
	}


	void backAccess2()
	{
		ReuseVector<std::string> rv;
		rv.pushBack("Water");
		rv.pushBack("Salad");
		QCOMPARE(rv.back(), std::string("Salad"));
	}


    void iteratorToBegin()
    {
        ReuseVector<int> rv;
        rv.pushBack(50);
        ReuseVector<int>::Iterator iter = rv.begin();

        QCOMPARE(*iter, 50);
    }

    void iteratorToBegin2()
    {
        ReuseVector<int> rv;
        rv.pushBack(7);
        ReuseVector<int>::Iterator iter = rv.begin();

        QCOMPARE(*iter, 7);
    }


    void iteratorIncrement1()
    {
        ReuseVector<int> rv;
        rv.pushBack(50);
        rv.pushBack(300);

        ReuseVector<int>::Iterator iter = rv.begin();
        QCOMPARE(*(++iter), 300);
    }


    void iteratorIncrement2()
    {
        ReuseVector<std::string> rv;
        rv.pushBack("abc");
        rv.pushBack("lol");
        rv.pushBack("cpp");

        ReuseVector<std::string>::Iterator iter = rv.begin();
        ++iter;
        QCOMPARE(*(++iter), std::string("cpp"));
    }


	void iteratorSum()
	{
		ReuseVector<int> rv;
		rv.pushBack(10);
		rv.pushBack(20);
		rv.pushBack(44);

		QCOMPARE(*(rv.begin()+2), 44);
	}


	void iteratorDifference()
	{
		ReuseVector<int> rv;
		rv.pushBack(10);
		rv.pushBack(20);
		rv.pushBack(44);

		ReuseVector<int>::Iterator iter = rv.begin();
		++iter;

		QCOMPARE(*(iter-1), 10);
	}


	/////// COMPOUND ASSIGNMENT ///////
	ReuseVector<std::string> buildIteratorCompoundAssignmentVector()
	{
		ReuseVector<std::string> rv;
		rv.pushBack("Cow");
		rv.pushBack("Ballon");
		rv.pushBack("The Walking Dead");
		rv.pushBack("Rick");
		rv.pushBack("Zombie Extras Drinking Water");
		rv.pushBack("Gareth");

		return rv;
	}


	void iteratorAdditionAssignment()
	{
		ReuseVector<std::string> rv = buildIteratorCompoundAssignmentVector();
		QCOMPARE(*(rv.begin()+=3), std::string("Rick"));
	}


	void iteratorAdditionSubtractionAssignment()
	{
		ReuseVector<std::string> rv = buildIteratorCompoundAssignmentVector();
		ReuseVector<std::string>::Iterator iter = rv.begin();
		iter += 4;
		iter -= 2;
		QCOMPARE(*iter, std::string("The Walking Dead"));
	}


	/////// BASIC ITERATION ///////
	void iteratorBeginToEnd1()
	{
		ReuseVector<int> rv;
		rv.pushBack(10);
		rv.pushBack(20);
		rv.pushBack(44);

		ReuseVector<int>::Iterator iter = rv.begin();
		int sum = 0;	//sum of all values in rv

		while (iter != rv.end())
		{
			sum += *iter;
			++iter;
		}

		QCOMPARE(sum, 74);
	}


	void iteratorBeginToEnd2()
	{
		ReuseVector<int> rv;
		rv.pushBack(4);
		rv.pushBack(5);
		rv.pushBack(6);

		int sum = 0;	//sum of all values in rv

		ReuseVector<int>::Iterator iter = rv.begin();
		while (true)	//just testing a weird type of iteration here
		{
			if (iter == rv.end())
				break;

			sum += *iter;
			++iter;
		}

		QCOMPARE(sum, 15);
	}


	void erasePosition1()
	{
		ReuseVector<int> rv;
		rv.pushBack(3);
		rv.pushBack(68);

		rv.erase(rv.begin());

		QCOMPARE(rv.front(), 68);
		QCOMPARE(rv.size(), 1U);
	}


	void erasePosition2()
	{
		ReuseVector<std::string> rv;
		rv.pushBack("water");
		rv.pushBack("void");
		rv.pushBack("november");

		rv.erase(++rv.begin());

		QCOMPARE(rv.front(), std::string("water"));
		QCOMPARE(rv.size(), 2U);
	}


	void eraseRange1()
	{
		ReuseVector<int> rv;
		rv.pushBack(40);
		rv.pushBack(50);
		rv.pushBack(60);

		rv.erase(rv.begin(), rv.end());

		QCOMPARE(rv.size(), 0U);
	}

	void eraseRange2()
	{
		ReuseVector<std::string> rv;
		rv.pushBack("May");

		rv.erase(rv.begin(), rv.end());

		QCOMPARE(rv.size(), 0U);
	}

	void eraseRange3()
	{
		ReuseVector<std::string> rv;
		rv.pushBack("a");
		rv.pushBack("b");
		rv.pushBack("c");
		rv.pushBack("d");
		rv.pushBack("e");

		rv.erase(rv.begin()+1, rv.begin()+4);

		QCOMPARE(rv.size(), 2U);
		QCOMPARE(rv.front(), std::string("a"));
		QCOMPARE(rv.back(), std::string("e"));
	}

	void swap1()
	{
		ReuseVector<int> rv1;
		rv1.pushBack(556);
		rv1.pushBack(789);
		rv1.pushBack(9);

		ReuseVector<int> rv2;
		rv2.pushBack(2);
		rv1.swap(rv2);

		QCOMPARE(rv1.size(), 1U);
		QCOMPARE(rv1.front(), 2);
		QCOMPARE(rv2.size(), 3U);
		QCOMPARE(rv2.front(), 556);
		QCOMPARE(rv2.back(), 9);
	}


private:
	void testResizeCapacity(unsigned capacity)
	{
		ReuseVector<int> rv;
		rv.resize(capacity);

		QCOMPARE(rv.capacity(), capacity);
	}
};

ReuseVectorTests::ReuseVectorTests()
{
}



QTEST_APPLESS_MAIN(ReuseVectorTests)

#include "ReuseVectorTests.moc"
