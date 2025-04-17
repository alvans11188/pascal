//Compartir valores entre hilos mediante clases
#include<iostream>
#include<thread>
using namespace std;
class Task
{
	public:
		void execute(std::string command)
		{
			for(int i=0;i<5;i++)
			{
				std::cout<<command<<" :: "<<i<<"\n";
			}
		}
};

int main()
{
	Task * taskPtr = new Task();
	std::thread th(&Task::execute,taskPtr,"Emitir trabajo");
	th.join();
	delete taskPtr;
	return 0;
}