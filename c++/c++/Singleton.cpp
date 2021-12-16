#include"Singleton.h"

SingletonA* SingletonA::pInstance = nullptr;
SingletonB SingletonB::instance;

void SingletonTest()
{
	//¿¡∫∫ Ω≤‚ ‘
	cout << "∂ˆ∫∫ Ωµ•¿˝ƒ£ Ω≤‚ ‘ £∫" << endl << endl;
	SingletonA *pA1 = SingletonA::getInstanceA();
	pA1->set(2);
	pA1->show();
	SingletonA *pA2 = SingletonA::getInstanceA();
	pA2->set(3);
	pA1->show();
	cout << pA1 << endl;
	cout << pA2 << endl;
	
	cout << endl << endl;

	cout << "¿¡∫∫ Ωµ•¿˝ƒ£ Ω≤‚ ‘ £∫" << endl << endl;
	//∂ˆ∫∫ Ω≤‚ ‘
	SingletonB *pB1 = SingletonB::getInstanceB();
	pB1->set(2);
	pB1->show();
	SingletonB *pB2 = SingletonB::getInstanceB();
	pB2->set(3);
	pB1->show();
	cout << pB1 << endl;
	cout << pB2 << endl;
}