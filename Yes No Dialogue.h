#pragma once

class YesNoDialogue
{

public:
	static bool show;
	static Button yesButton;
	static Button noButton;
	static std::string message;

	static Callback yesCallback;

	static void Show(std::string m, Callback callback)
	{
		message = m;
		yesCallback = callback;
		show = true;
		yesButton.Show();
		noButton.Show();
	}

	static void Hide()
	{
		show = false;
		yesButton.Hide();
		noButton.Hide();
	}

	static void YesPressed(Button button)
	{
		Hide();
		if (yesCallback)
		{
			(*yesCallback)(yesButton);
		}
	}

	static void NoPressed(Button button)
	{
		Hide();
	}

	static void Init()
	{
		noButton = Button::Create(0, 140, 100, 40, (char *)"No", NoPressed, true);
		yesButton = Button::Create(0, 140, 100, 40, (char *)"Yes", YesPressed, true);
	}

	static void Display(int window_width, int window_height)
	{
		if (show)
		{
			glBegin(GL_QUADS);
			glColor4f(0.0f, 0.0f, 0.0f, 0.85f);
			glVertex2f(0, window_height);
			glVertex2f(0 + window_width, window_height);
			glVertex2f(0 + window_width, 0);
			glVertex2f(0, 0);
			glEnd();

			display_text(message, (window_width / 2) - (get_text_width(message) / 2), window_height - 100);

			noButton.HorizontallyCenter(window_width);
			noButton.x_pos -= 55;
			yesButton.HorizontallyCenter(window_width);
			yesButton.x_pos += 55;
			noButton.Display(window_width, window_height);
			yesButton.Display(window_width, window_height);
		}
	}

	static bool Pressed(int button, int state, int x, int y)
	{
		if (show)
		{
			if (noButton.Pressed(button, state, x, y))
			{
				return true;
			}
			if (yesButton.Pressed(button, state, x, y))
			{
				return true;
			}
			return true;
		}
		return false;
	}

	static bool Hover(int x, int y)
	{
		bool output = false;
		if (show)
		{
			if (noButton.Hover(x, y))
			{
				output = true;
			}
			if (yesButton.Hover(x, y))
			{
				output = true;
			}
			return true;
		}
		return false;
	}
};
