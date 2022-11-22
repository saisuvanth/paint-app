#pragma once

#include <fstream>
#include <vector>
#include "Canvas.h"

class OpenFileDialogue
{

public:
	static bool show;
	static Button cancelButton;

	static std::vector<Button> fileButtons;
	static std::vector<Button> crossButtons;

	static std::string deletionPendingFileName;

	static void Show()
	{
		std::vector<std::string> files = FileManagement::GetList();
		for (int i = 0; i < fileButtons.size(); i++)
		{
			if (i < files.size())
			{
				fileButtons[i].text = files[i].c_str();
				fileButtons[i].Show();
				crossButtons[i].Show();
			}
			else
			{
				fileButtons[i].Hide();
				crossButtons[i].Hide();
			}
		}
		Cover::show = true;
		show = true;
		cancelButton.Show();
	}

	static void Hide()
	{
		Cover::show = false;
		show = false;
		cancelButton.Hide();
		for (int i = 0; i < fileButtons.size(); i++)
		{
			fileButtons[i].Hide();
			crossButtons[i].Hide();
		}
	}

	static void CancelPressed(Button button)
	{
		Hide();
	}

	static void SelectPressed(Button button)
	{
		std::string content = FileManagement::ReadFile(button.text);
		Canvas newCanvas = Canvas::Deserialize(content);
		currentCanvas = newCanvas;
		canvasAssigned = true;
		currentCanvas.fileName = button.text;
		Hide();
	}

	static void DeletePressed(Button button)
	{
		std::string fileName = "";
		for (int i = 0; i < fileButtons.size(); i++)
		{
			if (crossButtons[i].y_pos == button.y_pos)
			{
				fileName = fileButtons[i].text;
			}
		}
		YesNoDialogue::Show("Are you sure you want to delete " + fileName + ".dti?", DeleteConfirmedCallback);
		deletionPendingFileName = fileName; // << remember the file name so we can access it in the Callback function below
	}

	static void DeleteConfirmedCallback(Button button)
	{
		FileManagement::DeleteFile(deletionPendingFileName);
		Show();
	}

	static void Init()
	{
		show = false;
		cancelButton = Button::Create(0, 500, 100, 40, (char *)"Cancel", CancelPressed, false);
		for (int i = 0; i < 8; i++)
		{
			Button newButton = Button::Create(0, 160 + (i * 40), 300, 40, (char *)"asdf", SelectPressed, false);
			fileButtons.push_back(newButton);
			Button newCrossButton = Button::Create(0, 160 + (i * 40), 30, 40, (char *)"X", DeletePressed, false);
			crossButtons.push_back(newCrossButton);
		}
	}

	static void Display(int window_width, int window_height)
	{
		if (show)
		{
			char *text = (char *)"Select a file below to open it:";
			display_text(text, (window_width / 2) - (get_text_width(text) / 2), window_height - 100);
			char *textTwo = (char *)"(these are the .dti files in the application folder)";
			display_text_small(textTwo, (window_width / 2) - (get_text_width_small(textTwo) / 2), window_height - 140);
			cancelButton.HorizontallyCenter(window_width);
			cancelButton.Display(window_width, window_height);
			for (int i = 0; i < fileButtons.size(); i++)
			{
				fileButtons[i].HorizontallyCenter(window_width);
				fileButtons[i].Display(window_width, window_height);
				crossButtons[i].x_pos = fileButtons[i].x_pos + fileButtons[i].width;
				crossButtons[i].Display(window_width, window_height);
			}
		}
	}

	static bool Pressed(int button, int state, int x, int y)
	{
		if (show)
		{
			if (cancelButton.Pressed(button, state, x, y))
			{
				return true;
			}
			for (int i = 0; i < fileButtons.size(); i++)
			{
				if (fileButtons[i].Pressed(button, state, x, y))
				{
					return true;
				}
				if (crossButtons[i].Pressed(button, state, x, y))
				{
					return true;
				}
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
			for (int i = 0; i < fileButtons.size(); i++)
			{
				if (fileButtons[i].Hover(x, y))
				{
					output = true;
				}
				if (crossButtons[i].Hover(x, y))
				{
					output = true;
				}
			}
		}
		return output;
	}
};
