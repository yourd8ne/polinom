#include "pch.h"
#include "CppUnitTest.h"
#include "../main/Polinom.h"
//#include "../main/Monom.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestPolimom
{
	TEST_CLASS(TestPolinom)
	{
	public:
		
        TEST_METHOD(correct_ipnut)
        {
            string s1 = "x^3y^2z^3", s2 = "-2xyz", s3 = "+z";

            Polinom p(s1 + s2 + s3);

            Monom m1, m2, m3;
            istringstream m_in_1(s1); m_in_1 >> m1;
            istringstream m_in_2(s2); m_in_2 >> m2;
            istringstream m_in_3(s3); m_in_3 >> m3;

            List list;
            list.add(m1);
            list.add(m2);
            list.add(m3);

            Link* i = p.getList().getStart()->next;
            Link* j = list.getStart()->next;

            while (i != p.getList().getStart() && j != list.getStart()) {
                Assert::IsTrue(i->m.isEqual(j->m));
                i = i->next;
                j = j->next;
            }
        }
        TEST_METHOD(sum)
        {
            Polinom p1("3+x^2yz-y^6");
            Polinom p2("-3+xyz");

            Polinom p3(p1 + p2);
            ostringstream m_out;
            m_out << p3;
            string a = "x^2yz+xyz-y^6";
            Assert::AreEqual(a, m_out.str());
        }
        TEST_METHOD(subtr)
        {
            Polinom p1("3+x^2yz-y^6");
            Polinom p2("-3+xyz");

            Polinom p3(p1 - p2);
            ostringstream m_out;
            m_out << p3;

            Assert::IsTrue("x^2yz-xyz-y^6+6" == m_out.str());
        }
        TEST_METHOD(mult)
        {
            Polinom p1("3+x^2yz-y^6");
            Polinom p2("-3");

            Polinom p3(p1 * p2);
            ostringstream m_out;
            m_out << p3;

            Assert::IsTrue("-3x^2yz+3y^6-9" == m_out.str());
        }
	};
    TEST_CLASS(TestMonom)
    {
    public:

        TEST_METHOD(correct_input)
        {
            Monom m;
            istringstream m_in("-xyz^10"); m_in >> m;

            Assert::IsTrue(m.coef == -1);
            Assert::AreEqual(m.s, 9062);
        }
        TEST_METHOD(mult_monoms)
        {
            Monom m1, m2;
            istringstream m_in_1("4xyz"); m_in_1 >> m1;
            istringstream m_in_2("x^2y"); m_in_2 >> m2;

            Monom m3(m1 * m2);

            Monom m4;
            istringstream m_in_4("4x^3y^2z"); m_in_4 >> m4;

            Assert::AreEqual(m4.coef, m3.coef);
            Assert::AreEqual(m4.s, m3.s);
        }
        TEST_METHOD(test)
        {
            /*Monom m1, m2;
            istringstream m_in_1("y^5"); Assert::Fail(m_in_1 >> m1);
            istringstream m_in_2("y^6"); m_in_2 >> m2;

            
            Assert::Fail(m1 * m2);*/
        }

        TEST_METHOD(not_equal_monoms)
        {
            Monom m1;
            istringstream m_in_1("10xy^-5z"); m_in_1 >> m1;

            Monom m2;
            istringstream m_in_2("9y^5z"); m_in_2 >> m2;

            Assert::IsFalse(m1.isEqual(m2));
        }
        TEST_METHOD(equal_monoms)
        {
            Monom m1;
            istringstream m_in("10xy^-5z"); m_in >> m1;

            Monom m2(m1);
            Assert::IsTrue(m1.isEqual(m2));
        }
    };
}
