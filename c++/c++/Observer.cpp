#include"Observer.h"

void ObserverTest()
{
	ConcreteSubject *subject = new ConcreteSubject();
	ConceretObserver1 *ob1 = new ConceretObserver1(subject);
	ConceretObserver2 *ob2 = new ConceretObserver2(subject);
	//ע��۲��ߺͱ��۲���
	subject->SetState(2);
	subject->Attach(ob1);
	subject->Attach(ob2);
	subject->Notify();
	subject->SetState(1);
	subject->Notify();
	//ע�����۲���
	subject->Detach(ob2);
	subject->SetState(3);
	subject->Notify();
	//�������۲���
	ConceretObserver3 *ob3 = new ConceretObserver3(subject);
	subject->Attach(ob3);
	subject->Notify();
	delete ob1;
	delete ob2;
	delete ob3;
	delete subject;
}