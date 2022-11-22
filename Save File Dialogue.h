#pragma once

#include "Canvas.h"
#include <iostream>
#include <fstream>
#include <string>

class SaveFileDialogue
{

public:
	static bool show;
	static Button cancelButton;
	static Button saveButton;
	static std::string fileName;
	static bool showTooLongText;

	static void Reset()
	{
		fileName = "";
		saveButton.Hide();
		showTooLongText = false;
	}

	static void Show()
	{
		Cover::show = true;
		show = true;
		cancelButton.Show();
	}

	static void Hide()
	{
		Cover::show = false;
		show = false;
		cancelButton.Hide();
	}

	static void CancelPressed(Button button)
	{
		Hide();
	}

	static void SavePressed(Button button)
	{
		if ((fileName.size() > 0) && (fileName.size() < 40))
		{
			if (FileManagement::CheckExists(fileName))
			{
				YesNoDialogue::Show("File already exists. Overwrite?", SaveOverwriteCallback);
				return;
			}
			FileManagement::WriteFile(fileName, currentCanvas.Serialize());
			currentCanvas.fileName = fileName;
			Hide();
		}
	}

	static void SaveOverwriteCallback(Button button)
	{
		FileManagement::WriteFile(fileName, currentCanvas.Serialize());
		currentCanvas.fileName = fileName;
		Hide();
	}

	static void Init()
	{
		show = false;
		cancelButton = Button::Create(0, 200, 100, 40, (char *)"Cancel", CancelPressed, false);
		saveButton = Button::Create(0, 200, 75, 40, (char *)"Save", SavePressed, false);
	}

	static void Display(int window_width, int window_height)
	{
		if (show)
		{
			char *text = (char *)"Type in a file name to save it:";
			display_text(text, (window_width / 2) - (get_text_width(text) / 2), window_height - 100);
			display_text(fileName, (window_width / 2) - (get_text_width(fileName) / 2), window_height - 155);
			if (showTooLongText)
			{
				char *text2 = (char *)"40 character file name limit";
				display_text_small(text2, (window_width / 2) - (get_text_width_small(text2) / 2), window_height - 184);
			}
			cancelButton.HorizontallyCenter(window_width);
			cancelButton.x_pos -= 55;
			saveButton.HorizontallyCenter(window_width);
			saveButton.x_pos += 65;
			cancelButton.Display(window_width, window_height);
			saveButton.Display(window_width, window_height);
		}
	}

	static bool Pressed(int button, int state, int x, int y)
	{
		if (show)
		{
			// pass the event on to cancel and save buttons
			if (cancelButton.Pressed(button, state, x, y))
			{
				return true;
			}
			if (saveButton.Pressed(button, state, x, y))
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
			if (cancelButton.Hover(x, y))
			{
				output = true;
			}
			if (saveButton.Hover(x, y))
			{
				output = true;
			}
		}
		return output;
	}

	static bool KeyboardPressed(unsigned char key, int x, int y)
	{
		if (show)
		{
			std::string allowedChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-_+=[]{}!�$^&()`�,;@' ";
			if (allowedChars.find(key) != std::string::npos)
			{
				saveButton.Show();
				if (fileName.size() < 40)
				{
					fileName += key;
				}
				else
				{
					showTooLongText = true;
				}
				return true;
			}
			if (key == '\b')
			{
				if (fileName.size() > 0)
				{
					fileName = fileName.substr(0, fileName.size() - 1);
				}
				if (fileName.size() == 0)
				{
					saveButton.Hide();
				}
				showTooLongText = false;
				return true;
			}
		}
		return false;
	}
};
