#include"Observer.h"

void ObserverTest()
{
	ConcreteSubject *subject = new ConcreteSubject();
	ConceretObserver1 *ob1 = new ConceretObserver1(subject);
	ConceretObserver2 *ob2 = new ConceretObserver2(subject);
	//注册观察者和被观察者
	subject->SetState(2);
	subject->Attach(ob1);
	subject->Attach(ob2);
	subject->Notify();
	subject->SetState(1);
	subject->Notify();
	//注销被观察者
	subject->Detach(ob2);
	subject->SetState(3);
	subject->Notify();
	//新增被观察者
	ConceretObserver3 *ob3 = new ConceretObserver3(subject);
	subject->Attach(ob3);
	subject->Notify();
	delete ob1;
	delete ob2;
	delete ob3;
	delete subject;
}