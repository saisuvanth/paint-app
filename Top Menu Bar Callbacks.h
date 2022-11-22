#pragma once

#include "Button.h"
#include "Cover.h"
#include "Open File Dialogue.h"
#include "Save File Dialogue.h"

void NewConfirmedCallback(Button button)
{
	canvasAssigned = true;
	currentCanvas = NewCanvas(500, 500, 100, 100);
}

void NewButtonPressed(Button button)
{
	if (canvasAssigned)
	{
		YesNoDialogue::Show("You will loose any unsaved changes. Continue?", NewConfirmedCallback);
	}
	else
	{
		canvasAssigned = true;
		currentCanvas = NewCanvas(500, 500, 100, 100);
	}
}

void OpenButtonPressed(Button button)
{
	OpenFileDialogue::Show();
}

void SaveButtonPressed(Button button)
{
	if (!canvasAssigned)
	{
		AlertDialogue::Alert("No canvas has been created. Create one before saving.");
		return;
	}
	if (currentCanvas.fileName == "")
	{
		SaveFileDialogue::Reset();
		SaveFileDialogue::Show();
		return;
	}
	FileManagement::WriteFile(currentCanvas.fileName, currentCanvas.Serialize());
	AlertDialogue::Alert("Saved to " + currentCanvas.fileName + ".dti");
}

void SaveAsButtonPressed(Button button)
{
	if (!canvasAssigned)
	{
		AlertDialogue::Alert("No canvas has been created. Create one before saving.");
		return;
	}
	SaveFileDialogue::Reset();
	SaveFileDialogue::Show();
}
