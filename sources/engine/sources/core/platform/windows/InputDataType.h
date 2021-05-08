#ifndef INPUT_DATA_TYPE
#define INPUT_DATA_TYPE

class MouseData
{
	public:

		MouseData(): x_axis(0.0f), y_axis(0.0f) {};
		MouseData(float x, float y): x_axis(x), y_axis(y) {};
		~MouseData() {};

		MouseData& operator=(const MouseData& copy)
		{
			x_axis = copy.x_axis;
			y_axis = copy.x_axis;

			return *this;
		}

		void Set(const float x, const float y) { x_axis = x; y_axis = y; };

		float GetX() const { return x_axis; };
		float GetY() const { return y_axis; };

	private:

		float x_axis;
		float y_axis;
};

#endif