#pragma once

class AlertDialogue
{

public:
	static bool show;
	static Button okButton;
	static std::string message;

	static void Alert(std::string m)
	{
		message = m;
		show = true;
		okButton.Show();
		Cover::show = true;
	}

	static void Hide()
	{
		show = false;
		okButton.Hide();
		Cover::show = false;
	}

	static void OkPressed(Button button)
	{
		Hide();
	}

	static void Init()
	{
		okButton = Button::Create(0, 140, 100, 40, (char *)"Ok", OkPressed, true);
		Alert("Welcome to this 2D Drawing Tool. Press \"New\" to get started.");
	}

	static void Display(int window_width, int window_height)
	{
		if (show)
		{
			display_text(message, (window_width / 2) - (get_text_width(message) / 2), window_height - 100);
			okButton.HorizontallyCenter(window_width);
			okButton.Display(window_width, window_height);
		}
	}

	static bool Pressed(int button, int state, int x, int y)
	{
		if (show)
		{
			if (okButton.Pressed(button, state, x, y))
			{
				return true;
			}
		}
		return false;
	}

	static bool Hover(int x, int y)
	{
		bool output = false;
		if (show)
		{
			if (okButton.Hover(x, y))
			{
				output = true;
			}
		}
		return output;
	}
};