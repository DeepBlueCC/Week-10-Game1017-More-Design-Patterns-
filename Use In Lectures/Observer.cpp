#include <iostream>
#include <vector>
#include <string>

class ObserverInterface
{
public:
	virtual void update(int message) = 0;
};

class SubjectInterface
{
public:
	virtual void subscribe(ObserverInterface*);
	virtual void unsubscribe(ObserverInterface*);
	virtual void notify(int message);
private:
	std::vector<ObserverInterface*> mObservers;
};

void SubjectInterface::subscribe(ObserverInterface* observer)
{
	mObservers.push_back(observer);
}

void SubjectInterface::unsubscribe(ObserverInterface* observer)
{
	int count = mObservers.size();
	int i;

	// Finds the observer and removes it
	for (i = 0; i < count; i++)
	{
		if (mObservers[i] == observer)
			break;
	}
	if (i < count)
		mObservers.erase(mObservers.begin() + i);
}

void SubjectInterface::notify(int msg)
{
	int count = mObservers.size();

	// Calling the update functions in the observers
	for (int i = 0; i < count; i++)
		mObservers[i]->update(msg);
}

class MySubject : public SubjectInterface
{
public:
	enum Message{HEY, BYE};		// Message in the form of enum
};

class MyObserver : public ObserverInterface
{
public:
	// Storing name of the observer
	explicit MyObserver(const std::string& str) : name(str) {}
	// Update shows observer got the message
	void update(int message)
	{
		std::cout << name << " got message " << message << std::endl;
	}
private:
	std::string name;
};

int main()
{
	// Instantiating observers
	MyObserver observerA("observerA");
	MyObserver observerB("observerB");
	MyObserver observerC("observerC");

	// Instantiating the subject and its subscribers
	MySubject subject;
	subject.subscribe(&observerA);
	subject.subscribe(&observerB); 
	subject.subscribe(&observerC);

	// Notifying subscribers
	subject.notify(MySubject::HEY);

	// Unsubscribing obersverB
	subject.unsubscribe(&observerB);
	std::cout << "\nobserverB unsubscribed...\n\n";

	// New notification with a different message
	subject.notify(MySubject::BYE);

	std::cin.get();
	return 0;
}






