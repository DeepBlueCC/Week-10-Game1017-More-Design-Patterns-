#include <iostream>
#include <string>
#include <vector>

// A struct for all characters
struct Character
{
	double x = 0, y = 0;
	std::string name{ " " };
	Character(std::string _name) : name(_name) {	}
};

// Command base class
class Command
{
public:
	virtual void execute(Character&) = 0;
	virtual void undo(Character&) = 0;
};

// Taking a request and making it into a class
class Move : public Command
{
public:
	Move(double _x, double _y)
	{
		mx = _x;
		my = _y;
	}
	void execute(Character& c) override
	{
		c.x += mx;
		c.y += my;
		std::cout << c.name << " moves " << mx << ", " << my << std::endl;
	}
	void undo(Character& c) override
	{
		c.x -= mx;
		c.y -= my;
		std::cout << c.name << " undoes " << -mx << ", " << -my << std::endl;
	}
private:
	double mx, my;
};

int main()
{
	Character mike("Mike");
	std::vector<Command*> command_queue;

	// Initial position of mike
	std::cout << mike.x << ", " << mike.y << std::endl;

	// Stores commands from event handler
	command_queue.push_back(new Move(1, 2));
	command_queue.push_back(new Move(-3.5, 5));
	command_queue.push_back(new Move(22, 30));

	// Executing moves
	for (int i = 0; i < command_queue.size(); i++)
	{
		command_queue[i]->execute(mike);
		std::cout << mike.x << ", " << mike.y << std::endl;
	}

	std::cout << std::endl;

	// Undoing moves
	for (int i = command_queue.size() - 1; i >= 0; i--)
	{
		command_queue[i]->undo(mike);
		std::cout << mike.x << ", " << mike.y << std::endl;
	}

	return 0;
}