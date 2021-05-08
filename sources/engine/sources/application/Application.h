#ifndef APP_MANAGER
#define APP_MANAGER

class Application
{
	public:

		 Application();
		 virtual ~Application() {};
	  
		 virtual void Init() {};
		 virtual void Update() {};
		 virtual void Draw() {};
		 virtual void Close() {};

		 bool IsRunning() { return is_running; }

	protected:

		 /* App is running or not ? */
		 bool is_running;

	private:

		 Application(const Application &copy) {};
		 const Application & operator=(const Application &copy) {};	
};

#endif