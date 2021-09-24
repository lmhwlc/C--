#pragma once
#include<iostream>
#include<list>
using namespace std;

class Observer
{
public:
	virtual void Updata(int) = 0;
};

class Subject
{
	virtual void Attach(Observer*) = 0;
	virtual void Detach(Observer*) = 0;
	virtual void Notify() = 0;
};

class ConceretObserver1 : public Observer
{
private:
	Subject* m_pSubject;

public:
	ConceretObserver1(Subject* pSubject) : m_pSubject(pSubject) {}
	
	void Updata(int value) 
	{
		cout << "ob1 get the updata New State " << value << endl;
	}
};

class ConceretObserver2 : public Observer
{
private:
	Subject* m_pSubject;

public:
	ConceretObserver2(Subject* pSubject) : m_pSubject(pSubject) {}

	void Updata(int value)
	{
		cout << "ob2 get the updata New State " << value << endl;
	}
};

class ConceretObserver3 : public Observer
{
private:
	Subject* m_pSubject;

public:
	ConceretObserver3(Subject* pSubject) : m_pSubject(pSubject) {}

	void Updata(int value)
	{
		cout << "ob3 get the updata New State " << value << endl;
	}
};

class ConcreteSubject : public Subject
{
private:
	list<Observer*> m_ObserverList;
	int m_iState;

public:
	void SetState(int state)
	{
		m_iState = state;
	}

	void Attach(Observer* pObserver)
	{
		m_ObserverList.push_back(pObserver);
	}

	void Detach(Observer* pObserver)
	{
		m_ObserverList.remove(pObserver);
	}

	void Notify()
	{
		for (auto it : m_ObserverList)
		{
			it->Updata(m_iState);
		}
	}
};

